/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynDBEdit.pas, released 2000-05-05.
The Original Code is based on DBmwEdit.pas by Vladimir Kuznetsov, part of
the mwEdit component suite.
Portions created by Vladimir Kuznetsov are Copyright (C) 1999 Vladimir Kuznetsov.
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

$Id: SynDBEdit.pas,v 1.11.2.2 2009/06/14 13:33:38 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef SynDBEditH
#define SynDBEditH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.DBCtrls.hpp>
#include "SynEdit.h"
#include "SynEditTypes.h"
#include "SynEditKeyCmds.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>

namespace Syndbedit
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

class TCustomDBSynEdit : public Synedit::TCustomSynEdit
{
private:
	TFieldDataLink* FDataLink;
	bool fEditing;
	bool FBeginEdit;
	TNotifyEvent FLoadData;
	void __fastcall DataChange(TObject* Sender);
	void __fastcall EditingChange(TObject* Sender);
	String __fastcall GetDataField();
	TDataSource* __fastcall GetDataSource();
	TField* __fastcall GetField();
	void __fastcall SetDataField(const String Value);
	void __fastcall SetDataSource(TDataSource* Value);
	void __fastcall SetEditing(bool Value);
	void __fastcall UpdateData(TObject* Sender);
	HIDESBASE MESSAGE void __fastcall CMEnter(TCMEnter& Msg)/*# CM_ENTER */;
	HIDESBASE MESSAGE void __fastcall CMExit(TCMExit& Msg)/*# CM_EXIT */;
	MESSAGE void __fastcall CMGetDataLink(::TMessage& Msg)/*# CM_GETDATALINK */;
protected:
	virtual bool __fastcall GetReadOnly();
	virtual void __fastcall Loaded();
	virtual void __fastcall DoChange();
	virtual void __fastcall SetReadOnly(bool Value);
public:
	typedef Synedit::TCustomSynEdit inherited;
	#include "SynDBEdit_friends.inc"
	__fastcall TCustomDBSynEdit(TComponent* AOwner);
	virtual __fastcall ~TCustomDBSynEdit();
	DYNAMIC void __fastcall DragDrop(TObject* Source, int X, int Y);
	virtual void __fastcall ExecuteCommand(Synedittypes::TSynEditorCommand Command, WideChar AChar, void* Data);
	void __fastcall LoadMemo();
	virtual void __fastcall Notification(TComponent* AComponent, TOperation Operation);
protected:
	__property String DataField = { read = GetDataField, write = SetDataField };
	__property TDataSource* DataSource = { read = GetDataSource, write = SetDataSource };
	__property TField* Field = { read = GetField };
	__property TNotifyEvent OnLoadData = { read = FLoadData, write = FLoadData };
	BEGIN_MESSAGE_MAP
	  VCL_MESSAGE_HANDLER(CM_ENTER, TCMEnter, CMEnter)
	  VCL_MESSAGE_HANDLER(CM_EXIT, TCMExit, CMExit)
	  VCL_MESSAGE_HANDLER(CM_GETDATALINK, TMessage, CMGetDataLink)
	END_MESSAGE_MAP(Synedit::TCustomSynEdit)
public:
	__fastcall TCustomDBSynEdit(HWND ParentWindow);
};

class TDBSynEdit : public TCustomDBSynEdit
{
__published:
public:
    // TCustomDBSynEdit properties
	__property  DataField;
	__property  DataSource;
	__property  Field;
    // TCustomDBSynEdit events
	__property  OnLoadData;
    // inherited properties
	__property  ActiveLineColor;
	__property  Align;
	__property  Anchors;
	__property  Constraints;
	__property  Color;
	__property  Ctl3D;
	__property  Enabled;
	__property  Font;
	__property  Height;
	__property  Name;
	__property  ParentColor;
	__property  ParentCtl3D;
	__property  ParentFont;
	__property  ParentShowHint;
	__property  PopupMenu;
	__property  ShowHint;
	__property  TabOrder;
	__property  TabStop = { default = true };
	__property  Tag;
	__property  Visible;
	__property  Width;
    // inherited events
	__property  OnClick;
	__property  OnDblClick;
	__property  OnDragDrop;
	__property  OnDragOver;
	__property  OnEndDock;
	__property  OnEndDrag;
	__property  OnEnter;
	__property  OnExit;
	__property  OnKeyDown;
	__property  OnKeyPress;
	__property  OnKeyUp;
	__property  OnMouseDown;
	__property  OnMouseMove;
	__property  OnMouseUp;
	__property  OnStartDock;
	__property  OnStartDrag;
    // TCustomSynEdit properties
	__property  BookMarkOptions;
	__property  BorderStyle;
	__property  ExtraLineSpacing;
	__property  Gutter;
	__property  HideSelection;
	__property  Highlighter;
	__property  ImeMode;
	__property  ImeName;
	__property  InsertCaret;
	__property  InsertMode;
	__property  Keystrokes;
	__property  MaxUndo;
	__property  Options;
	__property  OverwriteCaret;
	__property  ReadOnly;
	__property  RightEdge;
	__property  RightEdgeColor;
	__property  ScrollBars;
	__property  SearchEngine;
	__property  SelectedColor;
	__property  SelectionMode;
	__property  TabWidth;
	__property  WantTabs;
    // TCustomSynEdit events
	__property  OnChange;
	__property  OnCommandProcessed;
	__property  OnDropFiles;
	__property  OnGutterClick;
	__property  OnGutterGetText;
	__property  OnPaint;
	__property  OnPlaceBookmark;
	__property  OnProcessCommand;
	__property  OnProcessUserCommand;
	__property  OnReplaceText;
	__property  OnSpecialLineColors;
	__property  OnStatusChange;
	__property  OnPaintTransient;
public:
	typedef TCustomDBSynEdit inherited;
	#include "SynDBEdit_friends.inc"
	__fastcall TDBSynEdit(TComponent* AOwner);
	__fastcall TDBSynEdit(HWND ParentWindow);
};


}  // namespace SynDBEdit

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syndbedit;
#endif

#endif // SynDBEditH

