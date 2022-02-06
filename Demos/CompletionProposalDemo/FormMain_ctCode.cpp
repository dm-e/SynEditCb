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
