
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterKix.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;

namespace Synhighlighterkix
{
#define Synhighlighterkix__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterkix__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterkix__2 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)


const String Keywords[169/*# range 0..168*/] = {L"addkey", L"addprinterconnection", L"addprogramgroup", L"addprogramitem", L"address", L"asc", L"at"
																				, L"backupeventlog", L"beep", L"big", L"box", L"break", L"call", L"case", L"cd", L"chr", L"cleareventlog", L"close", L"cls", L"color"
																				, L"comment", L"comparefiletimes", L"cookie1", L"copy", L"curdir", L"date", L"day", L"dectohex", L"del", L"delkey", L"delprinterconnection"
																				, L"delprogramgroup", L"delprogramitem", L"deltree", L"delvalue", L"dim", L"dir", L"display", L"do"
																				, L"domain", L"dos", L"else", L"endif", L"endselect", L"enumgroup", L"enumkey", L"enumlocalgroup", L"enumvalue", L"error", L"execute"
																				, L"exist", L"existkey", L"exit", L"expandenvironmentvars", L"flushkb", L"fullname", L"get", L"getdiskspace", L"getfileattr"
																				, L"getfilesize", L"getfiletime", L"getfileversion", L"gets", L"global", L"go", L"gosub", L"goto", L"homedir", L"homedrive"
																				, L"homeshr", L"hostname", L"if", L"ingroup", L"instr", L"inwin", L"ipaddress", L"kix", L"lanroot", L"lcase", L"ldomain", L"ldrive"
																				, L"len", L"lm", L"loadhive", L"loadkey", L"logevent", L"logoff", L"longhomedir", L"loop", L"lserver", L"ltrim", L"maxpwage", L"md"
																				, L"mdayno", L"messagebox", L"month", L"monthno", L"olecallfunc", L"olecallproc", L"olecreateobject", L"oleenumobject", L"olegetobject"
																				, L"olegetproperty", L"olegetsubobject", L"oleputproperty", L"olereleaseobject", L"open", L"password", L"play"
																				, L"primarygroup", L"priv", L"pwage", L"quit", L"ras", L"rd", L"readline", L"readprofilestring", L"readtype", L"readvalue", L"redirectoutput"
																				, L"return", L"rnd", L"rserver", L"rtrim", L"run", L"savekey", L"scriptdir", L"select", L"sendkeys", L"sendmessage", L"serror"
																				, L"set", L"setascii", L"setconsole", L"setdefaultprinter", L"setfileattr", L"setfocus", L"setl", L"setm", L"settime", L"setwallpaper"
																				, L"shell", L"showprogramgroup", L"shutdown", L"sid", L"site", L"sleep", L"small", L"srnd", L"startdir", L"substr", L"syslang"
																				, L"time", L"ucase", L"unloadhive", L"until", L"use", L"userid", L"userlang", L"val", L"wdayno", L"while", L"wksta", L"writeline"
																				, L"writeprofilestring", L"writevalue", L"wuserid", L"ydayno", L"year"};
const int KeyIndices[971/*# range 0..970*/] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 95, -1, -1, -1, -1, -1, -1, 10, -1, 29, 25, -1, -1, -1, 151, -1, -1, 22, -1, -1, -1, -1, -1, -1, -1, 64, -1, -1, 76, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 97, 135, -1, -1, -1, 89, -1, -1, -1, -1, -1, 48, -1, -1, -1, 164, -1, -1, -1, -1, -1, -1, -1, 52, -1, -1, -1, -1, -1, 153, -1, 17, -1, -1, -1, -1, -1, -1, -1
																				, 18, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 67, -1, -1, 101, -1, -1, -1, -1, -1, -1, 111, 159, -1, -1, -1, -1, -1, -1, -1, -1, 63, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1, 0, -1, -1, -1, -1, -1, 96, -1
																				, -1, 133, -1, -1, 117, 129, -1, -1, -1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 66, -1, -1, -1, -1, -1, -1, -1, -1, -1, 36, -1, -1, 88, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, -1, -1, -1, -1, -1, 150, -1, 72, -1, -1, -1, -1, -1, -1, 142, 94, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 80, 137, -1
																				, -1, 118, -1, -1, 112, -1, 85, -1, -1, -1, 2, -1, -1, -1, -1, -1, -1, 70, 30, -1, -1, -1, -1, -1, -1, -1, -1, 157, -1, 90, -1, 24, 91, -1, 131, -1, -1, -1, -1, -1, 147, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 43, -1, -1, -1, -1, -1, -1, -1, 161, -1, -1, -1, -1, -1, -1, 165, -1, -1, -1, -1, -1, -1, -1, 44, -1, -1, -1, -1, -1, -1, -1, 78, -1, -1, 127, 158, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 109, -1, -1, -1, 116, 100, -1, -1, -1, -1, -1, -1, -1, 119, -1, -1, -1, -1, -1, -1, -1, -1, 93, -1, -1, -1, -1, -1, -1, 41, 79, -1, 156
																				, -1, -1, 7, -1, -1, -1, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, 74, -1, -1, -1, -1, -1, -1, 81, -1, 31, -1, 148, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 39, -1, -1, -1, -1, -1, 32, -1, 121, -1, -1, 86
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 68, -1, -1, -1, 105, -1, -1, -1, -1, -1, -1, 33, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 138, -1, -1
																				, -1, -1, -1, -1, -1, -1, 61, -1, -1, -1, -1, -1, -1, -1, -1, 59, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 168, 160, -1, -1, -1, -1, -1, -1, -1, 26, -1, 14, -1, -1, 108, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 132, -1, -1, 50, -1, -1, 126, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 141, -1, -1, -1, -1, -1, -1, -1, 130, 84, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, 71, -1, -1, -1, -1, 45, 107, 13, -1, -1, -1, 65, -1, -1, -1, -1, 34, -1, -1, -1, -1, 143, -1, -1, -1, 128, -1, 73, 134, 27, -1, -1, -1, -1, -1, 120, -1, 57, -1, -1
																				, -1, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, 82, -1, -1, -1, -1, -1, -1, -1, -1, -1, 123, -1, -1, -1, -1, -1, -1, -1, 46, -1, -1, -1, -1, 49, -1, -1, -1, -1, -1, 54, 77, -1, -1, 98, -1, -1, -1, -1, -1
																				, 113, -1, -1, 104, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, 163, -1, 136, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6, -1, 19, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, 38, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, 102, -1, -1, 23, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, 92, -1, -1, -1, -1, -1, -1, -1, -1, 146, -1, -1, -1, -1, 103, -1, 99, -1, -1, -1, -1, -1, -1, -1, -1, -1, 140, -1, -1, -1, -1, 155, 56, 115, -1, -1, -1, -1, -1, -1, 162, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 125, -1, -1, -1, -1, 42, 58, -1, -1, -1, -1, -1, -1, -1, 167, -1, -1, -1, 87, -1, -1, -1, 53, -1, -1, -1, -1, -1, -1, -1, 47, -1, -1, -1, -1, 16, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, 35, 154, -1, 75, -1, 110, -1, 83, -1, -1, -1, -1, -1, 3, -1, -1, -1, -1, -1, 144, -1, -1, 8, -1, -1, -1, 114, -1, -1, -1, 152, -1, -1, -1, -1, 20, 145, 60, -1, -1, 28, -1, 55
																				, -1, -1, -1, -1, -1, 124, -1, -1, -1, -1, 106, -1, -1, -1, -1, 139, -1, -1, -1, 69, -1, -1, 122, 166, -1, 62, 149, 21, 37, -1, -1, -1, -1, 40, -1, -1, -1, -1, -1, -1, -1};

/*$Q-*/

unsigned int __fastcall TSynKixSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 949 + int((*Str)) * 246);
		++Str;
	}
	result = (unsigned int) (result % 971);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynKixSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 970 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynKixSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 970 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	for(stop = 970 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynKixSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynKixSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynKixSyn::TSynKixSyn(TComponent* AOwner)
 : inherited(AOwner),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fMiscellaneousAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fVariableAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterkix__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrKey, SYNS_FriendlyAttrKey);
	fKeyAttri->Style = Synhighlighterkix__1;
	addAttribute(fKeyAttri);
	fMiscellaneousAttri = new TSynHighlighterAttributes(SYNS_AttrMiscellaneous, SYNS_FriendlyAttrMiscellaneous);
	addAttribute(fMiscellaneousAttri);
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
	fDefaultFilter = SYNS_FilterKIX;
}

void __fastcall TSynKixSyn::AsciiCharProc()
{
	FTokenID = tkString;
	++Run;
	while(CharInSet(fLine[Run], Synhighlighterkix__2))
		++Run;
}

void __fastcall TSynKixSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynKixSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynKixSyn::MacroProc()
{

	auto IsMacroChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
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
	++Run;
	FTokenID = tkMiscellaneous;
	while(IsMacroChar())
		++Run;
}

void __fastcall TSynKixSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynKixSyn::PrintProc()
{
	FTokenID = tkKey;
	++Run;
}

void __fastcall TSynKixSyn::VariableProc()
{
	FTokenID = tkVariable;
	++Run;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynKixSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynKixSyn::NumberProc()
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

void __fastcall TSynKixSyn::CommentProc()
{
	FTokenID = tkComment;
	do
	{
		++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynKixSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynKixSyn::StringProc()
{
	WideChar C = L'\0';
	FTokenID = tkString;
	C = fLine[Run];
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
	while(!(fLine[Run] == C));
	label1:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynKixSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynKixSyn::Next()
{
	fTokenPos = Run;
	switch(fLine[Run])
	{
		case L'#':
		AsciiCharProc();
		break;
		case L'\x0d':
		CRProc();
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
		case L';':
		CommentProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'\"':
		case L'\'':
		StringProc();
		break;
		case L'@':
		MacroProc();
		break;
		case L'?':
		PrintProc();
		break;
		case L'$':
		VariableProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynKixSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynKixSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynKixSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynKixSyn::GetTokenAttribute()
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
		case tkMiscellaneous:
		result = fMiscellaneousAttri;
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

int __fastcall TSynKixSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

/*#static*/
String __fastcall TSynKixSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangKIX;
	return result;
}

bool __fastcall TSynKixSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterKIX;
	return result;
}

String __fastcall TSynKixSyn::GetSampleSource()
{
	String result;
	result = L"; KiXtart sample source\x0d\x0a"
	           L"break on\x0d\x0a"
	           L"color b/n\x0d\x0a"
	           L"\x0d\x0a"
	           L"AT(1, 30) \"Hello World!\"\x0d\x0a"
	           L"$USERID = @USERID\x0d\x0a"
	           L"AT(1, 30) $USERID";
	return result;
}

/*#static*/
String __fastcall TSynKixSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangKIX;
	return result;
}
static bool SynHighlighterKix_Initialized = false;

void SynHighlighterKix_initialization()
{
	if(SynHighlighterKix_Initialized)
		return;
	
	SynHighlighterKix_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynKixSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterKix

