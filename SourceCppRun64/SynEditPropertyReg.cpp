#include <vcl.h>
#pragma hdrstop

#include "SynEditPropertyReg.h"
#include <Vcl.Dialogs.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include "SynEditTypes.h"
#include "SynEditKeyCmds.h"
#include "SynEditKeyCmdsEditor.h"
#include "SynEdit.h"
#include "SynEditPrint.h"
#include "SynEditPrintMargins.h"
#include "SynEditPrintMarginsDialog.h"
#include "SynCompletionProposal.h"
#include "SynMacroRecorder.h"
#include "SynAutoCorrect.h"
#include "SynAutoCorrectEditor.h"
#include <System.SysUtils.hpp>
#include "d2c_sysrtti.h"

using namespace std;
using namespace d2c_system;
using namespace Designeditors;
using namespace Synautocorrect;
using namespace Syncompletionproposal;
using namespace Synedit;
using namespace Syneditkeycmds;
using namespace Syneditprint;
using namespace Syneditprintmargins;
using namespace Synedittypes;
using namespace Synmacrorecorder;
using namespace System;
using namespace System::Sysutils;
using namespace System::Uitypes;
using namespace Vcleditors;
using namespace Vcl::Controls;
using namespace Vcl::Dialogs;
using namespace Vcl::Forms;
using namespace Vcl::Graphics;

