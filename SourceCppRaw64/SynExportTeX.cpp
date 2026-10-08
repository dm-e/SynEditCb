#include <vcl.h>
#pragma hdrstop

#include "SynExportTeX.h"
#include "SynEditMiscProcs.h"
#include "SynEditStrConst.h"
#include <System.SysUtils.hpp>

using namespace std;
using namespace d2c_system;
using namespace Syneditexport;
using namespace Synedithighlighter;
using namespace Syneditmiscprocs;
using namespace Syneditstrconst;
using namespace Synunicode;
using namespace System;
using namespace System::Sysutils;
using namespace Vcl::Graphics;

namespace Synexporttex
{
#define Synexporttex__0 (TSysCharSet() <<  \
										49 << 50 << 51 << 52 << 53 << 54 <<  \
										55 << 56 << 57)
#define Synexporttex__1 (TSysCharSet() <<  \
          97 << 98 << 99 << 100 << 101 << 102 <<  \
          103 << 104 << 105 << 106 << 107 << 108 <<  \
          109 << 110 << 111 << 112 << 113 << 114 <<  \
          115 << 116 << 117 << 118 << 119 << 120 <<  \
          121 << 122 <<  \
          65 << 66 << 67 << 68 << 69 << 70 <<  \
          71 << 72 << 73 << 74 << 75 << 76 <<  \
          77 << 78 << 79 << 80 << 81 << 82 <<  \
          83 << 84 << 85 << 86 << 87 << 88 <<  \
          89 << 90)
#define Synexporttex__2 (TSynEncodings() << seAnsi)



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynExportTeX.pas, released 2002-09-12.

The Original Code is partly based on the mwHTMLExport.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Ascher Stefan.
Portions created by Ascher Stefan are Copyright 2002 Ascher Stefan.
Unicode translation by Maël Hörz.
All Rights Reserved.

Contributors to the SynEdit project are listed in the Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

$Id: SynExportTeX.pas,v 1.8.2.5 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
- LaTeX 2e doesn't support Unicode, so this exporter doesn't either.
  (There are solutions like the package utc.sty but still they don't allow mixing
  of different languages like Arabic and Chinese.
  We'll have to wait for LaTeX 3.)
-------------------------------------------------------------------------------*/


// DotDecSepFormat always formats with a dot as decimal separator.
// This is necessary because LaTeX expects a dot, but VCL's Format is
// language-dependent, i.e. with another locale set, the separator can be
// different (for example a comma).

String __fastcall DotDecSepFormat(const String Format, const TVarRec* Args, int Args_maxidx)
{
	String result;
	TFormatSettings pSettings = {};
	pSettings = FormatSettings;
	pSettings.DecimalSeparator = L'.';
	result = Sysutils::Format(Format, Args, Args_maxidx, pSettings);
	return result;
}

String __fastcall ColorToTeX(TColor AColor)
{
	String result;
	const WideChar f[] = L"%1.2g";
	const WideChar f2[] = L"%s,%s,%s";
	LongWord RGBColor = 0;
	String RValue;
	String GValue;
	String BValue;
	RGBColor = ColorToRGB(AColor);
	RValue = DotDecSepFormat(f, ARRAYOFCONST((double(GetRValue(RGBColor)) / 255)));
	GValue = DotDecSepFormat(f, ARRAYOFCONST((double(GetGValue(RGBColor)) / 255)));
	BValue = DotDecSepFormat(f, ARRAYOFCONST((double(GetBValue(RGBColor)) / 255)));
	result = Format(f2, ARRAYOFCONST((RValue, GValue, BValue)));
	return result;
}

/* TSynExporterTeX */

__fastcall TSynExporterTeX::TSynExporterTeX(TComponent* AOwner)
 : inherited(AOwner),
			fMargin(2),
			fLastAttri(nullptr),
			fCreateTeXFragment(false),
			fTabWidth(0),
			fPageStyleEmpty(false)
{
	fTabWidth = 2;
	fPageStyleEmpty = false;
	fDefaultFilter = SYNS_FilterTeX;
	FEncoding = seAnsi;
}

bool __fastcall TSynExporterTeX::AttriToCommandCallback(TSynCustomHighlighter* Highlighter, TSynHighlighterAttributes* Attri, String UniqueAttriName, void** Params, int Params_maxidx)
{
	bool result = false;
	String* Commands = nullptr;
	Commands = ((UnicodeString*) Params[0]);
	(*Commands) = (*Commands) + AttriToCommand(Attri, UniqueAttriName) + sLineBreak;
	result = true; // we want all attributes => tell EnumHighlighterAttris to continue
	return result;
}

String __fastcall TSynExporterTeX::AttriToCommand(TSynHighlighterAttributes* Attri, String UniqueAttriName)
{
	String result;
	const WideChar NewCommand[] = L"\\newcommand{\\%s}[1]{%s#1%s}";
	const WideChar SBold[] = L"\\textbf{";
	const WideChar SItalic[] = L"\\textit{";
	const WideChar SUnderline[] = L"\\uln{";
	const WideChar SColor[] = L"\\textcolor[rgb]{%s}{";
	const WideChar SBackColor[] = L"\\colorbox[rgb]{%s}{";
	String Formatting;
	int BracketCount = 0;
	BracketCount = 0;
	/*# with Attri do */
	{
		auto with0 = Attri;
		if(with0->Style.Contains(TFontStyle::fsBold))
		{
			Formatting = Formatting + SBold;
			++BracketCount;
		}
		if(with0->Style.Contains(TFontStyle::fsItalic))
		{
			Formatting = Formatting + SItalic;
			++BracketCount;
		}
		if(with0->Style.Contains(TFontStyle::fsUnderline))
		{
			Formatting = Formatting + SUnderline;
			++BracketCount;
		}
		if((with0->Foreground != clBlack) && (with0->Foreground != clNone))
		{
			Formatting = Formatting + Format(SColor, ARRAYOFCONST((ColorToTeX(with0->Foreground))));
			++BracketCount;
		}
		if(fUseBackground && (with0->Background != clNone))
		{
			Formatting = Formatting + Format(SBackColor, ARRAYOFCONST((ColorToTeX(with0->Background))));
			++BracketCount;
		}
		result = Format(NewCommand, ARRAYOFCONST((MakeValidName(UniqueAttriName), Formatting, StringOfChar(L'}', BracketCount))));
	}
	return result;
}

bool __fastcall TSynExporterTeX::CommandNameCallback(TSynCustomHighlighter* Highlighter, TSynHighlighterAttributes* Attri, String UniqueAttriName, void** Params, int Params_maxidx)
{
	bool result = false;
	TSynHighlighterAttributes* AttriToFind = nullptr;
	String* CommandName = nullptr;
	AttriToFind = ((TSynHighlighterAttributes*) Params[0]);
	CommandName = ((UnicodeString*) Params[1]);
	if(Attri == AttriToFind)
	{
		(*CommandName) = MakeValidName(UniqueAttriName);
		result = false; // found => inform EnumHighlighterAttris to stop searching
	}
	else
	result = true;
	return result;
}

void __fastcall TSynExporterTeX::FormatToken(String Token)
{
	String CommandName;
	CommandName = GetCommandName(Highlighter, fLastAttri);
	AddData(String(L"\\") + CommandName + L"{" + Token + L"}");
}

void __fastcall TSynExporterTeX::FormatNewLine()
{
	AddData(String(L"\\\\") + sLineBreak);
}

// do nothing with these

void __fastcall TSynExporterTeX::FormatAfterLastAttribute()
{

}

void __fastcall TSynExporterTeX::FormatAttributeDone(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged)
{

}

void __fastcall TSynExporterTeX::FormatAttributeInit(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged)
{

}

void __fastcall TSynExporterTeX::FormatBeforeFirstAttribute(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged)
{

}

String __fastcall TSynExporterTeX::GetCommandName(TSynCustomHighlighter* Highlighter, TSynHighlighterAttributes* Attri)
{
	String result;
	EnumHighlighterAttris(Highlighter, false, CommandNameCallback, OPENARRAY(void*, (Attri, &result)));
	return result;
}

String __fastcall TSynExporterTeX::GetFooter()
{
	String result;
	if(!fCreateTeXFragment)
		result = AnsiString("\x0d\x0a") + "\\end{ttfamily}" + sLineBreak + "\\end{document}";
	else
		result = AnsiString("\x0d\x0a") + "\\end{ttfamily}";
	return result;
}

String __fastcall TSynExporterTeX::GetFormatName()
{
	String result;
	result = SYNS_ExporterFormatTeX;
	return result;
}

String __fastcall TSynExporterTeX::GetHeader()
{
	String result;
	const UnicodeString TeXHeader = String(L"\\documentclass[a4paper, %dpt]{article}") + sLineBreak
	    + L"\\usepackage[a4paper, margin=%dcm]{geometry}"
	    + sLineBreak
	    + L"\\usepackage[T1]{fontenc}"
	    + sLineBreak
	    + L"\\usepackage{color}"
	    + sLineBreak
	    + L"\\usepackage{alltt}"
	    + sLineBreak
	    + L"\\usepackage{times}"
	    + sLineBreak
	    + L"\\usepackage{ulem}"
	    + sLineBreak
	    + L"\\usepackage[ansinew]{inputenc}"
	    + sLineBreak
	    + L"%s"
	    + sLineBreak; // New Commands
	const UnicodeString TeXHeader2 = String(L"%% Generated by SynEdit TeX exporter") + sLineBreak
	    + sLineBreak
	    + L"\\begin{document}";
	const WideChar EmptyPage[] = L"\\pagestyle{empty}";
	const UnicodeString TeXDocument = String(L"\\begin{ttfamily}") + sLineBreak + L"\\noindent" + sLineBreak;
	String PageStyle;
	if(!fCreateTeXFragment)
	{
		if(fPageStyleEmpty)
			PageStyle = AnsiString("\x0d\x0a") + EmptyPage;
		else
			PageStyle = L"";
		result = Format(String(L"\\documentclass[a4paper, %dpt]{article}") + sLineBreak
	           + L"\\usepackage[a4paper, margin=%dcm]{geometry}"
	           + sLineBreak
	           + L"\\usepackage[T1]{fontenc}"
	           + sLineBreak
	           + L"\\usepackage{color}"
	           + sLineBreak
	           + L"\\usepackage{alltt}"
	           + sLineBreak
	           + L"\\usepackage{times}"
	           + sLineBreak
	           + L"\\usepackage{ulem}"
	           + sLineBreak
	           + L"\\usepackage[ansinew]{inputenc}"
	           + sLineBreak
	           + L"%s"
	           + sLineBreak
	           + sLineBreak
	           + sLineBreak, ARRAYOFCONST((Font->Size, fMargin, GetNewCommands())));
		result = result + L"\\title{" + Title + L"}" + sLineBreak + TeXHeader2 + sLineBreak + PageStyle;
	}
	result = result + TeXDocument;
	return result;
}

String __fastcall TSynExporterTeX::GetNewCommands()
{
	String result;
	const UnicodeString FixedCommands = String(L"%% Special Characters") + sLineBreak
	    + L"\\newcommand\\SPC{\\hspace*{0.6em}}"
	    + sLineBreak
	    + L"\\newcommand\\TAB{\\hspace*{%sem}}"
	    + sLineBreak
	    + L"\\newcommand\\BS{\\mbox{\\char 92}}"
	    + sLineBreak
	    + L"\\newcommand\\TLD{\\mbox{\\char 126}}"
	    + sLineBreak
	    + L"\\newcommand\\CIR{\\mbox{\\char 94}}"
	    + sLineBreak
	    + L"\\newcommand\\HYP{\\mbox{\\char 45}}"
	    + sLineBreak
	    + L"\\newcommand\\QOT{\\mbox{\\char 34}}"
	    + sLineBreak
	    + L"\\newcommand{\\uln}[1]{\\bgroup \\markoverwith{\\hbox{\\_}}\\ULon{{#1}}}"
	    + sLineBreak
	    + L"%% Highlighter Attributes"
	    + sLineBreak;
	const WideChar f[] = L"%1.1g";
	String tw;
	String Commands;
	tw = DotDecSepFormat(f, ARRAYOFCONST(((long double)fTabWidth * 0.6)));
	result = Format(FixedCommands, ARRAYOFCONST((tw)));
	EnumHighlighterAttris(Highlighter, true, AttriToCommandCallback, OPENARRAY(void*, (&Commands)));
	result = result + Commands;
	return result;
}

String __fastcall TSynExporterTeX::MakeValidName(String Name)
{
	String result;
	int i = 0;
	int stop = 0;
	result = Name;
	for(stop = 1, i = result.Length(); i >= stop; i--)
	{
		if(CharInSet(result[i], Synexporttex__0))
			result[i] = ((Char) (int(L'A') + int(result[i]) - int(L'1')));
		else
		{
			if(result[i] == L'0')
				result[i] = L'Z';
			else
			{
				if(!CharInSet(result[i], Synexporttex__1))
					result.Delete(i, 	1);
			}
		}
	}
	return result;
}

String __fastcall TSynExporterTeX::ReplaceReservedChar(WideChar AChar)
{
	String result;
	switch(AChar)
	{
		case L'{':
		result = L"\\{";
		break;
		case L'}':
		result = L"\\}";
		break;
		case L'\\':
		result = L"\\BS ";
		break;
		case L'~':
		result = L"\\TLD ";
		break;
		case L'^':
		result = L"\\CIR ";
		break;
		case L' ':
		result = L"\\SPC ";
		break;
		case L'\x09':
		result = L"\\TAB ";
		break;
		case L'-':
		result = L"\\HYP ";
		break;
		case L'\"':
		result = L"\\QOT ";
		break;
		case L'@':
		result = L"$@$";
		break;
		case L'$':
		result = L"\\$";
		break;
		case L'&':
		result = L"\\&";
		break;
		case L'<':
		result = L"$<$";
		break;
		case L'>':
		result = L"$>$";
		break;
		case L'_':
		result = L"\\_";
		break;
		case L'#':
		result = L"\\#";
		break;
		case L'%':
		result = L"\\%";
		break;
		default:
		result = L"";
		break;
	}
	return result;
}

void __fastcall TSynExporterTeX::SetTokenAttribute(TSynHighlighterAttributes* Attri)
{
	fLastAttri = Attri;
}

TSynEncodings __fastcall TSynExporterTeX::SupportedEncodings()
{
	TSynEncodings result;
	result = Synexporttex__2;
	return result;
}

bool __fastcall TSynExporterTeX::UseBom()
{
	bool result = false;
	result = false;
	return result;
}


}  // namespace Synexporttex

