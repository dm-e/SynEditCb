
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterST.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;

namespace Synhighlighterst
{
#define Synhighlighterst__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterst__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterst__2 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterst__3 (TSysCharSet() << '=' << '>')
#define Synhighlighterst__4 (TSysCharSet() << '.' << ')')
#define Synhighlighterst__5 (System::Set<TtkTokenKind, TtkTokenKind::tkAsm, TtkTokenKind::tkUnknown>() << tkNull << tkComment << tkSpace)


const String KeyWords[75/*# range 0..74*/] = {L"action", L"and", L"any", L"any_num", L"array", L"at", L"bool", L"by", L"byte", L"case", L"configuration", L"constant"
                    , L"dint", L"do", L"dword", L"else", L"elsif", L"end_action", L"end_case", L"end_configuration", L"end_for", L"end_if", L"end_repeat"
                    , L"end_resource", L"end_step", L"end_struct", L"end_transition", L"end_type", L"end_var", L"end_while", L"exit"
                    , L"external", L"finally", L"for", L"from", L"function", L"goto", L"if", L"index", L"initial_step", L"initialization", L"int"
                    , L"label", L"not", L"of", L"on", L"or", L"program", L"real", L"repeat", L"resource", L"retain", L"return", L"sint", L"step", L"string"
                    , L"struct", L"then", L"time", L"to", L"transition", L"type", L"udint", L"uint", L"until", L"usint", L"var", L"var_external", L"var_global"
                    , L"var_in_out", L"var_input", L"var_output", L"while", L"word", L"xor"};
const int KeyIndices[211/*# range 0..210*/] = {-1, -1, -1, -1, -1, 55, 39, -1, -1, -1, -1, 51, -1, -1, -1, -1, 57, 49, 4, -1, 17, -1, -1, -1, -1, -1, -1, 24, -1, -1, -1, -1, -1, -1, 61, -1, -1, -1, 47, -1, -1, -1
                    , 58, 70, 38, -1, -1, 35, -1, -1, -1, 28, 12, -1, -1, -1, -1, -1, -1, 64, -1, -1, 1, -1, -1, 69, 27, 45, -1, 2, -1, -1, -1, 3, 9, -1, 37, 13, 63, -1, -1, 8, -1, -1, -1, -1, -1, 60, -1, -1, -1, -1, -1, -1, -1
                    , -1, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, 25, 20, -1, 53, 14, -1, -1, -1, 0, -1, -1, 26, 41, 42, 62, -1, -1, -1, 66, 21, 36, -1, -1, 30, -1, 73, 22, -1, 16, -1, -1, -1, -1, 74, -1, -1, 23, -1, 29
                    , 50, -1, -1, -1, -1, -1, 68, -1, -1, 19, -1, 15, 11, -1, 48, -1, 72, -1, 43, -1, -1, -1, -1, 67, 31, -1, 32, -1, -1, 6, -1, -1, 7, 65, -1, -1, 33, -1, -1, -1, -1, -1, -1, -1, 5, -1, 40, 52, 34, -1, -1, -1
                    , -1, -1, -1, -1, 56, -1, -1, 44, 54, -1, 71, 46, 59};

/*$Q-*/

unsigned int __fastcall TSynSTSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 381 + int((*Str)) * 141);
		++Str;
	}
	result = (unsigned int) (result % 211);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynSTSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkAsm;
	unsigned int Key = 0;
	fToIdent = MayBe;
	Key = HashKey(MayBe);
	if(Key <= 210 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[Key](KeyIndices[Key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynSTSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 210 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	for(stop = 210 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynSTSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkAsm;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSTSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkAsm;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynSTSyn::TSynSTSyn(TComponent* AOwner)
 : inherited(AOwner),
			fAsmStart(false),
			fRange(rsANil),
			FTokenID(tkAsm),
			fStringAttri(nullptr),
			fNumberAttri(nullptr),
			fKeyAttri(nullptr),
			fSymbolAttri(nullptr),
			fAsmAttri(nullptr),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fSpaceAttri(nullptr)
{
	fCaseSensitive = false;
	fAsmAttri = new TSynHighlighterAttributes(SYNS_AttrAssembler, SYNS_FriendlyAttrAssembler);
	AddAttribute(fAsmAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterst__0;
	AddAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterst__1;
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
	fRange = rsUnKnown;
	fDefaultFilter = SYNS_FilterST;
} /* Create */

void __fastcall TSynSTSyn::AddressOpProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'@')
		++Run;
}

void __fastcall TSynSTSyn::AsciiCharProc()
{
	FTokenID = tkString;
	++Run;
	while(CharInSet(fLine[Run], Synhighlighterst__2))
		++Run;
}

void __fastcall TSynSTSyn::BorProc()
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
					if(fRange == rsBorAsm)
						fRange = rsAsm;
					else
						fRange = rsUnKnown;
					break;
				}
				++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
	}
}

void __fastcall TSynSTSyn::BraceOpenProc()
{
	if(fRange == rsAsm)
		fRange = rsBorAsm;
	else
		fRange = rsBor;
	BorProc();
}

