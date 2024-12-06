
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterPHP.h"
#include "SynEditMiscProcs.h"
#include "SynEditStrConst.h"
#include <Winapi.Windows.hpp>

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditmiscprocs;
using namespace Syneditstrconst;
using namespace System;

namespace Synhighlighterphp
{
#define Synhighlighterphp__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterphp__1 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterphp__2 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterphp__3 (System::Set<TRangeState, TRangeState::rsUnKnown, TRangeState::rsVarExpansion>() << rsComment << rsDocument)
#define Synhighlighterphp__4 (System::Set<TRangeState, TRangeState::rsUnKnown, TRangeState::rsVarExpansion>() << rsComment << rsDocument)
#define Synhighlighterphp__5 (System::Set<TRangeState, TRangeState::rsUnKnown, TRangeState::rsVarExpansion>() << rsComment << rsDocument)
#define Synhighlighterphp__6 (System::Set<TExpansionSyntax, TExpansionSyntax::esNormal, TExpansionSyntax::esBrace>() << esBrace << esComplex)
#define Synhighlighterphp__7 (TSysCharSet() << '_' << '$')



/* expanded keyword list */
const WideString KeyWords[111/*# range 0..110*/] = {L"__autoload", L"__call", L"__callstatic", L"__class__", L"__clone", L"__construct", L"__debuginfo", L"__destruct"
                    , L"__dir__", L"__file__", L"__function__", L"__get", L"__halt_compiler", L"__invoke", L"__isset", L"__line__", L"__method__"
                    , L"__namespace__", L"__set", L"__set_state", L"__sleep", L"__tostring", L"__trait__", L"__unset", L"__wakeup", L"abstract"
                    , L"and", L"array", L"as", L"binary", L"bool", L"boolean", L"break", L"callable", L"case", L"catch", L"cfunction", L"class"
                    , L"clone", L"const", L"continue", L"declare", L"default", L"die", L"do", L"double", L"echo", L"else", L"elseif", L"empty", L"enddeclare"
                    , L"endfor", L"endforeach", L"endif", L"endswitch", L"endwhile", L"eval", L"exception", L"exit", L"extends", L"false"
                    , L"final", L"finally", L"float", L"for", L"foreach", L"function", L"global", L"goto", L"if", L"implements", L"include", L"include_once"
                    , L"instanceof", L"insteadof", L"int", L"integer", L"interface", L"isset", L"list", L"mixed", L"namespace", L"new"
                    , L"null", L"object", L"old_function", L"or", L"parent", L"print", L"private", L"protected", L"public", L"real", L"require", L"require_once"
                    , L"return", L"self", L"static", L"string", L"switch", L"throw", L"trait", L"true", L"try", L"unset", L"use", L"var"
                    , L"void", L"while", L"xor", L"yield"};
const int KeyIndices[439/*# range 0..438*/] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 31, -1, -1, -1, -1, -1, -1, -1, -1, 25, -1, 110, -1, -1, 72, 88, -1, 67, -1, -1, -1, -1, -1, -1, -1, -1, 75, -1, -1, 38, -1
                    , 80, -1, -1, -1, 11, -1, -1, -1, -1, -1, -1, -1, -1, 53, -1, 102, 43, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 104, -1, 40, -1, -1, -1, -1, -1, -1, -1
                    , 76, -1, 101, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, -1, 98, -1, -1, 64, -1, -1, -1, 37, -1, 29, -1, -1, -1, 36, 60, -1, -1, -1, -1, 54, -1, -1, -1, -1, -1, -1, -1, -1, 27, -1, 32, -1, 51, 94
                    , -1, 73, -1, -1, -1, -1, -1, -1, -1, -1, -1, 79, -1, -1, -1, 10, -1, -1, -1, -1, -1, 96, -1, -1, 9, -1, 100, -1, -1, -1, -1, -1, 57, -1, -1, -1, -1, -1, -1, 85, -1, -1, -1, 39, -1, -1, 109, 0, 44, -1, -1
                    , -1, 78, -1, -1, -1, 65, 19, -1, 81, -1, 46, 1, 6, -1, 69, -1, 14, -1, -1, 35, -1, 71, -1, -1, -1, 33, -1, -1, -1, -1, -1, -1, -1, -1, 50, -1, -1, -1, -1, -1, 4, -1, 20, 8, -1, -1, 47, 7, -1, 68, -1, 5, 49, -1
                    , -1, -1, 93, -1, -1, 89, -1, -1, -1, 34, -1, 59, -1, 86, -1, -1, 103, -1, -1, -1, -1, -1, 26, -1, -1, -1, -1, -1, 23, -1, 83, 66, 58, -1, -1, -1, 63, -1, 45, -1, -1, -1, -1, -1, -1, -1, 70, -1, -1, 105
                    , -1, -1, 62, -1, -1, -1, -1, -1, -1, 42, 82, 24, 30, -1, -1, -1, 97, -1, -1, -1, 17, -1, 74, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 106, -1, 22, 3, -1, -1, -1, 90, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, 15, -1, -1, -1, -1, 41, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, 61, -1, -1, -1, -1, -1, -1, 77, -1, 84, -1, -1, 92, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, 13, -1, 48, 12, -1, 28, -1, -1, -1, -1, -1, -1, 21, -1, 95, 108, 91, -1, -1, -1, -1, -1, 99, -1, -1, -1, -1, -1, 55, -1, -1, 107, 56, -1, -1, -1, -1, -1, 87};

/*$Q-*/

unsigned int __fastcall TSynPHPSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 155 + int((*Str)) * 90);
		++Str;
	}
	result = (unsigned int) (result % 439);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynPHPSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkSymbol;
	unsigned int Key = 0;
	fToIdent = MayBe;
	Key = HashKey(MayBe);
	if(Key <= 438 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[Key](KeyIndices[Key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynPHPSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 438 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	for(stop = 438 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynPHPSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkSymbol;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPHPSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynPHPSyn::TSynPHPSyn(TComponent* AOwner)
 : inherited(AOwner),
			fRange(rsUnKnown),
			FTokenID(tkSymbol),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fVariableAttri(nullptr),
			fDocumentAttri(nullptr)
{
	fCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterphp__0;
	AddAttribute(fCommentAttri);
	fDocumentAttri = new TSynHighlighterAttributes(SYNS_AttrDocumentation, SYNS_FriendlyAttrDocumentation);
	fDocumentAttri->Style = Synhighlighterphp__1;
	AddAttribute(fDocumentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterphp__2;
	AddAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	AddAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	AddAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	AddAttribute(fSymbolAttri);
	fVariableAttri = new TSynHighlighterAttributes(SYNS_AttrVariable, SYNS_FriendlyAttrVariable);
	AddAttribute(fVariableAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterPHP;
}

void __fastcall TSynPHPSyn::AndSymbolProc()
{
	{
		FTokenID = tkSymbol;
		switch(fLine[Run + 1])
		{
			case L'=':
			Run += 2;
			break;                 /*and assign*/
			case L'&':
			Run += 2;
			break;                 /*conditional and*/                                 /*and*/
			default:
			++Run;
			break;
		}
	}
}

void __fastcall TSynPHPSyn::CRProc()
{
	FTokenID = tkSpace;
	switch(fLine[Run + 1])
	{
		case L'\x0a':
		Run += 2;
		break;
		default:
		++Run;
		break;
	}
}

void __fastcall TSynPHPSyn::EqualProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':
		Run += 2;
		break;                  /*logical equal*/
		case L'>':
		Run += 2;
		break;                  /*Hash operator*/                                 /*assign*/
		default:
		++Run;
		break;
	}
}

void __fastcall TSynPHPSyn::GreaterProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':
		Run += 2;
		break;                   /*greater than or equal to*/
		case L'>':
		Run += 2;
		break;                                 /*greater than*/
		default:
		++Run;
		break;
	}
}

void __fastcall TSynPHPSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynPHPSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynPHPSyn::LowerProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*less than or equal to*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;
		case L'<':
		{
			FTokenID = tkSymbol;
			if(fLine[Run + 2] == L'=')   /*shift left assign*/
			{
				Run += 3;
			}
			else
                           /*shift left*/
			{
				Run += 2;
			}
		}
		break;                                 /*less than*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPHPSyn::MinusProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':
		Run += 2;
		break;                  /*subtract assign*/
		case L'-':
		Run += 2;
		break;                  /*decrement*/
		case L'>':
		Run += 2;
		break;                  /*Class operator*/                                 /*subtract*/
		default:
		++Run;
		break;
	}
}

void __fastcall TSynPHPSyn::MultiplyProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':
		Run += 2;
		break;                  /*multiply assign*/                                 /*multiply*/
		default:
		++Run;
		break;
	}
}

void __fastcall TSynPHPSyn::NotSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':
		Run += 2;
		break;                  /*not equal*/                                 /*logical complement*/
		default:
		++Run;
		break;
	}
}

void __fastcall TSynPHPSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynPHPSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'.':
			case L'-':
			case L'l':
			case L'L':
			case L'x':
			case L'X':
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
}

void __fastcall TSynPHPSyn::OrSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':
		Run += 2;
		break;                  /*inclusive or assign*/
		case L'|':
		Run += 2;
		break;                  /*conditional or*/                                 /*inclusive or*/
		default:
		++Run;
		break;
	}
}

void __fastcall TSynPHPSyn::PlusProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':
		Run += 2;
		break;                  /*add assign*/
		case L'|':
		Run += 2;
		break;                  /*increment*/                                 /*add*/
		default:
		++Run;
		break;
	}
}

void __fastcall TSynPHPSyn::PoundProc()
{
	do
	{
		++Run;
	}
	while(!IsLineEnd(Run));
	FTokenID = tkComment;
}

void __fastcall TSynPHPSyn::RemainderSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':
		Run += 2;
		break;                  /*remainder assign*/                                 /*remainder*/
		default:
		++Run;
		break;
	}
}

void __fastcall TSynPHPSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

//-- CodeFolding

void __fastcall TSynPHPSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	String CurLine;
	__int64 Line = 0;

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
		String S;
		result = false;
		S = TrimLeft(CurLine);
		if(UpperCase(S.SubString(1, 9)) == L"//#REGION")
		{
			FoldRanges->StartFoldRange(Line + 1, FoldRegionType);
			result = true;
		}
		else
		{
			if(UpperCase(S.SubString(1, 12)) == L"//#ENDREGION")
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
		if(Synhighlighterphp__3.Contains((TRangeState)(NativeInt)GetLineRange(LinesToScan, (int) Line)))
		{
			if(!(Synhighlighterphp__4.Contains((TRangeState)(NativeInt)GetLineRange(LinesToScan, (int) (Line - 1)))))
				FoldRanges->StartFoldRange((int) (Line + 1), 2);
			else
				FoldRanges->NoFoldInfo((int) (Line + 1));
			continue;
		}
		else
		{
			if(Synhighlighterphp__5.Contains((TRangeState)(NativeInt)GetLineRange(LinesToScan, (int) (Line - 1))))
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

void __fastcall TSynPHPSyn::SlashProc()
{
	switch(fLine[Run + 1])
	{
		case L'/':                               /*c++ style comments*/
		{
			Run += 2;
			FTokenID = tkComment;
			while(!IsLineEnd(Run))
				++Run;
		}
		break;
		case L'*':
		{
			if((fLine[Run + 2] == L'*') && (fLine[Run + 3] != L'/'))     /*documentation comment*/
			{
				fRange = rsDocument;
				FTokenID = tkDocument;
				++Run;
			}
			else
                           /*c style comment*/
			{
				fRange = rsComment;
				FTokenID = tkComment;
				++Run;
			}
			++Run;
			while(!IsLineEnd(Run))
				if(fLine[Run] == L'*')
				{
					if(fLine[Run + 1] == L'/')
					{
						fRange = rsUnKnown;
						Run += 2;
						break;
					}
					else
					++Run;
				}
				else
				++Run;
		}
		break;                               /*division assign*/
		case L'=':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*division*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPHPSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynPHPSyn::StringProc()
{

	auto IsEscaped = [&]() -> bool 
	{
		bool result = false;
		int iFirstSlashPos = 0;
		iFirstSlashPos = Run - 1;
		while((iFirstSlashPos > 0) && (fLine[iFirstSlashPos] == L'\\'))
			--iFirstSlashPos;
		result = (Run - iFirstSlashPos + 1) % 2 != 0;
		return result;
	};
	WideChar iCloseChar = L'\0';
	if(IsLineEnd(Run) && (fTokenPos == Run))
	{
		NextProcedure();
		return;
	}
	FTokenID = tkString;
	switch(fRange)
	{
		case rsString39:
		iCloseChar = L'\x27';
		break;
		case rsString34:
		iCloseChar = L'\x22';
		break;
		case rsString96:
		iCloseChar = L'`';
		break;
		default:
		iCloseChar = L'\x00';
		break;
	}
	while(!IsLineEnd(Run))
	{
		if((fLine[Run] == iCloseChar) && !IsEscaped())
			break;
		if((fLine[Run] == L'$') && (iCloseChar == L'\"') && ((fLine[Run + 1] == L'{') || IsIdentChar(fLine[Run + 1])))
		{
			if((Run > 1) && (fLine[Run - 1] == L'{')) /* complex syntax */
				--Run;
			if(!IsEscaped())
        /* break the token to process the variable */
			{
				fRange = rsVarExpansion;
				return;
			}
			else
			{
				if(fLine[Run] == L'{')
					++Run; /* restore Run if we previously deincremented it */
			}
		}
		++Run;
	}
	if(fLine[Run] == iCloseChar)
		fRange = rsUnKnown;
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynPHPSyn::VarExpansionProc()
{
	enum TExpansionSyntax {esNormal,
                       esComplex,
                       esBrace };
	TExpansionSyntax iSyntax = esNormal;
	int iOpenBraces = 0;
	int iOpenBrackets = 0;
	int iTempRun = 0;
	fRange = rsString34; /* var expansion only occurs in double quoted strings */
	FTokenID = tkVariable;
	if(fLine[Run] == L'{')
	{
		iSyntax = esComplex;
		Run += 2; /* skips '{$' */
	}
	else
	{
		++Run;
		if(fLine[Run] == L'{')
		{
			iSyntax = esBrace;
			++Run;
		}
		else
		iSyntax = esNormal;
	}
	if(Synhighlighterphp__6.Contains(iSyntax))
	{
		iOpenBraces = 1;
		while(!IsLineEnd(Run))
		{
			if(fLine[Run] == L'}')
			{
				--iOpenBraces;
				if(iOpenBraces == 0)
				{
					++Run;
					break;
				}
			}
			if(fLine[Run] == L'{')
				++iOpenBraces;
			++Run;
		}
	}
	else
	{
		while(IsIdentChar(fLine[Run]))
			++Run;
		iOpenBrackets = 0;
		iTempRun = Run;
    /* process arrays and objects */
		while(!IsLineEnd(iTempRun))
		{
			if(fLine[iTempRun] == L'[')
			{
				++iTempRun;
				if(fLine[iTempRun] == L'\x27')
				{
					++iTempRun;
					while(!IsLineEnd(iTempRun) && (fLine[iTempRun] != L'\x27'))
						++iTempRun;
					if((fLine[iTempRun] == L'\x27') && (fLine[iTempRun + 1] == L']'))
					{
						iTempRun += 2;
						Run = iTempRun;
						continue;
					}
					else
					break;
				}
				else
				++iOpenBrackets;
			}
			else
			{
				if((fLine[iTempRun] == L'-') && (fLine[iTempRun + 1] == L'>'))
					iTempRun += 2;
				else
					break;
			}
			if(!IsIdentChar(fLine[iTempRun]))
				break;
			else
			{
				do
				{
					++iTempRun;
				}
				while(!!IsIdentChar(fLine[iTempRun]));
			}
			while(fLine[iTempRun] == L']')
			{
				if(iOpenBrackets == 0)
					break;
				--iOpenBrackets;
				++iTempRun;
			}
			if(iOpenBrackets == 0)
				Run = iTempRun;
		}
	}
}

void __fastcall TSynPHPSyn::VariableProc()
{

/*begin*/
	if(IsIdentChar(fLine[Run + 1]))
	{
		++Run;
    /* checking function name */
		if(fLine[Run - 1] == L'@')
		{
			FTokenID = IdentKind((fLine + Run));
      /* isn't function, must be variable */
			if(FTokenID == tkIdentifier)
				FTokenID = tkVariable;
    /* rest are variables */
		}
		else
		FTokenID = tkVariable;
		while(IsIdentChar(fLine[Run]))
		{
			++Run;
		}
	}
	else
	{
		FTokenID = tkSymbol;
		++Run;
	}
/*end*/
}

void __fastcall TSynPHPSyn::XOrSymbolProc()
{
	FTokenID = tkSymbol;
	switch(fLine[Run + 1])
	{
		case L'=':
		Run += 2;
		break;                  /*xor assign*/                                 /*xor*/
		default:
		++Run;
		break;
	}
}

void __fastcall TSynPHPSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynPHPSyn::AnsiCProc()
{
	if(fRange == rsComment)
		FTokenID = tkComment;
	else
		FTokenID = tkDocument;
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
		if(fLine[Run] == L'*')
		{
			if(fLine[Run + 1] == L'/')
			{
				Run += 2;
				fRange = rsUnKnown;
				break;
			}
			else
			++Run;
		}
		else
		++Run;
}

void __fastcall TSynPHPSyn::String39Proc()
{
	fRange = rsString39;
	++Run;
	StringProc();
}

void __fastcall TSynPHPSyn::String34Proc()
{
	fRange = rsString34;
	++Run;
	StringProc();
}

void __fastcall TSynPHPSyn::Next()
{
	fTokenPos = Run;
	switch(fRange)
	{
		case rsComment:
		case rsDocument:
		AnsiCProc();
		break;
		case rsString39:
		case rsString34:
		StringProc();
		break;
		case rsVarExpansion:
		VarExpansionProc();
		break;
		default:
		{
			fRange = rsUnKnown;
			NextProcedure();
		}
		break;
	}

  // ensure that one call of Next is enough to reach next token
	if((fOldRun == Run) && !GetEol())
		Next();
	inherited::Next();
}

void __fastcall TSynPHPSyn::NextProcedure()
{
	switch(fLine[Run])
	{
		case L'&':
		AndSymbolProc();
		break;
		case L'\x27':
		String39Proc();
		break; // single quote
		case L'\x00':
		NullProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		case L'=':
		EqualProc();
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
		case L'<':
		LowerProc();
		break;
		case L'-':
		MinusProc();
		break;
		case L'*':
		MultiplyProc();
		break;
		case L'!':
		NotSymbolProc();
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
		case L'#':
		PoundProc();
		break;
		case L'%':
		RemainderSymbolProc();
		break;
		case L'(':
		case L')':
		case L'{':
		case L'}':
		case L'[':
		case L']':
		case L'@':
		case L':':
		case L',':
		case L'.':
		case L'\\':
		case L'?':
		case L'~':
		case L';':
		SymbolProc();
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
		case L'\x22':
		String34Proc();
		break; // double quote
		case L'`':
		String96Proc();
		break;
		case L'$':
		VariableProc();
		break;
		case L'^':
		XOrSymbolProc();
		break;
		default:
		UnknownProc();
		break;
	}
}

TSynHighlighterAttributes* __fastcall TSynPHPSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynPHPSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynPHPSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) fRange);
	return result;
}

TtkTokenKind __fastcall TSynPHPSyn::GetTokenID()
{
	TtkTokenKind result = tkSymbol;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynPHPSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkDocument:
		result = fDocumentAttri;
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
		case tkVariable:
		result = fVariableAttri;
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

int __fastcall TSynPHPSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynPHPSyn::ResetRange()
{
	fRange = rsUnKnown;
}

void __fastcall TSynPHPSyn::SetRange(void* Value)
{
	fRange = (TRangeState)(NativeInt)Value;
}

bool __fastcall TSynPHPSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterPHP;
	return result;
}

/*#static*/
String __fastcall TSynPHPSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangPHP;
	return result;
}

String __fastcall TSynPHPSyn::GetSampleSource()
{
	String result;
	result = L"// Syntax highlighting\x0d\x0a"
	           L"function printNumber()\x0d\x0a"
	           L"{\x0d\x0a"
	           L"  $number = 1234;\x0d\x0a"
	           L"  print \"The number is $number\";\x0d\x0a"
	           L"  for ($i = 0; $i <= $number; $i++)\x0d\x0a"
	           L"  {\x0d\x0a"
	           L"    $x++;\x0d\x0a"
	           L"    $x--;\x0d\x0a"
	           L"    $x += 1.0;\x0d\x0a"
	           L"  }\x0d\x0a"
	           L"}";
	return result;
}

/*#static*/
String __fastcall TSynPHPSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangPHP;
	return result;
}

bool __fastcall TSynPHPSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	result = IsCharAlphaNumeric(AChar) || CharInSet(AChar, Synhighlighterphp__7);
	return result;
}

bool __fastcall TSynPHPSyn::IsWordBreakChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
		 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
		 case 30: case 31: case 32:
		case L'.':
		case L',':
		case L';':
		case L':':
		case L'\"':
		case L'\'':
		case L'+':
		case L'`':
		case L'-':
		case L'^':
		case L'!':
		case L'?':
		case L'&':
		case L'@':
		case L'§':
		case L'%':
		case L'#':
		case L'~':
		case L'[':
		case L']':
		case L'(':
		case L')':
		case L'{':
		case L'}':
		case L'<':
		case L'>':
		case L'=':
		case L'*':
		case L'/':
		case L'\\':
		case L'|':
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

void __fastcall TSynPHPSyn::String96Proc()
{
	fRange = rsString96;
	++Run;
	StringProc();
}

	static bool SynHighlighterPHP_Initialized = false;
	
	void SynHighlighterPHP_initialization()
	{
		if(SynHighlighterPHP_Initialized)
			return;
		
		SynHighlighterPHP_Initialized = true;
		
		RegisterPlaceableHighlighter(__classid(TSynPHPSyn));
	}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterPHP

