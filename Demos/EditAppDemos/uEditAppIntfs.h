#ifndef uEditAppIntfsH
#define uEditAppIntfsH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: uEditAppIntfs.pas, released 2000-09-08.

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

$Id: uEditAppIntfs.pas,v 1.2 2000/11/22 08:34:14 mghie Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
__interface IEditor
{
	virtual void __fastcall Activate() = 0;
	virtual bool __fastcall AskSaveChanges() = 0;
	virtual bool __fastcall CanClose() = 0;
	virtual void __fastcall Close() = 0;
	virtual TPoint __fastcall GetCaretPos() = 0;
	virtual String __fastcall GetEditorState() = 0;
	virtual String __fastcall GetFileName() = 0;
	virtual String __fastcall GetFileTitle() = 0;
	virtual bool __fastcall GetModified() = 0;
	virtual void __fastcall OpenFile(String AFileName) = 0;
};
__interface IEditorFactory
{
	virtual bool __fastcall CanCloseAll() = 0;
	virtual void __fastcall CloseAll() = 0;
	virtual IEditor* __fastcall CreateBorderless(TForm* AOwner) = 0;
	virtual IEditor* __fastcall CreateMDIChild(TForm* AOwner) = 0;
	virtual IEditor* __fastcall CreateTabSheet(TPageControl* AOwner) = 0;
	virtual int __fastcall GetEditorCount() = 0;
	virtual IEditor* __fastcall GetEditor(int Index) = 0;
	virtual void __fastcall RemoveEditor(IEditor* AEditor) = 0;
	__property IEditor* Editor[int Index] = { read = GetEditor };
};
__interface IEditCommands
{
	virtual bool __fastcall CanCopy() = 0;
	virtual bool __fastcall CanCut() = 0;
	virtual bool __fastcall CanDelete() = 0;
	virtual bool __fastcall CanPaste() = 0;
	virtual bool __fastcall CanRedo() = 0;
	virtual bool __fastcall CanSelectAll() = 0;
	virtual bool __fastcall CanUndo() = 0;
	virtual void __fastcall ExecCopy() = 0;
	virtual void __fastcall ExecCut() = 0;
	virtual void __fastcall ExecDelete() = 0;
	virtual void __fastcall ExecPaste() = 0;
	virtual void __fastcall ExecRedo() = 0;
	virtual void __fastcall ExecSelectAll() = 0;
	virtual void __fastcall ExecUndo() = 0;
};
__interface IFileCommands
{
	virtual bool __fastcall CanClose() = 0;
	virtual bool __fastcall CanPrint() = 0;
	virtual bool __fastcall CanSave() = 0;
	virtual bool __fastcall CanSaveAs() = 0;
	virtual void __fastcall ExecClose() = 0;
	virtual void __fastcall ExecPrint() = 0;
	virtual void __fastcall ExecSave() = 0;
	virtual void __fastcall ExecSaveAs() = 0;
};
__interface ISearchCommands
{
	virtual bool __fastcall CanFind() = 0;
	virtual bool __fastcall CanFindNext() = 0;
	virtual bool __fastcall CanFindPrev() = 0;
	virtual bool __fastcall CanReplace() = 0;
	virtual void __fastcall ExecFind() = 0;
	virtual void __fastcall ExecFindNext() = 0;
	virtual void __fastcall ExecFindPrev() = 0;
	virtual void __fastcall ExecReplace() = 0;
};
extern IEditorFactory* GI_EditorFactory;
extern IEditor* GI_ActiveEditor;
extern IEditCommands* GI_EditCmds;
extern IFileCommands* GI_FileCmds;
extern ISearchCommands* GI_SearchCmds;
#endif // uEditAppIntfsH

