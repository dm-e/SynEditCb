#include <vcl.h>
#pragma hdrstop

#include "SynMacroRecorder.h"
#include <Vcl.Forms.hpp>
#include "SynEditMiscProcs.h"
#include <System.RTLConsts.hpp>
#include <System.SysUtils.hpp>
#include "OnLeavingScope.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Syneditkeycmds;
using namespace Syneditmiscprocs;
using namespace Syneditplugins;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Rtlconsts;
using namespace System::Sysutils;
using namespace Vcl::Forms;

namespace Synmacrorecorder
{
#define Synmacrorecorder__0 (TShiftState() << ssCtrl << ssShift)
#define Synmacrorecorder__1 (TShiftState() << ssCtrl << ssShift)
#define Synmacrorecorder__2 (TReplaceFlags() << rfReplaceAll)

__fastcall TSynBasicEvent::TSynBasicEvent() {}
__fastcall TSynCharEvent::TSynCharEvent() {}
__fastcall TSynStringEvent::TSynStringEvent() {}
__fastcall TSynPositionEvent::TSynPositionEvent() {}
__fastcall TSynDataEvent::TSynDataEvent() {}
__fastcall TSynMacroRecorder::TSynMacroRecorder(TComponent* aOwner) : inherited(aOwner) {}



/* TSynDataEvent */

void __fastcall TSynDataEvent::Initialize(TSynEditorCommand aCmd, WideChar aChar, void* aData)
{
	fCommand = aCmd;
	Assert(aChar == L'\x00');
	fData = aData;
}

void __fastcall TSynDataEvent::LoadFromStream(TStream* aStream)
{
	aStream->Read((void**) fData, (NativeInt) sizeof(fData));
}

void __fastcall TSynDataEvent::Playback(TCustomSynEdit* aEditor)
{
	aEditor->CommandProcessor(Command, L'\x00', fData);
}

void __fastcall TSynDataEvent::SaveToStream(TStream* aStream)
{
	inherited::SaveToStream(aStream);
	aStream->Write(fData, (NativeInt) sizeof(fData));
}

/* TCustomSynMacroRecorder */

void __fastcall TCustomSynMacroRecorder::AddCustomEvent(TSynMacroEvent* aEvent)
{
	InsertCustomEvent(EventCount, aEvent);
}

void __fastcall TCustomSynMacroRecorder::AddEditor(TCustomSynEdit* aEditor)
{
	inherited::AddEditor(aEditor);
}

void __fastcall TCustomSynMacroRecorder::AddEvent(TSynEditorCommand aCmd, WideChar aChar, void* aData)
{
	InsertEvent(EventCount, aCmd, aChar, aData);
}

void __fastcall TCustomSynMacroRecorder::Clear()
{
	int I = 0;
	TObject* Obj = nullptr;
	if(ASSIGNED(fEvents))
	{
		int stop = 0;
		for(stop = 0, I = fEvents->Count - 1; I >= stop; I--)
		{
			Obj = ((TObject*) fEvents->Items[I]);
			fEvents->Delete(I);
			delete Obj;
		}
		FreeAndNil(&fEvents);
	}
}

__fastcall TCustomSynMacroRecorder::TCustomSynMacroRecorder(TComponent* aOwner)
 : inherited(aOwner),
			fSaveMarkerPos(false),
			fCurrentEditor(nullptr),
			fState(msStopped),
			fEvents(nullptr)
{
	fMacroName = L"unnamed";
	fCommandIDs[mcRecord] = NewPluginCommand();
	fCommandIDs[mcPlayback] = NewPluginCommand();
	fShortCuts[mcRecord] = Menus::ShortCut((WORD) int(L'R'), Synmacrorecorder__0);
	fShortCuts[mcPlayback] = Menus::ShortCut((WORD) int(L'P'), Synmacrorecorder__1);
}

TSynMacroEvent* __fastcall TCustomSynMacroRecorder::CreateMacroEvent(TSynEditorCommand aCmd)
{
	TSynMacroEvent* result = nullptr;

	auto WantDefaultEvent = [&](TSynMacroEvent*& aEvent) -> bool 
	{
		bool result = false;
		if(ASSIGNED(OnUserCommand))
			OnUserCommand(this, aCmd, aEvent);
		result = aEvent == nullptr;
		return result;
	};
	switch(aCmd)
	{
		case ecGotoXY:
		case ecSelGotoXY:
		case 351: case 352: case 353: case 354: case 355: case 356: case 357: case 358: case 359: case 360:
		{
			result = new TSynPositionEvent();
			((TSynPositionEvent*) result)->Command = aCmd;
		}
		break;
		case ecChar:
		result = new TSynCharEvent();
		break;
		case ecString:
		result = new TSynStringEvent();
		break;
		default:
		{
			result = nullptr;
			if((aCmd < ecUserFirst) || WantDefaultEvent(result))
			{
				result = new TSynBasicEvent();
				((TSynBasicEvent*) result)->Command = aCmd;
			}
		}
		break;
	}
	return result;
}

void __fastcall TCustomSynMacroRecorder::DeleteEvent(int aIndex)
{
	void* iObj = nullptr;
	iObj = fEvents->Items[aIndex];
	fEvents->Delete(aIndex);
	delete ((TObject*) iObj);
}

__fastcall TCustomSynMacroRecorder::~TCustomSynMacroRecorder()
{
	Clear();
	// inherited;
	ReleasePluginCommand(PlaybackCommandID);
	ReleasePluginCommand(RecordCommandID);
}

void __fastcall TCustomSynMacroRecorder::DoAddEditor(TCustomSynEdit* aEditor)
{
	HookEditor(aEditor, RecordCommandID, (TShortCut) 0, RecordShortCut);
	HookEditor(aEditor, PlaybackCommandID, (TShortCut) 0, PlaybackShortCut);
}

void __fastcall TCustomSynMacroRecorder::DoRemoveEditor(TCustomSynEdit* aEditor)
{
	UnHookEditor(aEditor, RecordCommandID, RecordShortCut);
	UnHookEditor(aEditor, PlaybackCommandID, PlaybackShortCut);
}

void __fastcall TCustomSynMacroRecorder::Error(const String aMsg)
{
	throw new Exception(aMsg);
}

TSynMacroEvent* __fastcall TCustomSynMacroRecorder::GetEvent(int aIndex)
{
	TSynMacroEvent* result = nullptr;
	result = ((TSynMacroEvent*) fEvents->Items[aIndex]);
	return result;
}

int __fastcall TCustomSynMacroRecorder::GetEventCount()
{
	int result = 0;
	if(fEvents == nullptr)
		result = 0;
	else
		result = fEvents->Count;
	return result;
}

bool __fastcall TCustomSynMacroRecorder::GetIsEmpty()
{
	bool result = false;
	result = (fEvents == nullptr) || (fEvents->Count == 0);
	return result;
}

void __fastcall TCustomSynMacroRecorder::InsertCustomEvent(int aIndex, TSynMacroEvent* aEvent)
{
	if(fEvents == nullptr)
		fEvents = new TList();
	fEvents->Insert(aIndex, aEvent);
}

void __fastcall TCustomSynMacroRecorder::InsertEvent(int aIndex, TSynEditorCommand aCmd, WideChar aChar, void* aData)
{
	TSynMacroEvent* iEvent = nullptr;
	iEvent = CreateMacroEvent(aCmd);
	try
	{
		iEvent->Initialize(aCmd, aChar, aData);
		InsertCustomEvent(aIndex, iEvent);
	}
	catch(...)
	{
		delete iEvent;
		throw ;
	}
}

void __fastcall TCustomSynMacroRecorder::LoadFromStream(TStream* aSrc)
{
	LoadFromStreamEx(aSrc, true);
}

void __fastcall TCustomSynMacroRecorder::LoadFromStreamEx(TStream* aSrc, bool aClear)
{
	TSynEditorCommand iCommand = 0;
	TSynMacroEvent* iEvent = nullptr;
	int cnt = 0;
	int i = 0;
	Stop();
	if(aClear)
		Clear();
	fEvents = new TList();
	aSrc->Read((void**)&cnt, (NativeInt) sizeof(cnt));
	i = 0;
	fEvents->Capacity = (NativeInt) ((unsigned __int64)(aSrc->Size / /*div*/ sizeof(TSynEditorCommand)));
	while((aSrc->Position < aSrc->Size) && (i < cnt))
	{
		aSrc->Read((void**)&iCommand, (NativeInt) sizeof(TSynEditorCommand));
		iEvent = CreateMacroEvent(iCommand);
		iEvent->Initialize(iCommand, L'\x00', nullptr);
		iEvent->LoadFromStream(aSrc);
		fEvents->Add(iEvent);
		++i;
	}
}

// TODO: Sender could be also something else then a TCustomSynedit(namely a TObject) but the code below assumes it is a TCustomSynedit even if Sender is of type TObject.

void __fastcall TCustomSynMacroRecorder::OnCommand(TObject* Sender, bool AfterProcessing, bool& Handled, TSynEditorCommand& Command, WideChar& aChar, void* Data, void* HandlerData)
{
	TSynMacroEvent* iEvent = nullptr;
	if(AfterProcessing)
	{
		if((Sender == fCurrentEditor) && (State == msRecording) && (!Handled))
		{
			iEvent = CreateMacroEvent(Command);
			iEvent->Initialize(Command, aChar, Data);
			fEvents->Add(iEvent);
			if(SaveMarkerPos && (Command >= ecSetMarker0) && (Command <= ecSetMarker9) && (Data == nullptr))
			{
				((TSynPositionEvent*) iEvent)->Position = fCurrentEditor->CaretXY;
			}
		}
	}
	else

    /*not AfterProcessing*/
	{
		switch(State)
		{
			case msStopped:
			if(Command == RecordCommandID)
			{
				RecordMacro(((TCustomSynEdit*) Sender));
				Handled = true;
			}
			else
			{
				if(Command == PlaybackCommandID)
				{
					PlaybackMacro(((TCustomSynEdit*) Sender));
					Handled = true;
				}
			}
			break;
			case msPlaying:
			;
			break;
			case msPaused:
			if(Command == PlaybackCommandID)
			{
				Resume();
				Handled = true;
			}
			break;
			case msRecording:
			if(Command == PlaybackCommandID)
			{
				Pause();
				Handled = true;
			}
			else
			{
				if(Command == RecordCommandID)
				{
					Stop();
					Handled = true;
				}
			}
			break;
			default:
			  ;
			break;
		}
	}
}

void __fastcall TCustomSynMacroRecorder::Pause()
{
	if(State != msRecording)
		Error(sCannotPause);
	fState = msPaused;
	StateChanged();
}

void __fastcall TCustomSynMacroRecorder::PlaybackMacro(TCustomSynEdit* aEditor)
{
	int cEvent = 0;
	if(State != msStopped)
		Error(sCannotPlay);
	fState = msPlaying;
	try
	{
		int stop = 0;
		StateChanged();
		for(stop = EventCount - 1, cEvent = 0; cEvent <= stop; cEvent++)
		{
			Events[cEvent]->Playback(aEditor);
			if(State != msPlaying)
				break;
		}
	}
	__finally
	{
		if(State == msPlaying)
		{
			fState = msStopped;
			StateChanged();
		}
	}
}

void __fastcall TCustomSynMacroRecorder::RecordMacro(TCustomSynEdit* aEditor)
{
	if(fState != msStopped)
		Error(sCannotRecord);
	Clear();
	fEvents = new TList();
	fEvents->Capacity = 512;
	fState = msRecording;
	fCurrentEditor = aEditor;
	StateChanged();
}

void __fastcall TCustomSynMacroRecorder::RemoveEditor(TCustomSynEdit* aEditor)
{
	inherited::RemoveEditor(aEditor);
}

void __fastcall TCustomSynMacroRecorder::Resume()
{
	if(fState != msPaused)
		Error(sCannotResume);
	fState = msRecording;
	StateChanged();
}

void __fastcall TCustomSynMacroRecorder::SaveToStream(TStream* aDest)
{
	int cEvent = 0;
	int eCnt = 0;
	int stop = 0;
	eCnt = EventCount;
	aDest->Write(&eCnt, (NativeInt) sizeof(eCnt));
	for(stop = eCnt - 1, cEvent = 0; cEvent <= stop; cEvent++)
	{
		Events[cEvent]->SaveToStream(aDest);
	}
}

void __fastcall TCustomSynMacroRecorder::SetShortCut(int Index, const TShortCut Value)
{
	int cEditor = 0;
	if(fShortCuts[((TSynMacroCommand) Index)] != Value)
	{
		if(ASSIGNED(fEditors))
		{
			if(Value != 0)
			{
				int stop = 0;
				for(stop = fEditors->Count - 1, cEditor = 0; cEditor <= stop; cEditor++)
				{
					HookEditor(Editors[cEditor], fCommandIDs[((TSynMacroCommand) Index)], fShortCuts[((TSynMacroCommand) Index)], Value);
				}
			}
			else
			{
				int stop = 0;
				for(stop = fEditors->Count - 1, cEditor = 0; cEditor <= stop; cEditor++)
				{
					UnHookEditor(Editors[cEditor], fCommandIDs[((TSynMacroCommand) Index)], fShortCuts[((TSynMacroCommand) Index)]);
				}
			}
		}
		fShortCuts[((TSynMacroCommand) Index)] = Value;
	}
}

void __fastcall TCustomSynMacroRecorder::StateChanged()
{
	if(ASSIGNED(OnStateChange))
		OnStateChange(this);
}

void __fastcall TCustomSynMacroRecorder::Stop()
{
	if(fState == msStopped)
		return;
	fState = msStopped;
	fCurrentEditor = nullptr;
	if(fEvents->Count == 0)
		FreeAndNil(&fEvents);
	StateChanged();
}

String __fastcall TCustomSynMacroRecorder::GetAsString()
{
	String result;
	int i = 0;
	String eStr;
	result = String(L"macro ") + MacroName + L"\x0d\x0a" + L"begin" + L"\x0d\x0a";
	if(ASSIGNED(fEvents))
	{
		int stop = 0;
		for(stop = fEvents->Count - 1, i = 0; i <= stop; i++)
		{
			eStr = Events[i]->AsString;
			if(eStr != L"")
				result = result + L"  " + eStr + L"\x0d\x0a";
		}
	}
	result = result + L"end";
	return result;
}

TSynEditorCommand __fastcall TCustomSynMacroRecorder::GetPlaybackCommandID()
{
	TSynEditorCommand result = 0;
	result = fCommandIDs[mcPlayback];
	return result;
}

TShortCut __fastcall TCustomSynMacroRecorder::GetPlaybackShortCut(int Index)
{
	TShortCut result = (TShortCut) 0;
	result = fShortCuts[mcPlayback];
	return result;
}

TSynEditorCommand __fastcall TCustomSynMacroRecorder::GetRecordCommandID()
{
	TSynEditorCommand result = 0;
	result = fCommandIDs[mcRecord];
	return result;
}

TShortCut __fastcall TCustomSynMacroRecorder::GetRecordShortCut(int Index)
{
	TShortCut result = (TShortCut) 0;
	result = fShortCuts[mcRecord];
	return result;
}

void __fastcall TCustomSynMacroRecorder::SetAsString(const String Value)
{
	int i = 0;
	int p = 0;
	int Cmd = 0;
	TStrings* S = nullptr;
	String cmdStr;
	TSynMacroEvent* iEvent = nullptr;
	Stop();
	Clear();
	fEvents = new TList();
  // process file line by line and create events
	S = new TStringList();
	{
		auto olsLambda = onLeavingScope([&] 
		{
			delete S;
		});
		int stop = 0;
		S->Text = Value;
		for(stop = S->Count - 1, i = 0; i <= stop; i++)
		{
			cmdStr = Trim(S->Strings[i]);
			p = Pos(L" ", cmdStr);
			if(p == 0)
				p = cmdStr.Length() + 1;
			Cmd = ecNone;
			if(IdentToEditorCommand(cmdStr.SubString(1, p - 1), Cmd))  // D2 needs type-cast
			{
				cmdStr.Delete(1, 	p);
				iEvent = CreateMacroEvent((TSynEditorCommand) Cmd);
				try
				{
					fEvents->Add(iEvent);
					iEvent->InitEventParameters(cmdStr);
				}
				catch(...)
				{
					delete iEvent;
				}
			}
		}
	}
}

void __fastcall TCustomSynMacroRecorder::LoadFromFile(String aFilename)
{
	TFileStream* F = nullptr;
	F = new TFileStream(aFilename, (WORD) fmOpenRead);
	try
	{
		LoadFromStream(F);
		MacroName = ChangeFileExt(ExtractFileName(aFilename), L"");
	}
	__finally
	{
		delete F;
	}
}

void __fastcall TCustomSynMacroRecorder::SaveToFile(String aFilename)
{
	TFileStream* F = nullptr;
	F = new TFileStream(aFilename, (WORD) fmCreate);
	try
	{
		SaveToStream(F);
	}
	__finally
	{
		delete F;
	}
}

/* TSynBasicEvent */

String __fastcall TSynBasicEvent::GetAsString()
{
	String result;
	String Ident;
	EditorCommandToIdent((int) Command, Ident);
	result = Ident;
	if(RepeatCount > 1)
		result = result + L" " + IntToStr((int) RepeatCount);
	return result;
}

void __fastcall TSynBasicEvent::InitEventParameters(String aStr)
{

  // basic events have no parameters but can contain an optional repeat count
	RepeatCount = (Byte) StrToIntDef(Trim(aStr), 1);
}

void __fastcall TSynBasicEvent::Initialize(TSynEditorCommand aCmd, WideChar aChar, void* aData)
{
	Command = aCmd;
}

void __fastcall TSynBasicEvent::LoadFromStream(TStream* aStream)
{
	aStream->Read((void**)&fRepeatCount, (NativeInt) sizeof(fRepeatCount));
}

void __fastcall TSynBasicEvent::Playback(TCustomSynEdit* aEditor)
{
	int i = 0;
	int stop = 0;
	for(stop = RepeatCount, i = 1; i <= stop; i++)
	{
		aEditor->CommandProcessor(Command, L'\x00', nullptr);
	}
}

void __fastcall TSynBasicEvent::SaveToStream(TStream* aStream)
{
	aStream->Write(&Command, (NativeInt) sizeof(TSynEditorCommand));
	aStream->Write(&RepeatCount, (NativeInt) sizeof(RepeatCount));
}

/* TSynCharEvent */

String __fastcall TSynCharEvent::GetAsString()
{
	String result;
	String Ident;
	EditorCommandToIdent(ecChar, Ident);
	result = Ident + L" " + String(Key);
	if(RepeatCount > 1)
		result = result + L" " + IntToStr((int) RepeatCount);
	return result;
}

void __fastcall TSynCharEvent::InitEventParameters(String aStr)
{

  // aStr should be a Key value one character in length
  // with an optional repeat count whitespace separated
	if(aStr.Length() >= 1)
		Key = aStr[1];
	else
		Key = L' ';
	aStr.Delete(1, 	1); // if possible delete the first character
	RepeatCount = (Byte) StrToIntDef(Trim(aStr), 1);
}

void __fastcall TSynCharEvent::Initialize(TSynEditorCommand aCmd, WideChar aChar, void* aData)
{
	Key = aChar;
	Assert(aData == nullptr);
}

void __fastcall TSynCharEvent::LoadFromStream(TStream* aStream)
{
	aStream->Read((void**)&fKey, (NativeInt) sizeof(Key));
	aStream->Read((void**)&fRepeatCount, (NativeInt) sizeof(fRepeatCount));
}

void __fastcall TSynCharEvent::Playback(TCustomSynEdit* aEditor)
{
	int i = 0;
	int stop = 0;
	for(stop = RepeatCount, i = 1; i <= stop; i++)
	{
		aEditor->CommandProcessor((TSynEditorCommand) ecChar, Key, nullptr);
	}
}

void __fastcall TSynCharEvent::SaveToStream(TStream* aStream)
{
	const TSynEditorCommand iCharCommand = ecChar;
	aStream->Write(&iCharCommand, (NativeInt) sizeof(TSynEditorCommand));
	aStream->Write(&Key, (NativeInt) sizeof(Key));
	aStream->Write(&RepeatCount, (NativeInt) sizeof(RepeatCount));
}

/* TSynPositionEvent */

String __fastcall TSynPositionEvent::GetAsString()
{
	String result;
	result = inherited::GetAsString();
  // add position data here
	result = result + Format(L" (%d, %d)", ARRAYOFCONST((Position.Char, Position.Line)));
	if(RepeatCount > 1)
		result = result + L" " + IntToStr((int) RepeatCount);
	return result;
}

void __fastcall TSynPositionEvent::InitEventParameters(String aStr)
{
	int i = 0;
	int o = 0;
	int c = 0;
	int x = 0;
	int y = 0;
	String valStr;
	inherited::InitEventParameters(aStr);
  // aStr should be (x, y) with optional repeat count whitespace separated
	aStr = Trim(aStr);
	i = Pos(L",", aStr);
	o = Pos(L"(", aStr);
	c = Pos(L")", aStr);
	if((!((i == 0) || (o == 0) || (c == 0))) && ((i > o) && (i < c)))
	{
		valStr = aStr.SubString(o + 1, i - o - 1);
		x = StrToIntDef(valStr, 1);
		aStr.Delete(1, 	i);
		aStr = Trim(aStr);
		c = Pos(L")", aStr);
		valStr = aStr.SubString(1, c - 1);
		y = StrToIntDef(valStr, 1);
		Position = BufferCoord(x, y);
		aStr.Delete(1, 	c);
		aStr = Trim(aStr);
		RepeatCount = (Byte) StrToIntDef(aStr, 1);
	}
}

void __fastcall TSynPositionEvent::Initialize(TSynEditorCommand aCmd, WideChar aChar, void* aData)
{
	inherited::Initialize(aCmd, aChar, aData);
	if(aData != nullptr)
		Position = (*(TBufferCoord*) aData);
	else
		Position = BufferCoord(0, 0);
}

void __fastcall TSynPositionEvent::LoadFromStream(TStream* aStream)
{
	aStream->Read((void**)&fPosition, (NativeInt) sizeof(Position));
}

void __fastcall TSynPositionEvent::Playback(TCustomSynEdit* aEditor)
{
	if((Position.Char != 0) || (Position.Line != 0))
		aEditor->CommandProcessor(Command, L'\x00', &Position);
	else
		aEditor->CommandProcessor(Command, L'\x00', nullptr);
}

void __fastcall TSynPositionEvent::SaveToStream(TStream* aStream)
{
	inherited::SaveToStream(aStream);
	aStream->Write(&Position, (NativeInt) sizeof(Position));
}

/* TSynStringEvent */

String __fastcall TSynStringEvent::GetAsString()
{
	String result;
	String Ident;
	EditorCommandToIdent(ecString, Ident);
	result = Ident + L" " + AnsiQuotedStr(Value, L'\x27');
	if(RepeatCount > 1)
		result = result + L" " + IntToStr((int) RepeatCount);
	return result;
}

void __fastcall TSynStringEvent::InitEventParameters(String aStr)
{
	int o = 0;
	int c = 0;
	String valStr;                      
  // aStr = 'test' with optional whitespace separated repeat count
	o = Pos(L"\'", aStr);
	c = LastDelimiter(L"\'", aStr);
	valStr = aStr.SubString(o + 1, c - o - 1);
	Value = StringReplace(valStr, L"'", L"\'", Synmacrorecorder__2);
	aStr.Delete(1, 	c);
	RepeatCount = (Byte) StrToIntDef(Trim(aStr), 1);
}

void __fastcall TSynStringEvent::Initialize(TSynEditorCommand aCmd, WideChar aChar, void* aData)
{
	Value = String((wchar_t*)aData);
}

void __fastcall TSynStringEvent::LoadFromStream(TStream* aStream)
{
	int l = 0;
	PWideChar Buff = nullptr;
	aStream->Read((void**)&l, (NativeInt) sizeof(l));
	Buff = (PWideChar) GetMemory(l * sizeof(WideChar));
	try
	{
		FillMemory(Buff, (NativeUInt) l, 0);
		aStream->Read((void**)Buff, (NativeInt) (l * sizeof(WideChar)));
		fString = Buff;
	}
	__finally
	{
		FreeMemory(Buff);
	}
	aStream->Read((void**)&fRepeatCount, (NativeInt) sizeof(fRepeatCount));
}

void __fastcall TSynStringEvent::Playback(TCustomSynEdit* aEditor)
{
	int i = 0;
	int j = 0;
	int stop = 0;
	for(stop = RepeatCount, j = 1; j <= stop; j++)
	{
//    aEditor.CommandProcessor( ecString, #0, Pointer(Value) );
    // SynEdit doesn't actually support the ecString command so we convert
    // it into ecChar commands
		int stop1 = 0;
		for(stop1 = Value.Length(), i = 1; i <= stop1; i++)
		{
			aEditor->CommandProcessor((TSynEditorCommand) ecChar, Value[i], nullptr);
		}
	}
}

void __fastcall TSynStringEvent::SaveToStream(TStream* aStream)
{
	const TSynEditorCommand StrCommand = ecString;
	int l = 0;
	PWideChar Buff = nullptr;
	aStream->Write(&StrCommand, (NativeInt) sizeof(StrCommand));
	l = Value.Length() + 1;
	aStream->Write(&l, (NativeInt) sizeof(l));
	Buff = (PWideChar) GetMemory(l * sizeof(WideChar));
	try
	{
		FillMemory(Buff, (NativeUInt) l, 0);
		StrCopy(Buff, ustr2pwchar(Value));
		aStream->Write(Buff, (NativeInt) (l * sizeof(WideChar)));
	}
	__finally
	{
		FreeMemory(Buff);
	}
	aStream->Write(&RepeatCount, (NativeInt) sizeof(RepeatCount));
}


/* TSynMacroEvent */

__fastcall TSynMacroEvent::TSynMacroEvent()
 : fRepeatCount(1)
{
	//# inherited::Create();
}


}  // namespace SynMacroRecorder

