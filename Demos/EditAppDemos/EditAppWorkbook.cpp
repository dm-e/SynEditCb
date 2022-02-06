#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
//# it's recommended to create this file with C++Builder
//---------------------------------------------------------------------------
#include <Vcl.Forms.hpp>
#include "uEditAppIntfs.h"
#include "uHighlighterProcs.hpp"

USEFORM("..\SearchReplaceDemo\dlgConfirmReplace.cpp", ConfirmReplaceDialog);
USEFORM("frmMainWorkbook.cpp", WorkbookMainForm);
USEFORM("..\SearchReplaceDemo\dlgSearchText.cpp", TextSearchDialog);
USEFORM("frmMain.cpp", MainForm);
USEFORM("dmCommands.cpp", CommandsDataModule); /* TDataModule: File Type */
USEFORM("frmEditor.cpp", EditorForm);
//---------------------------------------------------------------------------
using namespace std;

#pragma resource "*.RES" 
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
  try
  {
    Application->Initialize();
    Application->Title = L"SynEdit Demo";
    Application->CreateForm(__classid(TWorkbookMainForm), (void**)&WorkbookMainForm);
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
