
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterCobol.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace Synhighlighterhashentries;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlightercobol
{
#define Synhighlightercobol__0 (TSysCharSet() <<  \
										1 << 2 << 3 << 4 << 5 << 6 <<  \
										7 << 8 << 9 << 10 << 11 << 12 <<  \
										13 << 14 << 15 << 16 << 17 << 18 <<  \
										19 << 20 << 21 << 22 << 23 << 24 <<  \
										25 << 26 << 27 << 28 << 29 << 30 <<  \
										31 << 32)
#define Synhighlightercobol__1 (System::Set<TRangeState, TRangeState::rsUnKnown, TRangeState::rsApostStringMayBe>() << rsQuoteStringMayBe << rsApostStringMayBe)
#define Synhighlightercobol__2 (TSysCharSet() <<  \
          48 << 49 << 50 << 51 << 52 << 53 <<  \
          54 << 55 << 56 << 57 << 'e' << 'E')
#define Synhighlightercobol__3 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57 << 'e' << 'E')
#define Synhighlightercobol__4 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57 << '.')
#define Synhighlightercobol__5 (TSysCharSet() << 'e' << 'E')
#define Synhighlightercobol__6 (System::Set<TRangeState, TRangeState::rsUnKnown, TRangeState::rsApostStringMayBe>() << rsQuoteString << rsApostString)
#define Synhighlightercobol__7 (System::Set<TRangeState, TRangeState::rsUnKnown, TRangeState::rsApostStringMayBe>() << rsQuoteString << rsApostString)
#define Synhighlightercobol__8 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlightercobol__9 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightercobol__10 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightercobol__11 (TSysCharSet() << 'x' << 'g' << 'X' << 'G')
#define Synhighlightercobol__12 (TSysCharSet() << '\"' << '\'')


const String BooleanWords = L"false, true";
const String Keywords = L"accept, access, acquire, add, address, advancing, after, all, allowing, "
	           L"alphabet, alphabetic, alphabetic-lower, alphabetic-upper, alphanumeric, "
	           L"alphanumeric-edited, also, alter, alternate, and, any, apply, are, "
	           L"area, areas, area-value, arithmetic, ascending, assign, at, author, "
	           L"auto, automatic, auto-skip, background-color, background-colour, "
	           L"backward, b-and, beep, before, beginning, bell, b-exor, binary, bit, "
	           L"bits, blank, b-less, blink, block, b-not, boolean, b-or, bottom, by, "
	           L"call, cancel, cd, cf, ch, chain, chaining, changed, character, "
	           L"characters, class, clock-units, close, cobol, code, code-set, col, "
	           L"collating, color, column, comma, command-line, commit, commitment, "
	           L"common, communication, comp, comp-0, comp-1, comp-2, comp-3, comp-4, "
	           L"comp-5, comp-6, comp-7, comp-8, comp-9, computational, computational-0, "
	           L"computational-1, computational-2, computational-3, computational-4, "
	           L"computational-5, computational-6, computational-7, computational-8, "
	           L"computational-9, computational-x, compute, comp-x, com-reg, "
	           L"configuration, connect, console, contained, contains, content, "
	           L"continue, control-area, controls, converting, corr, corresponding, "
	           L"count, crt, crt-under, currency, current, cursor, cycle, data, date, "
	           L"date-compiled, date-written, day, day-of-week, db, "
	           L"db-access-control-key, dbcs, db-data-name, db-exception, "
	           L"db-format-name, db-record-name, db-set-name, db-status, de, "
	           L"debug-contents, debugging, debug-item, debug-line, debug-name, "
	           L"debug-sub-1, debug-sub-2, debug-sub-3, decimal-point, declaratives, "
	           L"default, delimited, delimiter, depending, descending, destination, "
	           L"detail, disable, disconnect, disk, display, display-1, display-2, "
	           L"display-3, display-4, display-5, display-6, display-7, display-8, "
	           L"display-9, divide, division, down, drop, duplicate, duplicates, "
	           L"dynamic, egcs, egi, else, emi, empty, empty-check, enable, end, "
	           L"end-accept, end-add, end-call, end-compute, end-delete, end-disable, "
	           L"end-divide, end-enable, end-evaluate, end-if, ending, end-multiply, "
	           L"end-of-page, end-perform, end-read, end-receive, end-return, "
	           L"end-rewrite, end-search, end-send, end-start, end-string, end-subtract, "
	           L"end-transceive, end-unstring, end-write, enter, entry, environment, "
	           L"eop, equal, equals, erase, error, escape, esi, evaluate, every, exact, "
	           L"exceeds, exception, excess-3, exclusive, exec, execute, exhibit, exit, "
	           L"extend, external, externally-described-key, fd, fetch, file, "
	           L"file-control, file-id, filler, final, find, finish, first, fixed, "
	           L"footing, for, foreground-color, foreground-colour, form, format, free, "
	           L"from, full, function, generate, get, giving, global, go, goback, "
	           L"greater, group, heading, highlight, id, identification, if, in, index, "
	           L"index-1, index-2, index-3, index-4, index-5, index-6, index-7, index-8, "
	           L"index-9, indexed, indic, indicate, indicator, indicators, initial, "
	           L"initialize, initiate, input, input-output, inspect, installation, into, "
	           L"invalid, i-o, i-o-control, is, japanese, just, justified, kanji, keep, "
	           L"kept, key, keyboard, last, ld, leading, left, left-justify, length, "
	           L"length-check, less, like, limit, limits, linage, linage-counter, line, "
	           L"line-counter, lines, linkage, locally, lock, manual, member, memory, "
	           L"merge, message, mode, modified, modify, modules, more-labels, move, "
	           L"multiple, multiply, name, native, negative, next, no, no-echo, none, "
	           L"normal, not, number, numeric, numeric-edited, object-computer, occurs, "
	           L"of, off, omitted, on, only, open, optional, or, order, organization, "
	           L"other, output, overflow, owner, packed-decimal, padding, page, "
	           L"page-counter, palette, paragraph, password, perform, pf, ph, pic, "
	           L"picture, plus, pointer, position, positive, present, previous, printer, "
	           L"printer-1, printing, print-switch, prior, procedure, procedures, "
	           L"proceed, process, processing, program, program-id, prompt, protected, "
	           L"purge, queue, random, range, rd, read, realm, receive, reconnect, "
	           L"record, recording, record-name, records, redefines, reel, reference, "
	           L"references, relation, relative, release, remainder, removal, renames, "
	           L"repeated, replacing, report, reporting, reports, required, rerun, "
	           L"reserve, retaining, retrieval, return, return-code, reversed, "
	           L"reverse-video, rewind, rewrite, rf, rh, right, right-justify, rollback, "
	           L"rolling, rounded, run, same, screen, sd, search, section, secure, "
	           L"security, segment, segment-limit, select, send, sentence, separate, "
	           L"sequence, sequential, session-id, set, shared, shift-in, shift-out, "
	           L"sign, size, sort, sort-control, sort-core-size, sort-file-size, "
	           L"sort-merge, sort-message, sort-mode-size, sort-return, source, "
	           L"source-computer, space-fill, special-names, standard, standard-1, "
	           L"standard-2, standard-3, standard-4, start, starting, status, stop, "
	           L"store, string, subfile, subprogram, sub-queue-1, sub-queue-2, "
	           L"sub-queue-3, sub-schema, subtract, sum, suppress, switch, switch-1, "
	           L"switch-2, switch-3, switch-4, switch-5, switch-6, switch-7, switch-8, "
	           L"symbolic, sync, synchronized, table, tally, tallying, tape, tenant, "
	           L"terminal, terminate, test, text, than, then, through, thru, time, "
	           L"timeout, times, to, top, trailing, trailing-sign, transaction, "
	           L"transceive, type, underline, unequal, unit, unlock, unstring, until, "
	           L"up, update, upon, usage, usage-mode, user, using, valid, validate, "
	           L"value, values, variable, varying, wait, when, when-compiled, with, "
	           L"within, words, working-storage, write, write-only, zero-fill";
const String PreprocessorWords = L"basis, cbl, control, copy, delete, eject, insert, ready, reload, "
	           L"replace, reset, service, skip1, skip2, skip3, title, trace, use";
const String StringWords = L"high-value, high-values, low-value, low-values, null, nulls, quote, "
	           L"quotes, space, spaces, zero, zeroes, zeros";

  // Ambigious means that a simple string comparision is not enough
const String AmbigiousWords = L"label";
const WideChar StringChars[6/*# TRangeState*/] = {L'\x00', L'\"', L'\'', L'=', L'\"', L'\''};

void __fastcall TSynCobolSyn::DoAddKeyword(String AKeyword, int AKind)
{
	int HashValue = 0;
	HashValue = HashKey(ustr2pwchar(AKeyword));
	fKeywords->Items[HashValue] = new TSynHashEntry(AKeyword, AKind);
}

int __fastcall TSynCobolSyn::HashKey(PWideChar Str)
{
	int result = 0;
	int fRun = 0;

	auto GetOrd = [&]() -> int 
	{
		int result = 0;
		switch((*Str))
		{
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			result = 1 + int((*Str)) - int(L'a');
			break;
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			result = 1 + int((*Str)) - int(L'A');
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			result = 28 + int((*Str)) - int(L'0');
			break;
			case L'-':
			result = 27;
			break;
			default:
			result = 0;
			break;
		}
		return result;
	};
	fRun = Run;
	result = 0;
	while(IsIdentChar((*Str)) && (fRun <= fCodeEndPos))
	{
		result = (7 * result + GetOrd()) & 0xFFFFFF;
		++Str;
		++fRun;
	}
	result = result & 0xFF; // 255
	fStringLen = Str - fToIdent;
	return result;
}

TtkTokenKind __fastcall TSynCobolSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	TSynHashEntry* Entry = nullptr;
	int i = 0;
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
					if(result == tkUnknown) // handling of "ambigious" words 
					{
						if(IsCurrentToken(L"label"))
						{
							i = Run + wcslen(L"label");
							while(fLine[i] == L' ')
								++i;
							if((AnsiStrLComp(&fLine[i], const_cast<PWideChar>(L"record"), (unsigned int) wcslen(L"record")) == 0) && (i + wcslen(L"record") - 1 <= fCodeEndPos))
								result = tkKey;
							else
								result = tkPreprocessor;
						}
						else
						result = tkIdentifier;
					}
					return result;
				}
			}
		}
		Entry = Entry->Next;
	}
	result = tkIdentifier;
	return result;
}

void __fastcall TSynCobolSyn::SpaceProc()
{
	FTokenID = tkSpace;
	do
	{
		++Run;
	}
	while(!!CharInSet(fLine[Run], Synhighlightercobol__0));
}

void __fastcall TSynCobolSyn::FirstCharsProc()
{
	int i = 0;
	if(IsLineEnd(Run))
		NextProcedure();
	else
	{
		if(Run < fCodeStartPos - 1)
		{
			FTokenID = tkSequence;
			do
			{
				++Run;
			}
			while(!((Run == fCodeStartPos - 1) || IsLineEnd(Run)));
		}
		else
		{
			FTokenID = tkIndicator;
			switch(fLine[Run])
			{
				case L'*':
				case L'/':
				case L'D':
				case L'd':
				fIndicator = fLine[Run];
				break;
				case L'-':
				if(Synhighlightercobol__1.Contains(FRange))
				{
					i = Run + 1;
					while(fLine[i] == L' ')
						++i;
					if((AnsiStrLComp(&fLine[i], ustr2pwchar(StringOfChar(StringChars[FRange], 2)), 2) != 0) || (i + 1 > fCodeEndPos))
						FRange = rsUnKnown;
				}
				break;
				default:
				  ;
				break;
			}
			++Run;
		}
	}
}

void __fastcall TSynCobolSyn::LastCharsProc()
{
	if(IsLineEnd(Run))
		NextProcedure();
	else
	{
		FTokenID = tkTagArea;
		do
		{
			++Run;
		}
		while(!IsLineEnd(Run));
	}
}

void __fastcall TSynCobolSyn::CommentProc()
{
	fIndicator = L'\x00';
	if(IsLineEnd(Run))
		NextProcedure();
	else
	{
		FTokenID = tkComment;
		do
		{
			++Run;
		}
		while(!(IsLineEnd(Run) || (Run > fCodeEndPos)));
	}
}

void __fastcall TSynCobolSyn::DebugProc()
{
	fIndicator = L'\x00';
	if(IsLineEnd(Run))
		NextProcedure();
	else
	{
		FTokenID = tkDebugLines;
		do
		{
			++Run;
		}
		while(!(IsLineEnd(Run) || (Run > fCodeEndPos)));
	}
}

void __fastcall TSynCobolSyn::PointProc()
{
	if((Run < fCodeEndPos) && CharInSet(fLine[Run + 1], Synhighlightercobol__2))
		NumberProc();
	else
		UnknownProc();
}

void __fastcall TSynCobolSyn::NumberProc()
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
	bool fFloat = false;
	FTokenID = tkNumber;
	++Run;
	fFloat = false;
	while(IsNumberChar() && (Run <= fCodeEndPos))
	{
		switch(fLine[Run])
		{
			case L'.':
			if(!CharInSet(fLine[Run + 1], Synhighlightercobol__3))
				goto label0;
			else
				fFloat = true;
			break;
			case L'e':
			case L'E':
			if(!CharInSet(fLine[Run - 1], Synhighlightercobol__4))
				goto label1;
			else
				fFloat = true;
			break;
			case L'-':
			case L'+':
			{
				if(!fFloat || !CharInSet(fLine[Run - 1], Synhighlightercobol__5))
					goto label2;
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

void __fastcall TSynCobolSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynCobolSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynCobolSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynCobolSyn::StringOpenProc()
{
	switch(fLine[Run])
	{
		case L'\"':
		FRange = rsQuoteString;
		break;
		case L'\'':
		FRange = rsApostString;
		break;
		default:
		if(fLine[Run + 1] == L'=')
		{
			FRange = rsPseudoText;
			++Run;
		}
		else
		{
			UnknownProc();
			return;
		}
		break;
	}
	++Run;
	StringProc();
	FTokenID = tkString;
}

void __fastcall TSynCobolSyn::StringProc()
{
	FTokenID = tkString;
	if(Run <= fCodeEndPos)
	{
		do
		{
			if((fLine[Run] == StringChars[FRange]) && ((fLine[Run] != L'=') || ((Run > 0) && (fLine[Run - 1] == L'='))))
			{
				if((Run == fCodeEndPos) && (Synhighlightercobol__6.Contains(FRange)))
					Inc(FRange, 3);
				else
					FRange = rsUnKnown;
				++Run;
				break;
			}
			if(!IsLineEnd(Run))
				++Run;
		}
		while(!(IsLineEnd(Run) || (Run > fCodeEndPos)));
	}
}

void __fastcall TSynCobolSyn::StringEndProc()
{
	if(IsLineEnd(Run))
		NextProcedure();
	else
	{
		FTokenID = tkString;
		if((FRange != rsPseudoText) && (Run <= fCodeEndPos))
		{
			do
			{
				if(fLine[Run] == StringChars[FRange])
				{
					if(Synhighlightercobol__7.Contains(FRange))
						++Run;
					else
					{
						Run += 2;
						Dec(FRange, 3);
					}
					break;
				}
				++Run;
			}
			while(!(IsLineEnd(Run) || (Run > fCodeEndPos)));
		}
		StringProc();
	}
}

__fastcall TSynCobolSyn::TSynCobolSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkComment),
			fIndicator(L'\0'),
			fCodeStartPos(0),
			fCodeMediumPos(0),
			fCodeEndPos(0),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fAIdentifierAttri(nullptr),
			fPreprocessorAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fBooleanAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSequenceAttri(nullptr),
			fIndicatorAttri(nullptr),
			fTagAreaAttri(nullptr),
			fDebugLinesAttri(nullptr),
			fKeywords(nullptr)
{
	FCaseSensitive = false;
	fKeywords = new TSynHashEntryList();
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlightercobol__8;
	fCommentAttri->Foreground = (TColor) clGray;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fAIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrAreaAIdentifier, SYNS_FriendlyAttrAreaAIdentifier);
	fAIdentifierAttri->Foreground = (TColor) clTeal;
	fAIdentifierAttri->Style = Synhighlightercobol__9;
	addAttribute(fAIdentifierAttri);
	fPreprocessorAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	fPreprocessorAttri->Foreground = (TColor) clMaroon;
	addAttribute(fPreprocessorAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlightercobol__10;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = (TColor) clGreen;
	addAttribute(fNumberAttri);
	fBooleanAttri = new TSynHighlighterAttributes(SYNS_AttrBoolean, SYNS_FriendlyAttrBoolean);
	fBooleanAttri->Foreground = (TColor) clGreen;
	addAttribute(fBooleanAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = (TColor) clBlue;
	addAttribute(fStringAttri);
	fSequenceAttri = new TSynHighlighterAttributes(SYNS_AttrSequence, SYNS_FriendlyAttrSequence);
	fSequenceAttri->Foreground = (TColor) clDkGray;
	addAttribute(fSequenceAttri);
	fIndicatorAttri = new TSynHighlighterAttributes(SYNS_AttrIndicator, SYNS_FriendlyAttrIndicator);
	fIndicatorAttri->Foreground = (TColor) clRed;
	addAttribute(fIndicatorAttri);
	fTagAreaAttri = new TSynHighlighterAttributes(SYNS_AttrTagArea, SYNS_FriendlyAttrTagArea);
	fTagAreaAttri->Foreground = (TColor) clMaroon;
	addAttribute(fTagAreaAttri);
	fDebugLinesAttri = new TSynHighlighterAttributes(SYNS_AttrDebugLines, SYNS_FriendlyAttrDebugLines);
	fDebugLinesAttri->Foreground = (TColor) clDkGray;
	addAttribute(fDebugLinesAttri);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterCOBOL;
	fIndicator = L'\x00';
	fCodeStartPos = 7;
	fCodeMediumPos = 11;
	fCodeEndPos = 71;
	EnumerateKeywords(int(tkBoolean), BooleanWords, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkKey), Keywords, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkPreprocessor), PreprocessorWords, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkString), StringWords, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkUnknown), AmbigiousWords, IsIdentChar, DoAddKeyword);
}

__fastcall TSynCobolSyn::~TSynCobolSyn()
{
	delete fKeywords;
	//# inherited::Destroy();
}

void __fastcall TSynCobolSyn::IdentProc()
{
	if(CharInSet(fLine[Run], Synhighlightercobol__11) && (Run < fCodeEndPos) && CharInSet(fLine[Run + 1], Synhighlightercobol__12))
	{
		++Run;
		StringOpenProc();
	}
	else
	{
		FTokenID = IdentKind((fLine + Run));
		if((FTokenID == tkIdentifier) && (Run < fCodeMediumPos))
			FTokenID = tkAIdentifier;
		Run += fStringLen;
		while(IsIdentChar(fLine[Run]) && (Run <= fCodeEndPos))
			++Run;
	}
}

void __fastcall TSynCobolSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynCobolSyn::Next()
{
	fTokenPos = Run;
	if(fTokenPos < fCodeStartPos)
		FirstCharsProc();
	else
		switch(fIndicator)
		{
			case L'*':
			case L'/':
			CommentProc();
			break;
			case L'D':
			case L'd':
			DebugProc();
			break;
			default:
			if(fTokenPos > fCodeEndPos)
				LastCharsProc();
			else
				switch(FRange)
				{
					case rsQuoteString: case rsApostString: case rsPseudoText: case rsQuoteStringMayBe: case rsApostStringMayBe:
					StringEndProc();
					break;
					default:
					{
						FRange = rsUnKnown;
						NextProcedure();
					}
					break;
				}
			break;
		}
	inherited::Next();
}

void __fastcall TSynCobolSyn::NextProcedure()
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
		case L'\"':
		StringOpenProc();
		break;
		case L'\'':
		StringOpenProc();
		break;
		case L'=':
		StringOpenProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'.':
		PointProc();
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
		IdentProc();
		break;
		default:
		UnknownProc();
		break;
	}
}

TSynHighlighterAttributes* __fastcall TSynCobolSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynCobolSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynCobolSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynCobolSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkAIdentifier:
		result = fAIdentifierAttri;
		break;
		case tkPreprocessor:
		result = fPreprocessorAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkBoolean:
		result = fBooleanAttri;
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
		case tkSequence:
		result = fSequenceAttri;
		break;
		case tkIndicator:
		result = fIndicatorAttri;
		break;
		case tkTagArea:
		result = fTagAreaAttri;
		break;
		case tkDebugLines:
		result = fDebugLinesAttri;
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

