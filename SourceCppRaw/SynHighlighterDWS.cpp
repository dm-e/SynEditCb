
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterDWS.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"
#include "SynEditDelphiInstances.hpp"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Regularexpressions;
using namespace Vcl::Graphics;

namespace Synhighlighterdws
{
#define Synhighlighterdws__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterdws__1 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterdws__2 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterdws__3 (TRegExOptions() << roNotEmpty << roIgnoreCase)
#define Synhighlighterdws__4 (TRegExOptions() << roNotEmpty << roIgnoreCase)
#define Synhighlighterdws__5 (TRegExOptions() << roNotEmpty << roIgnoreCase)
#define Synhighlighterdws__6 (System::Set<WORD, 0, 255>() <<  \
										65 << 66 << 67 << 68 << 69 << 70 <<  \
										71 << 72 << 73 << 74 << 75 << 76 <<  \
										77 << 78 << 79 << 80 << 81 << 82 <<  \
										83 << 84 << 85 << 86 << 87 << 88 <<  \
										89 << 90)
#define Synhighlighterdws__7 (System::Set<TRangeState, TRangeState::rsANil, TRangeState::rsUnKnown>() << rsDirective << rsDirectiveAsm)
#define Synhighlighterdws__8 (System::Set<TRangeState, TRangeState::rsANil, TRangeState::rsUnKnown>() << rsBorAsm << rsDirectiveAsm)
#define Synhighlighterdws__9 (System::Set<TRangeState, TRangeState::rsANil, TRangeState::rsUnKnown>() << rsProperty << rsExports)
#define Synhighlighterdws__10 (System::Set<TtkTokenKind, TtkTokenKind::tkAsm, TtkTokenKind::tkChar>() << tkNull << tkComment << tkDirec << tkSpace)
#define Synhighlighterdws__11 (TRangeStates() << rsAnsi)
#define Synhighlighterdws__12 (TRangeStates() << rsAsm << rsAnsiAsm << rsBorAsm << rsDirectiveAsm)
#define Synhighlighterdws__13 (TRangeStates() << rsHereDocDouble)
#define Synhighlighterdws__14 (TRangeStates() << rsHereDocSingle)
#define Synhighlighterdws__15 (TRangeStates() << rsHereDocSingle)
#define Synhighlighterdws__16 (TRangeStates() << rsBor)
#define Synhighlighterdws__17 (TRangeStates() << rsDirective)
#define Synhighlighterdws__18 (TSynHighlighterCapabilities() << hcUserSettings)
#define Synhighlighterdws__19 (System::Set<unsigned char, 0, 255>() << '_' <<  \
          48 << 49 << 50 << 51 << 52 << 53 <<  \
          54 << 55 << 56 << 57 <<  \
          65 << 66 << 67 << 68 << 69 << 70 <<  \
          71 << 72 << 73 << 74 << 75 << 76 <<  \
          77 << 78 << 79 << 80 << 81 << 82 <<  \
          83 << 84 << 85 << 86 << 87 << 88 <<  \
          89 << 90 <<  \
          97 << 98 << 99 << 100 << 101 << 102 <<  \
          103 << 104 << 105 << 106 << 107 << 108 <<  \
          109 << 110 << 111 << 112 << 113 << 114 <<  \
          115 << 116 << 117 << 118 << 119 << 120 <<  \
          121 << 122)

__fastcall TAnsiStringList::TAnsiStringList() {}
__fastcall TAnsiStringList::TAnsiStringList(bool OwnsObjects) : inherited(OwnsObjects) {}
__fastcall TAnsiStringList::TAnsiStringList(Char QuoteChar, Char Delimiter) : inherited(QuoteChar, Delimiter) {}
__fastcall TAnsiStringList::TAnsiStringList(Char QuoteChar, Char Delimiter, TStringsOptions Options) : inherited(QuoteChar, Delimiter, Options) {}
__fastcall TAnsiStringList::TAnsiStringList(TDuplicates Duplicates, bool Sorted, bool CaseSensitive) : inherited(Duplicates, Sorted, CaseSensitive) {}


   // if the language is case-insensitive keywords *must* be in lowercase
const String cKeyWords[95/*# range 1..95*/] = {L"abstract", L"and", L"array", L"as", L"asm", L"begin", L"break", L"case", L"cdecl", L"class", L"const", L"constructor"
                    , L"continue", L"deprecated", L"destructor", L"div", L"do", L"downto", L"else", L"end", L"ensure", L"empty", L"except"
                    , L"exit", L"export", L"exports", L"external", L"final", L"finalization", L"finally", L"for", L"forward", L"function", L"helper"
                    , L"if", L"implementation", L"implements", L"implies", L"in", L"inherited", L"initialization", L"inline", L"interface", L"is"
                    , L"lambda", L"lazy", L"library", L"method", L"mod", L"new", L"nil", L"not", L"object", L"of", L"old", L"on", L"operator", L"or", L"overload"
                    , L"override", L"pascal", L"partial", L"private", L"procedure", L"program", L"property", L"protected", L"public", L"published"
                    , L"raise", L"record", L"register", L"reintroduce", L"repeat", L"require", L"resourcestring", L"sar", L"sealed", L"set"
                    , L"shl", L"shr", L"static", L"step", L"strict", L"then", L"to", L"try", L"type", L"unit", L"until", L"uses", L"var", L"virtual", L"while"
                    , L"xor"};
const String cKeyWordsPropertyScoped[5/*# range 0..4*/] = {L"default", L"index", L"read", L"stored", L"write"};
const String cKeywordsTypeScoped[2/*# range 0..1*/] = {L"enum", L"flag"};

int __fastcall TAnsiStringList::CompareStrings(const String S1, const String S2)
{
	int result = 0;
	result = CompareText(S1, S2);
	return result;
}


/* TSynDWSSyn */

