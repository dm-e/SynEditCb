#include <vcl.h>
#pragma hdrstop

#include "dmCommands.h"
#include "uHighlighterProcs.hpp"
#include "uEditAppIntfs.h"

using namespace std;
using namespace d2c_system;

__fastcall TCommandsDataModule::TCommandsDataModule(TComponent* AOwner) : inherited(AOwner) {}


TCommandsDataModule* CommandsDataModule = nullptr;
#pragma resource "*.DFM" 

const int MAX_MRU = 5;
const System::Char SFilterAllFiles[] = L"All files|*.*|";

/* TCommandsDataModule */

void __fastcall TCommandsDataModule::DataModuleCreate(TObject* Sender)
{
	fHighlighters = new TStringList();
	GetHighlighters(this, fHighlighters, false);
	dlgFileOpen->Filter = GetHighlightersFilter(fHighlighters) + SFilterAllFiles;
	fMRUFiles = new TStringList();
}

void __fastcall TCommandsDataModule::DataModuleDestroy(TObject* Sender)
{
	delete fMRUFiles;
	delete fHighlighters;
	delete fUntitledNumbers;
	CommandsDataModule = nullptr;
}

// implementation

void __fastcall TCommandsDataModule::AddMRUEntry(String AFileName)
{
	if(AFileName != L"")
	{
		RemoveMRUEntry(AFileName);
		fMRUFiles->Insert(0, AFileName);
		while(fMRUFiles->Count > MAX_MRU)
			fMRUFiles->Delete(fMRUFiles->Count - 1);
	}
}

TSynCustomHighlighter* __fastcall TCommandsDataModule::GetHighlighterForFile(String AFileName)
{
	TSynCustomHighlighter* result = nullptr;
	if(AFileName != L"")
		result = GetHighlighterFromFileExt(fHighlighters, ExtractFileExt(AFileName));
	else
		result = nullptr;
	return result;
}

int __fastcall TCommandsDataModule::GetMRUEntries()
{
	int result = 0;
	result = fMRUFiles->Count;
	return result;
}

String __fastcall TCommandsDataModule::GetMRUEntry(int Index)
{
	String result;
	if((Index >= 0) && (Index < fMRUFiles->Count))
		result = fMRUFiles->Strings[Index];
	else
		result = L"";
	return result;
}

bool __fastcall TCommandsDataModule::GetSaveFileName(String& ANewName, TSynCustomHighlighter* AHighlighter)
{
	bool result = false;
	/*# with dlgFileSave do */
	{
		auto with0 = dlgFileSave;
		if(ANewName != L"")
		{
			with0->InitialDir = ExtractFileDir(ANewName);
			with0->FileName = ExtractFileName(ANewName);
		}
		else
		{
			with0->InitialDir = L"";
			with0->FileName = L"";
		}
		if(AHighlighter != nullptr)
			with0->Filter = AHighlighter->DefaultFilter;
		else
			with0->Filter = SFilterAllFiles;
		if(with0->Execute())
		{
			ANewName = with0->FileName;
			result = true;
		}
		else
		result = false;
	}
	return result;
}

int __fastcall TCommandsDataModule::GetUntitledNumber()
{
	int result = 0;
	if(fUntitledNumbers == nullptr)
		fUntitledNumbers = new TBits();
	result = fUntitledNumbers->OpenBit();
	if(result == fUntitledNumbers->Size)
		fUntitledNumbers->Size = fUntitledNumbers->Size + 32;
	fUntitledNumbers->Bits[result] = true;
	++result;
	return result;
}

void __fastcall TCommandsDataModule::ReleaseUntitledNumber(int ANumber)
{
	--ANumber;
	if((fUntitledNumbers != nullptr) && (ANumber >= 0) && (ANumber < fUntitledNumbers->Size))
		fUntitledNumbers->Bits[ANumber] = false;
}

void __fastcall TCommandsDataModule::RemoveMRUEntry(String AFileName)
{
	int i = 0;
	int stop = 0;
	for(stop = 0, i = fMRUFiles->Count - 1; i >= stop; i--)
	{
		if(CompareText(AFileName, fMRUFiles->Strings[i]) == 0)
			fMRUFiles->Delete(i);
	}
}

void __fastcall TCommandsDataModule::actFileSaveExecute(TObject* Sender)
{
	if(GI_FileCmds != nullptr)
		GI_FileCmds->ExecSave();
}

void __fastcall TCommandsDataModule::actFileSaveUpdate(TObject* Sender)
{
	actFileSave->Enabled = (GI_FileCmds != nullptr) && GI_FileCmds->CanSave();
}

void __fastcall TCommandsDataModule::actFileSaveAsExecute(TObject* Sender)
{
	if(GI_FileCmds != nullptr)
		GI_FileCmds->ExecSaveAs();
}

void __fastcall TCommandsDataModule::actFileSaveAsUpdate(TObject* Sender)
{
	actFileSaveAs->Enabled = (GI_FileCmds != nullptr) && GI_FileCmds->CanSaveAs();
}

void __fastcall TCommandsDataModule::actFilePrintExecute(TObject* Sender)
{
	if(GI_FileCmds != nullptr)
		GI_FileCmds->ExecPrint();
}

void __fastcall TCommandsDataModule::actFilePrintUpdate(TObject* Sender)
{
	actFilePrint->Enabled = (GI_FileCmds != nullptr) && GI_FileCmds->CanPrint();
}

void __fastcall TCommandsDataModule::actFileCloseExecute(TObject* Sender)
{
	if(GI_FileCmds != nullptr)
		GI_FileCmds->ExecClose();
}

void __fastcall TCommandsDataModule::actFileCloseUpdate(TObject* Sender)
{
	actFileClose->Enabled = (GI_FileCmds != nullptr) && GI_FileCmds->CanClose();
}

void __fastcall TCommandsDataModule::actEditCutExecute(TObject* Sender)
{
	if(GI_EditCmds != nullptr)
		GI_EditCmds->ExecCut();
}

void __fastcall TCommandsDataModule::actEditCutUpdate(TObject* Sender)
{
	actEditCut->Enabled = (GI_EditCmds != nullptr) && GI_EditCmds->CanCut();
}

void __fastcall TCommandsDataModule::actEditCopyExecute(TObject* Sender)
{
	if(GI_EditCmds != nullptr)
		GI_EditCmds->ExecCopy();
}

void __fastcall TCommandsDataModule::actEditCopyUpdate(TObject* Sender)
{
	actEditCopy->Enabled = (GI_EditCmds != nullptr) && GI_EditCmds->CanCopy();
}

void __fastcall TCommandsDataModule::actEditPasteExecute(TObject* Sender)
{
	if(GI_EditCmds != nullptr)
		GI_EditCmds->ExecPaste();
}

void __fastcall TCommandsDataModule::actEditPasteUpdate(TObject* Sender)
{
	actEditPaste->Enabled = (GI_EditCmds != nullptr) && GI_EditCmds->CanPaste();
}

void __fastcall TCommandsDataModule::actEditDeleteExecute(TObject* Sender)
{
	if(GI_EditCmds != nullptr)
		GI_EditCmds->ExecDelete();
}

void __fastcall TCommandsDataModule::actEditDeleteUpdate(TObject* Sender)
{
	actEditDelete->Enabled = (GI_EditCmds != nullptr) && GI_EditCmds->CanDelete();
}

void __fastcall TCommandsDataModule::actEditSelectAllExecute(TObject* Sender)
{
	if(GI_EditCmds != nullptr)
		GI_EditCmds->ExecSelectAll();
}

void __fastcall TCommandsDataModule::actEditSelectAllUpdate(TObject* Sender)
{
	actEditSelectAll->Enabled = (GI_EditCmds != nullptr) && GI_EditCmds->CanSelectAll();
}

void __fastcall TCommandsDataModule::actEditRedoExecute(TObject* Sender)
{
	if(GI_EditCmds != nullptr)
		GI_EditCmds->ExecRedo();
}

void __fastcall TCommandsDataModule::actEditRedoUpdate(TObject* Sender)
{
	actEditRedo->Enabled = (GI_EditCmds != nullptr) && GI_EditCmds->CanRedo();
}

void __fastcall TCommandsDataModule::actEditUndoExecute(TObject* Sender)
{
	if(GI_EditCmds != nullptr)
		GI_EditCmds->ExecUndo();
}

void __fastcall TCommandsDataModule::actEditUndoUpdate(TObject* Sender)
{
	actEditUndo->Enabled = (GI_EditCmds != nullptr) && GI_EditCmds->CanUndo();
}

void __fastcall TCommandsDataModule::actSearchFindExecute(TObject* Sender)
{
	if(GI_SearchCmds != nullptr)
		GI_SearchCmds->ExecFind();
}

void __fastcall TCommandsDataModule::actSearchFindUpdate(TObject* Sender)
{
	actSearchFind->Enabled = (GI_SearchCmds != nullptr) && GI_SearchCmds->CanFind();
}

void __fastcall TCommandsDataModule::actSearchFindNextExecute(TObject* Sender)
{
	if(GI_SearchCmds != nullptr)
		GI_SearchCmds->ExecFindNext();
}

void __fastcall TCommandsDataModule::actSearchFindNextUpdate(TObject* Sender)
{
	actSearchFindNext->Enabled = (GI_SearchCmds != nullptr) && GI_SearchCmds->CanFindNext();
}

void __fastcall TCommandsDataModule::actSearchFindPrevExecute(TObject* Sender)
{
	if(GI_SearchCmds != nullptr)
		GI_SearchCmds->ExecFindPrev();
}

void __fastcall TCommandsDataModule::actSearchFindPrevUpdate(TObject* Sender)
{
	actSearchFindPrev->Enabled = (GI_SearchCmds != nullptr) && GI_SearchCmds->CanFindPrev();
}

void __fastcall TCommandsDataModule::actSearchReplaceExecute(TObject* Sender)
{
	if(GI_SearchCmds != nullptr)
		GI_SearchCmds->ExecReplace();
}

void __fastcall TCommandsDataModule::actSearchReplaceUpdate(TObject* Sender)
{
	actSearchReplace->Enabled = (GI_SearchCmds != nullptr) && GI_SearchCmds->CanReplace();
}
