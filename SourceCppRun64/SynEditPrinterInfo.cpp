#include <vcl.h>
#pragma hdrstop

#include "SynEditPrinterInfo.h"

using namespace std;
using namespace d2c_system;
using namespace System;

namespace Syneditprinterinfo
{

__fastcall TSynEditPrinterInfo::TSynEditPrinterInfo() {}



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPrinterInfo.pas, released 2000-06-01.

The Initial Author of the Original Code is Morten J. Skovrup.
Portions written by Morten J. Skovrup are copyright 2000 Morten J. Skovrup.
All Rights Reserved.

Contributors to the SynEdit project are listed in the Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

$Id: SynEditPrinterInfo.pas,v 1.4.2.2 2005/10/18 01:43:23 etrusco Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
CONTENTS:
  Class retrieving info about selected printer and paper size.
-------------------------------------------------------------------------------*/


/* TSynEditPrinterInfo */

int __fastcall TSynEditPrinterInfo::PixFromBottom(double mmValue)
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = static_cast<int>(Round(mmValue * FYPixPrmm - FBottomGutter));
	return result;
}

int __fastcall TSynEditPrinterInfo::PixFromLeft(double mmValue)
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = static_cast<int>(Round(mmValue * FXPixPrmm - FLeftGutter));
	return result;
}

int __fastcall TSynEditPrinterInfo::PixFromRight(double mmValue)
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = static_cast<int>(Round(mmValue * FXPixPrmm - FRightGutter));
	return result;
}

int __fastcall TSynEditPrinterInfo::PixFromTop(double mmValue)
{
	int result = 0;
	if(!FIsUpdated)
		UpdatePrinter();
	result = static_cast<int>(Round(mmValue * FYPixPrmm - FTopGutter));
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
	FXPixPrmm = static_cast<float>(double(FXPixPrInch) / 25.4);
	FYPixPrmm = static_cast<float>(double(FYPixPrInch) / 25.4);
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
	FPhysicalWidth = GetDeviceCaps(Printer()->Handle, PHYSICALWIDTH);
	FPhysicalHeight = GetDeviceCaps(Printer()->Handle, PHYSICALHEIGHT);
	FPrintableWidth = Printer()->PageWidth; /*or GetDeviceCaps(Printer.Handle, HorzRes);*/
	FPrintableHeight = Printer()->PageHeight; /*or GetDeviceCaps(Printer.Handle, VertRes);*/
	FLeftGutter = GetDeviceCaps(Printer()->Handle, PHYSICALOFFSETX);
	FTopGutter = GetDeviceCaps(Printer()->Handle, PHYSICALOFFSETY);
	FRightGutter = FPhysicalWidth - FPrintableWidth - FLeftGutter;
	FBottomGutter = FPhysicalHeight - FPrintableHeight - FTopGutter;
	FXPixPrInch = GetDeviceCaps(Printer()->Handle, LOGPIXELSX);
	FYPixPrInch = GetDeviceCaps(Printer()->Handle, LOGPIXELSY);
	FXPixPrmm = static_cast<float>(double(FXPixPrInch) / 25.4);
	FYPixPrmm = static_cast<float>(double(FYPixPrInch) / 25.4);
}


}  // namespace Syneditprinterinfo

