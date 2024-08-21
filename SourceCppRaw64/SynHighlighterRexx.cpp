
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterRexx.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterrexx
{
#define Synhighlighterrexx__0 (TFontStyles() << TFontStyle::fsItalic)


const System::Char SYNS_FilterREXX[] = L"Rexx sources|*.REX|All files (*.*)|*.*";
const System::Char SYNS_LangREXX[] = L"REXX";
const System::Char SYNS_FriendlyLangREXX[] = L"REXX";
const System::Char SYNS_AttrSpecial[] = L"Special";
const System::Char SYNS_FriendlyAttrSpecial[] = L"Special";
const System::Char SYNS_AttrStdFunction[] = L"StdFunction";
const System::Char SYNS_FriendlyAttrStdFunction[] = L"StdFunction";
  // as this language is case-insensitive keywords *must* be in lowercase
const UnicodeString Keywords[99/*# range 0..98*/] = {L"abbrev", L"abs", L"address", L"arg", L"b2x", L"bitand", L"bitor", L"bitxor", L"c2d", L"c2x", L"call", L"center"
                    , L"centre", L"changestr", L"charin", L"charout", L"chars", L"compare", L"condition", L"copies", L"d2c", L"d2x", L"datatype", L"date"
                    , L"delstr", L"delword", L"digits", L"do", L"drop", L"else", L"end", L"errortext", L"exit", L"form", L"format", L"fuzz", L"if"
                    , L"insert", L"interpret", L"iterate", L"justify", L"lastpos", L"leave", L"left", L"length", L"linein", L"lineout", L"lines", L"linesize"
                    , L"max", L"min", L"nop", L"numeric", L"options", L"otherwise", L"overlay", L"parse", L"pos", L"procedure", L"pull", L"push"
                    , L"queue", L"queued", L"random", L"return", L"reverse", L"right", L"rxfuncadd", L"rxfuncdrop", L"rxfuncquery", L"say", L"select"
                    , L"signal", L"sourceline", L"space", L"stream", L"strip", L"substr", L"subword", L"symbol", L"then", L"time", L"trace", L"translate"
                    , L"trunc", L"upper", L"value", L"var", L"verify", L"when", L"word", L"wordindex", L"wordlength", L"wordpos", L"words", L"x2b"
                    , L"x2c", L"x2d", L"xrange"};
const int KeyIndices[349/*# range 0..348*/] = {-1, 26, -1, -1, -1, -1, -1, -1, -1, 6, -1, -1, 20, -1, 75, 0, -1, 98, -1, -1, 50, -1, 10, -1, -1, -1, -1, -1, 44, -1, -1, -1, -1, -1, -1, -1, 66, -1, -1, -1, 84, -1, -1
                    , -1, -1, 83, 13, 42, 39, -1, -1, 5, -1, -1, 49, -1, -1, -1, 87, -1, 1, -1, -1, -1, -1, -1, 65, -1, 12, 74, -1, 38, 29, -1, 82, -1, -1, -1, -1, -1, -1, -1, -1, -1, 80, 45, 68, 19, -1, -1, 63, -1, 67, -1, -1
                    , -1, -1, -1, -1, 33, -1, -1, -1, -1, -1, 72, -1, -1, 60, -1, -1, 18, -1, -1, -1, -1, -1, -1, -1, -1, 3, 23, -1, -1, 93, -1, -1, -1, -1, 47, 61, 30, -1, -1, -1, -1, -1, 14, -1, -1, -1, -1, -1, 9, -1, -1, -1
                    , -1, -1, 59, -1, -1, -1, -1, -1, -1, -1, -1, -1, 58, -1, 90, -1, -1, -1, 92, -1, -1, 37, -1, -1, -1, 8, -1, 41, -1, -1, 51, -1, -1, -1, -1, -1, -1, -1, -1, 79, -1, -1, -1, -1, -1, 86, 88, 78, -1, -1, -1
                    , -1, 56, -1, -1, -1, -1, 31, -1, -1, 7, -1, 46, 27, 22, -1, -1, -1, 73, -1, -1, -1, -1, 16, -1, 94, -1, -1, -1, -1, 43, -1, -1, -1, -1, 36, -1, -1, -1, -1, 48, -1, -1, 53, -1, -1, -1, 34, -1, -1, -1, -1
                    , -1, -1, -1, -1, 70, -1, -1, -1, 95, 24, -1, -1, -1, -1, -1, -1, 69, -1, 35, -1, -1, -1, 81, -1, 96, -1, -1, -1, -1, -1, 85, 62, -1, -1, 28, -1, -1, 57, 4, 15, 97, 77, -1, -1, -1, -1, -1, 17, -1, -1, -1
                    , -1, -1, 91, -1, -1, -1, 52, 71, 76, -1, 25, 55, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 64, -1, -1, 11, -1, -1, -1, -1, -1, 89, 54, -1, -1, -1, 40, -1, 32, 2, 21};

void __fastcall TSynRexxSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 348 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[15] = FuncAbbrev;
	fIdentFuncTable[60] = FuncAbs;
	fIdentFuncTable[347] = FuncAddress;
	fIdentFuncTable[120] = FuncArg;
	fIdentFuncTable[287] = FuncB2x;
	fIdentFuncTable[51] = FuncBitand;
	fIdentFuncTable[9] = FuncBitor;
	fIdentFuncTable[207] = FuncBitxor;
	fIdentFuncTable[172] = FuncC2d;
	fIdentFuncTable[143] = FuncC2x;
	fIdentFuncTable[22] = FuncCall;
	fIdentFuncTable[333] = FuncCenter;
	fIdentFuncTable[68] = FuncCentre;
	fIdentFuncTable[46] = FuncChangestr;
	fIdentFuncTable[137] = FuncCharin;
	fIdentFuncTable[288] = FuncCharout;
	fIdentFuncTable[220] = FuncChars;
	fIdentFuncTable[296] = FuncCompare;
	fIdentFuncTable[111] = FuncCondition;
	fIdentFuncTable[87] = FuncCopies;
	fIdentFuncTable[12] = FuncD2c;
	fIdentFuncTable[348] = FuncD2x;
	fIdentFuncTable[211] = FuncDatatype;
	fIdentFuncTable[121] = FuncDate;
	fIdentFuncTable[258] = FuncDelstr;
	fIdentFuncTable[310] = FuncDelword;
	fIdentFuncTable[1] = FuncDigits;
	fIdentFuncTable[210] = FuncDo;
	fIdentFuncTable[283] = FuncDrop;
	fIdentFuncTable[72] = FuncElse;
	fIdentFuncTable[131] = FuncEnd;
	fIdentFuncTable[204] = FuncErrortext;
	fIdentFuncTable[346] = FuncExit;
	fIdentFuncTable[99] = FuncForm;
	fIdentFuncTable[244] = FuncFormat;
	fIdentFuncTable[267] = FuncFuzz;
	fIdentFuncTable[232] = FuncIf;
	fIdentFuncTable[168] = FuncInsert;
	fIdentFuncTable[71] = FuncInterpret;
	fIdentFuncTable[48] = FuncIterate;
	fIdentFuncTable[344] = FuncJustify;
	fIdentFuncTable[174] = FuncLastpos;
	fIdentFuncTable[47] = FuncLeave;
	fIdentFuncTable[227] = FuncLeft;
	fIdentFuncTable[28] = FuncLength;
	fIdentFuncTable[85] = FuncLinein;
	fIdentFuncTable[209] = FuncLineout;
	fIdentFuncTable[129] = FuncLines;
	fIdentFuncTable[237] = FuncLinesize;
	fIdentFuncTable[54] = FuncMax;
	fIdentFuncTable[20] = FuncMin;
	fIdentFuncTable[177] = FuncNop;
	fIdentFuncTable[306] = FuncNumeric;
	fIdentFuncTable[240] = FuncOptions;
	fIdentFuncTable[340] = FuncOtherwise;
	fIdentFuncTable[311] = FuncOverlay;
	fIdentFuncTable[199] = FuncParse;
	fIdentFuncTable[286] = FuncPos;
	fIdentFuncTable[159] = FuncProcedure;
	fIdentFuncTable[149] = FuncPull;
	fIdentFuncTable[108] = FuncPush;
	fIdentFuncTable[130] = FuncQueue;
	fIdentFuncTable[280] = FuncQueued;
	fIdentFuncTable[90] = FuncRandom;
	fIdentFuncTable[330] = FuncReturn;
	fIdentFuncTable[66] = FuncReverse;
	fIdentFuncTable[36] = FuncRight;
	fIdentFuncTable[92] = FuncRxfuncadd;
	fIdentFuncTable[86] = FuncRxfuncdrop;
	fIdentFuncTable[265] = FuncRxfuncquery;
	fIdentFuncTable[253] = FuncSay;
	fIdentFuncTable[307] = FuncSelect;
	fIdentFuncTable[105] = FuncSignal;
	fIdentFuncTable[215] = FuncSourceline;
	fIdentFuncTable[69] = FuncSpace;
	fIdentFuncTable[14] = FuncStream;
	fIdentFuncTable[308] = FuncStrip;
	fIdentFuncTable[290] = FuncSubstr;
	fIdentFuncTable[194] = FuncSubword;
	fIdentFuncTable[186] = FuncSymbol;
	fIdentFuncTable[84] = FuncThen;
	fIdentFuncTable[271] = FuncTime;
	fIdentFuncTable[74] = FuncTrace;
	fIdentFuncTable[45] = FuncTranslate;
	fIdentFuncTable[40] = FuncTrunc;
	fIdentFuncTable[279] = FuncUpper;
	fIdentFuncTable[192] = FuncValue;
	fIdentFuncTable[58] = FuncVar;
	fIdentFuncTable[193] = FuncVerify;
	fIdentFuncTable[339] = FuncWhen;
	fIdentFuncTable[161] = FuncWord;
	fIdentFuncTable[302] = FuncWordindex;
	fIdentFuncTable[165] = FuncWordlength;
	fIdentFuncTable[124] = FuncWordpos;
	fIdentFuncTable[222] = FuncWords;
	fIdentFuncTable[257] = FuncX2b;
	fIdentFuncTable[273] = FuncX2c;
	fIdentFuncTable[289] = FuncX2d;
	fIdentFuncTable[17] = FuncXrange;
}

