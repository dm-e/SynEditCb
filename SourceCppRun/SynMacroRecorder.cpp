#include <vcl.h>
#pragma hdrstop

#include "SynMacroRecorder.h"
#include <Vcl.Forms.hpp>
#include "SynEditMiscProcs.h"
#include <System.RTLConsts.hpp>
#include <System.SysUtils.hpp>
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
__fastcall TSynMacroRecorder::TSynMacroRecorder(TComponent* AOwner) : inherited(AOwner) {}



/* TSynDataEvent */

void __fastcall TSynDataEvent::Initialize(TSynEditorCommand ACmd, WideChar AChar, void* AData)
{
	FCommand = ACmd;
	Assert(AChar == L'\x00');
	FData = AData;
}

void __fastcall TSynDataEvent::LoadFromStream(TStream* AStream)
{
	AStream->Read((void**) FData, sizeof(FData));
}

void __fastcall TSynDataEvent::Playback(TCustomSynEdit* AEditor)
{
	AEditor->CommandProcessor(Command, L'\x00', FData);
}

void __fastcall TSynDataEvent::SaveToStream(TStream* AStream)
{
	inherited::SaveToStream(AStream);
	AStream->Write(FData, sizeof(FData));
}

/* TCustomSynMacroRecorder */

void __fastcall TCustomSynMacroRecorder::AddCustomEvent(TSynMacroEvent* AEvent)
{
	InsertCustomEvent(EventCount, AEvent);
}

void __fastcall TCustomSynMacroRecorder::AddEditor(TCustomSynEdit* AEditor)
{
	inherited::AddEditor(AEditor);
}

void __fastcall TCustomSynMacroRecorder::AddEvent(TSynEditorCommand ACmd, WideChar AChar, void* AData)
{
	InsertEvent(EventCount, ACmd, AChar, AData);
}

void __fastcall TCustomSynMacroRecorder::Clear()
{
	int i = 0;
	TObject* Obj = nullptr;
	if(ASSIGNED(FEvents))
	{
		int stop = 0;
		for(stop = 0, i = FEvents->Count - 1; i >= stop; i--)
		{
			Obj = ((TObject*) FEvents->Items[i]);
			FEvents->Delete(i);
			delete Obj;
		}
		FreeAndNil(&FEvents);
	}
}

__fastcall TCustomSynMacroRecorder::TCustomSynMacroRecorder(TComponent* AOwner)
 : inherited(AOwner),
			fSaveMarkerPos(false),
			FCurrentEditor(nullptr),
			fState(msStopped),
			FEvents(nullptr)
{
	fMacroName = L"unnamed";
	fCommandIDs[mcRecord] = NewPluginCommand();
	fCommandIDs[mcPlayback] = NewPluginCommand();
	fShortCuts[mcRecord] = Menus::ShortCut((WORD) int(L'R'), Synmacrorecorder__0);
	fShortCuts[mcPlayback] = Menus::ShortCut((WORD) int(L'P'), Synmacrorecorder__1);
}

TSynMacroEvent* __fastcall TCustomSynMacroRecorder::CreateMacroEvent(TSynEditorCommand ACmd)
{
	TSynMacroEvent* result = nullptr;

	auto WantDefaultEvent = [&](TSynMacroEvent*& AEvent) -> bool 
	{
		bool result = false;
		if(ASSIGNED(OnUserCommand))
			OnUserCommand(this, ACmd, AEvent);
		result = AEvent == nullptr;
		return result;
	};
	switch(ACmd)
	{
		case ecGotoXY:
		case ecSelGotoXY:
		case 351: case 352: case 353: case 354: case 355: case 356: case 357: case 358: case 359: case 360:
		{
			result = new TSynPositionEvent();
			((TSynPositionEvent*) result)->Command = ACmd;
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
			if((ACmd < ecUserFirst) || WantDefaultEvent(result))
			{
				result = new TSynBasicEvent();
				((TSynBasicEvent*) result)->Command = ACmd;
			}
		}
		break;
	}
	return result;
}

void __fastcall TCustomSynMacroRecorder::DeleteEvent(int AIndex)
{
	void* iObj = nullptr;
	iObj = FEvents->Items[AIndex];
	FEvents->Delete(AIndex);
	delete ((TObject*) iObj);
}

__fastcall TCustomSynMacroRecorder::~TCustomSynMacroRecorder()
{
	Clear();
	// inherited;
	ReleasePluginCommand(PlaybackCommandID);
	ReleasePluginCommand(RecordCommandID);
}

void __fastcall TCustomSynMacroRecorder::DoAddEditor(TCustomSynEdit* AEditor)
{
	HookEditor(AEditor, RecordCommandID, (TShortCut) 0, RecordShortCut);
	HookEditor(AEditor, PlaybackCommandID, (TShortCut) 0, PlaybackShortCut);
}

void __fastcall TCustomSynMacroRecorder::DoRemoveEditor(TCustomSynEdit* AEditor)
{
	UnHookEditor(AEditor, RecordCommandID, RecordShortCut);
	UnHookEditor(AEditor, PlaybackCommandID, PlaybackShortCut);
}

void __fastcall TCustomSynMacroRecorder::Error(const String aMsg)
{
	throw new Exception(aMsg);
}

TSynMacroEvent* __fastcall TCustomSynMacroRecorder::GetEvent(int AIndex)
{
	TSynMacroEvent* result = nullptr;
	result = ((TSynMacroEvent*) FEvents->Items[AIndex]);
	return result;
}

int __fastcall TCustomSynMacroRecorder::GetEventCount()
{
	int result = 0;
	if(FEvents == nullptr)
		result = 0;
	else
		result = FEvents->Count;
	return result;
}

bool __fastcall TCustomSynMacroRecorder::GetIsEmpty()
{
	bool result = false;
	result = (FEvents == nullptr) || (FEvents->Count == 0);
	return result;
}

void __fastcall TCustomSynMacroRecorder::InsertCustomEvent(int AIndex, TSynMacroEvent* AEvent)
{
	if(FEvents == nullptr)
		FEvents = new TList();
	FEvents->Insert(AIndex, AEvent);
}

void __fastcall TCustomSynMacroRecorder::InsertEvent(int AIndex, TSynEditorCommand ACmd, WideChar AChar, void* AData)
{
	TSynMacroEvent* IEvent = nullptr;
	IEvent = CreateMacroEvent(ACmd);
	try
	{
		IEvent->Initialize(ACmd, AChar, AData);
		InsertCustomEvent(AIndex, IEvent);
	}
	catch(...)
	{
		delete IEvent;
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
	TSynMacroEvent* IEvent = nullptr;
	int cnt = 0;
	int i = 0;
	Stop();
	if(aClear)
		Clear();
	FEvents = new TList();
	aSrc->Read((void**)&cnt, sizeof(cnt));
	i = 0;
	FEvents->Capacity = (__int64)(aSrc->Size / /*div*/ sizeof(TSynEditorCommand));
	while((aSrc->Position < aSrc->Size) && (i < cnt))
	{
		aSrc->Read((void**)&iCommand, sizeof(TSynEditorCommand));
		IEvent = CreateMacroEvent(iCommand);
		IEvent->Initialize(iCommand, L'\x00', nullptr);
		IEvent->LoadFromStream(aSrc);
		FEvents->Add(IEvent);
		++i;
	}
}

// TODO: Sender could be also something else then a TCustomSynedit(namely a TObject) but the code below assumes it is a TCustomSynedit even if Sender is of type TObject.

void __fastcall TCustomSynMacroRecorder::OnCommand(TObject* Sender, bool AfterProcessing, bool& Handled, TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData)
{
	TSynMacroEvent* IEvent = nullptr;
	if(AfterProcessing)
	{
		if((Sender == FCurrentEditor) && (State == msRecording) && (!Handled))
		{
			IEvent = CreateMacroEvent(Command);
			IEvent->Initialize(Command, AChar, Data);
			FEvents->Add(IEvent);
			if(SaveMarkerPos && (Command >= ecSetMarker0) && (Command <= ecSetMarker9) && (Data == nullptr))
			{
				((TSynPositionEvent*) IEvent)->Position = FCurrentEditor->CaretXY;
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
				pause();
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

void __fastcall TCustomSynMacroRecorder::pause()
{
	if(State != msRecording)
		Error(sCannotPause);
	fState = msPaused;
	StateChanged();
}

void __fastcall TCustomSynMacroRecorder::PlaybackMacro(TCustomSynEdit* AEditor)
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
			Events[cEvent]->Playback(AEditor);
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

void __fastcall TCustomSynMacroRecorder::RecordMacro(TCustomSynEdit* AEditor)
{
	if(fState != msStopped)
		Error(sCannotRecord);
	Clear();
	FEvents = new TList();
	FEvents->Capacity = 512;
	fState = msRecording;
	FCurrentEditor = AEditor;
	StateChanged();
}

void __fastcall TCustomSynMacroRecorder::RemoveEditor(TCustomSynEdit* AEditor)
{
	inherited::RemoveEditor(AEditor);
}

void __fastcall TCustomSynMacroRecorder::Resume()
{
	if(fState != msPaused)
		Error(sCannotResume);
	fState = msRecording;
	StateChanged();
}

void __fastcall TCustomSynMacroRecorder::SaveToStream(TStream* ADest)
{
	int cEvent = 0;
	int eCnt = 0;
	int stop = 0;
	eCnt = EventCount;
	ADest->Write(&eCnt, sizeof(eCnt));
	for(stop = eCnt - 1, cEvent = 0; cEvent <= stop; cEvent++)
	{
		Events[cEvent]->SaveToStream(ADest);
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
	FCurrentEditor = nullptr;
	if(FEvents->Count == 0)
		FreeAndNil(&FEvents);
	StateChanged();
}

String __fastcall TCustomSynMacroRecorder::GetAsString()
{
	String result;
	int i = 0;
	String eStr;
	result = String(L"macro ") + MacroName + L"\x0d\x0a" + L"begin" + L"\x0d\x0a";
	if(ASSIGNED(FEvents))
	{
		int stop = 0;
		for(stop = FEvents->Count - 1, i = 0; i <= stop; i++)
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
	int P = 0;
	int cmd = 0;
	TStrings* s = nullptr;
	String cmdStr;
	TSynMacroEvent* IEvent = nullptr;
	Stop();
	Clear();
	FEvents = new TList();
  // process file line by line and create events
	s = new TStringList();
	try
	{
		int stop = 0;
		s->Text = Value;
		for(stop = s->Count - 1, i = 0; i <= stop; i++)
		{
			cmdStr = Trim(s->Strings[i]);
			P = Pos(L" ", cmdStr);
			if(P == 0)
				P = cmdStr.Length() + 1;
			cmd = ecNone;
			if(IdentToEditorCommand(cmdStr.SubString(1, P - 1), cmd))  // D2 needs type-cast
			{
				cmdStr.Delete(1, 	P);
				IEvent = CreateMacroEvent((TSynEditorCommand) cmd);
				try
				{
					FEvents->Add(IEvent);
					IEvent->InitEventParameters(cmdStr);
				}
				catch(...)
				{
					delete IEvent;
				}
			}
		}
	}
	__finally
	{
		delete s;
	}
}

void __fastcall TCustomSynMacroRecorder::LoadFromFile(String AFileName)
{
	TFileStream* f = nullptr;
	f = new TFileStream(AFileName, (WORD) fmOpenRead);
	try
	{
		LoadFromStream(f);
		MacroName = ChangeFileExt(ExtractFileName(AFileName), L"");
	}
	__finally
	{
		delete f;
	}
}

void __fastcall TCustomSynMacroRecorder::SaveToFile(String AFileName)
{
	TFileStream* f = nullptr;
	f = new TFileStream(AFileName, (WORD) fmCreate);
	try
	{
		SaveToStream(f);
	}
	__finally
	{
		delete f;
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

void __fastcall TSynBasicEvent::InitEventParameters(String AStr)
{

  // basic events have no parameters but can contain an optional repeat count
	RepeatCount = (unsigned char) StrToIntDef(Trim(AStr), 1);
}

void __fastcall TSynBasicEvent::Initialize(TSynEditorCommand ACmd, WideChar AChar, void* AData)
{
	Command = ACmd;
}

void __fastcall TSynBasicEvent::LoadFromStream(TStream* AStream)
{
	AStream->Read((void**)&fRepeatCount, sizeof(fRepeatCount));
}

void __fastcall TSynBasicEvent::Playback(TCustomSynEdit* AEditor)
{
	int i = 0;
	int stop = 0;
	for(stop = RepeatCount, i = 1; i <= stop; i++)
	{
		AEditor->CommandProcessor(Command, L'\x00', nullptr);
	}
}

void __fastcall TSynBasicEvent::SaveToStream(TStream* AStream)
{
	AStream->Write(&Command, sizeof(TSynEditorCommand));
	AStream->Write(&RepeatCount, sizeof(RepeatCount));
}

/* TSynCharEvent */

String __fastcall TSynCharEvent::GetAsString()
{
	String result;
	String Ident;
	EditorCommandToIdent(ecChar, Ident);
	result = Ident + L" " + String(key);
	if(RepeatCount > 1)
		result = result + L" " + IntToStr((int) RepeatCount);
	return result;
}

void __fastcall TSynCharEvent::InitEventParameters(String AStr)
{

  // aStr should be a Key value one character in length
  // with an optional repeat count whitespace separated
	if(AStr.Length() >= 1)
		key = AStr[1];
	else
		key = L' ';
	AStr.Delete(1, 	1); // if possible delete the first character
	RepeatCount = (unsigned char) StrToIntDef(Trim(AStr), 1);
}

void __fastcall TSynCharEvent::Initialize(TSynEditorCommand ACmd, WideChar AChar, void* AData)
{
	key = AChar;
	Assert(AData == nullptr);
}

void __fastcall TSynCharEvent::LoadFromStream(TStream* AStream)
{
	AStream->Read((void**)&FKey, sizeof(key));
	AStream->Read((void**)&fRepeatCount, sizeof(fRepeatCount));
}

void __fastcall TSynCharEvent::Playback(TCustomSynEdit* AEditor)
{
	int i = 0;
	int stop = 0;
	for(stop = RepeatCount, i = 1; i <= stop; i++)
	{
		AEditor->CommandProcessor((TSynEditorCommand) ecChar, key, nullptr);
	}
}

void __fastcall TSynCharEvent::SaveToStream(TStream* AStream)
{
	const TSynEditorCommand iCharCommand = ecChar;
	AStream->Write(&iCharCommand, sizeof(TSynEditorCommand));
	AStream->Write(&key, sizeof(key));
	AStream->Write(&RepeatCount, sizeof(RepeatCount));
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

void __fastcall TSynPositionEvent::InitEventParameters(String AStr)
{
	int i = 0;
	int O = 0;
	int C = 0;
	int X = 0;
	int Y = 0;
	String valStr;
	inherited::InitEventParameters(AStr);
  // aStr should be (x, y) with optional repeat count whitespace separated
	AStr = Trim(AStr);
	i = Pos(L",", AStr);
	O = Pos(L"(", AStr);
	C = Pos(L")", AStr);
	if((!((i == 0) || (O == 0) || (C == 0))) && ((i > O) && (i < C)))
	{
		valStr = AStr.SubString(O + 1, i - O - 1);
		X = StrToIntDef(valStr, 1);
		AStr.Delete(1, 	i);
		AStr = Trim(AStr);
		C = Pos(L")", AStr);
		valStr = AStr.SubString(1, C - 1);
		Y = StrToIntDef(valStr, 1);
		Position = BufferCoord(X, Y);
		AStr.Delete(1, 	C);
		AStr = Trim(AStr);
		RepeatCount = (unsigned char) StrToIntDef(AStr, 1);
	}
}

void __fastcall TSynPositionEvent::Initialize(TSynEditorCommand ACmd, WideChar AChar, void* AData)
{
	inherited::Initialize(ACmd, AChar, AData);
	if(AData != nullptr)
		Position = (*(TBufferCoord*) AData);
	else
		Position = BufferCoord(0, 0);
}

void __fastcall TSynPositionEvent::LoadFromStream(TStream* AStream)
{
	AStream->Read((void**)&FPosition, sizeof(Position));
}

void __fastcall TSynPositionEvent::Playback(TCustomSynEdit* AEditor)
{
	if((Position.Char != 0) || (Position.Line != 0))
		AEditor->CommandProcessor(Command, L'\x00', &Position);
	else
		AEditor->CommandProcessor(Command, L'\x00', nullptr);
}

void __fastcall TSynPositionEvent::SaveToStream(TStream* AStream)
{
	inherited::SaveToStream(AStream);
	AStream->Write(&Position, sizeof(Position));
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

void __fastcall TSynStringEvent::InitEventParameters(String AStr)
{
	int O = 0;
	int C = 0;
	String valStr;                      
  // aStr = 'test' with optional whitespace separated repeat count
	O = Pos(L"\'", AStr);
	C = LastDelimiter(L"\'", AStr);
	valStr = AStr.SubString(O + 1, C - O - 1);
	Value = StringReplace(valStr, L"''", L"\'", Synmacrorecorder__2);
	AStr.Delete(1, 	C);
	RepeatCount = (unsigned char) StrToIntDef(Trim(AStr), 1);
}

void __fastcall TSynStringEvent::Initialize(TSynEditorCommand ACmd, WideChar AChar, void* AData)
{
	Value = String((wchar_t*)AData);
}

void __fastcall TSynStringEvent::LoadFromStream(TStream* AStream)
{
	int l = 0;
	PWideChar Buff = nullptr;
	AStream->Read((void**)&l, sizeof(l));
	Buff = (PWideChar) GetMemory(l * sizeof(WideChar));
	try
	{
		FillMemory(Buff, (NativeUInt) l, 0);
		AStream->Read((void**)Buff, l * sizeof(WideChar));
		FString = Buff;
	}
	__finally
	{
		FreeMemory(Buff);
	}
	AStream->Read((void**)&fRepeatCount, sizeof(fRepeatCount));
}

void __fastcall TSynStringEvent::Playback(TCustomSynEdit* AEditor)
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
			AEditor->CommandProcessor((TSynEditorCommand) ecChar, Value[i], nullptr);
		}
	}
}

void __fastcall TSynStringEvent::SaveToStream(TStream* AStream)
{
	const TSynEditorCommand StrCommand = ecString;
	int l = 0;
	PWideChar Buff = nullptr;
	AStream->Write(&StrCommand, sizeof(StrCommand));
	l = Value.Length() + 1;
	AStream->Write(&l, sizeof(l));
	Buff = (PWideChar) GetMemory(l * sizeof(WideChar));
	try
	{
		FillMemory(Buff, (NativeUInt) l, 0);
		StrCopy(Buff, ustr2pwchar(Value));
		AStream->Write(Buff, l * sizeof(WideChar));
	}
	__finally
	{
		FreeMemory(Buff);
	}
	AStream->Write(&RepeatCount, sizeof(RepeatCount));
}


/* TSynMacroEvent */

__fastcall TSynMacroEvent::TSynMacroEvent()
 : fRepeatCount(1)
{
	//# inherited::Create();
}


}  // namespace SynMacroRecorder

