
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterSDD.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Synhighlightersdd
{
#define SynHighlighterSDD__0 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterSDD__1 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterSDD__2 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterSDD__3 (TSysCharSet() <<  \
										1 << 2 << 3 << 4 << 5 << 6 <<  \
										7 << 8 << 9 << 10 << 11 << 12 <<  \
										13 << 14 << 15 << 16 << 17 << 18 <<  \
										19 << 20 << 21 << 22 << 23 << 24 <<  \
										25 << 26 << 27 << 28 << 29 << 30 <<  \
										31 << 32)


const String Keywords[27/*# range 0..26*/] = {L"array", L"binarydata", L"block", L"byte", L"database", L"date", L"end", L"endblock", L"integer", L"keys"
																				, L"longint", L"memotext", L"object", L"objects", L"of", L"owner", L"partition", L"partitions", L"primary", L"real", L"secondary"
																				, L"spec", L"string", L"superblock", L"superspec", L"time", L"var"};
const int KeyIndices[37/*# range 0..36*/] = {8, 3, 18, 0, 25, 14, 16, 22, 5, 19, 10, 20, -1, -1, 2, 26, -1, 21, -1, 12, 1, 17, 15, -1, 9, -1, 11, 7, -1, 4, 6, -1, 13, -1, -1, 24, 23};

/*$Q-*/

unsigned int __fastcall TSynSDDSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 813 + int((*Str)) * 168);
		++Str;
	}
	result = (unsigned int) (result % 37);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynSDDSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 36 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynSDDSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 36 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] ==  - 1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[3] = FuncArray;
	fIdentFuncTable[20] = FuncBinarydata;
	fIdentFuncTable[14] = FuncBlock;
	fIdentFuncTable[1] = FuncByte;
	fIdentFuncTable[29] = FuncDatabase;
	fIdentFuncTable[8] = FuncDate;
	fIdentFuncTable[30] = FuncEnd;
	fIdentFuncTable[27] = FuncEndblock;
	fIdentFuncTable[0] = FuncInteger;
	fIdentFuncTable[24] = FuncKeys;
	fIdentFuncTable[10] = FuncLongint;
	fIdentFuncTable[26] = FuncMemotext;
	fIdentFuncTable[19] = FuncObject;
	fIdentFuncTable[32] = FuncObjects;
	fIdentFuncTable[5] = FuncOf;
	fIdentFuncTable[22] = FuncOwner;
	fIdentFuncTable[6] = FuncPartition;
	fIdentFuncTable[21] = FuncPartitions;
	fIdentFuncTable[2] = FuncPrimary;
	fIdentFuncTable[9] = FuncReal;
	fIdentFuncTable[11] = FuncSecondary;
	fIdentFuncTable[17] = FuncSpec;
	fIdentFuncTable[7] = FuncString;
	fIdentFuncTable[36] = FuncSuperblock;
	fIdentFuncTable[35] = FuncSuperspec;
	fIdentFuncTable[4] = FuncTime;
	fIdentFuncTable[15] = FuncVar;
}

TtkTokenKind __fastcall TSynSDDSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncArray(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncBinarydata(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncBlock(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncByte(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncDatabase(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncDate(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncEnd(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncEndblock(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncInteger(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncKeys(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncLongint(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncMemotext(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncObject(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncObjects(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncOf(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncOwner(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncPartition(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncPartitions(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncPrimary(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncReal(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncSecondary(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncSpec(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncString(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncSuperblock(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncSuperspec(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncTime(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSDDSyn::FuncVar(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynSDDSyn::TSynSDDSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fDataTypeAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fSymbolAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Foreground = clNavy;
	fCommentAttri->Style = SynHighlighterSDD__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = SynHighlighterSDD__1;
	fKeyAttri->Foreground = clGreen;
	addAttribute(fKeyAttri);
	fDataTypeAttri = new TSynHighlighterAttributes(SYNS_AttrDataType, SYNS_FriendlyAttrDataType);
	fDataTypeAttri->Style = SynHighlighterSDD__2;
	fDataTypeAttri->Foreground = clTeal;
	addAttribute(fDataTypeAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = clBlue;
	addAttribute(fNumberAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterSDD;
} /* Create */

void __fastcall TSynSDDSyn::BraceOpenProc()
{
	FRange = rsComment;
	BraceCommentProc();
	FTokenID = tkComment;
} /* BraceOpenProc */

void __fastcall TSynSDDSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
} /* IdentProc */

void __fastcall TSynSDDSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
} /* NullProc */

void __fastcall TSynSDDSyn::SpaceProc()
{
	FTokenID = tkSpace;
	do
	{
		++Run;
	}
	while(!!CharInSet(fLine[Run], SynHighlighterSDD__3));
} /* SpaceProc */

void __fastcall TSynSDDSyn::BraceCommentProc()
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
				if(fLine[Run] == L'}')
				{
					++Run;
					FRange = rsUnKnown;
					break;
				}
				++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
	}
} /* BraceCommentProc */

void __fastcall TSynSDDSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
} /* UnknownProc */

void __fastcall TSynSDDSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsComment:
		BraceCommentProc();
		break;
		default:
		switch(fLine[Run])
		{
			case L'{':
			BraceOpenProc();
			break;
			case L'}':
			case L'!':
			case L'%':
			case L'&':
			case 40: case 41: case 42: case 43: case 44: case 45: case 46: case 47:
			case 58: case 59: case 60: case 61: case 62: case 63: case 64:
			case 91: case 92: case 93: case 94:
			case L'`':
			case L'~':
			SymbolProc();
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
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			NumberProc();
			break;
			case L'\x00':
			NullProc();
			break;
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
			 case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20:
			 case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30:
			 case 31: case 32:
			SpaceProc();
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
} /* Next */

void __fastcall TSynSDDSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
} /* CRProc */

void __fastcall TSynSDDSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
} /* LFProc */

String __fastcall TSynSDDSyn::GetSampleSource()
{
	String result;
	result = L"{ Semanta data dictionary }\x0d\x0a"
	           L"database Sample.001;\x0d\x0a"
	           L"owner = COAS;\x0d\x0a"
	           L"\x0d\x0a"
	           L"objects\x0d\x0a"
	           L"  Test = object\x0d\x0a"
	           L"    Code : string[4];\x0d\x0a"
	           L"    Name : string[80];\x0d\x0a"
	           L"  end;\x0d\x0a"
	           L"keys\x0d\x0a"
	           L"  primary Test.Index = [Code];\x0d\x0a"
	           L"end.";
	return result;
} /* GetSampleSource */

TSynHighlighterAttributes* __fastcall TSynSDDSyn::GetDefaultAttribute(int Index)
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
} /* GetDefaultAttribute */

bool __fastcall TSynSDDSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
} /* GetEol */

TtkTokenKind __fastcall TSynSDDSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
} /* GetTokenId */

TSynHighlighterAttributes* __fastcall TSynSDDSyn::GetTokenAttribute()
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
		case tkDataType:
		result = fDataTypeAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkNumber:
		result = fNumberAttri;
		break;
		case tkUnknown:
		result = fIdentifierAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
} /* GetTokenAttribute */

int __fastcall TSynSDDSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
} /* GetTokenKind */

void __fastcall TSynSDDSyn::ResetRange()
{
	inherited::ResetRange();
	FRange = rsUnKnown;
} /* ResetRange */

void __fastcall TSynSDDSyn::SetRange(void* Value)
{
	inherited::SetRange(Value);
	FRange = (TRangeState)(int)Value;
} /* SetRange */

void* __fastcall TSynSDDSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
} /* GetRange */

/*#static*/
String __fastcall TSynSDDSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangSDD;
	return result;
} /* GetLanguageName */

void __fastcall TSynSDDSyn::NumberProc()
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
} /* NumberProc */

bool __fastcall TSynSDDSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterSDD;
	return result;
} /* IsFilterStored */

void __fastcall TSynSDDSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

/*#static*/
String __fastcall TSynSDDSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangSDD;
	return result;
}
static bool SynHighlighterSDD_Initialized = false;

void SynHighlighterSDD_initialization()
{
	if(SynHighlighterSDD_Initialized)
		return;
	
	SynHighlighterSDD_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynSDDSyn));
}
class SynHighlighterSDD_unit
{
public:
	SynHighlighterSDD_unit()
	{
		SynHighlighterSDD_initialization();
	}
};

SynHighlighterSDD_unit _SynHighlighterSDD_unit;

}  // namespace SynHighlighterSDD

