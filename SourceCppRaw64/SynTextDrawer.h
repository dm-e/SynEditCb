/*==============================================================================
  Content:  TheTextDrawer, a helper class for drawing of
            fixed-pitched font characters
 ==============================================================================
  The contents of this file are subject to the Mozilla Public License Ver. 1.0
  (the "License"); you may not use this file except in compliance with the
  License. You may obtain a copy of the License at http://www.mozilla.org/MPL/

  Software distributed under the License is distributed on an "AS IS" basis,
  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
  the specific language governing rights and limitations under the License.
 ==============================================================================
  The Original Code is HANAI Tohru's private delphi library.
 ==============================================================================
  The Initial Developer of the Original Code is HANAI Tohru (Japan)
  Portions created by HANAI Tohru are Copyright (C) 1999.
  All Rights Reserved.
 ==============================================================================
  Contributor(s):   HANAI Tohru
  Unicode translation by Maël Hörz.
 ==============================================================================
  History:  01/19/1999  HANAI Tohru
                        Initial Version
            02/13/1999  HANAI Tohru
                        Changed default intercharacter spacing
            09/09/1999  HANAI Tohru
                        Redesigned all. Simplified interfaces.
                        When drawing text now it uses TextOut + SetTextCharacter-
                        Extra insted ExtTextOut since ExtTextOut has a little
                        heavy behavior.
            09/10/1999  HANAI Tohru
                        Added code to call ExtTextOut because there is a problem
                        when TextOut called with italicized raster type font.
                        After this changing, ExtTextOut is called without the
                        last parameter `lpDx' and be with SetTextCharacterExtra.
                        This pair performs faster than with `lpDx'.
            09/14/1999  HANAI Tohru
                        Changed code for saving/restoring DC
            09/15/1999  HANAI Tohru
                        Added X/Y parameters to ExtTextOut.
            09/16/1999  HANAI Tohru
                        Redesigned for multi-bytes character drawing.
            09/19/1999  HANAI Tohru
                        Since TheTextDrawer grew fat it was split into three
                        classes - TheFontStock, TheTextDrawer and TheTextDrawerEx.
                        Currently it should avoid TheTextDrawer because it is
                        slower than TheTextDrawer.
            09/25/1999  HANAI Tohru
                        Added internally definition of LeadBytes for Delphi 2
            10/01/1999  HANAI Tohru
                        To save font resources, now all fonts data are shared
                        among all of TheFontStock instances. With this changing,
                        there added a new class `TheFontsInfoManager' to manage
                        those shared data.
            10/09/1999  HANAI Tohru
                        Added BaseStyle property to TheFontFont class.
 ==============================================================================*/

// $Id: SynTextDrawer.pas,v 1.6.2.17 2008/09/17 13:59:12 maelh Exp $

// SynEdit note: The name had to be changed to get SynEdit to install 
//   together with mwEdit into the same Delphi installation
#ifndef SynTextDrawerH
#define SynTextDrawerH

#include <System.hpp>
#include "d2c_system.h"

#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Math.hpp>

namespace Syntextdrawer
{

/*==============================================================================
  Content:  TheTextDrawer, a helper class for drawing of
            fixed-pitched font characters
 ==============================================================================
  The contents of this file are subject to the Mozilla Public License Ver. 1.0
  (the "License"); you may not use this file except in compliance with the
  License. You may obtain a copy of the License at http://www.mozilla.org/MPL/

  Software distributed under the License is distributed on an "AS IS" basis,
  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
  the specific language governing rights and limitations under the License.
 ==============================================================================
  The Original Code is HANAI Tohru's private delphi library.
 ==============================================================================
  The Initial Developer of the Original Code is HANAI Tohru (Japan)
  Portions created by HANAI Tohru are Copyright (C) 1999.
  All Rights Reserved.
 ==============================================================================
  Contributor(s):   HANAI Tohru
  Unicode translation by Maël Hörz.
 ==============================================================================
  History:  01/19/1999  HANAI Tohru
                        Initial Version
            02/13/1999  HANAI Tohru
                        Changed default intercharacter spacing
            09/09/1999  HANAI Tohru
                        Redesigned all. Simplified interfaces.
                        When drawing text now it uses TextOut + SetTextCharacter-
                        Extra insted ExtTextOut since ExtTextOut has a little
                        heavy behavior.
            09/10/1999  HANAI Tohru
                        Added code to call ExtTextOut because there is a problem
                        when TextOut called with italicized raster type font.
                        After this changing, ExtTextOut is called without the
                        last parameter `lpDx' and be with SetTextCharacterExtra.
                        This pair performs faster than with `lpDx'.
            09/14/1999  HANAI Tohru
                        Changed code for saving/restoring DC
            09/15/1999  HANAI Tohru
                        Added X/Y parameters to ExtTextOut.
            09/16/1999  HANAI Tohru
                        Redesigned for multi-bytes character drawing.
            09/19/1999  HANAI Tohru
                        Since TheTextDrawer grew fat it was split into three
                        classes - TheFontStock, TheTextDrawer and TheTextDrawerEx.
                        Currently it should avoid TheTextDrawer because it is
                        slower than TheTextDrawer.
            09/25/1999  HANAI Tohru
                        Added internally definition of LeadBytes for Delphi 2
            10/01/1999  HANAI Tohru
                        To save font resources, now all fonts data are shared
                        among all of TheFontStock instances. With this changing,
                        there added a new class `TheFontsInfoManager' to manage
                        those shared data.
            10/09/1999  HANAI Tohru
                        Added BaseStyle property to TheFontFont class.
 ==============================================================================*/

// $Id: SynTextDrawer.pas,v 1.6.2.17 2008/09/17 13:59:12 maelh Exp $

// SynEdit note: The name had to be changed to get SynEdit to install 
//   together with mwEdit into the same Delphi installation


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
const int FontStyleCount = int((TFontStyle) 3 /*# High(TFontStyle) */) + 1;
const int FontStyleCombineCount = (1 << FontStyleCount);
typedef int TIntegerArray[536870911/*# range 0..MaxInt div SizeOf(Integer)-1*/];
typedef TIntegerArray* PIntegerArray;
typedef int /*0..FontStyleCombineCount-1*/ TheStockFontPatterns;
struct TheFontData;
typedef TheFontData* PheFontData;

struct TheFontData
{
	TFontStyles Style;
	HFONT Handle;
	int CharAdv;
	int CharHeight;
};
typedef TheFontData TheFontsData[FontStyleCombineCount - 1+1/*# TheStockFontPatterns*/];
typedef TheFontsData* PheFontsData;
    // reference counters
struct TheSharedFontsInfo;
typedef TheSharedFontsInfo* PheSharedFontsInfo;

struct TheSharedFontsInfo
{
	int RefCount;
	int LockCount;
    // font information
	TFont* BaseFont;
	TLogFont BaseLF;
	bool IsTrueType;
	TheFontsData FontsData;
};

  /* TheStockFontManager */

class TheFontsInfoManager : public System::TObject
{
	#include "SynTextDrawer_friends.inc"
public:
	typedef System::TObject inherited;
private:
	TList* FFontsInfo;
	PheSharedFontsInfo __fastcall FindFontsInfo(const TLogFont& LF);
	PheSharedFontsInfo __fastcall CreateFontsInfo(TFont* ABaseFont, const TLogFont& LF);
	void __fastcall DestroyFontHandles(PheSharedFontsInfo pFontsInfo);
	void __fastcall RetrieveLogFontForComparison(TFont* ABaseFont, TLogFont& LF);
public:
	__fastcall TheFontsInfoManager();
	virtual __fastcall ~TheFontsInfoManager();
	void __fastcall LockFontsInfo(PheSharedFontsInfo pFontsInfo);
	void __fastcall UnLockFontsInfo(PheSharedFontsInfo pFontsInfo);
	PheSharedFontsInfo __fastcall GetFontsInfo(TFont* ABaseFont);
	void __fastcall ReleaseFontsInfo(PheSharedFontsInfo pFontsInfo);
};

  /* TheFontStock */
enum SyntextdrawerEnum__0 {tooOpaque,
                           tooClipped };
typedef System::Set<SyntextdrawerEnum__0, SyntextdrawerEnum__0::tooOpaque, SyntextdrawerEnum__0::tooClipped> TTextOutOptions;
typedef void __fastcall (__closure *TheExtTextOutProc) (int, int, TTextOutOptions, const TRect&, const String, int);

class EheFontStockException : public System::Sysutils::Exception
{
	#include "SynTextDrawer_friends.inc"
public:
	typedef System::Sysutils::Exception inherited;
	__fastcall EheFontStockException(const String Msg);
	__fastcall EheFontStockException(const String Msg, const TVarRec* Args, int Args_maxidx);
	__fastcall EheFontStockException(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall EheFontStockException(const String Msg, int AHelpContext);
	__fastcall EheFontStockException(System::NativeUInt Ident);
	__fastcall EheFontStockException(System::PResStringRec ResStringRec);
	__fastcall EheFontStockException(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx);
	__fastcall EheFontStockException(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx);
	__fastcall EheFontStockException(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall EheFontStockException(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall EheFontStockException(System::NativeUInt Ident, int AHelpContext);
	__fastcall EheFontStockException(System::PResStringRec ResStringRec, int AHelpContext);
};

class TheFontStock : public System::TObject
{
	#include "SynTextDrawer_friends.inc"
public:
	typedef System::TObject inherited;
private:
    // private DC
	HDC FDC;
	int FDCRefCount;

    // Shared fonts
	PheSharedFontsInfo FpInfo;
	bool FUsingFontHandles;

    // Current font
	HFONT FCrntFont;
	TFontStyles FCrntStyle;
	PheFontData FpCrntFontData;
    // local font info
	TLogFont FBaseLF;
	TFont* __fastcall GetBaseFont();
	bool __fastcall GetIsTrueType();
protected:
	virtual HDC __fastcall InternalGetDC();
	virtual void __fastcall InternalReleaseDC(HDC Value);
	virtual HFONT __fastcall InternalCreateFont(TFontStyles Style);
	virtual int __fastcall GetCharAdvance();
	virtual int __fastcall GetCharHeight();
	virtual PheFontData __fastcall GetFontData(int Idx);
	void __fastcall UseFontHandles();
	void __fastcall ReleaseFontsInfo();
	virtual void __fastcall SetBaseFont(TFont* Value);
	virtual void __fastcall SetStyle(TFontStyles Value);
	__property PheFontData FontData[int Idx] = { read = GetFontData };
	__property PheSharedFontsInfo FontsInfo = { read = FpInfo };
public:
	__classmethod virtual int __fastcall CalcFontAdvance(HDC DC, PInteger pCharHeight);
	__fastcall TheFontStock(TFont* InitialFont);
	virtual __fastcall ~TheFontStock();
	virtual void __fastcall ReleaseFontHandles();
	__property TFont* BaseFont = { read = GetBaseFont };
	__property TFontStyles Style = { read = FCrntStyle, write = SetStyle };
	__property HFONT FontHandle = { read = FCrntFont };
	__property int CharAdvance = { read = GetCharAdvance };
	__property int CharHeight = { read = GetCharHeight };
	__property bool IsTrueType = { read = GetIsTrueType };
	__fastcall TheFontStock();
};

  /* TheTextDrawer */

class EheTextDrawerException : public System::Sysutils::Exception
{
	#include "SynTextDrawer_friends.inc"
public:
	typedef System::Sysutils::Exception inherited;
	__fastcall EheTextDrawerException(const String Msg);
	__fastcall EheTextDrawerException(const String Msg, const TVarRec* Args, int Args_maxidx);
	__fastcall EheTextDrawerException(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall EheTextDrawerException(const String Msg, int AHelpContext);
	__fastcall EheTextDrawerException(System::NativeUInt Ident);
	__fastcall EheTextDrawerException(System::PResStringRec ResStringRec);
	__fastcall EheTextDrawerException(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx);
	__fastcall EheTextDrawerException(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx);
	__fastcall EheTextDrawerException(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall EheTextDrawerException(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall EheTextDrawerException(System::NativeUInt Ident, int AHelpContext);
	__fastcall EheTextDrawerException(System::PResStringRec ResStringRec, int AHelpContext);
};

class TheTextDrawer : public System::TObject
{
	#include "SynTextDrawer_friends.inc"
public:
	typedef System::TObject inherited;
private:
	HDC FDC;
	int FSaveDC;

    // Font information
	TheFontStock* FFontStock;
	TBitmap* FStockBitmap;
	TFontStyles FCalcExtentBaseStyle;
	int FBaseCharWidth;
	int FBaseCharHeight;

    // current font and properties
	HFONT FCrntFont;
	PIntegerArray FETODist;

    // current font attributes
	TColor FColor;
	TColor FBkColor;
	int FCharExtra;

    // Begin/EndDrawing calling count
	int FDrawingCount;

    // GetCharABCWidthsW cache
	TABC FCharABCWidthCache[128/*# range 0..127*/];
	int FCharWidthCache[128/*# range 0..127*/];
protected:
	virtual void __fastcall ReleaseETODist();
	virtual void __fastcall AfterStyleSet();
	virtual void __fastcall DoSetCharExtra(int Value);
	void __fastcall FlushCharABCWidthCache();
	bool __fastcall GetCachedABCWidth(unsigned int C, TABC& ABC);
	__property HDC StockDC = { read = FDC };
	__property int DrawingCount = { read = FDrawingCount };
	__property TheFontStock* FontStock = { read = FFontStock };
	__property int BaseCharWidth = { read = FBaseCharWidth };
	__property int BaseCharHeight = { read = FBaseCharHeight };
public:
	__fastcall TheTextDrawer(TFontStyles CalcExtentBaseStyle, TFont* BaseFont);
	virtual __fastcall ~TheTextDrawer();
	virtual int __fastcall GetCharWidth();
	virtual int __fastcall GetCharHeight();
	virtual void __fastcall BeginDrawing(HDC DC);
	virtual void __fastcall EndDrawing();
	virtual void __fastcall TextOut(int X, int Y, PWideChar Text, int Length);
	virtual void __fastcall ExtTextOut(int X, int Y, TTextOutOptions Options, const TRect& ARect, PWideChar Text, int Length, bool UseLigatures = false);
	TSize __fastcall TextExtent(const String Text);
	TSize __fastcall TextExtent(PWideChar Text, int Count);
	int __fastcall TextWidth(const String Text);
	int __fastcall TextWidth(PWideChar Text, int Count);
	virtual void __fastcall SetBaseFont(TFont* Value);
	virtual void __fastcall SetBaseStyle(const TFontStyles Value);
	virtual void __fastcall SetStyle(TFontStyles Value);
	virtual void __fastcall SetForeColor(TColor Value);
	virtual void __fastcall SetBackColor(TColor Value);
	virtual void __fastcall SetCharExtra(int Value);
	virtual void __fastcall ReleaseTemporaryResources();
	__property int CharWidth = { read = GetCharWidth };
	__property int CharHeight = { read = GetCharHeight };
	__property TFont* BaseFont = { write = SetBaseFont };
	__property TFontStyles BaseStyle = { write = SetBaseStyle };
	__property TColor ForeColor = { write = SetForeColor };
	__property TColor BackColor = { write = SetBackColor };
	__property TFontStyles Style = { write = SetStyle };
	__property int CharExtra = { read = FCharExtra, write = SetCharExtra };
	__fastcall TheTextDrawer();
};
TheFontsInfoManager* __fastcall GetFontsInfoManager();
bool __fastcall UniversalExtTextOut(HDC DC, int X, int Y, TTextOutOptions Options, const TRect& Rect, PWideChar Str, int Count, PIntegerArray ETODist, bool UseLigatures = false);

void SynTextDrawer_finalization();


}  // namespace SynTextDrawer

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syntextdrawer;
#endif


#endif // SynTextDrawerH

