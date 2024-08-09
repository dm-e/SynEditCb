#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterMulti.h"
#include <Vcl.Graphics.hpp>
#include "SynEditMiscProcs.h"
#include "SynEditStrConst.h"
#include <System.RegularExpressions.hpp>
#include <System.SysUtils.hpp>
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditmiscclasses;
using namespace Syneditmiscprocs;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Regularexpressions;
using namespace System::Sysutils;
using namespace Vcl::Graphics;

namespace Synhighlightermulti
{
#define Synhighlightermulti__0 (TRegExOptions() << roNotEmpty << roCompiled)
#define Synhighlightermulti__1 (TRegExOptions() << roNotEmpty << roCompiled)
#define Synhighlightermulti__2 (TRegExOptions() << roNotEmpty << roIgnoreCase << roCompiled)
#define Synhighlightermulti__3 (TRegExOptions() << roNotEmpty << roCompiled)
#define Synhighlightermulti__4 (TRegExOptions() << roNotEmpty << roIgnoreCase << roCompiled)
#define Synhighlightermulti__5 (TFontStyles() << TFontStyle::fsBold)

__fastcall TSchemes::TSchemes(TCollectionItemClass ItemClass) : inherited(ItemClass) {}
__fastcall TMarker::TMarker() {}



void __fastcall CheckExpression(const String expr)
{
	TRegEx Parser = {};
  // will raise an exception if the expression is incorrect
	Parser = TRegEx(expr, Synhighlightermulti__0);
}

/* TMarker */

__fastcall TMarker::TMarker(int aScheme, int aStartPos, int aMarkerLen, bool aIsOpenMarker, const String aMarkerText)
 : fScheme(aScheme),
			fStartPos(aStartPos),
			fMarkerLen(aMarkerLen),
			fMarkerText(aMarkerText),
			fIsOpenMarker(false)
{
	fIsOpenMarker = aIsOpenMarker;
}

/* TSynMultiSyn */

void __fastcall TSynMultiSyn::ClearMarkers()
{
	int i = 0;
	int stop = 0;
	for(stop = fMarkers->Count - 1, i = 0; i <= stop; i++)
	{
		delete ((TObject*) fMarkers->Items[i]);
	}
	fMarkers->Clear();
}

__fastcall TSynMultiSyn::TSynMultiSyn(TComponent* AOwner)
 : inherited(AOwner),
			fMarkers(nullptr),
			fMarker(nullptr),
			fNextMarker(0),
			fCurrScheme(0),
			fTmpRange(nullptr),
			fSchemes(nullptr),
			fDefaultHighlighter(nullptr),
			fLineNumber(0)
{
	fSchemes = new TSchemes(this);
	fCurrScheme = -1;
	fMarkers = new TList();
	fRangeProc = NewRangeProc;
}

__fastcall TSynMultiSyn::~TSynMultiSyn()
{
	ClearMarkers();
  /* unhook notification handlers */
	Schemes->Clear();
	DefaultHighlighter = nullptr;
	//# inherited::Destroy();
	inherited::RemoveFreeNotifications();
	delete fSchemes;
	delete fMarkers;
}

int __fastcall TSynMultiSyn::GetAttribCount()
{
	int result = 0;
	int i = 0;
	int stop = 0;
	result = Schemes->Count;
	if(DefaultHighlighter != nullptr)
		result += DefaultHighlighter->AttrCount;
	for(stop = Schemes->Count - 1, i = 0; i <= stop; i++)
	{
		if(Schemes->Items[i]->Highlighter != nullptr)
			result += Schemes->Items[i]->Highlighter->AttrCount;
	}
	return result;
}

TSynHighlighterAttributes* __fastcall TSynMultiSyn::getAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	int i = 0;
	TSynCustomHighlighter* hl = nullptr;
	if(Index < Schemes->Count)
		result = Schemes->Items[Index]->MarkerAttri;
	else
	{
		int stop = 0;
		Index -= Schemes->Count;
		if(DefaultHighlighter != nullptr)
		{
			if(Index < DefaultHighlighter->AttrCount)
			{
				result = DefaultHighlighter->Attribute[Index];
				return result;
			}
			else
			Index -= DefaultHighlighter->AttrCount;
		}
		for(stop = Schemes->Count - 1, i = 0; i <= stop; i++)
		{
			hl = Schemes->Items[i]->Highlighter;
			if(hl != nullptr)
			{
				if(Index < hl->AttrCount)
				{
					result = hl->Attribute[Index];
					return result;
				}
				else
				Index -= hl->AttrCount;
			}
		}
		result = nullptr;
	}
	return result;
}

