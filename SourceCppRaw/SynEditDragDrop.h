#ifndef SynEditDragDropH
#define SynEditDragDropH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

namespace Syneditdragdrop
{


/*
  The contents of this file are subject to the Mozilla Public License
  Version 1.1 (the "License"); you may not use this file except in compliance
  with the License. You may obtain a copy of the License at
  http://www.mozilla.org/MPL/

  Software distributed under the License is distributed on an "AS IS" basis,
  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
  the specific language governing rights and limitations under the License.

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

   OLE Drag and Drop components and routines
   Based on Grahame Marsh's code for UNDO
*/


// Drop effects as Delphi style constants (originals in ActiveX)
const int deNone = DROPEFFECT_NONE;
const int deMove = DROPEFFECT_MOVE;
const int deCopy = DROPEFFECT_COPY;
const int deLink = DROPEFFECT_LINK;
const unsigned int deScroll = DROPEFFECT_SCROLL;

// Provides a translation of a IDropTarget interface into Delphi
typedef void __fastcall (__closure *TOnDragEvent) (TObject*, IDataObject*, TShiftState, const TPoint&, int&, HRESULT&);
typedef void __fastcall (__closure *TOnDragLeaveEvent) (TObject*, HRESULT&);

class TSynDropTarget : public System::TCppInterfacedObject<IDropTarget>
{
	#include "SynEditDragDrop_friends.inc"
public:
	typedef System::TCppInterfacedObject<IDropTarget> inherited;
private:
	IDataObject* FDataObject;
	TOnDragEvent FOnDragEnter;
	TOnDragEvent FOnDragOver;
	TOnDragLeaveEvent FOnDragLeave;
	TOnDragEvent FOnDrop;
// IDropTarget
	HRESULT __stdcall DragEnter(IDataObject* const dataObj, int grfKeyState, const TPoint& Pt, int& dwEffect);
	HRESULT __stdcall DragOver(int grfKeyState, const TPoint& Pt, int& dwEffect);
	HRESULT __stdcall DragLeave();
	HRESULT __stdcall Drop(IDataObject* const dataObj, int grfKeyState, const TPoint& Pt, int& dwEffect);
protected:
	void __fastcall DragEnter(IDataObject* dataObject, TShiftState State, const TPoint& Pt, int& Effect, HRESULT& result);
	void __fastcall DragOver(TShiftState State, const TPoint& Pt, int& Effect, HRESULT& result);
	void __fastcall DragLeave(HRESULT& result);
	void __fastcall Drop(IDataObject* dataObject, TShiftState State, const TPoint& Pt, int& Effect, HRESULT& result);
public:
	virtual __fastcall ~TSynDropTarget();
	__property TOnDragEvent OnDragEnter = { read = FOnDragEnter, write = FOnDragEnter };
	__property TOnDragEvent OnDragOver = { read = FOnDragOver, write = FOnDragOver };
	__property TOnDragLeaveEvent OnDragLeave = { read = FOnDragLeave, write = FOnDragLeave };
	__property TOnDragEvent OnDrop = { read = FOnDrop, write = FOnDrop };
	__fastcall TSynDropTarget();
};

class TSynDragSource : public System::TCppInterfacedObject<IDropSource>
{
	#include "SynEditDragDrop_friends.inc"
public:
	typedef System::TCppInterfacedObject<IDropSource> inherited;
private:
  // IDropSource
    // Called routinely by Windows to check that drag operations are to continue. See the
   // implementation below of QueryContinueDrag method for the default operation.
	HRESULT __stdcall QueryContinueDrag(BOOL fEscapePressed, int grfKeyState);
    // Called routinely to modify the displayed cursor.
	HRESULT __stdcall GiveFeedback(int dwEffect);
public:
	virtual __fastcall ~TSynDragSource();
	__fastcall TSynDragSource();
};


}  // namespace SynEditDragDrop

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditdragdrop;
#endif

#endif // SynEditDragDropH

