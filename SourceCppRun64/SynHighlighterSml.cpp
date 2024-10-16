
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterSml.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlightersml
{
#define Synhighlightersml__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlightersml__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightersml__2 (TFontStyles() << TFontStyle::fsBold)


const String KeyWords[41/*# range 0..40*/] = {L"abstype", L"and", L"andalso", L"as", L"case", L"datatype", L"do", L"else", L"end", L"eqtype", L"exception", L"fn"
                    , L"fun", L"functor", L"handle", L"if", L"in", L"include", L"infix", L"infixr", L"let", L"local", L"nonfix", L"of", L"op", L"open", L"orelse"
                    , L"raise", L"rec", L"sharing", L"sig", L"signature", L"struct", L"structure", L"then", L"type", L"val", L"where", L"while", L"with"
                    , L"withtype"};
const int KeyIndices[71/*# range 0..70*/] = {28, -1, -1, -1, 23, 4, 19, -1, -1, 32, 8, 6, -1, 33, 0, -1, 14, -1, 2, -1, -1, 29, 35, -1, -1, -1, -1, 13, -1, -1, 9, -1, 11, 30, 1, -1, 25, 36, -1, -1, -1, 40, -1, 7, -1, 16
                    , 26, 37, -1, 15, 21, -1, 18, 12, 5, -1, -1, 10, 22, 27, 34, 17, -1, 20, -1, 39, -1, 3, 38, 31, 24};

/*$Q-*/

unsigned int __fastcall TSynSMLSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 157 + int((*Str)) * 35);
		++Str;
	}
	result = (unsigned int) (result % 71);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynSMLSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkCharacter;
	unsigned int Key = 0;
	fToIdent = MayBe;
	Key = HashKey(MayBe);
	if(Key <= 70 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[Key](KeyIndices[Key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynSMLSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 70 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	for(stop = 70 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

bool __fastcall TSynSMLSyn::IsValidMLCharacter()
{
	bool result = false;

	auto IsABNRTChar = [&](int Run) -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case L'a':
			case L'b':
			case L'n':
			case L'r':
			case L't':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	String ASCIIStr;
	int ASCIICode = 0;
	int Error = 0;
	result = false;
	if(fLine[Run] == L'\"')
	{
		if((Run > 2) && (fLine[Run - 1] != L'\\') && (fLine[Run - 2] == L'\"'))
			result = true;
		else
		{
			if((Run > 3) && (fLine[Run - 1] == L'\\') && (fLine[Run - 2] == L'\\') && (fLine[Run - 3] == L'\"'))
				result = true;
			else
			{
				if((Run > 3) && IsABNRTChar(Run - 1) && (fLine[Run - 2] == L'\\') && (fLine[Run - 3] == L'\"'))
					result = true;
				else
				{
					if((Run > 5) && (fLine[Run - 4] == L'\\') && (fLine[Run - 5] == L'\"'))
					{
						ASCIIStr = String(fLine).SubString(Run - 2, 3);
						Val(ASCIIStr, ASCIICode, Error);
						if((Error == 0) && (ASCIICode >= 0) && (ASCIICode <= 255))
							result = true;
					}
				}
			}
		}
	}
	return result;
}

TtkTokenKind __fastcall TSynSMLSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkCharacter;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSMLSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkCharacter;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynSMLSyn::TSynSMLSyn(TComponent* AOwner)
 : inherited(AOwner),
			fBasis(false),
			fRange(rsUnknown),
			FTokenID(tkCharacter),
			fCharacterAttri(nullptr),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fOperatorAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fSyntaxErrorAttri(nullptr)
{
	fCaseSensitive = true;
	fCharacterAttri = new TSynHighlighterAttributes(SYNS_AttrCharacter, SYNS_FriendlyAttrCharacter);
	fCharacterAttri->Foreground = (TColor) clBlue;
	AddAttribute(fCharacterAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlightersml__0;
	fCommentAttri->Foreground = (TColor) clNavy;
	AddAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlightersml__1;
	fKeyAttri->Foreground = (TColor) clGreen;
	AddAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = (TColor) clRed;
	AddAttribute(fNumberAttri);
	fOperatorAttri = new TSynHighlighterAttributes(SYNS_AttrOperator, SYNS_FriendlyAttrOperator);
	fOperatorAttri->Foreground = (TColor) clMaroon;
	AddAttribute(fOperatorAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = (TColor) clBlue;
	AddAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	AddAttribute(fSymbolAttri);
	fSyntaxErrorAttri = new TSynHighlighterAttributes(SYNS_AttrSyntaxError, SYNS_FriendlyAttrSyntaxError);
	fSyntaxErrorAttri->Foreground = (TColor) clRed;
	fSyntaxErrorAttri->Style = Synhighlightersml__2;
	AddAttribute(fSyntaxErrorAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterSML;
	Basis = true;
}

void __fastcall TSynSMLSyn::CRProc()
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

void __fastcall TSynSMLSyn::ColonProc()
{
	++Run;
	if(Basis && (fLine[Run] == L':'))
	{
		FTokenID = tkOperator;
		++Run;
	}
	else
	FTokenID = tkSymbol;
}

void __fastcall TSynSMLSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynSMLSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynSMLSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynSMLSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'.':
			case L'u':
			case L'U':
			case L'l':
			case L'L':
			case L'x':
			case L'X':
			case L'e':
			case L'E':
			case L'f':
			case L'F':
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

void __fastcall TSynSMLSyn::OperatorProc()
{
	++Run;
	FTokenID = tkOperator;
}

void __fastcall TSynSMLSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynSMLSyn::StringProc()
{
	FTokenID = tkString;
	do
	{
		if(fLine[Run] == L'\\')
		{
			switch(fLine[Run + 1])
			{
				case L'\"':
				case L'\\':
				++Run;
				break;
				case L'\x00':
				{
					++Run;
					fRange = rsMultilineString;
					return;
				}
				default:
				  ;
				break;
			}
		}
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\"')));
	if(fLine[Run] == L'\"')
		++Run;
}

void __fastcall TSynSMLSyn::StringEndProc()
{
	FTokenID = tkString;
	switch(fLine[Run])
	{
		case L'\x00':
		{
			NullProc();
			return;
		}
		case L'\x0a':
		{
			LFProc();
			return;
		}
		case L'\x0d':
		{
			CRProc();
			return;
		}
		default:
		  ;
		break;
	}
	fRange = rsUnknown;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label1;
			case L'\\':
			{
				switch(fLine[Run + 1])
				{
					case L'\"':
					case L'\\':
					++Run;
					break;
					case L'\x00':
					{
						++Run;
						fRange = rsMultilineString;
						return;
					}
					default:
					  ;
					break;
				}
			}
			break;
			case L'\"':
			goto label2;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\"')));
	label1:;
	label2:;
	if(fLine[Run] == L'\"')
		++Run;
}

void __fastcall TSynSMLSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynSMLSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynSMLSyn::BasisOpProc()
{
	++Run;
	if(Basis)
		FTokenID = tkOperator;
	else
		FTokenID = tkIdentifier;
}

void __fastcall TSynSMLSyn::PoundProc()
{
	++Run;
	if(fLine[Run] == L'\"')
		CharacterProc();
	else
		FTokenID = tkIdentifier;
}

void __fastcall TSynSMLSyn::CharacterProc()
{
	switch(fLine[Run])
	{
		case L'\x00':
		NullProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		default:
		{
			do
			{
				++Run;
			}
			while(!(IsLineEnd(Run) || (fLine[Run] == L'\"')));
			if(IsValidMLCharacter())
				FTokenID = tkCharacter;
			else
			{
				if(fLine[Run] == L'\"')
					++Run;
				FTokenID = tkSyntaxError;
			}
		}
		break;
	}
}

void __fastcall TSynSMLSyn::RoundBracketOpenProc()
{
	++Run;
	if(fLine[Run] == L'*')
	{
		fRange = rsComment;
		CommentProc();
		FTokenID = tkComment;
	}
	else
	FTokenID = tkIdentifier;
}

void __fastcall TSynSMLSyn::CommentProc()
{
	switch(fLine[Run])
	{
		case L'\x00':
		NullProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		default:
		{
			FTokenID = tkComment;
			do
			{
				if((fLine[Run] == L'*') && (fLine[Run + 1] == L')'))
				{
					Run += 2;
					fRange = rsUnknown;
					break;
				}
				if(!IsLineEnd(Run))
					++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
	}
}

void __fastcall TSynSMLSyn::Next()
{
	fTokenPos = Run;
	switch(fRange)
	{
		case rsComment:
		CommentProc();
		break;
		case rsMultilineString:
		StringEndProc();
		break;
		default:
		{
			fRange = rsUnknown;
			switch(fLine[Run])
			{
				case L'\x0d':
				CRProc();
				break;
				case L'#':
				PoundProc();
				break;
				case L':':
				ColonProc();
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
				case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
				case L'\x0b':
				case L'\x0c':
				case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
				 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
				SpaceProc();
				break;
				case L'\"':
				StringProc();
				break;
				case L'@':
				case L'^':
				BasisOpProc();
				break;
				case L'(':
				RoundBracketOpenProc();
				break;
				case L'+':
				case L'-':
				case L'~':
				case L'*':
				case L'/':
				case L'=':
				case L'<':
				case L'>':
				OperatorProc();
				break;
				case L',':
				case L'.':
				case L';':
				SymbolProc();
				break;
				default:
				UnknownProc();
				break;
			}
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynSMLSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynSMLSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynSMLSyn::GetTokenID()
{
	TtkTokenKind result = tkCharacter;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynSMLSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkCharacter:
		result = fCharacterAttri;
		break;
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
		case tkOperator:
		result = fOperatorAttri;
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

int __fastcall TSynSMLSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

bool __fastcall TSynSMLSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterSML;
	return result;
}

bool __fastcall TSynSMLSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'\x27':
		case L'_':
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

/*#static*/
String __fastcall TSynSMLSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangSML;
	return result;
}

String __fastcall TSynSMLSyn::GetSampleSource()
{
	String result;
	result = L"(* Syntax highlighting *)\x0d\x0a"
	           L"load \"Real\";\x0d\x0a"
	           L"fun PrintNumber(x: int) =\x0d\x0a"
	           L"  let\x0d\x0a"
	           L"    val Number = real(x) / 10.0;\x0d\x0a"
	           L"    val Text = \"The Number is \" ^ Real.toString(~Number) ^ \"\\n\";\x0d\x0a"
	           L"  in\x0d\x0a"
	           L"    print Text;\x0d\x0a"
	           L"    if x = 0 then () else PrintNumber(x-1)\x0d\x0a"
	           L"  end;";
	return result;
}

void __fastcall TSynSMLSyn::ResetRange()
{
	fRange = rsUnknown;
}

void __fastcall TSynSMLSyn::SetRange(void* Value)
{
	fRange = (TRangeState)(NativeInt)Value;
}

void* __fastcall TSynSMLSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) fRange);
	return result;
}

/*#static*/
String __fastcall TSynSMLSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangSML;
	return result;
}
static bool SynHighlighterSml_Initialized = false;

void SynHighlighterSml_initialization()
{
	if(SynHighlighterSml_Initialized)
		return;
	
	SynHighlighterSml_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynSMLSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterSml

