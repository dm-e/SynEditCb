#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
//# it's recommended to create this file with C++Builder
//---------------------------------------------------------------------------
#include <Vcl.Forms.hpp>
#include <Vcl.Themes.hpp>
#include "uHighlighterProcs.h"

USEFORM("Unit1.cpp",Form1);
using namespace std;

#pragma resource "*.res" 
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
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
