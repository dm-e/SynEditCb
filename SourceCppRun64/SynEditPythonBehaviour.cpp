#include <vcl.h>
#pragma hdrstop

#include "SynEditPythonBehaviour.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Syneditkeycmds;
using namespace Syneditstrconst;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;

namespace Syneditpythonbehaviour
{



void __fastcall TSynEditPythonBehaviour::SetEditor(TSynEdit* Value)
{
	if(FEditor != Value)
	{
		if((Editor != nullptr) && !(ComponentState.Contains(csDesigning)))
			Editor->UnregisterCommandHandler(doProcessUserCommand);
    // Set the new editor
		FEditor = Value;
		if((Editor != nullptr) && !(ComponentState.Contains(csDesigning)))
			Editor->RegisterCommandHandler(doProcessUserCommand, nullptr);
	}
}

void __fastcall TSynEditPythonBehaviour::doProcessUserCommand(TObject* Sender, bool AfterProcessing, bool& Handled, TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData)
{
	TCustomSynEdit* IEditor = nullptr;
	String iPrevLine;
	int cSpace = 0;
	if((Command == ecLineBreak) && AfterProcessing)
	{
		IEditor = (TCustomSynEdit*) Sender;
    /* CaretY should never be lesser than 2 right after ecLineBreak, so there's
    no need for a check */
		iPrevLine = TrimRight(IEditor->Lines->Strings[IEditor->CaretY - 2]);
		if((iPrevLine != L"") && (iPrevLine[iPrevLine.Length()] == L':'))
		{
			IEditor->BeginUndoBlock();
			try
			{
				int stop = 0;
				for(stop = Indent, cSpace = 1; cSpace <= stop; cSpace++)
				{
					IEditor->ExecuteCommand((TSynEditorCommand) ecChar, L'\x20', nullptr);
				}
			}
			__finally
			{
				IEditor->EndUndoBlock();
			}
		}
	}
}

__fastcall TSynEditPythonBehaviour::TSynEditPythonBehaviour(TComponent* AOwner)
 : inherited(AOwner),
			FEditor(nullptr),
			FIndent(0)
{
	FIndent = 4;
}


}  // namespace SynEditPythonBehaviour

