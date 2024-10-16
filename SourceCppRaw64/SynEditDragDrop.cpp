#include <vcl.h>
#pragma hdrstop

#include "SynEditDragDrop.h"

using namespace std;
using namespace d2c_system;
using namespace System;
using namespace Winapi::Activex;

namespace Syneditdragdrop
{

__fastcall TSynDropTarget::TSynDropTarget() {}
__fastcall TSynDragSource::TSynDragSource() {}



//--- returns the normal response for a wanted effect:
//  no keys       = "move"
//  control only  = "copy"
//  control/shift = "link" - ignored in this case

int __fastcall StandardEffect(TShiftState Keys)
{
	int result = 0;
	result = deMove;
	if(Keys.Contains(ssCtrl))
	{
		result = deCopy;
	}
	return result;
}

/* TDropTarget */

HRESULT __fastcall TSynDropTarget::DragEnter(IDataObject* const DataObj, int grfKeyState, const TPoint& cpt, int& dwEffect)
{
	TPoint pt = cpt;
	HRESULT result = 0;
	result = S_OK;
	try
	{
		DragEnter(const_cast<IDataObject*>(DataObj), KeysToShiftState((WORD) grfKeyState), pt, dwEffect, result);
	}
	catch(...)
	{
		result = E_UNEXPECTED;
	}
	return result;
}

HRESULT __stdcall TSynDropTarget::DragLeave()
{
	HRESULT result = 0;
	result = S_OK;
	try
	{
		DragLeave(result);
	}
	catch(...)
	{
		result = E_UNEXPECTED;
	}
	return result;
}

HRESULT __fastcall TSynDropTarget::DragOver(int grfKeyState, const TPoint& cpt, int& dwEffect)
{
	TPoint pt = cpt;
	HRESULT result = 0;
	result = S_OK;
	try
	{
		DragOver(KeysToShiftState((WORD) grfKeyState), pt, dwEffect, result);
	}
	catch(...)
	{
		result = E_UNEXPECTED;
	}
	return result;
}

HRESULT __fastcall TSynDropTarget::Drop(IDataObject* const DataObj, int grfKeyState, const TPoint& cpt, int& dwEffect)
{
	TPoint pt = cpt;
	HRESULT result = 0;
	result = S_OK;
	try
	{
		Drop(const_cast<IDataObject*>(DataObj), KeysToShiftState((WORD) grfKeyState), pt, dwEffect, result);
	}
	catch(...)
	{
		result = E_UNEXPECTED;
	}
	return result;
}

void __fastcall TSynDropTarget::DragEnter(IDataObject* DataObject, TShiftState State, const TPoint& cPt, int& Effect, HRESULT& Result)
{
	TPoint Pt = cPt;
	Effect = StandardEffect(State);
	if(ASSIGNED(FOnDragEnter))
		FOnDragEnter(this, DataObject, State, Pt, Effect, Result);
	if(Effect == deNone)
		FDataObject = nullptr;
	else
		FDataObject = DataObject;
}

void __fastcall TSynDropTarget::DragLeave(HRESULT& Result)
{
	if(ASSIGNED(FDataObject))
		try
		{
			if(ASSIGNED(FOnDragLeave))
				FOnDragLeave(this, Result);
		}
		__finally
		{
			FDataObject = nullptr;
		}
}

void __fastcall TSynDropTarget::DragOver(TShiftState State, const TPoint& cPt, int& Effect, HRESULT& Result)
{
	TPoint Pt = cPt;
	if(FDataObject == nullptr)
	{
		Effect = deNone;
		return;
	}
	Effect = StandardEffect(State);
	if(ASSIGNED(FOnDragOver))
		FOnDragOver(this, FDataObject, State, Pt, Effect, Result);
}

void __fastcall TSynDropTarget::Drop(IDataObject* DataObject, TShiftState State, const TPoint& cPt, int& Effect, HRESULT& Result)
{
	TPoint Pt = cPt;
	if(FDataObject == nullptr)
	{
		Effect = deNone;
		return;
	}
	Effect = StandardEffect(State);
	try
	{
		if(ASSIGNED(FOnDrop))
			FOnDrop(this, DataObject, State, Pt, Effect, Result);
	}
	__finally
	{
		FDataObject = nullptr;
	}
}

__fastcall TSynDropTarget::~TSynDropTarget()
{
	FDataObject = nullptr;
	// inherited;
}

//===  DRAG SOURCE CLASS ===================================================

HRESULT __stdcall TSynDragSource::QueryContinueDrag(BOOL fEscapePressed, int grfKeyState)
{
	HRESULT result = 0;
	if(fEscapePressed)  // cancel the drop
		result = DRAGDROP_S_CANCEL;
	else
	{
		if((grfKeyState & MK_LBUTTON) == 0)   // drop has occurred
			result = DRAGDROP_S_DROP;
		else
			result = S_OK;
	}
	return result;
}

HRESULT __stdcall TSynDragSource::GiveFeedback(int dwEffect)
{
	HRESULT result = 0;
	result = DRAGDROP_S_USEDEFAULTCURSORS;
	return result;
}

__fastcall TSynDragSource::~TSynDragSource()
{

  // for debugging purposes
	// inherited;
}


}  // namespace SynEditDragDrop

