/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPrintPreview.pas, released 2000-06-01.

The Initial Author of the Original Code is Morten J. Skovrup.
Portions written by Morten J. Skovrup are copyright 2000 Morten J. Skovrup.
Portions written by Michael Hieke are copyright 2000 Michael Hieke.
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

$Id: SynEditPrintPreview.pas,v 1.18.2.2 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
CONTENTS:
  Print preview component. Allmost identical to code developed by Michael Hieke.
  It is important to call UpdatePreview whenever things change (i.e. just
  before the preview is shown, and when the printer is changed)
-------------------------------------------------------------------------------*/
#ifndef SynEditPrintPreviewH
#define SynEditPrintPreviewH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Themes.hpp>
#include <Winapi.Windows.hpp>
#include <Vcl.Controls.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Forms.hpp>
#include "SynEditPrint.h"
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

namespace Syneditprintpreview
{



/*------------------------------------------------------------------------------*/
/* Common compiler defines                                                      */
/* (remove the dot in front of a define to enable it)                           */
/*------------------------------------------------------------------------------*/

/*$B-,H+*/ // defaults are short evaluation of boolean values and long strings

/*.$DEFINE SYN_DEVELOPMENT_CHECKS*/ // additional tests for debugging
  

/*------------------------------------------------------------------------------*/
/* Pull in all defines from SynEditJedi.inc (must be done after the common      */
/* compiler defines to  work correctly). Use SynEdit-prefix to avoid problems   */
/* with other versions of jedi.inc in the search-path.                          */
/*------------------------------------------------------------------------------*/

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

/*------------------------------------------------------------------------------*/
/*  Please change this to suit your needs (to activate an option remove the dot */
/*  in front of a DEFINE)                                                       */
/*------------------------------------------------------------------------------*/

// "Heredoc" syntax highlighting
// If you enable the following statement and use highlighter(s) that have
// support for "Heredoc" strings as scheme(s) in SynMultiSyn, you must
// implement your own SynMultiSyn OnCustomRange event handler in order to
// properly store Range State information
/*.$DEFINE SYN_HEREDOC*/

// Turn this off if you don't need complex script support, since it is slower
/*.$DEFINE SYN_UNISCRIBE*/

// $Id: SynEdit.inc,v 1.16.2.19 2009/06/14 13:41:44 maelh Exp $


/*$M+*/
//Event raised when page is changed in preview
typedef void __fastcall (__closure *TPreviewPageEvent) (TObject*, int);
enum TSynPreviewScale {pscWholePage,
                       pscPageWidth,
                       pscUserScaled };

class TSynEditPrintPreview : public Vcl::Controls::TCustomControl
{
protected:
	TBorderStyle FBorderStyle;
	Syneditprint::TSynEditPrint* FSynEditPrint;
	TSynPreviewScale FScaleMode;
	int FScalePercent;
        // these are in pixels ( = screen device units)
	TPoint FVirtualSize;
	TPoint FVirtualOffset;
	TPoint FPageSize;
	TPoint FScrollPosition;
	TColor FPageBG;
	int FPageNumber;
	bool FShowScrollHint;
	TPreviewPageEvent FOnPreviewPage;
	TNotifyEvent FOnScaleChange;                                               // JD 2002-01-9
	int FWheelAccumulator;
	void __fastcall SetBorderStyle(TBorderStyle Value);
	void __fastcall SetPageBG(TColor Value);
	void __fastcall SetSynEditPrint(Syneditprint::TSynEditPrint* Value);
	void __fastcall SetScaleMode(TSynPreviewScale Value);
	void __fastcall SetScalePercent(int Value);
private:
	HIDESBASE MESSAGE void __fastcall WMEraseBkgnd(TWMEraseBkgnd& Msg)/*# WM_ERASEBKGND */;
	HIDESBASE MESSAGE void __fastcall WMHScroll(TWMHScroll& Msg)/*# WM_HSCROLL */;
	HIDESBASE MESSAGE void __fastcall WMSize(TWMSize& Msg)/*# WM_SIZE */;
	HIDESBASE MESSAGE void __fastcall WMVScroll(TWMVScroll& Msg)/*# WM_VSCROLL */;
	HIDESBASE MESSAGE void __fastcall WMMouseWheel(TWMMouseWheel& Message)/*# WM_MOUSEWHEEL */;
	void __fastcall PaintPaper();
	int __fastcall GetPageCount();
protected:
	virtual void __fastcall CreateParams(TCreateParams& Params);
	int __fastcall GetPageHeightFromWidth(int AWidth);
	int __fastcall GetPageHeight100Percent();
	int __fastcall GetPageWidthFromHeight(int AHeight);
	int __fastcall GetPageWidth100Percent();
	virtual void __fastcall Notification(TComponent* AComponent, TOperation Operation);
	void __fastcall ScrollHorzFor(int Value);
	virtual void __fastcall ScrollHorzTo(int Value);
	void __fastcall ScrollVertFor(int Value);
	virtual void __fastcall ScrollVertTo(int Value);
	virtual void __fastcall UpdateScrollBars();
	virtual void __fastcall SizeChanged();
public:
	typedef Vcl::Controls::TCustomControl inherited;
	#include "SynEditPrintPreview_friends.inc"
	__fastcall TSynEditPrintPreview(TComponent* AOwner);
	virtual void __fastcall Paint();
	void __fastcall UpdatePreview();
	void __fastcall NextPage();
	void __fastcall PreviousPage();
	void __fastcall FirstPage();
	void __fastcall LastPage();
	void __fastcall Print();
	__property int PageNumber = { read = FPageNumber };
	__property int PageCount = { read = GetPageCount };
__published:
	__property  Align = { default = /*# alClient */ 5 };
	__property TBorderStyle BorderStyle = { read = FBorderStyle, write = SetBorderStyle, default = /*# bsSingle */ 1 };
	__property  Color = { default = clAppWorkSpace };
	__property  Cursor;
	__property TColor PageBGColor = { read = FPageBG, write = SetPageBG, default = clWhite };
	__property  PopupMenu;                                                         // JD 2002-01-9
	__property Syneditprint::TSynEditPrint* SynEditPrint = { read = FSynEditPrint, write = SetSynEditPrint };
	__property TSynPreviewScale ScaleMode = { read = FScaleMode, write = SetScaleMode, default = /*# pscUserScaled */ 2 };
	__property int ScalePercent = { read = FScalePercent, write = SetScalePercent, default = 100 };
	__property  Visible = { default = true };
	__property bool ShowScrollHint = { read = FShowScrollHint, write = FShowScrollHint, default = true };
	__property  OnClick;
	__property  OnMouseDown;
	__property  OnMouseUp;
	__property TPreviewPageEvent OnPreviewPage = { read = FOnPreviewPage, write = FOnPreviewPage };
	__property TNotifyEvent OnScaleChange = { read = FOnScaleChange, write = FOnScaleChange };                    // JD 2002-01-9
                                                     // JD 2002-01-9
protected:
	BEGIN_MESSAGE_MAP
	  VCL_MESSAGE_HANDLER(WM_ERASEBKGND, TWMEraseBkgnd, WMEraseBkgnd)
	  VCL_MESSAGE_HANDLER(WM_HSCROLL, TWMHScroll, WMHScroll)
	  VCL_MESSAGE_HANDLER(WM_MOUSEWHEEL, TWMMouseWheel, WMMouseWheel)
	  VCL_MESSAGE_HANDLER(WM_SIZE, TWMSize, WMSize)
	  VCL_MESSAGE_HANDLER(WM_VSCROLL, TWMVScroll, WMVScroll)
	END_MESSAGE_MAP(Vcl::Controls::TCustomControl)
public:
	__fastcall TSynEditPrintPreview(HWND ParentWindow);
};


}  // namespace SynEditPrintPreview

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditprintpreview;
#endif

#endif // SynEditPrintPreviewH

