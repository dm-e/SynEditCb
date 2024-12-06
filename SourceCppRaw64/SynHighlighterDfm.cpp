
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterDfm.h"
#include "SynEditStrConst.h"
#include "OnLeavingScope.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;

namespace Synhighlighterdfm
{
#define Synhighlighterdfm__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterdfm__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterdfm__2 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterdfm__3 (TSysCharSet() << 'n' << 'N')
#define Synhighlighterdfm__4 (TSysCharSet() << 'd' << 'D')
#define Synhighlighterdfm__5 (TSysCharSet() << 'b' << 'B')
#define Synhighlighterdfm__6 (TSysCharSet() << 'j' << 'J')
#define Synhighlighterdfm__7 (TSysCharSet() << 'e' << 'E')
#define Synhighlighterdfm__8 (TSysCharSet() << 'c' << 'C')
#define Synhighlighterdfm__9 (TSysCharSet() << 't' << 'T')
#define Synhighlighterdfm__10 (TSysCharSet() << 'n' << 'N')
#define Synhighlighterdfm__11 (TSysCharSet() << 'h' << 'H')
#define Synhighlighterdfm__12 (TSysCharSet() << 'e' << 'E')
#define Synhighlighterdfm__13 (TSysCharSet() << 'r' << 'R')
#define Synhighlighterdfm__14 (TSysCharSet() << 'i' << 'I')
#define Synhighlighterdfm__15 (TSysCharSet() << 't' << 'T')
#define Synhighlighterdfm__16 (TSysCharSet() << 'e' << 'E')
#define Synhighlighterdfm__17 (TSysCharSet() << 'd' << 'D')
#define Synhighlighterdfm__18 (TSysCharSet() << 'n' << 'N')
#define Synhighlighterdfm__19 (TSysCharSet() << 'l' << 'L')
#define Synhighlighterdfm__20 (TSysCharSet() << 'i' << 'I')
#define Synhighlighterdfm__21 (TSysCharSet() << 'n' << 'N')
#define Synhighlighterdfm__22 (TSysCharSet() << 'e' << 'E')
#define Synhighlighterdfm__23 (TSysCharSet() << 'e' << 'E')
#define Synhighlighterdfm__24 (TSysCharSet() << 'o' << 'O')
#define Synhighlighterdfm__25 (TSysCharSet() << 'i' << 'I')



/* A couple of useful Delphi Form functions */

int __fastcall LoadDFMFile2Strings(const String AFile, TStrings* AStrings, bool& WasText)
{
	int result = 0;
	TStream* Src = nullptr;
	TStream* Dest = nullptr;
	TStreamOriginalFormat origFormat = sofUnknown;
	result = 0;
	WasText = false;
	AStrings->Clear();
	try
	{
		Src = new TFileStream(AFile, (WORD) (fmOpenRead | fmShareDenyWrite));
		{
			auto olsLambda = onLeavingScope([&] 
			{
				delete Src;
			});
			Dest = new TMemoryStream();
			{
				auto olsLambda = onLeavingScope([&] 
				{
					delete Dest;
				});
				origFormat = sofUnknown;
				ObjectResourceToText(Src, Dest, origFormat);
				WasText = origFormat == sofText;
				Dest->Seek(0, (WORD) soFromBeginning);
				AStrings->LoadFromStream(Dest);
			}
		}
	}
	catch(EInOutError* E)
	{
		result = -E->ErrorCode;
	}
	catch(...)
	{
		result = -1;
	}
	return result;
}

int __fastcall SaveStrings2DFMFile(TStrings* AStrings, const String AFile)
{
	int result = 0;
	TStream* Src = nullptr;
	TStream* Dest = nullptr;
	result = 0;
	try
	{
		Src = new TMemoryStream();
		{
			auto olsLambda = onLeavingScope([&] 
			{
				delete Src;
			});
			AStrings->SaveToStream(Src);
			Src->Seek(0, (WORD) soFromBeginning);
			Dest = new TFileStream(AFile, (WORD) fmCreate);
			{
				auto olsLambda = onLeavingScope([&] 
				{
					delete Dest;
				});
				ObjectTextToResource(Src, Dest);
			}
		}
	}
	catch(EInOutError* E)
	{
		result = -E->ErrorCode;
	}
	catch(...)
	{
		result = -1;
	}
	return result;
}

/* TSynDfmSyn */

__fastcall TSynDfmSyn::TSynDfmSyn(TComponent* AOwner)
 : inherited(AOwner),
			fRange(rsUnKnown),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr)
{
	fCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterdfm__0;
	AddAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrKey, SYNS_FriendlyAttrKey);
	fKeyAttri->Style = Synhighlighterdfm__1;
	AddAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	AddAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	AddAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	AddAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterDFM;
}

void __fastcall TSynDfmSyn::AltProc()
{
	FTokenID = tkIdentifier;
	do
	{
		++Run;
	}
	while(!!IsIdentChar(fLine[Run]));
}

void __fastcall TSynDfmSyn::AsciiCharProc()
{
	FTokenID = tkString;
	do
	{
		++Run;
	}
	while(!!CharInSet(fLine[Run], Synhighlighterdfm__2));
}

void __fastcall TSynDfmSyn::BraceCloseProc()
{
	++Run;
	fRange = rsUnKnown;
	FTokenID = tkIdentifier;
}

void __fastcall TSynDfmSyn::BraceOpenProc()
{
	fRange = rsComment;
	CommentProc();
}

void __fastcall TSynDfmSyn::CommentProc()
{
	FTokenID = tkComment;
	do
	{
		++Run;
		if(fLine[Run] == L'}')
		{
			++Run;
			fRange = rsUnKnown;
			break;
		}
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynDfmSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynDfmSyn::EndProc()
{
	if(CharInSet(fLine[Run + 1], Synhighlighterdfm__3) && CharInSet(fLine[Run + 2], Synhighlighterdfm__4) && !IsIdentChar(fLine[Run + 3]))
	{
		FTokenID = tkKey;
		Run += 3;
	}
	else
	AltProc();
}

void __fastcall TSynDfmSyn::IntegerProc()
{

	auto IsIntegerChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	FTokenID = tkNumber;
	do
	{
		++Run;
	}
	while(!!IsIntegerChar());
}

void __fastcall TSynDfmSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynDfmSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynDfmSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'e':
			case L'E':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	FTokenID = tkNumber;
	do
	{
		++Run;
		if(fLine[Run] == L'.')
		{
			if(fLine[Run + 1] != L'.')
				++Run;
			break;
		}
	}
	while(!!IsNumberChar());
}

void __fastcall TSynDfmSyn::ObjectProc()
{
	if(CharInSet(fLine[Run + 1], Synhighlighterdfm__5) && CharInSet(fLine[Run + 2], Synhighlighterdfm__6) && CharInSet(fLine[Run + 3], Synhighlighterdfm__7) && CharInSet(fLine[Run + 4], Synhighlighterdfm__8) && CharInSet(fLine[Run + 5], Synhighlighterdfm__9) && !IsIdentChar(fLine[Run + 6]))
	{
		FTokenID = tkKey;
		Run += 6;
	}
	else
	AltProc();
}

void __fastcall TSynDfmSyn::InheritedProc()
{
	if(CharInSet(fLine[Run + 1], Synhighlighterdfm__10) && CharInSet(fLine[Run + 2], Synhighlighterdfm__11) && CharInSet(fLine[Run + 3], Synhighlighterdfm__12) && CharInSet(fLine[Run + 4], Synhighlighterdfm__13) && CharInSet(fLine[Run + 5], Synhighlighterdfm__14) && CharInSet(fLine[Run + 6], Synhighlighterdfm__15) && CharInSet(fLine[Run + 7], Synhighlighterdfm__16) && CharInSet(fLine[Run + 8], Synhighlighterdfm__17) && !IsIdentChar(fLine[Run + 9]))
	{
		FTokenID = tkKey;
		Run += 9;
	}
	else
	{
		if(CharInSet(fLine[Run + 1], Synhighlighterdfm__18) && CharInSet(fLine[Run + 2], Synhighlighterdfm__19) && CharInSet(fLine[Run + 3], Synhighlighterdfm__20) && CharInSet(fLine[Run + 4], Synhighlighterdfm__21) && CharInSet(fLine[Run + 5], Synhighlighterdfm__22) && !IsIdentChar(fLine[Run + 6]))
		{
			FTokenID = tkKey;
			Run += 6;
		}
		else
		AltProc();
	}
}

void __fastcall TSynDfmSyn::SpaceProc()
{
	FTokenID = tkSpace;
	do
	{
		++Run;
	}
	while(!((fLine[Run] > L'\x20') || IsLineEnd(Run)));
}

void __fastcall TSynDfmSyn::StringProc()
{
	FTokenID = tkString;
	do
	{
		++Run;
		if(fLine[Run] == L'\'')
		{
			++Run;
			if(fLine[Run] != L'\'')
				break;
		}
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynDfmSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynDfmSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynDfmSyn::Next()
{
	fTokenPos = Run;
	if(fRange == rsComment)
	{
		if(fLine[Run] == L'\x00')
			NullProc();
		else
			CommentProc();
	}
	else
	switch(fLine[Run])
	{
		case L'#':
		AsciiCharProc();
		break;
		case L'}':
		BraceCloseProc();
		break;
		case L'{':
		BraceOpenProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		case L'_':
		if(CharInSet(fLine[Run], Synhighlighterdfm__23))
			EndProc();
		else
		{
			if(CharInSet(fLine[Run], Synhighlighterdfm__24))
				ObjectProc();
			else
			{
				if(CharInSet(fLine[Run], Synhighlighterdfm__25))
					InheritedProc();
				else
					AltProc();
			}
		}
		break;
		case L'$':
		IntegerProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'\x00':
		NullProc();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		NumberProc();
		break;
		case L'(':
		case L')':
		case L'/':
		case L'=':
		case L'<':
		case L'>':
		case L'.':
		case L',':
		case L'[':
		case L']':
		SymbolProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'\x27':
		StringProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynDfmSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_COMMENT:
		result = fCommentAttri;
		break;
		case SYN_ATTR_IDENTIFIER:
		result = fIdentifierAttri;
		break;
		case SYN_ATTR_KEYWORD:
		result = fKeyAttri;
		break;
		case SYN_ATTR_STRING:
		result = fStringAttri;
		break;
		case SYN_ATTR_WHITESPACE:
		result = fSpaceAttri;
		break;
		case SYN_ATTR_SYMBOL:
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynDfmSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynDfmSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) fRange);
	return result;
}

TtkTokenKind __fastcall TSynDfmSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynDfmSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkNumber:
		result = fNumberAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkUnknown:
		result = fIdentifierAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynDfmSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynDfmSyn::ResetRange()
{
	fRange = rsUnKnown;
}

void __fastcall TSynDfmSyn::SetRange(void* Value)
{
	fRange = (TRangeState)(NativeInt)Value;
}

bool __fastcall TSynDfmSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterDFM;
	return result;
}

/*#static*/
String __fastcall TSynDfmSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangDfm;
	return result;
}

String __fastcall TSynDfmSyn::GetSampleSource()
{
	String result;
	result = L"{ Delphi/C++ Builder Form Definitions }\x0d\x0a"
	           L"object TestForm: TTestForm\x0d\x0a"
	           L"  Left = 273\x0d\x0a"
	           L"  Top = 103\x0d\x0a"
	           L"  Caption = 'SynEdit sample source'\x0d\x0a"
	           L"end";
	return result;
} /* GetSampleSource */

/*#static*/
String __fastcall TSynDfmSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangDfm;
	return result;
}

	static bool SynHighlighterDfm_Initialized = false;
	
	void SynHighlighterDfm_initialization()
	{
		if(SynHighlighterDfm_Initialized)
			return;
		
		SynHighlighterDfm_Initialized = true;
		
		RegisterPlaceableHighlighter(__classid(TSynDfmSyn));
	}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterDfm

