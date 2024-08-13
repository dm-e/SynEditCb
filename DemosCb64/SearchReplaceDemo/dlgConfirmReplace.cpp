#include <vcl.h>
#pragma hdrstop

#include "dlgConfirmReplace.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;


TConfirmReplaceDialog* ConfirmReplaceDialog = nullptr;
const System::Char SAskReplaceText[] = L"Replace this occurence of \"%s\"?";

/* TConfirmReplaceDialog */

void __fastcall TConfirmReplaceDialog::FormCreate(TObject* Sender)
{
	Image1->Picture->Icon->Handle = LoadIcon(0, const_cast<LPCWSTR>(IDI_QUESTION));
}

void __fastcall TConfirmReplaceDialog::FormDestroy(TObject* Sender)
{
	ConfirmReplaceDialog = nullptr;
}

void __fastcall TConfirmReplaceDialog::PrepareShow(const TRect& cAEditorRect, int X, int Y1, int Y2, String AReplaceText)
{
	TRect AEditorRect = cAEditorRect;
	int nW = 0;
	int nH = 0;
	lblConfirmation->Caption = Format(SAskReplaceText, ARRAYOFCONST((AReplaceText)));
	nW = AEditorRect.Right - AEditorRect.Left;
	nH = AEditorRect.Bottom - AEditorRect.Top;
	if(nW <= Width)
		X = AEditorRect.Left - (int)((Width - nW) / /*div*/ 2);
	else
	{
		if(X + Width > AEditorRect.Right)
			X = AEditorRect.Right - Width;
	}
	if(Y2 > AEditorRect.Top + MulDiv(nH, 2, 3))
		Y2 = Y1 - Height - 4;
	else
		Y2 += 4;
	SetBounds(X, Y2, Width, Height);
}

__fastcall TConfirmReplaceDialog::TConfirmReplaceDialog(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	btnReplace(nullptr),
	lblConfirmation(nullptr),
	btnSkip(nullptr),
	btnCancel(nullptr),
	btnReplaceAll(nullptr),
	Image1(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Left = 176;
	Top = 158;
	BorderStyle = bsDialog;
	Caption = L"Confirm replace";
	ClientHeight = 98;
	ClientWidth = 328;
	Color = clBtnFace;
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = clWindowText;
	Font->Height = -11;
	Font->Name = L"MS Sans Serif";
	Font->Style = (TFontStyles());
	AssignFormOldCreateOrder(this, false);
	OnCreate = FormCreate;
	OnDestroy = FormDestroy;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	lblConfirmation = new TLabel(this);
	lblConfirmation->Parent = this;
	lblConfirmation->Left = 60;
	lblConfirmation->Top = 12;
	lblConfirmation->Width = 261;
	lblConfirmation->Height = 44;
	lblConfirmation->AutoSize = false;
	lblConfirmation->WordWrap = true;
	Image1 = new TImage(this);
	Image1->Parent = this;
	Image1->Left = 16;
	Image1->Top = 16;
	Image1->Width = 32;
	Image1->Height = 32;
	btnReplace = new TButton(this);
	btnReplace->Parent = this;
	btnReplace->Left = 8;
	btnReplace->Top = 67;
	btnReplace->Width = 75;
	btnReplace->Height = 23;
	btnReplace->Caption = L"&Yes";
	btnReplace->Default = true;
	btnReplace->ModalResult = 6;
	btnReplace->TabOrder = 0;
	btnSkip = new TButton(this);
	btnSkip->Parent = this;
	btnSkip->Left = 87;
	btnSkip->Top = 67;
	btnSkip->Width = 75;
	btnSkip->Height = 23;
	btnSkip->Caption = L"&No";
	btnSkip->ModalResult = 7;
	btnSkip->TabOrder = 1;
	btnCancel = new TButton(this);
	btnCancel->Parent = this;
	btnCancel->Left = 166;
	btnCancel->Top = 67;
	btnCancel->Width = 75;
	btnCancel->Height = 23;
	btnCancel->Cancel = true;
	btnCancel->Caption = L"Cancel";
	btnCancel->ModalResult = 2;
	btnCancel->TabOrder = 2;
	btnReplaceAll = new TButton(this);
	btnReplaceAll->Parent = this;
	btnReplaceAll->Left = 245;
	btnReplaceAll->Top = 67;
	btnReplaceAll->Width = 75;
	btnReplaceAll->Height = 23;
	btnReplaceAll->Caption = L"Yes to &all";
	btnReplaceAll->ModalResult = 10;
	btnReplaceAll->TabOrder = 3;
	ComponentState >> csLoading;
	//----- end of initializations from the dfm-file ----------------------------
}

