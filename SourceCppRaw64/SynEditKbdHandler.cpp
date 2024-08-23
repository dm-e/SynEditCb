#include <vcl.h>
#pragma hdrstop

#include "SynEditKbdHandler.h"

using namespace std;
using namespace d2c_system;
using namespace System;
using namespace Vcl::Controls;

namespace Syneditkbdhandler
{

__fastcall TKeyboardControl::TKeyboardControl(TComponent* AOwner) : inherited(AOwner) {}
__fastcall TKeyboardControl::TKeyboardControl(HWND ParentWindow) : inherited(ParentWindow) {}



/* TSynEditKbdHandler */

void __fastcall TSynEditKbdHandler::AddKeyDownHandler(TKeyEvent aHandler)
{
	fKeyDownChain->Add(*((TMethod*) &aHandler));
}

void __fastcall TSynEditKbdHandler::AddKeyUpHandler(TKeyEvent aHandler)
{
	fKeyUpChain->Add(*((TMethod*) &aHandler));
}

void __fastcall TSynEditKbdHandler::AddKeyPressHandler(TKeyPressEvent aHandler)
{
	fKeyPressChain->Add(*((TMethod*) &aHandler));
}

void __fastcall TSynEditKbdHandler::AddMouseDownHandler(TMouseEvent aHandler)
{
	fMouseDownChain->Add(*((TMethod*) &aHandler));
}

void __fastcall TSynEditKbdHandler::AddMouseUpHandler(TMouseEvent aHandler)
{
	fMouseUpChain->Add(*((TMethod*) &aHandler));
}

void __fastcall TSynEditKbdHandler::AddMouseCursorHandler(TMouseCursorEvent aHandler)
{
	fMouseCursorChain->Add(*((TMethod*) &aHandler));
}

__fastcall TSynEditKbdHandler::TSynEditKbdHandler()
 : fKeyPressChain(new TMethodList()),
			fKeyDownChain(nullptr),
			fKeyUpChain(nullptr),
			fMouseDownChain(nullptr),
			fMouseUpChain(nullptr),
			fMouseCursorChain(nullptr),
			fInKeyPress(false),
			fInKeyDown(false),
			fInKeyUp(false),
			fInMouseDown(false),
			fInMouseUp(false),
			fInMouseCursor(false)
{
	//# inherited::Create();

  /* Elements to handle KeyDown-Events */
	fKeyDownChain = new TMethodList();

  /* Elements to handle KeyUp-Events */
	fKeyUpChain = new TMethodList();

  /* Elements to handle KeyPress-Events */
	fMouseDownChain = new TMethodList();

  /* Elements to handle MouseUp Events */
	fMouseUpChain = new TMethodList();

  /* Elements to handle MouseCursor Events */
	fMouseCursorChain = new TMethodList();
}

__fastcall TSynEditKbdHandler::~TSynEditKbdHandler()
{
	delete fKeyPressChain;
	delete fKeyDownChain;
	delete fKeyUpChain;
	delete fMouseDownChain;
	delete fMouseUpChain;
	delete fMouseCursorChain;
	//# inherited::Destroy();
}

void __fastcall TSynEditKbdHandler::ExecuteKeyDown(TObject* Sender, WORD& key, TShiftState Shift)
{
	int Idx = 0;
	if(fInKeyDown)
		return;
	fInKeyDown = true;
	try
	{
		/*# with fKeyDownChain do */
		{
			auto with0 = fKeyDownChain;
			int stop = 0;
			for(stop = 0, Idx = with0->Count - 1; Idx >= stop; Idx--)
			{
				(*(TKeyEvent*)&with0->Items[Idx])(Sender, key, Shift);
				if(key == 0)
				{
					fInKeyDown = false;
					return;
				}
			}
		}
	}
	__finally
	{
		fInKeyDown = false;
	}
}

void __fastcall TSynEditKbdHandler::ExecuteKeyUp(TObject* Sender, WORD& key, TShiftState Shift)
{
	int Idx = 0;
	if(fInKeyUp)
		return;
	fInKeyUp = true;
	try
	{
		/*# with fKeyUpChain do */
		{
			auto with0 = fKeyUpChain;
			int stop = 0;
			for(stop = 0, Idx = with0->Count - 1; Idx >= stop; Idx--)
			{
				(*(TKeyEvent*)&with0->Items[Idx])(Sender, key, Shift);
				if(key == 0)
				{
					fInKeyUp = false;
					return;
				}
			}
		}
	}
	__finally
	{
		fInKeyUp = false;
	}
}

void __fastcall TSynEditKbdHandler::ExecuteKeyPress(TObject* Sender, WideChar& key)
{
	int Idx = 0;
	if(fInKeyPress)
		return;
	fInKeyPress = true;
	try
	{
		/*# with fKeyPressChain do */
		{
			auto with0 = fKeyPressChain;
			int stop = 0;
			for(stop = 0, Idx = with0->Count - 1; Idx >= stop; Idx--)
			{
				(*(TKeyPressEvent*)&with0->Items[Idx])(Sender, key);
				if(key == L'\x00')
				{
					fInKeyPress = false;
					return;
				}
			}
		}
	}
	__finally
	{
		fInKeyPress = false;
	}
}

void __fastcall TSynEditKbdHandler::ExecuteMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	int cHandler = 0;
	if(fInMouseDown)
		return;
	fInMouseDown = true;
	try
	{
		int stop = 0;
		for(stop = 0, cHandler = fMouseDownChain->Count - 1; cHandler >= stop; cHandler--)
		{
			(*(TMouseEvent*)&fMouseDownChain->Items[cHandler])(Sender, Button, Shift, X, Y);
		}
	}
	__finally
	{
		fInMouseDown = false;
	}
}

