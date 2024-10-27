#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Forms.hpp>
#include "frmMain.h"
#include "dlgSearchText.h"
#include "dlgReplaceText.h"
#include "dlgConfirmReplace.h"


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	HInstance = hInstance;
	try
	{
		Application->Initialize();
		SearchReplaceDemoForm = new TSearchReplaceDemoForm(Application, 0);
		Application->Run();
		SearchReplaceDemoForm->ShowModal();
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
