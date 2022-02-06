#include <vcl.h>
#pragma hdrstop

#include "dlgConfirmReplace.h"

using namespace std;
using namespace d2c_system;

__fastcall TConfirmReplaceDialog::TConfirmReplaceDialog(TComponent* AOwner) : inherited(AOwner) {}


TConfirmReplaceDialog* ConfirmReplaceDialog = nullptr;
#pragma resource "*.DFM" 

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
		X = AEditorRect.Left - (int)((Width - nW) / 2);
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
