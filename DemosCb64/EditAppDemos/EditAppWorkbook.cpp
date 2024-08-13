#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Forms.hpp>
#include "uEditAppIntfs.h"
#include "uHighlighterProcs.h"
#include "frmMain.h"
#include "frmMainWorkbook.h"
#include "frmEditor.h"
#include "dmCommands.h"
#include "dlgSearchText.h"
#include "dlgReplaceText.h"
#include "dlgConfirmReplace.h"
#include "EditAppDemosCb_initexit.h"


USEFORM("dmCommands.cpp", CommandsDataModule); /* TDataModule: File Type */
USEFORM("frmEditor.cpp", EditorForm);
USEFORM("frmMain.cpp", MainForm);
USEFORM("..\SearchReplaceDemo\dlgSearchText.cpp", TextSearchDialog);
USEFORM("frmMainWorkbook.cpp", WorkbookMainForm);
USEFORM("..\SearchReplaceDemo\dlgConfirmReplace.cpp", ConfirmReplaceDialog);
//---------------------------------------------------------------------------
CEditAppDemosCb_initexit _UnitsInitExit;
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	HInstance = hInstance;
	try
	{
		Application->Initialize();
		Application->Title = L"SynEdit Demo";
		WorkbookMainForm = new TWorkbookMainForm(Application, 0);
		Application->Run();
		WorkbookMainForm->ShowModal();
	}
	catch (Exception& exception)
	{
	  Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
		  throw Exception("");
		}
		catch (Exception& exception)
		{
		  Application->ShowException(&exception);
		}
	}
	return 0;
}
