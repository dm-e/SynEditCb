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
__fastcall TAbstractSynCompletion::TAbstractSynCompletion(TComponent* AOwner) : inherited(AOwner) {}


const int ecPluginBase = 64000;
int gCurrentCommand = ecPluginBase;

TSynEditorCommand __fastcall NewPluginCommand()
{
	TSynEditorCommand result = 0;
	result = (TSynEditorCommand) gCurrentCommand;
	++gCurrentCommand;
	return result;
}

void __fastcall ReleasePluginCommand(TSynEditorCommand ACmd)
{
	if(ACmd == Pred(gCurrentCommand))
		gCurrentCommand = (int) ACmd;
}

/* TAbstractSynPlugin */

int __fastcall TAbstractSynPlugin::AddEditor(TCustomSynEdit* AEditor)
{
	int result = 0;
	if(fEditors == nullptr)
	{
		fEditors = new TList();
	}
	else
	{
		if(fEditors->IndexOf(AEditor) >= 0)
		{
			result = -1;
			return result;
		}
	}
	AEditor->FreeNotification(this);
	result = fEditors->Add(AEditor);
	DoAddEditor(AEditor);
	return result;
}

__fastcall TAbstractSynPlugin::~TAbstractSynPlugin()
{

  /* RemoveEditor will free fEditors when it reaches count = 0*/
	while(ASSIGNED(fEditors))
		RemoveEditor(Editors[0]);
	// inherited;
}

void __fastcall TAbstractSynPlugin::Notification(TComponent* AComponent, TOperation aOperation)
{
	inherited::Notification(AComponent, aOperation);
	if(aOperation == opRemove)
	{
		if((AComponent == Editor) || (ObjectIs(AComponent, TCustomSynEdit*)))
			RemoveEditor(((TCustomSynEdit*) AComponent));
	}
}

void __fastcall TAbstractSynPlugin::DoAddEditor(TCustomSynEdit* AEditor)
{
}

void __fastcall TAbstractSynPlugin::DoRemoveEditor(TCustomSynEdit* AEditor)
{
}

int __fastcall TAbstractSynPlugin::RemoveEditor(TCustomSynEdit* AEditor)
{
	int result = 0;
	if(fEditors == nullptr)
	{
		result = -1;
		return result;
	}
	result = fEditors->Remove(AEditor);
  //aEditor.RemoveFreeNotification(Self);
	if(fEditors->Count == 0)
	{
		delete fEditors;
		fEditors = nullptr;
	}
	if(result >= 0)
		DoRemoveEditor(AEditor);
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

TCustomSynEdit* __fastcall TAbstractSynPlugin::GetEditors(int AIndex)
{
	TCustomSynEdit* result = nullptr;
	result = ((TCustomSynEdit*) fEditors->Items[AIndex]);
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

void __fastcall TAbstractSynHookerPlugin::HookEditor(TCustomSynEdit* AEditor, TSynEditorCommand aCommandID, TShortCut aOldShortCut, TShortCut aNewShortCut)
{
	int IIndex = 0;
	TSynEditKeyStroke* iKeystroke = nullptr;
	Assert(aNewShortCut != 0);
  /* shortcurts aren't created while in design-time */
	if(Syneditplugins__2 * ComponentState == Syneditplugins__3)
	{
		if(((TSynEdit*) AEditor)->Keystrokes->FindShortcut(aNewShortCut) >= 0)
			throw new ESynKeyError(SYNS_EDuplicateShortcut);
		else
			return;
	}
  /* tries to update old Keystroke */
	if(aOldShortCut != 0)
	{
		IIndex = ((TSynEdit*) AEditor)->Keystrokes->FindShortcut(aOldShortCut);
		if(IIndex >= 0)
		{
			iKeystroke = ((TSynEdit*) AEditor)->Keystrokes->Items[IIndex];
			if(iKeystroke->Command == aCommandID)
			{
				iKeystroke->ShortCut = aNewShortCut;
				return;
			}
		}
	}
  /* new Keystroke */
	iKeystroke = ((TSynEdit*) AEditor)->Keystrokes->Add();
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
	AEditor->RegisterCommandHandler(OnCommand, this);
}

void __fastcall TAbstractSynHookerPlugin::UnHookEditor(TCustomSynEdit* AEditor, TSynEditorCommand aCommandID, TShortCut AShortCut)
{
	int IIndex = 0;
	AEditor->UnregisterCommandHandler(OnCommand);
	IIndex = ((TSynEdit*) AEditor)->Keystrokes->FindShortcut(AShortCut);
	if((IIndex >= 0) && (((TSynEdit*) AEditor)->Keystrokes->Items[IIndex]->Command == aCommandID))
		delete ((TSynEdit*) AEditor)->Keystrokes->Items[IIndex];
}

/* TAbstractSynHookerPlugin */

void __fastcall TAbstractSynSingleHookPlugin::accept()
{
	fState = psAccepting;
	try
	{
		DoAccept();
	}
	__finally
	{
		FCurrentEditor = nullptr;
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
		FCurrentEditor = nullptr;
		fState = psNone;
	}
}

__fastcall TAbstractSynSingleHookPlugin::TAbstractSynSingleHookPlugin(TComponent* AOwner)
 : inherited(AOwner),
			fCommandID(NewPluginCommand()),
			fState(psNone),
			FCurrentEditor(nullptr),
			FShortCut((TShortCut) 0)
{
	FShortCut = DefaultShortCut();
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

void __fastcall TAbstractSynSingleHookPlugin::DoAddEditor(TCustomSynEdit* AEditor)
{
	if(ShortCut != 0)
		HookEditor(AEditor, CommandID, (TShortCut) 0, ShortCut);
}

void __fastcall TAbstractSynSingleHookPlugin::Execute(TCustomSynEdit* AEditor)
{
	if(Executing())
		Cancel();
	Assert(FCurrentEditor == nullptr);
	FCurrentEditor = AEditor;
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
	result = FShortCut != DefaultShortCut();
	return result;
}

void __fastcall TAbstractSynSingleHookPlugin::DoRemoveEditor(TCustomSynEdit* AEditor)
{
	if(ShortCut != 0)
		UnHookEditor(AEditor, CommandID, ShortCut);
	if(Executing() && (CurrentEditor == AEditor))
		Cancel();
}

void __fastcall TAbstractSynSingleHookPlugin::SetShortCut(const TShortCut Value)
{
	int cEditor = 0;
	if(FShortCut != Value)
	{
		if(ASSIGNED(fEditors))
		{
			if(Value != 0)
			{
				int stop = 0;
				for(stop = fEditors->Count - 1, cEditor = 0; cEditor <= stop; cEditor++)
				{
					HookEditor(Editors[cEditor], CommandID, FShortCut, Value);
				}
			}
			else
			{
				int stop = 0;
				for(stop = fEditors->Count - 1, cEditor = 0; cEditor <= stop; cEditor++)
				{
					UnHookEditor(Editors[cEditor], CommandID, FShortCut);
				}
			}
		}
		FShortCut = Value;
	}
}

/* TAbstractSynCompletion */

String __fastcall TAbstractSynCompletion::GetCurrentEditorString()
{
	String result;
	String s;
	int Col = 0;
	s = CurrentEditor->LineText;
	if((CurrentEditor->CaretX > 1) && (CurrentEditor->CaretX - 1 <= s.Length()))
	{
		int stop = 0;
		for(stop = 1, Col = CurrentEditor->CaretX - 1; Col >= stop; Col--)
		{
			if(!CurrentEditor->IsIdentChar(s[Col]))
				break;
		}
		result = s.SubString(Col + 1, CurrentEditor->CaretX - Col - 1);
	}
	return result;
}

void __fastcall TAbstractSynCompletion::DoAccept()
{
	FCurrentString = L"";
}

void __fastcall TAbstractSynCompletion::DoCancel()
{
	FCurrentString = L"";
}

void __fastcall TAbstractSynCompletion::DoExecute()
{
	CurrentString = GetCurrentEditorString();
}

void __fastcall TAbstractSynCompletion::OnCommand(TObject* Sender, bool AfterProcessing, bool& Handled, TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData)
{
	String s;
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
							accept();
                /*don't handle the char*/
					}
					break;
					case ecLineBreak:
					{
						accept();
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
					accept();
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
					s = GetCurrentEditorString();
					if(s == L"")
						Cancel();
					else
						CurrentString = s;
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
	FCurrentString = Value;
}

void __fastcall TAbstractSynCompletion::AddEditor(TCustomSynEdit* AEditor)
{
	inherited::AddEditor(AEditor);
}


}  // namespace SynEditPlugins

