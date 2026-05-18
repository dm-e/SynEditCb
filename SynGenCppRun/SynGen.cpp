#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Forms.hpp>
#include "GenLex.h"
#include "SynGenUnit.h"
#include "HashTableGen.h"

using namespace Genlex;
using namespace Vcl::Forms;



int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
	{
		HInstance = hInstance;
		try
		{
			Application->Initialize();
			Application->Title = L"SynGen";
			FrmMain = new TFrmMain(Application, 0);
			FrmHashTableGen = new TFrmHashTableGen(Application, 0);
			Application->Run();
			FrmMain->Visible = true;
			while(!Application->Terminated && FrmMain->Visible)
			 Application->HandleMessage();
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
