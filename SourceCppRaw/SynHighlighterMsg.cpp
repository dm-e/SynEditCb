
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterMsg.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Synhighlightermsg
{
#define SynHighlighterMsg__0 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterMsg__1 (TFontStyles() << TFontStyle::fsBold)


const String Keywords[7/*# range 0..6*/] = {L"beginproc", L"chars", L"enclosedby", L"endproc", L"keys", L"samplesource", L"tokentypes"};
const int KeyIndices[7/*# range 0..6*/] = {2, 1, 6, 4, 0, 5, 3};

/*$Q-*/

unsigned int __fastcall TSynMsgSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 182 + int((*Str)));
		++Str;
	}
	result = (unsigned int) (result % 7);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynMsgSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 6 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynMsgSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 6 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] ==  - 1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[4] = FuncBeginproc;
	fIdentFuncTable[1] = FuncChars;
	fIdentFuncTable[0] = FuncEnclosedby;
	fIdentFuncTable[6] = FuncEndproc;
	fIdentFuncTable[3] = FuncKeys;
	fIdentFuncTable[5] = FuncSamplesource;
	fIdentFuncTable[2] = FuncTokentypes;
}

TtkTokenKind __fastcall TSynMsgSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynMsgSyn::FuncBeginproc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynMsgSyn::FuncChars(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynMsgSyn::FuncEnclosedby(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynMsgSyn::FuncEndproc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynMsgSyn::FuncKeys(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynMsgSyn::FuncSamplesource(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynMsgSyn::FuncTokentypes(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynMsgSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynMsgSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynMsgSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynMsgSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynMsgSyn::BraceCommentOpenProc()
{
	++Run;
	FRange = rsBraceComment;
	BraceCommentProc();
	FTokenID = tkComment;
}

void __fastcall TSynMsgSyn::BraceCommentProc()
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
			if(fLine[Run] == L'}')
			{
				Run += 1;
				FRange = rsUnKnown;
				break;
			}
			if(!IsLineEnd(Run))
				++Run;
		}
		while(!IsLineEnd(Run));
		break;
	}
}

void __fastcall TSynMsgSyn::StringOpenProc()
{
	++Run;
	FRange = rsString;
	StringProc();
	FTokenID = tkString;
}

void __fastcall TSynMsgSyn::StringProc()
{
	FTokenID = tkString;
	do
	{
		if(fLine[Run] == L'\'')
		{
			Run += 1;
			FRange = rsUnKnown;
			break;
		}
		if(!IsLineEnd(Run))
			++Run;
	}
	while(!IsLineEnd(Run));
}

__fastcall TSynMsgSyn::TSynMsgSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fTerminatorAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = SynHighlighterMsg__0;
	fCommentAttri->Foreground = clNavy;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = SynHighlighterMsg__1;
	addAttribute(fKeyAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fTerminatorAttri = new TSynHighlighterAttributes(SYNS_AttrTerminator, SYNS_FriendlyAttrTerminator);
	addAttribute(fTerminatorAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterSynGenMsgfiles;
}

void __fastcall TSynMsgSyn::IdentProc()
{
	FTokenID = IdentKind(fLine + Run);
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynMsgSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynMsgSyn::TerminatorProc()
{
	++Run;
	if((fLine[Run] == L'>') && (fLine[Run + 1] == L'<') && (fLine[Run + 2] == L'|'))
	{
		FTokenID = tkTerminator;
		Run += 3;
	}
	else
	FTokenID = tkSymbol;
}

void __fastcall TSynMsgSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynMsgSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsBraceComment:
		BraceCommentProc();
		break;
		default:
		FRange = rsUnKnown;
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
			case L'{':
			BraceCommentOpenProc();
			break;
			case L'\'':
			StringOpenProc();
			break;
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			case L'\x0b':
			case L'\x0c':
			case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
			 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
			SpaceProc();
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
			case L'-':
			case L'+':
			case L'*':
			case L'/':
			case L'\\':
			case L',':
			case L'\"':
			case L'[':
			case L']':
			case L':':
			case L';':
			SymbolProc();
			break;
			case L'|':
			TerminatorProc();
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynMsgSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynMsgSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynMsgSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynMsgSyn::GetTokenAttribute()
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
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkTerminator:
		result = fTerminatorAttri;
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

int __fastcall TSynMsgSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

String __fastcall TSynMsgSyn::GetSampleSource()
{
	String result;
	result = L"TSynSampleSyn   {first identifier is the class name }\x0d\x0a"
	           L"tk              {second identifier is the prefix }\x0d\x0a"
	           L"IdentStart 'a'..'z':: 'a'..'z'::\x0d\x0a"
	           L"KEYS\x0d\x0a"
	           L"Sample\x0d\x0a"
	           L"Source\x0d\x0a"
	           L"|><|";
	return result;
}

bool __fastcall TSynMsgSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterSynGenMsgfiles;
	return result;
}

bool __fastcall TSynMsgSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'_':
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

/*#static*/
String __fastcall TSynMsgSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangSynGenMsgfiles;
	return result;
}

void __fastcall TSynMsgSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynMsgSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(int)Value;
}

void* __fastcall TSynMsgSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

/*#static*/
String __fastcall TSynMsgSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangSynGenMsgfiles;
	return result;
}
static bool SynHighlighterMsg_Initialized = false;

void SynHighlighterMsg_initialization()
{
	if(SynHighlighterMsg_Initialized)
		return;
	
	SynHighlighterMsg_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynMsgSyn));
}
class SynHighlighterMsg_unit
{
public:
	SynHighlighterMsg_unit()
	{
		SynHighlighterMsg_initialization();
	}
};

SynHighlighterMsg_unit _SynHighlighterMsg_unit;

}  // namespace SynHighlighterMsg

