#include <vcl.h>
#pragma hdrstop

#include "dlgReplaceText.h"

using namespace std;
using namespace d2c_system;

__fastcall TTextReplaceDialog::TTextReplaceDialog(TComponent* AOwner) : inherited(AOwner) {}


#pragma resource "*.DFM"


/* TTextReplaceDialog */

String __fastcall TTextReplaceDialog::GetReplaceText()
{
	String result;
	result = cbReplaceText->Text;
	return result;
}

String __fastcall TTextReplaceDialog::GetReplaceTextHistory()
{
	String result;
	int i = 0;
	int stop = 0;
	result = L"";
	for(stop = cbReplaceText->Items->Count - 1, i = 0; i <= stop; i++)
	{
		if(i >= 10)
			break;
		if(i > 0)
			result = result + L"\x0d\x0a";
		result = result + cbReplaceText->Items->Strings[i];
	}
	return result;
}

void __fastcall TTextReplaceDialog::SetReplaceText(String Value)
{
	cbReplaceText->Text = Value;
}

void __fastcall TTextReplaceDialog::SetReplaceTextHistory(String Value)
{
	cbReplaceText->Items->Text = Value;
}

void __fastcall TTextReplaceDialog::FormCloseQuery(TObject* Sender, bool& CanClose)
{
	String s;
	int i = 0;
	inherited::FormCloseQuery(Sender, CanClose);
	if(ModalResult == mrOk)
	{
		s = cbReplaceText->Text;
		if(s != L"")
		{
			i = cbReplaceText->Items->IndexOf(s);
			if(i > -1)
			{
				cbReplaceText->Items->Delete(i);
				cbReplaceText->Items->Insert(0, s);
				cbReplaceText->Text = s;
			}
			else
			cbReplaceText->Items->Insert(0, s);
		}
	}
}
