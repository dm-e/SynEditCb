/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynCompletionProposal.pas, released 2000-04-11.
The Original Code is based on mwCompletionProposal.pas by Cyrille de Brebisson,
part of the mwEdit component suite.
Portions created by Cyrille de Brebisson are Copyright (C) 1999
Cyrille de Brebisson.
Unicode translation by Ma?l H?rz.
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
#ifndef SynCompletionProposalH
#define SynCompletionProposalH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ImgList.hpp>
#include "SynEditTypes.h"
#include "SynEditKeyCmds.h"
#include "SynEdit.h"
#include "SynUnicode.h"

namespace Syncompletionproposal
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
enum SynCompletionType {ctCode,
                        ctHint,
                        ctParams };
typedef TCustomForm TSynForm;
typedef void __fastcall (__closure *TSynBaseCompletionProposalPaintItem) (TObject*, int, TCanvas*, const TRect&, bool&);
typedef void __fastcall (__closure *TSynBaseCompletionProposalMeasureItem) (TObject*, int, TCanvas*, int&);
typedef void __fastcall (__closure *TCodeCompletionEvent) (TObject*, String&, TShiftState, int, WideChar);
typedef void __fastcall (__closure *TAfterCodeCompletionEvent) (TObject*, const String, TShiftState, int, WideChar);
typedef void __fastcall (__closure *TValidateEvent) (TObject*, TShiftState, WideChar);
typedef void __fastcall (__closure *TCompletionParameter) (TObject*, int, int&, int&, WideChar&, String&);
typedef void __fastcall (__closure *TCompletionExecute) (SynCompletionType, TObject*, String&, int&, int&, bool&);
typedef void __fastcall (__closure *TCompletionChange) (TObject*, int);         //Use case sensitivity to do matches
    //Limit the matched text to only what they have typed in
       //Center the title in the box if you choose to use titles
         //Use the InsertList to insert text instead of the ItemList (which will be displayed)
         //Use the PrettyText function to output the words
       //Use the built in timer and the trigger keys to execute the proposal as well as the shortcut
     //When an end char is pressed, it triggers completion to occur (like the Delphi IDE)
//Use word break characters as additional end characters
       //Use the tab character for completion
enum TSynCompletionOption {scoCaseSensitive,
                           scoLimitToMatchedText,
                           scoTitleIsCentered,
                           scoUseInsertList,
                           scoUsePrettyText,
                           scoUseBuiltInTimer,
                           scoEndCharCompletion,
                           scoConsiderWordBreakChars,
                           scoCompleteWithTab,
                           scoCompleteWithEnter };
    //Use the Enter character for completion
typedef System::Set<TSynCompletionOption, TSynCompletionOption::scoCaseSensitive, TSynCompletionOption::scoCompleteWithEnter> TSynCompletionOptions;
const System::Set<TSynCompletionOption, TSynCompletionOption::scoCaseSensitive, TSynCompletionOption::scoCompleteWithEnter> DefaultProposalOptions = System::Set<TSynCompletionOption, TSynCompletionOption::scoCaseSensitive, TSynCompletionOption::scoCompleteWithEnter>() << Syncompletionproposal::scoLimitToMatchedText << Syncompletionproposal::scoEndCharCompletion << Syncompletionproposal::scoCompleteWithTab << Syncompletionproposal::scoCompleteWithEnter;
const System::WideChar DefaultEndOfTokenChr[] = L"()[]. ";
class DELPHICLASS TProposalColumns;

class TSynBaseCompletionProposalForm : public TSynForm
{
	#include "SynCompletionProposal_friends.inc"
public:
	typedef TSynForm inherited;
private:
	String FCurrentString;
	TSynBaseCompletionProposalPaintItem FOnPaintItem;
	TSynBaseCompletionProposalMeasureItem FOnMeasureItem;
	TCompletionChange FOnChangePosition;
	TStrings* FItemList;
	TStrings* FInsertList;
	TStrings* FAssignedList;
	int FPosition;
	int FLinesInWindow;
	int FTitleFontHeight;
	int FFontHeight;
	TScrollBar* FScrollbar;
	TValidateEvent FOnValidate;
	TNotifyEvent FOnCancel;
	TColor FClSelect;
	TColor fClSelectText;
	TColor FClTitleBackground;
	TColor fClBackGround;
	TBitmap* Bitmap; // used for drawing
	TBitmap* TitleBitmap; // used for title-drawing
	Synedit::TCustomSynEdit* FCurrentEditor;
	String FTitle;
	TFont* FTitleFont;
	TFont* FFont;
	bool FResizeable;
	int FItemHeight;
	int FMargin;
	int FEffectiveItemHeight;
	TCustomImageList* FImages;

//These are the reflections of the Options property of the CompletionProposal
	bool FCase;
	bool FMatchText;
	bool FFormattedText;
	bool FCenterTitle;
	bool FUseInsertList;
	bool FCompleteWithTab;
	bool FCompleteWithEnter;
	int FMouseWheelAccumulator;
	SynCompletionType FDisplayKind;
	TCompletionParameter FParameterToken;
	int FCurrentIndex;
	int FCurrentLevel;
	SynCompletionType FDefaultKind;
	String FEndOfTokenChr;
	String FTriggerChars;
	bool OldShowCaret;
	int FHeightBuffer;
	TProposalColumns* FColumns;
	void __fastcall SetCurrentString(const String Value);
	void __fastcall MoveLine(int cnt);
	void __fastcall ScrollbarOnChange(TObject* Sender);
	void __fastcall ScrollbarOnScroll(TObject* Sender, TScrollCode ScrollCode, int& ScrollPos);
	void __fastcall ScrollbarOnEnter(TObject* Sender);
	void __fastcall SetItemList(TStrings* const Value);
	void __fastcall SetInsertList(TStrings* const Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetResizeable(bool Value);
	void __fastcall SetItemHeight(int Value);
	void __fastcall SetImages(TCustomImageList* const Value);
	void __fastcall StringListChange(TObject* Sender);
	void __fastcall DoDoubleClick(TObject* Sender);
	void __fastcall DoFormShow(TObject* Sender);
	void __fastcall DoFormHide(TObject* Sender);
	void __fastcall AdjustScrollBarPosition();
	void __fastcall AdjustMetrics();
	void __fastcall SetTitle(const String Value);
	void __fastcall SetFont(TFont* const Value);
	void __fastcall SetTitleFont(TFont* const Value);
	void __fastcall SetColumns(TProposalColumns* Value);
	void __fastcall TitleFontChange(TObject* Sender);
	void __fastcall FontChange(TObject* Sender);
	void __fastcall RecalcItemHeight();
	bool __fastcall IsWordBreakChar(WideChar AChar);
	HIDESBASE MESSAGE void __fastcall WMNCHitTest(TWMNCHitTest& Message)/*# WM_NCHITTEST */;
protected:
	DYNAMIC void __fastcall KeyDown(WORD& Key, TShiftState Shift);
	DYNAMIC void __fastcall KeyPress(Char& Key);
	DYNAMIC void __fastcall Paint();
	DYNAMIC void __fastcall Activate();
	DYNAMIC void __fastcall Deactivate();
	DYNAMIC void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall Resize();
	virtual void __fastcall Notification(TComponent* AComponent, TOperation Operation);
	HIDESBASE MESSAGE void __fastcall WMMouseWheel(::TMessage& Msg)/*# WM_MOUSEWHEEL */;
	HIDESBASE MESSAGE void __fastcall WMActivate(TWMActivate& Message)/*# WM_ACTIVATE */;
	MESSAGE void __fastcall WMEraseBackgrnd(::TMessage& Message)/*# WM_ERASEBKGND */;
	MESSAGE void __fastcall WMGetDlgCode(TWMGetDlgCode& Message)/*# WM_GETDLGCODE */;
	virtual void __fastcall CreateParams(TCreateParams& Params);
	virtual int __fastcall GetCurrentPPI();
public:
	__fastcall TSynBaseCompletionProposalForm(TComponent* AOwner);
	virtual __fastcall ~TSynBaseCompletionProposalForm();
	int __fastcall LogicalToPhysicalIndex(int Index);
	int __fastcall PhysicalToLogicalIndex(int Index);
	__property SynCompletionType DisplayType = { read = FDisplayKind, write = FDisplayKind };
	__property SynCompletionType DefaultType = { read = FDefaultKind, write = FDefaultKind, default = /*# ctCode */ 0 };
	__property String CurrentString = { read = FCurrentString, write = SetCurrentString };
	__property int CurrentIndex = { read = FCurrentIndex, write = FCurrentIndex };
	__property int CurrentLevel = { read = FCurrentLevel, write = FCurrentLevel };
	__property TCompletionParameter OnParameterToken = { read = FParameterToken, write = FParameterToken };
	__property  OnKeyPress;
	__property TSynBaseCompletionProposalPaintItem OnPaintItem = { read = FOnPaintItem, write = FOnPaintItem };
	__property TSynBaseCompletionProposalMeasureItem OnMeasureItem = { read = FOnMeasureItem, write = FOnMeasureItem };
	__property TValidateEvent OnValidate = { read = FOnValidate, write = FOnValidate };
	__property TNotifyEvent OnCancel = { read = FOnCancel, write = FOnCancel };
	__property TStrings* ItemList = { read = FItemList, write = SetItemList };
	__property TStrings* InsertList = { read = FInsertList, write = SetInsertList };
	__property TStrings* AssignedList = { read = FAssignedList, write = FAssignedList };
	__property int Position = { read = FPosition, write = SetPosition };
	__property String Title = { read = FTitle, write = SetTitle };
	__property TColor ClSelect = { read = FClSelect, write = FClSelect, default = clHighlight };
	__property TColor ClSelectedText = { read = fClSelectText, write = fClSelectText, default = clHighlightText };
	__property TColor ClBackground = { read = fClBackGround, write = fClBackGround, default = clWindow };
	__property TColor ClTitleBackground = { read = FClTitleBackground, write = FClTitleBackground, default = clBtnFace };
	__property int ItemHeight = { read = FItemHeight, write = SetItemHeight, default = 0 };
	__property int Margin = { read = FMargin, write = FMargin, default = 2 };
	__property bool UsePrettyText = { read = FFormattedText, write = FFormattedText, default = false };
	__property bool UseInsertList = { read = FUseInsertList, write = FUseInsertList, default = false };
	__property bool CenterTitle = { read = FCenterTitle, write = FCenterTitle, default = true };
	__property bool CaseSensitive = { read = FCase, write = FCase, default = false };
	__property Synedit::TCustomSynEdit* CurrentEditor = { read = FCurrentEditor, write = FCurrentEditor };
	__property bool MatchText = { read = FMatchText, write = FMatchText };
	__property String EndOfTokenChr = { read = FEndOfTokenChr, write = FEndOfTokenChr };
	__property String TriggerChars = { read = FTriggerChars, write = FTriggerChars };
	__property bool CompleteWithTab = { read = FCompleteWithTab, write = FCompleteWithTab };
	__property bool CompleteWithEnter = { read = FCompleteWithEnter, write = FCompleteWithEnter };
	__property TFont* TitleFont = { read = FTitleFont, write = SetTitleFont };
	__property TFont* Font = { read = FFont, write = SetFont };
	__property TProposalColumns* Columns = { read = FColumns, write = SetColumns };
	__property bool Resizeable = { read = FResizeable, write = SetResizeable };
	__property TCustomImageList* Images = { read = FImages, write = SetImages };
protected:
	BEGIN_MESSAGE_MAP
	  VCL_MESSAGE_HANDLER(WM_ACTIVATE, TWMActivate, WMActivate)
	  VCL_MESSAGE_HANDLER(WM_ERASEBKGND, TMessage, WMEraseBackgrnd)
	  VCL_MESSAGE_HANDLER(WM_GETDLGCODE, TWMGetDlgCode, WMGetDlgCode)
	  VCL_MESSAGE_HANDLER(WM_MOUSEWHEEL, TMessage, WMMouseWheel)
	  VCL_MESSAGE_HANDLER(WM_NCHITTEST, TWMNCHitTest, WMNCHitTest)
	END_MESSAGE_MAP(Vcl::Forms::TCustomForm)
public:
	__fastcall TSynBaseCompletionProposalForm(TComponent* AOwner);
};

class TSynBaseCompletionProposal : public System::Classes::TComponent
{
private:
	TSynBaseCompletionProposalForm* FForm;
	TCompletionExecute FOnExecute;
	TNotifyEvent FOnClose;
	TNotifyEvent FOnShow;
	int FWidth;
	String FPreviousToken;
	int FDotOffset;
	TSynCompletionOptions FOptions;
	int FNbLinesInWindow;
	bool FFontsAreScaled;
	bool FCanExecute;
	TColor __fastcall GetClSelect();
	void __fastcall SetClSelect(const TColor Value);
	String __fastcall GetCurrentString();
	TStrings* __fastcall GetItemList();
	TStrings* __fastcall GetInsertList();
	TNotifyEvent __fastcall GetOnCancel();
	TKeyPressEvent __fastcall GetOnKeyPress();
	TSynBaseCompletionProposalPaintItem __fastcall GetOnPaintItem();
	TSynBaseCompletionProposalMeasureItem __fastcall GetOnMeasureItem();
	TValidateEvent __fastcall GetOnValidate();
	int __fastcall GetPosition();
	void __fastcall SetCurrentString(const String Value);
	void __fastcall SetItemList(TStrings* const Value);
	void __fastcall SetInsertList(TStrings* const Value);
	void __fastcall SetNbLinesInWindow(int Value);
	void __fastcall SetOnCancel(const TNotifyEvent Value);
	void __fastcall SetOnKeyPress(const TKeyPressEvent Value);
	void __fastcall SetOnPaintItem(const TSynBaseCompletionProposalPaintItem Value);
	void __fastcall SetOnMeasureItem(const TSynBaseCompletionProposalMeasureItem Value);
	void __fastcall SetPosition(int Value);
	void __fastcall SetOnValidate(const TValidateEvent Value);
	void __fastcall SetWidth(int Value);
	void __fastcall SetImages(TCustomImageList* const Value);
	SynCompletionType __fastcall GetDisplayKind();
	void __fastcall SetDisplayKind(SynCompletionType Value);
	TCompletionParameter __fastcall GetParameterToken();
	void __fastcall SetParameterToken(const TCompletionParameter Value);
	SynCompletionType __fastcall GetDefaultKind();
	void __fastcall SetDefaultKind(SynCompletionType Value);
	TColor __fastcall GetClBack();
	void __fastcall SetClBack(const TColor Value);
	TColor __fastcall GetClSelectedText();
	void __fastcall SetClSelectedText(const TColor Value);
	String __fastcall GetEndOfTokenChar();
	void __fastcall SetEndOfTokenChar(const String Value);
	TColor __fastcall GetClTitleBackground();
	void __fastcall SetClTitleBackground(const TColor Value);
	void __fastcall SetTitle(const String Value);
	String __fastcall GetTitle();
	TFont* __fastcall GetFont();
	TFont* __fastcall GetTitleFont();
	void __fastcall SetFont(TFont* const Value);
	void __fastcall SetTitleFont(TFont* const Value);
	TSynCompletionOptions __fastcall GetOptions();
	String __fastcall GetTriggerChars();
	void __fastcall SetTriggerChars(const String Value);
	TCompletionChange __fastcall GetOnChange();
	void __fastcall SetOnChange(const TCompletionChange Value);
	void __fastcall SetColumns(TProposalColumns* const Value);
	TProposalColumns* __fastcall GetColumns();
	bool __fastcall GetResizeable();
	void __fastcall SetResizeable(bool Value);
	int __fastcall GetItemHeight();
	void __fastcall SetItemHeight(int Value);
	int __fastcall GetMargin();
	void __fastcall SetMargin(int Value);
	TCustomImageList* __fastcall GetImages();
	bool __fastcall IsWordBreakChar(WideChar AChar);
protected:
	virtual void __fastcall DefineProperties(TFiler* Filer);
	virtual void __fastcall SetOptions(const TSynCompletionOptions Value);
	virtual void __fastcall EditorCancelMode(TObject* Sender);
	virtual void __fastcall HookedEditorCommand(TObject* Sender, bool AfterProcessing, bool& Handled, Synedittypes::TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData);
public:
	typedef System::Classes::TComponent inherited;
	#include "SynCompletionProposal_friends.inc"
	__fastcall TSynBaseCompletionProposal(TComponent* AOwner);
	void __fastcall Execute(String s, int x, int y);
	virtual void __fastcall ExecuteEx(String s, int x, int y, SynCompletionType Kind = Syncompletionproposal::ctCode);
	void __fastcall Activate();
	void __fastcall Deactivate();
	void __fastcall ClearList();
	String __fastcall DisplayItem(int AIndex);
	String __fastcall InsertItem(int AIndex);
	void __fastcall AddItemAt(int Where, String ADisplayText, String AInsertText);
	void __fastcall AddItem(String ADisplayText, String AInsertText);
	void __fastcall ResetAssignedList();
	__property TKeyPressEvent OnKeyPress = { read = GetOnKeyPress, write = SetOnKeyPress };
	__property TValidateEvent OnValidate = { read = GetOnValidate, write = SetOnValidate };
	__property TNotifyEvent OnCancel = { read = GetOnCancel, write = SetOnCancel };
	__property String CurrentString = { read = GetCurrentString, write = SetCurrentString };
	__property int DotOffset = { read = FDotOffset, write = FDotOffset };
	__property SynCompletionType DisplayType = { read = GetDisplayKind, write = SetDisplayKind };
	__property TSynBaseCompletionProposalForm* Form = { read = FForm };
	__property String PreviousToken = { read = FPreviousToken };
	__property int Position = { read = GetPosition, write = SetPosition };
	__property bool FontsAreScaled = { read = FFontsAreScaled, write = FFontsAreScaled };
__published:
	__property SynCompletionType DefaultType = { read = GetDefaultKind, write = SetDefaultKind, default = /*# ctCode */ 0 };
	__property TSynCompletionOptions Options = { read = GetOptions, write = SetOptions, default = /*# DefaultProposalOptions */ 0 };
	__property TStrings* ItemList = { read = GetItemList, write = SetItemList };
	__property TStrings* InsertList = { read = GetInsertList, write = SetInsertList };
	__property int NbLinesInWindow = { read = FNbLinesInWindow, write = SetNbLinesInWindow, default = 8 };
	__property TColor ClSelect = { read = GetClSelect, write = SetClSelect, default = clHighlight };
	__property TColor ClSelectedText = { read = GetClSelectedText, write = SetClSelectedText, default = clHighlightText };
	__property TColor ClBackground = { read = GetClBack, write = SetClBack, default = clWindow };
	__property TColor ClTitleBackground = { read = GetClTitleBackground, write = SetClTitleBackground, default = clBtnFace };
	__property int Width = { read = FWidth, write = SetWidth, default = 260 };
	__property String EndOfTokenChr = { read = GetEndOfTokenChar, write = SetEndOfTokenChar };
	__property String TriggerChars = { read = GetTriggerChars, write = SetTriggerChars };
	__property String Title = { read = GetTitle, write = SetTitle };
	__property TFont* Font = { read = GetFont, write = SetFont };
	__property TFont* TitleFont = { read = GetTitleFont, write = SetTitleFont };
	__property TProposalColumns* Columns = { read = GetColumns, write = SetColumns };
	__property bool Resizeable = { read = GetResizeable, write = SetResizeable, default = false };
	__property int ItemHeight = { read = GetItemHeight, write = SetItemHeight, default = 0 };
	__property TCustomImageList* Images = { read = GetImages, write = SetImages, default = NULL };
	__property int Margin = { read = GetMargin, write = SetMargin, default = 2 };
	__property TCompletionChange OnChange = { read = GetOnChange, write = SetOnChange };
	__property TNotifyEvent OnClose = { read = FOnClose, write = FOnClose };
	__property TCompletionExecute OnExecute = { read = FOnExecute, write = FOnExecute };
	__property TSynBaseCompletionProposalMeasureItem OnMeasureItem = { read = GetOnMeasureItem, write = SetOnMeasureItem };
	__property TSynBaseCompletionProposalPaintItem OnPaintItem = { read = GetOnPaintItem, write = SetOnPaintItem };
	__property TCompletionParameter OnParameterToken = { read = GetParameterToken, write = SetParameterToken };
	__property TNotifyEvent OnShow = { read = FOnShow, write = FOnShow };
};

class TSynCompletionProposal : public TSynBaseCompletionProposal
{
private:
	TList* fEditors;
	TShortCut FShortCut;
	bool FNoNextKey;
	int FCompletionStart;
	bool FAdjustCompletionStart;
	TCodeCompletionEvent FOnCodeCompletion;
	TTimer* FTimer;
	int FTimerInterval;
	Synedit::TCustomSynEdit* FEditor;
	TAfterCodeCompletionEvent FOnAfterCodeCompletion;
	TNotifyEvent FOnCancelled;
	void __fastcall SetEditor(Synedit::TCustomSynEdit* const Value);
	void __fastcall HandleOnCancel(TObject* Sender);
	void __fastcall HandleOnValidate(TObject* Sender, TShiftState Shift, WideChar EndToken);
	void __fastcall HandleOnKeyPress(TObject* Sender, WideChar& Key);
	void __fastcall HandleDblClick(TObject* Sender);
	void __fastcall EditorKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
	void __fastcall EditorKeyPress(TObject* Sender, WideChar& Key);
	void __fastcall TimerExecute(TObject* Sender);
	String __fastcall GetPreviousToken(Synedit::TCustomSynEdit* AEditor);
	String __fastcall GetCurrentInput(Synedit::TCustomSynEdit* AEditor);
	int __fastcall GetTimerInterval();
	void __fastcall SetTimerInterval(int Value);
	Synedit::TCustomSynEdit* __fastcall GetEditor(int i);
	void __fastcall InternalCancelCompletion();
protected:
	virtual void __fastcall DoExecute(Synedit::TCustomSynEdit* AEditor);
	virtual void __fastcall Notification(TComponent* AComponent, TOperation Operation);
	void __fastcall SetShortCut(TShortCut Value);
	virtual void __fastcall SetOptions(const TSynCompletionOptions Value);
	virtual void __fastcall EditorCancelMode(TObject* Sender);
	virtual void __fastcall HookedEditorCommand(TObject* Sender, bool AfterProcessing, bool& Handled, Synedittypes::TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData);
public:
	typedef TSynBaseCompletionProposal inherited;
	#include "SynCompletionProposal_friends.inc"
	__fastcall TSynCompletionProposal(TComponent* AOwner);
	virtual __fastcall ~TSynCompletionProposal();
	void __fastcall AddEditor(Synedit::TCustomSynEdit* AEditor);
	bool __fastcall RemoveEditor(Synedit::TCustomSynEdit* AEditor);
	int __fastcall EditorsCount();
	virtual void __fastcall ExecuteEx(String s, int x, int y, SynCompletionType Kind = Syncompletionproposal::ctCode);
	void __fastcall ActivateCompletion();
	void __fastcall CancelCompletion();
	void __fastcall ActivateTimer(Synedit::TCustomSynEdit* ACurrentEditor);
	void __fastcall DeactivateTimer();
	__property Synedit::TCustomSynEdit* Editors[int i] = { read = GetEditor };
	__property int CompletionStart = { read = FCompletionStart, write = FCompletionStart }; // ET 04/02/2003
__published:
	__property TShortCut ShortCut = { read = FShortCut, write = SetShortCut };
	__property Synedit::TCustomSynEdit* Editor = { read = FEditor, write = SetEditor };
	__property int TimerInterval = { read = GetTimerInterval, write = SetTimerInterval, default = 1000 };
	__property TAfterCodeCompletionEvent OnAfterCodeCompletion = { read = FOnAfterCodeCompletion, write = FOnAfterCodeCompletion };
	__property TNotifyEvent OnCancelled = { read = FOnCancelled, write = FOnCancelled };
	__property TCodeCompletionEvent OnCodeCompletion = { read = FOnCodeCompletion, write = FOnCodeCompletion };
};

class TSynAutoComplete : public System::Classes::TComponent
{
private:
	TShortCut FShortCut;
	Synedit::TCustomSynEdit* fEditor;
	TStrings* fAutoCompleteList;
	bool fNoNextKey;
	String FEndOfTokenChr;
	TNotifyEvent FOnBeforeExecute;
	TNotifyEvent FOnAfterExecute;
	TSynCompletionProposal* FInternalCompletion;
	bool FDoLookup;
	TSynCompletionOptions FOptions;
	void __fastcall SetAutoCompleteList(TStrings* List);
	void __fastcall SetEditor(Synedit::TCustomSynEdit* const Value);
	void __fastcall SetDoLookup(bool Value);
	void __fastcall CreateInternalCompletion();
	TSynCompletionOptions __fastcall GetOptions();
	void __fastcall SetOptions(const TSynCompletionOptions Value);
	void __fastcall DoInternalAutoCompletion(TObject* Sender, const String Value, TShiftState Shift, int Index, WideChar EndToken);
	bool __fastcall GetExecuting();
protected:
	void __fastcall SetShortCut(TShortCut Value);
	virtual void __fastcall Notification(TComponent* AComponent, TOperation Operation);
	virtual void __fastcall EditorKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
	virtual void __fastcall EditorKeyPress(TObject* Sender, WideChar& Key);
	String __fastcall GetPreviousToken(Synedit::TCustomSynEdit* Editor);
public:
	typedef System::Classes::TComponent inherited;
	#include "SynCompletionProposal_friends.inc"
	TSynCompletionProposal* __fastcall GetCompletionProposal();
	__fastcall TSynAutoComplete(TComponent* AOwner);
	virtual __fastcall ~TSynAutoComplete();
	void __fastcall Execute(String Token, Synedit::TCustomSynEdit* Editor);
	void __fastcall ExecuteEx(String Token, Synedit::TCustomSynEdit* Editor, bool LookupIfNotExact);
	String __fastcall GetTokenList();
	String __fastcall GetTokenValue(String Token);
	void __fastcall CancelCompletion();
	__property bool Executing = { read = GetExecuting };
__published:
	__property TStrings* AutoCompleteList = { read = fAutoCompleteList, write = SetAutoCompleteList };
	__property String EndOfTokenChr = { read = FEndOfTokenChr, write = FEndOfTokenChr };
	__property Synedit::TCustomSynEdit* Editor = { read = fEditor, write = SetEditor };
	__property TShortCut ShortCut = { read = FShortCut, write = SetShortCut };
	__property TNotifyEvent OnBeforeExecute = { read = FOnBeforeExecute, write = FOnBeforeExecute };
	__property TNotifyEvent OnAfterExecute = { read = FOnAfterExecute, write = FOnAfterExecute };
	__property bool DoLookupWhenNotExact = { read = FDoLookup, write = SetDoLookup, default = true };
	__property TSynCompletionOptions Options = { read = GetOptions, write = SetOptions, default = /*# DefaultProposalOptions */ 0 };
};

class TProposalColumn : public System::Classes::TCollectionItem
{
private:
	int FColumnWidth;
	int FInternalWidth;
	TFontStyles FFontStyle;
protected:
	virtual void __fastcall DefineProperties(TFiler* Filer);
public:
	typedef System::Classes::TCollectionItem inherited;
	#include "SynCompletionProposal_friends.inc"
	__fastcall TProposalColumn(TCollection* Collection);
	virtual __fastcall ~TProposalColumn();
	virtual void __fastcall Assign(TPersistent* Source);
__published:
	__property int ColumnWidth = { read = FColumnWidth, write = FColumnWidth };
	__property TFontStyles DefaultFontStyle = { read = FFontStyle, write = FFontStyle, default = 0 };
};

class TProposalColumns : public System::Classes::TCollection
{
private:
	TPersistent* FOwner;
	TProposalColumn* __fastcall GetItem(int Index);
	void __fastcall SetItem(int Index, TProposalColumn* Value);
protected:
	DYNAMIC TPersistent* __fastcall GetOwner();
public:
	typedef System::Classes::TCollection inherited;
	#include "SynCompletionProposal_friends.inc"
	__fastcall TProposalColumns(TPersistent* AOwner, TCollectionItemClass ItemClass);
	TProposalColumn* __fastcall Add();
	TProposalColumn* __fastcall FindItemID(int ID);
	TProposalColumn* __fastcall Insert(int Index);
	__property TProposalColumn* Items[int Index] = { read = GetItem, write = SetItem/*# default */ };
	__fastcall TProposalColumns(TCollectionItemClass ItemClass);
};
void __fastcall FormattedTextOut(TCanvas* TargetCanvas, const TRect& Rect, int PPI, const String Text, bool Selected, TProposalColumns* Columns, TCustomImageList* Images);
int __fastcall FormattedTextWidth(TCanvas* TargetCanvas, const String Text, int PPI, TProposalColumns* Columns, TCustomImageList* Images);
String __fastcall PrettyTextToFormattedString(const String APrettyText, bool AlternateBoldStyle = false);


}  // namespace SynCompletionProposal

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syncompletionproposal;
#endif

#endif // SynCompletionProposalH

