
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterGWS.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;

namespace Synhighlightergws
{
#define Synhighlightergws__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlightergws__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightergws__2 (TSysCharSet() << '\x27' << '\\')


const String KeyWords[13/*# range 0..12*/] = {L"bool", L"break", L"char", L"do", L"else", L"false", L"for", L"if", L"int", L"return", L"string", L"true", L"while"};
const int KeyIndices[13/*# range 0..12*/] = {8, 5, 11, 12, 1, 10, 0, 2, 9, 4, 6, 3, 7};

/*$Q-*/

unsigned int __fastcall TSynGWScriptSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 797 + int((*Str)) * 6);
		++Str;
	}
	result = (unsigned int) (result % 13);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

void __fastcall TSynGWScriptSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 12 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[6] = FuncBool;
	fIdentFuncTable[4] = FuncBreak;
	fIdentFuncTable[7] = FuncChar;
	fIdentFuncTable[11] = FuncDo;
	fIdentFuncTable[9] = FuncElse;
	fIdentFuncTable[1] = FuncFalse;
	fIdentFuncTable[10] = FuncFor;
	fIdentFuncTable[12] = FuncIf;
	fIdentFuncTable[0] = FuncInt;
	fIdentFuncTable[8] = FuncReturn;
	fIdentFuncTable[5] = FuncString;
	fIdentFuncTable[2] = FuncTrue;
	fIdentFuncTable[3] = FuncWhile;
}

