#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Forms.hpp>
USEFORM("frmMain.cpp",SearchReplaceDemoForm);
USEFORM("dlgSearchText.cpp",TextSearchDialog);
USEFORM("dlgReplaceText.cpp",TextReplaceDialog);
USEFORM("dlgConfirmReplace.cpp",ConfirmReplaceDialog);


//#pragma resource "*.RES" 

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	HInstance = hInstance;
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TSearchReplaceDemoForm), (void**)&SearchReplaceDemoForm);
		Application->Run();
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
