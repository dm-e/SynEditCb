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

HRESULT __stdcall TSynDropTarget::DragEnter(IDataObject* dataObj, unsigned long grfKeyState, _POINTL Pt, unsigned long* dwEffect)
{
	HRESULT result = 0;
	result = S_OK;
	try
	{
		DragEnter(dataObj, KeysToShiftState((WORD) grfKeyState), Pt, dwEffect, result);
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

HRESULT __stdcall TSynDropTarget::DragOver(unsigned long grfKeyState, POINTL Pt, unsigned long* dwEffect)
{
	HRESULT result = 0;
	result = S_OK;
	try
	{
		DragOver(KeysToShiftState((WORD) grfKeyState), Pt, dwEffect, result);
	}
	catch(...)
	{
		result = E_UNEXPECTED;
	}
	return result;
}

HRESULT __stdcall TSynDropTarget::Drop(IDataObject* dataObj, unsigned long grfKeyState, _POINTL Pt, unsigned long* dwEffect)
{
	HRESULT result = 0;
	result = S_OK;
	try
	{
		Drop(dataObj, KeysToShiftState((WORD) grfKeyState), Pt, dwEffect, result);
	}
	catch(...)
	{
		result = E_UNEXPECTED;
	}
	return result;
}

void __fastcall TSynDropTarget::DragEnter(IDataObject* dataObject, TShiftState State, _POINTL Pt, unsigned long* Effect, HRESULT& result)
{
	*Effect = StandardEffect(State);
	if(ASSIGNED(FOnDragEnter))
	{
		TPoint pt = *(TPoint*) &Pt;
		int iEffect = StandardEffect(State);
		FOnDragEnter(this, dataObject, State, pt, iEffect, result);
	}
	if(*Effect == deNone)
		FDataObject = nullptr;
	else
		FDataObject = dataObject;
}

void __fastcall TSynDropTarget::DragLeave(HRESULT& result)
{
	if(ASSIGNED(FDataObject))
		try
		{
			if(ASSIGNED(FOnDragLeave))
				FOnDragLeave(this, result);
		}
		__finally
		{
			FDataObject = nullptr;
		}
}

void __fastcall TSynDropTarget::DragOver(TShiftState State, POINTL Pt, unsigned long* Effect, HRESULT& result)
{
	if(FDataObject == nullptr)
	{
		*Effect = deNone;
		return;
	}
	*Effect = StandardEffect(State);
	if(ASSIGNED(FOnDragOver))
	{
		TPoint pt = *(TPoint*) &Pt;
		int iEffect = deNone;
		FOnDragOver(this, FDataObject, State, pt, iEffect, result);
	}
}

void __fastcall TSynDropTarget::Drop(IDataObject* dataObject, TShiftState State, _POINTL Pt, unsigned long* Effect, HRESULT& result)
{
	if(FDataObject == nullptr)
	{
		*Effect = deNone;
		return;
	}
	*Effect = StandardEffect(State);
	try
	{
		if(ASSIGNED(FOnDrop))
		{
			TPoint pt = *(TPoint*) &Pt;
			int iEffect = deNone;
			FOnDrop(this, dataObject, State, pt, iEffect, result);
		}
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

HRESULT __stdcall TSynDragSource::QueryContinueDrag(int fEscapePressed, unsigned long grfKeyState)
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

HRESULT __stdcall TSynDragSource::GiveFeedback(unsigned long dwEffect)
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



}  // namespace Syneditdragdrop

