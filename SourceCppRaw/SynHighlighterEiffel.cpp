
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterEiffel.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlightereiffel
{
#define Synhighlightereiffel__0 (TSysCharSet() <<  \
										35 << 36 << 37 << 38 << 39 << 40 <<  \
										41 << 42 << 43 << 44)
#define Synhighlightereiffel__1 (TSysCharSet() <<  \
										46 << 47)
#define Synhighlightereiffel__2 (TSysCharSet() <<  \
										58 << 59 << 60 << 61 << 62 << 63 <<  \
										64)
#define Synhighlightereiffel__3 (TSysCharSet() <<  \
										91 << 92 << 93 << 94 << 95 << 96)
#define Synhighlightereiffel__4 (TSysCharSet() <<  \
										123 << 124 << 125 << 126 << 127)
#define Synhighlightereiffel__5 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightereiffel__6 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlightereiffel__7 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightereiffel__8 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightereiffel__9 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightereiffel__10 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightereiffel__11 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightereiffel__12 (TFontStyles() << TFontStyle::fsItalic)


const String KeyWords[119/*# range 0..118*/] = {L"-", L"!", L"#", L"$", L"%u", L"&", L"(", L")", L"*", L".", L"/", L"//", L"/=", L":", L":=", L";", L"@", L"[", L"\\\\", L"]"
                    , L"^", L"|", L"+", L"<", L"<>", L"=", L">", L"adapt", L"alias", L"all", L"and", L"array", L"as", L"assertion", L"bit", L"boolean", L"character"
                    , L"check", L"class", L"cluster", L"colon", L"comma", L"creation", L"current", L"debug", L"default", L"deferred", L"do"
                    , L"double", L"else", L"elseif", L"end", L"ensure", L"exclude", L"executable", L"expanded", L"export", L"external", L"false", L"feature"
                    , L"from", L"frozen", L"generate", L"identifier", L"if", L"ignore", L"implies", L"include", L"include_path", L"indexing", L"infix"
                    , L"inherit", L"inspect", L"integer", L"invariant", L"is", L"like", L"local", L"loop", L"make", L"no", L"not", L"object", L"obsolete"
                    , L"old", L"once", L"optimize", L"option", L"or", L"pointer", L"precompiled", L"precursor", L"prefix", L"real", L"redefine"
                    , L"rename", L"require", L"rescue", L"result", L"retry", L"root", L"select", L"separate", L"string", L"strip", L"system", L"then"
                    , L"trace", L"true", L"undefine", L"unique", L"until", L"use", L"variant", L"visible", L"void", L"when", L"xor", L"yes"};
const int KeyIndices[503/*# range 0..502*/] = {-1, 49, -1, -1, -1, 97, 69, 85, -1, -1, -1, 106, -1, -1, 37, -1, -1, 63, -1, 92, -1, -1, -1, -1, 108, 82, 16, -1, -1, -1, -1, -1, 86, -1, 0, -1, -1, 66, -1, -1, -1
                    , -1, 91, 98, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 30, 13, -1, -1, -1, -1, -1, -1, -1, 61, -1, -1, -1, -1, -1, -1, -1, 76, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 58, -1, -1, -1, -1, 110, -1
                    , 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 31, -1, -1, -1, -1, -1, -1, -1, 9, -1, -1, -1, -1, -1, -1, 68, 88, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, 105, -1, -1, -1, 51, -1, -1, 6
                    , -1, 96, -1, -1, 17, -1, -1, 55, -1, -1, -1, -1, -1, 117, -1, -1, -1, 77, -1, -1, -1, -1, -1, -1, 56, -1, -1, -1, -1, 62, -1, 59, -1, -1, -1, -1, -1, -1, 79, -1, -1, -1, -1, -1, -1, -1, -1, -1, 83, 10, 95
                    , -1, 113, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 65, 18, 23, -1, -1, -1, 35, -1, -1, -1, 7, -1, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21, 90, -1, 103, -1
                    , -1, 80, -1, -1, -1, -1, 2, -1, 34, -1, -1, -1, -1, -1, -1, 41, -1, 27, 112, -1, -1, -1, 33, -1, 44, -1, 50, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 104, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, -1
                    , -1, -1, 93, -1, -1, -1, 8, 46, 102, -1, -1, 19, 87, -1, -1, -1, -1, 43, -1, -1, -1, -1, -1, -1, -1, 84, 53, -1, -1, -1, 71, -1, -1, 11, -1, 3, 107, 67, -1, 64, 47, -1, -1, -1, -1, -1, 24, -1, -1, -1, 114
                    , -1, -1, -1, 116, -1, -1, -1, -1, 81, 75, -1, -1, -1, -1, -1, -1, -1, 100, -1, -1, -1, -1, -1, 54, -1, -1, 26, 115, -1, -1, -1, -1, -1, 78, 22, 36, -1, 74, -1, 20, -1, -1, 42, -1, 99, -1, -1, -1, -1
                    , -1, -1, -1, 73, -1, 52, -1, -1, 29, -1, -1, -1, -1, -1, -1, -1, -1, 60, -1, 4, 94, -1, -1, 40, -1, -1, 39, -1, -1, -1, -1, 45, -1, 12, -1, -1, -1, 72, 38, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, 109, -1, -1, -1, -1, -1, -1, -1, -1, -1, 28, 48, -1, -1, -1, -1, -1, 101, -1, 118, -1, -1, 57, -1, -1, -1, -1, -1, 14, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1
                    , -1, 70, -1, 89, -1, -1, 111, -1};

