/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPrintMarginsDialog.pas, released 2000-06-01.

The Initial Author of the Original Code is Morten J. Skovrup.
Portions written by Morten J. Skovrup are copyright 2000 Morten J. Skovrup.
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

$Id: SynEditPrintMarginsDialog.pas,v 1.5.2.1 2004/08/31 12:55:18 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
CONTENTS:
  Property editor for TSynEditPrintMargins - nothing fancy, it only displays
  a picture that can help with understanding the different values.
-------------------------------------------------------------------------------*/
#ifndef SynEditPrintMarginsDialogH
#define SynEditPrintMarginsDialogH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include "SynEditPrint.h"
#include "SynEditPrintTypes.h"
#include "SynEditPrintMargins.h"
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

class TSynEditPrintMarginsDlg : public TForm
{
__published:
	TButton* OKBtn;
	TButton* CancelBtn;
	TImage* Image1;
	TLabel* Label1;
	TLabel* Label2;
	TLabel* Label3;
	TLabel* Label4;
	TLabel* Label5;
	TLabel* Label6;
	TLabel* Label7;
	TLabel* Label8;
	TLabel* Label9;
	TCheckBox* CBMirrorMargins;
	TLabel* Label10;
	TLabel* Label11;
	TEdit* EditLeft;
	TEdit* EditRight;
	TEdit* EditTop;
	TEdit* EditBottom;
	TEdit* EditGutter;
	TEdit* EditHeader;
	TEdit* EditFooter;
	TEdit* EditHFInternalMargin;
	TEdit* EditLeftHFTextIndent;
	TEdit* EditRightHFTextIndent;
	TComboBox* CBUnits;
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormDestroy(TObject* Sender);
	void __fastcall CBUnitsChange(TObject* Sender);
private:
    /* Private declarations */
	Syneditprintmargins::TSynEditPrintMargins* FMargins;
	bool FInternalCall;
public:
    /* Public declarations */
	typedef TForm inherited;
	void __fastcall SetMargins(Syneditprintmargins::TSynEditPrintMargins* SynEditMargins);
	void __fastcall GetMargins(Syneditprintmargins::TSynEditPrintMargins* SynEditMargins);
	__fastcall TSynEditPrintMarginsDlg(TComponent* AOwner);
};
#endif // SynEditPrintMarginsDialogH

