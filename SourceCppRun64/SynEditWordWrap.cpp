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

TDisplayCoord __fastcall TSynWordWrapPlugin::BufferToDisplayPos(const TBufferCoord& APos)
{
	TDisplayCoord result = {};
	int vStartRow = 0; // first row of the line
	int cRow = 0;
	int vRowLen = 0;
	int stop = 0;
	Assert(APos.Char > 0);
	Assert(APos.Line > 0);
	if(fLineCount < APos.Line)
    // beyond EOF
	{
		result.Column = APos.Char;
		result.Row = RowCount() + (APos.Line - fLineCount);
		return result;
	}
	if(APos.Line == 1)
		vStartRow = 0;
	else
		vStartRow = (*fLineOffsets)[APos.Line - 2];
	vRowLen = 0;
	for(stop = (*fLineOffsets)[APos.Line - 1] - 1, cRow = vStartRow; cRow <= stop; cRow++)
	{
		vRowLen += (*fRowLengths)[cRow];
		if(APos.Char <= vRowLen)
		{
			result.Column = APos.Char - vRowLen + (*fRowLengths)[cRow];
			result.Row = cRow + 1;
			return result;
		}
	}
  // beyond EOL
	result.Column = APos.Char - vRowLen + (*fRowLengths)[(*fLineOffsets)[APos.Line - 1] - 1];
	result.Row = (*fLineOffsets)[APos.Line - 1];
	return result;
}

__fastcall TSynWordWrapPlugin::TSynWordWrapPlugin(TCustomSynEdit* AOwner)
 : fLineOffsets(nullptr),
			fRowLengths(nullptr),
			fLineCapacity(0),
			fRowCapacity(0),
			fLineCount(0),
			FEditor(nullptr),
			fMinRowLength(0),
			fMaxRowLength(0)
{
	//# inherited::Create(); // just to work as reminder in case I revert it to a TComponent...
	if(AOwner == nullptr)
		throw new Exception(L"Owner of TSynWordWrapPlugin must be a TCustomSynEdit");
	FEditor = AOwner;
	fLineCount = FEditor->Lines->Count;
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

TBufferCoord __fastcall TSynWordWrapPlugin::DisplayToBufferPos(const TDisplayCoord& APos)
{
	TBufferCoord result = {};
	int cLine = 0;
	int cRow = 0;
	int stop = 0;
	Assert(APos.Column > 0);
	Assert(APos.Row > 0);
	if(APos.Row > RowCount())
    // beyond EOF
	{
		result.Char = APos.Column;
		result.Line = APos.Row - RowCount() + fLineCount;
		return result;
	}
  //todo: use a binary search or something smarter
	for(stop = 0, cLine = fLineCount - 2; cLine >= stop; cLine--)
	{
		if(APos.Row > (*fLineOffsets)[cLine])
		{
			int stop1 = 0;
			result.Line = cLine + 2;
			if(APos.Row == (*fLineOffsets)[cLine + 1]) //last row of line
				result.Char = Min(APos.Column, fMaxRowLength + 1);
			else
				result.Char = Min(APos.Column, (*fRowLengths)[APos.Row - 1] + 1);
			for(stop1 = APos.Row - 2, cRow = (*fLineOffsets)[cLine]; cRow <= stop1; cRow++)
			{
				result.Char += (*fRowLengths)[cRow];
			}
			return result;
		}
	}
  // first line
	result.Line = 1;
	if(APos.Row == (*fLineOffsets)[0]) //last row of line
		result.Char = Min(APos.Column, fMaxRowLength + 1);
	else
		result.Char = Min(APos.Column, (*fRowLengths)[APos.Row - 1] + 1);
	for(stop = APos.Row - 2, cRow = 0; cRow <= stop; cRow++)
	{
		result.Char += (*fRowLengths)[cRow];
	}
	return result;
}
// aRow is 1-based...

int __fastcall TSynWordWrapPlugin::GetRowLength(int ARow)
{
	int result = 0;
	if((ARow <= 0) || (ARow > RowCount()))
		TList::Error(System_Rtlconsts_SListIndexError, ARow);
	result = (int) (*fRowLengths)[ARow - 1];
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

int __fastcall TSynWordWrapPlugin::LinesDeleted(int AIndex, int ACount)
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
	Assert(AIndex >= 0);
	Assert(ACount >= 1);
	Assert(AIndex + ACount <= fLineCount);
	if(AIndex == 0)
		vStartRow = 0;
	else
		vStartRow = (*fLineOffsets)[AIndex - 1];
	vEndRow = (*fLineOffsets)[AIndex + ACount - 1];
	result = vEndRow - vStartRow;
  // resize fRowLengths
	if(vEndRow < RowCount())
		MoveRows((TRowIndex) vEndRow, -result);
  // resize fLineOffsets
	MoveLines((TLineIndex) (AIndex + ACount), -ACount);
	fLineCount -= ACount;
  // update offsets
	for(stop = fLineCount - 1, cLine = AIndex; cLine <= stop; cLine++)
	{
		(*fLineOffsets)[cLine] -= result;
	}
	if(fLineCount == 0)
		SetEmpty();
	return result;
}

int __fastcall TSynWordWrapPlugin::LinesInserted(int AIndex, int ACount)
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
	Assert(AIndex >= 0);
	Assert(ACount >= 1);
	Assert(AIndex <= fLineCount);
  // resize fLineOffsets
	GrowLines(fLineCount + ACount);
	if(AIndex < fLineCount) // no need for MoveLines if inserting at LineCount (TSynEditStringList.Add)
	{
		fLineCount += ACount; // fLineCount must be updated before calling MoveLines()
		MoveLines((TLineIndex) AIndex, ACount);
	}
	else
	fLineCount += ACount; 
  // set offset to same as previous line (i.e. the line has 0 rows)
	if(AIndex == 0)
		vPrevOffset = (TRowIndex) 0;
	else
		vPrevOffset = (*fLineOffsets)[AIndex - 1];
	for(stop = AIndex + ACount - 1, cLine = AIndex; cLine <= stop; cLine++)
	{
		(*fLineOffsets)[cLine] = vPrevOffset;
	}
  // Rewrap
	result = 0;
	for(stop = AIndex + ACount - 1, cLine = AIndex; cLine <= stop; cLine++)
	{
		result += ReWrapLine((TLineIndex) cLine);
	}
	return result;
}

