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
	const WideChar F2[] = L"%s,%s,%s";
	unsigned long RGBColor = 0;
	String RValue;
	String GValue;
	String BValue;
	RGBColor = ColorToRGB(AColor);
	RValue = DotDecSepFormat(f, ARRAYOFCONST(((long double) GetRValue(RGBColor) / 255)));
	GValue = DotDecSepFormat(f, ARRAYOFCONST(((long double)GetGValue(RGBColor) / 255)));
	BValue = DotDecSepFormat(f, ARRAYOFCONST(((long double)GetBValue(RGBColor) / 255)));
	result = Format(F2, ARRAYOFCONST((RValue, GValue, BValue)));
	return result;
}

/* TSynExporterTeX */

__fastcall TSynExporterTeX::TSynExporterTeX(TComponent* AOwner)
 : inherited(AOwner),
			FMargin(2),
			fLastAttri(nullptr),
			fCreateTeXFragment(false),
			FTabWidth(0),
			fPageStyleEmpty(false)
{
	FTabWidth = 2;
	fPageStyleEmpty = false;
	fDefaultFilter = SYNS_FilterTeX;
	FEncoding = seAnsi;
}

bool __fastcall TSynExporterTeX::AttriToCommandCallback(TSynCustomHighlighter* Highlighter, TSynHighlighterAttributes* Attri, String UniqueAttriName, void** Params, int Params_maxidx)
{
	bool result = false;
	String* Commands = nullptr;
	Commands = ((UnicodeString*) Params[0]);
	(*Commands) = (*Commands) + AttriToCommand(Attri, UniqueAttriName) + sLinebreak;
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
	const WideChar sColor[] = L"\\textcolor[rgb]{%s}{";
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
			Formatting = Formatting + Format(sColor, ARRAYOFCONST((ColorToTeX(with0->Foreground))));
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
	AddData(String(L"\\\\") + sLinebreak);
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
		result = AnsiString("\x0d\x0a") + "\\end{ttfamily}" + sLinebreak + "\\end{document}";
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
	const AnsiString TeXHeader = String(L"\\documentclass[a4paper, %dpt]{article}") + sLinebreak
	    + L"\\usepackage[a4paper, margin=%dcm]{geometry}"
	    + sLinebreak
	    + L"\\usepackage[T1]{fontenc}"
	    + sLinebreak
	    + L"\\usepackage{color}"
	    + sLinebreak
	    + L"\\usepackage{alltt}"
	    + sLinebreak
	    + L"\\usepackage{times}"
	    + sLinebreak
	    + L"\\usepackage{ulem}"
	    + sLinebreak
	    + L"\\usepackage[ansinew]{inputenc}"
	    + sLinebreak
	    + L"%s"
	    + sLinebreak; // New Commands
	const AnsiString TeXHeader2 = String(L"%% Generated by SynEdit TeX exporter") + sLinebreak
	    + sLinebreak
	    + L"\\begin{document}";
	const WideChar EmptyPage[] = L"\\pagestyle{empty}";
	const AnsiString TeXDocument = String(L"\\begin{ttfamily}") + sLinebreak + L"\\noindent" + sLinebreak;
	String PageStyle;
	if(!fCreateTeXFragment)
	{
		if(fPageStyleEmpty)
			PageStyle = AnsiString("\x0d\x0a") + EmptyPage;
		else
			PageStyle = L"";
		result = Format(String(L"\\documentclass[a4paper, %dpt]{article}") + sLinebreak
	           + L"\\usepackage[a4paper, margin=%dcm]{geometry}"
	           + sLinebreak
	           + L"\\usepackage[T1]{fontenc}"
	           + sLinebreak
	           + L"\\usepackage{color}"
	           + sLinebreak
	           + L"\\usepackage{alltt}"
	           + sLinebreak
	           + L"\\usepackage{times}"
	           + sLinebreak
	           + L"\\usepackage{ulem}"
	           + sLinebreak
	           + L"\\usepackage[ansinew]{inputenc}"
	           + sLinebreak
	           + L"%s"
	           + sLinebreak
	           + sLinebreak
	           + sLinebreak, ARRAYOFCONST((Font->Size, FMargin, GetNewCommands())));
		result = result + L"\\title{" + Title + L"}" + sLinebreak + TeXHeader2 + sLinebreak + PageStyle;
	}
	result = result + TeXDocument;
	return result;
}

String __fastcall TSynExporterTeX::GetNewCommands()
{
	String result;
	const AnsiString FixedCommands = String(L"%% Special Characters") + sLinebreak
	    + L"\\newcommand\\SPC{\\hspace*{0.6em}}"
	    + sLinebreak
	    + L"\\newcommand\\TAB{\\hspace*{%sem}}"
	    + sLinebreak
	    + L"\\newcommand\\BS{\\mbox{\\char 92}}"
	    + sLinebreak
	    + L"\\newcommand\\TLD{\\mbox{\\char 126}}"
	    + sLinebreak
	    + L"\\newcommand\\CIR{\\mbox{\\char 94}}"
	    + sLinebreak
	    + L"\\newcommand\\HYP{\\mbox{\\char 45}}"
	    + sLinebreak
	    + L"\\newcommand\\QOT{\\mbox{\\char 34}}"
	    + sLinebreak
	    + L"\\newcommand{\\uln}[1]{\\bgroup \\markoverwith{\\hbox{\\_}}\\ULon{{#1}}}"
	    + sLinebreak
	    + L"%% Highlighter Attributes"
	    + sLinebreak;
	const WideChar f[] = L"%1.1g";
	String tw;
	String Commands;
	tw = DotDecSepFormat(f, ARRAYOFCONST(((long double)FTabWidth * 0.6)));
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


}  // namespace SynExportTeX

