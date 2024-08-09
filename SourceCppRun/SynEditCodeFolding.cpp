#include <vcl.h>
#pragma hdrstop

#include "SynEditCodeFolding.h"
#include <Winapi.Windows.hpp>
#include <System.Math.hpp>
#include "SynEditTextBuffer.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Synedittextbuffer;
using namespace System;
using namespace System::Classes;
using namespace System::Math;
using namespace System::Sysutils;
using namespace Vcl::Graphics;

namespace Syneditcodefolding
{

__fastcall TSynCodeFoldingException::TSynCodeFoldingException(const String Msg) : inherited(Msg) {}
__fastcall TSynCodeFoldingException::TSynCodeFoldingException(const String Msg, const TVarRec* Args, int Args_maxidx) : inherited(Msg, Args, Args_maxidx) {}
__fastcall TSynCodeFoldingException::TSynCodeFoldingException(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Msg, Args, Args_maxidx, AHelpContext) {}
__fastcall TSynCodeFoldingException::TSynCodeFoldingException(const String Msg, int AHelpContext) : inherited(Msg, AHelpContext) {}
__fastcall TSynCodeFoldingException::TSynCodeFoldingException(System::NativeUInt Ident) : inherited(Ident) {}
__fastcall TSynCodeFoldingException::TSynCodeFoldingException(System::PResStringRec ResStringRec) : inherited(ResStringRec) {}
__fastcall TSynCodeFoldingException::TSynCodeFoldingException(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx) : inherited(Ident, Args, Args_maxidx) {}
__fastcall TSynCodeFoldingException::TSynCodeFoldingException(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx) : inherited(ResStringRec, Args, Args_maxidx) {}
__fastcall TSynCodeFoldingException::TSynCodeFoldingException(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(ResStringRec, Args, Args_maxidx, AHelpContext) {}
__fastcall TSynCodeFoldingException::TSynCodeFoldingException(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Ident, Args, Args_maxidx, AHelpContext) {}
__fastcall TSynCodeFoldingException::TSynCodeFoldingException(System::NativeUInt Ident, int AHelpContext) : inherited(Ident, AHelpContext) {}
__fastcall TSynCodeFoldingException::TSynCodeFoldingException(System::PResStringRec ResStringRec, int AHelpContext) : inherited(ResStringRec, AHelpContext) {}
__fastcall TSynCustomCodeFoldingHighlighter::TSynCustomCodeFoldingHighlighter(TComponent* AOwner) : inherited(AOwner) {}



/* TSynEditFoldRanges */

bool __fastcall TSynFoldRanges::CollapsedFoldAroundLine(int Line)
{
	bool result = false;
	int Index = 0;
	result = CollapsedFoldAroundLine(Line, Index);
	return result;
}

bool __fastcall TSynFoldRanges::CollapsedFoldAroundLine(int Line, int& Index)
{
	Index = 0; //# clear out parameter
	bool result = false;
	result = FoldAroundLineEx(Line, true, false, false, Index);
	return result;
}

bool __fastcall TSynFoldRanges::CollapsedFoldStartAtLine(int Line)
{
	bool result = false;
	int Index = 0;
	result = CollapsedFoldStartAtLine(Line, Index);
	return result;
}

bool __fastcall TSynFoldRanges::CollapsedFoldStartAtLine(int Line, int& Index)
{
	Index = 0; //# clear out parameter
	bool result = false;
	TSynFoldRange range;
	range.FromLine = Line;
	result = BinarySearchInFoldRangeList(fRanges, range,Index);
	if(result)
		result = result && fRanges->Items[Index].Collapsed;
	return result;
}

__fastcall TSynFoldRanges::TSynFoldRanges()
 : fCodeFoldingMode(cfmStandard),
			fRangesNeedFixing(false),
			fRanges(nullptr),
			fCollapsedState(nullptr),
			fFoldInfoList(nullptr)
{
	// inherited;

/*
//class TSynFoldRangesCmp : public TComparer__1<TSynFoldRange>
class TSynFoldRangesCmp : public System::DelphiInterface<System::Generics::Defaults::IComparer__1<TSynFoldRange> >
{
	int __fastcall Compare(const TSynFoldRange l, const TSynFoldRange R)
	{
		return l.FromLine - R.FromLine;
	}
};


	TSynFoldRangesCmp* pcmp = new TSynFoldRangesCmp(); // todo memory leak
	fRanges = new TList__1<TSynFoldRange>(*pcmp);

	fCollapsedState = new TList__1<int>();

class TSynInfoListCmp : public System::DelphiInterface<System::Generics::Defaults::IComparer__1<TLineFoldInfo> >
{
	int __fastcall Compare(const TLineFoldInfo l, const TLineFoldInfo R)
	{
		return l.Line - R.Line;
	}
};

	TSynInfoListCmp* pcmp2 = new TSynInfoListCmp(); // todo memory leak
	fFoldInfoList = new TList__1<TLineFoldInfo>(*pcmp2);

*/

	fRanges = CreateFoldRangeList();
	fCollapsedState = new TList__1<int>();
	fFoldInfoList = CreateFoldInfoList();
}

__fastcall TSynFoldRanges::~TSynFoldRanges()
{
	delete fRanges;
	delete fCollapsedState;
	delete fFoldInfoList;
	// inherited;
}

bool __fastcall TSynFoldRanges::FoldAroundLine(int Line)
{
	bool result = false;
	int Index = 0;
	result = FoldAroundLine(Line, Index);
	return result;
}

bool __fastcall TSynFoldRanges::FoldAroundLine(int Line, int& Index)
{
	Index = 0; //# clear out parameter
	bool result = false;
	result = FoldAroundLineEx(Line, false, false, false, Index);
	return result;
}

bool __fastcall TSynFoldRanges::FoldAroundLineEx(int Line, bool WantCollapsed, bool AcceptFromLine, bool AcceptToLine, int& Index)
{
	Index = 0; //# clear out parameter
	bool result = false;
	int i = 0;
	int stop = 0;
	result = false;
	for(stop = fRanges->Count - 1, i = 0; i <= stop; i++)
	{
		/*# with fRanges.List[i] do */
		{
			
			if(((fRanges->List[i].FromLine < Line) || ((fRanges->List[i].FromLine <= Line) && AcceptFromLine)) && ((fRanges->List[i].ToLine > Line) || ((fRanges->List[i].ToLine >= Line) && AcceptToLine)) && (fRanges->List[i].Collapsed == WantCollapsed))
			{
				Index = i;
				result = true;
			}
			if(fRanges->List[i].FromLine > Line)
				return result;
		}
	}
	return result;
}

bool __fastcall TSynFoldRanges::FoldEndAtLine(int Line, int& Index)
{
	Index = 0; //# clear out parameter
	bool result = false;
	int i = 0;
	int stop = 0;
	result = false;
	for(stop = fRanges->Count - 1, i = 0; i <= stop; i++)
	{
		/*# with fRanges.List[i] do */
		{
			
			if(fRanges->List[i].ToLine == Line)
			{
				Index = i;
				result = true;
				break;
			}
			else
			{
				if(fRanges->List[i].FromLine > Line)
					break;
			}
		}
	} // sorted by line. don't bother scanning further
	return result;
}

bool __fastcall TSynFoldRanges::FoldEndAtLine(int Line)
{
	bool result = false;
	int Index = 0;
	result = FoldEndAtLine(Line, Index);
	return result;
}

bool __fastcall TSynFoldRanges::FoldHidesLine(int Line)
{
	bool result = false;
	int Index = 0;
	result = FoldHidesLine(Line, Index);
	return result;
}

bool __fastcall TSynFoldRanges::FoldHidesLine(int Line, int& Index)
{
	Index = 0; //# clear out parameter
	bool result = false;
	result = FoldAroundLineEx(Line, true, false, true, Index);
	return result;
}

int __fastcall TSynFoldRanges::FoldLineToRow(int Line)
{
	int result = 0;
	int i = 0;
	int CollapsedTo = 0;
	int stop = 0;
	result = Line;
	CollapsedTo = 0;
	for(stop = fRanges->Count - 1, i = 0; i <= stop; i++)
	{
		/*# with fRanges.List[i] do */
		{
			
      // fold after line
			if(fRanges->List[i].FromLine >= Line)
				break;
			if(fRanges->List[i].Collapsed)
        // Line is found after fold
			{
				if(fRanges->List[i].ToLine < Line)
				{
					result -= Max(fRanges->List[i].ToLine - Max(fRanges->List[i].FromLine, CollapsedTo), 0);
					CollapsedTo = Max(CollapsedTo, fRanges->List[i].ToLine);
          // Inside fold
				}
				else
				{
					result -= Line - Max(fRanges->List[i].FromLine, CollapsedTo);
					break;
				}
			}
		}
	}
	return result;
}

int __fastcall TSynFoldRanges::FoldRowToLine(int Row)
{
	int result = 0;
	int i = 0;
	int CollapsedTo = 0;
	int stop = 0;
	result = Row;
	CollapsedTo = 0;
	for(stop = fRanges->Count - 1, i = 0; i <= stop; i++)
	{
		/*# with fRanges.List[i] do */
		{
			
			if(fRanges->List[i].FromLine >= result)
				break;
			if(fRanges->List[i].Collapsed)
			{
				result += Max(fRanges->List[i].ToLine - Max(fRanges->List[i].FromLine, CollapsedTo), 0);
				CollapsedTo = Max(CollapsedTo, fRanges->List[i].ToLine);
			}
		}
	}
	return result;
}
/*
   Returns an array of indices of folds with level = Level
   ignoring fold ranges of type FoldRegionType
*/

System::TArray<int> __fastcall TSynFoldRanges::FoldsAtLevel(int Level)
{
	System::TArray<int> result;
	int i = 0;
	TList__1<int>* FRStack = nullptr;
	TList__1<int>* ResultList = nullptr;

	auto RemoveClosed = [&](int Line) -> void 
	{
		int j = 0;
		int stop = 0;
		for(stop = 0, j = FRStack->Count - 1; j >= stop; j--)
		{
			if(fRanges->List[FRStack->Items[j]].ToLine <= Line)
				FRStack->Delete(j);
		}
	};
	FRStack = new TList__1<int>();
	ResultList = new TList__1<int>();
	try
	{
		int stop = 0;
		for(stop = fRanges->Count - 1, i = 0; i <= stop; i++)
		{
			if(fRanges->List[i].FoldType == FoldRegionType)
				continue;
			RemoveClosed(fRanges->List[i].FromLine);
			FRStack->Add(i);
			if(FRStack->Count == Level)
				ResultList->Add(i);
		}
		result = ResultList->ToArray();
	}
	__finally
	{
		delete FRStack;
		delete ResultList;
	}
	return result;
}
/*
   Returns an array of indices of folds with FoldType = aType
*/

System::TArray<int> __fastcall TSynFoldRanges::FoldsOfType(int AType)
{
	System::TArray<int> result;
	int i = 0;
	TList__1<int>* ResultList = nullptr;
	ResultList = new TList__1<int>();
	try
	{
		int stop = 0;
		for(stop = fRanges->Count - 1, i = 0; i <= stop; i++)
		{
			if(fRanges->List[i].FoldType == AType)
				ResultList->Add(i);
		}
		result = ResultList->ToArray();
	}
	__finally
	{
		delete ResultList;
	}
	return result;
}

bool __fastcall TSynFoldRanges::FoldStartAtLine(int Line)
{
	bool result = false;
	int Index = 0;
	result = FoldStartAtLine(Line, Index);
	return result;
}
/*
  If Result is False it Returns the First Index with Line greater than Line
*/

bool __fastcall TSynFoldRanges::FoldStartAtLine(int Line, int& Index)
{
	Index = 0; //# clear out parameter
	bool result = false;
	TSynFoldRange range;
	range.FromLine = Line;
	result = BinarySearchInFoldRangeList(fRanges, range,Index);
	return result;
}

void __fastcall TSynFoldRanges::AddByParts(int AFoldType, int AFromLine, int AToLine/*# = -1*/)
{
	int Index = 0;
	TSynFoldRange FR = {};
	// Insert keeping the list sorted
	TSynFoldRange range;
	range.FromLine = AFromLine;
	range.ToLine = AToLine;
	range.FoldType = AFoldType;
	FR = TSynFoldRange(range);
	if(FoldStartAtLine(AFromLine, Index))
		fRanges->List[Index] = FR;
	else
		fRanges->Insert(Index, FR);
}

void __fastcall TSynFoldRanges::AddFoldRange(const TSynFoldRange& cFoldRange)
{
	TSynFoldRange FoldRange = cFoldRange;
	fRanges->Add(FoldRange);
}

void __fastcall TSynFoldRanges::AddLineInfo(int ALine, int AFoldType, TFoldOpenClose AFoldOpenClose, int AIndent)
{
	TLineFoldInfo LineFoldInfo = {};
	int Index = 0;
	//LineFoldInfo = TLineFoldInfo(ALine, AFoldOpenClose, AFoldType, AIndent);
	LineFoldInfo.Line = ALine;
	LineFoldInfo.FoldOpenClose = AFoldOpenClose;
	LineFoldInfo.FoldType = AFoldType;
	LineFoldInfo.Indent = AIndent;

  // Insert keeping the list sorted
	//if(fFoldInfoList->BinarySearch(LineFoldInfo, Index))
	if(BinarySearchInLineFoldList(fFoldInfoList, LineFoldInfo, Index))
	{
		if((fFoldInfoList->List[Index].FoldOpenClose != AFoldOpenClose) || (fFoldInfoList->List[Index].FoldType != AFoldType) || (fFoldInfoList->List[Index].Indent != AIndent))
		{
			fFoldInfoList->List[Index].FoldOpenClose = AFoldOpenClose;
			fFoldInfoList->List[Index].FoldType = AFoldType;
			fFoldInfoList->List[Index].Indent = AIndent;
			fRangesNeedFixing = true;
		}
	}
	else
	{
		//fFoldInfoList->Insert(Index, LineFoldInfo);
		InsertIntoLineFoldList(fFoldInfoList, Index, LineFoldInfo);
		fRangesNeedFixing = true;
	}
}

TSynFoldRange __fastcall TSynFoldRanges::Get(int Index)
{
	TSynFoldRange result = {};
	result = fRanges->Items[Index];
	return result;
}

int __fastcall TSynFoldRanges::GetCount()
{
	int result = 0;
	result = fRanges->Count;
	return result;
}

int __fastcall TSynFoldRanges::GetIndentLevel(int Line)
{
	int result = 0;
	int Index = 0;
	int i = 0;
	int stop = 0;
	result = -1;
	TLineFoldInfo LineFoldInfo;
	LineFoldInfo.Line = Line;
	BinarySearchInLineFoldList(fFoldInfoList, LineFoldInfo, Index);
	// Search above Line
	for(stop = 0, i = Index - 1; i >= stop; i--)
	{
		if(fFoldInfoList->List[i].Indent >= 0)
		{
			result = fFoldInfoList->List[i].Indent;
			break;
		}
	}
	return result;
}
/*
  Adjust fFoldInfoList and fRanges
  aIndex is 0-based fFoldInfoList and fRanges are 1-based
  If needed recreate fRanges
*/

int __fastcall TSynFoldRanges::LinesDeleted(int AIndex, int ACount)
{
	int result = 0;
	int i = 0;
	int stop = 0;
	fRangesNeedFixing = false;
	result = ACount;
  // Adjust fFoldInfoList
  // aIndex is 0-based fFoldInfoList is 1-based
	for(stop = 0, i = fFoldInfoList->Count - 1; i >= stop; i--)
	{
		/*# with fFoldInfoList.List[i] do */
		{
			
			if(fFoldInfoList->List[i].Line > AIndex + ACount)
				fFoldInfoList->List[i].Line -= ACount;
			else
			{
				if(fFoldInfoList->List[i].Line > AIndex)
				{
					fRangesNeedFixing = true;
					fFoldInfoList->Delete(i);
				}
				else
				break;
			}
		}
	}
	for(stop = 0, i = fRanges->Count - 1; i >= stop; i--)
	{
		/*# with fRanges.List[i] do */
		{
			
			if(fRanges->List[i].FromLine > AIndex + ACount)
        // Move after affected area
				Ranges->List[i].Move(-ACount);
			else
			{
				if(fRanges->List[i].FromLine > AIndex)
				{
					fRangesNeedFixing = true;
					fRanges->Delete(i);
				}
				else
				{
					if(fRanges->List[i].ToLine > AIndex + ACount)
						fRanges->List[i].ToLine -= ACount;
					else
					{
						if(fRanges->List[i].ToLine > AIndex)
							fRanges->List[i].ToLine -= fRanges->List[i].ToLine - AIndex;
					}
				}
			}
		}
	}
	return result;
}
/*
  Adjust fFoldInfoList and fRanges
  aIndex is 0-based fFoldInfoList and fRanges are 1-based
*/

int __fastcall TSynFoldRanges::LinesInserted(int AIndex, int ACount)
{
	int result = 0;
	int i = 0;
	int stop = 0;
	result = ACount;
	for(stop = 0, i = fFoldInfoList->Count - 1; i >= stop; i--)
	{
		/*# with fFoldInfoList.List[i] do */
		{
			
			if(fFoldInfoList->List[i].Line > AIndex)
				fFoldInfoList->List[i].Line += ACount;
			else
				break;
		}
	}
	for(stop = 0, i = fRanges->Count - 1; i >= stop; i--)
	{
		/*# with fRanges.List[i] do */
		{
			
			if(fRanges->List[i].FromLine > AIndex) // insertion of count lines above FromLine
				fRanges->List[i].Move(ACount);
			else
			{
				if(fRanges->List[i].ToLine > AIndex)
					fRanges->List[i].ToLine += ACount;
			}
		}
	}
	return result;
}

int __fastcall TSynFoldRanges::LinePut(int AIndex, const String OldLine)
{
	int result = 0;
	result = 1;
	return result;
}

void __fastcall TSynFoldRanges::NoFoldInfo(int ALine)
{
	int Index = 0;
	TLineFoldInfo LineFoldInfo;
	LineFoldInfo.Line = ALine;
	if(BinarySearchInLineFoldList(fFoldInfoList, LineFoldInfo, Index))
		// we have deleted an existing fold open or close mark
	{
		fRangesNeedFixing = true;
		fFoldInfoList->Delete(Index);
	}
}

void __fastcall TSynFoldRanges::RecreateFoldRanges(TStrings* Lines)
{
	TList__1<int>* OpenFoldStack = nullptr;
	TLineFoldInfo LFI = {};
	PSynFoldRange PFoldRange = nullptr;
	int i = 0;
	int Line = 0;
   /* TODO : Account for type */
	fRanges->Clear();
	OpenFoldStack = new TList__1<int>();
	try
	{
		for(int iFor0 = 0; iFor0 < fFoldInfoList->Count; iFor0++)
		{
			TLineFoldInfo LFI = fFoldInfoList->Items[iFor0];
			if(LFI.FoldOpenClose == focOpen)
			{
				if(LFI.Indent >= 0)
				{
					int stop1 = 0;
					for(stop1 = 0, i = OpenFoldStack->Count - 1; i >= stop1; i--)
					{
			// Close all Fold Ranges with less Indent
						PFoldRange = &fRanges->List[OpenFoldStack->List[i]];
						if((*PFoldRange).Indent >= LFI.Indent)
						{
							(*PFoldRange).ToLine = LFI.Line - 1; // Do not include Line
							OpenFoldStack->Delete(i);
						}
					}
				}
				//fRanges->Add(TSynFoldRange(LFI.Line, LFI.Line, LFI.FoldType, LFI.Indent));
				TSynFoldRange range;
				range.FromLine = LFI.Line;
				range.ToLine = LFI.Line;
				range.FoldType = LFI.FoldType;
				range.Indent = LFI.Indent;
 //	linker error			fRanges->Add(range);
				AddToFoldRangeList(fRanges, range);
				OpenFoldStack->Add(fRanges->Count - 1);
			}
			else

      // foClose
			{
				if(LFI.Indent >= 0)
				{
					int stop1 = 0;
					for(stop1 = 0, i = OpenFoldStack->Count - 1; i >= stop1; i--)
					{
            // Close all Fold Ranges with less Indent
						PFoldRange = &fRanges->List[OpenFoldStack->List[i]];
						if((*PFoldRange).Indent >= LFI.Indent)
						{
							(*PFoldRange).ToLine = LFI.Line - 1; // Do not include Line
							OpenFoldStack->Delete(i);
						}
					}
				}
				else
				{
					int stop1 = 0;
					for(stop1 = 0, i = OpenFoldStack->Count - 1; i >= stop1; i--)
					{
						PFoldRange = &fRanges->List[OpenFoldStack->List[i]];
						if((*PFoldRange).FoldType == LFI.FoldType)
						{
							(*PFoldRange).ToLine = LFI.Line;
							OpenFoldStack->Delete(i);
							break;
						}
					}
				}
			}
		}
		if(CodeFoldingMode == cfmIndentation)
      // close all open indent based folds
		{
			int stop = 0;
			for(stop = 0, i = OpenFoldStack->Count - 1; i >= stop; i--)
			{
        // Close all Fold Ranges with less Indent
				PFoldRange = &fRanges->List[OpenFoldStack->List[i]];
				if((*PFoldRange).Indent >= 0)
				{
					(*PFoldRange).ToLine = Lines->Count; //
					OpenFoldStack->Delete(i);
				}
			}
      // Adjust LineTo for Indent based folds with empty lines in the end
			for(stop = fRanges->Count - 1, i = 0; i <= stop; i++)
			{
				PFoldRange = &fRanges->List[i];
				if((*PFoldRange).Indent >= 0)
				{
					Line = (*PFoldRange).ToLine;
					while((Line > (*PFoldRange).FromLine) && (TrimLeft(Lines->Strings[Line - 1]) == L""))
					{
						--(*PFoldRange).ToLine;
						--Line;
					}
				}
			}
		}
	}
	__finally
	{
		delete OpenFoldStack;
	}
}

void __fastcall TSynFoldRanges::Reset()
{
	fRanges->Clear();
	fCollapsedState->Clear();
	fFoldInfoList->Clear();
	fRangesNeedFixing = false;
}

void __fastcall TSynFoldRanges::RestoreCollapsedState(TStream* Stream)
{
	int Size = 0;
	int Line = 0;
	int Index = 0;
	Size = (int) Stream->Size;
	while(Stream->Position < Size)
	{
		Stream->ReadData(Line);
		if(FoldStartAtLine(Line, Index))
			fRanges->List[Index].Collapsed = true;
	}
}

void __fastcall TSynFoldRanges::RestoreCollapsedState()
{
	int i = 0;
	int Index = 0;
	for(int iFor0 = 0; iFor0 < fCollapsedState->Count; iFor0++)
	{
		int i = fCollapsedState->Items[iFor0];
		if(FoldStartAtLine(i, Index))
			fRanges->List[Index].Collapsed = true;
	}
	fCollapsedState->Clear();
}

void __fastcall TSynFoldRanges::StartFoldRange(int ALine, int AFoldType, int AIndent/*# = -1*/)
{
	AddLineInfo(ALine, AFoldType, focOpen, AIndent);
}

void __fastcall TSynFoldRanges::StartScanning()
{
}

void __fastcall TSynFoldRanges::StopFoldRange(int ALine, int AFoldType, int AIndent/*# = -1*/)
{
	AddLineInfo(ALine, AFoldType, focClose, AIndent);
}
/*
  Returns true if fold ranges changed
  Recreates FoldRanges if the Synedit lines are not updating
*/

bool __fastcall TSynFoldRanges::StopScanning(TStrings* Lines)
{
	bool result = false;
	result = fRangesNeedFixing;
	if(result)
	{
		StoreCollapsedState();
		RecreateFoldRanges(Lines);
		RestoreCollapsedState();
		fRangesNeedFixing = false;
	}
	return result;
}

void __fastcall TSynFoldRanges::StoreCollapsedState(TStream* Stream)
{
	TSynFoldRange FoldRange = {};
	for(int iFor0 = 0; iFor0 < fRanges->Count; iFor0++)
	{
		TSynFoldRange FoldRange = fRanges->Items[iFor0];
		if(FoldRange.Collapsed)
			Stream->WriteData(FoldRange.FromLine);
	}
}

void __fastcall TSynFoldRanges::StoreCollapsedState()
{
	TSynFoldRange FoldRange = {};
	fCollapsedState->Clear();
	for(int iFor0 = 0; iFor0 < fRanges->Count; iFor0++)
	{
		TSynFoldRange FoldRange = fRanges->Items[iFor0];
		if(FoldRange.Collapsed)
			fCollapsedState->Add(FoldRange.FromLine);
	}
}

/* TSynEditFoldRange */




void __fastcall TSynCodeFolding::Assign(TPersistent* Source)
{
	if(ObjectIs(Source, TSynCodeFolding*))
	{
		fIndentGuides = ((TSynCodeFolding*) Source)->fIndentGuides;
		fCollapsedLineColor = ((TSynCodeFolding*) Source)->fCollapsedLineColor;
		fFolderBarLinesColor = ((TSynCodeFolding*) Source)->fFolderBarLinesColor;
		fIndentGuidesColor = ((TSynCodeFolding*) Source)->fIndentGuidesColor;
		fShowCollapsedLine = ((TSynCodeFolding*) Source)->fShowCollapsedLine;
		fShowHintMark = ((TSynCodeFolding*) Source)->fShowHintMark;
		fGutterShapeSize = ((TSynCodeFolding*) Source)->fGutterShapeSize;
	}
	else
	inherited::Assign(Source);
}

__fastcall TSynCodeFolding::TSynCodeFolding()
 : fIndentGuides(true),
			fCollapsedLineColor((TColor) clGrayText),
			fFolderBarLinesColor((TColor) clGrayText),
			fIndentGuidesColor((TColor) clGray),
			fShowCollapsedLine(false),
			fShowHintMark(true),
			fGutterShapeSize(11)
{
}
/* Always returns an odd number */

int __fastcall TSynCodeFolding::ScaledGutterShapeSize(int PPI)
{
	int result = 0;
	result = MulDiv(fGutterShapeSize, PPI, 96);
	if(!Odd(result))
		--result;
	return result;
}

/* TSynFoldRanges.TLineFoldInfo */



/* TSynCustomCodeFoldingHighlighter */

void __fastcall TSynCustomCodeFoldingHighlighter::AdjustFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan)
{

  // Do nothing
}

TSynHighlighterAttributes* __fastcall TSynCustomCodeFoldingHighlighter::GetHighlighterAttriAtRowCol(TStrings* const Lines, int Line, int Char)
{
	TSynHighlighterAttributes* result = nullptr;
	String Token;
	int TokenType = 0;
	int Start = 0;
	GetHighlighterAttriAtRowColEx(Lines, Line, Char, Token, TokenType, Start, result);
	return result;
}

bool __fastcall TSynCustomCodeFoldingHighlighter::GetHighlighterAttriAtRowColEx(TStrings* const Lines, int Line, int Char, String& Token, int& TokenType, int& Start, TSynHighlighterAttributes*& Attri)
{
	bool result = false;
	String LineText;
	if((Line >= 0) && (Line < Lines->Count))
	{
		LineText = Lines->Strings[Line];
		if(Line == 0)
			ResetRange();
		else
			SetRange(((TSynEditStringList*) Lines)->Ranges[Line - 1]);
		SetLine(LineText, Line);
		if((Char > 0) && (Char <= LineText.Length()))
		{
			while(!GetEol())
			{
				Start = GetTokenPos() + 1;
				Token = GetToken();
				if((Char >= Start) && (Char < Start + Token.Length()))
				{
					Attri = GetTokenAttribute();
					TokenType = GetTokenKind();
					result = true;
					return result;
				}
				Next();
			}
		}
	}
	Token = L"";
	Attri = nullptr;
	result = false;
	return result;
}

void* __fastcall TSynCustomCodeFoldingHighlighter::GetLineRange(TStrings* Lines, int Line)
{
	void* result = nullptr;
	if((Line >= 0) && (Line < Lines->Count))
		result = ((TSynEditStringList*) Lines)->Ranges[Line];
	else
		result = nullptr;
	return result;
}

void __fastcall TSynCustomCodeFoldingHighlighter::InitFoldRanges(TSynFoldRanges* FoldRanges)
{
	FoldRanges->CodeFoldingMode = cfmStandard;
}

int __fastcall TSynCustomCodeFoldingHighlighter::TabWidth(TStrings* LinesToScan)
{
	int result = 0;
	result = ((TSynEditStringList*) LinesToScan)->TabWidth;
	return result;
}

/* TSynCodeFolding */

void __fastcall TSynCodeFolding::SetCollapsedLineColor(const TColor Value)
{
	if(fCollapsedLineColor != Value)
	{
		fCollapsedLineColor = Value;
		if(ASSIGNED(FOnChange))
			FOnChange(this);
	}
}

void __fastcall TSynCodeFolding::SetFolderBarLinesColor(const TColor Value)
{
	if(fFolderBarLinesColor != Value)
	{
		fFolderBarLinesColor = Value;
		if(ASSIGNED(FOnChange))
			FOnChange(this);
	}
}

void __fastcall TSynCodeFolding::SetGutterShapeSize(int Value)
{
	int NewValue = 0;
	NewValue = Value;
	if(fGutterShapeSize != NewValue)
	{
		fGutterShapeSize = NewValue;
		if(ASSIGNED(FOnChange))
			FOnChange(this);
	}
}

void __fastcall TSynCodeFolding::SetIndentGuides(bool Value)
{
	if(fIndentGuides != Value)
	{
		fIndentGuides = Value;
		if(ASSIGNED(FOnChange))
			FOnChange(this);
	}
}

void __fastcall TSynCodeFolding::SetIndentGuidesColor(const TColor Value)
{
	if(fIndentGuidesColor != Value)
	{
		fIndentGuidesColor = Value;
		if(ASSIGNED(FOnChange))
			FOnChange(this);
	}
}

void __fastcall TSynCodeFolding::SetShowHintMark(bool Value)
{
	if(fShowHintMark != Value)
	{
		fShowHintMark = Value;
		if(ASSIGNED(FOnChange))
			FOnChange(this);
	}
}

void __fastcall TSynCodeFolding::SetShowCollapsedLine(bool Value)
{
	if(fShowCollapsedLine != Value)
	{
		fShowCollapsedLine = Value;
		if(ASSIGNED(FOnChange))
			FOnChange(this);
	}
}


}  // namespace SynEditCodeFolding

