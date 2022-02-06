#ifndef SynEditMiscClassesH
#define SynEditMiscClassesH

#include <System.hpp>
#include "d2c_system.h"

#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Math.hpp>
#include <System.Win.Registry.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Consts.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ImgList.hpp>
#include "SynEditTypes.h"
#include "SynEditKeyConst.h"
#include "SynUnicode.h"

namespace Syneditmiscclasses
{

/* -------------------------------------------------------------------------------
  The contents of this file are subject to the Mozilla Public License
  Version 1.1 (the "License"); you may not use this file except in compliance
  with the License. You may obtain a copy of the License at
  http://www.mozilla.org/MPL/

  Software distributed under the License is distributed on an "AS IS" basis,
  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
  the specific language governing rights and limitations under the License.

  The Original Code is: SynEditMiscClasses.pas, released 2000-04-07.
  The Original Code is based on the mwSupportClasses.pas file from the
  mwEdit component suite by Martin Waldenburg and other developers, the Initial
  Author of this file is Michael Hieke.
  Unicode translation by Maël Hörz.
  All Rights Reserved.

  Contributors to the SynEdit and mwEdit projects are listed in the
  Contributors.txt file.

  Alternatively, the contents of this file may be used under the terms of the
  GNU General Public License Version 2 or later (the "GPL"), in which case
  the provisions of the GPL are applicable instead of those above.
  If you wish to allow use of your version of this file only under the terms
  of the GPL and not to allow others to use your version of this file
  under the MPL, indicate your decision by deleting the provisions above and
  replace them with the notice and other provisions required by the GPL.
  If you do not delete the provisions above, a recipient may use your version
  of this file under either the MPL or the GPL.

  Known Issues:
  ------------------------------------------------------------------------------- */
class DELPHICLASS TSynGutter;
class DELPHICLASS TSynInternalImage;

class TSynSelectedColor : public System::Classes::TPersistent
{
private:
	TColor fBG;
	TColor fFG;
	System::Classes::TNotifyEvent FOnChange;
	void __fastcall SetBG(TColor Value);
	void __fastcall SetFG(TColor Value);
public:
	typedef System::Classes::TPersistent inherited;	
	#include "SynEditMiscClasses_friends.inc"
	__fastcall TSynSelectedColor();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
__published:
	__property TColor Background = { read = fBG, write = SetBG, default = clHighlight };
	__property TColor Foreground = { read = fFG, write = SetFG, default = clHighlightText };
	__property TNotifyEvent OnChange = { read = FOnChange, write = FOnChange };
};
enum TSynGutterBorderStyle {gbsNone,
                            gbsMiddle,
                            gbsRight };
typedef void __fastcall (__closure *TGutterBandPaintEvent) (Vcl::Graphics::TCanvas*, const TRect&, int, int, bool&);
typedef void __fastcall (__closure *TGutterBandClickEvent) (TObject*, TMouseButton, int, int, int, int);
typedef void __fastcall (__closure *TGutterMouseCursorEvent) (TObject*, int, int, int, int, TCursor&);

  /* When created TGutter contains four bands (Marks, Line Numbers,
    Code Folding and Margin).  The order, width and other properties of the
    bands can be set at design time through the Bands property of TSynGutter.
    Custom bands can also be created.  They can be painted using
    OnPaintLines event handler.
    The width of the Line Numbers and Code Folding band is automatically
    calculated and not set at design time */
enum TSynGutterBandKind {gbkCustom,
                         gbkMarks,
                         gbkLineNumbers,
                         gbkFold,
                         gbkMargin,
                         gbkTrackChanges };
enum TSynGutterBandBackground {gbbNone,
                               gbbGutter,
                               gbbEditor };

class TSynGutterBand : public System::Classes::TCollectionItem
{
public:
	typedef System::Classes::TCollectionItem inherited;	
	#include "SynEditMiscClasses_friends.inc"
	static const int MarginX; //  = 2;
private:
	TSynGutterBandKind FKind;
	bool fVisible;
	int FWidth;
	TSynGutterBandBackground FBackground;
	TGutterBandPaintEvent FOnPaintLines;
	TGutterBandClickEvent FOnClick;
	TGutterMouseCursorEvent fOnMouseCursor;
	TSynGutter* __fastcall GetSynGutter();
	System::Classes::TPersistent* __fastcall GetEditor();
	void __fastcall DoPaintLines(Vcl::Graphics::TCanvas* Canvas, const TRect& ClipR, int FirstRow, int LastRow);
	void __fastcall PaintMarks(Vcl::Graphics::TCanvas* Canvas, const TRect& ClipR, int FirstRow, int LastRow);
	void __fastcall PaintLineNumbers(Vcl::Graphics::TCanvas* Canvas, const TRect& ClipR, int FirstRow, int LastRow);
	void __fastcall PaintFoldShapes(Vcl::Graphics::TCanvas* Canvas, const TRect& ClipR, int FirstRow, int LastRow);
	void __fastcall PaintMargin(Vcl::Graphics::TCanvas* Canvas, const TRect& ClipR, int FirstRow, int LastRow);
	void __fastcall SetBackground(TSynGutterBandBackground Value);
	void __fastcall SetVisible(bool Value);
	void __fastcall SetWidth(int Value);
	void __fastcall SetKind(TSynGutterBandKind Kind);
	void __fastcall SetOnPaintLines(const TGutterBandPaintEvent Value);
	bool __fastcall IsWidthStored();
	int __fastcall GetWidth();
	bool __fastcall GetVisible();
	void __fastcall SetOnClick(const TGutterBandClickEvent Value);
	int __fastcall GetLeftX();
	TRect __fastcall FoldShapeRect(int Row, int Line);
	void __fastcall SetOnMouseCursor(const TGutterMouseCursorEvent Value);
	bool __fastcall IsVisibleStored();
protected:
	virtual String __fastcall GetDisplayName();
public:
	__fastcall TSynGutterBand(System::Classes::TCollection* Collection);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	int __fastcall RealWidth();
	void __fastcall PaintLines(Vcl::Graphics::TCanvas* Canvas, const TRect& ClipR, int FirstRow, int LastRow);
	void __fastcall DoClick(TObject* Sender, TMouseButton Button, int X, int Y, int Row, int Line);
	void __fastcall DoMouseCursor(TObject* Sender, int X, int Y, int Row, int Line, TCursor& Cursor);
	__property int LeftX = { read = GetLeftX };
	__property System::Classes::TPersistent* Editor = { read = GetEditor };
	__property TSynGutter* Gutter = { read = GetSynGutter };
__published:
	__property TSynGutterBandKind Kind = { read = FKind, write = SetKind };
	__property bool Visible = { read = GetVisible, write = SetVisible, stored = IsVisibleStored };
	__property int Width = { read = GetWidth, write = SetWidth, stored = IsWidthStored };
	__property TSynGutterBandBackground Background = { read = FBackground, write = SetBackground, default = /*# gbbGutter */ 1 };
	__property TGutterBandPaintEvent OnPaintLines = { read = FOnPaintLines, write = SetOnPaintLines };
	__property TGutterBandClickEvent OnClick = { read = FOnClick, write = SetOnClick };
	__property TGutterMouseCursorEvent OnMouseCursor = { read = fOnMouseCursor, write = SetOnMouseCursor };
};

class TSynBandsCollection : public System::Classes::TOwnedCollection
{
private:
	TSynGutterBand* __fastcall GetBands(int Index);
protected:
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
public:
	typedef System::Classes::TOwnedCollection inherited;	
	#include "SynEditMiscClasses_friends.inc"
	__property TSynGutterBand* Bands[int Index] = { read = GetBands/*# default */ };
	__fastcall TSynBandsCollection(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass);
	//# problematic: __fastcall TSynBandsCollection(System::Classes::TCollectionItemClass ItemClass);
};

class TSynGutter : public System::Classes::TPersistent
{
private:
	System::Classes::TPersistent* FOwner; // Synedit
	int FUpdateCount;
	int FCurrentPPI;
	Vcl::Graphics::TFont* FFont;
	int fCharWidth;
	TColor FColor;
	TColor FBorderColor;
	int fDigitCount;
	bool fLeadingZeros;
	bool fZeroStart;
	System::Classes::TNotifyEvent FOnChange;
	TCursor FCursor;
	bool fVisible;
	bool fShowLineNumbers;
	bool fUseFontStyle;
	bool FAutoSize;
	int fAutoSizeDigitCount;
	TSynGutterBorderStyle FBorderStyle;
	int fLineNumberStart;
	bool fGradient;
	TColor FGradientStartColor;
	TColor FGradientEndColor;
	int fGradientSteps;
	TSynInternalImage* fInternalImage;
	TSynBandsCollection* FBands;
	void __fastcall SetAutoSize(bool Value);
	void __fastcall SetBorderColor(const TColor Value);
	void __fastcall SetColor(const TColor Value);
	void __fastcall SetDigitCount(int Value);
	void __fastcall SetLeadingZeros(bool Value);
	void __fastcall SetShowLineNumbers(bool Value);
	void __fastcall SetUseFontStyle(bool Value);
	void __fastcall SetVisible(bool Value);
	void __fastcall SetZeroStart(bool Value);
	void __fastcall SetFont(Vcl::Graphics::TFont* Value);
	void __fastcall OnFontChange(TObject* Sender);
	void __fastcall SetBorderStyle(TSynGutterBorderStyle Value);
	void __fastcall SetLineNumberStart(int Value);
	void __fastcall SetGradient(bool Value);
	void __fastcall SetGradientStartColor(const TColor Value);
	void __fastcall SetGradientEndColor(const TColor Value);
	void __fastcall SetGradientSteps(int Value);
	void __fastcall SetBands(TSynBandsCollection* const Value);
	TSynInternalImage* __fastcall GetInternalImage();
	TSynGutterBand* __fastcall GetBandByKind(TSynGutterBandKind Kind);
	void __fastcall CalcCharWidth();
	void __fastcall Changed();
protected:
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
public:
	bool AssignableBands;
	typedef System::Classes::TPersistent inherited;	
	#include "SynEditMiscClasses_friends.inc"
	__fastcall TSynGutter();
	__fastcall TSynGutter(System::Classes::TPersistent* Owner);
	virtual __fastcall ~TSynGutter();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	void __fastcall AutoSizeDigitCount();
	String __fastcall FormatLineNumber(int Line);
	int __fastcall RealGutterWidth();
	TSynGutterBand* __fastcall BandAtX(int X);
    // ++ DPI-Aware
	virtual void __fastcall ChangeScale(int m, int D);
    // -- DPI-Aware
	__property TSynInternalImage* InternalImage = { read = GetInternalImage };
    // Band returns the first band of a given kind
	__property TSynGutterBand* Band[TSynGutterBandKind Kind] = { read = GetBandByKind };
__published:
	__property bool AutoSize = { read = FAutoSize, write = SetAutoSize, default = true };
	__property TSynGutterBorderStyle BorderStyle = { read = FBorderStyle, write = SetBorderStyle, default = /*# gbsMiddle */ 1 };
	__property TColor Color = { read = FColor, write = SetColor, default = clBtnFace };
	__property TColor BorderColor = { read = FBorderColor, write = SetBorderColor, default = clWindow };
	__property TCursor Cursor = { read = FCursor, write = FCursor, default = /*# crDefault */ 0 };
	__property int DigitCount = { read = fDigitCount, write = SetDigitCount, default = 4 };
	__property TFont* Font = { read = FFont, write = SetFont };
	__property bool ShowLineNumbers = { read = fShowLineNumbers, write = SetShowLineNumbers, default = false };
	__property bool LeadingZeros = { read = fLeadingZeros, write = SetLeadingZeros, default = false };
	__property bool UseFontStyle = { read = fUseFontStyle, write = SetUseFontStyle, default = true };
	__property bool Visible = { read = fVisible, write = SetVisible, default = true };
	__property bool ZeroStart = { read = fZeroStart, write = SetZeroStart, default = false };
	__property int LineNumberStart = { read = fLineNumberStart, write = SetLineNumberStart, default = 1 };
	__property bool Gradient = { read = fGradient, write = SetGradient, default = false };
	__property TColor GradientStartColor = { read = FGradientStartColor, write = SetGradientStartColor, default = clWindow };
	__property TColor GradientEndColor = { read = FGradientEndColor, write = SetGradientEndColor, default = clBtnFace };
	__property int GradientSteps = { read = fGradientSteps, write = SetGradientSteps, default = 48 };
	__property TSynBandsCollection* Bands = { read = FBands, write = SetBands };
	__property TNotifyEvent OnChange = { read = FOnChange, write = FOnChange };
};

class TSynBookMarkOpt : public System::Classes::TPersistent
{
private:
	Vcl::Imglist::TCustomImageList* fBookmarkImages;
	bool fDrawBookmarksFirst;
	bool fEnableKeys;
	bool fGlyphsVisible;
	int fLeftMargin;
	System::Classes::TComponent* FOwner;
	int FXOffset;
	System::Classes::TNotifyEvent FOnChange;
	void __fastcall SetBookmarkImages(Vcl::Imglist::TCustomImageList* const Value);
	void __fastcall SetDrawBookmarksFirst(bool Value);
	void __fastcall SetGlyphsVisible(bool Value);
	void __fastcall SetLeftMargin(int Value);
	void __fastcall SetXOffset(int Value);
public:
	typedef System::Classes::TPersistent inherited;	
	#include "SynEditMiscClasses_friends.inc"
	__fastcall TSynBookMarkOpt(System::Classes::TComponent* AOwner);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
    // ++ DPI-Aware
	virtual void __fastcall ChangeScale(int m, int D);
    // -- DPI-Aware
__published:
	__property TCustomImageList* BookmarkImages = { read = fBookmarkImages, write = SetBookmarkImages };
	__property bool DrawBookmarksFirst = { read = fDrawBookmarksFirst, write = SetDrawBookmarksFirst, default = true };
	__property bool EnableKeys = { read = fEnableKeys, write = fEnableKeys, default = true };
	__property bool GlyphsVisible = { read = fGlyphsVisible, write = SetGlyphsVisible, default = true };
	__property int LeftMargin = { read = fLeftMargin, write = SetLeftMargin, default = 2 };
	__property int XOffset = { read = FXOffset, write = SetXOffset, default = 12 };
	__property TNotifyEvent OnChange = { read = FOnChange, write = FOnChange };
public:
	__fastcall TSynBookMarkOpt();
};

class TSynGlyph : public System::Classes::TPersistent
{
private:
	bool fVisible;
	Vcl::Graphics::TBitmap* fInternalGlyph;
	Vcl::Graphics::TBitmap* FGlyph;
	System::Classes::TNotifyEvent FOnChange;
	void __fastcall SetGlyph(Vcl::Graphics::TBitmap* Value);
	void __fastcall GlyphChange(TObject* Sender);
	void __fastcall SetVisible(bool Value);
	int __fastcall GetWidth();
	int __fastcall GetHeight();
public:
	typedef System::Classes::TPersistent inherited;	
	#include "SynEditMiscClasses_friends.inc"
	__fastcall TSynGlyph(THandle aModule, const String AName);
	virtual __fastcall ~TSynGlyph();
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
	void __fastcall Draw(Vcl::Graphics::TCanvas* ACanvas, int AX, int AY, int aLineHeight);
	__property int Width = { read = GetWidth };
	__property int Height = { read = GetHeight };
    // ++ DPI-Aware
	virtual void __fastcall ChangeScale(int m, int D);
    // -- DPI-Aware
__published:
	__property TBitmap* Glyph = { read = FGlyph, write = SetGlyph };
	__property bool Visible = { read = fVisible, write = SetVisible, default = true };
	__property TNotifyEvent OnChange = { read = FOnChange, write = FOnChange };
public:
	__fastcall TSynGlyph();
};

  /* TSynMethodChain */

class ESynMethodChain : public System::Sysutils::Exception
{
	#include "SynEditMiscClasses_friends.inc"
public:
	typedef System::Sysutils::Exception inherited;	
	__fastcall ESynMethodChain(const String Msg);
	__fastcall ESynMethodChain(const String Msg, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynMethodChain(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynMethodChain(const String Msg, int AHelpContext);
	__fastcall ESynMethodChain(System::NativeUInt Ident);
	__fastcall ESynMethodChain(System::PResStringRec ResStringRec);
	__fastcall ESynMethodChain(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynMethodChain(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynMethodChain(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynMethodChain(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynMethodChain(System::NativeUInt Ident, int AHelpContext);
	__fastcall ESynMethodChain(System::PResStringRec ResStringRec, int AHelpContext);
};
typedef void __fastcall (__closure *TSynExceptionEvent) (TObject*, System::Sysutils::Exception*, bool&);

class TSynMethodChain : public System::TObject
{
	#include "SynEditMiscClasses_friends.inc"
public:
	typedef TObject inherited;	
private:
	System::Classes::TList* FNotifyProcs;
	TSynExceptionEvent FExceptionHandler;
protected:
	virtual void __fastcall DoFire(const System::TMethod& AEvent){} // = 0;
	virtual bool __fastcall DoHandleException(System::Sysutils::Exception* e);
	__property TSynExceptionEvent ExceptionHandler = { read = FExceptionHandler, write = FExceptionHandler };
public:
	__fastcall TSynMethodChain();
	virtual __fastcall ~TSynMethodChain();
	void __fastcall Add(const System::TMethod& AEvent);
	void __fastcall Remove(const System::TMethod& AEvent);
	void __fastcall Fire();
};

  /* TSynNotifyEventChain */

class TSynNotifyEventChain : public TSynMethodChain
{
	#include "SynEditMiscClasses_friends.inc"
public:
	typedef TSynMethodChain inherited;	
private:
	TObject* FSender;
protected:
	virtual void __fastcall DoFire(const System::TMethod& AEvent);
public:
	__fastcall TSynNotifyEventChain(TObject* ASender);
	void __fastcall Add(System::Classes::TNotifyEvent AEvent);
	void __fastcall Remove(System::Classes::TNotifyEvent AEvent);
	__property  ExceptionHandler;
	__property TObject* Sender = { read = FSender, write = FSender };
	__fastcall TSynNotifyEventChain();
};

  /* TSynInternalImage */

class TSynInternalImage : public System::TObject
{
	#include "SynEditMiscClasses_friends.inc"
public:
	typedef TObject inherited;	
private:
	Vcl::Graphics::TBitmap* FImages;
	int FWidth;
	int FHeight;
	int FCount;
public:
	__fastcall TSynInternalImage(THandle aModule, const String Name, int Count);
	virtual __fastcall ~TSynInternalImage();
	void __fastcall Draw(Vcl::Graphics::TCanvas* ACanvas, int Number, int X, int Y, int LineHeight);
    // ++ DPI-Aware
	virtual void __fastcall ChangeScale(int m, int D);
    // -- DPI-Aware
	__fastcall TSynInternalImage();
};

  /* TSynHotKey */
const int BorderWidth = 0;
typedef Vcl::Forms::TBorderStyle TSynBorderStyle;
enum THKModifier {hkShift,
                  hkCtrl,
                  hkAlt };
typedef System::Set<THKModifier, hkShift, hkAlt> THKModifiers;
enum THKInvalidKey {hcNone,
                    hcShift,
                    hcCtrl,
                    hcAlt,
                    hcShiftCtrl,
                    hcShiftAlt,
                    hcCtrlAlt,
                    hcShiftCtrlAlt };
typedef System::Set<THKInvalidKey, hcNone, hcShiftCtrlAlt> THKInvalidKeys;

class TSynHotKey : public Vcl::Controls::TCustomControl
{
private:
	TSynBorderStyle FBorderStyle;
	System::Classes::TShortCut FHotKey;
	THKInvalidKeys FInvalidKeys;
	THKModifiers FModifiers;
	bool FPressedOnlyModifiers;
	void __fastcall SetBorderStyle(const TSynBorderStyle Value);
	void __fastcall SetHotKey(const System::Classes::TShortCut Value);
	void __fastcall SetInvalidKeys(const THKInvalidKeys Value);
	void __fastcall SetModifiers(const THKModifiers Value);
	MESSAGE void __fastcall WMGetDlgCode(TMessage& Message)/*# WM_GETDLGCODE */;
	HIDESBASE MESSAGE void __fastcall WMKillFocus(TWMKillFocus& Msg)/*# WM_KILLFOCUS */;
	HIDESBASE MESSAGE void __fastcall WMSetFocus(TWMSetFocus& Msg)/*# WM_SETFOCUS */;
protected:
	virtual void __fastcall CreateParams(Vcl::Controls::TCreateParams& Params);
	DYNAMIC void __fastcall DoExit();
	DYNAMIC void __fastcall KeyDown(WORD& key, System::Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyUp(WORD& key, System::Classes::TShiftState Shift);
	DYNAMIC void __fastcall MouseDown(TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Paint();
public:
	typedef Vcl::Controls::TCustomControl inherited;	
	#include "SynEditMiscClasses_friends.inc"
	__fastcall TSynHotKey(System::Classes::TComponent* AOwner);
__published:
	__property  Font;
	__property  Color;
	__property TSynBorderStyle BorderStyle = { read = FBorderStyle, write = SetBorderStyle, default = /*# bsSingle */ 1 };
	__property TShortCut HotKey = { read = FHotKey, write = SetHotKey, default = 0x0041 }; /* Alt+A */
	__property THKInvalidKeys InvalidKeys = { read = FInvalidKeys, write = SetInvalidKeys, default = /*# hcNone, hcShift */ 0 };
	__property THKModifiers Modifiers = { read = FModifiers, write = SetModifiers, default = /*# hkAlt */ 0 };
protected:
	BEGIN_MESSAGE_MAP
	  VCL_MESSAGE_HANDLER(WM_GETDLGCODE, TMessage, WMGetDlgCode)
	  VCL_MESSAGE_HANDLER(WM_KILLFOCUS, TWMKillFocus, WMKillFocus)
	  VCL_MESSAGE_HANDLER(WM_SETFOCUS, TWMSetFocus, WMSetFocus)
	END_MESSAGE_MAP(Vcl::Controls::TCustomControl)
public:
	__fastcall TSynHotKey(HWND ParentWindow);
};

class TSynEditSearchCustom : public System::Classes::TComponent
{
protected:
	virtual String __fastcall GetPattern(){return String();} // = 0;
	virtual void __fastcall SetPattern(const String Value){} // = 0;
	virtual int __fastcall GetLength(int Index){return 0;} // = 0;
	virtual int __fastcall GetResult(int Index){return 0;} // = 0;
	virtual int __fastcall GetResultCount(){return 0;} // = 0;
	virtual void __fastcall SetOptions(const Synedittypes::TSynSearchOptions Value){} // = 0;
public:
	typedef System::Classes::TComponent inherited;	
	#include "SynEditMiscClasses_friends.inc"
	virtual int __fastcall FindAll(const String NewText){return 0;} // = 0;
	virtual String __fastcall PreprocessReplaceExpression(const String AReplace);
	virtual String __fastcall Replace(const String aOccurrence, const String aReplacement){return String();} // = 0;
	__property String Pattern = { read = GetPattern, write = SetPattern };
	__property int ResultCount = { read = GetResultCount };
	__property int Results[int Index] = { read = GetResult };
	__property int Lengths[int Index] = { read = GetLength };
	__property Synedittypes::TSynSearchOptions Options = { write = SetOptions };
	__fastcall TSynEditSearchCustom(System::Classes::TComponent* AOwner);
};

class TBetterRegistry : public System::Win::Registry::TRegistry
{
	#include "SynEditMiscClasses_friends.inc"
public:
	typedef System::Win::Registry::TRegistry inherited;	
	bool __fastcall OpenKeyReadOnly(const String key);
	__fastcall TBetterRegistry();
	__fastcall TBetterRegistry(unsigned int AAccess);
};

  // ++ DPI-Aware
void __fastcall ResizeBitmap(Vcl::Graphics::TBitmap* BITMAP, int NewWidth, int NewHeight);
// -- DPI-Aware


}  // namespace SynEditMiscClasses

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditmiscclasses;
#endif

#endif // SynEditMiscClassesH

