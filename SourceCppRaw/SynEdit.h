#ifndef SynEditH
#define SynEditH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <Vcl.Controls.hpp>
#include <System.Contnrs.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Themes.hpp>
#include <System.UITypes.hpp>
#include <Winapi.Imm.hpp>
#include <System.Diagnostics.hpp>
#include "SynUnicode.h"
#include "SynTextDrawer.h"
#include "SynEditTypes.h"
#include "SynEditKeyConst.h"
#include "SynEditMiscProcs.h"
#include "SynEditMiscClasses.h"
#include "SynEditTextBuffer.h"
#include "SynEditKeyCmds.h"
#include "SynEditHighlighter.h"
#include "SynEditKbdHandler.h"
#include "SynEditCodeFolding.h"
#include <System.Math.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "SynEditDelphiInstances.hpp"

namespace Synedit
{

#define SynEdit__0 System::Classes::TShiftState()
/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is based on mwCustomEdit.pas by Martin Waldenburg, part of
the mwEdit component suite.
Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
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
-------------------------------------------------------------------------------*/
//todo: in WordWrap mode, parse lines only once in PaintLines()
//todo: Remove checks for WordWrap. Must abstract the behaviour with the plugins instead.
//todo: Move WordWrap glyph to the WordWrap plugin.

   // maximum scroll range
const int MAX_SCROLL = 32767;

  // Max number of book/gutter marks returned from GetEditMarksForLine - that
  // really should be enough.
const int MAX_MARKS = 16;
typedef TBufferCoord TBufferCoord;
typedef Synedittypes::TDisplayCoord TDisplayCoord;
typedef Vcl::Forms::TBorderStyle TSynBorderStyle;
enum TSynReplaceAction {raCancel,
                        raSkip,
                        raReplace,
                        raReplaceAll };

class ESynEditError : public Synedittypes::ESynError
{
	#include "SynEdit_friends.inc"
public:
	typedef Synedittypes::ESynError inherited;	
	__fastcall ESynEditError(const String Msg);
	__fastcall ESynEditError(const String Msg, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynEditError(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynEditError(const String Msg, int AHelpContext);
	__fastcall ESynEditError(System::NativeUInt Ident);
	__fastcall ESynEditError(System::PResStringRec ResStringRec);
	__fastcall ESynEditError(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynEditError(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynEditError(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynEditError(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynEditError(System::NativeUInt Ident, int AHelpContext);
	__fastcall ESynEditError(System::PResStringRec ResStringRec, int AHelpContext);
};
typedef void __fastcall (__closure *TDropFilesEvent) (TObject*, int, int, System::Classes::TStrings*);
typedef void __fastcall (__closure *TPaintEvent) (TObject*, Vcl::Graphics::TCanvas*);
typedef void __fastcall (__closure *TProcessCommandEvent) (TObject*, Synedittypes::TSynEditorCommand&, WideChar&, void*);
typedef void __fastcall (__closure *TReplaceTextEvent) (TObject*, const String, const String, int, int, TSynReplaceAction&);
typedef void __fastcall (__closure *TSpecialLineColorsEvent) (TObject*, int, bool&, TColor&, TColor&);
enum TTransientType {ttBefore,
                     ttAfter };
typedef void __fastcall (__closure *TPaintTransient) (TObject*, Vcl::Graphics::TCanvas*, TTransientType);
typedef void __fastcall (__closure *TScrollEvent) (TObject*, Vcl::Forms::TScrollBarKind);
typedef void __fastcall (__closure *TGutterGetTextEvent) (TObject*, int, String&);
enum TSynEditCaretType {ctVerticalLine,
                        ctHorizontalLine,
                        ctHalfBlock,
                        ctBlock };
enum TSynStateFlag {sfCaretChanged,
                    sfScrollbarChanged,
                    sfLinesChanging,
                    sfIgnoreNextChar,
                    sfCaretVisible,
                    sfPossibleGutterClick,
                    sfOleDragSource,
                    sfGutterDragging };
typedef System::Set<TSynStateFlag, sfCaretChanged, sfGutterDragging> TSynStateFlags;
enum TScrollHintFormat {shfTopLineOnly,
                        shfTopToBottom };
       //Holding down the Alt Key will put the selection mode into columnar format
              //Will indent the caret on new lines with the same amount of leading white space as the preceding line
     //Disables the scroll bar arrow buttons when you can't scroll in that direction any more
         //Allows you to select a block of text and drag it within the document to another location
               //Allows the editor accept OLE file drops
          //enhances home key positioning, similar to visual studio
           //enhances End key positioning, similar to JDeveloper
               //When undoing/redoing actions, handle all continous changes of the same kind in one call instead undoing/redoing each command separately
          //When scrolling with page-up and page-down commands, only scroll a half page at a time
      //if enabled, then the scrollbars will only show when necessary.  If you have ScrollPastEOL, then it the horizontal bar will always be there (it uses MaxLength instead)
              //When moving through lines w/o Cursor Past EOL, keeps the X position of the cursor
                 //Makes it so the caret is never visible
             //Disables selecting text
   //When clicking with the right mouse for a popup menu, move the cursor to that location
         //Forces scrolling to be one less
       //The scroll hint follows the mouse when scrolling vertically
           //Allows the cursor to go past the end of file marker
           //Allows the cursor to go past the last character into the white space at the end of a line
          //Shows a hint of the visible line numbers when scrolling vertically
        //Shows the special Characters
          //similar to Smart Tabs, but when you delete characters
               //When tabbing, the cursor will go to the next non-white space character of the previous line
    //disables the foreground text color override when using the OnSpecialLineColor event
               //When active <Tab> and <Shift><Tab> act as block indent, unindent when text is selected
            //Converts a tab character to a specified number of space characters
      //Spaces at the end of lines will be trimmed and not saved
           //Shows font ligatures, by default it is disabled
            //Do not include additional clipboard formats when you copy to Clipboard or drag text
enum TSynEditorOption {eoAltSetsColumnMode,
                       eoAutoIndent,
                       eoDisableScrollArrows,
                       eoDragDropEditing,
                       eoDropFiles,
                       eoEnhanceHomeKey,
                       eoEnhanceEndKey,
                       eoGroupUndo,
                       eoHalfPageScroll,
                       eoHideShowScrollbars,
                       eoKeepCaretX,
                       eoNoCaret,
                       eoNoSelection,
                       eoRightMouseMovesCursor,
                       eoScrollByOneLess,
                       eoScrollHintFollows,
                       eoScrollPastEof,
                       eoScrollPastEol,
                       eoShowScrollHint,
                       eoShowSpecialChars,
                       eoSmartTabDelete,
                       eoSmartTabs,
                       eoSpecialLineDefaultFg,
                       eoTabIndent,
                       eoTabsToSpaces,
                       eoTrimTrailingSpaces,
                       eoShowLigatures,
                       eoCopyPlainText };
typedef System::Set<TSynEditorOption, eoAltSetsColumnMode, eoCopyPlainText> TSynEditorOptions;
const System::Set<TSynEditorOption, eoAltSetsColumnMode, eoCopyPlainText> SYNEDIT_DEFAULT_OPTIONS = System::Set<TSynEditorOption, eoAltSetsColumnMode, eoCopyPlainText>() << Synedit::TSynEditorOption::eoAutoIndent << Synedit::TSynEditorOption::eoDragDropEditing << Synedit::TSynEditorOption::eoEnhanceEndKey << Synedit::TSynEditorOption::eoScrollPastEol << Synedit::TSynEditorOption::eoShowScrollHint << Synedit::TSynEditorOption::eoTabIndent << Synedit::TSynEditorOption::eoTabsToSpaces << Synedit::TSynEditorOption::eoSmartTabDelete << Synedit::TSynEditorOption::eoGroupUndo;
class DELPHICLASS TCustomSynEdit;

struct TCreateParamsW
{
	PWideChar Caption;
	DWORD Style;
	DWORD ExStyle;
	int X;
	int Y;
	int Width;
	int Height;
	HWND WndParent;
	void* Param;
	TWndClassW WindowClass;
	WideChar WinClassName[64/*# range 0..63*/];
	String InternalCaption;
};
// use scAll to update a statusbar when another TCustomSynEdit got the focus
enum TSynStatusChange {scAll,
                       scCaretX,
                       scCaretY,
                       scLeftChar,
                       scTopLine,
                       scInsertMode,
                       scModified,
                       scSelection,
                       scReadOnly };
typedef System::Set<TSynStatusChange, scAll, scReadOnly> TSynStatusChanges;
typedef void __fastcall (__closure *TContextHelpEvent) (TObject*, String);
typedef void __fastcall (__closure *TStatusChangeEvent) (TObject*, TSynStatusChanges);

//++ CodeFolding
typedef void __fastcall (__closure *TMouseCursorEvent) (TObject*, const TBufferCoord&, TCursor&);
//-- CodeFolding
typedef void __fastcall (__closure *TScanForFoldRangesEvent) (TObject*, Syneditcodefolding::TSynFoldRanges*, System::Classes::TStrings*, int, int);

class TSynEditMark : public System::TObject
{
	#include "SynEdit_friends.inc"
public:
	typedef TObject inherited;	
protected:
	int fLine;
	int fChar;
	int FImage;
	TCustomSynEdit* fEdit;
	bool fVisible;
	bool fInternalImage;
	int fBookmarkNum;
	virtual TCustomSynEdit* __fastcall GetEdit();
	virtual void __fastcall SetChar(int Value);
	virtual void __fastcall SetImage(int Value);
	virtual void __fastcall SetLine(int Value);
	void __fastcall SetVisible(bool Value);
	void __fastcall SetInternalImage(bool Value);
	bool __fastcall GetIsBookmark();
public:
	__fastcall TSynEditMark(TCustomSynEdit* AOwner);
	__property int Line = { read = fLine, write = SetLine };
	__property int Char = { read = fChar, write = SetChar };
	__property TCustomSynEdit* Edit = { read = fEdit };
	__property int ImageIndex = { read = FImage, write = SetImage };
	__property int BookmarkNumber = { read = fBookmarkNum, write = fBookmarkNum };
	__property bool Visible = { read = fVisible, write = SetVisible };
	__property bool InternalImage = { read = fInternalImage, write = SetInternalImage };
	__property bool IsBookmark = { read = GetIsBookmark };
	__fastcall TSynEditMark();
};
typedef void __fastcall (__closure *TPlaceMarkEvent) (TObject*, TSynEditMark*&);
typedef TSynEditMark* TSynEditMarks[16/*# range 1..MAX_MARKS*/];

  /* A list of mark objects. Each object cause a litle picture to be drawn in the gutter. */            // It makes more sence to derive from TObjectList,

class TSynEditMarkList : public System::Contnrs::TObjectList
{
	#include "SynEdit_friends.inc"
public:
	typedef System::Contnrs::TObjectList inherited;	
protected:                                        // as it automatically frees its members
	TCustomSynEdit* fEdit;
	System::Classes::TNotifyEvent FOnChange;
	virtual void __fastcall Notify(void* Ptr, System::Classes::TListNotification Action);
	TSynEditMark* __fastcall GetItem(int Index);
	void __fastcall SetItem(int Index, TSynEditMark* Item);
	__property  OwnsObjects;                          // This is to hide the inherited property,
public:                                           // because TSynEditMarkList always owns the marks
	__fastcall TSynEditMarkList(TCustomSynEdit* AOwner);
	TSynEditMark* __fastcall First();
	TSynEditMark* __fastcall Last();
	TSynEditMark* __fastcall Extract(TSynEditMark* Item);
	void __fastcall ClearLine(int Line);
	void __fastcall GetMarksForLine(int Line, TSynEditMarks& Marks);
	void __fastcall Place(TSynEditMark* Mark);
	__property TSynEditMark* Items[int Index] = { read = GetItem, write = SetItem/*# default */ };
	__property TCustomSynEdit* Edit = { read = fEdit };
	__property System::Classes::TNotifyEvent OnChange = { read = FOnChange, write = FOnChange };
	__fastcall TSynEditMarkList();
	__fastcall TSynEditMarkList(bool AOwnsObjects);
};
typedef void __fastcall (__closure *TGutterClickEvent) (TObject*, System::Uitypes::TMouseButton, int, int, int, TSynEditMark*);
enum TPluginHandler {phLinesInserted,
                     phLinesBeforeDeleted,
                     phLinesDeleted,
                     phLinePut,
                     phLinesChanged,
                     phPaintTransient,
                     phAfterPaint };
typedef System::Set<TPluginHandler, phLinesInserted, phAfterPaint> TPlugInHandlers;

class TSynEditPlugin : public System::TObject
{
	#include "SynEdit_friends.inc"
public:
	typedef TObject inherited;	
private:
	TCustomSynEdit* FOwner;
protected:
	TPlugInHandlers FHandlers;
	virtual void __fastcall AfterPaint(Vcl::Graphics::TCanvas* ACanvas, const TRect& AClip, int FirstLine, int LastLine);
	virtual void __fastcall PaintTransient(Vcl::Graphics::TCanvas* ACanvas, TTransientType ATransientType);
	virtual void __fastcall LinesInserted(int FirstLine, int Count);
	virtual void __fastcall LinesBeforeDeleted(int FirstLine, int Count);
	virtual void __fastcall LinesDeleted(int FirstLine, int Count);
	virtual void __fastcall LinePut(int AIndex, const String OldLine);
	virtual void __fastcall LinesChanged();
	__property TCustomSynEdit* Editor = { read = FOwner };
public:
	__fastcall TSynEditPlugin(TCustomSynEdit* AOwner);
	__fastcall TSynEditPlugin(TCustomSynEdit* AOwner, TPlugInHandlers AHandlers);
	virtual __fastcall ~TSynEditPlugin();
	__property TPlugInHandlers Handlers = { read = FHandlers };
	__fastcall TSynEditPlugin();
};
typedef void __fastcall (__closure *TCustomSynEditSearchNotFoundEvent) (TObject*, String);

class TCustomSynEdit : public Vcl::Controls::TCustomControl
{
private:
	HIDESBASE MESSAGE void __fastcall WMCancelMode(TMessage& Message)/*# WM_CANCELMODE */;
	MESSAGE void __fastcall WMCaptureChanged(TMessage& Msg)/*# WM_CAPTURECHANGED */;
	MESSAGE void __fastcall WMClear(TMessage& Msg)/*# WM_CLEAR */;
	MESSAGE void __fastcall WMCopy(TMessage& Message)/*# WM_COPY */;
	MESSAGE void __fastcall WMCut(TMessage& Message)/*# WM_CUT */;
	MESSAGE void __fastcall WMDropFiles(TMessage& Msg)/*# WM_DROPFILES */;
	HIDESBASE MESSAGE void __fastcall WMDestroy(TWMDestroy& Message)/*# WM_DESTROY */;
	HIDESBASE MESSAGE void __fastcall WMEraseBkgnd(TMessage& Msg)/*# WM_ERASEBKGND */;
	MESSAGE void __fastcall WMGetDlgCode(TWMGetDlgCode& Msg)/*# WM_GETDLGCODE */;
	MESSAGE void __fastcall WMGetText(TWMGetText& Msg)/*# WM_GETTEXT */;
	MESSAGE void __fastcall WMGetTextLength(TWMGetTextLength& Msg)/*# WM_GETTEXTLENGTH */;
	HIDESBASE MESSAGE void __fastcall WMHScroll(TWMScroll& Msg)/*# WM_HSCROLL */;
	MESSAGE void __fastcall WMPaste(TMessage& Message)/*# WM_PASTE */;
	MESSAGE void __fastcall WMSetText(TWMSetText& Msg)/*# WM_SETTEXT */;
	MESSAGE void __fastcall WMImeChar(TMessage& Msg)/*# WM_IME_CHAR */;
	MESSAGE void __fastcall WMImeComposition(TMessage& Msg)/*# WM_IME_COMPOSITION */;
	MESSAGE void __fastcall WMImeNotify(TMessage& Msg)/*# WM_IME_NOTIFY */;
	HIDESBASE MESSAGE void __fastcall WMKillFocus(TWMKillFocus& Msg)/*# WM_KILLFOCUS */;
	HIDESBASE MESSAGE void __fastcall WMSetCursor(TWMSetCursor& Msg)/*# WM_SETCURSOR */;
	HIDESBASE MESSAGE void __fastcall WMSetFocus(TWMSetFocus& Msg)/*# WM_SETFOCUS */;
	HIDESBASE MESSAGE void __fastcall WMSize(TWMSize& Msg)/*# WM_SIZE */;
	MESSAGE void __fastcall WMUndo(TMessage& Msg)/*# WM_UNDO */;
	HIDESBASE MESSAGE void __fastcall WMVScroll(TWMScroll& Msg)/*# WM_VSCROLL */;
//++ CodeFolding
	bool fUseCodeFolding;
	Syneditcodefolding::TSynCodeFolding* fCodeFolding;
	Syneditcodefolding::TSynFoldRanges* fAllFoldRanges;
//-- CodeFolding
	bool fAlwaysShowCaret;
	TBufferCoord fBlockBegin;
	TBufferCoord fBlockEnd;
	int fCaretX;
	int fLastCaretX;
	int fCaretY;
	int fCharsInWindow;
	int fCharWidth;
	Vcl::Graphics::TFont* fFontDummy;
	System::Uitypes::TFontQuality fFontQuality;
	bool fInserting;
	System::Classes::TStrings* FLines;
	System::Classes::TStrings* fOrigLines;
	Synedittypes::ISynEditUndo* fOrigUndoRedo;
	int fLinesInWindow;
	int fLeftChar;
	int fPaintLock;
	bool FReadOnly;
	int fRightEdge;
	TColor fRightEdgeColor;
	TColor fScrollHintColor;
	TScrollHintFormat fScrollHintFormat;
	System::Uitypes::TScrollStyle FScrollBars;
	int FTextHeight;
	int fTextMargin;
	int fTextOffset;
	int fTopLine;
	Synedithighlighter::TSynCustomHighlighter* fHighlighter;
	Syneditmiscclasses::TSynSelectedColor* FSelectedColor;
	TColor fActiveLineColor;
	Synedittypes::ISynEditUndo* fUndoRedo;
	TSynEditMark* fBookMarks[10/*# range 0..9*/]; // these are just references, fMarkList is the owner
	int fMouseDownX;
	int fMouseDownY;
	Syneditmiscclasses::TSynBookMarkOpt* fBookMarkOpt;
	TSynBorderStyle FBorderStyle;
	bool FHideSelection;
	int fMouseWheelAccumulator;
	TSynEditCaretType fOverwriteCaret;
	TSynEditCaretType fInsertCaret;
	TPoint fCaretOffset;
	Syneditkeycmds::TSynEditKeyStrokes* fKeyStrokes;
	TSynEditMarkList* fMarkList;
	int fExtraLineSpacing;
	Synedittypes::TSynSelectionMode FSelectionMode;
	Synedittypes::TSynSelectionMode fActiveSelectionMode; //mode of the active selection
	bool FWantReturns;
	bool FWantTabs;
	Synedittypes::ISynEditBufferPlugin* fWordWrapPlugin;
	Syneditmiscclasses::TSynGlyph* fWordWrapGlyph;
	bool fCaretAtEOL; // used by wordwrap
	Syneditmiscclasses::TSynGutter* fGutter;
	int FTabWidth;
	Syntextdrawer::TheTextDrawer* fTextDrawer;
	TRect fInvalidateRect;
	TSynStateFlags fStateFlags;
	TSynEditorOptions fOptions;
	TSynStatusChanges fStatusChanges;
	WORD fLastKey;
	System::Classes::TShiftState fLastShiftState;
	Syneditmiscclasses::TSynEditSearchCustom* fSearchEngine;
	System::Contnrs::TObjectList* fHookedCommandHandlers;
	Syneditkbdhandler::TSynEditKbdHandler* fKbdHandler;
	System::Classes::TList* fFocusList;
	System::Contnrs::TObjectList* fPlugins;
	Vcl::Extctrls::TTimer* FScrollTimer;
	int fScrollDeltaX;
	int fScrollDeltaY;
	System::Diagnostics::TStopwatch fClickCountTimer;
	int fClickCount;
	int FPaintTransientLock;
	bool FIsScrolling;
	System::Sysutils::TSysCharSet FAdditionalWordBreakChars;
	System::Sysutils::TSysCharSet FAdditionalIdentChars;
	int SelStartBeforeSearch;
	int SelLengthBeforeSearch;

    // event handlers
	System::Classes::TNotifyEvent FOnChange;
	TPlaceMarkEvent fOnClearMark;
	TProcessCommandEvent fOnCommandProcessed;
	TDropFilesEvent fOnDropFiles;
	TGutterClickEvent fOnGutterClick;
	TMouseCursorEvent fOnMouseCursor;
	TPaintEvent FOnPaint;
	TPlaceMarkEvent fOnPlaceMark;
	TProcessCommandEvent fOnProcessCommand;
	TProcessCommandEvent fOnProcessUserCommand;
	TReplaceTextEvent fOnReplaceText;
	TSpecialLineColorsEvent fOnSpecialLineColors;
	TContextHelpEvent fOnContextHelp;
	TPaintTransient fOnPaintTransient;
	TScrollEvent FOnScroll;
	TGutterGetTextEvent fOnGutterGetText;
	TStatusChangeEvent fOnStatusChange;
	System::Classes::TNotifyEvent fOnTripleClick;
	System::Classes::TNotifyEvent fOnQudrupleClick;
	System::Classes::TNotifyEvent fChainListCleared;
	Synedittextbuffer::TStringListChangeEvent fChainListDeleted;
	Synedittextbuffer::TStringListChangeEvent fChainListInserted;
	Synedittextbuffer::TStringListPutEvent fChainListPut;
	System::Classes::TNotifyEvent fChainLinesChanging;
	System::Classes::TNotifyEvent fChainLinesChanged;
	TCustomSynEdit* fChainedEditor;
	System::Classes::TNotifyEvent fChainModifiedChanged;
	TCustomSynEditSearchNotFoundEvent fSearchNotFound;
	System::Classes::TNotifyEvent OnFindBeforeSearch;
	System::Classes::TNotifyEvent OnReplaceBeforeSearch;
	System::Classes::TNotifyEvent OnCloseBeforeSearch;
//++ CodeFolding
	TScanForFoldRangesEvent fOnScanForFoldRanges;
	void __fastcall ReScanForFoldRanges(int FromLine, int ToLine);
	void __fastcall FullFoldScan();
	void __fastcall ScanForFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, System::Classes::TStrings* LinesToScan, int FromLine, int ToLine);
//-- CodeFolding
	void __fastcall BookMarkOptionsChanged(TObject* Sender);
	void __fastcall ComputeCaret(int X, int Y);
	void __fastcall ComputeScroll(int X, int Y);
	void __fastcall DoHomeKey(bool Selection);
	void __fastcall DoEndKey(bool Selection);
	void __fastcall DoLinesChanged();
	void __fastcall DoLinesBeforeDeleted(int FirstLine, int Count);
	void __fastcall DoLinesDeleted(int FirstLine, int Count);
	void __fastcall DoLinesInserted(int FirstLine, int Count);
	void __fastcall DoLinePut(int FirstLine, const String OldLine);
	void __fastcall DoShiftTabKey();
	void __fastcall DoTabKey();
	int __fastcall FindHookedCmdEvent(Synedittypes::THookedCommandEvent AHandlerProc);
	void __fastcall SynFontChanged(TObject* Sender);
	void __fastcall ForceCaretX(int aCaretX);
	TBufferCoord __fastcall GetBlockBegin();
	TBufferCoord __fastcall GetBlockEnd();
	bool __fastcall GetCanPaste();
	bool __fastcall GetCanRedo();
	bool __fastcall GetCanUndo();
	TBufferCoord __fastcall GetCaretXY();
	int __fastcall GetDisplayX();
	int __fastcall GetDisplayY();
	TDisplayCoord __fastcall GetDisplayXY();
	int __fastcall GetDisplayLineCount();
	Vcl::Graphics::TFont* __fastcall GetFont();
	int __fastcall GetHookedCommandHandlersCount();
	String __fastcall GetLineText();
	int __fastcall GetMaxUndo();
	bool __fastcall GetModified();
	TSynEditorOptions __fastcall GetOptions();
	bool __fastcall GetSelAvail();
	String __fastcall GetSelText();
	String __fastcall SynGetText();
	String __fastcall GetWordAtCursor();
	String __fastcall GetWordAtMouse();
	bool __fastcall GetWordWrap();
	void __fastcall GutterChanged(TObject* Sender);
	int __fastcall LeftSpaces(const String Line, bool ExpandTabs = false);
	String __fastcall GetLeftSpacing(int CharCount, bool WantTabs);
	void __fastcall LinesChanging(TObject* Sender);
	void __fastcall MoveCaretAndSelection(const TBufferCoord& ptBefore, const TBufferCoord& ptAfter, bool SelectionCommand);
	void __fastcall MoveCaretHorz(int DX, bool SelectionCommand);
	void __fastcall MoveCaretVert(int DY, bool SelectionCommand);
	void __fastcall PluginsAfterPaint(Vcl::Graphics::TCanvas* ACanvas, const TRect& AClip, int FirstLine, int LastLine);
	void __fastcall ReadAddedKeystrokes(System::Classes::TReader* Reader);
	void __fastcall ReadRemovedKeystrokes(System::Classes::TReader* Reader);
	int __fastcall ScanFrom(int Index);
	void __fastcall ScrollTimerHandler(TObject* Sender);
	void __fastcall SelectedColorsChanged(TObject* Sender);
	void __fastcall SetBlockBegin(const TBufferCoord& Value);
	void __fastcall SetBlockEnd(const TBufferCoord& Value);
	void __fastcall SetBorderStyle(TSynBorderStyle Value);
	void __fastcall SetCaretX(int Value);
	void __fastcall SetCaretY(int Value);
	void __fastcall InternalSetCaretX(int Value);
	void __fastcall InternalSetCaretY(int Value);
	void __fastcall SetInternalDisplayXY(const TDisplayCoord& APos);
	void __fastcall SetActiveLineColor(TColor Value);
	void __fastcall SetExtraLineSpacing(int Value);
	void __fastcall SetFont(Vcl::Graphics::TFont* const Value);
	void __fastcall SetGutter(Syneditmiscclasses::TSynGutter* const Value);
	void __fastcall SetGutterWidth(int Value);
	void __fastcall SetHideSelection(bool Value);
	void __fastcall SetHighlighter(Synedithighlighter::TSynCustomHighlighter* const Value);
	void __fastcall SetInsertCaret(TSynEditCaretType Value);
	void __fastcall SetInsertMode(bool Value);
	void __fastcall SetKeystrokes(Syneditkeycmds::TSynEditKeyStrokes* const Value);
	void __fastcall SetLeftChar(int Value);
	void __fastcall SetLines(System::Classes::TStrings* Value);
	void __fastcall SetLineText(String Value);
	void __fastcall SetMaxUndo(int Value);
	void __fastcall SetModified(bool Value);
	void __fastcall SetOptions(TSynEditorOptions Value);
	void __fastcall SetOverwriteCaret(TSynEditCaretType Value);
	void __fastcall SetRightEdge(int Value);
	void __fastcall SetRightEdgeColor(TColor Value);
	void __fastcall SetScrollBars(System::Uitypes::TScrollStyle Value);
	void __fastcall SetSearchEngine(Syneditmiscclasses::TSynEditSearchCustom* Value);
	void __fastcall SetSelectionMode(Synedittypes::TSynSelectionMode Value);
	void __fastcall SetActiveSelectionMode(Synedittypes::TSynSelectionMode Value);
	void __fastcall SetTabWidth(int Value);
	void __fastcall SynSetText(const String Value);
	void __fastcall SetTopLine(int Value);
	void __fastcall SetWordWrap(bool Value);
	void __fastcall SetWordWrapGlyph(Syneditmiscclasses::TSynGlyph* const Value);
	void __fastcall WordWrapGlyphChange(TObject* Sender);
	void __fastcall SizeOrFontChanged(bool bFont);
	void __fastcall ProperSetLine(int ALine, const String ALineText);
	void __fastcall ModifiedChanged(TObject* Sender);
	void __fastcall UpdateLastCaretX();
	void __fastcall UpdateScrollBars();
	void __fastcall WriteAddedKeystrokes(System::Classes::TWriter* Writer);
	void __fastcall WriteRemovedKeystrokes(System::Classes::TWriter* Writer);
	void __fastcall SetAdditionalIdentChars(const System::Sysutils::TSysCharSet Value);
	void __fastcall SetAdditionalWordBreakChars(const System::Sysutils::TSysCharSet Value);
	void __fastcall DoSearchFindFirstExecute(Vcl::Stdactns::TSearchFindFirst* Action);
	void __fastcall DoSearchFindExecute(Vcl::Stdactns::TSearchFind* Action);
	void __fastcall DoSearchReplaceExecute(Vcl::Stdactns::TSearchReplace* Action);
	void __fastcall DoSearchFindNextExecute(Vcl::Stdactns::TSearchFindNext* Action);
	void __fastcall FindDialogFindFirst(TObject* Sender);
	void __fastcall FindDialogFind(TObject* Sender);
	BOOL __fastcall SearchByFindDialog(Vcl::Dialogs::TFindDialog* FindDialog);
	void __fastcall FindDialogClose(TObject* Sender);
	void __fastcall DoMouseSelectLineRange(const TBufferCoord& NewPos);
	void __fastcall DoMouseSelectWordRange(const TBufferCoord& NewPos);
//++ CodeFolding
	void __fastcall SetUseCodeFolding(bool Value);
	void __fastcall OnCodeFoldingChange(TObject* Sender);
	TRect __fastcall GetCollapseMarkRect(int Row, int Line = -1);
//-- CodeFolding
protected:
	bool FIgnoreNextChar;
	String FCharCodeString;
	DYNAMIC bool __fastcall DoMouseWheel(System::Classes::TShiftState Shift, int WheelDelta, const TPoint& MousePos);
	virtual void __fastcall CreateParams(Vcl::Controls::TCreateParams& Params);
	virtual void __fastcall CreateWnd();
	virtual void __fastcall InvalidateRect(const TRect& ARect, bool aErase);
	DYNAMIC void __fastcall DblClick();
	virtual void __fastcall TripleClick();
	virtual void __fastcall QuadrupleClick();
	void __fastcall DecPaintLock();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall DoChange();
    //++ Ole Drag & Drop
	virtual void __fastcall OleDragEnter(TObject* Sender, IDataObject* dataObject, System::Classes::TShiftState State, const TPoint& MousePt, int& Effect, HRESULT& result);
	virtual void __fastcall OleDragOver(TObject* Sender, IDataObject* dataObject, System::Classes::TShiftState State, const TPoint& MousePt, int& Effect, HRESULT& result);
	virtual void __fastcall OleDrop(TObject* Sender, IDataObject* dataObject, System::Classes::TShiftState State, const TPoint& MousePt, int& Effect, HRESULT& result);
	virtual void __fastcall OleDragLeave(TObject* Sender, HRESULT& result);
    //-- Ole Drag & Drop
	virtual bool __fastcall GetReadOnly();
	void __fastcall HighlighterAttrChanged(TObject* Sender);
	void __fastcall IncPaintLock();
	void __fastcall InitializeCaret();
	DYNAMIC void __fastcall KeyUp(WORD& key, System::Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyDown(WORD& key, System::Classes::TShiftState Shift);
	DYNAMIC void __fastcall KeyPress(Char& key);
	virtual void __fastcall LinesChanged(TObject* Sender);
	void __fastcall ListCleared(TObject* Sender);
	void __fastcall ListBeforeDeleted(TObject* Sender, int AIndex, int ACount);
	void __fastcall ListDeleted(TObject* Sender, int AIndex, int ACount);
	void __fastcall ListInserted(TObject* Sender, int Index, int ACount);
	void __fastcall ListPut(TObject* Sender, int Index, const String OldLine);
    //helper procs to chain list commands
	void __fastcall ChainListCleared(TObject* Sender);
	void __fastcall ChainListDeleted(TObject* Sender, int AIndex, int ACount);
	void __fastcall ChainListInserted(TObject* Sender, int AIndex, int ACount);
	void __fastcall ChainListPut(TObject* Sender, int AIndex, const String OldLine);
	void __fastcall ChainLinesChanging(TObject* Sender);
	void __fastcall ChainLinesChanged(TObject* Sender);
	void __fastcall ChainModifiedChanged(TObject* Sender);
	void __fastcall ScanRanges();
	virtual void __fastcall Loaded();
	void __fastcall MarkListChange(TObject* Sender);
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall NotifyHookedCommandHandlers(bool AfterProcessing, Synedittypes::TSynEditorCommand& Command, WideChar& AChar, void* Data);
	virtual void __fastcall Paint();
	virtual void __fastcall PaintGutter(const TRect& AClip, int aFirstRow, int aLastRow);
	virtual void __fastcall PaintTextLines(const TRect& AClip, int aFirstRow, int aLastRow, int FirstCol, int LastCol);
	void __fastcall RecalcCharExtent();
	virtual void __fastcall InternalSetCaretXY(const TBufferCoord& Value);
	virtual void __fastcall SetCaretXY(const TBufferCoord& Value);
	virtual void __fastcall SetCaretXYEx(bool CallEnsureCursorPos, const TBufferCoord& Value);
	void __fastcall SetFontQuality(System::Uitypes::TFontQuality AValue);
	virtual void __fastcall SetName(const System::Classes::TComponentName Value);
	virtual void __fastcall SetReadOnly(bool Value);
	void __fastcall SetWantReturns(bool Value);
	void __fastcall SetSelText(const String Value);
	void __fastcall SetSelTextPrimitiveEx(Synedittypes::TSynSelectionMode PasteMode, String Value, bool AddToUndoList = true, bool SilentDelete = false);
	void __fastcall SetWantTabs(bool Value);
	void __fastcall StatusChanged(TSynStatusChanges AChanges);
    // If the translations requires Data, memory will be allocated for it via a
    // GetMem call.  The client must call FreeMem on Data if it is not NIL.
	Synedittypes::TSynEditorCommand __fastcall TranslateKeyCode(WORD Code, System::Classes::TShiftState Shift, void*& Data);
	virtual void __fastcall UpdateMouseCursor();
	int fGutterWidth;
	void __fastcall HideCaret();
	void __fastcall ShowCaret();
	virtual void __fastcall DoOnClearBookmark(TSynEditMark*& Mark);
	virtual void __fastcall DoOnCommandProcessed(Synedittypes::TSynEditorCommand Command, WideChar AChar, void* Data);
	virtual void __fastcall DoOnGutterClick(System::Uitypes::TMouseButton Button, int X, int Y);
	virtual void __fastcall DoOnPaint();
	virtual void __fastcall DoOnPaintTransientEx(TTransientType TransientType, bool Lock);
	virtual void __fastcall DoOnPaintTransient(TTransientType TransientType);
	virtual void __fastcall DoOnPlaceMark(TSynEditMark*& Mark);
	virtual void __fastcall DoOnProcessCommand(Synedittypes::TSynEditorCommand& Command, WideChar& AChar, void* Data);
	virtual TSynReplaceAction __fastcall DoOnReplaceText(const String ASearch, const String AReplace, int Line, int Column);
	virtual bool __fastcall DoOnSpecialLineColors(int Line, TColor& Foreground, TColor& Background);
	virtual void __fastcall DoOnStatusChange(TSynStatusChanges Changes);
	int __fastcall GetSelEnd();
	int __fastcall GetSelStart();
	int __fastcall GetSelLength();
	void __fastcall SetSelEnd(int Value);
	void __fastcall SetSelStart(int Value);
	void __fastcall SetSelLength(int Value);
	void __fastcall SetAlwaysShowCaret(bool Value);
	String __fastcall ShrinkAtWideGlyphs(const String s, int First, int& CharCount);
	void __fastcall LinesHookChanged();
	__property int InternalCaretX = { write = InternalSetCaretX };
	__property int InternalCaretY = { write = InternalSetCaretY };
	__property TBufferCoord InternalCaretXY = { write = InternalSetCaretXY };
	__property System::Uitypes::TFontQuality FontQuality = { read = fFontQuality, write = SetFontQuality };
//++ DPI-Aware
	DYNAMIC void __fastcall ChangeScale(int m, int D, bool isDpiChange);
//-- DPI-Aware
public:
	typedef Vcl::Controls::TCustomControl inherited;	
	#include "SynEdit_friends.inc"
	__fastcall TCustomSynEdit(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TCustomSynEdit();
	__property  Canvas;
	__property int SelStart = { read = GetSelStart, write = SetSelStart };
	__property int SelEnd = { read = GetSelEnd, write = SetSelEnd };
	__property bool AlwaysShowCaret = { read = fAlwaysShowCaret, write = SetAlwaysShowCaret };
	void __fastcall UpdateCaret();
	void __fastcall AddKey(Synedittypes::TSynEditorCommand Command, WORD Key1, System::Classes::TShiftState SS1, WORD Key2 = 0, System::Classes::TShiftState SS2 = SynEdit__0);
	void __fastcall BeginUndoBlock();
	void __fastcall BeginUpdate();
	bool __fastcall CaretInView();
	TBufferCoord __fastcall CharIndexToRowCol(int Index);
	void __fastcall Clear();
	void __fastcall ClearAll();
	void __fastcall ClearBookMark(int BookMark);
	void __fastcall ClearSelection();
	virtual void __fastcall CommandProcessor(Synedittypes::TSynEditorCommand Command, WideChar AChar, void* Data);
	void __fastcall ClearUndo();
	void __fastcall CopyToClipboard();
	void __fastcall CutToClipboard();
	void __fastcall DoCopyToClipboard(const String SText);
	void __fastcall EndUndoBlock();
	void __fastcall EndUpdate();
	void __fastcall EnsureCursorPosVisible();
	void __fastcall EnsureCursorPosVisibleEx(bool ForceToMiddle, bool EvenIfVisible = false);
	virtual void __fastcall FindMatchingBracket();
	virtual TBufferCoord __fastcall GetMatchingBracket();
	virtual TBufferCoord __fastcall GetMatchingBracketEx(const TBufferCoord& APoint, String Brackets = L"()[]{}<>");
	DYNAMIC bool __fastcall ExecuteAction(System::Classes::TBasicAction* Action);
	virtual void __fastcall ExecuteCommand(Synedittypes::TSynEditorCommand Command, WideChar AChar, void* Data);
	String __fastcall ExpandAtWideGlyphs(const String s);
	bool __fastcall GetBookMark(int BookMark, int& X, int& Y);
	bool __fastcall GetHighlighterAttriAtRowCol(const TBufferCoord& XY, String& Token, Synedithighlighter::TSynHighlighterAttributes*& Attri);
	bool __fastcall GetHighlighterAttriAtRowColEx(const TBufferCoord& XY, String& Token, int& TokenType, int& Start, Synedithighlighter::TSynHighlighterAttributes*& Attri);
	bool __fastcall GetPositionOfMouse(TBufferCoord& APos);
	String __fastcall GetWordAtRowCol(const TBufferCoord& XY);
	virtual void __fastcall GotoBookMark(int BookMark);
	virtual void __fastcall GotoLineAndCenter(int ALine);
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual bool __fastcall IsWhiteChar(WideChar AChar);
	virtual bool __fastcall IsWordBreakChar(WideChar AChar);
    // support procedure for ecDeletexxx commands
	virtual bool __fastcall IsNonWhiteChar(WideChar AChar);
	void __fastcall DoBlockIndent();
	void __fastcall DoBlockUnindent();
	void __fastcall InvalidateGutter();
	void __fastcall InvalidateGutterLine(int ALine);
	void __fastcall InvalidateGutterLines(int FirstLine, int LastLine);
	void __fastcall InvalidateLine(int Line);
	void __fastcall InvalidateLines(int FirstLine, int LastLine);
	void __fastcall InvalidateSelection();
	bool __fastcall IsBookmark(int BookMark);
	bool __fastcall IsPointInSelection(const TBufferCoord& Value);
	void __fastcall LockUndo();
	TDisplayCoord __fastcall BufferToDisplayPos(const TBufferCoord& P);
	TBufferCoord __fastcall DisplayToBufferPos(const TDisplayCoord& P);
	int __fastcall LineToRow(int ALine);
	int __fastcall RowToLine(int ARow);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall PasteFromClipboard();
	virtual TBufferCoord __fastcall NextWordPos();
	virtual TBufferCoord __fastcall NextWordPosEx(const TBufferCoord& XY);
	virtual TBufferCoord __fastcall WordStart();
	virtual TBufferCoord __fastcall WordStartEx(const TBufferCoord& XY);
	virtual TBufferCoord __fastcall WordEnd();
	virtual TBufferCoord __fastcall WordEndEx(const TBufferCoord& XY);
	virtual TBufferCoord __fastcall PrevWordPos();
	virtual TBufferCoord __fastcall PrevWordPosEx(const TBufferCoord& XY);
	TDisplayCoord __fastcall PixelsToRowColumn(int AX, int AY);
	TDisplayCoord __fastcall PixelsToNearestRowColumn(int AX, int AY);
	void __fastcall Redo();
	void __fastcall RegisterCommandHandler(const Synedittypes::THookedCommandEvent AHandlerProc, void* AHandlerData);
	TPoint __fastcall RowColumnToPixels(const TDisplayCoord& RowCol);
	int __fastcall RowColToCharIndex(const TBufferCoord& RowCol);
	int __fastcall SearchReplace(const String ASearch, const String AReplace, Synedittypes::TSynSearchOptions AOptions);
	void __fastcall SelectAll();
	void __fastcall SetBookMark(int BookMark, int X, int Y);
	void __fastcall SetCaretAndSelection(const TBufferCoord& ptCaret, const TBufferCoord& ptBefore, const TBufferCoord& ptAfter);
	virtual void __fastcall SetDefaultKeystrokes();
	void __fastcall SetSelWord();
	void __fastcall SetWordBlock(const TBufferCoord& Value);
	void __fastcall Undo();
	void __fastcall UnlockUndo();
	void __fastcall UnregisterCommandHandler(Synedittypes::THookedCommandEvent AHandlerProc);
	virtual bool __fastcall UpdateAction(System::Classes::TBasicAction* Action);
	virtual void __fastcall SetFocus();
	void __fastcall AddKeyUpHandler(Vcl::Controls::TKeyEvent aHandler);
	void __fastcall RemoveKeyUpHandler(Vcl::Controls::TKeyEvent aHandler);
	void __fastcall AddKeyDownHandler(Vcl::Controls::TKeyEvent aHandler);
	void __fastcall RemoveKeyDownHandler(Vcl::Controls::TKeyEvent aHandler);
	void __fastcall AddKeyPressHandler(Vcl::Controls::TKeyPressEvent aHandler);
	void __fastcall RemoveKeyPressHandler(Vcl::Controls::TKeyPressEvent aHandler);
	void __fastcall AddFocusControl(Vcl::Controls::TWinControl* AControl);
	void __fastcall RemoveFocusControl(Vcl::Controls::TWinControl* AControl);
	void __fastcall AddMouseDownHandler(Vcl::Controls::TMouseEvent aHandler);
	void __fastcall RemoveMouseDownHandler(Vcl::Controls::TMouseEvent aHandler);
	void __fastcall AddMouseUpHandler(Vcl::Controls::TMouseEvent aHandler);
	void __fastcall RemoveMouseUpHandler(Vcl::Controls::TMouseEvent aHandler);
	void __fastcall AddMouseCursorHandler(TMouseCursorEvent aHandler);
	void __fastcall RemoveMouseCursorHandler(TMouseCursorEvent aHandler);
	virtual void __fastcall WndProc(TMessage& Msg);
	void __fastcall SetLinesPointer(TCustomSynEdit* ASynEdit);
	void __fastcall RemoveLinesPointer();
	bool __fastcall IsChained();
	void __fastcall HookTextBuffer(Synedittextbuffer::TSynEditStringList* ABuffer, Synedittypes::ISynEditUndo* aUndoRedo);
	void __fastcall UnHookTextBuffer();
    /*Command implementations*/
	void __fastcall ExecCmdDeleteLine();
	void __fastcall ExecCmdCopyOrMoveLine(Synedittypes::TSynEditorCommand Command);
	void __fastcall ExecCmdCaseChange(Synedittypes::TSynEditorCommand cmd);
//++ CodeFolding
	void __fastcall CollapseAll();
	void __fastcall UncollapseAll();
	void __fastcall Collapse(int FoldRangeIndex, bool Invalidate = true);
	void __fastcall Uncollapse(int FoldRangeIndex, bool Invalidate = true);
	void __fastcall UncollapseAroundLine(int Line);
	void __fastcall CollapseNearest();
	void __fastcall UncollapseNearest();
	void __fastcall CollapseLevel(int Level);
	void __fastcall UnCollapseLevel(int Level);
	void __fastcall CollapseFoldType(int FoldType);
	void __fastcall UnCollapseFoldType(int FoldType);
//-- CodeFolding
	__property System::Sysutils::TSysCharSet AdditionalIdentChars = { read = FAdditionalIdentChars, write = SetAdditionalIdentChars };
	__property System::Sysutils::TSysCharSet AdditionalWordBreakChars = { read = FAdditionalWordBreakChars, write = SetAdditionalWordBreakChars };
	__property TBufferCoord BlockBegin = { read = GetBlockBegin, write = SetBlockBegin };
	__property TBufferCoord BlockEnd = { read = GetBlockEnd, write = SetBlockEnd };
	__property bool CanPaste = { read = GetCanPaste };
	__property bool CanRedo = { read = GetCanRedo };
	__property bool CanUndo = { read = GetCanUndo };
	__property int CaretX = { read = fCaretX, write = SetCaretX };
	__property int CaretY = { read = fCaretY, write = SetCaretY };
	__property TBufferCoord CaretXY = { read = GetCaretXY, write = SetCaretXY };
	__property TColor ActiveLineColor = { read = fActiveLineColor, write = SetActiveLineColor, default = clNone };
	__property int DisplayX = { read = GetDisplayX };
	__property int DisplayY = { read = GetDisplayY };
	__property TDisplayCoord DisplayXY = { read = GetDisplayXY };
	__property int DisplayLineCount = { read = GetDisplayLineCount };
	__property int CharsInWindow = { read = fCharsInWindow };
	__property int CharWidth = { read = fCharWidth };
	__property  Color;
	__property  Cursor = { default = /*# crIBeam */ -4 };
	__property Vcl::Graphics::TFont* Font = { read = GetFont, write = SetFont };
	__property Synedithighlighter::TSynCustomHighlighter* Highlighter = { read = fHighlighter, write = SetHighlighter };
	__property int LeftChar = { read = fLeftChar, write = SetLeftChar };
	__property int LineHeight = { read = FTextHeight };
	__property int LinesInWindow = { read = fLinesInWindow };
	__property String LineText = { read = GetLineText, write = SetLineText };
	__property System::Classes::TStrings* Lines = { read = FLines, write = SetLines };
	__property TSynEditMarkList* Marks = { read = fMarkList };
	__property bool Modified = { read = GetModified, write = SetModified };
	__property int PaintLock = { read = fPaintLock };
	__property bool ReadOnly = { read = GetReadOnly, write = SetReadOnly, default = false };
	__property Syneditmiscclasses::TSynEditSearchCustom* SearchEngine = { read = fSearchEngine, write = SetSearchEngine };
	__property bool SelAvail = { read = GetSelAvail };
	__property int SelLength = { read = GetSelLength, write = SetSelLength };
	__property String SelText = { read = GetSelText, write = SetSelText };
	__property TSynStateFlags StateFlags = { read = fStateFlags };
	__property String Text = { read = SynGetText, write = SynSetText };
	__property int TopLine = { read = fTopLine, write = SetTopLine };
	__property String WordAtCursor = { read = GetWordAtCursor };
	__property String WordAtMouse = { read = GetWordAtMouse };
	__property int GutterWidth = { read = fGutterWidth };
	__property int TextMargin = { read = fTextMargin };
	__property Synedittypes::ISynEditUndo* UndoRedo = { read = fUndoRedo };
	__property TProcessCommandEvent OnProcessCommand = { read = fOnProcessCommand, write = fOnProcessCommand };

//++ CodeFolding
	__property Syneditcodefolding::TSynCodeFolding* CodeFolding = { read = fCodeFolding, write = fCodeFolding };
	__property bool UseCodeFolding = { read = fUseCodeFolding, write = SetUseCodeFolding };
	__property Syneditcodefolding::TSynFoldRanges* AllFoldRanges = { read = fAllFoldRanges };
//-- CodeFolding
	__property Syneditmiscclasses::TSynBookMarkOpt* BookMarkOptions = { read = fBookMarkOpt, write = fBookMarkOpt };
	__property TSynBorderStyle BorderStyle = { read = FBorderStyle, write = SetBorderStyle, default = /*# bsSingle */ 1 };
	__property int ExtraLineSpacing = { read = fExtraLineSpacing, write = SetExtraLineSpacing, default = 0 };
	__property Syneditmiscclasses::TSynGutter* Gutter = { read = fGutter, write = SetGutter };
	__property bool HideSelection = { read = FHideSelection, write = SetHideSelection, default = false };
	__property TSynEditCaretType InsertCaret = { read = fInsertCaret, write = SetInsertCaret, default = /*# ctVerticalLine */ 0 };
	__property bool InsertMode = { read = fInserting, write = SetInsertMode, default = true };
	__property bool IsScrolling = { read = FIsScrolling };
	__property Syneditkeycmds::TSynEditKeyStrokes* Keystrokes = { read = fKeyStrokes, write = SetKeystrokes, stored = false };
	__property int MaxUndo = { read = GetMaxUndo, write = SetMaxUndo, default = 0 };
	__property TSynEditorOptions Options = { read = GetOptions, write = SetOptions, default = /*# SYNEDIT_DEFAULT_OPTIONS */ 0 };
	__property TSynEditCaretType OverwriteCaret = { read = fOverwriteCaret, write = SetOverwriteCaret, default = /*# ctBlock */ 3 };
	__property int RightEdge = { read = fRightEdge, write = SetRightEdge, default = 80 };
	__property TColor RightEdgeColor = { read = fRightEdgeColor, write = SetRightEdgeColor, default = clSilver };
	__property TColor ScrollHintColor = { read = fScrollHintColor, write = fScrollHintColor, default = clInfoBk };
	__property TScrollHintFormat ScrollHintFormat = { read = fScrollHintFormat, write = fScrollHintFormat, default = /*# shfTopLineOnly */ 0 };
	__property System::Uitypes::TScrollStyle ScrollBars = { read = FScrollBars, write = SetScrollBars, default = /*# ssBoth */ 3 };
	__property Syneditmiscclasses::TSynSelectedColor* SelectedColor = { read = FSelectedColor, write = FSelectedColor };
	__property Synedittypes::TSynSelectionMode SelectionMode = { read = FSelectionMode, write = SetSelectionMode, default = /*# smNormal */ 0 };
	__property Synedittypes::TSynSelectionMode ActiveSelectionMode = { read = fActiveSelectionMode, write = SetActiveSelectionMode, stored = false };
	__property int TabWidth = { read = FTabWidth, write = SetTabWidth, default = 8 };
	__property bool WantReturns = { read = FWantReturns, write = SetWantReturns, default = true };
	__property bool WantTabs = { read = FWantTabs, write = SetWantTabs, default = false };
	__property bool WordWrap = { read = GetWordWrap, write = SetWordWrap, default = false };
	__property Syneditmiscclasses::TSynGlyph* WordWrapGlyph = { read = fWordWrapGlyph, write = SetWordWrapGlyph };
	__property System::Classes::TNotifyEvent OnChange = { read = FOnChange, write = FOnChange };
	__property TPlaceMarkEvent OnClearBookmark = { read = fOnClearMark, write = fOnClearMark };
	__property TProcessCommandEvent OnCommandProcessed = { read = fOnCommandProcessed, write = fOnCommandProcessed };
	__property TContextHelpEvent OnContextHelp = { read = fOnContextHelp, write = fOnContextHelp };
	__property TDropFilesEvent OnDropFiles = { read = fOnDropFiles, write = fOnDropFiles };
	__property TGutterClickEvent OnGutterClick = { read = fOnGutterClick, write = fOnGutterClick };
	__property TGutterGetTextEvent OnGutterGetText = { read = fOnGutterGetText, write = fOnGutterGetText };
	__property TMouseCursorEvent OnMouseCursor = { read = fOnMouseCursor, write = fOnMouseCursor };
	__property TPaintEvent OnPaint = { read = FOnPaint, write = FOnPaint };
	__property TPlaceMarkEvent OnPlaceBookmark = { read = fOnPlaceMark, write = fOnPlaceMark };
	__property TProcessCommandEvent OnProcessUserCommand = { read = fOnProcessUserCommand, write = fOnProcessUserCommand };
	__property TReplaceTextEvent OnReplaceText = { read = fOnReplaceText, write = fOnReplaceText };
	__property TSpecialLineColorsEvent OnSpecialLineColors = { read = fOnSpecialLineColors, write = fOnSpecialLineColors };
	__property TStatusChangeEvent OnStatusChange = { read = fOnStatusChange, write = fOnStatusChange };
	__property TPaintTransient OnPaintTransient = { read = fOnPaintTransient, write = fOnPaintTransient };
	__property TScrollEvent OnScroll = { read = FOnScroll, write = FOnScroll };
	__property System::Classes::TNotifyEvent OnTripleClick = { read = fOnTripleClick, write = fOnTripleClick };
	__property System::Classes::TNotifyEvent OnQuadrupleClick = { read = fOnQudrupleClick, write = fOnQudrupleClick };
//++ CodeFolding
	__property TScanForFoldRangesEvent OnScanForFoldRanges = { read = fOnScanForFoldRanges, write = fOnScanForFoldRanges };
//-- CodeFolding
	__property TCustomSynEditSearchNotFoundEvent OnSearchNotFound = { read = fSearchNotFound, write = fSearchNotFound };
protected:
	BEGIN_MESSAGE_MAP
	  VCL_MESSAGE_HANDLER(WM_CANCELMODE, TMessage, WMCancelMode)
	  VCL_MESSAGE_HANDLER(WM_CAPTURECHANGED, TMessage, WMCaptureChanged)
	  VCL_MESSAGE_HANDLER(WM_CLEAR, TMessage, WMClear)
	  VCL_MESSAGE_HANDLER(WM_COPY, TMessage, WMCopy)
	  VCL_MESSAGE_HANDLER(WM_CUT, TMessage, WMCut)
	  VCL_MESSAGE_HANDLER(WM_DESTROY, TWMDestroy, WMDestroy)
	  VCL_MESSAGE_HANDLER(WM_DROPFILES, TMessage, WMDropFiles)
	  VCL_MESSAGE_HANDLER(WM_ERASEBKGND, TMessage, WMEraseBkgnd)
	  VCL_MESSAGE_HANDLER(WM_GETDLGCODE, TWMGetDlgCode, WMGetDlgCode)
	  VCL_MESSAGE_HANDLER(WM_GETTEXT, TWMGetText, WMGetText)
	  VCL_MESSAGE_HANDLER(WM_GETTEXTLENGTH, TWMGetTextLength, WMGetTextLength)
	  VCL_MESSAGE_HANDLER(WM_HSCROLL, TWMScroll, WMHScroll)
	  VCL_MESSAGE_HANDLER(WM_IME_CHAR, TMessage, WMImeChar)
	  VCL_MESSAGE_HANDLER(WM_IME_COMPOSITION, TMessage, WMImeComposition)
	  VCL_MESSAGE_HANDLER(WM_IME_NOTIFY, TMessage, WMImeNotify)
	  VCL_MESSAGE_HANDLER(WM_KILLFOCUS, TWMKillFocus, WMKillFocus)
	  VCL_MESSAGE_HANDLER(WM_PASTE, TMessage, WMPaste)
	  VCL_MESSAGE_HANDLER(WM_SETCURSOR, TWMSetCursor, WMSetCursor)
	  VCL_MESSAGE_HANDLER(WM_SETFOCUS, TWMSetFocus, WMSetFocus)
	  VCL_MESSAGE_HANDLER(WM_SETTEXT, TWMSetText, WMSetText)
	  VCL_MESSAGE_HANDLER(WM_SIZE, TWMSize, WMSize)
	  VCL_MESSAGE_HANDLER(WM_UNDO, TMessage, WMUndo)
	  VCL_MESSAGE_HANDLER(WM_VSCROLL, TWMScroll, WMVScroll)
	END_MESSAGE_MAP(Vcl::Controls::TCustomControl)
public:
	__fastcall TCustomSynEdit(HWND ParentWindow);
};

class TSynEdit : public TCustomSynEdit
{
__published:
    // inherited properties
	__property  Align;
	__property  Anchors;
	__property  DoubleBuffered;
	__property  Constraints;
	__property  Color;
	__property  ActiveLineColor;
	__property  Ctl3D;
	__property  Cursor;
	__property  ParentCtl3D;
	__property  Enabled;
	__property  Font;
	__property  Height;
	__property  Name;
	__property  ParentDoubleBuffered;
	__property  ParentColor = { default = false };
	__property  ParentFont = { default = false };
	__property  ParentShowHint;
	__property  PopupMenu;
	__property  ShowHint;
	__property  TabOrder;
	__property  TabStop = { default = true };
	__property  Visible;
	__property  Width;
    // inherited events
	__property  OnClick;
	__property  OnDblClick;
	__property  OnDragDrop;
	__property  OnDragOver;
	__property  OnEndDock;
	__property  OnStartDock;
	__property  OnEndDrag;
	__property  OnEnter;
	__property  OnExit;
	__property  OnKeyDown;
	__property  OnKeyPress;
	__property  OnKeyUp;
	__property  OnMouseDown;
	__property  OnMouseMove;
	__property  OnMouseUp;
	__property  OnMouseWheel;
	__property  OnMouseWheelDown;
	__property  OnMouseWheelUp;
	__property  OnStartDrag;
    // TCustomSynEdit properties
//++ CodeFolding
	__property  CodeFolding;
	__property  UseCodeFolding;
//-- CodeFolding
	__property  BookMarkOptions;
	__property  BorderStyle;
	__property  ExtraLineSpacing;
	__property  FontQuality = { default = /*# fqClearTypeNatural */ 6 };
	__property  Gutter;
	__property  HideSelection;
	__property  Highlighter;
	__property  ImeMode;
	__property  ImeName;
	__property  InsertCaret;
	__property  InsertMode;
	__property  Keystrokes;
	__property  Lines;
	__property  MaxUndo;
	__property  Options;
	__property  OverwriteCaret;
	__property  ReadOnly;
	__property  RightEdge;
	__property  RightEdgeColor;
	__property  ScrollHintColor;
	__property  ScrollHintFormat;
	__property  ScrollBars;
	__property  SearchEngine;
	__property  SelectedColor;
	__property  SelectionMode;
	__property  TabWidth;
	__property  WantReturns;
	__property  WantTabs;
	__property  WordWrap;
	__property  WordWrapGlyph;
    // TCustomSynEdit events
	__property  OnChange;
	__property  OnClearBookmark;
	__property  OnCommandProcessed;
	__property  OnContextHelp;
	__property  OnContextPopup;
	__property  OnDropFiles;
	__property  OnGutterClick;
	__property  OnGutterGetText;
	__property  OnMouseCursor;
	__property  OnPaint;
	__property  OnPlaceBookmark;
	__property  OnProcessCommand;
	__property  OnProcessUserCommand;
	__property  OnReplaceText;
	__property  OnScroll;
	__property  OnSpecialLineColors;
	__property  OnStatusChange;
	__property  OnPaintTransient;
	__property  OnTripleClick;
	__property  OnQuadrupleClick;
	__property  OnSearchNotFound;
//++ CodeFolding
	__property  OnScanForFoldRanges;
//-- CodeFolding
public:
	typedef TCustomSynEdit inherited;	
	#include "SynEdit_friends.inc"
	__fastcall TSynEdit(System::Classes::TComponent* AOwner);
	__fastcall TSynEdit(HWND ParentWindow);
};


}  // namespace SynEdit

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synedit;
#endif

#endif // SynEditH

