#include <vcl.h>
#pragma hdrstop

#include "SynEditOptionsDialog.h"
#include <System.Types.hpp>
#include "SynEditKeyConst.h"
#include "SynEditMiscProcs.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Syneditkeycmds;
using namespace Syneditkeyconst;
using namespace Syneditmiscclasses;
using namespace Syneditmiscprocs;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Types;
using namespace System::Uitypes;
using namespace Vcl::Comctrls;
using namespace Vcl::Controls;
using namespace Vcl::Dialogs;
using namespace Vcl::Extctrls;
using namespace Vcl::Forms;
using namespace Vcl::Graphics;
using namespace Vcl::Menus;
using namespace Vcl::Stdctrls;

#define Syneditoptionsdialog__0 (TSynEditorOptions() << eoAutoIndent << eoDragDropEditing << eoDropFiles << eoScrollPastEol << eoShowScrollHint << eoSmartTabs << eoAltSetsColumnMode << eoTabsToSpaces << eoTrimTrailingSpaces << eoKeepCaretX)
#define Syneditoptionsdialog__1 Syneditmiscclasses::THKInvalidKeys()
#define Syneditoptionsdialog__2 Syneditmiscclasses::THKModifiers()
#define Syneditoptionsdialog__3 Syneditmiscclasses::THKInvalidKeys()
#define Syneditoptionsdialog__4 Syneditmiscclasses::THKModifiers()



/* TSynEditOptionsDialog */

__fastcall TSynEditOptionsDialog::TSynEditOptionsDialog(TComponent* AOwner)
 : inherited(AOwner),
			FForm(new TfmEditorOptionsDialog(this, 0))
{
}

__fastcall TSynEditOptionsDialog::~TSynEditOptionsDialog()
{
	delete FForm;
	// inherited;
}

bool __fastcall TSynEditOptionsDialog::Execute(TSynEditorOptionsContainer* EditOptions)
{
	bool result = false;
	result = FForm->Execute(EditOptions);
	return result;
}

TSynEditorOptionsAllUserCommands __fastcall TSynEditOptionsDialog::GetUserCommands()
{
	TSynEditorOptionsAllUserCommands result;
	result = FForm->GetAllUserCommands;
	return result;
}

TSynEditorOptionsUserCommand __fastcall TSynEditOptionsDialog::GetUserCommandNames()
{
	TSynEditorOptionsUserCommand result;
	result = FForm->GetUserCommandNames;
	return result;
}

void __fastcall TSynEditOptionsDialog::SetUserCommands(const TSynEditorOptionsAllUserCommands Value)
{
	FForm->GetAllUserCommands = Value;
}

void __fastcall TSynEditOptionsDialog::SetUserCommandNames(const TSynEditorOptionsUserCommand Value)
{
	FForm->GetUserCommandNames = Value;
}

bool __fastcall TSynEditOptionsDialog::GetExtended()
{
	bool result = false;
	result = FForm->UseExtendedStrings;
	return result;
}

void __fastcall TSynEditOptionsDialog::SetExtended(bool Value)
{
	FForm->UseExtendedStrings = Value;
}

/* TSynEditorOptionsContainer */

void __fastcall TSynEditorOptionsContainer::Assign(TPersistent* Source)
{
	if(ASSIGNED(Source) && (ObjectIs(Source, TCustomSynEdit*)))
	{
		this->Font->Assign(((TCustomSynEdit*) Source)->Font);
		this->BookMarkOptions->Assign(((TCustomSynEdit*) Source)->BookMarkOptions);
		this->Gutter->Assign(((TCustomSynEdit*) Source)->Gutter);
		this->Keystrokes->Assign(((TCustomSynEdit*) Source)->Keystrokes);
		this->SelectedColor->Assign(((TCustomSynEdit*) Source)->SelectedColor);
		this->Color = ((TCustomSynEdit*) Source)->Color;
		this->Options = ((TCustomSynEdit*) Source)->Options;
		this->ExtraLineSpacing = ((TCustomSynEdit*) Source)->ExtraLineSpacing;
		this->HideSelection = ((TCustomSynEdit*) Source)->HideSelection;
		this->InsertCaret = ((TCustomSynEdit*) Source)->InsertCaret;
		this->OverwriteCaret = ((TCustomSynEdit*) Source)->OverwriteCaret;
		this->MaxUndo = ((TCustomSynEdit*) Source)->MaxUndo;
		this->RightEdge = ((TCustomSynEdit*) Source)->RightEdge;
		this->RightEdgeColor = ((TCustomSynEdit*) Source)->RightEdgeColor;
		this->TabWidth = ((TCustomSynEdit*) Source)->TabWidth;
		this->WantTabs = ((TCustomSynEdit*) Source)->WantTabs;
	}
	else
	inherited::Assign(Source);
}

void __fastcall TSynEditorOptionsContainer::AssignTo(TPersistent* Dest)
{
	if(ASSIGNED(Dest) && (ObjectIs(Dest, TCustomSynEdit*)))
	{
		((TCustomSynEdit*) Dest)->Font->Assign(this->Font);
		((TCustomSynEdit*) Dest)->BookMarkOptions->Assign(this->BookMarkOptions);
		((TCustomSynEdit*) Dest)->Gutter->Assign(this->Gutter);
		((TCustomSynEdit*) Dest)->Keystrokes->Assign(this->Keystrokes);
		((TCustomSynEdit*) Dest)->SelectedColor->Assign(this->SelectedColor);
		((TCustomSynEdit*) Dest)->Color = this->Color;
		((TCustomSynEdit*) Dest)->Options = this->Options;
		((TCustomSynEdit*) Dest)->ExtraLineSpacing = this->ExtraLineSpacing;
		((TCustomSynEdit*) Dest)->HideSelection = this->HideSelection;
		((TCustomSynEdit*) Dest)->InsertCaret = this->InsertCaret;
		((TCustomSynEdit*) Dest)->OverwriteCaret = this->OverwriteCaret;
		((TCustomSynEdit*) Dest)->MaxUndo = this->MaxUndo;
		((TCustomSynEdit*) Dest)->RightEdge = this->RightEdge;
		((TCustomSynEdit*) Dest)->RightEdgeColor = this->RightEdgeColor;
		((TCustomSynEdit*) Dest)->TabWidth = this->TabWidth;
		((TCustomSynEdit*) Dest)->WantTabs = this->WantTabs;
	}
	else
	inherited::AssignTo(Dest);
}

__fastcall TSynEditorOptionsContainer::TSynEditorOptionsContainer(TComponent* AOwner)
 : inherited(AOwner),
			FHideSelection(false),
			FWantTabs(false),
			FMaxUndo(0),
			fExtraLineSpacing(0),
			FTabWidth(0),
			FMaxScrollWidth(0),
			fRightEdge(0),
			FSelectedColor(nullptr),
			fRightEdgeColor((TColor) 0),
			FFont(nullptr),
			fBookMarks(nullptr),
			fOverwriteCaret(ctVerticalLine),
			fInsertCaret(ctVerticalLine),
			fKeyStrokes(nullptr),
			FSynGutter(nullptr),
			FColor((TColor) 0)
{
	fBookMarks = new TSynBookMarkOpt(this);
	fKeyStrokes = new TSynEditKeyStrokes(this);
	FSynGutter = new TSynGutter();
	FSynGutter->AssignableBands = false;
	FSelectedColor = new TSynSelectedColor();
	FSelectedColor->Foreground = clHighlightText;
	FSelectedColor->Background = clHighlight;
	FFont = new TFont();
	FFont->Name = DefaultFontName();
	FFont->Size = 8;
	Color = clWindow;
	Keystrokes->ResetDefaults();
	Options = Syneditoptionsdialog__0;
	ExtraLineSpacing = 0;
	HideSelection = false;
	InsertCaret = ctVerticalLine;
	OverwriteCaret = ctBlock;
	MaxScrollWidth = 1024;
	MaxUndo = 0;
	RightEdge = 80;
	RightEdgeColor = clSilver;
	TabWidth = 8;
	WantTabs = true;
}

__fastcall TSynEditorOptionsContainer::~TSynEditorOptionsContainer()
{
	delete fBookMarks;
	delete fKeyStrokes;
	delete FSynGutter;
	delete FSelectedColor;
	delete FFont;
	// inherited;
}

void __fastcall TSynEditorOptionsContainer::SetBookMarks(TSynBookMarkOpt* const Value)
{
	fBookMarks->Assign((TPersistent*) Value);
}

void __fastcall TSynEditorOptionsContainer::SetFont(TFont* const Value)
{
	FFont->Assign((TPersistent*) Value);
}

void __fastcall TSynEditorOptionsContainer::SetKeystrokes(TSynEditKeyStrokes* const Value)
{
	fKeyStrokes->Assign((TPersistent*) Value);
}

void __fastcall TSynEditorOptionsContainer::SetOptions(const TSynEditorOptions Value)
{
	fOptions = Value;
}

void __fastcall TSynEditorOptionsContainer::SetSynGutter(TSynGutter* const Value)
{
	FSynGutter->Assign((TPersistent*) Value);
}

/* TfmEditorOptionsDialog */

bool __fastcall TfmEditorOptionsDialog::Execute(TSynEditorOptionsContainer* EditOptions)
{
	bool result = false;
	if(EditOptions == nullptr)
	{
		result = false;
		return result;
	}
  //Assign the Containers
	FSynEdit = EditOptions;
  //Get Data
	GetData();
  //Show the form
	result = ShowModal() == System::Uitypes::mrOk;
  //PutData
	if(result)
		PutData();
	return result;
}

void __fastcall TfmEditorOptionsDialog::GetData()
{
	int i = 0;
	TListItem* Item = nullptr;
  //Gutter
	ckGutterVisible->Checked = FSynEdit->Gutter->Visible;
	ckGutterAutosize->Checked = FSynEdit->Gutter->AutoSize;
	ckGutterShowLineNumbers->Checked = FSynEdit->Gutter->ShowLineNumbers;
	ckGutterShowLeaderZeros->Checked = FSynEdit->Gutter->LeadingZeros;
	ckGutterStartAtZero->Checked = FSynEdit->Gutter->ZeroStart;
	cbGutterFont->Checked = FSynEdit->Gutter->UseFontStyle;
	pGutterColor->Color = FSynEdit->Gutter->Color;
	lblGutterFont->Font->Assign(FSynEdit->Gutter->Font);
	lblGutterFont->Caption = lblGutterFont->Font->Name + L" " + IntToStr(lblGutterFont->Font->Size) + L"pt";  
  //Right Edge
	eRightEdge->Text = IntToStr(FSynEdit->RightEdge);
	pRightEdgeColor->Color = FSynEdit->RightEdgeColor;
  //Line Spacing
	eLineSpacing->Text = IntToStr(FSynEdit->ExtraLineSpacing);
	eTabWidth->Text = IntToStr(FSynEdit->TabWidth);
  //Bookmarks
	ckBookmarkKeys->Checked = FSynEdit->BookMarkOptions->EnableKeys;
	ckBookmarkVisible->Checked = FSynEdit->BookMarkOptions->GlyphsVisible;
  //Font
	labFont->Font->Assign(FSynEdit->Font);
	labFont->Caption = labFont->Font->Name + L" " + IntToStr(labFont->Font->Size) + L"pt";
  //Options
	ckAutoIndent->Checked = FSynEdit->Options.Contains(eoAutoIndent);
	ckDragAndDropEditing->Checked = FSynEdit->Options.Contains(eoDragDropEditing);
	ckWantTabs->Checked = FSynEdit->WantTabs;
	ckSmartTabs->Checked = FSynEdit->Options.Contains(eoSmartTabs);
	ckAltSetsColumnMode->Checked = FSynEdit->Options.Contains(eoAltSetsColumnMode);
	ckHalfPageScroll->Checked = FSynEdit->Options.Contains(eoHalfPageScroll);
	ckScrollByOneLess->Checked = FSynEdit->Options.Contains(eoScrollByOneLess);
	ckScrollPastEOF->Checked = FSynEdit->Options.Contains(eoScrollPastEof);
	ckScrollPastEOL->Checked = FSynEdit->Options.Contains(eoScrollPastEol);
	ckShowScrollHint->Checked = FSynEdit->Options.Contains(eoShowScrollHint);
	ckTabsToSpaces->Checked = FSynEdit->Options.Contains(eoTabsToSpaces);
	ckTrimTrailingSpaces->Checked = FSynEdit->Options.Contains(eoTrimTrailingSpaces);
	ckKeepCaretX->Checked = FSynEdit->Options.Contains(eoKeepCaretX);
	ckSmartTabDelete->Checked = FSynEdit->Options.Contains(eoSmartTabDelete);
	ckRightMouseMoves->Checked = FSynEdit->Options.Contains(eoRightMouseMovesCursor);
	ckEnhanceHomeKey->Checked = FSynEdit->Options.Contains(eoEnhanceHomeKey);
	ckEnhanceEndKey->Checked = FSynEdit->Options.Contains(eoEnhanceEndKey);
	ckGroupUndo->Checked = FSynEdit->Options.Contains(eoGroupUndo);
	ckDisableScrollArrows->Checked = FSynEdit->Options.Contains(eoDisableScrollArrows);
	ckHideShowScrollbars->Checked = FSynEdit->Options.Contains(eoHideShowScrollbars);
	ckShowSpecialChars->Checked = FSynEdit->Options.Contains(eoShowSpecialChars);

  //Caret
	cInsertCaret->ItemIndex = int(FSynEdit->InsertCaret);
	cOverwriteCaret->ItemIndex = int(FSynEdit->OverwriteCaret);
	KeyList->Items->BeginUpdate();
	try
	{
		int stop = 0;
		KeyList->Items->Clear();
		for(stop = FSynEdit->Keystrokes->Count - 1, i = 0; i <= stop; i++)
		{
			Item = KeyList->Items->Add();
			FillInKeystrokeInfo(FSynEdit->Keystrokes->Items[i], Item);
			Item->Data = FSynEdit->Keystrokes->Items[i];
		}
		if(KeyList->Items->Count > 0)
			KeyList->Items->Item[0]->Selected = true;
	}
	__finally
	{
		KeyList->Items->EndUpdate();
	}
}

void __fastcall TfmEditorOptionsDialog::PutData()
{
	TSynEditorOptions vOptions;

	auto SetFlag = [&](TSynEditorOption aOption, bool AValue) -> void 
	{
		if(AValue)
			vOptions << aOption;
		else
			vOptions >> aOption;
	};
  //Gutter
	FSynEdit->Gutter->Visible = ckGutterVisible->Checked;
	FSynEdit->Gutter->AutoSize = ckGutterAutosize->Checked;
	FSynEdit->Gutter->ShowLineNumbers = ckGutterShowLineNumbers->Checked;
	FSynEdit->Gutter->LeadingZeros = ckGutterShowLeaderZeros->Checked;
	FSynEdit->Gutter->ZeroStart = ckGutterStartAtZero->Checked;
	FSynEdit->Gutter->Color = pGutterColor->Color;
	FSynEdit->Gutter->UseFontStyle = cbGutterFont->Checked;
	FSynEdit->Gutter->Font->Assign(lblGutterFont->Font);
  //Right Edge
	FSynEdit->RightEdge = StrToIntDef(eRightEdge->Text, 80);
	FSynEdit->RightEdgeColor = pRightEdgeColor->Color;
  //Line Spacing
	FSynEdit->ExtraLineSpacing = StrToIntDef(eLineSpacing->Text, 0);
	FSynEdit->TabWidth = StrToIntDef(eTabWidth->Text, 8);
  //Bookmarks
	FSynEdit->BookMarkOptions->EnableKeys = ckBookmarkKeys->Checked;
	FSynEdit->BookMarkOptions->GlyphsVisible = ckBookmarkVisible->Checked;
  //Font
	FSynEdit->Font->Assign(labFont->Font);
  //Options
	FSynEdit->WantTabs = ckWantTabs->Checked;
	vOptions = FSynEdit->Options; //Keep old values for unsupported options
	SetFlag(eoAutoIndent, ckAutoIndent->Checked);
	SetFlag(eoDragDropEditing, ckDragAndDropEditing->Checked);
	SetFlag(eoSmartTabs, ckSmartTabs->Checked);
	SetFlag(eoAltSetsColumnMode, ckAltSetsColumnMode->Checked);
	SetFlag(eoHalfPageScroll, ckHalfPageScroll->Checked);
	SetFlag(eoScrollByOneLess, ckScrollByOneLess->Checked);
	SetFlag(eoScrollPastEof, ckScrollPastEOF->Checked);
	SetFlag(eoScrollPastEol, ckScrollPastEOL->Checked);
	SetFlag(eoShowScrollHint, ckShowScrollHint->Checked);
	SetFlag(eoTabsToSpaces, ckTabsToSpaces->Checked);
	SetFlag(eoTrimTrailingSpaces, ckTrimTrailingSpaces->Checked);
	SetFlag(eoKeepCaretX, ckKeepCaretX->Checked);
	SetFlag(eoSmartTabDelete, ckSmartTabDelete->Checked);
	SetFlag(eoRightMouseMovesCursor, ckRightMouseMoves->Checked);
	SetFlag(eoEnhanceHomeKey, ckEnhanceHomeKey->Checked);
	SetFlag(eoEnhanceEndKey, ckEnhanceEndKey->Checked);
	SetFlag(eoGroupUndo, ckGroupUndo->Checked);
	SetFlag(eoDisableScrollArrows, ckDisableScrollArrows->Checked);
	SetFlag(eoHideShowScrollbars, ckHideShowScrollbars->Checked);
	SetFlag(eoShowSpecialChars, ckShowSpecialChars->Checked);
	FSynEdit->Options = vOptions;
  //Caret
	FSynEdit->InsertCaret = ((TSynEditCaretType) cInsertCaret->ItemIndex);
	FSynEdit->OverwriteCaret = ((TSynEditCaretType) cOverwriteCaret->ItemIndex);
}

TColor __fastcall TfmEditorOptionsDialog::GetColor(TMenuItem* Item)
{
	TColor result = (TColor) 0;
	if((Item->Tag == -1) || (Item->Tag > 24))
		result = clNone;
	else
		result = ((TColor) (((unsigned char) Item->Tag) | 0x80000000));
	return result;
}

void __fastcall TfmEditorOptionsDialog::PopupMenuClick(TObject* Sender)
{
	TColor C = (TColor) 0;
	C = GetColor(((TMenuItem*) Sender));
  //Set the color based on where it was "popped from"
	if(FPoppedFrom == cpGutter)
		pGutterColor->Color = C;
	else
	{
		if(FPoppedFrom == cpRightEdge)
			pRightEdgeColor->Color = C;
	}
}

void __fastcall TfmEditorOptionsDialog::FormCreate(TObject* Sender)
{
	int i = 0;
	TColor C = (TColor) 0;
	TBitmap* B = nullptr;
	KeyList->OnSelectItem = KeyListSelectItem;
	InChanging = false;
	B = new TBitmap();
	try
	{
		int stop = 0;
		B->Width = 16;
		B->Height = 16;
    //Loop through and create colored images
		for(stop = ColorPopup->Items->Count - 1, i = 0; i <= stop; i++)
		{
			if(ColorPopup->Items->Items[i]->Tag == -1)
				continue;
			C = GetColor(ColorPopup->Items->Items[i]);
			B->Canvas->Brush->Color = C;
			B->Canvas->Brush->Style = bsSolid;
			B->Canvas->Pen->Style = psSolid;
			B->Canvas->Pen->Color = clBlack;
			B->Canvas->Rectangle(0, 0, 16, 16);
			ImageList1->Add(B, nullptr);
			ColorPopup->Items->Items[i]->ImageIndex = ColorPopup->Items->Items[i]->Tag;
		}
	}
	__finally
	{
		delete B;
	}
	eKeyShort1 = new TSynHotKey(this);
	/*# with eKeyShort1 do */
	{
		auto with0 = eKeyShort1;
		with0->Parent = gbKeyStrokes;
		with0->Left = 120;
		with0->Top = 55;
		with0->Width = 185;
		with0->Height = 21;
		with0->HotKey = (TShortCut) 0;
		with0->InvalidKeys = Syneditoptionsdialog__1;
		with0->Modifiers = Syneditoptionsdialog__2;
		with0->TabOrder = (TTabOrder) 1;
	}
	eKeyShort2 = new TSynHotKey(this);
	/*# with eKeyShort2 do */
	{
		auto with1 = eKeyShort2;
		with1->Parent = gbKeyStrokes;
		with1->Left = 120;
		with1->Top = 87;
		with1->Width = 185;
		with1->Height = 21;
		with1->HotKey = (TShortCut) 0;
		with1->InvalidKeys = Syneditoptionsdialog__3;
		with1->Modifiers = Syneditoptionsdialog__4;
		with1->TabOrder = (TTabOrder) 2;
	}
}

void __fastcall TfmEditorOptionsDialog::pGutterColorClick(TObject* Sender)
{
	ColorDialog->Color = pGutterColor->Color;
	if(ColorDialog->Execute())
	{
		pGutterColor->Color = ColorDialog->Color;
	}
}

void __fastcall TfmEditorOptionsDialog::pRightEdgeColorClick(TObject* Sender)
{
	ColorDialog->Color = pRightEdgeColor->Color;
	if(ColorDialog->Execute())
	{
		pRightEdgeColor->Color = ColorDialog->Color;
	}
}

void __fastcall TfmEditorOptionsDialog::btnFontClick(TObject* Sender)
{
	FontDialog->Font->Assign(labFont->Font);
	if(FontDialog->Execute())
	{
		labFont->Font->Assign(FontDialog->Font);
		labFont->Caption = labFont->Font->Name;
		labFont->Caption = labFont->Font->Name + L" " + IntToStr(labFont->Font->Size) + L"pt";
	}
}

void __fastcall TfmEditorOptionsDialog::KeyListSelectItem(TObject* Sender, TListItem* Item, bool Selected)
{
	if(KeyList->Selected == nullptr)
		return;
	cKeyCommand->Text = KeyList->Selected->Caption;
	cKeyCommand->ItemIndex = cKeyCommand->Items->IndexOf(KeyList->Selected->Caption);
	eKeyShort1->HotKey = ((TSynEditKeyStroke*) KeyList->Selected->Data)->ShortCut;
	eKeyShort2->HotKey = ((TSynEditKeyStroke*) KeyList->Selected->Data)->ShortCut2;
	OldSelected = Item;
}

void __fastcall TfmEditorOptionsDialog::btnUpdateKeyClick(TObject* Sender)
{
	int cmd = 0;
/*    KeyLoc       : Integer;
    TmpCommand   : string;
    OldShortcut  : TShortcut;
    OldShortcut2 : TShortcut;
*/
	if((KeyList->Selected == nullptr) && (Sender != btnAddKey))
	{
		btnAddKey->Click();
		return;
	}
	if(KeyList->Selected == nullptr)
		return;
	if(cKeyCommand->ItemIndex < 0)
		return;
	cmd = (NativeInt) cKeyCommand->Items->Objects[cKeyCommand->ItemIndex];
	((TSynEditKeyStroke*) OldSelected->Data)->Command = (TSynEditorCommand) cmd;
	if(eKeyShort1->HotKey != 0)
		((TSynEditKeyStroke*) OldSelected->Data)->ShortCut = eKeyShort1->HotKey;
	if(eKeyShort2->HotKey != 0)
		((TSynEditKeyStroke*) OldSelected->Data)->ShortCut2 = eKeyShort2->HotKey;
	FillInKeystrokeInfo(((TSynEditKeyStroke*) OldSelected->Data), KeyList->Selected);
}

void __fastcall TfmEditorOptionsDialog::btnAddKeyClick(TObject* Sender)
{
	TListItem* Item = nullptr;
	if(cKeyCommand->ItemIndex < 0)
		return;
	Item = KeyList->Items->Add();
	Item->Data = FSynEdit->Keystrokes->Add();
	Item->Selected = true;
	btnUpdateKeyClick(btnAddKey);
}

void __fastcall TfmEditorOptionsDialog::btnRemKeyClick(TObject* Sender)
{
	if(KeyList->Selected == nullptr)
		return;
	delete ((TSynEditKeyStroke*) KeyList->Selected->Data);
	KeyList->Selected->Delete();
}

void __fastcall TfmEditorOptionsDialog::EditStrCallback(const String s)
{

  //Add the Item
	if(FExtended)
		cKeyCommand->Items->AddObject(s, ((TObject*) ConvertExtendedToCommand(s)));
	else
		cKeyCommand->Items->AddObject(s, ((TObject*) ConvertCodeStringToCommand(s)));
}

void __fastcall TfmEditorOptionsDialog::FormShow(TObject* Sender)
{
	TStringList* Commands = nullptr;
	int i = 0;
//We need to do this now because it will not have been assigned when
//create occurs
	cKeyCommand->Items->Clear();
  //Start the callback to add the strings
	if(FExtended)
		GetEditorCommandExtended(EditStrCallback);
	else
		GetEditorCommandValues(EditStrCallback);
  //Now add in the user defined ones if they have any
	if(ASSIGNED(FAllUserCommands))
	{
		Commands = new TStringList();
		try
		{
			int stop = 0;
			FAllUserCommands(Commands);
			for(stop = Commands->Count - 1, i = 0; i <= stop; i++)
			{
				if(Commands->Objects[i] != nullptr)
					cKeyCommand->Items->AddObject(Commands->Strings[i], Commands->Objects[i]);
			}
		}
		__finally
		{
			delete Commands;
		}
	}
	PageControl1->ActivePage = PageControl1->pages[0];
}

void __fastcall TfmEditorOptionsDialog::KeyListEditing(TObject* Sender, TListItem* Item, bool& AllowEdit)
{
	AllowEdit = false;
}

void __fastcall TfmEditorOptionsDialog::btnOKClick(TObject* Sender)
{
	btnUpdateKey->Click();
	ModalResult = (TModalResult) System::Uitypes::mrOk;
}

void __fastcall TfmEditorOptionsDialog::btnGutterFontClick(TObject* Sender)
{
	FontDialog->Font->Assign(lblGutterFont->Font);
	if(FontDialog->Execute())
	{
		lblGutterFont->Font->Assign(FontDialog->Font);
		lblGutterFont->Caption = lblGutterFont->Font->Name + L" " + IntToStr(lblGutterFont->Font->Size) + L"pt";
	}
}

void __fastcall TfmEditorOptionsDialog::cbGutterFontClick(TObject* Sender)
{
	lblGutterFont->Enabled = cbGutterFont->Checked;
	btnGutterFont->Enabled = cbGutterFont->Checked;
}

void __fastcall TfmEditorOptionsDialog::btnRightEdgeMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TPoint P = {};
	FPoppedFrom = cpRightEdge;
	P = pRightEdgeColor->ClientToScreen(Point(-1, pRightEdgeColor->Height - 1));
	btnRightEdge->BevelOuter = bvLowered;
	ColorPopup->Popup(P.X, P.Y);
	btnRightEdge->BevelOuter = bvNone;
}

void __fastcall TfmEditorOptionsDialog::btnGutterColorMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TPoint P = {};
	FPoppedFrom = cpGutter;
	P = pGutterColor->ClientToScreen(Point(-1, pGutterColor->Height - 1));
	btnGutterColor->BevelOuter = bvLowered;
	ColorPopup->Popup(P.X, P.Y);
	btnGutterColor->BevelOuter = bvNone;
}

void __fastcall TfmEditorOptionsDialog::FillInKeystrokeInfo(TSynEditKeyStroke* AKey, TListItem* AItem)
{
	String TmpString;
	/*# with AKey do */
	{
		auto with0 = AKey;
		if(with0->Command >= ecUserFirst)
		{
			TmpString = L"User Command";
			if(ASSIGNED(GetUserCommandNames))
				GetUserCommandNames((int) with0->Command, TmpString);
		}
		else
		{
			if(FExtended)
				TmpString = ConvertCodeStringToExtended(EditorCommandToCodeString(with0->Command));
			else
				TmpString = EditorCommandToCodeString(with0->Command);
		}
		AItem->Caption = TmpString;
		AItem->SubItems->Clear();
		TmpString = L"";
		if(with0->ShortCut != 0)
			TmpString = ShortCutToText(with0->ShortCut);
		if((TmpString != L"") && (with0->ShortCut2 != 0))
			TmpString = TmpString + L" " + ShortCutToText(with0->ShortCut2);
		AItem->SubItems->Add(TmpString);
	}
}

