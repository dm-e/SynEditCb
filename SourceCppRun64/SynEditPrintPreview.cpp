#include <vcl.h>
#pragma hdrstop

#include "SynEditPrintPreview.h"
#include <System.Types.hpp>
#include "SynEditStrConst.h"
#include "d2c_graphics.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditprint;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Types;
using namespace System::Uitypes;
using namespace Vcl::Controls;
using namespace Vcl::Graphics;

namespace Syneditprintpreview
{
#define Syneditprintpreview__0 (TControlStyle() << csNeedsBorderPaint)

__fastcall TSynEditPrintPreview::TSynEditPrintPreview(HWND ParentWindow) : inherited(ParentWindow) {}


const int MARGIN_X = 12; // margin width left and right of page
const int MARGIN_Y = 12; // margin height above and below page
const int SHADOW_SIZE = 2; // page shadow width

/* TSynEditPrintPreview */

__fastcall TSynEditPrintPreview::TSynEditPrintPreview(TComponent* AOwner)
 : inherited(AOwner),
			FBorderStyle((TBorderStyle) bsSingle),
			FSynEditPrint(nullptr),
			FScaleMode(pscWholePage),
			FScalePercent(0),
			FPageBG((TColor) 0),
			FPageNumber(0),
			FShowScrollHint(false),
			FWheelAccumulator(0)
{
	ControlStyle = ControlStyle + Syneditprintpreview__0;
	FScaleMode = pscUserScaled;
	FScalePercent = 100;
	FPageBG = (TColor) clWhite;
	Width = 200;
	Height = 120;
	ParentColor = false;
	Color = (TColor) clAppWorkSpace;
	Visible = true;
	FPageNumber = 1;
	FShowScrollHint = true;
	Align = alClient;
	FWheelAccumulator = 0;
}

void __fastcall TSynEditPrintPreview::CreateParams(TCreateParams& Params)
{
	const DWORD BorderStyles[bsSingle - bsNone+ 1/*# TBorderStyle*/] = {0, (DWORD) WS_BORDER};
	inherited::CreateParams(Params);
	/*# with Params do */
	{
		auto& with0 = Params;
		with0.Style = with0.Style | WS_HSCROLL | WS_VSCROLL | BorderStyles[FBorderStyle] | WS_CLIPCHILDREN;
		if(NewStyleControls && Ctl3D && (FBorderStyle == bsSingle))
		{
			with0.Style = with0.Style & ~WS_BORDER;
			with0.ExStyle = with0.ExStyle | WS_EX_CLIENTEDGE;
		}
	}
}

int __fastcall TSynEditPrintPreview::GetPageHeightFromWidth(int AWidth)
{
	int result = 0;
	if(ASSIGNED(FSynEditPrint))
	{
		/*# with FSynEditPrint.PrinterInfo do */
		{
			auto with0 = FSynEditPrint->PrinterInfo;
			result = MulDiv(AWidth, with0->PhysicalHeight, with0->PhysicalWidth);
		}
	}
	else
	result = MulDiv(AWidth, 141, 100); // fake A4 size
	return result;
}

int __fastcall TSynEditPrintPreview::GetPageWidthFromHeight(int AHeight)
{
	int result = 0;
	if(ASSIGNED(FSynEditPrint))
	{
		/*# with FSynEditPrint.PrinterInfo do */
		{
			auto with0 = FSynEditPrint->PrinterInfo;
			result = MulDiv(AHeight, with0->PhysicalWidth, with0->PhysicalHeight);
		}
	}
	else
	result = MulDiv(AHeight, 100, 141); // fake A4 size
	return result;
}

int __fastcall TSynEditPrintPreview::GetPageHeight100Percent()
{
	int result = 0;
	HDC DC = 0;
	int ScreenDPI = 0;
	result = 0;
	DC = GetDC(0);
	ScreenDPI = GetDeviceCaps(DC, LOGPIXELSY);
	ReleaseDC(0, DC);
	if(ASSIGNED(FSynEditPrint))
		/*# with FSynEditPrint.PrinterInfo do */
		{
			auto with0 = FSynEditPrint->PrinterInfo;
			result = MulDiv(with0->PhysicalHeight, ScreenDPI, with0->YPixPrInch);
		}
	return result;
}

int __fastcall TSynEditPrintPreview::GetPageWidth100Percent()
{
	int result = 0;
	HDC DC = 0;
	int ScreenDPI = 0;
	result = 0;
	DC = GetDC(0);
	ScreenDPI = GetDeviceCaps(DC, LOGPIXELSX);
	ReleaseDC(0, DC);
	if(ASSIGNED(FSynEditPrint))
		/*# with FSynEditPrint.PrinterInfo do */
		{
			auto with0 = FSynEditPrint->PrinterInfo;
			result = MulDiv(with0->PhysicalWidth, ScreenDPI, with0->XPixPrInch);
		}
	return result;
}

void __fastcall TSynEditPrintPreview::Notification(TComponent* AComponent, TOperation Operation)
{
	inherited::Notification(AComponent, Operation);
	if((Operation == opRemove) && (AComponent == FSynEditPrint))
		SynEditPrint = nullptr;
}

void __fastcall TSynEditPrintPreview::PaintPaper()
{
	TRect rcClip = {};
	TRect rcPaper = {};
	HRGN rgnPaper = 0;
	int i = 0;
	/*# with Canvas do */
	{
		auto with0 = Canvas;
      // we work in MM_TEXT mapping mode here...
		rcClip = with0->ClipRect;
		if(IsRectEmpty(rcClip))
			return;
		with0->Brush->Color = this->Color;
		with0->Brush->Style = bsSolid;
		with0->Pen->Color = (TColor) clBlack;
		with0->Pen->Width = 1;
		with0->Pen->Style = psSolid;
		if((ComponentState.Contains(csDesigning)) || (!ASSIGNED(FSynEditPrint)))
		{
			with0->FillRect(rcClip);
			with0->Brush->Color = FPageBG;
			with0->Rectangle(MARGIN_X, MARGIN_Y, MARGIN_X + 30, MARGIN_Y + 43);
			return;
		}
      // fill background around paper
		/*# with rcPaper do */
		{
			auto& with1 = rcPaper;
			with1.Left = FVirtualOffset.X + FScrollPosition.X;
			if(ScaleMode == pscWholePage)
				with1.Top = FVirtualOffset.Y;
			else
				with1.Top = FVirtualOffset.Y + FScrollPosition.Y;
			with1.Right = with1.Left + FPageSize.X;
			with1.Bottom = with1.Top + FPageSize.Y;
			rgnPaper = CreateRectRgn(with1.Left, with1.Top, with1.Right + 1, with1.Bottom + 1);
		}
		if(NULLREGION != ExtSelectClipRgn(with0->Handle, rgnPaper, RGN_DIFF))
			with0->FillRect(rcClip);
      // paper shadow
		with0->Brush->Color = (TColor) clDkGray;
		/*# with rcPaper do */
		{
			auto& with2 = rcPaper;
			int stop = 0;
			for(stop = SHADOW_SIZE, i = 1; i <= stop; i++)
			{
				with0->Polyline(OPENARRAY(TPoint, (Point(with2.Left + i, with2.Bottom + i), Point(with2.Right + i, with2.Bottom + i), Point(with2.Right + i, with2.Top + i))));
			}
		}
      // paint paper background
		SelectClipRgn(with0->Handle, rgnPaper);
		with0->Brush->Color = FPageBG;
		/*# with rcPaper do */
		{
			auto& with3 = rcPaper;
			with0->Rectangle(with3.Left, with3.Top, with3.Right + 1, with3.Bottom + 1);
		}
		DeleteObject(rgnPaper);
	}
}

void __fastcall TSynEditPrintPreview::Paint()
{
	TPoint ptOrgScreen = {};
	/*# with Canvas do */
	{
		auto with0 = Canvas;
		PaintPaper();
		if((ComponentState.Contains(csDesigning)) || (!ASSIGNED(FSynEditPrint)))
			return;
      // paint the contents, clipped to the area inside of the print margins
      // correct scaling for output:
		SetMapMode(with0->Handle, MM_ANISOTROPIC);
      // compute the logical point (0, 0) in screen pixels
		/*# with FSynEditPrint.PrinterInfo do */
		{
			auto with1 = FSynEditPrint->PrinterInfo;
			SetWindowExtEx(with0->Handle, with1->PhysicalWidth, with1->PhysicalHeight, nullptr);
			SetViewportExtEx(with0->Handle, FPageSize.X, FPageSize.Y, nullptr);
			ptOrgScreen.X = MulDiv(with1->LeftGutter, FPageSize.X, with1->PhysicalWidth);
			ptOrgScreen.Y = MulDiv(with1->TopGutter, FPageSize.Y, with1->PhysicalHeight);
			ptOrgScreen.X += FVirtualOffset.X + FScrollPosition.X;
			if(ScaleMode == pscWholePage)
				ptOrgScreen.Y += FVirtualOffset.Y;
			else
				ptOrgScreen.Y += FVirtualOffset.Y + FScrollPosition.Y;
			SetViewportOrgEx(with0->Handle, ptOrgScreen.X, ptOrgScreen.Y, nullptr);
          // clip the output to the print margins
			IntersectClipRect(with0->Handle, 0, 0, with1->PrintableWidth, with1->PrintableHeight);
		}
		FSynEditPrint->PrintToCanvas(Canvas, FPageNumber);
	}
}

void __fastcall TSynEditPrintPreview::ScrollHorzFor(int Value)
{
	ScrollHorzTo(FScrollPosition.X + Value);
}

void __fastcall TSynEditPrintPreview::ScrollHorzTo(int Value)
{
	int nW = 0;
	int n = 0;
	nW = ClientWidth;
	n = nW - FVirtualSize.X;
	if(Value < n)
		Value = n;
	if(Value > 0)
		Value = 0;
	if(Value != FScrollPosition.X)
	{
		n = Value - FScrollPosition.X;
		FScrollPosition.X = Value;
		UpdateScrollbars();
		if(Abs(n) > (int)(nW / /*div*/ 2))
			Invalidate();
		else
		{
			ScrollWindow(Handle, n, 0, nullptr, nullptr);
			Update();
		}
	}
}

void __fastcall TSynEditPrintPreview::ScrollVertFor(int Value)
{
	ScrollVertTo(FScrollPosition.Y + Value);
}

void __fastcall TSynEditPrintPreview::ScrollVertTo(int Value)
{
	int nH = 0;
	int n = 0;
	nH = ClientHeight;
	n = nH - FVirtualSize.Y;
	if(Value < n)
		Value = n;
	if(Value > 0)
		Value = 0;
	if(Value != FScrollPosition.Y)
	{
		n = Value - FScrollPosition.Y;
		FScrollPosition.Y = Value;
		UpdateScrollbars();
		if(Abs(n) > (int)(nH / /*div*/ 2))
			Invalidate();
		else
		{
			ScrollWindow(Handle, 0, n, nullptr, nullptr);
			Update();
		}
	}
}

void __fastcall TSynEditPrintPreview::SizeChanged()
{
	int nWDef = 0;
	if(!(HandleAllocated() && ASSIGNED(FSynEditPrint)))
		return;
  // compute paper size
	switch(FScaleMode)
	{
		case pscWholePage:
		{
			FPageSize.X = ClientWidth - 2 * MARGIN_X - SHADOW_SIZE;
			FPageSize.Y = ClientHeight - 2 * MARGIN_Y - SHADOW_SIZE;
			nWDef = GetPageWidthFromHeight(FPageSize.Y);
			if(nWDef < FPageSize.X)
				FPageSize.X = nWDef;
			else
				FPageSize.Y = GetPageHeightFromWidth(FPageSize.X);
		}
		break;
		case pscPageWidth:
		{
			FPageSize.X = ClientWidth - 2 * MARGIN_X - SHADOW_SIZE;
			FPageSize.Y = GetPageHeightFromWidth(FPageSize.X);
		}
		break;
		case pscUserScaled:
		{
			FPageSize.X = MulDiv(GetPageWidth100Percent(), FScalePercent, 100);
			FPageSize.Y = MulDiv(GetPageHeight100Percent(), FScalePercent, 100);
		}
		break;
		default:
		  ;
		break;
	}
	FVirtualSize.X = FPageSize.X + 2 * MARGIN_X + SHADOW_SIZE;
	FVirtualSize.Y = FPageSize.Y + 2 * MARGIN_Y + SHADOW_SIZE;
	FVirtualOffset.X = MARGIN_X;
	if(FVirtualSize.X < ClientWidth)
		FVirtualOffset.X += (int)((ClientWidth - FVirtualSize.X) / /*div*/ 2);
	FVirtualOffset.Y = MARGIN_Y;
	if(FVirtualSize.Y < ClientHeight)
		FVirtualOffset.Y += (int)((ClientHeight - FVirtualSize.Y) / /*div*/ 2);
	UpdateScrollbars();
// TODO
	FScrollPosition.X = 0;
	FScrollPosition.Y = 0;
}

void __fastcall TSynEditPrintPreview::UpdateScrollbars()
{
	TScrollInfo si = {};
	FillChar((void**)&si, (int) sizeof(TScrollInfo), 0);
	si.cbSize = (UINT) sizeof(TScrollInfo);
	si.fMask = (UINT) SIF_ALL;
	switch(FScaleMode)
	{
		case pscWholePage:
        // hide horizontal scrollbar
		{
			ShowScrollBar(Handle, SB_HORZ, false);
        // show vertical scrollbar, enable if more than one page
			si.fMask = si.fMask | SIF_DISABLENOSCROLL;
			si.nMin = 1;
			if(ASSIGNED(FSynEditPrint))
			{
				si.nMax = FSynEditPrint->PageCount;
				si.nPos = FPageNumber;
			}
			else
			{
				si.nMax = 1;
				si.nPos = 1;
			}
			si.nPage = 1;
			SetScrollInfo(Handle, SB_VERT, &si, true);
		}
		break;
        // hide horizontal scrollbar
		case pscPageWidth:
		{
			ShowScrollBar(Handle, SB_HORZ, false);
        // show vertical scrollbar
			si.fMask = si.fMask | SIF_DISABLENOSCROLL;
			si.nMax = FVirtualSize.Y;
			si.nPos = -FScrollPosition.Y;
			si.nPage = (UINT) ClientHeight;
			SetScrollInfo(Handle, SB_VERT, &si, true);
		}
		break;
		case pscUserScaled:
		{
			ShowScrollBar(Handle, SB_HORZ, true);
			ShowScrollBar(Handle, SB_VERT, true);
			si.fMask = si.fMask | SIF_DISABLENOSCROLL;
        // show horizontal scrollbar
			si.nMax = FVirtualSize.X;
			si.nPos = -FScrollPosition.X;
			si.nPage = (UINT) ClientWidth;
			SetScrollInfo(Handle, SB_HORZ, &si, true);
        // show vertical scrollbar
			si.nMax = FVirtualSize.Y;
			si.nPos = -FScrollPosition.Y;
			si.nPage = (UINT) ClientHeight;
			SetScrollInfo(Handle, SB_VERT, &si, true);
		}
		break;
		default:
		  ;
		break;
	}
}

void __fastcall TSynEditPrintPreview::SetBorderStyle(TBorderStyle Value)
{
	if(Value != FBorderStyle)
	{
		FBorderStyle = Value;
		RecreateWnd();
	}
}

void __fastcall TSynEditPrintPreview::SetPageBG(TColor Value)
{
	if(FPageBG != Value)
	{
		FPageBG = Value;
		Invalidate();
	}
}

void __fastcall TSynEditPrintPreview::SetSynEditPrint(TSynEditPrint* Value)
{
	if(FSynEditPrint != Value)
	{
		FSynEditPrint = Value;
		if(ASSIGNED(FSynEditPrint))
			FSynEditPrint->FreeNotification(this);
	}
}

void __fastcall TSynEditPrintPreview::SetScaleMode(TSynPreviewScale Value)
{
	if(FScaleMode != Value)
	{
		FScaleMode = Value;
		FScrollPosition = Point(0, 0);
		SizeChanged();
		if(ASSIGNED(FOnScaleChange))                                            // JD 2002-01-9
			FOnScaleChange(this);                                                     // JD 2002-01-9
		Invalidate();
	}
}

void __fastcall TSynEditPrintPreview::SetScalePercent(int Value)
{
	if(FScalePercent != Value)
	{
		FScaleMode = pscUserScaled;
		FScrollPosition = Point(0, 0);
		FScalePercent = Value;
		SizeChanged();
		Invalidate();
	}
	else
	ScaleMode = pscUserScaled;
	if(ASSIGNED(FOnScaleChange))                                              // JD 2002-01-9
		FOnScaleChange(this);                                                       // JD 2002-01-9
}

void __fastcall TSynEditPrintPreview::WMEraseBkgnd(TWMEraseBkgnd& Msg)
{
	Msg.Result = 1;
}

void __fastcall TSynEditPrintPreview::WMHScroll(TWMHScroll& Msg)
{
	int nW = 0;
	if(FScaleMode != pscWholePage)
	{
		nW = ClientWidth;
		switch(Msg.ScrollCode)
		{
			case SB_TOP:
			ScrollHorzTo(0);
			break;
			case SB_BOTTOM:
			ScrollHorzTo(-FVirtualSize.X);
			break;
			case SB_LINEDOWN:
			ScrollHorzFor(-((int)(nW / /*div*/ 10)));
			break;
			case SB_LINEUP:
			ScrollHorzFor((int)(nW / /*div*/ 10));
			break;
			case SB_PAGEDOWN:
			ScrollHorzFor(-((int)(nW / /*div*/ 2)));
			break;
			case SB_PAGEUP:
			ScrollHorzFor((int)(nW / /*div*/ 2));
			break;
			case SB_THUMBPOSITION:
			case SB_THUMBTRACK:
			ScrollHorzTo(-Msg.Pos);
			break;
			default:
			  ;
			break;
		}
	}
}

void __fastcall TSynEditPrintPreview::WMSize(TWMSize& Msg)
{
	inherited::Dispatch(&Msg);  //#inherited method "WMSize" not not accessible;
	if(!(ComponentState.Contains(csDesigning)))
		SizeChanged();
}
THintWindow* ScrollHintWnd = nullptr;

THintWindow* __fastcall GetScrollHint()
{
	THintWindow* result = nullptr;
	if(ScrollHintWnd == nullptr)
	{
		//ScrollHintWnd = (THintWindow*) CreateObject(HintWindowClass)(Application);
		ScrollHintWnd = new THintWindow(Application);
		ScrollHintWnd->Visible = false;
	}
	result = ScrollHintWnd;
	return result;
}

void __fastcall TSynEditPrintPreview::WMVScroll(TWMVScroll& Msg)
{
	int nH = 0;
	String s;
	TRect rc = {};
	TPoint pt = {};
	THintWindow* ScrollHint = nullptr;
	if(FScaleMode == pscWholePage)
	{
		if(ASSIGNED(FSynEditPrint))
			switch(Msg.ScrollCode)
			{
				case SB_TOP:
				FPageNumber = 1;
				break;
				case SB_BOTTOM:
				FPageNumber = FSynEditPrint->PageCount;
				break;
				case SB_LINEDOWN:
				case SB_PAGEDOWN:
				{
					FPageNumber = FPageNumber + 1;
					if(FPageNumber > FSynEditPrint->PageCount)
						FPageNumber = FSynEditPrint->PageCount;
				}
				break;
				case SB_LINEUP:
				case SB_PAGEUP:
				{
					FPageNumber = FPageNumber - 1;
					if(FPageNumber < 1)
						FPageNumber = 1;
				}
				break;
				case SB_THUMBPOSITION:
				case SB_THUMBTRACK:
				{
					FPageNumber = Msg.Pos;
              //Showing hint window - principle copied from SynEdit.pas
					if(FShowScrollHint)
					{
						ScrollHint = GetScrollHint();
						if(!ScrollHint->Visible)
						{
							ScrollHint->Color = Application->HintColor;
							ScrollHint->Visible = true;
						}
						s = Format(SYNS_PreviewScrollInfoFmt, ARRAYOFCONST((FPageNumber)));
						rc = ScrollHint->CalcHintRect(200, s, nullptr);
						pt = ClientToScreen(Point(ClientWidth - rc.Right - 4, 10));
						OffsetRect(rc, pt.X, pt.Y);
						ScrollHint->ActivateHint(rc, s);
						SendMessage(ScrollHint->Handle, (UINT) WM_NCPAINT, 1, 0);
						ScrollHint->Update();
					}
				}
				break;
				case SB_ENDSCROLL:
				{
					if(FShowScrollHint)
					{
						ScrollHint = GetScrollHint();
						ScrollHint->Visible = false;
						ShowWindow(ScrollHint->Handle, SW_HIDE);
					}
				}
				break;
				default:
				  ;
				break;
			}
      /*Updating scroll position and redrawing*/
		FScrollPosition.Y = -(FPageNumber - 1);
		UpdateScrollbars();
		if(ASSIGNED(FOnPreviewPage))
			FOnPreviewPage(this, FPageNumber);
		Invalidate();
	}
	else
	{
		nH = ClientHeight;
		switch(Msg.ScrollCode)
		{
			case SB_TOP:
			ScrollVertTo(0);
			break;
			case SB_BOTTOM:
			ScrollVertTo(-FVirtualSize.Y);
			break;
			case SB_LINEDOWN:
			ScrollVertFor(-((int)(nH / /*div*/ 10)));
			break;
			case SB_LINEUP:
			ScrollVertFor((int)(nH / /*div*/ 10));
			break;
			case SB_PAGEDOWN:
			ScrollVertFor(-((int)(nH / /*div*/ 2)));
			break;
			case SB_PAGEUP:
			ScrollVertFor((int)(nH / /*div*/ 2));
			break;
			case SB_THUMBPOSITION:
			case SB_THUMBTRACK:
			ScrollVertTo(-Msg.Pos);
			break;
			default:
			  ;
			break;
		}
	}
}

void __fastcall TSynEditPrintPreview::WMMouseWheel(TWMMouseWheel& Message)
{
	bool bCtrl = false;

	auto MouseWheelUp = [&]() -> void 
	{
		if(bCtrl && (FPageNumber > 1))
			PreviousPage();
		else
			ScrollVertFor(WHEEL_DELTA);
	};

	auto MouseWheelDown = [&]() -> void 
	{
		if(bCtrl && (FPageNumber < PageCount))
			NextPage();
		else
			ScrollVertFor(-WHEEL_DELTA);
	};
	TPoint MousePos = {};
	bool IsNeg = false;
  /* Find modifiers */
	bCtrl = GetKeyState(VK_CONTROL) < 0;

  /* Find mouse pos and increment accumulator */
	MousePos = SmallPointToPoint(Message.Pos);
	FWheelAccumulator += Message.WheelDelta;

  /* Do actions while accumulated is bigger than delta */
	while(Abs(FWheelAccumulator) >= WHEEL_DELTA)
	{
		IsNeg = FWheelAccumulator < 0;
		FWheelAccumulator = Abs(FWheelAccumulator) - WHEEL_DELTA;
		if(IsNeg)
		{
			if(FWheelAccumulator != 0)
				FWheelAccumulator = -FWheelAccumulator;
			MouseWheelDown();
		}
		else
		MouseWheelUp();
	}
}

void __fastcall TSynEditPrintPreview::UpdatePreview()
{
	int OldScale = 0;
	TSynPreviewScale OldMode = pscWholePage;
	OldScale = ScalePercent;
	OldMode = ScaleMode;
	ScalePercent = 100;
	if(ASSIGNED(FSynEditPrint))
		FSynEditPrint->UpdatePages(Canvas);
	SizeChanged();
	Invalidate();
	ScaleMode = OldMode;
	if(ScaleMode == pscUserScaled)
		ScalePercent = OldScale;
	if(ASSIGNED(FOnPreviewPage))
		FOnPreviewPage(this, FPageNumber);
}

void __fastcall TSynEditPrintPreview::FirstPage()
{
	FPageNumber = 1;
	if(ASSIGNED(FOnPreviewPage))
		FOnPreviewPage(this, FPageNumber);
	Invalidate();
}

void __fastcall TSynEditPrintPreview::LastPage()
{
	if(ASSIGNED(FSynEditPrint))
		FPageNumber = FSynEditPrint->PageCount;
	if(ASSIGNED(FOnPreviewPage))
		FOnPreviewPage(this, FPageNumber);
	Invalidate();
}

void __fastcall TSynEditPrintPreview::NextPage()
{
	FPageNumber = FPageNumber + 1;
	if(ASSIGNED(FSynEditPrint) && (FPageNumber > FSynEditPrint->PageCount))
		FPageNumber = FSynEditPrint->PageCount;
	if(ASSIGNED(FOnPreviewPage))
		FOnPreviewPage(this, FPageNumber);
	Invalidate();
}

void __fastcall TSynEditPrintPreview::PreviousPage()
{
	FPageNumber = FPageNumber - 1;
	if(ASSIGNED(FSynEditPrint) && (FPageNumber < 1))
		FPageNumber = 1;
	if(ASSIGNED(FOnPreviewPage))
		FOnPreviewPage(this, FPageNumber);
	Invalidate();
}

void __fastcall TSynEditPrintPreview::Print()
{
	if(ASSIGNED(FSynEditPrint))
	{
		FSynEditPrint->Print();
		UpdatePreview();
	}
}

int __fastcall TSynEditPrintPreview::GetPageCount()
{
	int result = 0;
	result = SynEditPrint->PageCount;
	return result;
}


}  // namespace SynEditPrintPreview