/*$Q-*/

unsigned int __fastcall TSynEiffelSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)) || IsOperatorChar((*Str)))
	{
		result = (unsigned int) (result * 543 + int((*Str)) * 79);
		++Str;
	}
	result = (unsigned int) (result % 503);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynEiffelSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkBasicTypes;
	unsigned int Key = 0;
	fToIdent = MayBe;
	Key = HashKey(MayBe);
	if(Key <= 502 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[Key](KeyIndices[Key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynEiffelSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 502 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[34] = OperatorFunc;
	fIdentFuncTable[92] = OperatorFunc;
	fIdentFuncTable[250] = OperatorFunc;
	fIdentFuncTable[329] = OperatorFunc;
	fIdentFuncTable[413] = Func37u;
	fIdentFuncTable[487] = OperatorFunc;
	fIdentFuncTable[142] = OperatorFunc;
	fIdentFuncTable[221] = OperatorFunc;
	fIdentFuncTable[300] = OperatorFunc;
	fIdentFuncTable[113] = OperatorFunc;
	fIdentFuncTable[192] = OperatorFunc;
	fIdentFuncTable[327] = OperatorFunc;
	fIdentFuncTable[427] = OperatorFunc;
	fIdentFuncTable[55] = OperatorFunc;
	fIdentFuncTable[480] = OperatorFunc;
	fIdentFuncTable[134] = OperatorFunc;
	fIdentFuncTable[26] = OperatorFunc;
	fIdentFuncTable[147] = OperatorFunc;
	fIdentFuncTable[212] = OperatorFunc;
	fIdentFuncTable[305] = OperatorFunc;
	fIdentFuncTable[384] = OperatorFunc;
	fIdentFuncTable[239] = OperatorFunc;
	fIdentFuncTable[379] = OperatorFunc;
	fIdentFuncTable[213] = OperatorFunc;
	fIdentFuncTable[340] = OperatorFunc;
	fIdentFuncTable[292] = OperatorFunc;
	fIdentFuncTable[371] = OperatorFunc;
	fIdentFuncTable[261] = FuncAdapt;
	fIdentFuncTable[462] = FuncAlias;
	fIdentFuncTable[402] = FuncAll;
	fIdentFuncTable[54] = FuncAnd;
	fIdentFuncTable[105] = FuncArray;
	fIdentFuncTable[224] = FuncAs;
	fIdentFuncTable[266] = FuncAssertion;
	fIdentFuncTable[252] = FuncBit;
	fIdentFuncTable[217] = FuncBoolean;
	fIdentFuncTable[380] = FuncCharacter;
	fIdentFuncTable[14] = FuncCheck;
	fIdentFuncTable[432] = FuncClass;
	fIdentFuncTable[420] = FuncCluster;
	fIdentFuncTable[417] = FuncColon;
	fIdentFuncTable[259] = FuncComma;
	fIdentFuncTable[387] = FuncCreation;
	fIdentFuncTable[311] = FuncCurrent;
	fIdentFuncTable[268] = FuncDebug;
	fIdentFuncTable[425] = FuncDefault;
	fIdentFuncTable[301] = FuncDeferred;
	fIdentFuncTable[334] = FuncDo;
	fIdentFuncTable[463] = FuncDouble;
	fIdentFuncTable[1] = FuncElse;
	fIdentFuncTable[270] = FuncElseif;
	fIdentFuncTable[139] = FuncEnd;
	fIdentFuncTable[399] = FuncEnsure;
	fIdentFuncTable[320] = FuncExclude;
	fIdentFuncTable[368] = FuncExecutable;
	fIdentFuncTable[150] = FuncExpanded;
	fIdentFuncTable[167] = FuncExport;
	fIdentFuncTable[474] = FuncExternal;
	fIdentFuncTable[85] = FuncFalse;
	fIdentFuncTable[174] = FuncFeature;
	fIdentFuncTable[411] = FuncFrom;
	fIdentFuncTable[63] = FuncFrozen;
	fIdentFuncTable[172] = FuncGenerate;
	fIdentFuncTable[17] = FuncIdentifier;
	fIdentFuncTable[333] = FuncIf;
	fIdentFuncTable[211] = FuncIgnore;
	fIdentFuncTable[37] = FuncImplies;
	fIdentFuncTable[331] = FuncInclude;
	fIdentFuncTable[120] = FuncInclude95path;
	fIdentFuncTable[6] = FuncIndexing;
	fIdentFuncTable[496] = FuncInfix;
	fIdentFuncTable[324] = FuncInherit;
	fIdentFuncTable[431] = FuncInspect;
	fIdentFuncTable[397] = FuncInteger;
	fIdentFuncTable[382] = FuncInvariant;
	fIdentFuncTable[354] = FuncIs;
	fIdentFuncTable[71] = FuncLike;
	fIdentFuncTable[160] = FuncLocal;
	fIdentFuncTable[378] = FuncLoop;
	fIdentFuncTable[181] = FuncMake;
	fIdentFuncTable[245] = FuncNo;
	fIdentFuncTable[353] = FuncNot;
	fIdentFuncTable[25] = FuncObject;
	fIdentFuncTable[191] = FuncObsolete;
	fIdentFuncTable[319] = FuncOld;
	fIdentFuncTable[7] = FuncOnce;
	fIdentFuncTable[32] = FuncOptimize;
	fIdentFuncTable[306] = FuncOption;
	fIdentFuncTable[121] = FuncOr;
	fIdentFuncTable[498] = FuncPointer;
	fIdentFuncTable[240] = FuncPrecompiled;
	fIdentFuncTable[42] = FuncPrecursor;
	fIdentFuncTable[19] = FuncPrefix;
	fIdentFuncTable[296] = FuncReal;
	fIdentFuncTable[414] = FuncRedefine;
	fIdentFuncTable[193] = FuncRename;
	fIdentFuncTable[144] = FuncRequire;
	fIdentFuncTable[5] = FuncRescue;
	fIdentFuncTable[43] = FuncResult;
	fIdentFuncTable[389] = FuncRetry;
	fIdentFuncTable[362] = FuncRoot;
	fIdentFuncTable[469] = FuncSelect;
	fIdentFuncTable[302] = FuncSeparate;
	fIdentFuncTable[242] = FuncString;
	fIdentFuncTable[282] = FuncStrip;
	fIdentFuncTable[135] = FuncSystem;
	fIdentFuncTable[11] = FuncThen;
	fIdentFuncTable[330] = FuncTrace;
	fIdentFuncTable[24] = FuncTrue;
	fIdentFuncTable[452] = FuncUndefine;
	fIdentFuncTable[90] = FuncUnique;
	fIdentFuncTable[501] = FuncUntil;
	fIdentFuncTable[262] = FuncUse;
	fIdentFuncTable[195] = FuncVariant;
	fIdentFuncTable[344] = FuncVisible;
	fIdentFuncTable[372] = FuncVoid;
	fIdentFuncTable[348] = FuncWhen;
	fIdentFuncTable[156] = FuncXor;
	fIdentFuncTable[471] = FuncYes;
}

TtkTokenKind __fastcall TSynEiffelSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::OperatorFunc(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkOperatorAndSymbols;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::Func37u(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkPredefined;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncAdapt(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncAlias(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncAll(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncAnd(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncArray(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkBasicTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncAs(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncAssertion(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncBit(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkPredefined;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncBoolean(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkBasicTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncCharacter(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkBasicTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncCheck(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncClass(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncCluster(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncColon(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncComma(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncCreation(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncCurrent(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkPredefined;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncDebug(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncDefault(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncDeferred(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncDo(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncDouble(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkBasicTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncElse(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncElseif(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncEnd(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncEnsure(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncExclude(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncExecutable(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncExpanded(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncExport(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncExternal(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncFalse(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkPredefined;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncFeature(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncFrom(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncFrozen(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncGenerate(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncIdentifier(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncIf(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncIgnore(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncImplies(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncInclude(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncInclude95path(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncIndexing(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncInfix(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncInherit(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncInspect(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncInteger(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkBasicTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncInvariant(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncIs(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncLike(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncLocal(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncLoop(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncMake(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncNo(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncNot(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncObject(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncObsolete(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncOld(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncOnce(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncOptimize(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncOption(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncOr(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncPointer(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkBasicTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncPrecompiled(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncPrecursor(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkPredefined;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncPrefix(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncReal(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkBasicTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncRedefine(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncRename(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncRequire(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncRescue(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncResult(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkResultValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncRetry(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncRoot(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncSelect(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncSeparate(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncString(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkBasicTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncStrip(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkPredefined;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncSystem(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncThen(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncTrace(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncTrue(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkPredefined;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncUndefine(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncUnique(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkPredefined;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncUntil(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncUse(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncVariant(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncVisible(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncVoid(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkPredefined;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncWhen(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncXor(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::FuncYes(int Index)
{
	TtkTokenKind result = tkBasicTypes;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkLace;
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynEiffelSyn::SpaceProc()
{
	++Run;
	fTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynEiffelSyn::NullProc()
{
	fTokenID = tkNull;
	++Run;
}

void __fastcall TSynEiffelSyn::CRProc()
{
	fTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynEiffelSyn::LFProc()
{
	fTokenID = tkSpace;
	++Run;
}

void __fastcall TSynEiffelSyn::OperatorAndSymbolProc()
{
	fTokenID = tkIdentifier;
	if(fLine[Run] == L'\x21')
	{
		fRange = rsOperatorAndSymbolProc;
		fTokenID = tkOperatorAndSymbols;
		++Run;
		return;
	}
	if(CharInSet(fLine[Run], Synhighlightereiffel__0))
	{
		fRange = rsOperatorAndSymbolProc;
		fTokenID = tkOperatorAndSymbols;
		++Run;
		return;
	}
	if(CharInSet(fLine[Run], Synhighlightereiffel__1))
	{
		fRange = rsOperatorAndSymbolProc;
		fTokenID = tkOperatorAndSymbols;
		++Run;
		return;
	}
	if(CharInSet(fLine[Run], Synhighlightereiffel__2))
	{
		fRange = rsOperatorAndSymbolProc;
		fTokenID = tkOperatorAndSymbols;
		++Run;
		return;
	}
	if(CharInSet(fLine[Run], Synhighlightereiffel__3))
	{
		fRange = rsOperatorAndSymbolProc;
		fTokenID = tkOperatorAndSymbols;
		++Run;
		return;
	}
	if(CharInSet(fLine[Run], Synhighlightereiffel__4))
	{
		fRange = rsOperatorAndSymbolProc;
		fTokenID = tkOperatorAndSymbols;
		++Run;
		return;
	}
}

void __fastcall TSynEiffelSyn::EiffelCommentOpenProc()
{
	++Run;
	if((fLine[Run - 1] == L'-') && (fLine[Run] == L'-'))
	{
		fRange = rsEiffelComment;
		EiffelCommentProc();
		fTokenID = tkComment;
	}
	else
	fTokenID = tkOperatorAndSymbols;
}

void __fastcall TSynEiffelSyn::EiffelCommentProc()
{
	fTokenID = tkComment;
	do
	{
		if(!IsLineEnd(Run))
			++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynEiffelSyn::StringOpenProc()
{
	++Run;
	fRange = rsString;
	StringProc();
	fTokenID = tkString;
}

void __fastcall TSynEiffelSyn::StringProc()
{
	fTokenID = tkString;
	do
	{
		if(fLine[Run] == L'\"')
		{
			Run += 1;
			fRange = rsUnKnown;
			break;
		}
		if(!IsLineEnd(Run))
			++Run;
	}
	while(!IsLineEnd(Run));
}

__fastcall TSynEiffelSyn::TSynEiffelSyn(TComponent* AOwner)
 : inherited(AOwner),
			fRange(rsUnKnown),
			fTokenID(tkBasicTypes),
			fBasicTypesAttri(nullptr),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fLaceAttri(nullptr),
			fOperatorAndSymbolsAttri(nullptr),
			fPredefinedAttri(nullptr),
			fResultValueAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr)
{
	fCaseSensitive = false;
	fBasicTypesAttri = new TSynHighlighterAttributes(SYNS_AttrBasicTypes, SYNS_FriendlyAttrBasicTypes);
	fBasicTypesAttri->Style = Synhighlightereiffel__5;
	fBasicTypesAttri->Foreground = (TColor) clBlue;
	AddAttribute(fBasicTypesAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlightereiffel__6;
	fCommentAttri->Foreground = (TColor) clTeal;
	AddAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	fIdentifierAttri->Foreground = (TColor) clMaroon;
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlightereiffel__7;
	fKeyAttri->Foreground = (TColor) clNavy;
	AddAttribute(fKeyAttri);
	fLaceAttri = new TSynHighlighterAttributes(SYNS_AttrLace, SYNS_FriendlyAttrLace);
	fLaceAttri->Style = Synhighlightereiffel__8;
	fLaceAttri->Foreground = (TColor) clNavy;
	AddAttribute(fLaceAttri);
	fOperatorAndSymbolsAttri = new TSynHighlighterAttributes(SYNS_AttrOperatorAndSymbols, SYNS_FriendlyAttrOperatorAndSymbols);
	fOperatorAndSymbolsAttri->Style = Synhighlightereiffel__9;
	fOperatorAndSymbolsAttri->Foreground = (TColor) clOlive;
	AddAttribute(fOperatorAndSymbolsAttri);
	fPredefinedAttri = new TSynHighlighterAttributes(SYNS_AttrPredefined, SYNS_FriendlyAttrPredefined);
	fPredefinedAttri->Style = Synhighlightereiffel__10;
	fPredefinedAttri->Foreground = (TColor) clRed;
	AddAttribute(fPredefinedAttri);
	fResultValueAttri = new TSynHighlighterAttributes(SYNS_AttrResultValue, SYNS_FriendlyAttrResultValue);
	fResultValueAttri->Style = Synhighlightereiffel__11;
	fResultValueAttri->Foreground = (TColor) clPurple;
	AddAttribute(fResultValueAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Style = Synhighlightereiffel__12;
	fStringAttri->Foreground = (TColor) clGray;
	AddAttribute(fStringAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterEiffel;
}

void __fastcall TSynEiffelSyn::IdentProc()
{
	fTokenID = IdentKind(fLine + Run);
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynEiffelSyn::UnknownProc()
{
	++Run;
	fTokenID = tkUnknown;
}

void __fastcall TSynEiffelSyn::Next()
{
	fTokenPos = Run;
	fRange = rsUnKnown;
	switch(fLine[Run])
	{
		case L'\x21':
		case 35: case 36: case 37: case 38: case 39: case 40: case 41: case 42: case 43: case 44:
		case 46: case 47:
		case 58: case 59: case 60: case 61: case 62: case 63: case 64:
		case 91: case 92: case 93: case 94: case 95: case 96:
		case 123: case 124: case 125: case 126: case 127:
		OperatorAndSymbolProc();
		break;
		case L'\x00':
		NullProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		case L'-':
		EiffelCommentOpenProc();
		break;
		case L'\"':
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
		IdentProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynEiffelSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynEiffelSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

String __fastcall TSynEiffelSyn::GetKeyWords(int TokenKind)
{
	String result;
	result = L"-,!,#,$,%U,&,(,),*,.,/,//,/=,:,:=,;,@,[,\\\\,],^,|,+,<,<>,=,>,adapt,ali"
	           L"as,all,and,Array,as,assertion,BIT,boolean,character,check,class,cluste"
	           L"r,colon,comma,creation,current,debug,default,deferred,do,double,else,e"
	           L"lseif,end,ensure,exclude,executable,expanded,export,external,false,fea"
	           L"ture,from,frozen,generate,identifier,if,ignore,implies,include,include"
	           L"_path,indexing,infix,inherit,inspect,integer,invariant,is,like,local,l"
	           L"oop,make,no,not,object,obsolete,old,once,optimize,option,or,pointer,pr"
	           L"ecompiled,precursor,prefix,real,redefine,rename,require,rescue,result,"
	           L"retry,root,select,separate,string,strip,system,then,trace,true,undefin"
	           L"e,unique,until,use,variant,visible,void,when,xor,yes";
	return result;
}

TtkTokenKind __fastcall TSynEiffelSyn::GetTokenID()
{
	TtkTokenKind result = tkBasicTypes;
	result = fTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynEiffelSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkBasicTypes:
		result = fBasicTypesAttri;
		break;
		case tkComment:
		result = fCommentAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkLace:
		result = fLaceAttri;
		break;
		case tkOperatorAndSymbols:
		result = fOperatorAndSymbolsAttri;
		break;
		case tkPredefined:
		result = fPredefinedAttri;
		break;
		case tkResultValue:
		result = fResultValueAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
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

int __fastcall TSynEiffelSyn::GetTokenKind()
{
	int result = 0;
	result = int(fTokenID);
	return result;
}

String __fastcall TSynEiffelSyn::GetSampleSource()
{
	String result;
	result = L"-- Eiffel sample source from SmartEiffel\x0d\x0a"
	           L"class FIBONACCI\x0d\x0a"
	           L"-- Eiffel comment\x0d\x0a"
	           L"creation make\x0d\x0a"
	           L"\x0d\x0a"
	           L"feature\x0d\x0a"
	           L"\x0d\x0a"
	           L"   make is\x0d\x0a"
	           L"      do\x0d\x0a"
	           L"         if argument_count /= 1 or else\x0d\x0a"
	           L"            not argument(1).is_integer\x0d\x0a"
	           L"          then\x0d\x0a"
	           L"            io.put_string(\"Usage: \");\x0d\x0a"
	           L"            io.put_string(argument(0));\x0d\x0a"
	           L"            io.put_string(\" <Integer_value>%N\");\x0d\x0a"
	           L"            die_with_code(exit_failure_code);\x0d\x0a"
	           L"         end;\x0d\x0a"
	           L"         io.put_integer(fibonacci(argument(1).to_integer));\x0d\x0a"
	           L"         io.put_new_line;\x0d\x0a"
	           L"      end;\x0d\x0a"
	           L"   -- Eiffel comment\x0d\x0a"
	           L"   fibonacci(i: INTEGER): INTEGER is\x0d\x0a"
	           L"      require -- Eiffel comment\x0d\x0a"
	           L"         i >= 0\x0d\x0a"
	           L"      do\x0d\x0a"
	           L"         if i = 0 then\x0d\x0a"
	           L"            Result := 1;\x0d\x0a"
	           L"         elseif i = 1 then\x0d\x0a"
	           L"            Result := 1;\x0d\x0a"
	           L"         else\x0d\x0a"
	           L"            Result := fibonacci(i - 1) + fibonacci(i - 2) ;\x0d\x0a"
	           L"         end;\x0d\x0a"
	           L"      end;\x0d\x0a"
	           L"\x0d\x0a"
	           L"end";
	return result;
}

bool __fastcall TSynEiffelSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterEiffel;
	return result;
}

/*#static*/
String __fastcall TSynEiffelSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangEiffel;
	return result;
}

void __fastcall TSynEiffelSyn::ResetRange()
{
	fRange = rsUnKnown;
}

void __fastcall TSynEiffelSyn::SetRange(void* Value)
{
	fRange = (TRangeState)(NativeInt)Value;
}

void* __fastcall TSynEiffelSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) fRange);
	return result;
}

bool __fastcall TSynEiffelSyn::IsOperatorChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'-':
		case L'!':
		case L'#':
		case L'$':
		case L'%':
		case L'&':
		case L'(':
		case L')':
		case L'*':
		case L'.':
		case L'/':
		case L':':
		case L';':
		case L'@':
		case L'[':
		case L'\\':
		case L']':
		case L'^':
		case L'|':
		case L'+':
		case L'<':
		case L'=':
		case L'>':
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

/*#static*/
String __fastcall TSynEiffelSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangEiffel;
	return result;
}

	static bool SynHighlighterEiffel_Initialized = false;
	
	void SynHighlighterEiffel_initialization()
	{
		if(SynHighlighterEiffel_Initialized)
			return;
		
		SynHighlighterEiffel_Initialized = true;
		
		RegisterPlaceableHighlighter(__classid(TSynEiffelSyn));
	}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterEiffel

