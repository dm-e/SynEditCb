#include <vcl.h>
#pragma hdrstop

#include "SynEditPrintMarginsDialog.h"
#include <System.UITypes.hpp>

using namespace std;
using namespace d2c_system;
using namespace Syneditprintmargins;
using namespace Syneditprinttypes;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Uitypes;
using namespace Vcl::Dialogs;
using namespace Vcl::Stdctrls;

#define SynEditPrintMarginsDialog__0 (TMsgDlgButtons() << System::Uitypes::TMsgDlgBtn::mbOK)

__fastcall TSynEditPrintMarginsDlg::TSynEditPrintMarginsDlg(System::Classes::TComponent* AOwner) : inherited(AOwner) {}


#pragma resource "*.dfm" 


/* TSynEditPrintMarginsDlg */

void __fastcall TSynEditPrintMarginsDlg::FormCreate(TObject* Sender)
{
	FMargins = new TSynEditPrintMargins();
	FInternalCall = false;
}

void __fastcall TSynEditPrintMarginsDlg::FormDestroy(TObject* Sender)
{
	delete FMargins;
}

void __fastcall TSynEditPrintMarginsDlg::GetMargins(TSynEditPrintMargins* SynEditMargins)
{
	TEdit* CurEdit = nullptr;

	auto StringToFloat = [&](TEdit* Edit) -> double 
	{
		double result = 0.0;
		CurEdit = Edit;
		result = StrToFloat(Edit->Text);
		return result;
	};
	/*# with SynEditMargins do */
	{
		auto with0 = SynEditMargins;
		if(!FInternalCall)
			with0->UnitSystem = ((TUnitSystem) CBUnits->ItemIndex);
		try
		{
			with0->Left = StringToFloat(EditLeft);
			with0->Right = StringToFloat(EditRight);
			with0->Top = StringToFloat(EditTop);
			with0->Bottom = StringToFloat(EditBottom);
			with0->Gutter = StringToFloat(EditGutter);
			with0->Header = StringToFloat(EditHeader);
			with0->Footer = StringToFloat(EditFooter);
			with0->LeftHFTextIndent = StringToFloat(EditLeftHFTextIndent);
			with0->RightHFTextIndent = StringToFloat(EditRightHFTextIndent);
			with0->HFInternalMargin = StringToFloat(EditHFInternalMargin);
		}
		catch(...)
		{
			MessageDlg(L"Invalid number!", System::Uitypes::TMsgDlgType::mtError, SynEditPrintMarginsDialog__0, 0);
			CurEdit->SetFocus();
		}
		with0->MirrorMargins = CBMirrorMargins->Checked;
	}
}

void __fastcall TSynEditPrintMarginsDlg::SetMargins(TSynEditPrintMargins* SynEditMargins)
{
	/*# with SynEditMargins do */
	{
		auto with0 = SynEditMargins;
		CBUnits->ItemIndex = int(with0->UnitSystem);
		EditLeft->Text = FloatToStr(with0->Left);
		EditRight->Text = FloatToStr(with0->Right);
		EditTop->Text = FloatToStr(with0->Top);
		EditBottom->Text = FloatToStr(with0->Bottom);
		EditGutter->Text = FloatToStr(with0->Gutter);
		EditHeader->Text = FloatToStr(with0->Header);
		EditFooter->Text = FloatToStr(with0->Footer);
		EditLeftHFTextIndent->Text = FloatToStr(with0->LeftHFTextIndent);
		EditRightHFTextIndent->Text = FloatToStr(with0->RightHFTextIndent);
		EditHFInternalMargin->Text = FloatToStr(with0->HFInternalMargin);
		CBMirrorMargins->Checked = with0->MirrorMargins;
	}
}

void __fastcall TSynEditPrintMarginsDlg::CBUnitsChange(TObject* Sender)
{
	FInternalCall = true;
	GetMargins(FMargins);
	FInternalCall = false;
	FMargins->UnitSystem = ((TUnitSystem) CBUnits->ItemIndex);
	SetMargins(FMargins);
}
