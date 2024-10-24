
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterWebIDL.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace Vcl::Graphics;

namespace Synhighlighterwebidl
{
#define Synhighlighterwebidl__0 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterwebidl__1 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterwebidl__2 (TFontStyles() << TFontStyle::fsBold << TFontStyle::fsItalic)
#define Synhighlighterwebidl__3 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterwebidl__4 (TFontStyles() << TFontStyle::fsBold)


const System::Char SYNS_FilterWebIDL[] = L"Web IDL (*.idl)|*.idl";
const System::Char SYNS_LangWebIDL[] = L"Web IDL";
const System::Char SYNS_FriendlyLangWebIDL[] = L"Web IDL";
const System::Char SYNS_AttrArguments[] = L"Arguments";
const System::Char SYNS_FriendlyAttrArguments[] = L"Arguments";
const System::Char SYNS_AttrExtended[] = L"Extended";
const System::Char SYNS_FriendlyAttrExtended[] = L"Extended";
  // as this language is case-insensitive keywords *must* be in lowercase
const UnicodeString KeyWords[38/*# range 0..37*/] = {L"any", L"attribute", L"boolean", L"byte", L"bytestring", L"callback", L"const", L"creator", L"date", L"deleter"
                    , L"dictionary", L"domstring", L"double", L"enum", L"exception", L"float", L"getter", L"implements", L"inherit", L"interface"
                    , L"legacycaller", L"long", L"object", L"octet", L"optional", L"partial", L"readonly", L"regexp", L"sequence", L"setter"
                    , L"short", L"static", L"stringifier", L"typedef", L"unresticted", L"unrestricted", L"unsigned", L"void"};
const int KeyIndices[59/*# range 0..58*/] = {14, 28, 4, 37, 21, -1, -1, 12, 17, -1, -1, 22, -1, 3, -1, -1, 29, -1, 27, 31, -1, 1, 20, -1, 24, 15, 2, -1, -1, -1, -1, 23, -1, 19, 0, 13, 11, 16, 34, 10, 36, 25, -1, 30
                    , -1, 33, 32, 6, -1, 9, 7, -1, 8, -1, 26, 18, -1, 5, 35};

__fastcall TSynWebIDLSyn::TSynWebIDLSyn(TComponent* AOwner)
 : inherited(AOwner),
			fRange(rsUnknown),
			fTokenID(tkArguments),
			fSymbolTokenID(stkBraceOpen),
			fArgumentsAttri(nullptr),
			fExtendedAttri(nullptr),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fTypesAttri(nullptr)
{
	fCaseSensitive = false;
	fArgumentsAttri = new TSynHighlighterAttributes(SYNS_AttrArguments, SYNS_FriendlyAttrArguments);
	fArgumentsAttri->Style = Synhighlighterwebidl__0;
	fArgumentsAttri->Foreground = (TColor) clNavy;
	AddAttribute(fArgumentsAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterwebidl__1;
	fCommentAttri->Foreground = (TColor) clGreen;
	AddAttribute(fCommentAttri);
	fExtendedAttri = new TSynHighlighterAttributes(SYNS_AttrExtended, SYNS_FriendlyAttrExtended);
	fExtendedAttri->Style = Synhighlighterwebidl__2;
	fExtendedAttri->Foreground = (TColor) clMaroon;
	AddAttribute(fExtendedAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterwebidl__3;
	fKeyAttri->Foreground = (TColor) clNavy;
	AddAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = (TColor) clBlue;
	AddAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = (TColor) clPurple;
	AddAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	fSymbolAttri->Style = Synhighlighterwebidl__4;
	fSymbolAttri->Foreground = (TColor) clMaroon;
	AddAttribute(fSymbolAttri);
	fTypesAttri = new TSynHighlighterAttributes(SYNS_AttrDataType, SYNS_FriendlyAttrDataType);
	fTypesAttri->Foreground = (TColor) clNavy;
	AddAttribute(fTypesAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterWebIDL;
}

void __fastcall TSynWebIDLSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 58 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[34] = FuncAny;
	fIdentFuncTable[21] = FuncAttribute;
	fIdentFuncTable[26] = FuncBoolean;
	fIdentFuncTable[13] = FuncByte;
	fIdentFuncTable[2] = FuncBytestring;
	fIdentFuncTable[57] = FuncCallback;
	fIdentFuncTable[47] = FuncConst;
	fIdentFuncTable[50] = FuncCreator;
	fIdentFuncTable[52] = FuncDate;
	fIdentFuncTable[49] = FuncDeleter;
	fIdentFuncTable[39] = FuncDictionary;
	fIdentFuncTable[36] = FuncDomstring;
	fIdentFuncTable[7] = FuncDouble;
	fIdentFuncTable[35] = FuncEnum;
	fIdentFuncTable[0] = FuncException;
	fIdentFuncTable[25] = FuncFloat;
	fIdentFuncTable[37] = FuncGetter;
	fIdentFuncTable[8] = FuncImplements;
	fIdentFuncTable[55] = FuncInherit;
	fIdentFuncTable[33] = FuncInterface;
	fIdentFuncTable[22] = FuncLegacycaller;
	fIdentFuncTable[4] = FuncLong;
	fIdentFuncTable[11] = FuncObject;
	fIdentFuncTable[31] = FuncOctet;
	fIdentFuncTable[24] = FuncOptional;
	fIdentFuncTable[41] = FuncPartial;
	fIdentFuncTable[54] = FuncReadonly;
	fIdentFuncTable[18] = FuncRegexp;
	fIdentFuncTable[1] = FuncSequence;
	fIdentFuncTable[16] = FuncSetter;
	fIdentFuncTable[43] = FuncShort;
	fIdentFuncTable[19] = FuncStatic;
	fIdentFuncTable[46] = FuncStringifier;
	fIdentFuncTable[45] = FuncTypedef;
	fIdentFuncTable[38] = FuncUnresticted;
	fIdentFuncTable[58] = FuncUnrestricted;
	fIdentFuncTable[40] = FuncUnsigned;
	fIdentFuncTable[3] = FuncVoid;
}

void __fastcall TSynWebIDLSyn::ColonProc()
{
	++Run;
	fTokenID = tkSymbol;
	fSymbolTokenID = stkColon;
}

/*$Q-*/

unsigned int __fastcall TSynWebIDLSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 622 + int((*Str)) * 657);
		++Str;
	}
	result = (unsigned int) (result % 59);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynWebIDLSyn::FuncAny(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncAttribute(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncBoolean(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncByte(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncBytestring(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncCallback(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncConst(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncCreator(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncDate(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncDeleter(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncDictionary(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncDomstring(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncDouble(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncEnum(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncException(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncFloat(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncGetter(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncImplements(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncInherit(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncInterface(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncLegacycaller(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncLong(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncObject(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncOctet(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncOptional(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncPartial(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncReadonly(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncRegexp(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncSequence(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncSetter(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncShort(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncStatic(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncStringifier(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncTypedef(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncUnresticted(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncUnrestricted(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArguments;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncUnsigned(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::FuncVoid(int Index)
{
	TtkTokenKind result = tkArguments;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkTypes;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkArguments;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkArguments;
	unsigned int Key = 0;
	fToIdent = MayBe;
	Key = HashKey(MayBe);
	if(Key <= 58 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[Key](KeyIndices[Key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynWebIDLSyn::SpaceProc()
{
	++Run;
	fTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynWebIDLSyn::NullProc()
{
	fTokenID = tkNull;
	++Run;
}

void __fastcall TSynWebIDLSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'.':
			case 97: case 98: case 99: case 100: case 101: case 102:
			case 65: case 66: case 67: case 68: case 69: case 70:
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

	auto IsHexChar = [&](int Run) -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 97: case 98: case 99: case 100: case 101: case 102:
			case 65: case 66: case 67: case 68: case 69: case 70:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	int idx1 = 0; // token[1]
	bool isHex = false;
	fTokenID = tkNumber;
	isHex = false;
	idx1 = Run;
	++Run;
	while(IsNumberChar())
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Succ(Run)] == L'.')
				goto label0;
			break;
			case 97: case 98: case 99: case 100: case 101: case 102:
			case 65: case 66: case 67: case 68: case 69: case 70:
			if(!isHex)
				goto label1;
			break;
			case L'x':
			case L'X':
			{
				if((fLine[idx1] != L'0') || (Run > Succ(idx1)))
					goto label2;
				if(!IsHexChar(Succ(Run)))
					goto label3;
				isHex = true;
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
	label3:;
}

void __fastcall TSynWebIDLSyn::QuestionMarkProc()
{
	++Run;
	fTokenID = tkSymbol;
	fSymbolTokenID = stkQuestionMark;
}

void __fastcall TSynWebIDLSyn::CRProc()
{
	fTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynWebIDLSyn::GreaterProc()
{
	++Run;
	fTokenID = tkSymbol;
	fSymbolTokenID = stkGreater;
}

void __fastcall TSynWebIDLSyn::LessProc()
{
	++Run;
	fTokenID = tkSymbol;
	fSymbolTokenID = stkLess;
}

void __fastcall TSynWebIDLSyn::LFProc()
{
	fTokenID = tkSpace;
	++Run;
}

void __fastcall TSynWebIDLSyn::SlashProc()
{
	++Run;
	switch(fLine[Run])
	{
		case L'/':
		{
			do
			{
				++Run;
			}
			while(!IsLineEnd(Run));
			fRange = rsSingleComment;
			fTokenID = tkComment;
		}
		break;
		case L'*':
		{
			Run += 1;
			fRange = rsCStyleComment;
			fTokenID = tkComment;
		}
		break;
		default:
		fTokenID = tkIdentifier;
		break;
	}
}

void __fastcall TSynWebIDLSyn::CStyleCommentProc()
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
			fTokenID = tkComment;
			do
			{
				if((fLine[Run] == L'*') && (fLine[Run + 1] == L'/'))
				{
					Run += 2;
					fRange = rsUnknown;
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

void __fastcall TSynWebIDLSyn::StringOpenProc()
{
	++Run;
	fRange = rsString;
	fTokenID = tkString;
}

void __fastcall TSynWebIDLSyn::StringProc()
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
			fTokenID = tkString;
			do
			{
				if(fLine[Run] == L'\"')
				{
					Run += 1;
					fRange = rsUnknown;
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

void __fastcall TSynWebIDLSyn::IdentProc()
{
	fTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynWebIDLSyn::BraceOpenProc()
{
	++Run;
	fTokenID = tkSymbol;
	fSymbolTokenID = stkBraceOpen;
}

void __fastcall TSynWebIDLSyn::BraceCloseProc()
{
	++Run;
	fTokenID = tkSymbol;
	fSymbolTokenID = stkBraceClose;
}

void __fastcall TSynWebIDLSyn::SquareOpenProc()
{
	++Run;
	fTokenID = tkSymbol;
	fSymbolTokenID = stkSquareOpen;
	fRange = rsExtendedAttributes;
}

void __fastcall TSynWebIDLSyn::SquareCloseProc()
{
	++Run;
	fTokenID = tkSymbol;
	fSymbolTokenID = stkSquareClose;
	fRange = rsUnknown;
}

void __fastcall TSynWebIDLSyn::UnknownProc()
{
	++Run;
	fTokenID = tkUnknown;
}

void __fastcall TSynWebIDLSyn::Next()
{
	fTokenPos = Run;
	switch(fRange)
	{
		case rsCStyleComment:
		CStyleCommentProc();
		break;
		case rsString:
		StringProc();
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
			SlashProc();
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
			BraceCloseProc();
			break;
			case L']':
			SquareCloseProc();
			break;
			case L'[':
			SquareOpenProc();
			break;
			case L'?':
			QuestionMarkProc();
			break;
			case L':':
			ColonProc();
			break;
			case L'>':
			GreaterProc();
			break;
			case L'<':
			LessProc();
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynWebIDLSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynWebIDLSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

UnicodeString __fastcall TSynWebIDLSyn::GetKeyWords(int TokenKind)
{
	UnicodeString result;
	result = L"any,attribute,boolean,byte,ByteString,callback,const,creator,Date,del"
	           L"eter,dictionary,DOMString,double,enum,exception,float,getter,implement"
	           L"s,inherit,interface,legacycaller,long,object,octet,optional,partial,re"
	           L"adonly,RegExp,sequence,setter,short,static,stringifier,typedef,unresti"
	           L"cted,unrestricted,unsigned,void";
	return result;
}

TtkTokenKind __fastcall TSynWebIDLSyn::GetTokenID()
{
	TtkTokenKind result = tkArguments;
	result = fTokenID;
	if((fRange == rsExtendedAttributes) && !((fTokenID == tkSymbol) && (fSymbolTokenID == stkSquareOpen)))
		result = tkExtendedAttributes;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynWebIDLSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkArguments:
		result = fArgumentsAttri;
		break;
		case tkComment:
		result = fCommentAttri;
		break;
		case tkExtendedAttributes:
		result = fExtendedAttri;
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
		case tkTypes:
		result = fTypesAttri;
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

int __fastcall TSynWebIDLSyn::GetTokenKind()
{
	int result = 0;
	result = int(fTokenID);
	return result;
}

bool __fastcall TSynWebIDLSyn::IsIdentChar(WideChar AChar)
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

UnicodeString __fastcall TSynWebIDLSyn::GetSampleSource()
{
	UnicodeString result;
	result = L"/* WEB IDL sample source */\x0d\x0a"
	           L"[Constructor]\x0d\x0a"
	           L"interface GraphicalWindow {\x0d\x0a"
	           L"  readonly attribute unsigned long width;\x0d\x0a"
	           L"  readonly attribute unsigned long height;\x0d\x0a"
	           L"\x0d\x0a"
	           L"  attribute Paint currentPaint;\x0d\x0a"
	           L"\x0d\x0a"
	           L"  void drawRectangle(float x, float y, float width, float height);"
	           L"\x0d\x0a\x0d\x0a"
	           L"  void drawText(float x, float y, DOMString text);\x0d\x0a"
	           L"};";
	return result;
}

bool __fastcall TSynWebIDLSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterWebIDL;
	return result;
}

/*#static*/
UnicodeString __fastcall TSynWebIDLSyn::GetFriendlyLanguageName()
{
	UnicodeString result;
	result = SYNS_FriendlyLangWebIDL;
	return result;
}

/*#static*/
String __fastcall TSynWebIDLSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangWebIDL;
	return result;
}

void __fastcall TSynWebIDLSyn::ResetRange()
{
	fRange = rsUnknown;
}

void __fastcall TSynWebIDLSyn::SetRange(void* Value)
{
	fRange = (TRangeState)(NativeInt)Value;
}

void* __fastcall TSynWebIDLSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) fRange);
	return result;
}
static bool SynHighlighterWebIDL_Initialized = false;

void SynHighlighterWebIDL_initialization()
{
	if(SynHighlighterWebIDL_Initialized)
		return;
	
	SynHighlighterWebIDL_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynWebIDLSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterWebIDL

