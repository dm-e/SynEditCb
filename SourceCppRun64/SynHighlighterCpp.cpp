
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterCpp.h"
#include <Winapi.Windows.hpp>
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditmiscclasses;
using namespace Syneditstrconst;
using namespace System;

namespace Synhighlightercpp
{
#define Synhighlightercpp__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlightercpp__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightercpp__2 (TSysCharSet() << '\x27' << '\\')
#define Synhighlightercpp__3 (TSysCharSet() << 'e' << 'E')
#define Synhighlightercpp__4 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlightercpp__5 (TSysCharSet() << 'e' << 'E')
#define Synhighlightercpp__6 (TSysCharSet() << 'f' << 'F')
#define Synhighlightercpp__7 (TSysCharSet() << 'l' << 'L')
#define Synhighlightercpp__8 (TSysCharSet() << 'l' << 'L')
#define Synhighlightercpp__9 (TSysCharSet() << 'f' << 'F')
#define Synhighlightercpp__10 (TSysCharSet() << 'u' << 'U')
#define Synhighlightercpp__11 (TSysCharSet() << 'x' << 'X')
#define Synhighlightercpp__12 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlightercpp__13 (System::Set<TtkTokenKind, TtkTokenKind::tkBracket, TtkTokenKind::tkOctal>() << tkComment << tkSpace << tkNull)
#define Synhighlightercpp__14 (TSynHighlighterCapabilities() << hcUserSettings)


const String KeyWords[130/*# range 0..129*/] = {L"__asm", L"__automated", L"__cdecl", L"__classid", L"__closure", L"__declspec", L"__dispid", L"__except", L"__export"
                    , L"__fastcall", L"__finally", L"__import", L"__int16", L"__int32", L"__int64", L"__int8", L"__pascal", L"__property", L"__published"
                    , L"__rtti", L"__stdcall", L"__thread", L"__try", L"_Alignas", L"_Alignof", L"_asm", L"_Atomic", L"_Bool", L"_cdecl"
                    , L"_Complex", L"_export", L"_fastcall", L"_Generic", L"_Imaginary", L"_import", L"_Noreturn", L"_pascal", L"_Pragma", L"_Static_assert"
                    , L"_stdcall", L"_Thread_local", L"alignas", L"alignof", L"and", L"and_eq", L"asm", L"auto", L"bitand", L"bitor"
                    , L"bool", L"break", L"case", L"catch", L"cdecl", L"class", L"compl", L"const", L"const_cast", L"constexpr", L"continue", L"decltype"
                    , L"default", L"delete", L"do", L"double", L"dynamic_cast", L"else", L"enum", L"explicit", L"extern", L"false", L"final"
                    , L"float", L"for", L"friend", L"goto", L"char", L"char16_t", L"char32_t", L"if", L"inline", L"int", L"interface", L"long", L"mutable"
                    , L"namespace", L"new", L"noexcept", L"not", L"not_eq", L"nullptr", L"operator", L"or", L"or_eq", L"override", L"pascal", L"private"
                    , L"protected", L"public", L"register", L"reinterpret_cast", L"restrict", L"return", L"short", L"signed", L"sizeof", L"static"
                    , L"static_assert", L"static_cast", L"struct", L"switch", L"template", L"this", L"thread_local", L"throw", L"true", L"try"
                    , L"typedef", L"typeid", L"typename", L"union", L"unsigned", L"using", L"virtual", L"void", L"volatile", L"while", L"wchar_t", L"xor"
                    , L"xor_eq"};
const int KeyIndices[641/*# range 0..640*/] = {68, -1, -1, -1, -1, -1, -1, -1, -1, 110, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, 17, -1, -1, -1, -1, 97, -1, -1, -1, -1, -1, 62, -1, 28
                    , -1, -1, -1, -1, -1, -1, 64, 21, 90, -1, -1, -1, -1, 108, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, 81, -1, 3, -1, 69, -1, -1, -1, -1, -1, 127, -1, 98, 54, -1, -1, -1, -1, -1, -1, 101, -1
                    , -1, -1, 65, -1, -1, -1, 58, -1, -1, -1, -1, -1, -1, -1, -1, -1, 78, -1, -1, -1, -1, -1, -1, -1, -1, 75, -1, -1, 93, 121, 99, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, 100, -1, -1, 57, 120, 4, -1, 86, -1
                    , -1, -1, -1, 44, -1, -1, -1, -1, 56, -1, -1, -1, -1, -1, -1, -1, -1, 124, -1, -1, -1, -1, 50, -1, -1, -1, 112, -1, -1, -1, -1, 40, -1, -1, -1, -1, -1, -1, -1, -1, 73, -1, -1, -1, -1, -1, -1, -1, -1, 41
                    , -1, -1, -1, 55, 109, 89, -1, 9, 114, 128, -1, 123, -1, 8, -1, -1, -1, -1, -1, -1, 36, -1, -1, -1, 34, -1, 103, -1, -1, 22, -1, 20, -1, -1, -1, -1, -1, 94, -1, 83, -1, 51, -1, 33, -1, -1, -1, -1, -1
                    , 47, -1, -1, -1, -1, 74, -1, -1, -1, -1, -1, -1, -1, -1, 116, 91, -1, 6, -1, -1, -1, -1, -1, -1, 53, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 129, -1, -1, 35, -1, -1, -1, -1, -1, -1, -1, 92, -1, -1
                    , -1, 7, -1, 23, -1, -1, -1, -1, -1, -1, 59, -1, -1, -1, 48, -1, -1, -1, -1, -1, -1, -1, -1, -1, 119, 67, -1, -1, 60, -1, -1, -1, 38, -1, -1, -1, 111, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 88, -1, -1
                    , -1, -1, -1, 80, -1, 42, -1, -1, -1, -1, -1, 25, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 95, 26, -1, -1, -1, -1, -1, -1, -1, 61, -1, -1, -1, 32, 46, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , 122, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, 66, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 71, 72, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, 39, -1, -1
                    , -1, -1, -1, -1, -1, 43, 24, 105, -1, -1, -1, -1, -1, -1, -1, 118, -1, -1, -1, -1, -1, -1, -1, -1, 45, 49, -1, -1, -1, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, 77, 82, -1, -1, 125, 70, -1, -1, -1, -1
                    , -1, -1, -1, 29, -1, -1, -1, -1, -1, -1, -1, 113, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, -1, -1, -1, 11, -1, -1, 104, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, 117, -1
                    , -1, -1, -1, 30, -1, -1, -1, -1, -1, -1, -1, 27, -1, -1, 84, -1, -1, -1, -1, -1, 106, -1, 126, -1, -1, -1, -1, 13, -1, -1, -1, -1, -1, -1, 52, -1, -1, 107, -1, 37, -1, -1, -1, -1, -1, -1, -1, 115, 87
                    , -1, -1, 85, -1, -1, -1, -1, -1, -1, -1, 31, 19, 102, 79, -1, -1, -1, 18, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, -1, -1, -1, -1, -1, -1, 63, -1, 96, -1, -1, -1, 76, -1, -1, -1};

/*$Q-*/

unsigned int __fastcall TSynCppSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 61 + int((*Str)) * 145);
		++Str;
	}
	result = (unsigned int) (result % 641);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynCppSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkBracket;
	unsigned int Key = 0;
	fToIdent = MayBe;
	Key = HashKey(MayBe);
	if(Key <= 640 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[Key](KeyIndices[Key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynCppSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 640 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[352] = FuncAsm;
	fIdentFuncTable[433] = FuncAsm;
	fIdentFuncTable[467] = FuncAsm;
	for(stop = 640 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynCppSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkBracket;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCppSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkBracket;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCppSyn::FuncAsm(int Index)
{
	TtkTokenKind result = tkBracket;
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

__fastcall TSynCppSyn::TSynCppSyn(TComponent* AOwner)
 : inherited(AOwner),
			fAsmStart(false),
			fRange(rsUnknown),
			FTokenID(tkBracket),
			FExtTokenID(xtkAdd),
			fAsmAttri(nullptr),
			fCommentAttri(nullptr),
			fDirecAttri(nullptr),
			fIdentifierAttri(nullptr),
			fInvalidAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fFloatAttri(nullptr),
			fHexAttri(nullptr),
			fOctalAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fCharAttri(nullptr),
			fSymbolAttri(nullptr),
			fBracketAttri(nullptr),
			FNewPreprocesorStyle(false)
{
	fCaseSensitive = true;
	FNewPreprocesorStyle = false;
	fAsmAttri = new TSynHighlighterAttributes(SYNS_AttrAssembler, SYNS_FriendlyAttrAssembler);
	AddAttribute(fAsmAttri);
	fBracketAttri = new TSynHighlighterAttributes(SYNS_AttrBrackets, SYNS_AttrBrackets);
	AddAttribute(fBracketAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlightercpp__0;
	AddAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fInvalidAttri = new TSynHighlighterAttributes(SYNS_AttrIllegalChar, SYNS_FriendlyAttrIllegalChar);
	AddAttribute(fInvalidAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlightercpp__1;
	AddAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	AddAttribute(fNumberAttri);
	fCharAttri = new TSynHighlighterAttributes(SYNS_AttrCharacter, SYNS_FriendlyAttrCharacter);
	AddAttribute(fCharAttri);
	fFloatAttri = new TSynHighlighterAttributes(SYNS_AttrFloat, SYNS_FriendlyAttrFloat);
	AddAttribute(fFloatAttri);
	fHexAttri = new TSynHighlighterAttributes(SYNS_AttrHexadecimal, SYNS_FriendlyAttrHexadecimal);
	AddAttribute(fHexAttri);
	fOctalAttri = new TSynHighlighterAttributes(SYNS_AttrOctal, SYNS_FriendlyAttrOctal);
	AddAttribute(fOctalAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	AddAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	AddAttribute(fSymbolAttri);
	fDirecAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	AddAttribute(fDirecAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fRange = rsUnknown;
	fDefaultFilter = SYNS_FilterCPP;
}

void __fastcall TSynCppSyn::AnsiCProc()
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
				if(fRange == rsAnsiCAsm)
					fRange = rsAsm;
				else
				{
					if(fRange == rsAnsiCAsmBlock)
						fRange = rsAsmBlock;
					else
					{
						if((fRange == rsDirectiveComment) && !IsLineEnd(Run))
							fRange = rsMultiLineDirective;
						else
							fRange = rsUnknown;
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

void __fastcall TSynCppSyn::AndSymbolProc()
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

void __fastcall TSynCppSyn::AsciiCharProc()
{
	FTokenID = tkChar;
	do
	{
		if(fLine[Run] == L'\\')
		{
			if(CharInSet(fLine[Run + 1], Synhighlightercpp__2))
				++Run;
		}
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\x27')));
	if(fLine[Run] == L'\x27')
		++Run;
}

void __fastcall TSynCppSyn::AtSymbolProc()
{
	FTokenID = tkUnknown;
	++Run;
}

void __fastcall TSynCppSyn::BraceCloseProc()
{
	++Run;
	FTokenID = tkBracket;
	FExtTokenID = xtkBraceClose;
	if(fRange == rsAsmBlock)
		fRange = rsUnknown;
}

void __fastcall TSynCppSyn::BraceOpenProc()
{
	++Run;
	FTokenID = tkBracket;
	FExtTokenID = xtkBraceOpen;
	if(fRange == rsAsm)
	{
		fRange = rsAsmBlock;
		fAsmStart = true;
	}
}

void __fastcall TSynCppSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run + 1] == L'\x0a')
		++Run;
}

void __fastcall TSynCppSyn::ColonProc()
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

void __fastcall TSynCppSyn::CommaProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkComma;
}

void __fastcall TSynCppSyn::DirectiveProc()
{
	bool WasWord = false;
	if(FNewPreprocesorStyle)
	{
		if(Trim(fLine)[1] != L'#')
		{
			FTokenID = tkUnknown;
			++Run;
			return;
		}
		WasWord = false;
		FTokenID = tkDirective;
		fRange = rsUnknown;
		do
		{
			if(!WasWord && IsIdentChar(fLine[Run]))
				WasWord = true;
			++Run;
		}
		while(!(IsLineEnd(Run) || (fLine[Run] == L' ') && WasWord));
	}
	else
	{
		if(Trim(fLine)[1] != L'#') // '#' is not first char on the line, treat it as an invalid char
		{
			FTokenID = tkUnknown;
			++Run;
			return;
		}
		FTokenID = tkDirective;
		do
		{
			if(fLine[Run] == L'/') // comment?
			{
				if(fLine[Run + 1] == L'/') // is end of directive as well
				{
					fRange = rsUnknown;
					return;
				}
				else
				{
					if(fLine[Run + 1] == L'*') // might be embedded only
					{
						fRange = rsDirectiveComment;
						return;
					}
				}
			}
			if((fLine[Run] == L'\\') && (fLine[Run + 1] == L'\x00')) // a multiline directive
			{
				++Run;
				fRange = rsMultiLineDirective;
				return;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
	}
}

void __fastcall TSynCppSyn::DirectiveEndProc()
{
	FTokenID = tkDirective;
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
	fRange = rsUnknown;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label3; // comment?
			case L'/':
			{
				switch(fLine[Run + 1])
				{
					case L'/': // is end of directive as well
					{
						fRange = rsUnknown;
						return;
					} // might be embedded only
					case L'*':
					{
						fRange = rsDirectiveComment;
						return;
					}
					default:
					  ;
					break;
				}
			}
			break; // yet another line?
			case L'\\':
			{
				if(fLine[Run + 1] == L'\x00')
				{
					++Run;
					fRange = rsMultiLineDirective;
					return;
				}
			}
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!IsLineEnd(Run));
	label3:;
}

void __fastcall TSynCppSyn::EqualProc()
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

void __fastcall TSynCppSyn::GreaterProc()
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

void __fastcall TSynCppSyn::QuestionProc()
{
	FTokenID = tkSymbol;                /*conditional*/
	FExtTokenID = xtkQuestion;
	++Run;
}

void __fastcall TSynCppSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynCppSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynCppSyn::LowerProc()
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

void __fastcall TSynCppSyn::MinusProc()
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

void __fastcall TSynCppSyn::ModSymbolProc()
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

void __fastcall TSynCppSyn::NotSymbolProc()
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

void __fastcall TSynCppSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynCppSyn::NumberProc()
{

	auto IsNumberChar = [&](int Run) -> bool 
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

	auto IsDigitPlusMinusChar = [&](int Run) -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'+':
			case L'-':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};

	auto IsHexDigit = [&](int Run) -> bool 
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

	auto IsAlphaUncerscore = [&](int Run) -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			case L'_':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	int idx1 = 0; // token[1]
	int i = 0;
	idx1 = Run;
	++Run;
	FTokenID = tkNumber;
	while(IsNumberChar(Run))
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Succ(Run)] == L'.')
				goto label4;
			else
			{
				if(FTokenID != tkHex)
					FTokenID = tkFloat;
				else
 // invalid
				{
					FTokenID = tkUnknown;
					return;
				}
			}
			break;
			case L'-':
			case L'+':
			{
				if(FTokenID != tkFloat) // number <> float. an arithmetic operator
					return;
				if(!CharInSet(fLine[Pred(Run)], Synhighlightercpp__3))
					return; // number = float, but no exponent. an arithmetic operator
				if(!IsDigitPlusMinusChar(Succ(Run))) // invalid
				{
					++Run;
					FTokenID = tkUnknown;
					return;
				}
			}
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55:
			if((Run == Succ(idx1)) && (fLine[idx1] == L'0')) // octal number
				FTokenID = tkOctal;
			break;
			case L'8':
			case L'9':
			if((fLine[idx1] == L'0') && ((FTokenID != tkHex) && (FTokenID != tkFloat))) // invalid octal char
				FTokenID = tkUnknown;
			break;
			case 97: case 98: case 99: case 100:
			case 65: case 66: case 67: case 68:
			if(FTokenID != tkHex)
				goto label5;
			break;
			case L'e':
			case L'E':
			if(FTokenID != tkHex)
			{
				if(CharInSet(fLine[Pred(Run)], Synhighlightercpp__4)) // exponent
				{
					int stop = 0;
					for(stop = Pred(Run), i = idx1; i <= stop; i++)
					{
						if(CharInSet(fLine[i], Synhighlightercpp__5)) // too many exponents
						{
							FTokenID = tkUnknown;
							return;
						}
					}
					if(!IsDigitPlusMinusChar(Succ(Run)))
						goto label6;
					else
						FTokenID = tkFloat;
				}
				else
				goto label7;
			}
			break;
			case L'f':
			case L'F':
			if(FTokenID != tkHex)
			{
				int stop = 0;
				for(stop = Pred(Run), i = idx1; i <= stop; i++)
				{
					if(CharInSet(fLine[i], Synhighlightercpp__6)) // declaration syntax error
					{
						FTokenID = tkUnknown;
						return;
					}
				}
				if(FTokenID == tkFloat)
				{
					if(CharInSet(fLine[Pred(Run)], Synhighlightercpp__7))
						goto label8;
				}
				else
				FTokenID = tkFloat;
			}
			break;
			case L'l':
			case L'L':
			{
				int stop = 0;
				for(stop = Run - 2, i = idx1; i <= stop; i++)
				{
					if(CharInSet(fLine[i], Synhighlightercpp__8)) // declaration syntax error
					{
						FTokenID = tkUnknown;
						return;
					}
				}
				if(FTokenID == tkFloat)
				{
					if(CharInSet(fLine[Pred(Run)], Synhighlightercpp__9))
						goto label9;
				}
			}
			break;
			case L'u':
			case L'U':
			if(FTokenID == tkFloat)
				goto label10;
			else
			{
				int stop = 0;
				for(stop = Pred(Run), i = idx1; i <= stop; i++)
				{
					if(CharInSet(fLine[i], Synhighlightercpp__10)) // declaration syntax error
					{
						FTokenID = tkUnknown;
						return;
					}
				}
			}
			break;
			case L'x':
			case L'X':
			if((Run == Succ(idx1)) && (fLine[idx1] == L'0') && IsHexDigit(Succ(Run)))   // 0x... 'x' must be second char
  // 0x...
 // 0x... must be continued with a number
				FTokenID = tkHex;
			else
 // invalid char
			{
				if(!IsIdentChar(fLine[Succ(Run)]) && CharInSet(fLine[Succ(idx1)], Synhighlightercpp__11))
				{
					++Run; // highlight 'x' too
					FTokenID = tkUnknown;
				}
				goto label11;
			}
			break;
			default:
			  ;
			break;
		} // case
		++Run;
	} // while
	label4:;
	label5:;
	label6:;
	label7:;
	label8:;
	label9:;
	label10:;
	label11:;
	if(IsAlphaUncerscore(Run))
		FTokenID = tkUnknown;
}

void __fastcall TSynCppSyn::OrSymbolProc()
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

void __fastcall TSynCppSyn::PlusProc()
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

void __fastcall TSynCppSyn::PointProc()
{
	FTokenID = tkSymbol;
	if((fLine[Run + 1] == L'.') && (fLine[Run + 2] == L'.'))                              /*ellipse*/
	{
		Run += 3;
		FExtTokenID = xtkEllipse;
	}
	else
	{
		if(CharInSet(fLine[Run + 1], Synhighlightercpp__12)) // float
		{
			--Run; // numberproc must see the point
			NumberProc();
		}
		else
                                 /*point*/
		{
			++Run;
			FExtTokenID = xtkPoint;
		}
	}
}

void __fastcall TSynCppSyn::RoundCloseProc()
{
	++Run;
	FTokenID = tkBracket;
	FExtTokenID = xtkRoundClose;
}

void __fastcall TSynCppSyn::RoundOpenProc()
{
	++Run;
	FTokenID = tkBracket;
	FExtTokenID = xtkRoundOpen;
}

void __fastcall TSynCppSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	String CurLine;
	__int64 Line = 0;

	auto InsideComment = [&](int Line, int Col) -> bool 
	{
		bool result = false;
		result = GetHighlighterAttriAtRowCol(LinesToScan, Line, Col) == fCommentAttri;
		return result;
	};

	auto LineHasChar = [&](int Line, Char character, int StartCol) -> bool 
	{
		bool result = false;
		int i = 0;
		int stop = 0;
		result = false;
		for(stop = CurLine.Length(), i = StartCol; i <= stop; i++)
		{
			if(CurLine[i] == character)
        // Char must have proper highlighting (ignore stuff inside comments...)
			{
				if(!InsideComment(Line, i))
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
				if(!InsideComment(Line, Col))
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
        // Char must have symbol attri too
				{
					if(!InsideComment(Line, Col))
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
		String S;
		result = false;
		S = TrimLeft(CurLine);
		if(UpperCase(S.SubString(1, 14)) == L"#PRAGMA REGION")
		{
			FoldRanges->StartFoldRange(Line + 1, FoldRegionType);
			result = true;
		}
		else
		{
			if(UpperCase(S.SubString(1, 17)) == L"#PRAGMA ENDREGION")
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

    // Find Fold regions
		}
		CurLine = LinesToScan->Strings[Line];
		if(FoldRegion((int) Line))
			continue;

    // Find an braces on this line  (Fold Type 1)
		CurLine = LinesToScan->Strings[Line];
		if(!FindBraces((int) Line))
			FoldRanges->NoFoldInfo((int) (Line + 1));
	} // while Line
}

void __fastcall TSynCppSyn::SemiColonProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSemiColon;
	if(fRange == rsAsm)
		fRange = rsUnknown;
}

void __fastcall TSynCppSyn::SlashProc()
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
			if(fRange == rsAsm)
				fRange = rsAnsiCAsm;
			else
			{
				if(fRange == rsAsmBlock)
					fRange = rsAnsiCAsmBlock;
				else
				{
					if(fRange != rsDirectiveComment)
						fRange = rsAnsiC;
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
						if(fRange == rsDirectiveComment)
							fRange = rsMultiLineDirective;
						else
						{
							if(fRange == rsAnsiCAsm)
								fRange = rsAsm;
							else
							{
								if(fRange == rsAnsiCAsmBlock)
									fRange = rsAsmBlock;
								else
									fRange = rsUnknown;
							}
						}
						goto label12;
					}
					else
					++Run;
					break;
					case L'\x0a':
					case L'\x0d':
					{
						if(fRange == rsDirectiveComment)
							fRange = rsAnsiC;
						goto label13;
					}
					default:
					++Run;
					break;
				}
			label12:;
			label13:;
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

void __fastcall TSynCppSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynCppSyn::SquareCloseProc()
{
	++Run;
	FTokenID = tkBracket;
	FExtTokenID = xtkSquareClose;
}

void __fastcall TSynCppSyn::SquareOpenProc()
{
	++Run;
	FTokenID = tkBracket;
	FExtTokenID = xtkSquareOpen;
}

void __fastcall TSynCppSyn::StarProc()
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

void __fastcall TSynCppSyn::StringProc()
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
					fRange = rsMultiLineString;
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

void __fastcall TSynCppSyn::StringEndProc()
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
	fRange = rsUnknown;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label14;
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
						fRange = rsMultiLineString;
						return;
					}
					default:
					  ;
					break;
				}
			}
			break;
			case L'\x22':
			goto label15;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\x22')));
	label14:;
	label15:;
	if(fLine[Run] == L'\x22')
		++Run;
}

void __fastcall TSynCppSyn::TildeProc()
{
	++Run;                            /*bitwise complement*/
	FTokenID = tkSymbol;
	FExtTokenID = xtkBitComplement;
}

void __fastcall TSynCppSyn::XOrSymbolProc()
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

void __fastcall TSynCppSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynCppSyn::Next()
{
	fAsmStart = false;
	fTokenPos = Run;
	switch(fRange)
	{
		case rsAnsiC:
		case rsAnsiCAsm:
		case rsAnsiCAsmBlock:
		case rsDirectiveComment:
		AnsiCProc();
		break;
		case rsMultiLineDirective:
		DirectiveEndProc();
		break;
		case rsMultiLineString:
		StringEndProc();
		break;
		default:
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
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynCppSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynCppSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynCppSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) fRange);
	return result;
}

