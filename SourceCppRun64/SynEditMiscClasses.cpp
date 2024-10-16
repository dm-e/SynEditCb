#include <vcl.h>
#pragma hdrstop

#include "SynEditMiscClasses.h"
#include <System.Rtti.hpp>
#include <Winapi.Wincodec.hpp>
#include <Vcl.GraphUtil.hpp>
#include "SynEditMiscProcs.h"
#include "SynEditCodeFolding.h"
#include "SynTextDrawer.h"
#include "SynEdit.h"
#include "d2c_convert.h"
#include "SynEditDelphiInstances.hpp"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Syneditcodefolding;
using namespace Syneditkeyconst;
using namespace Syneditmiscprocs;
using namespace Synedittypes;
using namespace Syntextdrawer;
using namespace System;
using namespace System::Classes;
using namespace System::Rtti;
using namespace System::Sysutils;
using namespace System::Uitypes;
using namespace System::Win::Registry;
using namespace Vcl::Controls;
using namespace Vcl::Forms;
using namespace Vcl::Graphutil;
using namespace Vcl::Graphics;
using namespace Winapi::Wincodec;

namespace Syneditmiscclasses
{
#define Syneditmiscclasses__0 TFontStyles()
#define Syneditmiscclasses__1 TShiftState()
#define Syneditmiscclasses__2 (TShiftState() << ssShift << ssAlt << ssCtrl)
#define Syneditmiscclasses__3 (TShiftState() << ssShift)
#define Syneditmiscclasses__4 (TShiftState() << ssCtrl)
#define Syneditmiscclasses__5 (TShiftState() << ssAlt)
#define Syneditmiscclasses__6 (TShiftState() << ssShift << ssCtrl)
#define Syneditmiscclasses__7 (TShiftState() << ssShift << ssAlt)
#define Syneditmiscclasses__8 (TShiftState() << ssCtrl << ssAlt)
#define Syneditmiscclasses__9 (TShiftState() << ssShift << ssCtrl << ssAlt)
#define Syneditmiscclasses__10 (TControlStyle() << csNeedsBorderPaint)
#define Syneditmiscclasses__11 (THKInvalidKeys() << hcNone << hcShift)
#define Syneditmiscclasses__12 (THKModifiers() << hkAlt)
#define Syneditmiscclasses__13 (System::Set<TSynGutterBandKind, TSynGutterBandKind::gbkCustom, TSynGutterBandKind::gbkTrackChanges>() << gbkLineNumbers << gbkFold)
#define Syneditmiscclasses__14 (System::Set<TSynGutterBandKind, TSynGutterBandKind::gbkCustom, TSynGutterBandKind::gbkTrackChanges>() << gbkLineNumbers << gbkFold)
#define Syneditmiscclasses__15 (TTextFormat() << tfSingleLine << tfVerticalCenter << tfRight)
#define Syneditmiscclasses__16 (System::Set<int, 0, 255>() <<  \
										0 << 1 << 2 << 3 << 4 << 5 <<  \
										6 << 7 << 8 << 9)
#define Syneditmiscclasses__17 (System::Set<TSynGutterBandKind, TSynGutterBandKind::gbkCustom, TSynGutterBandKind::gbkTrackChanges>() << gbkLineNumbers << gbkFold)

__fastcall TSynBandsCollection::TSynBandsCollection(TPersistent* AOwner, TCollectionItemClass ItemClass) : inherited(AOwner, ItemClass) {}
//# problematic: __fastcall TSynBandsCollection::TSynBandsCollection(TCollectionItemClass ItemClass) : inherited(ItemClass) {}
__fastcall TSynBookMarkOpt::TSynBookMarkOpt() {}
__fastcall TSynGlyph::TSynGlyph() {}
__fastcall ESynMethodChain::ESynMethodChain(const String Msg) : inherited(Msg) {}
__fastcall ESynMethodChain::ESynMethodChain(const String Msg, const TVarRec* Args, int Args_maxidx) : inherited(Msg, Args, Args_maxidx) {}
__fastcall ESynMethodChain::ESynMethodChain(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Msg, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynMethodChain::ESynMethodChain(const String Msg, int AHelpContext) : inherited(Msg, AHelpContext) {}
__fastcall ESynMethodChain::ESynMethodChain(System::NativeUInt Ident) : inherited(Ident) {}
__fastcall ESynMethodChain::ESynMethodChain(System::PResStringRec ResStringRec) : inherited(ResStringRec) {}
__fastcall ESynMethodChain::ESynMethodChain(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx) : inherited(Ident, Args, Args_maxidx) {}
__fastcall ESynMethodChain::ESynMethodChain(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx) : inherited(ResStringRec, Args, Args_maxidx) {}
__fastcall ESynMethodChain::ESynMethodChain(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(ResStringRec, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynMethodChain::ESynMethodChain(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Ident, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynMethodChain::ESynMethodChain(System::NativeUInt Ident, int AHelpContext) : inherited(Ident, AHelpContext) {}
__fastcall ESynMethodChain::ESynMethodChain(System::PResStringRec ResStringRec, int AHelpContext) : inherited(ResStringRec, AHelpContext) {}
__fastcall TSynNotifyEventChain::TSynNotifyEventChain() {}
__fastcall TSynInternalImage::TSynInternalImage() {}
__fastcall TSynHotKey::TSynHotKey(HWND ParentWindow) : inherited(ParentWindow) {}
__fastcall TSynEditSearchCustom::TSynEditSearchCustom(TComponent* AOwner) : inherited(AOwner) {}
__fastcall TBetterRegistry::TBetterRegistry() {}
__fastcall TBetterRegistry::TBetterRegistry(unsigned long AAccess) : inherited(AAccess) {}


/*static */const int TSynGutterBand::MarginX = 2; 
// ++ DPI-Aware

void __fastcall ResizeBitmap(TBitmap* Bitmap, int NewWidth, int NewHeight)
{
	IWICImagingFactory* Factory = nullptr;
	IWICBitmapScaler* Scaler = nullptr;
	TWICImage* Source = nullptr;
	Bitmap->AlphaFormat = afDefined;
	Source = new TWICImage();
	try
	{
		Source->Assign(Bitmap);
		Factory = TWICImage::ImagingFactory;
		Factory->CreateBitmapScaler(&Scaler);
		try
		{
			Scaler->Initialize(Source->Handle, (UINT) NewWidth, (UINT) NewHeight, WICBitmapInterpolationModeHighQualityCubic);
			Source->Handle = ((IWICBitmap*) Scaler);
		}
		__finally
		{
			Scaler = nullptr;
			Factory = nullptr;
		}
		Bitmap->Assign(Source);
	}
	__finally
	{
		delete Source;
	}
}
// -- DPI-Aware
 

/* TSynSelectedColor */

__fastcall TSynSelectedColor::TSynSelectedColor()
 : fBG((TColor) clHighlight),
			fFG((TColor) clHighlightText)
{
	//# inherited::Create();
}

void __fastcall TSynSelectedColor::Assign(TPersistent* Source)
{
	TSynSelectedColor* Src = nullptr;
	if((Source != nullptr) && (ObjectIs(Source, TSynSelectedColor*)))
	{
		Src = ((TSynSelectedColor*) Source);
		fBG = Src->fBG;
		fFG = Src->fFG;
		if(ASSIGNED(fOnChange))
			fOnChange(this);
	}
	else
	inherited::Assign(Source);
}

void __fastcall TSynSelectedColor::SetBG(TColor Value)
{
	if(fBG != Value)
	{
		fBG = Value;
		if(ASSIGNED(fOnChange))
			fOnChange(this);
	}
}

void __fastcall TSynSelectedColor::SetFG(TColor Value)
{
	if(fFG != Value)
	{
		fFG = Value;
		if(ASSIGNED(fOnChange))
			fOnChange(this);
	}
}

/* TSynGutter */

void __fastcall TSynGutter::CalcCharWidth()
{
	TBitmap* Bitmap = nullptr;
	TCustomSynEdit* Editor = nullptr;
	Editor = ((TCustomSynEdit*) FOwner);
	if(UseFontStyle || !ASSIGNED(Editor))
	{
		if(ASSIGNED(Editor) && Editor->HandleAllocated())
		{
			Editor->Canvas->Font = Font;
			FCharWidth = TheFontStock::CalcFontAdvance(Editor->Canvas->Handle, nullptr);
			Editor->Canvas->Font = Font;
		}
		else
		{
			Bitmap = new TBitmap();
			try
			{
				Bitmap->Canvas->Font = Font;
				FCharWidth = TheFontStock::CalcFontAdvance(Bitmap->Canvas->Handle, nullptr);
			}
			__finally
			{
				delete Bitmap;
			}
		}
	}
	else
	FCharWidth = Editor->CharWidth;
}

void __fastcall TSynGutter::Changed()
{
	if((FUpdateCount == 0) && ASSIGNED(fOnChange))
		fOnChange(this);
}

void __fastcall TSynGutter::ChangeScale(int M, int D)
{
	FFont->Height = (int) Round(FFont->Height * M / D);
	if(ASSIGNED(FInternalImage))
		FInternalImage->ChangeScale(M, D);
	FCurrentPPI = M; // Vcl does the same
	Changed();
}

__fastcall TSynGutter::TSynGutter()
 : FOwner(nullptr),
			FUpdateCount(0),
			FCurrentPPI(0),
			FFont(nullptr),
			FCharWidth(0),
			FColor((TColor) 0),
			FBorderColor((TColor) 0),
			FDigitCount(0),
			FLeadingZeros(false),
			FZeroStart(false),
			FCursor((TCursor) 0),
			FVisible(false),
			FShowLineNumbers(false),
			FUseFontStyle(false),
			FAutoSize(false),
			FAutoSizeDigitCount(0),
			FBorderStyle(gbsNone),
			FLineNumberStart(0),
			FGradient(false),
			FGradientStartColor((TColor) 0),
			FGradientEndColor((TColor) 0),
			FGradientSteps(0),
			FInternalImage(nullptr),
			FBands(nullptr),
			AssignableBands(false)
{

	auto AddBand = [&](TSynGutterBandKind AKind, int AWidth, bool IsVisible) -> void 
	{
		/*# with FBands.Add as TSynGutterBand do */
		{
			auto with0 = (TSynGutterBand*) FBands->Add();
			with0->FKind = AKind;
			with0->FWidth = AWidth;
			with0->FVisible = IsVisible;
		}
	};
	//# inherited::Create();
	FCurrentPPI = 96;
	FFont = new TFont();
	FFont->Name = DefaultFontName();
	FFont->Size = 8;
	FFont->Style = Syneditmiscclasses__0;
	FUseFontStyle = true;
	CalcCharWidth();
	FFont->OnChange = OnFontChange;
	FColor = (TColor) clBtnFace;
	FVisible = true;
	FDigitCount = 4;
	FAutoSizeDigitCount = FDigitCount;
	FAutoSize = true;
	FBorderColor = (TColor) clWindow;
	FBorderStyle = gbsMiddle;
	FLineNumberStart = 1;
	FZeroStart = false;
	FGradient = false;
	FGradientStartColor = (TColor) clWindow;
	FGradientEndColor = (TColor) clBtnFace;
	FGradientSteps = 48;
	AutoSizeDigitCount();
	FBands = new TSynBandsCollection(this, __classid(TSynGutterBand));
	Bands->BeginUpdate();
	try
	{
		AddBand(gbkMarks, 13, true);
		AddBand(gbkLineNumbers, 0, false);
		AddBand(gbkFold, 0, false);
		AddBand(gbkMargin, 3, true);
	}
	__finally
	{
		Bands->EndUpdate();
	}
	AssignableBands = true;
}

__fastcall TSynGutter::TSynGutter(TPersistent* Owner)
 : TSynGutter()  //# delegation
{
	FOwner = Owner;
}

__fastcall TSynGutter::~TSynGutter()
{
	FOwner = nullptr;
	delete FFont;
	delete FBands;
	delete FInternalImage;
	//# inherited::Destroy();
}

void __fastcall TSynGutter::EndUpdate()
{
	--FUpdateCount;
	Changed();
}

void __fastcall TSynGutter::Assign(TPersistent* Source)
{
	TSynGutter* Src = nullptr;
	if(ASSIGNED(Source) && (ObjectIs(Source, TSynGutter*)))
	{
		Src = ((TSynGutter*) Source);
		FFont->Assign(Src->Font);
		FUseFontStyle = Src->FUseFontStyle;
		FColor = Src->FColor;
		FVisible = Src->FVisible;
		FLeadingZeros = Src->FLeadingZeros;
		FZeroStart = Src->FZeroStart;
		FDigitCount = Src->FDigitCount;
		FAutoSize = Src->FAutoSize;
		FAutoSizeDigitCount = Src->FAutoSizeDigitCount;
		FLineNumberStart = Src->FLineNumberStart;
		FBorderColor = Src->FBorderColor;
		FBorderStyle = Src->FBorderStyle;
		FGradient = Src->FGradient;
		FGradientStartColor = Src->FGradientStartColor;
		FGradientEndColor = Src->FGradientEndColor;
		FGradientSteps = Src->FGradientSteps;
		if(AssignableBands && Src->AssignableBands)
			FBands->Assign(Src->FBands);
		AutoSizeDigitCount();
		Changed();
	}
	else
	inherited::Assign(Source);
}

void __fastcall TSynGutter::AutoSizeDigitCount()
{
	int nDigits = 0;
	TCustomSynEdit* SynEdit = nullptr;
	int LinesCount = 0;
	SynEdit = ((TCustomSynEdit*) FOwner);
	if(ASSIGNED(SynEdit) && FAutoSize)
	{
		LinesCount = SynEdit->Lines->Count;
		if(FZeroStart)
			--LinesCount;
		else
		{
			if(FLineNumberStart > 1)
				LinesCount += FLineNumberStart - 1;
		}
		nDigits = Max(IntToStr(LinesCount).Length(), FDigitCount);
		if(FAutoSizeDigitCount != nDigits)
		{
			FAutoSizeDigitCount = nDigits;
			Changed();
		}
	}
	else
	FAutoSizeDigitCount = FDigitCount;
}

TSynGutterBand* __fastcall TSynGutter::BandAtX(int X)
{
	TSynGutterBand* result = nullptr;
	int I = 0;
	int L = 0;
	TSynGutterBand* Band = nullptr;
	int stop = 0;
	result = nullptr;
	L = 0;
	for(stop = Bands->Count - 1, I = 0; I <= stop; I++)
	{
		Band = Bands->Bands[I];
		if(!Band->Visible)
			continue;
		L += Band->RealWidth();
		if(X < L)
			return Band;
	}
	return result;
}

void __fastcall TSynGutter::BeginUpdate()
{
	++FUpdateCount;
}

String __fastcall TSynGutter::FormatLineNumber(int Line)
{
	String result;
	int I = 0;
	if(FZeroStart)
		--Line;
	else
	{
		if(FLineNumberStart > 1)
			Line += FLineNumberStart - 1;
	}
	result = Format(L"%*d", ARRAYOFCONST((FAutoSizeDigitCount, Line)));
	if(FLeadingZeros)
	{
		int stop = 0;
		for(stop = FAutoSizeDigitCount - 1, I = 1; I <= stop; I++)
		{
			if(result[I] != L' ')
				break;
			result[I] = L'0';
		}
	}
	return result;
}

int __fastcall TSynGutter::RealGutterWidth()
{
	int result = 0;
	int I = 0;
	result = 0;
	if(FVisible && ASSIGNED(FOwner))
	{
		int stop = 0;
		for(stop = Bands->Count - 1, I = 0; I <= stop; I++)
		{
			result += Bands->Bands[I]->RealWidth();
		}
	}
	return result;
}

void __fastcall TSynGutter::SetAutoSize(bool Value)
{
	if(FAutoSize != Value)
	{
		FAutoSize = Value;
		AutoSizeDigitCount();
		Changed();
	}
}

void __fastcall TSynGutter::SetColor(const TColor Value)
{
	if(FColor != Value)
	{
		FColor = Value;
		Changed();
	}
}

void __fastcall TSynGutter::SetFont(TFont* Value)
{
	FFont->Assign(Value);
}

void __fastcall TSynGutter::OnFontChange(TObject* Sender)
{
	CalcCharWidth();
	Changed();
}

void __fastcall TSynGutter::SetDigitCount(int Value)
{
	Value = MinMax(Value, 2, 12);
	if(FDigitCount != Value)
	{
		FDigitCount = Value;
		AutoSizeDigitCount();
		Changed();
	}
}

void __fastcall TSynGutter::SetLeadingZeros(bool Value)
{
	if(FLeadingZeros != Value)
	{
		FLeadingZeros = Value;
		AutoSizeDigitCount();
		Changed();
	}
}

void __fastcall TSynGutter::SetShowLineNumbers(bool Value)
{
	if(FShowLineNumbers != Value)
	{
		FShowLineNumbers = Value;
		Changed();
	}
}

void __fastcall TSynGutter::SetUseFontStyle(bool Value)
{
	if(FUseFontStyle != Value)
	{
		FUseFontStyle = Value;
		Changed();
	}
}

void __fastcall TSynGutter::SetVisible(bool Value)
{
	if(FVisible != Value)
	{
		FVisible = Value;
		Changed();
	}
}

void __fastcall TSynGutter::SetZeroStart(bool Value)
{
	if(FZeroStart != Value)
	{
		FZeroStart = Value;
		Changed();
	}
}

void __fastcall TSynGutter::SetBorderStyle(TSynGutterBorderStyle Value)
{
	FBorderStyle = Value;
	Changed();
}

void __fastcall TSynGutter::SetLineNumberStart(int Value)
{
	if(Value != FLineNumberStart)
	{
		FLineNumberStart = Value;
		if(FLineNumberStart < 0)
			FLineNumberStart = 0;
		if(FLineNumberStart == 0)
			FZeroStart = true;
		else
			FZeroStart = false;
		AutoSizeDigitCount();
		Changed();
	}
}

void __fastcall TSynGutter::SetBands(TSynBandsCollection* const Value)
{
	FBands->Assign((TPersistent*) Value);
}

void __fastcall TSynGutter::SetBorderColor(const TColor Value)
{
	if(FBorderColor != Value)
	{
		FBorderColor = Value;
		Changed();
	}
}

void __fastcall TSynGutter::SetGradient(bool Value)
{
	if(Value != FGradient)
	{
		FGradient = Value;
		Changed();
	}
}

void __fastcall TSynGutter::SetGradientEndColor(const TColor Value)
{
	if(Value != FGradientEndColor)
	{
		FGradientEndColor = Value;
		Changed();
	}
}

void __fastcall TSynGutter::SetGradientStartColor(const TColor Value)
{
	if(Value != FGradientStartColor)
	{
		FGradientStartColor = Value;
		Changed();
	}
}

void __fastcall TSynGutter::SetGradientSteps(int Value)
{
	if(Value != FGradientSteps)
	{
		FGradientSteps = Value;
		if(FGradientSteps < 2)
			FGradientSteps = 2;
		Changed();
	}
}

TSynGutterBand* __fastcall TSynGutter::GetBandByKind(TSynGutterBandKind Kind)
{
	TSynGutterBand* result = nullptr;
	int I = 0;
	int stop = 0;
	result = nullptr;
	for(stop = Bands->Count - 1, I = 0; I <= stop; I++)
	{
		if(Bands->Bands[I]->Kind == Kind)
			return Bands->Bands[I];
	}
	return result;
}

TSynInternalImage* __fastcall TSynGutter::GetInternalImage()
{
	TSynInternalImage* result = nullptr;
	if(!ASSIGNED(FInternalImage))
	{
		FInternalImage = new TSynInternalImage((THandle) HInstance, L"SynEditInternalImages", 10);
    // ++ DPI-Aware
		if(ASSIGNED(FOwner))
			FInternalImage->ChangeScale(FCurrentPPI, 96);
    // -- DPI-Aware
	}
	result = FInternalImage;
	return result;
}

TPersistent* __fastcall TSynGutter::GetOwner()
{
	TPersistent* result = nullptr;
	result = FOwner;
	return result;
}

/* TSynBookMarkOpt */

// ++ DPI-Aware

void __fastcall TSynBookMarkOpt::ChangeScale(int M, int D)
{
	FLeftMargin = MulDiv(FLeftMargin, M, D);
	FXoffset = MulDiv(FXoffset, M, D);
}
// -- DPI-Aware

__fastcall TSynBookMarkOpt::TSynBookMarkOpt(TComponent* AOwner)
 : FBookmarkImages(nullptr),
			FDrawBookmarksFirst(false),
			FEnableKeys(false),
			FGlyphsVisible(false),
			FLeftMargin(0),
			FOwner(nullptr),
			FXoffset(0)
{
	//# inherited::Create();
	FDrawBookmarksFirst = true;
	FEnableKeys = true;
	FGlyphsVisible = true;
	FLeftMargin = 2;
	FOwner = AOwner;
	FXoffset = 12;
}

void __fastcall TSynBookMarkOpt::Assign(TPersistent* Source)
{
	TSynBookMarkOpt* Src = nullptr;
	if((Source != nullptr) && (ObjectIs(Source, TSynBookMarkOpt*)))
	{
		Src = ((TSynBookMarkOpt*) Source);
		FBookmarkImages = Src->FBookmarkImages;
		FDrawBookmarksFirst = Src->FDrawBookmarksFirst;
		FEnableKeys = Src->FEnableKeys;
		FGlyphsVisible = Src->FGlyphsVisible;
		FLeftMargin = Src->FLeftMargin;
		FXoffset = Src->FXoffset;
		if(ASSIGNED(fOnChange))
			fOnChange(this);
	}
	else
	inherited::Assign(Source);
}

void __fastcall TSynBookMarkOpt::SetBookmarkImages(TCustomImageList* const Value)
{
	if(FBookmarkImages != Value)
	{
		FBookmarkImages = const_cast<TCustomImageList*>(Value);
		if(ASSIGNED(FBookmarkImages))
			FBookmarkImages->FreeNotification(FOwner);
		if(ASSIGNED(fOnChange))
			fOnChange(this);
	}
}

void __fastcall TSynBookMarkOpt::SetDrawBookmarksFirst(bool Value)
{
	if(Value != FDrawBookmarksFirst)
	{
		FDrawBookmarksFirst = Value;
		if(ASSIGNED(fOnChange))
			fOnChange(this);
	}
}

void __fastcall TSynBookMarkOpt::SetGlyphsVisible(bool Value)
{
	if(FGlyphsVisible != Value)
	{
		FGlyphsVisible = Value;
		if(ASSIGNED(fOnChange))
			fOnChange(this);
	}
}

void __fastcall TSynBookMarkOpt::SetLeftMargin(int Value)
{
	if(FLeftMargin != Value)
	{
		FLeftMargin = Value;
		if(ASSIGNED(fOnChange))
			fOnChange(this);
	}
}

void __fastcall TSynBookMarkOpt::SetXOffset(int Value)
{
	if(FXoffset != Value)
	{
		FXoffset = Value;
		if(ASSIGNED(fOnChange))
			fOnChange(this);
	}
}

/* TSynGlyph */

// ++ DPI-Aware

void __fastcall TSynGlyph::ChangeScale(int M, int D)
{
	ResizeBitmap(FInternalGlyph, MulDiv(FInternalGlyph->Width, M, D), MulDiv(FInternalGlyph->Height, M, D));
	if(!FGlyph->Empty)
		ResizeBitmap(FGlyph, MulDiv(FGlyph->Width, M, D), MulDiv(FGlyph->Height, M, D));
}
// -- DPI-Aware

__fastcall TSynGlyph::TSynGlyph(THandle aModule, const String aName)
 : FVisible(true),
			FInternalGlyph(nullptr),
			FGlyph(nullptr)
{
	//# inherited::Create();
	if(aName != L"")
	{
		FInternalGlyph = new TBitmap();
		FInternalGlyph->LoadFromResourceName(aModule, aName);
	}
	FGlyph = new TBitmap();
	FGlyph->OnChange = GlyphChange;
}

__fastcall TSynGlyph::~TSynGlyph()
{
	if(ASSIGNED(FInternalGlyph))
		FreeAndNil(&FInternalGlyph);
	delete FGlyph;
	//# inherited::Destroy();
}

void __fastcall TSynGlyph::Assign(TPersistent* aSource)
{
	TSynGlyph* vSrc = nullptr;
	if(ASSIGNED(aSource) && (ObjectIs(aSource, TSynGlyph*)))
	{
		vSrc = ((TSynGlyph*) aSource);
		FInternalGlyph = vSrc->FInternalGlyph;
		FVisible = vSrc->FVisible;
		FGlyph = vSrc->FGlyph;
		if(ASSIGNED(fOnChange))
			fOnChange(this);
	}
	else
	inherited::Assign(aSource);
}

void __fastcall TSynGlyph::Draw(TCanvas* aCanvas, int aX, int aY, int aLineHeight)
{
	TRect rcSrc = {};
	TRect rcDest = {};
	TBitmap* vGlyph = nullptr;
	if(!FGlyph->Empty)
		vGlyph = FGlyph;
	else
	{
		if(ASSIGNED(FInternalGlyph))
			vGlyph = FInternalGlyph;
		else
			return;
	}
	if(aLineHeight >= vGlyph->Height)
	{
		rcSrc = Rect(0, 0, vGlyph->Width, vGlyph->Height);
		aY += (int)((aLineHeight - vGlyph->Height) / /*div*/ 2);
		rcDest = Rect(aX, aY, aX + vGlyph->Width, aY + vGlyph->Height);
	}
	else

    // TODO: Skip drawing?
	{
		rcDest = Rect(aX, aY, aX + vGlyph->Width, aY + aLineHeight);
		aY = (int)((vGlyph->Height - aLineHeight) / /*div*/ 2);
		rcSrc = Rect(0, aY, vGlyph->Width, aY + aLineHeight);
	}
	DrawTransparentBitmap(vGlyph, rcSrc, aCanvas, rcDest, 255);
}

void __fastcall TSynGlyph::SetGlyph(TBitmap* Value)
{
	FGlyph->Assign(Value);
}

void __fastcall TSynGlyph::GlyphChange(TObject* Sender)
{
	if(ASSIGNED(fOnChange))
		fOnChange(this);
}

void __fastcall TSynGlyph::SetVisible(bool Value)
{
	if(FVisible != Value)
	{
		FVisible = Value;
		if(ASSIGNED(fOnChange))
			fOnChange(this);
	}
}

int __fastcall TSynGlyph::GetWidth()
{
	int result = 0;
	if(!FGlyph->Empty)
		result = FGlyph->Width;
	else
	{
		if(ASSIGNED(FInternalGlyph))
			result = FInternalGlyph->Width;
		else
			result = 0;
	}
	return result;
}

int __fastcall TSynGlyph::GetHeight()
{
	int result = 0;
	if(!FGlyph->Empty)
		result = FGlyph->Height;
	else
	{
		if(ASSIGNED(FInternalGlyph))
			result = FInternalGlyph->Height;
		else
			result = 0;
	}
	return result;
}

/* TSynMethodChain */

void __fastcall TSynMethodChain::Add(const TMethod& cAEvent)
{
	TMethod AEvent = cAEvent;
	if(!ASSIGNED(AEvent.Code))
		throw new ESynMethodChain(L"%s.Entry : the parameter `AEvent' must be specified.", ARRAYOFCONST((ClassName())));
	/*# with FNotifyProcs, AEvent do */
	{
		auto with0 = FNotifyProcs;
		auto& with1 = AEvent;
		with0->Add(with1.Code);
		with0->Add(with1.Data);
	}
}

__fastcall TSynMethodChain::TSynMethodChain()
 : FNotifyProcs(new TList())
{
	// inherited;
}

__fastcall TSynMethodChain::~TSynMethodChain()
{
	delete FNotifyProcs;
	// inherited;
}

bool __fastcall TSynMethodChain::DoHandleException(Exception* E)
{
	bool result = false;
	if(!ASSIGNED(FExceptionHandler))
		throw E;
	else
		try
		{
			result = true;
			FExceptionHandler(this, E, result);
		}
		catch(...)
		{
			throw new ESynMethodChain(L"%s.DoHandleException : MUST NOT occur any kind of exception in " L"ExceptionHandler", ARRAYOFCONST((ClassName())));
		}
	return result;
}

void __fastcall TSynMethodChain::Fire()
{
	TMethod AMethod = {};
	int I = 0;
	I = 0;
	/*# with FNotifyProcs, AMethod do */
	{
		auto with0 = FNotifyProcs;
		auto& with1 = AMethod;
		while(I < with0->Count)
			try
			{
				do
				{
					with1.Code = with0->Items[I];
					++I;
					with1.Data = with0->Items[I];
					++I;
					DoFire(AMethod);
				}
				while(!(I >= with0->Count));
			}
			catch(Exception* E)
			{
				if(!DoHandleException(E))
					I = MaxInt;
			}
	}
}

void __fastcall TSynMethodChain::Remove(const TMethod& cAEvent)
{
	TMethod AEvent = cAEvent;
	int I = 0;
	if(!ASSIGNED(AEvent.Code))
		throw new ESynMethodChain(L"%s.Remove: the parameter `AEvent' must be specified.", ARRAYOFCONST((ClassName())));
	/*# with FNotifyProcs, AEvent do */
	{
		auto with0 = FNotifyProcs;
		auto& with1 = AEvent;
		I = with0->Count - 1;
		while(I > 0)
			if(with0->Items[I] != with1.Data)
				I -= 2;
			else
			{
				--I;
				if(with0->Items[I] == with1.Code)
				{
					with0->Delete(I);
					with0->Delete(I);
				}
				--I;
			}
	}
}

/* TSynNotifyEventChain */

void __fastcall TSynNotifyEventChain::Add(TNotifyEvent AEvent)
{
	inherited::Add(*((TMethod*) &AEvent));
}

__fastcall TSynNotifyEventChain::TSynNotifyEventChain(TObject* ASender)
 : FSender(ASender)
{
	//# inherited::Create();
}

void __fastcall TSynNotifyEventChain::DoFire(const TMethod& AEvent)
{
	(*(TNotifyEvent*)&AEvent)(FSender);
}

void __fastcall TSynNotifyEventChain::Remove(TNotifyEvent AEvent)
{
	inherited::Remove(*((TMethod*) &AEvent));
}

/* TSynInternalImage */

class TInternalResource : public TObject
{
	#include "SynEditMiscClasses_friends.inc"
public:
	typedef TObject inherited;
	int UsageCount;
	String Name;
	TBitmap* Bitmap;
	__fastcall TInternalResource() {}
};

void __fastcall TSynInternalImage::ChangeScale(int M, int D)
{
	if(M == D)
		return;
	FWidth = MulDiv(FWidth, M, D);
	ResizeBitmap(FImages, FWidth * FCount, MulDiv(FImages->Height, M, D));
	FHeight = FImages->Height;
}

__fastcall TSynInternalImage::TSynInternalImage(THandle aModule, const String Name, int Count)
 : FImages(new TBitmap()),
			FWidth((int)((FImages->Width + (Count >> 1)) / /*div*/ Count)),
			FHeight(FImages->Height),
			FCount(Count)
{
	//# inherited::Create();
	FImages->LoadFromResourceName(aModule, Name);
}

__fastcall TSynInternalImage::~TSynInternalImage()
{
	delete FImages;
	//# inherited::Destroy();
}

void __fastcall TSynInternalImage::Draw(TCanvas* aCanvas, int Number, int X, int Y, int LineHeight)
{
	TRect rcSrc = {};
	TRect rcDest = {};
	if((Number >= 0) && (Number < FCount))
	{
		if(LineHeight >= FHeight)
		{
			rcSrc = Rect(Number * FWidth, 0, (Number + 1) * FWidth, FHeight);
			Y += (int)((LineHeight - FHeight) / /*div*/ 2);
			rcDest = Rect(X, Y, X + FWidth, Y + FHeight);
		}
		else
		{
			rcDest = Rect(X, Y, X + FWidth, Y + LineHeight);
			Y = (int)((FHeight - LineHeight) / /*div*/ 2);
			rcSrc = Rect(Number * FWidth, Y, (Number + 1) * FWidth, Y + LineHeight);
		}
		DrawTransparentBitmap(FImages, rcSrc, aCanvas, rcDest, 255);
	}
}

/* TSynHotKey */

bool __fastcall KeySameAsShiftState(WORD Key, TShiftState Shift)
{
	bool result = false;
	result = (Key == SYNEDIT_SHIFT) && (Shift.Contains(ssShift)) || (Key == SYNEDIT_CONTROL) && (Shift.Contains(ssCtrl)) || (Key == SYNEDIT_MENU) && (Shift.Contains(ssAlt));
	return result;
}

TShiftState __fastcall ModifiersToShiftState(THKModifiers Modifiers)
{
	TShiftState result;
	result = Syneditmiscclasses__1;
	if(Modifiers.Contains(hkShift))
		result << ssShift;
	if(Modifiers.Contains(hkCtrl))
		result << ssCtrl;
	if(Modifiers.Contains(hkAlt))
		result << ssAlt;
	return result;
}

THKInvalidKey __fastcall ShiftStateToTHKInvalidKey(TShiftState Shift)
{
	THKInvalidKey result = hcNone;
	Shift = Shift * Syneditmiscclasses__2;
	if(Shift == Syneditmiscclasses__3)
		result = hcShift;
	else
	{
		if(Shift == Syneditmiscclasses__4)
			result = hcCtrl;
		else
		{
			if(Shift == Syneditmiscclasses__5)
				result = hcAlt;
			else
			{
				if(Shift == Syneditmiscclasses__6)
					result = hcShiftCtrl;
				else
				{
					if(Shift == Syneditmiscclasses__7)
						result = hcShiftAlt;
					else
					{
						if(Shift == Syneditmiscclasses__8)
							result = hcCtrlAlt;
						else
						{
							if(Shift == Syneditmiscclasses__9)
								result = hcShiftCtrlAlt;
							else
								result = hcNone;
						}
					}
				}
			}
		}
	}
	return result;
}

String __fastcall ShortCutToTextEx(WORD Key, TShiftState Shift)
{
	String result;
	if(Shift.Contains(ssCtrl))
		result = Vcl_Consts_SmkcCtrl;
	if(Shift.Contains(ssShift))
		result = result + Vcl_Consts_SmkcShift;
	if(Shift.Contains(ssAlt))
		result = result + Vcl_Consts_SmkcAlt;
	result = result + ShortCutToText(((TShortCut) Key));
	if(result == L"")
		result = Vcl_Consts_srNone;
	return result;
}

__fastcall TSynHotKey::TSynHotKey(TComponent* AOwner)
 : inherited(AOwner),
			FBorderStyle((Vcl::Forms::TBorderStyle) 0),
			FHotKey((TShortCut) 0),
			FPressedOnlyModifiers(false)
{
	BorderStyle = (TBorderStyle) bsSingle;
	ControlStyle = ControlStyle + Syneditmiscclasses__10;
	FInvalidKeys = Syneditmiscclasses__11;
	FModifiers = Syneditmiscclasses__12;
	SetHotKey((TShortCut) 0x0041); /* Alt+A */
	ParentColor = false;
	Color = (TColor) clWindow;
	TabStop = true;
}

void __fastcall TSynHotKey::CreateParams(TCreateParams& Params)
{
	const DWORD BorderStyles[bsSingle - bsNone+ 1/*# TSynBorderStyle*/] = {0, (DWORD) WS_BORDER};
	const unsigned long ClassStylesOff = CS_VREDRAW | CS_HREDRAW;
	inherited::CreateParams(Params);
	/*# with Params do */
	{
		auto& with0 = Params;
		with0.WindowClass.style = with0.WindowClass.style & ~ClassStylesOff;
		with0.Style = with0.Style | BorderStyles[FBorderStyle] | WS_CLIPCHILDREN;
		if(NewStyleControls && Ctl3D && (FBorderStyle == bsSingle))
		{
			with0.Style = with0.Style & ~WS_BORDER;
			with0.ExStyle = with0.ExStyle | WS_EX_CLIENTEDGE;
		}
	}
}

void __fastcall TSynHotKey::DoExit()
{
	inherited::DoExit();
	if(FPressedOnlyModifiers)
	{
		Text = Vcl_Consts_srNone;
		Invalidate();
	}
}

void __fastcall TSynHotKey::KeyDown(WORD& Key, TShiftState Shift)
{
	THKInvalidKey MaybeInvalidKey = hcNone;
	WORD SavedKey = 0;
	SavedKey = Key;
	FPressedOnlyModifiers = KeySameAsShiftState(Key, Shift);
	MaybeInvalidKey = ShiftStateToTHKInvalidKey(Shift);
	if(FInvalidKeys.Contains(MaybeInvalidKey))
		Shift = ModifiersToShiftState(FModifiers);
	if(!FPressedOnlyModifiers)
	{
		FHotKey = ShortCut(Key, Shift);
	}
	else
	{
		FHotKey = (TShortCut) 0;
		Key = 0;
	}
	if(Text != ShortCutToTextEx(Key, Shift))
	{
		Text = ShortCutToTextEx(Key, Shift);
		Invalidate();
		SetCaretPos(BorderWidth + 1 + Canvas->TextWidth(Text), BorderWidth + 1);
	}
	Key = SavedKey;
}

void __fastcall TSynHotKey::KeyUp(WORD& Key, TShiftState Shift)
{
	if(FPressedOnlyModifiers)
	{
		Text = Vcl_Consts_srNone;
		Invalidate();
		SetCaretPos(BorderWidth + 1 + Canvas->TextWidth(Text), BorderWidth + 1);
	}
}

void __fastcall TSynHotKey::MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
	inherited::MouseDown(Button, Shift, X, Y);
	SetFocus();
}

void __fastcall TSynHotKey::Paint()
{
	TRect R = {};
	R = ClientRect;
	Canvas->Brush->Style = bsSolid;
	Canvas->Brush->Color = Color;
	InflateRect(R, -BorderWidth, -BorderWidth);
	Canvas->FillRect(R);
	Canvas->Font = Font;
	Canvas->TextRect(R, BorderWidth + 1, BorderWidth + 1, Text);
}

void __fastcall TSynHotKey::SetBorderStyle(const Synedit::TSynBorderStyle Value)
{
	if(FBorderStyle != Value)
	{
		FBorderStyle = Value;
		RecreateWnd();
	}
}

void __fastcall TSynHotKey::SetHotKey(const TShortCut Value)
{
	WORD Key = 0;
	TShiftState Shift;
	THKInvalidKey MaybeInvalidKey = hcNone;
	ShortCutToKey(Value, Key, Shift);
	MaybeInvalidKey = ShiftStateToTHKInvalidKey(Shift);
	if(FInvalidKeys.Contains(MaybeInvalidKey))
		Shift = ModifiersToShiftState(FModifiers);
	FHotKey = ShortCut(Key, Shift);
	Text = ShortCutToTextEx(Key, Shift);
	Invalidate();
	if(!Visible)
		SetCaretPos(BorderWidth + 1 + Canvas->TextWidth(Text), BorderWidth + 1);
}

void __fastcall TSynHotKey::SetInvalidKeys(const THKInvalidKeys Value)
{
	FInvalidKeys = Value;
	SetHotKey(FHotKey);
}

void __fastcall TSynHotKey::SetModifiers(const THKModifiers Value)
{
	FModifiers = Value;
	SetHotKey(FHotKey);
}

void __fastcall TSynHotKey::WMGetDlgCode(::TMessage& Message)
{
	Message.Result = DLGC_WANTTAB | DLGC_WANTARROWS;
}

void __fastcall TSynHotKey::WMKillFocus(TWMKillFocus& Msg)
{
	DestroyCaret();
}

void __fastcall TSynHotKey::WMSetFocus(TWMSetFocus& Msg)
{
	Canvas->Font = Font;
	CreateCaret(Handle, 0, 1, -Canvas->Font->Height + 2);
	SetCaretPos(BorderWidth + 1 + Canvas->TextWidth(Text), BorderWidth + 1);
	ShowCaret(Handle);
}

/* TBetterRegistry */

bool __fastcall TBetterRegistry::OpenKeyReadOnly(const String Key)
{
	bool result = false;

	auto IsRelative = [&](const String Value) -> bool 
	{
		bool result = false;
		result = !((Value != L"") && (Value[1] == L'\\'));
		return result;
	};
	HKEY TempKey = 0;
	String S;
	bool Relative = false;
	S = Key;
	Relative = IsRelative(S);
	if(!Relative)
		S.Delete(1, 	1);
	TempKey = 0;
	result = RegOpenKeyEx(GetBaseKey(Relative), ustr2pwchar(S), 0, (REGSAM) KEY_READ, &TempKey) == ERROR_SUCCESS;
	if(result)
	{
		if((CurrentKey != 0) && Relative)
			S = CurrentPath + L"\\" + S;
		ChangeKey(TempKey, S);
	}
	return result;
} /* TBetterRegistry.OpenKeyReadOnly */

/* TSynEditSearchCustom */

// possibility to preprocess search expression before is send to SynEdit.SearchReplace()

String __fastcall TSynEditSearchCustom::PreprocessReplaceExpression(const String AReplace)
{
	String result;
	result = AReplace;
	return result;
}

/* TSynGutterBand */

void __fastcall TSynGutterBand::Assign(TPersistent* Source)
{
	TSynGutterBand* Src = nullptr;
	if(ASSIGNED(Source) && (ObjectIs(Source, TSynGutterBand*)))
	{
		Src = ((TSynGutterBand*) Source);
		FKind = Src->FKind;
		FVisible = Src->FVisible;
		FBackground = Src->FBackground;
		FWidth = Src->FWidth;
		Changed(false);
	}
	else
	inherited::Assign(Source);
}

__fastcall TSynGutterBand::TSynGutterBand(TCollection* Collection)
 : inherited(Collection),
			FKind(gbkCustom),
			FVisible(false),
			FWidth(0),
			FBackground(gbbNone)
{
	FVisible = true;
	FBackground = gbbGutter;
}

void __fastcall TSynGutterBand::DoClick(TObject* Sender, TMouseButton Button, int X, int Y, int Row, int Line)
{
	TCustomSynEdit* SynEdit = nullptr;
	int Index = 0;
	TRect rcFold = {};
	if(Visible && (FKind == gbkFold))
	{
		SynEdit = ((TCustomSynEdit*) Editor);
		if(SynEdit->AllFoldRanges->FoldStartAtLine(Line, Index))
		{
			rcFold = FoldShapeRect(Row, Line);
      // See if we actually clicked on the rectangle...
			if(!rcFold.IsEmpty() && PtInRect(rcFold, Point(X, Y)))
			{
				if(SynEdit->AllFoldRanges->Ranges->Items[Index].Collapsed)
					SynEdit->Uncollapse(Index);
				else
					SynEdit->Collapse(Index);
			}
		}
	}
	if(ASSIGNED(FOnClick))
		FOnClick(Sender, Button, X, Y, Row, Line);
}

void __fastcall TSynGutterBand::DoMouseCursor(TObject* Sender, int X, int Y, int Row, int Line, TCursor& Cursor)
{
	TCustomSynEdit* SynEdit = nullptr;
	int Index = 0;
	TRect rcFold = {};
	if(Visible && (FKind == gbkFold))
	{
		SynEdit = ((TCustomSynEdit*) Editor);
		if(SynEdit->AllFoldRanges->FoldStartAtLine(Line, Index))
		{
			rcFold = FoldShapeRect(Row, Line);
			if(!rcFold.IsEmpty() && PtInRect(rcFold, Point(X, Y)))
				Cursor = System::Uitypes::crHandPoint;
		}
	}
	if(ASSIGNED(FOnMouseCursor))
		FOnMouseCursor(Sender, X, Y, Row, Line, Cursor);
}
// Drawing of builtin bands

void __fastcall TSynGutterBand::DoPaintLines(TCanvas* Canvas, const TRect& cClipR, int FirstRow, int LastRow)
{
	TRect ClipR = cClipR;
	switch(FKind)
	{
		case gbkMarks:
		PaintMarks(Canvas, ClipR, FirstRow, LastRow);
		break;
		case gbkLineNumbers:
		PaintLineNumbers(Canvas, ClipR, FirstRow, LastRow);
		break;
		case gbkFold:
		PaintFoldShapes(Canvas, ClipR, FirstRow, LastRow);
		break;
		case gbkMargin:
		PaintMargin(Canvas, ClipR, FirstRow, LastRow);
		break;
		default:
		  ;
		break;
	}
}
// Given that WordWrap and CodeFolding are mutally exclusive Row = Line
// But at some point this could be relaxed

TRect __fastcall TSynGutterBand::FoldShapeRect(int Row, int Line)
{
	TRect result = {};
	TCustomSynEdit* SynEdit = nullptr;
	int L = 0;
	int Index = 0;
	int ShapeSize = 0;
	int Margin = 0;
	result = TRect::Empty();
	if(!Visible || (FKind != gbkFold))
		return result;
	SynEdit = ((TCustomSynEdit*) Editor);
	if(SynEdit->RowToLine(Row) != Line)
		return result;
	if(SynEdit->AllFoldRanges->FoldStartAtLine(Line, Index))
	{
		ShapeSize = SynEdit->CodeFolding->ScaledGutterShapeSize(Gutter->FCurrentPPI);
		L = LeftX;
		if(L < 0)
			return result;
		Margin = MulDiv(MarginX, Gutter->FCurrentPPI, 96);
		result.TopLeft() = Point(L + Margin, (Row - SynEdit->TopLine) * SynEdit->LineHeight + (int)((SynEdit->LineHeight - ShapeSize) / /*div*/ 2));
		result.BottomRight() = result.TopLeft();
		result.BottomRight().Offset(ShapeSize, ShapeSize);
	}
	return result;
}

String __fastcall TSynGutterBand::GetDisplayName()
{
	String result;
// ld.lld: error: undefined symbol: System::UnicodeString System::Rtti::TRttiEnumerationType::GetName<Syneditmiscclasses::TSynGutterBandKind>(Syneditmiscclasses::TSynGutterBandKind)	
// todo dme	result = Format(L"%s - kind: %s", ARRAYOFCONST((ClassName(), TRttiEnumerationType::GetName<TSynGutterBandKind>(FKind))));
	return result;
}

TPersistent* __fastcall TSynGutterBand::GetEditor()
{
	TPersistent* result = nullptr;
	if(ASSIGNED(Gutter))
		result = Gutter->GetOwner();
	else
		result = nullptr;
	return result;
}

int __fastcall TSynGutterBand::GetLeftX()
{
	int result = 0;
	int I = 0;
	int L = 0;
	TSynGutterBand* Band = nullptr;
	result = -1;
	L = 0;
	if(ASSIGNED(Gutter))
	{
		int stop = 0;
		for(stop = Gutter->Bands->Count - 1, I = 0; I <= stop; I++)
		{
			Band = Gutter->Bands->Bands[I];
			if(!Band->Visible)
				continue;
			if(Gutter->Bands->Bands[I] == this)
				return L;
			L += Band->RealWidth();
		}
	}
	return result;
}

TSynGutter* __fastcall TSynGutterBand::GetSynGutter()
{
	TSynGutter* result = nullptr;
	if(ASSIGNED(Collection))
		result = (TSynGutter*) Collection->Owner();
	else
		result = nullptr;
	return result;
}

bool __fastcall TSynGutterBand::GetVisible()
{
	bool result = false;
	result = FVisible;
	switch(FKind)
	{
		case gbkLineNumbers:
		result = ASSIGNED(Gutter) && Gutter->ShowLineNumbers;
		break;
		case gbkFold:
		result = ASSIGNED(Editor) && ((TCustomSynEdit*) Editor)->UseCodeFolding;
		break;
		default:
		  ;
		break;
	}
	return result;
}

int __fastcall TSynGutterBand::GetWidth()
{
	int result = 0;
	switch(FKind)
	{
		case gbkLineNumbers:
		case gbkFold:
		result = 0;
		break;
		default:
		result = FWidth;
		break;
	}
	return result;
}

bool __fastcall TSynGutterBand::IsVisibleStored()
{
	bool result = false;
	result = FVisible && !(Syneditmiscclasses__13.Contains(FKind));
	return result;
}

bool __fastcall TSynGutterBand::IsWidthStored()
{
	bool result = false;
	result = !(Syneditmiscclasses__14.Contains(FKind));
	return result;
}

void __fastcall TSynGutterBand::PaintFoldShapes(TCanvas* Canvas, const TRect& cClipR, int FirstRow, int LastRow)
{
	TRect ClipR = cClipR;
	const int PlusMinusMargin = 2;
	TCustomSynEdit* SynEdit = nullptr;
	int vLine = 0;
	__int64 cRow = 0;
	TRect rcFold = {};
	int X = 0;
	TSynFoldRange FoldRange = {};
	int Index = 0;
	int Margin = 0;
	int PMMargin = 0;
	int ShapeSize = 0;
	int PPI = 0;
	SynEdit = ((TCustomSynEdit*) Editor);
	Assert(ASSIGNED(SynEdit));
	Assert(ASSIGNED(Gutter));
	PPI = Gutter->FCurrentPPI;

  // Draw the folding lines and squares
	if(SynEdit->UseCodeFolding)
	{
		__int64 stop = 0;
		Margin = MulDiv(MarginX, PPI, 96);
		PMMargin = MulDiv(PlusMinusMargin, PPI, 96);
		ShapeSize = SynEdit->CodeFolding->ScaledGutterShapeSize(PPI);
		for(stop = LastRow, cRow = FirstRow; cRow <= stop; cRow++)
		{
			vLine = SynEdit->RowToLine((int) cRow);
			if(vLine > SynEdit->Lines->Count)
				break;
			rcFold.TopLeft() = Point(ClipR.Left + Margin, (cRow - SynEdit->TopLine) * SynEdit->LineHeight + (int)((SynEdit->LineHeight - ShapeSize) / /*div*/ 2));
			rcFold.BottomRight() = rcFold.TopLeft();
			rcFold.BottomRight().Offset(ShapeSize, ShapeSize);
			Canvas->Pen->Color = SynEdit->CodeFolding->FolderBarLinesColor;

      // Any fold ranges beginning on this line?
			if(SynEdit->AllFoldRanges->FoldStartAtLine(vLine, Index))
			{
				FoldRange = SynEdit->AllFoldRanges->Ranges->Items[Index];
				Canvas->Brush->Color = SynEdit->CodeFolding->FolderBarLinesColor;
				Canvas->FrameRect(rcFold);

        // Paint minus sign
				Canvas->Pen->Color = SynEdit->CodeFolding->FolderBarLinesColor;
				Canvas->MoveTo(rcFold.Left + PMMargin, rcFold.Top + (int)(ShapeSize / /*div*/ 2));
				Canvas->LineTo(rcFold.Right - PMMargin, rcFold.Top + (int)(ShapeSize / /*div*/ 2));

        // Paint vertical line of plus sign
				if(FoldRange.Collapsed)
				{
					X = rcFold.Left + (int)(ShapeSize / /*div*/ 2);
					Canvas->MoveTo(X, rcFold.Top + PMMargin);
					Canvas->LineTo(X, rcFold.Bottom - PMMargin);
				}
				else

        // Draw the bottom part of a line
				{
					X = rcFold.Left + (int)(ShapeSize / /*div*/ 2);
					Canvas->MoveTo(X, rcFold.Bottom);
					Canvas->LineTo(X, (int) ((cRow - SynEdit->TopLine + 1) * SynEdit->LineHeight));
				}
			}
			else

        // Need to paint a line end?
			{
				if(SynEdit->AllFoldRanges->FoldEndAtLine(vLine, Index))
				{
					X = rcFold.Left + (int)(ShapeSize / /*div*/ 2);
					Canvas->MoveTo(X, (int) ((cRow - SynEdit->TopLine) * SynEdit->LineHeight));
					Canvas->LineTo(X, rcFold.Top + ((int)((rcFold.Bottom - rcFold.Top) / /*div*/ 2)));
					Canvas->LineTo(rcFold.Right, rcFold.Top + ((int)((rcFold.Bottom - rcFold.Top) / /*div*/ 2)));
				}
        // Need to paint a line?
				if(SynEdit->AllFoldRanges->FoldAroundLine(vLine, Index))
				{
					X = rcFold.Left + (int)(ShapeSize / /*div*/ 2);
					Canvas->MoveTo(X, (int) ((cRow - SynEdit->TopLine) * SynEdit->LineHeight));
					Canvas->LineTo(X, (int) ((cRow - SynEdit->TopLine + 1) * SynEdit->LineHeight));
				}
			}
		}
	}
}

void __fastcall TSynGutterBand::PaintLineNumbers(TCanvas* Canvas, const TRect& cClipR, int FirstRow, int LastRow)
{
	TRect ClipR = cClipR;
	TCustomSynEdit* SynEdit = nullptr;
	__int64 Row = 0;
	int Line = 0;
	int LineTop = 0;
	TRect LineRect = {};
	int PPI = 0;
	String S;
	__int64 stop = 0;
	SynEdit = ((TCustomSynEdit*) Editor);
	Assert(ASSIGNED(Gutter));
	Assert(ASSIGNED(SynEdit));
	PPI = Gutter->FCurrentPPI;
	if(Gutter->UseFontStyle)
		Canvas->Font = Gutter->Font;
	else
		Canvas->Font = SynEdit->Font;
	Canvas->Brush->Style = bsClear;
	for(stop = LastRow, Row = FirstRow; Row <= stop; Row++)
	{
		Line = SynEdit->RowToLine((int) Row);
		LineTop = (int) ((Row - SynEdit->TopLine) * SynEdit->LineHeight);
		if(SynEdit->WordWrap && (Row != SynEdit->LineToRow(Line)))
      // paint wrapped line glyphs
			SynEdit->WordWrapGlyph->Draw(Canvas, ClipR.Right - SynEdit->WordWrapGlyph->Width, LineTop, SynEdit->LineHeight);
		else
		{
			LineRect = Rect(ClipR.Left + MulDiv(MarginX, PPI, 96), LineTop, ClipR.Right, LineTop + SynEdit->LineHeight);
			S = Gutter->FormatLineNumber(Line);
			if(ASSIGNED(SynEdit->OnGutterGetText))
				SynEdit->OnGutterGetText(this, Line, S);
			Canvas->TextRect(LineRect, S, Syneditmiscclasses__15);
		}
	}
}

void __fastcall TSynGutterBand::PaintLines(TCanvas* Canvas, const TRect& cClipR, int FirstRow, int LastRow)
{
	TRect ClipR = cClipR;
	bool DoDefault = false;
	DoDefault = true;
	if(ASSIGNED(FOnPaintLines))
		FOnPaintLines(Canvas, ClipR, FirstRow, LastRow, DoDefault);
	if(DoDefault)
		DoPaintLines(Canvas, ClipR, FirstRow, LastRow);
}

void __fastcall TSynGutterBand::PaintMargin(TCanvas* Canvas, const TRect& cClipR, int FirstRow, int LastRow)
{
	TRect ClipR = cClipR;
	int Offset = 0;
	if(Gutter->BorderStyle != gbsNone)
		/*# with Canvas do */
		{
			auto with0 = Canvas;
			with0->Pen->Color = Gutter->BorderColor;
			with0->Pen->Width = 1;
			if(Gutter->BorderStyle == gbsMiddle)
				Offset = Max(2, (int)((ClipR.Right - ClipR.Left) / /*div*/ 2));
			else
				Offset = 1;
			with0->MoveTo(ClipR.Right - Offset, ClipR.Top);
			with0->LineTo(ClipR.Right - Offset, ClipR.Bottom);
		}
}

void __fastcall TSynGutterBand::PaintMarks(TCanvas* Canvas, const TRect& cClipR, int FirstRow, int LastRow)
{
	TRect ClipR = cClipR;
	TCustomSynEdit* SynEdit = nullptr;

	auto DrawMark = [&](TSynEditMark* aMark, int& aGutterOff, int aMarkRow) -> void 
	{
		if((!aMark->InternalImage) && ASSIGNED(SynEdit->BookMarkOptions->BookmarkImages))
		{
			if(aMark->ImageIndex <= SynEdit->BookMarkOptions->BookmarkImages->Count)
			{
				if(aMark->IsBookmark == SynEdit->BookMarkOptions->DrawBookmarksFirst)
					aGutterOff = 0;
				else
				{
					if(aGutterOff == 0)
						aGutterOff = SynEdit->BookMarkOptions->Xoffset;
				}
				SynEdit->BookMarkOptions->BookmarkImages->Draw(Canvas, ClipR.Left + SynEdit->BookMarkOptions->LeftMargin + aGutterOff, (aMarkRow - SynEdit->TopLine) * SynEdit->LineHeight, aMark->ImageIndex);
				aGutterOff += SynEdit->BookMarkOptions->Xoffset;
			}
		}
		else
		{
			if(Syneditmiscclasses__16.Contains(aMark->ImageIndex))
			{
				if(aGutterOff == 0)
				{
					Gutter->InternalImage->Draw(Canvas, aMark->ImageIndex, ClipR.Left + SynEdit->BookMarkOptions->LeftMargin + aGutterOff, (aMarkRow - SynEdit->TopLine) * SynEdit->LineHeight, SynEdit->LineHeight);
				}
				aGutterOff += SynEdit->BookMarkOptions->Xoffset;
			}
		}
	};
	int vFirstLine = 0;
	int vLastLine = 0;
	int cMark = 0;
	int vMarkRow = 0;
	TArray<int> aGutterOffs;
	bool bHasOtherMarks = false;
	int Index = 0;
	SynEdit = ((TCustomSynEdit*) Editor);
	Assert(ASSIGNED(SynEdit));
	vFirstLine = SynEdit->RowToLine(FirstRow);
	vLastLine = SynEdit->RowToLine(LastRow);
	if(SynEdit->BookMarkOptions->GlyphsVisible && (SynEdit->Marks->Count > 0) && (vLastLine >= vFirstLine))
	{
		int stop = 0;
		aGutterOffs.Length = LastRow - FirstRow + 1;
    // Instead of making a two pass loop we look while drawing the bookmarks
    // whether there is any other mark to be drawn
		bHasOtherMarks = false;
		for(stop = SynEdit->Marks->Count - 1, cMark = 0; cMark <= stop; cMark++)
		{
			/*# with SynEdit.Marks[cMark] do */
			{
				
				if(SynEdit->Marks->Items[cMark]->Visible && (SynEdit->Marks->Items[cMark]->Line >= vFirstLine) && (SynEdit->Marks->Items[cMark]->Line <= vLastLine) && (SynEdit->Marks->Items[cMark]->Line <= SynEdit->Lines->Count) && !(SynEdit->UseCodeFolding && SynEdit->AllFoldRanges->FoldHidesLine(SynEdit->Marks->Items[cMark]->Line, Index)))
				{
					if(SynEdit->Marks->Items[cMark]->IsBookmark != SynEdit->BookMarkOptions->DrawBookmarksFirst)
						bHasOtherMarks = true;
					else
					{
						vMarkRow = SynEdit->LineToRow(SynEdit->Marks->Items[cMark]->Line);
						if(vMarkRow >= FirstRow)
							DrawMark(SynEdit->Marks->Items[cMark], aGutterOffs[vMarkRow - FirstRow], vMarkRow);
					}
				}
			}
		}
		if(bHasOtherMarks)
		{
			int stop = 0;
			for(stop = SynEdit->Marks->Count - 1, cMark = 0; cMark <= stop; cMark++)
			{
				/*# with SynEdit.Marks[cMark] do */
				{
					
					if(SynEdit->Marks->Items[cMark]->Visible && (SynEdit->Marks->Items[cMark]->IsBookmark != SynEdit->BookMarkOptions->DrawBookmarksFirst) && (SynEdit->Marks->Items[cMark]->Line >= vFirstLine) && (SynEdit->Marks->Items[cMark]->Line <= vLastLine) && (SynEdit->Marks->Items[cMark]->Line <= SynEdit->Lines->Count) && !(SynEdit->UseCodeFolding && SynEdit->AllFoldRanges->FoldHidesLine(SynEdit->Marks->Items[cMark]->Line, Index)))
					{
						vMarkRow = SynEdit->LineToRow(SynEdit->Marks->Items[cMark]->Line);
						if(vMarkRow >= FirstRow)
							DrawMark(SynEdit->Marks->Items[cMark], aGutterOffs[vMarkRow - FirstRow], vMarkRow);
					}
				}
			}
		}
	}
}

int __fastcall TSynGutterBand::RealWidth()
{
	int result = 0;
	int PPI = 0;
	Assert(ASSIGNED(Editor));
	Assert(ASSIGNED(Gutter));
	PPI = Gutter->FCurrentPPI;
	if(Visible)
		switch(FKind)
		{
			case gbkLineNumbers:
      // A margin of two pixels at the end
			result = Gutter->FAutoSizeDigitCount * IfThen(Gutter->UseFontStyle, Gutter->FCharWidth, ((TCustomSynEdit*) Editor)->CharWidth) + MulDiv(MarginX, PPI, 96);
			break;
			case gbkFold:
			result = ((TCustomSynEdit*) Editor)->CodeFolding->ScaledGutterShapeSize(PPI) + MulDiv(MarginX, PPI, 96);
			break;
			default:
			result = MulDiv(FWidth, PPI, 96);
			break;
		}
	else
		result = 0;
	return result;
}

void __fastcall TSynGutterBand::SetBackground(TSynGutterBandBackground Value)
{
	FBackground = Value;
	Changed(false);
}

void __fastcall TSynGutterBand::SetKind(TSynGutterBandKind Kind)
{
	FKind = Kind;
	Changed(false);
}

void __fastcall TSynGutterBand::SetOnClick(const TGutterBandClickEvent Value)
{
	FOnClick = Value;
	Changed(false);
}

void __fastcall TSynGutterBand::SetOnMouseCursor(const TGutterMouseCursorEvent Value)
{
	FOnMouseCursor = Value;
}

void __fastcall TSynGutterBand::SetOnPaintLines(const TGutterBandPaintEvent Value)
{
	FOnPaintLines = Value;
	Changed(false);
}

void __fastcall TSynGutterBand::SetVisible(bool Value)
{
	FVisible = Value;
	Changed(false);
}

void __fastcall TSynGutterBand::SetWidth(int Value)
{
	if(!(Syneditmiscclasses__17.Contains(FKind)))
	{
		FWidth = Value;
		Changed(false);
	}
}

/* TSynBandsCollection */

TSynGutterBand* __fastcall TSynBandsCollection::GetBands(int Index)
{
	TSynGutterBand* result = nullptr;
	result = ((TSynGutterBand*) Items[Index]);
	return result;
}

void __fastcall TSynBandsCollection::Update(TCollectionItem* Item)
{
	TSynGutter* Gutter = nullptr;
	Gutter = ((TSynGutter*) GetOwner());
	if(ASSIGNED(Gutter))
		Gutter->Changed();
}


}  // namespace SynEditMiscClasses

