#include <vcl.h>
#pragma hdrstop

#include "frmMain.h"
#include <System.IniFiles.hpp>
#include "dmCommands.h"

using namespace std;
using namespace d2c_system;

__fastcall TMainForm::TMainForm(TComponent* AOwner) : inherited(AOwner) {}


#pragma resource "*.DFM"


/* TMainForm */

void __fastcall TMainForm::FormCreate(TObject* Sender)
{
	fMRUItems[1 - 1] = miFileMRU1;
	fMRUItems[2 - 1] = miFileMRU2;
	fMRUItems[3 - 1] = miFileMRU3;
	fMRUItems[4 - 1] = miFileMRU4;
	fMRUItems[5 - 1] = miFileMRU5;
	CommandsDataModule = new TCommandsDataModule(this);
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
	int Cnt = 0;
	Cnt = ParamCount();
	if(Cnt > 0)
	{
		__int64 stop = 0;
		if(!AMultipleFiles && (Cnt > 1))
			Cnt = 1;
		for(stop = Cnt, i = 1; i <= stop; i++)
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
	TIniFile* iniFile = nullptr;
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	int i = 0;
	String s;
	iniFile = new TIniFile(ChangeFileExt(Application->ExeName, L".ini"));
	try
	{
		int stop = 0;
		x = iniFile->ReadInteger(L"Main", L"Left", 0);
		y = iniFile->ReadInteger(L"Main", L"Top", 0);
		w = iniFile->ReadInteger(L"Main", L"Width", 0);
		h = iniFile->ReadInteger(L"Main", L"Height", 0);
		if((w > 0) && (h > 0))
			SetBounds(x, y, w, h);
		if(iniFile->ReadInteger(L"Main", L"Maximized", 0) != 0)
			WindowState = TWindowState::wsMaximized;
		StatusBar->Visible = iniFile->ReadInteger(L"Main", L"ShowStatusbar", 1) != 0;
    // MRU files
		for(stop = 1, i = 5; i >= stop; i--)
		{
			s = iniFile->ReadString(L"MRUFiles", Format(L"MRUFile%d", ARRAYOFCONST((i))), L"");
			if(s != L"")
				CommandsDataModule->AddMRUEntry(s);
		}
	}
	__finally
	{
		delete iniFile;
	}
}

void __fastcall TMainForm::WriteIniSettings()
{
	TIniFile* iniFile = nullptr;
	TWindowPlacement wp = {};
	int i = 0;
	String s;
	iniFile = new TIniFile(ChangeFileExt(Application->ExeName, L".ini"));
	try
	{
		int stop = 0;
		wp.length = sizeof(TWindowPlacement);
		GetWindowPlacement(Handle, &wp);
    // form properties
		/*# with wp.rcNormalPosition do */
		{
			auto& with0 = wp.rcNormalPosition;
			iniFile->WriteInteger(L"Main", L"Left", with0.left);
			iniFile->WriteInteger(L"Main", L"Top", with0.top);
			iniFile->WriteInteger(L"Main", L"Width", with0.right - with0.left);
			iniFile->WriteInteger(L"Main", L"Height", with0.bottom - with0.top);
		}
		iniFile->WriteInteger(L"Main", L"Maximized", int(WindowState == TWindowState::wsMaximized));
		iniFile->WriteInteger(L"Main", L"ShowStatusbar", int(StatusBar->Visible));
    // MRU files
		for(stop = 5, i = 1; i <= stop; i++)
		{
			s = CommandsDataModule->GetMRUEntry(i - 1);
			if(s != L"")
				iniFile->WriteString(L"MRUFiles", Format(L"MRUFile%d", ARRAYOFCONST((i))), s);
			else
				iniFile->DeleteKey(L"MRUFiles", Format(L"MRUFile%d", ARRAYOFCONST((i))));
		}
	}
	__finally
	{
		delete iniFile;
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
