
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterM3.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace Synhighlighterhashentries;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterm3
{
#define Synhighlighterm3__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterm3__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterm3__2 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterm3__3 (TSysCharSet() <<  \
										50 << 51 << 52 << 53 << 54 << 55 <<  \
										56 << 57)
#define Synhighlighterm3__4 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54)
#define Synhighlighterm3__5 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterm3__6 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterm3__7 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterm3__8 (TSysCharSet() << '+' << '-')
#define Synhighlighterm3__9 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterm3__10 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterm3__11 (TSysCharSet() << '\x22' << '\\')


const String Keywords = L"AS,AND,ANY,ARRAY,BEGIN,BITS,BRANDED,BY,CASE,CONST,DIV,DO,ELSE,ELSIF,END,"
	           L"EVAL,EXCEPT,EXCEPTION,EXIT,EXPORTS,FINALLY,FOR,FROM,GENERIC,IF,IMPORT,"
	           L"IN,INTERFACE,LOCK,LOOP,METHODS,MOD,MODULE,NOT,OBJECT,OF,OR,OVERRIDES,"
	           L"PROCEDURE,RAISE,RAISES,READONLY,RECORD,REF,REPEAT,RETURN,REVEAL,ROOT,"
	           L"SET,THEN,TO,TRY,TYPE,TYPECASE,UNSAFE,UNTIL,UNTRACED,VALUE,VAR,WHILE,WITH";
const String ReservedWords = L"ABS,ADDRESS,ADR,ADRSIZE,BITSIZE,BOOLEAN,BYTESIZE,CARDINAL,CEILING,CHAR,"
	           L"DEC,DISPOSE,FALSE,FIRST,FLOAT,FLOOR,INC,INTEGER,ISTYPE,LAST,LONGFLOAT,"
	           L"LONGREAL,LOOPHOLE,MAX,MIN,MUTEX,NARROW,NEW,NIL,NULL,NUMBER,ORD,REAL,"
	           L"REFANY,ROUND,SUBARRAY,TEXT,TRUE,TRUNC,TYPECODE,VAL";

void __fastcall TSynM3Syn::DoAddKeyword(String AKeyword, int AKind)
{
	int HashValue = 0;
	HashValue = HashKey(ustr2pwchar(AKeyword));
	fKeywords->Items[HashValue] = new TSynHashEntry(AKeyword, AKind);
}

int __fastcall TSynM3Syn::HashKey(PWideChar Str)
{
	int result = 0;

	auto GetOrd = [&]() -> int 
	{
		int result = 0;
		switch((*Str))
		{
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			result = 1 + int((*Str)) - int(L'a');
			break;
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			result = 1 + int((*Str)) - int(L'A');
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			result = 28 + int((*Str)) - int(L'0');
			break;
			case L'_':
			result = 27;
			break;
			default:
			result = 0;
			break;
		}
		return result;
	};
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (7 * result + GetOrd()) & 0xFFFFFF;
		++Str;
	}
	result = result & 0xFF; // 255
	fStringLen = Str - fToIdent;
	return result;
}

TtkTokenKind __fastcall TSynM3Syn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkComment;
	TSynHashEntry* Entry = nullptr;
	fToIdent = MayBe;
	Entry = fKeywords->Items[HashKey(MayBe)];
	while(ASSIGNED(Entry))
	{
		if(Entry->KeywordLen > fStringLen)
			break;
		else
		{
			if(Entry->KeywordLen == fStringLen)
			{
				if(IsCurrentToken(Entry->Keyword))
				{
					result = ((TtkTokenKind) Entry->Kind);
					return result;
				}
			}
		}
		Entry = Entry->Next;
	}
	result = tkIdentifier;
	return result;
}

__fastcall TSynM3Syn::TSynM3Syn(TComponent* AOwner)
 : inherited(AOwner),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fPragmaAttri(nullptr),
			fReservedAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fSyntaxErrorAttri(nullptr),
			fKeywords(nullptr)
{
	fCaseSensitive = true;
	fKeywords = new TSynHashEntryList();
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterm3__0;
	AddAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrKey, SYNS_FriendlyAttrKey);
	fKeyAttri->Style = Synhighlighterm3__1;
	AddAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	AddAttribute(fNumberAttri);
	fPragmaAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	fPragmaAttri->Style = Synhighlighterm3__2;
	AddAttribute(fPragmaAttri);
	fReservedAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	AddAttribute(fReservedAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	AddAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	AddAttribute(fSymbolAttri);
	fSyntaxErrorAttri = new TSynHighlighterAttributes(SYNS_AttrSyntaxError, SYNS_FriendlyAttrSyntaxError);
	fSyntaxErrorAttri->Foreground = (TColor) clRed;
	AddAttribute(fSyntaxErrorAttri);
	SetAttributesOnChange(DefHighlightChange);
	EnumerateKeywords(int(tkKey), Keywords, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkReserved), ReservedWords, IsIdentChar, DoAddKeyword);
	fDefaultFilter = SYNS_FilterModula3;
}

