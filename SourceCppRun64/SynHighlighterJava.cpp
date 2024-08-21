
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterJava.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterjava
{
#define Synhighlighterjava__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterjava__1 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterjava__2 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterjava__3 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterjava__4 (System::Set<TRangeState, TRangeState::rsANil, TRangeState::rsUnKnown>() << rsComment << rsDocument)
#define Synhighlighterjava__5 (System::Set<TRangeState, TRangeState::rsANil, TRangeState::rsUnKnown>() << rsComment << rsDocument)
#define Synhighlighterjava__6 (System::Set<TRangeState, TRangeState::rsANil, TRangeState::rsUnKnown>() << rsComment << rsDocument)
#define Synhighlighterjava__7 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterjava__8 (TSysCharSet() << '_' << '$')


const String Keywords[52/*# range 0..51*/] = {L"abstract", L"assert", L"boolean", L"break", L"byte", L"case", L"catch", L"char", L"class", L"const", L"continue"
                    , L"default", L"do", L"double", L"else", L"extends", L"false", L"final", L"finally", L"float", L"for", L"goto", L"if", L"implements"
                    , L"import", L"instanceof", L"int", L"interface", L"long", L"native", L"new", L"null", L"package", L"private", L"protected"
                    , L"public", L"return", L"short", L"static", L"strictfp", L"super", L"switch", L"synchronized", L"this", L"throw", L"throws"
                    , L"transient", L"true", L"try", L"void", L"volatile", L"while"};
const int KeyIndices[113/*# range 0..112*/] = {1, -1, -1, 45, -1, -1, 39, -1, -1, -1, 9, 36, 26, -1, -1, 4, 27, 5, 50, 25, 33, -1, 18, -1, 17, 6, 28, -1, -1, -1, 51, -1, -1, -1, -1, 21, 48, -1, 7, 3, -1, -1, -1, 49, 41
                    , -1, 35, -1, 46, 40, -1, -1, -1, 42, -1, -1, -1, -1, -1, -1, 43, -1, -1, -1, -1, -1, 13, 24, -1, 37, -1, -1, 31, 11, -1, 22, -1, -1, -1, 44, -1, 10, 19, 8, -1, -1, 38, 15, -1, -1, 34, -1, 14, -1, -1, -1
                    , 0, 12, -1, 20, -1, 23, -1, 47, -1, -1, 29, 30, -1, -1, 16, 32, 2};

/*$Q-*/

unsigned int __fastcall TSynJavaSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 598 + int((*Str)) * 349);
		++Str;
	}
	result = (unsigned int) (result % 113);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynJavaSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkSymbol;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 112 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynJavaSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 112 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	for(stop = 112 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynJavaSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkSymbol;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynJavaSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynJavaSyn::TSynJavaSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FRoundCount(0),
			FSquareCount(0),
			FTokenID(tkSymbol),
			FExtTokenID(xtkAdd),
			fCommentAttri(nullptr),
			fDocumentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fInvalidAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr)
{
	FCaseSensitive = true;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterjava__0;
	addAttribute(fCommentAttri);
	fDocumentAttri = new TSynHighlighterAttributes(SYNS_AttrDocumentation, SYNS_FriendlyAttrDocumentation);
	fDocumentAttri->Style = Synhighlighterjava__1;
	addAttribute(fDocumentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fInvalidAttri = new TSynHighlighterAttributes(SYNS_AttrInvalidSymbol, SYNS_FriendlyAttrInvalidSymbol);
	addAttribute(fInvalidAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterjava__2;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	fSpaceAttri->Foreground = (TColor) clWindow;
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterJava;
} /* Create */

void __fastcall TSynJavaSyn::CommentProc()
{
	if(FRange == rsComment)
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
		switch(fLine[Run])
		{
			case L'*':
			if(fLine[Run + 1] == L'/')
			{
				Run += 2;
				FRange = rsUnKnown;
				goto label0;
			}
			else
			++Run;
			break;
			default:
			++Run;
			break;
		}
	label0:;
}

void __fastcall TSynJavaSyn::AndSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*and assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkAndAssign;
		}
		break;                               /*conditional and*/
		case L'&':
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkCondAnd;
		}
		break;                                 /*and*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkAnd;
		}
		break;
	}
}

void __fastcall TSynJavaSyn::AsciiCharProc()
{
	FTokenID = tkString;
	do
	{
		if(IsLineEnd(Run))
			break;
		if(fLine[Run] == L'\x5c')
			++Run; // backslash, if we have an escaped single character, skip to the next
		if(!IsLineEnd(Run))
			++Run; //Add check here to prevent overrun from backslash being last char
	}
	while(!(fLine[Run] == L'\x27'));
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynJavaSyn::AtSymbolProc()
{
	FTokenID = tkInvalid;
	++Run;
}

void __fastcall TSynJavaSyn::BraceCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkBraceClose;
}

void __fastcall TSynJavaSyn::BraceOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkBraceOpen;
}

void __fastcall TSynJavaSyn::CRProc()
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

void __fastcall TSynJavaSyn::ColonProc()
{
	++Run;                            /*colon - conditional*/
	FTokenID = tkSymbol;
	FExtTokenID = xtkColon;
}

void __fastcall TSynJavaSyn::CommaProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkComma;
}

void __fastcall TSynJavaSyn::EqualProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*logical equal*/
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkLogEqual;
		}
		break;                                 /*assign*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkAssign;
		}
		break;
	}
}

void __fastcall TSynJavaSyn::GreaterProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*greater than or equal to*/
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkGreaterThanEqual;
		}
		break;
		case L'>':
		{
			switch(fLine[Run + 2])
			{
				case L'=':                         /*shift right assign*/
				{
					Run += 3;
					FExtTokenID = xtkShiftRightAssign;
				}
				break;
				case L'>':
				if(fLine[Run + 3] == L'=')
				{
					Run += 4;             /*unsigned shift right assign*/
					FExtTokenID = xtkUnsignShiftRightAssign;
				}
				else
				{
					Run += 3;             /*unsigned shift right*/
					FExtTokenID = xtkUnsignShiftRight;
				}
				break;                           /*shift right*/
				default:
				{
					Run += 2;
					FExtTokenID = xtkShiftRight;
				}
				break;
			}
			FTokenID = tkSymbol;
		}
		break;                                 /*greater than*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkGreaterThan;
		}
		break;
	}
}

void __fastcall TSynJavaSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynJavaSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynJavaSyn::LowerProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*less than or equal to*/
		{
			Run += 2;
			FTokenID = tkSymbol;
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
			FTokenID = tkSymbol;
		}
		break;                                 /*less than*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkLessThan;
		}
		break;
	}
}

void __fastcall TSynJavaSyn::MinusProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*subtract assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkSubtractAssign;
		}
		break;                               /*decrement*/
		case L'-':
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkDecrement;
		}
		break;                                 /*subtract*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkSubtract;
		}
		break;
	}
}

void __fastcall TSynJavaSyn::MultiplyProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*multiply assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkMultiplyAssign;
		}
		break;                                 /*multiply*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkMultiply;
		}
		break;
	}
}

void __fastcall TSynJavaSyn::NotSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*not equal*/
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkNotEqual;
		}
		break;                                 /*logical complement*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkLogComplement;
		}
		break;
	}
}

void __fastcall TSynJavaSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynJavaSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'.':
			case L'l':
			case L'L':
			case L'x':
			case L'X':
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:                    //Fiala
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
				goto label1;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label1:;
}

void __fastcall TSynJavaSyn::OrSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*inclusive or assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkIncOrAssign;
		}
		break;                               /*conditional or*/
		case L'|':
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkCondOr;
		}
		break;                                 /*inclusive or*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkIncOr;
		}
		break;
	}
}

void __fastcall TSynJavaSyn::PlusProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*add assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkAddAssign;
		}
		break;                               /*increment*/
		case L'+':
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkIncrement;
		}
		break;                                 /*add*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkAdd;
		}
		break;
	}
}

void __fastcall TSynJavaSyn::PointProc()
{
	++Run;                            /*point*/
	if(CharInSet(fLine[Run], Synhighlighterjava__3))
	{
		NumberProc();
		return;
	}
	FTokenID = tkSymbol;
	FExtTokenID = xtkPoint;
}

void __fastcall TSynJavaSyn::PoundProc()
{
	++Run;
	FTokenID = tkInvalid;
}

void __fastcall TSynJavaSyn::QuestionProc()
{
	FTokenID = tkSymbol;                /*question mark - conditional*/
	FExtTokenID = xtkQuestion;
	++Run;
}

void __fastcall TSynJavaSyn::RemainderSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*remainder assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkRemainderAssign;
		}
		break;                                 /*remainder*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkRemainder;
		}
		break;
	}
}

void __fastcall TSynJavaSyn::RoundCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkRoundClose;
	--FRoundCount;
}

void __fastcall TSynJavaSyn::RoundOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkRoundOpen;
	++FRoundCount;
}

//++ CodeFolding

void __fastcall TSynJavaSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
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
		if(Synhighlighterjava__4.Contains((TRangeState)(NativeInt)GetLineRange(LinesToScan, (int) Line)))
		{
			if(!(Synhighlighterjava__5.Contains((TRangeState)(NativeInt)GetLineRange(LinesToScan, (int) (Line - 1)))))
				FoldRanges->StartFoldRange((int) (Line + 1), 2);
			else
				FoldRanges->NoFoldInfo((int) (Line + 1));
			continue;
		}
		else
		{
			if(Synhighlighterjava__6.Contains((TRangeState)(NativeInt)GetLineRange(LinesToScan, (int) (Line - 1))))
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

void __fastcall TSynJavaSyn::SemiColonProc()
{
	++Run;                            /*semicolon*/
	FTokenID = tkSymbol;
	FExtTokenID = xtkSemiColon;
}

void __fastcall TSynJavaSyn::SlashProc()
{
	switch(fLine[Run + 1])
	{
		case L'/':                               /*c++ style comments*/
		{
			Run += 2;
			FTokenID = tkComment;
			while(!IsLineEnd(Run))
			{
				++Run;
			}
		}
		break;
		case L'*':
		{
			if((fLine[Run + 2] == L'*') && (fLine[Run + 3] != L'/'))     /*documentation comment*/
			{
				FRange = rsDocument;
				FTokenID = tkDocument;
				++Run;
			}
			else
                           /*c style comment*/
			{
				FRange = rsComment;
				FTokenID = tkComment;
			}
			Run += 2;
			while(!IsLineEnd(Run))
				switch(fLine[Run])
				{
					case L'*':
					if(fLine[Run + 1] == L'/')
					{
						Run += 2;
						FRange = rsUnKnown;
						goto label2;
					}
					else
					++Run;
					break;
					default:
					++Run;
					break;
				}
			label2:;
		}
		break;                               /*division assign*/
		case L'=':
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkDivideAssign;
		}
		break;                                 /*division*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkDivide;
		}
		break;
	}
}

void __fastcall TSynJavaSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynJavaSyn::SquareCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSquareClose;
	--FSquareCount;
}

void __fastcall TSynJavaSyn::SquareOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
	FExtTokenID = xtkSquareOpen;
	++FSquareCount;
}

void __fastcall TSynJavaSyn::StringProc()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x22') && (fLine[Run + 2] == L'\x22'))
		Run += 2;
	do
	{
		if(IsLineEnd(Run))
			break;
		switch(fLine[Run])
		{
			case L'\x5c':
			++Run;
			break;  // Backslash, if we have an escaped charcter it can be skipped
			default:
			  ;
			break;
		}
		if(!IsLineEnd(Run))
			++Run; //Add check here to prevent overrun from backslash being last char
	}
	while(!(fLine[Run] == L'\x22'));
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynJavaSyn::TildeProc()
{
	++Run;                            /*bitwise complement*/
	FTokenID = tkSymbol;
	FExtTokenID = xtkBitComplement;
}

void __fastcall TSynJavaSyn::XOrSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*xor assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
			FExtTokenID = xtkXorAssign;
		}
		break;                                 /*xor*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
			FExtTokenID = xtkXor;
		}
		break;
	}
}

void __fastcall TSynJavaSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynJavaSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsComment:
		CommentProc();
		break;
		case rsDocument:
		CommentProc();
		break;
		default:
		if(IsCharAlphaNumeric(fLine[Run]) && !CharInSet(fLine[Run], Synhighlighterjava__7)) //Fiala
			IdentProc();
		else
		{
			FRange = rsUnKnown;
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
				case L'=':
				EqualProc();
				break;
				case L'>':
				GreaterProc();
				break;
//        'A'..'Z', 'a'..'z', '_', '$', 'L'..'Ö', 'Ø'..'ö', 'ø'..'ÿ': IdentProc;  //Fiala
				case L'_':
				IdentProc();
				break;                                                         //Fiala
				case L'\x0a':
				LFProc();
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
				case L'#':
				PoundProc();
				break;
				case L'?':
				QuestionProc();
				break;
				case L'%':
				RemainderSymbolProc();
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

TSynHighlighterAttributes* __fastcall TSynJavaSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynJavaSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynJavaSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

void __fastcall TSynJavaSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynJavaSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

TtkTokenKind __fastcall TSynJavaSyn::GetTokenID()
{
	TtkTokenKind result = tkSymbol;
	result = FTokenID;
	return result;
}

TxtkTokenKind __fastcall TSynJavaSyn::GetExtTokenID()
{
	TxtkTokenKind result = xtkAdd;
	result = FExtTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynJavaSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
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
		case tkInvalid:
		result = fInvalidAttri;
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
		case tkUnknown:
		result = fInvalidAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynJavaSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

bool __fastcall TSynJavaSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterJava;
	return result;
}

bool __fastcall TSynJavaSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	result = IsCharAlphaNumeric(AChar) || CharInSet(AChar, Synhighlighterjava__8);       //Fiala
/*
  case AChar of
    '_', '$', '0'..'9', 'a'..'z', 'A'..'Z', 'L'..'Ö', 'Ø'..'ö', 'ø'..'ÿ':
      Result := True;
    else
      Result := False;
  end;
*/
	return result;
}

/*#static*/
String __fastcall TSynJavaSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangJava;
	return result;
}

String __fastcall TSynJavaSyn::GetSampleSource()
{
	String result;
	result = L"/* Java syntax highlighting */\x0d\x0a"
	           L"import java.util.*;\x0d\x0a"
	           L"\x0d\x0a"
	           L"/** Example class */\x0d\x0a"
	           L"public class Sample {\x0d\x0a"
	           L"  public static void main(String[] args) {\x0d\x0a"
	           L"    int i = 0;\x0d\x0a"
	           L"    for(i = 0; i < 10; i++)\x0d\x0a"
	           L"      System.out.println(\"Hello world\");\x0d\x0a"
	           L"  }\x0d\x0a"
	           L"}";
	return result;
}

/*#static*/
String __fastcall TSynJavaSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangJava;
	return result;
}
static bool SynHighlighterJava_Initialized = false;

void SynHighlighterJava_initialization()
{
	if(SynHighlighterJava_Initialized)
		return;
	
	SynHighlighterJava_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynJavaSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterJava

