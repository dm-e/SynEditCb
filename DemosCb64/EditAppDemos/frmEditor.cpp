
#include <vcl.h>
#pragma hdrstop

#include "frmEditor.h"
#include <Vcl.ComCtrls.hpp>
#include "dmCommands.h"
#include "dlgSearchText.h"
#include "dlgReplaceText.h"
#include "dlgConfirmReplace.h"
#include "d2c_convert.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;
#define Frmeditor__0 (TSynStatusChanges() << scAll << scSelection)
#define Frmeditor__1 TSynStatusChanges()
#define Frmeditor__2 (TSynStatusChanges() << scAll << scSelection)
#define Frmeditor__3 TSynStatusChanges()
#define Frmeditor__4 (TSynStatusChanges() << scAll << scModified)
#define Frmeditor__5 TSynStatusChanges()
#define Frmeditor__6 (TSynSearchOptions() << ssoPrompt << ssoReplace << ssoReplaceAll)
#define Frmeditor__7 TSynSearchOptions()

__fastcall TEditor::TEditor() {}


const int WM_DELETETHIS = WM_USER + 42;
bool gbSearchBackwards = false;
bool gbSearchCaseSensitive = false;
bool gbSearchFromCaret = false;
bool gbSearchSelectionOnly = false;
bool gbSearchTextAtCaret = false;
bool gbSearchWholeWords = false;
String gsSearchText;
String gsSearchTextHistory;
String gsReplaceText;
String gsReplaceTextHistory;
const System::Char SInsert[] = L"Insert";
const System::Char SOverwrite[] = L"Overwrite";
const System::Char SReadOnly[] = L"Read Only";
const System::Char SNonameFileTitle[] = L"Untitled";
const System::Char SEditorCaption[] = L"Editor";
const System::Char SAskSaveChanges[] = L"The text in the \"%s\" file has changed.\x0d\x0a\x0d\x0a" L"Do you want to save the modifications?";
/* TEditor */

__fastcall TEditor::TEditor(TEditorForm* AForm)
 : FForm(nullptr),
			fHasSelection(false),
			FIsEmpty(false),
			fIsReadOnly(false),
			FModified(false),
			fUntitledNumber(0)
{
	Assert(AForm != nullptr);
	//# inherited::Create();
	FForm = AForm;
	fUntitledNumber = -1;
}

void __fastcall TEditor::Activate()
{
	if(FForm != nullptr)
		FForm->DoActivate();
}

bool __fastcall TEditor::AskSaveChanges()
{
	bool result = false;
	if(FForm != nullptr)
		result = FForm->DoAskSaveChanges();
	else
		result = true;
	return result;
}

bool __fastcall TEditor::CanClose()
{
	bool result = false;
	result = FForm != nullptr;
	return result;
}

void __fastcall TEditor::Close()
{
	if((FFileName != L"") && (CommandsDataModule != nullptr))
		CommandsDataModule->AddMRUEntry(FFileName);
	if(fUntitledNumber != -1)
		CommandsDataModule->ReleaseUntitledNumber(fUntitledNumber);
	if(FForm != nullptr)
		FForm->Close();
}

void __fastcall TEditor::DoSetFileName(String AFileName)
{
	if(AFileName != FFileName)
	{
		FFileName = AFileName;
		if(fUntitledNumber != -1)
		{
			CommandsDataModule->ReleaseUntitledNumber(fUntitledNumber);
			fUntitledNumber = -1;
		}
	}
}

TPoint __fastcall TEditor::GetCaretPos()
{
	TPoint result = {};
	if(FForm != nullptr)
    //result = FForm->SynEditor->CaretXY;
    d2c_memcpy(&result, FForm->SynEditor->CaretXY, sizeof(result));
	else
		result = Point(-1, -1);
	return result;
}

String __fastcall TEditor::GetEditorState()
{
	String result;
	if(FForm != nullptr)
	{
		if(FForm->SynEditor->ReadOnly)
			result = SReadOnly;
		else
		{
			if(FForm->SynEditor->InsertMode)
				result = SInsert;
			else
				result = SOverwrite;
		}
	}
	else
	result = L"";
	return result;
}