int __fastcall TSynCobolSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

String __fastcall TSynCobolSyn::GetSampleSource()
{
	String result;
	result = L"000100* This is a sample file to be used to show all TSynCobolSyn's\x0d\x0a"
	           L"000200* features.\x0d\x0a"
	           L"000300* This isn't a valid COBOL program.\x0d\x0a"
	           L"000400\x0d\x0a"
	           L"000500* 1. Supported COBOL features.\x0d\x0a"
	           L"000600\x0d\x0a"
	           L"000700* 1.1  Sequence area.\x0d\x0a"
	           L"000800*    First six columns in COBOL are reserved for enumeration\x0d\x0a"
	           L"000900*    of source lines.\x0d\x0a"
	           L"001000* 1.2  Indicator area.\x0d\x0a"
	           L"001100*    7th column in COBOL is reserved for special markers like '*'\x0d\x0a"
	           L"001200*    or 'D'.\x0d\x0a"
	           L"001300* 1.3  Comment lines.\x0d\x0a"
	           L"001400*    Any line started from '*' in 7th column is a comment.\x0d\x0a"
	           L"001500*    No separate word highlighting will be done by the editor.\x0d\x0a"
	           L"001600* 1.4  Debug lines.\x0d\x0a"
	           L"001700D    Any line started from 'D' will be treated as containing debug\x0d\x0a"
	           L"001800D    commands. No separate word highlighting will be done\x0d\x0a"
	           L"001900D    by the editor.\x0d\x0a"
	           L"002000* 1.5  Tag area.\x0d\x0a"
	           L"002100*    Only columns from 8th till 72th can be used for COBOL        TAG_AREA\x0d\x0a"
	           L"002200*    program. Columns beyond the 72th one may be used by some     TAG_AREA\x0d\x0a"
	           L"002300*    COBOL compilers to tag the code in some internal way.        TAG_AREA\x0d\x0a"
	           L"002400* 1.6  Area A identifiers.\x0d\x0a"
	           L"002500*    In area A (from 8th column till\x0d\x0a"
	           L"002600*    11th one) you should type only sections'/paragraphs' names.\x0d\x0a"
	           L"002700*    For example \"SOME\" is a section name:\x0d\x0a"
	           L"002800 SOME SECTION.\x0d\x0a"
	           L"002900* 1.7  Preprocessor directives.\x0d\x0a"
	           L"003000*    For example \"COPY\" is a preprocessor directive:\x0d\x0a"
	           L"003100     COPY \"PRD-DATA.SEL\".\x0d\x0a"
	           L"003200* 1.8  Key words.\x0d\x0a"
	           L"003300*    For example \"ACCEPT\" and \"AT\" are COBOL key words:\x0d\x0a"
	           L"003400     ACCEPT WS-ENTRY AT 2030.\x0d\x0a"
	           L"003500* 1.9  Boolean constants.\x0d\x0a"
	           L"003600*    These are \"TRUE\" and \"FALSE\" constants. For example:\x0d\x0a"
	           L"003700     EVALUATE TRUE.\x0d\x0a"
	           L"003800* 1.10 Numbers.\x0d\x0a"
	           L"003900*    Here are the examples of numbers:\x0d\x0a"
	           L"004000 01  WSV-TEST-REC.\x0d\x0a"
	           L"004100     03  WSV-INT-T	       PIC 9(5) VALUE 12345.\x0d\x0a"
	           L"004200     03  WSV-PRICES              PIC 9(4)V99 COMP-3 VALUE 0000.33. 		\x0d\x0a"
	           L"004300     03  WSV-Z-PRICES            PIC Z(5)9.99- VALUE -2.12. 		\x0d\x0a"
	           L"004400     03  WSV-STORE-DATE          PIC 9(4)V99E99 VALUE 0001.33E02.\x0d\x0a"
	           L"004500* 1.11 Strings.\x0d\x0a"
	           L"004600*    The following types of strings are supported:\x0d\x0a"
	           L"004700*    1.11.1 Quoted strings.\x0d\x0a"
	           L"004800         MOVE \"The name of field is \"\"PRODUCT\"\"\" TO WS-ERR-MESS.\x0d\x0a"
	           L"004900         MOVE 'The name of field is ''PRODUCT''' TO WS-ERR-MESS.\x0d\x0a"
	           L"005000*    1.11.2 Pseudo-text.\x0d\x0a"
	           L"005100         COPY\x0d\x0a"
	           L"005200             REPLACING ==+00001== BY  +2\x0d\x0a"
	           L"005300                       == 1 ==    BY  -3.\x0d\x0a"
	           L"005400*    1.11.3 Figurative constants.\x0d\x0a"
	           L"005500*        For example \"SPACES\" is figurative constant:\x0d\x0a"
	           L"005600             DISPLAY SPACES UPON CRT.\x0d\x0a"
	           L"005700* 1.12 Continued lines.\x0d\x0a"
	           L"005800*    Only continued strings are supported. For example:\x0d\x0a"
	           L"005900         MOVE \"The name of figurative constant field is\x0d\x0a"
	           L"006000-\"SPACES\" TO WS-ERR-MESS.\x0d\x0a"
	           L"006100*    Or (a single quotation mark in 72th column):\x0d\x0a"
	           L"005900         MOVE \"The name of figurative constant field is  \"\"SPACES\"\x0d\x0a"
	           L"006000-\"\"\" TO WS-ERR-MESS.\x0d\x0a"
	           L"006100\x0d\x0a"
	           L"006200* 2. Unsupported COBOL features.\x0d\x0a"
	           L"006300\x0d\x0a"
	           L"006400* 2.1 Continued lines.\x0d\x0a"
	           L"006500*    Continuation of key words is not supported. For example,\x0d\x0a"
	           L"006600*    the following COBOL code is valid but TSynCobolSyn won't\x0d\x0a"
	           L"006700*    highlight \"VALUE\" keyword properly:\x0d\x0a"
	           L"006800     03  WSV-STORE-DATE                         PIC 9(4)V99E99 VAL\x0d\x0a"
	           L"006900-UE 0001.33E02.\x0d\x0a"
	           L"007000* 2.2 Identifiers started from digits.\x0d\x0a"
	           L"007100*    They are valid in COBOL but won't be highlighted properly\x0d\x0a"
	           L"007200*    by TSynCobolSyn. For example, \"000-main\" is a paragraph\x0d\x0a"
	           L"007300*    name and should be highlighted as Area A identifier:\x0d\x0a"
	           L"007400 000-main.\x0d\x0a"
	           L"007500* 2.3 Comment entries in optional paragraphs\x0d\x0a"
	           L"007600*    The so called comment-entries in the optional paragraphs\x0d\x0a"
	           L"007700*    of the Identification Division are not supported and won't\x0d\x0a"
	           L"007800*    be highlighted properly.";
	return result;
}

