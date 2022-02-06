#include <vcl.h>
#pragma hdrstop

#include "frmMainMDI.h"

using namespace std;
using namespace d2c_system;

__fastcall TMDIMainForm::TMDIMainForm(TComponent* AOwner) : inherited(AOwner) {}


TMDIMainForm* MDIMainForm = nullptr;
#pragma resource "*.DFM" 


/* TMDIMainForm */

IEditor* __fastcall TMDIMainForm::DoCreateEditor(String AFileName)
{
	IEditor* result = nullptr;
	if(GI_EditorFactory != nullptr)
		result = GI_EditorFactory->CreateMDIChild(this);
	else
		result = nullptr;
	return result;
}

void __fastcall TMDIMainForm::FormCreate(TObject* Sender)
{
	inherited::FormCreate(Sender);
	CmdLineOpenFiles(true);
}
