#include <vcl.h>
#pragma hdrstop

#include "SynEditKeyCmdEditor.h"
#include <System.UITypes.hpp>

using namespace std;
using namespace d2c_system;
using namespace Syneditkeycmds;
using namespace Syneditmiscclasses;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Uitypes;
using namespace Vcl::Dialogs;
using namespace Vcl::Forms;

#define SynEditKeyCmdEditor__0 (TMsgDlgButtons() << System::Uitypes::TMsgDlgBtn::mbOK)
#define SynEditKeyCmdEditor__1 (TMsgDlgButtons() << System::Uitypes::TMsgDlgBtn::mbOK)
#define SynEditKeyCmdEditor__2 Syneditmiscclasses::THKInvalidKeys()
#define SynEditKeyCmdEditor__3 Syneditmiscclasses::THKModifiers()
#define SynEditKeyCmdEditor__4 Syneditmiscclasses::THKInvalidKeys()
#define SynEditKeyCmdEditor__5 Syneditmiscclasses::THKModifiers()

__fastcall TSynEditKeystrokeEditorForm::TSynEditKeystrokeEditorForm(System::Classes::TComponent* AOwner) : inherited(AOwner) {}


TSynEditKeystrokeEditorForm* SynEditKeystrokeEditorForm = nullptr;
#pragma resource "*.dfm" 


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
	if(cmbCommand->ItemIndex !=  - 1)
	{
		result = ((TSynEditorCommand) ((int) cmbCommand->Items->Objects[cmbCommand->ItemIndex]));
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
		MessageDlg(L"You must first select a command.", System::Uitypes::TMsgDlgType::mtError, SynEditKeyCmdEditor__0, 0);
		cmbCommand->SetFocus();
		cmbCommand->SelectAll();
	}
	else
	{
		if(Keystroke == 0)
		{
			MessageDlg(String(L"The command \"") + cmbCommand->Text
	           + L"\" needs to have at least one keystroke assigned to it.", System::Uitypes::TMsgDlgType::mtError, SynEditKeyCmdEditor__1, 0);
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
		with0->InvalidKeys = SynEditKeyCmdEditor__2;
		with0->Modifiers = SynEditKeyCmdEditor__3;
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
		with1->InvalidKeys = SynEditKeyCmdEditor__4;
		with1->Modifiers = SynEditKeyCmdEditor__5;
		with1->TabOrder = (TTabOrder) 2;
	}
}
