#include <vcl.h>
#pragma hdrstop

#include "FormMain_ctCode.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;
#define Formmain_ctcode__0 (TSynCompletionOptions() << scoCaseSensitive)
#define Formmain_ctcode__1 (TSynCompletionOptions() << scoUsePrettyText)
#define Formmain_ctcode__2 (TSynCompletionOptions() << scoUseInsertList)
#define Formmain_ctcode__3 (TSynCompletionOptions() << scoLimitToMatchedText)
#define Formmain_ctcode__4 (TSynCompletionOptions() << scoCaseSensitive)
#define Formmain_ctcode__5 (TSynCompletionOptions() << scoUsePrettyText)
#define Formmain_ctcode__6 (TSynCompletionOptions() << scoUseInsertList)
#define Formmain_ctcode__7 (TSynCompletionOptions() << scoLimitToMatchedText)


TForm1* Form1 = nullptr;

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
				scpDemo->Options = scpDemo->Options + Formmain_ctcode__0;
				break;
				case cPrettyText:
				scpDemo->Options = scpDemo->Options + Formmain_ctcode__1;
				break;
				case cInsertList:
				scpDemo->Options = scpDemo->Options + Formmain_ctcode__2;
				break;
				case cMatchedText:
				scpDemo->Options = scpDemo->Options + Formmain_ctcode__3;
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
				scpDemo->Options = scpDemo->Options - Formmain_ctcode__4;
				break;
				case cPrettyText:
				scpDemo->Options = scpDemo->Options - Formmain_ctcode__5;
				break;
				case cInsertList:
				scpDemo->Options = scpDemo->Options - Formmain_ctcode__6;
				break;
				case cMatchedText:
				scpDemo->Options = scpDemo->Options - Formmain_ctcode__7;
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

__fastcall TForm1::TForm1(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	scpDemo(nullptr),
	PageControl1(nullptr),
	CodeCompletion(nullptr),
	TabSheet2(nullptr),
	mmoInsert(nullptr),
	mmoItem(nullptr),
	Label1(nullptr),
	Label2(nullptr),
	Button1(nullptr),
	Button2(nullptr),
	SynTest(nullptr),
	edBiggestWord(nullptr),
	Label3(nullptr),
	cbCase(nullptr),
	cbPrettyText(nullptr),
	cbUseInsertList(nullptr),
	cbLimitToMatchedText(nullptr),
	SynEdit1(nullptr),
	edTitle(nullptr),
	Label4(nullptr),
	Button3(nullptr),
	Button4(nullptr),
	FontDialog1(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Left = 212;
	Top = 100;
	Width = 776;
	Height = 586;
	Caption = L"SynEdit Code Completion Demo for ctCode";
	Color = clBtnFace;
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = clWindowText;
	Font->Height = -11;
	Font->Name = L"MS Sans Serif";
	Font->Style = (TFontStyles());
	AssignFormOldCreateOrder(this, false);
	OnCreate = FormCreate;
	OnShow = FormShow;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	PageControl1 = new TPageControl(this);
	PageControl1->Parent = this;
	PageControl1->Left = 8;
	PageControl1->Top = 8;
	PageControl1->Width = 753;
	PageControl1->Height = 537;
	PageControl1->TabOrder = 0;
	CodeCompletion = new TTabSheet(PageControl1);
	CodeCompletion->Parent = PageControl1;
	CodeCompletion->PageControl = PageControl1;
	CodeCompletion->Caption = L"CodeCompletion";
	Label3 = new TLabel(CodeCompletion);
	Label3->Parent = CodeCompletion;
	Label3->Left = 8;
	Label3->Top = 19;
	Label3->Width = 64;
	Label3->Height = 13;
	Label3->Caption = L"BiggestWord:";
	Label4 = new TLabel(CodeCompletion);
	Label4->Parent = CodeCompletion;
	Label4->Left = 224;
	Label4->Top = 19;
	Label4->Width = 23;
	Label4->Height = 13;
	Label4->Caption = L"Title:";
	SynTest = new TSynEdit(CodeCompletion);
	SynTest->Parent = CodeCompletion;
	SynTest->Left = 416;
	SynTest->Top = 8;
	SynTest->Width = 321;
	SynTest->Height = 497;
	SynTest->Font->Charset = DEFAULT_CHARSET;
	SynTest->Font->Color = clWindowText;
	SynTest->Font->Height = -13;
	SynTest->Font->Name = L"Courier New";
	SynTest->Font->Style = (TFontStyles());
	SynTest->TabOrder = 9;
	SynTest->Gutter->Font->Charset = DEFAULT_CHARSET;
	SynTest->Gutter->Font->Color = clWindowText;
	SynTest->Gutter->Font->Height = -11;
	SynTest->Gutter->Font->Name = L"Terminal";
	SynTest->Gutter->Font->Style = (TFontStyles());
	SynTest->Gutter->Visible = false;
	SynTest->Lines->Add(L"This is a Demo to show you how the");
	SynTest->Lines->Add(L"Code Completion component works");
	SynTest->Lines->Add(L"when the default kind is ctCode.");
	SynTest->Lines->Add(L"");
	SynTest->Lines->Add(L"BiggestWord: If you are using");
	SynTest->Lines->Add(L"  PrettyText then this is the biggest");
	SynTest->Lines->Add(L"  word that will show up before the");
	SynTest->Lines->Add(L"  *bold* words");
	SynTest->Lines->Add(L"");
	SynTest->Lines->Add(L"CaseSensitive: makes the text you");
	SynTest->Lines->Add(L"  type and the matching in the");
	SynTest->Lines->Add(L"  dropdown list case sensitive");
	SynTest->Lines->Add(L"");
	SynTest->Lines->Add(L"AnsiStrings  : Use Ansi string");
	SynTest->Lines->Add(L"  comparisons instead of default");
	SynTest->Lines->Add(L"  string comparisons");
	SynTest->Lines->Add(L"");
	SynTest->Lines->Add(L"UsePrettyText: Allows you to format");
	SynTest->Lines->Add(L"  the text displayed in the dropdown.");
	SynTest->Lines->Add(L"  Please refer to the tsyncompletion-");
	SynTest->Lines->Add(L"  proposal.html file for a description");
	SynTest->Lines->Add(L"  of the available commands.");
	SynTest->Lines->Add(L"");
	SynTest->Lines->Add(L"UseInsertList: Lets you display one");
	SynTest->Lines->Add(L"  thing in the dropdown and insert");
	SynTest->Lines->Add(L"  another thing when they choose an");
	SynTest->Lines->Add(L"  item.  Like in Delphi, the");
	SynTest->Lines->Add(L"  dropdown might display");
	SynTest->Lines->Add(L"  \"procedure foo(AVariable: Integer)\"");
	SynTest->Lines->Add(L"  and only insert foo when you");
	SynTest->Lines->Add(L"  select it.  The InsertList must");
	SynTest->Lines->Add(L"  have as many items as the ItemList");
	SynTest->Lines->Add(L"  or you will get a list index out");
	SynTest->Lines->Add(L"  of bounds error when you select");
	SynTest->Lines->Add(L"  an item outside of the range.");
	SynTest->Lines->Add(L"");
	SynTest->Lines->Add(L"LimitToMatchedText: Limits the");
	SynTest->Lines->Add(L"  dropdown to the items matching the");
	SynTest->Lines->Add(L"  text you have typed, similar to the");
	SynTest->Lines->Add(L"  way the D6 does it.");
//	GetTSynEditRemovedKeystrokes(SynTest, 0)->Command = ecContextHelp;
//	GetTSynEditRemovedKeystrokes(SynTest, 0)->ShortCut = 112;
//	SynTest->AddedKeystrokes->Add();
//	SynTest->AddedKeystrokes->AddedKeystrokes[0]->Command = ecContextHelp;
//	SynTest->AddedKeystrokes->AddedKeystrokes[0]->ShortCut = 16496;
	edBiggestWord = new TEdit(CodeCompletion);
	edBiggestWord->Parent = CodeCompletion;
	edBiggestWord->Left = 80;
	edBiggestWord->Top = 16;
	edBiggestWord->Width = 121;
	edBiggestWord->Height = 21;
	edBiggestWord->TabOrder = 0;
	edBiggestWord->Text = L"constructor";
	edBiggestWord->OnChange = edBiggestWordChange;
	cbCase = new TCheckBox(CodeCompletion);
	cbCase->Parent = CodeCompletion;
	cbCase->Tag = 1;
	cbCase->Left = 8;
	cbCase->Top = 40;
	cbCase->Width = 129;
	cbCase->Height = 17;
	cbCase->Caption = L"Case Sensitive";
	cbCase->TabOrder = 2;
	cbCase->OnClick = CheckBoxClick;
	cbPrettyText = new TCheckBox(CodeCompletion);
	cbPrettyText->Parent = CodeCompletion;
	cbPrettyText->Tag = 3;
	cbPrettyText->Left = 8;
	cbPrettyText->Top = 64;
	cbPrettyText->Width = 129;
	cbPrettyText->Height = 17;
	cbPrettyText->Caption = L"Use Pretty Text";
	cbPrettyText->Checked = true;
	cbPrettyText->State = cbChecked;
	cbPrettyText->TabOrder = 3;
	cbPrettyText->OnClick = CheckBoxClick;
	cbUseInsertList = new TCheckBox(CodeCompletion);
	cbUseInsertList->Parent = CodeCompletion;
	cbUseInsertList->Tag = 4;
	cbUseInsertList->Left = 8;
	cbUseInsertList->Top = 88;
	cbUseInsertList->Width = 129;
	cbUseInsertList->Height = 17;
	cbUseInsertList->Caption = L"Use Insert List";
	cbUseInsertList->Checked = true;
	cbUseInsertList->State = cbChecked;
	cbUseInsertList->TabOrder = 4;
	cbUseInsertList->OnClick = CheckBoxClick;
	cbLimitToMatchedText = new TCheckBox(CodeCompletion);
	cbLimitToMatchedText->Parent = CodeCompletion;
	cbLimitToMatchedText->Tag = 5;
	cbLimitToMatchedText->Left = 8;
	cbLimitToMatchedText->Top = 112;
	cbLimitToMatchedText->Width = 129;
	cbLimitToMatchedText->Height = 17;
	cbLimitToMatchedText->Caption = L"Limit To Matched Text";
	cbLimitToMatchedText->Checked = true;
	cbLimitToMatchedText->State = cbChecked;
	cbLimitToMatchedText->TabOrder = 5;
	cbLimitToMatchedText->OnClick = CheckBoxClick;
	SynEdit1 = new TSynEdit(CodeCompletion);
	SynEdit1->Parent = CodeCompletion;
	SynEdit1->Left = 5;
	SynEdit1->Top = 160;
	SynEdit1->Width = 401;
	SynEdit1->Height = 344;
	SynEdit1->Font->Charset = DEFAULT_CHARSET;
	SynEdit1->Font->Color = clWindowText;
	SynEdit1->Font->Height = -13;
	SynEdit1->Font->Name = L"Courier New";
	SynEdit1->Font->Style = (TFontStyles());
	SynEdit1->TabOrder = 8;
	SynEdit1->Gutter->Font->Charset = DEFAULT_CHARSET;
	SynEdit1->Gutter->Font->Color = clWindowText;
	SynEdit1->Gutter->Font->Height = -11;
	SynEdit1->Gutter->Font->Name = L"Terminal";
	SynEdit1->Gutter->Font->Style = (TFontStyles());
	SynEdit1->Lines->Add(L"Use Ctrl+Space to activate Code Completion");
	SynEdit1->Lines->Add(L"with a shortcut, or use the \x27" L".\x27" L" key");
	SynEdit1->Lines->Add(L"to activate it with a timer");
	SynEdit1->Lines->Add(L"");
	SynEdit1->Lines->Add(L"");
//	GetTSynEditRemovedKeystrokes(SynEdit1, 0)->Command = ecContextHelp;
//	GetTSynEditRemovedKeystrokes(SynEdit1, 0)->ShortCut = 112;
//	SynEdit1->AddedKeystrokes->Add();
//	SynEdit1->AddedKeystrokes->AddedKeystrokes[0]->Command = ecContextHelp;
//	SynEdit1->AddedKeystrokes->AddedKeystrokes[0]->ShortCut = 16496;
	edTitle = new TEdit(CodeCompletion);
	edTitle->Parent = CodeCompletion;
	edTitle->Left = 256;
	edTitle->Top = 16;
	edTitle->Width = 145;
	edTitle->Height = 21;
	edTitle->TabOrder = 1;
	edTitle->Text = L"Completion Proposal Demo";
	edTitle->OnChange = edTitleChange;
	Button3 = new TButton(CodeCompletion);
	Button3->Parent = CodeCompletion;
	Button3->Left = 240;
	Button3->Top = 112;
	Button3->Width = 75;
	Button3->Height = 25;
	Button3->Caption = L"Font";
	Button3->TabOrder = 6;
	Button3->OnClick = Button3Click;
	Button4 = new TButton(CodeCompletion);
	Button4->Parent = CodeCompletion;
	Button4->Left = 328;
	Button4->Top = 112;
	Button4->Width = 75;
	Button4->Height = 25;
	Button4->Caption = L"Title Font";
	Button4->TabOrder = 7;
	Button4->OnClick = Button4Click;
	TabSheet2 = new TTabSheet(PageControl1);
	TabSheet2->Parent = PageControl1;
	TabSheet2->PageControl = PageControl1;
	TabSheet2->Caption = L"Insert and Item Lists";
	TabSheet2->ImageIndex = 1;
	Label1 = new TLabel(TabSheet2);
	Label1->Parent = TabSheet2;
	Label1->Left = 8;
	Label1->Top = 8;
	Label1->Width = 57;
	Label1->Height = 13;
	Label1->Caption = L"Insert List";
	Label1->Font->Charset = DEFAULT_CHARSET;
	Label1->Font->Color = clWindowText;
	Label1->Font->Height = -11;
	Label1->Font->Name = L"MS Sans Serif";
	Label1->Font->Style = (TFontStyles() << fsBold);
	Label1->ParentFont = false;
	Label2 = new TLabel(TabSheet2);
	Label2->Parent = TabSheet2;
	Label2->Left = 8;
	Label2->Top = 240;
	Label2->Width = 45;
	Label2->Height = 13;
	Label2->Caption = L"ItemList";
	Label2->Font->Charset = DEFAULT_CHARSET;
	Label2->Font->Color = clWindowText;
	Label2->Font->Height = -11;
	Label2->Font->Name = L"MS Sans Serif";
	Label2->Font->Style = (TFontStyles() << fsBold);
	Label2->ParentFont = false;
	mmoInsert = new TMemo(TabSheet2);
	mmoInsert->Parent = TabSheet2;
	mmoInsert->Left = 8;
	mmoInsert->Top = 24;
	mmoInsert->Width = 729;
	mmoInsert->Height = 169;
	mmoInsert->Font->Charset = DEFAULT_CHARSET;
	mmoInsert->Font->Color = clWindowText;
	mmoInsert->Font->Height = -11;
	mmoInsert->Font->Name = L"Courier New";
	mmoInsert->Font->Style = (TFontStyles());
	mmoInsert->Lines->Add(L"mmoInsert");
	mmoInsert->ParentFont = false;
	mmoInsert->TabOrder = 0;
	mmoItem = new TMemo(TabSheet2);
	mmoItem->Parent = TabSheet2;
	mmoItem->Left = 8;
	mmoItem->Top = 256;
	mmoItem->Width = 729;
	mmoItem->Height = 209;
	mmoItem->Font->Charset = DEFAULT_CHARSET;
	mmoItem->Font->Color = clWindowText;
	mmoItem->Font->Height = -11;
	mmoItem->Font->Name = L"Courier New";
	mmoItem->Font->Style = (TFontStyles());
	mmoItem->Lines->Add(L"mmoItem");
	mmoItem->ParentFont = false;
	mmoItem->TabOrder = 1;
	mmoItem->WantTabs = true;
	Button1 = new TButton(TabSheet2);
	Button1->Parent = TabSheet2;
	Button1->Left = 8;
	Button1->Top = 200;
	Button1->Width = 137;
	Button1->Height = 25;
	Button1->Caption = L"Update Insert List";
	Button1->TabOrder = 2;
	Button1->OnClick = Button1Click;
	Button2 = new TButton(TabSheet2);
	Button2->Parent = TabSheet2;
	Button2->Left = 8;
	Button2->Top = 472;
	Button2->Width = 137;
	Button2->Height = 25;
	Button2->Caption = L"Update Item List";
	Button2->TabOrder = 3;
	Button2->OnClick = Button2Click;
	scpDemo = new TSynCompletionProposal(this);
	scpDemo->Options = (TSynCompletionOptions() << scoLimitToMatchedText << scoUseInsertList << scoUsePrettyText << scoUseBuiltInTimer << scoEndCharCompletion << scoCompleteWithTab << scoCompleteWithEnter);
	scpDemo->Width = 262;
	scpDemo->EndOfTokenChr = L"()[]. ";
	scpDemo->TriggerChars = L".";
	scpDemo->Title = L"Completion Proposal Demo";
	scpDemo->Font->Charset = DEFAULT_CHARSET;
	scpDemo->Font->Color = clWindowText;
	scpDemo->Font->Height = -11;
	scpDemo->Font->Name = L"MS Sans Serif";
	scpDemo->Font->Style = (TFontStyles());
	scpDemo->TitleFont->Charset = DEFAULT_CHARSET;
	scpDemo->TitleFont->Color = clBtnText;
	scpDemo->TitleFont->Height = -11;
	scpDemo->TitleFont->Name = L"MS Sans Serif";
	scpDemo->TitleFont->Style = (TFontStyles() << fsBold);
	scpDemo->Columns->Add();
	scpDemo->ShortCut = 16416;
	// non-visible component: Left
	FontDialog1 = new TFontDialog(this);
	FontDialog1->Font->Charset = DEFAULT_CHARSET;
	FontDialog1->Font->Color = clWindowText;
	FontDialog1->Font->Height = -11;
	FontDialog1->Font->Name = L"MS Sans Serif";
	FontDialog1->Font->Style = (TFontStyles());
	// non-visible component: Left
	// non-visible component: Top
	ComponentState >> csLoading;
	//----- shifted initializations from the dfm-file ---------------------------
	PageControl1->ActivePage = CodeCompletion;
	scpDemo->Editor = SynEdit1;
	//----- end of initializations from the dfm-file ----------------------------
}