String __fastcall TEditor::GetFileName()
{
	String result;
	result = FFileName;
	return result;
}

String __fastcall TEditor::GetFileTitle()
{
	String result;
	if(FFileName != L"")
		result = ExtractFileName(FFileName);
	else
	{
		if(fUntitledNumber == -1)
			fUntitledNumber = CommandsDataModule->GetUntitledNumber();
		result = String(SNonameFileTitle) + IntToStr(fUntitledNumber);
	}
	return result;
}

bool __fastcall TEditor::GetModified()
{
	bool result = false;
	if(FForm != nullptr)
		result = FForm->SynEditor->Modified;
	else
		result = false;
	return result;
}

void __fastcall TEditor::OpenFile(String AFileName)
{
	FFileName = AFileName;
	if(FForm != nullptr)
	{
		if((AFileName != L"") && FileExists(AFileName))
			FForm->SynEditor->Lines->LoadFromFile(AFileName);
		else
			FForm->SynEditor->Lines->Clear();
		FForm->DoUpdateCaption();
		FForm->DoUpdateHighlighter();
	}
}
// IEditCommands implementation

bool __fastcall TEditor::CanCopy()
{
	bool result = false;
	result = (FForm != nullptr) && fHasSelection;
	return result;
}

bool __fastcall TEditor::CanCut()
{
	bool result = false;
	result = (FForm != nullptr) && fHasSelection && !fIsReadOnly;
	return result;
}

bool __fastcall TEditor::CanPaste()
{
	bool result = false;
	result = (FForm != nullptr) && FForm->SynEditor->CanPaste;
	return result;
}

bool __fastcall TEditor::CanRedo()
{
	bool result = false;
	result = (FForm != nullptr) && FForm->SynEditor->CanRedo;
	return result;
}

bool __fastcall TEditor::CanSelectAll()
{
	bool result = false;
	result = FForm != nullptr;
	return result;
}

bool __fastcall TEditor::CanUndo()
{
	bool result = false;
	result = (FForm != nullptr) && FForm->SynEditor->CanUndo;
	return result;
}

void __fastcall TEditor::ExecCopy()
{
	if(FForm != nullptr)
		FForm->SynEditor->CopyToClipboard();
}

void __fastcall TEditor::ExecCut()
{
	if(FForm != nullptr)
		FForm->SynEditor->CutToClipboard();
}

void __fastcall TEditor::ExecDelete()
{
	if(FForm != nullptr)
		FForm->SynEditor->SelText = L"";
}

void __fastcall TEditor::ExecPaste()
{
	if(FForm != nullptr)
		FForm->SynEditor->PasteFromClipboard();
}

void __fastcall TEditor::ExecRedo()
{
	if(FForm != nullptr)
		FForm->SynEditor->Redo();
}

void __fastcall TEditor::ExecSelectAll()
{
	if(FForm != nullptr)
		FForm->SynEditor->SelectAll();
}

void __fastcall TEditor::ExecUndo()
{
	if(FForm != nullptr)
		FForm->SynEditor->Undo();
}
// IFileCommands implementation

bool __fastcall TEditor::CanPrint()
{
	bool result = false;
	result = false;
	return result;
}

bool __fastcall TEditor::CanSave()
{
	bool result = false;
	result = (FForm != nullptr) && (FModified || (FFileName == L""));
	return result;
}

bool __fastcall TEditor::CanSaveAs()
{
	bool result = false;
	result = FForm != nullptr;
	return result;
}

void __fastcall TEditor::ExecPrint()
{
	if(FForm != nullptr)
// TODO
		;
}

void __fastcall TEditor::ExecSave()
{
	if(FForm != nullptr)
	{
		if(FFileName != L"")
			FForm->DoSave();
		else
			FForm->DoSaveAs();
	}
}

void __fastcall TEditor::ExecSaveAs()
{
	if(FForm != nullptr)
		FForm->DoSaveAs();
}
// ISearchCommands implementation

bool __fastcall TEditor::CanFind()
{
	bool result = false;
	result = (FForm != nullptr) && !FIsEmpty;
	return result;
}

bool __fastcall TEditor::CanFindNext()
{
	bool result = false;
	result = (FForm != nullptr) && !FIsEmpty && (gsSearchText != L"");
	return result;
}

bool __fastcall TEditor::CanReplace()
{
	bool result = false;
	result = (FForm != nullptr) && !fIsReadOnly && !FIsEmpty;
	return result;
}

void __fastcall TEditor::ExecFind()
{
	if(FForm != nullptr)
		FForm->ShowSearchReplaceDialog(false);
}

void __fastcall TEditor::ExecFindNext()
{
	if(FForm != nullptr)
		FForm->DoSearchReplaceText(false, false);
}

void __fastcall TEditor::ExecFindPrev()
{
	if(FForm != nullptr)
		FForm->DoSearchReplaceText(false, true);
}

void __fastcall TEditor::ExecReplace()
{
	if(FForm != nullptr)
		FForm->ShowSearchReplaceDialog(true);
}
/* TEditorTabSheet */

class TEditorTabSheet : public TTabSheet
{
private:
	MESSAGE void __fastcall WMDeleteThis(::TMessage& Msg)/*# WM_DELETETHIS */;
protected:
	BEGIN_MESSAGE_MAP
	  VCL_MESSAGE_HANDLER(WM_DELETETHIS, TMessage, WMDeleteThis)
	END_MESSAGE_MAP(TTabSheet)
public:
	typedef TTabSheet inherited;
	#include "frmEditor_friends.inc"
	__fastcall TEditorTabSheet(TComponent* AOwner) : inherited(AOwner) {}
	__fastcall TEditorTabSheet(HWND ParentWindow) : inherited(ParentWindow) {}
};

void __fastcall TEditorTabSheet::WMDeleteThis(::TMessage& Msg)
{
	Free();
}
/* TEditorFactory */

class TEditorFactory : public TCppInterfacedObject<IEditorFactory>
{
	#include "frmEditor_friends.inc"
public:
	typedef TCppInterfacedObject<IEditorFactory> inherited;
private:
    // IEditorFactory implementation
	bool __fastcall CanCloseAll();
	void __fastcall CloseAll();
	IEditor* __fastcall CreateBorderless(TForm* AOwner);
	IEditor* __fastcall CreateMDIChild(TForm* AOwner);
	IEditor* __fastcall CreateTabSheet(TPageControl* AOwner);
	int __fastcall GetEditorCount();
	IEditor* __fastcall GetEditor(int Index);
	void __fastcall RemoveEditor(IEditor* AEditor);
  //TInterfaceList* fEditors;
  typedef std::vector<IEditor*> editorlist;
  typedef editorlist::iterator teditorlist;
  editorlist fEditors;  
	__fastcall TEditorFactory();
	virtual __fastcall ~TEditorFactory();
};

__fastcall TEditorFactory::TEditorFactory()
// : fEditors(new TInterfaceList())
{
	//# inherited::Create();
}

__fastcall TEditorFactory::~TEditorFactory()
{
//  delete fEditors;
	//# inherited::Destroy();
}

bool __fastcall TEditorFactory::CanCloseAll()
{
	bool result = false;
	int i = 0;
	IEditor* LEditor = nullptr;
	i = fEditors.size() - 1;
	while(i >= 0)
	{
//		LEditor = ((IEditor*) fEditors->Items[i]);
//		fEditors->Items[i]->QueryInterface<IEditor>(&LEditor);   // ?
    	LEditor = fEditors[i];
		if(!LEditor->AskSaveChanges())
		{
			result = false;
			return result;
		}
		--i;
	}
	result = true;
	return result;
}

void __fastcall TEditorFactory::CloseAll()
{
	int i = 0;
	i = fEditors.size() - 1;
	while(i >= 0)
	{
//    ((IEditor*) fEditors->Items[i])->Close();
    	fEditors[i]->Close();
		--i;
	}
}

