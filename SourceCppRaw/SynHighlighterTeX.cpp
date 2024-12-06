
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterTeX.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Synhighlightertex
{
#define Synhighlightertex__0 TFontStyles()
#define Synhighlightertex__1 TFontStyles()
#define Synhighlightertex__2 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightertex__3 TFontStyles()
#define Synhighlightertex__4 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightertex__5 TFontStyles()
#define Synhighlightertex__6 (TFontStyles() << TFontStyle::fsBold)



__fastcall TSynTeXSyn::TSynTeXSyn(TComponent* AOwner)
 : inherited(AOwner),
			fTokenID(tkBrace),
			fTextAttri(nullptr),
			fControlSequenceAttri(nullptr),
			fMathmodeAttri(nullptr),
			fCommentAttri(nullptr),
			fSpaceAttri(nullptr),
			fBracketAttri(nullptr),
			fBraceAttri(nullptr)
{
	fCommentAttri = CreateHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment, (TColor) clTeal, (TColor) clNone, Synhighlightertex__0);
	AddAttribute(fCommentAttri);
	fTextAttri = CreateHighlighterAttributes(SYNS_AttrText, SYNS_FriendlyAttrText, (TColor) clBlack, (TColor) clNone, Synhighlightertex__1);
	AddAttribute(fTextAttri);
	fMathmodeAttri = CreateHighlighterAttributes(SYNS_AttrMathMode, SYNS_FriendlyAttrMathMode, (TColor) clOlive, (TColor) clNone, Synhighlightertex__2);
	AddAttribute(fMathmodeAttri);
	fSpaceAttri = CreateHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace, (TColor) clNone, (TColor) clWhite, Synhighlightertex__3);
	AddAttribute(fSpaceAttri);
	fControlSequenceAttri = CreateHighlighterAttributes(SYNS_AttrTeXCommand, SYNS_FriendlyAttrTeXCommand, (TColor) clBlue, (TColor) clWhite, Synhighlightertex__4);
	AddAttribute(fControlSequenceAttri);
	fBracketAttri = CreateHighlighterAttributes(SYNS_AttrSquareBracket, SYNS_FriendlyAttrSquareBracket, (TColor) clPurple, (TColor) clNone, Synhighlightertex__5);
	AddAttribute(fBracketAttri);
	fBraceAttri = CreateHighlighterAttributes(SYNS_AttrRoundBracket, SYNS_FriendlyAttrRoundBracket, (TColor) clRed, (TColor) clNone, Synhighlightertex__6);
	AddAttribute(fBraceAttri);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterTeX;
}  /* Create */

void __fastcall TSynTeXSyn::CRProc()
{
	fTokenID = tkSpace;
	switch(fLine[Run + 1])
	{
		case L'\x0a':
		Run += 2;
		break;
		default:
		++Run;
		break;
	}
}  /* CRProc */

void __fastcall TSynTeXSyn::SpaceProc()
{
	fTokenID = tkSpace;
	++Run;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}  /* SpaceProc */

void __fastcall TSynTeXSyn::TextProc()
{
	fTokenID = tkText;
	++Run;
}  /* TextProc */

void __fastcall TSynTeXSyn::LFProc()
{
	fTokenID = tkSpace;
	++Run;
}  /* SpaceProc */

void __fastcall TSynTeXSyn::BraceOpenProc()
{
	fTokenID = tkBrace;
	++Run;
}  /* BraceOpen */

void __fastcall TSynTeXSyn::BraceCloseProc()
{
	fTokenID = tkBrace;
	++Run;
}  /* BraceClose */

void __fastcall TSynTeXSyn::BracketOpenProc()
{
	fTokenID = tkBracket;
	++Run;
}  /* BracketOpen */

void __fastcall TSynTeXSyn::BracketCloseProc()
{
	fTokenID = tkBracket;
	++Run;
}  /* BracketClose */

void __fastcall TSynTeXSyn::NullProc()
{
	fTokenID = tkNull;
	++Run;
}  /* NullProc */

void __fastcall TSynTeXSyn::CommentProc()
{
	fTokenID = tkComment;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			goto label0;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x0d'));
	label0:;
	return;
}  /* CommentProc */

