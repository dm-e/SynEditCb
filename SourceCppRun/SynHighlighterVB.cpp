
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterVB.h"
#include "SynEditStrConst.h"
#include "SynEditDelphiInstances.hpp"
#include "d2c_syshelper.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Regularexpressions;

namespace Synhighlightervb
{
#define Synhighlightervb__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlightervb__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightervb__2 (TRegExOptions() << roIgnoreCase)
#define Synhighlightervb__3 (TRegExOptions() << roIgnoreCase)
#define Synhighlightervb__4 (TSysCharSet() << '=' << '>')


  /*added keywords: catch, try, import*/
const String Keywords[226/*# range 0..225*/] = {L"abs", L"and", L"appactivate", L"array", L"as", L"asc", L"atn", L"attribute", L"base", L"beep", L"begin", L"boolean"
                    , L"byref", L"byte", L"byval", L"call", L"case", L"catch", L"cbool", L"cbyte", L"ccur", L"cdate", L"cdbl", L"cint", L"circle", L"class"
                    , L"clear", L"clng", L"close", L"command", L"compare", L"const", L"cos", L"createobject", L"csng", L"cstr", L"curdir", L"currency"
                    , L"cvar", L"cverr", L"date", L"dateadd", L"datediff", L"datepart", L"dateserial", L"datevalue", L"ddb", L"deftype", L"dim"
                    , L"dir", L"do", L"doevents", L"double", L"each", L"else", L"elseif", L"empty", L"end", L"enum", L"environ", L"eof", L"eqv", L"erase"
                    , L"err", L"error", L"exit", L"exp", L"explicit", L"false", L"fileattr", L"filecopy", L"filedatetime", L"filelen", L"fix"
                    , L"for", L"form", L"format", L"freefile", L"friend", L"function", L"fv", L"get", L"getattr", L"getobject", L"gosub", L"goto", L"hex"
                    , L"hour", L"chdir", L"chdrive", L"chr", L"if", L"iif", L"imp", L"imports", L"input", L"instr", L"int", L"integer", L"ipmt", L"irr"
                    , L"is", L"isarray", L"isdate", L"isempty", L"iserror", L"ismissing", L"isnull", L"isnumeric", L"isobject", L"kill", L"lbound"
                    , L"lcase", L"left", L"len", L"let", L"line", L"loc", L"local", L"lock", L"lof", L"log", L"long", L"loop", L"lset", L"ltrim", L"me"
                    , L"mid", L"minute", L"mirr", L"mkdir", L"mod", L"module", L"month", L"msgbox", L"name", L"new", L"next", L"not", L"nothing", L"now"
                    , L"nper", L"npv", L"object", L"oct", L"on", L"open", L"option", L"or", L"pmt", L"ppmt", L"print", L"private", L"property", L"pset"
                    , L"public", L"put", L"pv", L"qbcolor", L"raise", L"randomize", L"rate", L"redim", L"rem", L"reset", L"resume", L"return", L"rgb"
                    , L"right", L"rmdir", L"rnd", L"rset", L"rtrim", L"second", L"seek", L"select", L"sendkeys", L"set", L"setattr", L"sgn", L"shell"
                    , L"sin", L"single", L"sln", L"space", L"spc", L"sqr", L"static", L"step", L"stop", L"str", L"strcomp", L"strconv", L"string", L"sub"
                    , L"switch", L"syd", L"system", L"tab", L"tan", L"then", L"time", L"timer", L"timeserial", L"timevalue", L"to", L"trim", L"true"
                    , L"try", L"typename", L"typeof", L"ubound", L"ucase", L"unlock", L"until", L"val", L"variant", L"vartype", L"version", L"weekday"
                    , L"wend", L"while", L"width", L"with", L"write", L"xor"};
const int KeyIndices[1511/*# range 0..1510*/] = {100, -1, -1, -1, -1, -1, -1, -1, 91, -1, -1, -1, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 7, -1, -1, -1, -1, 74, -1, -1, -1, 176
                    , -1, -1, 181, 146, 171, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, 184, 213, -1, -1, -1, 31, -1, -1, 145, -1, 28, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 141, -1
                    , -1, -1, -1, 203, 195, -1, -1, 159, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 225, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, 175, 211, -1, -1, -1, 186, -1, -1, 174, -1, -1, -1, -1, -1, -1, 149, -1, -1, -1, -1, 193, -1, 192, -1, -1, -1, -1, -1, -1, -1, -1, 180, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 169, -1, 131, -1, -1, -1, -1, -1, -1, 33, -1, 44, -1, 118, -1, -1, 54, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , 150, -1, -1, -1, -1, -1, -1, -1, -1, 183, -1, -1, -1, -1, 167, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 107, 57, -1, -1, 173, -1, -1, -1, -1, 38, -1, 139, -1, -1, -1, -1
                    , -1, -1, -1, -1, 185, -1, 125, -1, -1, -1, 201, -1, -1, -1, -1, 49, -1, -1, -1, -1, -1, -1, 161, 130, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, 119, -1, 36, -1, -1, -1, -1, 219, -1, -1, 114, -1
                    , -1, -1, 56, -1, -1, -1, -1, 103, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 23, 190, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 214, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 116, -1, -1, -1, -1, -1, -1, -1, -1, 177, -1, -1, -1, 18, 222, -1, -1, 94, -1, -1, -1, -1, -1, -1, -1, 202, -1, -1, -1, -1, -1, -1, -1, -1
                    , 188, -1, -1, -1, 223, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 47, -1, -1, -1, -1, -1, 3, 115, -1, -1, -1, -1, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, 143, -1, -1, -1, -1, -1, -1, 154, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 191, -1, -1, -1, -1, -1, -1, -1, -1, -1, 95, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, 67, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 200, 182
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 132, -1, 134, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 142, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, 217, -1, -1, -1, -1, -1, -1, 165, -1, -1, -1, -1, -1, 189, 72, 39, 187, -1, -1, -1, -1, -1, 194, 29, -1, -1, -1, 17, -1, -1, 84, 79, -1, -1, -1, 40, 37, -1, 71, -1, -1, 55, -1, -1, -1, -1
                    , -1, 75, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 166, -1, 80, 104, -1, -1, -1, 113, -1, -1, -1, -1, -1, 76, -1, -1, -1, 148, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 92, -1, -1, -1, -1
                    , -1, -1, 66, -1, -1, -1, 178, -1, -1, 147, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 24, -1, -1, -1, -1, 198, 48, -1, -1, -1, 197, 216, -1, -1, -1, -1, -1, -1, -1, 70, -1, -1, 123, -1, -1, 204, -1
                    , -1, -1, -1, -1, -1, 210, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 215, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, 126, -1, -1, -1, -1, 12, -1, -1, -1, -1, 220, -1
                    , 117, -1, -1, -1, -1, -1, 101, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 208, -1, -1, 22, 41, -1, -1, -1, -1, -1, 168, -1, 157, -1, -1, -1, -1, 162, -1, -1, -1, -1, -1, -1, -1, 34, -1, -1, -1, -1
                    , -1, -1, -1, 52, -1, -1, -1, -1, -1, -1, -1, 82, -1, 120, -1, 61, -1, -1, -1, -1, -1, -1, -1, -1, 163, -1, 6, 86, -1, -1, -1, 164, -1, 11, -1, -1, -1, -1, -1, -1, -1, -1, 27, -1, -1, -1, -1, 50, -1, -1
                    , -1, -1, 69, -1, -1, -1, -1, -1, -1, -1, 60, -1, -1, -1, -1, -1, 158, -1, 68, -1, -1, -1, -1, -1, 221, -1, -1, -1, -1, 64, -1, -1, -1, 83, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 42, -1, 179
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 35, -1, -1, -1, -1, -1, -1, -1, -1, 199, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 212, -1, 207, -1, -1, -1, -1
                    , -1, -1, 122, -1, -1, -1, 99, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 160, -1, -1, -1, -1, 30, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, 218, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 151, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 59, -1, -1, -1, -1, -1, -1, -1, -1, 144, -1, 53, -1, -1, -1, -1, -1, -1, 102, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 93, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 96, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 106, -1, -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, 135, -1, -1, -1, -1, -1, 156, -1, -1, 105, -1, -1, -1, -1, 133, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 43, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, 4, 20, -1, -1, -1, 155, -1, -1, -1, 170, -1, -1, -1, 2, -1, -1, -1
                    , -1, -1, 73, -1, -1, 65, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 97, 172, 89, -1, -1, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, 108, -1, -1, -1, 224, -1, -1, -1, -1, -1, 14, -1, -1, -1, 112
                    , -1, -1, -1, 127, -1, -1, 63, -1, -1, -1, 124, -1, 209, -1, -1, -1, 206, -1, -1, -1, -1, -1, -1, -1, 85, -1, -1, -1, -1, -1, 81, -1, -1, -1, -1, -1, -1, -1, -1, 121, -1, -1, -1, -1, 136, -1, -1
                    , -1, 51, -1, -1, -1, 58, -1, -1, 110, -1, -1, -1, -1, -1, -1, 45, -1, -1, -1, -1, -1, -1, -1, 88, -1, -1, -1, -1, 153, 62, -1, -1, -1, -1, -1, -1, 109, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 196, -1
                    , -1, -1, -1, 137, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 205, -1, -1, 26, -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, -1, -1, -1, 9, 152, -1
                    , 138, -1, -1, 128, 129, -1, -1, 78, -1, -1, -1, -1, -1, -1, 8, -1, -1, 90, 77, -1, -1, -1, -1, -1, 111, -1, 98, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 87, -1, -1, -1, -1};

/*$Q-*/

unsigned int __fastcall TSynVBSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 573 + int((*Str)) * 524);
		++Str;
	}
	result = (unsigned int) (result % 1511);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynVBSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkSymbol;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 1510 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynVBSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 1510 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[842] = FuncRem;
	for(stop = 1510 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynVBSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkSymbol;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynVBSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynVBSyn::FuncRem(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
	{
		ApostropheProc();
		fStringLen = 0;
		result = tkComment;
	}
	else
	result = tkIdentifier;
	return result;
}

__fastcall TSynVBSyn::TSynVBSyn(TComponent* AOwner)
 : inherited(AOwner),
			FTokenID(tkSymbol),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlightervb__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlightervb__1;
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
	fDefaultFilter = SYNS_FilterVisualBASIC;

//++ CodeFolding
	RE_BlockBegin = TRegEx(L"\\b(sub |function |private sub |private function |if |for |select case)\\b", Synhighlightervb__2);
	RE_BlockEnd = TRegEx(L"\\b(end sub|end function|end if|next|end select)\\b", Synhighlightervb__3);
//-- CodeFolding
}