TSynHighlighterAttributes* __fastcall TSynMultiSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	TSynCustomHighlighter* hl = nullptr;
	if((CurrScheme >= 0) && (Schemes->Items[CurrScheme]->Highlighter != nullptr))
		hl = Schemes->Items[CurrScheme]->Highlighter;
	else
		hl = DefaultHighlighter;
  /* the typecast to TSynMultiSyn is only necessary because the
  GetDefaultAttribute method is protected.
  And don't worry: this really works */
	if(hl != nullptr)
		result = ((TSynMultiSyn*) hl)->GetDefaultAttribute(Index);
	else
		result = nullptr;
	return result;
}

bool __fastcall TSynMultiSyn::GetEol()
{
	bool result = false;
	if(fMarker != nullptr)
		result = false;
	else
	{
		if(fCurrScheme >= 0)
			result = Schemes->Items[CurrScheme]->Highlighter->GetEol();
		else
		{
			if(DefaultHighlighter != nullptr)
				result = DefaultHighlighter->GetEol();
			else
				result = Run > fLineLen + 1;
		}
	}
	return result;
}

/*#static*/
String __fastcall TSynMultiSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangGeneralMulti;
	return result;
}

TMarker* __fastcall TSynMultiSyn::GetMarkers(int Index)
{
	TMarker* result = nullptr;
	result = ((TMarker*) fMarkers->Items[Index]);
	return result;
}

void __fastcall TSynMultiSyn::OldRangeProc(TRangeOperation Operation, TRangeUNativeInt& Range)
{
	const int MaxNestedMultiSyn = 6;
  /* number of bits of the Range that will be used to store the SchemeIndex */
	const int SchemeIndexSize = 4;
	const int MaxSchemeCount = (1 << SchemeIndexSize) - 1;
  /* number of bits of the Range that will be used to store the SchemeRange */
	const int SchemeRangeSize = 8;
	const int MaxSchemeRange = (1 << SchemeRangeSize) - 1;
	TSynCustomHighlighter* iHL = nullptr;
	unsigned int iSchemeIndex = 0;
	unsigned int iSchemeRange = 0;
	if(Operation == roGet)
	{
		if(fCurrScheme < 0)
			iHL = DefaultHighlighter;
		else
			iHL = Schemes->Items[fCurrScheme]->Highlighter;
		iSchemeIndex = (unsigned int) (fCurrScheme + 2);
		Assert(iSchemeIndex <= MaxSchemeCount);
		if(iHL != nullptr)
		{
			iSchemeRange = (NativeUInt)iHL->GetRange();
			Assert((iSchemeRange <= MaxSchemeRange) || (ObjectIs(iHL, TSynMultiSyn*)));
		}
		else
		iSchemeRange = 0;
    /* checks the limit of nested MultiSyns */
		Assert(iSchemeRange >> ((MaxNestedMultiSyn - 1) * SchemeIndexSize + SchemeRangeSize) == 0);
		iSchemeRange = (unsigned int) ((iSchemeRange << SchemeIndexSize) | iSchemeIndex);
		Range = iSchemeRange;
	}
	else
	{
		if(Range == 0)
			return;
		iSchemeRange = ((unsigned int) Range);
		fCurrScheme = iSchemeRange & MaxSchemeCount - 2;
		iSchemeRange = (unsigned int) (iSchemeRange >> SchemeIndexSize);
		if(CurrScheme < 0)
		{
			if(DefaultHighlighter != nullptr)
				DefaultHighlighter->SetRange(((void*) iSchemeRange));
		}
		else
		Schemes->Items[CurrScheme]->Highlighter->SetRange(((void*) iSchemeRange));
	}
}

String __fastcall TSynMultiSyn::GetToken()
{
	String result;
	if(DefaultHighlighter == nullptr)
		result = fLineStr;
	else
		result = inherited::GetToken();
	return result;
}

TSynHighlighterAttributes* __fastcall TSynMultiSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	if(fMarker != nullptr)
		result = Schemes->Items[fMarker->fScheme]->MarkerAttri;
	else
	{
		if(CurrScheme >= 0)
			result = Schemes->Items[CurrScheme]->Highlighter->GetTokenAttribute();
		else
		{
			if(DefaultHighlighter != nullptr)
				result = DefaultHighlighter->GetTokenAttribute();
			else
				result = nullptr;
		}
	}
	return result;
}

int __fastcall TSynMultiSyn::GetTokenKind()
{
	int result = 0;
	if(fMarker != nullptr)
		result = 0;
	else
	{
		if(fCurrScheme >= 0)
			result = Schemes->Items[fCurrScheme]->Highlighter->GetTokenKind();
		else
		{
			if(DefaultHighlighter != nullptr)
				result = DefaultHighlighter->GetTokenKind();
			else
				result = 0;
		}
	}
	return result;
}

void __fastcall TSynMultiSyn::HookHighlighter(TSynCustomHighlighter* aHL)
{
	aHL->FreeNotification(this);
	aHL->HookAttrChangeEvent(DefHighlightChange);
}

void __fastcall TSynMultiSyn::Next()
{
	String iToken;
	String TmpLine;
	String ExpandedTmpLine;
	TSynCustomHighlighter* iHL = nullptr;
	if(DefaultHighlighter == nullptr)
	{
		if(Run > 0)
			++Run;
		else
			Run = fLineStr.Length() + 1;
		inherited::Next();
		return;
	}
	if((fNextMarker < fMarkers->Count) && (Run + 1 >= Markers[fNextMarker]->fStartPos))
	{
		fMarker = Markers[fNextMarker];
		if(fMarker->fIsOpenMarker)
		{
			fCurrScheme = fMarker->fScheme;
			fTmpRange = DefaultHighlighter->GetRange();
			Schemes->Items[CurrScheme]->Highlighter->ResetRange();
		}
		++fNextMarker;
		fTokenPos = Run;
		Run += fMarker->fMarkerLen;
		inherited::Next();
		return;
	}
	if(Run == 0)
	{
		if(CurrScheme >= 0)
			iHL = Schemes->Items[CurrScheme]->Highlighter;
		else
			iHL = DefaultHighlighter;
		if(fMarkers->Count == 0)
			TmpLine = fLineStr;
		else
			TmpLine = fLineStr.SubString(1, Markers[fNextMarker]->fStartPos - 1);
		if(fExpandedLine != nullptr)
		{
			if(fMarkers->Count == 0)
				ExpandedTmpLine = fExpandedLineStr;
			else
				ExpandedTmpLine = fExpandedLineStr.SubString(1, PosToExpandedPos(Markers[fNextMarker]->fStartPos - 1));
			iHL->SetLineExpandedAtWideGlyphs(TmpLine, ExpandedTmpLine, fLineNumber);
		}
		else
		iHL->SetLine(TmpLine, fLineNumber);
	}
	else
	{
		if(fMarker != nullptr)
		{
			if(!fMarker->fIsOpenMarker)
			{
				fCurrScheme = -1;
				DefaultHighlighter->SetRange(fTmpRange);
			}
			fMarker = nullptr;
			if(CurrScheme >= 0)
				iHL = Schemes->Items[CurrScheme]->Highlighter;
			else
				iHL = DefaultHighlighter;
			if(fNextMarker < fMarkers->Count)
				TmpLine = fLineStr.SubString(Run + 1, Markers[fNextMarker]->fStartPos - Run - 1);
			else
				TmpLine = fLineStr.SubString(Run + 1, MaxInt);
			if(fExpandedLine != nullptr)
			{
				if(fNextMarker < fMarkers->Count)
					ExpandedTmpLine = fExpandedLineStr.SubString(ExpandedRun + 1, PosToExpandedPos(Markers[fNextMarker]->fStartPos - Run - 1));
				else
					ExpandedTmpLine = fExpandedLineStr.SubString(ExpandedRun + 1, MaxInt);
				iHL->SetLineExpandedAtWideGlyphs(TmpLine, ExpandedTmpLine, fLineNumber);
			}
			else
			iHL->SetLine(TmpLine, fLineNumber);
		}
		else
		{
			if(CurrScheme >= 0)
				iHL = Schemes->Items[CurrScheme]->Highlighter;
			else
				iHL = DefaultHighlighter;
			iHL->Next();
		}
	}
	fTokenPos = iHL->GetTokenPos();
	iToken = iHL->GetToken();
	if(fNextMarker > 0)
		/*# with Markers[fNextMarker-1] do */
		{
			
			fTokenPos += Markers[fNextMarker - 1]->fStartPos + Markers[fNextMarker - 1]->fMarkerLen - 1;
		}
	Run += (fTokenPos - Run) + iToken.Length();
	inherited::Next();
}

void __fastcall TSynMultiSyn::Notification(TComponent* aComp, TOperation aOp)
{
	int i = 0;
	inherited::Notification(aComp, aOp);
  // 'opRemove' doesn't mean the component is being destroyed. It means it's
  // being removed from its Owner's list of Components.
	if((aOp == opRemove) && (ObjectIs(aComp, TSynCustomHighlighter*)) && (aComp->ComponentState.Contains(csDestroying)))
	{
		int stop = 0;
		if(DefaultHighlighter == aComp)
			DefaultHighlighter = nullptr;
		for(stop = Schemes->Count - 1, i = 0; i <= stop; i++)
		{
			if(Schemes->Items[i]->Highlighter == aComp)
				Schemes->Items[i]->Highlighter = nullptr;
		}
	}
}

void __fastcall TSynMultiSyn::ResetRange()
{
	fCurrScheme = -1;
	if(DefaultHighlighter != nullptr)
	{
		DefaultHighlighter->ResetRange();
		fTmpRange = DefaultHighlighter->GetRange();
	}
}

void __fastcall TSynMultiSyn::SetDefaultHighlighter(TSynCustomHighlighter* const Value)
{
	const WideChar sDefaultHlSetToSelf[] = L"A SynMultiSyn cannot be its own DefaultHighlighter.";
	if(DefaultHighlighter != Value)
	{
		if(Value == this)
			throw new Exception(sDefaultHlSetToSelf);
		if(DefaultHighlighter != nullptr)
			UnhookHighlighter(DefaultHighlighter);
		fDefaultHighlighter = const_cast<TSynCustomHighlighter*>(Value);
		if(DefaultHighlighter != nullptr)
			HookHighlighter(DefaultHighlighter);
		DefHighlightChange(this);
	}
}

