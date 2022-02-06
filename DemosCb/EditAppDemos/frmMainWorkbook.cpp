#include <vcl.h>
#pragma hdrstop

#include "frmMainWorkbook.h"

using namespace std;
using namespace d2c_system;

__fastcall TWorkbookMainForm::TWorkbookMainForm(TComponent* AOwner) : inherited(AOwner) {}


TWorkbookMainForm* WorkbookMainForm = nullptr;
#pragma resource "*.DFM" 


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