void __fastcall TSynSTSyn::ColonOrGreaterProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynSTSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynSTSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynSTSyn::IntegerProc()
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
	++Run;
	FTokenID = tkNumber;
	while(IsIntegerChar())
		++Run;
}

void __fastcall TSynSTSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynSTSyn::LowerProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], Synhighlighterst__3))
		++Run;
}

void __fastcall TSynSTSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynSTSyn::NumberProc()
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

void __fastcall TSynSTSyn::PointProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], Synhighlighterst__4))
		++Run;
}

void __fastcall TSynSTSyn::AnsiProc()
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
		FTokenID = tkComment;
		do
		{
			if((fLine[Run] == L'*') && (fLine[Run + 1] == L')'))
			{
				Run += 2;
				if(fRange == rsAnsiAsm)
					fRange = rsAsm;
				else
					fRange = rsUnKnown;
				break;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
		break;
	}
}

void __fastcall TSynSTSyn::RoundOpenProc()
{
	++Run;
	switch(fLine[Run])
	{
		case L'*':
		{
			++Run;
			if(fRange == rsAsm)
				fRange = rsAnsiAsm;
			else
				fRange = rsAnsi;
			FTokenID = tkComment;
			if(!IsLineEnd(Run))
				AnsiProc();
		}
		break;
		case L'.':
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
		default:
		FTokenID = tkSymbol;
		break;
	}
}

void __fastcall TSynSTSyn::SemicolonProc()
{
	++Run;
	FTokenID = tkSymbol;
	if(fRange == rsProperty)
		fRange = rsUnKnown;
}

void __fastcall TSynSTSyn::SlashProc()
{
	++Run;
	if(fLine[Run] == L'/')
	{
		FTokenID = tkComment;
		do
		{
			++Run;
		}
		while(!IsLineEnd(Run));
	}
	else
	FTokenID = tkSymbol;
}

void __fastcall TSynSTSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynSTSyn::StringProc()
{
	FTokenID = tkString;
	++Run;
	while(!IsLineEnd(Run))
	{
		if(fLine[Run] == L'\x27')
		{
			++Run;
			if(fLine[Run] != L'\x27')
				break;
		}
		++Run;
	}
}

void __fastcall TSynSTSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynSTSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynSTSyn::Next()
{
	fAsmStart = false;
	fTokenPos = Run;
	switch(fRange)
	{
		case rsAnsi:
		case rsAnsiAsm:
		AnsiProc();
		break;
		case rsBor:
		case rsBorAsm:
		BorProc();
		break;
		default:
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
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			case L'\x0b':
			case L'\x0c':
			case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
			 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
			SpaceProc();
			break;
			case L'#':
			AsciiCharProc();
			break;
			case L'$':
			IntegerProc();
			break;
			case L'\x27':
			StringProc();
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			NumberProc();
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
			case L'{':
			BraceOpenProc();
			break;
			case L'}':
			case L'!':
			case L'\"':
			case L'%':
			case L'&':
			case 40: case 41: case 42: case 43: case 44: case 45: case 46: case 47:
			case 58: case 59: case 60: case 61: case 62: case 63: case 64:
			case 91: case 92: case 93: case 94:
			case L'`':
			case L'~':
			{
				switch(fLine[Run])
				{
					case L'(':
					RoundOpenProc();
					break;
					case L'.':
					PointProc();
					break;
					case L';':
					SemicolonProc();
					break;
					case L'/':
					SlashProc();
					break;
					case L':':
					case L'>':
					ColonOrGreaterProc();
					break;
					case L'<':
					LowerProc();
					break;
					case L'@':
					AddressOpProc();
					break;
					default:
					SymbolProc();
					break;
				}
			}
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynSTSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynSTSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynSTSyn::GetTokenID()
{
	TtkTokenKind result = tkAsm;
	if(!fAsmStart && (fRange == rsAsm) && !(Synhighlighterst__5.Contains(FTokenID)))
		result = tkAsm;
	else
		result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynSTSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkAsm:
		result = fAsmAttri;
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

int __fastcall TSynSTSyn::GetTokenKind()
{
	int result = 0;
	result = int(GetTokenID());
	return result;
}

void* __fastcall TSynSTSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) fRange);
	return result;
}

void __fastcall TSynSTSyn::SetRange(void* Value)
{
	fRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynSTSyn::ResetRange()
{
	fRange = rsUnKnown;
}

/*#static*/
String __fastcall TSynSTSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangST;
	return result;
}

bool __fastcall TSynSTSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterST;
	return result;
}

/*#static*/
String __fastcall TSynSTSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangST;
	return result;
}

	static bool SynHighlighterST_Initialized = false;
	
	void SynHighlighterST_initialization()
	{
		if(SynHighlighterST_Initialized)
			return;
		
		SynHighlighterST_Initialized = true;
		
		RegisterPlaceableHighlighter(__classid(TSynSTSyn));
	}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterST

