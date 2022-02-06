
#include <vcl.h>
#pragma hdrstop

#include "SynURIOpener.h"
#include <Winapi.ShellAPI.hpp>
#include <Vcl.Forms.hpp>
#include "SynEditHighlighter.h"
#include "SynEditKeyConst.h"
#include <System.SysUtils.hpp>
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Synedithighlighter;
using namespace Syneditkeyconst;
using namespace Synhighlighteruri;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Types;
using namespace Vcl::Controls;
using namespace Vcl::Forms;
using namespace Winapi::Shellapi;

namespace Synuriopener
{



class TAccessCustomSynEdit : public TCustomSynEdit
{
public:
	typedef TCustomSynEdit inherited;	
	#include "SynURIOpener_friends.inc"
	__fastcall TAccessCustomSynEdit(TComponent* AOwner) : inherited(AOwner) {}
	__fastcall TAccessCustomSynEdit(HWND ParentWindow) : inherited(ParentWindow) {}
};

class TAccessSynURISyn : public TSynURISyn
{
public:
	typedef TSynURISyn inherited;	
	#include "SynURIOpener_friends.inc"
	__fastcall TAccessSynURISyn(TComponent* AOwner) : inherited(AOwner) {}
};

/* TSynURIOpener */

__fastcall TSynURIOpener::TSynURIOpener(TComponent* AOwner)
 : inherited(AOwner),
			FControlDown(false),
			FCtrlActivatesLinks(false),
			FEditor(nullptr),
			fMouseDownX(0),
			fMouseDownY(0),
			FURIHighlighter(nullptr),
			FVisitedURIs(nullptr)
{
	FCtrlActivatesLinks = true;
	FVisitedURIs = new TStringList();
	FVisitedURIs->Sorted = true;
}

__fastcall TSynURIOpener::~TSynURIOpener()
{
	delete FVisitedURIs;
	// inherited;
}


bool __fastcall TSynURIOpener::MouseInSynEdit()
{
	bool result = false;
	TPoint Pt = {};
	Pt = Mouse->CursorPos;
	result = PtInRect(FEditor->ClientRect, FEditor->ScreenToClient(Pt));
	return result;
}

void __fastcall TSynURIOpener::NewKeyDown(TObject* Sender, WORD& key, TShiftState Shift)
{
	if((key == SYNEDIT_CONTROL) && !FControlDown && MouseInSynEdit())
	{
		FControlDown = true;
		((TAccessCustomSynEdit*) FEditor)->UpdateMouseCursor();
	}
}

void __fastcall TSynURIOpener::NewKeyUp(TObject* Sender, WORD& key, TShiftState Shift)
{
	if((key == SYNEDIT_CONTROL) && FControlDown)
	{
		FControlDown = false;
		((TAccessCustomSynEdit*) FEditor)->UpdateMouseCursor();
	}
}

bool __fastcall IsControlPressed()
{
	bool result = false;
	result = GetAsyncKeyState(VK_CONTROL) != 0;
	return result;
}

void __fastcall TSynURIOpener::NewMouseCursor(TObject* Sender, const TBufferCoord& aLineCharPos, TCursor& aCursor)
{
	int TokenType = 0;
	int Start = 0;
	String Token;
	TSynHighlighterAttributes* Attri = nullptr;
	FControlDown = IsControlPressed();
	if(!(FCtrlActivatesLinks && !FControlDown || (FEditor->ComponentState.Contains(csDesigning))) && FEditor->Focused())
		/*# with FEditor do */
		{
			auto with0 = FEditor;
			with0->GetHighlighterAttriAtRowColEx(aLineCharPos, Token, TokenType, Start, Attri);
			if(ASSIGNED(URIHighlighter) && ((Attri == URIHighlighter->URIAttri) || (Attri == URIHighlighter->VisitedURIAttri)) && !((with0->Options.Contains(TSynEditorOption::eoDragDropEditing)) && with0->IsPointInSelection(aLineCharPos)))
				aCursor = crHandPoint;
		}
}

void __fastcall TSynURIOpener::NewMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if((Button == Vcl::Controls::TMouseButton::mbLeft) && !(FCtrlActivatesLinks) || FControlDown)
	{
		fMouseDownX = X;
		fMouseDownY = Y;
	}
}

void __fastcall TSynURIOpener::NewMouseUp(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TBufferCoord ptLineCol = {};
	int TokenType = 0;
	int Start = 0;
	String Token;
	TSynHighlighterAttributes* Attri = nullptr;
	if((Button != Vcl::Controls::TMouseButton::mbLeft) || (FCtrlActivatesLinks && !FControlDown) || (Abs(fMouseDownX - X) > 4) || (Abs(fMouseDownY - Y) > 4))
		return;
	/*# with TAccessCustomSynEdit(FEditor) do */
	{
		auto with0 = ((TAccessCustomSynEdit*) FEditor);
		if((with0->Options.Contains(TSynEditorOption::eoDragDropEditing)) && with0->IsPointInSelection(ptLineCol))
			return;
		if(X >= with0->fGutterWidth)
		{
			ptLineCol = with0->DisplayToBufferPos(with0->PixelsToRowColumn(X, Y));
			with0->GetHighlighterAttriAtRowColEx(ptLineCol, Token, TokenType, Start, Attri);
			if(ASSIGNED(URIHighlighter) && ((Attri == URIHighlighter->URIAttri) || (Attri == URIHighlighter->VisitedURIAttri)) && !((with0->Options.Contains(TSynEditorOption::eoDragDropEditing)) && with0->IsPointInSelection(ptLineCol)))
			{
				OpenLink(Token, TokenType);
				with0->InvalidateLine(ptLineCol.Line);
			}
		}
	}
}

void __fastcall TSynURIOpener::Notification(TComponent* AComponent, TOperation Operation)
{
	inherited::Notification(AComponent, Operation);
	if((Operation == opRemove) && ASSIGNED(Editor) && (AComponent == Editor))
		Editor = nullptr;
	if((Operation == opRemove) && ASSIGNED(URIHighlighter) && (AComponent == URIHighlighter))
		URIHighlighter = nullptr;
}

void __fastcall TSynURIOpener::OpenLink(String URI, int LinkType)
{
	FVisitedURIs->Add(URI);
	switch(((TtkTokenKind) LinkType))
	{
		case tkMailtoLink:
		if(Pos(L"mailto:", URI) != 1)
			URI = String(L"mailto:") + URI;
		break;
		case tkWebLink:
		URI = String(L"http://") + URI;
		break;
		default:
		  ;
		break;
	}/*SW_SHOWNORMAL*/
	ShellExecute(0, nullptr, ustr2pwchar(URI), nullptr, nullptr, 1);
}

void __fastcall TSynURIOpener::SetEditor(TCustomSynEdit* const Value)
{
	if(Editor != Value)
	{
		if(!(ComponentState.Contains(csDesigning)) && ASSIGNED(FEditor))
		{
			/*# with FEditor do */
			{
				auto with0 = FEditor;
				with0->RemoveKeyDownHandler(NewKeyDown);
				with0->RemoveKeyUpHandler(NewKeyUp);
				with0->RemoveMouseCursorHandler(NewMouseCursor);
				with0->RemoveMouseDownHandler(NewMouseDown);
				with0->RemoveMouseUpHandler(NewMouseUp);
			}
		}
		FEditor = const_cast<TCustomSynEdit*>(Value);
		if(!(ComponentState.Contains(csDesigning)) && ASSIGNED(FEditor))
		{
			/*# with FEditor do */
			{
				auto with1 = FEditor;
				with1->AddKeyDownHandler(NewKeyDown);
				with1->AddKeyUpHandler(NewKeyUp);
				with1->AddMouseCursorHandler(NewMouseCursor);
				with1->AddMouseDownHandler(NewMouseDown);
				with1->AddMouseUpHandler(NewMouseUp);
			}
		}
	}
}

void __fastcall TSynURIOpener::SetURIHighlighter(TSynURISyn* const Value)
{
	if(!(ComponentState.Contains(csDesigning)) && ASSIGNED(URIHighlighter))
		((TAccessSynURISyn*) FURIHighlighter)->SetAlreadyVisitedURIFunc(nullptr);
	FURIHighlighter = const_cast<TSynURISyn*>(Value);
	if(!(ComponentState.Contains(csDesigning)) && ASSIGNED(URIHighlighter))
		((TAccessSynURISyn*) FURIHighlighter)->SetAlreadyVisitedURIFunc(VisitedURI);
}

bool __fastcall TSynURIOpener::VisitedURI(String URI)
{
	bool result = false;
	int Dummy = 0;
	result = FVisitedURIs->Find(URI, Dummy);
	return result;
}
const Char* const IDC_LINK = (MakeIntResource) 32649;
THandle CursorHandle = 0;
static bool SynURIOpener_Initialized = false;

void SynURIOpener_initialization()
{
	if(SynURIOpener_Initialized)
		return;
	
	SynURIOpener_Initialized = true;
	
	CursorHandle = (THandle) LoadCursor(0, const_cast<LPCWSTR>(IDC_LINK));
	if(CursorHandle != 0)
		Screen->Cursors[crHandPoint] = (HICON) CursorHandle;
}
class SynURIOpener_unit
{
public:
	SynURIOpener_unit()
	{
		SynURIOpener_initialization();
	}
};

SynURIOpener_unit _SynURIOpener_unit;

}  // namespace SynURIOpener

