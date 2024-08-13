#include <vcl.h>
#pragma hdrstop

#include "dlgReplaceText.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;



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

__fastcall TTextReplaceDialog::TTextReplaceDialog(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	Label2(nullptr),
	cbReplaceText(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Caption = L"Replace text";
	ClientHeight = 210;
	AssignFormOldCreateOrder(this, true);
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	Label2 = new TLabel(this);
	Label2->Parent = this;
	Label2->Left = 8;
	Label2->Top = 41;
	Label2->Width = 65;
	Label2->Height = 13;
	Label2->Caption = L"&Replace with:";
	/*inherited*/gbSearchOptions->Top = 70;
	/*inherited*/gbSearchOptions->TabOrder = 2;
	/*inherited*/rgSearchDirection->Top = 70;
	/*inherited*/rgSearchDirection->TabOrder = 3;
	/*inherited*/btnOK->Top = 179;
	/*inherited*/btnOK->TabOrder = 4;
	/*inherited*/btnCancel->Top = 179;
	/*inherited*/btnCancel->TabOrder = 5;
	cbReplaceText = new TComboBox(this);
	cbReplaceText->Parent = this;
	cbReplaceText->Left = 96;
	cbReplaceText->Top = 37;
	cbReplaceText->Width = 228;
	cbReplaceText->Height = 21;
	cbReplaceText->ItemHeight = 13;
	cbReplaceText->TabOrder = 1;
	ComponentState >> csLoading;
	//----- end of initializations from the dfm-file ----------------------------
}