//++ CodeFolding
const int FT_Standard = 1;  // begin end, class end, record end
const int FT_Comment = 11;
const int FT_CodeDeclaration = 16;
const int FT_CodeDeclarationWithBody = 17;
const int FT_Implementation = 18;

void __fastcall TSynVBSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	String CurLine;
	__int64 Line = 0;
	bool OK = false;

	auto BlockDelimiter = [&](int Line) -> bool 
	{
		bool result = false;
		int Index = 0;
		TMatchCollection mcb = {};
		TMatchCollection mce = {};
		TMatch Match = {};
		result = false;
		mcb = RE_BlockBegin.Matches(CurLine);
		if(mcb.Count > 0)
      // Char must have proper highlighting (ignore stuff inside comments...)
		{
			Index = mcb.Item[0].Index;
			if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Index) != fCommentAttri)
			{
				OK = false;
        // And ignore lines with both opening and closing chars in them
				for(int iFor0 = 0; iFor0 < RE_BlockEnd.Matches(CurLine).Count; iFor0++)
				{
					TMatch Match = RE_BlockEnd.Matches(CurLine).Item[iFor0];
					if(Match.Index > Index)
					{
						OK = true;
						break;
					}
				}
				if(!OK)
				{
					FoldRanges->StartFoldRange(Line + 1, FT_Standard);
					result = true;
				}
			}
		}
		else
		{
			mce = RE_BlockEnd.Matches(CurLine);
			if(mce.Count > 0)
			{
				Index = mce.Item[0].Index;
				if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Index) != fCommentAttri)
				{
					FoldRanges->StopFoldRange(Line + 1, FT_Standard);
					result = true;
				}
			}
		}
		return result;
	};

	auto FoldRegion = [&](int Line) -> bool 
	{
		bool result = false;
		String s;
		result = false;
		s = TrimLeft(CurLine);
		if(UpperCase(s.SubString(1, 7)) == L"#REGION")
		{
			FoldRanges->StartFoldRange(Line + 1, FoldRegionType);
			result = true;
		}
		else
		{
			if(UpperCase(s.SubString(1, 11)) == L"#END REGION")
			{
				FoldRanges->StopFoldRange(Line + 1, FoldRegionType);
				result = true;
			}
		}
		return result;
	};
	__int64 stop = 0;
	for(stop = ToLine, Line = FromLine; Line <= stop; Line++)
	{
    // Deal first with Multiline statements
		CurLine = LinesToScan->Strings[Line];

    // Skip empty lines
		if(CurLine == L"")
		{
			FoldRanges->NoFoldInfo((int) (Line + 1));
			continue;
		}

    // Find Fold regions
		if(FoldRegion((int) Line))
			continue;

    // Find begin or end  (Fold Type 1)
		if(!BlockDelimiter((int) Line))
			FoldRanges->NoFoldInfo((int) (Line + 1));
	} //for Line
}
/*
   Provide folding for procedures and functions included nested ones.
*/