__fastcall TSynM3Syn::~TSynM3Syn()
{
	delete fKeywords;
	//# inherited::Destroy();
}

void __fastcall TSynM3Syn::SymAsciiCharProc()
{
	FTokenID = tkString;
	++Run;
	while(!IsLineEnd(Run))
	{
		switch(fLine[Run])
		{
			case L'\\':
			if(fLine[Run + 1] == L'\x27')
				++Run;
			break;
			case L'\x27':
			{
				++Run;
				if(fLine[Run] != L'\x27')
					goto label0;
			}
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label0:;
}

void __fastcall TSynM3Syn::SymCommentHelpProc()
{
	FTokenID = tkComment;
	SymNestedHelperProc(L'(', L')');
}

void __fastcall TSynM3Syn::SymCRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynM3Syn::SymIdentProc()
{
	FTokenID = IdentKind(fLine + Run);
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynM3Syn::SymLFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynM3Syn::SymNestedHelperProc(WideChar AOpenChar, WideChar ACloseChar)
{
	switch(fLine[Run])
	{
		case L'\x00':
		SymNullProc();
		break;
		case L'\x0a':
		SymLFProc();
		break;
		case L'\x0d':
		SymCRProc();
		break;
		default:
		do
		{
			if(fLine[Run] == AOpenChar)
			{
				++Run;
				if(fLine[Run] == L'*')
				{
					++Run;
					++fRange.Level;
				}
			}
			else
			{
				if(fLine[Run] == L'*')
				{
					++Run;
					if(fLine[Run] == ACloseChar)
					{
						++Run;
						if(fRange.Level > 0)
							--fRange.Level;
						if(fRange.Level == 0)
						{
							fRange.TokenRange = (WORD) int(trNone);
							break;
						}
					}
				}
				else
				++Run;
			}
		}
		while(!IsLineEnd(Run));
		break;
	}
}

void __fastcall TSynM3Syn::SymNullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynM3Syn::SymNumberProc()
{
	bool BasedNumber = false;
	int MaxDigit = 0;

	auto IsValidDigit = [&](WideChar AChar) -> bool 
	{
		bool result = false;
		int Digit = 0;
		switch(AChar)
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			Digit = int(AChar) - int(L'0');
			break;
			case 97: case 98: case 99: case 100: case 101: case 102:
			Digit = int(AChar) - int(L'a');
			break;
			case 65: case 66: case 67: case 68: case 69: case 70:
			Digit = int(AChar) - int(L'A');
			break;
			default:
			Digit = -1;
			break;
		}
		result = (Digit >= 0) && (Digit <= MaxDigit);
		return result;
	};

	auto IsExponentChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case L'd':
			case L'D':
			case L'e':
			case L'E':
			case L'x':
			case L'X':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	FTokenID = tkNumber;
	BasedNumber = false;
	MaxDigit = 9;
  // skip leading zeros, but they can be numbers too
	while(fLine[Run] == L'0')
		++Run;
	if(!IsIdentChar(fLine[Run]))
		return;
  // check for numbers with a base prefix
	if(CharInSet(fLine[Run], Synhighlighterm3__3) && (fLine[Run + 1] == L'_'))
	{
		BasedNumber = true;
		MaxDigit = int(fLine[Run]) - int(L'0') - 1;
		Run += 2;
	}
	else
	{
		if((fLine[Run] == L'1') && CharInSet(fLine[Run + 1], Synhighlighterm3__4) && (fLine[Run + 2] == L'_'))
		{
			BasedNumber = true;
			MaxDigit = 10 + int(fLine[Run + 1]) - int(L'0') - 1;
			Run += 3;
		}
	}
	if(BasedNumber)
    // advance over all valid digits, but at least one has to be there
	{
		if(IsValidDigit(fLine[Run]))
		{
			do
			{
				++Run;
			}
			while(!!IsValidDigit(fLine[Run]));
		}
		else
		FTokenID = tkSyntaxError;
	}
	else

    // "normal" numbers
	{
		do
		{
			++Run;
		}
		while(!!CharInSet(fLine[Run], Synhighlighterm3__5));
    // can include a decimal point and an exponent
		if(fLine[Run] == L'.')
		{
			++Run;
			if(CharInSet(fLine[Run], Synhighlighterm3__6))
			{
				do
				{
					++Run;
				}
				while(!!CharInSet(fLine[Run], Synhighlighterm3__7));
			}
			else
			FTokenID = tkSyntaxError; // must be a number after the '.'
		}
    // can include an exponent
		if(IsExponentChar())
		{
			++Run;
			if(CharInSet(fLine[Run], Synhighlighterm3__8))
				++Run;
			if(CharInSet(fLine[Run], Synhighlighterm3__9))
			{
				do
				{
					++Run;
				}
				while(!!CharInSet(fLine[Run], Synhighlighterm3__10));
			}
			else
 // exponent must include a number
			FTokenID = tkSyntaxError;
		}
	}
  // it's a syntax error if there are any Identifier chars left
	if(IsIdentChar(fLine[Run]))
	{
		FTokenID = tkSyntaxError;
		do
		{
			++Run;
		}
		while(!!IsIdentChar(fLine[Run]));
	}
}

void __fastcall TSynM3Syn::SymPragmaProc()
{
	++Run;
	if(fLine[Run] == L'*')
	{
		++Run;
		fRange.TokenRange = (WORD) int(trPragma);
		++fRange.Level;
		if(IsLineEnd(Run))
			FTokenID = tkPragma;
		else
			SymPragmaHelpProc();
	}
	else
	FTokenID = tkSymbol;
}

void __fastcall TSynM3Syn::SymPragmaHelpProc()
{
	FTokenID = tkPragma;
	SymNestedHelperProc(L'<', L'>');
}

void __fastcall TSynM3Syn::SymRoundOpenProc()
{
	++Run;
	if(fLine[Run] == L'*')
	{
		++Run;
		fRange.TokenRange = (WORD) int(trComment);
		++fRange.Level;
		if(IsLineEnd(Run))
			FTokenID = tkComment;
		else
			SymCommentHelpProc();
	}
	else
	{
		FTokenID = tkSymbol;
		if(fLine[Run] == L'.')
			++Run;
	}
}

void __fastcall TSynM3Syn::SymSpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynM3Syn::SymStringProc()
{
	FTokenID = tkString;
	++Run;
	while(!IsLineEnd(Run))
	{
		switch(fLine[Run])
		{
			case L'\x22':
			{
				++Run;
				goto label1;
			}
			case L'\\':
			if(CharInSet(fLine[Run + 1], Synhighlighterm3__11))
				++Run;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label1:;
}

void __fastcall TSynM3Syn::SymSymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynM3Syn::SymUnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynM3Syn::Next()
{
	fTokenPos = Run;
	switch(((TTokenRange) fRange.TokenRange))
	{
		case trComment:
		SymCommentHelpProc();
		break;
		case trPragma:
		SymPragmaHelpProc();
		break;
		default:
		switch(fLine[Run])
		{
			case L'\x27':
			SymAsciiCharProc();
			break;
			case L'\x0d':
			SymCRProc();
			break;
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			case L'_':
			SymIdentProc();
			break;
			case L'\x0a':
			SymLFProc();
			break;
			case L'\x00':
			SymNullProc();
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			SymNumberProc();
			break;
			case L'(':
			SymRoundOpenProc();
			break;
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			case L'\x0b':
			case L'\x0c':
			case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
			 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
			SymSpaceProc();
			break;
			case L'{':
			case L'}':
			case L'|':
			case L'!':
			case 35: case 36: case 37: case 38:
			case 42: case 43: case 44: case 45: case 46: case 47:
			case L'\x3a':
			case L'\x3b':
			case 61: case 62: case 63: case 64:
			case 91: case 92: case 93: case 94:
			case L')':
			SymSymbolProc();
			break;
			case L'<':
			SymPragmaProc();
			break;
			case L'\x22':
			SymStringProc();
			break;
			default:
			SymUnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynM3Syn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynM3Syn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

bool __fastcall TSynM3Syn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterModula3;
	return result;
}

/*#static*/
String __fastcall TSynM3Syn::GetLanguageName()
{
	String result;
	result = SYNS_LangModula3;
	return result;
}

void* __fastcall TSynM3Syn::GetRange()
{
	void* result = nullptr;
	result = fRange.p;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynM3Syn::GetTokenAttribute()
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
		case tkPragma:
		result = fPragmaAttri;
		break;
		case tkReserved:
		result = fReservedAttri;
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
		case tkSyntaxError:
		result = fSyntaxErrorAttri;
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

TtkTokenKind __fastcall TSynM3Syn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

int __fastcall TSynM3Syn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynM3Syn::ResetRange()
{
	fRange.p = nullptr;
}

void __fastcall TSynM3Syn::SetRange(void* Value)
{
	fRange.p = Value;
}

/*#static*/
String __fastcall TSynM3Syn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangModula3;
	return result;
}

	static bool SynHighlighterM3_Initialized = false;
	
	void SynHighlighterM3_initialization()
	{
		if(SynHighlighterM3_Initialized)
			return;
		
		SynHighlighterM3_Initialized = true;
		
		RegisterPlaceableHighlighter(__classid(TSynM3Syn));
	}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterM3

