//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("main.cpp", SyneditTest_frm);
USEFORM("..\SourceCppRun64\SynEditKeyCmdEditor.cpp", SynEditKeystrokeEditorForm);
USEFORM("..\SourceCppRun64\SynEditKeyCmdsEditor.cpp", SynEditKeystrokesEditorForm);
USEFORM("..\SourceCppRun64\SynEditOptionsDialog.cpp", fmEditorOptionsDialog);
USEFORM("..\SourceCppRun64\SynEditPrintMarginsDialog.cpp", SynEditPrintMarginsDlg);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TSyneditTest_frm), &SyneditTest_frm);
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