void __fastcall TSynVBSyn::AdjustFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan)
{
	int i = 0;
	int j = 0;
	int SkipTo = 0;
	int ImplementationIndex = 0;
	TSynFoldRange FoldRange = {};
	TMatchCollection mc = {};
	int stop = 0;
	ImplementationIndex = -1;
	for(stop = 0, i = FoldRanges->Ranges->Count - 1; i >= stop; i--)
	{
		if(FoldRanges->Ranges->List[i].FoldType == FT_Implementation)
			ImplementationIndex = i;
		else
		{
			if(FoldRanges->Ranges->List[i].FoldType == FT_CodeDeclaration)
			{
				if(ImplementationIndex >= 0)
        // Code declaration in the Interface part of a unit
				{
					FoldRanges->Ranges->Delete(i);
					--ImplementationIndex;
					continue;
				}
      // Examine the following ranges
				SkipTo = 0;
				j = i + 1;
				while(j < FoldRanges->Ranges->Count)
				{
					FoldRange = FoldRanges->Ranges->List[j];
					++j;
					switch(FoldRange.FoldType)
					{
						case FT_CodeDeclarationWithBody:
          // Nested procedure or function
						{
							SkipTo = FoldRange.ToLine;
							continue;
						}
						break;
          // possibly begin end;
						case FT_Standard:
						if(FoldRange.ToLine <= SkipTo)
							continue;
						else
						{
							mc = RE_BlockBegin.Matches(LinesToScan->Strings[FoldRange.FromLine - 1]);
							if(mc.Count > 0)
							{
								if(d2c_system::TStringHelper(mc.Item[0].Value).ToLower() == L"begin")
                  // function or procedure followed by begin end block
                  // Adjust ToLine
								{
									FoldRanges->Ranges->List[i].ToLine = FoldRange.ToLine;
									FoldRanges->Ranges->List[i].FoldType = FT_CodeDeclarationWithBody;
									goto label0;
								}
								else

                  // class or record declaration follows, so
								{
									FoldRanges->Ranges->Delete(i);
									goto label1;
								}
							}
							else
							Assert(false, L"TSynVBSSyn.AdjustFoldRanges");
						}
						break;
						default:
						{
							if(FoldRange.ToLine <= SkipTo)
								continue;
							else

              // Otherwise delete
              // eg. function definitions within a class definition
							{
								FoldRanges->Ranges->Delete(i);
								break;
							}
						}
						break;
					}
				}
				label0:;
				label1:;
			}
		}
	}
	if(ImplementationIndex >= 0)
    // Looks better without it
    //FoldRanges.Ranges.List[ImplementationIndex].ToLine := LinesToScan.Count;
		FoldRanges->Ranges->Delete(ImplementationIndex);
}
//-- CodeFolding

