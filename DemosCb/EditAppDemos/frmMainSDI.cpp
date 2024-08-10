#include <vcl.h>
#pragma hdrstop

#include "frmMainSDI.h"

using namespace std;
using namespace d2c_system;

__fastcall TSDIMainForm::TSDIMainForm(TComponent* AOwner) : inherited(AOwner) {}


TSDIMainForm* SDIMainForm = nullptr;
#pragma resource "*.DFM"


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
