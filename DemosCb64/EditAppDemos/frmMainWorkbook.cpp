#include <vcl.h>
#pragma hdrstop

#include "frmMainWorkbook.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;


TWorkbookMainForm* WorkbookMainForm = nullptr;

/* TWorkbookMainForm */

IEditor* __fastcall TWorkbookMainForm::DoCreateEditor(String AFileName)
{
	IEditor* result = nullptr;
	if(GI_EditorFactory != nullptr)
		result = GI_EditorFactory->CreateTabSheet(pctrlMain);
	else
		result = nullptr;
	return result;
}

void __fastcall TWorkbookMainForm::FormCreate(TObject* Sender)
{
	inherited::FormCreate(Sender);
	CmdLineOpenFiles(true);
}

void __fastcall TWorkbookMainForm::FormCloseQuery(TObject* Sender, bool& CanClose)
{
	/*#inherited method "FormCloseQuery" not found or not accessible*/;
	if(GI_EditorFactory != nullptr)
		CanClose = GI_EditorFactory->CanCloseAll();
}

__fastcall TWorkbookMainForm::TWorkbookMainForm(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	pctrlMain(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Caption = L"Workbook Edit Demo";
	AssignFormOldCreateOrder(this, true);
	OnCloseQuery = FormCloseQuery;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	pctrlMain = new TPageControl(this);
	pctrlMain->Parent = this;
	pctrlMain->Left = 0;
	pctrlMain->Top = 0;
	pctrlMain->Width = 506;
	pctrlMain->Height = 273;
	pctrlMain->Align = alClient;
	pctrlMain->TabOrder = 0;
	pctrlMain->TabStop = false;
	ComponentState >> csLoading;
	//----- end of initializations from the dfm-file ----------------------------
}

