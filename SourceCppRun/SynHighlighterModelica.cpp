
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterModelica.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Uitypes;

namespace Synhighlightermodelica
{
#define SynHighlighterModelica__0 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterModelica__1 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterModelica__2 (TSysCharSet() << L'=' << L'&')
#define SynHighlighterModelica__3 (TSysCharSet() << L'=' << L'-' << L'>')
#define SynHighlighterModelica__4 (TSysCharSet() << L'=' << L'|')
#define SynHighlighterModelica__5 (TSysCharSet() << L'=' << L'+')


const String Keywords[48/*# range 0..47*/] = {L"algorithm", L"and", L"annotation", L"assert", L"block", L"Boolean", L"class", L"connect", L"connector", L"constant"
																				, L"der", L"discrete", L"else", L"elseif", L"end", L"equation", L"extends", L"external", L"false", L"final", L"flow", L"for"
																				, L"function", L"if", L"in", L"input", L"Integer", L"loop", L"model", L"nondiscrete", L"not", L"or", L"output", L"package", L"parameter"
																				, L"partial", L"protected", L"public", L"Real", L"record", L"redeclare", L"replaceable", L"terminate", L"then", L"true"
																				, L"type", L"when", L"while"};
const int KeyIndices[97/*# range 0..96*/] = {-1, 8, 41, 46, -1, 21, -1, 30, 5, -1, 45, -1, -1, 23, 7, -1, -1, 17, 15, -1, -1, 10, -1, -1, -1, 3, -1, 18, -1, 28, -1, -1, 47, -1, -1, -1, -1, -1, 39, 16, 27, 25, -1, 4
																				, 22, -1, 43, -1, 37, 40, -1, -1, 31, -1, 42, -1, -1, 26, 14, 24, 44, -1, -1, -1, -1, 11, 33, 0, -1, -1, -1, -1, 36, 19, -1, 38, -1, 32, -1, -1, 29, -1, -1, -1, 6, 35, 12, 1, -1, -1, -1, 20, 34, -1, 13, 9, 2};

/*$Q-*/

unsigned int __fastcall TSynModelicaSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 598 + int((*Str)) * 127);
		++Str;
	}
	result = (unsigned int) (result % 97);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynModelicaSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 96 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynModelicaSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 96 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] ==  - 1)
			fIdentFuncTable[i] = AltFunc;
	}
	for(stop = 96 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynModelicaSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynModelicaSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynModelicaSyn::TSynModelicaSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fDirectiveAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr)
{
	FCaseSensitive = true;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = SynHighlighterModelica__0;
	addAttribute(fCommentAttri);
	fDirectiveAttri = new TSynHighlighterAttributes(SYNS_AttrDirective, SYNS_FriendlyAttrDirective);
	addAttribute(fDirectiveAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = SynHighlighterModelica__1;
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
	fDefaultFilter = SYNS_FilterModelica;
}

void __fastcall TSynModelicaSyn::AndSymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
	if(CharInSet(fLine[Run], SynHighlighterModelica__2))
		++Run;
}

