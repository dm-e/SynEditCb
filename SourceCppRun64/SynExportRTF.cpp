#include <vcl.h>
#pragma hdrstop

#include "SynExportRTF.h"
#include "SynEditStrConst.h"
#include <System.SysUtils.hpp>

using namespace std;
using namespace d2c_system;
using namespace Syneditexport;
using namespace Syneditstrconst;
using namespace Synunicode;
using namespace System;
using namespace System::Sysutils;
using namespace System::Uitypes;

namespace Synexportrtf
{
#define Synexportrtf__0 (TSynEncodings() << seUTF8)



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynExportRTF.pas, released 2000-04-16.

The Original Code is partly based on the mwRTFExport.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Michael Hieke.
Portions created by Michael Hieke are Copyright 2000 Michael Hieke.
Portions created by James D. Jacobson are Copyright 1999 Martin Waldenburg.
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

$Id: SynExportRTF.pas,v 1.10.2.3 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

/* TSynExporterRTF */

__fastcall TSynExporterRTF::TSynExporterRTF(TComponent* AOwner)
 : inherited(AOwner),
			fAttributesChanged(false),
			fListColors(nullptr)
{
	fListColors = new TList();
	fDefaultFilter = SYNS_FilterRTF;
	fClipboardFormat = RegisterClipboardFormat(const_cast<LPCWSTR>(CF_RTF));
	FEncoding = seUTF8;
}

__fastcall TSynExporterRTF::~TSynExporterRTF()
{
	delete fListColors;
	fListColors = nullptr;
	//# inherited::Destroy();
}

void __fastcall TSynExporterRTF::Clear()
{
	inherited::Clear();
	if(ASSIGNED(fListColors))
		fListColors->Clear();
}

String __fastcall TSynExporterRTF::ColorToRTF(TColor AColor)
{
	String result;
	int Col = 0;
	Col = ColorToRGB(AColor);
	result = Format(L"\\red%d\\green%d\\blue%d;", ARRAYOFCONST((GetRValue(static_cast<DWORD>(Col)), GetGValue(static_cast<DWORD>(Col)), GetBValue(static_cast<DWORD>(Col)))));
	return result;
}

void __fastcall TSynExporterRTF::FormatAfterLastAttribute()
{

  // no need to reset the font style here...

}

void __fastcall TSynExporterRTF::FormatAttributeDone(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged)
{
	const String FontTags[4/*# TFontStyle*/] = {L"\\b0", L"\\i0", L"\\ul0", L"\\strike0"};
	TFontStyle AStyle = TFontStyle::fsBold;
  // nothing to do about the color, but reset the font style
	TFontStyle stop = (TFontStyle) 0;
	for(stop = (TFontStyle) 3 /*# High(TFontStyle) */, AStyle = (TFontStyle) 0 /*# Low(TFontStyle) */; AStyle <= stop; Inc(AStyle))
	{
		if(FontStylesChanged.Contains(AStyle))
		{
			fAttributesChanged = true;
			AddData(FontTags[AStyle]);
		}
	}
}

void __fastcall TSynExporterRTF::FormatAttributeInit(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged)
{
	const String FontTags[4/*# TFontStyle*/] = {L"\\b", L"\\i", L"\\ul", L"\\strike"};
	TFontStyle AStyle = TFontStyle::fsBold;
  // background color
	TFontStyle stop = (TFontStyle) 0;
	if(BackgroundChanged)
	{
		AddData(Format(L"\\chshdng10000\\chcbpat%d\\cb%d", ARRAYOFCONST((GetColorIndex(fLastBG), GetColorIndex(fLastBG)))));
		fAttributesChanged = true;
	}
  // text color
	if(ForegroundChanged)
	{
		AddData(Format(L"\\cf%d", ARRAYOFCONST((GetColorIndex(fLastFG)))));
		fAttributesChanged = true;
	}
  // font styles
	for(stop = (TFontStyle) 3 /*# High(TFontStyle) */, AStyle = (TFontStyle) 0 /*# Low(TFontStyle) */; AStyle <= stop; Inc(AStyle))
	{
		if(FontStylesChanged.Contains(AStyle))
		{
			AddData(FontTags[AStyle]);
			fAttributesChanged = true;
		}
	}
	if(fAttributesChanged)
	{
		AddData(L" ");
		fAttributesChanged = false;
	}
}

void __fastcall TSynExporterRTF::FormatBeforeFirstAttribute(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged)
{
	FormatAttributeInit(BackgroundChanged, ForegroundChanged, FontStylesChanged);
}

void __fastcall TSynExporterRTF::FormatNewLine()
{
	AddData(L"\x0d\x0a" L"\\par ");
}

int __fastcall TSynExporterRTF::GetColorIndex(TColor AColor)
{
	int result = 0;
	result = fListColors->IndexOf(((void*) AColor));
	if(result == -1)
		result = fListColors->Add(((void*) AColor));
	return result;
}

String __fastcall TSynExporterRTF::GetFooter()
{
	String result;
	result = L"}";
	return result;
}

String __fastcall TSynExporterRTF::GetFormatName()
{
	String result;
	result = SYNS_ExporterFormatRTF;
	return result;
}

String __fastcall TSynExporterRTF::GetHeader()
{
	String result;
	int i = 0;

	auto GetFontTable = [&]() -> String 
	{
		String result;
		result = String(L"{\\fonttbl{\\f0\\fmodern ") + Font->Name;
		result = result + L";}}\x0d\x0a";
		return result;
	};
	int stop = 0;
	result = String(L"{\\rtf1\\ansi\\ansicpg1252\\uc1\\deff0\\deftab720") + GetFontTable();
  // all the colors
	result = result + L"{\\colortbl";
	for(stop = fListColors->Count - 1, i = 0; i <= stop; i++)
	{
		result = result + ColorToRTF((TColor)(NativeInt)fListColors->Items[i]);
	}
	result = result + L"}\x0d\x0a";
  // title and creator comment
	result = result + L"{\\info{\\comment Generated by the SynEdit RTF " + L"exporter}\x0d\x0a";
	result = result + L"{\\title " + fTitle + L"}}\x0d\x0a";
	if(fUseBackground) /* TODO: use background color */
		result = result + L"\x0d\x0a";
	result = result + Format(L"\\deflang1033\\pard\\plain\\f0\\fs%d ", ARRAYOFCONST((2 * Font->Size)));
	return result;
}

String __fastcall TSynExporterRTF::ReplaceReservedChar(WideChar AChar)
{
	String result;
	result = L"";
	switch(AChar)
	{
		case L'\\':
		result = L"\\\\";
		break;
		case L'{':
		result = L"\\{";
		break;
		case L'}':
		result = L"\\}";
		break;
		default:
		  ;
		break;
	}
	if(AChar > L'\x7f')
	{
		if(AChar <= L'\xff')
			result = String(L"\\'") + LowerCase(IntToHex(int(AChar), 2));
		else

      // SmallInt type-cast is necessary because RTF
      // uses signed 16-Bit Integer for Unicode characters
			result = String(L"\\u") + IntToStr(((short int) AChar)) + L"?";
	}
	return result;
}

TSynEncodings __fastcall TSynExporterRTF::SupportedEncodings()
{
	TSynEncodings result;
	result = Synexportrtf__0;
	return result;
}

bool __fastcall TSynExporterRTF::UseBom()
{
	bool result = false;
	result = false;
	return result;
}


}  // namespace Synexportrtf

