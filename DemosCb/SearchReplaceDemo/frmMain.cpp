#include <vcl.h>
#pragma hdrstop

#include "frmMain.h"
#include "dlgSearchText.h"
#include "dlgReplaceText.h"
#include "dlgConfirmReplace.h"
#include "plgSearchHighlighter.h"
#include "SynEditTypes.h"
#include "SynEditMiscProcs.h"

using namespace std;
using namespace d2c_system;
#define Frmmain__0 (TSynSearchOptions() << ssoPrompt << ssoReplace << ssoReplaceAll)
#define Frmmain__1 TSynSearchOptions()

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
	/*# with TSearchTextHightlighterSynEditPlugin.Create(SynEditor) do */
	{
		auto with0 = new TSearchTextHightlighterSynEditPlugin(SynEditor);
		with0->Attribute->Background = (TColor) 0x0078AAFF;
	}
}

void __fastcall TSearchReplaceDemoForm::DoSearchReplaceText(bool AReplace, bool ABackwards)
{
	TSynSearchOptions Options;
	Statusbar->SimpleText = L"";
	if(AReplace)
		Options = Frmmain__0;
	else
		Options = Frmmain__1;
	if(ABackwards)
		Options << ssoBackwards;
	if(gbSearchCaseSensitive)
		Options << ssoMatchCase;
	if(!FSearchFromCaret)
		Options << ssoEntireScope;
	if(gbSearchSelectionOnly)
		Options << ssoSelectedOnly;
	if(gbSearchWholeWords)
		Options << ssoWholeWord;
	if(gbSearchRegex)
		SynEditor->SearchEngine = SynEditRegexSearch;
	else
		SynEditor->SearchEngine = SynEditSearch;
	if(SynEditor->SearchReplace(gsSearchText, gsReplaceText, Options) == 0)
	{
		MessageBeep((UINT) MB_ICONASTERISK);
		Statusbar->SimpleText = STextNotFound;
		if(Options.Contains(ssoBackwards))
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
	TTextSearchDialog* dlg = nullptr;
	Statusbar->SimpleText = L"";
	if(AReplace)
		dlg = new TTextReplaceDialog(this);
	else
		dlg = new TTextSearchDialog(this);
	/*# with dlg do */
	{
		auto with0 = dlg;
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
				/*# with dlg as TTextReplaceDialog do */
				{
					auto with1 = (TTextReplaceDialog*) dlg;
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
					/*# with dlg as TTextReplaceDialog do */
					{
						auto with2 = (TTextReplaceDialog*) dlg;
						gsReplaceText = with2->ReplaceText;
						gsReplaceTextHistory = with2->ReplaceTextHistory;
					}
				FSearchFromCaret = gbSearchFromCaret;
				if(gsSearchText != L"")
				{
					DoSearchReplaceText(AReplace, gbSearchBackwards);
					FSearchFromCaret = true;
				}
			}
		}
		__finally
		{
			delete dlg;
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
		Action = raSkip;
	else
	{
		APos = SynEditor->ClientToScreen(SynEditor->RowColumnToPixels(SynEditor->BufferToDisplayPos(BufferCoord(Column, Line))));
		EditRect = ClientRect;
		EditRect.TopLeft() = ClientToScreen(EditRect.TopLeft());
		EditRect.BottomRight() = ClientToScreen(EditRect.BottomRight());
		if(ConfirmReplaceDialog == nullptr)
			ConfirmReplaceDialog = new TConfirmReplaceDialog(Application);
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
			Action = raSkip;
			break;
			default:
			Action = raCancel;
			break;
		}
	}
}
