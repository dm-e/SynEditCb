#include <vcl.h>
#pragma hdrstop

#include "dlgSearchText.h"

using namespace std;
using namespace d2c_system;

__fastcall TTextSearchDialog::TTextSearchDialog(TComponent* AOwner) : inherited(AOwner) {}


#pragma resource "*.DFM"


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