void __fastcall TSynMultiSyn::DoCheckMarker(TScheme* Scheme, int StartPos, int MarkerLen, const String MarkerText, bool Start, int Line, const String LineStr)
{
	int aStartPos = 0;
	int aMarkerLen = 0;
	String aMarkerText;
	aStartPos = StartPos;
	aMarkerLen = MarkerLen;
	aMarkerText = MarkerText;
	if(Start && ASSIGNED(Scheme->OnCheckStartMarker))
		Scheme->OnCheckStartMarker(this, aStartPos, aMarkerLen, aMarkerText, Line, LineStr);
	else
	{
		if(!Start && ASSIGNED(Scheme->OnCheckEndMarker))
			Scheme->OnCheckEndMarker(this, aStartPos, aMarkerLen, aMarkerText, Line, LineStr);
	}
	if((aMarkerText != L"") && (aMarkerLen > 0))
	{
		fMarkers->Add(new TMarker(Scheme->Index, aStartPos, aMarkerLen, Start, aMarkerText));
	}
}

void __fastcall TSynMultiSyn::SetSchemes(TSchemes* const Value)
{
	fSchemes->Assign((TPersistent*) Value);
}

void __fastcall TSynMultiSyn::UnhookHighlighter(TSynCustomHighlighter* aHL)
{
	aHL->UnhookAttrChangeEvent(DefHighlightChange);
	aHL->RemoveFreeNotification(this);
}

String __fastcall TSynMultiSyn::GetSampleSource()
{
	String result;
	result = fSampleSource;
	return result;
}

void __fastcall TSynMultiSyn::SetSampleSource(String Value)
{
	fSampleSource = Value;
}

bool __fastcall TSynMultiSyn::LoadFromRegistry(HKEY RootKey, String key)
{
	bool result = false;
	TBetterRegistry* R = nullptr;
	int i = 0;
	if(DefaultHighlighter != nullptr)
		result = DefaultHighlighter->LoadFromRegistry(RootKey, key + L"\\DefaultHighlighter");
	else
		result = false;
	R = new TBetterRegistry();
	try
	{
		int stop = 0;
		R->RootKey = RootKey;
		for(stop = Schemes->Count - 1, i = 0; i <= stop; i++)
		{
			if((Schemes->Items[i]->SchemeName != L"") && R->OpenKeyReadOnly(key + L"\\" + Schemes->Items[i]->SchemeName))
			{
				result = Schemes->Items[i]->MarkerAttri->LoadFromRegistry(R) && result;
				R->CloseKey();
				result = (Schemes->Items[i]->Highlighter != nullptr) && Schemes->Items[i]->Highlighter->LoadFromRegistry(RootKey, key + L"\\" + Schemes->Items[i]->SchemeName) && result;
			}
			else
			result = false;
		}
	}
	__finally
	{
		delete R;
	}
	return result;
}

bool __fastcall TSynMultiSyn::SaveToRegistry(HKEY RootKey, String key)
{
	bool result = false;
	TBetterRegistry* R = nullptr;
	int i = 0;
	if(DefaultHighlighter != nullptr)
		result = DefaultHighlighter->SaveToRegistry(RootKey, key + L"\\DefaultHighlighter");
	else
		result = false;
	R = new TBetterRegistry();
	try
	{
		int stop = 0;
		R->RootKey = RootKey;
		for(stop = Schemes->Count - 1, i = 0; i <= stop; i++)
		{
			if((Schemes->Items[i]->SchemeName != L"") && R->OpenKey(key + L"\\" + Schemes->Items[i]->SchemeName, true))
			{
				result = Schemes->Items[i]->MarkerAttri->SaveToRegistry(R) && result;
				R->CloseKey();
				result = (Schemes->Items[i]->Highlighter != nullptr) && Schemes->Items[i]->Highlighter->SaveToRegistry(RootKey, key + L"\\" + Schemes->Items[i]->SchemeName) && result;
			}
			else
			result = false;
		}
	}
	__finally
	{
		delete R;
	}
	return result;
}

void* __fastcall TSynMultiSyn::GetRange()
{
	void* result = nullptr;
	result = nullptr;
	fRangeProc(roGet, ((TRangeUNativeInt&) result));
	return result;
}

void __fastcall TSynMultiSyn::SetRange(void* Value)
{
	fRangeProc(roSet, ((TRangeUNativeInt&) Value));
}

void __fastcall TSynMultiSyn::NewRangeProc(TRangeOperation Operation, TRangeUNativeInt& Range)
{
	const int SchemeIndexSize = 3;
	const int MaxSchemeCount = (1 << SchemeIndexSize) - 1;
	const int SchemeRangeSize = 4;
	const int MaxSchemeRange = (1 << SchemeRangeSize) - 1;
	if(Operation == roGet)
	{
		if(DefaultHighlighter != nullptr)
			Range = (NativeUInt)DefaultHighlighter->GetRange();
		else
			Range = 0;
		if(CurrScheme >= 0)
		{
			Assert((NativeUInt)Schemes->Items[CurrScheme]->Highlighter->GetRange() <= MaxSchemeRange);
			Range = (TRangeUNativeInt) (Range << SchemeRangeSize);
			Range = (TRangeUNativeInt) (Range | (NativeUInt)Schemes->Items[CurrScheme]->Highlighter->GetRange());
		}
		Assert(CurrScheme <= MaxSchemeCount);
		Range = (TRangeUNativeInt) (Range << SchemeIndexSize);
		Range = (TRangeUNativeInt) (Range | ((unsigned int) (CurrScheme + 1)));
	}
	else
	{
		CurrScheme = Range & MaxSchemeCount - 1;
		Range = (TRangeUNativeInt) (Range >> SchemeIndexSize);
		if(CurrScheme >= 0)
		{
			Schemes->Items[CurrScheme]->Highlighter->SetRange(((void*) (Range & MaxSchemeRange)));
			Range = (TRangeUNativeInt) (Range >> SchemeRangeSize);
		}
		if(DefaultHighlighter != nullptr)
		{
			fTmpRange = ((void*) Range);
			DefaultHighlighter->SetRange(fTmpRange);
		}
	}
}
// determines the appropriate RangeProcs and returns whether they were changed

bool __fastcall TSynMultiSyn::UpdateRangeProcs()
{
	bool result = false;
	int i = 0;
	TRangeProc OldProc;
	OldProc = fRangeProc;
	if(ASSIGNED(OnCustomRange))
		fRangeProc = UserRangeProc;
	else
	{
		int stop = 0;
		fRangeProc = NewRangeProc;
		for(stop = Schemes->Count - 1, i = 0; i <= stop; i++)
		{
			if(ObjectIs(Schemes->Items[i]->Highlighter, TSynMultiSyn*))
			{
				fRangeProc = OldRangeProc;
				break;
			}
		}
	}
	result = ((TMethod*) &OldProc)->Code != ((TMethod*) &fRangeProc)->Code;
	if(result)
		DefHighlightChange(this);
	return result;
}

void __fastcall TSynMultiSyn::UserRangeProc(TRangeOperation Operation, TRangeUNativeInt& Range)
{
	OnCustomRange(this, Operation, ((void*&) Range));
	if((Operation == roSet) && (DefaultHighlighter != nullptr))
		fTmpRange = DefaultHighlighter->GetRange();
}

void __fastcall TSynMultiSyn::SetOnCustomRange(const TCustomRangeEvent Value)
{
	if((((TMethod*) &OnCustomRange)->Code != ((TMethod*) &Value)->Code) || (((TMethod*) &OnCustomRange)->Data != ((TMethod*) &Value)->Data))
	{
		fOnCustomRange = Value;
		UpdateRangeProcs();
	}
}

void __fastcall TSynMultiSyn::Loaded()
{
	inherited::Loaded();
	DefHighlightChange(this);
}

bool __fastcall TSynMultiSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	if(CurrScheme >= 0)
		result = Schemes->Items[CurrScheme]->Highlighter->IsIdentChar(AChar);
	else
	{
		if(DefaultHighlighter != nullptr)
			result = DefaultHighlighter->IsIdentChar(AChar);
		else
			result = inherited::IsIdentChar(AChar);
	}
	return result;
}

