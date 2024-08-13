
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterLDraw.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterldraw
{
#define Synhighlighterldraw__0 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterldraw__1 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57 << '.')


const String Keywords[1/*# range 0..0*/] = {L"author"};
const int KeyIndices[2/*# range 0..1*/] = {-1, 0};

/*$Q-*/

unsigned int __fastcall TSynLDRSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = result + int((*Str));
		++Str;
	}
	result = (unsigned int) (result % 2);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynLDRSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkColor;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 1 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynLDRSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 1 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[1] = FuncAuthor;
}

TtkTokenKind __fastcall TSynLDRSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkColor;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynLDRSyn::FuncAuthor(int Index)
{
	TtkTokenKind result = tkColor;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynLDRSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynLDRSyn::CRProc()
{
	FTokenID = tkUnknown;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynLDRSyn::LFProc()
{
	FTokenID = tkUnknown;
	++Run;
}

__fastcall TSynLDRSyn::TSynLDRSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkColor),
			fColorAttri(nullptr),
			fCommentAttri(nullptr),
			fFirstTriAttri(nullptr),
			fFourthTriAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fLineAttri(nullptr),
			fOpLineAttri(nullptr),
			fQuadAttri(nullptr),
			fSecondTriAttri(nullptr),
			fThirdTriAttri(nullptr),
			fTriangleAttri(nullptr)
{
	fColorAttri = new TSynHighlighterAttributes(SYNS_AttrColor, SYNS_FriendlyAttrColor);
	fColorAttri->Foreground = clNavy;
	addAttribute(fColorAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Foreground = clBlue;
	addAttribute(fCommentAttri);
	fFirstTriAttri = new TSynHighlighterAttributes(SYNS_AttrFirstTri, SYNS_FriendlyAttrFirstTri);
	fFirstTriAttri->Foreground = (TColor) RGB(206, 111, 73);
	addAttribute(fFirstTriAttri);
	fFourthTriAttri = new TSynHighlighterAttributes(SYNS_AttrFourthTri, SYNS_FriendlyAttrFourthTri);
	fFourthTriAttri->Foreground = (TColor) RGB(54, 99, 12);
	addAttribute(fFourthTriAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterldraw__0;
	addAttribute(fKeyAttri);
	fLineAttri = new TSynHighlighterAttributes(SYNS_AttrLine, SYNS_FriendlyAttrLine);
	fLineAttri->Foreground = clBlack;
	addAttribute(fLineAttri);
	fOpLineAttri = new TSynHighlighterAttributes(SYNS_AttrOpLine, SYNS_FriendlyAttrOpLine);
	fOpLineAttri->Foreground = clBlack;
	addAttribute(fOpLineAttri);
	fQuadAttri = new TSynHighlighterAttributes(SYNS_AttrQuad, SYNS_FriendlyAttrQuad);
	fQuadAttri->Foreground = clRed;
	addAttribute(fQuadAttri);
	fSecondTriAttri = new TSynHighlighterAttributes(SYNS_AttrSecondTri, SYNS_FriendlyAttrSecondTri);
	fSecondTriAttri->Foreground = (TColor) RGB(54, 99, 12);
	addAttribute(fSecondTriAttri);
	fThirdTriAttri = new TSynHighlighterAttributes(SYNS_AttrThirdTri, SYNS_FriendlyAttrThirdTri);
	fThirdTriAttri->Foreground = (TColor) RGB(206, 111, 73);
	addAttribute(fThirdTriAttri);
	fTriangleAttri = new TSynHighlighterAttributes(SYNS_AttrTriangle, SYNS_FriendlyAttrTriangle);
	fTriangleAttri->Foreground = clBlack;
	addAttribute(fTriangleAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterLDraw;
}

WideChar __fastcall TSynLDRSyn::FirstChar(PWideChar DatLine)
{
	WideChar result = L'\0';
	int i = 0;
	i = 0;
	while(DatLine[i] == L' ')
		++i;
	result = DatLine[i];
	return result;
}

void __fastcall TSynLDRSyn::IdentProc()
{
	if(FirstChar(fLine) == L'0')
	{
		FTokenID = tkComment;
		while((fLine[Run] != L'\x0a') && (fLine[Run] != L'\x0d') && (fLine[Run] != L'\x00'))
			++Run;
	}
	else
	{
		FTokenID = IdentKind((fLine + Run));
		Run += fStringLen;
		while(IsIdentChar(fLine[Run]))
			++Run;
	}
}

void __fastcall TSynLDRSyn::Number1Proc()
{

	auto ArgNumber = [&](PWideChar DatLine) -> unsigned char 
	{
		unsigned char result = 0;
		int i = 0;
		bool B = false;
		i = 0;
		result = 0;
		B = false;
		while(i <= Run)
		{
			if(DatLine[i] == L' ')
			{
				++i;
				B = false;
			}
			else
			{
				if(!B)
					++result;
				B = true;
				++i;
			}
		}
		return result;
	};
	switch(ArgNumber(fLine))
	{
		case 1:
		{
			switch(fLine[Run])
			{
				case L'0':
				FTokenID = tkComment;
				break;
				case L'1':
				FTokenID = tkIdentifier;
				break;
				case L'2':
				FTokenID = tkLine;
				break;
				case L'3':
				FTokenID = tkTriangle;
				break;
				case L'4':
				FTokenID = tkQuad;
				break;
				case L'5':
				FTokenID = tkOpLine;
				break;
				default:
				  ;
				break;
			}
		}
		break;
		case 2:
		if(FirstChar(fLine) != L'0')
			FTokenID = tkColor;
		else
			FTokenID = tkComment;
		break;
		case 3: case 4: case 5:
		if(FirstChar(fLine) != L'0')
			FTokenID = tkFirstTri;
		else
			FTokenID = tkComment;
		break;
		case 6: case 7: case 8:
		if(FirstChar(fLine) != L'0')
			FTokenID = tkSecondTri;
		else
			FTokenID = tkComment;
		break;
		case 9: case 10: case 11:
		if(FirstChar(fLine) != L'0')
			FTokenID = tkThirdTri;
		else
			FTokenID = tkComment;
		break;
		case 12: case 13: case 14:
		if(FirstChar(fLine) != L'0')
			FTokenID = tkFourthTri;
		else
			FTokenID = tkComment;
		break;
		default:
		FTokenID = tkIdentifier;
		break;
	}
	while(CharInSet(fLine[Run], Synhighlighterldraw__1))
		++Run;
}

void __fastcall TSynLDRSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynLDRSyn::Next()
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
		Number1Proc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynLDRSyn::GetDefaultAttribute(int Index)
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
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynLDRSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

String __fastcall TSynLDRSyn::GetKeyWords(int TokenKind)
{
	String result;
	result = L"Author";
	return result;
}

TtkTokenKind __fastcall TSynLDRSyn::GetTokenID()
{
	TtkTokenKind result = tkColor;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynLDRSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkColor:
		result = fColorAttri;
		break;
		case tkComment:
		result = fCommentAttri;
		break;
		case tkFirstTri:
		result = fFirstTriAttri;
		break;
		case tkFourthTri:
		result = fFourthTriAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkLine:
		result = fLineAttri;
		break;
		case tkOpLine:
		result = fOpLineAttri;
		break;
		case tkQuad:
		result = fQuadAttri;
		break;
		case tkSecondTri:
		result = fSecondTriAttri;
		break;
		case tkThirdTri:
		result = fThirdTriAttri;
		break;
		case tkTriangle:
		result = fTriangleAttri;
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

int __fastcall TSynLDRSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

String __fastcall TSynLDRSyn::GetSampleSource()
{
	String result;
	result = L"\x0d\x0a"
	           L"Sample source for: \x0d\x0a"
	           L"Ldraw Parser/Highlighter\x0d\x0a"
	           L"0 Comment\x0d\x0a"
	           L"1 16 0 0 0 1 0 0 0 1 0 0 0 1 stud.dat\x0d\x0a"
	           L"2 16 0 0 0 1 1 1\x0d\x0a"
	           L"3 16 0 0 0 1 1 1 2 2 2\x0d\x0a"
	           L"4 16 0 0 0 1 1 1 2 2 2 3 3 3\x0d\x0a"
	           L"5 16 0 0 0 1 1 1 2 2 2 3 3 3";
	return result;
}

bool __fastcall TSynLDRSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterLDraw;
	return result;
}

bool __fastcall TSynLDRSyn::IsIdentChar(WideChar AChar)
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
String __fastcall TSynLDRSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangLDraw;
	return result;
}

void __fastcall TSynLDRSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynLDRSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void* __fastcall TSynLDRSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

/*#static*/
String __fastcall TSynLDRSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangLDraw;
	return result;
}
static bool SynHighlighterLDraw_Initialized = false;

void SynHighlighterLDraw_initialization()
{
	if(SynHighlighterLDraw_Initialized)
		return;
	
	SynHighlighterLDraw_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynLDRSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterLDraw

