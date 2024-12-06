/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEdit.pas, released 2000-04-07.
The Original Code is based on mwCustomEdit.pas by Martin Waldenburg, part of
the mwEdit component suite.
Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
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

$Id: SynEditOptionsDialog.pas,v 1.21.2.5 2005/07/20 13:37:18 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:

-------------------------------------------------------------------------------*/
#ifndef SynEditOptionsDialogH
#define SynEditOptionsDialogH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Winapi.CommCtrl.hpp>
#include <System.Win.Registry.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include "SynEdit.h"
#include "SynEditHighlighter.h"
#include "SynEditMiscClasses.h"
#include "SynEditKeyCmds.h"
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.ImageList.hpp>




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
class TSynEditorOptionsContainer;
enum TColorPopup {cpGutter,
                  cpRightEdge };


  //NOTE: in order for the user commands to be recorded correctly, you must
  //      put the command itself in the object property.
  //      you can do this like so:
  //
  //      StringList.AddObject('ecSomeCommand', TObject(ecSomeCommand))
  //
  //      where ecSomeCommand is the command that you want to add
typedef void __fastcall (__closure *TSynEditorOptionsUserCommand) (int, String&);
typedef void __fastcall (__closure *TSynEditorOptionsAllUserCommands) (TStrings*);

class TfmEditorOptionsDialog : public TForm
{
__published:
public:
	TPageControl* PageControl1;
	TButton* btnOk;
	TButton* btnCancel;
	TTabSheet* Display;
	TColorDialog* ColorDialog;
	TPopupMenu* ColorPopup;
	TMenuItem* None1;
	TMenuItem* Scrollbar1;
	TMenuItem* ActiveCaption1;
	TMenuItem* Background1;
	TMenuItem* InactiveCaption1;
	TMenuItem* Menu1;
	TMenuItem* Window1;
	TMenuItem* WindowFrame1;
	TMenuItem* MEnu2;
	TMenuItem* WindowText1;
	TMenuItem* CaptionText1;
	TMenuItem* ActiveBorder1;
	TMenuItem* InactiveBorder1;
	TMenuItem* ApplicationWorkspace1;
	TMenuItem* Highlight1;
	TMenuItem* HighlightText1;
	TMenuItem* ButtonFace1;
	TMenuItem* ButtonShadow1;
	TMenuItem* GrayText1;
	TMenuItem* ButtonText1;
	TMenuItem* InactiveCaptionText1;
	TMenuItem* Highlight2;
	TMenuItem* N3dDarkShadow1;
	TMenuItem* N3DLight1;
	TMenuItem* InfoTipText1;
	TMenuItem* InfoTipBackground1;
	TImageList* ImageList1;
	TTabSheet* Options;
	TTabSheet* Keystrokes;
	TGroupBox* gbBookmarks;
	TCheckBox* ckBookmarkKeys;
	TCheckBox* ckBookmarkVisible;
	TGroupBox* gbLineSpacing;
	TEdit* eLineSpacing;
	TGroupBox* gbGutter;
	TLabel* Label1;
	TCheckBox* ckGutterAutosize;
	TCheckBox* ckGutterShowLineNumbers;
	TCheckBox* ckGutterShowLeaderZeros;
	TCheckBox* ckGutterStartAtZero;
	TCheckBox* ckGutterVisible;
	TGroupBox* gbRightEdge;
	TLabel* Label3;
	TPanel* pRightEdgeBack;
	TEdit* eRightEdge;
	TGroupBox* gbEditorFont;
	TButton* btnFont;
	TGroupBox* gbOptions;
	TCheckBox* ckAutoIndent;
	TCheckBox* ckDragAndDropEditing;
	TCheckBox* ckHalfPageScroll;
	TCheckBox* ckEnhanceEndKey;
	TCheckBox* ckScrollByOneLess;
	TCheckBox* ckScrollPastEOF;
	TCheckBox* ckScrollPastEOL;
	TCheckBox* ckShowScrollHint;
	TCheckBox* ckSmartTabs;
	TCheckBox* ckTabsToSpaces;
	TCheckBox* ckTrimTrailingSpaces;
	TCheckBox* ckWantTabs;
	TGroupBox* gbCaret;
	TComboBox* cInsertCaret;
	TLabel* Label2;
	TLabel* Label4;
	TComboBox* cOverwriteCaret;
	TPanel* Panel3;
	TLabel* labFont;
	TFontDialog* FontDialog;
	TButton* btnAddKey;
	TButton* btnRemKey;
	TGroupBox* gbKeyStrokes;
	TLabel* Label5;
	TLabel* Label6;
	TLabel* Label7;
	TComboBox* cKeyCommand;
	TButton* btnUpdateKey;
	TCheckBox* ckAltSetsColumnMode;
	TCheckBox* ckKeepCaretX;
	TEdit* eTabWidth;
	TPanel* pRightEdgeColor;
	TLabel* Label8;
	TLabel* Label9;
	TLabel* Label10;
	TCheckBox* cbGutterFont;
	TButton* btnGutterFont;
	TPanel* btnRightEdge;
	TImage* Image1;
	TPanel* pGutterBack;
	TPanel* pGutterColor;
	TPanel* btnGutterColor;
	TImage* Image2;
	TCheckBox* ckScrollHintFollows;
	TCheckBox* ckGroupUndo;
	TCheckBox* ckSmartTabDelete;
	TCheckBox* ckRightMouseMoves;
	TPanel* pnlGutterFontDisplay;
	TLabel* lblGutterFont;
	TCheckBox* ckEnhanceHomeKey;
	TPanel* pnlCommands;
	TListView* KeyList;
	TCheckBox* ckHideShowScrollbars;
	TCheckBox* ckDisableScrollArrows;
	TCheckBox* ckShowSpecialChars;
	void __fastcall PopupMenuClick(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall pGutterColorClick(TObject* Sender);
	void __fastcall pRightEdgeColorClick(TObject* Sender);
	void __fastcall btnFontClick(TObject* Sender);
	void __fastcall KeyListSelectItem(TObject* Sender, TListItem* Item, bool Selected);
	void __fastcall btnUpdateKeyClick(TObject* Sender);
	void __fastcall btnAddKeyClick(TObject* Sender);
	void __fastcall btnRemKeyClick(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall KeyListEditing(TObject* Sender, TListItem* Item, bool& AllowEdit);
	void __fastcall btnOkClick(TObject* Sender);
	void __fastcall btnGutterFontClick(TObject* Sender);
	void __fastcall cbGutterFontClick(TObject* Sender);
	void __fastcall btnRightEdgeMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnGutterColorMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall cKeyCommandKeyUp(TObject* Sender, WORD& Key, TShiftState Shift);
	void __fastcall KeyListChanging(TObject* Sender, TListItem* Item, TItemChange Change, bool& AllowChange);
private:
	TSynEditorOptionsContainer* FSynEdit;
	TColorPopup FPoppedFrom;
	TSynEditorOptionsUserCommand FUserCommand;
	TSynEditorOptionsAllUserCommands FAllUserCommands;
	TListItem* OldSelected;
	bool InChanging;
	bool FExtended;
	TColor __fastcall GetColor(TMenuItem* Item);
	void __fastcall GetData();
	void __fastcall PutData();
	void __fastcall EditStrCallback(const String S);
	void __fastcall FillInKeystrokeInfo(Syneditkeycmds::TSynEditKeyStroke* AKey, TListItem* AItem);
public:
	Syneditmiscclasses::TSynHotKey* eKeyShort2;
	Syneditmiscclasses::TSynHotKey* eKeyShort1;
	typedef TForm inherited;
	#include "SynEditOptionsDialog_friends.inc"
	bool __fastcall Execute(TSynEditorOptionsContainer* EditOptions);
	__property TSynEditorOptionsUserCommand GetUserCommandNames = { read = FUserCommand, write = FUserCommand };
	__property TSynEditorOptionsAllUserCommands GetAllUserCommands = { read = FAllUserCommands, write = FAllUserCommands };
	__property bool UseExtendedStrings = { read = FExtended, write = FExtended };
	__fastcall TfmEditorOptionsDialog(TComponent* AOwner, int Dummy);
protected:
	//# please uncomment for main forms
	//# void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params)
		//# {inherited::CreateParams(Params); Params.ExStyle = Params.ExStyle | WS_EX_APPWINDOW;}
};

class TSynEditOptionsDialog : public System::Classes::TComponent
{
private:
	TfmEditorOptionsDialog* FForm;
	TSynEditorOptionsUserCommand __fastcall GetUserCommandNames();
	void __fastcall SetUserCommandNames(const TSynEditorOptionsUserCommand Value);
	TSynEditorOptionsAllUserCommands __fastcall GetUserCommands();
	void __fastcall SetUserCommands(const TSynEditorOptionsAllUserCommands Value);
	bool __fastcall GetExtended();
	void __fastcall SetExtended(bool Value);
public:
	typedef System::Classes::TComponent inherited;
	#include "SynEditOptionsDialog_friends.inc"
	__fastcall TSynEditOptionsDialog(TComponent* AOwner);
	virtual __fastcall ~TSynEditOptionsDialog();
	bool __fastcall Execute(TSynEditorOptionsContainer* EditOptions);
	__property TfmEditorOptionsDialog* Form = { read = FForm };
__published:
public:
	__property TSynEditorOptionsUserCommand GetUserCommand = { read = GetUserCommandNames, write = SetUserCommandNames };
	__property TSynEditorOptionsAllUserCommands GetAllUserCommands = { read = GetUserCommands, write = SetUserCommands };
	__property bool UseExtendedStrings = { read = GetExtended, write = SetExtended };
};

  //This class is assignable to a SynEdit without modifying key properties that affect function

class TSynEditorOptionsContainer : public System::Classes::TComponent
{
private:
	bool FHideSelection;
	bool FWantTabs;
	int FMaxUndo;
	int FExtraLineSpacing;
	int FTabWidth;
	int FMaxScrollWidth;
	int FRightEdge;
	Syneditmiscclasses::TSynSelectedColor* FSelectedColor;
	TColor FRightEdgeColor;
	TFont* FFont;
	Syneditmiscclasses::TSynBookMarkOpt* FBookmarks;
	Synedit::TSynEditCaretType FOverwriteCaret;
	Synedit::TSynEditCaretType FInsertCaret;
	Syneditkeycmds::TSynEditKeyStrokes* FKeystrokes;
	Synedit::TSynEditorOptions FOptions;
	Syneditmiscclasses::TSynGutter* FSynGutter;
	TColor FColor;
	void __fastcall SetBookMarks(Syneditmiscclasses::TSynBookMarkOpt* const Value);
	void __fastcall SetFont(TFont* const Value);
	void __fastcall SetKeystrokes(Syneditkeycmds::TSynEditKeyStrokes* const Value);
	void __fastcall SetOptions(const Synedit::TSynEditorOptions Value);
	void __fastcall SetSynGutter(Syneditmiscclasses::TSynGutter* const Value);
public:
	typedef System::Classes::TComponent inherited;
	#include "SynEditOptionsDialog_friends.inc"
	__fastcall TSynEditorOptionsContainer(TComponent* AOwner);
	virtual __fastcall ~TSynEditorOptionsContainer();
	virtual void __fastcall Assign(TPersistent* Source);
	virtual void __fastcall AssignTo(TPersistent* Dest);
__published:
public:
	__property Synedit::TSynEditorOptions Options = { read = FOptions, write = SetOptions };
	__property Syneditmiscclasses::TSynBookMarkOpt* BookMarkOptions = { read = FBookmarks, write = SetBookMarks };
	__property TColor Color = { read = FColor, write = FColor };
	__property TFont* Font = { read = FFont, write = SetFont };
	__property int ExtraLineSpacing = { read = FExtraLineSpacing, write = FExtraLineSpacing };
	__property Syneditmiscclasses::TSynGutter* Gutter = { read = FSynGutter, write = SetSynGutter };
	__property int RightEdge = { read = FRightEdge, write = FRightEdge };
	__property TColor RightEdgeColor = { read = FRightEdgeColor, write = FRightEdgeColor };
	__property bool WantTabs = { read = FWantTabs, write = FWantTabs };
	__property Synedit::TSynEditCaretType InsertCaret = { read = FInsertCaret, write = FInsertCaret };
	__property Synedit::TSynEditCaretType OverwriteCaret = { read = FOverwriteCaret, write = FOverwriteCaret };
	__property bool HideSelection = { read = FHideSelection, write = FHideSelection };
	__property int MaxScrollWidth = { read = FMaxScrollWidth, write = FMaxScrollWidth };
	__property int MaxUndo = { read = FMaxUndo, write = FMaxUndo };
	__property Syneditmiscclasses::TSynSelectedColor* SelectedColor = { read = FSelectedColor, write = FSelectedColor };
	__property int TabWidth = { read = FTabWidth, write = FTabWidth };
	__property Syneditkeycmds::TSynEditKeyStrokes* Keystrokes = { read = FKeystrokes, write = SetKeystrokes };
};
#endif // SynEditOptionsDialogH

