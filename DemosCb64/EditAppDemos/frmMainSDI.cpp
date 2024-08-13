#include <vcl.h>
#pragma hdrstop

#include "frmMainSDI.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;


TSDIMainForm* SDIMainForm = nullptr;

/* TSDIMainForm */

IEditor* __fastcall TSDIMainForm::DoCreateEditor(String AFileName)
{
	IEditor* result = nullptr;
	if(fEditorForm != nullptr)
		result = fEditorForm;
	else
	{
		if(GI_EditorFactory != nullptr)
		{
			fEditorForm = GI_EditorFactory->CreateBorderless(this);
			result = fEditorForm;
		}
		else
		result = nullptr;
	}
	return result;
}

void __fastcall TSDIMainForm::FormCreate(TObject* Sender)
{
	inherited::FormCreate(Sender);
	if(!CmdLineOpenFiles(false))
		DoOpenFile(L"");
}

void __fastcall TSDIMainForm::FormCloseQuery(TObject* Sender, bool& CanClose)
{
	/*#inherited method "FormCloseQuery" not found or not accessible*/;
	if(GI_EditorFactory != nullptr)
		CanClose = GI_EditorFactory->CanCloseAll();
}

__fastcall TSDIMainForm::TSDIMainForm(TComponent* AOwner, int Dummy)
 : inherited(AOwner, Dummy)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Caption = L"Single Document Edit Demo";
	OnCloseQuery = FormCloseQuery;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	/*inherited*/mnuMain->mFile->miFileClose->Visible = false;
	/*inherited*/mnuMain->mFile->miFileCloseAll->Visible = false;
	ComponentState >> csLoading;
	//----- end of initializations from the dfm-file ----------------------------
}

