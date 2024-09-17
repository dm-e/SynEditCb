
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterCS.h"
#include <Winapi.Windows.hpp>
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditmiscclasses;
using namespace Syneditstrconst;
using namespace System;

namespace Synhighlightercs
{
#define Synhighlightercs__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlightercs__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightercs__2 (TSysCharSet() << '\x27' << '\\')
#define Synhighlightercs__3 (System::Set<TtkTokenKind, TtkTokenKind::tkSymbol, TtkTokenKind::tkUnknown>() << tkComment << tkSpace << tkNull)
#define Synhighlightercs__4 (TSynHighlighterCapabilities() << hcUserSettings)


const String Keywords[77/*# range 0..76*/] = {L"abstract", L"as", L"base", L"bool", L"break", L"byte", L"case", L"catch", L"class", L"const", L"continue", L"decimal"
                    , L"default", L"delegate", L"do", L"double", L"else", L"enum", L"event", L"explicit", L"extern", L"false", L"finally", L"fixed"
                    , L"float", L"for", L"foreach", L"goto", L"char", L"checked", L"if", L"implicit", L"in", L"int", L"interface", L"internal", L"is"
                    , L"lock", L"long", L"namespace", L"new", L"null", L"object", L"operator", L"out", L"override", L"params", L"private", L"protected", L"public"
                    , L"readonly", L"ref", L"return", L"sbyte", L"sealed", L"short", L"sizeof", L"stackalloc", L"static", L"string", L"struct", L"switch"
                    , L"this", L"throw", L"true", L"try", L"typeof", L"uint", L"ulong", L"unchecked", L"unsafe", L"ushort", L"using", L"virtual", L"void"
                    , L"volatile", L"while"};
const int KeyIndices[211/*# range 0..210*/] = {-1, 37, -1, -1, -1, -1, 27, -1, 70, -1, -1, 75, 7, -1, -1, 68, -1, -1, -1, -1, -1, -1, 43, -1, 73, -1, -1, -1, 55, -1, 22, 39, -1, 10, -1, 6, -1, 34, 61, -1, 40, -1, -1
                    , 60, 26, -1, -1, -1, -1, 45, -1, 29, 30, 67, 13, -1, 62, 72, -1, -1, 74, -1, -1, 41, -1, 1, 51, -1, -1, -1, -1, -1, 36, -1, 53, -1, -1, -1, -1, 11, -1, -1, -1, 46, 58, 71, -1, -1, -1, -1, -1, -1, -1, -1
                    , 28, 25, 0, -1, 16, -1, 63, -1, -1, 44, -1, 50, -1, 5, -1, -1, -1, 23, 38, 32, 33, 20, -1, -1, -1, -1, -1, -1, -1, 3, -1, -1, -1, 18, -1, -1, -1, -1, 54, -1, -1, 12, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, 59
                    , 56, 21, 47, 69, 64, -1, -1, -1, 65, -1, -1, 9, 15, -1, -1, -1, -1, -1, 76, 24, -1, -1, 14, -1, -1, -1, 19, 4, -1, -1, -1, -1, -1, -1, -1, 31, 48, 35, 66, -1, 52, -1, -1, -1, -1, -1, -1, -1, 57, -1, 49, -1
                    , 17, -1, 2, -1, -1, -1, -1, -1, -1, -1, -1, 42};

/*$Q-*/

unsigned int __fastcall TSynCSSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 52 + int((*Str)) * 456);
		++Str;
	}
	result = (unsigned int) (result % 211);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynCSSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkSymbol;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 210 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynCSSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 210 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}

  /* nasledujici funkce nahradit za DataTypeFunc :
  bool, byte, decimal, double, float, char, int, long, sbyte, short, string, uint, ulong, ushort
  */
	fIdentFuncTable[96] = FuncAbstract;
	fIdentFuncTable[65] = FuncAs;
	fIdentFuncTable[201] = FuncBase;
	fIdentFuncTable[123] = DataTypeFunc;
	fIdentFuncTable[174] = FuncBreak;
	fIdentFuncTable[107] = DataTypeFunc;
	fIdentFuncTable[35] = FuncCase;
	fIdentFuncTable[12] = FuncCatch;
	fIdentFuncTable[136] = FuncClass;
	fIdentFuncTable[158] = FuncConst;
	fIdentFuncTable[33] = FuncContinue;
	fIdentFuncTable[79] = DataTypeFunc;
	fIdentFuncTable[135] = FuncDefault;
	fIdentFuncTable[54] = FuncDelegate;
	fIdentFuncTable[169] = FuncDo;
	fIdentFuncTable[159] = DataTypeFunc;
	fIdentFuncTable[98] = FuncElse;
	fIdentFuncTable[199] = FuncEnum;
	fIdentFuncTable[127] = FuncEvent;
	fIdentFuncTable[173] = FuncExplicit;
	fIdentFuncTable[115] = FuncExtern;
	fIdentFuncTable[148] = FuncFalse;
	fIdentFuncTable[30] = FuncFinally;
	fIdentFuncTable[111] = FuncFixed;
	fIdentFuncTable[166] = DataTypeFunc;
	fIdentFuncTable[95] = FuncFor;
	fIdentFuncTable[44] = FuncForeach;
	fIdentFuncTable[6] = FuncGoto;
	fIdentFuncTable[94] = DataTypeFunc;
	fIdentFuncTable[51] = FuncChecked;
	fIdentFuncTable[52] = FuncIf;
	fIdentFuncTable[182] = FuncImplicit;
	fIdentFuncTable[113] = FuncIn;
	fIdentFuncTable[114] = DataTypeFunc;
	fIdentFuncTable[37] = FuncInterface;
	fIdentFuncTable[184] = FuncInternal;
	fIdentFuncTable[72] = FuncIs;
	fIdentFuncTable[1] = FuncLock;
	fIdentFuncTable[112] = DataTypeFunc;
	fIdentFuncTable[31] = FuncNamespace;
	fIdentFuncTable[40] = FuncNew;
	fIdentFuncTable[63] = FuncNull;
	fIdentFuncTable[210] = FuncObject;
	fIdentFuncTable[22] = FuncOperator;
	fIdentFuncTable[103] = FuncOut;
	fIdentFuncTable[49] = FuncOverride;
	fIdentFuncTable[83] = FuncParams;
	fIdentFuncTable[149] = FuncPrivate;
	fIdentFuncTable[183] = FuncProtected;
	fIdentFuncTable[197] = FuncPublic;
	fIdentFuncTable[105] = FuncReadonly;
	fIdentFuncTable[66] = FuncRef;
	fIdentFuncTable[187] = FuncReturn;
	fIdentFuncTable[74] = DataTypeFunc;
	fIdentFuncTable[132] = FuncSealed;
	fIdentFuncTable[28] = DataTypeFunc;
	fIdentFuncTable[147] = FuncSizeof;
	fIdentFuncTable[195] = FuncStackalloc;
	fIdentFuncTable[84] = FuncStatic;
	fIdentFuncTable[146] = DataTypeFunc;
	fIdentFuncTable[43] = FuncStruct;
	fIdentFuncTable[38] = FuncSwitch;
	fIdentFuncTable[56] = FuncThis;
	fIdentFuncTable[100] = FuncThrow;
	fIdentFuncTable[151] = FuncTrue;
	fIdentFuncTable[155] = FuncTry;
	fIdentFuncTable[185] = FuncTypeof;
	fIdentFuncTable[53] = DataTypeFunc;
	fIdentFuncTable[15] = DataTypeFunc;
	fIdentFuncTable[150] = FuncUnchecked;
	fIdentFuncTable[8] = FuncUnsafe;
	fIdentFuncTable[85] = DataTypeFunc;
	fIdentFuncTable[57] = FuncUsing;
	fIdentFuncTable[24] = FuncVirtual;
	fIdentFuncTable[60] = FuncVoid;
	fIdentFuncTable[11] = FuncVolatile;
	fIdentFuncTable[165] = FuncWhile;
}

TtkTokenKind __fastcall TSynCSSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkSymbol;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncAbstract(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncAs(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncBase(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncBreak(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncCase(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncCatch(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncChecked(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncClass(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncConst(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncContinue(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncDefault(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncDelegate(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncDo(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncElse(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncEnum(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncEvent(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncExplicit(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncExtern(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncFalse(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncFinally(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncFixed(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncFor(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncForeach(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncGoto(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncIf(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncImplicit(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncIn(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncInterface(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncInternal(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncIs(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncLock(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncNamespace(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncNew(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncNull(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncObject(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncOperator(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncOut(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncOverride(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncParams(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncPrivate(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncProtected(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncPublic(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncReadonly(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncRef(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncReturn(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncSealed(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncSizeof(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncStackalloc(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncStatic(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncStruct(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncSwitch(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncThis(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncThrow(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncTrue(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncTry(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncTypeof(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncUnchecked(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncUnsafe(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncUsing(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncVirtual(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncVoid(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncVolatile(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::FuncWhile(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynCSSyn::TSynCSSyn(TComponent* AOwner)
 : inherited(AOwner),
			fAsmStart(false),
			FRange(rsUnKnown),
			FTokenID(tkSymbol),
			FExtTokenID(xtkAdd),
			fAsmAttri(nullptr),
			fCommentAttri(nullptr),
			fDirecAttri(nullptr),
			fIdentifierAttri(nullptr),
			fInvalidAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fTypeAttri(nullptr)
{
	FCaseSensitive = true;
	fAsmAttri = new TSynHighlighterAttributes(SYNS_AttrAssembler, SYNS_FriendlyAttrAssembler);
	addAttribute(fAsmAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlightercs__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fInvalidAttri = new TSynHighlighterAttributes(SYNS_AttrIllegalChar, SYNS_FriendlyAttrIllegalChar);
	addAttribute(fInvalidAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlightercs__1;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fDirecAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	addAttribute(fDirecAttri);
	fTypeAttri = new TSynHighlighterAttributes(SYNS_AttrDataType, SYNS_FriendlyAttrDataType);
	addAttribute(fTypeAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	FRange = rsUnKnown;
	fDefaultFilter = SYNS_FilterCS;
} /* Create */

void __fastcall TSynCSSyn::AnsiCProc()
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
	while(fLine[Run] != L'\x00')
		switch(fLine[Run])
		{
			case L'*':
			if(fLine[Run + 1] == L'/')
			{
				Run += 2;
				if(FRange == rsAnsiCAsm)
					FRange = rsAsm;
				else
				{
					if(FRange == rsAnsiCAsmBlock)
						FRange = rsAsmBlock;
					else
					{
						if(FRange == rsDirectiveComment)
							FRange = rsDirective;
						else
							FRange = rsUnKnown;
					}
				}
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

void __fastcall TSynCSSyn::AndSymbolProc()
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

void __fastcall TSynCSSyn::AsciiCharProc()
{
	FTokenID = tkString;
	do
	{
		if(fLine[Run] == L'\\')
		{
			if(CharInSet(fLine[Run + 1], Synhighlightercs__2))
				++Run;
		}
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\x27')));
	if(fLine[Run] == L'\x27')
		++Run;
}

void __fastcall TSynCSSyn::AtSymbolProc()
{
	FTokenID = tkUnknown;
	++Run;
}

void __fastcall TSynCSSyn::BraceCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkBraceClose;
	if(FRange == rsAsmBlock)
		FRange = rsUnKnown;
}

void __fastcall TSynCSSyn::BraceOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkBraceOpen;
	if(FRange == rsAsm)
	{
		FRange = rsAsmBlock;
		fAsmStart = true;
	}
}

void __fastcall TSynCSSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run + 1] == L'\x0a')
		++Run;
}

void __fastcall TSynCSSyn::ColonProc()
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

void __fastcall TSynCSSyn::CommaProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkComma;
}

TtkTokenKind __fastcall TSynCSSyn::DataTypeFunc(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkType;
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynCSSyn::DirectiveProc()
{
	if(IsLineEnd(Run))
	{
		if((Run <= 0) || (fLine[Run - 1] != L'\\'))
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
					if(fLine[Run + 1] == L'/') // is end of directive as well
					{
						FRange = rsUnKnown;
						goto label3;
					}
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
				break; // directive continued on next line?
				case L'\\':
				{
					++Run;
					if(IsLineEnd(Run))
					{
						FRange = rsDirective;
						goto label5;
					}
				}
				break;
				case L'\x00':
				case L'\x0a':
				case L'\x0d':
				{
					FRange = rsUnKnown;
					goto label6;
				}
				default:
				++Run;
				break;
			}
		label3:;
		label4:;
		label5:;
		label6:;
	}
}

void __fastcall TSynCSSyn::EqualProc()
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

void __fastcall TSynCSSyn::GreaterProc()
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

void __fastcall TSynCSSyn::QuestionProc()
{
	FTokenID = tkSymbol;                /*conditional*/
	FExtTokenID = xtkQuestion;
	++Run;
}

void __fastcall TSynCSSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynCSSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynCSSyn::LowerProc()
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

void __fastcall TSynCSSyn::MinusProc()
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

void __fastcall TSynCSSyn::ModSymbolProc()
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

void __fastcall TSynCSSyn::NotSymbolProc()
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

void __fastcall TSynCSSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynCSSyn::NumberProc()
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
				goto label7;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label7:;
}

void __fastcall TSynCSSyn::OrSymbolProc()
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

void __fastcall TSynCSSyn::PlusProc()
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

void __fastcall TSynCSSyn::PointProc()
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

void __fastcall TSynCSSyn::RoundCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkRoundClose;
}

void __fastcall TSynCSSyn::RoundOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkRoundOpen;
}

//++ CodeFolding

void __fastcall TSynCSSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	String CurLine;
	__int64 Line = 0;

	auto LineHasChar = [&](int Line, Char Character, int StartCol) -> bool 
	{
		bool result = false;
		int i = 0;
		int stop = 0;
		result = false;
		for(stop = CurLine.Length(), i = StartCol; i <= stop; i++)
		{
			if(CurLine[i] == Character)
        // Char must have proper highlighting (ignore stuff inside comments...)
			{
				if(GetHighlighterAttriAtRowCol(LinesToScan, Line, i) != fCommentAttri)
				{
					result = true;
					break;
				}
			}
		}
		return result;
	}; // faster than Pos!

	auto FindBraces = [&](int Line) -> bool 
	{
		bool result = false;
		int Col = 0;
		int stop = 0;
		result = false;
		for(stop = CurLine.Length(), Col = 1; Col <= stop; Col++)
		{
      // We've found a starting character
			if(CurLine[Col] == L'{')
        // Char must have proper highlighting (ignore stuff inside comments...)
			{
				if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Col) != fCommentAttri)
          // And ignore lines with both opening and closing chars in them
				{
					if(!LineHasChar(Line, L'}', Col + 1))
					{
						FoldRanges->StartFoldRange(Line + 1, 1);
						result = true;
					}
          // Skip until a newline
					break;
				}
			}
			else
			{
				if(CurLine[Col] == L'}')
				{
					if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Col) != fCommentAttri)
          // And ignore lines with both opening and closing chars in them
					{
						if(!LineHasChar(Line, L'{', Col + 1))
						{
							FoldRanges->StopFoldRange(Line + 1, 1);
							result = true;
						}
          // Skip until a newline
						break;
					}
				}
			}
		} // for Col
		return result;
	};

	auto FoldRegion = [&](int Line) -> bool 
	{
		bool result = false;
		String s;
		result = false;
		s = TrimLeft(CurLine);
		if(UpperCase(s.SubString(1, 9)) == L"//#REGION")
		{
			FoldRanges->StartFoldRange(Line + 1, FoldRegionType);
			result = true;
		}
		else
		{
			if(UpperCase(s.SubString(1, 12)) == L"//#ENDREGION")
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
    // Deal first with Multiline comments (Fold Type 2)
		if((TRangeState)(NativeInt)GetLineRange(LinesToScan, (int) Line) == rsAnsiC)
		{
			if((TRangeState)(NativeInt)GetLineRange(LinesToScan, (int) (Line - 1)) != rsAnsiC)
				FoldRanges->StartFoldRange((int) (Line + 1), 2);
			else
				FoldRanges->NoFoldInfo((int) (Line + 1));
			continue;
		}
		else
		{
			if((TRangeState)(NativeInt)GetLineRange(LinesToScan, (int) (Line - 1)) == rsAnsiC)
			{
				FoldRanges->StopFoldRange((int) (Line + 1), 2);
				continue;
			}
		}
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

    // Find an braces on this line  (Fold Type 1)
		if(!FindBraces((int) Line))
			FoldRanges->NoFoldInfo((int) (Line + 1));
	} // while Line
}
//-- CodeFolding

void __fastcall TSynCSSyn::SemiColonProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSemiColon;
	if(FRange == rsAsm)
		FRange = rsUnKnown;
}

void __fastcall TSynCSSyn::SlashProc()
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
			if(FRange == rsAsm)
				FRange = rsAnsiCAsm;
			else
			{
				if(FRange == rsAsmBlock)
					FRange = rsAnsiCAsmBlock;
				else
				{
					if(FRange != rsDirectiveComment)
						FRange = rsAnsiC;
				}
			}
			Run += 2;
			while(fLine[Run] != L'\x00')
				switch(fLine[Run])
				{
					case L'*':
					if(fLine[Run + 1] == L'/')
					{
						Run += 2;
						if(FRange == rsDirectiveComment)
							FRange = rsDirective;
						else
						{
							if(FRange == rsAnsiCAsm)
								FRange = rsAsm;
							else
							{
								if(FRange == rsAnsiCAsmBlock)
									FRange = rsAsmBlock;
								else
									FRange = rsUnKnown;
							}
						}
						goto label8;
					}
					else
					++Run;
					break;
					case L'\x0a':
					case L'\x0d':
					{
						if(FRange == rsDirectiveComment)
							FRange = rsAnsiC;
						goto label9;
					}
					default:
					++Run;
					break;
				}
			label8:;
			label9:;
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

void __fastcall TSynCSSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynCSSyn::SquareCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSquareClose;
}

void __fastcall TSynCSSyn::SquareOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSquareOpen;
}

void __fastcall TSynCSSyn::StarProc()
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

void __fastcall TSynCSSyn::StringProc()
{
	FTokenID = tkString;
	do
	{
		if(fLine[Run] == L'\\')
		{
			switch(fLine[Run + 1])
			{
				case L'\x22':
				case L'\\':
				++Run;
				break;
				case L'\x00':
				{
					++Run;
					FRange = rsMultiLineString;
					return;
				}
				default:
				  ;
				break;
			}
		}
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\x22')));
	if(fLine[Run] == L'\x22')
		++Run;
}

void __fastcall TSynCSSyn::StringEndProc()
{
	FTokenID = tkString;
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
	FRange = rsUnKnown;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label10;
			case L'\\':
			{
				switch(fLine[Run + 1])
				{
					case L'\x22':
					case L'\\':
					++Run;
					break;
					case L'\x00':
					{
						++Run;
						FRange = rsMultiLineString;
						return;
					}
					default:
					  ;
					break;
				}
			}
			break;
			case L'\x22':
			goto label11;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\x22')));
	label10:;
	label11:;
	if(fLine[Run] == L'\x22')
		++Run;
}

void __fastcall TSynCSSyn::TildeProc()
{
	++Run;                            /*bitwise complement*/
	FTokenID = tkSymbol;
	FExtTokenID = xtkBitComplement;
}

void __fastcall TSynCSSyn::XOrSymbolProc()
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

void __fastcall TSynCSSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynCSSyn::Next()
{
	fAsmStart = false;
	fTokenPos = Run;
	switch(FRange)
	{
		case rsAnsiC:
		case rsAnsiCAsm:
		case rsAnsiCAsmBlock:
		case rsDirectiveComment:
		AnsiCProc();
		break;
		case rsDirective:
		DirectiveProc();
		break;
		case rsMultiLineString:
		StringEndProc();
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

void __fastcall TSynCSSyn::NextProcedure()
{
	switch(fLine[Run])
	{
		case L'&':
		AndSymbolProc();
		break;
		case L'\x27':
		AsciiCharProc();
		break;
		case L'@':
		AtSymbolProc();
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

TSynHighlighterAttributes* __fastcall TSynCSSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynCSSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynCSSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynCSSyn::GetTokenID()
{
	TtkTokenKind result = tkSymbol;
	result = FTokenID;
	if(((FRange == rsAsm) || (FRange == rsAsmBlock)) && !fAsmStart && !(Synhighlightercs__3.Contains(FTokenID)))
		result = tkAsm;
	return result;
}

TxtkTokenKind __fastcall TSynCSSyn::GetExtTokenID()
{
	TxtkTokenKind result = xtkAdd;
	result = FExtTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynCSSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
	{
		case tkAsm:
		result = fAsmAttri;
		break;
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
		case tkType:
		result = fTypeAttri;
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

int __fastcall TSynCSSyn::GetTokenKind()
{
	int result = 0;
	result = int(GetTokenID());
	return result;
}

void __fastcall TSynCSSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynCSSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynCSSyn::EnumUserSettings(TStrings* Settings)
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

bool __fastcall TSynCSSyn::UseUserSettings(int settingIndex)
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
				for(stop = Name.Length(), i = 1; i <= stop; i++)
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
		TSynHighlighterAttributes* tmpAsmAttri = nullptr;
		TSynHighlighterAttributes* tmpCommentAttri = nullptr;
		TSynHighlighterAttributes* tmpIdentifierAttri = nullptr;
		TSynHighlighterAttributes* tmpInvalidAttri = nullptr;
		TSynHighlighterAttributes* tmpSpaceAttri = nullptr;
		TSynHighlighterAttributes* tmpDirecAttri = nullptr;
		TStringList* s = nullptr; /* ReadCPPBSettings */
		s = new TStringList();
		try
		{
			EnumUserSettings(s);
			if(settingIndex >= s->Count)
				result = false;
			else
			{
				tmpStringAttri = new TSynHighlighterAttributes(L"", L"");
				tmpNumberAttri = new TSynHighlighterAttributes(L"", L"");
				tmpKeyAttri = new TSynHighlighterAttributes(L"", L"");
				tmpSymbolAttri = new TSynHighlighterAttributes(L"", L"");
				tmpAsmAttri = new TSynHighlighterAttributes(L"", L"");
				tmpCommentAttri = new TSynHighlighterAttributes(L"", L"");
				tmpIdentifierAttri = new TSynHighlighterAttributes(L"", L"");
				tmpInvalidAttri = new TSynHighlighterAttributes(L"", L"");
				tmpSpaceAttri = new TSynHighlighterAttributes(L"", L"");
				tmpDirecAttri = new TSynHighlighterAttributes(L"", L"");
				tmpStringAttri->Assign(fStringAttri);
				tmpNumberAttri->Assign(fNumberAttri);
				tmpKeyAttri->Assign(fKeyAttri);
				tmpSymbolAttri->Assign(fSymbolAttri);
				tmpAsmAttri->Assign(fAsmAttri);
				tmpCommentAttri->Assign(fCommentAttri);
				tmpIdentifierAttri->Assign(fIdentifierAttri);
				tmpInvalidAttri->Assign(fInvalidAttri);
				tmpSpaceAttri->Assign(fSpaceAttri);
				tmpDirecAttri->Assign(fDirecAttri);
				if(((String)s->Strings[settingIndex])[1] == L'1')
					result = ReadCPPBSetting(s->Strings[settingIndex], fAsmAttri, L"Plain text");
				else
					result = ReadCPPBSetting(s->Strings[settingIndex], fAsmAttri, L"Assembler");
				result = result && ReadCPPBSetting(s->Strings[settingIndex], fCommentAttri, L"Comment") && ReadCPPBSetting(s->Strings[settingIndex], fIdentifierAttri, L"Identifier") && ReadCPPBSetting(s->Strings[settingIndex], fInvalidAttri, L"Illegal Char") && ReadCPPBSetting(s->Strings[settingIndex], fKeyAttri, L"Reserved word") && ReadCPPBSetting(s->Strings[settingIndex], fNumberAttri, L"Integer") && ReadCPPBSetting(s->Strings[settingIndex], fSpaceAttri, L"Whitespace") && ReadCPPBSetting(s->Strings[settingIndex], fStringAttri, L"String") && ReadCPPBSetting(s->Strings[settingIndex], fSymbolAttri, L"Symbol") && ReadCPPBSetting(s->Strings[settingIndex], fDirecAttri, L"Preprocessor");
				if(!result)
				{
					fStringAttri->Assign(tmpStringAttri);
					fNumberAttri->Assign(tmpNumberAttri);
					fKeyAttri->Assign(tmpKeyAttri);
					fSymbolAttri->Assign(tmpSymbolAttri);
					fAsmAttri->Assign(tmpAsmAttri);
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
				delete tmpAsmAttri;
				delete tmpCommentAttri;
				delete tmpIdentifierAttri;
				delete tmpInvalidAttri;
				delete tmpSpaceAttri;
				delete tmpDirecAttri;
			}
		}
		__finally
		{
			delete s;
		}
		return result;
	}; /* ReadCPPBSettings */
	result = ReadCPPBSettings(settingIndex);
	return result;
} /* TSynCSSyn.UseUserSettings */

String __fastcall TSynCSSyn::GetSampleSource()
{
	String result;
	result = L"/* Syntax Highlighting */\x0d\x0a"
	           L"int num = 12345;\x0d\x0a"
	           L"string str = \"Hello World\";\x0d\x0a";
	return result;
} /* GetSampleSource */

/*#static*/
String __fastcall TSynCSSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangCS;
	return result;
}

bool __fastcall TSynCSSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterCS;
	return result;
}

/*#static*/
TSynHighlighterCapabilities __fastcall TSynCSSyn::GetCapabilities()
{
	TSynHighlighterCapabilities result;
	result = inherited::GetCapabilities() + Synhighlightercs__4;
	return result;
}

/*#static*/
String __fastcall TSynCSSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangCS;
	return result;
}
static bool SynHighlighterCS_Initialized = false;

void SynHighlighterCS_initialization()
{
	if(SynHighlighterCS_Initialized)
		return;
	
	SynHighlighterCS_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynCSSyn));
}
class SynHighlighterCS_unit
{
public:
	SynHighlighterCS_unit()
	{
		SynHighlighterCS_initialization();
	}
};

SynHighlighterCS_unit _SynHighlighterCS_unit;

}  // namespace SynHighlighterCS

