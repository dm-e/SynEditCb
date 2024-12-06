
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterFoxpro.h"
#include "SynEditStrConst.h"
#include "SynEditDelphiInstances.hpp"
#include "d2c_syshelper.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace Synhighlighterhashentries;
using namespace System;
using namespace System::Regularexpressions;

namespace Synhighlighterfoxpro
{
#define Synhighlighterfoxpro__0 (TRegExOptions() << roIgnoreCase)
#define Synhighlighterfoxpro__1 (TRegExOptions() << roIgnoreCase)


const String KeyWords = L"_curobj, _msysmenu, _pageno, _screen, _vfp, abs, accept, aclass, acopy, acos, "
	           L"acti, activate, adatabases, adbobjects, add, additive, adel, adir, aelement, "
	           L"aerror, afields, afont, after, again, ains, ainstance, alen, alias, alines, "
	           L"all, alltrim, alt, alter, alternate, amembers, and, ansi, ansitooem, any, "
	           L"aplabout, app, appe, append, application, aprinters, array, as, asc, ascan, "
	           L"ascending, ascii, aselobj, asin, asort, assert, asserts, assist, asubscript, "
	           L"at, at_c, atan, atc, atcc, atcline, atline, atn2, aused, auto, autoincerror, "
	           L"autosave, average, avg, backcolor, bar, barcount, barprompt, baseclass, before,"
	           L"begin, bell, between, bintoc, bitand, bitclear, bitlshift, bitnot, bitor, "
	           L"bitrshift, bitset, bittest, bitxor, blan, blank, blink, blocksize, bof, border, "
	           L"bott, bottom, box, brow, browse, browseime, brstatus, build, by, calculate, "
	           L"call, cancel, candidate, capslock, caption, carry, case, catch, cd, cdow, cdx, "
	           L"ceiling, century, class, classlib, clear, clock, clos, close, cls, cmonth, cnt, "
	           L"cntbar, cntpad, codepage, col, collate, color, colorscheme, comm, command, "
	           L"commands, comment, compact, compatible, compile, compobj, confirm, connection, "
	           L"connections, connstring, console, continue, copy, cos, count, coverage, "
	           L"cpcompile, cpconvert, cpcurrent, cpdbf, cpdialog, cpnotrans, create, "
	           L"createobject, createoffline, ctobin, ctod, ctot, curdir, currency, cursor, "
	           L"curval, custom, cycle, database, databases, datasession, date, "
	           L"dateformat, datemark, datetime, day, dbalias, dbc, dbf, dbused, ddeaborttrans, "
	           L"ddeadvise, ddeenabled, ddeexecute, ddeinitiate, ddelasterror, ddepoke, "
	           L"dderequest, ddesetoption, ddesetservice, ddesettopic, ddeterminate, deactivate, "
	           L"debug, debugout, decimals, declare, default, define, dele, delete, "
	           L"deleted, delimite, delimited, delimiters, descending, desktop, development, "
	           L"device, dif, difference, dim, dimension, dir, directory, disable, "
	           L"diskspace, display, displayvalue, distinct, dll, dlls, dmy, do, dock, "
	           L"dodefault, doevents, dohistory, double, dow, drop, dtoc, dtor, dtos, dtot, "
	           L"each, edit, echo, eject, else, empty, enable, end, endcase, "
	           L"enddefine, enddo, endfor, endfunc, endif, endprintjob, endproc, endscan, "
	           L"endtext, endwith, enginebehavior, environment, eof, erase, error, escape, "
	           L"evaluate, event, eventhandler, eventlist, events, eventtracking, exact, except, "
	           L"exclusive, exe, exists, exit, exp, export, expression, extended, external, "
	           L"false, fclose, fcount, fcreate, fdow, feof, ferror, fetch, fflush, fgets, fchsize, "
	           L"field, fields, file, files, fill, filter, finally, find, fixed, fklabel, fkmax, "
	           L"float, flock, floor, flush, font, fontmetric, footer, fopen, for, force, "
	           L"foreign, form, format, found, fox2x, foxplus, foxpro), fputs, fread, free, "
	           L"freeze, from, fseek, fsize, fullpath, func, functi, function, fv, fw2, fweek, "
	           L"fwrite, gath, gather, general, get, getbar, getcolor, getcp, getdir, getenv, "
	           L"getexpr, getfile, getfldstate, getfont, getnextmodified, getobject, getpad, "
	           L"getpict, getprinter, gets, global, go, gomonth, gotfocus, goto, group, grow, "
	           L"halfheight, having, header, heading, headings, height, help, helpcontextid, "
	           L"helpfilter, hidden, hide, highlight, hour, hours, change, char, chdir, "
	           L"check, chr, chrsaw, chrtran, chrtranc, icon, id, idxcollate, if, ifdef, ifndef, "
	           L"iif, import, in, include, indbc, index, indexes, inkey, inlist, input, insert, "
	           L"insmode, int, integer, intensity, interval, into, is, isalpha, iscolor, "
	           L"isdigit, isexclusive, isflocked, islower, isnull, isreadonly, isrlocked, "
	           L"isupper, join, key, keyboard, keycomp, keymatch, label, last, lastkey, ledit, "
	           L"left, leftc, len, lenc, level, library, like, line, lineno, linked, list, "
	           L"load, loadpicture, local, locate, locfile, lock, lockscreen, log, log10, "
	           L"logerrors, logout, long, lookup, loop, lower, lparameter, lparameters, "
	           L"lpartition, ltrim, lupdate, macdesktop, mackey, macro, macros, machelp, margin, "
	           L"mark, master, max, mcol, md, mdown, mdx, mdy, memlines, memo, memory, memos, "
	           L"memowidth, memvar, menu, menus, message, messagebox, messages, middle, min, "
	           L"minimize, minute, mkdir, mline, mod, modal, modi, modify, module, month, mouse, "
	           L"movable, move, moved, mover, mrkbar, mrkpad, mrow, mtdll, mton, multilocks, "
	           L"multiselect, mvcount, mwindow, name, ndx, near, negotiate, network, newobject, "
	           L"next, noalias, noappend, noclear, noclose, noconsole, nocptrans, nodata, "
	           L"nodebug, nodefault, nodelete, noedit, noeject, noenvironment, nofloat, nogrow, "
	           L"noinit, nolgrid, nolink, nolock, nomargin, nomdi, nomenu, nominimize, nomodify, "
	           L"nomouse, none, nooptimize, nooverwrite, noprompt, noread, norefresh, "
	           L"norequery, norgrid, normal, normalize, nosave, noshadow, noshow, nospace, not, "
	           L"note, notify, noupdate, novalidate, noverify, nowait, nowindow, nowrap, nozoom, "
	           L"npv, ntom, null, nulldisplay, number, numlock, nvl, object, objects, "
	           L"objnum, objtoclient, objvar, occurs, odometer, oemtoansi, of, off, oldval, "
	           L"oleclass, olecontrol, oleobject, olepublic, on, only, open, optimize, or, "
	           L"order, os, otherwise, outer, overview, overwrite, pack, pad, padc, padl, padr, "
	           L"page, palette, panel, para, parameter, parameters, partition, path, payment, "
	           L"pcol, pdox, pdsetup, pen, pi, pictres, picture, pixels, plain, play, point, "
	           L"pop, popup, popups, preference, preview, primary, print, printer, printjob, "
	           L"printstatus, private, prmbar, prmpad, proc, proced, procedure, procedures, "
	           L"production, program, project, prompt, proper, protected, prow, prtinfo, public, "
	           L"push, putfile, pv, query, quit, rand, range, rat, ratc, ratline, rd, rdlevel, "
	           L"read, readborder, readerror, readkey, recall, reccount, recno, record, recover, "
	           L"recsize, redit, reference, references, refresh, region, regional, reindex, "
	           L"rela, relati, relation, relative, release, remote, remove, rename, repl, repla, "
	           L"replace, replicate, report, reprocess, requery, reset, resizable, resize, "
	           L"resource, resources, rest, restore, resume, retry, retu, return, rgb, "
	           L"rgbscheme, right, rightc, rightclick, righttoleft, rlock, rmdir, rollback, "
	           L"round, row, rtod, rtrim, run, runscript, runtime, safety, same, save, say, "
	           L"scan, scat, scatt, scatter, scols, scoreboard, screen, scroll, sdf, "
	           L"second, seconds, seek, sele, select, selected, selection, separator, "
	           L"set, shadow, shadows, shape, show, shutdown, scheme, "
	           L"schemes, sign, sin, single, sizable, size, skip, skpbar, skppad, some, sort, "
	           L"sorted, soundex, space, sql, sqlcommit, sqlrollback, sqlstringconnect, sqrt, "
	           L"srows, status, statusbartext, std, step, sticky, store, str, strconv, "
	           L"strictdate, string, strtran, structure, stuff, stuffc, style, sub, substr, substrc, "
	           L"sum, summary, suspend, sylk, sys, sysformats, sysmenu, sysmenus, sysmetric, "
	           L"system, tab, tabindex, table, tablerevert, tables, tableupdate, tablevalidate, "
	           L"tabstop, tag, talk, tan, target, text, textmerge, textwidth, then, this, thisform, "
	           L"thisformset, time, timeout, timer, title, titles, to, top, topic, total, "
	           L"transaction, transform, trap, trbetween, trigger, trim, true, try, ttoc, ttod, "
	           L"txnlevel, txtwidth, type, typeahead, udfparms, undefine, union, unique, unlock, "
	           L"unpack, until, update, updated, upper, use, used, val, valid, validate, value, "
	           L"values, var, varread, vartype, version, view, views, volume, wait, wborder, "
	           L"wcols, week, wexist, wfont, when, where, while, wchild, width, window, "
	           L"windowlist, windows, with, wk1, wk3, wks, wlast, wlcol, wlrow, wontop, "
	           L"workarea, woutput, wparent, wr1, wrap, wread, writeexpression, writemethod, "
	           L"wrk, wrows, wtitle, wvisible, xcmdfile, xl5, xls, year, zap, zoom, zorder, "
	           L"zorderset";

/*$Q-*/

unsigned int __fastcall TSynFoxproSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;

	auto GetOrd = [&]() -> unsigned int 
	{
		unsigned int result = 0;
		switch((*Str))
		{
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			result = (unsigned int) (1 + int((*Str)) - int(L'a'));
			break;
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			result = (unsigned int) (1 + int((*Str)) - int(L'A'));
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			result = (unsigned int) (28 + int((*Str)) - int(L'0'));
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
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) ((7 * result + GetOrd()) & 0xFFFFFF);
		++Str;
	}
	result = (unsigned int) (result & 0xFF); // 255
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynFoxproSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkSymbol;
	TSynHashEntry* Entry = nullptr;
	fToIdent = MayBe;
	Entry = fKeywords->Items[HashKey(MayBe)];
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

__fastcall TSynFoxproSyn::TSynFoxproSyn(TComponent* AOwner)
 : inherited(AOwner),
			FTokenID(tkSymbol),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fKeywords(nullptr)
{
	fCaseSensitive = false;
	fKeywords = new TSynHashEntryList();
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	AddAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	AddAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	AddAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	AddAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	AddAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterFoxpro;
	EnumerateKeywords(int(tkKey), KeyWords, IsIdentChar, DoAddKeyword);
//++ CodeFolding
	RE_BlockBegin = TRegEx(L"\\b(function |procedure )\\b", Synhighlighterfoxpro__0);
	RE_BlockEnd = TRegEx(L"\\b(endproc|endfunc)\\b", Synhighlighterfoxpro__1);
//-- CodeFolding
}

//++ CodeFolding
const int FT_Standard = 1;  // begin end, class end, record end
const int FT_Comment = 11;
const int FT_CodeDeclaration = 16;
const int FT_CodeDeclarationWithBody = 17;
const int FT_Implementation = 18;

void __fastcall TSynFoxproSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
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
		if(UpperCase(S.SubString(1, 7)) == L"*REGION")
		{
			FoldRanges->StartFoldRange(Line + 1, FoldRegionType);
			result = true;
		}
		else
		{
			if(UpperCase(S.SubString(1, 11)) == L"*ENDREGION")
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

void __fastcall TSynFoxproSyn::AdjustFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan)
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

void __fastcall TSynFoxproSyn::AndSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'&':                               /*Comments*/
		{
			Run += 2;
			FTokenID = tkComment;
			while(fLine[Run] != L'\x00')
			{
				switch(fLine[Run])
				{
					case L'\x0a':
					case L'\x0d':
					goto label2;
					default:
					  ;
					break;
				} //case
				++Run;
			}
			label2:;
		}
		break;                                 /*and*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynFoxproSyn::AsciiCharProc()
{
	FTokenID = tkString;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label3;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x27'));
	label3:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynFoxproSyn::AtSymbolProc()
{
	FTokenID = tkKey;
	++Run;
}

void __fastcall TSynFoxproSyn::BraceOpenProc()
{
	FTokenID = tkString;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label4;
			case L'\x5c':
			if(fLine[Run + 1] == L'\x0a')
				++Run;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'}'));
	label4:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynFoxproSyn::CRProc()
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

__fastcall TSynFoxproSyn::~TSynFoxproSyn()
{
	delete fKeywords;
	// inherited;
}

void __fastcall TSynFoxproSyn::DoAddKeyword(String AKeyword, int AKind)
{
	int HashValue = 0;
	HashValue = (int) HashKey(ustr2pwchar(AKeyword));
	fKeywords->Items[HashValue] = new TSynHashEntry(AKeyword, AKind);
}

void __fastcall TSynFoxproSyn::ColonProc()
{

  /*colon*/
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::CommaProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::EqualProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*logical equal*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*assign*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynFoxproSyn::GreaterProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*greater than or equal to*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;
		case L'>':
		{
			if(fLine[Run + 2] == L'=')   /*shift right assign*/
				Run += 3;
			else
                           /*shift right*/
				Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*greater than*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynFoxproSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynFoxproSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynFoxproSyn::LowerProc()
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
			if(fLine[Run + 2] == L'=')   /*shift left assign*/
				Run += 3;
			else
                           /*shift left*/
				Run += 2;
			FTokenID = tkSymbol;
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

void __fastcall TSynFoxproSyn::MinusProc()
{

  /*subtract*/
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::ModSymbolProc()
{

  /*mod*/
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::NotSymbolProc()
{

  /*not*/
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynFoxproSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'.':
			case L'x':
			case L'X':
			case L'e':
			case L'E':
			case L'f':
			case L'F':
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
				goto label5;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label5:;
}

void __fastcall TSynFoxproSyn::OrSymbolProc()
{

  /*or*/
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::PlusProc()
{

  /*subtract*/
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::PointProc()
{
	if(((UpperCase(String(fLine[Run + 1])) == L"T") || (UpperCase(String(fLine[Run + 1])) == L"F")) && (fLine[Run + 2] == L'.'))      /*.t.*/     /*.f.*/
	{
		Run += 3;
		FTokenID = tkSymbol;
	}
	else
	{
		if((((UpperCase(String(fLine[Run + 1])) == L"A") && (UpperCase(String(fLine[Run + 2])) == L"N") && (UpperCase(String(fLine[Run + 3])) == L"D")) || ((UpperCase(String(fLine[Run + 1])) == L"N") && (UpperCase(String(fLine[Run + 2])) == L"O") && (UpperCase(String(fLine[Run + 3])) == L"T"))) && (fLine[Run + 4] == L'.'))   /*.and.*/   /*.not.*/
		{
			Run += 5;
			FTokenID = tkSymbol;
		}
		else
		{
			if((UpperCase(String(fLine[Run + 1])) == L"O") && (UpperCase(String(fLine[Run + 2])) == L"R") && (fLine[Run + 3] == L'.'))  /*.or.*/
			{
				Run += 4;
				FTokenID = tkSymbol;
			}
			else
                                 /*point*/
			{
				++Run;
				FTokenID = tkSymbol;
			}
		}
	}
}

void __fastcall TSynFoxproSyn::QuestionProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::RoundCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::RoundOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::SemiColonProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::SlashProc()
{

  /*division*/
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynFoxproSyn::SquareCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::SquareOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::StarProc()
{
	if((Run == 0) || (Trim(String(fLine).SubString(1, Run)) == L""))                        /*Foxpro Comments*/
	{
		++Run;
		FTokenID = tkComment;
		while(fLine[Run] != L'\x00')
		{
			switch(fLine[Run])
			{
				case L'\x0a':
				case L'\x0d':
				goto label6;
				default:
				  ;
				break;
			}
			++Run;
		}
		label6:;
	}
	else

    /*star*/
	{
		++Run;
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynFoxproSyn::StringProc()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x22') && (fLine[Run + 2] == L'\x22'))
		Run += 2;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label7;
			case L'\x5c':
			if(fLine[Run + 1] == L'\x0a')
				++Run;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x22'));
	label7:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynFoxproSyn::TildeProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::XOrSymbolProc()
{

  /*xor*/
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynFoxproSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynFoxproSyn::Next()
{
	fTokenPos = Run;
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
		case L'?':
		QuestionProc();
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
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynFoxproSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynFoxproSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynFoxproSyn::GetTokenID()
{
	TtkTokenKind result = tkSymbol;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynFoxproSyn::GetTokenAttribute()
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

int __fastcall TSynFoxproSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

bool __fastcall TSynFoxproSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterFoxpro;
	return result;
}

/*#static*/
String __fastcall TSynFoxproSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangFoxpro;
	return result;
}

/*#static*/
String __fastcall TSynFoxproSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangFoxpro;
	return result;
}

	static bool SynHighlighterFoxpro_Initialized = false;
	
	void SynHighlighterFoxpro_initialization()
	{
		if(SynHighlighterFoxpro_Initialized)
			return;
		
		SynHighlighterFoxpro_Initialized = true;
		
		RegisterPlaceableHighlighter(__classid(TSynFoxproSyn));
	}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterFoxpro

