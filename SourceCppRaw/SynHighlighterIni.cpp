
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterIni.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterini
{
#define Synhighlighterini__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterini__1 (TFontStyles() << TFontStyle::fsBold)



__fastcall TSynIniSyn::TSynIniSyn(TComponent* AOwner)
 : inherited(AOwner),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fTextAttri(nullptr),
			fSectionAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr)
{
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterini__0;
	fCommentAttri->Foreground = clGreen;
	addAttribute(fCommentAttri);
	fTextAttri = new TSynHighlighterAttributes(SYNS_AttrText, SYNS_FriendlyAttrText);
	addAttribute(fTextAttri);
	fSectionAttri = new TSynHighlighterAttributes(SYNS_AttrSection, SYNS_FriendlyAttrSection);
	fSectionAttri->Style = Synhighlighterini__1;
	addAttribute(fSectionAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrKey, SYNS_FriendlyAttrKey);
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
	fDefaultFilter = SYNS_FilterINI;
} /* Create */

void __fastcall TSynIniSyn::SectionOpenProc()
{

  // if it is not column 0 mark as tkText and get out of here
	if(Run > 0)
	{
		FTokenID = tkText;
		++Run;
		return;
	}

  // this is column 0 ok it is a Section
	FTokenID = tkSection;
	++Run;
	while(fLine[Run] != L'\x00')
		switch(fLine[Run])
		{
			case L']':
			{
				++Run;
				goto label0;
			}
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

void __fastcall TSynIniSyn::CRProc()
{
	FTokenID = tkSpace;
	switch(fLine[Run + 1])
	{
		case L'\x0a':
		Run += 2;
		break;
		default:
		++Run;
		break;
	}
}

void __fastcall TSynIniSyn::EqualProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynIniSyn::KeyProc()
{
	FTokenID = tkKey;
	++Run;
	while(fLine[Run] != L'\x00')
		switch(fLine[Run])
		{
			case L'=':
			goto label3;
			case L'\x0a':
			goto label4;
			case L'\x0d':
			goto label5;
			default:
			++Run;
			break;
		}
	label3:;
	label4:;
	label5:;
}

void __fastcall TSynIniSyn::TextProc()
{

	auto IsTextChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	if(Run == 0)
		KeyProc();
	else
	{
		FTokenID = tkText;
		++Run;
		while(fLine[Run] != L'\x00')
			if(IsTextChar())
				++Run;
			else
				break;
	}
}

void __fastcall TSynIniSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynIniSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynIniSyn::NumberProc()
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

	auto IsAlphaChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	if(Run == 0)
		KeyProc();
	else
	{
		++Run;
		FTokenID = tkNumber;
		while(IsNumberChar())
			++Run;
		if(IsAlphaChar())
			TextProc();
	}
}

// ;

void __fastcall TSynIniSyn::SemiColonProc()
{

  // if it is not column 0 mark as tkText and get out of here
	if(Run > 0)
	{
		FTokenID = tkText;
		++Run;
		return;
	}

  // this is column 0 ok it is a comment
	FTokenID = tkComment;
	++Run;
	while(fLine[Run] != L'\x00')
		switch(fLine[Run])
		{
			case L'\x0a':
			goto label6;
			case L'\x0d':
			goto label7;
			default:
			++Run;
			break;
		}
	label6:;
	label7:;
}

void __fastcall TSynIniSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

// ""

void __fastcall TSynIniSyn::StringProc()
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
			goto label8;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x22'));
	label8:;
	if(fLine[Run] != L'\x00')
		++Run;
}

// ''

void __fastcall TSynIniSyn::StringProc1()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x27') && (fLine[Run + 2] == L'\x27'))
		Run += 2;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label9;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x27'));
	label9:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynIniSyn::Next()
{
	fTokenPos = Run;
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
		case L'\x22':
		StringProc();
		break;
		case L'\x27':
		StringProc1();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		NumberProc();
		break;
		case L'\x3b':
		SemiColonProc();
		break;
		case L'\x3d':
		EqualProc();
		break;
		case L'\x5b':
		SectionOpenProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		default:
		TextProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynIniSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_COMMENT:
		result = fCommentAttri;
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

bool __fastcall TSynIniSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynIniSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynIniSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkText:
		result = fTextAttri;
		break;
		case tkSection:
		result = fSectionAttri;
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
		result = fTextAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynIniSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

bool __fastcall TSynIniSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterINI;
	return result;
}

/*#static*/
String __fastcall TSynIniSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangINI;
	return result;
}

String __fastcall TSynIniSyn::GetSampleSource()
{
	String result;
	result = L"; Syntax highlighting\x0d\x0a"
	           L"[Section]\x0d\x0a"
	           L"Key=value\x0d\x0a"
	           L"String=\"Arial\"\x0d\x0a"
	           L"Number=123456";
	return result;
}

/*#static*/
String __fastcall TSynIniSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangINI;
	return result;
}
static bool SynHighlighterIni_Initialized = false;

void SynHighlighterIni_initialization()
{
	if(SynHighlighterIni_Initialized)
		return;
	
	SynHighlighterIni_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynIniSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterIni

