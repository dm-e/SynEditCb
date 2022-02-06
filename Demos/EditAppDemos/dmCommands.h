#ifndef dmCommandsH
#define dmCommandsH

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
#include <Vcl.ActnList.hpp>
#include "SynHighlighterSQL.hpp"
#include "SynHighlighterPas.hpp"
#include "SynEditHighlighter.hpp"
#include "SynHighlighterCpp.hpp"

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: dmCommands.pas, released 2000-09-08.

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

$Id: dmCommands.pas,v 1.2 2000/11/22 08:34:13 mghie Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

class TCommandsDataModule : public TDataModule
{
__published:
	TOpenDialog* dlgFileOpen;
	TActionList* actlMain;
	TAction* actFileSave;
	TAction* actFileSaveAs;
	TAction* actFileClose;
	TAction* actFilePrint;
	TAction* actEditCut;
	TAction* actEditCopy;
	TAction* actEditPaste;
	TAction* actEditDelete;
	TAction* actEditUndo;
	TAction* actEditRedo;
	TAction* actEditSelectAll;
	TAction* actSearchFind;
	TAction* actSearchFindNext;
	TAction* actSearchFindPrev;
	TAction* actSearchReplace;
	TSynCppSyn* SynCppSyn1;
	TSynPasSyn* SynPasSyn1;
	TSynSQLSyn* SynSQLSyn1;
	TSaveDialog* dlgFileSave;
	void __fastcall DataModuleCreate(TObject* Sender);
	void __fastcall DataModuleDestroy(TObject* Sender);
	void __fastcall actFileSaveExecute(TObject* Sender);
	void __fastcall actFileSaveUpdate(TObject* Sender);
	void __fastcall actFileSaveAsExecute(TObject* Sender);
	void __fastcall actFileSaveAsUpdate(TObject* Sender);
	void __fastcall actFilePrintExecute(TObject* Sender);
	void __fastcall actFilePrintUpdate(TObject* Sender);
	void __fastcall actFileCloseExecute(TObject* Sender);
	void __fastcall actFileCloseUpdate(TObject* Sender);
	void __fastcall actEditCutExecute(TObject* Sender);
	void __fastcall actEditCutUpdate(TObject* Sender);
	void __fastcall actEditCopyExecute(TObject* Sender);
	void __fastcall actEditCopyUpdate(TObject* Sender);
	void __fastcall actEditPasteExecute(TObject* Sender);
	void __fastcall actEditPasteUpdate(TObject* Sender);
	void __fastcall actEditDeleteExecute(TObject* Sender);
	void __fastcall actEditDeleteUpdate(TObject* Sender);
	void __fastcall actEditSelectAllExecute(TObject* Sender);
	void __fastcall actEditSelectAllUpdate(TObject* Sender);
	void __fastcall actEditRedoExecute(TObject* Sender);
	void __fastcall actEditRedoUpdate(TObject* Sender);
	void __fastcall actEditUndoExecute(TObject* Sender);
	void __fastcall actEditUndoUpdate(TObject* Sender);
	void __fastcall actSearchFindExecute(TObject* Sender);
	void __fastcall actSearchFindUpdate(TObject* Sender);
	void __fastcall actSearchFindNextExecute(TObject* Sender);
	void __fastcall actSearchFindNextUpdate(TObject* Sender);
	void __fastcall actSearchFindPrevExecute(TObject* Sender);
	void __fastcall actSearchFindPrevUpdate(TObject* Sender);
	void __fastcall actSearchReplaceExecute(TObject* Sender);
	void __fastcall actSearchReplaceUpdate(TObject* Sender);
private:
	TStringList* fHighlighters;
	TStringList* fMRUFiles;
	TBits* fUntitledNumbers;
public:
	typedef TDataModule inherited;	
	void __fastcall AddMRUEntry(String AFileName);
	TSynCustomHighlighter* __fastcall GetHighlighterForFile(String AFileName);
	int __fastcall GetMRUEntries();
	String __fastcall GetMRUEntry(int Index);
	bool __fastcall GetSaveFileName(String& ANewName, TSynCustomHighlighter* AHighlighter);
	int __fastcall GetUntitledNumber();
	void __fastcall ReleaseUntitledNumber(int ANumber);
	void __fastcall RemoveMRUEntry(String AFileName);
	__fastcall TCommandsDataModule(TComponent* AOwner);
};
extern TCommandsDataModule* CommandsDataModule;
#endif // dmCommandsH

