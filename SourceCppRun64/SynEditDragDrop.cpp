                                                                                                  #include <vcl.h>
#pragma hdrstop

#include "SynEditDragDrop.h"
#include "d2c_graphics.h"
#include "d2c_refconvert.h"

using namespace std;
using namespace d2c_system;
using namespace System;

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
    if (Keys.Contains(ssCtrl))
    {
        result = deCopy;
    }
    return result;
}

/* TDropTarget */

HRESULT STDMETHODCALLTYPE TSynDropTarget::DragEnter(IDataObject* DataObj, DWORD grfKeyState, POINTL pt, DWORD* dwEffect)
{
	if (dwEffect == nullptr)
		return E_POINTER;
    HRESULT result = 0;
    result = S_OK;
    try
	{
		DragEnter(DataObj, KeysToShiftState(static_cast<WORD>(grfKeyState)), POINTLToTPoint(pt), d2c_inout_ref_conv<int>(dwEffect), result);
	}
    catch (...)
    {
        result = E_UNEXPECTED;
    }
    return result;
}

HRESULT STDMETHODCALLTYPE TSynDropTarget::DragLeave()
{
    HRESULT result = 0;
    result = S_OK;
    try
    {
        DragLeave(result);
    }
    catch (...)
    {
        result = E_UNEXPECTED;
    }
    return result;
}

HRESULT STDMETHODCALLTYPE TSynDropTarget::DragOver(DWORD grfKeyState, POINTL pt, DWORD* dwEffect)
{
    if (dwEffect == nullptr)
        return E_POINTER;
    HRESULT result = 0;
    result = S_OK;
    try
	{
		DragOver(KeysToShiftState(static_cast<WORD>(grfKeyState)), POINTLToTPoint(pt), d2c_inout_ref_conv<int>(dwEffect), result);
    }
    catch (...)
    {
        result = E_UNEXPECTED;
    }
    return result;
}

HRESULT STDMETHODCALLTYPE TSynDropTarget::Drop(IDataObject* DataObj, DWORD grfKeyState, POINTL pt, DWORD* dwEffect)
{
    if (dwEffect == nullptr)
        return E_POINTER;
    HRESULT result = 0;
    result = S_OK;
    try
	{
		Drop(DataObj, KeysToShiftState(static_cast<WORD>(grfKeyState)), POINTLToTPoint(pt), d2c_inout_ref_conv<int>(dwEffect), result);
    }
    catch (...)
    {
        result = E_UNEXPECTED;
    }
    return result;
}

void __fastcall TSynDropTarget::DragEnter(const _di_IDataObject& DataObject, TShiftState State, const TPoint& cPt, int& Effect, HRESULT& Result)
{
    TPoint Pt = cPt;
    Effect = StandardEffect(State);
    if (Assigned(FOnDragEnter))
        FOnDragEnter(this, DataObject, State, Pt, Effect, Result);
    if (Effect == deNone)
        FDataObject = nullptr;
    else
        FDataObject = DataObject;
    }

void __fastcall TSynDropTarget::DragLeave(HRESULT& Result)
{
	if(ASSIGNED(FDataObject))
        try
        {
            if (Assigned(FOnDragLeave))
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
    if (FDataObject == nullptr)
    {
        Effect = deNone;
        return;
    }
    Effect = StandardEffect(State);
    if (Assigned(FOnDragOver))
        FOnDragOver(this, FDataObject, State, Pt, Effect, Result);
    }

void __fastcall TSynDropTarget::Drop(const _di_IDataObject& DataObject, TShiftState State, const TPoint& cPt, int& Effect, HRESULT& Result)
{
    TPoint Pt = cPt;
    if (FDataObject == nullptr)
    {
        Effect = deNone;
        return;
    }
    Effect = StandardEffect(State);
    try
    {
        if (Assigned(FOnDrop))
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

HRESULT STDMETHODCALLTYPE TSynDragSource::QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState)
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

HRESULT STDMETHODCALLTYPE TSynDragSource::GiveFeedback(DWORD dwEffect)
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

