#include <vcl.h>
#pragma hdrstop

#include "FormMain_ctCode.h"

using namespace std;
using namespace d2c_system;
#define FormMain_ctCode__0 (TSynCompletionOptions() << TSynCompletionOption::scoCaseSensitive)
#define FormMain_ctCode__1 (TSynCompletionOptions() << TSynCompletionOption::scoUsePrettyText)
#define FormMain_ctCode__2 (TSynCompletionOptions() << TSynCompletionOption::scoUseInsertList)
#define FormMain_ctCode__3 (TSynCompletionOptions() << TSynCompletionOption::scoLimitToMatchedText)
#define FormMain_ctCode__4 (TSynCompletionOptions() << TSynCompletionOption::scoCaseSensitive)
#define FormMain_ctCode__5 (TSynCompletionOptions() << TSynCompletionOption::scoUsePrettyText)
#define FormMain_ctCode__6 (TSynCompletionOptions() << TSynCompletionOption::scoUseInsertList)
#define FormMain_ctCode__7 (TSynCompletionOptions() << TSynCompletionOption::scoLimitToMatchedText)

__fastcall TForm1::TForm1(TComponent* AOwner) : inherited(AOwner) {}


TForm1* Form1 = nullptr;
#pragma resource "*.DFM" 


void __fastcall TForm1::FormCreate(TObject* Sender)
{
	SynTest = new TSynEdit(this);
	SynTest->Parent = this;
	SynTest->Left = 416;
	SynTest->Top = 8;
	SynTest->Width = 321;
	SynTest->Height = 497;
	SynTest->Font->Charset = DEFAULT_CHARSET;
	SynTest->Font->Color = clWindowText;
	SynTest->Font->Height = -13;
	SynTest->Font->Name = "Courier New";
	//SynTest->Font->Style;
	SynTest->TabOrder = 9;
	SynTest->Gutter->Font->Charset = DEFAULT_CHARSET;
	SynTest->Gutter->Font->Color = clWindowText;
	SynTest->Gutter->Font->Height = -11;
	SynTest->Gutter->Font->Name = "Terminal";
	//SynTest->Gutter->Font->Style;
	SynTest->Gutter->Visible = False;
	SynTest->Lines->Add("This is a Demo to show you how the");
	SynTest->Lines->Add("Code Completion component works");
	SynTest->Lines->Add("when the default kind is ctCode.");
	SynTest->Lines->Add("");
	SynTest->Lines->Add("BiggestWord: If you are using");
	SynTest->Lines->Add("  PrettyText then this is the biggest");
	SynTest->Lines->Add("  word that will show up before the");
	SynTest->Lines->Add("  *bold* words");
	SynTest->Lines->Add("");
	SynTest->Lines->Add("CaseSensitive: makes the text you");
	SynTest->Lines->Add("  type and the matching in the");
	SynTest->Lines->Add("  dropdown list case sensitive");
	SynTest->Lines->Add("");
	SynTest->Lines->Add("AnsiStrings  : Use Ansi string");
	SynTest->Lines->Add("  comparisons instead of default");
	SynTest->Lines->Add("  string comparisons");
	SynTest->Lines->Add("");
	SynTest->Lines->Add("UsePrettyText: Allows you to format");
	SynTest->Lines->Add("  the text displayed in the dropdown.");
	SynTest->Lines->Add("  Please refer to the tsyncompletion-");
	SynTest->Lines->Add("  proposal.html file for a description");
	SynTest->Lines->Add("  of the available commands.");
	SynTest->Lines->Add("");
	SynTest->Lines->Add("UseInsertList: Lets you display one");
	SynTest->Lines->Add("  thing in the dropdown and insert");
	SynTest->Lines->Add("  another thing when they choose an");
	SynTest->Lines->Add("  item.  Like in Delphi, the");
	SynTest->Lines->Add("  dropdown might display");
	SynTest->Lines->Add("  \"procedure foo(AVariable: Integer)\"");
	SynTest->Lines->Add("  and only insert foo when you");
	SynTest->Lines->Add("  select it.  The InsertList must");
	SynTest->Lines->Add("  have as many items as the ItemList");
	SynTest->Lines->Add("  or you will get a list index out");
	SynTest->Lines->Add("  of bounds error when you select");
	SynTest->Lines->Add("  an item outside of the range.");
	SynTest->Lines->Add("");
	SynTest->Lines->Add("LimitToMatchedText: Limits the");
	SynTest->Lines->Add("  dropdown to the items matching the");
	SynTest->Lines->Add("  text you have typed, similar to the");
	SynTest->Lines->Add("  way the D6 does it.");
	RemovedKeystroke(SynTest, L"ecContextHelp", 112);
	RemovedKeystroke(SynTest, L"ecContextHelp", 16496);

	SynEdit1 = new TSynEdit(this);
	SynEdit1->Parent = this;
	SynEdit1->Left = 5;
	SynEdit1->Top = 160;
	SynEdit1->Width = 401;
	SynEdit1->Height = 344;
	SynEdit1->Font->Charset = DEFAULT_CHARSET;
	SynEdit1->Font->Color = clWindowText;
	SynEdit1->Font->Height = -13;
	SynEdit1->Font->Name = "Courier New";
	//SynEdit1->Font->Style;
	SynEdit1->TabOrder = 8;
	SynEdit1->Gutter->Font->Charset = DEFAULT_CHARSET;
	SynEdit1->Gutter->Font->Color = clWindowText;
	SynEdit1->Gutter->Font->Height = -11;
	SynEdit1->Gutter->Font->Name = "Terminal";
	//SynEdit1->Gutter->Font->Style;
	SynEdit1->Lines->Add("Use Ctrl+Space to activate Code Completion");
	SynEdit1->Lines->Add("with a shortcut, or use the \x27" L".\x27" L" key");
	SynEdit1->Lines->Add("to activate it with a timer");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("");
	RemovedKeystroke(SynEdit1, L"ecContextHelp", 112);
	RemovedKeystroke(SynEdit1, L"ecContextHelp", 16496);


	scpDemo = new TSynCompletionProposal(this);
	scpDemo->Options = TSynCompletionOptions() << scoLimitToMatchedText << scoUseInsertList << scoUsePrettyText << scoUseBuiltInTimer << scoEndCharCompletion << scoCompleteWithTab << scoCompleteWithEnter;
	scpDemo->Width = 262;
	scpDemo->EndOfTokenChr = "()[]. ";
	scpDemo->TriggerChars = ".";
	scpDemo->Title = "Completion Proposal Demo";
	scpDemo->Font->Charset = DEFAULT_CHARSET;
	scpDemo->Font->Color = clWindowText;
	scpDemo->Font->Height = -11;
	scpDemo->Font->Name = "MS Sans Serif";
	//scpDemo->Font->Style;
	scpDemo->TitleFont->Charset = DEFAULT_CHARSET;
	scpDemo->TitleFont->Color = clBtnText;
	scpDemo->TitleFont->Height = -11;
	scpDemo->TitleFont->Name = "MS Sans Serif";
	scpDemo->TitleFont->Style << fsBold;
	//scpDemo->Columns;
	scpDemo->ShortCut = 16416;
	scpDemo->Editor = SynEdit1;
	//scpDemo->Left = 216;

	/*# with mmoInsert.Lines do */
	{
		auto with0 = mmoInsert->Lines;
		with0->Clear();
		with0->Add(L"Create");
		with0->Add(L"Destroy");
		with0->Add(L"Add");
		with0->Add(L"ClearLine");
		with0->Add(L"Delete");
		with0->Add(L"First");
		with0->Add(L"GetMarksForLine");
		with0->Add(L"Insert");
		with0->Add(L"Last");
		with0->Add(L"Place");
		with0->Add(L"Remove");
		with0->Add(L"WMCaptureChanged");
		with0->Add(L"WMCopy");
		with0->Add(L"WMCut");
		with0->Add(L"WMDropFiles");
		with0->Add(L"WMEraseBkgnd");
		with0->Add(L"WMGetDlgCode");
		with0->Add(L"WMHScroll");
		with0->Add(L"WMPaste");
	}
	/*# with mmoItem.Lines do */
	{
		auto with1 = mmoItem->Lines;
		with1->Clear();
		with1->Add(L"constructor \\column{}\\style{+B}Create\\style{-B}(AOwner: TCustomSynEdit)");
		with1->Add(L"destructor \\column{}\\style{+B}Destroy\\style{-B}");
		with1->Add(L"function \\column{}\\style{+B}Add\\style{-B}(Item: TSynEditMark): Integer");
		with1->Add(L"procedure \\column{}\\style{+B}ClearLine\\style{-B}(line: integer)");
		with1->Add(L"procedure \\column{}\\style{+B}Delete\\style{-B}(Index: Integer)");
		with1->Add(L"function \\column{}\\style{+B}First\\style{-B}: TSynEditMark");
		with1->Add(L"procedure \\column{}\\style{+B}GetMarksForLine\\style{-B}(line: integer; var Marks: TSynEditMarks)");
		with1->Add(L"procedure \\column{}\\style{+B}Insert\\style{-B}(Index: Integer; Item: TSynEditMark)");
		with1->Add(L"function \\column{}\\style{+B}Last\\style{-B}: TSynEditMark");
		with1->Add(L"procedure \\column{}\\style{+B}Place\\style{-B}(mark: TSynEditMark)");
		with1->Add(L"function \\column{}\\style{+B}Remove\\style{-B}(Item: TSynEditMark): Integer");
		with1->Add(L"procedure \\column{}\\style{+B}WMCaptureChanged\\style{-B}(var Msg: TMessage); message WM_CAPTURECHANGED");
		with1->Add(L"procedure \\column{}\\style{+B}WMCopy\\style{-B}(var Message: TMessage); message WM_COPY");
		with1->Add(L"procedure \\column{}\\style{+B}WMCut\\style{-B}(var Message: TMessage); message WM_CUT");
		with1->Add(L"procedure \\column{}\\style{+B}WMDropFiles\\style{-B}(var Msg: TMessage); message WM_DROPFILES");
		with1->Add(L"procedure \\column{}\\style{+B}WMEraseBkgnd\\style{-B}(var Msg: TMessage); message WM_ERASEBKGND");
		with1->Add(L"procedure \\column{}\\style{+B}WMGetDlgCode\\style{-B}(var Msg: TWMGetDlgCode); message WM_GETDLGCODE");
		with1->Add(L"procedure \\column{}\\style{+B}WMHScroll\\style{-B}(var Msg: TWMScroll); message WM_HSCROLL");
		with1->Add(L"procedure \\column{}\\style{+B}WMPaste\\style{-B}(var Message: TMessage); message WM_PASTE");
	}
	scpDemo->InsertList->AddStrings(mmoInsert->Lines);
	scpDemo->ItemList->AddStrings(mmoItem->Lines);
}

void __fastcall TForm1::CheckBoxClick(TObject* Sender)
{
	if(ObjectIs(Sender, TCheckBox*))
	{
		if(((TCheckBox*) Sender)->Checked)
		{
			switch(((TCheckBox*) Sender)->Tag)
			{
				case cCaseSensitive:
				scpDemo->Options = scpDemo->Options + FormMain_ctCode__0;
				break;
				case cPrettyText:
				scpDemo->Options = scpDemo->Options + FormMain_ctCode__1;
				break;
				case cInsertList:
				scpDemo->Options = scpDemo->Options + FormMain_ctCode__2;
				break;
				case cMatchedText:
				scpDemo->Options = scpDemo->Options + FormMain_ctCode__3;
				break;
				default:
				  ;
				break;
			}
		}
		else
		{
			switch(((TCheckBox*) Sender)->Tag)
			{
				case cCaseSensitive:
				scpDemo->Options = scpDemo->Options - FormMain_ctCode__4;
				break;
				case cPrettyText:
				scpDemo->Options = scpDemo->Options - FormMain_ctCode__5;
				break;
				case cInsertList:
				scpDemo->Options = scpDemo->Options - FormMain_ctCode__6;
				break;
				case cMatchedText:
				scpDemo->Options = scpDemo->Options - FormMain_ctCode__7;
				break;
				default:
				  ;
				break;
			}
		}
	}
}

void __fastcall TForm1::edBiggestWordChange(TObject* Sender)
{

//TODO: set column width based on word length
//  scpDemo.Columns[0].BiggestWord := edBiggestWord.Text;
}

void __fastcall TForm1::Button1Click(TObject* Sender)
{
	scpDemo->InsertList->Clear();
	scpDemo->InsertList->AddStrings(mmoInsert->Lines);
}

void __fastcall TForm1::Button2Click(TObject* Sender)
{
	scpDemo->ItemList->Clear();
	scpDemo->ItemList->AddStrings(mmoItem->Lines);
	scpDemo->ResetAssignedList();
}

void __fastcall TForm1::edTitleChange(TObject* Sender)
{
	scpDemo->Title = edTitle->Text;
}

void __fastcall TForm1::Button3Click(TObject* Sender)
{
	FontDialog1->Font->Assign(scpDemo->Font);
	if(FontDialog1->Execute())
		scpDemo->Font->Assign(FontDialog1->Font);
}

void __fastcall TForm1::Button4Click(TObject* Sender)
{
	FontDialog1->Font->Assign(scpDemo->TitleFont);
	if(FontDialog1->Execute())
		scpDemo->TitleFont->Assign(FontDialog1->Font);
}

void __fastcall TForm1::FormShow(TObject* Sender)
{
	SynEdit1->SetFocus();
}

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	TComponent *Temp;
	for (int I = ComponentCount - 1; I >= 0; I--)
	{
		Temp = Components[I];
		if (dynamic_cast<TCustomSynEdit*>(Temp) != NULL) {
			RemoveComponent(Temp);
		}
	}
}
//---------------------------------------------------------------------------

