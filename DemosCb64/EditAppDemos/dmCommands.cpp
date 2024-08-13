#include <vcl.h>
#pragma hdrstop

#include "dmCommands.h"
#include "uHighlighterProcs.h"
#include "uEditAppIntfs.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;


TCommandsDataModule* CommandsDataModule = nullptr;
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

__fastcall TCommandsDataModule::TCommandsDataModule(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	dlgFileOpen(nullptr),
	actlMain(nullptr),
	actFileSave(nullptr),
	actFileSaveAs(nullptr),
	actFileClose(nullptr),
	actFilePrint(nullptr),
	actEditCut(nullptr),
	actEditCopy(nullptr),
	actEditPaste(nullptr),
	actEditDelete(nullptr),
	actEditUndo(nullptr),
	actEditRedo(nullptr),
	actEditSelectAll(nullptr),
	actSearchFind(nullptr),
	actSearchFindNext(nullptr),
	actSearchFindPrev(nullptr),
	actSearchReplace(nullptr),
	SynCppSyn1(nullptr),
	SynPasSyn1(nullptr),
	SynSQLSyn1(nullptr),
	dlgFileSave(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	OnCreate = DataModuleCreate;
	OnDestroy = DataModuleDestroy;
	AssignDataModuleHeight(this, 276);
	AssignDataModuleWidth(this, 420);
	PixelsPerInch = 96;
	dlgFileOpen = new TOpenDialog(this);
	dlgFileOpen->Options = (TOpenOptions() << ofHideReadOnly << ofPathMustExist << ofEnableSizing);
	// non-visible component: Left
	// non-visible component: Top
	actlMain = new TActionList(this);
	// non-visible component: Left
	// non-visible component: Top
	actFileSave = new TAction(actlMain);
	actFileSave->Category = L"File";
	actFileSave->Caption = L"&Save";
	actFileSave->Enabled = false;
	actFileSave->ShortCut = 16467;
	actFileSave->OnExecute = actFileSaveExecute;
	actFileSave->OnUpdate = actFileSaveUpdate;
	actFileSaveAs = new TAction(actlMain);
	actFileSaveAs->Category = L"File";
	actFileSaveAs->Caption = L"Save &As...";
	actFileSaveAs->Enabled = false;
	actFileSaveAs->OnExecute = actFileSaveAsExecute;
	actFileSaveAs->OnUpdate = actFileSaveAsUpdate;
	actFileClose = new TAction(actlMain);
	actFileClose->Category = L"File";
	actFileClose->Caption = L"&Close";
	actFileClose->Enabled = false;
	actFileClose->ShortCut = 16499;
	actFileClose->OnExecute = actFileCloseExecute;
	actFileClose->OnUpdate = actFileCloseUpdate;
	actFilePrint = new TAction(actlMain);
	actFilePrint->Category = L"File";
	actFilePrint->Caption = L"&Print...";
	actFilePrint->Enabled = false;
	actFilePrint->OnExecute = actFilePrintExecute;
	actFilePrint->OnUpdate = actFilePrintUpdate;
	actEditCut = new TAction(actlMain);
	actEditCut->Category = L"Edit";
	actEditCut->Caption = L"Cu&t";
	actEditCut->Enabled = false;
	actEditCut->ShortCut = 16472;
	actEditCut->OnExecute = actEditCutExecute;
	actEditCut->OnUpdate = actEditCutUpdate;
	actEditCopy = new TAction(actlMain);
	actEditCopy->Category = L"Edit";
	actEditCopy->Caption = L"&Copy";
	actEditCopy->Enabled = false;
	actEditCopy->ShortCut = 16451;
	actEditCopy->OnExecute = actEditCopyExecute;
	actEditCopy->OnUpdate = actEditCopyUpdate;
	actEditPaste = new TAction(actlMain);
	actEditPaste->Category = L"Edit";
	actEditPaste->Caption = L"&Paste";
	actEditPaste->Enabled = false;
	actEditPaste->ShortCut = 16470;
	actEditPaste->OnExecute = actEditPasteExecute;
	actEditPaste->OnUpdate = actEditPasteUpdate;
	actEditDelete = new TAction(actlMain);
	actEditDelete->Category = L"Edit";
	actEditDelete->Caption = L"De&lete";
	actEditDelete->Enabled = false;
	actEditDelete->OnExecute = actEditDeleteExecute;
	actEditDelete->OnUpdate = actEditDeleteUpdate;
	actEditUndo = new TAction(actlMain);
	actEditUndo->Category = L"Edit";
	actEditUndo->Caption = L"&Undo";
	actEditUndo->Enabled = false;
	actEditUndo->ShortCut = 16474;
	actEditUndo->OnExecute = actEditUndoExecute;
	actEditUndo->OnUpdate = actEditUndoUpdate;
	actEditRedo = new TAction(actlMain);
	actEditRedo->Category = L"Edit";
	actEditRedo->Caption = L"&Redo";
	actEditRedo->Enabled = false;
	actEditRedo->ShortCut = 24666;
	actEditRedo->OnExecute = actEditRedoExecute;
	actEditRedo->OnUpdate = actEditRedoUpdate;
	actEditSelectAll = new TAction(actlMain);
	actEditSelectAll->Category = L"Edit";
	actEditSelectAll->Caption = L"Select &All";
	actEditSelectAll->Enabled = false;
	actEditSelectAll->ShortCut = 16449;
	actEditSelectAll->OnExecute = actEditSelectAllExecute;
	actEditSelectAll->OnUpdate = actEditSelectAllUpdate;
	actSearchFind = new TAction(actlMain);
	actSearchFind->Category = L"Search";
	actSearchFind->Caption = L"&Find...";
	actSearchFind->Enabled = false;
	actSearchFind->ShortCut = 16454;
	actSearchFind->OnExecute = actSearchFindExecute;
	actSearchFind->OnUpdate = actSearchFindUpdate;
	actSearchFindNext = new TAction(actlMain);
	actSearchFindNext->Category = L"Search";
	actSearchFindNext->Caption = L"Find &Next";
	actSearchFindNext->Enabled = false;
	actSearchFindNext->ShortCut = 114;
	actSearchFindNext->OnExecute = actSearchFindNextExecute;
	actSearchFindNext->OnUpdate = actSearchFindNextUpdate;
	actSearchFindPrev = new TAction(actlMain);
	actSearchFindPrev->Category = L"Search";
	actSearchFindPrev->Caption = L"Find &Previous";
	actSearchFindPrev->Enabled = false;
	actSearchFindPrev->ShortCut = 8306;
	actSearchFindPrev->OnExecute = actSearchFindPrevExecute;
	actSearchFindPrev->OnUpdate = actSearchFindPrevUpdate;
	actSearchReplace = new TAction(actlMain);
	actSearchReplace->Category = L"Search";
	actSearchReplace->Caption = L"&Replace...";
	actSearchReplace->Enabled = false;
	actSearchReplace->ShortCut = 16456;
	actSearchReplace->OnExecute = actSearchReplaceExecute;
	actSearchReplace->OnUpdate = actSearchReplaceUpdate;
	SynCppSyn1 = new TSynCppSyn(this);
	SynCppSyn1->DefaultFilter = L"C++ files (*.cpp,*.h,*.hpp)|*.cpp;*.h;*.hpp";
	SynCppSyn1->Options->AutoDetectEnabled = false;
	SynCppSyn1->Options->AutoDetectLineLimit = 0;
	SynCppSyn1->Options->Visible = false;
	SynCppSyn1->CommentAttri->Foreground = clGreen;
	SynCppSyn1->DirecAttri->Foreground = clMaroon;
	SynCppSyn1->IdentifierAttri->Foreground = clNavy;
	SynCppSyn1->InvalidAttri->Foreground = clRed;
	SynCppSyn1->NumberAttri->Foreground = clBlue;
	SynCppSyn1->StringAttri->Foreground = clBlue;
	// non-visible component: Left
	// non-visible component: Top
	SynPasSyn1 = new TSynPasSyn(this);
	SynPasSyn1->Options->AutoDetectEnabled = false;
	SynPasSyn1->Options->AutoDetectLineLimit = 0;
	SynPasSyn1->Options->Visible = false;
	SynPasSyn1->CommentAttri->Foreground = clGreen;
	SynPasSyn1->IdentifierAttri->Foreground = clNavy;
	SynPasSyn1->NumberAttri->Foreground = clBlue;
	SynPasSyn1->StringAttri->Foreground = clBlue;
	// non-visible component: Left
	// non-visible component: Top
	SynSQLSyn1 = new TSynSQLSyn(this);
	SynSQLSyn1->DefaultFilter = L"SQL files (*.sql)|*.sql";
	SynSQLSyn1->Options->AutoDetectEnabled = false;
	SynSQLSyn1->Options->AutoDetectLineLimit = 0;
	SynSQLSyn1->Options->Visible = false;
	SynSQLSyn1->CommentAttri->Foreground = clGreen;
	SynSQLSyn1->IdentifierAttri->Foreground = clNavy;
	SynSQLSyn1->NumberAttri->Foreground = clBlue;
	SynSQLSyn1->StringAttri->Foreground = clBlue;
	SynSQLSyn1->SQLDialect = sqlSybase;
	// non-visible component: Left
	// non-visible component: Top
	dlgFileSave = new TSaveDialog(this);
	dlgFileSave->Options = (TOpenOptions() << ofHideReadOnly << ofPathMustExist << ofEnableSizing);
	// non-visible component: Left
	// non-visible component: Top
	ComponentState >> csLoading;
	//----- end of initializations from the dfm-file ----------------------------
}

