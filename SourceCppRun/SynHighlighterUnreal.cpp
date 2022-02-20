
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterUnreal.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Uitypes;

namespace Synhighlighterunreal
{
#define SynHighlighterUnreal__0 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterUnreal__1 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterUnreal__2 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterUnreal__3 (TSynHighlighterCapabilities() << TSynHighlighterCapability::hcUserSettings)


const String Keywords[143/*# range 0..142*/] = {L"abstract", L"always", L"array", L"arraycount", L"assert", L"auto", L"automated", L"bool", L"boundingbox", L"boundingvolume"
																				, L"break", L"button", L"byte", L"cache", L"cacheexempt", L"case", L"catch", L"class", L"coerce", L"collapsecategories", L"color"
																				, L"config", L"const", L"continue", L"coords", L"cpptext", L"cross", L"default", L"defaultproperties", L"delegate", L"delete"
																				, L"dependson", L"deprecated", L"do", L"dontcollapsecategories", L"dot", L"each", L"edfindable", L"editconst", L"editconstarray"
																				, L"editinline", L"editinlinenew", L"editinlinenotify", L"editinlineuse", L"else", L"enum", L"enumcount", L"event"
																				, L"exec", L"expands", L"explicit", L"export", L"exportstructs", L"extends", L"false", L"final", L"float", L"for", L"foreach"
																				, L"function", L"global", L"globalconfig", L"goto", L"guid", L"hidecategories", L"hidedropdown", L"hideparent", L"if"
																				, L"ignores", L"import", L"init", L"input", L"insert", L"instanced", L"int", L"intrinsic", L"invariant", L"iterator", L"latent"
																				, L"length", L"local", L"localized", L"long", L"mesh", L"model", L"mutable", L"name", L"native", L"nativereplication", L"new"
																				, L"noexport", L"none", L"noteditinlinenew", L"notplaceable", L"nousercreate", L"operator", L"optional", L"out", L"parseconfig"
																				, L"perobjectconfig", L"placeable", L"plane", L"pointer", L"postoperator", L"preoperator", L"private", L"protected"
																				, L"register", L"reliable", L"remove", L"replication", L"return", L"rng", L"rot", L"rotator", L"safereplace", L"scale"
																				, L"scriptconst", L"self", L"showcategories", L"simulated", L"singular", L"skip", L"sound", L"state", L"static", L"stop"
																				, L"string", L"struct", L"super", L"switch", L"texture", L"transient", L"travel", L"true", L"unreliable", L"until", L"var"
																				, L"vect", L"vector", L"void", L"while", L"within"};
const int KeyIndices[733/*# range 0..732*/] = {-1, -1, -1, -1, -1, -1, 78, -1, -1, -1, -1, 25, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 79, -1, -1, -1, -1, -1, -1, -1, -1, 104, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 34, -1, -1, -1, 18, -1, -1, -1, -1, -1, 30, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 63, -1, -1
																				, -1, -1, 114, -1, -1, 121, -1, -1, -1, -1, -1, 105, -1, -1, 108, -1, 135, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, 117, 33, 109, -1, -1, -1, -1, -1, -1, 90, -1, -1, -1, -1, -1, 106, -1, -1, -1, -1
																				, -1, -1, -1, 124, -1, -1, -1, -1, 19, -1, -1, -1, -1, 81, -1, 82, -1, -1, -1, -1, 40, 15, -1, -1, -1, 52, -1, 80, -1, -1, -1, -1, -1, -1, 136, -1, -1, 61, -1, 113, -1, -1, -1, 83, -1, -1, -1, -1, -1
																				, -1, 27, -1, -1, 133, -1, -1, -1, -1, 62, -1, -1, -1, -1, -1, -1, -1, 76, -1, -1, -1, -1, -1, -1, -1, 126, -1, -1, -1, -1, -1, 2, -1, -1, -1, -1, 51, -1, -1, -1, -1, 44, -1, 22, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, 20, -1, -1, -1, 8, -1, -1, -1, 110, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 96, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 65, -1, -1, -1, -1, -1, -1, -1, 39, 24, -1
																				, -1, -1, -1, 54, -1, 4, 123, -1, -1, -1, -1, -1, -1, 50, 141, -1, -1, -1, -1, -1, -1, -1, 87, -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 60, -1, -1, -1, -1, -1, 85, -1, -1
																				, -1, -1, -1, 70, -1, 68, 131, -1, -1, 69, -1, -1, -1, -1, -1, 128, 26, -1, -1, -1, -1, -1, -1, -1, -1, 7, -1, -1, 142, -1, -1, 122, -1, 74, -1, -1, -1, -1, -1, -1, -1, 13, -1, -1, -1, -1, 101, 119, -1
																				, -1, 94, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 100, -1, -1, -1, -1, -1, 89, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, -1, -1, 92, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, 112, -1, -1, -1, -1, 67, -1, -1, 45, -1, 116, -1, -1, 132, 28, -1, -1, -1, 31, -1, -1, -1, 77, -1, -1, -1, -1, -1, 91, -1, 37, -1, -1, -1, -1, 35, -1, 6, -1, -1, -1, -1, -1, -1, -1, 97, -1, -1, -1
																				, -1, -1, 53, -1, 84, -1, -1, -1, -1, 56, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 23, -1, 107, -1, -1, -1, -1, 98, -1, -1, 75, -1, -1, -1, -1, -1, 88, -1, -1, 103, -1, -1, 93, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, 59, 139, 11, 42, -1, -1, 95, -1, -1, -1, -1, -1, 3, -1, -1, -1, 38, -1, -1, -1, -1, -1, -1, -1, -1, 16, -1, 46, -1, -1, -1, -1, -1, 102, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, 111, -1, -1, 41, -1, -1, -1, -1, -1, -1, -1, -1, 48, 64, -1, -1, -1, -1, 86, -1, 58, 43, 72, -1, -1, 66, 137, 71, -1, -1, -1, -1, -1, 129, -1, -1, -1, -1, -1, -1, -1, -1, 17, 130, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, 120, -1, 73, -1, -1, 118, -1, -1, -1, -1, -1, -1, 138, -1, -1, -1, 55, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, 115, -1, -1, -1, -1, 32, 47, 49, -1, -1, -1, -1, -1, -1, -1, 57, -1, -1, -1, -1, -1, -1, 125, 134, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 99, 12, -1, 127, 140, -1, -1};

/*$Q-*/

unsigned int __fastcall TSynUnrealSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 41 + int((*Str)) * 701);
		++Str;
	}
	result = (unsigned int) (result % 733);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynUnrealSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 732 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynUnrealSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 732 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] ==  - 1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[410] = FuncAbstract;
	fIdentFuncTable[71] = FuncAlways;
	fIdentFuncTable[219] = FuncArray;
	fIdentFuncTable[554] = FuncArraycount;
	fIdentFuncTable[294] = FuncAssert;
	fIdentFuncTable[681] = FuncAuto;
	fIdentFuncTable[477] = FuncAutomated;
	fIdentFuncTable[364] = FuncBool;
	fIdentFuncTable[249] = FuncBoundingbox;
	fIdentFuncTable[109] = FuncBoundingvolume;
	fIdentFuncTable[675] = FuncBreak;
	fIdentFuncTable[544] = FuncButton;
	fIdentFuncTable[727] = FuncByte;
	fIdentFuncTable[380] = FuncCache;
	fIdentFuncTable[499] = FuncCacheexempt;
	fIdentFuncTable[160] = FuncCase;
	fIdentFuncTable[567] = FuncCatch;
	fIdentFuncTable[635] = FuncClass;
	fIdentFuncTable[64] = FuncCoerce;
	fIdentFuncTable[147] = FuncCollapsecategories;
	fIdentFuncTable[245] = FuncColor;
	fIdentFuncTable[314] = FuncConfig;
	fIdentFuncTable[231] = FuncConst;
	fIdentFuncTable[510] = FuncContinue;
	fIdentFuncTable[287] = FuncCoords;
	fIdentFuncTable[11] = FuncCpptext;
	fIdentFuncTable[355] = FuncCross;
	fIdentFuncTable[189] = FuncDefault;
	fIdentFuncTable[454] = FuncDefaultproperties;
	fIdentFuncTable[425] = FuncDelegate;
	fIdentFuncTable[70] = FuncDelete;
	fIdentFuncTable[458] = FuncDependson;
	fIdentFuncTable[696] = FuncDeprecated;
	fIdentFuncTable[120] = FuncDo;
	fIdentFuncTable[60] = FuncDontcollapsecategories;
	fIdentFuncTable[475] = FuncDot;
	fIdentFuncTable[49] = FuncEach;
	fIdentFuncTable[470] = FuncEdfindable;
	fIdentFuncTable[558] = FuncEditconst;
	fIdentFuncTable[286] = FuncEditconstarray;
	fIdentFuncTable[159] = FuncEditinline;
	fIdentFuncTable[596] = FuncEditinlinenew;
	fIdentFuncTable[545] = FuncEditinlinenotify;
	fIdentFuncTable[614] = FuncEditinlineuse;
	fIdentFuncTable[229] = FuncElse;
	fIdentFuncTable[448] = FuncEnum;
	fIdentFuncTable[569] = FuncEnumcount;
	fIdentFuncTable[697] = FuncEvent;
	fIdentFuncTable[605] = FuncExec;
	fIdentFuncTable[698] = FuncExpands;
	fIdentFuncTable[302] = FuncExplicit;
	fIdentFuncTable[224] = FuncExport;
	fIdentFuncTable[164] = FuncExportstructs;
	fIdentFuncTable[491] = FuncExtends;
	fIdentFuncTable[292] = FuncFalse;
	fIdentFuncTable[662] = FuncFinal;
	fIdentFuncTable[498] = FuncFloat;
	fIdentFuncTable[706] = FuncFor;
	fIdentFuncTable[613] = FuncForeach;
	fIdentFuncTable[542] = FuncFunction;
	fIdentFuncTable[330] = FuncGlobal;
	fIdentFuncTable[176] = FuncGlobalconfig;
	fIdentFuncTable[197] = FuncGoto;
	fIdentFuncTable[89] = FuncGuid;
	fIdentFuncTable[606] = FuncHidecategories;
	fIdentFuncTable[278] = FuncHidedropdown;
	fIdentFuncTable[618] = FuncHideparent;
	fIdentFuncTable[445] = FuncIf;
	fIdentFuncTable[344] = FuncIgnores;
	fIdentFuncTable[348] = FuncImport;
	fIdentFuncTable[342] = FuncInit;
	fIdentFuncTable[620] = FuncInput;
	fIdentFuncTable[615] = FuncInsert;
	fIdentFuncTable[648] = FuncInstanced;
	fIdentFuncTable[372] = FuncInt;
	fIdentFuncTable[520] = FuncIntrinsic;
	fIdentFuncTable[205] = FuncInvariant;
	fIdentFuncTable[462] = FuncIterator;
	fIdentFuncTable[6] = FuncLatent;
	fIdentFuncTable[24] = FuncLength;
	fIdentFuncTable[166] = FuncLocal;
	fIdentFuncTable[152] = FuncLocalized;
	fIdentFuncTable[154] = FuncLong;
	fIdentFuncTable[182] = FuncMesh;
	fIdentFuncTable[493] = FuncModel;
	fIdentFuncTable[336] = FuncMutable;
	fIdentFuncTable[611] = FuncName;
	fIdentFuncTable[311] = FuncNative;
	fIdentFuncTable[526] = FuncNativereplication;
	fIdentFuncTable[407] = FuncNew;
	fIdentFuncTable[128] = FuncNoexport;
	fIdentFuncTable[468] = FuncNone;
	fIdentFuncTable[428] = FuncNoteditinlinenew;
	fIdentFuncTable[532] = FuncNotplaceable;
	fIdentFuncTable[389] = FuncNousercreate;
	fIdentFuncTable[548] = FuncOperator;
	fIdentFuncTable[265] = FuncOptional;
	fIdentFuncTable[485] = FuncOut;
	fIdentFuncTable[517] = FuncParseconfig;
	fIdentFuncTable[726] = FuncPerobjectconfig;
	fIdentFuncTable[401] = FuncPlaceable;
	fIdentFuncTable[385] = FuncPlane;
	fIdentFuncTable[575] = FuncPointer;
	fIdentFuncTable[529] = FuncPostoperator;
	fIdentFuncTable[33] = FuncPreoperator;
	fIdentFuncTable[103] = FuncPrivate;
	fIdentFuncTable[134] = FuncProtected;
	fIdentFuncTable[512] = FuncRegister;
	fIdentFuncTable[106] = FuncReliable;
	fIdentFuncTable[121] = FuncRemove;
	fIdentFuncTable[253] = FuncReplication;
	fIdentFuncTable[593] = FuncReturn;
	fIdentFuncTable[440] = FuncRng;
	fIdentFuncTable[178] = FuncRot;
	fIdentFuncTable[94] = FuncRotator;
	fIdentFuncTable[691] = FuncSafereplace;
	fIdentFuncTable[450] = FuncScale;
	fIdentFuncTable[119] = FuncScriptconst;
	fIdentFuncTable[651] = FuncSelf;
	fIdentFuncTable[386] = FuncShowcategories;
	fIdentFuncTable[646] = FuncSimulated;
	fIdentFuncTable[97] = FuncSingular;
	fIdentFuncTable[370] = FuncSkip;
	fIdentFuncTable[295] = FuncSound;
	fIdentFuncTable[142] = FuncState;
	fIdentFuncTable[713] = FuncStatic;
	fIdentFuncTable[213] = FuncStop;
	fIdentFuncTable[729] = FuncString;
	fIdentFuncTable[354] = FuncStruct;
	fIdentFuncTable[626] = FuncSuper;
	fIdentFuncTable[636] = FuncSwitch;
	fIdentFuncTable[345] = FuncTexture;
	fIdentFuncTable[453] = FuncTransient;
	fIdentFuncTable[192] = FuncTravel;
	fIdentFuncTable[714] = FuncTrue;
	fIdentFuncTable[108] = FuncUnreliable;
	fIdentFuncTable[173] = FuncUntil;
	fIdentFuncTable[619] = FuncVar;
	fIdentFuncTable[658] = FuncVect;
	fIdentFuncTable[543] = FuncVector;
	fIdentFuncTable[730] = FuncVoid;
	fIdentFuncTable[303] = FuncWhile;
	fIdentFuncTable[367] = FuncWithin;
}