namespace Syneditpropertyreg
{
#define Syneditpropertyreg__0 (TFontDialogOptions() << fdShowHelp << fdForceFontExist << fdFixedPitchOnly)
#define Syneditpropertyreg__1 (TPropertyAttributes() << paMultiSelect << paDialog << paValueList << paRevertable)
#define Syneditpropertyreg__2 (TPropertyAttributes() << paDialog << paReadOnly)
#define Syneditpropertyreg__3 (TPropertyAttributes() << paDialog << paSubProperties << paReadOnly << paSortList)
#define Syneditpropertyreg__4 (TPropertyAttributes() << paDialog << paReadOnly)

__fastcall TSynEditFontProperty::TSynEditFontProperty(IDesigner* const ADesigner, int APropCount) : inherited(ADesigner, APropCount) {}
__fastcall TSynEditFontProperty::TSynEditFontProperty() {}
__fastcall TSynEditCommandProperty::TSynEditCommandProperty(IDesigner* const ADesigner, int APropCount) : inherited(ADesigner, APropCount) {}
__fastcall TSynEditCommandProperty::TSynEditCommandProperty() {}
__fastcall TSynEditKeystrokesProperty::TSynEditKeystrokesProperty(IDesigner* const ADesigner, int APropCount) : inherited(ADesigner, APropCount) {}
__fastcall TSynEditKeystrokesProperty::TSynEditKeystrokesProperty() {}
__fastcall TSynEditPrintMarginsProperty::TSynEditPrintMarginsProperty(IDesigner* const ADesigner, int APropCount) : inherited(ADesigner, APropCount) {}
__fastcall TSynEditPrintMarginsProperty::TSynEditPrintMarginsProperty() {}
__fastcall TAutoCorrectionProperty::TAutoCorrectionProperty(IDesigner* const ADesigner, int APropCount) : inherited(ADesigner, APropCount) {}
__fastcall TAutoCorrectionProperty::TAutoCorrectionProperty() {}
__fastcall TSynAutoCorrectComponentEditor::TSynAutoCorrectComponentEditor(TComponent* AComponent, IDesigner* ADesigner) : inherited(AComponent, ADesigner) {}
__fastcall TSynAutoCorrectComponentEditor::TSynAutoCorrectComponentEditor() {}



/* TSynEditFontProperty */

void __fastcall TSynEditFontProperty::Edit()
{

  /* context ids for the Font editor */
	const int hcDFontEditor = 25000;
	TFontDialog* FontDialog = nullptr;
	FontDialog = new TFontDialog(Application);
	try
	{
		FontDialog->Font = ((TFont*) GetOrdValue());
		FontDialog->HelpContext = (THelpContext) hcDFontEditor;
		FontDialog->Options = FontDialog->Options + Syneditpropertyreg__0;
		if(FontDialog->Execute())
			SetOrdValue(((NativeInt) FontDialog->Font));
	}
	__finally
	{
		delete FontDialog;
	}
}

/* TSynEditCommandProperty */

void __fastcall TSynEditCommandProperty::Edit()
{
	ShowMessage(L"I'm thinking that this will show a dialog that has a list\x0d\x0a"
	           L"of all editor commands and a description of them to choose from.");
}

TPropertyAttributes __fastcall TSynEditCommandProperty::GetAttributes()
{
	TPropertyAttributes result;
	result = Syneditpropertyreg__1;
	return result;
}

String __fastcall TSynEditCommandProperty::GetValue()
{
	String result;
	result = EditorCommandToCodeString(((TSynEditorCommand) GetOrdValue()));
	return result;
}

void __fastcall TSynEditCommandProperty::GetValues(TGetStrProc Proc)
{
	GetEditorCommandValues(Proc);
}

void __fastcall TSynEditCommandProperty::SetValue(const String Value)
{
	int NewValue = 0;
	if(IdentToEditorCommand(Value, NewValue))
		SetOrdValue(NewValue);
	else
		inherited::SetValue(Value);
}

/* TSynEditKeystrokesProperty */

void __fastcall TSynEditKeystrokesProperty::Edit()
{
	TSynEditKeystrokesEditorForm* Dlg = nullptr;
	Application->CreateForm(__classid(TSynEditKeystrokesEditorForm), (void**)&Dlg);
	try
	{
		Dlg->Caption = this->GetName();
		Dlg->Keystrokes = ((TSynEditKeyStrokes*) GetOrdValue());
		if(Dlg->ShowModal() == System::Uitypes::mrOk)
      /* SetOrdValue will operate on all selected propertiy values */
		{
			SetOrdValue(((NativeInt) Dlg->Keystrokes));
			Modified();
		}
	}
	__finally
	{
		delete Dlg;
	}
}

TPropertyAttributes __fastcall TSynEditKeystrokesProperty::GetAttributes()
{
	TPropertyAttributes result;
	result = Syneditpropertyreg__2;
	return result;
}

/* TSynEditPrintMarginsProperty */

void __fastcall TSynEditPrintMarginsProperty::Edit()
{
	TSynEditPrintMarginsDlg* SynEditPrintMarginsDlg = nullptr;
	SynEditPrintMarginsDlg = new TSynEditPrintMarginsDlg((TComponent*)nullptr, 0);
	try
	{
		SynEditPrintMarginsDlg->SetMargins(((TSynEditPrintMargins*) GetOrdValue()));
		if(SynEditPrintMarginsDlg->ShowModal() == System::Uitypes::mrOk)
			SynEditPrintMarginsDlg->GetMargins(((TSynEditPrintMargins*) GetOrdValue()));
	}
	__finally
	{
		delete SynEditPrintMarginsDlg;
	}
}

TPropertyAttributes __fastcall TSynEditPrintMarginsProperty::GetAttributes()
{
	TPropertyAttributes result;
	result = Syneditpropertyreg__3;
	return result;
}

void __fastcall TSynAutoCorrectComponentEditor::Edit()
{
	TfrmAutoCorrectEditor* frmAutoCorrectEditor = nullptr;
	frmAutoCorrectEditor = new TfrmAutoCorrectEditor(Application, 0);
	try
	{
		frmAutoCorrectEditor->SynAutoCorrect = ((TSynAutoCorrect*) Component);
		frmAutoCorrectEditor->ShowModal();
	}
	__finally
	{
		delete frmAutoCorrectEditor;
	}
	Designer->Modified;
}

void __fastcall TSynAutoCorrectComponentEditor::ExecuteVerb(int Index)
{
	switch(Index)
	{
		case 0:
		Edit();
		break;
		default:
		  ;
		break;
	}
}

String __fastcall TSynAutoCorrectComponentEditor::GetVerb(int Index)
{
	String result;
	switch(Index)
	{
		case 0:
		result = L"&Edit...";
		break;
		default:
		  ;
		break;
	}
	return result;
}

int __fastcall TSynAutoCorrectComponentEditor::GetVerbCount()
{
	int result = 0;
	result = 1;
	return result;
}

void __fastcall TAutoCorrectionProperty::Edit()
{
	TfrmAutoCorrectEditor* frmAutoCorrectEditor = nullptr;
	frmAutoCorrectEditor = new TfrmAutoCorrectEditor(Application, 0);
	try
	{
		frmAutoCorrectEditor->SynAutoCorrect = ((TSynAutoCorrect*) GetComponent(0));
		frmAutoCorrectEditor->ShowModal();
	}
	__finally
	{
		delete frmAutoCorrectEditor;
	}
	Designer->Modified();
}

TPropertyAttributes __fastcall TAutoCorrectionProperty::GetAttributes()
{
	TPropertyAttributes result;
	result = Syneditpropertyreg__4;
	return result;
}

String __fastcall TAutoCorrectionProperty::GetValue()
{
	String result;
	result = L"(AutoCorrections)";
	return result;
}                


/* Register */

void __fastcall Register()
{
	RegisterPropertyEditor(((TTypeInfo*) TypeInfo<WideChar>()), nullptr, L"", __classid(TCharProperty));
	RegisterPropertyEditor(((TTypeInfo*) TypeInfo<TStrings>()), nullptr, L"", __classid(TStringListProperty));
	RegisterPropertyEditor(((TTypeInfo*) TypeInfo<TFont>()), __classid(TCustomSynEdit), L"Font", __classid(TSynEditFontProperty));
	RegisterPropertyEditor(((TTypeInfo*) TypeInfo<TSynEditorCommand>()), nullptr, L"", __classid(TSynEditCommandProperty));
	RegisterPropertyEditor(((TTypeInfo*) TypeInfo<TSynEditKeyStrokes>()), nullptr, L"", __classid(TSynEditKeystrokesProperty));
	RegisterPropertyEditor(((TTypeInfo*) TypeInfo<TSynEditPrintMargins>()), __classid(TPersistent), L"", __classid(TSynEditPrintMarginsProperty));
	RegisterPropertyEditor(((TTypeInfo*) TypeInfo<TStrings>()), __classid(TSynAutoCorrect), L"Items", __classid(TAutoCorrectionProperty));
	RegisterComponentEditor(__classid(TSynAutoCorrect), __classid(TSynAutoCorrectComponentEditor));
	RegisterPropertyEditor(((TTypeInfo*) TypeInfo<TShortCut>()), __classid(TSynCompletionProposal), L"", __classid(TShortCutProperty));
	RegisterPropertyEditor(((TTypeInfo*) TypeInfo<TShortCut>()), __classid(TSynAutoComplete), L"", __classid(TShortCutProperty));
	RegisterPropertyEditor(((TTypeInfo*) TypeInfo<TShortCut>()), __classid(TSynMacroRecorder), L"", __classid(TShortCutProperty));
}


}  // namespace SynEditPropertyReg