IEditor* __fastcall TEditorFactory::CreateBorderless(TForm* AOwner)
{
	IEditor* result = nullptr;
	TEditorForm* LForm = nullptr;
	LForm = new TEditorForm(AOwner, 0);
	/*# with LForm do */
	{
		TEditorForm* with0 = LForm;
		with0->FEditor = new TEditor(LForm);
		result = with0->FEditor;
		with0->FKind = ekBorderless;
		with0->BorderStyle = bsNone;
		with0->Parent = AOwner;
		with0->Align = alClient;
		with0->Visible = true;
	}
	if(result != nullptr)
 //	fEditors->Add(result);
	fEditors.push_back(result);
	return result;
}

IEditor* __fastcall TEditorFactory::CreateMDIChild(TForm* AOwner)
{
	IEditor* result = nullptr;
	TEditorForm* LForm = nullptr;
	LForm = new TEditorForm(AOwner, 0);
	/*# with LForm do */
	{
		auto with0 = LForm;
		with0->FEditor = new TEditor(LForm);
		result = with0->FEditor;
		with0->FKind = ekMDIChild;
		with0->FormStyle = fsMDIChild;
	}
	if(result != nullptr)
//    fEditors->Add(result);
	fEditors.push_back(result);
	return result;
}

IEditor* __fastcall TEditorFactory::CreateTabSheet(TPageControl* AOwner)
{
	IEditor* result = nullptr;
	TTabSheet* Sheet = nullptr;
	TEditorForm* LForm = nullptr;
	Sheet = new TEditorTabSheet(AOwner);
	try
	{
		Sheet->PageControl = AOwner;
		LForm = new TEditorForm(Sheet, 0);
		/*# with LForm do */
		{
			auto with0 = LForm;
			with0->FEditor = new TEditor(LForm);
			result = with0->FEditor;
			with0->FKind = ekInTabsheet;
			with0->BorderStyle = bsNone;
			with0->Parent = Sheet;
			with0->Align = alClient;
			with0->Visible = true;
			AOwner->ActivePage = Sheet;
			LForm->SetFocus();
		}
    // fix for Delphi 4 (???)
		LForm->Realign();
		if(result != nullptr)
//      fEditors->Add(result);
      fEditors.push_back(result);
	}
	catch(...)
	{
		delete Sheet;
	}
	return result;
}

int __fastcall TEditorFactory::GetEditorCount()
{
	int result = 0;
	result = fEditors.size();
	return result;
}

IEditor* __fastcall TEditorFactory::GetEditor(int Index)
{
	IEditor* result = nullptr;
	//result = ((IEditor*) fEditors->Items[Index]);
	result = (IEditor*) fEditors[Index];
	return result;
}

void __fastcall TEditorFactory::RemoveEditor(IEditor* AEditor)
{
	int i = 0;
	/*
	i = fEditors->IndexOf(AEditor);
	if(i > -1)
		fEditors->Delete(i);
  */
	teditorlist it = find (fEditors.begin(), fEditors.end(), AEditor);
	if (it != fEditors.end())
		fEditors.erase(it);
}
/* TEditorForm */

void __fastcall TEditorForm::FormActivate(TObject* Sender)
{
	DoAssignInterfacePointer(true);
}

void __fastcall TEditorForm::FormDeactivate(TObject* Sender)
{
	DoAssignInterfacePointer(false);
}

void __fastcall TEditorForm::FormShow(TObject* Sender)
{
	DoUpdateCaption();
}

void __fastcall TEditorForm::FormClose(TObject* Sender, TCloseAction& Action)
{
	if(FKind == ekInTabsheet)
	{
		PostMessage(Parent->Handle, (UINT) WM_DELETETHIS, 0, 0);
		Action = TCloseAction::caNone;
	}
	else
	Action = TCloseAction::caFree;
}

void __fastcall TEditorForm::FormCloseQuery(TObject* Sender, bool& CanClose)
{

  // need to prevent this from happening more than once (e.g. with MDI childs)
	if(!(ComponentState.Contains(csDestroying)))
		CanClose = DoAskSaveChanges();
}

void __fastcall TEditorForm::FormDestroy(TObject* Sender)
{
	IEditor* LEditor = nullptr;
	LEditor = FEditor;
	Assert(FEditor != nullptr);
	FEditor->FForm = nullptr;
	Assert(GI_EditorFactory != nullptr);
	GI_EditorFactory->RemoveEditor(LEditor);
}

void __fastcall TEditorForm::SynEditorChange(TObject* Sender)
{
	bool Empty = false;
	int i = 0;
	int stop = 0;
	Assert(FEditor != nullptr);
	Empty = true;
	for(stop = 0, i = SynEditor->Lines->Count - 1; i >= stop; i--)
	{
		if(SynEditor->Lines->Strings[i] != L"")
		{
			Empty = false;
			break;
		}
	}
	FEditor->FIsEmpty = Empty;
}

void __fastcall TEditorForm::SynEditorEnter(TObject* Sender)
{
	DoAssignInterfacePointer(true);
}

void __fastcall TEditorForm::SynEditorExit(TObject* Sender)
{
	DoAssignInterfacePointer(false);
}

void __fastcall TEditorForm::SynEditorReplaceText(TObject* Sender, const String ASearch, const String AReplace, int Line, int Column, TSynReplaceAction& Action)
{
	TPoint APos = {};
	TRect EditRect = {};
	if(ASearch == AReplace)
		Action = TSynReplaceAction::raSkip;
	else
	{
		APos = SynEditor->ClientToScreen(SynEditor->RowColumnToPixels(SynEditor->BufferToDisplayPos(BufferCoord(Column, Line))));
		EditRect = ClientRect;
		EditRect.TopLeft() = ClientToScreen(EditRect.TopLeft());
		EditRect.BottomRight() = ClientToScreen(EditRect.BottomRight());
		if(ConfirmReplaceDialog == nullptr)
			ConfirmReplaceDialog = new TConfirmReplaceDialog(Application, 0);
		ConfirmReplaceDialog->PrepareShow(EditRect, APos.X, APos.Y, APos.Y + SynEditor->LineHeight, ASearch);
		switch(ConfirmReplaceDialog->ShowModal())
		{
			case mrYes:
			Action = raReplace;
			break;
			case mrYesToAll:
			Action = raReplaceAll;
			break;
			case mrNo:
			Action = TSynReplaceAction::raSkip;
			break;
			default:
			Action = TSynReplaceAction::raCancel;
			break;
		}
	}
}

void __fastcall TEditorForm::SynEditorStatusChange(TObject* Sender, TSynStatusChanges Changes)
{
	Assert(FEditor != nullptr);
	if(Changes * Frmeditor__0 != Frmeditor__1)
		FEditor->fHasSelection = SynEditor->SelAvail;
	if(Changes * Frmeditor__2 != Frmeditor__3)
		FEditor->fIsReadOnly = SynEditor->ReadOnly;
	if(Changes * Frmeditor__4 != Frmeditor__5)
		FEditor->FModified = SynEditor->Modified;
}

void __fastcall TEditorForm::DoActivate()
{
	TTabSheet* Sheet = nullptr;
	TPageControl* PCtrl = nullptr;
	if(FormStyle == fsMDIChild)
		BringToFront();
	else
	{
		if(ObjectIs(Parent, TTabSheet*))
		{
			Sheet = ((TTabSheet*) Parent);
			PCtrl = Sheet->PageControl;
			if(PCtrl != nullptr)
				PCtrl->ActivePage = Sheet;
		}
	}
}

bool __fastcall TEditorForm::DoAskSaveChanges()
{
	bool result = false;
	const int MBType = MB_YESNOCANCEL | MB_ICONQUESTION;
	String s;
  // this is necessary to prevent second confirmation when closing MDI childs
	if(SynEditor->Modified)
	{
		DoActivate();
		MessageBeep((UINT) MB_ICONQUESTION);
		Assert(FEditor != nullptr);
		s = Format(SAskSaveChanges, ARRAYOFCONST((ExtractFileName(FEditor->GetFileTitle()))));
		switch(Application->MessageBox(ustr2pwchar(s), ustr2pwchar(Application->Title), MBType))
		{
			case IDYES:
			result = DoSave();
			break;
			case IDNO:
			result = true;
			break;
			default:
			result = false;
			break;
		}
	}
	else
	result = true;
	return result;
}

void __fastcall TEditorForm::DoAssignInterfacePointer(bool AActive)
{
	if(AActive)
	{
		GI_ActiveEditor = FEditor;
		GI_EditCmds = FEditor;
		GI_FileCmds = FEditor;
		GI_SearchCmds = FEditor;
	}
	else
	{
		if(GI_ActiveEditor == ((IEditor*) FEditor))
			GI_ActiveEditor = nullptr;
		if(GI_EditCmds == ((IEditCommands*) FEditor))
			GI_EditCmds = nullptr;
		if(GI_FileCmds == ((IFileCommands*) FEditor))
			GI_FileCmds = nullptr;
		if(GI_SearchCmds == ((ISearchCommands*) FEditor))
			GI_SearchCmds = nullptr;
	}
}

bool __fastcall TEditorForm::DoSave()
{
	bool result = false;
	Assert(FEditor != nullptr);
	if(FEditor->FFileName != L"")
		result = DoSaveFile();
	else
		result = DoSaveAs();
	return result;
}

bool __fastcall TEditorForm::DoSaveFile()
{
	bool result = false;
	Assert(FEditor != nullptr);
	try
	{
		SynEditor->Lines->SaveToFile(FEditor->FFileName);
		SynEditor->Modified = false;
		result = true;
	}
	catch(...)
	{
		Application->HandleException(this);
		result = false;
	}
	return result;
}

bool __fastcall TEditorForm::DoSaveAs()
{
	bool result = false;
	String NewName;
	Assert(FEditor != nullptr);
	NewName = FEditor->FFileName;
	if(CommandsDataModule->GetSaveFileName(NewName, SynEditor->Highlighter))
	{
		FEditor->DoSetFileName(NewName);
		DoUpdateCaption();
		DoUpdateHighlighter();
		result = DoSaveFile();
	}
	else
	result = false;
	return result;
}

void __fastcall TEditorForm::DoSearchReplaceText(bool AReplace, bool ABackwards)
{
	TSynSearchOptions Options;
	if(AReplace)
		Options = Frmeditor__6;
	else
		Options = Frmeditor__7;
	if(ABackwards)
		Options << ssoBackwards;
	if(gbSearchCaseSensitive)
		Options << ssoMatchCase;
	if(!fSearchFromCaret)
		Options << ssoEntireScope;
	if(gbSearchSelectionOnly)
		Options << ssoSelectedOnly;
	if(gbSearchWholeWords)
		Options << ssoWholeWord;
	if(SynEditor->SearchReplace(gsSearchText, gsReplaceText, Options) == 0)
	{
		MessageBeep((UINT) MB_ICONASTERISK);
		if(Options.Contains(ssoBackwards))
			SynEditor->BlockEnd = SynEditor->BlockBegin;
		else
			SynEditor->BlockBegin = SynEditor->BlockEnd;
		SynEditor->CaretXY = SynEditor->BlockBegin;
	}
	if(ConfirmReplaceDialog != nullptr)
		delete ConfirmReplaceDialog;
}

void __fastcall TEditorForm::DoUpdateCaption()
{
	Assert(FEditor != nullptr);
	switch(FKind)
	{
		case ekInTabsheet:
		((TTabSheet*) Parent)->Caption = FEditor->GetFileTitle();
		break;
		case ekMDIChild:
		Caption = FEditor->GetFileTitle() + L" - " + SEditorCaption;
		break;
		default:
		  ;
		break;
	}
}

void __fastcall TEditorForm::DoUpdateHighlighter()
{
	Assert(FEditor != nullptr);
	if(FEditor->FFileName != L"")
	{
		SynEditor->Highlighter = CommandsDataModule->GetHighlighterForFile(FEditor->FFileName);
	}
	else
	SynEditor->Highlighter = nullptr;
}

void __fastcall TEditorForm::ShowSearchReplaceDialog(bool AReplace)
{
	TTextSearchDialog* Dlg = nullptr;
	if(AReplace)
		Dlg = new TTextReplaceDialog(this, 0);
	else
		Dlg = new TTextSearchDialog(this, 0);
	/*# with Dlg do */
	{
		auto with0 = Dlg;
		try

    // assign search options
		{
			with0->SearchBackwards = gbSearchBackwards;
			with0->SearchCaseSensitive = gbSearchCaseSensitive;
			with0->SearchFromCursor = gbSearchFromCaret;
			with0->SearchInSelectionOnly = gbSearchSelectionOnly;
    // start with last search text
			with0->SearchText = gsSearchText;
			if(gbSearchTextAtCaret)
      // if something is selected search for that text
			{
				if(SynEditor->SelAvail && (SynEditor->BlockBegin.Line == SynEditor->BlockEnd.Line))
					with0->SearchText = SynEditor->SelText;
				else
					with0->SearchText = SynEditor->GetWordAtRowCol(SynEditor->CaretXY);
			}
			with0->SearchTextHistory = gsSearchTextHistory;
			if(AReplace)
				/*# with Dlg as TTextReplaceDialog do */
				{
					auto with1 = (TTextReplaceDialog*) Dlg;
					with1->ReplaceText = gsReplaceText;
					with1->ReplaceTextHistory = gsReplaceTextHistory;
				}
			with0->SearchWholeWords = gbSearchWholeWords;
			if(with0->ShowModal() == mrOk)
			{
				gbSearchBackwards = with0->SearchBackwards;
				gbSearchCaseSensitive = with0->SearchCaseSensitive;
				gbSearchFromCaret = with0->SearchFromCursor;
				gbSearchSelectionOnly = with0->SearchInSelectionOnly;
				gbSearchWholeWords = with0->SearchWholeWords;
				gsSearchText = with0->SearchText;
				gsSearchTextHistory = with0->SearchTextHistory;
				if(AReplace)
					/*# with Dlg as TTextReplaceDialog do */
					{
						auto with2 = (TTextReplaceDialog*) Dlg;
						gsReplaceText = with2->ReplaceText;
						gsReplaceTextHistory = with2->ReplaceTextHistory;
					}
				fSearchFromCaret = gbSearchFromCaret;
				if(gsSearchText != L"")
				{
					DoSearchReplaceText(AReplace, gbSearchBackwards);
					fSearchFromCaret = true;
				}
			}
		}
		__finally
		{
			delete Dlg;
		}
	}
}

