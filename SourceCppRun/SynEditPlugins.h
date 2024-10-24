/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPlugins.pas, released 2001-10-17.

Author of this file is Flávio Etrusco.
Portions created by Flávio Etrusco are Copyright 2001 Flávio Etrusco.
Unicode translation by Maël Hörz.
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

$Id: SynEditPlugins.pas,v 1.8.2.2 2008/09/14 16:24:58 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef SynEditPluginsH
#define SynEditPluginsH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Menus.hpp>
#include "SynEdit.h"
#include "SynEditTypes.h"
#include "SynEditKeyCmds.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>

namespace Syneditplugins
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

class TAbstractSynPlugin : public System::Classes::TComponent
{
private:
	void __fastcall SetEditor(Synedit::TCustomSynEdit* const Value);
	Synedit::TCustomSynEdit* __fastcall GetEditors(int aIndex);
	Synedit::TCustomSynEdit* __fastcall GetEditor();
	int __fastcall GetEditorCount();
protected:
	TList* fEditors;
	virtual void __fastcall Notification(TComponent* aComponent, TOperation aOperation);
	virtual void __fastcall DoAddEditor(Synedit::TCustomSynEdit* aEditor);
	virtual void __fastcall DoRemoveEditor(Synedit::TCustomSynEdit* aEditor);
	int __fastcall AddEditor(Synedit::TCustomSynEdit* aEditor);
	int __fastcall RemoveEditor(Synedit::TCustomSynEdit* aEditor);
public:
	typedef System::Classes::TComponent inherited;
	#include "SynEditPlugins_friends.inc"
	virtual __fastcall ~TAbstractSynPlugin();
	__property Synedit::TCustomSynEdit* Editors[int aIndex] = { read = GetEditors };
	__property int EditorCount = { read = GetEditorCount };
__published:
	__property Synedit::TCustomSynEdit* Editor = { read = GetEditor, write = SetEditor };
public:
	__fastcall TAbstractSynPlugin(TComponent* AOwner);
};

class TAbstractSynHookerPlugin : public TAbstractSynPlugin
{
protected:
	void __fastcall HookEditor(Synedit::TCustomSynEdit* aEditor, Synedittypes::TSynEditorCommand aCommandID, TShortCut aOldShortCut, TShortCut aNewShortCut);
	void __fastcall UnHookEditor(Synedit::TCustomSynEdit* aEditor, Synedittypes::TSynEditorCommand aCommandID, TShortCut aShortCut);
	virtual void __fastcall OnCommand(TObject* Sender, bool AfterProcessing, bool& Handled, Synedittypes::TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData){} // = 0;
public:
	typedef TAbstractSynPlugin inherited;
	#include "SynEditPlugins_friends.inc"
	__fastcall TAbstractSynHookerPlugin(TComponent* AOwner);
};
enum TPluginState {psNone,
                   psExecuting,
                   psAccepting,
                   psCancelling };

class TAbstractSynSingleHookPlugin : public TAbstractSynHookerPlugin
{
private:
	Synedittypes::TSynEditorCommand fCommandID;
	bool __fastcall IsShortCutStored();
	void __fastcall SetShortCut(const TShortCut Value);
protected:
	TPluginState fState;
	Synedit::TCustomSynEdit* fCurrentEditor;
	TShortCut fShortCut;
	__classmethod virtual TShortCut __fastcall DefaultShortCut();
	virtual void __fastcall DoAddEditor(Synedit::TCustomSynEdit* aEditor);
	virtual void __fastcall DoRemoveEditor(Synedit::TCustomSynEdit* aEditor);
    /**/
	virtual void __fastcall DoExecute(){} // = 0;
	virtual void __fastcall DoAccept(){} // = 0;
	virtual void __fastcall DoCancel(){} // = 0;
public:
	typedef TAbstractSynHookerPlugin inherited;
	#include "SynEditPlugins_friends.inc"
	__fastcall TAbstractSynSingleHookPlugin(TComponent* aOwner);
	virtual __fastcall ~TAbstractSynSingleHookPlugin();
	__property Synedittypes::TSynEditorCommand CommandID = { read = fCommandID };
	__property Synedit::TCustomSynEdit* CurrentEditor = { read = fCurrentEditor };
	bool __fastcall Executing();
	void __fastcall Execute(Synedit::TCustomSynEdit* aEditor);
	void __fastcall Accept();
	void __fastcall Cancel();
__published:
	__property TShortCut ShortCut = { read = fShortCut, write = SetShortCut, stored = IsShortCutStored };
};

  /* use TAbstractSynCompletion for non-visual completion */

class TAbstractSynCompletion : public TAbstractSynSingleHookPlugin
{
protected:
	String fCurrentString;
	virtual void __fastcall SetCurrentString(const String Value);
	virtual void __fastcall OnCommand(TObject* Sender, bool AfterProcessing, bool& Handled, Synedittypes::TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData);
	virtual void __fastcall DoExecute();
	virtual void __fastcall DoAccept();
	virtual void __fastcall DoCancel();
	virtual String __fastcall GetCurrentEditorString();
public:
	typedef TAbstractSynSingleHookPlugin inherited;
	#include "SynEditPlugins_friends.inc"
	void __fastcall AddEditor(Synedit::TCustomSynEdit* aEditor);
	__property String CurrentString = { read = fCurrentString, write = SetCurrentString };
	__fastcall TAbstractSynCompletion(TComponent* aOwner);
};
Synedittypes::TSynEditorCommand __fastcall NewPluginCommand();
void __fastcall ReleasePluginCommand(Synedittypes::TSynEditorCommand aCmd);


}  // namespace SynEditPlugins

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditplugins;
#endif

#endif // SynEditPluginsH

