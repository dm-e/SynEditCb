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

void __fastcall TSynEditKbdHandler::AddKeyDownHandler(const TKeyEvent& aHandler)
{
	fKeyDownChain->Add(to_method(aHandler));
}

void __fastcall TSynEditKbdHandler::AddKeyUpHandler(const TKeyEvent& aHandler)
{
	fKeyUpChain->Add(to_method(aHandler));
}

void __fastcall TSynEditKbdHandler::AddKeyPressHandler(const TKeyPressEvent& aHandler)
{
	fKeyPressChain->Add(to_method(aHandler));
}

void __fastcall TSynEditKbdHandler::AddMouseDownHandler(const TMouseEvent& aHandler)
{
	fMouseDownChain->Add(to_method(aHandler));
}

void __fastcall TSynEditKbdHandler::AddMouseUpHandler(const TMouseEvent& aHandler)
{
	fMouseUpChain->Add(to_method(aHandler));
}

void __fastcall TSynEditKbdHandler::AddMouseCursorHandler(const TMouseCursorEvent& aHandler)
{
	fMouseCursorChain->Add(to_method(aHandler));
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

void __fastcall TSynEditKbdHandler::ExecuteKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
	int idx = 0;
	if(fInKeyDown)
		return;
	fInKeyDown = true;
	try
	{
		/*# with fKeyDownChain do */
		{
			auto with0 = fKeyDownChain;
			int stop = 0;
			for(stop = 0, idx = with0->Count - 1; idx >= stop; idx--)
			{
				from_method<TKeyEvent>(with0->Items[idx])(Sender, Key, Shift);
				if(Key == 0)
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

void __fastcall TSynEditKbdHandler::ExecuteKeyUp(TObject* Sender, WORD& Key, TShiftState Shift)
{
	int idx = 0;
	if(fInKeyUp)
		return;
	fInKeyUp = true;
	try
	{
		/*# with fKeyUpChain do */
		{
			auto with0 = fKeyUpChain;
			int stop = 0;
			for(stop = 0, idx = with0->Count - 1; idx >= stop; idx--)
			{
				from_method<TKeyEvent>(with0->Items[idx])(Sender, Key, Shift);
				if(Key == 0)
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

void __fastcall TSynEditKbdHandler::ExecuteKeyPress(TObject* Sender, WideChar& Key)
{
	int idx = 0;
	if(fInKeyPress)
		return;
	fInKeyPress = true;
	try
	{
		/*# with fKeyPressChain do */
		{
			auto with0 = fKeyPressChain;
			int stop = 0;
			for(stop = 0, idx = with0->Count - 1; idx >= stop; idx--)
			{
				from_method<TKeyPressEvent>(with0->Items[idx])(Sender, Key);
				if(Key == L'\x00')
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
			from_method<TMouseEvent>(fMouseDownChain->Items[cHandler])(Sender, Button, Shift, X, Y);
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
			from_method<TMouseEvent>(fMouseUpChain->Items[cHandler])(Sender, Button, Shift, X, Y);
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
			from_method<TMouseCursorEvent>(fMouseCursorChain->Items[cHandler])(Sender, aLineCharPos, aCursor);
		}
	}
	__finally
	{
		fInMouseCursor = false;
	}
}

void __fastcall TSynEditKbdHandler::RemoveKeyDownHandler(const TKeyEvent& aHandler)
{
	fKeyDownChain->Remove(to_method(aHandler));
}

void __fastcall TSynEditKbdHandler::RemoveKeyUpHandler(const TKeyEvent& aHandler)
{
	fKeyUpChain->Remove(to_method(aHandler));
}

void __fastcall TSynEditKbdHandler::RemoveKeyPressHandler(const TKeyPressEvent& aHandler)
{
	fKeyPressChain->Remove(to_method(aHandler));
}

void __fastcall TSynEditKbdHandler::RemoveMouseDownHandler(const TMouseEvent& aHandler)
{
	fMouseDownChain->Remove(to_method(aHandler));
}

void __fastcall TSynEditKbdHandler::RemoveMouseUpHandler(const TMouseEvent& aHandler)
{
	fMouseUpChain->Remove(to_method(aHandler));
}

void __fastcall TSynEditKbdHandler::RemoveMouseCursorHandler(const TMouseCursorEvent& aHandler)
{
	fMouseCursorChain->Remove(to_method(aHandler));
}

/* TMethodList */

void __fastcall TMethodList::Add(const TMethod& caHandler)
{
	TMethod aHandler = caHandler;
	fData->Add(aHandler.Data);
	fData->Add(aHandler.Code);
}

__fastcall TMethodList::TMethodList()
 : fData(new TList())
{
	//# inherited::Create();
}

__fastcall TMethodList::~TMethodList()
{
	delete fData;
	//# inherited::Destroy();
}

int __fastcall TMethodList::GetCount()
{
	int result = 0;
	result = (NativeInt)(fData->Count / /*div*/ 2);
	return result;
}

TMethod __fastcall TMethodList::GetItem(int Index)
{
	TMethod result = {};
	Index = Index * 2;
	result.Data = fData->Items[Index];
	result.Code = fData->Items[Index + 1];
	return result;
}

void __fastcall TMethodList::Remove(const TMethod& caHandler)
{
	TMethod aHandler = caHandler;
	int cPos = 0;
	cPos = fData->Count - 2;
	while(cPos >= 0)
	{
		if((fData->List[cPos] == aHandler.Data) && (fData->List[cPos + 1] == aHandler.Code))
		{
			fData->Delete(cPos);
			fData->Delete(cPos);
			return;
		}
		cPos -= 2;
	}
}


}  // namespace Syneditkbdhandler

