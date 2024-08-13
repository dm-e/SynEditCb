
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterFortran.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;

namespace Synhighlighterfortran
{
#define Synhighlighterfortran__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterfortran__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterfortran__2 (TSysCharSet() << 'C' << 'c')
#define Synhighlighterfortran__3 (TSysCharSet() << 'E' << 'T')
#define Synhighlighterfortran__4 (TSysCharSet() << 'E' << 'T')


const String Keywords[70/*# range 0..69*/] = {L"allocatable", L"allocate", L"allocated", L"associated", L"call", L"case", L"character", L"close", L"common"
                    , L"complex", L"contains", L"continue", L"cycle", L"data", L"deallocate", L"default", L"define", L"dimension", L"do", L"else"
                    , L"elseif", L"elsewhere", L"end", L"enddo", L"endif", L"entry", L"equivalence", L"exit", L"external", L"forall", L"format", L"function"
                    , L"if", L"implicit", L"include", L"integer", L"interface", L"logical", L"map", L"module", L"namelist", L"nullify", L"open"
                    , L"optional", L"parameter", L"pause", L"pointer", L"print", L"private", L"program", L"public", L"pure", L"read", L"real", L"record"
                    , L"return", L"save", L"select", L"stop", L"subroutine", L"target", L"then", L"type", L"union", L"use", L"value", L"volatile", L"where"
                    , L"while", L"write"};
const int KeyIndices[193/*# range 0..192*/] = {8, -1, -1, -1, -1, 11, -1, -1, -1, 31, 2, -1, -1, 59, -1, -1, -1, -1, -1, 13, 55, -1, -1, -1, 65, -1, 38, 54, 40, 10, 37, -1, -1, 25, -1, -1, 5, -1, -1, -1, -1, -1, -1
                    , 4, -1, -1, 21, -1, -1, 49, -1, -1, -1, -1, 9, -1, -1, 27, -1, 22, -1, 6, -1, -1, -1, -1, -1, -1, -1, -1, 64, -1, -1, 53, 68, -1, 34, -1, -1, 69, 30, -1, -1, -1, 32, -1, -1, -1, 19, 16, -1, -1, -1, -1, -1
                    , -1, -1, 62, -1, -1, -1, -1, -1, -1, 36, 60, 14, -1, -1, 66, 29, -1, -1, -1, -1, 24, -1, 67, -1, 15, -1, -1, -1, -1, -1, -1, 44, 35, -1, -1, 46, -1, 17, -1, -1, 28, -1, 56, 61, -1, -1, 63, 45, 18, -1, 0
                    , 20, -1, -1, -1, -1, -1, -1, 42, -1, 50, 3, 58, 52, -1, -1, -1, 51, -1, 48, -1, -1, -1, -1, -1, -1, -1, -1, 12, 23, -1, 26, 1, -1, 41, 43, -1, -1, -1, 33, 7, -1, -1, -1, 47, 39, 57, -1};

/*$Q-*/

unsigned int __fastcall TSynFortranSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 294 + int((*Str)) * 110);
		++Str;
	}
	result = (unsigned int) (result % 193);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynFortranSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 192 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynFortranSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 192 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	for(stop = 192 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynFortranSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynFortranSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynFortranSyn::TSynFortranSyn(TComponent* AOwner)
 : inherited(AOwner),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterfortran__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterfortran__1;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterFortran;
}

void __fastcall TSynFortranSyn::AsciiCharProc()
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

void __fastcall TSynFortranSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynFortranSyn::CommaProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFortranSyn::EqualProc()
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

