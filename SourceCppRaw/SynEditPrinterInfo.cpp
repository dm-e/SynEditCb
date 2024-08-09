#include <vcl.h>
#pragma hdrstop

#include "SynEditPrinterInfo.h"

using namespace std;
using namespace d2c_system;
using namespace System;

namespace Syneditprinterinfo
{

__fastcall TSynEditPrinterInfo::TSynEditPrinterInfo() {}



/* TSynEditPrinterInfo */

int __fastcall TSynEditPrinterInfo::PixFromBottom(double mmValue)
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = (int) Round(mmValue * FYPixPrmm - FBottomGutter);
	return result;
}

int __fastcall TSynEditPrinterInfo::PixFromLeft(double mmValue)
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = (int) Round(mmValue * FXPixPrmm - FLeftGutter);
	return result;
}

int __fastcall TSynEditPrinterInfo::PixFromRight(double mmValue)
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = (int) Round(mmValue * FXPixPrmm - FRightGutter);
	return result;
}

int __fastcall TSynEditPrinterInfo::PixFromTop(double mmValue)
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = (int) Round(mmValue * FYPixPrmm - FTopGutter);
	return result;
}
/*In case of no printers installed this information is used
 (I think it's taken from a HP LaserJet III with A4 paper)*/

void __fastcall TSynEditPrinterInfo::FillDefault()
{
	FPhysicalWidth = 2481;
	FPhysicalHeight = 3507;
	FPrintableWidth = 2358;
	FPrintableHeight = 3407;
	FLeftGutter = 65;
	FRightGutter = 58;
	FTopGutter = 50;
	FBottomGutter = 50;
	FXPixPrInch = 300;
	FYPixPrInch = 300;
	FXPixPrmm = (float) (double(FXPixPrInch) / 25.4);
	FYPixPrmm = (float) (double(FYPixPrInch) / 25.4);
}

int __fastcall TSynEditPrinterInfo::GetBottomGutter()
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = FBottomGutter;
	return result;
}

int __fastcall TSynEditPrinterInfo::GetLeftGutter()
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = FLeftGutter;
	return result;
}

int __fastcall TSynEditPrinterInfo::GetPhysicalHeight()
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = FPhysicalHeight;
	return result;
}

int __fastcall TSynEditPrinterInfo::GetPhysicalWidth()
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = FPhysicalWidth;
	return result;
}

int __fastcall TSynEditPrinterInfo::GetPrintableHeight()
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = FPrintableHeight;
	return result;
}

int __fastcall TSynEditPrinterInfo::GetPrintableWidth()
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = FPrintableWidth;
	return result;
}

int __fastcall TSynEditPrinterInfo::GetRightGutter()
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = FRightGutter;
	return result;
}

int __fastcall TSynEditPrinterInfo::GetTopGutter()
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = FTopGutter;
	return result;
}

int __fastcall TSynEditPrinterInfo::GetXPixPrInch()
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = FXPixPrInch;
	return result;
}

float __fastcall TSynEditPrinterInfo::GetXPixPrmm()
{
	float result = 0.0F;
	if(!FIsUpdated)
		UpdatePrinter();
	result = FXPixPrmm;
	return result;
}

int __fastcall TSynEditPrinterInfo::GetYPixPrInch()
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = FYPixPrInch;
	return result;
}

float __fastcall TSynEditPrinterInfo::GetYPixPrmm()
{
	float result = 0.0F;
	if(!FIsUpdated)
		UpdatePrinter();
	result = FYPixPrmm;
	return result;
}

void __fastcall TSynEditPrinterInfo::UpdatePrinter()
{
	FIsUpdated = true;
	Printer()->Refresh();
	if(Printer()->Printers->Count <= 0)
	{
		FillDefault();
		return;
	}
	FPhysicalWidth = GetDeviceCaps(Printer()->Handle, ::PhysicalWidth);
	FPhysicalHeight = GetDeviceCaps(Printer()->Handle, ::PhysicalHeight);
	FPrintableWidth = Printer()->PageWidth; /*or GetDeviceCaps(Printer.Handle, HorzRes);*/
	FPrintableHeight = Printer()->PageHeight; /*or GetDeviceCaps(Printer.Handle, VertRes);*/
	FLeftGutter = GetDeviceCaps(Printer()->Handle, PHYSICALOFFSETX);
	FTopGutter = GetDeviceCaps(Printer()->Handle, PHYSICALOFFSETY);
	FRightGutter = FPhysicalWidth - FPrintableWidth - FLeftGutter;
	FBottomGutter = FPhysicalHeight - FPrintableHeight - FTopGutter;
	FXPixPrInch = GetDeviceCaps(Printer()->Handle, LOGPIXELSX);
	FYPixPrInch = GetDeviceCaps(Printer()->Handle, LOGPIXELSY);
	FXPixPrmm = (float) (double(FXPixPrInch) / 25.4);
	FYPixPrmm = (float) (double(FYPixPrInch) / 25.4);
}


}  // namespace SynEditPrinterInfo