__fastcall TEditorForm::TEditorForm(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	SynEditor(nullptr),
	pmnuEditor(nullptr),
	lmiEditCut(nullptr),
	lmiEditCopy(nullptr),
	lmiEditPaste(nullptr),
	lmiEditDelete(nullptr),
	N1(nullptr),
	lmiEditSelectAll(nullptr),
	lmiEditUndo(nullptr),
	lmiEditRedo(nullptr),
	N2(nullptr),
	SynEditSearch1(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Left = 338;
	Top = 199;
	Caption = L"Editor";
	ClientHeight = 287;
	ClientWidth = 454;
	Color = clBtnFace;
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = clWindowText;
	Font->Height = -11;
	Font->Name = L"MS Sans Serif";
	Font->Style = (TFontStyles());
	OnActivate = FormActivate;
	OnClose = FormClose;
	OnCloseQuery = FormCloseQuery;
	OnDestroy = FormDestroy;
	OnDeactivate = FormDeactivate;
	OnShow = FormShow;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	SynEditor = new TSynEdit(this);
	SynEditor->Parent = this;
	SynEditor->Left = 0;
	SynEditor->Top = 0;
	SynEditor->Width = 454;
	SynEditor->Height = 287;
	SynEditor->Align = alClient;
	SynEditor->Font->Charset = DEFAULT_CHARSET;
	SynEditor->Font->Color = clWindowText;
	SynEditor->Font->Height = -13;
	SynEditor->Font->Name = L"Courier New";
	SynEditor->Font->Style = (TFontStyles());
	SynEditor->Font->Quality = TFontQuality::fqClearTypeNatural;
	SynEditor->TabOrder = 0;
	SynEditor->OnEnter = SynEditorEnter;
	SynEditor->OnExit = SynEditorExit;
	SynEditor->UseCodeFolding = false;
	SynEditor->Gutter->Font->Charset = DEFAULT_CHARSET;
	SynEditor->Gutter->Font->Color = clWindowText;
	SynEditor->Gutter->Font->Height = -11;
	SynEditor->Gutter->Font->Name = L"Courier New";
	SynEditor->Gutter->Font->Style = (TFontStyles());
//	SynEditor->Gutter->Add();
//TSynBandsCollection* b = SynEditor->Gutter->Bands;
//TSynGutterBand* gb = b->Bands[0];
//	b->  [0]->Kind = gbkMarks;
	SynEditor->Gutter->Bands->Bands[0]->Kind = gbkMarks;
	SynEditor->Gutter->Bands->Bands[0]->Visible = true;
	SynEditor->Gutter->Bands->Bands[0]->Width = 15;
//	SynEditor->Gutter->Add();
	SynEditor->Gutter->Bands->Bands[1]->Kind = gbkLineNumbers;
//	SynEditor->Gutter->Add();
	SynEditor->Gutter->Bands->Bands[2]->Kind = gbkFold;
//	SynEditor->Gutter->Add();
	SynEditor->Gutter->Bands->Bands[3]->Kind = gbkMargin;
	SynEditor->Gutter->Bands->Bands[3]->Visible = true;
	SynEditor->Gutter->Bands->Bands[3]->Width = 2;
	SynEditor->OnChange = SynEditorChange;
	SynEditor->OnReplaceText = SynEditorReplaceText;
	SynEditor->OnStatusChange = SynEditorStatusChange;
//	GetTSynEditRemovedKeystrokes(SynEditor, 0)->Command = ecLineBreak;
//	GetTSynEditRemovedKeystrokes(SynEditor, 0)->ShortCut = (TShortCut) 8205;
//	GetTSynEditRemovedKeystrokes(SynEditor, 1)->Command = ecContextHelp;
//	GetTSynEditRemovedKeystrokes(SynEditor, 1)->ShortCut = (TShortCut) 112;
	// SynEditor->AddedKeystrokes =
	pmnuEditor = new TPopupMenu(this);
	// non-visible component: Left
	// non-visible component: Top
	lmiEditUndo = new TMenuItem(pmnuEditor);
	lmiEditRedo = new TMenuItem(pmnuEditor);
	N2 = new TMenuItem(pmnuEditor);
	N2->Caption = L"-";
	lmiEditCut = new TMenuItem(pmnuEditor);
	lmiEditCopy = new TMenuItem(pmnuEditor);
	lmiEditPaste = new TMenuItem(pmnuEditor);
	lmiEditDelete = new TMenuItem(pmnuEditor);
	N1 = new TMenuItem(pmnuEditor);
	N1->Caption = L"-";
	lmiEditSelectAll = new TMenuItem(pmnuEditor);
	SynEditSearch1 = new TSynEditSearch(this);
	// non-visible component: Left
	// non-visible component: Top
	ComponentState >> csLoading;
	//----- shifted initializations from the dfm-file ---------------------------
	ActiveControl = SynEditor;
	SynEditor->PopupMenu = pmnuEditor;
	SynEditor->SearchEngine = SynEditSearch1;
	lmiEditUndo->Action = CommandsDataModule->actEditUndo;
	lmiEditRedo->Action = CommandsDataModule->actEditRedo;
	lmiEditCut->Action = CommandsDataModule->actEditCut;
	lmiEditCopy->Action = CommandsDataModule->actEditCopy;
	lmiEditPaste->Action = CommandsDataModule->actEditPaste;
	lmiEditDelete->Action = CommandsDataModule->actEditDelete;
	lmiEditSelectAll->Action = CommandsDataModule->actEditSelectAll;
	//----- end of initializations from the dfm-file ----------------------------
}

static bool frmEditor_Initialized = false;

void frmEditor_initialization()
{
	if(frmEditor_Initialized)
		return;
	
	frmEditor_Initialized = true;
	
	GI_EditorFactory = new TEditorFactory();
}
static bool frmEditor_Finalized = false;

void frmEditor_finalization()
{
	if(frmEditor_Finalized)
		return;
	
	frmEditor_Finalized = true;
	
	GI_EditorFactory = nullptr;
}
class frmEditor_unit
{
public:
	frmEditor_unit()
	{
		frmEditor_initialization();
	}
	~frmEditor_unit()
	{
		frmEditor_finalization();
	}
};

frmEditor_unit _frmEditor_unit;
