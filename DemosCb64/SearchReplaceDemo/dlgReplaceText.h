/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: dlgReplaceText.pas, released 2000-06-23.

The Original Code is part of the SearchReplaceDemo project, written by
Michael Hieke for the SynEdit component suite.
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

$Id: dlgReplaceText.pas,v 1.2 2000/11/22 08:37:05 mghie Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef dlgReplaceTextH
#define dlgReplaceTextH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include "dlgSearchText.h"
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: dlgReplaceText.pas, released 2000-06-23.

The Original Code is part of the SearchReplaceDemo project, written by
Michael Hieke for the SynEdit component suite.
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

$Id: dlgReplaceText.pas,v 1.2 2000/11/22 08:37:05 mghie Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

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

class TTextReplaceDialog : public TTextSearchDialog
{
__published:
public:
	TLabel* Label2;
	TComboBox* cbReplaceText;
	void __fastcall FormCloseQuery(TObject* Sender, bool& CanClose);
private:
	String __fastcall GetReplaceText();
	String __fastcall GetReplaceTextHistory();
	void __fastcall SetReplaceText(String Value);
	void __fastcall SetReplaceTextHistory(String Value);
public:
	typedef TTextSearchDialog inherited;
	__property String ReplaceText = { read = GetReplaceText, write = SetReplaceText };
	__property String ReplaceTextHistory = { read = GetReplaceTextHistory, write = SetReplaceTextHistory };
	__fastcall TTextReplaceDialog(TComponent* AOwner, int Dummy);
protected:
	//# please uncomment for main forms
	//# void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params)
		//# {inherited::CreateParams(Params); Params.ExStyle = Params.ExStyle | WS_EX_APPWINDOW;}
};

#endif // dlgReplaceTextH
