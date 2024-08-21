
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterIDL.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighteridl
{
#define Synhighlighteridl__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighteridl__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighteridl__2 (TFontStyles() << TFontStyle::fsBold)


const String Keywords[48/*# range 0..47*/] = {L"abstract", L"any", L"attribute", L"boolean", L"case", L"char", L"const", L"context", L"custom", L"default", L"double"
                    , L"enum", L"exception", L"factory", L"FALSE", L"fixed", L"float", L"in", L"inout", L"interface", L"local", L"long", L"module"
                    , L"native", L"Object", L"octet", L"oneway", L"out", L"private", L"public", L"raises", L"readonly", L"sequence", L"short", L"string"
                    , L"struct", L"supports", L"switch", L"TRUE", L"truncatable", L"typedef", L"union", L"unsigned", L"ValueBase", L"valuetype", L"void"
                    , L"wchar", L"wstring"};
const int KeyIndices[101/*# range 0..100*/] = {5, 19, 17, 7, -1, -1, -1, -1, -1, 15, 18, -1, 37, -1, 24, -1, -1, -1, 44, -1, 11, 31, -1, 25, 33, -1, -1, 42, 39, -1, -1, 36, 46, -1, 27, -1, 43, 28, 26, 20, -1, 1, 32
                    , 6, -1, 14, 8, -1, -1, -1, -1, 0, 35, -1, -1, -1, -1, -1, -1, -1, -1, 45, 22, 47, -1, -1, 12, 4, -1, -1, -1, 10, -1, -1, 3, -1, 9, -1, 34, 30, 13, -1, 2, 21, 16, -1, 29, 40, -1, -1, -1, -1, -1, -1, -1, 23, -1
                    , 38, -1, -1, 41};

/*$Q-*/

unsigned int __fastcall TSynIdlSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 612 + int((*Str)) * 199);
		++Str;
	}
	result = (unsigned int) (result % 101);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynIdlSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 100 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynIdlSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 100 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[51] = FuncAbstract;
	fIdentFuncTable[41] = FuncAny;
	fIdentFuncTable[82] = FuncAttribute;
	fIdentFuncTable[74] = FuncBoolean;
	fIdentFuncTable[67] = FuncCase;
	fIdentFuncTable[0] = FuncChar;
	fIdentFuncTable[43] = FuncConst;
	fIdentFuncTable[3] = FuncContext;
	fIdentFuncTable[46] = FuncCustom;
	fIdentFuncTable[76] = FuncDefault;
	fIdentFuncTable[71] = FuncDouble;
	fIdentFuncTable[20] = FuncEnum;
	fIdentFuncTable[66] = FuncException;
	fIdentFuncTable[80] = FuncFactory;
	fIdentFuncTable[45] = FuncFalse;
	fIdentFuncTable[9] = FuncFixed;
	fIdentFuncTable[84] = FuncFloat;
	fIdentFuncTable[2] = FuncIn;
	fIdentFuncTable[10] = FuncInout;
	fIdentFuncTable[1] = FuncInterface;
	fIdentFuncTable[39] = FuncLocal;
	fIdentFuncTable[83] = FuncLong;
	fIdentFuncTable[62] = FuncModule;
	fIdentFuncTable[95] = FuncNative;
	fIdentFuncTable[14] = FuncObject;
	fIdentFuncTable[23] = FuncOctet;
	fIdentFuncTable[38] = FuncOneway;
	fIdentFuncTable[34] = FuncOut;
	fIdentFuncTable[37] = FuncPrivate;
	fIdentFuncTable[86] = FuncPublic;
	fIdentFuncTable[79] = FuncRaises;
	fIdentFuncTable[21] = FuncReadonly;
	fIdentFuncTable[42] = FuncSequence;
	fIdentFuncTable[24] = FuncShort;
	fIdentFuncTable[78] = FuncString;
	fIdentFuncTable[52] = FuncStruct;
	fIdentFuncTable[31] = FuncSupports;
	fIdentFuncTable[12] = FuncSwitch;
	fIdentFuncTable[97] = FuncTrue;
	fIdentFuncTable[28] = FuncTruncatable;
	fIdentFuncTable[87] = FuncTypedef;
	fIdentFuncTable[100] = FuncUnion;
	fIdentFuncTable[27] = FuncUnsigned;
	fIdentFuncTable[36] = FuncValuebase;
	fIdentFuncTable[18] = FuncValuetype;
	fIdentFuncTable[61] = FuncVoid;
	fIdentFuncTable[32] = FuncWchar;
	fIdentFuncTable[63] = FuncWstring;
}

