
#include <vcl.h>
#pragma hdrstop

#include "SynTextDrawer.h"
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include "d2c_systypes.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synunicode;
using namespace System;
using namespace System::Sysutils;
using namespace System::Types;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Syntextdrawer
{
#define Syntextdrawer__0 TFontStyles()
#define Syntextdrawer__1 TTextOutOptions()

__fastcall EheFontStockException::EheFontStockException(const String Msg) : inherited(Msg) {}
__fastcall EheFontStockException::EheFontStockException(const String Msg, const TVarRec* Args, int Args_maxidx) : inherited(Msg, Args, Args_maxidx) {}
__fastcall EheFontStockException::EheFontStockException(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Msg, Args, Args_maxidx, AHelpContext) {}
__fastcall EheFontStockException::EheFontStockException(const String Msg, int AHelpContext) : inherited(Msg, AHelpContext) {}
__fastcall EheFontStockException::EheFontStockException(System::NativeUInt Ident) : inherited(Ident) {}
__fastcall EheFontStockException::EheFontStockException(System::PResStringRec ResStringRec) : inherited(ResStringRec) {}
__fastcall EheFontStockException::EheFontStockException(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx) : inherited(Ident, Args, Args_maxidx) {}
__fastcall EheFontStockException::EheFontStockException(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx) : inherited(ResStringRec, Args, Args_maxidx) {}
__fastcall EheFontStockException::EheFontStockException(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(ResStringRec, Args, Args_maxidx, AHelpContext) {}
__fastcall EheFontStockException::EheFontStockException(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Ident, Args, Args_maxidx, AHelpContext) {}
__fastcall EheFontStockException::EheFontStockException(System::NativeUInt Ident, int AHelpContext) : inherited(Ident, AHelpContext) {}
__fastcall EheFontStockException::EheFontStockException(System::PResStringRec ResStringRec, int AHelpContext) : inherited(ResStringRec, AHelpContext) {}
__fastcall TheFontStock::TheFontStock() {}
__fastcall EheTextDrawerException::EheTextDrawerException(const String Msg) : inherited(Msg) {}
__fastcall EheTextDrawerException::EheTextDrawerException(const String Msg, const TVarRec* Args, int Args_maxidx) : inherited(Msg, Args, Args_maxidx) {}
__fastcall EheTextDrawerException::EheTextDrawerException(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Msg, Args, Args_maxidx, AHelpContext) {}
__fastcall EheTextDrawerException::EheTextDrawerException(const String Msg, int AHelpContext) : inherited(Msg, AHelpContext) {}
__fastcall EheTextDrawerException::EheTextDrawerException(System::NativeUInt Ident) : inherited(Ident) {}
__fastcall EheTextDrawerException::EheTextDrawerException(System::PResStringRec ResStringRec) : inherited(ResStringRec) {}
__fastcall EheTextDrawerException::EheTextDrawerException(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx) : inherited(Ident, Args, Args_maxidx) {}
__fastcall EheTextDrawerException::EheTextDrawerException(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx) : inherited(ResStringRec, Args, Args_maxidx) {}
__fastcall EheTextDrawerException::EheTextDrawerException(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(ResStringRec, Args, Args_maxidx, AHelpContext) {}
__fastcall EheTextDrawerException::EheTextDrawerException(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Ident, Args, Args_maxidx, AHelpContext) {}
__fastcall EheTextDrawerException::EheTextDrawerException(System::NativeUInt Ident, int AHelpContext) : inherited(Ident, AHelpContext) {}
__fastcall EheTextDrawerException::EheTextDrawerException(System::PResStringRec ResStringRec, int AHelpContext) : inherited(ResStringRec, AHelpContext) {}
__fastcall TheTextDrawer::TheTextDrawer() {}


TheFontsInfoManager* gFontsInfoManager = nullptr;

/* utility routines */

TheFontsInfoManager* __fastcall GetFontsInfoManager()
{
	TheFontsInfoManager* result = nullptr;
	if(!ASSIGNED(gFontsInfoManager))
		gFontsInfoManager = new TheFontsInfoManager();
	result = gFontsInfoManager;
	return result;
}

int __fastcall Min(int x, int y)
{
	int result = 0;
	if(x < y)
		result = x;
	else
		result = y;
	return result;
}

// UniversalExtTextOut uses UniScribe where available for the best possible
// output quality. This also avoids a bug in (Ext)TextOut that surfaces when
// displaying a combination of Chinese and Korean text.
//
// See here for details: http://groups.google.com/group/microsoft.public.win32.programmer.international/browse_thread/thread/77cd596f2b96dc76/146300208098285c?lnk=st&q=font+substitution+problem#146300208098285c

bool __fastcall UniversalExtTextOut(HDC DC, int X, int Y, TTextOutOptions Options, const TRect& cRect, PWideChar Str, int Count, PIntegerArray ETODist, bool UseLigatures/*# = false*/)
{
	TRect Rect = cRect;
	bool result = false;
	DynamicArray<WideChar> Glyphs;
	TGCPResults CharPlaceInfo = {};
	DWORD TextOutFlags = 0;
	TextOutFlags = 0;
	if(Options.Contains(tooOpaque))
		TextOutFlags = TextOutFlags | ETO_OPAQUE;
	if(Options.Contains(tooClipped))
		TextOutFlags = TextOutFlags | ETO_CLIPPED;
	{
		if(UseLigatures && (Str != nullptr) && ((*Str) != WideNull))
		{
			TextOutFlags = TextOutFlags | ETO_GLYPH_INDEX;
			ZeroMemory(&CharPlaceInfo, sizeof(CharPlaceInfo));
			CharPlaceInfo.lStructSize = sizeof(CharPlaceInfo);
			Glyphs.Length = wcslen(Str);
			CharPlaceInfo.lpGlyphs = &Glyphs[0];
			CharPlaceInfo.nGlyphs = (UINT) Glyphs.Length;
			if(GetCharacterPlacement(DC, Str, wcslen(Str), 0, &CharPlaceInfo, (DWORD) GCP_LIGATE) != 0)
				result = ExtTextOutW(DC, X, Y, TextOutFlags, &Rect, array2ptr(Glyphs), Glyphs.Length, ((int*) ((void*) ETODist)));
			else
				result = ExtTextOutW(DC, X, Y, TextOutFlags, &Rect, Str, Count, ((int*) ((void*) ETODist)));
		}
		else
		result = ExtTextOutW(DC, X, Y, TextOutFlags, &Rect, Str, Count, ((int*) ((void*) ETODist)));
	}
	return result;
}

/* TheFontsInfoManager */

void __fastcall TheFontsInfoManager::LockFontsInfo(PheSharedFontsInfo pFontsInfo)
{
	++(*pFontsInfo).LockCount;
}

__fastcall TheFontsInfoManager::TheFontsInfoManager()
 : FFontsInfo(new TList())
{
	// inherited;
}

PheSharedFontsInfo __fastcall TheFontsInfoManager::CreateFontsInfo(TFont* ABaseFont, const TLogFont& LF)
{
	PheSharedFontsInfo result = nullptr;
	result = new TheSharedFontsInfo;
	FillChar((void**)result, (int) sizeof(TheSharedFontsInfo), 0);
	/*# with result^ do */
	{
		auto& with0 = (*result);
		try
		{
			with0.BaseFont = new TFont();
			with0.BaseFont->Assign(ABaseFont);
			with0.BaseLF = LF;
			with0.IsTrueType = (0 != (TRUETYPE_FONTTYPE & LF.lfPitchAndFamily));
		}
		catch(...)
		{
			delete (*result).BaseFont;
			delete result;
			throw ;
		}
	}
	return result;
}

void __fastcall TheFontsInfoManager::UnLockFontsInfo(PheSharedFontsInfo pFontsInfo)
{
	/*# with pFontsInfo^ do */
	{
		auto& with0 = (*pFontsInfo);
		--with0.LockCount;
		if(0 == with0.LockCount)
			DestroyFontHandles(pFontsInfo);
	}
}

__fastcall TheFontsInfoManager::~TheFontsInfoManager()
{
	gFontsInfoManager = nullptr;
	if(ASSIGNED(FFontsInfo))
	{
		while(FFontsInfo->Count > 0)
		{
			Assert(1 == (*((PheSharedFontsInfo) FFontsInfo->Items[FFontsInfo->Count - 1])).RefCount);
			ReleaseFontsInfo(((PheSharedFontsInfo) FFontsInfo->Items[FFontsInfo->Count - 1]));
		}
		delete FFontsInfo;
	}
	// inherited;
}

void __fastcall TheFontsInfoManager::DestroyFontHandles(PheSharedFontsInfo pFontsInfo)
{
	int i = 0;
	/*# with pFontsInfo^ do */
	{
		auto& with0 = (*pFontsInfo);
		int stop = 0;
		for(stop = FontStyleCombineCount - 1 /*# High(TheStockFontPatterns) */, i = 0 /*# Low(TheStockFontPatterns) */; i <= stop; i++)
		{
			/*# with FontsData[i] do */
			{
				
				if(with0.FontsData[i].Handle != 0)
				{
					DeleteObject(with0.FontsData[i].Handle);
					with0.FontsData[i].Handle = 0;
				}
			}
		}
	}
}

PheSharedFontsInfo __fastcall TheFontsInfoManager::FindFontsInfo(const TLogFont& LF)
{
	PheSharedFontsInfo result = nullptr;
	int i = 0;
	int stop = 0;
	for(stop = FFontsInfo->Count - 1, i = 0; i <= stop; i++)
	{
		result = ((PheSharedFontsInfo) FFontsInfo->Items[i]);
		if(CompareMem(&((*result).BaseLF), (void*) &LF, (NativeInt) sizeof(TLogFont)))
			return result;
	}
	result = nullptr;
	return result;
}

PheSharedFontsInfo __fastcall TheFontsInfoManager::GetFontsInfo(TFont* ABaseFont)
{
	PheSharedFontsInfo result = nullptr;
	TLogFont LF = {};
	Assert(ASSIGNED(ABaseFont));
	RetrieveLogFontForComparison(ABaseFont, LF);
	result = FindFontsInfo(LF);
	if(!ASSIGNED(result))
	{
		result = CreateFontsInfo(ABaseFont, LF);
		FFontsInfo->Add(result);
	}
	if(ASSIGNED(result))
		++(*result).RefCount;
	return result;
}

void __fastcall TheFontsInfoManager::ReleaseFontsInfo(PheSharedFontsInfo pFontsInfo)
{
	Assert(ASSIGNED(pFontsInfo));
	/*# with pFontsInfo^ do */
	{
		auto& with0 = (*pFontsInfo);
		Assert(with0.LockCount < with0.RefCount);
		if(with0.RefCount > 1)
			--with0.RefCount;
		else
		{
			FFontsInfo->Remove(pFontsInfo);
      // free all objects
			delete with0.BaseFont;
			delete pFontsInfo;
		}
	}
}

void __fastcall TheFontsInfoManager::RetrieveLogFontForComparison(TFont* ABaseFont, TLogFont& LF)
{
	PChar pEnd = nullptr;
	GetObject(ABaseFont->Handle, (int) sizeof(TLogFont), &LF);
	/*# with LF do */
	{
		auto& with0 = LF;
		with0.lfItalic = 0;
		with0.lfUnderline = 0;
		with0.lfStrikeOut = 0;
		pEnd = StrEnd(with0.lfFaceName);
		FillChar((void**)&pEnd[1], &with0.lfFaceName[31 /*# High(lfFaceName) */] - pEnd, 0);
	}
}

/* TheFontStock */

// CalcFontAdvance : Calculation a advance of a character of a font.
//  [*]hCalcFont will be selected as FDC's font if FDC wouldn't be zero.

/*#static*/
int __fastcall TheFontStock::CalcFontAdvance(HDC DC, PInteger pCharHeight)
{
	int result = 0;
	TTextMetric TM = {};
	TABC ABC = {};
	bool HasABC = false;
  // Calculate advance of a character.
  // The following code uses ABC widths instead TextMetric.tmAveCharWidth
  // because ABC widths always tells truth but tmAveCharWidth does not.
  // A true-type font will have ABC widths but others like raster type will not
  // so if the function fails then use TextMetric.tmAveCharWidth.
	GetTextMetrics(DC, &TM);
	HasABC = GetCharABCWidths(DC, (UINT) int(L'M'), (UINT) int(L'M'), &ABC);
	if(!HasABC)
	{
		/*# with ABC do */
		{
			auto& with0 = ABC;
			with0.abcA = 0;
			with0.abcB = TM.tmAveCharWidth;
			with0.abcC = 0;
		}
		TM.tmOverhang = 0;
	}

  // Result(CharWidth)
	/*# with ABC do */
	{
		auto& with1 = ABC;
		result = with1.abcA + ((int) with1.abcB) + with1.abcC + TM.tmOverhang;
	}
  // pCharHeight
	if(ASSIGNED(pCharHeight)) /*+ TM.tmInternalLeading*/
		(*pCharHeight) = Abs(TM.tmHeight);
	return result;
}

__fastcall TheFontStock::TheFontStock(TFont* InitialFont)
 : FDC(0),
			FDCRefCount(0),
			FpInfo(nullptr),
			FUsingFontHandles(false),
			FCrntFont(0),
			FpCrntFontData(nullptr)
{
	//# inherited::Create();
	SetBaseFont(InitialFont);
}

__fastcall TheFontStock::~TheFontStock()
{
	ReleaseFontsInfo();
	Assert(FDCRefCount == 0);
	// inherited;
}

TFont* __fastcall TheFontStock::GetBaseFont()
{
	TFont* result = nullptr;
	result = (*FpInfo).BaseFont;
	return result;
}

int __fastcall TheFontStock::GetCharAdvance()
{
	int result = 0;
	result = (*FpCrntFontData).CharAdv;
	return result;
}

int __fastcall TheFontStock::GetCharHeight()
{
	int result = 0;
	result = (*FpCrntFontData).CharHeight;
	return result;
}

PheFontData __fastcall TheFontStock::GetFontData(int idx)
{
	PheFontData result = nullptr;
	result = &(*FpInfo).FontsData[idx];
	return result;
}

bool __fastcall TheFontStock::GetIsTrueType()
{
	bool result = false;
	result = (*FpInfo).IsTrueType;
	return result;
}

HFONT __fastcall TheFontStock::InternalCreateFont(TFontStyles Style)
{
	HFONT result = 0;
	const int Bolds[2/*# boolean*/] = {400, 700};
	/*# with FBaseLF do */
	{
		auto& with0 = FBaseLF;
		with0.lfWeight = Bolds[Style.Contains(TFontStyle::fsBold)];
		with0.lfItalic = (Byte) int(((BOOL) Style.Contains(TFontStyle::fsItalic)));
		with0.lfUnderline = (Byte) int(((BOOL) Style.Contains(TFontStyle::fsUnderline)));
		with0.lfStrikeOut = (Byte) int(((BOOL) Style.Contains(TFontStyle::fsStrikeOut)));
	}
	result = CreateFontIndirect(FBaseLF);
	return result;
}

HDC __fastcall TheFontStock::InternalGetDC()
{
	HDC result = 0;
	if(FDCRefCount == 0)
	{
		Assert(FDC == 0);
		FDC = GetDC(0);
	}
	++FDCRefCount;
	result = FDC;
	return result;
}

void __fastcall TheFontStock::InternalReleaseDC(HDC Value)
{
	--FDCRefCount;
	if(FDCRefCount <= 0)
	{
		Assert((FDC != 0) && (FDC == Value));
		ReleaseDC(0, FDC);
		FDC = 0;
		Assert(FDCRefCount == 0);
	}
}

void __fastcall TheFontStock::ReleaseFontHandles()
{
	if(FUsingFontHandles)
		/*# with GetFontsInfoManager do */
		{
			auto with0 = GetFontsInfoManager();
			with0->UnLockFontsInfo(FpInfo);
			FUsingFontHandles = false;
		}
}

void __fastcall TheFontStock::ReleaseFontsInfo()
{
	if(ASSIGNED(FpInfo))
		/*# with GetFontsInfoManager do */
		{
			auto with0 = GetFontsInfoManager();
			if(FUsingFontHandles)
			{
				with0->UnLockFontsInfo(FpInfo);
				FUsingFontHandles = false;
			}
			with0->ReleaseFontsInfo(FpInfo);
			FpInfo = nullptr;
		}
}

void __fastcall TheFontStock::SetBaseFont(TFont* Value)
{
	PheSharedFontsInfo pInfo = nullptr;
	if(ASSIGNED(Value))
	{
		pInfo = GetFontsInfoManager()->GetFontsInfo(Value);
		if(pInfo == FpInfo)
			GetFontsInfoManager()->ReleaseFontsInfo(pInfo);
		else
		{
			ReleaseFontsInfo();
			FpInfo = pInfo;
			FBaseLF = (*FpInfo).BaseLF;
			SetStyle(Value->Style);
		}
	}
	else
	throw new EheFontStockException(L"SetBaseFont: 'Value' must be specified.");
}

void __fastcall TheFontStock::SetStyle(TFontStyles Value)
{
	int idx = 0;
	HDC DC = 0;
	HFONT hOldFont = 0;
	PheFontData p = nullptr;
	Assert(sizeof(TFontStyles) == 1);
	idx = (int) ToByte(Value);
	Assert(idx <= FontStyleCombineCount - 1 /*# High(TheStockFontPatterns) */);
	UseFontHandles();
	p = FontData[idx];
	if(FpCrntFontData == p)
		return;
	FpCrntFontData = p;
	/*# with p^ do */
	{
		auto& with0 = (*p);
		if(with0.Handle != 0)
		{
			FCrntFont = with0.Handle;
			FCrntStyle = with0.Style;
			return;
		}
	}

  // create font
	FCrntFont = InternalCreateFont(Value);
	DC = InternalGetDC();
	hOldFont = (HFONT) SelectObject(DC, FCrntFont);

  // retrieve height and advances of new font
	/*# with FpCrntFontData^ do */
	{
		auto& with1 = (*FpCrntFontData);
		with1.Handle = FCrntFont;
		with1.CharAdv = CalcFontAdvance(DC, &with1.CharHeight);
	}
	SelectObject(DC, hOldFont);
	InternalReleaseDC(DC);
}

void __fastcall TheFontStock::UseFontHandles()
{
	if(!FUsingFontHandles)
		/*# with GetFontsInfoManager do */
		{
			auto with0 = GetFontsInfoManager();
			with0->LockFontsInfo(FpInfo);
			FUsingFontHandles = true;
		}
}

/* TheTextDrawer */

__fastcall TheTextDrawer::TheTextDrawer(TFontStyles CalcExtentBaseStyle, TFont* BaseFont)
 : FDC(0),
			FSaveDC(0),
			FFontStock(nullptr),
			FStockBitmap(nullptr),
			FBaseCharWidth(0),
			FBaseCharHeight(0),
			FCrntFont(0),
			FETODist(nullptr),
			FColor((TColor) 0),
			FBkColor((TColor) 0),
			FCharExtra(0),
			FDrawingCount(0)
{
	//# inherited::Create();
	FFontStock = new TheFontStock(BaseFont);
	FStockBitmap = new TBitmap();
	FCalcExtentBaseStyle = CalcExtentBaseStyle;
	SetBaseFont(BaseFont);
	FColor = clWindowText;
	FBkColor = clWindow;
}

__fastcall TheTextDrawer::~TheTextDrawer()
{
	delete FStockBitmap;
	delete FFontStock;
	ReleaseETODist();
	// inherited;
}

void __fastcall TheTextDrawer::ReleaseETODist()
{
	if(ASSIGNED(FETODist))
	{
		FreeMemory(FETODist);
		FETODist = nullptr;
	}
}

void __fastcall TheTextDrawer::BeginDrawing(HDC DC)
{
	if(FDC == DC)
		Assert(FDC != 0);
	else
	{
		Assert((FDC == 0) && (DC != 0) && (FDrawingCount == 0));
		FDC = DC;
		FSaveDC = SaveDC(DC);
		SelectObject(DC, FCrntFont);
		::SetTextColor(DC, ColorToRGB(FColor));
		::SetBkColor(DC, ColorToRGB(FBkColor));
		DoSetCharExtra(FCharExtra);
	}
	++FDrawingCount;
}

void __fastcall TheTextDrawer::EndDrawing()
{
	Assert(FDrawingCount >= 1);
	--FDrawingCount;
	if(FDrawingCount <= 0)
	{
		if(FDC != 0)
			RestoreDC(FDC, FSaveDC);
		FSaveDC = 0;
		FDC = 0;
		FDrawingCount = 0;
	}
}

int __fastcall TheTextDrawer::GetCharWidth()
{
	int result = 0;
	result = FBaseCharWidth + FCharExtra;
	return result;
}

int __fastcall TheTextDrawer::GetCharHeight()
{
	int result = 0;
	result = FBaseCharHeight;
	return result;
}

void __fastcall TheTextDrawer::SetBaseFont(TFont* Value)
{
	if(ASSIGNED(Value))
	{
		FlushCharABCWidthCache();
		ReleaseETODist();
		FStockBitmap->Canvas->Font->Assign(Value);
		FStockBitmap->Canvas->Font->Style = Syntextdrawer__0;
		/*# with FFontStock do */
		{
			auto with0 = FFontStock;
			with0->SetBaseFont(Value);
			with0->Style = FCalcExtentBaseStyle;
			FBaseCharWidth = with0->CharAdvance;
			FBaseCharHeight = with0->CharHeight;
		}
		SetStyle(Value->Style);
	}
	else
	throw new EheTextDrawerException(L"SetBaseFont: 'Value' must be specified.");
}

void __fastcall TheTextDrawer::SetBaseStyle(const TFontStyles Value)
{
	if(FCalcExtentBaseStyle != Value)
	{
		FCalcExtentBaseStyle = Value;
		FlushCharABCWidthCache();
		ReleaseETODist();
		/*# with FFontStock do */
		{
			auto with0 = FFontStock;
			with0->Style = Value;
			FBaseCharWidth = with0->CharAdvance;
			FBaseCharHeight = with0->CharHeight;
		}
	}
}

void __fastcall TheTextDrawer::SetStyle(TFontStyles Value)
{
	/*# with FFontStock do */
	{
		auto with0 = FFontStock;
		with0->SetStyle(Value);
		this->FCrntFont = with0->FontHandle;
	}
	AfterStyleSet();
}

void __fastcall TheTextDrawer::AfterStyleSet()
{
	if(FDC != 0)
		SelectObject(FDC, FCrntFont);
}

void __fastcall TheTextDrawer::SetForeColor(TColor Value)
{
	if(FColor != Value)
	{
		FColor = Value;
		if(FDC != 0)
			SetTextColor(FDC, ColorToRGB(Value));
	}
}

void __fastcall TheTextDrawer::SetBackColor(TColor Value)
{
	if(FBkColor != Value)
	{
		FBkColor = Value;
		if(FDC != 0)
			::SetBkColor(FDC, ColorToRGB(Value));
	}
}

void __fastcall TheTextDrawer::SetCharExtra(int Value)
{
	if(FCharExtra != Value)
	{
		FCharExtra = Value;
		DoSetCharExtra(FCharExtra);
	}
}

void __fastcall TheTextDrawer::DoSetCharExtra(int Value)
{
	if(FDC != 0)
		SetTextCharacterExtra(FDC, Value);
}

void __fastcall TheTextDrawer::FlushCharABCWidthCache()
{
	FillChar((void**)&FCharABCWidthCache, (int) (sizeof(TABC) * (MAXIDX(FCharABCWidthCache) + 1)), 0);
	FillChar((void**)&FCharWidthCache, (int) (sizeof(int) * (MAXIDX(FCharWidthCache) + 1)), 0);
}

bool __fastcall TheTextDrawer::GetCachedABCWidth(unsigned int c, TABC& abc)
{
	bool result = false;
	if(c > 127 /*# High(FCharABCWidthCache) */)
	{
		result = GetCharABCWidthsW(FDC, c, c, &abc);
		return result;
	}
	abc = FCharABCWidthCache[c];
	if((abc.abcA | ((int) abc.abcB) | abc.abcC) == 0)
	{
		result = GetCharABCWidthsW(FDC, c, c, &abc);
		if(result)
			FCharABCWidthCache[c] = abc;
	}
	else
	result = true;
	return result;
}

void __fastcall TheTextDrawer::TextOut(int X, int Y, PWideChar Text, int Length)
{
	TRect r = {};
	r = Rect(X, Y, X, Y);
	UniversalExtTextOut(FDC, X, Y, Syntextdrawer__1, r, Text, Length, nullptr);
}

void __fastcall TheTextDrawer::ExtTextOut(int X, int Y, TTextOutOptions Options, const TRect& cARect, PWideChar Text, int Length, bool UseLigatures/*# = false*/)
{
	TRect ARect = cARect;

	auto InitETODist = [&](int CharWidth) -> void 
	{
		TSize Size = {};
		int i = 0;
		int stop = 0;
		FETODist = (PIntegerArray) ReallocMemory(FETODist, Length * sizeof(int));
		for(stop = Length - 1, i = 0; i <= stop; i++)
		{
			Size = TextExtent(&Text[i], 1);
			if(Size.cx != CharWidth)
				(*FETODist)[i] = Ceil(double(Size.cx) / CharWidth) * CharWidth;
			else
				(*FETODist)[i] = CharWidth;
		}
	};

	auto AdjustLastCharWidthAndRect = [&]() -> void 
	{
		unsigned int LastChar = 0;
		int RealCharWidth = 0;
		int CharWidth = 0;
		TABC CharInfo = {};
		TTextMetricA tm = {};
		if(Length <= 0)
			return;
		LastChar = (unsigned int) int(Text[Length - 1]);
		CharWidth = (*FETODist)[Length - 1];
		RealCharWidth = CharWidth;
		if(GetCachedABCWidth(LastChar, CharInfo))
		{
			RealCharWidth = CharInfo.abcA + ((int) CharInfo.abcB);
			if(CharInfo.abcC >= 0)
				RealCharWidth += CharInfo.abcC;
		}
		else
		{
			if(LastChar < int(High<AnsiChar>()))
			{
				GetTextMetricsA(FDC, &tm);
				RealCharWidth = tm.tmAveCharWidth + tm.tmOverhang;
			}
		}
		if(RealCharWidth > CharWidth)
			ARect.Right += RealCharWidth - CharWidth;
		(*FETODist)[Length - 1] = Max(RealCharWidth, CharWidth);
	};
	InitETODist(GetCharWidth());
	AdjustLastCharWidthAndRect();
	UniversalExtTextOut(FDC, X, Y, Options, ARect, Text, Length, FETODist, UseLigatures);
}

void __fastcall TheTextDrawer::ReleaseTemporaryResources()
{
	FFontStock->ReleaseFontHandles();
}

TSize __fastcall TheTextDrawer::TextExtent(const String Text)
{
	TSize result = {};
	result = FStockBitmap->Canvas->TextExtent(Text);
	return result;
}

TSize __fastcall TheTextDrawer::TextExtent(PWideChar Text, int Count)
{
	TSize result = {};
	result = Synunicode::GetTextSize(FStockBitmap->Canvas->Handle, Text, Count);
	return result;
}

int __fastcall TheTextDrawer::TextWidth(const String Text)
{
	int result = 0;
	unsigned int c = 0;
	if(Text.Length() == 1)
	{
		c = (unsigned int) int(Text[1]);
		if(c <= 127 /*# High(FCharWidthCache) */)
		{
			result = FCharWidthCache[c];
			if(result == 0)
			{
				result = FStockBitmap->Canvas->TextExtent(Text).cx;
				FCharWidthCache[c] = result;
			}
			return result;
		}
	}
	result = FStockBitmap->Canvas->TextExtent(Text).cx;
	return result;
}

int __fastcall TheTextDrawer::TextWidth(PWideChar Text, int Count)
{
	int result = 0;
	result = Synunicode::GetTextSize(FStockBitmap->Canvas->Handle, Text, Count).cx;
	return result;
}
	static bool SynTextDrawer_Finalized = false;
	
	void SynTextDrawer_finalization()
	{
		if(SynTextDrawer_Finalized)
			return;
		
		SynTextDrawer_Finalized = true;
		
		delete gFontsInfoManager;
	}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynTextDrawer

