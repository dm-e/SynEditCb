
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterJSON.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterjson
{
#define Synhighlighterjson__0 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterjson__1 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterjson__2 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterjson__3 (TSysCharSet() << 'e' << 'E')
#define Synhighlighterjson__4 (TSysCharSet() << '+' << '-')
#define Synhighlighterjson__5 (TSysCharSet() <<  \
          48 << 49 << 50 << 51 << 52 << 53 <<  \
          54 << 55 << 56 << 57 <<  \
          65 << 66 << 67 << 68 << 69 << 70 <<  \
          97 << 98 << 99 << 100 << 101 << 102)
#define Synhighlighterjson__6 (TSysCharSet() << '\x20' << '\"')
#define Synhighlighterjson__7 (System::Set<TRangeState, TRangeState::rsUnKnown, TRangeState::rsArrayValue>() << rsObjectValue << rsArrayValue)



/* TSynJSONSyn */

__fastcall TSynJSONSyn::TSynJSONSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkString),
			FReservedAttri(nullptr),
			fAttributeAttri(nullptr),
			fValueAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fSymbolAttri(nullptr)
{
	FCaseSensitive = true;

  // Attribute
	fAttributeAttri = new TSynHighlighterAttributes(SYNS_AttrAttribute, SYNS_FriendlyAttrAttribute);
	fAttributeAttri->Foreground = (TColor) clNavy;
	addAttribute(fAttributeAttri);

  // reserved words ("true", "false", "null")
	FReservedAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	FReservedAttri->Style = Synhighlighterjson__0;
	addAttribute(FReservedAttri);

  // numbers
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = (TColor) clRed;
	addAttribute(fNumberAttri);

  // spaces
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);

  // symbols
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	fSymbolAttri->Foreground = (TColor) clGreen;
	addAttribute(fSymbolAttri);

  // Value
	fValueAttri = new TSynHighlighterAttributes(SYNS_AttrValue, SYNS_FriendlyAttrValue);
	fValueAttri->Foreground = (TColor) clBlue;
	addAttribute(fValueAttri);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterJSON;
}

void __fastcall TSynJSONSyn::CloseArrayProc()
{
	SymbolProc();
	FRange = rsUnKnown;
}

void __fastcall TSynJSONSyn::CloseObjectProc()
{
	SymbolProc();
	FRange = rsUnKnown;
}

void __fastcall TSynJSONSyn::ColonProc()
{
	SymbolProc();
	FRange = rsObjectValue;
}

void __fastcall TSynJSONSyn::CommaProc()
{
	SymbolProc();
	if(FRange == rsObjectValue)
		FRange = rsAttribute;
}

void __fastcall TSynJSONSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynJSONSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynJSONSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynJSONSyn::NumberProc()
{

	auto ExpectDigit = [&]() -> bool 
	{
		bool result = false;
		result = CharInSet(fLine[Run], Synhighlighterjson__1);
		while(CharInSet(fLine[Run], Synhighlighterjson__2))
			++Run;
		return result;
	};
	FTokenID = tkNumber;
	if(fLine[Run] == L'-')
		++Run;

  // ensure that a zero is followed by a dot
	if(fLine[Run] == L'0')
	{
		if(fLine[Run + 1] != L'.')
		{
			FTokenID = tkUnknown;
			while((fLine[Run] != L'\x20') && !IsLineEnd(Run))
				++Run;
			return;
		}

  // at least any digit must appear here
	}
	if(!ExpectDigit())
	{
		FTokenID = tkUnknown;
		while((fLine[Run] != L'\x20') && !IsLineEnd(Run))
			++Run;
		return;
	}

  // check for dot
	if(fLine[Run] == L'.')
    // advance
	{
		++Run;

    // at least any digit must appear after a dot!
		if(!ExpectDigit())
		{
			FTokenID = tkUnknown;
			while((fLine[Run] != L'\x20') && !IsLineEnd(Run))
				++Run;
			return;
		}
	}

  // check for an exponent
	if(CharInSet(fLine[Run], Synhighlighterjson__3))
	{
		++Run;

    // allow +/- here
		if(CharInSet(fLine[Run], Synhighlighterjson__4))
			++Run;

    // at least any digit must appear here
		if(!ExpectDigit())
		{
			FTokenID = tkUnknown;
			while((fLine[Run] != L'\x20') && !IsLineEnd(Run))
				++Run;
			return;
		}
	}
}

void __fastcall TSynJSONSyn::OpenArrayProc()
{
	SymbolProc();
	FRange = rsArrayValue;
}