TtkTokenKind __fastcall TSynIdlSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncAbstract(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncAny(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncAttribute(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncBoolean(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncCase(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncChar(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncConst(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncContext(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncCustom(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncDefault(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncDouble(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncEnum(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncException(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncFactory(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncFalse(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncFixed(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncFloat(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncIn(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncInout(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncInterface(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncLocal(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncLong(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncModule(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncNative(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncObject(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncOctet(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncOneway(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncOut(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncPrivate(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncPublic(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncRaises(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncReadonly(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncSequence(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncShort(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncString(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncStruct(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncSupports(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncSwitch(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncTrue(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncTruncatable(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncTypedef(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncUnion(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncUnsigned(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncValuebase(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncValuetype(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncVoid(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncWchar(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::FuncWstring(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkDataType;
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynIdlSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynIdlSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynIdlSyn::NumberProc()
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
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Run + 1] == L'.')
				goto label0;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label0:;
} /* NumberProc */

void __fastcall TSynIdlSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynIdlSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynIdlSyn::CommentOpenProc()
{
	++Run;
	if(fLine[Run] == L'*')
	{
		FRange = rsComment;
		CommentProc();
		FTokenID = tkComment;
	}
	else
	{
		if(fLine[Run] == L'/')
		{
			while(!IsLineEnd(Run))
				++Run;
			FTokenID = tkComment;
		}
		else
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynIdlSyn::CommentProc()
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

void __fastcall TSynIdlSyn::StringOpenProc()
{
	++Run;
	FRange = rsString;
	StringProc();
	FTokenID = tkString;
}

void __fastcall TSynIdlSyn::StringProc()
{
	FTokenID = tkString;
	do
	{
		if(fLine[Run] == L'\"')
		{
			++Run;
			FRange = rsUnKnown;
			break;
		}
		else
		{
			if(fLine[Run] == L'\\')
				++Run;
		}
		if(!IsLineEnd(Run))
			++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynIdlSyn::CharOpenProc()
{
	++Run;
	FRange = rsChar;
	CharProc();
	FTokenID = tkString;
}

void __fastcall TSynIdlSyn::CharProc()
{
	FTokenID = tkString;
	do
	{
		if(fLine[Run] == L'\'')
		{
			++Run;
			FRange = rsUnKnown;
			break;
		}
		if(!IsLineEnd(Run))
			++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynIdlSyn::PreProcessorProc()
{

	auto IsWhiteChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x09':
			case L'\x0a':
			case L'\x0d':
			case L'\x20':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	String Directive;
	Directive = L"";
	while(!IsWhiteChar())
	{
		Directive = Directive + String(fLine[Run]);
		++Run;
	}
	if(CompareStr(Directive, L"#include") == 0)
		FTokenID = tkPreprocessor;
	else
	{
		if(CompareStr(Directive, L"#pragma") == 0)
			FTokenID = tkPreprocessor;
		else
			FTokenID = tkIdentifier;
	}
} /* PreProcessorProc */

__fastcall TSynIdlSyn::TSynIdlSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fDataTypeAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fPreprocessorAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr)
{
	FCaseSensitive = true;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighteridl__0;
	fCommentAttri->Foreground = (TColor) clNavy;
	addAttribute(fCommentAttri);
	fDataTypeAttri = new TSynHighlighterAttributes(SYNS_AttrDataType, SYNS_FriendlyAttrDataType);
	fDataTypeAttri->Style = Synhighlighteridl__1;
	fDataTypeAttri->Foreground = (TColor) clTeal;
	addAttribute(fDataTypeAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighteridl__2;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = (TColor) clBlue;
	addAttribute(fNumberAttri);
	fPreprocessorAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	fPreprocessorAttri->Foreground = (TColor) clRed;
	addAttribute(fPreprocessorAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = (TColor) clBlue;
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterCORBAIDL;
}

void __fastcall TSynIdlSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynIdlSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynIdlSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynIdlSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsComment:
		CommentProc();
		break;
		default:
		{
			FRange = rsUnKnown;
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
				CommentOpenProc();
				break;
				case L'\"':
				StringOpenProc();
				break;
				case L'\'':
				CharOpenProc();
				break;
				case L'#':
				PreProcessorProc();
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
				case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
				NumberProc();
				break;
				case L'-':
				case L'+':
				case L'*':
				case L'\\':
				case L',':
				case L'.':
				case L'[':
				case L']':
				case L'{':
				case L'}':
				case L'<':
				case L'>':
				case L'(':
				case L')':
				case L'=':
				case L'?':
				case L':':
				case L';':
				SymbolProc();
				break;
				default:
				UnknownProc();
				break;
			}
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynIdlSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynIdlSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynIdlSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynIdlSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkDataType:
		result = fDataTypeAttri;
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
		case tkPreprocessor:
		result = fPreprocessorAttri;
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

int __fastcall TSynIdlSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

String __fastcall TSynIdlSyn::GetSampleSource()
{
	String result;
	result = L"/* CORBA IDL sample source */\x0d\x0a"
	           L"#include <sample.idl>\x0d\x0a"
	           L"\x0d\x0a"
	           L"const string TestString = \"Hello World\";\x0d\x0a"
	           L"const long TestLong = 10;\x0d\x0a"
	           L"\x0d\x0a"
	           L"module TestModule {\x0d\x0a"
	           L"  interface DemoInterface {\x0d\x0a"
	           L"    boolean HelloWorld(in string Message);\x0d\x0a"
	           L"  }\x0d\x0a"
	           L"}";
	return result;
}

bool __fastcall TSynIdlSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterCORBAIDL;
	return result;
}

bool __fastcall TSynIdlSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'_':
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

/*#static*/
String __fastcall TSynIdlSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangCORBAIDL;
	return result;
}

void __fastcall TSynIdlSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynIdlSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void* __fastcall TSynIdlSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

/*#static*/
String __fastcall TSynIdlSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangCORBAIDL;
	return result;
}
static bool SynHighlighterIDL_Initialized = false;

void SynHighlighterIDL_initialization()
{
	if(SynHighlighterIDL_Initialized)
		return;
	
	SynHighlighterIDL_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynIdlSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterIDL

