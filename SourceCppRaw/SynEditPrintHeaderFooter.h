/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPrintHeaderFooter.pas, released 2000-06-01.

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

$Id: SynEditPrintHeaderFooter.pas,v 1.10.2.7 2008/09/23 14:02:08 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
CONTENTS:
  Classes handling info about headers and footers.

  THeaderFooterItem:
    Class handling an item in a header or footer. An item has a text,Font,
    LineNumber and Alignment (i.e. two items can be on the same line but have
    different fonts). Used internally.

  THeaderFooter:
    Collection of THeaderFooterItem's
    Design-time properties:
      FrameTypes : Frame around header or footer - can be any combination of:
                   ftLine   : Line under header or line above footer
                   ftBox    : Box around header or footer
                   ftShaded : Filled box (without frame) around header or footer.
      ShadedColor : Fill color if ftShaded is in FrameTypes
      LineColor   : Color of line or box if ftLine or ftBox is in FrameTypes
      DefaultFont : Default font for THeaderFooterItem's. This can be used to
                    set the header/footer font once for all items.
      RomanNumbers : Print page numbers as Roman numbers.
      MirrorPosition : Mirror position of left/right aligned THeaderFooterItem's
                       Can be used when printing 2-sided.
    Run-time methods:
      function Add(Text: string; Font: TFont;
                   Alignment: TAlignment;
                   LineNumber: Integer) : Integer;
        Add a THeaderFooterItem. If Font is nil or not specified then DefaultFont
        is used. Returned value is the index of the added item.
        The Text parameter can contain the following macros:
          $PAGECOUNT$  : Print total number of pages
          $PAGENUM$    : Print current page number
          $TITLE$      : Print the title
          $DATE$       : Print the date
          $TIME$       : Print the time
          $DATETIME$   : Print the date and then the time
          $TIMEDATE$   : Print the time and then the date
      procedure Delete(Index : Integer);
        Delete THeaderFooterItem with index Index.
      procedure Clear;
        Clear all THeaderFooterItems.
      function Count : Integer;
        Returns number of THeaderFooterItems.
      function Get(Index : Integer) : THeaderFooterItem;
        Returns THeaderFooterItem with Index.
      procedure SetPixPrInch(Value : Integer);
        Corrects the PixPerInch property of fonts. Used internally by
        TSynEditPrint.
      procedure InitPrint(ACanvas : TCanvas;NumPages : Integer; Title : string;
                          Margins : TSynEditPrintMargins);
        Prepares the header or footer for printing. Used internally by
        TSynEditPrint.
      procedure Print(ACanvas : TCanvas; PageNum : Integer = 0);
        Prints the header or footer. Used internally by TSynEditPrint.

-------------------------------------------------------------------------------*/
#ifndef SynEditPrintHeaderFooterH
#define SynEditPrintHeaderFooterH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include "SynEditPrintTypes.h"
#include "SynEditPrintMargins.h"
#include "SynUnicode.h"
#include <Vcl.Graphics.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

namespace Syneditprintheaderfooter
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPrintHeaderFooter.pas, released 2000-06-01.

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

$Id: SynEditPrintHeaderFooter.pas,v 1.10.2.7 2008/09/23 14:02:08 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
CONTENTS:
  Classes handling info about headers and footers.

  THeaderFooterItem:
    Class handling an item in a header or footer. An item has a text,Font,
    LineNumber and Alignment (i.e. two items can be on the same line but have
    different fonts). Used internally.

  THeaderFooter:
    Collection of THeaderFooterItem's
    Design-time properties:
      FrameTypes : Frame around header or footer - can be any combination of:
                   ftLine   : Line under header or line above footer
                   ftBox    : Box around header or footer
                   ftShaded : Filled box (without frame) around header or footer.
      ShadedColor : Fill color if ftShaded is in FrameTypes
      LineColor   : Color of line or box if ftLine or ftBox is in FrameTypes
      DefaultFont : Default font for THeaderFooterItem's. This can be used to
                    set the header/footer font once for all items.
      RomanNumbers : Print page numbers as Roman numbers.
      MirrorPosition : Mirror position of left/right aligned THeaderFooterItem's
                       Can be used when printing 2-sided.
    Run-time methods:
      function Add(Text: string; Font: TFont;
                   Alignment: TAlignment;
                   LineNumber: Integer) : Integer;
        Add a THeaderFooterItem. If Font is nil or not specified then DefaultFont
        is used. Returned value is the index of the added item.
        The Text parameter can contain the following macros:
          $PAGECOUNT$  : Print total number of pages
          $PAGENUM$    : Print current page number
          $TITLE$      : Print the title
          $DATE$       : Print the date
          $TIME$       : Print the time
          $DATETIME$   : Print the date and then the time
          $TIMEDATE$   : Print the time and then the date
      procedure Delete(Index : Integer);
        Delete THeaderFooterItem with index Index.
      procedure Clear;
        Clear all THeaderFooterItems.
      function Count : Integer;
        Returns number of THeaderFooterItems.
      function Get(Index : Integer) : THeaderFooterItem;
        Returns THeaderFooterItem with Index.
      procedure SetPixPrInch(Value : Integer);
        Corrects the PixPerInch property of fonts. Used internally by
        TSynEditPrint.
      procedure InitPrint(ACanvas : TCanvas;NumPages : Integer; Title : string;
                          Margins : TSynEditPrintMargins);
        Prepares the header or footer for printing. Used internally by
        TSynEditPrint.
      procedure Print(ACanvas : TCanvas; PageNum : Integer = 0);
        Prints the header or footer. Used internally by TSynEditPrint.

-------------------------------------------------------------------------------*/
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

  //An item in a header or footer. An item has a text,Font,LineNumber and
  //Alignment (i.e. two items can be on the same line but have different
  //fonts).

class THeaderFooterItem : public System::TObject
{
	#include "SynEditPrintHeaderFooter_friends.inc"
public:
	typedef System::TObject inherited;
private:
	String FText;
	TFont* FFont;
	int FLineNumber;
	TAlignment FAlignment;
        /*Used to store the original Index when the item was added - the index
         might change when the list is sorted*/
	int FIndex;
	String __fastcall GetAsString();
	void __fastcall SetAsString(const String Value);
	void __fastcall SetFont(TFont* const Value);
public:
	__fastcall THeaderFooterItem();
	virtual __fastcall ~THeaderFooterItem();
	String __fastcall GetText(int NumPages, int PageNum, bool Roman, String Title, String ATime, String ADate);
	void __fastcall LoadFromStream(TStream* AStream);
	void __fastcall SaveToStream(TStream* AStream);
	__property TAlignment Alignment = { read = FAlignment, write = FAlignment };
	__property String AsString = { read = GetAsString, write = SetAsString };
	__property TFont* Font = { read = FFont, write = SetFont };
	__property int LineNumber = { read = FLineNumber, write = FLineNumber };
	__property String Text = { read = FText, write = FText };
};
enum THeaderFooterType {hftHeader,
                        hftFooter };


  //Used internally to calculate line height and font-base-line for header and
  //footer

class TLineInfo : public System::TObject
{
	#include "SynEditPrintHeaderFooter_friends.inc"
public:
	typedef System::TObject inherited;
	int LineHeight;
	int MaxBaseDist;
	__fastcall TLineInfo();
};

  //The header/footer class

class THeaderFooter : public System::Classes::TPersistent
{
private:
	THeaderFooterType FType; // Indicates if header or footer
	Syneditprinttypes::TFrameTypes FFrameTypes;
	TColor FShadedColor;
	TColor FLineColor;
	TList* FItems;
	TFont* FDefaultFont;
	String FDate;
	String FTime;
	int FNumPages;
	String FTitle;
	Syneditprintmargins::TSynEditPrintMargins* FMargins;
	int FFrameHeight;
	TPen* FOldPen;
	TBrush* FOldBrush;
	TFont* FOldFont;
	bool FRomanNumbers;
	TList* FLineInfo;
	int FLineCount;
	bool FMirrorPosition;
	void __fastcall SetDefaultFont(TFont* const Value);
	void __fastcall DrawFrame(TCanvas* ACanvas);
	void __fastcall CalcHeight(TCanvas* ACanvas);
	void __fastcall SaveFontPenBrush(TCanvas* ACanvas);
	void __fastcall RestoreFontPenBrush(TCanvas* ACanvas);
	String __fastcall GetAsString();
	void __fastcall SetAsString(const String Value);
public:
	typedef System::Classes::TPersistent inherited;
	#include "SynEditPrintHeaderFooter_friends.inc"
	__fastcall THeaderFooter();
	virtual __fastcall ~THeaderFooter();
	int __fastcall Add(String Text, TFont* Font, TAlignment Alignment, int LineNumber);
	void __fastcall Delete(int Index);
	void __fastcall Clear();
	int __fastcall Count();
	THeaderFooterItem* __fastcall Get(int Index);
	void __fastcall SetPixPrInch(int Value);
	void __fastcall InitPrint(TCanvas* ACanvas, int NumPages, String Title, Syneditprintmargins::TSynEditPrintMargins* Margins);
	void __fastcall Print(TCanvas* ACanvas, int PageNum);
	virtual void __fastcall Assign(TPersistent* Source);
	void __fastcall FixLines();
	__property String AsString = { read = GetAsString, write = SetAsString };
	void __fastcall LoadFromStream(TStream* AStream);
	void __fastcall SaveToStream(TStream* AStream);
__published:
	__property Syneditprinttypes::TFrameTypes FrameTypes = { read = FFrameTypes, write = FFrameTypes, default = /*# ftLine */ 0 };
	__property TColor ShadedColor = { read = FShadedColor, write = FShadedColor, default = clSilver };
	__property TColor LineColor = { read = FLineColor, write = FLineColor, default = clBlack };
	__property TFont* DefaultFont = { read = FDefaultFont, write = SetDefaultFont };
	__property bool RomanNumbers = { read = FRomanNumbers, write = FRomanNumbers, default = false };
	__property bool MirrorPosition = { read = FMirrorPosition, write = FMirrorPosition, default = false };
};

  //The header and footer - does nothing but set the value of FType in
  //THeaderFooter

class THeader : public THeaderFooter
{
public:
	typedef THeaderFooter inherited;
	#include "SynEditPrintHeaderFooter_friends.inc"
	__fastcall THeader();
};

class TFooter : public THeaderFooter
{
public:
	typedef THeaderFooter inherited;
	#include "SynEditPrintHeaderFooter_friends.inc"
	__fastcall TFooter();
};


}  // namespace SynEditPrintHeaderFooter

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditprintheaderfooter;
#endif

#endif // SynEditPrintHeaderFooterH