int __fastcall TSynWordWrapPlugin::LinePut(int AIndex, const String OldLine)
{
	int result = 0;
	if(fMaxRowLength == 0)
	{
		result = 0;
		return result;
	}
	Assert(AIndex >= 0);
	Assert(AIndex < fLineCount);
  // Rewrap
	result = 0;
	result += ReWrapLine((TLineIndex) AIndex);
	return result;
}

void __fastcall TSynWordWrapPlugin::MoveLines(TLineIndex AStart, int aMoveBy)
{
	int vMoveCount = 0;
	Assert(aMoveBy != 0);
	Assert(AStart + aMoveBy >= 0);
	Assert(AStart + aMoveBy < fLineCount);
	vMoveCount = fLineCount - AStart;
	if(aMoveBy > 0)
		vMoveCount -= aMoveBy;
	Move(&(*fLineOffsets)[AStart], &(*fLineOffsets)[AStart + aMoveBy], (size_t) (vMoveCount * sizeof(TRowIndex)));
}

void __fastcall TSynWordWrapPlugin::MoveRows(TRowIndex AStart, int aMoveBy)
{
	int vMoveCount = 0;
	Assert(aMoveBy != 0);
	Assert(AStart + aMoveBy >= 0);
	Assert(AStart + aMoveBy < RowCount());
	vMoveCount = RowCount() - AStart;
	if(aMoveBy > 0)
		vMoveCount -= aMoveBy;
	Move(&(*fRowLengths)[AStart], &(*fRowLengths)[AStart + aMoveBy], (size_t) (vMoveCount * sizeof(TRowLength)));
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

int __fastcall TSynWordWrapPlugin::ReWrapLine(TLineIndex AIndex)
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
	PRowIndexArray P = nullptr;
  // ****** First parse the new string using an auxiliar array *****
	vLine = ((TSynEditStringList*) Editor->Lines)->ExpandedStrings[AIndex];
	vLine = Editor->ExpandAtWideGlyphs(vLine);
  // Pre-allocate a buffer for rowlengths - at least one row
	vMaxNewRows = Max(((int)((vLine.Length() - 1) / /*div*/ fMinRowLength)) + 1, 1);
	vTempRowLengths = ((PRowLengthArray) AllocMem((unsigned int) (vMaxNewRows * sizeof(TRowLength))));
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
		if(AIndex == 0)
			vStartRow = 0;
		else
			vStartRow = (*fLineOffsets)[AIndex - 1];
		vOldNextRow = (*fLineOffsets)[AIndex];
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
					P = fLineOffsets;
					for(stop = fLineCount - 1, cLine = AIndex; cLine <= stop; cLine++)
					{
						++(*P)[cLine];
					}
				}
				else
				{
					int stop = 0;
					P = fLineOffsets;
					for(stop = fLineCount - 1, cLine = AIndex; cLine <= stop; cLine++)
					{
						(*P)[cLine] += result;
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
				for(stop = fLineCount - 1, cLine = AIndex; cLine <= stop; cLine++)
				{
					(*fLineOffsets)[cLine] += result;
				}
			}
		}
		Move(&(*vTempRowLengths)[0], &(*fRowLengths)[vStartRow], (size_t) (vLineRowCount * sizeof(TRowLength)));
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