void __fastcall TSynVBSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynVBSyn::ApostropheProc()
{
	FTokenID = tkComment;
	do
	{
		++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynVBSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynVBSyn::DateProc()
{
	FTokenID = tkString;
	do
	{
		if(IsLineEnd(Run))
			break;
		++Run;
	}
	while(!(fLine[Run] == L'#'));
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynVBSyn::GreaterProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynVBSyn::IdentProc()
{
	FTokenID = IdentKind(fLine + Run);
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynVBSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynVBSyn::LowerProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], Synhighlightervb__4))
		++Run;
}

void __fastcall TSynVBSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynVBSyn::NumberProc()
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
		++Run;
}

void __fastcall TSynVBSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynVBSyn::StringProc()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x22') && (fLine[Run + 2] == L'\x22'))
		Run += 2;
	do
	{
		if(IsLineEnd(Run))
			break;
		++Run;
	}
	while(!(fLine[Run] == L'\x22'));
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynVBSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynVBSyn::Next()
{
	fTokenPos = Run;
	switch(fLine[Run])
	{
		case L'&':
		SymbolProc();
		break;
		case L'\x27':
		ApostropheProc();
		break;
		case L'}':
		SymbolProc();
		break;
		case L'{':
		SymbolProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		case L':':
		SymbolProc();
		break;
		case L',':
		SymbolProc();
		break;
		case L'#':
		DateProc();
		break;
		case L'=':
		SymbolProc();
		break;
		case L'^':
		SymbolProc();
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
		SymbolProc();
		break;
		case L'\x00':
		NullProc();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		NumberProc();
		break;
		case L'+':
		SymbolProc();
		break;
		case L'.':
		SymbolProc();
		break;
		case L')':
		SymbolProc();
		break;
		case L'(':
		SymbolProc();
		break;
		case L';':
		SymbolProc();
		break;
		case L'/':
		SymbolProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'*':
		SymbolProc();
		break;
		case L'\x22':
		StringProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynVBSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynVBSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynVBSyn::GetTokenID()
{
	TtkTokenKind result = tkSymbol;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynVBSyn::GetTokenAttribute()
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

int __fastcall TSynVBSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

bool __fastcall TSynVBSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterVisualBASIC;
	return result;
}

/*#static*/
String __fastcall TSynVBSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangVisualBASIC;
	return result;
}

String __fastcall TSynVBSyn::GetSampleSource()
{
	String result;
	result = L"' Syntax highlighting\x0d\x0a"
	           L"Function PrintNumber\x0d\x0a"
	           L"  Dim Number\x0d\x0a"
	           L"  Dim X\x0d\x0a"
	           L"\x0d\x0a"
	           L"  Number = 123456\x0d\x0a"
	           L"  Response.Write \"The number is \" & number\x0d\x0a"
	           L"\x0d\x0a"
	           L"  For I = 0 To Number\x0d\x0a"
	           L"    X = X + &h4c\x0d\x0a"
	           L"    X = X - &o8\x0d\x0a"
	           L"    X = X + 1.0\x0d\x0a"
	           L"  Next\x0d\x0a"
	           L"\x0d\x0a"
	           L"  I = I + @;  ' illegal character\x0d\x0a"
	           L"End Function";
	return result;
}

/*#static*/
String __fastcall TSynVBSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangVisualBASIC;
	return result;
}
static bool SynHighlighterVB_Initialized = false;

void SynHighlighterVB_initialization()
{
	if(SynHighlighterVB_Initialized)
		return;
	
	SynHighlighterVB_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynVBSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterVB

