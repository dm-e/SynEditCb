
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterHaskell.h"
#include <Winapi.Windows.hpp>
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditmiscclasses;
using namespace Syneditstrconst;
using namespace System;

namespace Synhighlighterhaskell
{
#define Synhighlighterhaskell__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterhaskell__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterhaskell__2 (TSysCharSet() << '\x27' << '\\')
#define Synhighlighterhaskell__3 (TSysCharSet() << '\x22' << '\\')
#define Synhighlighterhaskell__4 (TSynHighlighterCapabilities() << hcUserSettings)


const String KeyWords[24/*# range 0..23*/] = {L"Bool", L"Char", L"class", L"data", L"deriving", L"Double", L"else", L"False", L"Float", L"if", L"import", L"in"
                    , L"instance", L"Int", L"Integer", L"IO", L"let", L"module", L"otherwise", L"String", L"then", L"True", L"type", L"where"};
const int KeyIndices[29/*# range 0..28*/] = {2, 23, 10, 16, 7, -1, 22, 8, 14, 17, 5, 4, 11, -1, 1, 9, 12, 0, -1, 6, -1, 3, 15, 18, 20, -1, 13, 19, 21};

/*$Q-*/

unsigned int __fastcall TSynHaskellSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 904 + int((*Str)) * 779);
		++Str;
	}
	result = (unsigned int) (result % 29);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynHaskellSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkComment;
	unsigned int Key = 0;
	fToIdent = MayBe;
	Key = HashKey(MayBe);
	if(Key <= 28 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[Key](KeyIndices[Key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynHaskellSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 28 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	for(stop = 28 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynHaskellSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynHaskellSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynHaskellSyn::TSynHaskellSyn(TComponent* AOwner)
 : inherited(AOwner),
			fAsmStart(false),
			fRange(rsUnknown),
			FTokenID(tkComment),
			FExtTokenID(xtkAdd),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr)
{
	fCaseSensitive = true;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterhaskell__0;
	AddAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterhaskell__1;
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
	InitIdent();
	fRange = rsUnknown;
	fDefaultFilter = SYNS_FilterHaskell;
} /* Create */

void __fastcall TSynHaskellSyn::AnsiCProc()
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
				if(fRange == rsAnsiCAsm)
					fRange = rsAsm;
				else
				{
					if(fRange == rsAnsiCAsmBlock)
						fRange = rsAsmBlock;
					else
					{
						if(fRange == rsDirectiveComment)
							fRange = rsDirective;
						else
							fRange = rsUnknown;
					}
				}
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

void __fastcall TSynHaskellSyn::AndSymbolProc()
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

void __fastcall TSynHaskellSyn::AsciiCharProc()
{
	FTokenID = tkString;
	do
	{
		if(fLine[Run] == L'\\')
		{
			if(CharInSet(fLine[Run + 1], Synhighlighterhaskell__2))
				++Run;
		}
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\x27')));
	if(fLine[Run] == L'\x27')
		++Run;
}

void __fastcall TSynHaskellSyn::AtSymbolProc()
{
	FTokenID = tkUnknown;
	++Run;
}

void __fastcall TSynHaskellSyn::BraceCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkBraceClose;
	if(fRange == rsAsmBlock)
		fRange = rsUnknown;
}

void __fastcall TSynHaskellSyn::BraceOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkBraceOpen;
	if(fRange == rsAsm)
	{
		fRange = rsAsmBlock;
		fAsmStart = true;
	}
}

void __fastcall TSynHaskellSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run + 1] == L'\x0a')
		++Run;
}

void __fastcall TSynHaskellSyn::ColonProc()
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

void __fastcall TSynHaskellSyn::CommaProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkComma;
}

void __fastcall TSynHaskellSyn::EqualProc()
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

void __fastcall TSynHaskellSyn::GreaterProc()
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

void __fastcall TSynHaskellSyn::QuestionProc()
{
	FTokenID = tkSymbol;                /*conditional*/
	FExtTokenID = xtkQuestion;
	++Run;
}

void __fastcall TSynHaskellSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynHaskellSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynHaskellSyn::LowerProc()
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

void __fastcall TSynHaskellSyn::MinusProc()
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
			FTokenID = tkComment;
			Run += 2;
			while(!IsLineEnd(Run))
				++Run;
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

void __fastcall TSynHaskellSyn::ModSymbolProc()
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

void __fastcall TSynHaskellSyn::NotSymbolProc()
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

void __fastcall TSynHaskellSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynHaskellSyn::NumberProc()
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

void __fastcall TSynHaskellSyn::OrSymbolProc()
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

void __fastcall TSynHaskellSyn::PlusProc()
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

void __fastcall TSynHaskellSyn::PointProc()
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

void __fastcall TSynHaskellSyn::RoundCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkRoundClose;
}

void __fastcall TSynHaskellSyn::RoundOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkRoundOpen;
}

void __fastcall TSynHaskellSyn::SemiColonProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSemiColon;
	if(fRange == rsAsm)
		fRange = rsUnknown;
}

void __fastcall TSynHaskellSyn::SlashProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*divide assign*/
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

void __fastcall TSynHaskellSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynHaskellSyn::SquareCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSquareClose;
}

void __fastcall TSynHaskellSyn::SquareOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSquareOpen;
}

void __fastcall TSynHaskellSyn::StarProc()
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

void __fastcall TSynHaskellSyn::StringProc()
{
	FTokenID = tkString;
	do
	{
		if(fLine[Run] == L'\\')
		{
			if(CharInSet(fLine[Run + 1], Synhighlighterhaskell__3))
				++Run;
		}
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\x22')));
	if(fLine[Run] == L'\x22')
		++Run;
}

void __fastcall TSynHaskellSyn::TildeProc()
{
	++Run;                            /*bitwise complement*/
	FTokenID = tkSymbol;
	FExtTokenID = xtkBitComplement;
}

void __fastcall TSynHaskellSyn::XOrSymbolProc()
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

void __fastcall TSynHaskellSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynHaskellSyn::Next()
{
	fAsmStart = false;
	fTokenPos = Run;
	switch(fRange)
	{
		case rsAnsiC:
		case rsAnsiCAsm:
		case rsAnsiCAsmBlock:
		AnsiCProc();
		break;
		default:
		{
			fRange = rsUnknown;
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

TSynHighlighterAttributes* __fastcall TSynHaskellSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynHaskellSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynHaskellSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) fRange);
	return result;
}

TtkTokenKind __fastcall TSynHaskellSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TxtkTokenKind __fastcall TSynHaskellSyn::GetExtTokenID()
{
	TxtkTokenKind result = xtkAdd;
	result = FExtTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynHaskellSyn::GetTokenAttribute()
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
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynHaskellSyn::GetTokenKind()
{
	int result = 0;
	result = int(GetTokenID());
	return result;
}

void __fastcall TSynHaskellSyn::ResetRange()
{
	fRange = rsUnknown;
}

void __fastcall TSynHaskellSyn::SetRange(void* Value)
{
	fRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynHaskellSyn::EnumUserSettings(TStrings* settings)
{

  /* returns the user settings that exist in the registry */
	/*# with TBetterRegistry.Create do */
	{
		auto with0 = new TBetterRegistry();
		try
		{
			with0->RootKey = HKEY_LOCAL_MACHINE;
			if(with0->OpenKeyReadOnly(L"\\SOFTWARE\\Borland\\C++Builder"))
			{
				try
				{
					with0->GetKeyNames(settings);
				}
				__finally
				{
					with0->CloseKey();
				}
			}
		}
		__finally
		{
			delete with0;
		}
	}
}

bool __fastcall TSynHaskellSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterHaskell;
	return result;
}

bool __fastcall TSynHaskellSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'_':
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case L'\x27':
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

/*#static*/
String __fastcall TSynHaskellSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangHaskell;
	return result;
}

/*#static*/
TSynHighlighterCapabilities __fastcall TSynHaskellSyn::GetCapabilities()
{
	TSynHighlighterCapabilities result;
	result = inherited::GetCapabilities() + Synhighlighterhaskell__4;
	return result;
}

String __fastcall TSynHaskellSyn::GetSampleSource()
{
	String result;
	result = L"-- Haskell Sample Source\x0d\x0a" L"tail :: [a] -> [a]\x0d\x0a" L"tail (x:xs) = xs\x0d\x0a" L"";
	return result;
}

/*#static*/
String __fastcall TSynHaskellSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangHaskell;
	return result;
}
static bool SynHighlighterHaskell_Initialized = false;

void SynHighlighterHaskell_initialization()
{
	if(SynHighlighterHaskell_Initialized)
		return;
	
	SynHighlighterHaskell_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynHaskellSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterHaskell

