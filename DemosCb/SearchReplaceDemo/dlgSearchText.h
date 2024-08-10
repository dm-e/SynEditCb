/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: dlgSearchText.pas, released 2000-06-23.

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

$Id: dlgSearchText.pas,v 1.3 2002/08/01 05:44:05 etrusco Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef dlgSearchTextH
#define dlgSearchTextH

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

The Original Code is: dlgSearchText.pas, released 2000-06-23.

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

$Id: dlgSearchText.pas,v 1.3 2002/08/01 05:44:05 etrusco Exp $

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

class TTextSearchDialog : public TForm
{
__published:
	TLabel* Label1;
	TComboBox* cbSearchText;
	TRadioGroup* rgSearchDirection;
	TGroupBox* gbSearchOptions;
	TCheckBox* cbSearchCaseSensitive;
	TCheckBox* cbSearchWholeWords;
	TCheckBox* cbSearchFromCursor;
	TCheckBox* cbSearchSelectedOnly;
	TButton* btnOK;
	TButton* btnCancel;
	TCheckBox* cbRegularExpression;
	void __fastcall FormCloseQuery(TObject* Sender, bool& CanClose);
private:
	bool __fastcall GetSearchBackwards();
	bool __fastcall GetSearchCaseSensitive();
	bool __fastcall GetSearchFromCursor();
	bool __fastcall GetSearchInSelection();
	String __fastcall GetSearchText();
	String __fastcall GetSearchTextHistory();
	bool __fastcall GetSearchWholeWords();
	void __fastcall SetSearchBackwards(bool Value);
	void __fastcall SetSearchCaseSensitive(bool Value);
	void __fastcall SetSearchFromCursor(bool Value);
	void __fastcall SetSearchInSelection(bool Value);
	void __fastcall SetSearchText(String Value);
	void __fastcall SetSearchTextHistory(String Value);
	void __fastcall SetSearchWholeWords(bool Value);
	void __fastcall SetSearchRegularExpression(bool Value);
	bool __fastcall GetSearchRegularExpression();
public:
	typedef TForm inherited;
	__property bool SearchBackwards = { read = GetSearchBackwards, write = SetSearchBackwards };
	__property bool SearchCaseSensitive = { read = GetSearchCaseSensitive, write = SetSearchCaseSensitive };
	__property bool SearchFromCursor = { read = GetSearchFromCursor, write = SetSearchFromCursor };
	__property bool SearchInSelectionOnly = { read = GetSearchInSelection, write = SetSearchInSelection };
	__property String SearchText = { read = GetSearchText, write = SetSearchText };
	__property String SearchTextHistory = { read = GetSearchTextHistory, write = SetSearchTextHistory };
	__property bool SearchWholeWords = { read = GetSearchWholeWords, write = SetSearchWholeWords };
	__property bool SearchRegularExpression = { read = GetSearchRegularExpression, write = SetSearchRegularExpression };
	__fastcall TTextSearchDialog(TComponent* AOwner);
};

#endif // dlgSearchTextH