void __fastcall TSynJSONSyn::OpenObjectProc()
{
	SymbolProc();
	FRange = rsAttribute;
}

void __fastcall TSynJSONSyn::ReservedWordProc()
{

	auto SkipToken = [&]() -> void 
	{
		while((fLine[Run] != L'\x20') && (fLine[Run] != L',') && !IsLineEnd(Run))
			++Run;
	};
	FTokenID = tkUnknown;
	switch(fLine[Run])
	{
		case L'n':
		if((fLine[Run + 1] == L'u') && (fLine[Run + 2] == L'l') && (fLine[Run + 3] == L'l'))
		{
			FTokenID = tkReserved;
			Run += 4;
		}
		else
		SkipToken();
		break;
		case L't':
		if((fLine[Run + 1] == L'r') && (fLine[Run + 2] == L'u') && (fLine[Run + 3] == L'e'))
		{
			FTokenID = tkReserved;
			Run += 4;
		}
		else
		SkipToken();
		break;
		case L'f':
		if((fLine[Run + 1] == L'a') && (fLine[Run + 2] == L'l') && (fLine[Run + 3] == L's') && (fLine[Run + 4] == L'e'))
		{
			FTokenID = tkReserved;
			Run += 5;
		}
		else
		SkipToken();
		break;
		default:
		SkipToken();
		break;
	}
}

void __fastcall TSynJSONSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynJSONSyn::StringProc()
{

	auto IsHex = [&](Char digit) -> bool 
	{
		bool result = false;
		result = CharInSet(digit, Synhighlighterjson__5);
		return result;
	};
	FTokenID = tkString;
	do
	{
		++Run;
		switch(fLine[Run])
		{
			case L'\"':
			{
				++Run;
				goto label0;
			}
			case L'\\':
			switch(fLine[Run + 1])
			{
				case L'\"':
				case L'/':
				case L'\\':
				case L'b':
				case L'f':
				case L'n':
				case L'r':
				case L't':
				++Run;
				break;
				case L'u':
				{
					++Run;
					if(!(IsHex(fLine[Run + 1]) && IsHex(fLine[Run + 2]) && IsHex(fLine[Run + 3]) && IsHex(fLine[Run + 4])))
                // a 4 hex digit is expected
					{
						FTokenID = tkUnknown;
						while(!CharInSet(fLine[Run], Synhighlighterjson__6) && !IsLineEnd(Run))
							++Run;
						return;
					}
					Run += 4;
				}
				break;
				default:
				  ;
				break;
			}
			break;
			default:
			  ;
			break;
		}
	}
	while(!IsLineEnd(Run));
	label0:;
}

void __fastcall TSynJSONSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynJSONSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynJSONSyn::Next()
{
	fTokenPos = Run;
	switch(fLine[Run])
	{
		case L'\x00':
		NullProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		case L'-':
		NumberProc();
		break;
		case L't':
		case L'f':
		case L'n':
		ReservedWordProc();
		break;
		case L'\"':
		StringProc();
		break;
		case L':':
		ColonProc();
		break;
		case L'{':
		OpenObjectProc();
		break;
		case L'[':
		OpenArrayProc();
		break;
		case L'}':
		CloseObjectProc();
		break;
		case L']':
		CloseArrayProc();
		break;
		case L',':
		CommaProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynJSONSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_KEYWORD:
		result = FReservedAttri;
		break;
		case SYN_ATTR_IDENTIFIER:
		result = fAttributeAttri;
		break;
		case SYN_ATTR_WHITESPACE:
		result = fSpaceAttri;
		break;
		case SYN_ATTR_SYMBOL:
		result = fSymbolAttri;
		break;
		case SYN_ATTR_STRING:
		result = fValueAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynJSONSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynJSONSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynJSONSyn::GetTokenID()
{
	TtkTokenKind result = tkString;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynJSONSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkString:
		if(Synhighlighterjson__7.Contains(FRange))
			result = fValueAttri;
		else
			result = fAttributeAttri;
		break;
		case tkReserved:
		result = FReservedAttri;
		break;
		case tkNumber:
		result = fNumberAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkUnknown:
		result = fAttributeAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynJSONSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynJSONSyn::ResetRange()
{
	FRange = rsUnKnown;
}

//++ CodeFolding

void __fastcall TSynJSONSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	String CurLine;
	__int64 Line = 0;

	auto LineHasChar = [&](int Line, Char Character, int StartCol) -> bool 
	{
		bool result = false;
		int i = 0;
		int stop = 0;
		result = false;
		for(stop = CurLine.Length(), i = StartCol; i <= stop; i++)
		{
			if(CurLine[i] == Character)
        // Char must have proper highlighting (ignore stuff inside comments...)
			{
				if(GetHighlighterAttriAtRowCol(LinesToScan, Line, i) != CommentAttribute)
				{
					result = true;
					break;
				}
			}
		}
		return result;
	}; // faster than Pos!

	auto FindBraces = [&](int Line, Char OpenBrace, Char CloseBrace, int FoldType) -> bool 
	{
		bool result = false;
		int Col = 0;
		int stop = 0;
		result = false;
		for(stop = CurLine.Length(), Col = 1; Col <= stop; Col++)
		{
      // We've found a starting character
			if(CurLine[Col] == OpenBrace)
        // Char must have proper highlighting (ignore stuff inside comments...)
			{
				if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Col) != CommentAttribute)
          // And ignore lines with both opening and closing chars in them
				{
					if(!LineHasChar(Line, CloseBrace, Col + 1))
					{
						FoldRanges->StartFoldRange(Line + 1, FoldType);
						result = true;
					}
          // Skip until a newline
					break;
				}
			}
			else
			{
				if(CurLine[Col] == CloseBrace)
				{
					if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Col) != CommentAttribute)
          // And ignore lines with both opening and closing chars in them
					{
						if(!LineHasChar(Line, OpenBrace, Col + 1))
						{
							FoldRanges->StopFoldRange(Line + 1, FoldType);
							result = true;
						}
          // Skip until a newline
						break;
					}
				}
			}
		} // for Col
		return result;
	};
	__int64 stop = 0;
	for(stop = ToLine, Line = FromLine; Line <= stop; Line++)
	{
		CurLine = LinesToScan->Strings[Line];

    // Skip empty lines
		if(CurLine == L"")
		{
			FoldRanges->NoFoldInfo((int) (Line + 1));
			continue;
		}

    // Find an braces on this line  (Fold Type 1)
		if(!FindBraces((int) Line, L'{', L'}', 1))
		{
			if(!FindBraces((int) Line, L'[', L']', 2))
				FoldRanges->NoFoldInfo((int) (Line + 1));
		}
	} // while Line
}
//-- CodeFolding

void __fastcall TSynJSONSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

bool __fastcall TSynJSONSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterJSON;
	return result;
}

/*#static*/
String __fastcall TSynJSONSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangJSON;
	return result;
}

String __fastcall TSynJSONSyn::GetSampleSource()
{
	String result;
	result = L"{\x0d\x0a"
	           L"  \"firstName\": \"John\",\x0d\x0a"
	           L"  \"lastName\": \"Smith\",\x0d\x0a"
	           L"  \"isAlive\": true,\x0d\x0a"
	           L"  \"age\": 25,\x0d\x0a"
	           L"  \"height_cm\": 167.6,\x0d\x0a"
	           L"  \"address\": {\x0d\x0a"
	           L"    \"streetAddress\": \"21 2nd Street\",\x0d\x0a"
	           L"    \"city\": \"New York\",\x0d\x0a"
	           L"    \"state\": \"NY\",\x0d\x0a"
	           L"    \"postalCode\": \"10021-3100\"\x0d\x0a"
	           L"  },\x0d\x0a"
	           L"  \"phoneNumbers\": [\x0d\x0a"
	           L"    {\x0d\x0a"
	           L"      \"type\": \"home\",\x0d\x0a"
	           L"      \"number\": \"212 555-1234\"\x0d\x0a"
	           L"    },\x0d\x0a"
	           L"    {\x0d\x0a"
	           L"      \"type\": \"office\",\x0d\x0a"
	           L"      \"number\": \"646 555-4567\"\x0d\x0a"
	           L"    }\x0d\x0a"
	           L"  ],\x0d\x0a"
	           L"  \"face\": \"\\uD83D\\uDE02\",\x0d\x0a"
	           L"  \"children\": [],\x0d\x0a"
	           L"  \"spouse\": null\x0d\x0a"
	           L"}";
	return result;
}

/*#static*/
String __fastcall TSynJSONSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangJSON;
	return result;
}
static bool SynHighlighterJSON_Initialized = false;

void SynHighlighterJSON_initialization()
{
	if(SynHighlighterJSON_Initialized)
		return;
	
	SynHighlighterJSON_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynJSONSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterJSON

