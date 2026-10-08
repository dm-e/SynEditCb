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
using namespace System::Classes;

namespace Syneditpythonbehaviour
{



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPythonBehaviour.pas, released 2000-06-23.
The Original Code is based on odPythonBehaviour.pas by Olivier Deckmyn, part
of the mwEdit component suite.
Unicode translation by Maël Hörz.

Contributors to the SynEdit and mwEdit projects are listed in the
Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

$Id: SynEditPythonBehaviour.pas,v 1.5.2.3 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a component which implements editing rules to apply to a Python source file)
@author(Olivier Deckmyn, converted to SynEdit by David Muir <dhm@dmsoftware.co.uk>)
@created(1999-10-17)
@lastmod(May 19, 2000)
The  SynEditPythonBehaviour unit provides a simple component implements editing rules to apply
to a python source file. Python has a unusual way to mark blocks (like begin/end in pascal) : it
uses indentation. So the rule is after a ":" and a line break, we have to indent once.
*/

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
	TCustomSynEdit* iEditor = nullptr;
	String iPrevLine;
	int cSpace = 0;
	if((Command == ecLineBreak) && AfterProcessing)
	{
		iEditor = (TCustomSynEdit*) Sender;
    /* CaretY should never be lesser than 2 right after ecLineBreak, so there's
    no need for a check */
		iPrevLine = TrimRight(iEditor->Lines->Strings[iEditor->CaretY - 2]);
		if((iPrevLine != L"") && (iPrevLine[iPrevLine.Length()] == L':'))
		{
			iEditor->BeginUndoBlock();
			try
			{
				int stop = 0;
				for(stop = Indent, cSpace = 1; cSpace <= stop; cSpace++)
				{
					iEditor->ExecuteCommand(static_cast<TSynEditorCommand>(ecChar), L'\x20', nullptr);
				}
			}
			__finally
			{
				iEditor->EndUndoBlock();
			}
		}
	}
}

__fastcall TSynEditPythonBehaviour::TSynEditPythonBehaviour(TComponent* aOwner)
 : inherited(aOwner),
			FEditor(nullptr),
			fIndent(0)
{
	fIndent = 4;
}


}  // namespace Syneditpythonbehaviour

