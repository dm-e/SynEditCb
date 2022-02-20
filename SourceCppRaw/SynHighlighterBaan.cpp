
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterBaan.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Uitypes;

namespace Synhighlighterbaan
{
#define SynHighlighterBaan__0 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterBaan__1 (TFontStyles() << TFontStyle::fsBold)


const String Keywords[113/*# range 0..112*/] = {L"__based", L"__cdecl", L"__declspe", L"__except", L"__export", L"__far", L"__fastcal", L"__fortran", L"__import"
																				, L"__int16", L"__int32", L"__int64", L"__int8", L"__interrup", L"__loadds", L"__near", L"__pascal", L"__rtti", L"__segment"
																				, L"__segname", L"__self", L"__stdcall", L"__thread", L"__try", L"_cdecl", L"_export", L"_fastcall", L"_import", L"_pascal"
																				, L"_stdcall", L"auto", L"bool", L"break", L"brp.open", L"case", L"catch", L"cdecl", L"char", L"class", L"const", L"continue", L"date.num"
																				, L"default", L"defined", L"delete", L"do", L"domain", L"double", L"else", L"endif", L"endselect", L"enum", L"explicit", L"export"
																				, L"extern", L"false", L"fastcall", L"finally", L"float", L"for", L"friend", L"from", L"function", L"goto", L"if", L"import", L"inline"
																				, L"int", L"interrupt", L"long", L"mutable", L"namespace", L"new", L"null", L"operator", L"pascal", L"private", L"protected", L"public"
																				, L"register", L"reinterpr", L"return", L"select", L"selectdo", L"short", L"signed", L"sizeof", L"sql.close", L"static", L"static_ca"
																				, L"stdcall", L"string", L"strip$", L"struct", L"switch", L"table", L"template", L"this", L"throw", L"true", L"try", L"typedef"
																				, L"typeid", L"typename", L"union", L"unsigned", L"using", L"virtual", L"void", L"volatile", L"wchar_t", L"where", L"while"};
const int KeyIndices[461/*# range 0..460*/] = {-1, -1, -1, -1, -1, -1, 83, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, 33, 26, -1, 78, -1, -1, -1, -1, -1, 5, -1, 14, -1, 27, -1, 92, -1, -1, -1, -1, 42, -1
																				, 77, -1, -1, -1, -1, -1, -1, -1, -1, -1, 61, -1, -1, -1, 93, 2, -1, -1, -1, 50, -1, -1, -1, -1, -1, 40, -1, -1, -1, -1, 63, -1, 94, -1, -1, 69, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, -1, -1, 44, -1
																				, -1, -1, 110, -1, -1, 51, -1, -1, -1, -1, 56, -1, 32, -1, -1, 109, -1, -1, -1, -1, 16, -1, -1, -1, -1, 23, 88, -1, -1, 10, -1, -1, -1, -1, 67, -1, -1, -1, 72, 81, -1, -1, -1, 82, 24, -1, -1, -1, -1, -1
																				, -1, -1, -1, 79, -1, -1, 64, 21, 80, -1, -1, 59, 0, -1, -1, -1, 12, -1, -1, 107, -1, 36, -1, -1, -1, -1, 31, -1, -1, -1, 62, -1, -1, 112, -1, -1, -1, -1, -1, -1, 7, -1, 106, -1, -1, -1, -1, -1, -1, -1
																				, -1, 52, 104, -1, 18, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 65, -1, -1, -1, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, 28, 43, -1, 20, -1, -1, -1, 38, -1, -1
																				, -1, -1, -1, 103, -1, 70, 87, -1, -1, -1, 85, -1, 74, -1, -1, -1, -1, -1, 35, 39, -1, -1, 97, 53, -1, -1, -1, -1, -1, -1, -1, 84, -1, 95, -1, -1, -1, -1, -1, -1, -1, 100, 98, -1, -1, -1, -1, -1, -1, -1
																				, -1, 111, 73, -1, 47, -1, -1, -1, -1, -1, -1, -1, 105, -1, -1, -1, -1, -1, 66, 86, -1, -1, -1, -1, -1, -1, -1, -1, 34, -1, -1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 37, 55, -1, -1, -1, 89, -1
																				, 11, -1, -1, -1, 19, -1, -1, -1, -1, 90, -1, 102, 54, -1, -1, 45, -1, -1, 6, 30, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 46, 8, 22, -1, -1, -1, -1, 99, -1, -1, -1, -1, -1, -1, -1, -1, -1, 101, -1, -1, -1
																				, -1, -1, -1, -1, 71, -1, -1, -1, -1, -1, 96, 48, -1, -1, -1, -1, -1, 75, -1, 60, -1, -1, 58, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, 17, 4, -1, -1, -1, -1, 49, -1, -1, -1, -1, 57, -1, -1, -1, -1, 15, 91
																				, -1, -1, 41, -1, -1, -1, 76, 68, -1, -1, -1, 108, -1, -1};

/*$Q-*/

unsigned int __fastcall TSynBaanSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 838 + int((*Str)) * 296);
		++Str;
	}
	result = (unsigned int) (result % 461);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynBaanSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 460 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynBaanSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 460 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] ==  - 1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[21] = FuncBrp46open;
	fIdentFuncTable[449] = FuncDate46num;
	for(stop = 460 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynBaanSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBaanSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBaanSyn::FuncBrp46open(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkVariable;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBaanSyn::FuncDate46num(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkVariable;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynBaanSyn::TSynBaanSyn(TComponent* AOwner)
 : inherited(AOwner),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fDirectiveAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fVariableAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = SynHighlighterBaan__0;
	addAttribute(fCommentAttri);
	fDirectiveAttri = new TSynHighlighterAttributes(SYNS_AttrDirective, SYNS_FriendlyAttrDirective);
	addAttribute(fDirectiveAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = SynHighlighterBaan__1;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fVariableAttri = new TSynHighlighterAttributes(SYNS_AttrVariable, SYNS_FriendlyAttrVariable);
	addAttribute(fVariableAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterBaan;
}

void __fastcall TSynBaanSyn::AndSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*and assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                               /*logical and*/
		case L'&':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*and*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynBaanSyn::AsciiCharProc()
{
	FTokenID = tkString;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label0;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x27'));
	label0:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynBaanSyn::AtSymbolProc()
{
	FTokenID = tkSymbol;
	++Run;
}

void __fastcall TSynBaanSyn::BraceCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynBaanSyn::BraceOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynBaanSyn::CRProc()
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

void __fastcall TSynBaanSyn::ColonProc()
{
	switch(fLine[Run + 1])
	{
		case L':':                               /*scope resolution operator*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*colon*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynBaanSyn::CommaProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynBaanSyn::DirectiveProc()
{
	FTokenID = tkDirective;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label1;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x00'));
	label1:;
}

void __fastcall TSynBaanSyn::EqualProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*logical equal*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*assign*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynBaanSyn::ErectProc()
{
	Run += 1;                        /*Bann Comments*/
	FTokenID = tkComment;
	while(fLine[Run] != L'\x00')
	{
		switch(fLine[Run])
		{
			case L'\x0a':
			case L'\x0d':
			goto label2;
			default:
			  ;
			break;
		} //case
		++Run;
	} //while
	label2:;
}

void __fastcall TSynBaanSyn::GreaterProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*greater than or equal to*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;
		case L'>':
		{
			if(fLine[Run + 2] == L'=')   /*shift right assign*/
				Run += 3;
			else
                           /*shift right*/
				Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*greater than*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynBaanSyn::IdentProc()
{
	FTokenID = IdentKind(fLine + Run);
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynBaanSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynBaanSyn::LowerProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*less than or equal to*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;
		case L'<':
		{
			if(fLine[Run + 2] == L'=')   /*shift left assign*/
				Run += 3;
			else
                           /*shift left*/
				Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*less than*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynBaanSyn::MinusProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*subtract assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                               /*decrement*/
		case L'-':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                               /*arrow*/
		case L'>':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*subtract*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynBaanSyn::ModSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*mod assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*mod*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynBaanSyn::NotSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*not equal*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*not*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynBaanSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynBaanSyn::NumberProc()
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
				goto label3;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label3:;
}

void __fastcall TSynBaanSyn::PlusProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*add assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                               /*increment*/
		case L'+':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*subtract*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynBaanSyn::RoundCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynBaanSyn::RoundOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynBaanSyn::SemiColonProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynBaanSyn::SlashProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*division assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*division*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynBaanSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynBaanSyn::SquareCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynBaanSyn::SquareOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynBaanSyn::StarProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*multiply assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*star*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynBaanSyn::StringProc()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x22') && (fLine[Run + 2] == L'\x22'))
		Run += 2;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label4;
			case L'\x5c':
			if(fLine[Run + 1] == L'\x0a')
				++Run;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x22'));
	label4:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynBaanSyn::TildeProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynBaanSyn::XOrSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*xor assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*xor*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynBaanSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynBaanSyn::Next()
{
	fTokenPos = Run;
	switch(fLine[Run])
	{
		case L'&':
		AndSymbolProc();
		break;
		case L'\x27':
		AsciiCharProc();
		break;
		case L'@':
		AtSymbolProc();
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
		case L':':
		ColonProc();
		break;
		case L',':
		CommaProc();
		break;
		case L'#':
		DirectiveProc();
		break;
		case L'=':
		EqualProc();
		break;
		case L'|':
		ErectProc();
		break;
		case L'>':
		GreaterProc();
		break;
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		case L'_':
		case L'.':
		case L'$':
		IdentProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'<':
		LowerProc();
		break;
		case L'-':
		MinusProc();
		break;
		case L'%':
		ModSymbolProc();
		break;
		case L'!':
		NotSymbolProc();
		break;
		case L'\x00':
		NullProc();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		NumberProc();
		break;
		case L'+':
		PlusProc();
		break;
		case L')':
		RoundCloseProc();
		break;
		case L'(':
		RoundOpenProc();
		break;
		case L';':
		SemiColonProc();
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
		case L']':
		SquareCloseProc();
		break;
		case L'[':
		SquareOpenProc();
		break;
		case L'*':
		StarProc();
		break;
		case L'\x22':
		StringProc();
		break;
		case L'~':
		TildeProc();
		break;
		case L'^':
		XOrSymbolProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynBaanSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynBaanSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynBaanSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynBaanSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkDirective:
		result = fDirectiveAttri;
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
		case tkVariable:
		result = fVariableAttri;
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

int __fastcall TSynBaanSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

bool __fastcall TSynBaanSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterBaan;
	return result;
}

bool __fastcall TSynBaanSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'.':
		case L'$':
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
String __fastcall TSynBaanSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangBaan;
	return result;
}

/*#static*/
String __fastcall TSynBaanSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangBaan;
	return result;
}
static bool SynHighlighterBaan_Initialized = false;

void SynHighlighterBaan_initialization()
{
	if(SynHighlighterBaan_Initialized)
		return;
	
	SynHighlighterBaan_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynBaanSyn));
}
class SynHighlighterBaan_unit
{
public:
	SynHighlighterBaan_unit()
	{
		SynHighlighterBaan_initialization();
	}
};

SynHighlighterBaan_unit _SynHighlighterBaan_unit;

}  // namespace SynHighlighterBaan

