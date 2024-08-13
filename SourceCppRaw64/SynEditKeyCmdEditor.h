/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditKeyCmdEditor.pas, released 2000-04-07.
The Original Code is based on the mwKeyCmdEditor.pas file from the
mwEdit component suite by Martin Waldenburg and other developers.
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

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef SynEditKeyCmdEditorH
#define SynEditKeyCmdEditorH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "SynEditTypes.h"
#include "SynEditKeyCmds.h"
#include "SynEditMiscClasses.h"
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

class TSynEditKeystrokeEditorForm : public TForm
{
__published:
public:
	TPanel* pnlAlign;
	TLabel* Label1;
	TLabel* Label2;
	TLabel* Label4;
	TButton* bntClearKey;
	TButton* btnOK;
	TComboBox* cmbCommand;
	TButton* btnCancel;
	void __fastcall FormShow(TObject* Sender);
	void __fastcall bntClearKeyClick(TObject* Sender);
	void __fastcall btnOKClick(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
private:
	bool FExtended;
	void __fastcall SetCommand(Synedittypes::TSynEditorCommand Value);
	void __fastcall SetKeystroke(const TShortCut Value);
	void __fastcall AddEditorCommand(const String s);
	Synedittypes::TSynEditorCommand __fastcall GetCommand();
	TShortCut __fastcall GetKeystroke();
	TShortCut __fastcall GetKeystroke2();
	void __fastcall SetKeystroke2(const TShortCut Value);
public:
	Syneditmiscclasses::TSynHotKey* hkKeystroke2;
	Syneditmiscclasses::TSynHotKey* hkKeystroke;
	typedef TForm inherited;
	__property Synedittypes::TSynEditorCommand Command = { read = GetCommand, write = SetCommand };
	__property TShortCut Keystroke = { read = GetKeystroke, write = SetKeystroke };
	__property TShortCut Keystroke2 = { read = GetKeystroke2, write = SetKeystroke2 };
	__property bool ExtendedString = { read = FExtended, write = FExtended, default = true };
	__fastcall TSynEditKeystrokeEditorForm(TComponent* AOwner, int Dummy);
protected:
	//# please uncomment for main forms
	//# void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params)
		//# {inherited::CreateParams(Params); Params.ExStyle = Params.ExStyle | WS_EX_APPWINDOW;}
};
extern PACKAGE TSynEditKeystrokeEditorForm* SynEditKeystrokeEditorForm;
#endif // SynEditKeyCmdEditorH