/*$Q-*/

unsigned int __fastcall TSynRexxSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 290 + int((*Str)) * 365);
		++Str;
	}
	result = (unsigned int) (result % 349);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynRexxSyn::FuncAbbrev(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncAbs(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncAddress(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncArg(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncB2x(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncBitand(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncBitor(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncBitxor(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncC2d(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncC2x(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncCall(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncCenter(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncCentre(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncChangestr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncCharin(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncCharout(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncChars(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncCompare(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncCondition(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncCopies(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncD2c(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncD2x(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncDatatype(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncDate(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncDelstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncDelword(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncDigits(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncDo(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncDrop(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncElse(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncEnd(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncErrortext(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncExit(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncForm(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncFormat(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncFuzz(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncIf(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncInsert(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncInterpret(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncIterate(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncJustify(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncLastpos(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncLeave(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncLeft(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncLength(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncLinein(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncLineout(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncLines(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncLinesize(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncMax(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncMin(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncNop(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncNumeric(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncOptions(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncOtherwise(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncOverlay(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncParse(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncPos(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncProcedure(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncPull(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncPush(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncQueue(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncQueued(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncRandom(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncReturn(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncReverse(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncRight(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncRxfuncadd(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncRxfuncdrop(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncRxfuncquery(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncSay(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncSelect(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncSignal(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncSourceline(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncSpace(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncStream(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncStrip(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncSubstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncSubword(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncSymbol(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncThen(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncTime(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncTrace(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncTranslate(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncTrunc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncUpper(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncValue(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncVar(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncVerify(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncWhen(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncWord(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncWordindex(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncWordlength(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncWordpos(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncWords(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncX2b(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncX2c(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncX2d(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::FuncXrange(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkStdFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 348 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynRexxSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynRexxSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynRexxSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynRexxSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynRexxSyn::MultilineCommentOpenProc()
{
	++Run;
	if(fLine[Run] == L'*')
	{
		Run += 1;
		FRange = rsMultilineComment;
		FTokenID = tkComment;
	}
	else
	FTokenID = tkIdentifier;
}

void __fastcall TSynRexxSyn::MultilineCommentProc()
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
				if((fLine[Run] == L'*') && (fLine[Run + 1] == L'/'))
				{
					Run += 2;
					FRange = rsUnKnown;
					break;
				}
				if(!IsLineEnd(Run))
					++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
	}
}

void __fastcall TSynRexxSyn::SinglelineCommentOpenProc()
{
	++Run;
	if(fLine[Run] == L'-')
	{
		Run += 1;
		FRange = rsSinglelineComment;
		SinglelineCommentProc();
		FTokenID = tkComment;
	}
	else
	FTokenID = tkIdentifier;
}

void __fastcall TSynRexxSyn::SinglelineCommentProc()
{
	FTokenID = tkComment;
	do
	{
		if((fLine[Run] == L'-') && (fLine[Run + 1] == L'-'))
		{
			Run += 2;
			FRange = rsUnKnown;
			break;
		}
		if(!IsLineEnd(Run))
			++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynRexxSyn::StringDoubleOpenProc()
{
	++Run;
	FRange = rsStringDouble;
	StringDoubleProc();
	FTokenID = tkString;
}

void __fastcall TSynRexxSyn::StringDoubleProc()
{
	FTokenID = tkString;
	do
	{
		if(fLine[Run] == L'\"')
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

void __fastcall TSynRexxSyn::StringSingleOpenProc()
{
	++Run;
	FRange = rsStringSingle;
	StringSingleProc();
	FTokenID = tkString;
}

void __fastcall TSynRexxSyn::StringSingleProc()
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

__fastcall TSynRexxSyn::TSynRexxSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fSpaceAttri(nullptr),
			fSpecialAttri(nullptr),
			fStdFunctionAttri(nullptr),
			fStringAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterrexx__0;
	fCommentAttri->Foreground = (TColor) 0x00EFBC89;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	fIdentifierAttri->Foreground = (TColor) clLime;
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Foreground = (TColor) 0x009797FF;
	addAttribute(fKeyAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fSpecialAttri = new TSynHighlighterAttributes(SYNS_AttrSpecial, SYNS_FriendlyAttrSpecial);
	fSpecialAttri->Foreground = (TColor) clAqua;
	addAttribute(fSpecialAttri);
	fStdFunctionAttri = new TSynHighlighterAttributes(SYNS_AttrStdFunction, SYNS_FriendlyAttrStdFunction);  /* new token type here */
	fStdFunctionAttri->Foreground = (TColor) clAqua;
	addAttribute(fStdFunctionAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = (TColor) 0x008CD959;
	fStringAttri->Background = (TColor) 0x00606060;
	addAttribute(fStringAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterREXX;
}

void __fastcall TSynRexxSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynRexxSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynRexxSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsMultilineComment:
		MultilineCommentProc();
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
			case L'/':
			MultilineCommentOpenProc();
			break;
			case L'-':
			SinglelineCommentOpenProc();
			break;
			case L'\"':
			StringDoubleOpenProc();
			break;
			case L'\'':
			StringSingleOpenProc();
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
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynRexxSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynRexxSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

UnicodeString __fastcall TSynRexxSyn::GetKeyWords(int TokenKind)
{
	UnicodeString result;
	result = L"ABBREV,ABS,ADDRESS,ARG,B2X,BITAND,BITOR,BITXOR,C2D,C2X,CALL,CENTER,CE"
	           L"NTRE,CHANGESTR,CHARIN,CHAROUT,CHARS,COMPARE,CONDITION,COPIES,D2C,D2X,D"
	           L"ATATYPE,DATE,DELSTR,DELWORD,DIGITS,DO,DROP,ELSE,END,ERRORTEXT,EXIT,FOR"
	           L"M,FORMAT,FUZZ,IF,INSERT,INTERPRET,ITERATE,JUSTIFY,LASTPOS,LEAVE,LEFT,L"
	           L"ENGTH,LINEIN,LINEOUT,LINES,LINESIZE,MAX,MIN,NOP,NUMERIC,OPTIONS,OTHERW"
	           L"ISE,OVERLAY,PARSE,POS,PROCEDURE,PULL,PUSH,QUEUE,QUEUED,RANDOM,RETURN,R"
	           L"EVERSE,RIGHT,RXFUNCADD,RXFUNCDROP,RXFUNCQUERY,SAY,SELECT,SIGNAL,SOURCE"
	           L"LINE,SPACE,STREAM,STRIP,SUBSTR,SUBWORD,SYMBOL,THEN,TIME,TRACE,TRANSLAT"
	           L"E,TRUNC,UPPER,VALUE,VAR,VERIFY,WHEN,WORD,WORDINDEX,WORDLENGTH,WORDPOS,"
	           L"WORDS,X2B,X2C,X2D,XRANGE";
	return result;
}

TtkTokenKind __fastcall TSynRexxSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynRexxSyn::GetTokenAttribute()
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
		case tkSpecial:
		result = fSpecialAttri;
		break;
		case tkStdFunction:
		result = fStdFunctionAttri;
		break;
		case tkString:
		result = fStringAttri;
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

int __fastcall TSynRexxSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

bool __fastcall TSynRexxSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'_':
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
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
}

UnicodeString __fastcall TSynRexxSyn::GetSampleSource()
{
	UnicodeString result;
	result = L"\x0d\x0a"
	           L"/* multiline comment */\x0d\x0a"
	           L"-- single line comment\x0d\x0a"
	           L"identifier = 12\x0d\x0a"
	           L"say identifier\x0d\x0a"
	           L"return(identifier)";
	return result;
}

bool __fastcall TSynRexxSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterREXX;
	return result;
}

/*#static*/
UnicodeString __fastcall TSynRexxSyn::GetFriendlyLanguageName()
{
	UnicodeString result;
	result = SYNS_FriendlyLangREXX;
	return result;
}

/*#static*/
String __fastcall TSynRexxSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangREXX;
	return result;
}

void __fastcall TSynRexxSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynRexxSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void* __fastcall TSynRexxSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}
static bool SynHighlighterRexx_Initialized = false;

void SynHighlighterRexx_initialization()
{
	if(SynHighlighterRexx_Initialized)
		return;
	
	SynHighlighterRexx_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynRexxSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterRexx

