#ifndef SynMacroRecorderH
#define SynMacroRecorderH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.StdCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Menus.hpp>
#include "SynEdit.h"
#include "SynEditKeyCmds.h"
#include "SynEditPlugins.h"
#include "SynEditTypes.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>
#include "SynEditDelphiInstances.hpp"

namespace Synmacrorecorder
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynMacroRecorder.pas, released 2001-10-17.

Author of this file is Flávio Etrusco.
Portions created by Flávio Etrusco are Copyright 2001 Flávio Etrusco.
Unicode translation by Maël Hörz.
All Rights Reserved.

Contributors to the SynEdit project are listed in the Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

$Id: SynMacroRecorder.pas,v 1.31.2.3 2008/09/14 16:25:03 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
const System::Char sCannotRecord[] = L"Cannot record macro; already recording or playing";
const System::Char sCannotPlay[] = L"Cannot playback macro; already playing or recording";
const System::Char sCannotPause[] = L"Can only pause when recording";
const System::Char sCannotResume[] = L"Can only resume when paused";
class DELPHICLASS TCustomSynMacroRecorder;
enum TSynMacroState {msStopped,
                     msRecording,
                     msPlaying,
                     msPaused };
enum TSynMacroCommand {mcRecord,
                       mcPlayback };

class TSynMacroEvent : public System::TObject
{
	#include "SynMacroRecorder_friends.inc"
public:
	typedef TObject inherited;	
protected:
	unsigned char fRepeatCount;
	virtual String __fastcall GetAsString(){return String();} // = 0;
	virtual void __fastcall InitEventParameters(String AStr){} // = 0;
public:
	__fastcall TSynMacroEvent();
	virtual void __fastcall Initialize(Synedittypes::TSynEditorCommand ACmd, WideChar AChar, void* AData){} // = 0;
    /* the CommandID must not be read inside LoadFromStream/SaveToStream. It's read by the
    MacroRecorder component to decide which MacroEvent class to instanciate */
	virtual void __fastcall LoadFromStream(System::Classes::TStream* AStream){} // = 0;
	virtual void __fastcall SaveToStream(System::Classes::TStream* AStream){} // = 0;
	virtual void __fastcall Playback(Synedit::TCustomSynEdit* AEditor){} // = 0;
	__property String AsString = { read = GetAsString };
	__property unsigned char RepeatCount = { read = fRepeatCount, write = fRepeatCount };
};

class TSynBasicEvent : public TSynMacroEvent
{
	#include "SynMacroRecorder_friends.inc"
public:
	typedef TSynMacroEvent inherited;	
protected:
	Synedittypes::TSynEditorCommand FCommand;
	virtual String __fastcall GetAsString();
	virtual void __fastcall InitEventParameters(String AStr);
public:
	virtual void __fastcall Initialize(Synedittypes::TSynEditorCommand ACmd, WideChar AChar, void* AData);
	virtual void __fastcall LoadFromStream(System::Classes::TStream* AStream);
	virtual void __fastcall SaveToStream(System::Classes::TStream* AStream);
	virtual void __fastcall Playback(Synedit::TCustomSynEdit* AEditor);
	__property Synedittypes::TSynEditorCommand Command = { read = FCommand, write = FCommand };
	__fastcall TSynBasicEvent();
};

class TSynCharEvent : public TSynMacroEvent
{
	#include "SynMacroRecorder_friends.inc"
public:
	typedef TSynMacroEvent inherited;	
protected:
	WideChar FKey;
	virtual String __fastcall GetAsString();
	virtual void __fastcall InitEventParameters(String AStr);
public:
	virtual void __fastcall Initialize(Synedittypes::TSynEditorCommand ACmd, WideChar AChar, void* AData);
	virtual void __fastcall LoadFromStream(System::Classes::TStream* AStream);
	virtual void __fastcall SaveToStream(System::Classes::TStream* AStream);
	virtual void __fastcall Playback(Synedit::TCustomSynEdit* AEditor);
	__property WideChar key = { read = FKey, write = FKey };
	__fastcall TSynCharEvent();
};

class TSynStringEvent : public TSynMacroEvent
{
	#include "SynMacroRecorder_friends.inc"
public:
	typedef TSynMacroEvent inherited;	
protected:
	String FString;
	virtual String __fastcall GetAsString();
	virtual void __fastcall InitEventParameters(String AStr);
public:
	virtual void __fastcall Initialize(Synedittypes::TSynEditorCommand ACmd, WideChar AChar, void* AData);
	virtual void __fastcall LoadFromStream(System::Classes::TStream* AStream);
	virtual void __fastcall SaveToStream(System::Classes::TStream* AStream);
	virtual void __fastcall Playback(Synedit::TCustomSynEdit* AEditor);
	__property String Value = { read = FString, write = FString };
	__fastcall TSynStringEvent();
};

class TSynPositionEvent : public TSynBasicEvent
{
	#include "SynMacroRecorder_friends.inc"
public:
	typedef TSynBasicEvent inherited;	
protected:
	TBufferCoord FPosition;
	virtual String __fastcall GetAsString();
	virtual void __fastcall InitEventParameters(String AStr);
public:
	virtual void __fastcall Initialize(Synedittypes::TSynEditorCommand ACmd, WideChar AChar, void* AData);
	virtual void __fastcall LoadFromStream(System::Classes::TStream* AStream);
	virtual void __fastcall SaveToStream(System::Classes::TStream* AStream);
	virtual void __fastcall Playback(Synedit::TCustomSynEdit* AEditor);
	__property TBufferCoord Position = { read = FPosition, write = FPosition };
	__fastcall TSynPositionEvent();
};

class TSynDataEvent : public TSynBasicEvent
{
	#include "SynMacroRecorder_friends.inc"
public:
	typedef TSynBasicEvent inherited;	
protected:
	void* FData;
public:
	virtual void __fastcall Initialize(Synedittypes::TSynEditorCommand ACmd, WideChar AChar, void* AData);
	virtual void __fastcall LoadFromStream(System::Classes::TStream* AStream);
	virtual void __fastcall SaveToStream(System::Classes::TStream* AStream);
	virtual void __fastcall Playback(Synedit::TCustomSynEdit* AEditor);
	__fastcall TSynDataEvent();
};

  /* TCustomSynMacroRecorder
  OnStateChange:
    occurs right after start playing, recording, pausing or stopping
  SaveMarkerPos:
    if true, Bookmark position is recorded in the macro. Otherwise, the Bookmark
    is created in the position the Caret is at the time of playback.
  */
typedef void __fastcall (__closure *TSynUserCommandEvent) (TCustomSynMacroRecorder*, Synedittypes::TSynEditorCommand, TSynMacroEvent*&);

class TCustomSynMacroRecorder : public Syneditplugins::TAbstractSynHookerPlugin
{
private:
	System::Classes::TShortCut fShortCuts[2/*# TSynMacroCommand*/];
	System::Classes::TNotifyEvent FOnStateChange;
	TSynUserCommandEvent fOnUserCommand;
	String fMacroName;
	bool fSaveMarkerPos;
	TSynMacroEvent* __fastcall GetEvent(int AIndex);
	int __fastcall GetEventCount();
	String __fastcall GetAsString();
	Synedittypes::TSynEditorCommand __fastcall GetPlaybackCommandID();
	System::Classes::TShortCut __fastcall GetPlaybackShortCut(int Index);
	Synedittypes::TSynEditorCommand __fastcall GetRecordCommandID();
	System::Classes::TShortCut __fastcall GetRecordShortCut(int Index);
	void __fastcall SetAsString(const String Value);
protected:
	Synedit::TCustomSynEdit* FCurrentEditor;
	TSynMacroState fState;
	System::Classes::TList* FEvents;
	Synedittypes::TSynEditorCommand fCommandIDs[2/*# TSynMacroCommand*/];
	void __fastcall SetShortCut(int Index, const System::Classes::TShortCut Value);
	bool __fastcall GetIsEmpty();
	void __fastcall StateChanged();
	virtual void __fastcall DoAddEditor(Synedit::TCustomSynEdit* AEditor);
	virtual void __fastcall DoRemoveEditor(Synedit::TCustomSynEdit* AEditor);
	virtual void __fastcall OnCommand(TObject* Sender, bool AfterProcessing, bool& Handled, Synedittypes::TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData);
	TSynMacroEvent* __fastcall CreateMacroEvent(Synedittypes::TSynEditorCommand ACmd);
	__property Synedittypes::TSynEditorCommand RecordCommandID = { read = GetRecordCommandID };
	__property Synedittypes::TSynEditorCommand PlaybackCommandID = { read = GetPlaybackCommandID };
public:
	typedef Syneditplugins::TAbstractSynHookerPlugin inherited;	
	#include "SynMacroRecorder_friends.inc"
	__fastcall TCustomSynMacroRecorder(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TCustomSynMacroRecorder();
	void __fastcall Error(const String aMsg);
	void __fastcall AddEditor(Synedit::TCustomSynEdit* AEditor);
	void __fastcall RemoveEditor(Synedit::TCustomSynEdit* AEditor);
	void __fastcall RecordMacro(Synedit::TCustomSynEdit* AEditor);
	void __fastcall PlaybackMacro(Synedit::TCustomSynEdit* AEditor);
	void __fastcall Stop();
	void __fastcall pause();
	void __fastcall Resume();
	__property bool IsEmpty = { read = GetIsEmpty };
	__property TSynMacroState State = { read = fState };
	void __fastcall Clear();
	void __fastcall AddEvent(Synedittypes::TSynEditorCommand ACmd, WideChar AChar, void* AData);
	void __fastcall InsertEvent(int AIndex, Synedittypes::TSynEditorCommand ACmd, WideChar AChar, void* AData);
	void __fastcall AddCustomEvent(TSynMacroEvent* AEvent);
	void __fastcall InsertCustomEvent(int AIndex, TSynMacroEvent* AEvent);
	void __fastcall DeleteEvent(int AIndex);
	void __fastcall LoadFromStream(System::Classes::TStream* aSrc);
	void __fastcall LoadFromStreamEx(System::Classes::TStream* aSrc, bool aClear);
	void __fastcall SaveToStream(System::Classes::TStream* ADest);
	void __fastcall LoadFromFile(String AFileName);
	void __fastcall SaveToFile(String AFileName);
	__property int EventCount = { read = GetEventCount };
	__property TSynMacroEvent* Events[int AIndex] = { read = GetEvent };
	__property System::Classes::TShortCut RecordShortCut = { index = int(Synmacrorecorder::mcRecord), read = GetRecordShortCut, write = SetShortCut };
	__property System::Classes::TShortCut PlaybackShortCut = { index = int(Synmacrorecorder::mcPlayback), read = GetPlaybackShortCut, write = SetShortCut };
	__property bool SaveMarkerPos = { read = fSaveMarkerPos, write = fSaveMarkerPos, default = false };
	__property String AsString = { read = GetAsString, write = SetAsString };
	__property String MacroName = { read = fMacroName, write = fMacroName };
	__property System::Classes::TNotifyEvent OnStateChange = { read = FOnStateChange, write = FOnStateChange };
	__property TSynUserCommandEvent OnUserCommand = { read = fOnUserCommand, write = fOnUserCommand };
};

class TSynMacroRecorder : public TCustomSynMacroRecorder
{
__published:
	__property  SaveMarkerPos;
	__property  RecordShortCut;
	__property  PlaybackShortCut;
	__property  OnStateChange;
	__property  OnUserCommand;
public:
	typedef TCustomSynMacroRecorder inherited;	
	#include "SynMacroRecorder_friends.inc"
	__fastcall TSynMacroRecorder(System::Classes::TComponent* AOwner);
};


}  // namespace SynMacroRecorder

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synmacrorecorder;
#endif

#endif // SynMacroRecorderH