bool __fastcall TSynCobolSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterCOBOL;
	return result;
}

bool __fastcall TSynCobolSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'-':
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

void __fastcall TSynCobolSyn::SetCodeStartPos(int Value)
{
	if(Value < fCodeMediumPos)
		fCodeStartPos = Value;
	else
		fCodeStartPos = fCodeMediumPos;
}

void __fastcall TSynCobolSyn::SetCodeMediumPos(int Value)
{
	if((fCodeStartPos <= Value) && (Value <= fCodeEndPos))
		fCodeMediumPos = Value;
	else
	{
		if(Value > fCodeEndPos)
			fCodeMediumPos = fCodeEndPos;
		else
			fCodeMediumPos = fCodeStartPos;
	}
}

void __fastcall TSynCobolSyn::SetCodeEndPos(int Value)
{
	if(Value > fCodeMediumPos)
		fCodeEndPos = Value;
	else
		fCodeEndPos = fCodeMediumPos;
}

/*#static*/
String __fastcall TSynCobolSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangCOBOL;
	return result;
}

void __fastcall TSynCobolSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynCobolSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void* __fastcall TSynCobolSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

/*#static*/
String __fastcall TSynCobolSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangCOBOL;
	return result;
}
static bool SynHighlighterCobol_Initialized = false;

void SynHighlighterCobol_initialization()
{
	if(SynHighlighterCobol_Initialized)
		return;
	
	SynHighlighterCobol_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynCobolSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterCobol

