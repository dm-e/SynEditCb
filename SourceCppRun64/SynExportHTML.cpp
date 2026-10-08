#include <vcl.h>
#pragma hdrstop

#include "SynExportHTML.h"
#include "SynEditMiscProcs.h"
#include "SynEditStrConst.h"
#include "SynHighlighterMulti.h"
#include <System.SysUtils.hpp>

using namespace std;
using namespace d2c_system;
using namespace Syneditexport;
using namespace Synedithighlighter;
using namespace Syneditmiscprocs;
using namespace Syneditstrconst;
using namespace Synhighlightermulti;
using namespace Synunicode;
using namespace System;
using namespace System::Sysutils;
using namespace Vcl::Graphics;

namespace Synexporthtml
{
#define Synexporthtml__0 (TSysCharSet() << '.' << '_')
#define Synexporthtml__1 (TSysCharSet() <<  \
          97 << 98 << 99 << 100 << 101 << 102 <<  \
          103 << 104 << 105 << 106 << 107 << 108 <<  \
          109 << 110 << 111 << 112 << 113 << 114 <<  \
          115 << 116 << 117 << 118 << 119 << 120 <<  \
          121 << 122 <<  \
          48 << 49 << 50 << 51 << 52 << 53 <<  \
          54 << 55 << 56 << 57 << '-')
#define Synexporthtml__2 (System::Set<TSynEncoding, TSynEncoding::seUTF8, TSynEncoding::seAnsi>() << seUTF16LE << seUTF16BE)
#define Synexporthtml__3 (TSynEncodings() << seUTF8 << seUTF16LE << seUTF16BE)



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynExportHTML.pas, released 2000-04-16.

The Original Code is partly based on the mwHTMLExport.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Michael Hieke.
Portions created by Michael Hieke are Copyright 2000 Michael Hieke.
Portions created by James D. Jacobson are Copyright 1999 Martin Waldenburg.
Changes to emit XHTML 1.0 Strict complying code by Maël Hörz.
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

$Id: SynExportHTML.pas,v 1.19.2.7 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

/* TSynExporterHTML */

__fastcall TSynExporterHTML::TSynExporterHTML(TComponent* AOwner)
 : inherited(AOwner),
			fCreateHTMLFragment(false)
{
	const WideChar CF_HTML[] = L"HTML Format";
	fClipboardFormat = RegisterClipboardFormat(const_cast<LPCWSTR>(CF_HTML));
	fDefaultFilter = SYNS_FilterHTML;
	FEncoding = seUTF8;
}

String __fastcall TSynExporterHTML::AttriToCSS(TSynHighlighterAttributes* Attri, String UniqueAttriName)
{
	String result;
	String StyleName;
	StyleName = MakeValidName(UniqueAttriName);
	result = String(L".") + StyleName + L" { ";
	if(UseBackground && (Attri->Background != clNone))
		result = result + L"background-color: " + ColorToHTML(Attri->Background) + L"; ";
	if(Attri->Foreground != clNone)
		result = result + L"color: " + ColorToHTML(Attri->Foreground) + L"; ";
	if(Attri->Style.Contains(TFontStyle::fsBold))
		result = result + L"font-weight: bold; ";
	if(Attri->Style.Contains(TFontStyle::fsItalic))
		result = result + L"font-style: italic; ";
	if(Attri->Style.Contains(TFontStyle::fsUnderline))
		result = result + L"text-decoration: underline; ";
	if(Attri->Style.Contains(TFontStyle::fsStrikeOut))
		result = result + L"text-decoration: line-through; ";
	result = result + L"}";
	return result;
}

bool __fastcall TSynExporterHTML::AttriToCSSCallback(TSynCustomHighlighter* Highlighter, TSynHighlighterAttributes* Attri, String UniqueAttriName, void** Params, int Params_maxidx)
{
	bool result = false;
	String* Styles = nullptr;
	Styles = ((UnicodeString*) Params[0]);
	(*Styles) = (*Styles) + AttriToCSS(Attri, UniqueAttriName) + L"\x0d\x0a";
	result = true; // we want all attributes => tell EnumHighlighterAttris to continue
	return result;
}

String __fastcall TSynExporterHTML::ColorToHTML(TColor AColor)
{
	String result;
	int RGBColor = 0;
	Byte RGBValue = 0;
	const Char Digits[16/*# range 0..15*/] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	RGBColor = ColorToRGB(AColor);
	result = L"#000000";
	RGBValue = GetRValue(static_cast<DWORD>(RGBColor));
	if(RGBValue > 0)
	{
		result[2] = Digits[RGBValue >> 4];
		result[3] = Digits[RGBValue & 15];
	}
	RGBValue = GetGValue(static_cast<DWORD>(RGBColor));
	if(RGBValue > 0)
	{
		result[4] = Digits[RGBValue >> 4];
		result[5] = Digits[RGBValue & 15];
	}
	RGBValue = GetBValue(static_cast<DWORD>(RGBColor));
	if(RGBValue > 0)
	{
		result[6] = Digits[RGBValue >> 4];
		result[7] = Digits[RGBValue & 15];
	}
	return result;
}

void __fastcall TSynExporterHTML::FormatAfterLastAttribute()
{
	AddData(L"</span>");
}

void __fastcall TSynExporterHTML::FormatAttributeDone(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged)
{
	AddData(L"</span>");
}

void __fastcall TSynExporterHTML::FormatAttributeInit(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged)
{
	String StyleName;
	StyleName = GetStyleName(Highlighter, Highlighter->GetTokenAttribute());
	AddData(Format(L"<span class=\"%s\">", ARRAYOFCONST((StyleName))));
}

void __fastcall TSynExporterHTML::FormatBeforeFirstAttribute(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged)
{
	String StyleName;
	StyleName = GetStyleName(Highlighter, Highlighter->GetTokenAttribute());
	AddData(Format(L"<span class=\"%s\">", ARRAYOFCONST((StyleName))));
}

void __fastcall TSynExporterHTML::FormatNewLine()
{
	AddData(L"<br>");
}

String __fastcall TSynExporterHTML::GetFooter()
{
	String result;
	result = L"";
	if(fExportAsText)
		result = L"</span>\x0d\x0a" L"</code></pre>\x0d\x0a";
	else
		result = L"</code></pre><!--EndFragment-->";
	if(!(fCreateHTMLFragment && fExportAsText))
		result = result + L"</body>\x0d\x0a" L"</html>";
	return result;
}

String __fastcall TSynExporterHTML::GetFormatName()
{
	String result;
	result = SYNS_ExporterFormatHTML;
	return result;
}

String __fastcall TSynExporterHTML::GetHeader()
{
	String result;
	const int DescriptionSize = 105;
	const int FooterSize1 = 47;
	const int FooterSize2 = 31;
	const WideChar NativeHeader[] = L"Version:0.9\x0d\x0a"
	    L"StartHTML:%.10d\x0d\x0a"
	    L"EndHTML:%.10d\x0d\x0a"
	    L"StartFragment:%.10d\x0d\x0a"
	    L"EndFragment:%.10d\x0d\x0a";
	const WideChar HTMLAsTextHeader[] = L"<?xml version=\"1.0\" encoding=\"%s\"?>\x0d\x0a"
	    L"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\x0d\x0a"
	    L"<html xmlns=\"http://www.w3.org/1999/xhtml\">\x0d\x0a"
	    L"<head>\x0d\x0a";
	const WideChar HTMLAsTextHeader2[] = L"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=%s\" />\x0d\x0a"
	    L"<meta name=\"generator\" content=\"SynEdit HTML exporter\" />\x0d\x0a"
	    L"<style type=\"text/css\">\x0d\x0a"
	    L"<!--\x0d\x0a"
	    L"body { color: %s; background-color: %s; }\x0d\x0a"
	    L"%s"
	    L"-->\x0d\x0a"
	    L"</style>\x0d\x0a"
	    L"</head>\x0d\x0a"
	    L"<body>\x0d\x0a";
	const String EncodingStrs[4/*# TSynEncoding*/] = {L"UTF-8", L"UTF-16", L"UTF-16", L"ANSI is Unsupported"};
	String EncodingStr;
	String Styles;
	String Header;
	String Header2;
	EncodingStr = EncodingStrs[Encoding];
	EnumHighlighterAttris(Highlighter, true, AttriToCSSCallback, OPENARRAY(void*, (&Styles)));
	Header = Format(HTMLAsTextHeader, ARRAYOFCONST((EncodingStr)));
	Header = Header
	           + L"<title>"
	           + Title
	           + L"</title>\x0d\x0a"
	           + Format(HTMLAsTextHeader2, ARRAYOFCONST((EncodingStr, ColorToHTML(fFont->Color), ColorToHTML(fBackgroundColor), Styles)));
	result = L"";
	if(fExportAsText)
	{
		if(!fCreateHTMLFragment)
			result = Header;
		result = result
	           + Format(L"<pre>\x0d\x0a" L"<code><span style=\"font: %dpt %s;\">", ARRAYOFCONST((fFont->Size, fFont->Name)));
	}
	else

    // Described in http://msdn.microsoft.com/library/sdkdoc/htmlclip/htmlclipboard.htm
	{
		Header2 = L"<!--StartFragment--><pre><code>";
		result = Format(NativeHeader, ARRAYOFCONST((DescriptionSize, DescriptionSize + Header.Length() + Header2.Length() + GetBufferSize() + FooterSize1, DescriptionSize + Header.Length()
                    , DescriptionSize + Header.Length() + Header2.Length() + GetBufferSize() + FooterSize2)));
		result = result + Header + Header2;
	}
	return result;
}

String __fastcall TSynExporterHTML::GetStyleName(TSynCustomHighlighter* Highlighter, TSynHighlighterAttributes* Attri)
{
	String result;
	EnumHighlighterAttris(Highlighter, false, StyleNameCallback, OPENARRAY(void*, (Attri, &result)));
	return result;
}

String __fastcall TSynExporterHTML::MakeValidName(String Name)
{
	String result;
	int i = 0;
	int stop = 0;
	result = LowerCase(Name);
	for(stop = 1, i = result.Length(); i >= stop; i--)
	{
		if(CharInSet(result[i], Synexporthtml__0))
			result[i] = L'-';
		else
		{
			if(!CharInSet(result[i], Synexporthtml__1))
				result.Delete(i, 	1);
		}
	}
	return result;
}

String __fastcall TSynExporterHTML::ReplaceReservedChar(WideChar AChar)
{
	String result;
	switch(AChar)
	{
		case L'&':
		result = L"&amp;";
		break;
		case L'<':
		result = L"&lt;";
		break;
		case L'>':
		result = L"&gt;";
		break;
		case L'\"':
		result = L"&quot;";
		break;
		case L' ':
		result = L"&nbsp;";
		break;
		default:
		result = L"";
		break;
	}
	return result;
}

bool __fastcall TSynExporterHTML::StyleNameCallback(TSynCustomHighlighter* Highlighter, TSynHighlighterAttributes* Attri, String UniqueAttriName, void** Params, int Params_maxidx)
{
	bool result = false;
	TSynHighlighterAttributes* AttriToFind = nullptr;
	String* StyleName = nullptr;
	AttriToFind = ((TSynHighlighterAttributes*) Params[0]);
	StyleName = ((UnicodeString*) Params[1]);
	if(Attri == AttriToFind)
	{
		(*StyleName) = MakeValidName(UniqueAttriName);
		result = false; // found => inform EnumHighlighterAttris to stop searching
	}
	else
	result = true;
	return result;
}

bool __fastcall TSynExporterHTML::UseBom()
{
	bool result = false;
  // do not include seUTF8 as some browsers have problems with UTF-8-BOM
	result = Synexporthtml__2.Contains(Encoding);
	return result;
}

TSynEncodings __fastcall TSynExporterHTML::SupportedEncodings()
{
	TSynEncodings result;
	result = Synexporthtml__3;
	return result;
}


}  // namespace Synexporthtml

