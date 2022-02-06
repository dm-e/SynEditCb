#include <vcl.h>
#pragma hdrstop

#include "uEditAppIntfs.h"

using namespace std;
using namespace d2c_system;


IEditorFactory* GI_EditorFactory = nullptr;
IEditor* GI_ActiveEditor = nullptr;
IEditCommands* GI_EditCmds = nullptr;
IFileCommands* GI_FileCmds = nullptr;
ISearchCommands* GI_SearchCmds = nullptr;
