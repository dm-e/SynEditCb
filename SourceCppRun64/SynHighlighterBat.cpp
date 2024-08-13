
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterBat.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterbat
{
#define Synhighlighterbat__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterbat__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterbat__2 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57 << '.')
#define Synhighlighterbat__3 (TSysCharSet() << 'E' << 'e')
#define Synhighlighterbat__4 (TSysCharSet() << 'M' << 'm')


const String Keywords[21/*# range 0..20*/] = {L"call", L"cd", L"cls", L"copy", L"del", L"do", L"echo", L"errorlevel", L"exist", L"for", L"goto", L"if", L"in"
																				, L"not", L"off", L"on", L"pause", L"set", L"shift", L"start", L"title"};
const int KeyIndices[25/*# range 0..24*/] = {14, 4, -1, 6, 17, 12, 8, 18, 19, 15, -1, -1, 10, 3, 13, 0, 1, 11, 20, 7, 2, 5, -1, 16, 9};

/*$Q-*/

unsigned int __fastcall TSynBatSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 869 + int((*Str)) * 61);
		++Str;
	}
	result = (unsigned int) (result % 25);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynBatSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 24 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynBatSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 24 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[15] = FuncCall;
	fIdentFuncTable[16] = FuncCd;
	fIdentFuncTable[20] = FuncCls;
	fIdentFuncTable[13] = FuncCopy;
	fIdentFuncTable[1] = FuncDel;
	fIdentFuncTable[21] = FuncDo;
	fIdentFuncTable[3] = FuncEcho;
	fIdentFuncTable[19] = FuncErrorlevel;
	fIdentFuncTable[6] = FuncExist;
	fIdentFuncTable[24] = FuncFor;
	fIdentFuncTable[12] = FuncGoto;
	fIdentFuncTable[17] = FuncIf;
	fIdentFuncTable[5] = FuncIn;
	fIdentFuncTable[14] = FuncNot;
	fIdentFuncTable[0] = FuncOff;
	fIdentFuncTable[9] = FuncOn;
	fIdentFuncTable[23] = FuncPause;
	fIdentFuncTable[4] = FuncSet;
	fIdentFuncTable[7] = FuncShift;
	fIdentFuncTable[8] = FuncStart;
	fIdentFuncTable[18] = FuncTitle;
}

TtkTokenKind __fastcall TSynBatSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncCall(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncCd(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncCls(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncCopy(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncDel(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncDo(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncEcho(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncErrorlevel(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncExist(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncFor(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncGoto(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncIf(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncIn(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncNot(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncOff(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncOn(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncPause(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncSet(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncShift(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncStart(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::FuncTitle(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynBatSyn::TSynBatSyn(TComponent* AOwner)
 : inherited(AOwner),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fVariableAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterbat__0;
	fCommentAttri->Foreground = clNavy;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrKey, SYNS_FriendlyAttrKey);
	fKeyAttri->Style = Synhighlighterbat__1;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = clBlue;
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fVariableAttri = new TSynHighlighterAttributes(SYNS_AttrVariable, SYNS_FriendlyAttrVariable);
	fVariableAttri->Foreground = clGreen;
	addAttribute(fVariableAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterBatch;
}

void __fastcall TSynBatSyn::VariableProc()
{

	auto IsVarChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case L'_':
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
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
	};
	FTokenID = tkVariable;
	do
	{
		++Run;
	}
	while(!!IsVarChar());
	if(fLine[Run] == L'%')
		++Run;
}

void __fastcall TSynBatSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynBatSyn::CommentProc()
{
	FTokenID = tkIdentifier;
	++Run;
	if(fLine[Run] == L':')
	{
		FTokenID = tkComment;
		do
		{
			++Run;
		}
		while(!IsLineEnd(Run));
	}
}

void __fastcall TSynBatSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynBatSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynBatSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynBatSyn::NumberProc()
{
	FTokenID = tkNumber;
	do
	{
		++Run;
	}
	while(!!CharInSet(fLine[Run], Synhighlighterbat__2));
}

void __fastcall TSynBatSyn::REMCommentProc()
{
	if(CharInSet(fLine[Run + 1], Synhighlighterbat__3) && CharInSet(fLine[Run + 2], Synhighlighterbat__4) && (fLine[Run + 3] < L'\x21'))
	{
		FTokenID = tkComment;
		Run += 3;
		while((fLine[Run] != L'\x00'))
		{
			switch(fLine[Run])
			{
				case L'\x0a':
				case L'\x0d':
				goto label0;
				default:
				  ;
				break;
			} /* case */
			++Run;
		} /* while */
		label0:;
	}
	else
	{
		FTokenID = tkIdentifier;
		IdentProc();
	}
}

void __fastcall TSynBatSyn::SpaceProc()
{
	FTokenID = tkSpace;
	do
	{
		++Run;
	}
	while(!((fLine[Run] > L'\x20') || IsLineEnd(Run)));
}

void __fastcall TSynBatSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynBatSyn::Next()
{
	fTokenPos = Run;
	switch(fLine[Run])
	{
		case L'%':
		VariableProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		case L':':
		CommentProc();
		break;
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81:
		case 83: case 84: case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113:
		case 115: case 116: case 117: case 118: case 119: case 120: case 121: case 122:
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
		case L'R':
		case L'r':
		REMCommentProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynBatSyn::GetDefaultAttribute(int Index)
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
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynBatSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynBatSyn::GetTokenAttribute()
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
		case tkUnknown:
		result = fIdentifierAttri;
		break;
		case tkVariable:
		result = fVariableAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

TtkTokenKind __fastcall TSynBatSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

int __fastcall TSynBatSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

bool __fastcall TSynBatSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterBatch;
	return result;
}

/*#static*/
String __fastcall TSynBatSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangBatch;
	return result;
}

String __fastcall TSynBatSyn::GetSampleSource()
{
	String result;
	result = L"rem MS-DOS batch file\x0d\x0a"
	           L"rem\x0d\x0a"
	           L"@echo off\x0d\x0a"
	           L"cls\x0d\x0a"
	           L"echo The command line is: %1 %2 %3 %4 %5\x0d\x0a"
	           L"rem\x0d\x0a"
	           L"rem now wait for the user ...\x0d\x0a"
	           L"pause\x0d\x0a"
	           L"copy c:\\*.pas d:\\\x0d\x0a"
	           L"if errorlevel 1 echo Error in copy action!";
	return result;
}

/*#static*/
String __fastcall TSynBatSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangBatch;
	return result;
}
static bool SynHighlighterBat_Initialized = false;

void SynHighlighterBat_initialization()
{
	if(SynHighlighterBat_Initialized)
		return;
	
	SynHighlighterBat_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynBatSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterBat

