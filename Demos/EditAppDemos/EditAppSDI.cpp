//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("..\SearchReplaceDemo\dlgConfirmReplace.cpp", ConfirmReplaceDialog);
USEFORM("frmMainSDI.cpp", SDIMainForm);
USEFORM("..\SearchReplaceDemo\dlgSearchText.cpp", TextSearchDialog);
USEFORM("frmMain.cpp", MainForm);
USEFORM("dmCommands.cpp", CommandsDataModule); /* TDataModule: File Type */
USEFORM("frmEditor.cpp", EditorForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TSDIMainForm), &SDIMainForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