/*#static*/
String __fastcall TSynMultiSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangGeneralMulti;
	return result;
}

void __fastcall TSynMultiSyn::DoSetLine(const String Value, int LineNumber)
{
	TRegEx iParser = {};
	TMatch Match = {};
	TScheme* iScheme = nullptr;
	String iExpr;
	String iLine;
	int iEaten = 0;
	int i = 0;
	ClearMarkers();
	iEaten = 0;
	iLine = Value;
	if(CurrScheme >= 0)
		iScheme = fSchemes->Items[CurrScheme];
	else
		iScheme = nullptr;
	while(iLine != L"")
		if(iScheme != nullptr)
		{
			if(iScheme->CaseSensitive)
				iParser = TRegEx(iScheme->EndExpr, Synhighlightermulti__1);
			else
				iParser = TRegEx(iScheme->EndExpr, Synhighlightermulti__2);
			Match = iParser.Match(iLine);
			if(Match.Success)
			{
				iExpr = Value.SubString(Match.Index + iEaten, Match.Length);
				DoCheckMarker(iScheme, Match.Index + iEaten, Match.Length, iExpr, false, LineNumber, Value);
				iLine.Delete(1, Match.Index - 1 + Match.Length);
				iEaten += Match.Index - 1 + Match.Length;
				iScheme = nullptr;
			}
			else
			break;
		}
		else
		{
			int stop = 0;
			for(stop = Schemes->Count - 1, i = 0; i <= stop; i++)
			{
				iScheme = Schemes->Items[i];
				if((iScheme->StartExpr == L"") || (iScheme->EndExpr == L"") || (iScheme->Highlighter == nullptr) || (!iScheme->Highlighter->Enabled))
				{
					continue;
				}
				if(iScheme->CaseSensitive)
					iParser = TRegEx(iScheme->StartExpr, Synhighlightermulti__3);
				else
					iParser = TRegEx(iScheme->StartExpr, Synhighlightermulti__4);
				Match = iParser.Match(iLine);
				if(Match.Success)
				{
					iExpr = Value.SubString(Match.Index + iEaten, Match.Length);
					DoCheckMarker(iScheme, Match.Index + iEaten, Match.Length, iExpr, true, LineNumber, Value);
					iLine.Delete(1, Match.Index - 1 + Match.Length);
					iEaten += Match.Index - 1 + Match.Length;
					break;
				}
			} /*for*/
			if(i >= Schemes->Count)
				break;
		} /*else*/
	fLineStr = Value;
	fLine = ustr2pwchar(fLineStr);
	fCasedLineStr = L"";
	fCasedLine = ustr2pwchar(fLineStr);
	fMarker = nullptr;
	Run = 0;
	ExpandedRun = 0;
	fOldRun = Run;
	fTokenPos = 0;
	fExpandedTokenPos = 0;
	fNextMarker = 0;
	fLineNumber = LineNumber;
}

String __fastcall TSynMultiSyn::GetExpandedToken()
{
	String result;
	if((DefaultHighlighter == nullptr) && (fExpandedLine != nullptr))
		result = fExpandedLineStr;
	else
		result = inherited::GetExpandedToken();
	return result;
}

/* TSchemes */

__fastcall TSchemes::TSchemes(TSynMultiSyn* AOwner)
 : inherited(__classid(TScheme)),
			FOwner(AOwner)
{
}

TScheme* __fastcall TSchemes::GetItems(int Index)
{
	TScheme* result = nullptr;
	result = (TScheme*) inherited::Items[Index];
	return result;
}

TPersistent* __fastcall TSchemes::GetOwner()
{
	TPersistent* result = nullptr;
	result = FOwner;
	return result;
}

void __fastcall TSchemes::SetItems(int Index, TScheme* const Value)
{
	inherited::Items[Index] = (TCollectionItem*) Value;
}

void __fastcall TSchemes::Update(TCollectionItem* Item)
{
	if(Item != nullptr)
		FOwner->DefHighlightChange(Item);
	else
 // pass the MultiSyn as the Sender so Editors reparse their text
		FOwner->DefHighlightChange(FOwner);
}

/* TScheme */

String __fastcall TScheme::ConvertExpression(const String Value)
{
	String result;
	if(!CaseSensitive)
		result = Sysutils::AnsiUpperCase(Value);
	else
		result = Value;
	return result;
}

__fastcall TScheme::TScheme(TCollection* Collection)
 : inherited(Collection),
			fHighlighter(nullptr),
			fMarkerAttri(nullptr),
			FCaseSensitive(false)
{
	FCaseSensitive = true;
	fMarkerAttri = new TSynHighlighterAttributes(SYNS_AttrMarker, SYNS_FriendlyAttrMarker);
	fMarkerAttri->OnChange = MarkerAttriChanged;
	MarkerAttri->Background = clYellow;
	MarkerAttri->Style = Synhighlightermulti__5;
	MarkerAttri->InternalSaveDefaultValues();
}

__fastcall TScheme::~TScheme()
{

  /* unhook notification handlers */
	Highlighter = nullptr;
	//# inherited::Destroy();
	delete fMarkerAttri;
}

void __fastcall TScheme::DefineProperties(TFiler* Filer)
{
	inherited::DefineProperties(Filer);
}

String __fastcall TScheme::GetDisplayName()
{
	String result;
	if(SchemeName != L"")
		result = SchemeName;
	else
		result = inherited::GetDisplayName();
	return result;
}

void __fastcall TScheme::MarkerAttriChanged(TObject* Sender)
{
	Changed(false);
}

void __fastcall TScheme::SetCaseSensitive(bool Value)
{
	if(FCaseSensitive != Value)
	{
		FCaseSensitive = Value;
		Changed(true);
	}
}

void __fastcall TScheme::SetDisplayName(const String Value)
{
	SchemeName = Value;
}

void __fastcall TScheme::SetEndExpr(const String Value)
{
	String OldValue;
	if(fEndExpr != Value)
	{
		if(Value != L"")
			CheckExpression(Value);
		OldValue = fEndExpr;
		fEndExpr = Value;
		if(ConvertExpression(OldValue) != ConvertExpression(Value))
			Changed(true);
	}
}

void __fastcall TScheme::SetHighlighter(TSynCustomHighlighter* const Value)
{
	TSynMultiSyn* iOwner = nullptr;
	bool iAlreadyRepainted = false;
	if(Highlighter != Value)
	{
		iOwner = ((TSchemes*) Collection)->FOwner;
		if((Highlighter != nullptr) && (Highlighter != iOwner))
			iOwner->UnhookHighlighter(Highlighter);
		fHighlighter = const_cast<TSynCustomHighlighter*>(Value);
		if((Highlighter != nullptr) && (Highlighter != iOwner))
			iOwner->HookHighlighter(Highlighter);
		if(ObjectIs(Highlighter, TSynMultiSyn*))
			iAlreadyRepainted = iOwner->UpdateRangeProcs();
		else
			iAlreadyRepainted = false;
		if(!iAlreadyRepainted)
			Changed(true);
	}
}

void __fastcall TScheme::SetMarkerAttri(TSynHighlighterAttributes* const Value)
{
	fMarkerAttri->Assign((TPersistent*) Value);
}

void __fastcall TScheme::SetStartExpr(const String Value)
{
	String OldValue;
	if(fStartExpr != Value)
	{
		if(Value != L"")
			CheckExpression(Value);
		OldValue = fStartExpr;
		fStartExpr = Value;
		if(ConvertExpression(Value) != ConvertExpression(OldValue))
			Changed(true);
	}
}


}  // namespace SynHighlighterMulti

