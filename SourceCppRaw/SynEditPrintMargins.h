#ifndef SynEditPrintMarginsH
#define SynEditPrintMarginsH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditPrintTypes.h"
#include "SynEditPrinterInfo.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

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
/*$M+*/
  //Margins class - sorting out dimensions of printable area

class TSynEditPrintMargins : public System::Classes::TPersistent
{
private:                      // Distance from left edge of paper to text
                     // Distance from right edge of paper to text
                       // Distance from top edge of paper to top of text
	double FLeft;
	double FRight;
	double FTop;
	double FBottom;            // Distance from bottom edge of paper to bottom of text
                    // Distance from top edge of paper to line below header
	double FHeader;
	double FFooter;            // Distance from bottom edge of paper to line above footer
	double FLeftHFTextIndent;  // Distance from left margin to first left-aligned character
                                // in header or footer
	double FRightHFTextIndent; // Distance from right margin to last right-aligned character
                                // in header or footer
	double FHFInternalMargin;  // Internal margin between top-line and text in header and
                                // footer AND between bottom-line and text in header and
                                // footer
	double fGutter;            // Binding gutter - added to right margin (or left if 2-sided)
	bool FMirrorMargins;    // Set if margins should be mirrored (i.e. when printing
                                // 2-sided)
	Syneditprinttypes::TUnitSystem FUnitSystem;   // The units used to specify sizes in.
                                // Internally is allways used mm
	double __fastcall ConvertTo(double Value);
	double __fastcall ConvertFrom(double Value);
	double __fastcall GetBottom();
	double __fastcall GetFooter();
	double __fastcall GetGutter();
	double __fastcall GetHeader();
	double __fastcall GetLeft();
	double __fastcall GetRight();
	double __fastcall GetTop();
	double __fastcall GetLeftHFTextIndent();
	double __fastcall GetRightHFTextIndent();
	double __fastcall GetHFInternalMargin();
	void __fastcall SetBottom(double Value);
	void __fastcall SetFooter(double Value);
	void __fastcall SetGutter(double Value);
	void __fastcall SetHeader(double Value);
	void __fastcall SetLeft(double Value);
	void __fastcall SetRight(double Value);
	void __fastcall SetTop(double Value);
	void __fastcall SetLeftHFTextIndent(double Value);
	void __fastcall SetRightHFTextIndent(double Value);
	void __fastcall SetHFInternalMargin(double Value);
public:
    /* When initpage has been called, the following values will reflect the
      margins in paper units. Note that all values are calculated from
      left or top of paper (i.e. PRight is distance from left margin) */  // Left position of text in device units (pixels) - this is the left
            // margin minus the left unprintable distance (+ gutter)
 // Right position of text in device units (pixels) - calculated form
            // left
   // Top position of text in device units (pixels) - this is the top
            // margin minus the top unprintable distance
	int PLeft;
	int PRight;
	int PTop;
	int PBottom; // Bottom position of text in device units (pixels) -
                      // calculated form top
          // Header in device units (pixels)
	int PHeader;
	int PFooter; // Footer in device units (pixels) - calculated from top
	int PLeftHFTextIndent;  // Left position of text in header and footer in device
                                 // units (pixels). Calculated as Left margin + LeftHFTextIndent
	int PRightHFTextIndent; // Right position of text in header and footer in device
                                 // units (pixels). Calculated from left
	int PHFInternalMargin;  // Internal margin in device units (pixels)
	int PGutter; // Binding gutter in device units (pixels)
	typedef System::Classes::TPersistent inherited;	
	#include "SynEditPrintMargins_friends.inc"
	__fastcall TSynEditPrintMargins();
	void __fastcall InitPage(Vcl::Graphics::TCanvas* ACanvas, int PageNum, Syneditprinterinfo::TSynEditPrinterInfo* PrinterInfo, bool LineNumbers, bool LineNumbersInMargin, int MaxLineNum);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall LoadFromStream(System::Classes::TStream* AStream);
	void __fastcall SaveToStream(System::Classes::TStream* AStream);
__published:
	__property TUnitSystem UnitSystem = { read = FUnitSystem, write = FUnitSystem, default = /*# usMM */ 0 };
	__property double Left = { read = GetLeft, write = SetLeft };
	__property double Right = { read = GetRight, write = SetRight };
	__property double Top = { read = GetTop, write = SetTop };
	__property double Bottom = { read = GetBottom, write = SetBottom };
	__property double Header = { read = GetHeader, write = SetHeader };
	__property double Footer = { read = GetFooter, write = SetFooter };
	__property double LeftHFTextIndent = { read = GetLeftHFTextIndent, write = SetLeftHFTextIndent };
	__property double RightHFTextIndent = { read = GetRightHFTextIndent, write = SetRightHFTextIndent };
	__property double HFInternalMargin = { read = GetHFInternalMargin, write = SetHFInternalMargin };
	__property double Gutter = { read = GetGutter, write = SetGutter };
	__property bool MirrorMargins = { read = FMirrorMargins, write = FMirrorMargins };
};


}  // namespace SynEditPrintMargins

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditprintmargins;
#endif

#endif // SynEditPrintMarginsH

