#include <vcl.h>
#pragma hdrstop

#include "SynAutoCorrectEditor.h"
#include <System.Types.hpp>
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;
using namespace Synautocorrect;
using namespace System::Types;
using namespace System::Uitypes;
using namespace Vcl::Graphics;




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
	if(MessageBox(0, ((PChar) SClearListConfirmation), ((PChar) SConfirmation), (UINT) (MB_YESNO | MB_ICONQUESTION)) != IDYES)
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

__fastcall TfrmAutoCorrectEditor::TfrmAutoCorrectEditor(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	lblLabel1(nullptr),
	lblLabel2(nullptr),
	lbxItems(nullptr),
	btnAdd(nullptr),
	btnDelete(nullptr),
	btnClear(nullptr),
	btnEdit(nullptr),
	btnDone(nullptr),
	bvlSeparator(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Left = 210;
	Top = 111;
	BorderStyle = bsDialog;
	Caption = L"AutoCorrection Items...";
	ClientHeight = 377;
	ClientWidth = 521;
	Color = clBtnFace;
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = clWindowText;
	Font->Height = -11;
	Font->Name = L"MS Sans Serif";
	Font->Style = (TFontStyles());
	AssignFormOldCreateOrder(this, true);
	Position = poScreenCenter;
	ShowHint = true;
	OnCreate = FormCreate;
	OnPaint = FormPaint;
	OnShow = FormShow;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	lblLabel1 = new TLabel(this);
	lblLabel1->Parent = this;
	lblLabel1->Left = 16;
	lblLabel1->Top = 56;
	lblLabel1->Width = 38;
	lblLabel1->Height = 13;
	lblLabel1->Caption = L"&Original:";
	lblLabel2 = new TLabel(this);
	lblLabel2->Parent = this;
	lblLabel2->Left = 252;
	lblLabel2->Top = 56;
	lblLabel2->Width = 56;
	lblLabel2->Height = 13;
	lblLabel2->Caption = L"&Corrections:";
	btnAdd = new TSpeedButton(this);
	btnAdd->Parent = this;
	btnAdd->Left = 16;
	btnAdd->Top = 16;
	btnAdd->Width = 65;
	btnAdd->Height = 23;
	btnAdd->Hint = L"Adds a new item to the auto-correction list.";
	btnAdd->Caption = L" &Add";
	AssignTBitmapData(btnAdd, {
					0x36,0x03,0x00,0x00,0x42,0x4D,0x36,0x03,0x00,0x00
					,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00
					,0x00,0x00,0x10,0x00,0x00,0x00,0x10,0x00,0x00,0x00
					,0x01,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x03
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80
					,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00
					,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80
					,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00
					,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
					,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
					,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
					,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
					,0x80,0x80,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80
					,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0xFF,0xFF
					,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF
					,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00
					,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF
					,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x80,0x80,0x80
					,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF
					,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF
					,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF
					,0x00,0x00,0x00,0xC0,0xC0,0xC0,0x00,0x00,0x00,0xFF
					,0xFF,0xFF,0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x80
					,0x80,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0xFF,0xFF
					,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00
					,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00
					,0x00,0x00,0xFF,0xFF,0xC0,0xC0,0xC0,0x00,0x00,0x00
					,0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x80,0x80,0x00
					,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF
					,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF
					,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x80,0x80,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00
					,0xFF,0xFF,0xFF,0x80,0x80,0x80,0x00,0xFF,0xFF,0xFF
					,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF
					,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF
					,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x80
					,0x80,0x80,0x80,0x80,0x80,0x00,0xFF,0xFF,0x00,0xFF
					,0xFF,0x80,0x80,0x80,0xFF,0xFF,0xFF,0x00,0xFF,0xFF
					,0x80,0x80,0x80,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
					,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF
					,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x80,0x80,0x80
					,0x00,0x80,0x80,0x80,0x80,0x80,0xFF,0xFF,0xFF,0x80
					,0x80,0x80,0x00,0xFF,0xFF,0x80,0x80,0x80,0x00,0xFF
					,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0xFF,0xFF
					,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00
					,0xFF,0xFF,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80
					,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,0xFF,0xFF
					,0x80,0x80,0x80,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF
					,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF
					,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF
					,0x00,0x00,0x00,0x80,0x80,0x80,0xFF,0xFF,0xFF,0x00
					,0xFF,0xFF,0x80,0x80,0x80,0x00,0xFF,0xFF,0xFF,0xFF
					,0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
					,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x80,0x80
					,0x00,0xFF,0xFF,0x80,0x80,0x80,0x00,0xFF,0xFF,0x80
					,0x80,0x80,0x00,0xFF,0xFF,0x00,0x80,0x80,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80
					,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00
					,0x80,0x80,0x80,0x80,0x80,0x00,0xFF,0xFF,0x00,0x80
					,0x80,0x80,0x80,0x80,0xFF,0xFF,0xFF,0x00,0x80,0x80
					,0x80,0x80,0x80,0x00,0xFF,0xFF,0x00,0x80,0x80,0x00
					,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80
					,0x00,0xFF,0xFF,0x00,0x80,0x80,0x00,0x80,0x80,0x80
					,0x80,0x80,0x00,0xFF,0xFF,0x00,0x80,0x80,0x00,0x80
					,0x80,0x80,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80
					,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00
					,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x80,0x80
					,0xFF,0xFF,0xFF,0x00,0x80,0x80,0x00,0x80,0x80,0x00
					,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80
					,0x00,0x80,0x80,0x00,0x80,0x80
					});
	btnAdd->OnClick = btnAddClick;
	btnDelete = new TSpeedButton(this);
	btnDelete->Parent = this;
	btnDelete->Left = 88;
	btnDelete->Top = 16;
	btnDelete->Width = 65;
	btnDelete->Height = 23;
	btnDelete->Hint = L"Removes the selected item from the auto-correction list.";
	btnDelete->Caption = L"&Delete";
	btnDelete->Enabled = false;
	AssignTBitmapData(btnDelete, {
					0x36,0x03,0x00,0x00,0x42,0x4D,0x36,0x03,0x00,0x00
					,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00
					,0x00,0x00,0x10,0x00,0x00,0x00,0x10,0x00,0x00,0x00
					,0x01,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x03
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80
					,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00
					,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80
					,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00
					,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
					,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
					,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
					,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
					,0x80,0x80,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80
					,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0xFF,0xFF
					,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF
					,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00
					,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF
					,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x80,0x80,0x80
					,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF
					,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF
					,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF
					,0x00,0x00,0x00,0xC0,0xC0,0xC0,0x00,0x00,0x00,0xFF
					,0xFF,0xFF,0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00
					,0x80,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0xFF,0xFF
					,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00
					,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00
					,0x00,0x00,0xFF,0xFF,0xC0,0xC0,0xC0,0x00,0x00,0x00
					,0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x80,0x00
					,0x00,0x80,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF
					,0xFF,0xFF,0xFF,0xFF,0x80,0x80,0x80,0x00,0x00,0x80
					,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x80
					,0x80,0x80,0x80,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x80
					,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0xFF,0xFF
					,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF
					,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x80
					,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x80,0x00,0x00
					,0x80,0x80,0x80,0x80,0x00,0xFF,0xFF,0x00,0x00,0x80
					,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF
					,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF
					,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x80,0x80,0x80
					,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x80,0x00
					,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0xFF,0xFF
					,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF
					,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00
					,0xFF,0xFF,0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x80
					,0x80,0x80,0x80,0x80,0x00,0x00,0x80,0x00,0x00,0x80
					,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF
					,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF
					,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF
					,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00
					,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00
					,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x80,0x80,0x00,0x00,0x80,0x00,0x00,0x80
					,0x80,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x80,0x00
					,0x00,0x80,0x80,0x80,0x80,0x00,0x80,0x80,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80
					,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00
					,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x80
					,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x80,0x80,0x00
					,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80
					,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00
					,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x00
					,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x80,0x80
					,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00
					,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80
					,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00
					,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80
					,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80
					,0x00,0x80,0x80,0x00,0x80,0x80
					});
	btnDelete->OnClick = btnDeleteClick;
	btnClear = new TSpeedButton(this);
	btnClear->Parent = this;
	btnClear->Left = 160;
	btnClear->Top = 16;
	btnClear->Width = 65;
	btnClear->Height = 23;
	btnClear->Hint = L"Clears the entire list.";
	btnClear->Caption = L"&Clear";
	AssignTBitmapData(btnClear, {
					0xF6,0x00,0x00,0x00,0x42,0x4D,0xF6,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x76,0x00,0x00,0x00,0x28,0x00
					,0x00,0x00,0x10,0x00,0x00,0x00,0x10,0x00,0x00,0x00
					,0x01,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x80,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x10,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00
					,0x00,0x80,0x80,0x00,0x80,0x00,0x00,0x00,0x80,0x00
					,0x80,0x00,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00
					,0xC0,0xC0,0xC0,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF
					,0x00,0x00,0x00,0xFF,0xFF,0x00,0xFF,0x00,0x00,0x00
					,0xFF,0x00,0xFF,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF
					,0xFF,0x00,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88
					,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x80
					,0x88,0x88,0x88,0x88,0x88,0x08,0x88,0x00,0x08,0x88
					,0x88,0x88,0x88,0x88,0x88,0x00,0x00,0x88,0x88,0x88
					,0x80,0x88,0x88,0x80,0x00,0x88,0x88,0x88,0x08,0x88
					,0x88,0x88,0x00,0x08,0x88,0x80,0x08,0x88,0x88,0x88
					,0x80,0x00,0x88,0x00,0x88,0x88,0x88,0x88,0x88,0x00
					,0x00,0x08,0x88,0x88,0x88,0x88,0x88,0x80,0x00,0x88
					,0x88,0x88,0x88,0x88,0x88,0x00,0x00,0x08,0x88,0x88
					,0x88,0x88,0x80,0x00,0x88,0x00,0x88,0x88,0x88,0x80
					,0x00,0x08,0x88,0x80,0x08,0x88,0x88,0x00,0x00,0x88
					,0x88,0x88,0x00,0x88,0x88,0x00,0x08,0x88,0x88,0x88
					,0x88,0x08,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88
					
					});
	btnClear->OnClick = btnClearClick;
	btnEdit = new TSpeedButton(this);
	btnEdit->Parent = this;
	btnEdit->Left = 232;
	btnEdit->Top = 16;
	btnEdit->Width = 65;
	btnEdit->Height = 23;
	btnEdit->Hint = L"Edits the selected item on the auto-correction list.";
	btnEdit->Caption = L"&Edit";
	btnEdit->Enabled = false;
	btnEdit->OnClick = btnEditClick;
	btnDone = new TSpeedButton(this);
	btnDone->Parent = this;
	btnDone->Left = 312;
	btnDone->Top = 16;
	btnDone->Width = 65;
	btnDone->Height = 23;
	btnDone->Hint = L"Closes the edit dialog and saves the list.";
	btnDone->Caption = L"&Done";
	btnDone->OnClick = btnDoneClick;
	bvlSeparator = new TBevel(this);
	bvlSeparator->Parent = this;
	bvlSeparator->Left = 304;
	bvlSeparator->Top = 16;
	bvlSeparator->Width = 2;
	bvlSeparator->Height = 23;
	lbxItems = new TListBox(this);
	lbxItems->Parent = this;
	lbxItems->Left = 16;
	lbxItems->Top = 72;
	lbxItems->Width = 489;
	lbxItems->Height = 289;
	lbxItems->Style = lbOwnerDrawFixed;
	lbxItems->BorderStyle = bsNone;
	lbxItems->ItemHeight = 15;
	lbxItems->TabOrder = 0;
	lbxItems->OnClick = lbxItemsClick;
	ComponentState >> csLoading;
	//----- shifted initializations from the dfm-file ---------------------------
	lblLabel1->FocusControl = lbxItems;
	lblLabel2->FocusControl = lbxItems;
	//----- end of initializations from the dfm-file ----------------------------
}

