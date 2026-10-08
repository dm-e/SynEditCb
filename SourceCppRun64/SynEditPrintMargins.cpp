#include <vcl.h>
#pragma hdrstop

#include "SynEditPrintMargins.h"
#include "d2c_sysinterface.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditprinterinfo;
using namespace Syneditprinttypes;
using namespace System;
using namespace System::Classes;

namespace Syneditprintmargins
{



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPrintMargins.pas, released 2000-06-01.

The Initial Author of the Original Code is Morten J. Skovrup.
Portions written by Morten J. Skovrup are copyright 2000 Morten J. Skovrup.
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

$Id: SynEditPrintMargins.pas,v 1.5.2.2 2006/05/21 11:59:34 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
CONTENTS:
  Class handling all sizes involded when printing.

  Design-time properties
    UnitSystem : The units used to specify sizes in. Internally is allways used mm.
    Left       : Distance from left edge of paper to text.
    Right      : Distance from right edge of paper to text.
    Top        : Distance from top edge of paper to top of text.
    Bottom     : Distance from bottom edge of paper to bottom of text.
    Gutter     : Binding gutter - added to right margin (or left if 2-sided)
    Header     : Distance from top edge of paper to line below header.
    Footer     : Distance from bottom edge of paper to line above footer.
    LeftHFTextIndent  : Distance from left margin to first left-aligned character
                        in header or footer
    RightHFTextIndent : Distance from right margin to last right-aligned character
                        in header or footer
    HFInternalMargin  : Internal margin between top-line and text in header and
                        footer AND between bottom-line and text in header and
                        footer.
    MirrorMargins     : Set if margins should be mirrored (i.e. when printing
                        2-sided).

  Run-time properties
    PLeft   : Left position of text in device units (pixels) - this is the left
              margin minus the left unprintable distance (+ gutter).
    PRight  : Right position of text in device units (pixels) - calculated form
              left.
    PTop    : Top position of text in device units (pixels)  - this is the top
              margin minus the top unprintable distance.
    PBottom : Bottom position of text in device units (pixels) - calculated form
              top.
    PGutter : Binding gutter in device units (pixels)
    PHeader : Header in device units (pixels)
    PFooter : Footer in device units (pixels) - calculated from top
    PLeftHFTextIndent  : Left position of text in header and footer in device
                         units (pixels). Calculated as Left margin + LeftHFTextIndent
    PRightHFTextIndent : Right position of text in header and footer in device
                         units (pixels). Calculated from left
    PHFInternalMargin  : Internal margin in device units (pixels).

  Run-time methods
    InitPage : Called by TSynEditPrint class to initialize margins.
    Assign   : Assign values from another TSynEditPrintMargins object.

-------------------------------------------------------------------------------*/


/* TSynEditPrintMargins */
const double mmPrInch = 25.4;
const int mmPrCm = 10;

__fastcall TSynEditPrintMargins::TSynEditPrintMargins()
 : FLeft(static_cast<double>(DefLeft)),
			FRight(static_cast<double>(DefRight)),
			FTop(static_cast<double>(DefTop)),
			FBottom(static_cast<double>(DefBottom)),
			FHeader(static_cast<double>(DefHeader)),
			FFooter(static_cast<double>(DefFooter)),
			FLeftHFTextIndent(static_cast<double>(DefLeftHFTextIndent)),
			FRightHFTextIndent(static_cast<double>(DefRightHFTextIndent)),
			FHFInternalMargin(DefHFInternalMargin),
			FGutter(static_cast<double>(DefGutter)),
			FMirrorMargins(false),
			FUnitSystem(usMM),
			PLeft(0),
			PRight(0),
			PTop(0),
			PBottom(0),
			PHeader(0),
			PFooter(0),
			PLeftHFTextIndent(0),
			PRightHFTextIndent(0),
			PHFInternalMargin(0),
			PGutter(0)
{
	// inherited;
	FUnitSystem = usMM;
}
/*Convert Value to mm*/

double __fastcall TSynEditPrintMargins::ConvertTo(double Value)
{
	double result = 0.0;
	switch(FUnitSystem)
	{
		case usCM:
		result = Value * mmPrCm;
		break;
		case usInch:
		result = Value * mmPrInch;
		break;
		case muThousandthsOfInches:
		result = mmPrInch * Value / 1000.0;
		break;
		default:
		result = Value;
		break;
	}
	return result;
}
/*Convert from mm to selected UnitSystem*/

double __fastcall TSynEditPrintMargins::ConvertFrom(double Value)
{
	double result = 0.0;
	switch(FUnitSystem)
	{
		case usCM:
		result = Value / mmPrCm;
		break;
		case usInch:
		result = Value / mmPrInch;
		break;
		case muThousandthsOfInches:
		result = 1000.0 * Value / mmPrInch;
		break;
		default:
		result = Value;
		break;
	}
	return result;
}

double __fastcall TSynEditPrintMargins::GetBottom()
{
	double result = 0.0;
	result = ConvertFrom(FBottom);
	return result;
}

double __fastcall TSynEditPrintMargins::GetFooter()
{
	double result = 0.0;
	result = ConvertFrom(FFooter);
	return result;
}

double __fastcall TSynEditPrintMargins::GetGutter()
{
	double result = 0.0;
	result = ConvertFrom(FGutter);
	return result;
}

double __fastcall TSynEditPrintMargins::GetHeader()
{
	double result = 0.0;
	result = ConvertFrom(FHeader);
	return result;
}

double __fastcall TSynEditPrintMargins::GetLeft()
{
	double result = 0.0;
	result = ConvertFrom(FLeft);
	return result;
}

double __fastcall TSynEditPrintMargins::GetRight()
{
	double result = 0.0;
	result = ConvertFrom(FRight);
	return result;
}

double __fastcall TSynEditPrintMargins::GetTop()
{
	double result = 0.0;
	result = ConvertFrom(FTop);
	return result;
}

double __fastcall TSynEditPrintMargins::GetLeftHFTextIndent()
{
	double result = 0.0;
	result = ConvertFrom(FLeftHFTextIndent);
	return result;
}

double __fastcall TSynEditPrintMargins::GetRightHFTextIndent()
{
	double result = 0.0;
	result = ConvertFrom(FRightHFTextIndent);
	return result;
}

double __fastcall TSynEditPrintMargins::GetHFInternalMargin()
{
	double result = 0.0;
	result = ConvertFrom(FHFInternalMargin);
	return result;
}

void __fastcall TSynEditPrintMargins::SetBottom(double Value)
{
	FBottom = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetFooter(double Value)
{
	FFooter = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetGutter(double Value)
{
	FGutter = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetHeader(double Value)
{
	FHeader = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetLeft(double Value)
{
	FLeft = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetRight(double Value)
{
	FRight = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetTop(double Value)
{
	FTop = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetLeftHFTextIndent(double Value)
{
	FLeftHFTextIndent = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetRightHFTextIndent(double Value)
{
	FRightHFTextIndent = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetHFInternalMargin(double Value)
{
	FHFInternalMargin = ConvertTo(Value);
}

// -----------------------------------------------------------------------------
// Called by TSynEditPrint class to initialize margins

//Calculate the P... values

void __fastcall TSynEditPrintMargins::InitPage(TCanvas* ACanvas, int PageNum, TSynEditPrinterInfo* PrinterInfo, bool LineNumbers, bool LineNumbersInMargin, int MaxLineNum)
{
	if(FMirrorMargins && ((PageNum % 2) == 0))
	{
		PLeft = PrinterInfo->PixFromLeft(FRight);
		PRight = PrinterInfo->PrintableWidth - PrinterInfo->PixFromRight(FLeft + FGutter);
	}
	else
	{
		PLeft = PrinterInfo->PixFromLeft(FLeft + FGutter);
		PRight = PrinterInfo->PrintableWidth - PrinterInfo->PixFromRight(FRight);
	}
	if(LineNumbers && (!LineNumbersInMargin))
		PLeft = PLeft + ACanvas->TextWidth(IntToStr(MaxLineNum) + L": ");
	PTop = PrinterInfo->PixFromTop(FTop);
	PBottom = PrinterInfo->PrintableHeight - PrinterInfo->PixFromBottom(FBottom);
	PHeader = PrinterInfo->PixFromTop(FHeader);
	PFooter = PrinterInfo->PrintableHeight - PrinterInfo->PixFromBottom(FFooter);
	PHFInternalMargin = static_cast<int>(Round(PrinterInfo->YPixPrmm * FHFInternalMargin));
	PGutter = static_cast<int>(Round(PrinterInfo->XPixPrmm * FGutter));
	PRightHFTextIndent = static_cast<int>(PRight - Round(PrinterInfo->XPixPrmm * FRightHFTextIndent));
	PLeftHFTextIndent = static_cast<int>(PLeft + Round(PrinterInfo->XPixPrmm * FLeftHFTextIndent));
}

// -----------------------------------------------------------------------------
// Assign values from another TSynEditPrintMargins object

void __fastcall TSynEditPrintMargins::Assign(TPersistent* Source)
{
	TSynEditPrintMargins* Src = nullptr;
	if((Source != nullptr) && (ObjectIs(Source, TSynEditPrintMargins*)))
	{
		Src = ((TSynEditPrintMargins*) Source);
		FLeft = Src->FLeft;
		FRight = Src->FRight;
		FTop = Src->FTop;
		FBottom = Src->FBottom;
		FHeader = Src->FHeader;
		FFooter = Src->FFooter;
		FLeftHFTextIndent = Src->FLeftHFTextIndent;
		FRightHFTextIndent = Src->FRightHFTextIndent;
		FHFInternalMargin = Src->FHFInternalMargin;
		FGutter = Src->FGutter;
		FMirrorMargins = Src->FMirrorMargins;
		FUnitSystem = Src->FUnitSystem;
	}
	else
	inherited::Assign(Source);
}

void __fastcall TSynEditPrintMargins::LoadFromStream(TStream* AStream)
{

  // we read all our values in MM
	/*# with AStream do */
	{
		auto with0 = AStream;
		with0->Read(&FUnitSystem, static_cast<NativeInt>(sizeof(FUnitSystem)));
		with0->Read(&FLeft, static_cast<NativeInt>(sizeof(FLeft)));
		with0->Read(&FRight, static_cast<NativeInt>(sizeof(FRight)));
		with0->Read(&FTop, static_cast<NativeInt>(sizeof(FTop)));
		with0->Read(&FBottom, static_cast<NativeInt>(sizeof(FBottom)));
		with0->Read(&FHeader, static_cast<NativeInt>(sizeof(FHeader)));
		with0->Read(&FFooter, static_cast<NativeInt>(sizeof(FFooter)));
		with0->Read(&FLeftHFTextIndent, static_cast<NativeInt>(sizeof(FLeftHFTextIndent)));
		with0->Read(&FRightHFTextIndent, static_cast<NativeInt>(sizeof(FRightHFTextIndent)));
		with0->Read(&FHFInternalMargin, static_cast<NativeInt>(sizeof(FHFInternalMargin)));
		with0->Read(&FGutter, static_cast<NativeInt>(sizeof(FGutter)));
		with0->Read(&FMirrorMargins, static_cast<NativeInt>(sizeof(FMirrorMargins)));
	}
}

void __fastcall TSynEditPrintMargins::SaveToStream(TStream* AStream)
{

  // we always write our values in MM
	/*# with AStream do */
	{
		auto with0 = AStream;
		with0->Write(&FUnitSystem, static_cast<NativeInt>(sizeof(FUnitSystem)));
		with0->Write(&FLeft, static_cast<NativeInt>(sizeof(FLeft)));
		with0->Write(&FRight, static_cast<NativeInt>(sizeof(FRight)));
		with0->Write(&FTop, static_cast<NativeInt>(sizeof(FTop)));
		with0->Write(&FBottom, static_cast<NativeInt>(sizeof(FBottom)));
		with0->Write(&FHeader, static_cast<NativeInt>(sizeof(FHeader)));
		with0->Write(&FFooter, static_cast<NativeInt>(sizeof(FFooter)));
		with0->Write(&FLeftHFTextIndent, static_cast<NativeInt>(sizeof(FLeftHFTextIndent)));
		with0->Write(&FRightHFTextIndent, static_cast<NativeInt>(sizeof(FRightHFTextIndent)));
		with0->Write(&FHFInternalMargin, static_cast<NativeInt>(sizeof(FHFInternalMargin)));
		with0->Write(&FGutter, static_cast<NativeInt>(sizeof(FGutter)));
		with0->Write(&FMirrorMargins, static_cast<NativeInt>(sizeof(FMirrorMargins)));
	}
}


}  // namespace Syneditprintmargins