void __fastcall TSynModelicaSyn::AsciiCharProc()
{
	FRange = rsString39;
	FTokenID = tkString;
	do
	{
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\x27')));
	if(fLine[Run] == L'\x27')
	{
		FRange = rsUnKnown;
		++Run;
	}
}

void __fastcall TSynModelicaSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynModelicaSyn::ColonProc()
{
	++Run;
	FTokenID = tkSymbol;
	if(fLine[Run] == L':')
		++Run;
}

void __fastcall TSynModelicaSyn::DirectiveProc()
{
	FTokenID = tkDirective;
	do
	{
		++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynModelicaSyn::GreaterProc()
{
	++Run;
	FTokenID = tkSymbol;
	switch(fLine[Run])
	{
		case L'=':
		++Run;
		break;
		case L'>':
		{
			++Run;
			if(fLine[Run] == L'=')
				++Run;
		}
		break;
		default:
		  ;
		break;
	}
}

void __fastcall TSynModelicaSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynModelicaSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynModelicaSyn::LowerProc()
{
	++Run;
	FTokenID = tkSymbol;
	switch(fLine[Run])
	{
		case L'=':
		++Run;
		break;
		case L'<':
		{
			++Run;
			if(fLine[Run] == L'=')
				++Run;
		}
		break;
		default:
		  ;
		break;
	}
}

void __fastcall TSynModelicaSyn::MinusProc()
{
	++Run;
	FTokenID = tkSymbol;
	if(CharInSet(fLine[Run], SynHighlighterModelica__3))
		++Run;
}

void __fastcall TSynModelicaSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynModelicaSyn::NumberProc()
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

void __fastcall TSynModelicaSyn::OrSymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
	if(CharInSet(fLine[Run], SynHighlighterModelica__4))
		++Run;
}

void __fastcall TSynModelicaSyn::PlusProc()
{
	++Run;
	FTokenID = tkSymbol;
	if(CharInSet(fLine[Run], SynHighlighterModelica__5))
		++Run;
}

void __fastcall TSynModelicaSyn::PointProc()
{
	++Run;
	FTokenID = tkSymbol;
	if((fLine[Run] == L'.') && (fLine[Run + 1] == L'.'))
		Run += 2;
}

void __fastcall TSynModelicaSyn::SlashProc()
{
	++Run;
	switch(fLine[Run])
	{
		case L'/':
		{
			FTokenID = tkComment;
			do
			{
				++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
		case L'*':
		{
			FRange = rsComment;
			++Run;
			if(IsLineEnd(Run))
				FTokenID = tkComment;
			else
				AnsiCProc();
		}
		break;
		default:
		FTokenID = tkSymbol;
		if(fLine[Run] == L'=')
			++Run;
		break;
	}
}

void __fastcall TSynModelicaSyn::SpaceProc()
{
	FTokenID = tkSpace;
	do
	{
		++Run;
	}
	while(!((fLine[Run] > L'\x20') || IsLineEnd(Run)));
}

void __fastcall TSynModelicaSyn::StringProc()
{
	FRange = rsString34;
	++Run;
	if(IsLineEnd(Run))
		FTokenID = tkString;
	else
		String34Proc();
}

void __fastcall TSynModelicaSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynModelicaSyn::SymbolProcWithEqual()
{
	++Run;
	FTokenID = tkSymbol;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynModelicaSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynModelicaSyn::AnsiCProc()
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
			if((fLine[Run] == L'*') && (fLine[Run + 1] == L'/'))
			{
				Run += 2;
				FRange = rsUnKnown;
				break;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
		break;
	}
}

void __fastcall TSynModelicaSyn::String39Proc()
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
		FTokenID = tkString;
		do
		{
			if(fLine[Run] == L'\x27')
			{
				++Run;
				FRange = rsUnKnown;
				break;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
		break;
	}
}

void __fastcall TSynModelicaSyn::String34Proc()
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
		FTokenID = tkString;
		do
		{
			switch(fLine[Run])
			{
				case L'\x22':
				{
					++Run;
					FRange = rsUnKnown;
					goto label1;
				}
				case L'\x5c':
				{
					++Run;
					if(fLine[Run] == L'\x22')
						++Run;
				}
				break;
				default:
				++Run;
				break;
			}
		}
		while(!IsLineEnd(Run));
		label1:;
		break;
	}
}

void __fastcall TSynModelicaSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsComment:
		AnsiCProc();
		break;
		case rsString39:
		String39Proc();
		break;
		case rsString34:
		String34Proc();
		break;
		default:
		FRange = rsUnKnown;
		switch(fLine[Run])
		{
			case L'&':
			AndSymbolProc();
			break;
			case L'\x27':
			AsciiCharProc();
			break;
			case L'\x0d':
			CRProc();
			break;
			case L':':
			ColonProc();
			break;
			case L'#':
			DirectiveProc();
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
			StringProc();
			break;
			case L'~':
			case L'[':
			case L']':
			case L'@':
			case L'{':
			case L'}':
			case L'(':
			case L')':
			case L';':
			case L',':
			SymbolProc();
			break;
			case L'*':
			case L'^':
			case L'=':
			case L'%':
			case L'!':
			SymbolProcWithEqual();
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynModelicaSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynModelicaSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynModelicaSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynModelicaSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynModelicaSyn::GetTokenAttribute()
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
		case tkUnknown:
		result = fIdentifierAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynModelicaSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynModelicaSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynModelicaSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(int)Value;
}

bool __fastcall TSynModelicaSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterModelica;
	return result;
}

/*#static*/
String __fastcall TSynModelicaSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangModelica;
	return result;
}

/*#static*/
String __fastcall TSynModelicaSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangModelica;
	return result;
}
static bool SynHighlighterModelica_Initialized = false;

void SynHighlighterModelica_initialization()
{
	if(SynHighlighterModelica_Initialized)
		return;
	
	SynHighlighterModelica_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynModelicaSyn));
}
class SynHighlighterModelica_unit
{
public:
	SynHighlighterModelica_unit()
	{
		SynHighlighterModelica_initialization();
	}
};

SynHighlighterModelica_unit _SynHighlighterModelica_unit;

}  // namespace SynHighlighterModelica

