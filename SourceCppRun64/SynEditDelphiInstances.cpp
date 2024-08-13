
#include <vcl.h>
#pragma hdrstop

#include "SynEditDelphiInstances.h"

using namespace std;
using namespace d2c_system;
using namespace System;
using namespace System::Generics::Defaults;

namespace Syneditdelphiinstances
{

__fastcall TSynUndoItem::TSynUndoItem() {}
__fastcall TSynFoldRangesCmp::TSynFoldRangesCmp() {}
__fastcall TLineFoldInfoCmp::TLineFoldInfoCmp() {}



int __fastcall TSynFoldRangesCmp::Compare(const TSynFoldRange& Left, const TSynFoldRange& Right)
{
	int result = 0;
	result = Left.FromLine - Right.FromLine;
	return result;
}

int __fastcall TLineFoldInfoCmp::Compare(const TLineFoldInfo& Left, const TLineFoldInfo& Right)
{
	int result = 0;
	result = Left.Line - Right.Line;
	return result;
}

System::Generics::Collections::TList__1<TSynFoldRange>* __fastcall CreateFoldRangeList()
{
	System::Generics::Collections::TList__1<TSynFoldRange>* result = nullptr;
	result = new System::Generics::Collections::TList__1<TSynFoldRange>(new TSynFoldRangesCmp());
	return result;
}

System::Generics::Collections::TList__1<TLineFoldInfo>* __fastcall CreateFoldInfoList()
{
	System::Generics::Collections::TList__1<TLineFoldInfo>* result = nullptr;
	result = new System::Generics::Collections::TList__1<TLineFoldInfo>(new TLineFoldInfoCmp());
	return result;
}


/* TSynEditFoldRange */

__fastcall TSynFoldRange::TSynFoldRange(int AFromLine, int AToLine/*# = -1*/, int AFoldType/*# = 1*/, int AIndent/*# = -1*/, bool ACollapsed/*# = false*/)
 : FromLine(AFromLine),
			ToLine(AToLine),
			FoldType(AFoldType),
			Indent(AIndent),
			Collapsed(ACollapsed)
{
}

int __fastcall TSynFoldRange::GetLinesCollapsed()
{
	int result = 0;
	if(Collapsed)
		result = ToLine - FromLine;
	else
		result = 0;
	return result;
}

void __fastcall TSynFoldRange::Move(int Count)
{
	FromLine += Count;
	ToLine += Count;
}

__fastcall TLineFoldInfo::TLineFoldInfo(int ALine, TFoldOpenClose AFoldOpenClose/*# = focOpen*/, int AFoldType/*# = 1*/, int AIndent/*# = -1*/)
 : Line(ALine),
			FoldOpenClose(AFoldOpenClose),
			FoldType(AFoldType),
			Indent(AIndent)
{
}

void __fastcall AddToFoldRangeList(System::Generics::Collections::TList__1<TSynFoldRange>* AList, const TSynFoldRange& cARange)
{
	TSynFoldRange ARange = cARange;
	AList->Add(ARange);
}

void __fastcall InsertIntoFoldRangeList(System::Generics::Collections::TList__1<TSynFoldRange>* AList, int AIndex, const TSynFoldRange& cARange)
{
	TSynFoldRange ARange = cARange;
	AList->Insert(AIndex, ARange);
}

bool __fastcall BinarySearchInFoldRangeList(System::Generics::Collections::TList__1<TSynFoldRange>* AList, const TSynFoldRange& cARange, int& AIndex)
{
	TSynFoldRange ARange = cARange;
	bool result = false;
	result = AList->BinarySearch(ARange, AIndex);
	return result;
}

// for SynEditCodeFolding

void __fastcall InsertIntoLineFoldList(System::Generics::Collections::TList__1<TLineFoldInfo>* AList, int AIndex, const TLineFoldInfo& cAInfo)
{
	TLineFoldInfo AInfo = cAInfo;
	AList->Insert(AIndex, AInfo);
}

bool __fastcall BinarySearchInLineFoldList(System::Generics::Collections::TList__1<TLineFoldInfo>* AList, const TLineFoldInfo& cAInfo, int& AIndex)
{
	TLineFoldInfo AInfo = cAInfo;
	bool result = false;
	result = AList->BinarySearch(AInfo, AIndex);
	return result;
}

/* TBufferCoord */

bool __fastcall operator == (const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	bool result = false;
	result = (A.Char == B.Char) && (A.Line == B.Line);
	return result;
}

bool __fastcall operator > (const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	bool result = false;
	result = (B.Line < A.Line) || ((B.Line == A.Line) && (B.Char < A.Char));
	return result;
}

bool __fastcall operator >= (const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	bool result = false;
	result = (B.Line < A.Line) || ((B.Line == A.Line) && (B.Char <= A.Char));
	return result;
}

bool __fastcall operator < (const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	bool result = false;
	result = (B.Line > A.Line) || ((B.Line == A.Line) && (B.Char > A.Char));
	return result;
}

bool __fastcall operator <= (const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	bool result = false;
	result = (B.Line > A.Line) || ((B.Line == A.Line) && (B.Char >= A.Char));
	return result;
}

/*#static*/
TBufferCoord __fastcall TBufferCoord::Max(const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	TBufferCoord result = {};
	if((B.Line < A.Line) || ((B.Line == A.Line) && (B.Char < A.Char)))
		result = A;
	else
		result = B;
	return result;
}

/*#static*/
TBufferCoord __fastcall TBufferCoord::Min(const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	TBufferCoord result = {};
	if((B.Line < A.Line) || ((B.Line == A.Line) && (B.Char < A.Char)))
		result = B;
	else
		result = A;
	return result;
}

bool __fastcall operator != (const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	bool result = false;
	result = (A.Char != B.Char) || (A.Line != B.Line);
	return result;
}
System::Generics::Collections::TList__1<TSynFoldRange>* rlist = nullptr;
TSynFoldRange R = {};
static bool SynEditDelphiInstances_Initialized = false;

void SynEditDelphiInstances_initialization()
{
	if(SynEditDelphiInstances_Initialized)
		return;
	
	SynEditDelphiInstances_Initialized = true;
	
	delete new System::Generics::Collections::TList__1<System::Word>();
	delete new System::Generics::Collections::TList__1<int>();
	delete new System::Generics::Collections::TList__1<TLineFoldInfo>();
	delete new System::Generics::Collections::TEnumerable__1<System::Word>();
	rlist = new System::Generics::Collections::TList__1<TSynFoldRange>();
	rlist->Add(R);
	delete rlist;
	delete new System::Generics::Collections::TObjectStack__1<TSynUndoItem*>();
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynEditDelphiInstances

