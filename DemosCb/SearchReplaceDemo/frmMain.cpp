#include <vcl.h>
#pragma hdrstop

#include "FrmMain.h"
#include "dlgSearchText.h"
#include "dlgReplaceText.h"
#include "dlgConfirmReplace.h"
#include "plgSearchHighlighter.h"
#include "SynEditTypes.h"
#include "SynEditMiscProcs.h"

using namespace std;
using namespace d2c_system;
#define FrmMain__0 (TSynSearchOptions() << TSynSearchOption::ssoPrompt << TSynSearchOption::ssoReplace << TSynSearchOption::ssoReplaceAll)
#define FrmMain__1 TSynSearchOptions()

__fastcall TSearchReplaceDemoForm::TSearchReplaceDemoForm(TComponent* AOwner) : inherited(AOwner) {}


TSearchReplaceDemoForm* SearchReplaceDemoForm = nullptr;
#pragma resource "*.DFM" 


  // options - to be saved to the registry
bool gbSearchBackwards = false;
bool gbSearchCaseSensitive = false;
bool gbSearchFromCaret = false;
bool gbSearchSelectionOnly = false;
bool gbSearchTextAtCaret = false;
bool gbSearchWholeWords = false;
bool gbSearchRegex = false;
String gsSearchText;
String gsSearchTextHistory;
String gsReplaceText;
String gsReplaceTextHistory;
const System::Char STextNotFound[] = L"Text not found";

/* TSearchReplaceDemoForm */

void __fastcall TSearchReplaceDemoForm::FormCreate(TObject* Sender)
{
	SynEditor = new TSynEdit(this);
	SynEditor->Parent = this;;
	SynEditor->Left = 0;
	SynEditor->Top = 26;
	SynEditor->Width = 554;
	SynEditor->Height = 300;
	SynEditor->Align = alClient;
	SynEditor->Font->Charset = DEFAULT_CHARSET;
	SynEditor->Font->Color = clWindowText;
	SynEditor->Font->Height-13;
	SynEditor->Font->Name = "Courier New";
	//SynEditor->Font->Style;
	SynEditor->TabOrder = 0;
	/* doesn't work in 110 any more
	SynEditor->Gutter->Font->Charset = DEFAULT_CHARSET;
	SynEditor->Gutter->Font->Color = clWindowText;
	SynEditor->Gutter->Font->Height-11;
	SynEditor->Gutter->Font->Name = "Terminal";
	//SynEditor->Gutter->Font->Style;
    */
	SynEditor->OnReplaceText = SynEditorReplaceText;
	RemovedKeystroke(SynEditor, L"ecDeleteLastChar", 8200);
	RemovedKeystroke(SynEditor, L"ecLineBreak", 8205);
	RemovedKeystroke(SynEditor, L"ecContextHelp", 112);
	//SynEditor->AddedKeystrokes;
	SynEditSearch = new TSynEditSearch(this);
	//SynEditSearch->Left = 188;
	//SynEditSearch->Top = 112;
	SynEditRegexSearch = new TSynEditRegexSearch(this);
	//SynEditRegexSearch->Left = 188;
	//SynEditRegexSearch->Top = 160;
	/*# with TSearchTextHightlighterSynEditPlugin.Create(SynEditor) do */
	{
		auto with0 = new TSearchTextHightlighterSynEditPlugin(SynEditor);
		with0->Attribute->Background = (TColor) 0x0078AAFF;
	}
}

void __fastcall TSearchReplaceDemoForm::DoSearchReplaceText(bool AReplace, bool ABackwards)
{
	TSynSearchOptions Options;
	StatusBar->SimpleText = L"";
	if(AReplace)
		Options = FrmMain__0;
	else
		Options = FrmMain__1;
	if(ABackwards)
		Options << TSynSearchOption::ssoBackwards;
	if(gbSearchCaseSensitive)
		Options << TSynSearchOption::ssoMatchCase;
	if(!fSearchFromCaret)
		Options << TSynSearchOption::ssoEntireScope;
	if(gbSearchSelectionOnly)
		Options << TSynSearchOption::ssoSelectedOnly;
	if(gbSearchWholeWords)
		Options << TSynSearchOption::ssoWholeWord;
	if(gbSearchRegex)
		SynEditor->SearchEngine = SynEditRegexSearch;
	else
		SynEditor->SearchEngine = SynEditSearch;
	if(SynEditor->SearchReplace(gsSearchText, gsReplaceText, Options) == 0)
	{
		MessageBeep((UINT) MB_ICONASTERISK);
		StatusBar->SimpleText = STextNotFound;
		if(Options.Contains(TSynSearchOption::ssoBackwards))
			SynEditor->BlockEnd = SynEditor->BlockBegin;
		else
			SynEditor->BlockBegin = SynEditor->BlockEnd;
		SynEditor->CaretXY = SynEditor->BlockBegin;
	}
	if(ConfirmReplaceDialog != nullptr)
		delete ConfirmReplaceDialog;
}

void __fastcall TSearchReplaceDemoForm::ShowSearchReplaceDialog(bool AReplace)
{
	TTextSearchDialog* Dlg = nullptr;
	StatusBar->SimpleText = L"";
	if(AReplace)
		Dlg = new TTextReplaceDialog(this);
	else
		Dlg = new TTextSearchDialog(this);
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
				gbSearchRegex = with0->SearchRegularExpression;
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

/* event handler */

void __fastcall TSearchReplaceDemoForm::ActionFileOpenExecute(TObject* Sender)
{
	if(OpenDialogFile->Execute())
	{
		SynEditor->Lines->LoadFromFile(OpenDialogFile->FileName);
		SynEditor->ReadOnly = OpenDialogFile->Options.Contains(TOpenOption::ofReadOnly);
	}
}

void __fastcall TSearchReplaceDemoForm::ActionSearchExecute(TObject* Sender)
{
	ShowSearchReplaceDialog(false);
}

void __fastcall TSearchReplaceDemoForm::ActionSearchNextExecute(TObject* Sender)
{
	DoSearchReplaceText(false, false);
}

void __fastcall TSearchReplaceDemoForm::ActionSearchPrevExecute(TObject* Sender)
{
	DoSearchReplaceText(false, true);
}

void __fastcall TSearchReplaceDemoForm::ActionSearchReplaceExecute(TObject* Sender)
{
	ShowSearchReplaceDialog(true);
}

void __fastcall TSearchReplaceDemoForm::actSearchUpdate(TObject* Sender)
{
	((TAction*) Sender)->Enabled = gsSearchText != L"";
}

void __fastcall TSearchReplaceDemoForm::ActionSearchReplaceUpdate(TObject* Sender)
{
	((TAction*) Sender)->Enabled = (gsSearchText != L"") && !SynEditor->ReadOnly;
}

void __fastcall TSearchReplaceDemoForm::SynEditorReplaceText(TObject* Sender, const UnicodeString ASearch, const UnicodeString AReplace, int Line, int Column, TSynReplaceAction& Action)
{
	TPoint APos = {};
	TRect EditRect = {};
	if(ASearch == AReplace)
		Action = TSynReplaceAction::raSkip;
	else
	{
		APos = SynEditor->ClientToScreen(SynEditor->RowColumnToPixels(SynEditor->BufferToDisplayPos(BufferCoord(Column, Line))));
		EditRect = ClientRect;
		TRect tmp = ClientToScreen(EditRect.TopLeft());
		EditRect.Top = tmp.Top;
		EditRect.Left = tmp.Left;
		tmp = ClientToScreen(EditRect.BottomRight());
		EditRect.Bottom = tmp.Bottom;
		EditRect.Right = tmp.Right;
		if(ConfirmReplaceDialog == nullptr)
			ConfirmReplaceDialog = new TConfirmReplaceDialog(Application);
		ConfirmReplaceDialog->PrepareShow(EditRect, APos.X, APos.Y, APos.Y + SynEditor->LineHeight, ASearch);
		switch(ConfirmReplaceDialog->ShowModal())
		{
			case mrYes:
			Action = TSynReplaceAction::raReplace;
			break;
			case mrYesToAll:
			Action = TSynReplaceAction::raReplaceAll;
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
