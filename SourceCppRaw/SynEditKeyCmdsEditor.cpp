#include <vcl.h>
#pragma hdrstop

#include "SynEditKeyCmdsEditor.h"
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include "SynEditKeyCmdEditor.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditkeycmds;
using namespace Syneditstrconst;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Types;
using namespace System::Uitypes;
using namespace Vcl::Forms;

#define Syneditkeycmdseditor__0 (TMsgDlgButtons() << TMsgDlgBtn::mbOK << TMsgDlgBtn::mbCancel)
#define Syneditkeycmdseditor__1 (TMsgDlgButtons() << TMsgDlgBtn::mbOK << TMsgDlgBtn::mbCancel)


#pragma resource "*.dfm"


/* TSynEditKeystrokesEditorForm */

__fastcall TSynEditKeystrokesEditorForm::TSynEditKeystrokesEditorForm(TComponent* AOwner)
 : inherited(AOwner),
			pnlBottom(nullptr),
			lnlInfo(nullptr),
			lnlInfo2(nullptr),
			btnAdd(nullptr),
			btnEdit(nullptr),
			btnDelete(nullptr),
			btnClear(nullptr),
			btnReset(nullptr),
			btnOK(nullptr),
			btnCancel(nullptr),
			pnlCommands(nullptr),
			KeyCmdList(nullptr),
			FKeystrokes(nullptr),
			FExtended(false)
{
	FKeystrokes = nullptr;
}

__fastcall TSynEditKeystrokesEditorForm::~TSynEditKeystrokesEditorForm()
{
	if(ASSIGNED(FKeystrokes))
		delete FKeystrokes;
	//# inherited::TForm::Destroy();
}

void __fastcall TSynEditKeystrokesEditorForm::SetKeystrokes(TSynEditKeyStrokes* const Value)
{
	if(FKeystrokes == nullptr)
		FKeystrokes = new TSynEditKeyStrokes(this);
	FKeystrokes->Assign((TPersistent*) Value);
	UpdateKeystrokesList();
}

void __fastcall TSynEditKeystrokesEditorForm::UpdateKeystrokesList()
{
	int x = 0;
	KeyCmdList->Items->BeginUpdate();
	try
	{
		int stop = 0;
		KeyCmdList->Items->Clear();
		for(stop = FKeystrokes->Count - 1, x = 0; x <= stop; x++)
		{
			/*# with KeyCmdList.Items.Add do */
			{
				auto with0 = KeyCmdList->Items->Add();
				if(FExtended)
					with0->Caption = ConvertCodeStringToExtended(EditorCommandToCodeString(FKeystrokes->Items[x]->Command));
				else
					with0->Caption = EditorCommandToCodeString(FKeystrokes->Items[x]->Command);
				if(FKeystrokes->Items[x]->ShortCut == 0)
					with0->SubItems->Add(SYNS_ShortcutNone);
				else
				{
					if(FKeystrokes->Items[x]->ShortCut2 == 0)
						with0->SubItems->Add(Menus::ShortCutToText(FKeystrokes->Items[x]->ShortCut));
					else
						with0->SubItems->Add(Menus::ShortCutToText(FKeystrokes->Items[x]->ShortCut)
	           + L" "
	           + Menus::ShortCutToText(FKeystrokes->Items[x]->ShortCut2));
				}
			}
		}
	}
	__finally
	{
		KeyCmdList->Items->EndUpdate();
	}
}

void __fastcall TSynEditKeystrokesEditorForm::FormResize(TObject* Sender)
{
	pnlBottom->Width = pnlBottom->Left + ClientWidth - 25;
	pnlBottom->Height = ClientHeight - 11;
	pnlCommands->Width = ClientWidth - 136;
	pnlCommands->Height = ClientHeight - 75;
	btnAdd->Left = pnlCommands->Left + pnlCommands->Width + 14;
	btnEdit->Left = pnlCommands->Left + pnlCommands->Width + 14;
	btnDelete->Left = pnlCommands->Left + pnlCommands->Width + 14;
	btnClear->Left = pnlCommands->Left + pnlCommands->Width + 14;
	btnReset->Left = pnlCommands->Left + pnlCommands->Width + 14;
	btnOK->Left = pnlCommands->Left + pnlCommands->Width + 14;
	btnOK->Top = pnlCommands->Top + pnlCommands->Height - 19;
	btnCancel->Left = pnlCommands->Left + pnlCommands->Width + 14;
	btnCancel->Top = pnlCommands->Top + pnlCommands->Height + 13;
	lnlInfo->Top = pnlCommands->Top + pnlCommands->Height + 11;
	lnlInfo2->Top = pnlCommands->Top + pnlCommands->Height + 27;
}

void __fastcall TSynEditKeystrokesEditorForm::WMGetMinMaxInfo(TWMGetMinMaxInfo& Msg)
{
	inherited::Dispatch(&Msg);  //#inherited method "WMGetMinMaxInfo" not not accessible;
	Msg.MinMaxInfo->ptMinTrackSize = Point(300, 225);
}            //DDH 10/16/01 Begin (reworked proc)

void __fastcall TSynEditKeystrokesEditorForm::btnAddClick(TObject* Sender)
{
	TSynEditKeyStroke* NewStroke = nullptr;
	TSynEditKeystrokeEditorForm* AForm = nullptr;

	auto AddKeyStroke = [&]() -> bool 
	{
		bool result = false;
		int KeyLoc = 0;
		String TmpCommand;
		result = false;
		KeyLoc = 0;
		if(AForm->ShowModal() == mrOk)
		{
			result = true;
			NewStroke = FKeystrokes->Add();
			NewStroke->Command = AForm->Command;
			try
			{
				KeyLoc = ((TSynEditKeyStrokes*) NewStroke->Collection)->FindShortcut2(AForm->Keystroke, AForm->Keystroke2);
				NewStroke->ShortCut = AForm->Keystroke;
				NewStroke->ShortCut2 = AForm->Keystroke2;
			}
			catch(ESynKeyError*)
			{
				{
					if(FExtended)
						TmpCommand = ConvertCodeStringToExtended(EditorCommandToCodeString(((TSynEditKeyStrokes*) NewStroke->Collection)->Items[KeyLoc]->Command));
					else
						TmpCommand = EditorCommandToCodeString(((TSynEditKeyStrokes*) NewStroke->Collection)->Items[KeyLoc]->Command);
					result = MessageDlg(Format(SYNS_DuplicateShortcutMsg, ARRAYOFCONST((Menus::ShortCutToText(AForm->Keystroke), TmpCommand))), TMsgDlgType::mtError, Syneditkeycmdseditor__0, 0) == mrOk;
					delete NewStroke;
					if(result)
						result = result;
				}
			}
        // Some other kind of exception, we don't deal with it...

            // Shortcut already exists in the collection!
		}
		return result;
	};
	AForm = new TSynEditKeystrokeEditorForm(this);
	/*# with AForm do */
	{
		auto with0 = AForm;
		try
		{
			with0->Caption = L"Add Keystroke";
			with0->ExtendedString = this->ExtendedString;
			with0->Command = (TSynEditorCommand) ecNone;
			with0->Keystroke = (TShortCut) 0;
			with0->Keystroke2 = (TShortCut) 0;
			if(AddKeyStroke())
			{
				/*# with KeyCmdList.Items.Add do */
				{
					auto with1 = KeyCmdList->Items->Add();
					if(FExtended)
						with1->Caption = ConvertCodeStringToExtended(EditorCommandToCodeString(NewStroke->Command));
					else
						with1->Caption = EditorCommandToCodeString(NewStroke->Command);
					if(NewStroke->ShortCut == 0)
						with1->SubItems->Add(SYNS_ShortcutNone);
					else
					{
						if(NewStroke->ShortCut2 == 0)
							with1->SubItems->Add(Menus::ShortCutToText(NewStroke->ShortCut));
						else
							with1->SubItems->Add(Menus::ShortCutToText(NewStroke->ShortCut) + L" " + Menus::ShortCutToText(NewStroke->ShortCut2));
					}
				}
			}
		}
		__finally
		{
			delete AForm;
		}
	}
}

void __fastcall TSynEditKeystrokesEditorForm::btnEditClick(TObject* Sender)
{
	TListItem* SelItem = nullptr;
	TShortCut OldShortcut = (TShortCut) 0;
	TShortCut OldShortcut2 = (TShortCut) 0;
	TSynEditKeystrokeEditorForm* AForm = nullptr;

	auto EditKeyStroke = [&]() -> bool 
	{
		bool result = false;
		int KeyLoc = 0;
		String TmpCommand;
		result = false;
		KeyLoc = 0;
		if(AForm->ShowModal() == mrOk)
		{
			result = true;
			OldShortcut = FKeystrokes->Items[SelItem->Index]->ShortCut;
			OldShortcut2 = FKeystrokes->Items[SelItem->Index]->ShortCut2;
			try
			{
				KeyLoc = ((TSynEditKeyStrokes*) FKeystrokes->Items[SelItem->Index]->Collection)->FindShortcut2(AForm->Keystroke, AForm->Keystroke2);
				FKeystrokes->Items[SelItem->Index]->Command = AForm->Command;
				FKeystrokes->Items[SelItem->Index]->ShortCut = AForm->Keystroke;
				FKeystrokes->Items[SelItem->Index]->ShortCut2 = AForm->Keystroke2;
			}
			catch(ESynKeyError*)
			{
				{
					if(FExtended)
						TmpCommand = ConvertCodeStringToExtended(EditorCommandToCodeString(((TSynEditKeyStrokes*) FKeystrokes->Items[SelItem->Index]->Collection)->Items[KeyLoc]->Command));
					else
						TmpCommand = EditorCommandToCodeString(((TSynEditKeyStrokes*) FKeystrokes->Items[SelItem->Index]->Collection)->Items[KeyLoc]->Command);
					result = MessageDlg(Format(SYNS_DuplicateShortcutMsg, ARRAYOFCONST((Menus::ShortCutToText(AForm->Keystroke), TmpCommand))), TMsgDlgType::mtError, Syneditkeycmdseditor__1, 0) == mrOk;
					FKeystrokes->Items[SelItem->Index]->ShortCut = OldShortcut;
					FKeystrokes->Items[SelItem->Index]->ShortCut2 = OldShortcut2;
					if(result)
						result = result;
				}
			}
        // Some other kind of exception, we don't deal with it...

            // Shortcut already exists in the collection!
		}
/*
      if ShowModal = mrOK then
      begin

        try
        except
          on ESynKeyError do
            begin
              // Shortcut already exists in the collection!
              MessageDlg(Format(SYNS_DuplicateShortcutMsg2,
                [Menus.ShortCutToText(Keystroke)]), mtError, [mbOK], 0);
            end;
          // Some other kind of exception, we don't deal with it...
        end;
*/
		return result;
	};
	SelItem = KeyCmdList->Selected;
	if(SelItem == nullptr)
	{
		MessageBeep(1);
		return;
	}
	AForm = new TSynEditKeystrokeEditorForm(this);
	/*# with AForm do */
	{
		auto with0 = AForm;
		try
		{
			with0->ExtendedString = this->ExtendedString;
			with0->Command = FKeystrokes->Items[SelItem->Index]->Command;
			with0->Keystroke = FKeystrokes->Items[SelItem->Index]->ShortCut;
			with0->Keystroke2 = FKeystrokes->Items[SelItem->Index]->ShortCut2;
			if(EditKeyStroke())
			{
				KeyCmdList->Items->BeginUpdate();
				try
				{
					/*# with SelItem do */
					{
						auto with1 = SelItem;
						if(FExtended)
							with1->Caption = ConvertCodeStringToExtended(EditorCommandToCodeString(FKeystrokes->Items[with1->Index]->Command));
						else
							with1->Caption = EditorCommandToCodeString(FKeystrokes->Items[with1->Index]->Command);
						if(FKeystrokes->Items[with1->Index]->ShortCut == 0)
							with1->SubItems->Strings[0] = SYNS_ShortcutNone;
						else
						{
							if(FKeystrokes->Items[with1->Index]->ShortCut2 == 0)
								with1->SubItems->Strings[0] = Menus::ShortCutToText(FKeystrokes->Items[with1->Index]->ShortCut);
							else
								with1->SubItems->Strings[0] = Menus::ShortCutToText(FKeystrokes->Items[with1->Index]->ShortCut)
	           + L" "
	           + Menus::ShortCutToText(FKeystrokes->Items[with1->Index]->ShortCut2);
						}
					}
				}
				__finally
				{
					KeyCmdList->Items->EndUpdate();
				}
			}
		}
		__finally
		{
			delete AForm;
		}
	}
}                                                                            //DDH 10/16/01 End (reworked procs)

void __fastcall TSynEditKeystrokesEditorForm::btnDeleteClick(TObject* Sender)
{
	TListItem* SelItem = nullptr;
	SelItem = KeyCmdList->Selected;
	if(SelItem == nullptr)
	{
		MessageBeep(1);
		return;
	}
	delete FKeystrokes->Items[SelItem->Index];
	KeyCmdList->Items->Delete(SelItem->Index);
}

void __fastcall TSynEditKeystrokesEditorForm::btnClearClick(TObject* Sender)
{
	FKeystrokes->Clear();
	KeyCmdList->Items->Clear();
}

void __fastcall TSynEditKeystrokesEditorForm::btnResetClick(TObject* Sender)
{
	FKeystrokes->ResetDefaults();
	UpdateKeystrokesList();
}

void __fastcall TSynEditKeystrokesEditorForm::FormCreate(TObject* Sender)
{
	KeyCmdList->RowSelect = true;
}

void __fastcall TSynEditKeystrokesEditorForm::btnOKClick(TObject* Sender)
{
	ModalResult = (TModalResult) mrOk;
}

void __fastcall TSynEditKeystrokesEditorForm::btnCancelClick(TObject* Sender)
{
	ModalResult = (TModalResult) mrCancel;
}

void __fastcall TSynEditKeystrokesEditorForm::KeyCmdListClick(TObject* Sender)
{
	btnEdit->Enabled = ASSIGNED(KeyCmdList->Selected);
	btnDelete->Enabled = btnEdit->Enabled;
}