void __fastcall TfmEditorOptionsDialog::cKeyCommandKeyUp(TObject* Sender, WORD& key, TShiftState Shift)
{
	if(key == SYNEDIT_RETURN)
		btnUpdateKey->Click();
}

void __fastcall TfmEditorOptionsDialog::KeyListChanging(TObject* Sender, TListItem* Item, TItemChange Change, bool& AllowChange)
{

//make sure that it's saved.
	if(InChanging)
		return;
	InChanging = true;
	if(Visible)
	{
		if((Item == OldSelected) && ((Item->Caption != cKeyCommand->Text) || (((TSynEditKeyStroke*) Item->Data)->ShortCut != eKeyShort1->HotKey) || (((TSynEditKeyStroke*) Item->Data)->ShortCut2 != eKeyShort2->HotKey)))
		{
			btnUpdateKeyClick(btnUpdateKey);
		}
	}
	InChanging = false;
}

__fastcall TfmEditorOptionsDialog::TfmEditorOptionsDialog(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	PageControl1(nullptr),
	btnOK(nullptr),
	btnCancel(nullptr),
	Display(nullptr),
	ColorDialog(nullptr),
	ColorPopup(nullptr),
	None1(nullptr),
	Scrollbar1(nullptr),
	ActiveCaption1(nullptr),
	Background1(nullptr),
	InactiveCaption1(nullptr),
	Menu1(nullptr),
	Window1(nullptr),
	WindowFrame1(nullptr),
	Menu2(nullptr),
	WindowText1(nullptr),
	CaptionText1(nullptr),
	ActiveBorder1(nullptr),
	InactiveBorder1(nullptr),
	ApplicationWorkspace1(nullptr),
	Highlight1(nullptr),
	HighlightText1(nullptr),
	ButtonFace1(nullptr),
	ButtonShadow1(nullptr),
	GrayText1(nullptr),
	ButtonText1(nullptr),
	InactiveCaptionText1(nullptr),
	Highlight2(nullptr),
	N3dDarkShadow1(nullptr),
	N3DLight1(nullptr),
	InfoTipText1(nullptr),
	InfoTipBackground1(nullptr),
	ImageList1(nullptr),
	Options(nullptr),
	Keystrokes(nullptr),
	gbBookmarks(nullptr),
	ckBookmarkKeys(nullptr),
	ckBookmarkVisible(nullptr),
	gbLineSpacing(nullptr),
	eLineSpacing(nullptr),
	gbGutter(nullptr),
	Label1(nullptr),
	ckGutterAutosize(nullptr),
	ckGutterShowLineNumbers(nullptr),
	ckGutterShowLeaderZeros(nullptr),
	ckGutterStartAtZero(nullptr),
	ckGutterVisible(nullptr),
	gbRightEdge(nullptr),
	Label3(nullptr),
	pRightEdgeBack(nullptr),
	eRightEdge(nullptr),
	gbEditorFont(nullptr),
	btnFont(nullptr),
	gbOptions(nullptr),
	ckAutoIndent(nullptr),
	ckDragAndDropEditing(nullptr),
	ckHalfPageScroll(nullptr),
	ckEnhanceEndKey(nullptr),
	ckScrollByOneLess(nullptr),
	ckScrollPastEOF(nullptr),
	ckScrollPastEOL(nullptr),
	ckShowScrollHint(nullptr),
	ckSmartTabs(nullptr),
	ckTabsToSpaces(nullptr),
	ckTrimTrailingSpaces(nullptr),
	ckWantTabs(nullptr),
	gbCaret(nullptr),
	cInsertCaret(nullptr),
	Label2(nullptr),
	Label4(nullptr),
	cOverwriteCaret(nullptr),
	Panel3(nullptr),
	labFont(nullptr),
	FontDialog(nullptr),
	btnAddKey(nullptr),
	btnRemKey(nullptr),
	gbKeyStrokes(nullptr),
	Label5(nullptr),
	Label6(nullptr),
	Label7(nullptr),
	cKeyCommand(nullptr),
	btnUpdateKey(nullptr),
	ckAltSetsColumnMode(nullptr),
	ckKeepCaretX(nullptr),
	eTabWidth(nullptr),
	pRightEdgeColor(nullptr),
	Label8(nullptr),
	Label9(nullptr),
	Label10(nullptr),
	cbGutterFont(nullptr),
	btnGutterFont(nullptr),
	btnRightEdge(nullptr),
	Image1(nullptr),
	pGutterBack(nullptr),
	pGutterColor(nullptr),
	btnGutterColor(nullptr),
	Image2(nullptr),
	ckScrollHintFollows(nullptr),
	ckGroupUndo(nullptr),
	ckSmartTabDelete(nullptr),
	ckRightMouseMoves(nullptr),
	pnlGutterFontDisplay(nullptr),
	lblGutterFont(nullptr),
	ckEnhanceHomeKey(nullptr),
	pnlCommands(nullptr),
	KeyList(nullptr),
	ckHideShowScrollbars(nullptr),
	ckDisableScrollArrows(nullptr),
	ckShowSpecialChars(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Left = 580;
	Top = 154;
	BorderStyle = bsDialog;
	Caption = L"Editor Options";
	ClientHeight = 394;
	ClientWidth = 369;
	Color = clBtnFace;
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = clWindowText;
	Font->Height = -11;
	Font->Name = L"MS Sans Serif";
	Font->Style = (TFontStyles());
	Position = poScreenCenter;
	OnCreate = FormCreate;
	OnShow = FormShow;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	PageControl1 = new TPageControl(this);
	PageControl1->Parent = this;
	PageControl1->Left = 6;
	PageControl1->Top = 8;
	PageControl1->Width = 355;
	PageControl1->Height = 345;
	PageControl1->TabOrder = 0;
	Display = new TTabSheet(PageControl1);
	Display->Parent = PageControl1;
	Display->PageControl = PageControl1;
	Display->Caption = L"Display";
	gbRightEdge = new TGroupBox(Display);
	gbRightEdge->Parent = Display;
	gbRightEdge->Left = 8;
	gbRightEdge->Top = 136;
	gbRightEdge->Width = 159;
	gbRightEdge->Height = 88;
	gbRightEdge->Caption = L"Right Edge";
	gbRightEdge->TabOrder = 1;
	Label3 = new TLabel(gbRightEdge);
	Label3->Parent = gbRightEdge;
	Label3->Left = 9;
	Label3->Top = 56;
	Label3->Width = 54;
	Label3->Height = 13;
	Label3->Caption = L"Edge color:";
	Label10 = new TLabel(gbRightEdge);
	Label10->Parent = gbRightEdge;
	Label10->Left = 9;
	Label10->Top = 26;
	Label10->Width = 66;
	Label10->Height = 13;
	Label10->Caption = L"Edge Column:";
	pRightEdgeBack = new TPanel(gbRightEdge);
	pRightEdgeBack->Parent = gbRightEdge;
	pRightEdgeBack->Left = 80;
	pRightEdgeBack->Top = 54;
	pRightEdgeBack->Width = 52;
	pRightEdgeBack->Height = 21;
	pRightEdgeBack->BorderWidth = 1;
	pRightEdgeBack->TabOrder = 1;
	pRightEdgeColor = new TPanel(pRightEdgeBack);
	pRightEdgeColor->Parent = pRightEdgeBack;
	pRightEdgeColor->Left = 2;
	pRightEdgeColor->Top = 2;
	pRightEdgeColor->Width = 38;
	pRightEdgeColor->Height = 17;
	pRightEdgeColor->Align = alClient;
	pRightEdgeColor->BevelOuter = bvLowered;
	pRightEdgeColor->Color = clGray;
	pRightEdgeColor->TabOrder = 0;
	pRightEdgeColor->OnClick = pRightEdgeColorClick;
	btnRightEdge = new TPanel(pRightEdgeBack);
	btnRightEdge->Parent = pRightEdgeBack;
	btnRightEdge->Left = 40;
	btnRightEdge->Top = 2;
	btnRightEdge->Width = 10;
	btnRightEdge->Height = 17;
	btnRightEdge->Align = alRight;
	btnRightEdge->BevelOuter = bvNone;
	btnRightEdge->TabOrder = 1;
	btnRightEdge->OnMouseDown = btnRightEdgeMouseDown;
	Image1 = new TImage(btnRightEdge);
	Image1->Parent = btnRightEdge;
	Image1->Left = 3;
	Image1->Top = 6;
	Image1->Width = 5;
	Image1->Height = 5;
	AssignTPictureData(Image1, {
					0x07,0x54,0x42,0x69,0x74,0x6D,0x61,0x70,0x8A,0x00
					,0x00,0x00,0x42,0x4D,0x8A,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x76,0x00,0x00,0x00,0x28,0x00,0x00,0x00
					,0x05,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x01,0x00
					,0x04,0x00,0x00,0x00,0x00,0x00,0x14,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00
					,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x00,0x80
					,0x80,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x80,0x00
					,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0xC0,0xC0
					,0xC0,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00
					,0x00,0xFF,0xFF,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00
					,0xFF,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xFF,0x00
					,0xDD,0xDD,0xD0,0x00,0xDD,0x0D,0xD0,0x00,0xD0,0x00
					,0xD0,0x00,0x00,0x00,0x00,0x00,0xDD,0xDD,0xD0,0x00
					
					});
	Image1->Transparent = true;
	Image1->OnMouseDown = btnRightEdgeMouseDown;
	eRightEdge = new TEdit(gbRightEdge);
	eRightEdge->Parent = gbRightEdge;
	eRightEdge->Left = 80;
	eRightEdge->Top = 23;
	eRightEdge->Width = 51;
	eRightEdge->Height = 21;
	eRightEdge->TabOrder = 0;
	eRightEdge->Text = L"0";
	gbGutter = new TGroupBox(Display);
	gbGutter->Parent = Display;
	gbGutter->Left = 8;
	gbGutter->Top = 8;
	gbGutter->Width = 330;
	gbGutter->Height = 121;
	gbGutter->Caption = L"Gutter";
	gbGutter->TabOrder = 0;
	Label1 = new TLabel(gbGutter);
	Label1->Parent = gbGutter;
	Label1->Left = 176;
	Label1->Top = 89;
	Label1->Width = 58;
	Label1->Height = 13;
	Label1->Caption = L"Gutter color:";
	ckGutterAutosize = new TCheckBox(gbGutter);
	ckGutterAutosize->Parent = gbGutter;
	ckGutterAutosize->Left = 9;
	ckGutterAutosize->Top = 37;
	ckGutterAutosize->Width = 120;
	ckGutterAutosize->Height = 17;
	ckGutterAutosize->Caption = L"Autosize";
	ckGutterAutosize->TabOrder = 1;
	ckGutterShowLineNumbers = new TCheckBox(gbGutter);
	ckGutterShowLineNumbers->Parent = gbGutter;
	ckGutterShowLineNumbers->Left = 9;
	ckGutterShowLineNumbers->Top = 56;
	ckGutterShowLineNumbers->Width = 120;
	ckGutterShowLineNumbers->Height = 17;
	ckGutterShowLineNumbers->Caption = L"Show line numbers";
	ckGutterShowLineNumbers->TabOrder = 2;
	ckGutterShowLeaderZeros = new TCheckBox(gbGutter);
	ckGutterShowLeaderZeros->Parent = gbGutter;
	ckGutterShowLeaderZeros->Left = 9;
	ckGutterShowLeaderZeros->Top = 94;
	ckGutterShowLeaderZeros->Width = 120;
	ckGutterShowLeaderZeros->Height = 17;
	ckGutterShowLeaderZeros->Caption = L"Show leading zeros";
	ckGutterShowLeaderZeros->TabOrder = 4;
	ckGutterStartAtZero = new TCheckBox(gbGutter);
	ckGutterStartAtZero->Parent = gbGutter;
	ckGutterStartAtZero->Left = 9;
	ckGutterStartAtZero->Top = 75;
	ckGutterStartAtZero->Width = 120;
	ckGutterStartAtZero->Height = 17;
	ckGutterStartAtZero->Caption = L"Start at zero";
	ckGutterStartAtZero->TabOrder = 3;
	ckGutterVisible = new TCheckBox(gbGutter);
	ckGutterVisible->Parent = gbGutter;
	ckGutterVisible->Left = 9;
	ckGutterVisible->Top = 18;
	ckGutterVisible->Width = 120;
	ckGutterVisible->Height = 17;
	ckGutterVisible->Caption = L"Visible";
	ckGutterVisible->Checked = true;
	ckGutterVisible->State = cbChecked;
	ckGutterVisible->TabOrder = 0;
	cbGutterFont = new TCheckBox(gbGutter);
	cbGutterFont->Parent = gbGutter;
	cbGutterFont->Left = 176;
	cbGutterFont->Top = 18;
	cbGutterFont->Width = 120;
	cbGutterFont->Height = 17;
	cbGutterFont->Caption = L"Use Gutter Font";
	cbGutterFont->TabOrder = 5;
	cbGutterFont->OnClick = cbGutterFontClick;
	btnGutterFont = new TButton(gbGutter);
	btnGutterFont->Parent = gbGutter;
	btnGutterFont->Left = 282;
	btnGutterFont->Top = 13;
	btnGutterFont->Width = 40;
	btnGutterFont->Height = 25;
	btnGutterFont->Caption = L"Font";
	btnGutterFont->TabOrder = 6;
	btnGutterFont->OnClick = btnGutterFontClick;
	pGutterBack = new TPanel(gbGutter);
	pGutterBack->Parent = gbGutter;
	pGutterBack->Left = 252;
	pGutterBack->Top = 85;
	pGutterBack->Width = 52;
	pGutterBack->Height = 21;
	pGutterBack->BorderWidth = 1;
	pGutterBack->TabOrder = 8;
	pGutterColor = new TPanel(pGutterBack);
	pGutterColor->Parent = pGutterBack;
	pGutterColor->Left = 2;
	pGutterColor->Top = 2;
	pGutterColor->Width = 38;
	pGutterColor->Height = 17;
	pGutterColor->Align = alClient;
	pGutterColor->BevelOuter = bvLowered;
	pGutterColor->Color = clGray;
	pGutterColor->TabOrder = 0;
	pGutterColor->OnClick = pGutterColorClick;
	btnGutterColor = new TPanel(pGutterBack);
	btnGutterColor->Parent = pGutterBack;
	btnGutterColor->Left = 40;
	btnGutterColor->Top = 2;
	btnGutterColor->Width = 10;
	btnGutterColor->Height = 17;
	btnGutterColor->Align = alRight;
	btnGutterColor->BevelOuter = bvNone;
	btnGutterColor->TabOrder = 1;
	btnGutterColor->OnMouseDown = btnGutterColorMouseDown;
	Image2 = new TImage(btnGutterColor);
	Image2->Parent = btnGutterColor;
	Image2->Left = 3;
	Image2->Top = 6;
	Image2->Width = 5;
	Image2->Height = 5;
	AssignTPictureData(Image2, {
					0x07,0x54,0x42,0x69,0x74,0x6D,0x61,0x70,0x8A,0x00
					,0x00,0x00,0x42,0x4D,0x8A,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x76,0x00,0x00,0x00,0x28,0x00,0x00,0x00
					,0x05,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x01,0x00
					,0x04,0x00,0x00,0x00,0x00,0x00,0x14,0x00,0x00,0x00
					,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00
					,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00
					,0x00,0x00,0x80,0x00,0x00,0x80,0x00,0x00,0x00,0x80
					,0x80,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x80,0x00
					,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0xC0,0xC0
					,0xC0,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00
					,0x00,0xFF,0xFF,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00
					,0xFF,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xFF,0x00
					,0xDD,0xDD,0xD0,0x00,0xDD,0x0D,0xD0,0x00,0xD0,0x00
					,0xD0,0x00,0x00,0x00,0x00,0x00,0xDD,0xDD,0xD0,0x00
					
					});
	Image2->Transparent = true;
	Image2->OnMouseDown = btnGutterColorMouseDown;
	pnlGutterFontDisplay = new TPanel(gbGutter);
	pnlGutterFontDisplay->Parent = gbGutter;
	pnlGutterFontDisplay->Left = 176;
	pnlGutterFontDisplay->Top = 40;
	pnlGutterFontDisplay->Width = 145;
	pnlGutterFontDisplay->Height = 33;
	pnlGutterFontDisplay->BevelOuter = bvNone;
	pnlGutterFontDisplay->TabOrder = 7;
	lblGutterFont = new TLabel(pnlGutterFontDisplay);
	lblGutterFont->Parent = pnlGutterFontDisplay;
	lblGutterFont->Left = 19;
	lblGutterFont->Top = 9;
	lblGutterFont->Width = 105;
	lblGutterFont->Height = 14;
	lblGutterFont->Caption = L"Courier New 8pt";
	lblGutterFont->Font->Charset = DEFAULT_CHARSET;
	lblGutterFont->Font->Color = clWindowText;
	lblGutterFont->Font->Height = -11;
	lblGutterFont->Font->Name = L"Courier New";
	lblGutterFont->Font->Style = (TFontStyles());
	lblGutterFont->ParentFont = false;
	gbBookmarks = new TGroupBox(Display);
	gbBookmarks->Parent = Display;
	gbBookmarks->Left = 8;
	gbBookmarks->Top = 232;
	gbBookmarks->Width = 159;
	gbBookmarks->Height = 79;
	gbBookmarks->Caption = L"Bookmarks";
	gbBookmarks->TabOrder = 3;
	ckBookmarkKeys = new TCheckBox(gbBookmarks);
	ckBookmarkKeys->Parent = gbBookmarks;
	ckBookmarkKeys->Left = 9;
	ckBookmarkKeys->Top = 24;
	ckBookmarkKeys->Width = 97;
	ckBookmarkKeys->Height = 17;
	ckBookmarkKeys->Caption = L"Bookmark keys";
	ckBookmarkKeys->TabOrder = 0;
	ckBookmarkVisible = new TCheckBox(gbBookmarks);
	ckBookmarkVisible->Parent = gbBookmarks;
	ckBookmarkVisible->Left = 9;
	ckBookmarkVisible->Top = 48;
	ckBookmarkVisible->Width = 121;
	ckBookmarkVisible->Height = 17;
	ckBookmarkVisible->Caption = L"Bookmarks visible";
	ckBookmarkVisible->TabOrder = 1;
	gbEditorFont = new TGroupBox(Display);
	gbEditorFont->Parent = Display;
	gbEditorFont->Left = 180;
	gbEditorFont->Top = 232;
	gbEditorFont->Width = 159;
	gbEditorFont->Height = 79;
	gbEditorFont->Caption = L"Editor Font";
	gbEditorFont->TabOrder = 4;
	btnFont = new TButton(gbEditorFont);
	btnFont->Parent = gbEditorFont;
	btnFont->Left = 64;
	btnFont->Top = 49;
	btnFont->Width = 84;
	btnFont->Height = 25;
	btnFont->Caption = L"Font";
	btnFont->TabOrder = 0;
	btnFont->OnClick = btnFontClick;
	Panel3 = new TPanel(gbEditorFont);
	Panel3->Parent = gbEditorFont;
	Panel3->Left = 8;
	Panel3->Top = 19;
	Panel3->Width = 143;
	Panel3->Height = 30;
	Panel3->BevelOuter = bvNone;
	Panel3->TabOrder = 1;
	labFont = new TLabel(Panel3);
	labFont->Parent = Panel3;
	labFont->Left = 2;
	labFont->Top = 1;
	labFont->Width = 128;
	labFont->Height = 16;
	labFont->Caption = L"Courier New 10pt";
	labFont->Font->Charset = DEFAULT_CHARSET;
	labFont->Font->Color = clWindowText;
	labFont->Font->Height = -13;
	labFont->Font->Name = L"Courier New";
	labFont->Font->Style = (TFontStyles());
	labFont->ParentFont = false;
	gbLineSpacing = new TGroupBox(Display);
	gbLineSpacing->Parent = Display;
	gbLineSpacing->Left = 180;
	gbLineSpacing->Top = 136;
	gbLineSpacing->Width = 159;
	gbLineSpacing->Height = 88;
	gbLineSpacing->Caption = L"Line spacing / Tab spacing";
	gbLineSpacing->TabOrder = 2;
	Label8 = new TLabel(gbLineSpacing);
	Label8->Parent = gbLineSpacing;
	Label8->Left = 9;
	Label8->Top = 27;
	Label8->Width = 55;
	Label8->Height = 13;
	Label8->Caption = L"Extra Lines:";
	Label9 = new TLabel(gbLineSpacing);
	Label9->Parent = gbLineSpacing;
	Label9->Left = 9;
	Label9->Top = 56;
	Label9->Width = 53;
	Label9->Height = 13;
	Label9->Caption = L"Tab Width:";
	eLineSpacing = new TEdit(gbLineSpacing);
	eLineSpacing->Parent = gbLineSpacing;
	eLineSpacing->Left = 80;
	eLineSpacing->Top = 23;
	eLineSpacing->Width = 52;
	eLineSpacing->Height = 21;
	eLineSpacing->TabOrder = 0;
	eLineSpacing->Text = L"0";
	eTabWidth = new TEdit(gbLineSpacing);
	eTabWidth->Parent = gbLineSpacing;
	eTabWidth->Left = 80;
	eTabWidth->Top = 53;
	eTabWidth->Width = 52;
	eTabWidth->Height = 21;
	eTabWidth->TabOrder = 1;
	eTabWidth->Text = L"8";
	Options = new TTabSheet(PageControl1);
	Options->Parent = PageControl1;
	Options->PageControl = PageControl1;
	Options->Caption = L"Options";
	gbOptions = new TGroupBox(Options);
	gbOptions->Parent = Options;
	gbOptions->Left = 8;
	gbOptions->Top = 0;
	gbOptions->Width = 330;
	gbOptions->Height = 247;
	gbOptions->Caption = L"Options";
	gbOptions->TabOrder = 0;
	ckAutoIndent = new TCheckBox(gbOptions);
	ckAutoIndent->Parent = gbOptions;
	ckAutoIndent->Left = 9;
	ckAutoIndent->Top = 15;
	ckAutoIndent->Width = 130;
	ckAutoIndent->Height = 17;
	ckAutoIndent->Hint = L"Will indent the caret on new lines with the same amount of leading white space as the preceding line";
	ckAutoIndent->Caption = L"Auto indent";
	ckAutoIndent->TabOrder = 0;
	ckDragAndDropEditing = new TCheckBox(gbOptions);
	ckDragAndDropEditing->Parent = gbOptions;
	ckDragAndDropEditing->Left = 9;
	ckDragAndDropEditing->Top = 34;
	ckDragAndDropEditing->Width = 130;
	ckDragAndDropEditing->Height = 17;
	ckDragAndDropEditing->Hint = L"Allows you to select a block of text and drag it within the document to another location";
	ckDragAndDropEditing->Caption = L"Drag and drop editing";
	ckDragAndDropEditing->TabOrder = 1;
	ckHalfPageScroll = new TCheckBox(gbOptions);
	ckHalfPageScroll->Parent = gbOptions;
	ckHalfPageScroll->Left = 176;
	ckHalfPageScroll->Top = 15;
	ckHalfPageScroll->Width = 130;
	ckHalfPageScroll->Height = 17;
	ckHalfPageScroll->Hint = L"When scrolling with page-up and page-down commands, only scroll a half page at a time";
	ckHalfPageScroll->Caption = L"Half page scroll";
	ckHalfPageScroll->TabOrder = 11;
	ckEnhanceEndKey = new TCheckBox(gbOptions);
	ckEnhanceEndKey->Parent = gbOptions;
	ckEnhanceEndKey->Left = 9;
	ckEnhanceEndKey->Top = 167;
	ckEnhanceEndKey->Width = 130;
	ckEnhanceEndKey->Height = 17;
	ckEnhanceEndKey->Hint = L"Makes it so the caret is never visible";
	ckEnhanceEndKey->Caption = L"Enhance End Key";
	ckEnhanceEndKey->TabOrder = 8;
	ckScrollByOneLess = new TCheckBox(gbOptions);
	ckScrollByOneLess->Parent = gbOptions;
	ckScrollByOneLess->Left = 176;
	ckScrollByOneLess->Top = 34;
	ckScrollByOneLess->Width = 130;
	ckScrollByOneLess->Height = 17;
	ckScrollByOneLess->Hint = L"Forces scrolling to be one less";
	ckScrollByOneLess->Caption = L"Scroll by one less";
	ckScrollByOneLess->TabOrder = 12;
	ckScrollPastEOF = new TCheckBox(gbOptions);
	ckScrollPastEOF->Parent = gbOptions;
	ckScrollPastEOF->Left = 176;
	ckScrollPastEOF->Top = 53;
	ckScrollPastEOF->Width = 130;
	ckScrollPastEOF->Height = 17;
	ckScrollPastEOF->Hint = L"Allows the cursor to go past the end of file marker";
	ckScrollPastEOF->Caption = L"Scroll past end of file";
	ckScrollPastEOF->TabOrder = 13;
	ckScrollPastEOL = new TCheckBox(gbOptions);
	ckScrollPastEOL->Parent = gbOptions;
	ckScrollPastEOL->Left = 176;
	ckScrollPastEOL->Top = 72;
	ckScrollPastEOL->Width = 130;
	ckScrollPastEOL->Height = 17;
	ckScrollPastEOL->Hint = L"Allows the cursor to go past the last character into the white space at the end of a line";
	ckScrollPastEOL->Caption = L"Scroll past end of line";
	ckScrollPastEOL->TabOrder = 14;
	ckShowScrollHint = new TCheckBox(gbOptions);
	ckShowScrollHint->Parent = gbOptions;
	ckShowScrollHint->Left = 176;
	ckShowScrollHint->Top = 91;
	ckShowScrollHint->Width = 130;
	ckShowScrollHint->Height = 17;
	ckShowScrollHint->Hint = L"Shows a hint of the visible line numbers when scrolling vertically";
	ckShowScrollHint->Caption = L"Show scroll hint";
	ckShowScrollHint->TabOrder = 15;
	ckSmartTabs = new TCheckBox(gbOptions);
	ckSmartTabs->Parent = gbOptions;
	ckSmartTabs->Left = 9;
	ckSmartTabs->Top = 110;
	ckSmartTabs->Width = 130;
	ckSmartTabs->Height = 17;
	ckSmartTabs->Hint = L"When tabbing, the cursor will go to the next non-white space character of the previous line";
	ckSmartTabs->Caption = L"Smart tabs";
	ckSmartTabs->TabOrder = 5;
	ckTabsToSpaces = new TCheckBox(gbOptions);
	ckTabsToSpaces->Parent = gbOptions;
	ckTabsToSpaces->Left = 176;
	ckTabsToSpaces->Top = 129;
	ckTabsToSpaces->Width = 130;
	ckTabsToSpaces->Height = 17;
	ckTabsToSpaces->Hint = L"Converts a tab character to the number of spaces in Tab Width";
	ckTabsToSpaces->Caption = L"Tabs to spaces";
	ckTabsToSpaces->TabOrder = 17;
	ckTrimTrailingSpaces = new TCheckBox(gbOptions);
	ckTrimTrailingSpaces->Parent = gbOptions;
	ckTrimTrailingSpaces->Left = 176;
	ckTrimTrailingSpaces->Top = 148;
	ckTrimTrailingSpaces->Width = 130;
	ckTrimTrailingSpaces->Height = 17;
	ckTrimTrailingSpaces->Hint = L"Spaces at the end of lines will be trimmed and not saved";
	ckTrimTrailingSpaces->Caption = L"Trim trailing spaces";
	ckTrimTrailingSpaces->TabOrder = 18;
	ckWantTabs = new TCheckBox(gbOptions);
	ckWantTabs->Parent = gbOptions;
	ckWantTabs->Left = 9;
	ckWantTabs->Top = 91;
	ckWantTabs->Width = 130;
	ckWantTabs->Height = 17;
	ckWantTabs->Hint = L"Let the editor accept tab characters instead of going to the next control";
	ckWantTabs->Caption = L"Want tabs";
	ckWantTabs->TabOrder = 4;
	ckAltSetsColumnMode = new TCheckBox(gbOptions);
	ckAltSetsColumnMode->Parent = gbOptions;
	ckAltSetsColumnMode->Left = 9;
	ckAltSetsColumnMode->Top = 53;
	ckAltSetsColumnMode->Width = 130;
	ckAltSetsColumnMode->Height = 17;
	ckAltSetsColumnMode->Hint = L"Holding down the Alt Key will put the selection mode into columnar format";
	ckAltSetsColumnMode->Caption = L"Alt sets column mode";
	ckAltSetsColumnMode->TabOrder = 2;
	ckKeepCaretX = new TCheckBox(gbOptions);
	ckKeepCaretX->Parent = gbOptions;
	ckKeepCaretX->Left = 9;
	ckKeepCaretX->Top = 72;
	ckKeepCaretX->Width = 130;
	ckKeepCaretX->Height = 17;
	ckKeepCaretX->Hint = L"When moving through lines the X position will always stay the same";
	ckKeepCaretX->Caption = L"Maintain caret column";
	ckKeepCaretX->TabOrder = 3;
	ckScrollHintFollows = new TCheckBox(gbOptions);
	ckScrollHintFollows->Parent = gbOptions;
	ckScrollHintFollows->Left = 176;
	ckScrollHintFollows->Top = 110;
	ckScrollHintFollows->Width = 152;
	ckScrollHintFollows->Height = 17;
	ckScrollHintFollows->Hint = L"The scroll hint follows the mouse when scrolling vertically";
	ckScrollHintFollows->Caption = L"Scroll hint follows mouse";
	ckScrollHintFollows->TabOrder = 16;
	ckGroupUndo = new TCheckBox(gbOptions);
	ckGroupUndo->Parent = gbOptions;
	ckGroupUndo->Left = 177;
	ckGroupUndo->Top = 167;
	ckGroupUndo->Width = 130;
	ckGroupUndo->Height = 17;
	ckGroupUndo->Hint = L"When undoing/redoing actions, handle all continous changes of the same kind in one call instead undoing/redoing each command separately";
	ckGroupUndo->Caption = L"Group undo";
	ckGroupUndo->TabOrder = 19;
	ckSmartTabDelete = new TCheckBox(gbOptions);
	ckSmartTabDelete->Parent = gbOptions;
	ckSmartTabDelete->Left = 9;
	ckSmartTabDelete->Top = 129;
	ckSmartTabDelete->Width = 130;
	ckSmartTabDelete->Height = 17;
	ckSmartTabDelete->Hint = L"similar to Smart Tabs, but when you delete characters";
	ckSmartTabDelete->Caption = L"Smart tab delete";
	ckSmartTabDelete->TabOrder = 6;
	ckRightMouseMoves = new TCheckBox(gbOptions);
	ckRightMouseMoves->Parent = gbOptions;
	ckRightMouseMoves->Left = 177;
	ckRightMouseMoves->Top = 186;
	ckRightMouseMoves->Width = 146;
	ckRightMouseMoves->Height = 17;
	ckRightMouseMoves->Hint = L"When clicking with the right mouse for a popup menu, move the cursor to that location";
	ckRightMouseMoves->Caption = L"Right mouse moves cursor";
	ckRightMouseMoves->TabOrder = 20;
	ckEnhanceHomeKey = new TCheckBox(gbOptions);
	ckEnhanceHomeKey->Parent = gbOptions;
	ckEnhanceHomeKey->Left = 9;
	ckEnhanceHomeKey->Top = 148;
	ckEnhanceHomeKey->Width = 146;
	ckEnhanceHomeKey->Height = 17;
	ckEnhanceHomeKey->Hint = L"enhances home key positioning, similar to visual studio";
	ckEnhanceHomeKey->Caption = L"Enhance Home Key";
	ckEnhanceHomeKey->TabOrder = 7;
	ckHideShowScrollbars = new TCheckBox(gbOptions);
	ckHideShowScrollbars->Parent = gbOptions;
	ckHideShowScrollbars->Left = 9;
	ckHideShowScrollbars->Top = 186;
	ckHideShowScrollbars->Width = 156;
	ckHideShowScrollbars->Height = 17;
	ckHideShowScrollbars->Hint = L"if enabled, then the scrollbars will only show when necessary.  If you have ScrollPastEOL, then it the horizontal bar will always be there (it uses MaxLength instead)";
	ckHideShowScrollbars->Caption = L"Hide scrollbars as necessary";
	ckHideShowScrollbars->TabOrder = 9;
	ckDisableScrollArrows = new TCheckBox(gbOptions);
	ckDisableScrollArrows->Parent = gbOptions;
	ckDisableScrollArrows->Left = 9;
	ckDisableScrollArrows->Top = 205;
	ckDisableScrollArrows->Width = 130;
	ckDisableScrollArrows->Height = 17;
	ckDisableScrollArrows->Hint = L"Disables the scroll bar arrow buttons when you can\x27" L"t scroll in that direction any more";
	ckDisableScrollArrows->Caption = L"Disable scroll arrows";
	ckDisableScrollArrows->TabOrder = 10;
	ckShowSpecialChars = new TCheckBox(gbOptions);
	ckShowSpecialChars->Parent = gbOptions;
	ckShowSpecialChars->Left = 177;
	ckShowSpecialChars->Top = 205;
	ckShowSpecialChars->Width = 130;
	ckShowSpecialChars->Height = 17;
	ckShowSpecialChars->Hint = L"Shows linebreaks, spaces and tabs using special symbols";
	ckShowSpecialChars->Caption = L"Show special chars";
	ckShowSpecialChars->TabOrder = 21;
	gbCaret = new TGroupBox(Options);
	gbCaret->Parent = Options;
	gbCaret->Left = 8;
	gbCaret->Top = 249;
	gbCaret->Width = 330;
	gbCaret->Height = 62;
	gbCaret->Caption = L"Caret";
	gbCaret->TabOrder = 1;
	Label2 = new TLabel(gbCaret);
	Label2->Parent = gbCaret;
	Label2->Left = 16;
	Label2->Top = 17;
	Label2->Width = 56;
	Label2->Height = 13;
	Label2->Caption = L"Insert caret:";
	Label4 = new TLabel(gbCaret);
	Label4->Parent = gbCaret;
	Label4->Left = 16;
	Label4->Top = 41;
	Label4->Width = 75;
	Label4->Height = 13;
	Label4->Caption = L"Overwrite caret:";
	cInsertCaret = new TComboBox(gbCaret);
	cInsertCaret->Parent = gbCaret;
	cInsertCaret->Left = 120;
	cInsertCaret->Top = 13;
	cInsertCaret->Width = 186;
	cInsertCaret->Height = 21;
	cInsertCaret->Style = csDropDownList;
	cInsertCaret->TabOrder = 0;
	cInsertCaret->Items->Add(L"Vertical Line");
	cInsertCaret->Items->Add(L"Horizontal Line");
	cInsertCaret->Items->Add(L"Half Block");
	cInsertCaret->Items->Add(L"Block");
	cOverwriteCaret = new TComboBox(gbCaret);
	cOverwriteCaret->Parent = gbCaret;
	cOverwriteCaret->Left = 120;
	cOverwriteCaret->Top = 37;
	cOverwriteCaret->Width = 186;
	cOverwriteCaret->Height = 21;
	cOverwriteCaret->Style = csDropDownList;
	cOverwriteCaret->TabOrder = 1;
	cOverwriteCaret->Items->Add(L"Vertical Line");
	cOverwriteCaret->Items->Add(L"Horizontal Line");
	cOverwriteCaret->Items->Add(L"Half Block");
	cOverwriteCaret->Items->Add(L"Block");
	Keystrokes = new TTabSheet(PageControl1);
	Keystrokes->Parent = PageControl1;
	Keystrokes->PageControl = PageControl1;
	Keystrokes->Caption = L"Keystrokes";
	btnAddKey = new TButton(Keystrokes);
	btnAddKey->Parent = Keystrokes;
	btnAddKey->Left = 96;
	btnAddKey->Top = 152;
	btnAddKey->Width = 75;
	btnAddKey->Height = 25;
	btnAddKey->Caption = L"&Add";
	btnAddKey->TabOrder = 2;
	btnAddKey->OnClick = btnAddKeyClick;
	btnRemKey = new TButton(Keystrokes);
	btnRemKey->Parent = Keystrokes;
	btnRemKey->Left = 176;
	btnRemKey->Top = 152;
	btnRemKey->Width = 75;
	btnRemKey->Height = 25;
	btnRemKey->Caption = L"&Remove";
	btnRemKey->TabOrder = 3;
	btnRemKey->OnClick = btnRemKeyClick;
	gbKeyStrokes = new TGroupBox(Keystrokes);
	gbKeyStrokes->Parent = Keystrokes;
	gbKeyStrokes->Left = 8;
	gbKeyStrokes->Top = 192;
	gbKeyStrokes->Width = 330;
	gbKeyStrokes->Height = 119;
	gbKeyStrokes->Caption = L"Keystroke Options";
	gbKeyStrokes->TabOrder = 4;
	Label5 = new TLabel(gbKeyStrokes);
	Label5->Parent = gbKeyStrokes;
	Label5->Left = 16;
	Label5->Top = 28;
	Label5->Width = 50;
	Label5->Height = 13;
	Label5->Caption = L"Command:";
	Label6 = new TLabel(gbKeyStrokes);
	Label6->Parent = gbKeyStrokes;
	Label6->Left = 16;
	Label6->Top = 91;
	Label6->Width = 50;
	Label6->Height = 13;
	Label6->Caption = L"Keystroke:";
	Label7 = new TLabel(gbKeyStrokes);
	Label7->Parent = gbKeyStrokes;
	Label7->Left = 16;
	Label7->Top = 59;
	Label7->Width = 50;
	Label7->Height = 13;
	Label7->Caption = L"Keystroke:";
	cKeyCommand = new TComboBox(gbKeyStrokes);
	cKeyCommand->Parent = gbKeyStrokes;
	cKeyCommand->Left = 120;
	cKeyCommand->Top = 23;
	cKeyCommand->Width = 186;
	cKeyCommand->Height = 21;
	cKeyCommand->Style = csDropDownList;
	cKeyCommand->TabOrder = 0;
	cKeyCommand->OnKeyUp = cKeyCommandKeyUp;
	btnUpdateKey = new TButton(Keystrokes);
	btnUpdateKey->Parent = Keystrokes;
	btnUpdateKey->Left = 16;
	btnUpdateKey->Top = 152;
	btnUpdateKey->Width = 75;
	btnUpdateKey->Height = 25;
	btnUpdateKey->Caption = L"&Update";
	btnUpdateKey->TabOrder = 1;
	btnUpdateKey->OnClick = btnUpdateKeyClick;
	pnlCommands = new TPanel(Keystrokes);
	pnlCommands->Parent = Keystrokes;
	pnlCommands->Left = 8;
	pnlCommands->Top = 13;
	pnlCommands->Width = 330;
	pnlCommands->Height = 132;
	pnlCommands->BevelInner = bvRaised;
	pnlCommands->BevelOuter = bvLowered;
	pnlCommands->Caption = L"pnlCommands";
	pnlCommands->TabOrder = 0;
	KeyList = new TListView(pnlCommands);
	KeyList->Parent = pnlCommands;
	KeyList->Left = 2;
	KeyList->Top = 2;
	KeyList->Width = 326;
	KeyList->Height = 128;
	KeyList->Align = alClient;
	KeyList->BorderStyle = bsNone;
	GetTListColumnsitem(KeyList->Columns, 0)->Caption = L"Command";
	GetTListColumnsitem(KeyList->Columns, 0)->Width = (TWidth) 167;
	GetTListColumnsitem(KeyList->Columns, 1)->Caption = L"Keystroke";
	GetTListColumnsitem(KeyList->Columns, 1)->Width = (TWidth) 142;
	KeyList->ColumnClick = false;
	KeyList->HideSelection = false;
	KeyList->ReadOnly = true;
	KeyList->RowSelect = true;
	KeyList->TabOrder = 0;
	KeyList->ViewStyle = vsReport;
	KeyList->OnChanging = KeyListChanging;
	btnOK = new TButton(this);
	btnOK->Parent = this;
	btnOK->Left = 200;
	btnOK->Top = 362;
	btnOK->Width = 75;
	btnOK->Height = 25;
	btnOK->Caption = L"&OK";
	btnOK->ModalResult = 1;
	btnOK->TabOrder = 1;
	btnOK->OnClick = btnOKClick;
	btnCancel = new TButton(this);
	btnCancel->Parent = this;
	btnCancel->Left = 280;
	btnCancel->Top = 362;
	btnCancel->Width = 75;
	btnCancel->Height = 25;
	btnCancel->Caption = L"&Cancel";
	btnCancel->ModalResult = 2;
	btnCancel->TabOrder = 2;
	ColorDialog = new TColorDialog(this);
	// non-visible component: Left
	// non-visible component: Top
	ColorPopup = new TPopupMenu(this);
	// non-visible component: Left
	// non-visible component: Top
	None1 = new TMenuItem(ColorPopup);
	None1->Tag = -1;
	None1->Caption = L"None";
	None1->OnClick = PopupMenuClick;
	Scrollbar1 = new TMenuItem(ColorPopup);
	Scrollbar1->Caption = L"Scrollbar";
	Scrollbar1->OnClick = PopupMenuClick;
	Background1 = new TMenuItem(ColorPopup);
	Background1->Tag = 1;
	Background1->Caption = L"Background";
	Background1->OnClick = PopupMenuClick;
	ActiveCaption1 = new TMenuItem(ColorPopup);
	ActiveCaption1->Tag = 2;
	ActiveCaption1->Caption = L"Active Caption";
	ActiveCaption1->OnClick = PopupMenuClick;
	InactiveCaption1 = new TMenuItem(ColorPopup);
	InactiveCaption1->Tag = 3;
	InactiveCaption1->Caption = L"Inactive Caption";
	InactiveCaption1->OnClick = PopupMenuClick;
	Menu1 = new TMenuItem(ColorPopup);
	Menu1->Tag = 4;
	Menu1->Caption = L"Menu";
	Menu1->OnClick = PopupMenuClick;
	Window1 = new TMenuItem(ColorPopup);
	Window1->Tag = 5;
	Window1->Caption = L"Window";
	Window1->OnClick = PopupMenuClick;
	WindowFrame1 = new TMenuItem(ColorPopup);
	WindowFrame1->Tag = 6;
	WindowFrame1->Caption = L"Window Frame";
	WindowFrame1->OnClick = PopupMenuClick;
	Menu2 = new TMenuItem(ColorPopup);
	Menu2->Tag = 7;
	Menu2->Caption = L"Menu Text";
	Menu2->OnClick = PopupMenuClick;
	WindowText1 = new TMenuItem(ColorPopup);
	WindowText1->Tag = 8;
	WindowText1->Caption = L"Window Text";
	WindowText1->OnClick = PopupMenuClick;
	CaptionText1 = new TMenuItem(ColorPopup);
	CaptionText1->Tag = 9;
	CaptionText1->Caption = L"Caption Text";
	CaptionText1->OnClick = PopupMenuClick;
	ActiveBorder1 = new TMenuItem(ColorPopup);
	ActiveBorder1->Tag = 10;
	ActiveBorder1->Caption = L"Active Border";
	ActiveBorder1->OnClick = PopupMenuClick;
	InactiveBorder1 = new TMenuItem(ColorPopup);
	InactiveBorder1->Tag = 11;
	InactiveBorder1->Caption = L"Inactive Border";
	InactiveBorder1->OnClick = PopupMenuClick;
	ApplicationWorkspace1 = new TMenuItem(ColorPopup);
	ApplicationWorkspace1->Tag = 12;
	ApplicationWorkspace1->Caption = L"Application Workspace";
	ApplicationWorkspace1->OnClick = PopupMenuClick;
	Highlight1 = new TMenuItem(ColorPopup);
	Highlight1->Tag = 13;
	Highlight1->Caption = L"Highlight";
	Highlight1->OnClick = PopupMenuClick;
	HighlightText1 = new TMenuItem(ColorPopup);
	HighlightText1->Tag = 14;
	HighlightText1->Caption = L"Highlight Text";
	HighlightText1->OnClick = PopupMenuClick;
	ButtonFace1 = new TMenuItem(ColorPopup);
	ButtonFace1->Tag = 15;
	ButtonFace1->Caption = L"Button Face";
	ButtonFace1->OnClick = PopupMenuClick;
	ButtonShadow1 = new TMenuItem(ColorPopup);
	ButtonShadow1->Tag = 16;
	ButtonShadow1->Caption = L"Button Shadow";
	ButtonShadow1->OnClick = PopupMenuClick;
	GrayText1 = new TMenuItem(ColorPopup);
	GrayText1->Tag = 17;
	GrayText1->Caption = L"Gray Text";
	GrayText1->OnClick = PopupMenuClick;
	ButtonText1 = new TMenuItem(ColorPopup);
	ButtonText1->Tag = 18;
	ButtonText1->Caption = L"Button Text";
	ButtonText1->OnClick = PopupMenuClick;
	InactiveCaptionText1 = new TMenuItem(ColorPopup);
	InactiveCaptionText1->Tag = 19;
	InactiveCaptionText1->Caption = L"Inactive Caption Text";
	InactiveCaptionText1->OnClick = PopupMenuClick;
	Highlight2 = new TMenuItem(ColorPopup);
	Highlight2->Tag = 20;
	Highlight2->Caption = L"Highlight";
	Highlight2->OnClick = PopupMenuClick;
	N3dDarkShadow1 = new TMenuItem(ColorPopup);
	N3dDarkShadow1->Tag = 21;
	N3dDarkShadow1->Caption = L"3D Dark Shadow";
	N3dDarkShadow1->OnClick = PopupMenuClick;
	N3DLight1 = new TMenuItem(ColorPopup);
	N3DLight1->Tag = 22;
	N3DLight1->Caption = L"3D Light";
	N3DLight1->OnClick = PopupMenuClick;
	InfoTipText1 = new TMenuItem(ColorPopup);
	InfoTipText1->Tag = 23;
	InfoTipText1->Caption = L"Info Tip Text";
	InfoTipText1->OnClick = PopupMenuClick;
	InfoTipBackground1 = new TMenuItem(ColorPopup);
	InfoTipBackground1->Tag = 24;
	InfoTipBackground1->Caption = L"Info Tip Background";
	InfoTipBackground1->OnClick = PopupMenuClick;
	ImageList1 = new TImageList(this);
	// non-visible component: Left
	// non-visible component: Top
	FontDialog = new TFontDialog(this);
	FontDialog->Font->Charset = DEFAULT_CHARSET;
	FontDialog->Font->Color = clWindowText;
	FontDialog->Font->Height = -11;
	FontDialog->Font->Name = L"MS Sans Serif";
	FontDialog->Font->Style = (TFontStyles());
	FontDialog->Options = (TFontDialogOptions() << fdEffects << fdFixedPitchOnly);
	// non-visible component: Left
	// non-visible component: Top
	ComponentState >> csLoading;
	//----- shifted initializations from the dfm-file ---------------------------
	PageControl1->ActivePage = Keystrokes;
	//----- end of initializations from the dfm-file ----------------------------
}

