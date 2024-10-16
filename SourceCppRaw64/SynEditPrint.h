/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPrint.pas, released 2000-06-01.

The Initial Author of the Original Code is Morten J. Skovrup.
Portions written by Morten J. Skovrup are copyright 2000 Morten J. Skovrup.
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

$Id: SynEditPrint.pas,v 1.34.2.12 2008/09/23 14:02:08 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
  Wrapping across page boundaries is not supported
-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------
CONTENTS:
  Print controller component.
    Allows setting margins, headers and footers.

  Design time properties:
    Header        : Class property to set properties for headers -
                    see CSynEditHeaderFooter.pas
    Footer        : Class property to set properties for footers -
                    see CSynEditHeaderFooter.pas
    Margins       : Class property to set properties for margins -
                    see CSynEditPrintMargins.pas
    Lines         : The lines that should be printed (see also SynEdit the
                    property below)
    Font          : The font the lines should be printed in (see also SynEdit
                    the property below)
    Title         : A title - can be referenced in headers/footers by using the
                    $TITLE$ macro
    Wrap          : Wrap text to margins
    Highlight     : Highlight text
    Colors        : Print in colors
    LineNumbers   : Print line numbers
    LineOffset    : Value added to linenumbers when printing
    PageOffset    : Value added to pagenumbers when printing
    OnPrintLine   : Fired when a line is printed
    OnPrintStatus : Fired at Beginning, End and when a new page is started
    Highlighter   : The highlighter used for highlighting the text (see also the
                    SynEdit property below)
    LineNumbersInMargin : If true line numbers are printed in the left margin,
                          else left margin is increased by width of line
                          number text.
    SelectedOnly  : Print only the selected Area
  Run-time properties:
    DocTitle    : Used to display the document name in the print queue monitor
    PrinterInfo : Read only. Returns info on printer (used internally)
    PageCount   : Returns the total number of pages;
    SynEdit     : By setting SynEdit to a specific TSynEdit component, the
                  properties Lines, Font and Highlighter are automatically
                  set to the corresponding values of the TSynEdit component
  Run-time methods:
    UpdatePages   : Used internally by the TSynEditPrintPreview component
    PrintToCanvas : Used internally by the TSynEditPrintPreview component
    Print         : Prints the contents of the Lines property
    PrintRange(StartPage,EndPage) : Prints the specified page-range (both inclusive)
-------------------------------------------------------------------------------*/
#ifndef SynEditPrintH
#define SynEditPrintH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Printers.hpp>
#include "SynEdit.h"
#include "SynEditTypes.h"
#include "SynEditPrintTypes.h"
#include "SynEditPrintHeaderFooter.h"
#include "SynEditPrinterInfo.h"
#include "SynEditPrintMargins.h"
#include "SynEditMiscProcs.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "SynEditDelphiInstances.hpp"

namespace Syneditprint
{



/*$M+*/
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

class TPageLine : public System::TObject
{
	#include "SynEditPrint_friends.inc"
public:
	typedef System::TObject inherited;
	int FirstLine;
	__fastcall TPageLine();
};
  //The actual print controller object

class TSynEditPrint : public System::Classes::TComponent
{
private:
	int FCopies;
	Syneditprintheaderfooter::TFooter* FFooter;
	Syneditprintheaderfooter::THeader* FHeader;
	TStrings* FLines;
	Syneditprintmargins::TSynEditPrintMargins* FMargins;
	int FPageCount;
	TFont* FFont;
	String FTitle;
	String FDocTitle;
	Syneditprinterinfo::TSynEditPrinterInfo* FPrinterInfo;
	TList* FPages;
	TCanvas* FCanvas;
	int FCharWidth;
	int FMaxLeftChar;
	bool FWrap;
	Syneditprinttypes::TPrintLineEvent FOnPrintLine;
	Syneditprinttypes::TPrintStatusEvent FOnPrintStatus;
	int FYPos;
	int FLineHeight;
	bool FHighlight;
	bool FColors;
	Synedithighlighter::TSynCustomHighlighter* FHighlighter;
	TFont* FOldFont;
	bool FSynOK;
	bool FLineNumbers;
	int FLineNumber;
	int FLineOffset;
	bool FAbort;
	bool FPrinting;
	TColor FDefaultBG;
	int FPageOffset;
	bool FRangesOK;
	int FMaxWidth;
	int FMaxCol;
	bool FPagesCounted;
	bool FLineNumbersInMargin;
	int FTabWidth;
	TColor fFontColor;
	bool fSelectedOnly;
	bool fSelAvail;
	Synedittypes::TSynSelectionMode fSelMode;
	TBufferCoord fBlockBegin;
	TBufferCoord fBlockEnd;
	Syneditmiscprocs::PIntArray FETODist;
	void __fastcall CalcPages();
	void __fastcall SetLines(TStrings* const Value);
	void __fastcall SetFont(TFont* const Value);
	void __fastcall SetCharWidth(int Value);
	void __fastcall SetMaxLeftChar(int Value);
	void __fastcall PrintPage(int Num);
	void __fastcall WriteLine(const String Text);
	void __fastcall WriteLineNumber();
	void __fastcall HandleWrap(const String Text, int MaxWidth);
	void __fastcall TextOut(const String Text, TList* AList);
	void __fastcall SetHighlighter(Synedithighlighter::TSynCustomHighlighter* const Value);
	void __fastcall RestoreCurrentFont();
	void __fastcall SaveCurrentFont();
	void __fastcall SetPixelsPrInch();
	void __fastcall InitPrint();
	void __fastcall InitRanges();
	int __fastcall GetPageCount();
	void __fastcall SetSynEdit(Synedit::TCustomSynEdit* const Value);
	void __fastcall SetFooter(Syneditprintheaderfooter::TFooter* const Value);
	void __fastcall SetHeader(Syneditprintheaderfooter::THeader* const Value);
	void __fastcall SetMargins(Syneditprintmargins::TSynEditPrintMargins* const Value);
	String __fastcall ClipLineToRect(String S, const TRect& R);
	String __fastcall ExpandAtWideGlyphs(const String S);
protected:
	virtual void __fastcall DefineProperties(TFiler* Filer);
	__property int MaxLeftChar = { read = FMaxLeftChar, write = SetMaxLeftChar };
	__property int CharWidth = { read = FCharWidth, write = SetCharWidth };
	virtual void __fastcall PrintStatus(Syneditprinttypes::TSynPrintStatus Status, int PageNumber, bool& Abort);
	virtual void __fastcall PrintLine(int LineNumber, int PageNumber);
public:
	typedef System::Classes::TComponent inherited;
	#include "SynEditPrint_friends.inc"
	__fastcall TSynEditPrint(TComponent* AOwner);
	virtual __fastcall ~TSynEditPrint();
	void __fastcall UpdatePages(TCanvas* ACanvas);
	void __fastcall PrintToCanvas(TCanvas* ACanvas, int PageNumber);
	void __fastcall Print();
	void __fastcall PrintRange(int StartPage, int EndPage);
	__property Syneditprinterinfo::TSynEditPrinterInfo* PrinterInfo = { read = FPrinterInfo };
	__property int PageCount = { read = GetPageCount };
	__property Synedit::TCustomSynEdit* SynEdit = { write = SetSynEdit };
	void __fastcall LoadFromStream(TStream* AStream);
	void __fastcall SaveToStream(TStream* AStream);
__published:
public:
	__property int Copies = { read = FCopies, write = FCopies };
	__property Syneditprintheaderfooter::THeader* Header = { read = FHeader, write = SetHeader };
	__property Syneditprintheaderfooter::TFooter* Footer = { read = FFooter, write = SetFooter };
	__property Syneditprintmargins::TSynEditPrintMargins* Margins = { read = FMargins, write = SetMargins };
	__property TStrings* Lines = { read = FLines, write = SetLines };
	__property TFont* Font = { read = FFont, write = SetFont };
	__property String Title = { read = FTitle, write = FTitle };
	__property String DocTitle = { read = FDocTitle, write = FDocTitle };
	__property bool Wrap = { read = FWrap, write = FWrap, default = true };
	__property bool Highlight = { read = FHighlight, write = FHighlight, default = true };
	__property bool SelectedOnly = { read = fSelectedOnly, write = fSelectedOnly, default = false };
	__property bool Colors = { read = FColors, write = FColors, default = false };
	__property bool LineNumbers = { read = FLineNumbers, write = FLineNumbers, default = false };
	__property int LineOffset = { read = FLineOffset, write = FLineOffset, default = 0 };
	__property int PageOffset = { read = FPageOffset, write = FPageOffset, default = 0 };
	__property Syneditprinttypes::TPrintLineEvent OnPrintLine = { read = FOnPrintLine, write = FOnPrintLine };
	__property Syneditprinttypes::TPrintStatusEvent OnPrintStatus = { read = FOnPrintStatus, write = FOnPrintStatus };
	__property Synedithighlighter::TSynCustomHighlighter* Highlighter = { read = FHighlighter, write = SetHighlighter };
	__property bool LineNumbersInMargin = { read = FLineNumbersInMargin, write = FLineNumbersInMargin, default = false };
	__property int TabWidth = { read = FTabWidth, write = FTabWidth };
	__property TColor Color = { read = FDefaultBG, write = FDefaultBG };
};


}  // namespace SynEditPrint

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditprint;
#endif

#endif // SynEditPrintH