void __fastcall TSynTeXSyn::MathmodeProc()
{
	fTokenID = tkMathMode;
	++Run;
}  /* MathModeProc */

void __fastcall TSynTeXSyn::ControlSequenceProc()
{
	fTokenID = tkControlSequence;
	do
	{
		switch(fLine[Run])
		{
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
			 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
			 case 30: case 31:
			goto label1;  //No Control Chars !
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			goto label2;  //No Numbers !
               //Just the Characters that
              //only can follow to '\'
			case 33: case 34: case 35: case 36: case 37: case 38: case 39: case 40: case 41: case 42:
			 case 43: case 44: case 45: case 46: case 47:
			case 58: case 59: case 60: case 61: case 62: case 63: case 64:
			case L'\x5b':
			case L'\x5d':
			case L'\x5e':
			case L'\x7b':
			case L'\x7d':
			case L'\x7e':
			{
				if(fLine[Run - 1] == L'\\')
					Run += 1;
				goto label3;
			}
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x20'));
	label1:;
	label2:;
	label3:;
	return;
}  /* ControlSequenceProc */

void __fastcall TSynTeXSyn::Next()
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
		case L'\x25':
		CommentProc();
		break;
		case L'\x5c':
		ControlSequenceProc();
		break;
		case L'\x7b':
		BraceOpenProc();
		break;
		case L'\x7d':
		BraceCloseProc();
		break;
		case L'\x5b':
		BracketOpenProc();
		break;
		case L'\x5d':
		BracketCloseProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'\x24':
		MathmodeProc();
		break;
		default:
		TextProc();
		break;
	}
	inherited::Next();
}  /* Next */

TSynHighlighterAttributes* __fastcall TSynTeXSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_COMMENT:
		result = fCommentAttri;
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

bool __fastcall TSynTeXSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}  /* GetDefaultAttribute */

TtkTokenKind __fastcall TSynTeXSyn::GetTokenID()
{
	TtkTokenKind result = tkBrace;
	result = fTokenID;
	return result;
}  /* GetTokenID */

TSynHighlighterAttributes* __fastcall TSynTeXSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(fTokenID)
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkText:
		result = fTextAttri;
		break;
		case tkControlSequence:
		result = fControlSequenceAttri;
		break;
		case tkMathMode:
		result = fMathmodeAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkBrace:
		result = fBraceAttri;
		break;
		case tkBracket:
		result = fBracketAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}  /* GetTokenAttribute */

int __fastcall TSynTeXSyn::GetTokenKind()
{
	int result = 0;
	result = int(fTokenID);
	return result;
}  /* GetTokenKind */

bool __fastcall TSynTeXSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterTeX;
	return result;
}

/*#static*/
String __fastcall TSynTeXSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangTeX;
	return result;
}  /* GetLanguageName */

TSynHighlighterAttributes* __fastcall TSynTeXSyn::CreateHighlighterAttributes(String Name, String FriendlyName, TColor Foreground, TColor Background, TFontStyles FontStyles)
{
	TSynHighlighterAttributes* result = nullptr;
	result = new TSynHighlighterAttributes(Name, FriendlyName);
	if(Foreground != clNone)
		result->Foreground = Foreground;
	if(Background != clNone)
		result->Background = Background;
	result->Style = FontStyles;
	return result;
}

String __fastcall TSynTeXSyn::GetSampleSource()
{
	String result;
	result = L"\\documentclass[a4paper]{article}"
	           L"\x0d\x0a"
	           L"% LaTeX sample source"
	           L"\x0d\x0a"
	           L"\\begin{document}"
	           L"\x0d\x0a"
	           L"Here is a formula: $ (2x + 3)*5y $"
	           L"\x0d\x0a"
	           L"\\end{document}";
	return result;
}

/*#static*/
String __fastcall TSynTeXSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangTeX;
	return result;
}

	static bool SynHighlighterTeX_Initialized = false;
	
	void SynHighlighterTeX_initialization()
	{
		if(SynHighlighterTeX_Initialized)
			return;
		
		SynHighlighterTeX_Initialized = true;
		
		RegisterPlaceableHighlighter(__classid(TSynTeXSyn));
	}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterTeX

