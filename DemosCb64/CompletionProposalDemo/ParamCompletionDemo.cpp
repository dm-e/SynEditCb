#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Forms.hpp>
#include "FormMain_ctParams.h"



USEFORM("FormMain_ctParams.cpp", Form1);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	HInstance = hInstance;
	try
	{
		Application->Initialize();
		Form1 = new TForm1(Application, 0);
		Application->Run();
		Form1->ShowModal();
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