TtkTokenKind __fastcall TSynUnrealSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncAbstract(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncAlways(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncArray(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncArraycount(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncAssert(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncAuto(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncAutomated(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncBool(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncBoundingbox(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncBoundingvolume(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncBreak(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncButton(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncByte(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncCache(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncCacheexempt(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncCase(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncCatch(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncClass(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncCoerce(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncCollapsecategories(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncColor(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncConfig(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncConst(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncContinue(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncCoords(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncCpptext(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncCross(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSymbol;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncDefault(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncDefaultproperties(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncDelegate(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncDelete(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncDependson(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncDeprecated(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncDo(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncDontcollapsecategories(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncDot(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSymbol;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncEach(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncEdfindable(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncEditconst(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncEditconstarray(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncEditinline(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncEditinlinenew(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncEditinlinenotify(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncEditinlineuse(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncElse(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncEnum(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncEnumcount(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncEvent(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncExec(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncExpands(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncExplicit(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncExport(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncExportstructs(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncExtends(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncFalse(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncFinal(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncFloat(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncFor(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncForeach(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncFunction(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncGlobal(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncGlobalconfig(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncGoto(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncGuid(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncHidecategories(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncHidedropdown(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncHideparent(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncIf(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncIgnores(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncImport(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncInit(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncInput(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncInsert(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncInstanced(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncInt(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncIntrinsic(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncInvariant(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncIterator(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncLatent(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncLength(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncLocal(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncLocalized(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncLong(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncMesh(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncModel(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncMutable(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncName(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncNative(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncNativereplication(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncNew(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncNoexport(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncNone(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncNoteditinlinenew(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncNotplaceable(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncNousercreate(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncOperator(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncOptional(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncOut(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncParseconfig(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncPerobjectconfig(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncPlaceable(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncPlane(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncPointer(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncPostoperator(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncPreoperator(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncPrivate(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncProtected(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncRegister(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncReliable(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncRemove(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncReplication(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncReturn(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncRng(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncRot(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncRotator(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncSafereplace(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncScale(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncScriptconst(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncSelf(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncShowcategories(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncSimulated(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncSingular(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncSkip(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncSound(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncState(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncStatic(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncStop(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncString(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncStruct(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncSuper(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncSwitch(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncTexture(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncTransient(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncTravel(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncTrue(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncUnreliable(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey2;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncUntil(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncVar(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncVect(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncVector(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncVoid(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncWhile(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::FuncWithin(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynUnrealSyn::TSynUnrealSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FRoundCount(0),
			FSquareCount(0),
			FTokenID(tkComment),
			FExtTokenID(xtkAdd),
			fCommentAttri(nullptr),
			fDirecAttri(nullptr),
			fIdentifierAttri(nullptr),
			fInvalidAttri(nullptr),
			fKeyAttri(nullptr),
			fKey2Attri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fString2Attri(nullptr),
			fSymbolAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = SynHighlighterUnreal__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fInvalidAttri = new TSynHighlighterAttributes(SYNS_AttrIllegalChar, SYNS_FriendlyAttrIllegalChar);
	addAttribute(fInvalidAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = SynHighlighterUnreal__1;
	addAttribute(fKeyAttri);
	fKey2Attri = new TSynHighlighterAttributes(SYNS_AttrSecondReservedWord, SYNS_FriendlyAttrSecondReservedWord);
	fKey2Attri->Style = SynHighlighterUnreal__2;
	addAttribute(fKey2Attri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fString2Attri = new TSynHighlighterAttributes(SYNS_AttrSingleString, SYNS_FriendlyAttrSingleString);
	addAttribute(fString2Attri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fDirecAttri = new TSynHighlighterAttributes(SYNS_AttrDirective, SYNS_FriendlyAttrDirective);
	addAttribute(fDirecAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterCPP;
} /* Create */

void __fastcall TSynUnrealSyn::AnsiCProc()
{
	FTokenID = tkComment;
	switch(fLine[Run])
	{
		case L'\x00':
		{
			NullProc();
			return;
		}
		case L'\x0a':
		{
			LFProc();
			return;
		}
		case L'\x0d':
		{
			CRProc();
			return;
		}
		default:
		  ;
		break;
	}
	while(!IsLineEnd(Run))
		switch(fLine[Run])
		{
			case L'*':
			if(fLine[Run + 1] == L'/')
			{
				Run += 2;
				if(FRange == rsDirectiveComment)
					FRange = rsDirective;
				else
					FRange = rsUnKnown;
				goto label0;
			}
			else
			++Run;
			break;
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

void __fastcall TSynUnrealSyn::AndSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*and assign*/
		{
			Run += 2;
			FExtTokenID = xtkAndAssign;
		}
		break;                               /*logical and*/
		case L'&':
		{
			Run += 2;
			FExtTokenID = xtkLogAnd;
		}
		break;                                 /*and*/
		default:
		{
			++Run;
			FExtTokenID = xtkAnd;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::AsciiCharProc()
{
	FTokenID = tkString2;
	do
	{
		if(IsLineEnd(Run))
			break;
		if(fLine[Run] == L'\x5c')
		{
			if(fLine[Run + 1] == L'\x27')                             /*backslash*/
        /*if we have an escaped single quote it doesn't count*/
				++Run;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x27'));
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynUnrealSyn::BraceCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkBraceClose;
}

void __fastcall TSynUnrealSyn::BraceOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkBraceOpen;
}

void __fastcall TSynUnrealSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run + 1] == L'\x0a')
		++Run;
}

void __fastcall TSynUnrealSyn::ColonProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L':':                               /*scope resolution operator*/
		{
			Run += 2;
			FExtTokenID = xtkScopeResolution;
		}
		break;                                 /*colon*/
		default:
		{
			++Run;
			FExtTokenID = xtkColon;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::CommaProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkComma;
}

void __fastcall TSynUnrealSyn::DirectiveProc()
{
	if(IsLineEnd(Run))
	{
		if(Run <= 0)
			FRange = rsUnKnown;
		NextProcedure();
	}
	else
	{
		FTokenID = tkDirective;
		while(true)
			switch(fLine[Run])
			{
				case L'/': // comment?
				{
					if(fLine[Run + 1] == L'/')
						goto label3;
					else
					{
						if(fLine[Run + 1] == L'*') // might be embedded only
						{
							FRange = rsDirectiveComment;
							goto label4;
						}
						else
						++Run;
					}
				}
				break;
				case L'\x00':
				case L'\x0a':
				case L'\x0d':
				{
					FRange = rsUnKnown;
					goto label5;
				}
				default:
				++Run;
				break;
			}
		label3:;
		label4:;
		label5:;
	}
}

void __fastcall TSynUnrealSyn::EqualProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*logical equal*/
		{
			Run += 2;
			FExtTokenID = xtkLogEqual;
		}
		break;                                 /*assign*/
		default:
		{
			++Run;
			FExtTokenID = xtkAssign;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::GreaterProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*greater than or equal to*/
		{
			Run += 2;
			FExtTokenID = xtkGreaterThanEqual;
		}
		break;
		case L'>':
		{
			if(fLine[Run + 2] == L'=')   /*shift right assign*/
			{
				Run += 3;
				FExtTokenID = xtkShiftRightAssign;
			}
			else
                           /*shift right*/
			{
				Run += 2;
				FExtTokenID = xtkShiftRight;
			}
		}
		break;                                 /*greater than*/
		default:
		{
			++Run;
			FExtTokenID = xtkGreaterThan;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::QuestionProc()
{
	FTokenID = tkSymbol;                /*conditional*/
	FExtTokenID = xtkQuestion;
	++Run;
}

void __fastcall TSynUnrealSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynUnrealSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynUnrealSyn::LowerProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*less than or equal to*/
		{
			Run += 2;
			FExtTokenID = xtkLessThanEqual;
		}
		break;
		case L'<':
		{
			if(fLine[Run + 2] == L'=')   /*shift left assign*/
			{
				Run += 3;
				FExtTokenID = xtkShiftLeftAssign;
			}
			else
                           /*shift left*/
			{
				Run += 2;
				FExtTokenID = xtkShiftLeft;
			}
		}
		break;                                 /*less than*/
		default:
		{
			++Run;
			FExtTokenID = xtkLessThan;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::MinusProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*subtract assign*/
		{
			Run += 2;
			FExtTokenID = xtkSubtractAssign;
		}
		break;                               /*decrement*/
		case L'-':
		{
			Run += 2;
			FExtTokenID = xtkDecrement;
		}
		break;                               /*arrow*/
		case L'>':
		{
			Run += 2;
			FExtTokenID = xtkArrow;
		}
		break;                                 /*subtract*/
		default:
		{
			++Run;
			FExtTokenID = xtkSubtract;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::ModSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*mod assign*/
		{
			Run += 2;
			FExtTokenID = xtkModAssign;
		}
		break;                                 /*mod*/
		default:
		{
			++Run;
			FExtTokenID = xtkMod;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::NotSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*not equal*/
		{
			Run += 2;
			FExtTokenID = xtkNotEqual;
		}
		break;                                 /*not*/
		default:
		{
			++Run;
			FExtTokenID = xtkLogComplement;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynUnrealSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			case L'.':
			case L'u':
			case L'U':
			case L'l':
			case L'L':
			case L'x':
			case L'X':
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
				goto label6;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label6:;
}

void __fastcall TSynUnrealSyn::OrSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*or assign*/
		{
			Run += 2;
			FExtTokenID = xtkIncOrAssign;
		}
		break;                               /*logical or*/
		case L'|':
		{
			Run += 2;
			FExtTokenID = xtkLogOr;
		}
		break;                                 /*or*/
		default:
		{
			++Run;
			FExtTokenID = xtkIncOr;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::PlusProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*add assign*/
		{
			Run += 2;
			FExtTokenID = xtkAddAssign;
		}
		break;                               /*increment*/
		case L'+':
		{
			Run += 2;
			FExtTokenID = xtkIncrement;
		}
		break;                                 /*add*/
		default:
		{
			++Run;
			FExtTokenID = xtkAdd;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::PointProc()
{
	FTokenID = tkSymbol;
	if((fLine[Run + 1] == L'.') && (fLine[Run + 2] == L'.'))                              /*ellipse*/
	{
		Run += 3;
		FExtTokenID = xtkEllipse;
	}
	else
                                 /*point*/
	{
		++Run;
		FExtTokenID = xtkPoint;
	}
}

void __fastcall TSynUnrealSyn::RoundCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkRoundClose;
	--FRoundCount;
}

void __fastcall TSynUnrealSyn::RoundOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkRoundOpen;
	++FRoundCount;
}

void __fastcall TSynUnrealSyn::SemiColonProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSemiColon;
}

void __fastcall TSynUnrealSyn::SlashProc()
{
	switch(fLine[Run + 1])
	{
		case L'/':                               /*c++ style comments*/
		{
			FTokenID = tkComment;
			Run += 2;
			while(!IsLineEnd(Run))
				++Run;
		}
		break;                               /*c style comments*/
		case L'*':
		{
			FTokenID = tkComment;
			if(FRange != rsDirectiveComment)
				FRange = rsAnsiC;
			Run += 2;
			while(!IsLineEnd(Run))
				switch(fLine[Run])
				{
					case L'*':
					if(fLine[Run + 1] == L'/')
					{
						Run += 2;
						if(FRange == rsDirectiveComment)
							FRange = rsDirective;
						else
							FRange = rsUnKnown;
						goto label7;
					}
					else
					++Run;
					break;
					case L'\x0a':
					case L'\x0d':
					{
						if(FRange == rsDirectiveComment)
							FRange = rsAnsiC;
						goto label8;
					}
					default:
					++Run;
					break;
				}
			label7:;
			label8:;
		}
		break;                               /*divide assign*/
		case L'=':
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkDivideAssign;
		}
		break;                                 /*divide*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkDivide;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynUnrealSyn::SquareCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSquareClose;
	--FSquareCount;
}

void __fastcall TSynUnrealSyn::SquareOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSquareOpen;
	++FSquareCount;
}

void __fastcall TSynUnrealSyn::StarProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*multiply assign*/
		{
			Run += 2;
			FExtTokenID = xtkMultiplyAssign;
		}
		break;                                 /*star*/
		default:
		{
			++Run;
			FExtTokenID = xtkStar;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::StringProc()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x22') && (fLine[Run + 2] == L'\x22'))
		Run += 2;
	do
	{
		if(IsLineEnd(Run))
			break;
		if(fLine[Run] == L'\x5c')
			switch(fLine[Run + 1])
			{                             /*backslash*/
				case L'\x0a':
				++Run;
				break;               /*line continuation character*/
				case L'\x22':
				++Run;
				break;               /*escaped quote doesn't count*/
				case L'\x5c':
				++Run;
				break;
				default:
				  ;
				break;
			}
		++Run;
	}
	while(!(fLine[Run] == L'\x22'));
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynUnrealSyn::DollarSignProc()
{
	FTokenID = tkSymbol;
	++Run;
}

void __fastcall TSynUnrealSyn::TildeProc()
{
	++Run;                            /*bitwise complement*/
	FTokenID = tkSymbol;
	FExtTokenID = xtkBitComplement;
}

void __fastcall TSynUnrealSyn::XOrSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':                               /*xor assign*/
		{
			Run += 2;
			FExtTokenID = xtkXorAssign;
		}
		break;                                 /*xor*/
		default:
		{
			++Run;
			FExtTokenID = xtkXor;
		}
		break;
	}
}

void __fastcall TSynUnrealSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynUnrealSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsAnsiC:
		case rsDirectiveComment:
		AnsiCProc();
		break;
		case rsDirective:
		DirectiveProc();
		break;
		default:
		{
			FRange = rsUnKnown;
			NextProcedure();
		}
		break;
	}
	inherited::Next();
}

void __fastcall TSynUnrealSyn::NextProcedure()
{
	switch(fLine[Run])
	{
		case L'&':
		AndSymbolProc();
		break;
		case L'\x27':
		AsciiCharProc();
		break;
		case L'}':
		BraceCloseProc();
		break;
		case L'{':
		BraceOpenProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		case L':':
		ColonProc();
		break;
		case L',':
		CommaProc();
		break;
		case L'#':
		DirectiveProc();
		break;
		case L'=':
		EqualProc();
		break;
		case L'>':
		GreaterProc();
		break;
		case L'?':
		QuestionProc();
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
		MinusProc();
		break;
		case L'%':
		ModSymbolProc();
		break;
		case L'!':
		NotSymbolProc();
		break;
		case L'\x00':
		NullProc();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		NumberProc();
		break;
		case L'|':
		OrSymbolProc();
		break;
		case L'+':
		PlusProc();
		break;
		case L'.':
		PointProc();
		break;
		case L')':
		RoundCloseProc();
		break;
		case L'(':
		RoundOpenProc();
		break;
		case L';':
		SemiColonProc();
		break;
		case L'/':
		SlashProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L']':
		SquareCloseProc();
		break;
		case L'[':
		SquareOpenProc();
		break;
		case L'*':
		StarProc();
		break;
		case L'\x22':
		StringProc();
		break;
		case L'$':
		case L'@':
		DollarSignProc();
		break;
		case L'~':
		TildeProc();
		break;
		case L'^':
		XOrSymbolProc();
		break;
		default:
		UnknownProc();
		break;
	}
}

TSynHighlighterAttributes* __fastcall TSynUnrealSyn::GetDefaultAttribute(int Index)
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
		case SYN_ATTR_WHITESPACE:
		result = fSpaceAttri;
		break;
		case SYN_ATTR_STRING:
		result = fStringAttri;
		break;
		case SYN_ATTR_IDENTIFIER:
		result = fIdentifierAttri;
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

bool __fastcall TSynUnrealSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynUnrealSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynUnrealSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TxtkTokenKind __fastcall TSynUnrealSyn::GetExtTokenID()
{
	TxtkTokenKind result = xtkAdd;
	result = FExtTokenID;
	return result;
}

bool __fastcall TSynUnrealSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterCPP;
	return result;
} /* IsFilterStored */

TSynHighlighterAttributes* __fastcall TSynUnrealSyn::GetTokenAttribute()
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
		case tkKey2:
		result = fKey2Attri;
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
		case tkString2:
		result = fString2Attri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkUnknown:
		result = fInvalidAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynUnrealSyn::GetTokenKind()
{
	int result = 0;
	result = int(GetTokenID());
	return result;
}

void __fastcall TSynUnrealSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynUnrealSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(int)Value;
}

void __fastcall TSynUnrealSyn::EnumUserSettings(TStrings* Settings)
{

  /* returns the user settings that exist in the registry */
	/*# with TBetterRegistry.Create do */
	{
		auto with0 = new TBetterRegistry();
		try
		{
			with0->RootKey = HKEY_LOCAL_MACHINE;
			if(with0->OpenKeyReadOnly(L"\\SOFTWARE\\Borland\\C++Builder"))
			{
				try
				{
					with0->GetKeyNames(Settings);
				}
				__finally
				{
					with0->CloseKey();
				}
			}
		}
		__finally
		{
			delete with0;
		}
	}
}
// Possible parameter values:
//   index into TStrings returned by EnumUserSettings
// Possible return values:
//   true : settings were read and used
//   false: problem reading settings or invalid version specified - old settings
//          were preserved

bool __fastcall TSynUnrealSyn::UseUserSettings(int settingIndex)
{
	bool result = false;

	auto ReadCPPBSettings = [&](int settingIndex) -> bool 
	{
		bool result = false;

		auto ReadCPPBSetting = [&](String settingTag, TSynHighlighterAttributes* Attri, String key) -> bool 
		{
			bool result = false;

			auto ReadCPPB1 = [&](String settingTag, TSynHighlighterAttributes* Attri, String Name) -> bool 
			{
				bool result = false;
				int i = 0;
				int stop = 0;
				for(stop = (int) Name.Length(), i = 1; i <= stop; i++)
				{
					if(Name[i] == L' ')
						Name[i] = L'_';
				}
				result = Attri->LoadFromBorlandRegistry(HKEY_CURRENT_USER, String(L"\\SOFTWARE\\Borland\\C++Builder\\") + settingTag
	           + L"\\Highlight", Name, true);
				return result;
			}; /* ReadCPPB1 */

			auto ReadCPPB3OrMore = [&](String settingTag, TSynHighlighterAttributes* Attri, String key) -> bool 
			{
				bool result = false;
				result = Attri->LoadFromBorlandRegistry(HKEY_CURRENT_USER, String(L"\\Software\\Borland\\C++Builder\\") + settingTag
	           + L"\\Editor\\Highlight", key, false);
				return result;
			}; /* ReadCPPB3OrMore */ /* ReadCPPBSetting */
			try
			{
				if(settingTag[1] == L'1')
					result = ReadCPPB1(settingTag, Attri, key);
				else
					result = ReadCPPB3OrMore(settingTag, Attri, key);
			}
			catch(...)
			{
				result = false;
			}
			return result;
		}; /* ReadCPPBSetting */
		TSynHighlighterAttributes* tmpStringAttri = nullptr;
		TSynHighlighterAttributes* tmpNumberAttri = nullptr;
		TSynHighlighterAttributes* tmpKeyAttri = nullptr;
		TSynHighlighterAttributes* tmpSymbolAttri = nullptr;
		TSynHighlighterAttributes* tmpCommentAttri = nullptr;
		TSynHighlighterAttributes* tmpIdentifierAttri = nullptr;
		TSynHighlighterAttributes* tmpInvalidAttri = nullptr;
		TSynHighlighterAttributes* tmpSpaceAttri = nullptr;
		TSynHighlighterAttributes* tmpDirecAttri = nullptr;
		TStringList* sl = nullptr; /* ReadCPPBSettings */
		sl = new TStringList();
		try
		{
			EnumUserSettings(sl);
			if(settingIndex >= sl->Count)
				result = false;
			else
			{
				tmpStringAttri = new TSynHighlighterAttributes(L"", L"");
				tmpNumberAttri = new TSynHighlighterAttributes(L"", L"");
				tmpKeyAttri = new TSynHighlighterAttributes(L"", L"");
				tmpSymbolAttri = new TSynHighlighterAttributes(L"", L"");
				tmpCommentAttri = new TSynHighlighterAttributes(L"", L"");
				tmpIdentifierAttri = new TSynHighlighterAttributes(L"", L"");
				tmpInvalidAttri = new TSynHighlighterAttributes(L"", L"");
				tmpSpaceAttri = new TSynHighlighterAttributes(L"", L"");
				tmpDirecAttri = new TSynHighlighterAttributes(L"", L"");
				tmpStringAttri->Assign(fStringAttri);
				tmpNumberAttri->Assign(fNumberAttri);
				tmpKeyAttri->Assign(fKeyAttri);
				tmpSymbolAttri->Assign(fSymbolAttri);
				tmpCommentAttri->Assign(fCommentAttri);
				tmpIdentifierAttri->Assign(fIdentifierAttri);
				tmpInvalidAttri->Assign(fInvalidAttri);
				tmpSpaceAttri->Assign(fSpaceAttri);
				tmpDirecAttri->Assign(fDirecAttri);
				result = ReadCPPBSetting(sl->Strings[settingIndex], fCommentAttri, L"Comment") && ReadCPPBSetting(sl->Strings[settingIndex], fIdentifierAttri, L"Identifier") && ReadCPPBSetting(sl->Strings[settingIndex], fInvalidAttri, L"Illegal Char") && ReadCPPBSetting(sl->Strings[settingIndex], fKeyAttri, L"Reserved word") && ReadCPPBSetting(sl->Strings[settingIndex], fNumberAttri, L"Integer") && ReadCPPBSetting(sl->Strings[settingIndex], fSpaceAttri, L"Whitespace") && ReadCPPBSetting(sl->Strings[settingIndex], fStringAttri, L"String") && ReadCPPBSetting(sl->Strings[settingIndex], fSymbolAttri, L"Symbol") && ReadCPPBSetting(sl->Strings[settingIndex], fDirecAttri, L"Preprocessor");
				if(!result)
				{
					fStringAttri->Assign(tmpStringAttri);
					fString2Attri->Assign(tmpStringAttri);
					fNumberAttri->Assign(tmpNumberAttri);
					fKeyAttri->Assign(tmpKeyAttri);
					fKey2Attri->Assign(tmpKeyAttri);
					fSymbolAttri->Assign(tmpSymbolAttri);
					fCommentAttri->Assign(tmpCommentAttri);
					fIdentifierAttri->Assign(tmpIdentifierAttri);
					fInvalidAttri->Assign(tmpInvalidAttri);
					fSpaceAttri->Assign(tmpSpaceAttri);
					fDirecAttri->Assign(tmpDirecAttri);
				}
				delete tmpStringAttri;
				delete tmpNumberAttri;
				delete tmpKeyAttri;
				delete tmpSymbolAttri;
				delete tmpCommentAttri;
				delete tmpIdentifierAttri;
				delete tmpInvalidAttri;
				delete tmpSpaceAttri;
				delete tmpDirecAttri;
			}
		}
		__finally
		{
			delete sl;
		}
		return result;
	}; /* ReadCPPBSettings */
	result = ReadCPPBSettings(settingIndex);
	return result;
} /* TSynUnrealSyn.UseUserSettings */

/*#static*/
String __fastcall TSynUnrealSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangUnreal;
	return result;
}

/*#static*/
TSynHighlighterCapabilities __fastcall TSynUnrealSyn::GetCapabilities()
{
	TSynHighlighterCapabilities result;
	result = inherited::GetCapabilities() + SynHighlighterUnreal__3;
	return result;
}

String __fastcall TSynUnrealSyn::GetSampleSource()
{
	String result;
	result = L"//----Comment-----------------------------------------------------------\x0d\x0a"
	           L"class TestObject expands Object native;\x0d\x0a"
	           L"\x0d\x0a"
	           L"#exec MESH    IMPORT     MESH=Something ANIVFILE=MODELS\\Something.3D DATAFILE=MODELS\\Something.3D X=0 Y=0 Z=0 MLOD=0\x0d\x0a"
	           L"\x0d\x0a"
	           L"var() Sound HitSound;\x0d\x0a"
	           L"function Cast()\x0d\x0a"
	           L"{\x0d\x0a"
	           L"  Super.Cast();\x0d\x0a"
	           L"  CastTime = 50;\x0d\x0a"
	           L"  GatherEffect = Spawn( class'SomethingCorona',,, GetStartLoc(), Pawn(Owner).ViewRotation );\x0d\x0a"
	           L"  GatherEffect.SetFollowPawn( Pawn(Owner) );\x0d\x0a"
	           L"}\x0d\x0a"
	           L"\x0d\x0a"
	           L"defaultproperties\x0d\x0a"
	           L"{\x0d\x0a"
	           L"  PickupMessage=\"You have picked up a thing.\"\x0d\x0a"
	           L"}";
	return result;
}

/*#static*/
String __fastcall TSynUnrealSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangUnreal;
	return result;
}
static bool SynHighlighterUnreal_Initialized = false;

void SynHighlighterUnreal_initialization()
{
	if(SynHighlighterUnreal_Initialized)
		return;
	
	SynHighlighterUnreal_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynUnrealSyn));
}
class SynHighlighterUnreal_unit
{
public:
	SynHighlighterUnreal_unit()
	{
		SynHighlighterUnreal_initialization();
	}
};

SynHighlighterUnreal_unit _SynHighlighterUnreal_unit;

}  // namespace SynHighlighterUnreal

