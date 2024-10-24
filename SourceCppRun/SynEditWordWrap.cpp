#include <vcl.h>
#pragma hdrstop

#include "SynEditWordWrap.h"
#include "SynUnicode.h"
#include <System.RTLConsts.hpp>
#include "SynEditMiscProcs.h"
#include <System.Math.hpp>
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Syneditmiscprocs;
using namespace Synedittextbuffer;
using namespace Synedittypes;
using namespace Synunicode;
using namespace System;
using namespace System::Math;
using namespace System::Rtlconsts;

namespace Syneditwordwrap
{

__fastcall TSynWordWrapPlugin::TSynWordWrapPlugin() {}



/* TSynWordWrapPlugin */

TDisplayCoord __fastcall TSynWordWrapPlugin::BufferToDisplayPos(const TBufferCoord& aPos)
{
	TDisplayCoord result = {};
	int vStartRow = 0; // first row of the line
	int cRow = 0;
	int vRowLen = 0;
	int stop = 0;
	Assert(aPos.Char > 0);
	Assert(aPos.Line > 0);
	if(fLineCount < aPos.Line)
    // beyond EOF
	{
		result.Column = aPos.Char;
		result.Row = RowCount() + (aPos.Line - fLineCount);
		return result;
	}
	if(aPos.Line == 1)
		vStartRow = 0;
	else
		vStartRow = (*fLineOffsets)[aPos.Line - 2];
	vRowLen = 0;
	for(stop = (*fLineOffsets)[aPos.Line - 1] - 1, cRow = vStartRow; cRow <= stop; cRow++)
	{
		vRowLen += (*fRowLengths)[cRow];
		if(aPos.Char <= vRowLen)
		{
			result.Column = aPos.Char - vRowLen + (*fRowLengths)[cRow];
			result.Row = cRow + 1;
			return result;
		}
	}
  // beyond EOL
	result.Column = aPos.Char - vRowLen + (*fRowLengths)[(*fLineOffsets)[aPos.Line - 1] - 1];
	result.Row = (*fLineOffsets)[aPos.Line - 1];
	return result;
}

__fastcall TSynWordWrapPlugin::TSynWordWrapPlugin(TCustomSynEdit* aOwner)
 : fLineOffsets(nullptr),
			fRowLengths(nullptr),
			fLineCapacity(0),
			fRowCapacity(0),
			fLineCount(0),
			fEditor(nullptr),
			fMinRowLength(0),
			fMaxRowLength(0)
{
	//# inherited::Create(); // just to work as reminder in case I revert it to a TComponent...
	if(aOwner == nullptr)
		throw new Exception(L"Owner of TSynWordWrapPlugin must be a TCustomSynEdit");
	fEditor = aOwner;
	fLineCount = fEditor->Lines->Count;
	Reset();
}

__fastcall TSynWordWrapPlugin::~TSynWordWrapPlugin()
{
	// inherited;
	FreeMemory(fLineOffsets);
	FreeMemory(fRowLengths);
}

void __fastcall TSynWordWrapPlugin::DisplayChanged()
{
	if(Editor->CharsInWindow != fMaxRowLength)
		Reset();
}

TBufferCoord __fastcall TSynWordWrapPlugin::DisplayToBufferPos(const TDisplayCoord& aPos)
{
	TBufferCoord result = {};
	int cLine = 0;
	int cRow = 0;
	int stop = 0;
	Assert(aPos.Column > 0);
	Assert(aPos.Row > 0);
	if(aPos.Row > RowCount())
    // beyond EOF
	{
		result.Char = aPos.Column;
		result.Line = aPos.Row - RowCount() + fLineCount;
		return result;
	}
  //todo: use a binary search or something smarter
	for(stop = 0, cLine = fLineCount - 2; cLine >= stop; cLine--)
	{
		if(aPos.Row > (*fLineOffsets)[cLine])
		{
			int stop1 = 0;
			result.Line = cLine + 2;
			if(aPos.Row == (*fLineOffsets)[cLine + 1]) //last row of line
				result.Char = Min(aPos.Column, fMaxRowLength + 1);
			else
				result.Char = Min(aPos.Column, (*fRowLengths)[aPos.Row - 1] + 1);
			for(stop1 = aPos.Row - 2, cRow = (*fLineOffsets)[cLine]; cRow <= stop1; cRow++)
			{
				result.Char += (*fRowLengths)[cRow];
			}
			return result;
		}
	}
  // first line
	result.Line = 1;
	if(aPos.Row == (*fLineOffsets)[0]) //last row of line
		result.Char = Min(aPos.Column, fMaxRowLength + 1);
	else
		result.Char = Min(aPos.Column, (*fRowLengths)[aPos.Row - 1] + 1);
	for(stop = aPos.Row - 2, cRow = 0; cRow <= stop; cRow++)
	{
		result.Char += (*fRowLengths)[cRow];
	}
	return result;
}
// aRow is 1-based...

int __fastcall TSynWordWrapPlugin::GetRowLength(int aRow)
{
	int result = 0;
	if((aRow <= 0) || (aRow > RowCount()))
		TList::Error(System_Rtlconsts_SListIndexError, aRow);
	result = (int) (*fRowLengths)[aRow - 1];
	return result;
}

void __fastcall TSynWordWrapPlugin::GrowLines(int aMinSize)
{
	const int vStepSize = 256;
	if(aMinSize <= 0)
		aMinSize = 1;
	if(aMinSize > fLineCapacity)
	{
		aMinSize = aMinSize + vStepSize - (aMinSize % vStepSize);
		fLineOffsets = (PRowIndexArray) ReallocMemory(fLineOffsets, aMinSize * sizeof(TRowIndex));
		fLineCapacity = aMinSize;
	}
}

void __fastcall TSynWordWrapPlugin::GrowRows(int aMinSize)
{
	const int vStepSize = 512;
	if(aMinSize <= 0)
		aMinSize = 1;
	if(aMinSize > fRowCapacity)
	{
		aMinSize = aMinSize + vStepSize - (aMinSize % vStepSize);
		fRowLengths = (PRowLengthArray) ReallocMemory(fRowLengths, aMinSize * sizeof(TRowLength));
		fRowCapacity = aMinSize;
	}
}

int __fastcall TSynWordWrapPlugin::LinesDeleted(int aIndex, int aCount)
{
	int result = 0;
	int vStartRow = 0;
	int vEndRow = 0;
	int cLine = 0;
	int stop = 0;
	if(fMaxRowLength == 0)
	{
		result = 0;
		return result;
	}
	Assert(aIndex >= 0);
	Assert(aCount >= 1);
	Assert(aIndex + aCount <= fLineCount);
	if(aIndex == 0)
		vStartRow = 0;
	else
		vStartRow = (*fLineOffsets)[aIndex - 1];
	vEndRow = (*fLineOffsets)[aIndex + aCount - 1];
	result = vEndRow - vStartRow;
  // resize fRowLengths
	if(vEndRow < RowCount())
		MoveRows((TRowIndex) vEndRow, -result);
  // resize fLineOffsets
	MoveLines((TLineIndex) (aIndex + aCount), -aCount);
	fLineCount -= aCount;
  // update offsets
	for(stop = fLineCount - 1, cLine = aIndex; cLine <= stop; cLine++)
	{
		(*fLineOffsets)[cLine] -= result;
	}
	if(fLineCount == 0)
		SetEmpty();
	return result;
}

int __fastcall TSynWordWrapPlugin::LinesInserted(int aIndex, int aCount)
{
	int result = 0;
	TRowIndex vPrevOffset = (TRowIndex) 0;
	int cLine = 0;
	int stop = 0;
	if(fMaxRowLength == 0)
	{
		result = 0;
		return result;
	}
	Assert(aIndex >= 0);
	Assert(aCount >= 1);
	Assert(aIndex <= fLineCount);
  // resize fLineOffsets
	GrowLines(fLineCount + aCount);
	if(aIndex < fLineCount) // no need for MoveLines if inserting at LineCount (TSynEditStringList.Add)
	{
		fLineCount += aCount; // fLineCount must be updated before calling MoveLines()
		MoveLines((TLineIndex) aIndex, aCount);
	}
	else
	fLineCount += aCount; 
  // set offset to same as previous line (i.e. the line has 0 rows)
	if(aIndex == 0)
		vPrevOffset = (TRowIndex) 0;
	else
		vPrevOffset = (*fLineOffsets)[aIndex - 1];
	for(stop = aIndex + aCount - 1, cLine = aIndex; cLine <= stop; cLine++)
	{
		(*fLineOffsets)[cLine] = vPrevOffset;
	}
  // Rewrap
	result = 0;
	for(stop = aIndex + aCount - 1, cLine = aIndex; cLine <= stop; cLine++)
	{
		result += ReWrapLine((TLineIndex) cLine);
	}
	return result;
}

int __fastcall TSynWordWrapPlugin::LinePut(int aIndex, const String OldLine)
{
	int result = 0;
	if(fMaxRowLength == 0)
	{
		result = 0;
		return result;
	}
	Assert(aIndex >= 0);
	Assert(aIndex < fLineCount);
  // Rewrap
	result = 0;
	result += ReWrapLine((TLineIndex) aIndex);
	return result;
}

void __fastcall TSynWordWrapPlugin::MoveLines(TLineIndex aStart, int aMoveBy)
{
	int vMoveCount = 0;
	Assert(aMoveBy != 0);
	Assert(aStart + aMoveBy >= 0);
	Assert(aStart + aMoveBy < fLineCount);
	vMoveCount = fLineCount - aStart;
	if(aMoveBy > 0)
		vMoveCount -= aMoveBy;
	Move(&(*fLineOffsets)[aStart], &(*fLineOffsets)[aStart + aMoveBy], vMoveCount * sizeof(TRowIndex));
}

void __fastcall TSynWordWrapPlugin::MoveRows(TRowIndex aStart, int aMoveBy)
{
	int vMoveCount = 0;
	Assert(aMoveBy != 0);
	Assert(aStart + aMoveBy >= 0);
	Assert(aStart + aMoveBy < RowCount());
	vMoveCount = RowCount() - aStart;
	if(aMoveBy > 0)
		vMoveCount -= aMoveBy;
	Move(&(*fRowLengths)[aStart], &(*fRowLengths)[aStart + aMoveBy], vMoveCount * sizeof(TRowLength));
}

void __fastcall TSynWordWrapPlugin::Reset()
{
	Assert(Editor->CharsInWindow >= 0);
	fMaxRowLength = (TRowLength) Editor->CharsInWindow;
	fMinRowLength = (TRowLength) (Editor->CharsInWindow - ((int)(Editor->CharsInWindow / /*div*/ 3)));
	if(fMinRowLength <= 0)
		fMinRowLength = 1;
	WrapLines();
}
// Returns RowCount delta (how many wrapped lines were added or removed by this change).

int __fastcall TSynWordWrapPlugin::ReWrapLine(TLineIndex aIndex)
{
	int result = 0;
	unsigned int vMaxNewRows = 0;
	String vLine;
	int vLineRowCount = 0; //numbers of rows parsed in this line
	PRowLengthArray vTempRowLengths = nullptr;
	PWideChar vRowBegin = nullptr;
	PWideChar vLineEnd = nullptr;
	PWideChar vRowEnd = nullptr;
	PWideChar vRunner = nullptr;
	PWideChar vRowMinEnd = nullptr;
	PWideChar vLastVisibleChar = nullptr;
	int vStartRow = 0; // first row of the line
	int vOldNextRow = 0; // first row of the next line, before the change
	int cLine = 0;
	PRowIndexArray p = nullptr;
  // ****** First parse the new string using an auxiliar array *****
	vLine = ((TSynEditStringList*) Editor->Lines)->ExpandedStrings[aIndex];
	vLine = Editor->ExpandAtWideGlyphs(vLine);
  // Pre-allocate a buffer for rowlengths - at least one row
	vMaxNewRows = (unsigned int) Max(((int)((vLine.Length() - 1) / /*div*/ fMinRowLength)) + 1, 1);
	vTempRowLengths = ((PRowLengthArray) AllocMem(vMaxNewRows * sizeof(TRowLength)));
	try
	{
		vLineRowCount = 0;
		vRowBegin = ustr2pwchar(vLine);
		vRowEnd = vRowBegin + fMaxRowLength;
		vLineEnd = vRowBegin + vLine.Length();
		while(vRowEnd < vLineEnd)
		{
			vRowMinEnd = vRowBegin + fMinRowLength;
			vRunner = vRowEnd - 1;
			while(vRunner > vRowMinEnd)
			{
				if(Editor->IsWordBreakChar((*vRunner)))
				{
					vRowEnd = vRunner + 1;
					break;
				}
				--vRunner;
			}
      // do not cut wide glyphs in half
			if(vRowEnd > vRowBegin)
			{
				vLastVisibleChar = vRowEnd - 1;
				while(((*vLastVisibleChar) == FillerChar) && (vLastVisibleChar > vRowBegin))
					--vLastVisibleChar;
				vRowEnd = vLastVisibleChar + 1;
			}

      // Finally store the rowlength
			(*vTempRowLengths)[vLineRowCount] = (TRowLength) (vRowEnd - vRowBegin);
			++vLineRowCount;
			vRowBegin = vRowEnd;
			vRowEnd += fMaxRowLength;
		} //endwhile vRowEnd < vLineEnd
		if((vLineEnd > vRowBegin) || (vLine.Length() == 0))
		{
			(*vTempRowLengths)[vLineRowCount] = (TRowLength) (vLineEnd - vRowBegin);
			++vLineRowCount;
		}

    // ****** Then updates the main arrays ******
		if(aIndex == 0)
			vStartRow = 0;
		else
			vStartRow = (*fLineOffsets)[aIndex - 1];
		vOldNextRow = (*fLineOffsets)[aIndex];
		result = vLineRowCount - (vOldNextRow - vStartRow);
		if(result != 0)
      // MoveRows depends on RowCount, so we need some special processing...
		{
			if(result > 0)
        // ...if growing, update offsets (and thus RowCount) before rowlengths
			{
				GrowRows(RowCount() + result);
				if(result == 1)
          // EG: this makes Schlemiel run twice as fast, but doesn't solve
          // the algorithmic issue if someone can spend some time looking
          // at the big picture... there are huge speedups to be made by
          // eliminating this loop
				{
					int stop = 0;
					p = fLineOffsets;
					for(stop = fLineCount - 1, cLine = aIndex; cLine <= stop; cLine++)
					{
						++(*p)[cLine];
					}
				}
				else
				{
					int stop = 0;
					p = fLineOffsets;
					for(stop = fLineCount - 1, cLine = aIndex; cLine <= stop; cLine++)
					{
						(*p)[cLine] += result;
					}
				}
				if(vOldNextRow < RowCount() - result)
					MoveRows((TRowIndex) vOldNextRow, result);
			}
			else

        // ...if shrinking, update offsets after rowlengths
			{
				int stop = 0;
				if(vOldNextRow < RowCount())
					MoveRows((TRowIndex) vOldNextRow, result);
				for(stop = fLineCount - 1, cLine = aIndex; cLine <= stop; cLine++)
				{
					(*fLineOffsets)[cLine] += result;
				}
			}
		}
		Move(&(*vTempRowLengths)[0], &(*fRowLengths)[vStartRow], vLineRowCount * sizeof(TRowLength));
	}
	__finally
	{
		FreeMemory(vTempRowLengths);
	}
	return result;
}

void __fastcall TSynWordWrapPlugin::WrapLines()
{
	int cRow = 0;
	int cLine = 0;
	String vLine;
	int vMaxNewRows = 0;
	PWideChar vRowBegin = nullptr;
	PWideChar vLineEnd = nullptr;
	PWideChar vRowEnd = nullptr;
	PWideChar vRunner = nullptr;
	PWideChar vRowMinEnd = nullptr;
	PWideChar vLastVisibleChar = nullptr;
	int stop = 0;
	if((Editor->Lines->Count == 0) || (fMaxRowLength <= 0))
		return;
	GrowLines(Editor->Lines->Count);
	GrowRows(Editor->Lines->Count);
	cRow = 0;
	for(stop = Editor->Lines->Count - 1, cLine = 0; cLine <= stop; cLine++)
	{
		vLine = ((TSynEditStringList*) Editor->Lines)->ExpandedStrings[cLine];
		vLine = Editor->ExpandAtWideGlyphs(vLine);
		vMaxNewRows = ((int)((vLine.Length() - 1) / /*div*/ fMinRowLength)) + 1;
		GrowRows(cRow + vMaxNewRows);
		vRowBegin = ustr2pwchar(vLine);
		vRowEnd = vRowBegin + fMaxRowLength;
		vLineEnd = vRowBegin + vLine.Length();
		while(vRowEnd < vLineEnd)
		{
			vRowMinEnd = vRowBegin + fMinRowLength;
			vRunner = vRowEnd - 1;
			while(vRunner > vRowMinEnd)
			{
				if(Editor->IsWordBreakChar((*vRunner)))
				{
					vRowEnd = vRunner + 1;
					break;
				}
				--vRunner;
			}
      // do not cut wide glyphs in half
			if(vRowEnd > vRowBegin)
			{
				vLastVisibleChar = vRowEnd - 1;
				while(((*vLastVisibleChar) == FillerChar) && (vLastVisibleChar > vRowBegin))
					--vLastVisibleChar;
				vRowEnd = vLastVisibleChar + 1;
			}
			(*fRowLengths)[cRow] = (TRowLength) (vRowEnd - vRowBegin);
			++cRow;
			vRowBegin = vRowEnd;
			vRowEnd += fMaxRowLength;
		}
		if((vLineEnd > vRowBegin) || (vLine.Length() == 0))
		{
			(*fRowLengths)[cRow] = (TRowLength) (vLineEnd - vRowBegin);
			++cRow;
		}
		(*fLineOffsets)[cLine] = (TRowIndex) cRow;
	}
}

int __fastcall TSynWordWrapPlugin::RowCount()
{
	int result = 0;
	if(fLineCount > 0)
		result = (*fLineOffsets)[fLineCount - 1];
	else
		result = 0;
	return result;
}

void __fastcall TSynWordWrapPlugin::SetEmpty()
{
	fLineCount = 0;
  // free unsused memory
	TrimArrays();
}

void __fastcall TSynWordWrapPlugin::TrimArrays()
{
	fLineOffsets = (PRowIndexArray) ReallocMemory(fLineOffsets, fLineCount * sizeof(TRowIndex));
	fLineCapacity = fLineCount;
	fRowLengths = (PRowLengthArray) ReallocMemory(fRowLengths, RowCount() * sizeof(TRowLength));
	fRowCapacity = RowCount();
}


}  // namespace SynEditWordWrap