__fastcall TSynDWSSyn::TSynDWSSyn(TComponent* AOwner)
 : inherited(AOwner),
			fAsmStart(false),
			FRange(rsANil),
			fCommentClose(L'\0'),
			fKeywords(nullptr),
			FKeywordsPropertyScoped(nullptr),
			FKeywordsTypeScoped(nullptr),
			FTokenID(tkAsm),
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
			fSpaceAttri(nullptr)
{
	FCaseSensitive = true; // bypass automatic lowercase, we handle it here
	fAsmAttri = new TSynHighlighterAttributes(SYNS_AttrAssembler, SYNS_FriendlyAttrAssembler);
	fAsmAttri->Foreground = (TColor) RGB(128, 0, 0);
	addAttribute(fAsmAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Foreground = clGreen;
	fCommentAttri->Style = Synhighlighterdws__0;
	addAttribute(fCommentAttri);
	fDirecAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	fDirecAttri->Foreground = ((TColor) 0x808000);
	fDirecAttri->Style = Synhighlighterdws__1;
	addAttribute(fDirecAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterdws__2;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = clBlue;
	addAttribute(fNumberAttri);
	fFloatAttri = new TSynHighlighterAttributes(SYNS_AttrFloat, SYNS_FriendlyAttrFloat);
	fFloatAttri->Foreground = clBlue;
	addAttribute(fFloatAttri);
	fHexAttri = new TSynHighlighterAttributes(SYNS_AttrHexadecimal, SYNS_FriendlyAttrHexadecimal);
	fHexAttri->Foreground = clBlue;
	addAttribute(fHexAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = clBlue;
	addAttribute(fStringAttri);
	fCharAttri = new TSynHighlighterAttributes(SYNS_AttrCharacter, SYNS_FriendlyAttrCharacter);
	fCharAttri->Foreground = clBlue;
	addAttribute(fCharAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	fSymbolAttri->Foreground = clNavy;
	addAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	fKeywords = new TAnsiStringList();
	FKeywordsPropertyScoped = new TAnsiStringList();
	FKeywordsTypeScoped = new TAnsiStringList();
	InitIdent();
	FRange = rsUnKnown;
	fDefaultFilter = SYNS_FilterDWS;

//++ CodeFolding
	RE_BlockBegin = TRegEx(L"\\b(begin|record|class)\\b", Synhighlighterdws__3);
	RE_BlockEnd = TRegEx(L"\\bend\\b", Synhighlighterdws__4);
	RE_Code = TRegEx(L"^\\s*(function|procedure)\\b", Synhighlighterdws__5);
//-- CodeFolding
}

// Destroy
//

__fastcall TSynDWSSyn::~TSynDWSSyn()
{
	// inherited;
	delete fKeywords;
	delete FKeywordsPropertyScoped;
	delete FKeywordsTypeScoped;
}

unsigned int __fastcall TSynDWSSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	WORD C = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		C = (WORD) int((*Str));
		if(Synhighlighterdws__6.Contains(C))
			C = (WORD) (C + (int(L'a') - int(L'A')));
		result = (unsigned int) (result * 692 + C * 171);
		++Str;
	}
	fStringLen = Str - fToIdent;
	result = result % ((unsigned int) (MAXIDX(fIdentFuncTable) + 1));
	return result;
}

TtkTokenKind __fastcall TSynDWSSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkAsm;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 388 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key]();
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynDWSSyn::InitIdent()
{

	auto SetIdentFunc = [&](int h, const TIdentFuncTableFunc Func) -> void 
	{
		fIdentFuncTable[h] = Func;
	};
	int i = 0;
	int stop = 0;
	for(stop = 95 /*# High(cKeyWords) */, i = 1 /*# Low(cKeyWords) */; i <= stop; i++)
	{
		SetIdentFunc((int) HashKey(&((String)cKeyWords[i - 1])[1]), KeyWordFunc);
		fKeywords->Add(cKeyWords[i - 1]);
	}
	for(stop = 4 /*# High(cKeyWordsPropertyScoped) */, i = 0; i <= stop; i++)
	{
		SetIdentFunc((int) HashKey(&((String)cKeyWordsPropertyScoped[i])[1]), FuncPropertyScoped);
		FKeywordsPropertyScoped->Add(cKeyWordsPropertyScoped[i]);
	}
	for(stop = 1 /*# High(cKeywordsTypeScoped) */, i = 0; i <= stop; i++)
	{
		SetIdentFunc((int) HashKey(&((String)cKeywordsTypeScoped[i])[1]), FuncTypeScoped);
		FKeywordsTypeScoped->Add(cKeywordsTypeScoped[i]);
	}
	for(stop = 388 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = AltFunc;
	}
	SetIdentFunc((int) HashKey(const_cast<PWideChar>(L"asm")), FuncAsm);
	SetIdentFunc((int) HashKey(const_cast<PWideChar>(L"end")), FuncEnd);
	SetIdentFunc((int) HashKey(const_cast<PWideChar>(L"property")), FuncProperty);
	SetIdentFunc((int) HashKey(const_cast<PWideChar>(L"type")), FuncType);
	fKeywords->Sorted = true;
}

TtkTokenKind __fastcall TSynDWSSyn::AltFunc()
{
	TtkTokenKind result = tkAsm;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDWSSyn::KeyWordFunc()
{
	TtkTokenKind result = tkAsm;
	String Buf;
	SetString(Buf, fToIdent, fStringLen);
	if((fKeywords->IndexOf(Buf) >= 0) && (fLine[Run - 1] != L'&'))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDWSSyn::FuncAsm()
{
	TtkTokenKind result = tkAsm;
	if(IsCurrentToken(L"asm"))
	{
		result = tkKey;
		FRange = rsAsm;
		fAsmStart = true;
	}
	else
	result = KeyWordFunc();
	return result;
}

TtkTokenKind __fastcall TSynDWSSyn::FuncEnd()
{
	TtkTokenKind result = tkAsm;
	if(IsCurrentToken(L"end"))
	{
		if(fLine[Run - 1] != L'&')
		{
			result = tkKey;
			FRange = rsUnKnown;
		}
		else
		result = tkIdentifier;
	}
	else
	result = KeyWordFunc();
	return result;
}

TtkTokenKind __fastcall TSynDWSSyn::FuncTypeScoped()
{
	TtkTokenKind result = tkAsm;
	String Buf;
	SetString(Buf, fToIdent, fStringLen);
	if((FRange == rsType) && (FKeywordsTypeScoped->IndexOf(Buf) >= 0))
		result = tkKey;
	else
		result = KeyWordFunc();
	return result;
}

TtkTokenKind __fastcall TSynDWSSyn::FuncType()
{
	TtkTokenKind result = tkAsm;
	if(IsCurrentToken(L"type"))
	{
		if(fLine[Run - 1] != L'&')
		{
			result = tkKey;
			FRange = rsType;
		}
		else
		result = tkIdentifier;
	}
	else
	result = KeyWordFunc();
	return result;
}

TtkTokenKind __fastcall TSynDWSSyn::FuncPropertyScoped()
{
	TtkTokenKind result = tkAsm;
	String Buf;
	SetString(Buf, fToIdent, fStringLen);
	if((FRange == rsProperty) && (FKeywordsPropertyScoped->IndexOf(Buf) >= 0))
		result = tkKey;
	else
		result = KeyWordFunc();
	return result;
}

TtkTokenKind __fastcall TSynDWSSyn::FuncProperty()
{
	TtkTokenKind result = tkAsm;
	if(IsCurrentToken(L"property"))
	{
		result = tkKey;
		FRange = rsProperty;
	}
	else
	result = KeyWordFunc();
	return result;
}

void __fastcall TSynDWSSyn::AddressOpProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'@')
		++Run;
}

void __fastcall TSynDWSSyn::AsciiCharProc()
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
	FTokenID = tkChar;
	++Run;
	if(fLine[Run] == L'\'')
		StringAposMultiProc();
	else
	{
		while(IsAsciiChar())
			++Run;
	}
}

void __fastcall TSynDWSSyn::BorProc()
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
			if(Synhighlighterdws__7.Contains(FRange))
				FTokenID = tkDirec;
			else
				FTokenID = tkComment;
			do
			{
				if(fLine[Run] == L'}')
				{
					++Run;
					if(Synhighlighterdws__8.Contains(FRange))
						FRange = rsAsm;
					else
						FRange = rsUnKnown;
					break;
				}
				++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
	}
}

void __fastcall TSynDWSSyn::BraceOpenProc()
{
	if(fLine[Run + 1] == L'$')
	{
		if(FRange == rsAsm)
			FRange = rsDirectiveAsm;
		else
			FRange = rsDirective;
	}
	else
	{
		if(FRange == rsAsm)
			FRange = rsBorAsm;
		else
			FRange = rsBor;
	}
	BorProc();
}

void __fastcall TSynDWSSyn::ColonOrGreaterProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynDWSSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynDWSSyn::IdentProc()
{
	FTokenID = IdentKind(fLine + Run);
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynDWSSyn::IntegerProc()
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
	FTokenID = tkHex;
	while(IsIntegerChar())
		++Run;
}

void __fastcall TSynDWSSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynDWSSyn::LoadDelphiStyle()
{

	auto AddKeyword = [&](const String AName) -> void 
	{
		int i = 0;
		i = (int) HashKey(ustr2pwchar(AName, 1 - 1));
		fIdentFuncTable[i] = KeyWordFunc;
		fKeywords->Add(AName);
	};

	auto RemoveKeyword = [&](const String AName) -> void 
	{
		int i = 0;
		i = fKeywords->IndexOf(AName);
		if(i != -1)
			fKeywords->Delete(i);
	};
	const int clID = clNavy;
	const int clString = clBlue;
	const int clComment = clGreen;
	const String cKeywordsToAdd[1/*# range 0..0*/] = {L"string"};
	const String cKeywordsToRemove[2/*# range 0..1*/] = {L"break", L"exit"};
	int i = 0;
  // This routine can be called to install a Delphi style of colors
  // and highlighting. It modifies the basic TSynDWSSyn to reproduce
  // the most recent Delphi editor highlighting.

  // Delphi colors...
	int stop = 0;
	KeyAttri->Foreground = clID;
	StringAttri->Foreground = clString;
	CommentAttri->Foreground = clComment;

  // These are keywords highlighted in Delphi but not in TSynDWSSyn ..
	for(stop = 0 /*# High(cKeywordsToAdd) */, i = 0 /*# Low(cKeywordsToAdd) */; i <= stop; i++)
	{
		AddKeyword(cKeywordsToAdd[i]);
	}

  // These are keywords highlighted in TSynDWSSyn but not in Delphi...
	for(stop = 1 /*# High(cKeywordsToRemove) */, i = 0 /*# Low(cKeywordsToRemove) */; i <= stop; i++)
	{
		RemoveKeyword(cKeywordsToRemove[i]);
	}
}

void __fastcall TSynDWSSyn::LowerProc()
{
	FTokenID = tkSymbol;
	++Run;
	if((fLine[Run] == L'=') || (fLine[Run] == L'>'))
		++Run;
}

void __fastcall TSynDWSSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynDWSSyn::NumberProc()
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
	FTokenID = tkNumber;
	while(IsNumberChar())
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Run + 1] == L'.')
				goto label0;
			else
				FTokenID = tkFloat;
			break;
			case L'e':
			case L'E':
			FTokenID = tkFloat;
			break;
			case L'-':
			case L'+':
			{
				if(FTokenID != tkFloat)
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

void __fastcall TSynDWSSyn::PointProc()
{
	FTokenID = tkSymbol;
	++Run;
	if((fLine[Run] == L'.') || (fLine[Run - 1] == L')'))
		++Run;
}

void __fastcall TSynDWSSyn::AnsiProc()
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
		FTokenID = tkComment;
		do
		{
			if((fLine[Run] == L'*') && (fLine[Run + 1] == fCommentClose))
			{
				Run += 2;
				if(FRange == rsAnsiAsm)
					FRange = rsAsm;
				else
					FRange = rsUnKnown;
				break;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
		break;
	}
}

void __fastcall TSynDWSSyn::RoundOpenProc()
{
	++Run;
	switch(fLine[Run])
	{
		case L'*':
		{
			++Run;
			if(FRange == rsAsm)
				FRange = rsAnsiAsm;
			else
				FRange = rsAnsi;
			FTokenID = tkComment;
			fCommentClose = L')';
			if(!IsLineEnd(Run))
				AnsiProc();
		}
		break;
		case L'.':
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
		default:
		FTokenID = tkSymbol;
		break;
	}
}

void __fastcall TSynDWSSyn::SemiColonProc()
{
	++Run;
	FTokenID = tkSymbol;
	if(Synhighlighterdws__9.Contains(FRange))
		FRange = rsUnKnown;
}

void __fastcall TSynDWSSyn::SlashProc()
{
	++Run;
	switch(fLine[Run])
	{
		case L'/':
		{
			FTokenID = tkComment;
			do
			{
				++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
		case L'*':
		{
			++Run;
			if(FRange == rsAsm)
				FRange = rsAnsiAsm;
			else
				FRange = rsAnsi;
			FTokenID = tkComment;
			fCommentClose = L'/';
			if(!IsLineEnd(Run))
				AnsiProc();
		}
		break;
		default:
		FTokenID = tkSymbol;
		break;
	}
}

void __fastcall TSynDWSSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynDWSSyn::StringAposProc()
{
	FTokenID = tkString;
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

void __fastcall TSynDWSSyn::StringAposMultiProc()
{
	FTokenID = tkString;
	if((Run > 0) || IsLineEnd(Run + 1))
		++Run;
	FRange = rsHereDocSingle;
	while(!IsLineEnd(Run))
	{
		if(fLine[Run] == L'\'')
		{
			++Run;
			if(fLine[Run] != L'\'')
			{
				FRange = rsUnKnown;
				break;
			}
		}
		++Run;
	}
}

void __fastcall TSynDWSSyn::StringQuoteProc()
{
	FTokenID = tkString;
	if(FRange != rsHereDocDouble)
	{
		FRange = rsHereDocDouble;
		++Run;
	}
	else
	{
		if(IsLineEnd(Run))
		{
			++Run;
			return;
		}
	}
	while(!IsLineEnd(Run))
	{
		if(fLine[Run] == L'\"')
		{
			++Run;
			if(fLine[Run] != L'\"')
			{
				FRange = rsUnKnown;
				break;
			}
		}
		++Run;
	}
}

void __fastcall TSynDWSSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynDWSSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynDWSSyn::Next()
{
	fAsmStart = false;
	fTokenPos = Run;
	switch(FRange)
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
		case rsHereDocSingle:
		StringAposMultiProc();
		break;
		case rsHereDocDouble:
		StringQuoteProc();
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
			StringAposProc();
			break;
			case L'\"':
			StringQuoteProc();
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
					SemiColonProc();
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
			if(fLine[Run] >= L'\x80' && fLine[Run] <= L'\xffff')
			if(IsLetterOrDigit(fLine[Run]))
				IdentProc();
			else
				UnknownProc();
			else
			{
			UnknownProc();
			}
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynDWSSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynDWSSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynDWSSyn::GetTokenID()
{
	TtkTokenKind result = tkAsm;
	if(!fAsmStart && (FRange == rsAsm) && !(Synhighlighterdws__10.Contains(FTokenID)))
		result = tkAsm;
	else
		result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynDWSSyn::GetTokenAttribute()
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
		case tkUnknown:
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynDWSSyn::GetTokenKind()
{
	int result = 0;
	result = int(GetTokenID());
	return result;
}

void* __fastcall TSynDWSSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
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

void __fastcall TSynDWSSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	String CurLine;
	__int64 Line = 0;

	auto BlockDelimiter = [&](int Line) -> bool 
	{
		bool result = false;
		int Index = 0;
		TMatch Match = {};
		result = false;
		Match = RE_BlockBegin.Match(CurLine);
		if(Match.Success)
      // Char must have proper highlighting (ignore stuff inside comments...)
		{
			Index = Match.Index;
			if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Index) != fCommentAttri)
        // And ignore lines with both opening and closing chars in them
			{
				if(!RE_BlockEnd.IsMatch(CurLine, Index + 1))
				{
					FoldRanges->StartFoldRange(Line + 1, FT_Standard);
					result = true;
				}
			}
		}
		else
		{
			Match = RE_BlockEnd.Match(CurLine);
			if(Match.Success)
			{
				{
					Index = Match.Index;
					if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Index) != fCommentAttri)
					{
						FoldRanges->StopFoldRange(Line + 1, FT_Standard);
						result = true;
					}
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
		if(UpperCase(s.SubString(1, 8)) == L"{$REGION")
		{
			FoldRanges->StartFoldRange(Line + 1, FoldRegionType);
			result = true;
		}
		else
		{
			if(UpperCase(s.SubString(1, 11)) == L"{$ENDREGION")
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
		String s;
		result = false;
		s = TrimLeft(CurLine);
		if(UpperCase(s.SubString(1, 7)) == L"{$IFDEF")
		{
			FoldRanges->StartFoldRange(Line + 1, FT_ConditionalDirective);
			result = true;
		}
		else
		{
			if(UpperCase(s.SubString(1, 7)) == L"{$ENDIF")
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
		if(IsMultiLineStatement((int) Line, Synhighlighterdws__11, true, FT_Comment) || IsMultiLineStatement((int) Line, Synhighlighterdws__12, true, FT_Asm) || IsMultiLineStatement((int) Line, Synhighlighterdws__13, true, FT_HereDocDouble) || IsMultiLineStatement((int) Line, Synhighlighterdws__14, true, FT_HereDocSingle) || IsMultiLineStatement((int) Line, Synhighlighterdws__15, true, FT_HereDocSingle) || IsMultiLineStatement((int) Line, Synhighlighterdws__16, true, FT_Comment) || IsMultiLineStatement((int) Line, Synhighlighterdws__17, false))
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
			if(RE_Code.IsMatch(CurLine))
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

void __fastcall TSynDWSSyn::AdjustFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan)
{
	int i = 0;
	int j = 0;
	int SkipTo = 0;
	int ImplementationIndex = 0;
	TSynFoldRange FoldRange = {};
	TMatch Match = {};
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
							Match = RE_BlockBegin.Match(LinesToScan->Strings[FoldRange.FromLine - 1]);
							if(Match.Success)
							{
								if(LowerCase(Match.Value) == L"begin")
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

void __fastcall TSynDWSSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynDWSSyn::ResetRange()
{
	FRange = rsUnKnown;
}

String __fastcall TSynDWSSyn::GetSampleSource()
{
	String result;
	result = L"{ Syntax highlighting }\x0d\x0a"
	           L"procedure TForm1.Button1Click(Sender: TObject);\x0d\x0a"
	           L"var\x0d\x0a"
	           L"  Number, I, X: Integer;\x0d\x0a"
	           L"begin\x0d\x0a"
	           L"  Number := 123456;\x0d\x0a"
	           L"  Caption := 'The Number is' + #32 + IntToStr(Number);\x0d\x0a"
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
String __fastcall TSynDWSSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangPascal;
	return result;
}

/*#static*/
TSynHighlighterCapabilities __fastcall TSynDWSSyn::GetCapabilities()
{
	TSynHighlighterCapabilities result;
	result = inherited::GetCapabilities() + Synhighlighterdws__18;
	return result;
}

bool __fastcall TSynDWSSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterPascal;
	return result;
}

// IsCurrentToken
//

bool __fastcall TSynDWSSyn::IsCurrentToken(const String Token)
{
	bool result = false;
	int i = 0;
	PWideChar Temp = nullptr;
	Temp = fToIdent;
	if(Token.Length() == fStringLen)
	{
		int stop = 0;
		result = true;
		for(stop = fStringLen, i = 1; i <= stop; i++)
		{
			if(((*Temp) != Token[i]) && (((*Temp) > L'z') || (UpCase((*Temp)) != UpCase(Token[i]))))
			{
				result = false;
				break;
			}
			++Temp;
		}
	}
	else
	result = false;
	return result;
}

// IsIdentChar
//

bool __fastcall TSynDWSSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	if(int(AChar) <= 0x7F)
		result = Synhighlighterdws__19.Contains(((AnsiChar) AChar));
	else
		result = IsLetterOrDigit(AChar);
	return result;
}

/*#static*/
String __fastcall TSynDWSSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangPascal;
	return result;
}
static bool SynHighlighterDWS_Initialized = false;

void SynHighlighterDWS_initialization()
{
	if(SynHighlighterDWS_Initialized)
		return;
	
	SynHighlighterDWS_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynDWSSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterDWS

