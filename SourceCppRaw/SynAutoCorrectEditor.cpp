#include <vcl.h>
#pragma hdrstop

#include "SynAutoCorrectEditor.h"
#include <System.Types.hpp>

using namespace std;
using namespace d2c_system;
using namespace Synautocorrect;
using namespace System::Types;
using namespace System::Uitypes;
using namespace Vcl::Graphics;


__fastcall TfrmAutoCorrectEditor::TfrmAutoCorrectEditor(TComponent* AOwner) : inherited(AOwner) {}


#pragma resource "*.dfm"


void __fastcall TfrmAutoCorrectEditor::FormShow(TObject* Sender)
{
	lbxItems->Items->Assign(SynAutoCorrect->Items);
	Invalidate();
}

void __fastcall TfrmAutoCorrectEditor::lbxItemsDrawItemCLX(TObject* Sender, int Index, const TRect& cRect, TOwnerDrawState State, bool& Handled)
{
	TRect Rect = cRect;
	String s;
	/*# with lbxItems do */
	{
		auto with0 = lbxItems;
		s = with0->Items->Strings[Index];
		with0->Canvas->FillRect(Rect);
		with0->Canvas->TextOut(Rect.Left + 2, Rect.Top, SynAutoCorrect->HalfString(s, true));
		with0->Canvas->TextOut(Rect.Left + ((int)(lbxItems->ClientWidth / /*div*/ 2)) + 2, Rect.Top, SynAutoCorrect->HalfString(s, false));
		FormPaint(nullptr);
	}
}

void __fastcall TfrmAutoCorrectEditor::lbxItemsDrawItem(TWinControl* Control, int Index, const TRect& cRect, TOwnerDrawState State)
{
	TRect Rect = cRect;
	bool Dummy = false;
	Dummy = true;
	lbxItemsDrawItemCLX(Control, Index, Rect, State, Dummy);
}

void __fastcall TfrmAutoCorrectEditor::btnAddClick(TObject* Sender)
{
	String Original;
	String Correction;
	if(InputQuery(SAdd, SOriginal, Original))
		InputQuery(SAdd, SCorrection, Correction);
	else
		return;
	/*# with SynAutoCorrect do */
	{
		auto with0 = SynAutoCorrect;
		if((Original != L"") && (Correction != L""))
		{
			with0->Add(Original, Correction);
			lbxItems->Items->Assign(SynAutoCorrect->Items);
		}
	}
	btnDelete->Enabled = lbxItems->ItemIndex > -1;
	btnEdit->Enabled = lbxItems->ItemIndex > -1;
}

void __fastcall TfrmAutoCorrectEditor::btnDeleteClick(TObject* Sender)
{
	if(lbxItems->ItemIndex < 0)
	{
		MessageBox(0, ((PChar) SPleaseSelectItem), ((PChar) SError), (UINT) (MB_ICONERROR | MB_OK));
		return;
	}
	SynAutoCorrect->Delete(lbxItems->ItemIndex);
	lbxItems->Items->Assign(SynAutoCorrect->Items);
	btnDelete->Enabled = lbxItems->ItemIndex > -1;
	btnEdit->Enabled = lbxItems->ItemIndex > -1;
}

void __fastcall TfrmAutoCorrectEditor::btnEditClick(TObject* Sender)
{
	String Original;
	String Correction;
	String CurrText;
	if(lbxItems->ItemIndex < 0)
	{
		MessageBox(0, ((PChar) SPleaseSelectItem), ((PChar) SError), (UINT) (MB_ICONERROR | MB_OK));
		return;
	}
	/*# with SynAutoCorrect do */
	{
		auto with0 = SynAutoCorrect;
		CurrText = SynAutoCorrect->Items->Strings[lbxItems->ItemIndex];
		Original = SynAutoCorrect->HalfString(CurrText, true);
		Correction = SynAutoCorrect->HalfString(CurrText, false);
		if(InputQuery(SEdit, SOriginal, Original))
			InputQuery(SEdit, SCorrection, Correction);
		else
			return;
		with0->Edit(lbxItems->ItemIndex, Original, Correction);
		lbxItems->Items->Assign(SynAutoCorrect->Items);
	}
	btnDelete->Enabled = lbxItems->ItemIndex > -1;
	btnEdit->Enabled = lbxItems->ItemIndex > -1;
}

void __fastcall TfrmAutoCorrectEditor::btnDoneClick(TObject* Sender)
{
	Close();
}

void __fastcall TfrmAutoCorrectEditor::btnClearClick(TObject* Sender)
{
	if(MessageBox(0, ((PChar) SClearListConfirmation), ((PChar) SConfirmation), (UINT) (MB_YESNO | MB_ICONQUESTION)) != System::Uitypes::idYes)
		return;
	SynAutoCorrect->Items->Clear();
	lbxItems->Items->Clear();
	btnDelete->Enabled = lbxItems->ItemIndex > -1;
	btnEdit->Enabled = lbxItems->ItemIndex > -1;
}

void __fastcall TfrmAutoCorrectEditor::lbxItemsClick(TObject* Sender)
{
	btnDelete->Enabled = lbxItems->ItemIndex > -1;
	btnEdit->Enabled = lbxItems->ItemIndex > -1;
}

void __fastcall TfrmAutoCorrectEditor::FormCreate(TObject* Sender)
{
	ClientWidth = 521;
	ClientHeight = 377;
	lbxItems->OnDrawItem = lbxItemsDrawItem;
	BorderStyle = bsSingle;
}

void __fastcall TfrmAutoCorrectEditor::FormPaint(TObject* Sender)
{

  /* Paints the line in the middle of the listbox. */
	/*# with lbxItems.Canvas do */
	{
		auto with0 = lbxItems->Canvas;
		with0->Pen->Color = (TColor) clBlack;
		with0->PenPos = Point((int)(lbxItems->Width / /*div*/ 2) - 8, 0);
		with0->LineTo((int)(lbxItems->Width / /*div*/ 2) - 8, lbxItems->Height);
	}
}
