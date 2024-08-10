#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Forms.hpp>
USEFORM("FormMain_ctParams.cpp",Form1);



//#pragma resource "*.RES" 

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	HInstance = hInstance;
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TForm1), (void**)&Form1);
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