TtkTokenKind __fastcall TSynCppSyn::GetTokenID()
{
	TtkTokenKind result = tkBracket;
	result = FTokenID;
	if(((fRange == rsAsm) || (fRange == rsAsmBlock)) && !fAsmStart && !(Synhighlightercpp__13.Contains(FTokenID)))
		result = tkAsm;
	return result;
}

TxtkTokenKind __fastcall TSynCppSyn::GetExtTokenID()
{
	TxtkTokenKind result = xtkAdd;
	result = FExtTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynCppSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	FTokenID = GetTokenID();
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
		case tkFloat:
		result = fFloatAttri;
		break;
		case tkHex:
		result = fHexAttri;
		break;
		case tkOctal:
		result = fOctalAttri;
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
		case tkUnknown:
		result = fInvalidAttri;
		break;
		case tkBracket:
		result = fBracketAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynCppSyn::GetTokenKind()
{
	int result = 0;
	result = int(GetTokenID());
	return result;
}

void __fastcall TSynCppSyn::ResetRange()
{
	fRange = rsUnknown;
}

void __fastcall TSynCppSyn::SetRange(void* Value)
{
	fRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynCppSyn::EnumUserSettings(TStrings* settings)
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
					with0->GetKeyNames(settings);
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

bool __fastcall TSynCppSyn::UseUserSettings(int settingIndex)
{
	bool result = false;

	auto ReadCPPBSettings = [&](int settingIndex) -> bool 
	{
		bool result = false;

		auto ReadCPPBSetting = [&](String settingTag, TSynHighlighterAttributes* attri, String key) -> bool 
		{
			bool result = false;

			auto ReadCPPB1 = [&](String settingTag, TSynHighlighterAttributes* attri, String name) -> bool 
			{
				bool result = false;
				int i = 0;
				int stop = 0;
				for(stop = name.Length(), i = 1; i <= stop; i++)
				{
					if(name[i] == L' ')
						name[i] = L'_';
				}
				result = attri->LoadFromBorlandRegistry(HKEY_CURRENT_USER, String(L"\\SOFTWARE\\Borland\\C++Builder\\") + settingTag
	           + L"\\Highlight", name, true);
				return result;
			}; /* ReadCPPB1 */

			auto ReadCPPB3OrMore = [&](String settingTag, TSynHighlighterAttributes* attri, String key) -> bool 
			{
				bool result = false;
				result = attri->LoadFromBorlandRegistry(HKEY_CURRENT_USER, String(L"\\Software\\Borland\\C++Builder\\") + settingTag
	           + L"\\Editor\\Highlight", key, false);
				return result;
			}; /* ReadCPPB3OrMore */ /* ReadCPPBSetting */
			try
			{
				if(settingTag[1] == L'1')
					result = ReadCPPB1(settingTag, attri, key);
				else
					result = ReadCPPB3OrMore(settingTag, attri, key);
			}
			catch(...)
			{
				result = false;
			}
			return result;
		}; /* ReadCPPBSetting */
		TSynHighlighterAttributes* tmpStringAttri = nullptr;
		TSynHighlighterAttributes* tmpCharAttri = nullptr;
		TSynHighlighterAttributes* tmpNumberAttri = nullptr;
		TSynHighlighterAttributes* tmpFloatAttri = nullptr;
		TSynHighlighterAttributes* tmpHexAttri = nullptr;
		TSynHighlighterAttributes* tmpOctalAttri = nullptr;
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
				tmpCharAttri = new TSynHighlighterAttributes(L"", L"");
				tmpNumberAttri = new TSynHighlighterAttributes(L"", L"");
				tmpFloatAttri = new TSynHighlighterAttributes(L"", L"");
				tmpHexAttri = new TSynHighlighterAttributes(L"", L"");
				tmpOctalAttri = new TSynHighlighterAttributes(L"", L"");
				tmpKeyAttri = new TSynHighlighterAttributes(L"", L"");
				tmpSymbolAttri = new TSynHighlighterAttributes(L"", L"");
				tmpAsmAttri = new TSynHighlighterAttributes(L"", L"");
				tmpCommentAttri = new TSynHighlighterAttributes(L"", L"");
				tmpIdentifierAttri = new TSynHighlighterAttributes(L"", L"");
				tmpInvalidAttri = new TSynHighlighterAttributes(L"", L"");
				tmpSpaceAttri = new TSynHighlighterAttributes(L"", L"");
				tmpDirecAttri = new TSynHighlighterAttributes(L"", L"");
				tmpStringAttri->Assign(fStringAttri);
				tmpCharAttri->Assign(fCharAttri);
				tmpNumberAttri->Assign(fNumberAttri);
				tmpFloatAttri->Assign(fFloatAttri);
				tmpHexAttri->Assign(fHexAttri);
				tmpOctalAttri->Assign(fOctalAttri);
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
				result = result && ReadCPPBSetting(s->Strings[settingIndex], fCommentAttri, L"Comment") && ReadCPPBSetting(s->Strings[settingIndex], fIdentifierAttri, L"Identifier") && ReadCPPBSetting(s->Strings[settingIndex], fInvalidAttri, L"Illegal Char") && ReadCPPBSetting(s->Strings[settingIndex], fKeyAttri, L"Reserved word") && ReadCPPBSetting(s->Strings[settingIndex], fNumberAttri, L"Integer") && ReadCPPBSetting(s->Strings[settingIndex], fFloatAttri, L"Float") && ReadCPPBSetting(s->Strings[settingIndex], fHexAttri, L"Hex") && ReadCPPBSetting(s->Strings[settingIndex], fOctalAttri, L"Octal") && ReadCPPBSetting(s->Strings[settingIndex], fSpaceAttri, L"Whitespace") && ReadCPPBSetting(s->Strings[settingIndex], fStringAttri, L"String") && ReadCPPBSetting(s->Strings[settingIndex], fCharAttri, L"Character") && ReadCPPBSetting(s->Strings[settingIndex], fSymbolAttri, L"Symbol") && ReadCPPBSetting(s->Strings[settingIndex], fDirecAttri, L"Preprocessor");
				if(!result)
				{
					fStringAttri->Assign(tmpStringAttri);
					fCharAttri->Assign(tmpCharAttri);
					fNumberAttri->Assign(tmpNumberAttri);
					fFloatAttri->Assign(tmpFloatAttri);
					fHexAttri->Assign(tmpHexAttri);
					fOctalAttri->Assign(tmpOctalAttri);
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
				delete tmpCharAttri;
				delete tmpNumberAttri;
				delete tmpFloatAttri;
				delete tmpHexAttri;
				delete tmpOctalAttri;
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
} /* TSynCppSyn.UseUserSettings */

bool __fastcall TSynCppSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterCPP;
	return result;
}

/*#static*/
String __fastcall TSynCppSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangCPP;
	return result;
}

/*#static*/
TSynHighlighterCapabilities __fastcall TSynCppSyn::GetCapabilities()
{
	TSynHighlighterCapabilities result;
	result = inherited::GetCapabilities() + Synhighlightercpp__14;
	return result;
}

String __fastcall TSynCppSyn::GetSampleSource()
{
	String result;
	result = L"// Syntax Highlighting\x0d\x0a"
	           L"void __fastcall TForm1::Button1Click(TObject *Sender)\x0d\x0a"
	           L"{\x0d\x0a"
	           L"  int number = 123456;\x0d\x0a"
	           L"  char c = 'a';\x0d\x0a"
	           L"  Caption = \"The number is \" + IntToStr(i);\x0d\x0a"
	           L"  for (int i = 0; i <= number; i++)\x0d\x0a"
	           L"  {\x0d\x0a"
	           L"    x -= 0xff;\x0d\x0a"
	           L"    x -= 023;\x0d\x0a"
	           L"    x += 1.0;\x0d\x0a"
	           L"    x += @; /* illegal character */\x0d\x0a"
	           L"  }\x0d\x0a"
	           L"  #ifdef USE_ASM\x0d\x0a"
	           L"    asm\x0d\x0a"
	           L"    {\x0d\x0a"
	           L"      ASM MOV AX, 0x1234\x0d\x0a"
	           L"      ASM MOV i, AX\x0d\x0a"
	           L"    }\x0d\x0a"
	           L"  #endif\x0d\x0a"
	           L"}";
	return result;
}

/*#static*/
String __fastcall TSynCppSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangCPP;
	return result;
}

void __fastcall TSynCppSyn::SetNewPreprocesorStyle(bool Value)
{
	if(FNewPreprocesorStyle != Value)
	{
		FNewPreprocesorStyle = Value;
		ResetRange();
	}
}
static bool SynHighlighterCpp_Initialized = false;

void SynHighlighterCpp_initialization()
{
	if(SynHighlighterCpp_Initialized)
		return;
	
	SynHighlighterCpp_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynCppSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterCpp

