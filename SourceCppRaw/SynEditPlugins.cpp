#include <vcl.h>
#pragma hdrstop

#include "SynEditPlugins.h"
#include <System.Types.hpp>
#include <Vcl.Forms.hpp>
#include "SynEditMiscProcs.h"
#include "SynEditStrConst.h"
#include <System.SysUtils.hpp>

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Syneditkeycmds;
using namespace Syneditmiscprocs;
using namespace Syneditstrconst;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Types;
using namespace Vcl::Forms;

namespace Syneditplugins
{
#define Syneditplugins__0 (TComponentState() << csDesigning)
#define Syneditplugins__1 (TComponentState() << csDesigning)
#define Syneditplugins__2 (TComponentState() << csDesigning)
#define Syneditplugins__3 (TComponentState() << csDesigning)

__fastcall TAbstractSynPlugin::TAbstractSynPlugin(TComponent* AOwner) : inherited(AOwner) {}
__fastcall TAbstractSynHookerPlugin::TAbstractSynHookerPlugin(TComponent* AOwner) : inherited(AOwner) {}
__fastcall TAbstractSynCompletion::TAbstractSynCompletion(TComponent* aOwner) : inherited(aOwner) {}


const int ecPluginBase = 64000;
int gCurrentCommand = ecPluginBase;

TSynEditorCommand __fastcall NewPluginCommand()
{
	TSynEditorCommand result = 0;
	result = (TSynEditorCommand) gCurrentCommand;
	++gCurrentCommand;
	return result;
}

void __fastcall ReleasePluginCommand(TSynEditorCommand aCmd)
{
	if(aCmd == Pred(gCurrentCommand))
		gCurrentCommand = (int) aCmd;
}

/* TAbstractSynPlugin */

int __fastcall TAbstractSynPlugin::AddEditor(TCustomSynEdit* aEditor)
{
	int result = 0;
	if(fEditors == nullptr)
	{
		fEditors = new TList();
	}
	else
	{
		if(fEditors->IndexOf(aEditor) >= 0)
		{
			result = -1;
			return result;
		}
	}
	aEditor->FreeNotification(this);
	result = fEditors->Add(aEditor);
	DoAddEditor(aEditor);
	return result;
}

__fastcall TAbstractSynPlugin::~TAbstractSynPlugin()
{

  /* RemoveEditor will free fEditors when it reaches count = 0*/
	while(ASSIGNED(fEditors))
		RemoveEditor(Editors[0]);
	// inherited;
}

void __fastcall TAbstractSynPlugin::Notification(TComponent* aComponent, TOperation aOperation)
{
	inherited::Notification(aComponent, aOperation);
	if(aOperation == opRemove)
	{
		if((aComponent == Editor) || (ObjectIs(aComponent, TCustomSynEdit*)))
			RemoveEditor(((TCustomSynEdit*) aComponent));
	}
}

void __fastcall TAbstractSynPlugin::DoAddEditor(TCustomSynEdit* aEditor)
{
}

void __fastcall TAbstractSynPlugin::DoRemoveEditor(TCustomSynEdit* aEditor)
{
}

int __fastcall TAbstractSynPlugin::RemoveEditor(TCustomSynEdit* aEditor)
{
	int result = 0;
	if(fEditors == nullptr)
	{
		result = -1;
		return result;
	}
	result = fEditors->Remove(aEditor);
  //aEditor.RemoveFreeNotification(Self);
	if(fEditors->Count == 0)
	{
		delete fEditors;
		fEditors = nullptr;
	}
	if(result >= 0)
		DoRemoveEditor(aEditor);
	return result;
}

void __fastcall TAbstractSynPlugin::SetEditor(TCustomSynEdit* const Value)
{
	TCustomSynEdit* iEditor = nullptr;
	iEditor = Editor;
	if(iEditor != Value)
		try
		{
			if((iEditor != nullptr) && (fEditors->Count == 1))
				RemoveEditor(iEditor);
			if(Value != nullptr)
				AddEditor(const_cast<TCustomSynEdit*>(Value));
		}
		catch(...)
		{
			if(Syneditplugins__0 * ComponentState == Syneditplugins__1)
				Application->HandleException(this);
			else
				throw ;
		}
}

TCustomSynEdit* __fastcall TAbstractSynPlugin::GetEditors(int aIndex)
{
	TCustomSynEdit* result = nullptr;
	result = ((TCustomSynEdit*) fEditors->Items[aIndex]);
	return result;
}

TCustomSynEdit* __fastcall TAbstractSynPlugin::GetEditor()
{
	TCustomSynEdit* result = nullptr;
	if(fEditors != nullptr)
		result = ((TCustomSynEdit*) fEditors->Items[0]);
	else
		result = nullptr;
	return result;
}

int __fastcall TAbstractSynPlugin::GetEditorCount()
{
	int result = 0;
	if(fEditors != nullptr)
		result = fEditors->Count;
	else
		result = 0;
	return result;
}

/* TAbstractSynHookerPlugin */

void __fastcall TAbstractSynHookerPlugin::HookEditor(TCustomSynEdit* aEditor, TSynEditorCommand aCommandID, TShortCut aOldShortCut, TShortCut aNewShortCut)
{
	int iIndex = 0;
	TSynEditKeyStroke* iKeystroke = nullptr;
	Assert(aNewShortCut != 0);
  /* shortcurts aren't created while in design-time */
	if(Syneditplugins__2 * ComponentState == Syneditplugins__3)
	{
		if(((TSynEdit*) aEditor)->Keystrokes->FindShortcut(aNewShortCut) >= 0)
			throw new ESynKeyError(SYNS_EDuplicateShortcut);
		else
			return;
	}
  /* tries to update old Keystroke */
	if(aOldShortCut != 0)
	{
		iIndex = ((TSynEdit*) aEditor)->Keystrokes->FindShortcut(aOldShortCut);
		if(iIndex >= 0)
		{
			iKeystroke = ((TSynEdit*) aEditor)->Keystrokes->Items[iIndex];
			if(iKeystroke->Command == aCommandID)
			{
				iKeystroke->ShortCut = aNewShortCut;
				return;
			}
		}
	}
  /* new Keystroke */
	iKeystroke = ((TSynEdit*) aEditor)->Keystrokes->Add();
	try
	{
		iKeystroke->ShortCut = aNewShortCut;
	}
	catch(...)
	{
		delete iKeystroke;
		throw ;
	}
	iKeystroke->Command = aCommandID;
	aEditor->RegisterCommandHandler(OnCommand, this);
}

void __fastcall TAbstractSynHookerPlugin::UnHookEditor(TCustomSynEdit* aEditor, TSynEditorCommand aCommandID, TShortCut aShortCut)
{
	int iIndex = 0;
	aEditor->UnregisterCommandHandler(OnCommand);
	iIndex = ((TSynEdit*) aEditor)->Keystrokes->FindShortcut(aShortCut);
	if((iIndex >= 0) && (((TSynEdit*) aEditor)->Keystrokes->Items[iIndex]->Command == aCommandID))
		delete ((TSynEdit*) aEditor)->Keystrokes->Items[iIndex];
}

/* TAbstractSynHookerPlugin */

void __fastcall TAbstractSynSingleHookPlugin::Accept()
{
	fState = psAccepting;
	try
	{
		DoAccept();
	}
	__finally
	{
		fCurrentEditor = nullptr;
		fState = psNone;
	}
}

void __fastcall TAbstractSynSingleHookPlugin::Cancel()
{
	fState = psCancelling;
	try
	{
		DoCancel();
	}
	__finally
	{
		fCurrentEditor = nullptr;
		fState = psNone;
	}
}

__fastcall TAbstractSynSingleHookPlugin::TAbstractSynSingleHookPlugin(TComponent* aOwner)
 : inherited(aOwner),
			fCommandID(NewPluginCommand()),
			fState(psNone),
			fCurrentEditor(nullptr),
			fShortCut((TShortCut) 0)
{
	fShortCut = DefaultShortCut();
}

/*#static*/
TShortCut __fastcall TAbstractSynSingleHookPlugin::DefaultShortCut()
{
	TShortCut result = (TShortCut) 0;
	result = (TShortCut) 0;
	return result;
}

__fastcall TAbstractSynSingleHookPlugin::~TAbstractSynSingleHookPlugin()
{
	if(Executing())
		Cancel();
	ReleasePluginCommand(CommandID);
	// inherited;
}

void __fastcall TAbstractSynSingleHookPlugin::DoAddEditor(TCustomSynEdit* aEditor)
{
	if(ShortCut != 0)
		HookEditor(aEditor, CommandID, (TShortCut) 0, ShortCut);
}

void __fastcall TAbstractSynSingleHookPlugin::Execute(TCustomSynEdit* aEditor)
{
	if(Executing())
		Cancel();
	Assert(fCurrentEditor == nullptr);
	fCurrentEditor = aEditor;
	Assert(fState == psNone);
	fState = psExecuting;
	try
	{
		DoExecute();
	}
	catch(...)
	{
		Cancel();
		throw ;
	}
}

bool __fastcall TAbstractSynSingleHookPlugin::Executing()
{
	bool result = false;
	result = fState == psExecuting;
	return result;
}

bool __fastcall TAbstractSynSingleHookPlugin::IsShortCutStored()
{
	bool result = false;
	result = fShortCut != DefaultShortCut();
	return result;
}

void __fastcall TAbstractSynSingleHookPlugin::DoRemoveEditor(TCustomSynEdit* aEditor)
{
	if(ShortCut != 0)
		UnHookEditor(aEditor, CommandID, ShortCut);
	if(Executing() && (CurrentEditor == aEditor))
		Cancel();
}

void __fastcall TAbstractSynSingleHookPlugin::SetShortCut(const TShortCut Value)
{
	int cEditor = 0;
	if(fShortCut != Value)
	{
		if(ASSIGNED(fEditors))
		{
			if(Value != 0)
			{
				int stop = 0;
				for(stop = fEditors->Count - 1, cEditor = 0; cEditor <= stop; cEditor++)
				{
					HookEditor(Editors[cEditor], CommandID, fShortCut, Value);
				}
			}
			else
			{
				int stop = 0;
				for(stop = fEditors->Count - 1, cEditor = 0; cEditor <= stop; cEditor++)
				{
					UnHookEditor(Editors[cEditor], CommandID, fShortCut);
				}
			}
		}
		fShortCut = Value;
	}
}

/* TAbstractSynCompletion */

String __fastcall TAbstractSynCompletion::GetCurrentEditorString()
{
	String result;
	String S;
	int Col = 0;
	S = CurrentEditor->LineText;
	if((CurrentEditor->CaretX > 1) && (CurrentEditor->CaretX - 1 <= S.Length()))
	{
		int stop = 0;
		for(stop = 1, Col = CurrentEditor->CaretX - 1; Col >= stop; Col--)
		{
			if(!CurrentEditor->IsIdentChar(S[Col]))
				break;
		}
		result = S.SubString(Col + 1, CurrentEditor->CaretX - Col - 1);
	}
	return result;
}

void __fastcall TAbstractSynCompletion::DoAccept()
{
	fCurrentString = L"";
}

void __fastcall TAbstractSynCompletion::DoCancel()
{
	fCurrentString = L"";
}

void __fastcall TAbstractSynCompletion::DoExecute()
{
	CurrentString = GetCurrentEditorString();
}

void __fastcall TAbstractSynCompletion::OnCommand(TObject* Sender, bool AfterProcessing, bool& Handled, TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData)
{
	String S;
	if(!Executing())
	{
		if(Command == CommandID)
		{
			Execute((TCustomSynEdit*) Sender);
			Handled = true;
		}
	}
	else
	{
		if(Sender == CurrentEditor) /* Executing */
		{
			if(!AfterProcessing)
			{
				switch(Command)
				{
					case ecChar:
					if(AChar == L'\x1b')
					{
						Cancel();
						Handled = true;
					}
					else
					{
						if(!(CurrentEditor->IsIdentChar(AChar)))
							Accept();
                /*don't handle the char*/
					}
					break;
					case ecLineBreak:
					{
						Accept();
						Handled = true;
					}
					break;
					case ecLeft:
					case ecSelLeft:
					if(CurrentString == L"")
						Handled = true;
					break;
					case ecDeleteLastChar:
					if(CurrentString == L"")
						Handled = true;
					break;
					case ecTab:
					Accept();
					break;
					case ecDeleteChar:
					case ecRight:
					case ecSelRight:
					case ecLostFocus:
					case ecGotFocus:
					;
					break; /*processed on AfterProcessing*/
					default:
					Cancel();
					break;
				}
			}
			else
			switch(Command)
			{ /* AfterProcessing */
				case ecLostFocus:
				case ecGotFocus:
				case ecDeleteChar:
				;
				break;
				case ecDeleteLastChar:
				case ecLeft:
				case ecSelLeft:
				case ecChar:
				CurrentString = GetCurrentEditorString();
				break;
				case ecRight:
				case ecSelRight:
				{
					S = GetCurrentEditorString();
					if(S == L"")
						Cancel();
					else
						CurrentString = S;
				}
				break;
				default:
				if(CurrentString != GetCurrentEditorString())
					Cancel();
				break;
			}
		} /*endif Sender = CurrentEditor*/
	}
}

void __fastcall TAbstractSynCompletion::SetCurrentString(const String Value)
{
	fCurrentString = Value;
}

void __fastcall TAbstractSynCompletion::AddEditor(TCustomSynEdit* aEditor)
{
	inherited::AddEditor(aEditor);
}


}  // namespace SynEditPlugins