void __fastcall TSynEditKbdHandler::ExecuteMouseUp(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	int cHandler = 0;
	if(fInMouseUp)
		return;
	fInMouseUp = true;
	try
	{
		int stop = 0;
		for(stop = 0, cHandler = fMouseUpChain->Count - 1; cHandler >= stop; cHandler--)
		{
			(*(TMouseEvent*)&fMouseUpChain->Items[cHandler])(Sender, Button, Shift, X, Y);
		}
	}
	__finally
	{
		fInMouseUp = false;
	}
}

void __fastcall TSynEditKbdHandler::ExecuteMouseCursor(TObject* Sender, const TBufferCoord& aLineCharPos, TCursor& aCursor)
{
	int cHandler = 0;
	if(fInMouseCursor)
		return;
	fInMouseCursor = true;
	try
	{
		int stop = 0;
		for(stop = 0, cHandler = fMouseCursorChain->Count - 1; cHandler >= stop; cHandler--)
		{
			(*(TMouseCursorEvent*)&fMouseCursorChain->Items[cHandler])(Sender, aLineCharPos, aCursor);
		}
	}
	__finally
	{
		fInMouseCursor = false;
	}
}

void __fastcall TSynEditKbdHandler::RemoveKeyDownHandler(TKeyEvent aHandler)
{
	fKeyDownChain->Remove(*((TMethod*) &aHandler));
}

void __fastcall TSynEditKbdHandler::RemoveKeyUpHandler(TKeyEvent aHandler)
{
	fKeyUpChain->Remove(*((TMethod*) &aHandler));
}

void __fastcall TSynEditKbdHandler::RemoveKeyPressHandler(TKeyPressEvent aHandler)
{
	fKeyPressChain->Remove(*((TMethod*) &aHandler));
}

void __fastcall TSynEditKbdHandler::RemoveMouseDownHandler(TMouseEvent aHandler)
{
	fMouseDownChain->Remove(*((TMethod*) &aHandler));
}

void __fastcall TSynEditKbdHandler::RemoveMouseUpHandler(TMouseEvent aHandler)
{
	fMouseUpChain->Remove(*((TMethod*) &aHandler));
}

void __fastcall TSynEditKbdHandler::RemoveMouseCursorHandler(TMouseCursorEvent aHandler)
{
	fMouseCursorChain->Remove(*((TMethod*) &aHandler));
}

/* TMethodList */

void __fastcall TMethodList::Add(const TMethod& caHandler)
{
	TMethod aHandler = caHandler;
	FData->Add(aHandler.Data);
	FData->Add(aHandler.Code);
}

__fastcall TMethodList::TMethodList()
 : FData(new TList())
{
	//# inherited::Create();
}

__fastcall TMethodList::~TMethodList()
{
	delete FData;
	//# inherited::Destroy();
}

int __fastcall TMethodList::GetCount()
{
	int result = 0;
	result = (NativeInt)(FData->Count / /*div*/ 2);
	return result;
}

TMethod __fastcall TMethodList::GetItem(int Index)
{
	TMethod result = {};
	Index = Index * 2;
	result.Data = FData->Items[Index];
	result.Code = FData->Items[Index + 1];
	return result;
}

void __fastcall TMethodList::Remove(const TMethod& caHandler)
{
	TMethod aHandler = caHandler;
	int cpos = 0;
	cpos = FData->Count - 2;
	while(cpos >= 0)
	{
		if((FData->List[cpos] == aHandler.Data) && (FData->List[cpos + 1] == aHandler.Code))
		{
			FData->Delete(cpos);
			FData->Delete(cpos);
			return;
		}
		cpos -= 2;
	}
}


}  // namespace SynEditKbdHandler

