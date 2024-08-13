#include <vcl.h>
#pragma hdrstop

#include "SynEditPrintMargins.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditprinttypes;
using namespace Syneditprinterinfo;
using namespace System;
using namespace System::Classes;

namespace Syneditprintmargins
{



/* TSynEditPrintMargins */
const double mmPrInch = 25.4;
const int mmPrCm = 10;

__fastcall TSynEditPrintMargins::TSynEditPrintMargins()
 : FLeft((double) DefLeft),
			FRight((double) DefRight),
			FTop((double) DefTop),
			FBottom((double) DefBottom),
			FHeader((double) DefHeader),
			FFooter((double) DefFooter),
			FLeftHFTextIndent((double) DefLeftHFTextIndent),
			FRightHFTextIndent((double) DefRightHFTextIndent),
			FHFInternalMargin(DefHFInternalMargin),
			fGutter((double) DefGutter),
			FMirrorMargins(false),
			FUnitSystem(usMM),
			PLeft(0),
			PRight(0),
			PTop(0),
			PBottom(0),
			PHeader(0),
			PFooter(0),
			PLeftHFTextIndent(0),
			PRightHFTextIndent(0),
			PHFInternalMargin(0),
			PGutter(0)
{
	// inherited;
	FUnitSystem = usMM;
}
/*Convert Value to mm*/

double __fastcall TSynEditPrintMargins::ConvertTo(double Value)
{
	double result = 0.0;
	switch(FUnitSystem)
	{
		case usCM:
		result = Value * mmPrCm;
		break;
		case usInch:
		result = Value * mmPrInch;
		break;
		case muThousandthsOfInches:
		result = mmPrInch * Value / 1000.0;
		break;
		default:
		result = Value;
		break;
	}
	return result;
}
/*Convert from mm to selected UnitSystem*/

double __fastcall TSynEditPrintMargins::ConvertFrom(double Value)
{
	double result = 0.0;
	switch(FUnitSystem)
	{
		case usCM:
		result = Value / mmPrCm;
		break;
		case usInch:
		result = Value / mmPrInch;
		break;
		case muThousandthsOfInches:
		result = 1000.0 * Value / mmPrInch;
		break;
		default:
		result = Value;
		break;
	}
	return result;
}

double __fastcall TSynEditPrintMargins::GetBottom()
{
	double result = 0.0;
	result = ConvertFrom(FBottom);
	return result;
}

double __fastcall TSynEditPrintMargins::GetFooter()
{
	double result = 0.0;
	result = ConvertFrom(FFooter);
	return result;
}

double __fastcall TSynEditPrintMargins::GetGutter()
{
	double result = 0.0;
	result = ConvertFrom(fGutter);
	return result;
}

double __fastcall TSynEditPrintMargins::GetHeader()
{
	double result = 0.0;
	result = ConvertFrom(FHeader);
	return result;
}

double __fastcall TSynEditPrintMargins::GetLeft()
{
	double result = 0.0;
	result = ConvertFrom(FLeft);
	return result;
}

double __fastcall TSynEditPrintMargins::GetRight()
{
	double result = 0.0;
	result = ConvertFrom(FRight);
	return result;
}

double __fastcall TSynEditPrintMargins::GetTop()
{
	double result = 0.0;
	result = ConvertFrom(FTop);
	return result;
}

double __fastcall TSynEditPrintMargins::GetLeftHFTextIndent()
{
	double result = 0.0;
	result = ConvertFrom(FLeftHFTextIndent);
	return result;
}

double __fastcall TSynEditPrintMargins::GetRightHFTextIndent()
{
	double result = 0.0;
	result = ConvertFrom(FRightHFTextIndent);
	return result;
}

double __fastcall TSynEditPrintMargins::GetHFInternalMargin()
{
	double result = 0.0;
	result = ConvertFrom(FHFInternalMargin);
	return result;
}

void __fastcall TSynEditPrintMargins::SetBottom(double Value)
{
	FBottom = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetFooter(double Value)
{
	FFooter = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetGutter(double Value)
{
	fGutter = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetHeader(double Value)
{
	FHeader = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetLeft(double Value)
{
	FLeft = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetRight(double Value)
{
	FRight = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetTop(double Value)
{
	FTop = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetLeftHFTextIndent(double Value)
{
	FLeftHFTextIndent = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetRightHFTextIndent(double Value)
{
	FRightHFTextIndent = ConvertTo(Value);
}

void __fastcall TSynEditPrintMargins::SetHFInternalMargin(double Value)
{
	FHFInternalMargin = ConvertTo(Value);
}

// -----------------------------------------------------------------------------
// Called by TSynEditPrint class to initialize margins

//Calculate the P... values

void __fastcall TSynEditPrintMargins::InitPage(TCanvas* ACanvas, int PageNum, TSynEditPrinterInfo* PrinterInfo, bool LineNumbers, bool LineNumbersInMargin, int MaxLineNum)
{
	if(FMirrorMargins && ((PageNum % 2) == 0))
	{
		PLeft = PrinterInfo->PixFromLeft(FRight);
		PRight = PrinterInfo->PrintableWidth - PrinterInfo->PixFromRight(FLeft + fGutter);
	}
	else
	{
		PLeft = PrinterInfo->PixFromLeft(FLeft + fGutter);
		PRight = PrinterInfo->PrintableWidth - PrinterInfo->PixFromRight(FRight);
	}
	if(LineNumbers && (!LineNumbersInMargin))
		PLeft = PLeft + ACanvas->TextWidth(IntToStr(MaxLineNum) + L": ");
	PTop = PrinterInfo->PixFromTop(FTop);
	PBottom = PrinterInfo->PrintableHeight - PrinterInfo->PixFromBottom(FBottom);
	PHeader = PrinterInfo->PixFromTop(FHeader);
	PFooter = PrinterInfo->PrintableHeight - PrinterInfo->PixFromBottom(FFooter);
	PHFInternalMargin = (int) Round(PrinterInfo->YPixPrmm * FHFInternalMargin);
	PGutter = (int) Round(PrinterInfo->XPixPrmm * fGutter);
	PRightHFTextIndent = (int) (PRight - Round(PrinterInfo->XPixPrmm * FRightHFTextIndent));
	PLeftHFTextIndent = (int) (PLeft + Round(PrinterInfo->XPixPrmm * FLeftHFTextIndent));
}

// -----------------------------------------------------------------------------
// Assign values from another TSynEditPrintMargins object

void __fastcall TSynEditPrintMargins::Assign(TPersistent* Source)
{
	TSynEditPrintMargins* Src = nullptr;
	if((Source != nullptr) && (ObjectIs(Source, TSynEditPrintMargins*)))
	{
		Src = ((TSynEditPrintMargins*) Source);
		FLeft = Src->FLeft;
		FRight = Src->FRight;
		FTop = Src->FTop;
		FBottom = Src->FBottom;
		FHeader = Src->FHeader;
		FFooter = Src->FFooter;
		FLeftHFTextIndent = Src->FLeftHFTextIndent;
		FRightHFTextIndent = Src->FRightHFTextIndent;
		FHFInternalMargin = Src->FHFInternalMargin;
		fGutter = Src->fGutter;
		FMirrorMargins = Src->FMirrorMargins;
		FUnitSystem = Src->FUnitSystem;
	}
	else
	inherited::Assign(Source);
}

void __fastcall TSynEditPrintMargins::LoadFromStream(TStream* AStream)
{

  // we read all our values in MM
	/*# with AStream do */
	{
		auto with0 = AStream;
		with0->Read((void**)&FUnitSystem, (NativeInt) sizeof(FUnitSystem));
		with0->Read((void**)&FLeft, (NativeInt) sizeof(FLeft));
		with0->Read((void**)&FRight, (NativeInt) sizeof(FRight));
		with0->Read((void**)&FTop, (NativeInt) sizeof(FTop));
		with0->Read((void**)&FBottom, (NativeInt) sizeof(FBottom));
		with0->Read((void**)&FHeader, (NativeInt) sizeof(FHeader));
		with0->Read((void**)&FFooter, (NativeInt) sizeof(FFooter));
		with0->Read((void**)&FLeftHFTextIndent, (NativeInt) sizeof(FLeftHFTextIndent));
		with0->Read((void**)&FRightHFTextIndent, (NativeInt) sizeof(FRightHFTextIndent));
		with0->Read((void**)&FHFInternalMargin, (NativeInt) sizeof(FHFInternalMargin));
		with0->Read((void**)&fGutter, (NativeInt) sizeof(fGutter));
		with0->Read((void**)&FMirrorMargins, (NativeInt) sizeof(FMirrorMargins));
	}
}

void __fastcall TSynEditPrintMargins::SaveToStream(TStream* AStream)
{

  // we always write our values in MM
	/*# with AStream do */
	{
		auto with0 = AStream;
		with0->Write(&FUnitSystem, (NativeInt) sizeof(FUnitSystem));
		with0->Write(&FLeft, (NativeInt) sizeof(FLeft));
		with0->Write(&FRight, (NativeInt) sizeof(FRight));
		with0->Write(&FTop, (NativeInt) sizeof(FTop));
		with0->Write(&FBottom, (NativeInt) sizeof(FBottom));
		with0->Write(&FHeader, (NativeInt) sizeof(FHeader));
		with0->Write(&FFooter, (NativeInt) sizeof(FFooter));
		with0->Write(&FLeftHFTextIndent, (NativeInt) sizeof(FLeftHFTextIndent));
		with0->Write(&FRightHFTextIndent, (NativeInt) sizeof(FRightHFTextIndent));
		with0->Write(&FHFInternalMargin, (NativeInt) sizeof(FHFInternalMargin));
		with0->Write(&fGutter, (NativeInt) sizeof(fGutter));
		with0->Write(&FMirrorMargins, (NativeInt) sizeof(FMirrorMargins));
	}
}


}  // namespace SynEditPrintMargins

