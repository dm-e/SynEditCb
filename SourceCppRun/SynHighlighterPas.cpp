
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterPas.h"
#include "SynEditStrConst.h"
#include "SynEditDelphiInstances.hpp"
#include "d2c_syshelper.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditmiscclasses;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Regularexpressions;

namespace Synhighlighterpas
{
#define Synhighlighterpas__0 (System::Set<TRangeState, TRangeState::rsANil, TRangeState::rsUnKnown>() << rsProperty << rsExports)
#define Synhighlighterpas__1 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterpas__2 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterpas__3 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterpas__4 (TRegExOptions() << roIgnoreCase)
#define Synhighlighterpas__5 (TRegExOptions() << roIgnoreCase)
#define Synhighlighterpas__6 (TRegExOptions() << roIgnoreCase)
#define Synhighlighterpas__7 (System::Set<TRangeState, TRangeState::rsANil, TRangeState::rsUnKnown>() << rsDirective << rsDirectiveAsm)
#define Synhighlighterpas__8 (System::Set<TRangeState, TRangeState::rsANil, TRangeState::rsUnKnown>() << rsBorAsm << rsDirectiveAsm)
#define Synhighlighterpas__9 (System::Set<TRangeState, TRangeState::rsANil, TRangeState::rsUnKnown>() << rsProperty << rsExports)
#define Synhighlighterpas__10 (System::Set<TtkTokenKind, TtkTokenKind::tkSymbol, TtkTokenKind::tkType>() << tkNull << tkComment << tkDirec << tkSpace)
#define Synhighlighterpas__11 TReplaceFlags()
#define Synhighlighterpas__12 (TSynHighlighterCapabilities() << hcUserSettings)
#define Synhighlighterpas__13 (TRangeStates() << rsAnsi)
#define Synhighlighterpas__14 (TRangeStates() << rsAsm << rsAnsiAsm << rsBorAsm << rsDirectiveAsm)
#define Synhighlighterpas__15 (TRangeStates() << rsBor)
#define Synhighlighterpas__16 (TRangeStates() << rsDirective)


