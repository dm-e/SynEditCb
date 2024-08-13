
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterRC.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;

namespace Synhighlighterrc
{
#define Synhighlighterrc__0 (TFontStyles() << TFontStyle::fsBold)


const String Keywords[78/*# range 0..77*/] = {L"ACCELERATORS", L"ALT", L"ASCII", L"AUTO3STATE", L"AUTOCHECKBOX", L"AUTORADIOBUTTON", L"BITMAP", L"BLOCK"
																				, L"CAPTION", L"CHARACTERISTICS", L"CHECKBOX", L"CHECKED", L"CLASS", L"COMBOBOX", L"COMMENTS", L"COMPANYNAME", L"CONTROL"
																				, L"CTEXT", L"CURSOR", L"DEFPUSHBUTTON", L"DIALOG", L"DIALOGEX", L"DISCARDABLE", L"EDITTEXT", L"EXSTYLE", L"FILEDESCRIPTION", L"FILEFLAGS"
																				, L"FILEFLAGSMASK", L"FILEOS", L"FILESUBTYPE", L"FILETYPE", L"FILEVERSION", L"FIXED", L"FONT", L"GRAYED", L"GROUPBOX", L"HELP"
																				, L"ICON", L"IMPURE", L"INACTIVE", L"INTERNALNAME", L"LANGUAGE", L"LEGALCOPYRIGHT", L"LEGALTRADEMARKS", L"LISTBOX", L"LOADONCALL"
																				, L"LTEXT", L"MENU", L"MENUBARBREAK", L"MENUBREAK", L"MENUEX", L"MENUITEM", L"MESSAGETABLE", L"MOVEABLE", L"NOINVERT"
																				, L"ORIGINALFILENAME", L"POPUP", L"PRELOAD", L"PRIVATEBUILD", L"PRODUCTNAME", L"PRODUCTVERSION", L"PURE", L"PUSHBOX"
																				, L"PUSHBUTTON", L"RADIOBUTTON", L"RCDATA", L"RTEXT", L"SCROLLBAR", L"SEPARATOR", L"SHIFT", L"SPECIALBUILD", L"STATE3"
																				, L"STRINGTABLE", L"STYLE", L"VALUE", L"VERSION", L"VERSIONINFO", L"VIRTKEY"};
const int KeyIndices[241/*# range 0..240*/] = {-1, -1, -1, 35, -1, 57, 54, -1, -1, -1, 74, -1, -1, -1, 64, -1, -1, -1, -1, 9, 68, -1, 41, -1, -1, 10, -1, -1, 13, 24, -1, -1, -1, 42, -1, -1, -1, -1, -1, 61, -1, -1
																				, 20, 67, -1, -1, -1, -1, -1, -1, -1, -1, 2, -1, -1, 23, -1, -1, -1, -1, -1, 48, -1, 12, -1, -1, -1, -1, -1, -1, -1, 75, 73, 14, -1, 77, -1, 4, 63, -1, -1, -1, -1, 65, 19, 27, -1, 31, 38, -1, -1, -1, -1, -1
																				, 50, -1, -1, -1, 28, -1, -1, -1, -1, -1, -1, -1, 8, 6, 18, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 49, 76, -1, 59, -1, -1, 52, 47, 29, -1, -1, -1, -1, -1, -1, -1, 56, -1, -1, 44, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, 71, 17, 32, 34, -1, 45, -1, -1, -1, 70, -1, 3, -1, 62, 43, 5, -1, -1, 33, 0, 51, 16, 69, -1, -1, -1, 39, -1, -1, 7, -1, 11, -1, -1, -1, 21, -1, 40, -1, -1
																				, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 53, -1, 26, -1, 66, 25, -1, -1, 72, -1, -1, 60, 15, -1, -1, -1, -1, 55, -1, -1, -1, 30, -1, -1, -1, 46, -1, 58, -1, 37, 22, -1};

/* TSynRCSyn */

/*$Q-*/

unsigned int __fastcall TSynRCSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 25 + int((*Str)) * 298);
		++Str;
	}
	result = (unsigned int) (result % 241);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynRCSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 240 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynRCSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 240 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	for(stop = 240 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynRCSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRCSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynRCSyn::TSynRCSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fDirecAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr)
{
	FCaseSensitive = true;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	addAttribute(fCommentAttri);
	fDirecAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	addAttribute(fDirecAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterrc__0;
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
	fDefaultFilter = SYNS_FilterRC;
}

__fastcall TSynRCSyn::~TSynRCSyn()
{
	// inherited;
}

void __fastcall TSynRCSyn::QuoteProc()
{
	FTokenID = tkString;
	do
	{
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\x22')));
	if(fLine[Run] == L'\x22')
		++Run;
}

void __fastcall TSynRCSyn::SlashProc()
{
	switch(fLine[Run + 1])
	{
		case L'\x0d':
		CRProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'/':
		{
			FTokenID = tkComment;
			Run += 2;
			while(!IsLineEnd(Run))
				++Run;
		}
		break;
		case L'*':
		{
			FTokenID = tkComment;
			FRange = rsComment;
			Run += 2;
			while(fLine[Run] != L'\x00')
				switch(fLine[Run])
				{
					case L'*':
					if(fLine[Run + 1] == L'/')
					{
						Run += 2;
						FRange = rsUnKnown;
						goto label0;
					}
					else
					++Run;
					break;
					case L'\x0a':
					case L'\x0d':
					goto label1;
					default:
					++Run;
					break;
				}
			label0:;
			label1:;
		}
		break;
		default:
		FTokenID = tkSymbol;
		++Run;
		break;
	}
}

void __fastcall TSynRCSyn::CommentProc()
{
	FTokenID = tkComment;
	switch(fLine[Run])
	{
		case L'\x00':
		NullProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		case L'\x0a':
		LFProc();
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
			else
			++Run;
		}
		while(!IsLineEnd(Run));
		break;
	}
}

void __fastcall TSynRCSyn::DirectiveProc()
{
	FTokenID = tkDirective;
	do
	{
		if(fLine[Run] == L'/')
		{
			if(fLine[Run + 1] == L'/')
			{
				FRange = rsUnKnown;
				return;
			}
			else
			{
				if(fLine[Run + 1] == L'*')
				{
					FRange = rsComment;
					return;
				}
			}
		}
		++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynRCSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynRCSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynRCSyn::LFProc()
{
	++Run;
	FTokenID = tkSpace;
}

void __fastcall TSynRCSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynRCSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynRCSyn::NumberProc()
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
			case L'x':
			case L'X':
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			case L'L':
			case L'l':
			case L'-':
			case L'+':
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

void __fastcall TSynRCSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynRCSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynRCSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsDirective:
		DirectiveProc();
		break;
		case rsComment:
		CommentProc();
		break;
		default:
		switch(fLine[Run])
		{
			case L'\x00':
			NullProc();
			break;
			case L'\x0d':
			CRProc();
			break;
			case L'\x0a':
			LFProc();
			break;
			case L'/':
			SlashProc();
			break;
			case L'\"':
			QuoteProc();
			break;
			case L'#':
			DirectiveProc();
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
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			case L'\x0b':
			case L'\x0c':
			case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
			 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
			SpaceProc();
			break;
			case L'|':
			case L',':
			case L'{':
			case L'}':
			SymbolProc();
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynRCSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynRCSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynRCSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynRCSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynRCSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkDirective:
		result = fDirecAttri;
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

int __fastcall TSynRCSyn::GetTokenKind()
{
	int result = 0;
	result = int(GetTokenID());
	return result;
}

void __fastcall TSynRCSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynRCSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynRCSyn::EnumUserSettings(TStrings* Settings)
{

  // ** ??
}

bool __fastcall TSynRCSyn::UseUserSettings(int settingIndex)
{
	bool result = false;
	result = false;
	return result;
}

/*#static*/
TSynHighlighterCapabilities __fastcall TSynRCSyn::GetCapabilities()
{
	TSynHighlighterCapabilities result;
	result = inherited::GetCapabilities();
	return result;
}

bool __fastcall TSynRCSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterRC;
	return result;
}

/*#static*/
String __fastcall TSynRCSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangRC;
	return result;
}

String __fastcall TSynRCSyn::GetSampleSource()
{
	String result;
	result = L"";
	return result;
}

/*#static*/
String __fastcall TSynRCSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangRC;
	return result;
}
static bool SynHighlighterRC_Initialized = false;

void SynHighlighterRC_initialization()
{
	if(SynHighlighterRC_Initialized)
		return;
	
	SynHighlighterRC_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynRCSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterRC

