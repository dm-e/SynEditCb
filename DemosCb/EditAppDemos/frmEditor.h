/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: frmEditor.pas, released 2000-09-08.

The Original Code is part of the EditAppDemos project, written by
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

$Id: frmEditor.pas,v 1.5.2.2 2008/09/14 16:24:57 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef frmEditorH
#define frmEditorH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include "uEditAppIntfs.h"
#include "SynEdit.h"
#include "SynEditTypes.h"
#include "SynEditMiscProcs.h"
#include "SynEditMiscClasses.h"
#include "SynEditSearch.h"
#include "SynUnicode.h"

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: frmEditor.pas, released 2000-09-08.

The Original Code is part of the EditAppDemos project, written by
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

$Id: frmEditor.pas,v 1.5.2.2 2008/09/14 16:24:57 maelh Exp $

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
class DELPHICLASS TEditor;
enum TEditorKind {ekBorderless,
                  ekInTabsheet,
                  ekMDIChild };

class TEditorForm : public TForm
{
__published:
	TPopupMenu* pmnuEditor;
	TMenuItem* lmiEditCut;
	TMenuItem* lmiEditCopy;
	TMenuItem* lmiEditPaste;
	TMenuItem* lmiEditDelete;
	TMenuItem* N1;
	TMenuItem* lmiEditSelectAll;
	TMenuItem* lmiEditUndo;
	TMenuItem* lmiEditRedo;
	TMenuItem* N2;
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall FormCloseQuery(TObject* Sender, bool& CanClose);
	void __fastcall FormDestroy(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall FormActivate(TObject* Sender);
	void __fastcall FormDeactivate(TObject* Sender);
	void __fastcall SynEditorChange(TObject* Sender);
	void __fastcall SynEditorEnter(TObject* Sender);
	void __fastcall SynEditorExit(TObject* Sender);
	void __fastcall SynEditorReplaceText(TObject* Sender, const UnicodeString ASearch, const UnicodeString AReplace, int Line, int Column, TSynReplaceAction& Action);
	void __fastcall SynEditorStatusChange(TObject* Sender, TSynStatusChanges Changes);
	void __fastcall FormCreate(TObject *Sender);
private:
	TSynEdit* SynEditor;
	TSynEditSearch* SynEditSearch1;
	TEditor* FEditor;
	TEditorKind FKind;
	bool fSearchFromCaret;
	bool __fastcall DoAskSaveChanges();
	void __fastcall DoAssignInterfacePointer(bool AActive);
	bool __fastcall DoSave();
	bool __fastcall DoSaveFile();
	bool __fastcall DoSaveAs();
	void __fastcall DoSearchReplaceText(bool AReplace, bool ABackwards);
	void __fastcall DoUpdateCaption();
	void __fastcall DoUpdateHighlighter();
	void __fastcall ShowSearchReplaceDialog(bool AReplace);
public:
	typedef TForm inherited;
	#include "frmEditor_friends.inc"
	void __fastcall DoActivate();
	__fastcall TEditorForm(TComponent* AOwner);
};

class TEditor : public TCppInterfacedObject<IEditor>, public IEditCommands, public IFileCommands, public ISearchCommands
{
	#include "frmEditor_friends.inc"
public:
	typedef TCppInterfacedObject<IEditor> inherited;
private:
    // IEditor implementation
	void __fastcall Activate();
	bool __fastcall AskSaveChanges();
	void __fastcall Close();
	TPoint __fastcall GetCaretPos();
	String __fastcall GetEditorState();
	String __fastcall GetFileName();
	String __fastcall GetFileTitle();
	bool __fastcall GetModified();
	void __fastcall OpenFile(String AFileName);
    // IEditCommands implementation
	bool __fastcall CanCopy();
	bool __fastcall CanCut();
	bool __fastcall CanPaste();
	bool __fastcall CanRedo();
	bool __fastcall CanSelectAll();
	bool __fastcall CanUndo();
	void __fastcall ExecCopy();
	void __fastcall ExecCut();
	void __fastcall ExecDelete();
	void __fastcall ExecPaste();
	void __fastcall ExecRedo();
	void __fastcall ExecSelectAll();
	void __fastcall ExecUndo();
    // IFileCommands implementation
	bool __fastcall CanClose();
	bool __fastcall CanPrint();
	bool __fastcall CanSave();
	bool __fastcall CanSaveAs();
	void __fastcall ExecPrint();
	void __fastcall ExecSave();
	void __fastcall ExecSaveAs();
    // ISearchCommands implementation
	bool __fastcall CanFind();
	bool __fastcall CanFindNext();
	bool __fastcall CanReplace();
	void __fastcall ExecFind();
	void __fastcall ExecFindNext();
	void __fastcall ExecFindPrev();
	void __fastcall ExecReplace();

    bool __fastcall CanDelete() {return false;} // dme else abstract
    void __fastcall ExecClose(){} // dme else abstract
    bool __fastcall CanFindPrev() {return false;} // dme abstract

	String FFileName;
	TEditorForm* FForm;
	bool fHasSelection;
	bool FIsEmpty;
	bool fIsReadOnly;
	bool FModified;
	int fUntitledNumber;
	__fastcall TEditor(TEditorForm* AForm);
	void __fastcall DoSetFileName(String AFileName);
public:
	__fastcall TEditor();
};

void frmEditor_initialization();
void frmEditor_finalization();

#endif // frmEditorH