TtkTokenKind __fastcall TSynGWScriptSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncBool(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncBreak(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncChar(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncDo(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncElse(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncFalse(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncFor(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncIf(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncInt(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncReturn(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncString(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncTrue(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::FuncWhile(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkComment;
	unsigned int Key = 0;
	fToIdent = MayBe;
	Key = HashKey(MayBe);
	if(Key <= 12 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[Key](KeyIndices[Key]);
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynGWScriptSyn::TSynGWScriptSyn(TComponent* AOwner)
 : inherited(AOwner),
			fRange(rsUnKnown),
			FTokenID(tkComment),
			FExtTokenID(xtkAdd),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fInvalidAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr)
{
	fCaseSensitive = true;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlightergws__0;
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	fInvalidAttri = new TSynHighlighterAttributes(SYNS_AttrIllegalChar, SYNS_FriendlyAttrIllegalChar);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlightergws__1;
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	AddAttribute(fCommentAttri);
	AddAttribute(fIdentifierAttri);
	AddAttribute(fInvalidAttri);
	AddAttribute(fKeyAttri);
	AddAttribute(fNumberAttri);
	AddAttribute(fSpaceAttri);
	AddAttribute(fStringAttri);
	AddAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterGWS;
} /* Create */

void __fastcall TSynGWScriptSyn::AnsiCProc()
{
	FTokenID = tkComment;
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
	while(fLine[Run] != L'\x00')
		switch(fLine[Run])
		{
			case L'*':
			if(fLine[Run + 1] == L'/')
			{
				Run += 2;
				fRange = rsUnKnown;
				goto label0;
			}
			else
			++Run;
			break;
			case L'\x0a':
			goto label1;
			case L'\x0d':
			goto label2;
			default:
			++Run;
			break;
		}
	label0:;
	label1:;
	label2:;
}

void __fastcall TSynGWScriptSyn::AndSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*and assign*/
		{
			Run += 2;
			FExtTokenID = xtkAndAssign;
		}
		break;                               /*logical and*/
		case L'&':
		{
			Run += 2;
			FExtTokenID = xtkLogAnd;
		}
		break;                                 /*and*/
		default:
		{
			++Run;
			FExtTokenID = xtkAnd;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::AsciiCharProc()
{
	FTokenID = tkString;
	do
	{
		if(fLine[Run] == L'\\')
		{
			if(CharInSet(fLine[Run + 1], Synhighlightergws__2))
				++Run;
		}
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\x27')));
	if(fLine[Run] == L'\x27')
		++Run;
}

void __fastcall TSynGWScriptSyn::AtSymbolProc()
{
	FTokenID = tkUnknown;
	++Run;
}

void __fastcall TSynGWScriptSyn::BraceCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkBraceClose;
	fRange = rsUnKnown;
}

void __fastcall TSynGWScriptSyn::BraceOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkBraceOpen;
}

void __fastcall TSynGWScriptSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run + 1] == L'\x0a')
		++Run;
}

void __fastcall TSynGWScriptSyn::ColonProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L':':                               /*scope resolution operator*/
		{
			Run += 2;
			FExtTokenID = xtkScopeResolution;
		}
		break;                                 /*colon*/
		default:
		{
			++Run;
			FExtTokenID = xtkColon;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::CommaProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkComma;
}

void __fastcall TSynGWScriptSyn::EqualProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*logical equal*/
		{
			Run += 2;
			FExtTokenID = xtkLogEqual;
		}
		break;                                 /*assign*/
		default:
		{
			++Run;
			FExtTokenID = xtkAssign;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::GreaterProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*greater than or equal to*/
		{
			Run += 2;
			FExtTokenID = xtkGreaterThanEqual;
		}
		break;
		case L'>':
		{
			if(fLine[Run + 2] == L'=')   /*shift right assign*/
			{
				Run += 3;
				FExtTokenID = xtkShiftRightAssign;
			}
			else
                           /*shift right*/
			{
				Run += 2;
				FExtTokenID = xtkShiftRight;
			}
		}
		break;                                 /*greater than*/
		default:
		{
			++Run;
			FExtTokenID = xtkGreaterThan;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::QuestionProc()
{
	FTokenID = tkSymbol;                /*conditional*/
	FExtTokenID = xtkQuestion;
	++Run;
}

void __fastcall TSynGWScriptSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynGWScriptSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynGWScriptSyn::LowerProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*less than or equal to*/
		{
			Run += 2;
			FExtTokenID = xtkLessThanEqual;
		}
		break;
		case L'<':
		{
			if(fLine[Run + 2] == L'=')   /*shift left assign*/
			{
				Run += 3;
				FExtTokenID = xtkShiftLeftAssign;
			}
			else
                           /*shift left*/
			{
				Run += 2;
				FExtTokenID = xtkShiftLeft;
			}
		}
		break;                                 /*less than*/
		default:
		{
			++Run;
			FExtTokenID = xtkLessThan;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::MinusProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*subtract assign*/
		{
			Run += 2;
			FExtTokenID = xtkSubtractAssign;
		}
		break;                               /*decrement*/
		case L'-':
		{
			Run += 2;
			FExtTokenID = xtkDecrement;
		}
		break;                               /*arrow*/
		case L'>':
		{
			Run += 2;
			FExtTokenID = xtkArrow;
		}
		break;                                 /*subtract*/
		default:
		{
			++Run;
			FExtTokenID = xtkSubtract;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::ModSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*mod assign*/
		{
			Run += 2;
			FExtTokenID = xtkModAssign;
		}
		break;                                 /*mod*/
		default:
		{
			++Run;
			FExtTokenID = xtkMod;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::NotSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*not equal*/
		{
			Run += 2;
			FExtTokenID = xtkNotEqual;
		}
		break;                                 /*not*/
		default:
		{
			++Run;
			FExtTokenID = xtkLogComplement;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynGWScriptSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			case L'.':
			case L'u':
			case L'U':
			case L'l':
			case L'L':
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

void __fastcall TSynGWScriptSyn::OrSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*or assign*/
		{
			Run += 2;
			FExtTokenID = xtkIncOrAssign;
		}
		break;                               /*logical or*/
		case L'|':
		{
			Run += 2;
			FExtTokenID = xtkLogOr;
		}
		break;                                 /*or*/
		default:
		{
			++Run;
			FExtTokenID = xtkIncOr;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::PlusProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*add assign*/
		{
			Run += 2;
			FExtTokenID = xtkAddAssign;
		}
		break;                               /*increment*/
		case L'+':
		{
			Run += 2;
			FExtTokenID = xtkIncrement;
		}
		break;                                 /*add*/
		default:
		{
			++Run;
			FExtTokenID = xtkAdd;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::PointProc()
{
	FTokenID = tkSymbol;
	if((fLine[Run + 1] == L'.') && (fLine[Run + 2] == L'.'))                              /*ellipse*/
	{
		Run += 3;
		FExtTokenID = xtkEllipse;
	}
	else
                                 /*point*/
	{
		++Run;
		FExtTokenID = xtkPoint;
	}
}

void __fastcall TSynGWScriptSyn::RoundCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkRoundClose;
}

void __fastcall TSynGWScriptSyn::RoundOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkRoundOpen;
}

void __fastcall TSynGWScriptSyn::SemiColonProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSemiColon;
	fRange = rsUnKnown;
}

void __fastcall TSynGWScriptSyn::SlashProc()
{
	switch(fLine[Run + 1])
	{
		case L'/':                               /*c++ style comments*/
		{
			FTokenID = tkComment;
			Run += 2;
			while(!IsLineEnd(Run))
				++Run;
		}
		break;                               /*c style comments*/
		case L'*':
		{
			FTokenID = tkComment;
			fRange = rsAnsiC;
			Run += 2;
			while(fLine[Run] != L'\x00')
				switch(fLine[Run])
				{
					case L'*':
					if(fLine[Run + 1] == L'/')
					{
						Run += 2;
						fRange = rsUnKnown;
						goto label4;
					}
					else
					++Run;
					break;
					case L'\x0a':
					goto label5;
					case L'\x0d':
					goto label6;
					default:
					++Run;
					break;
				}
			label4:;
			label5:;
			label6:;
		}
		break;                               /*divide assign*/
		case L'=':
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkDivideAssign;
		}
		break;                                 /*divide*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkDivide;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynGWScriptSyn::SquareCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSquareClose;
}

void __fastcall TSynGWScriptSyn::SquareOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSquareOpen;
}

void __fastcall TSynGWScriptSyn::StarProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*multiply assign*/
		{
			Run += 2;
			FExtTokenID = xtkMultiplyAssign;
		}
		break;                                 /*star*/
		default:
		{
			++Run;
			FExtTokenID = xtkStar;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::StringProc()
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
			goto label7;                             /*backslash*/
			case L'\x5c':
			switch(fLine[Run + 1])
			{
				case L'\x22':
				++Run;
				break;               /*escaped quote doesn't count*/
				case L'\x5c':
				++Run;
				break;               /*escaped backslash doesn't count*/
				default:
				  ;
				break;
			}
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x22'));
	label7:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynGWScriptSyn::TildeProc()
{
	++Run;                            /*bitwise complement*/
	FTokenID = tkSymbol;
	FExtTokenID = xtkBitComplement;
}

void __fastcall TSynGWScriptSyn::XOrSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*xor assign*/
		{
			Run += 2;
			FExtTokenID = xtkXorAssign;
		}
		break;                                 /*xor*/
		default:
		{
			++Run;
			FExtTokenID = xtkXor;
		}
		break;
	}
}

void __fastcall TSynGWScriptSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynGWScriptSyn::Next()
{
	fTokenPos = Run;
	switch(fRange)
	{
		case rsAnsiC:
		AnsiCProc();
		break;
		default:
		{
			fRange = rsUnKnown;
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
				case L'=':
				EqualProc();
				break;
				case L'>':
				GreaterProc();
				break;
				case L'?':
				QuestionProc();
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
				case L'!':
				NotSymbolProc();
				break;
				case L'\x00':
				NullProc();
				break;
				case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
				NumberProc();
				break;
				case L'|':
				OrSymbolProc();
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
		}
		break;
	}
	inherited::Next();
}

bool __fastcall TSynGWScriptSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynGWScriptSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) fRange);
	return result;
}

TtkTokenKind __fastcall TSynGWScriptSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TxtkTokenKind __fastcall TSynGWScriptSyn::GetExtTokenID()
{
	TxtkTokenKind result = xtkAdd;
	result = FExtTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynGWScriptSyn::GetTokenAttribute()
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
		result = fInvalidAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynGWScriptSyn::GetTokenKind()
{
	int result = 0;
	result = int(GetTokenID());
	return result;
}

void __fastcall TSynGWScriptSyn::ResetRange()
{
	fRange = rsUnKnown;
}

void __fastcall TSynGWScriptSyn::SetRange(void* Value)
{
	fRange = (TRangeState)(NativeInt)Value;
}

bool __fastcall TSynGWScriptSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterGWS;
	return result;
}

/*#static*/
String __fastcall TSynGWScriptSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangGWS;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynGWScriptSyn::GetDefaultAttribute(int Index)
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

/*#static*/
String __fastcall TSynGWScriptSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangGWS;
	return result;
}

	static bool SynHighlighterGWS_Initialized = false;
	
	void SynHighlighterGWS_initialization()
	{
		if(SynHighlighterGWS_Initialized)
			return;
		
		SynHighlighterGWS_Initialized = true;
		
		RegisterPlaceableHighlighter(__classid(TSynGWScriptSyn));
	}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterGWS

