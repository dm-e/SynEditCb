/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditKeyCmdsEditor.pas, released 2000-04-07.
The Original Code is based on the mwKeyCmdsEditor.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Brad Stowers.
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

$Id: SynEditKeyCmdsEditor.pas,v 1.10.2.2 2004/12/10 15:31:05 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef SynEditKeyCmdsEditorH
#define SynEditKeyCmdsEditorH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "SynEditKeyCmds.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>




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

class TSynEditKeystrokesEditorForm : public TForm
{
__published:
public:
	TPanel* pnlBottom;
	TLabel* lnlInfo;
	TLabel* lnlInfo2;
	TButton* btnAdd;
	TButton* btnEdit;
	TButton* btnDelete;
	TButton* btnClear;
	TButton* btnReset;
	TButton* btnOK;
	TButton* btnCancel;
	TPanel* pnlCommands;
	TListView* KeyCmdList;
	void __fastcall FormResize(TObject* Sender);
	void __fastcall btnAddClick(TObject* Sender);
	void __fastcall btnEditClick(TObject* Sender);
	void __fastcall btnDeleteClick(TObject* Sender);
	void __fastcall btnResetClick(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall btnClearClick(TObject* Sender);
	void __fastcall btnOKClick(TObject* Sender);
	void __fastcall btnCancelClick(TObject* Sender);
	void __fastcall KeyCmdListClick(TObject* Sender);
private:
	Syneditkeycmds::TSynEditKeyStrokes* fKeyStrokes;
	bool FExtended;
	void __fastcall SetKeystrokes(Syneditkeycmds::TSynEditKeyStrokes* const Value);
	void __fastcall UpdateKeystrokesList();
	HIDESBASE MESSAGE void __fastcall WMGetMinMaxInfo(TWMGetMinMaxInfo& Msg)/*# WM_GETMINMAXINFO */;
public:
	typedef TForm inherited;
	__fastcall TSynEditKeystrokesEditorForm(TComponent* AOwner);
	virtual __fastcall ~TSynEditKeystrokesEditorForm();
	__property Syneditkeycmds::TSynEditKeyStrokes* Keystrokes = { read = fKeyStrokes, write = SetKeystrokes };
	__property bool ExtendedString = { read = FExtended, write = FExtended };
protected:
	BEGIN_MESSAGE_MAP
	  VCL_MESSAGE_HANDLER(WM_GETMINMAXINFO, TWMGetMinMaxInfo, WMGetMinMaxInfo)
	END_MESSAGE_MAP(Vcl::Forms::TCustomForm)
};
#endif // SynEditKeyCmdsEditorH

