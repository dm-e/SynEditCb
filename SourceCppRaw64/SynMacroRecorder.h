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

/*------------------------------------------------------------------------------*/
/* Common compiler defines                                                      */
/* (remove the dot in front of a define to enable it)                           */
/*------------------------------------------------------------------------------*/

/*$B-,H+*/ // defaults are short evaluation of boolean values and long strings

/*.$DEFINE SYN_DEVELOPMENT_CHECKS*/ // additional tests for debugging
  

/*------------------------------------------------------------------------------*/
/* Pull in all defines from SynEditJedi.inc (must be done after the common      */
/* compiler defines to  work correctly). Use SynEdit-prefix to avoid problems   */
/* with other versions of jedi.inc in the search-path.                          */
/*------------------------------------------------------------------------------*/

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

/*------------------------------------------------------------------------------*/
/*  Please change this to suit your needs (to activate an option remove the dot */
/*  in front of a DEFINE)                                                       */
/*------------------------------------------------------------------------------*/

// "Heredoc" syntax highlighting
// If you enable the following statement and use highlighter(s) that have
// support for "Heredoc" strings as scheme(s) in SynMultiSyn, you must
// implement your own SynMultiSyn OnCustomRange event handler in order to
// properly store Range State information
/*.$DEFINE SYN_HEREDOC*/

// Turn this off if you don't need complex script support, since it is slower
/*.$DEFINE SYN_UNISCRIBE*/

// $Id: SynEdit.inc,v 1.16.2.19 2009/06/14 13:41:44 maelh Exp $
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
	typedef System::TObject inherited;
protected:
	System::Byte fRepeatCount;
	virtual String __fastcall GetAsString(){return String();} // = 0;
	virtual void __fastcall InitEventParameters(String aStr){} // = 0;
public:
	__fastcall TSynMacroEvent();
	virtual void __fastcall Initialize(Synedittypes::TSynEditorCommand aCmd, WideChar aChar, void* aData){} // = 0;
    /* the CommandID must not be read inside LoadFromStream/SaveToStream. It's read by the
    MacroRecorder component to decide which MacroEvent class to instanciate */
	virtual void __fastcall LoadFromStream(TStream* aStream){} // = 0;
	virtual void __fastcall SaveToStream(TStream* aStream){} // = 0;
	virtual void __fastcall Playback(Synedit::TCustomSynEdit* aEditor){} // = 0;
	__property String AsString = { read = GetAsString };
	__property System::Byte RepeatCount = { read = fRepeatCount, write = fRepeatCount };
};

class TSynBasicEvent : public TSynMacroEvent
{
	#include "SynMacroRecorder_friends.inc"
public:
	typedef TSynMacroEvent inherited;
protected:
	Synedittypes::TSynEditorCommand fCommand;
	virtual String __fastcall GetAsString();
	virtual void __fastcall InitEventParameters(String aStr);
public:
	virtual void __fastcall Initialize(Synedittypes::TSynEditorCommand aCmd, WideChar aChar, void* aData);
	virtual void __fastcall LoadFromStream(TStream* aStream);
	virtual void __fastcall SaveToStream(TStream* aStream);
	virtual void __fastcall Playback(Synedit::TCustomSynEdit* aEditor);
	__property Synedittypes::TSynEditorCommand Command = { read = fCommand, write = fCommand };
	__fastcall TSynBasicEvent();
};

class TSynCharEvent : public TSynMacroEvent
{
	#include "SynMacroRecorder_friends.inc"
public:
	typedef TSynMacroEvent inherited;
protected:
	WideChar fKey;
	virtual String __fastcall GetAsString();
	virtual void __fastcall InitEventParameters(String aStr);
public:
	virtual void __fastcall Initialize(Synedittypes::TSynEditorCommand aCmd, WideChar aChar, void* aData);
	virtual void __fastcall LoadFromStream(TStream* aStream);
	virtual void __fastcall SaveToStream(TStream* aStream);
	virtual void __fastcall Playback(Synedit::TCustomSynEdit* aEditor);
	__property WideChar Key = { read = fKey, write = fKey };
	__fastcall TSynCharEvent();
};

class TSynStringEvent : public TSynMacroEvent
{
	#include "SynMacroRecorder_friends.inc"
public:
	typedef TSynMacroEvent inherited;
protected:
	String fString;
	virtual String __fastcall GetAsString();
	virtual void __fastcall InitEventParameters(String aStr);
public:
	virtual void __fastcall Initialize(Synedittypes::TSynEditorCommand aCmd, WideChar aChar, void* aData);
	virtual void __fastcall LoadFromStream(TStream* aStream);
	virtual void __fastcall SaveToStream(TStream* aStream);
	virtual void __fastcall Playback(Synedit::TCustomSynEdit* aEditor);
	__property String Value = { read = fString, write = fString };
	__fastcall TSynStringEvent();
};

class TSynPositionEvent : public TSynBasicEvent
{
	#include "SynMacroRecorder_friends.inc"
public:
	typedef TSynBasicEvent inherited;
protected:
	TBufferCoord fPosition;
	virtual String __fastcall GetAsString();
	virtual void __fastcall InitEventParameters(String aStr);
public:
	virtual void __fastcall Initialize(Synedittypes::TSynEditorCommand aCmd, WideChar aChar, void* aData);
	virtual void __fastcall LoadFromStream(TStream* aStream);
	virtual void __fastcall SaveToStream(TStream* aStream);
	virtual void __fastcall Playback(Synedit::TCustomSynEdit* aEditor);
	__property TBufferCoord Position = { read = fPosition, write = fPosition };
	__fastcall TSynPositionEvent();
};

class TSynDataEvent : public TSynBasicEvent
{
	#include "SynMacroRecorder_friends.inc"
public:
	typedef TSynBasicEvent inherited;
protected:
	void* fData;
public:
	virtual void __fastcall Initialize(Synedittypes::TSynEditorCommand aCmd, WideChar aChar, void* aData);
	virtual void __fastcall LoadFromStream(TStream* aStream);
	virtual void __fastcall SaveToStream(TStream* aStream);
	virtual void __fastcall Playback(Synedit::TCustomSynEdit* aEditor);
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
	TShortCut fShortCuts[2/*# TSynMacroCommand*/];
	TNotifyEvent fOnStateChange;
	TSynUserCommandEvent fOnUserCommand;
	String fMacroName;
	bool fSaveMarkerPos;
	TSynMacroEvent* __fastcall GetEvent(int aIndex);
	int __fastcall GetEventCount();
	String __fastcall GetAsString();
	Synedittypes::TSynEditorCommand __fastcall GetPlaybackCommandID();
	TShortCut __fastcall GetPlaybackShortCut(int Index);
	Synedittypes::TSynEditorCommand __fastcall GetRecordCommandID();
	TShortCut __fastcall GetRecordShortCut(int Index);
	void __fastcall SetAsString(const String Value);
protected:
	Synedit::TCustomSynEdit* fCurrentEditor;
	TSynMacroState fState;
	TList* fEvents;
	Synedittypes::TSynEditorCommand fCommandIDs[2/*# TSynMacroCommand*/];
	void __fastcall SetShortCut(int Index, const TShortCut Value);
	bool __fastcall GetIsEmpty();
	void __fastcall StateChanged();
	virtual void __fastcall DoAddEditor(Synedit::TCustomSynEdit* aEditor);
	virtual void __fastcall DoRemoveEditor(Synedit::TCustomSynEdit* aEditor);
	virtual void __fastcall OnCommand(TObject* Sender, bool AfterProcessing, bool& Handled, Synedittypes::TSynEditorCommand& Command, WideChar& aChar, void* Data, void* HandlerData);
	TSynMacroEvent* __fastcall CreateMacroEvent(Synedittypes::TSynEditorCommand aCmd);
	__property Synedittypes::TSynEditorCommand RecordCommandID = { read = GetRecordCommandID };
	__property Synedittypes::TSynEditorCommand PlaybackCommandID = { read = GetPlaybackCommandID };
public:
	typedef Syneditplugins::TAbstractSynHookerPlugin inherited;
	#include "SynMacroRecorder_friends.inc"
	__fastcall TCustomSynMacroRecorder(TComponent* aOwner);
	virtual __fastcall ~TCustomSynMacroRecorder();
	void __fastcall Error(const String aMsg);
	void __fastcall AddEditor(Synedit::TCustomSynEdit* aEditor);
	void __fastcall RemoveEditor(Synedit::TCustomSynEdit* aEditor);
	void __fastcall RecordMacro(Synedit::TCustomSynEdit* aEditor);
	void __fastcall PlaybackMacro(Synedit::TCustomSynEdit* aEditor);
	void __fastcall Stop();
	void __fastcall Pause();
	void __fastcall Resume();
	__property bool IsEmpty = { read = GetIsEmpty };
	__property TSynMacroState State = { read = fState };
	void __fastcall Clear();
	void __fastcall AddEvent(Synedittypes::TSynEditorCommand aCmd, WideChar aChar, void* aData);
	void __fastcall InsertEvent(int aIndex, Synedittypes::TSynEditorCommand aCmd, WideChar aChar, void* aData);
	void __fastcall AddCustomEvent(TSynMacroEvent* aEvent);
	void __fastcall InsertCustomEvent(int aIndex, TSynMacroEvent* aEvent);
	void __fastcall DeleteEvent(int aIndex);
	void __fastcall LoadFromStream(TStream* aSrc);
	void __fastcall LoadFromStreamEx(TStream* aSrc, bool aClear);
	void __fastcall SaveToStream(TStream* aDest);
	void __fastcall LoadFromFile(String aFilename);
	void __fastcall SaveToFile(String aFilename);
	__property int EventCount = { read = GetEventCount };
	__property TSynMacroEvent* Events[int aIndex] = { read = GetEvent };
	__property TShortCut RecordShortCut = { index = int(Synmacrorecorder::mcRecord), read = GetRecordShortCut, write = SetShortCut };
	__property TShortCut PlaybackShortCut = { index = int(Synmacrorecorder::mcPlayback), read = GetPlaybackShortCut, write = SetShortCut };
	__property bool SaveMarkerPos = { read = fSaveMarkerPos, write = fSaveMarkerPos, default = false };
	__property String AsString = { read = GetAsString, write = SetAsString };
	__property String MacroName = { read = fMacroName, write = fMacroName };
	__property TNotifyEvent OnStateChange = { read = fOnStateChange, write = fOnStateChange };
	__property TSynUserCommandEvent OnUserCommand = { read = fOnUserCommand, write = fOnUserCommand };
};

class TSynMacroRecorder : public TCustomSynMacroRecorder
{
__published:
public:
	__property  SaveMarkerPos;
	__property  RecordShortCut;
	__property  PlaybackShortCut;
	__property  OnStateChange;
	__property  OnUserCommand;
public:
	typedef TCustomSynMacroRecorder inherited;
	#include "SynMacroRecorder_friends.inc"
	__fastcall TSynMacroRecorder(TComponent* aOwner);
};


}  // namespace SynMacroRecorder

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synmacrorecorder;
#endif

#endif // SynMacroRecorderH

