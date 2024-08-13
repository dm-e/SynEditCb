#include <vcl.h>
#pragma hdrstop

#include "dlgSearchText.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;



/* TTextSearchDialog */

bool __fastcall TTextSearchDialog::GetSearchBackwards()
{
	bool result = false;
	result = rgSearchDirection->ItemIndex == 1;
	return result;
}

bool __fastcall TTextSearchDialog::GetSearchCaseSensitive()
{
	bool result = false;
	result = cbSearchCaseSensitive->Checked;
	return result;
}

bool __fastcall TTextSearchDialog::GetSearchFromCursor()
{
	bool result = false;
	result = cbSearchFromCursor->Checked;
	return result;
}

bool __fastcall TTextSearchDialog::GetSearchInSelection()
{
	bool result = false;
	result = cbSearchSelectedOnly->Checked;
	return result;
}

bool __fastcall TTextSearchDialog::GetSearchRegularExpression()
{
	bool result = false;
	result = cbRegularExpression->Checked;
	return result;
}

String __fastcall TTextSearchDialog::GetSearchText()
{
	String result;
	result = cbSearchText->Text;
	return result;
}

String __fastcall TTextSearchDialog::GetSearchTextHistory()
{
	String result;
	int i = 0;
	int stop = 0;
	result = L"";
	for(stop = cbSearchText->Items->Count - 1, i = 0; i <= stop; i++)
	{
		if(i >= 10)
			break;
		if(i > 0)
			result = result + L"\x0d\x0a";
		result = result + cbSearchText->Items->Strings[i];
	}
	return result;
}

bool __fastcall TTextSearchDialog::GetSearchWholeWords()
{
	bool result = false;
	result = cbSearchWholeWords->Checked;
	return result;
}

void __fastcall TTextSearchDialog::SetSearchBackwards(bool Value)
{
	rgSearchDirection->ItemIndex = int(Value);
}

void __fastcall TTextSearchDialog::SetSearchCaseSensitive(bool Value)
{
	cbSearchCaseSensitive->Checked = Value;
}

void __fastcall TTextSearchDialog::SetSearchFromCursor(bool Value)
{
	cbSearchFromCursor->Checked = Value;
}

void __fastcall TTextSearchDialog::SetSearchInSelection(bool Value)
{
	cbSearchSelectedOnly->Checked = Value;
}

void __fastcall TTextSearchDialog::SetSearchText(String Value)
{
	cbSearchText->Text = Value;
}

void __fastcall TTextSearchDialog::SetSearchTextHistory(String Value)
{
	cbSearchText->Items->Text = Value;
}

void __fastcall TTextSearchDialog::SetSearchWholeWords(bool Value)
{
	cbSearchWholeWords->Checked = Value;
}

void __fastcall TTextSearchDialog::SetSearchRegularExpression(bool Value)
{
	cbRegularExpression->Checked = Value;
}

/* event handlers */

void __fastcall TTextSearchDialog::FormCloseQuery(TObject* Sender, bool& CanClose)
{
	String s;
	int i = 0;
	if(ModalResult == mrOk)
	{
		s = cbSearchText->Text;
		if(s != L"")
		{
			i = cbSearchText->Items->IndexOf(s);
			if(i > -1)
			{
				cbSearchText->Items->Delete(i);
				cbSearchText->Items->Insert(0, s);
				cbSearchText->Text = s;
			}
			else
			cbSearchText->Items->Insert(0, s);
		}
	}
}

__fastcall TTextSearchDialog::TTextSearchDialog(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	Label1(nullptr),
	cbSearchText(nullptr),
	rgSearchDirection(nullptr),
	gbSearchOptions(nullptr),
	cbSearchCaseSensitive(nullptr),
	cbSearchWholeWords(nullptr),
	cbSearchFromCursor(nullptr),
	cbSearchSelectedOnly(nullptr),
	btnOK(nullptr),
	btnCancel(nullptr),
	cbRegularExpression(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Left = 132;
	Top = 168;
	BorderStyle = bsDialog;
	Caption = L"Search Text";
	ClientHeight = 180;
	ClientWidth = 332;
	Color = clBtnFace;
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = clWindowText;
	Font->Height = -11;
	Font->Name = L"MS Sans Serif";
	Font->Style = (TFontStyles());
	AssignFormOldCreateOrder(this, false);
	OnCloseQuery = FormCloseQuery;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	Label1 = new TLabel(this);
	Label1->Parent = this;
	Label1->Left = 8;
	Label1->Top = 12;
	Label1->Width = 52;
	Label1->Height = 13;
	Label1->Caption = L"&Search for:";
	cbSearchText = new TComboBox(this);
	cbSearchText->Parent = this;
	cbSearchText->Left = 96;
	cbSearchText->Top = 8;
	cbSearchText->Width = 228;
	cbSearchText->Height = 21;
	cbSearchText->ItemHeight = 13;
	cbSearchText->TabOrder = 0;
	gbSearchOptions = new TGroupBox(this);
	gbSearchOptions->Parent = this;
	gbSearchOptions->Left = 8;
	gbSearchOptions->Top = 40;
	gbSearchOptions->Width = 154;
	gbSearchOptions->Height = 127;
	gbSearchOptions->Caption = L"Options";
	gbSearchOptions->TabOrder = 1;
	cbSearchCaseSensitive = new TCheckBox(gbSearchOptions);
	cbSearchCaseSensitive->Parent = gbSearchOptions;
	cbSearchCaseSensitive->Left = 8;
	cbSearchCaseSensitive->Top = 17;
	cbSearchCaseSensitive->Width = 140;
	cbSearchCaseSensitive->Height = 17;
	cbSearchCaseSensitive->Caption = L"C&ase sensitivity";
	cbSearchCaseSensitive->TabOrder = 0;
	cbSearchWholeWords = new TCheckBox(gbSearchOptions);
	cbSearchWholeWords->Parent = gbSearchOptions;
	cbSearchWholeWords->Left = 8;
	cbSearchWholeWords->Top = 39;
	cbSearchWholeWords->Width = 140;
	cbSearchWholeWords->Height = 17;
	cbSearchWholeWords->Caption = L"&Whole words only";
	cbSearchWholeWords->TabOrder = 1;
	cbSearchFromCursor = new TCheckBox(gbSearchOptions);
	cbSearchFromCursor->Parent = gbSearchOptions;
	cbSearchFromCursor->Left = 8;
	cbSearchFromCursor->Top = 61;
	cbSearchFromCursor->Width = 140;
	cbSearchFromCursor->Height = 17;
	cbSearchFromCursor->Caption = L"Search from &caret";
	cbSearchFromCursor->TabOrder = 2;
	cbSearchSelectedOnly = new TCheckBox(gbSearchOptions);
	cbSearchSelectedOnly->Parent = gbSearchOptions;
	cbSearchSelectedOnly->Left = 8;
	cbSearchSelectedOnly->Top = 83;
	cbSearchSelectedOnly->Width = 140;
	cbSearchSelectedOnly->Height = 17;
	cbSearchSelectedOnly->Caption = L"&Selected text only";
	cbSearchSelectedOnly->TabOrder = 3;
	cbRegularExpression = new TCheckBox(gbSearchOptions);
	cbRegularExpression->Parent = gbSearchOptions;
	cbRegularExpression->Left = 8;
	cbRegularExpression->Top = 104;
	cbRegularExpression->Width = 140;
	cbRegularExpression->Height = 17;
	cbRegularExpression->Caption = L"&Regular expression";
	cbRegularExpression->TabOrder = 4;
	rgSearchDirection = new TRadioGroup(this);
	rgSearchDirection->Parent = this;
	rgSearchDirection->Left = 170;
	rgSearchDirection->Top = 40;
	rgSearchDirection->Width = 154;
	rgSearchDirection->Height = 65;
	rgSearchDirection->Caption = L"Direction";
	rgSearchDirection->ItemIndex = 0;
	rgSearchDirection->Items->Add(L"&Forward");
	rgSearchDirection->Items->Add(L"&Backward");
	rgSearchDirection->TabOrder = 2;
	btnOK = new TButton(this);
	btnOK->Parent = this;
	btnOK->Left = 170;
	btnOK->Top = 149;
	btnOK->Width = 75;
	btnOK->Height = 23;
	btnOK->Caption = L"OK";
	btnOK->Default = true;
	btnOK->ModalResult = 1;
	btnOK->TabOrder = 3;
	btnCancel = new TButton(this);
	btnCancel->Parent = this;
	btnCancel->Left = 249;
	btnCancel->Top = 149;
	btnCancel->Width = 75;
	btnCancel->Height = 23;
	btnCancel->Cancel = true;
	btnCancel->Caption = L"Cancel";
	btnCancel->ModalResult = 2;
	btnCancel->TabOrder = 4;
	ComponentState >> csLoading;
	//----- end of initializations from the dfm-file ----------------------------
}

