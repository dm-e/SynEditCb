/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynAutoCorrectEditor.pas, released 2001-10-05.
Author of this file is Aaron Chan.
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

$Id: SynAutoCorrectEditor.pas,v 1.9.2.3 2008/09/14 16:24:57 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef SynAutoCorrectEditorH
#define SynAutoCorrectEditorH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <System.Win.Registry.hpp>
#include "SynAutoCorrect.h"
#include "SynUnicode.h"
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

class TfrmAutoCorrectEditor : public TForm
{
__published:
public:
	TLabel* lblLabel1;
	TLabel* lblLabel2;
	TListBox* lbxItems;
	TSpeedButton* btnAdd;
	TSpeedButton* btnDelete;
	TSpeedButton* btnClear;
	TSpeedButton* btnEdit;
	TSpeedButton* btnDone;
	TBevel* bvlSeparator;
	void __fastcall FormShow(TObject* Sender);
	void __fastcall btnAddClick(TObject* Sender);
	void __fastcall btnDeleteClick(TObject* Sender);
	void __fastcall btnEditClick(TObject* Sender);
	void __fastcall btnDoneClick(TObject* Sender);
	void __fastcall btnClearClick(TObject* Sender);
	void __fastcall lbxItemsClick(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormPaint(TObject* Sender);
private:
	void __fastcall lbxItemsDrawItemCLX(TObject* Sender, int Index, const TRect& Rect, TOwnerDrawState State, bool& Handled);
	void __fastcall lbxItemsDrawItem(TWinControl* Control, int Index, const TRect& Rect, TOwnerDrawState State);
public:
	Synautocorrect::TSynAutoCorrect* SynAutoCorrect;
	typedef TForm inherited;
	__fastcall TfrmAutoCorrectEditor(TComponent* AOwner, int Dummy);
protected:
	//# please uncomment for main forms
	//# void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params)
		//# {inherited::CreateParams(Params); Params.ExStyle = Params.ExStyle | WS_EX_APPWINDOW;}
};
const System::Char SConfirmation[] = L"Confirmation";
const System::Char SError[] = L"Error";
const System::Char SOriginal[] = L"Original:";
const System::Char SCorrection[] = L"Correction:";
const System::Char SAdd[] = L"Add...";
const System::Char SEdit[] = L"Edit...";
const System::Char SPleaseSelectItem[] = L"Please select an item before executing this command!";
const System::Char SClearListConfirmation[] = L"Are you sure you want to clear the entire list?";
#endif // SynAutoCorrectEditorH

