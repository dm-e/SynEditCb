#include <vcl.h>
#pragma hdrstop

#include "SynEditKeyCmdsEditor.h"
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include "SynEditKeyCmdEditor.h"
#include "SynEditStrConst.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditkeycmds;
using namespace Syneditstrconst;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Types;
using namespace System::Uitypes;
using namespace Vcl::Comctrls;
using namespace Vcl::Controls;
using namespace Vcl::Extctrls;
using namespace Vcl::Forms;
using namespace Vcl::Graphics;
using namespace Vcl::Stdctrls;

#define Syneditkeycmdseditor__0 (TMsgDlgButtons() << TMsgDlgBtn::mbOK << TMsgDlgBtn::mbCancel)
#define Syneditkeycmdseditor__1 (TMsgDlgButtons() << TMsgDlgBtn::mbOK << TMsgDlgBtn::mbCancel)



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
			fKeyStrokes(nullptr),
			FExtended(false)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Left = 300;
	Top = 241;
	BorderIcons = (TBorderIcons() << biSystemMenu << biMaximize);
	Caption = L"Keystroke Editor";
	ClientHeight = 319;
	ClientWidth = 382;
	Color = clBtnFace;
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = clWindowText;
	Font->Height = -11;
	Font->Name = L"MS Sans Serif";
	Font->Style = (TFontStyles());
	AssignFormOldCreateOrder(this, true);
	Position = poScreenCenter;
	OnCreate = FormCreate;
	OnResize = FormResize;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	pnlBottom = new TPanel(this);
	pnlBottom->Parent = this;
	pnlBottom->Left = 8;
	pnlBottom->Top = 8;
	pnlBottom->Width = 365;
	pnlBottom->Height = 308;
	pnlBottom->BevelInner = bvRaised;
	pnlBottom->BevelOuter = bvLowered;
	pnlBottom->TabOrder = 0;
	lnlInfo = new TLabel(pnlBottom);
	lnlInfo->Parent = pnlBottom;
	lnlInfo->Left = 5;
	lnlInfo->Top = 271;
	lnlInfo->Width = 229;
	lnlInfo->Height = 13;
	lnlInfo->Caption = L"NOTE: To have multiple keystrokes do the same";
	lnlInfo2 = new TLabel(pnlBottom);
	lnlInfo2->Parent = pnlBottom;
	lnlInfo2->Left = 42;
	lnlInfo2->Top = 287;
	lnlInfo2->Width = 217;
	lnlInfo2->Height = 13;
	lnlInfo2->Caption = L"command, assign the command multiple times.";
	pnlCommands = new TPanel(pnlBottom);
	pnlCommands->Parent = pnlBottom;
	pnlCommands->Left = 16;
	pnlCommands->Top = 16;
	pnlCommands->Width = 246;
	pnlCommands->Height = 244;
	pnlCommands->BevelInner = bvLowered;
	pnlCommands->BorderWidth = 4;
	pnlCommands->Caption = L"pnlCommands";
	pnlCommands->TabOrder = 0;
	KeyCmdList = new TListView(pnlCommands);
	KeyCmdList->Parent = pnlCommands;
	KeyCmdList->Left = 6;
	KeyCmdList->Top = 6;
	KeyCmdList->Width = 234;
	KeyCmdList->Height = 232;
	KeyCmdList->Align = alClient;
	KeyCmdList->BorderStyle = bsNone;
	GetTListColumnsitem(KeyCmdList->Columns, 0)->Caption = L"Command";
	GetTListColumnsitem(KeyCmdList->Columns, 0)->Width = (TWidth) 117;
	GetTListColumnsitem(KeyCmdList->Columns, 1)->Caption = L"Keystroke";
	GetTListColumnsitem(KeyCmdList->Columns, 1)->Width = (TWidth) 101;
	KeyCmdList->ColumnClick = false;
	KeyCmdList->HideSelection = false;
	KeyCmdList->TabOrder = 0;
	KeyCmdList->ViewStyle = vsReport;
	KeyCmdList->OnClick = KeyCmdListClick;
	KeyCmdList->OnDblClick = btnEditClick;
	btnAdd = new TButton(pnlBottom);
	btnAdd->Parent = pnlBottom;
	btnAdd->Left = 276;
	btnAdd->Top = 20;
	btnAdd->Width = 75;
	btnAdd->Height = 25;
	btnAdd->Caption = L"&Add";
	btnAdd->TabOrder = 1;
	btnAdd->OnClick = btnAddClick;
	btnEdit = new TButton(pnlBottom);
	btnEdit->Parent = pnlBottom;
	btnEdit->Left = 276;
	btnEdit->Top = 52;
	btnEdit->Width = 75;
	btnEdit->Height = 25;
	btnEdit->Caption = L"&Edit";
	btnEdit->Enabled = false;
	btnEdit->TabOrder = 2;
	btnEdit->OnClick = btnEditClick;
	btnDelete = new TButton(pnlBottom);
	btnDelete->Parent = pnlBottom;
	btnDelete->Left = 276;
	btnDelete->Top = 84;
	btnDelete->Width = 75;
	btnDelete->Height = 25;
	btnDelete->Caption = L"&Delete";
	btnDelete->Enabled = false;
	btnDelete->TabOrder = 3;
	btnDelete->OnClick = btnDeleteClick;
	btnClear = new TButton(pnlBottom);
	btnClear->Parent = pnlBottom;
	btnClear->Left = 276;
	btnClear->Top = 116;
	btnClear->Width = 75;
	btnClear->Height = 25;
	btnClear->Caption = L"C&lear List";
	btnClear->TabOrder = 4;
	btnClear->OnClick = btnClearClick;
	btnReset = new TButton(pnlBottom);
	btnReset->Parent = pnlBottom;
	btnReset->Left = 276;
	btnReset->Top = 148;
	btnReset->Width = 75;
	btnReset->Height = 25;
	btnReset->Caption = L"&Reset List";
	btnReset->TabOrder = 5;
	btnReset->OnClick = btnResetClick;
	btnOK = new TButton(pnlBottom);
	btnOK->Parent = pnlBottom;
	btnOK->Left = 276;
	btnOK->Top = 241;
	btnOK->Width = 75;
	btnOK->Height = 25;
	btnOK->Caption = L"&OK";
	btnOK->Default = true;
	btnOK->TabOrder = 6;
	btnOK->OnClick = btnOKClick;
	btnCancel = new TButton(pnlBottom);
	btnCancel->Parent = pnlBottom;
	btnCancel->Left = 276;
	btnCancel->Top = 273;
	btnCancel->Width = 75;
	btnCancel->Height = 25;
	btnCancel->Cancel = true;
	btnCancel->Caption = L"&Cancel";
	btnCancel->TabOrder = 7;
	btnCancel->OnClick = btnCancelClick;
	ComponentState >> csLoading;
	fKeyStrokes = nullptr;
}

__fastcall TSynEditKeystrokesEditorForm::~TSynEditKeystrokesEditorForm()
{
	if(ASSIGNED(fKeyStrokes))
		delete fKeyStrokes;
	//# inherited::TForm::Destroy();
}

void __fastcall TSynEditKeystrokesEditorForm::SetKeystrokes(TSynEditKeyStrokes* const Value)
{
	if(fKeyStrokes == nullptr)
		fKeyStrokes = new TSynEditKeyStrokes(this);
	fKeyStrokes->Assign((TPersistent*) Value);
	UpdateKeystrokesList();
}

void __fastcall TSynEditKeystrokesEditorForm::UpdateKeystrokesList()
{
	int X = 0;
	KeyCmdList->Items->BeginUpdate();
	try
	{
		int stop = 0;
		KeyCmdList->Items->Clear();
		for(stop = fKeyStrokes->Count - 1, X = 0; X <= stop; X++)
		{
			/*# with KeyCmdList.Items.Add do */
			{
				auto with0 = KeyCmdList->Items->Add();
				if(FExtended)
					with0->Caption = ConvertCodeStringToExtended(EditorCommandToCodeString(fKeyStrokes->Items[X]->Command));
				else
					with0->Caption = EditorCommandToCodeString(fKeyStrokes->Items[X]->Command);
				if(fKeyStrokes->Items[X]->ShortCut == 0)
					with0->SubItems->Add(SYNS_ShortcutNone);
				else
				{
					if(fKeyStrokes->Items[X]->ShortCut2 == 0)
						with0->SubItems->Add(Menus::ShortCutToText(fKeyStrokes->Items[X]->ShortCut));
					else
						with0->SubItems->Add(Menus::ShortCutToText(fKeyStrokes->Items[X]->ShortCut)
	           + L" "
	           + Menus::ShortCutToText(fKeyStrokes->Items[X]->ShortCut2));
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
	Msg.MINMAXINFO->ptMinTrackSize = Point(300, 225);
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
			NewStroke = fKeyStrokes->Add();
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
	AForm = new TSynEditKeystrokeEditorForm(this, 0);
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
			OldShortcut = fKeyStrokes->Items[SelItem->Index]->ShortCut;
			OldShortcut2 = fKeyStrokes->Items[SelItem->Index]->ShortCut2;
			try
			{
				KeyLoc = ((TSynEditKeyStrokes*) fKeyStrokes->Items[SelItem->Index]->Collection)->FindShortcut2(AForm->Keystroke, AForm->Keystroke2);
				fKeyStrokes->Items[SelItem->Index]->Command = AForm->Command;
				fKeyStrokes->Items[SelItem->Index]->ShortCut = AForm->Keystroke;
				fKeyStrokes->Items[SelItem->Index]->ShortCut2 = AForm->Keystroke2;
			}
			catch(ESynKeyError*)
			{
				{
					if(FExtended)
						TmpCommand = ConvertCodeStringToExtended(EditorCommandToCodeString(((TSynEditKeyStrokes*) fKeyStrokes->Items[SelItem->Index]->Collection)->Items[KeyLoc]->Command));
					else
						TmpCommand = EditorCommandToCodeString(((TSynEditKeyStrokes*) fKeyStrokes->Items[SelItem->Index]->Collection)->Items[KeyLoc]->Command);
					result = MessageDlg(Format(SYNS_DuplicateShortcutMsg, ARRAYOFCONST((Menus::ShortCutToText(AForm->Keystroke), TmpCommand))), TMsgDlgType::mtError, Syneditkeycmdseditor__1, 0) == mrOk;
					fKeyStrokes->Items[SelItem->Index]->ShortCut = OldShortcut;
					fKeyStrokes->Items[SelItem->Index]->ShortCut2 = OldShortcut2;
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
	AForm = new TSynEditKeystrokeEditorForm(this, 0);
	/*# with AForm do */
	{
		auto with0 = AForm;
		try
		{
			with0->ExtendedString = this->ExtendedString;
			with0->Command = fKeyStrokes->Items[SelItem->Index]->Command;
			with0->Keystroke = fKeyStrokes->Items[SelItem->Index]->ShortCut;
			with0->Keystroke2 = fKeyStrokes->Items[SelItem->Index]->ShortCut2;
			if(EditKeyStroke())
			{
				KeyCmdList->Items->BeginUpdate();
				try
				{
					/*# with SelItem do */
					{
						auto with1 = SelItem;
						if(FExtended)
							with1->Caption = ConvertCodeStringToExtended(EditorCommandToCodeString(fKeyStrokes->Items[with1->Index]->Command));
						else
							with1->Caption = EditorCommandToCodeString(fKeyStrokes->Items[with1->Index]->Command);
						if(fKeyStrokes->Items[with1->Index]->ShortCut == 0)
							with1->SubItems->Strings[0] = SYNS_ShortcutNone;
						else
						{
							if(fKeyStrokes->Items[with1->Index]->ShortCut2 == 0)
								with1->SubItems->Strings[0] = Menus::ShortCutToText(fKeyStrokes->Items[with1->Index]->ShortCut);
							else
								with1->SubItems->Strings[0] = Menus::ShortCutToText(fKeyStrokes->Items[with1->Index]->ShortCut)
	           + L" "
	           + Menus::ShortCutToText(fKeyStrokes->Items[with1->Index]->ShortCut2);
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
	delete fKeyStrokes->Items[SelItem->Index];
	KeyCmdList->Items->Delete(SelItem->Index);
}

void __fastcall TSynEditKeystrokesEditorForm::btnClearClick(TObject* Sender)
{
	fKeyStrokes->Clear();
	KeyCmdList->Items->Clear();
}

void __fastcall TSynEditKeystrokesEditorForm::btnResetClick(TObject* Sender)
{
	fKeyStrokes->ResetDefaults();
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
