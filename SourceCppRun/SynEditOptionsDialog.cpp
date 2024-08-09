#include <vcl.h>
#pragma hdrstop

#include "SynEditOptionsDialog.h"
#include <System.Types.hpp>
#include "SynEditKeyConst.h"
#include "SynEditMiscProcs.h"

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
using namespace Vcl::Forms;
using namespace Vcl::Graphics;

#define Syneditoptionsdialog__0 (TSynEditorOptions() << eoAutoIndent << eoDragDropEditing << eoDropFiles << eoScrollPastEol << eoShowScrollHint << eoSmartTabs << eoAltSetsColumnMode << eoTabsToSpaces << eoTrimTrailingSpaces << eoKeepCaretX)
#define Syneditoptionsdialog__1 Syneditmiscclasses::THKInvalidKeys()
#define Syneditoptionsdialog__2 Syneditmiscclasses::THKModifiers()
#define Syneditoptionsdialog__3 Syneditmiscclasses::THKInvalidKeys()
#define Syneditoptionsdialog__4 Syneditmiscclasses::THKModifiers()

__fastcall TfmEditorOptionsDialog::TfmEditorOptionsDialog(TComponent* AOwner) : inherited(AOwner) {}


#pragma resource "*.dfm"


/* TSynEditOptionsDialog */

__fastcall TSynEditOptionsDialog::TSynEditOptionsDialog(TComponent* AOwner)
 : inherited(AOwner),
			FForm(new TfmEditorOptionsDialog(this))
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
	PageControl1->ActivePage = PageControl1->Pages[0];
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