  // if the language is case-insensitive keywords *must* be in lowercase
const String KeyWords[132/*# range 0..131*/] = {L"absolute", L"abstract", L"and", L"ansistring", L"array", L"as", L"asm", L"assembler", L"automated", L"begin"
                    , L"boolean", L"byte", L"bytebool", L"cardinal", L"case", L"cdecl", L"class", L"const", L"constructor", L"contains", L"currency"
                    , L"default", L"deprecated", L"destructor", L"dispid", L"dispinterface", L"div", L"do", L"double", L"downto", L"dynamic"
                    , L"else", L"end", L"except", L"export", L"exports", L"extended", L"external", L"far", L"file", L"final", L"finalization", L"finally"
                    , L"for", L"forward", L"function", L"goto", L"helper", L"if", L"implementation", L"implements", L"in", L"index", L"inherited"
                    , L"initialization", L"inline", L"int64", L"integer", L"interface", L"is", L"label", L"library", L"longbool", L"longint"
                    , L"longword", L"message", L"mod", L"name", L"near", L"nil", L"nodefault", L"not", L"object", L"of", L"on", L"operator", L"or"
                    , L"out", L"overload", L"override", L"package", L"packed", L"pascal", L"platform", L"private", L"procedure", L"program", L"property"
                    , L"protected", L"public", L"published", L"raise", L"read", L"readonly", L"real48", L"record", L"register", L"reintroduce", L"repeat"
                    , L"requires", L"resourcestring", L"safecall", L"sealed", L"set", L"shl", L"shortint", L"shortstring", L"shr", L"single", L"smallint"
                    , L"stdcall", L"stored", L"string", L"stringresource", L"then", L"threadvar", L"to", L"try", L"type", L"unit", L"until", L"uses"
                    , L"var", L"virtual", L"while", L"string", L"with", L"word", L"wordbool", L"write", L"writeonly", L"xor"};
const int KeyIndices[641/*# range 0..640*/] = {-1, -1, -1, 34, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 122, -1, 78, -1, -1, 11, -1, -1, -1, -1, -1, -1, -1, 128, -1, -1, -1, -1, -1, -1
                    , -1, -1, 107, -1, -1, 31, -1, -1, -1, -1, -1, -1, -1, -1, 35, -1, -1, -1, 4, 79, -1, 36, -1, -1, 117, -1, -1, -1, -1, -1, 49, -1, -1, -1, 77, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 105, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 113, -1, 112, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, 72, -1, 40, -1, 121, 83, 98, -1, -1, -1, -1, -1, 38, -1, -1, -1, -1
                    , 74, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 100, -1, 86, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 64, 32, -1, -1, -1, -1, 58, 44, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 67, -1, 6, 13, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 71, -1, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, -1, 3, -1, 43, -1, -1, -1, 96, -1, -1, 53, -1, 76, -1, -1, -1, -1, -1, -1, -1, -1, -1, 104, -1, -1, -1, -1, -1, 12
                    , -1, -1, -1, -1, -1, -1, 37, 90, -1, 126, -1, -1, 85, 81, -1, -1, -1, -1, -1, -1, -1, 52, -1, -1, -1, 124, -1, -1, -1, 69, -1, -1, -1, -1, -1, -1, 42, -1, -1, 29, -1, 127, -1, -1, -1, -1, -1, -1, 129
                    , -1, -1, -1, 16, -1, -1, 108, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1, 101, 61, -1, -1, 26, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 59, 131, -1, -1, -1, -1, -1, -1, -1, -1, 65, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, 41, 2, -1, -1, 82, -1, -1, -1, 30, -1, -1, 33, -1, -1, -1, -1, 95, -1, -1, -1, -1, -1, -1, -1, 114, -1, 51, -1, 9, -1, 21, -1, 0, -1, -1, 66, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, 55, 14, 18, -1, -1, -1, -1, 110, -1, -1, -1, -1, 10, -1, -1, -1, 97, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1, -1, -1, -1, -1, 8, 70, -1, -1, -1, -1, -1, -1, 27, 116
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 87, 111, -1, -1, 25, 50, -1, 57, -1, 24, -1, -1, -1, -1, -1, 39, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 109, -1, 123, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, 130, -1, -1, -1, -1, -1, -1, -1, -1, 102, -1, -1, -1, -1, 17, 63, -1, -1, -1, -1, -1, -1, -1, -1, -1, 125, -1, -1, -1, -1, 103, -1, -1, -1, 99, -1, -1, -1, -1, -1, -1, -1, 120, -1, -1
                    , -1, -1, -1, -1, -1, 119, -1, 118, -1, -1, -1, -1, 88, 7, -1, -1, -1, -1, -1, -1, -1, 46, 89, -1, -1, -1, -1, -1, 62, -1, -1, -1, -1, -1, -1, -1, 45, -1, -1, 54, -1, 75, -1, -1, 56, -1, -1, -1, -1, -1
                    , -1, 68, -1, 115, -1, 60, -1, -1, 91, -1, -1, -1, -1, -1, -1, 93, -1, -1, 106, -1, 94, 73, -1, -1, -1, -1, -1, 22, -1, -1, -1, 84, -1, 92, -1, -1, 47, -1, -1, -1, -1, -1, 23, -1, -1, -1, -1, -1, -1, 80};

/*$Q-*/

unsigned int __fastcall TSynPasSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 526 + int((*Str)) * 502);
		++Str;
	}
	result = (unsigned int) (result % 641);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynPasSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkSymbol;
	unsigned int Key = 0;
	fToIdent = MayBe;
	Key = HashKey(MayBe);
	if(Key <= 640 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[Key](KeyIndices[Key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynPasSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 640 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[215] = FuncType;
	fIdentFuncTable[412] = FuncType;
	fIdentFuncTable[26] = FuncType;
	fIdentFuncTable[242] = FuncType;
	fIdentFuncTable[188] = FuncType;
	fIdentFuncTable[428] = FuncType;
	fIdentFuncTable[310] = FuncType;
	fIdentFuncTable[62] = FuncType;
	fIdentFuncTable[585] = FuncType;
	fIdentFuncTable[462] = FuncType;
	fIdentFuncTable[569] = FuncType;
	fIdentFuncTable[511] = FuncType;
	fIdentFuncTable[166] = FuncType;
	fIdentFuncTable[611] = FuncType;
	fIdentFuncTable[86] = FuncType;
	fIdentFuncTable[609] = FuncType;
	fIdentFuncTable[298] = FuncType;
	fIdentFuncTable[484] = FuncType;
	fIdentFuncTable[521] = FuncType;
	fIdentFuncTable[284] = FuncType;
	fIdentFuncTable[34] = FuncType;
	fIdentFuncTable[111] = FuncType;
	fIdentFuncTable[187] = FuncAsm;
	fIdentFuncTable[434] = FuncAutomated;
	fIdentFuncTable[419] = FuncCdecl;
	fIdentFuncTable[353] = FuncContains;
	fIdentFuncTable[618] = FuncDeprecated;
	fIdentFuncTable[464] = FuncDispid;
	fIdentFuncTable[459] = FuncDispinterface;
	fIdentFuncTable[167] = FuncEnd;
	fIdentFuncTable[55] = FuncExports;
	fIdentFuncTable[126] = FuncFinal;
	fIdentFuncTable[355] = FuncFinalization;
	fIdentFuncTable[627] = FuncHelper;
	fIdentFuncTable[460] = FuncImplements;
	fIdentFuncTable[264] = FuncIndex;
	fIdentFuncTable[185] = FuncName;
	fIdentFuncTable[435] = FuncNodefault;
	fIdentFuncTable[582] = FuncOperator;
	fIdentFuncTable[23] = FuncOverload;
	fIdentFuncTable[640] = FuncPackage;
	fIdentFuncTable[129] = FuncPlatform;
	fIdentFuncTable[455] = FuncProperty;
	fIdentFuncTable[624] = FuncRead;
	fIdentFuncTable[606] = FuncReadonly;
	fIdentFuncTable[416] = FuncReintroduce;
	fIdentFuncTable[530] = FuncRequires;
	fIdentFuncTable[153] = FuncResourcestring;
	fIdentFuncTable[312] = FuncSafecall;
	fIdentFuncTable[505] = FuncSealed;
	fIdentFuncTable[407] = FuncStdcall;
	fIdentFuncTable[456] = FuncStored;
	fIdentFuncTable[109] = FuncStringresource;
	fIdentFuncTable[594] = FuncThreadvar;
	fIdentFuncTable[291] = FuncWrite;
	fIdentFuncTable[496] = FuncWriteonly;
	for(stop = 640 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynPasSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkSymbol;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncAsm(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(KeyWords[Index]))
	{
		result = tkKey;
		fRange = rsAsm;
		fAsmStart = true;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncAutomated(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi3) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncCdecl(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi2) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncContains(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(PackageSource && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncDeprecated(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi6) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncDispid(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi3) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncDispinterface(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi3) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncEnd(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(KeyWords[Index]))
	{
		result = tkKey;
		fRange = rsUnKnown;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncExports(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(KeyWords[Index]))
	{
		result = tkKey;
		fRange = rsExports;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncFinal(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi8) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncFinalization(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi2) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncHelper(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi8) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncImplements(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((fRange == rsProperty) && (DelphiVersion >= dvDelphi4) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncIndex(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((Synhighlighterpas__0.Contains(fRange)) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncName(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((fRange == rsExports) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncNodefault(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((fRange == rsProperty) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncOperator(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi8) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncOverload(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi4) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncPackage(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(PackageSource && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncPlatform(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi6) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncProperty(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(KeyWords[Index]))
	{
		result = tkKey;
		fRange = rsProperty;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncRead(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((fRange == rsProperty) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncReadonly(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi3) && (fRange == rsProperty) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncReintroduce(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi4) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncRequires(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(PackageSource && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncResourcestring(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi3) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncSafecall(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi3) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncSealed(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi8) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncStdcall(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi2) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncStored(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((fRange == rsProperty) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncStringresource(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi3) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncThreadvar(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi3) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncWrite(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((fRange == rsProperty) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncWriteonly(int Index)
{
	TtkTokenKind result = tkSymbol;
	if((DelphiVersion >= dvDelphi3) && (fRange == rsProperty) && IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::FuncType(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkType;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynPasSyn::TSynPasSyn(TComponent* AOwner)
 : inherited(AOwner),
			fAsmStart(false),
			fRange(rsANil),
			fTokenID(tkSymbol),
			fStringAttri(nullptr),
			fCharAttri(nullptr),
			fNumberAttri(nullptr),
			fFloatAttri(nullptr),
			fHexAttri(nullptr),
			fKeyAttri(nullptr),
			fSymbolAttri(nullptr),
			fAsmAttri(nullptr),
			fCommentAttri(nullptr),
			fDirecAttri(nullptr),
			fIdentifierAttri(nullptr),
			fSpaceAttri(nullptr),
			fDelphiVersion(dvDelphi1),
			fPackageSource(false),
			fTypeAttri(nullptr)
{
	fCaseSensitive = false;
	fDelphiVersion = LastDelphiVersion;
	fPackageSource = true;
	fAsmAttri = new TSynHighlighterAttributes(SYNS_AttrAssembler, SYNS_FriendlyAttrAssembler);
	AddAttribute(fAsmAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterpas__1;
	AddAttribute(fCommentAttri);
	fDirecAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	fDirecAttri->Style = Synhighlighterpas__2;
	AddAttribute(fDirecAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterpas__3;
	AddAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	AddAttribute(fNumberAttri);
	fFloatAttri = new TSynHighlighterAttributes(SYNS_AttrFloat, SYNS_FriendlyAttrFloat);
	AddAttribute(fFloatAttri);
	fHexAttri = new TSynHighlighterAttributes(SYNS_AttrHexadecimal, SYNS_FriendlyAttrHexadecimal);
	AddAttribute(fHexAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	AddAttribute(fStringAttri);
	fCharAttri = new TSynHighlighterAttributes(SYNS_AttrCharacter, SYNS_FriendlyAttrCharacter);
	AddAttribute(fCharAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	AddAttribute(fSymbolAttri);
	fTypeAttri = new TSynHighlighterAttributes(SYNS_AttrDataType, SYNS_FriendlyAttrDataType);
	AddAttribute(fTypeAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fRange = rsUnKnown;
	fDefaultFilter = SYNS_FilterPascal;

//++ CodeFolding
	RE_BlockBegin = TRegEx(L"\\b(begin|record|class)\\b", Synhighlighterpas__4);
	RE_BlockEnd = TRegEx(L"\\bend\\b", Synhighlighterpas__5);
	RE_Code = TRegEx(L"^\\s*(function|procedure)\\b", Synhighlighterpas__6);
//-- CodeFolding
}

void __fastcall TSynPasSyn::AddressOpProc()
{
	fTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'@')
		++Run;
}

void __fastcall TSynPasSyn::AsciiCharProc()
{

	auto IsAsciiChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'$':
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	fTokenID = tkChar;
	++Run;
	while(IsAsciiChar())
		++Run;
}

void __fastcall TSynPasSyn::BorProc()
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
			if(Synhighlighterpas__7.Contains(fRange))
				fTokenID = tkDirec;
			else
				fTokenID = tkComment;
			do
			{
				if(fLine[Run] == L'}')
				{
					++Run;
					if(Synhighlighterpas__8.Contains(fRange))
						fRange = rsAsm;
					else
						fRange = rsUnKnown;
					break;
				}
				++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
	}
}

void __fastcall TSynPasSyn::BraceOpenProc()
{
	if(fLine[Run + 1] == L'$')
	{
		if(fRange == rsAsm)
			fRange = rsDirectiveAsm;
		else
			fRange = rsDirective;
	}
	else
	{
		if(fRange == rsAsm)
			fRange = rsBorAsm;
		else
			fRange = rsBor;
	}
	BorProc();
}

void __fastcall TSynPasSyn::ColonOrGreaterProc()
{
	fTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynPasSyn::CRProc()
{
	fTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynPasSyn::IdentProc()
{
	fTokenID = IdentKind(fLine + Run);
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynPasSyn::IntegerProc()
{

	auto IsIntegerChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	++Run;
	fTokenID = tkHex;
	while(IsIntegerChar())
		++Run;
}

void __fastcall TSynPasSyn::LFProc()
{
	fTokenID = tkSpace;
	++Run;
}

void __fastcall TSynPasSyn::LowerProc()
{
	fTokenID = tkSymbol;
	++Run;
	if((fLine[Run] == L'=') || (fLine[Run] == L'>'))
		++Run;
}

void __fastcall TSynPasSyn::NullProc()
{
	fTokenID = tkNull;
	++Run;
}

void __fastcall TSynPasSyn::NumberProc()
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
	fTokenID = tkNumber;
	while(IsNumberChar())
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Run + 1] == L'.')
				goto label0;
			else
				fTokenID = tkFloat;
			break;
			case L'e':
			case L'E':
			fTokenID = tkFloat;
			break;
			case L'-':
			case L'+':
			{
				if(fTokenID != tkFloat)
					goto label1;
				if((fLine[Run - 1] != L'e') && (fLine[Run - 1] != L'E'))
					goto label2; //float, but it ends here
			}
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label0:;
	label1:;
	label2:;
}

void __fastcall TSynPasSyn::PointProc()
{
	fTokenID = tkSymbol;
	++Run;
	if((fLine[Run] == L'.') || (fLine[Run - 1] == L')'))
		++Run;
}

void __fastcall TSynPasSyn::AnsiProc()
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
		fTokenID = tkComment;
		do
		{
			if((fLine[Run] == L'*') && (fLine[Run + 1] == L')'))
			{
				Run += 2;
				if(fRange == rsAnsiAsm)
					fRange = rsAsm;
				else
					fRange = rsUnKnown;
				break;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
		break;
	}
}

void __fastcall TSynPasSyn::RoundOpenProc()
{
	++Run;
	switch(fLine[Run])
	{
		case L'*':
		{
			++Run;
			if(fRange == rsAsm)
				fRange = rsAnsiAsm;
			else
				fRange = rsAnsi;
			fTokenID = tkComment;
			if(!IsLineEnd(Run))
				AnsiProc();
		}
		break;
		case L'.':
		{
			++Run;
			fTokenID = tkSymbol;
		}
		break;
		default:
		fTokenID = tkSymbol;
		break;
	}
}

void __fastcall TSynPasSyn::SemicolonProc()
{
	++Run;
	fTokenID = tkSymbol;
	if(Synhighlighterpas__9.Contains(fRange))
		fRange = rsUnKnown;
}

void __fastcall TSynPasSyn::SlashProc()
{
	++Run;
	if((fLine[Run] == L'/') && (fDelphiVersion > dvDelphi1))
	{
		fTokenID = tkComment;
		do
		{
			++Run;
		}
		while(!IsLineEnd(Run));
	}
	else
	fTokenID = tkSymbol;
}

void __fastcall TSynPasSyn::SpaceProc()
{
	++Run;
	fTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynPasSyn::StringProc()
{
	fTokenID = tkString;
	++Run;
	while(!IsLineEnd(Run))
	{
		if(fLine[Run] == L'\x27')
		{
			++Run;
			if(fLine[Run] != L'\x27')
				break;
		}
		++Run;
	}
}

void __fastcall TSynPasSyn::SymbolProc()
{
	++Run;
	fTokenID = tkSymbol;
}

void __fastcall TSynPasSyn::UnknownProc()
{
	++Run;
	fTokenID = tkUnknown;
}

void __fastcall TSynPasSyn::Next()
{
	fAsmStart = false;
	fTokenPos = Run;
	switch(fRange)
	{
		case rsAnsi:
		case rsAnsiAsm:
		AnsiProc();
		break;
		case rsBor:
		case rsBorAsm:
		case rsDirective:
		case rsDirectiveAsm:
		BorProc();
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
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			case L'\x0b':
			case L'\x0c':
			case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
			 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
			SpaceProc();
			break;
			case L'#':
			AsciiCharProc();
			break;
			case L'$':
			IntegerProc();
			break;
			case L'\x27':
			StringProc();
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			NumberProc();
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
			case L'{':
			BraceOpenProc();
			break;
			case L'}':
			case L'!':
			case L'\"':
			case L'%':
			case L'&':
			case 40: case 41: case 42: case 43: case 44: case 45: case 46: case 47:
			case 58: case 59: case 60: case 61: case 62: case 63: case 64:
			case 91: case 92: case 93: case 94:
			case L'`':
			case L'~':
			{
				switch(fLine[Run])
				{
					case L'(':
					RoundOpenProc();
					break;
					case L'.':
					PointProc();
					break;
					case L';':
					SemicolonProc();
					break;
					case L'/':
					SlashProc();
					break;
					case L':':
					case L'>':
					ColonOrGreaterProc();
					break;
					case L'<':
					LowerProc();
					break;
					case L'@':
					AddressOpProc();
					break;
					default:
					SymbolProc();
					break;
				}
			}
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynPasSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynPasSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynPasSyn::GetTokenID()
{
	TtkTokenKind result = tkSymbol;
	if(!fAsmStart && (fRange == rsAsm) && !(Synhighlighterpas__10.Contains(fTokenID)))
		result = tkAsm;
	else
		result = fTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynPasSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkAsm:
		result = fAsmAttri;
		break;
		case tkComment:
		result = fCommentAttri;
		break;
		case tkDirec:
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
		case tkFloat:
		result = fFloatAttri;
		break;
		case tkHex:
		result = fHexAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkChar:
		result = fCharAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkType:
		result = fTypeAttri;
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

int __fastcall TSynPasSyn::GetTokenKind()
{
	int result = 0;
	result = int(GetTokenID());
	return result;
}

void* __fastcall TSynPasSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) fRange);
	return result;
}

void __fastcall TSynPasSyn::SetRange(void* Value)
{
	fRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynPasSyn::ResetRange()
{
	fRange = rsUnKnown;
}

void __fastcall TSynPasSyn::EnumUserSettings(TStrings* DelphiVersions)
{

	auto LoadKeyVersions = [&](const String Key, const String Prefix) -> void 
	{
		TStringList* Versions = nullptr;
		int i = 0;
		/*# with TBetterRegistry.Create do */
		{
			auto with0 = new TBetterRegistry();
			try
			{
				with0->RootKey = HKEY_LOCAL_MACHINE;
				if(with0->OpenKeyReadOnly(Key))
				{
					try
					{
						Versions = new TStringList();
						try
						{
							int stop = 0;
							with0->GetKeyNames(Versions);
							for(stop = Versions->Count - 1, i = 0; i <= stop; i++)
							{
								DelphiVersions->Add(Prefix + Versions->Strings[i]);
							}
						}
						__finally
						{
							FreeAndNil(&Versions);
						}
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
	};
  /* returns the user settings that exist in the registry */
  // See UseUserSettings below where these strings are used
	LoadKeyVersions(L"\\SOFTWARE\\Borland\\Delphi", L"");
	LoadKeyVersions(L"\\SOFTWARE\\Borland\\BDS", BDSVersionPrefix);
	LoadKeyVersions(L"\\SOFTWARE\\CodeGear\\BDS", BDSVersionPrefix);
}
// Possible parameter values:
//   index into TStrings returned by EnumUserSettings
// Possible return values:
//   True : settings were read and used
//   False: problem reading settings or invalid version specified - old settings
//          were preserved

bool __fastcall TSynPasSyn::UseUserSettings(int VersionIndex)
{
	bool result = false;

	auto ReadDelphiSettings = [&](int settingIndex) -> bool 
	{
		bool result = false;

		auto ReadDelphiSetting = [&](String settingTag, TSynHighlighterAttributes* attri, String key) -> bool 
		{
			bool result = false;
			Currency Version = 0.0;
			String VersionStr;

			auto ReadDelphi2Or3 = [&](String settingTag, TSynHighlighterAttributes* attri, String name) -> bool 
			{
				bool result = false;
				int i = 0;
				int stop = 0;
				for(stop = name.Length(), i = 1; i <= stop; i++)
				{
					if(name[i] == L' ')
						name[i] = L'_';
				}
				result = attri->LoadFromBorlandRegistry(HKEY_CURRENT_USER, String(L"\\Software\\Borland\\Delphi\\") + settingTag
	           + L"\\Highlight", name, true);
				return result;
			}; /* ReadDelphi2Or3 */

			auto ReadDelphi4OrMore = [&](String settingTag, TSynHighlighterAttributes* attri, String key) -> bool 
			{
				bool result = false;
				result = attri->LoadFromBorlandRegistry(HKEY_CURRENT_USER, String(L"\\Software\\Borland\\Delphi\\") + settingTag
	           + L"\\Editor\\Highlight", key, false);
				return result;
			}; /* ReadDelphi4OrMore */

			auto ReadDelphi8To2007 = [&](String settingTag, TSynHighlighterAttributes* attri, String key) -> bool 
			{
				bool result = false;
				result = attri->LoadFromBorlandRegistry(HKEY_CURRENT_USER, String(L"\\Software\\Borland\\BDS\\") + settingTag
	           + L"\\Editor\\Highlight", key, false);
				return result;
			}; /* ReadDelphi8OrMore */

			auto ReadDelphi2009OrMore = [&](String settingTag, TSynHighlighterAttributes* attri, String key) -> bool 
			{
				bool result = false;
				result = attri->LoadFromBorlandRegistry(HKEY_CURRENT_USER, String(L"\\Software\\CodeGear\\BDS\\") + settingTag
	           + L"\\Editor\\Highlight", key, false);
				return result;
			}; /* ReadDelphi2009OrMore */ /* ReadDelphiSetting */
			try
			{
				if(Pos(L"BDS", settingTag) == 1) // BDS product
				{
					VersionStr = settingTag.SubString(wcslen(BDSVersionPrefix) + 1, 999);
					Version = 0;
					if(!TryStrToCurr(StringReplace(VersionStr, L".", String(FormatSettings.DecimalSeparator), Synhighlighterpas__11), Version))
					{
						result = false;
						return result;
					}
					if(Version >= 6)
						result = ReadDelphi2009OrMore(VersionStr, attri, key);
					else
						result = ReadDelphi8To2007(VersionStr, attri, key);
				}
				else
 // Borland Delphi 7 or earlier
				{
					if((settingTag[1] == L'2') || (settingTag[1] == L'3'))
						result = ReadDelphi2Or3(settingTag, attri, key);
					else
						result = ReadDelphi4OrMore(settingTag, attri, key);
				}
			}
			catch(...)
			{
				result = false;
			}
			return result;
		}; /* ReadDelphiSetting */
		TSynHighlighterAttributes* tmpAsmAttri = nullptr;
		TSynHighlighterAttributes* tmpCommentAttri = nullptr;
		TSynHighlighterAttributes* tmpIdentAttri = nullptr;
		TSynHighlighterAttributes* tmpKeyAttri = nullptr;
		TSynHighlighterAttributes* tmpNumberAttri = nullptr;
		TSynHighlighterAttributes* tmpSpaceAttri = nullptr;
		TSynHighlighterAttributes* tmpStringAttri = nullptr;
		TSynHighlighterAttributes* tmpSymbolAttri = nullptr;
		TStringList* iVersions = nullptr;
		String iVersionTag; /* ReadDelphiSettings */
		iVersions = new TStringList();
		try
		{
			EnumUserSettings(iVersions);
			if((settingIndex < 0) || (settingIndex >= iVersions->Count))
			{
				result = false;
				return result;
			}
			iVersionTag = iVersions->Strings[settingIndex];
		}
		__finally
		{
			delete iVersions;
		}
		tmpAsmAttri = new TSynHighlighterAttributes(L"", L"");
		tmpCommentAttri = new TSynHighlighterAttributes(L"", L"");
		tmpIdentAttri = new TSynHighlighterAttributes(L"", L"");
		tmpKeyAttri = new TSynHighlighterAttributes(L"", L"");
		tmpNumberAttri = new TSynHighlighterAttributes(L"", L"");
		tmpSpaceAttri = new TSynHighlighterAttributes(L"", L"");
		tmpStringAttri = new TSynHighlighterAttributes(L"", L"");
		tmpSymbolAttri = new TSynHighlighterAttributes(L"", L"");
		result = ReadDelphiSetting(iVersionTag, tmpAsmAttri, L"Assembler") && ReadDelphiSetting(iVersionTag, tmpCommentAttri, L"Comment") && ReadDelphiSetting(iVersionTag, tmpIdentAttri, L"Identifier") && ReadDelphiSetting(iVersionTag, tmpKeyAttri, L"Reserved word") && ReadDelphiSetting(iVersionTag, tmpNumberAttri, L"Number") && ReadDelphiSetting(iVersionTag, tmpSpaceAttri, L"Whitespace") && ReadDelphiSetting(iVersionTag, tmpStringAttri, L"String") && ReadDelphiSetting(iVersionTag, tmpSymbolAttri, L"Symbol");
		if(result)
		{
			fAsmAttri->AssignColorAndStyle(tmpAsmAttri);
			fCharAttri->AssignColorAndStyle(tmpStringAttri); /* Delphi lacks Char attribute */
			fCommentAttri->AssignColorAndStyle(tmpCommentAttri);
			fDirecAttri->AssignColorAndStyle(tmpCommentAttri); /* Delphi lacks Directive attribute */
			fFloatAttri->AssignColorAndStyle(tmpNumberAttri); /* Delphi lacks Float attribute */
			fHexAttri->AssignColorAndStyle(tmpNumberAttri); /* Delphi lacks Hex attribute */
			fIdentifierAttri->AssignColorAndStyle(tmpIdentAttri);
			fKeyAttri->AssignColorAndStyle(tmpKeyAttri);
			fNumberAttri->AssignColorAndStyle(tmpNumberAttri);
			fSpaceAttri->AssignColorAndStyle(tmpSpaceAttri);
			fStringAttri->AssignColorAndStyle(tmpStringAttri);
			fSymbolAttri->AssignColorAndStyle(tmpSymbolAttri);
		}
		delete tmpAsmAttri;
		delete tmpCommentAttri;
		delete tmpIdentAttri;
		delete tmpKeyAttri;
		delete tmpNumberAttri;
		delete tmpSpaceAttri;
		delete tmpStringAttri;
		delete tmpSymbolAttri;
		return result;
	};
	result = ReadDelphiSettings(VersionIndex);
	return result;
}

String __fastcall TSynPasSyn::GetSampleSource()
{
	String result;
	result = L"{ Syntax highlighting }\x0d\x0a"
	           L"procedure TForm1.Button1Click(Sender: TObject);\x0d\x0a"
	           L"var\x0d\x0a"
	           L"  Number, I, X: Integer;\x0d\x0a"
	           L"begin\x0d\x0a"
	           L"  Number := 123456;\x0d\x0a"
			   L"  Caption := 'The Number is' + \" + IntToStr(Number);\x0d\x0a"
			   L"  for I := 0 to Number do\x0d\x0a"
	           L"  begin\x0d\x0a"
	           L"    Inc(X);\x0d\x0a"
	           L"    Dec(X);\x0d\x0a"
	           L"    X := X + 1.0;\x0d\x0a"
	           L"    X := X - $5E;\x0d\x0a"
	           L"  end;\x0d\x0a"
	           L"  {$R+}\x0d\x0a"
	           L"  asm\x0d\x0a"
	           L"    mov AX, 1234H\x0d\x0a"
	           L"    mov Number, AX\x0d\x0a"
	           L"  end;\x0d\x0a"
	           L"  {$R-}\x0d\x0a"
	           L"end;";
	return result;
}

/*#static*/
String __fastcall TSynPasSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangPascal;
	return result;
}

/*#static*/
TSynHighlighterCapabilities __fastcall TSynPasSyn::GetCapabilities()
{
	TSynHighlighterCapabilities result;
	result = inherited::GetCapabilities() + Synhighlighterpas__12;
	return result;
}

bool __fastcall TSynPasSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterPascal;
	return result;
}

void __fastcall TSynPasSyn::SetDelphiVersion(TDelphiVersion Value)
{
	if(fDelphiVersion != Value)
	{
		fDelphiVersion = Value;
		if((fDelphiVersion < dvDelphi3) && fPackageSource)
			fPackageSource = false;
		DefHighlightChange(this);
	}
}

void __fastcall TSynPasSyn::SetPackageSource(bool Value)
{
	if(fPackageSource != Value)
	{
		fPackageSource = Value;
		if(fPackageSource && (fDelphiVersion < dvDelphi3))
			fDelphiVersion = dvDelphi3;
		DefHighlightChange(this);
	}
}

/*#static*/
String __fastcall TSynPasSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangPascal;
	return result;
}

//++ CodeFolding
typedef System::Set<TRangeState, TRangeState::rsANil, TRangeState::rsUnKnown> TRangeStates;
const int FT_Standard = 1;  // begin end, class end, record end
const int FT_Comment = 11;
const int FT_Asm = 12;
const int FT_HereDocDouble = 13;
const int FT_HereDocSingle = 14;
const int FT_ConditionalDirective = 15;
const int FT_CodeDeclaration = 16;
const int FT_CodeDeclarationWithBody = 17;
const int FT_Implementation = 18;

void __fastcall TSynPasSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	String CurLine;
	__int64 Line = 0;
	bool ok = false;

	auto BlockDelimiter = [&](int Line) -> bool 
	{
		bool result = false;
		int Index = 0;
		TMatchCollection mcb = {};
		TMatchCollection mce = {};
		TMatch match = {};
		result = false;
		mcb = RE_BlockBegin.Matches(CurLine);
		if(mcb.Count > 0)
      // Char must have proper highlighting (ignore stuff inside comments...)
		{
			Index = mcb.Item[0].Index;
			if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Index) != fCommentAttri)
			{
				ok = false;
        // And ignore lines with both opening and closing chars in them
				for(int iFor0 = 0; iFor0 < RE_BlockEnd.Matches(CurLine).Count; iFor0++)
				{
					TMatch match = RE_BlockEnd.Matches(CurLine).Item[iFor0];
					if(match.Index > Index)
					{
						ok = true;
						break;
					}
				}
				if(!ok)
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
		String S;
		result = false;
		S = TrimLeft(CurLine);
		if(UpperCase(S.SubString(1, 8)) == L"{$REGION")
		{
			FoldRanges->StartFoldRange(Line + 1, FoldRegionType);
			result = true;
		}
		else
		{
			if(UpperCase(S.SubString(1, 11)) == L"{$ENDREGION")
			{
				FoldRanges->StopFoldRange(Line + 1, FoldRegionType);
				result = true;
			}
		}
		return result;
	};

	auto ConditionalDirective = [&](int Line) -> bool 
	{
		bool result = false;
		String S;
		result = false;
		S = TrimLeft(CurLine);
		if(UpperCase(S.SubString(1, 7)) == L"{$IFDEF")
		{
			FoldRanges->StartFoldRange(Line + 1, FT_ConditionalDirective);
			result = true;
		}
		else
		{
			if(UpperCase(S.SubString(1, 7)) == L"{$ENDIF")
			{
				FoldRanges->StopFoldRange(Line + 1, FT_ConditionalDirective);
				result = true;
			}
		}
		return result;
	};

	auto IsMultiLineStatement = [&](int Line, TRangeStates Ranges, bool Fold, int FoldType = 1) -> bool 
	{
		bool result = false;
		result = true;
		if(Ranges.Contains((TRangeState)(NativeInt)GetLineRange(LinesToScan, Line)))
		{
			if(Fold && !(Ranges.Contains((TRangeState)(NativeInt)GetLineRange(LinesToScan, Line - 1))))
				FoldRanges->StartFoldRange(Line + 1, FoldType);
			else
				FoldRanges->NoFoldInfo(Line + 1);
		}
		else
		{
			if(Fold && (Ranges.Contains((TRangeState)(NativeInt)GetLineRange(LinesToScan, Line - 1))))
			{
				FoldRanges->StopFoldRange(Line + 1, FoldType);
			}
			else
			result = false;
		}
		return result;
	};
	__int64 stop = 0;
	for(stop = ToLine, Line = FromLine; Line <= stop; Line++)
	{
    // Deal first with Multiline statements
		if(IsMultiLineStatement((int) Line, Synhighlighterpas__13, true, FT_Comment) || IsMultiLineStatement((int) Line, Synhighlighterpas__14, true, FT_Asm) || IsMultiLineStatement((int) Line, Synhighlighterpas__15, true, FT_Comment) || IsMultiLineStatement((int) Line, Synhighlighterpas__16, false))
			continue;
		CurLine = LinesToScan->Strings[Line];

    // Skip empty lines
		if(CurLine == L"")
		{
			FoldRanges->NoFoldInfo((int) (Line + 1));
			continue;
		}

    //  Deal with ConditionalDirectives
		if(ConditionalDirective((int) Line))
			continue;

    // Find Fold regions
		if(FoldRegion((int) Line))
			continue;

    // Implementation
		if(UpperCase(TrimLeft(CurLine)) == L"IMPLEMENTATION")
    // Functions and procedures
			FoldRanges->StartFoldRange((int) (Line + 1), FT_Implementation);
		else
		{
			if(RE_Code.Matches(CurLine).Count > 0)
    // Find begin or end  (Fold Type 1)
				FoldRanges->StartFoldRange((int) (Line + 1), FT_CodeDeclaration);
			else
			{
				if(!BlockDelimiter((int) Line))
					FoldRanges->NoFoldInfo((int) (Line + 1));
			}
		}
	} //for Line
}
/*
   Provide folding for procedures and functions included nested ones.
*/

void __fastcall TSynPasSyn::AdjustFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan)
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
									goto label3;
								}
								else

                  // class or record declaration follows, so
								{
									FoldRanges->Ranges->Delete(i);
									goto label4;
								}
							}
							else
							Assert(false, L"TSynDWSSyn.AdjustFoldRanges");
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
				label3:;
				label4:;
			}
		}
	}
	if(ImplementationIndex >= 0)
    // Looks better without it
    //FoldRanges.Ranges.List[ImplementationIndex].ToLine := LinesToScan.Count;
		FoldRanges->Ranges->Delete(ImplementationIndex);
}
//-- CodeFolding

	static bool SynHighlighterPas_Initialized = false;
	
	void SynHighlighterPas_initialization()
	{
		if(SynHighlighterPas_Initialized)
			return;
		
		SynHighlighterPas_Initialized = true;
		
		RegisterPlaceableHighlighter(__classid(TSynPasSyn));
	}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterPas

