//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("dmCommands.cpp", CommandsDataModule); /* TDataModule: File Type */
USEFORM("frmEditor.cpp", EditorForm);
USEFORM("frmMain.cpp", MainForm);
USEFORM("frmMainSDI.cpp", SDIMainForm);
USEFORM("..\SearchReplaceDemo\dlgConfirmReplace.cpp", ConfirmReplaceDialog);
USEFORM("..\SearchReplaceDemo\dlgSearchText.cpp", TextSearchDialog);
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