void __fastcall TSynFortranSyn::ExclamationProc()
{
	Run += 1;                        /*Fortran Comments*/
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

void __fastcall TSynFortranSyn::GreaterProc()
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

void __fastcall TSynFortranSyn::IdentProc()
{
	if(CharInSet(fLine[Run], Synhighlighterfortran__2) && (Run == 0))   //Fortran comments
	{
		Run += 1;
		CommentProc();
	}
	else
	{
		FTokenID = IdentKind(fLine + Run);
		Run += fStringLen;
		while(IsIdentChar(fLine[Run]))
			++Run;
	}
}

void __fastcall TSynFortranSyn::LFProc()
{
	++Run;
	FTokenID = tkSpace;
}

void __fastcall TSynFortranSyn::LowerProc()
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

void __fastcall TSynFortranSyn::MinusProc()
{

  /*subtract*/
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFortranSyn::ModSymbolProc()
{

  /*mod*/
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFortranSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynFortranSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'.':
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
				goto label2;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label2:;
}

void __fastcall TSynFortranSyn::PlusProc()
{

  /*subtract*/
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFortranSyn::PointProc()
{
	if((((Sysutils::AnsiUpperCase(String(fLine[Run + 1])) == L"G") && CharInSet(Sysutils::AnsiUpperCase(String(fLine[Run + 2]))[1], Synhighlighterfortran__3)) || ((Sysutils::AnsiUpperCase(String(fLine[Run + 1])) == L"L") && CharInSet(Sysutils::AnsiUpperCase(String(fLine[Run + 2]))[1], Synhighlighterfortran__4)) || ((Sysutils::AnsiUpperCase(String(fLine[Run + 1])) == L"N") && (Sysutils::AnsiUpperCase(String(fLine[Run + 2])) == L"E")) || ((Sysutils::AnsiUpperCase(String(fLine[Run + 1])) == L"E") && (Sysutils::AnsiUpperCase(String(fLine[Run + 2])) == L"Q")) || ((Sysutils::AnsiUpperCase(String(fLine[Run + 1])) == L"O") && (Sysutils::AnsiUpperCase(String(fLine[Run + 2])) == L"R"))) && (fLine[Run + 3] == L'.')) /*.ge. .gt.*/ /*.le. .lt.*/ /*.ne.*/ /*.eq.*//*.or.*/
	{
		Run += 4;
		FTokenID = tkSymbol;
	}
	else
	{
		if((((Sysutils::AnsiUpperCase(String(fLine[Run + 1])) == L"A") && (Sysutils::AnsiUpperCase(String(fLine[Run + 2])) == L"N") && (Sysutils::AnsiUpperCase(String(fLine[Run + 3])) == L"D")) || ((Sysutils::AnsiUpperCase(String(fLine[Run + 1])) == L"N") && (Sysutils::AnsiUpperCase(String(fLine[Run + 2])) == L"O") && (Sysutils::AnsiUpperCase(String(fLine[Run + 3])) == L"T"))) && (fLine[Run + 4] == L'.'))    /*.and.*/    /*.not.*/
		{
			Run += 5;
			FTokenID = tkSymbol;
		}
		else
		{
			if((Sysutils::AnsiUpperCase(String(fLine[Run + 1])) == L"T") && (Sysutils::AnsiUpperCase(String(fLine[Run + 2])) == L"R") && (Sysutils::AnsiUpperCase(String(fLine[Run + 3])) == L"U") && (Sysutils::AnsiUpperCase(String(fLine[Run + 4])) == L"E") && (fLine[Run + 5] == L'.'))  /*.true.*/
			{
				Run += 6;
				FTokenID = tkSymbol;
			}
			else
			{
				if((Sysutils::AnsiUpperCase(String(fLine[Run + 1])) == L"F") && (Sysutils::AnsiUpperCase(String(fLine[Run + 2])) == L"A") && (Sysutils::AnsiUpperCase(String(fLine[Run + 3])) == L"L") && (Sysutils::AnsiUpperCase(String(fLine[Run + 4])) == L"S") && (Sysutils::AnsiUpperCase(String(fLine[Run + 5])) == L"E") && (fLine[Run + 6] == L'.'))  /*.false.*/
				{
					Run += 7;
					FTokenID = tkSymbol;
				}
				else
                                 /*point*/
				{
					++Run;
					FTokenID = tkSymbol;
				}
			}
		}
	}
}

void __fastcall TSynFortranSyn::RoundCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFortranSyn::RoundOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFortranSyn::SemiColonProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFortranSyn::SlashProc()
{

  /*division*/
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFortranSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynFortranSyn::StarProc()
{
	if(Run == 0)   //Fortran comments
	{
		++Run;
		CommentProc();
	}
	else

    /*star*/
	{
		++Run;
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynFortranSyn::CommentProc()
{
	FTokenID = tkComment;
	while(fLine[Run] != L'\x00')
	{
		switch(fLine[Run])
		{
			case L'\x0a':
			case L'\x0d':
			goto label3;
			default:
			  ;
			break;
		} //case
		++Run;
	} //while
	label3:;
}

void __fastcall TSynFortranSyn::StringProc()
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

void __fastcall TSynFortranSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynFortranSyn::Next()
{
	fTokenPos = Run;
	switch(fLine[Run])
	{
		case L'\x27':
		AsciiCharProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		case L',':
		CommaProc();
		break;
		case L'=':
		EqualProc();
		break;
		case L'!':
		ExclamationProc();
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
		case L'\x00':
		NullProc();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		NumberProc();
		break;
		case L'+':
		PlusProc();
		break;
		case L'.':
		PointProc();
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
		case L'*':
		StarProc();
		break;
		case L'\x22':
		StringProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynFortranSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynFortranSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynFortranSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynFortranSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
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

int __fastcall TSynFortranSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

bool __fastcall TSynFortranSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterFortran;
	return result;
}

/*#static*/
String __fastcall TSynFortranSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangFortran;
	return result;
}

/*#static*/
String __fastcall TSynFortranSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangFortran;
	return result;
}
static bool SynHighlighterFortran_Initialized = false;

void SynHighlighterFortran_initialization()
{
	if(SynHighlighterFortran_Initialized)
		return;
	
	SynHighlighterFortran_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynFortranSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterFortran

