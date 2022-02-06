
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterVBScript.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"
#include "SynEditDelphiInstances.hpp"
#include "d2c_syshelper.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace Synhighlighterhashentries;
using namespace System;
using namespace System::Classes;
using namespace System::Regularexpressions;
using namespace System::Sysutils;
using namespace System::Uitypes;

namespace Synhighlightervbscript
{
#define SynHighlighterVBScript__0 (TSysCharSet() <<  \
										97 << 98 << 99 << 100 << 101 << 102 <<  \
										103 << 104 << 105 << 106 << 107 << 108 <<  \
										109 << 110 << 111 << 112 << 113 << 114 <<  \
										115 << 116 << 117 << 118 << 119 << 120 <<  \
										121 << 122 <<  \
										65 << 66 << 67 << 68 << 69 << 70 <<  \
										71 << 72 << 73 << 74 << 75 << 76 <<  \
										77 << 78 << 79 << 80 << 81 << 82 <<  \
										83 << 84 << 85 << 86 << 87 << 88 <<  \
										89 << 90 << L'_' << L'-')
#define SynHighlighterVBScript__1 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define SynHighlighterVBScript__2 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVBScript__3 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterVBScript__4 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterVBScript__5 (TRegExOptions() << roIgnoreCase)
#define SynHighlighterVBScript__6 (TRegExOptions() << roIgnoreCase)
#define SynHighlighterVBScript__7 (TSysCharSet() << L'=' << L'>')
#define SynHighlighterVBScript__8 (TSysCharSet() << L'E' << L'e')
#define SynHighlighterVBScript__9 (TSysCharSet() << L'M' << L'm')


const String Keywords = L"and, as, boolean, byref, byte, byval, call, case, class, const, currency,"
	           L"default, description , dim, do, double, each, else, elseif, empty, end,"
	           L"endif, enum, eqv, error, event, exit, explicit, false, firstindex , for,"
	           L"function, get, global , goto, helpcontext , helpfile , if, ignorecase, imp,"
	           L"implements, in, integer, is, length , let, like, long, loop, lset, me, mod,"
	           L"new, next, not, nothing, null, number , on, option, optional, or, paramarray,"
	           L"pattern, preserve, private, property, public, raiseevent, redim, resume,"
	           L"rset, select, set, shared, single, source , static, sub, submatches, then,"
	           L"to, true, type, typeof, until, value, variant, wend, while, with, xor";
const String FunctionConsts = L"vbabort, vbabortretryignore, vbapplicationmodal, vbarray, vbbinarycompare,"
	           L"vbblack, vbblue, vbboolean, vbbyte, vbcancel, vbcr, vbcritical, vbcrlf,"
	           L"vbcurrency, vbcyan, vbdatabasecompare, vbdataobject, vbdate, vbdecimal,"
	           L"vbdefaultbutton1, vbdefaultbutton2, vbdefaultbutton3, vbdefaultbutton4,"
	           L"vbdouble, vbempty, vberror, vbexclamation, vbfalse, vbfirstfourdays,"
	           L"vbfirstfullweek, vbfirstjan1, vbformfeed, vbfriday, vbgeneraldate, vbgreen,"
	           L"vbignore, vbinformation, vbinteger, vblf, vblong, vblongdate, vblongtime,"
	           L"vbmagenta, vbmonday, vbmsgboxhelpbutton, vbmsgboxright, vbmsgboxrtlreading,"
	           L"vbmsgboxsetforeground, vbnewline, vbno, vbnull, vbnullchar, vbnullstring,"
	           L"vbobject, vbobjecterror, vbok, vbokcancel, vbokonly, vbquestion, vbred,"
	           L"vbretry, vbretrycancel, vbsaturday, vbshortdate, vbshorttime, vbsingle,"
	           L"vbstring, vbsunday, vbsystemmodal, vbtab, vbtextcompare, vbthursday, vbtrue,"
	           L"vbtuesday, vbusedefault, vbusesystem, vbusesystemdayofweek, vbvariant,"
	           L"vbverticaltab, vbwednesday, vbwhite, vbyellow, vbyes, vbyesno, vbyesnocancel";
const String Functions = L"abs, anchor, array, asc, ascb, ascw, atn, cbool, cbyte, ccur, cdate, cdbl,"
	           L"chr, chrb, chrw, cint, class_initialize, class_terminate, clear, clng, cos,"
	           L"createcomponent, createobject, csng, cstr, date, dateadd,"
	           L"datediff, datepart, dateserial, datevalue, day, debug, dictionary, document,"
	           L"element, erase, err, escape, eval, execute, executeglobal, exp,"
	           L"filesystemobject, filter, fix, form, formatcurrency, formatdatetime,"
	           L"formatnumber, formatpercent, getlocale, getobject, getref,"
	           L"getresource, hex, history, hour, inputbox, instr, instrb, instrrev, int,"
	           L"isarray, isdate, isempty, isnull, isnumeric, isobject, join, lbound, lcase,"
	           L"left, leftb, len, lenb, link, loadpicture, location, log, ltrim, mid, midb,"
	           L"minute, month, monthname, msgbox, navigator, now, oct, raise, randomize,"
	           L"regexp, rem, replace, rgb, right, rightb, rnd, round, rtrim, scriptengine,"
	           L"scriptenginebuildversion, scriptenginemajorversion, scriptengineminorversion,"
	           L"second, setlocale, sgn, sin, space, split, sqr, step, stop, strcomp, string,"
	           L"strreverse, tan, test, textstream, time, timer, timeserial, timevalue, trim,"
	           L"typename, ubound, ucase, unescape, vartype, weekday, weekdayname, window,"
	           L"write, writeline, year";


/*$Q-*/

unsigned int __fastcall TSynVBScriptSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(CharInSet((*Str), SynHighlighterVBScript__0))
	{
		if((*Str) != L'-')
			switch((*Str))
			{
				case L'_':
				result += 27;
				break;
				case L'-':
				result += 28;
				break;
				default:
				result += int(UpperCase(String((*Str)))[1]) - 64;
				break;
			}
		++Str;
	}
	while(CharInSet((*Str), SynHighlighterVBScript__1))
	{
		result += int((*Str)) - int(L'0');
		++Str;
	}
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

void __fastcall TSynVBScriptSyn::DoAddKeyword(String AKeyword, int AKind)
{
	int HashValue = 0;
	HashValue = (int) HashKey(ustr2pwchar(AKeyword));
	fKeywords->Items[HashValue] = new TSynHashEntry(AKeyword, AKind);
}

TtkTokenKind __fastcall TSynVBScriptSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkSymbol;
	TSynHashEntry* Entry = nullptr;
	fToIdent = Maybe;
	Entry = fKeywords->Items[HashKey(Maybe)];
	while(ASSIGNED(Entry))
	{
		if(Entry->KeywordLen > fStringLen)
			break;
		else
		{
			if(Entry->KeywordLen == fStringLen)
			{
				if(IsCurrentToken(Entry->Keyword))
				{
					result = ((TtkTokenKind) Entry->Kind);
					return result;
				}
			}
		}
		Entry = Entry->Next;
	}
	result = tkIdentifier;
	return result;
}

__fastcall TSynVBScriptSyn::TSynVBScriptSyn(TComponent* AOwner)
 : inherited(AOwner),
			FTokenID(tkSymbol),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fFunctionAttri(nullptr),
			fCOnstAttri(nullptr),
			fKeywords(nullptr)
{
	FCaseSensitive = false;
	fKeywords = new TSynHashEntryList();
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = SynHighlighterVBScript__2;
	addAttribute(fCommentAttri);
	fCOnstAttri = new TSynHighlighterAttributes(SYNS_AttrConst, SYNS_AttrConst);
	fCOnstAttri->Style = SynHighlighterVBScript__3;
	addAttribute(fCOnstAttri);
	fFunctionAttri = new TSynHighlighterAttributes(SYNS_AttrSystem, SYNS_FriendlyAttrSystem);
	addAttribute(fFunctionAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = SynHighlighterVBScript__4;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterVBScript;
	EnumerateKeywords(int(tkKey), Keywords, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkConst), FunctionConsts, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkFunction), Functions, IsIdentChar, DoAddKeyword);

//++ CodeFolding
	RE_BlockBegin = TRegEx(L"\\b^(sub |function |private sub |private function |class )\\b", SynHighlighterVBScript__5);
	RE_BlockEnd = TRegEx(L"\\b^(end sub|end function|end class)\\b", SynHighlighterVBScript__6);
//-- CodeFolding
}

__fastcall TSynVBScriptSyn::~TSynVBScriptSyn()
{
	delete fKeywords;
	//# inherited::Destroy();
}


//++ CodeFolding
const int FT_Standard = 1;  // begin end, class end, record end
const int FT_Comment = 11;
const int FT_CodeDeclaration = 16;
const int FT_CodeDeclarationWithBody = 17;
const int FT_Implementation = 18;

void __fastcall TSynVBScriptSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	String CurLine;
	__int64 Line = 0;
	bool OK = false;

	auto BlockDelimiter = [&](int Line) -> bool 
	{
		bool result = false;
		int Index = 0;
		TMatchCollection mcb = {};
		TMatchCollection mce = {};
		TMatch Match = {};
		result = false;
		mcb = RE_BlockBegin.Matches(CurLine);
		if(mcb.Count > 0)
      // Char must have proper highlighting (ignore stuff inside comments...)
		{
			Index = mcb.Item[0].Index;
			if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Index) != fCommentAttri)
			{
				OK = false;
        // And ignore lines with both opening and closing chars in them
				for(int iFor0 = 0; iFor0 < RE_BlockEnd.Matches(CurLine).Count; iFor0++)
				{
					TMatch	Match = RE_BlockEnd.Matches(CurLine).Item[iFor0];
					if(Match.Index > Index)
					{
						OK = true;
						break;
					}
				}
				if(!OK)
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
		String s;
		result = false;
		s = TrimLeft(CurLine);
		if(UpperCase(s.SubString(1, 7)) == L"'REGION")
		{
			FoldRanges->StartFoldRange(Line + 1, FoldRegionType);
			result = true;
		}
		else
		{
			if(UpperCase(s.SubString(1, 10)) == L"'ENDREGION")
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
    // Deal first with Multiline statements
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

    // Find begin or end  (Fold Type 1)
		if(!BlockDelimiter((int) Line))
			FoldRanges->NoFoldInfo((int) (Line + 1));
	} //for Line
}
/*
   Provide folding for procedures and functions included nested ones.
*/

void __fastcall TSynVBScriptSyn::AdjustFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan)
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
									goto label0;
								}
								else

                  // class or record declaration follows, so
								{
									FoldRanges->Ranges->Delete(i);
									goto label1;
								}
							}
							else
							Assert(false, L"TSynVBSSyn.AdjustFoldRanges");
						}
						break;
						default:
						if(FoldRange.ToLine <= SkipTo)
							continue;
						else

              // Otherwise delete
              // eg. function definitions within a class definition
						{
							FoldRanges->Ranges->Delete(i);
							break;
						}
						break;
					}
				}
				label0:;
				label1:;
			}
		}
	}
	if(ImplementationIndex >= 0)
    // Looks better without it
    //FoldRanges.Ranges.List[ImplementationIndex].ToLine := LinesToScan.Count;
		FoldRanges->Ranges->Delete(ImplementationIndex);
}
//-- CodeFolding

void __fastcall TSynVBScriptSyn::ApostropheProc()
{
	FTokenID = tkComment;
	do
	{
		++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynVBScriptSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynVBScriptSyn::DateProc()
{
	FTokenID = tkString;
	do
	{
		if(IsLineEnd(Run))
			break;
		++Run;
	}
	while(!(fLine[Run] == L'#'));
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynVBScriptSyn::GreaterProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynVBScriptSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynVBScriptSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynVBScriptSyn::LowerProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], SynHighlighterVBScript__7))
		++Run;
}

void __fastcall TSynVBScriptSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynVBScriptSyn::NumberProc()
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
		++Run;
}

void __fastcall TSynVBScriptSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynVBScriptSyn::StringProc()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x22') && (fLine[Run + 2] == L'\x22'))
		Run += 2;
	do
	{
		if(IsLineEnd(Run))
			break;
		++Run;
	}
	while(!(fLine[Run] == L'\x22'));
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynVBScriptSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynVBScriptSyn::UnknownProc()
{
	++Run;
	FTokenID = tkIdentifier;
}

void __fastcall TSynVBScriptSyn::Next()
{
	fTokenPos = Run;
	switch(fLine[Run])
	{
		case L'\x27':
		ApostropheProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		case L'#':
		DateProc();
		break;
		case L'>':
		GreaterProc();
		break;
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81:
		case 83: case 84: case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113:
		case 115: case 116: case 117: case 118: case 119: case 120: case 121: case 122:
		case L'_':
		IdentProc();
		break;
		case L'R':
		case L'r':
		RemProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'<':
		LowerProc();
		break;
		case L'\x00':
		NullProc();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		NumberProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'\x22':
		StringProc();
		break;
		case L'&':
		case L'{':
		case L'}':
		case L':':
		case L',':
		case L'=':
		case L'^':
		case L'-':
		case L'+':
		case L'.':
		case L'(':
		case L')':
		case L';':
		case L'/':
		case L'*':
		SymbolProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynVBScriptSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynVBScriptSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynVBScriptSyn::GetTokenID()
{
	TtkTokenKind result = tkSymbol;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynVBScriptSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkConst:
		result = fCOnstAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkFunction:
		result = fFunctionAttri;
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
		result = fIdentifierAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynVBScriptSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

bool __fastcall TSynVBScriptSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterVBScript;
	return result;
}

/*#static*/
String __fastcall TSynVBScriptSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangVBSScript;
	return result;
}

String __fastcall TSynVBScriptSyn::GetSampleSource()
{
	String result;
	result = L"' Syntax highlighting\x0d\x0a"
	           L"function printNumber()\x0d\x0a"
	           L"  number = 12345\x0d\x0a"
	           L"  document.write(\"The number is \" + number)\x0d\x0a"
	           L"  for i = 0 to 10\x0d\x0a"
	           L"    x = x + 1.0\x0d\x0a"
	           L"  next\x0d\x0a"
	           L"end function";
	return result;
}

/*#static*/
String __fastcall TSynVBScriptSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangVBSScript;
	return result;
}

void __fastcall TSynVBScriptSyn::RemProc()
{
	if(CharInSet(fLine[Run + 1], SynHighlighterVBScript__8) && CharInSet(fLine[Run + 2], SynHighlighterVBScript__9) && (fLine[Run + 3] <= L'\x20'))
		ApostropheProc();
	else
	{
		FTokenID = tkIdentifier;
		IdentProc();
	}
}
static bool SynHighlighterVBScript_Initialized = false;

void SynHighlighterVBScript_initialization()
{
	if(SynHighlighterVBScript_Initialized)
		return;
	
	SynHighlighterVBScript_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynVBScriptSyn));
}
class SynHighlighterVBScript_unit
{
public:
	SynHighlighterVBScript_unit()
	{
		SynHighlighterVBScript_initialization();
	}
};

SynHighlighterVBScript_unit _SynHighlighterVBScript_unit;

}  // namespace SynHighlighterVBScript

