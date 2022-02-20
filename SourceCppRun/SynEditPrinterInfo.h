#ifndef SynEditPrinterInfoH
#define SynEditPrinterInfoH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Printers.hpp>

namespace Syneditprinterinfo
{

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
  //Printer info class - getting dimensions of paper

class TSynEditPrinterInfo : public System::TObject
{

public:
	typedef TObject inherited;	
private:
	int FPhysicalWidth;
	int FPhysicalHeight;
	int FPrintableWidth;
	int FPrintableHeight;
	int FLeftGutter;
	int FRightGutter;
	int FTopGutter;
	int FBottomGutter;
	int FXPixPrInch;
	int FYPixPrInch;
	float FXPixPrmm;
	float FYPixPrmm;
	bool FIsUpdated;
	void __fastcall FillDefault();
	int __fastcall GetBottomGutter();
	int __fastcall GetLeftGutter();
	int __fastcall GetPhysicalHeight();
	int __fastcall GetPhysicalWidth();
	int __fastcall GetPrintableHeight();
	int __fastcall GetPrintableWidth();
	int __fastcall GetRightGutter();
	int __fastcall GetTopGutter();
	int __fastcall GetXPixPrInch();
	int __fastcall GetYPixPrInch();
	float __fastcall GetXPixPrmm();
	float __fastcall GetYPixPrmm();
public:
	void __fastcall UpdatePrinter();
	int __fastcall PixFromLeft(double mmValue);
	int __fastcall PixFromRight(double mmValue);
	int __fastcall PixFromTop(double mmValue);
	int __fastcall PixFromBottom(double mmValue);
	__property int PhysicalWidth = { read = GetPhysicalWidth };
	__property int PhysicalHeight = { read = GetPhysicalHeight };
	__property int PrintableWidth = { read = GetPrintableWidth };
	__property int PrintableHeight = { read = GetPrintableHeight };
	__property int LeftGutter = { read = GetLeftGutter };
	__property int RightGutter = { read = GetRightGutter };
	__property int TopGutter = { read = GetTopGutter };
	__property int BottomGutter = { read = GetBottomGutter };
	__property int XPixPrInch = { read = GetXPixPrInch };
	__property int YPixPrInch = { read = GetYPixPrInch };
	__property float XPixPrmm = { read = GetXPixPrmm };
	__property float YPixPrmm = { read = GetYPixPrmm };
	__fastcall TSynEditPrinterInfo();
};


}  // namespace SynEditPrinterInfo

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditprinterinfo;
#endif

#endif // SynEditPrinterInfoH

