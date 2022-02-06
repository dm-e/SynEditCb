#ifndef SynEditKbdHandlerH
#define SynEditKbdHandlerH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include "SynEditTypes.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "SynEditDelphiInstances.hpp"

namespace Syneditkbdhandler
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditKeyCmds.pas, released 2000-04-07.
The Original Code is based on the mwKeyCmds.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Brad Stowers.
Unicode translation by Maël Hörz.
All Rights Reserved.

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

$Id: SynEditKbdHandler.pas,v 1.10.2.1 2004/08/31 12:55:17 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
  /* This class provides a TWinControl-Object which supports only the
    needed Methods */

class TKeyboardControl : public Vcl::Controls::TWinControl
{
public:
	typedef Vcl::Controls::TWinControl inherited;	
	#include "SynEditKbdHandler_friends.inc"
	__property  OnKeyDown;
	__property  OnKeyPress;
	__property  OnMouseDown;
	__fastcall TKeyboardControl(System::Classes::TComponent* AOwner);
	__fastcall TKeyboardControl(HWND ParentWindow);
};
typedef void __fastcall (__closure *TMouseCursorEvent) (TObject*, const TBufferCoord&, TCursor&);

class TMethodList : public System::TObject
{
	#include "SynEditKbdHandler_friends.inc"
public:
	typedef TObject inherited;	
private:
	System::Classes::TList* FData;
	System::TMethod __fastcall GetItem(int Index);
	int __fastcall GetCount();
public:
	__fastcall TMethodList();
	virtual __fastcall ~TMethodList();
	void __fastcall Add(const System::TMethod& aHandler);
	void __fastcall Remove(const System::TMethod& aHandler);
	__property System::TMethod Items[int Index] = { read = GetItem/*# default */ };
	__property int Count = { read = GetCount };
};

class TSynEditKbdHandler : public System::TObject
{
	#include "SynEditKbdHandler_friends.inc"
public:
	typedef TObject inherited;	
private:
	TMethodList* fKeyPressChain;
	TMethodList* fKeyDownChain;
	TMethodList* fKeyUpChain;
	TMethodList* fMouseDownChain;
	TMethodList* fMouseUpChain;
	TMethodList* fMouseCursorChain;
    /* avoid infinite recursiveness */
	bool fInKeyPress;
	bool fInKeyDown;
	bool fInKeyUp;
	bool fInMouseDown;
	bool fInMouseUp;
	bool fInMouseCursor;
public:
	__fastcall TSynEditKbdHandler();
	virtual __fastcall ~TSynEditKbdHandler();
	void __fastcall ExecuteKeyPress(TObject* Sender, WideChar& key);
	void __fastcall ExecuteKeyDown(TObject* Sender, WORD& key, System::Classes::TShiftState Shift);
	void __fastcall ExecuteKeyUp(TObject* Sender, WORD& key, System::Classes::TShiftState Shift);
	void __fastcall ExecuteMouseDown(TObject* Sender, TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall ExecuteMouseUp(TObject* Sender, TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall ExecuteMouseCursor(TObject* Sender, const TBufferCoord& aLineCharPos, TCursor& aCursor);
	void __fastcall AddKeyDownHandler(Vcl::Controls::TKeyEvent aHandler);
	void __fastcall RemoveKeyDownHandler(Vcl::Controls::TKeyEvent aHandler);
	void __fastcall AddKeyUpHandler(Vcl::Controls::TKeyEvent aHandler);
	void __fastcall RemoveKeyUpHandler(Vcl::Controls::TKeyEvent aHandler);
	void __fastcall AddKeyPressHandler(Vcl::Controls::TKeyPressEvent aHandler);
	void __fastcall RemoveKeyPressHandler(Vcl::Controls::TKeyPressEvent aHandler);
	void __fastcall AddMouseDownHandler(Vcl::Controls::TMouseEvent aHandler);
	void __fastcall RemoveMouseDownHandler(Vcl::Controls::TMouseEvent aHandler);
	void __fastcall AddMouseUpHandler(Vcl::Controls::TMouseEvent aHandler);
	void __fastcall RemoveMouseUpHandler(Vcl::Controls::TMouseEvent aHandler);
	void __fastcall AddMouseCursorHandler(TMouseCursorEvent aHandler);
	void __fastcall RemoveMouseCursorHandler(TMouseCursorEvent aHandler);
};


}  // namespace SynEditKbdHandler

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditkbdhandler;
#endif

#endif // SynEditKbdHandlerH

