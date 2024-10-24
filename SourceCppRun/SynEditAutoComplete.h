/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditAutoComplete.pas, released 2000-06-25.

The Initial Author of the Original Code is Michael Hieke.
Portions written by Michael Hieke are Copyright 2000 Michael Hieke.
Portions written by Cyrille de Brebisson (from mwCompletionProposal.pas) are
Copyright 1999 Cyrille de Brebisson.
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

$Id: SynEditAutoComplete.pas,v 1.10.2.4 2008/09/14 16:24:58 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef SynEditAutoCompleteH
#define SynEditAutoCompleteH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Menus.hpp>
#include "SynEdit.h"
#include "SynEditTypes.h"
#include "SynEditKeyCmds.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>

namespace Syneditautocomplete
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

class TCustomSynAutoComplete : public System::Classes::TComponent
{
protected:
	TStrings* fAutoCompleteList;
	TStrings* fCompletions;
	TStrings* fCompletionComments;
	TStrings* fCompletionValues;
	Synedit::TCustomSynEdit* fEditor;
	TList* fEditors;
	String fEOTokenChars;
	bool fCaseSensitive;
	bool fParsed;
	void __fastcall CompletionListChanged(TObject* Sender);
	virtual void __fastcall DefineProperties(TFiler* Filer);
	TStrings* __fastcall GetCompletions();
	TStrings* __fastcall GetCompletionComments();
	TStrings* __fastcall GetCompletionValues();
	int __fastcall GetEditorCount();
	Synedit::TCustomSynEdit* __fastcall GetNthEditor(int Index);
	virtual void __fastcall SetAutoCompleteList(TStrings* Value);
	void __fastcall SetEditor(Synedit::TCustomSynEdit* Value);
	void __fastcall SynEditCommandHandler(TObject* Sender, bool AfterProcessing, bool& Handled, Synedittypes::TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData);
	virtual void __fastcall Notification(TComponent* AComponent, TOperation Operation);
public:
	typedef System::Classes::TComponent inherited;
	#include "SynEditAutoComplete_friends.inc"
	__fastcall TCustomSynAutoComplete(TComponent* AOwner);
	virtual __fastcall ~TCustomSynAutoComplete();
	bool __fastcall AddEditor(Synedit::TCustomSynEdit* AEditor);
	bool __fastcall RemoveEditor(Synedit::TCustomSynEdit* AEditor);
	void __fastcall AddCompletion(const String AToken, const String AValue, const String AComment);
	virtual void __fastcall Execute(Synedit::TCustomSynEdit* AEditor);
	virtual void __fastcall ExecuteCompletion(const String AToken, Synedit::TCustomSynEdit* AEditor);
	virtual void __fastcall ParseCompletionList();
	__property TStrings* AutoCompleteList = { read = fAutoCompleteList, write = SetAutoCompleteList };
	__property bool CaseSensitive = { read = fCaseSensitive, write = fCaseSensitive };
	__property TStrings* Completions = { read = GetCompletions };
	__property TStrings* CompletionComments = { read = GetCompletionComments };
	__property TStrings* CompletionValues = { read = GetCompletionValues };
	__property Synedit::TCustomSynEdit* Editor = { read = fEditor, write = SetEditor };
	__property int EditorCount = { read = GetEditorCount };
	__property Synedit::TCustomSynEdit* Editors[int Index] = { read = GetNthEditor };
	__property String EndOfTokenChr = { read = fEOTokenChars, write = fEOTokenChars };
};

class TSynAutoComplete : public TCustomSynAutoComplete
{
__published:
	__property  AutoCompleteList;
	__property  CaseSensitive;
	__property  Editor;
	__property  EndOfTokenChr;
public:
	typedef TCustomSynAutoComplete inherited;
	#include "SynEditAutoComplete_friends.inc"
	__fastcall TSynAutoComplete(TComponent* AOwner);
};


}  // namespace SynEditAutoComplete

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditautocomplete;
#endif

#endif // SynEditAutoCompleteH

