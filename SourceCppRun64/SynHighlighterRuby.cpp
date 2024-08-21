
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterRuby.h"
#include "SynEditMiscProcs.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditmiscprocs;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Types;
using namespace Vcl::Graphics;

namespace Synhighlighterruby
{


const int RubyKeysCount = 43;
const String RubyKeys[43/*# range 1..RubyKeysCount*/] = {L"alias", L"attr", L"begin", L"break", L"case", L"class", L"def", L"do", L"else", L"elsif", L"end", L"ensure", L"exit"
                    , L"extend", L"false", L"for", L"gets", L"if", L"in", L"include", L"load", L"loop", L"module", L"next", L"nil", L"not", L"print", L"private"
                    , L"public", L"puts", L"raise", L"redo", L"require", L"rescue", L"retry", L"return", L"self", L"then", L"true", L"unless", L"when"
                    , L"while", L"yield"};

bool __fastcall TSynRubySyn::IsKeyword(const String AKeyword)
{
	bool result = false;
	int First = 0;
	int Last = 0;
	int i = 0;
	int Compare = 0;
	String Token;
	First = 0;
	Last = fKeywords->Count - 1;
	result = false;
	Token = Sysutils::AnsiUpperCase(AKeyword);
	while(First <= Last)
	{
		i = (First + Last) >> 1;
		Compare = CompareStr(fKeywords->Strings[i], Token);
		if(Compare == 0)
		{
			result = true;
			break;
		}
		else
		{
			if(Compare < 0)
				First = i + 1;
			else
				Last = i - 1;
		}
	}
	return result;
} /* IsKeyWord */

bool __fastcall TSynRubySyn::IsSecondKeyWord(String AToken)
{
	bool result = false;
	int First = 0;
	int Last = 0;
	int i = 0;
	int Compare = 0;
	String Token;
	First = 0;
	Last = fSecondKeys->Count - 1;
	result = false;
	Token = Sysutils::AnsiUpperCase(AToken);
	while(First <= Last)
	{
		i = (First + Last) >> 1;
		Compare = CompareStr(fSecondKeys->Strings[i], Token);
		if(Compare == 0)
		{
			result = true;
			break;
		}
		else
		{
			if(Compare < 0)
				First = i + 1;
			else
				Last = i - 1;
		}
	}
	return result;
} /* IsSecondKeyWord */

__fastcall TSynRubySyn::TSynRubySyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkComment),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fKeyAttri(nullptr),
			fSecondKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fCommentAttri(nullptr),
			fSpaceAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeywords(nullptr),
			fSecondKeys(nullptr)
{
	int i = 0;
	FCaseSensitive = false;
	fKeywords = new TStringList();
	((TStringList*) fKeywords)->Sorted = true;
	((TStringList*) fKeywords)->Duplicates = System::Types::dupIgnore;
	fSecondKeys = new TStringList();
	((TStringList*) fSecondKeys)->Sorted = true;
	((TStringList*) fSecondKeys)->Duplicates = System::Types::dupIgnore;
	if(!(ComponentState.Contains(csDesigning)))
	{
		int stop = 0;
		for(stop = RubyKeysCount, i = 1; i <= stop; i++)
		{
			fKeywords->Add(RubyKeys[i - 1]);
		}
	}
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Foreground = (TColor) clMaroon;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Foreground = (TColor) clBlue;
	addAttribute(fKeyAttri);
	fSecondKeyAttri = new TSynHighlighterAttributes(SYNS_AttrSecondReservedWord, SYNS_FriendlyAttrSecondReservedWord);
	addAttribute(fSecondKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = (TColor) clGreen;
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = (TColor) clPurple;
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	fSymbolAttri->Foreground = (TColor) clBlue;
	addAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterRuby;
} /* Create */

__fastcall TSynRubySyn::~TSynRubySyn()
{
	delete fKeywords;
	delete fSecondKeys;
	//# inherited::Destroy();
} /* Destroy */

void __fastcall TSynRubySyn::BraceOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynRubySyn::PointCommaProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynRubySyn::CRProc()
{
	FTokenID = tkSpace;
	switch(fLine[Run + 1])
	{
		case L'\x0a':
		Run += 2;
		break;
		default:
		++Run;
		break;
	}
}

void __fastcall TSynRubySyn::IdentProc()
{
	while(IsIdentChar(fLine[Run]))
		++Run;
	if(IsKeyword(GetToken()))
	{
		FTokenID = tkKey;
		return;
	}
	else
	FTokenID = tkIdentifier;
	if(IsSecondKeyWord(GetToken()))
		FTokenID = tkSecondKey;
	else
		FTokenID = tkIdentifier;
}

void __fastcall TSynRubySyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynRubySyn::LowerProc()
{
	{
		++Run;
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynRubySyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynRubySyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'.':
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
	++Run;
	FTokenID = tkNumber;
	while(IsNumberChar())
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Run + 1] == L'.')
				goto label0;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label0:;
}

void __fastcall TSynRubySyn::RoundOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynRubySyn::SlashProc()
{
	switch(fLine[Run])
	{
		case L'/':
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
		case L'*':
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
		default:
		{
			FTokenID = tkComment;
			while(fLine[Run] != L'\x00')
			{
				switch(fLine[Run])
				{
					case L'\x0a':
					case L'\x0d':
					goto label1;
					default:
					  ;
					break;
				}
				++Run;
			}
			label1:;
		}
		break;
	}
}

void __fastcall TSynRubySyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynRubySyn::StringProc()
{
	WideChar QuoteChar = L'\0';
// Ha, ha, Strings in Ruby (could be anything)!!!!

//There are three more ways to construct string literals: %q, %Q, and ``here
//documents.''
//
//%q and %Q start delimited single- and double-quoted strings.
//
//%q/general single-quoted string/ » general single-quoted string
//%Q!general double-quoted string! » general double-quoted string
//%Q{Seconds/day: #{24*60*60}}     » Seconds/day: 86400
//
//The character following the ``q'' or ``Q'' is the delimiter. If it is an
//opening bracket, brace, parenthesis, or less-than sign, the string is read
//until the matching close symbol is found. Otherwise the string is read until
//the next occurrence of the same delimiter.
	FTokenID = tkString;
	QuoteChar = fLine[Run];      // either " or '
	if((fLine[Run + 1] == QuoteChar) && (fLine[Run + 2] == QuoteChar))
		Run += 2;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label2;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == QuoteChar));
	label2:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynRubySyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynRubySyn::Next()
{
	fTokenPos = Run;
	NextProcedure();
	inherited::Next();
}

void __fastcall TSynRubySyn::NextProcedure()
{
	switch(fLine[Run])
	{
		case L'<':
		LowerProc();
		break;
		case L'#':
		SlashProc();
		break;
		case L'{':
		BraceOpenProc();
		break;
		case L';':
		PointCommaProc();
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
		IdentProc();
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
		RoundOpenProc();
		break;
		case L'/':
		SlashProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'\x22':
		case L'\x27':
		StringProc();
		break;
		default:
		UnknownProc();
		break;
	}
}

TSynHighlighterAttributes* __fastcall TSynRubySyn::GetDefaultAttribute(int Index)
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
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynRubySyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynRubySyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynRubySyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynRubySyn::GetTokenAttribute()
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
		case tkSecondKey:
		result = fSecondKeyAttri;
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
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynRubySyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynRubySyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynRubySyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynRubySyn::SetSecondKeys(TStrings* const Value)
{
	int i = 0;
	if(Value != nullptr)
	{
		int stop = 0;
		Value->BeginUpdate();
		for(stop = Value->Count - 1, i = 0; i <= stop; i++)
		{
			Value->Strings[i] = Sysutils::AnsiUpperCase(Value->Strings[i]);
		}
		Value->EndUpdate();
	}
	fSecondKeys->Assign((TPersistent*) Value);
	DefHighlightChange(nullptr);
}

bool __fastcall TSynRubySyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterRuby;
	return result;
}

/*#static*/
String __fastcall TSynRubySyn::GetLanguageName()
{
	String result;
	result = SYNS_LangRuby;
	return result;
}

String __fastcall TSynRubySyn::GetSampleSource()
{
	String result;
	result = L"# Factorial"
	           L"\x0d\x0a"
	           L"def fact(n)"
	           L"\x0d\x0a"
	           L"  if n == 0"
	           L"\x0d\x0a"
	           L"    1"
	           L"\x0d\x0a"
	           L"  else"
	           L"\x0d\x0a"
	           L"    n * fact(n-1)"
	           L"\x0d\x0a"
	           L"  end"
	           L"\x0d\x0a"
	           L"end"
	           L"\x0d\x0a"
	           L"print fact(ARGV[0].to_i), \"\\n\"";
	return result;
}

/*#static*/
String __fastcall TSynRubySyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangRuby;
	return result;
}
static bool SynHighlighterRuby_Initialized = false;

void SynHighlighterRuby_initialization()
{
	if(SynHighlighterRuby_Initialized)
		return;
	
	SynHighlighterRuby_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynRubySyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterRuby

