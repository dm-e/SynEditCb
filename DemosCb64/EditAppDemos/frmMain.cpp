#include <vcl.h>
#pragma hdrstop

#include "FrmMain.h"
#include <System.IniFiles.hpp>
#include "dmCommands.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;



/* TMainForm */

void __fastcall TMainForm::FormCreate(TObject* Sender)
{
	fMRUItems[1 - 1] = miFileMRU1;
	fMRUItems[2 - 1] = miFileMRU2;
	fMRUItems[3 - 1] = miFileMRU3;
	fMRUItems[4 - 1] = miFileMRU4;
	fMRUItems[5 - 1] = miFileMRU5;
// to constructor  CommandsDataModule = new TCommandsDataModule(this);
	ReadIniSettings();
}

void __fastcall TMainForm::FormDestroy(TObject* Sender)
{
	if(GI_EditorFactory != nullptr)
		GI_EditorFactory->CloseAll();
	WriteIniSettings();
	delete CommandsDataModule;
}

// implementation

bool __fastcall TMainForm::CanCloseAll()
{
	bool result = false;
	result = true;
	return result;
}

bool __fastcall TMainForm::CmdLineOpenFiles(bool AMultipleFiles)
{
	bool result = false;
	__int64 i = 0;
	int cnt = 0;
	cnt = ParamCount();
	if(cnt > 0)
	{
		__int64 stop = 0;
		if(!AMultipleFiles && (cnt > 1))
			cnt = 1;
		for(stop = cnt, i = 1; i <= stop; i++)
		{
			DoOpenFile(ParamStr((int) i));
		}
		result = true;
	}
	else
	result = false;
	return result;
}

IEditor* __fastcall TMainForm::DoCreateEditor(String AFileName)
{
	IEditor* result = nullptr;
	result = nullptr;
	return result;
}

void __fastcall TMainForm::DoOpenFile(String AFileName)
{
	int i = 0;
	IEditor* LEditor = nullptr;
	AFileName = ExpandFileName(AFileName);
	if(AFileName != L"")
	{
		int stop = 0;
		CommandsDataModule->RemoveMRUEntry(AFileName);
    // activate the editor if already open
		Assert(GI_EditorFactory != nullptr);
		for(stop = 0, i = GI_EditorFactory->GetEditorCount() - 1; i >= stop; i--)
		{
			LEditor = GI_EditorFactory->Editor[i];
			if(CompareText(LEditor->GetFileName(), AFileName) == 0)
			{
				LEditor->Activate();
				return;
			}
		}
	}
  // create a new editor, add it to the editor list, open the file
	LEditor = DoCreateEditor(AFileName);
	if(LEditor != nullptr)
		LEditor->OpenFile(AFileName);
}

void __fastcall TMainForm::ReadIniSettings()
{
	TIniFile* IniFile = nullptr;
	int X = 0;
	int Y = 0;
	int W = 0;
	int h = 0;
	int i = 0;
	String s;
	IniFile = new TIniFile(ChangeFileExt(Application->ExeName, L".ini"));
	try
	{
		int stop = 0;
		X = IniFile->ReadInteger(L"Main", L"Left", 0);
		Y = IniFile->ReadInteger(L"Main", L"Top", 0);
		W = IniFile->ReadInteger(L"Main", L"Width", 0);
		h = IniFile->ReadInteger(L"Main", L"Height", 0);
		if((W > 0) && (h > 0))
			SetBounds(X, Y, W, h);
		if(IniFile->ReadInteger(L"Main", L"Maximized", 0) != 0)
			WindowState = TWindowState::wsMaximized;
		StatusBar->Visible = IniFile->ReadInteger(L"Main", L"ShowStatusbar", 1) != 0;
    // MRU files
		for(stop = 1, i = 5; i >= stop; i--)
		{
			s = IniFile->ReadString(L"MRUFiles", Format(L"MRUFile%d", ARRAYOFCONST((i))), L"");
			if(s != L"")
				CommandsDataModule->AddMRUEntry(s);
		}
	}
	__finally
	{
		delete IniFile;
	}
}

void __fastcall TMainForm::WriteIniSettings()
{
	TIniFile* IniFile = nullptr;
	TWindowPlacement wp = {};
	int i = 0;
	String s;
	IniFile = new TIniFile(ChangeFileExt(Application->ExeName, L".ini"));
	try
	{
		int stop = 0;
	wp.length = (UINT) sizeof(TWindowPlacement);
		GetWindowPlacement(Handle, &wp);
    // form properties
		/*# with wp.rcNormalPosition do */
		{
		  RECT& with0 = wp.rcNormalPosition;
		  IniFile->WriteInteger(L"Main", L"Left", with0.left);
		  IniFile->WriteInteger(L"Main", L"Top", with0.top);
		  IniFile->WriteInteger(L"Main", L"Width", with0.right - with0.left);
		  IniFile->WriteInteger(L"Main", L"Height", with0.bottom - with0.top);
		}
		IniFile->WriteInteger(L"Main", L"Maximized", int(WindowState == TWindowState::wsMaximized));
		IniFile->WriteInteger(L"Main", L"ShowStatusbar", int(StatusBar->Visible));
    // MRU files
		for(stop = 5, i = 1; i <= stop; i++)
		{
			s = CommandsDataModule->GetMRUEntry(i - 1);
			if(s != L"")
				IniFile->WriteString(L"MRUFiles", Format(L"MRUFile%d", ARRAYOFCONST((i))), s);
			else
				IniFile->DeleteKey(L"MRUFiles", Format(L"MRUFile%d", ARRAYOFCONST((i))));
		}
	}
	__finally
	{
		delete IniFile;
	}
}

// action handler methods

void __fastcall TMainForm::actFileNewOrOpenUpdate(TObject* Sender)
{
	((TAction*) Sender)->Enabled = GI_EditorFactory != nullptr;
}

void __fastcall TMainForm::actFileNewExecute(TObject* Sender)
{
	DoOpenFile(L"");
}

void __fastcall TMainForm::actFileOpenExecute(TObject* Sender)
{
	/*# with CommandsDataModule.dlgFileOpen do */
	{
		auto with0 = CommandsDataModule->dlgFileOpen;
		if(with0->Execute())
			DoOpenFile(with0->FileName);
	}
}

void __fastcall TMainForm::actFileCloseAllExecute(TObject* Sender)
{
	int i = 0;
	if(GI_EditorFactory != nullptr)
	{
		if(!CanCloseAll())
			return;
		i = GI_EditorFactory->GetEditorCount() - 1;
    // close all editor childs
		while(i >= 0)
		{
			GI_EditorFactory->GetEditor(i)->Close();
			--i;
		}
	}
}

void __fastcall TMainForm::actFileCloseAllUpdate(TObject* Sender)
{
	actFileCloseAll->Enabled = (GI_EditorFactory != nullptr) && (GI_EditorFactory->GetEditorCount() > 0);
}

void __fastcall TMainForm::actFileExitExecute(TObject* Sender)
{
	Close();
}

void __fastcall TMainForm::mRecentFilesClick(TObject* Sender)
{
	int i = 0;
	String s;
	int stop = 0;
	for(stop = 5 /*# High(fMRUItems) */, i = 1 /*# Low(fMRUItems) */; i <= stop; i++)
	{
		if(fMRUItems[i - 1] != nullptr)
		{
			s = CommandsDataModule->GetMRUEntry(i - 1 /*# Low(fMRUItems) */);
			fMRUItems[i - 1]->Visible = s != L"";
			fMRUItems[i - 1]->Caption = s;
		}
	}
}

void __fastcall TMainForm::mFileClick(TObject* Sender)
{
	mRecentFiles->Enabled = CommandsDataModule->GetMRUEntries() > 0;
}

void __fastcall TMainForm::actViewStatusbarUpdate(TObject* Sender)
{
	actViewStatusbar->Checked = StatusBar->Visible;
}

void __fastcall TMainForm::actViewStatusbarExecute(TObject* Sender)
{
	StatusBar->Visible = !StatusBar->Visible;
}

void __fastcall TMainForm::OnOpenMRUFile(TObject* Sender)
{
	int i = 0;
	String s;
	int stop = 0;
	for(stop = 5 /*# High(fMRUItems) */, i = 1 /*# Low(fMRUItems) */; i <= stop; i++)
	{
		if(Sender == fMRUItems[i - 1])
		{
			s = CommandsDataModule->GetMRUEntry(i - 1);
			if(s != L"")
				DoOpenFile(s);
		}
	}
}

void __fastcall TMainForm::actUpdateStatusBarPanelsUpdate(TObject* Sender)
{
	const System::Char SModified[] = 	L"Modified";
	TPoint ptCaret = {};
	actUpdateStatusBarPanels->Enabled = true;
	if(GI_ActiveEditor != nullptr)
	{
		ptCaret = GI_ActiveEditor->GetCaretPos();
		if((ptCaret.X > 0) && (ptCaret.Y > 0))
			StatusBar->Panels->Items[0]->Text = Format(L" %6d:%3d ", ARRAYOFCONST(((int)ptCaret.Y, (int)ptCaret.X)));
		else
			StatusBar->Panels->Items[0]->Text = L"";
		if(GI_ActiveEditor->GetModified())
			StatusBar->Panels->Items[1]->Text = SModified;
		else
			StatusBar->Panels->Items[1]->Text = L"";
		StatusBar->Panels->Items[2]->Text = GI_ActiveEditor->GetEditorState();
	}
	else
	{
		StatusBar->Panels->Items[0]->Text = L"";
		StatusBar->Panels->Items[1]->Text = L"";
		StatusBar->Panels->Items[2]->Text = L"";
	}
}

__fastcall TMainForm::TMainForm(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	mnuMain(nullptr),
	mFile(nullptr),
	miFileExit(nullptr),
	miFileNew(nullptr),
	N1(nullptr),
	mEdit(nullptr),
	miFileOpen(nullptr),
	miFileSave(nullptr),
	miFileSaveAs(nullptr),
	miFileClose(nullptr),
	miEditUndo(nullptr),
	miEditRedo(nullptr),
	N2(nullptr),
	miEditCut(nullptr),
	miEditCopy(nullptr),
	miEditPaste(nullptr),
	miEditDelete(nullptr),
	miEditSelectAll(nullptr),
	N3(nullptr),
	miEditFind(nullptr),
	miEditFindNext(nullptr),
	miEditFindPrev(nullptr),
	miEditReplace(nullptr),
	StatusBar(nullptr),
	miViewStatusbar(nullptr),
	mView(nullptr),
	N4(nullptr),
	mRecentFiles(nullptr),
	miFileMRU5(nullptr),
	miFileMRU4(nullptr),
	miFileMRU3(nullptr),
	miFileMRU2(nullptr),
	miFileMRU1(nullptr),
	N5(nullptr),
	miFilePrint(nullptr),
	actlStandard(nullptr),
	actFileNew(nullptr),
	actFileOpen(nullptr),
	actFileExit(nullptr),
	actViewStatusbar(nullptr),
	actUpdateStatusBarPanels(nullptr),
	actFileCloseAll(nullptr),
	miFileCloseAll(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Left = 186;
	Top = 133;
	ClientHeight = 307;
	ClientWidth = 498;
	Color = clBtnFace;
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = clWindowText;
	Font->Height = -11;
	Font->Name = L"MS Sans Serif";
	Font->Style = (TFontStyles());
	OnCreate = FormCreate;
	OnDestroy = FormDestroy;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	StatusBar = new TStatusBar(this);
	StatusBar->Parent = this;
	StatusBar->Left = 0;
	StatusBar->Top = 288;
	StatusBar->Width = 498;
	StatusBar->Height = 19;
	StatusBar->Panels->Add();
	StatusBar->Panels->Items[0]->Alignment = taCenter;
	StatusBar->Panels->Items[0]->Width = 84;
	StatusBar->Panels->Add();
	StatusBar->Panels->Items[1]->Alignment = taCenter;
	StatusBar->Panels->Items[1]->Width = 72;
	StatusBar->Panels->Add();
	StatusBar->Panels->Items[2]->Alignment = taCenter;
	StatusBar->Panels->Items[2]->Width = 84;
	StatusBar->Panels->Add();
	StatusBar->Panels->Items[3]->Width = 50;
	// EXPLICITTOP
	// EXPLICITWIDTH
	mnuMain = new TMainMenu(this);
	// non-visible component: Left
	// non-visible component: Top
	mFile = CreateTMainMenuTMenuItem(mnuMain);
	mFile->Caption = L"&File";
	mFile->OnClick = mFileClick;
	miFileNew = CreateTMenuItemTMenuItem(mFile);
	miFileOpen = CreateTMenuItemTMenuItem(mFile);
	mRecentFiles = CreateTMenuItemTMenuItem(mFile);
	mRecentFiles->Caption = L"&Recent Files";
	mRecentFiles->OnClick = mRecentFilesClick;
	miFileMRU1 = CreateTMenuItemTMenuItem(mRecentFiles);
	miFileMRU1->Caption = L"[MRU1]";
	miFileMRU1->OnClick = OnOpenMRUFile;
	miFileMRU2 = CreateTMenuItemTMenuItem(mRecentFiles);
	miFileMRU2->Caption = L"[MRU2]";
	miFileMRU2->OnClick = OnOpenMRUFile;
	miFileMRU3 = CreateTMenuItemTMenuItem(mRecentFiles);
	miFileMRU3->Caption = L"[MRU3]";
	miFileMRU3->OnClick = OnOpenMRUFile;
	miFileMRU4 = CreateTMenuItemTMenuItem(mRecentFiles);
	miFileMRU4->Caption = L"[MRU4]";
	miFileMRU4->OnClick = OnOpenMRUFile;
	miFileMRU5 = CreateTMenuItemTMenuItem(mRecentFiles);
	miFileMRU5->Caption = L"[MRU5]";
	miFileMRU5->OnClick = OnOpenMRUFile;
	N4 = CreateTMenuItemTMenuItem(mFile);
	N4->Caption = L"-";
	miFileSave = CreateTMenuItemTMenuItem(mFile);
	miFileSaveAs = CreateTMenuItemTMenuItem(mFile);
	miFileClose = CreateTMenuItemTMenuItem(mFile);
	miFileCloseAll = CreateTMenuItemTMenuItem(mFile);
	N5 = CreateTMenuItemTMenuItem(mFile);
	N5->Caption = L"-";
	miFilePrint = CreateTMenuItemTMenuItem(mFile);
	N1 = CreateTMenuItemTMenuItem(mFile);
	N1->Caption = L"-";
	miFileExit = CreateTMenuItemTMenuItem(mFile);
	mEdit = CreateTMainMenuTMenuItem(mnuMain);
	mEdit->Caption = L"&Edit";
	miEditUndo = CreateTMenuItemTMenuItem(mEdit);
	miEditRedo = CreateTMenuItemTMenuItem(mEdit);
	N2 = CreateTMenuItemTMenuItem(mEdit);
	N2->Caption = L"-";
	miEditCut = CreateTMenuItemTMenuItem(mEdit);
	miEditCopy = CreateTMenuItemTMenuItem(mEdit);
	miEditPaste = CreateTMenuItemTMenuItem(mEdit);
	miEditDelete = CreateTMenuItemTMenuItem(mEdit);
	miEditSelectAll = CreateTMenuItemTMenuItem(mEdit);
	N3 = CreateTMenuItemTMenuItem(mEdit);
	N3->Caption = L"-";
	miEditFind = CreateTMenuItemTMenuItem(mEdit);
	miEditFindNext = CreateTMenuItemTMenuItem(mEdit);
	miEditFindPrev = CreateTMenuItemTMenuItem(mEdit);
	miEditReplace = CreateTMenuItemTMenuItem(mEdit);
	mView = CreateTMainMenuTMenuItem(mnuMain);
	mView->Caption = L"&View";
	miViewStatusbar = CreateTMenuItemTMenuItem(mView);
	actlStandard = new TActionList(this);
	// non-visible component: Left
	// non-visible component: Top
	actFileNew = new TAction(actlStandard);
	actFileNew->Category = L"File";
	actFileNew->Caption = L"&New";
	actFileNew->ShortCut = 16462;
	actFileNew->OnExecute = actFileNewExecute;
	actFileNew->OnUpdate = actFileNewOrOpenUpdate;
	actFileOpen = new TAction(actlStandard);
	actFileOpen->Category = L"File";
	actFileOpen->Caption = L"&Open...";
	actFileOpen->ShortCut = 16463;
	actFileOpen->OnExecute = actFileOpenExecute;
	actFileOpen->OnUpdate = actFileNewOrOpenUpdate;
	actFileCloseAll = new TAction(actlStandard);
	actFileCloseAll->Category = L"File";
	actFileCloseAll->Caption = L"Close All Fi&les";
	actFileCloseAll->Enabled = false;
	actFileCloseAll->ShortCut = 24691;
	actFileCloseAll->OnExecute = actFileCloseAllExecute;
	actFileCloseAll->OnUpdate = actFileCloseAllUpdate;
	actFileExit = new TAction(actlStandard);
	actFileExit->Category = L"File";
	actFileExit->Caption = L"E&xit";
	actFileExit->ShortCut = 32883;
	actFileExit->OnExecute = actFileExitExecute;
	actViewStatusbar = new TAction(actlStandard);
	actViewStatusbar->Category = L"View";
	actViewStatusbar->Caption = L"&Status Bar";
	actViewStatusbar->OnExecute = actViewStatusbarExecute;
	actViewStatusbar->OnUpdate = actViewStatusbarUpdate;
	actUpdateStatusBarPanels = new TAction(actlStandard);
	actUpdateStatusBarPanels->Caption = L"actUpdateStatusBarPanels";
	actUpdateStatusBarPanels->OnUpdate = actUpdateStatusBarPanelsUpdate;
	ComponentState >> csLoading;
	//----- shifted initializations from the dfm-file ---------------------------
	Menu = mnuMain;
	StatusBar->Action = actUpdateStatusBarPanels;
	miFileNew->Action = actFileNew;
	miFileOpen->Action = actFileOpen;
	CommandsDataModule = new TCommandsDataModule(this, 0);
	miFileSave->Action = CommandsDataModule->actFileSave;
	miFileSaveAs->Action = CommandsDataModule->actFileSaveAs;
	miFileClose->Action = CommandsDataModule->actFileClose;
	miFileCloseAll->Action = actFileCloseAll;
	miFilePrint->Action = CommandsDataModule->actFilePrint;
	miFileExit->Action = actFileExit;
	miEditUndo->Action = CommandsDataModule->actEditUndo;
	miEditRedo->Action = CommandsDataModule->actEditRedo;
	miEditCut->Action = CommandsDataModule->actEditCut;
	miEditCopy->Action = CommandsDataModule->actEditCopy;
	miEditPaste->Action = CommandsDataModule->actEditPaste;
	miEditDelete->Action = CommandsDataModule->actEditDelete;
	miEditSelectAll->Action = CommandsDataModule->actEditSelectAll;
	miEditFind->Action = CommandsDataModule->actSearchFind;
	miEditFindNext->Action = CommandsDataModule->actSearchFindNext;
	miEditFindPrev->Action = CommandsDataModule->actSearchFindPrev;
	miEditReplace->Action = CommandsDataModule->actSearchReplace;
	miViewStatusbar->Action = actViewStatusbar;
	//----- end of initializations from the dfm-file ----------------------------
}

