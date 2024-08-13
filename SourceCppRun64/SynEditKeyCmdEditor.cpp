#include <vcl.h>
#pragma hdrstop

#include "SynEditKeyCmdEditor.h"
#include <System.UITypes.hpp>
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditkeycmds;
using namespace Syneditmiscclasses;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Uitypes;
using namespace Vcl::Controls;
using namespace Vcl::Extctrls;
using namespace Vcl::Forms;
using namespace Vcl::Graphics;
using namespace Vcl::Stdctrls;

#define Syneditkeycmdeditor__0 (TMsgDlgButtons() << TMsgDlgBtn::mbOK)
#define Syneditkeycmdeditor__1 (TMsgDlgButtons() << TMsgDlgBtn::mbOK)
#define Syneditkeycmdeditor__2 Syneditmiscclasses::THKInvalidKeys()
#define Syneditkeycmdeditor__3 Syneditmiscclasses::THKModifiers()
#define Syneditkeycmdeditor__4 Syneditmiscclasses::THKInvalidKeys()
#define Syneditkeycmdeditor__5 Syneditmiscclasses::THKModifiers()


TSynEditKeystrokeEditorForm* SynEditKeystrokeEditorForm = nullptr;

/* TSynEditKeystrokeEditorForm */

void __fastcall TSynEditKeystrokeEditorForm::SetCommand(TSynEditorCommand Value)
{
	if(FExtended)
		cmbCommand->Text = ConvertCodeStringToExtended(EditorCommandToCodeString(Value));
	else
		cmbCommand->Text = EditorCommandToCodeString(Value);
}

void __fastcall TSynEditKeystrokeEditorForm::SetKeystroke(const TShortCut Value)
{
	hkKeystroke->HotKey = Value;
}

void __fastcall TSynEditKeystrokeEditorForm::FormShow(TObject* Sender)
{
	int i = 0;
	int stop = 0;
	if(FExtended)
		GetEditorCommandExtended(AddEditorCommand);
	else
		GetEditorCommandValues(AddEditorCommand);

  //Now add the values for quick access
	for(stop = cmbCommand->Items->Count - 1, i = 0; i <= stop; i++)
	{
		cmbCommand->Items->Objects[i] = ((TObject*) IndexToEditorCommand(i));
	}
	if(FExtended)
		cmbCommand->Sorted = true;
}

void __fastcall TSynEditKeystrokeEditorForm::AddEditorCommand(const String s)
{
	cmbCommand->Items->Add(s);
}

TSynEditorCommand __fastcall TSynEditKeystrokeEditorForm::GetCommand()
{
	TSynEditorCommand result = 0;
	if(cmbCommand->ItemIndex != -1)
	{
		result = ((TSynEditorCommand) (NativeInt) cmbCommand->Items->Objects[cmbCommand->ItemIndex]);
	}
	else
	result = (TSynEditorCommand) ecNone;
	return result;
}

TShortCut __fastcall TSynEditKeystrokeEditorForm::GetKeystroke()
{
	TShortCut result = (TShortCut) 0;
	result = hkKeystroke->HotKey;
	return result;
}

void __fastcall TSynEditKeystrokeEditorForm::bntClearKeyClick(TObject* Sender)
{
	hkKeystroke->HotKey = (TShortCut) 0;
	hkKeystroke2->HotKey = (TShortCut) 0;
}

TShortCut __fastcall TSynEditKeystrokeEditorForm::GetKeystroke2()
{
	TShortCut result = (TShortCut) 0;
	result = hkKeystroke2->HotKey;
	return result;
}

void __fastcall TSynEditKeystrokeEditorForm::SetKeystroke2(const TShortCut Value)
{
	hkKeystroke2->HotKey = Value;
}

void __fastcall TSynEditKeystrokeEditorForm::btnOKClick(TObject* Sender)
{
	if(Command == ecNone)
	{
		MessageDlg(L"You must first select a command.", TMsgDlgType::mtError, Syneditkeycmdeditor__0, 0);
		cmbCommand->SetFocus();
		cmbCommand->SelectAll();
	}
	else
	{
		if(Keystroke == 0)
		{
			MessageDlg(String(L"The command \"") + cmbCommand->Text
	           + L"\" needs to have at least one keystroke assigned to it.", TMsgDlgType::mtError, Syneditkeycmdeditor__1, 0);
			hkKeystroke->SetFocus();
		}
		else
		ModalResult = (TModalResult) mrOk;
	}
}

void __fastcall TSynEditKeystrokeEditorForm::FormCreate(TObject* Sender)
{
	hkKeystroke = new TSynHotKey(this);
	/*# with hkKeystroke do */
	{
		auto with0 = hkKeystroke;
		with0->Parent = pnlAlign;
		with0->Left = 65;
		with0->Top = 38;
		with0->Width = 186;
		with0->Height = 19;
		with0->HotKey = (TShortCut) 0;
		with0->InvalidKeys = Syneditkeycmdeditor__2;
		with0->Modifiers = Syneditkeycmdeditor__3;
		with0->TabOrder = (TTabOrder) 1;
	}
	hkKeystroke2 = new TSynHotKey(this);
	/*# with hkKeystroke2 do */
	{
		auto with1 = hkKeystroke2;
		with1->Parent = pnlAlign;
		with1->Left = 65;
		with1->Top = 62;
		with1->Width = 186;
		with1->Height = 19;
		with1->HotKey = (TShortCut) 0;
		with1->InvalidKeys = Syneditkeycmdeditor__4;
		with1->Modifiers = Syneditkeycmdeditor__5;
		with1->TabOrder = (TTabOrder) 2;
	}
}

__fastcall TSynEditKeystrokeEditorForm::TSynEditKeystrokeEditorForm(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	pnlAlign(nullptr),
	Label1(nullptr),
	Label2(nullptr),
	Label4(nullptr),
	bntClearKey(nullptr),
	btnOK(nullptr),
	cmbCommand(nullptr),
	btnCancel(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Left = 424;
	Top = 306;
	BorderStyle = bsDialog;
	Caption = L"Edit Keystroke";
	ClientHeight = 129;
	ClientWidth = 269;
	Color = clBtnFace;
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = clWindowText;
	Font->Height = -11;
	Font->Name = L"MS Sans Serif";
	Font->Style = (TFontStyles());
	AssignFormOldCreateOrder(this, true);
	Position = poScreenCenter;
	OnCreate = FormCreate;
	OnShow = FormShow;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	pnlAlign = new TPanel(this);
	pnlAlign->Parent = this;
	pnlAlign->Left = 3;
	pnlAlign->Top = 5;
	pnlAlign->Width = 262;
	pnlAlign->Height = 120;
	pnlAlign->BevelInner = bvRaised;
	pnlAlign->BevelOuter = bvLowered;
	pnlAlign->TabOrder = 0;
	Label1 = new TLabel(pnlAlign);
	Label1->Parent = pnlAlign;
	Label1->Left = 9;
	Label1->Top = 14;
	Label1->Width = 50;
	Label1->Height = 13;
	Label1->Caption = L"Command:";
	Label2 = new TLabel(pnlAlign);
	Label2->Parent = pnlAlign;
	Label2->Left = 9;
	Label2->Top = 41;
	Label2->Width = 50;
	Label2->Height = 13;
	Label2->Caption = L"Keystroke:";
	Label4 = new TLabel(pnlAlign);
	Label4->Parent = pnlAlign;
	Label4->Left = 9;
	Label4->Top = 65;
	Label4->Width = 50;
	Label4->Height = 13;
	Label4->Caption = L"Keystroke:";
	bntClearKey = new TButton(pnlAlign);
	bntClearKey->Parent = pnlAlign;
	bntClearKey->Left = 9;
	bntClearKey->Top = 86;
	bntClearKey->Width = 75;
	bntClearKey->Height = 25;
	bntClearKey->Caption = L"Clear Key";
	bntClearKey->TabOrder = 3;
	bntClearKey->OnClick = bntClearKeyClick;
	btnOK = new TButton(pnlAlign);
	btnOK->Parent = pnlAlign;
	btnOK->Left = 93;
	btnOK->Top = 86;
	btnOK->Width = 75;
	btnOK->Height = 25;
	btnOK->Caption = L"OK";
	btnOK->TabOrder = 1;
	btnOK->OnClick = btnOKClick;
	cmbCommand = new TComboBox(pnlAlign);
	cmbCommand->Parent = pnlAlign;
	cmbCommand->Left = 65;
	cmbCommand->Top = 14;
	cmbCommand->Width = 186;
	cmbCommand->Height = 21;
	cmbCommand->Style = csDropDownList;
	cmbCommand->TabOrder = 0;
	btnCancel = new TButton(pnlAlign);
	btnCancel->Parent = pnlAlign;
	btnCancel->Left = 177;
	btnCancel->Top = 86;
	btnCancel->Width = 75;
	btnCancel->Height = 25;
	btnCancel->Cancel = true;
	btnCancel->Caption = L"Cancel";
	btnCancel->ModalResult = 2;
	btnCancel->TabOrder = 2;
	ComponentState >> csLoading;
	//----- end of initializations from the dfm-file ----------------------------
}

