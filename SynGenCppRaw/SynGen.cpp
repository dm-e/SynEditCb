#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

//---------------------------------------------------------------------------
//# it's recommended to create this file with C++Builder
//---------------------------------------------------------------------------
#include <Vcl.Forms.hpp>
#include "GenLex.h"
namespace Syngenunit{ 
USEFORM("SynGenUnit.cpp",FrmMain); }
namespace Hashtablegen{ 
USEFORM("HashTableGen.cpp",FrmHashTableGen); }

using namespace std;
using namespace Genlex;
using namespace System;
using namespace Vcl::Forms;



#pragma resource "*.RES" 

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = L"SynGen";
		Application->CreateForm(__classid(TFrmMain), (void**)&FrmMain);
		Application->CreateForm(__classid(TFrmHashTableGen), (void**)&FrmHashTableGen);
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
