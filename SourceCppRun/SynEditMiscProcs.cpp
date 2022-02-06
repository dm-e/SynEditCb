#include <vcl.h>
#pragma hdrstop

#include "SynEditMiscProcs.h"
#include <System.SysUtils.hpp>
#include "SynHighlighterMulti.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Synedittypes;
using namespace Synhighlightermulti;
using namespace System;
using namespace System::Classes;
using namespace System::Math;
using namespace System::Sysutils;
using namespace Vcl::Graphics;

namespace Syneditmiscprocs
{
#define SynEditMiscProcs__0 (System::Set<WORD, 0, 255>() << 0 << 10 << 13)
#define SynEditMiscProcs__1 (System::Set<WORD, 0, 255>() << 10 << 13)
#define SynEditMiscProcs__2 (System::Set<WORD, 0, 255>() << 10 << 13)
#define SynEditMiscProcs__3 (System::Set<WORD, 0, 255>() << 10 << 13)
#define SynEditMiscProcs__4 (TSysCharSet() << L'T' << L't')



int __fastcall MinMax(int X, int mi, int ma)
{
	int result = 0;
	X = Min(X, ma);
	result = Max(X, mi);
	return result;
}

void __fastcall SwapInt(int& l, int& R)
{
	int Tmp = 0;
	Tmp = R;
	R = l;
	l = Tmp;
}

void __fastcall InternalFillRect(HDC DC, const TRect& rcPaint)
{
	ExtTextOut(DC, 0, 0, ETO_OPAQUE, const_cast<PRect>(&rcPaint), nullptr, 0, nullptr);
}

// Please don't change this function; no stack frame and efficient register use.

bool __fastcall GetHasTabs(PWideChar pLine, int& CharsBefore)
{
	bool result = false;
	CharsBefore = 0;
	if(ASSIGNED(pLine))
	{
		while((*pLine) != L'\x00')
		{
			if((*pLine) == L'\x09')
				break;
			++CharsBefore;
			++pLine;
		}
		result = (*pLine) == L'\x09';
	}
	else
	result = false;
	return result;
}

String __fastcall ConvertTabs1Ex(const String Line, int TabWidth, bool& HasTabs)
{
	String result;
	PWideChar PDest = nullptr;
	int nBeforeTab = 0;
	result = Line; // increment reference count only
	if(GetHasTabs(ustr2pwchar(Line), nBeforeTab))
	{
		HasTabs = true;
		PDest = ustr2pwchar(result, nBeforeTab + 1 - 1); // this will make a copy of Line
    // We have at least one tab in the string, and the tab width is 1.
    // pDest points to the first tab char. We overwrite all tabs with spaces.
		do
		{
			if((*PDest) == L'\x09')
				(*PDest) = L' ';
			++PDest;
		}
		while(!((*PDest) == L'\x00'));
	}
	else
	HasTabs = false;
	return result;
}

String __fastcall ConvertTabs1(const String Line, int TabWidth)
{
	String result;
	bool HasTabs = false;
	result = ConvertTabs1Ex(Line, TabWidth, HasTabs);
	return result;
}

String __fastcall ConvertTabs2nEx(const String Line, int TabWidth, bool& HasTabs)
{
	String result;
	int i = 0;
	int DestLen = 0;
	int TabCount = 0;
	int TabMask = 0;
	PWideChar PSrc = nullptr;
	PWideChar PDest = nullptr;
	result = Line; // increment reference count only
	if(GetHasTabs(ustr2pwchar(Line), DestLen))
	{
		HasTabs = true;
		PSrc = ustr2pwchar(Line, 1 + DestLen - 1);
    // We have at least one tab in the string, and the tab width equals 2^n.
    // pSrc points to the first tab char in Line. We get the number of tabs
    // and the length of the expanded string now.
		TabCount = 0;
		TabMask = (TabWidth - 1) ^ 0x7FFFFFFF;
		do
		{
			if((*PSrc) == L'\x09')
			{
				DestLen = (DestLen + TabWidth) & TabMask;
				++TabCount;
			}
			else
			++DestLen;
			++PSrc;
		}
		while(!((*PSrc) == L'\x00'));
    // Set the length of the expanded string.
		result.SetLength(DestLen);
		DestLen = 0;
		PSrc = ustr2pwchar(Line);
		PDest = ustr2pwchar(result);
    // We use another TabMask here to get the difference to 2^n.
		TabMask = TabWidth - 1;
		do
		{
			if((*PSrc) == L'\x09')
			{
				i = TabWidth - (DestLen & TabMask);
				DestLen += i;
        // This is used for both drawing and other stuff and is meant to be #9 and not #32
				do
				{
					(*PDest) = L'\x09';
					++PDest;
					--i;
				}
				while(!(i == 0));
				--TabCount;
				if(TabCount == 0)
				{
					do
					{
						++PSrc;
						(*PDest) = (*PSrc);
						++PDest;
					}
					while(!((*PSrc) == L'\x00'));
					return result;
				}
			}
			else
			{
				(*PDest) = (*PSrc);
				++PDest;
				++DestLen;
			}
			++PSrc;
		}
		while(!((*PSrc) == L'\x00'));
	}
	else
	HasTabs = false;
	return result;
}

String __fastcall ConvertTabs2n(const String Line, int TabWidth)
{
	String result;
	bool HasTabs = false;
	result = ConvertTabs2nEx(Line, TabWidth, HasTabs);
	return result;
}

String __fastcall ConvertTabsEx(const String Line, int TabWidth, bool& HasTabs)
{
	String result;
	int i = 0;
	int DestLen = 0;
	int TabCount = 0;
	PWideChar PSrc = nullptr;
	PWideChar PDest = nullptr;
	result = Line; // increment reference count only
	if(GetHasTabs(ustr2pwchar(Line), DestLen))
	{
		HasTabs = true;
		PSrc = ustr2pwchar(Line, 1 + DestLen - 1);
    // We have at least one tab in the string, and the tab width is greater
    // than 1. pSrc points to the first tab char in Line. We get the number
    // of tabs and the length of the expanded string now.
		TabCount = 0;
		do
		{
			if((*PSrc) == L'\x09')
			{
				DestLen = DestLen + TabWidth - DestLen % TabWidth;
				++TabCount;
			}
			else
			++DestLen;
			++PSrc;
		}
		while(!((*PSrc) == L'\x00'));
    // Set the length of the expanded string.
		result.SetLength(DestLen);
		DestLen = 0;
		PSrc = ustr2pwchar(Line);
		PDest = ustr2pwchar(result);
		do
		{
			if((*PSrc) == L'\x09')
			{
				i = TabWidth - (DestLen % TabWidth);
				DestLen += i;
				do
				{
					(*PDest) = L'\x09';
					++PDest;
					--i;
				}
				while(!(i == 0));
				--TabCount;
				if(TabCount == 0)
				{
					do
					{
						++PSrc;
						(*PDest) = (*PSrc);
						++PDest;
					}
					while(!((*PSrc) == L'\x00'));
					return result;
				}
			}
			else
			{
				(*PDest) = (*PSrc);
				++PDest;
				++DestLen;
			}
			++PSrc;
		}
		while(!((*PSrc) == L'\x00'));
	}
	else
	HasTabs = false;
	return result;
}

String __fastcall ConvertTabs(const String Line, int TabWidth)
{
	String result;
	bool HasTabs = false;
	result = ConvertTabsEx(Line, TabWidth, HasTabs);
	return result;
}

bool __fastcall IsPowerOfTwo(int TabWidth)
{
	bool result = false;
	int nW = 0;
	nW = 2;
	do
	{
		if(nW >= TabWidth)
			break;
		nW += nW;
	}
	while(!(nW >= 0x10000)); // we don't want 64 kByte spaces...
	result = (nW == TabWidth);
	return result;
}

TConvertTabsProc __fastcall GetBestConvertTabsProc(int TabWidth)
{
	TConvertTabsProc result;
	if(TabWidth < 2)
		result = TConvertTabsProc(ConvertTabs1);
	else
	{
		if(IsPowerOfTwo(TabWidth))
			result = TConvertTabsProc(ConvertTabs2n);
		else
			result = TConvertTabsProc(ConvertTabs);
	}
	return result;
}

TConvertTabsProcEx __fastcall GetBestConvertTabsProcEx(int TabWidth)
{
	TConvertTabsProcEx result;
	if(TabWidth < 2)
		result = ConvertTabs1Ex;
	else
	{
		if(IsPowerOfTwo(TabWidth))
			result = ConvertTabs2nEx;
		else
			result = ConvertTabsEx;
	}
	return result;
}

int __fastcall GetExpandedLength(const String AStr, int aTabWidth)
{
	int result = 0;
	PWideChar iRun = nullptr;
	result = 0;
	iRun = ustr2pwchar(AStr);
	while((*iRun) != L'\x00')
	{
		if((*iRun) == L'\x09')
			result += aTabWidth - (result % aTabWidth);
		else
			++result;
		++iRun;
	}
	return result;
}

int __fastcall CharIndex2CaretPos(int Index, int TabWidth, const String Line)
{
	int result = 0;
	int iChar = 0;
	PWideChar pNext = nullptr;
  // possible sanity check here: Index := Max(Index, Length(Line));
	if(Index > 1)
	{
		if((TabWidth <= 1) || !GetHasTabs(ustr2pwchar(Line), iChar))
			result = Index;
		else
		{
			if(iChar + 1 >= Index)
				result = Index;
			else

        // iChar is number of chars before first #9
			{
				result = iChar;
        // Index is *not* zero-based
				++iChar;
				Index -= iChar;
				pNext = ustr2pwchar(Line, iChar - 1);
				while(Index > 0)
				{
					switch((*pNext))
					{
						case L'\x00':
						{
							result += Index;
							goto label0;
						}
                // Result is still zero-based
						case L'\x09':
						{
							result += TabWidth;
							result -= result % TabWidth;
						}
						break;
						default:
						++result;
						break;
					}
					--Index;
					++pNext;
				}
        // done with zero-based computation
				label0:;
				++result;
			}
		}
	}
	else
	result = 1;
	return result;
}

int __fastcall CaretPos2CharIndex(int Position, int TabWidth, const String Line, bool& InsideTabChar)
{
	int result = 0;
	int iPos = 0;
	PWideChar pNext = nullptr;
	InsideTabChar = false;
	if(Position > 1)
	{
		if((TabWidth <= 1) || !GetHasTabs(ustr2pwchar(Line), iPos))
			result = Position;
		else
		{
			if(iPos + 1 >= Position)
				result = Position;
			else

        // iPos is number of chars before first #9
			{
				result = iPos + 1;
				pNext = ustr2pwchar(Line, result - 1);
        // for easier computation go zero-based (mod-operation)
				--Position;
				while(iPos < Position)
				{
					switch((*pNext))
					{
						case L'\x00':
						goto label1;
						case L'\x09':
						{
							iPos += TabWidth;
							iPos -= iPos % TabWidth;
							if(iPos > Position)
							{
								InsideTabChar = true;
								goto label2;
							}
						}
						break;
						default:
						++iPos;
						break;
					}
					++result;
					++pNext;
				}
				label1:;
				label2:;
			}
		}
	}
	else
	result = Position;
	return result;
}

int __fastcall StrScanForCharInCategory(const String Line, int Start, TCategoryMethod IsOfCategory)
{
	int result = 0;
	PWideChar P = nullptr;
	if((Start > 0) && (Start <= Line.Length()))
	{
		P = ustr2pwchar(Line, Start - 1);
		do
		{
			if(IsOfCategory((*P)))
			{
				result = Start;
				return result;
			}
			++P;
			++Start;
		}
		while(!((*P) == L'\x00'));
	}
	result = 0;
	return result;
}

int __fastcall StrRScanForCharInCategory(const String Line, int Start, TCategoryMethod IsOfCategory)
{
	int result = 0;
	int i = 0;
	result = 0;
	if((Start > 0) && (Start <= Line.Length()))
	{
		int stop = 0;
		for(stop = 1, i = Start; i >= stop; i--)
		{
			if(IsOfCategory(Line[i]))
			{
				result = i;
				return result;
			}
		}
	}
	return result;
}

PWideChar __fastcall GetEol(PChar P)
{
	PWideChar result = nullptr;
	result = P;
	if(ASSIGNED(result))
	{
//		while(((*result) != L'\x00') && ((*result) != L'\x0a') && ((*result) != L'\x0d'))
		while((((WORD) (*result)) > 13) || !(SynEditMiscProcs__0.Contains(((WORD) (*result)))))
			++result;
	}
	return result;
}

int __fastcall CountLines(const String s)
{
	int result = 0;
	PChar P = nullptr;
	PChar PEnd = nullptr;
	result = 0;
	P = ustr2pwchar(s);
	PEnd = P + s.Length();
	while(P < PEnd)

    //  We do it that way instead of checking for $0 as well
    //  so the we properly deal with strings containing #0  (who knows)
	{
		while((P < PEnd) && ((((WORD) (*P)) > 13) || !(SynEditMiscProcs__1.Contains(((WORD) (*P))))))
			++P;
		++result;
		if((*P) == L'\x0d')
			++P;
		if((*P) == L'\x0a')
			++P;
	}
  // Include Empty line at the end?
	if((s != L"") && (SynEditMiscProcs__2.Contains(((WORD) s[s.Length()]))))
		++result;
	return result;
}
// At least one line possibly empty

TArray<String> __fastcall StringToLines(const String Value)
{
	TArray<String> result;
	int Count = 0;
	PChar P = nullptr;
	PChar pStart = nullptr;
	PChar PEnd = nullptr;
	String s;
	P = ustr2pwchar(Value);
	Count = CountLines(Value);
	result.Length = Count;
	Count = 0;
	PEnd = P + Value.Length();
	while(P < PEnd)
	{
		pStart = P;
    //  We do it that way instead of checking for $0 as well
    //  so the we properly deal with strings containing #0  (who knows)
		while((P < PEnd) && ((((WORD) (*P)) > 13) || !(SynEditMiscProcs__3.Contains(((WORD) (*P))))))
			++P;
		SetString(s, pStart, P - pStart);
		result[Count] = s;
		++Count;
		if((*P) == L'\x0d')
			++P;
		if((*P) == L'\x0a')
			++P;
	}
	return result;
}
//#pragma resource "-"


String __fastcall EncodeString(String s)
{
	String result;
	int i = 0;
	int j = 0;
	int stop = 0;
	result.SetLength((int) (2 * s.Length())); // worst case
	j = 0;
	for(stop = (int) s.Length(), i = 1; i <= stop; i++)
	{
		++j;
		if(s[i] == L'\\')
		{
			result[j] = L'\\';
			result[j + 1] = L'\\';
			++j;
		}
		else
		{
			if(s[i] == L'/')
			{
				result[j] = L'\\';
				result[j + 1] = L'.';
				++j;
			}
			else
			result[j] = s[i];
		}
	} // for
	result.SetLength(j);
	return result;
} /* EncodeString */

String __fastcall DecodeString(String s)
{
	String result;
	int i = 0;
	int j = 0;
	result.SetLength((int) s.Length()); // worst case
	j = 0;
	i = 1;
	while(i <= s.Length())
	{
		++j;
		if(s[i] == L'\\')
		{
			++i;
			if(s[i] == L'\\')
				result[j] = L'\\';
			else
				result[j] = L'/';
		}
		else
		result[j] = s[i];
		++i;
	} // for
	result.SetLength(j);
	return result;
} /* DecodeString */

String __fastcall DeleteTypePrefixAndSynSuffix(String s)
{
	String result;
	result = s;
	if(CharInSet(result[1], SynEditMiscProcs__4))
	{
		if(Pos(L"tsyn", LowerCase(result)) == 1)
  // ClassName is never empty so no AV possible
			result.Delete(1, 	4);
		else
			result.Delete(1, 	1);
	}
	if(LowerCase(result).SubString(result.Length() - 2, 3) == L"syn")
		result.SetLength((int) (result.Length() - 3));
	return result;
}

int __fastcall GetHighlighterIndex(TSynCustomHighlighter* Highlighter, TList* HighlighterList)
{
	int result = 0;
	int i = 0;
	int stop = 0;
	result = 1;
	for(stop = HighlighterList->Count - 1, i = 0; i <= stop; i++)
	{
		if(HighlighterList->Items[i] == Highlighter)
			return result;
		else
		{
			if(ASSIGNED(HighlighterList->Items[i]) && (((TObject*)HighlighterList->Items[i])->ClassType() == Highlighter->ClassType()))
				++result;
		}
	}
	return result;
}

bool __fastcall InternalEnumHighlighterAttris(TSynCustomHighlighter* Highlighter, bool SkipDuplicates, THighlighterAttriProc HighlighterAttriProc, void** Params, int Params_maxidx, TList* HighlighterList)
{
	bool result = false;
	int i = 0;
	String UniqueAttriName;
	result = true;
	if(HighlighterList->IndexOf(Highlighter) >= 0)
	{
		if(SkipDuplicates)
			return result;
	}
	else
	HighlighterList->Add(Highlighter);
	if(ObjectIs(Highlighter, TSynMultiSyn*))
		/*# with TSynMultiSyn(Highlighter) do */
		{
			auto with0 = ((TSynMultiSyn*) Highlighter);
			int stop = 0;
			result = InternalEnumHighlighterAttris(with0->DefaultHighlighter, SkipDuplicates, HighlighterAttriProc, Params, Params_maxidx, HighlighterList);
			if(!result)
				return result;
			for(stop = with0->Schemes->Count - 1, i = 0; i <= stop; i++)
			{
				UniqueAttriName = Highlighter->ExportName
	           + IntToStr(GetHighlighterIndex(Highlighter, HighlighterList))
	           + L"."
	           + with0->Schemes->Items[i]->MarkerAttri->Name
	           + IntToStr(i + 1);
				result = HighlighterAttriProc(Highlighter, with0->Schemes->Items[i]->MarkerAttri, UniqueAttriName, Params, Params_maxidx);
				if(!result)
					return result;
				result = InternalEnumHighlighterAttris(with0->Schemes->Items[i]->Highlighter, SkipDuplicates, HighlighterAttriProc, Params, Params_maxidx, HighlighterList);
				if(!result)
					return result;
			}
		}
	else
	{
		if(ASSIGNED(Highlighter))
		{
			int stop = 0;
			for(stop = Highlighter->AttrCount - 1, i = 0; i <= stop; i++)
			{
				UniqueAttriName = Highlighter->ExportName
	           + IntToStr(GetHighlighterIndex(Highlighter, HighlighterList))
	           + L"."
	           + Highlighter->Attribute[i]->Name;
				result = HighlighterAttriProc(Highlighter, Highlighter->Attribute[i], UniqueAttriName, Params, Params_maxidx);
				if(!result)
					return result;
			}
		}
	}
	return result;
}

bool __fastcall EnumHighlighterAttris(TSynCustomHighlighter* Highlighter, bool SkipDuplicates, THighlighterAttriProc HighlighterAttriProc, void** Params, int Params_maxidx)
{
	bool result = false;
	TList* HighlighterList = nullptr;
	if(!ASSIGNED(Highlighter) || !ASSIGNED(HighlighterAttriProc))
	{
		result = false;
		return result;
	}
	HighlighterList = new TList();
	try
	{
		result = InternalEnumHighlighterAttris(Highlighter, SkipDuplicates, HighlighterAttriProc, Params, Params_maxidx, HighlighterList);
	}
	__finally
	{
		delete HighlighterList;
	}
	return result;
}

void __fastcall SynDrawGradient(TCanvas* const ACanvas, const TColor AStartColor, const TColor AEndColor, int ASteps, const TRect& ARect, bool AHorizontal)
{
	unsigned char StartColorR = 0;
	unsigned char StartColorG = 0;
	unsigned char StartColorB = 0;
	int DiffColorR = 0;
	int DiffColorG = 0;
	int DiffColorB = 0;
	int i = 0;
	int Size = 0;
	TRect PaintRect = {};
	StartColorR = GetRValue(ColorToRGB(AStartColor));
	StartColorG = GetGValue(ColorToRGB(AStartColor));
	StartColorB = GetBValue(ColorToRGB(AStartColor));
	DiffColorR = (int) (GetRValue(ColorToRGB(AEndColor)) - StartColorR);
	DiffColorG = (int) (GetGValue(ColorToRGB(AEndColor)) - StartColorG);
	DiffColorB = (int) (GetBValue(ColorToRGB(AEndColor)) - StartColorB);
	ASteps = MinMax(ASteps, 2, 256);
	if(AHorizontal)
	{
		int stop = 0;
		Size = ARect.Right - ARect.Left;
		PaintRect.Top = ARect.Top;
		PaintRect.Bottom = ARect.Bottom;
		for(stop = ASteps - 1, i = 0; i <= stop; i++)
		{
			PaintRect.Left = ARect.Left + MulDiv(i, Size, ASteps);
			PaintRect.Right = ARect.Left + MulDiv(i + 1, Size, ASteps);
			ACanvas->Brush->Color = (TColor) RGB(StartColorR + MulDiv(i, DiffColorR, ASteps - 1), StartColorG + MulDiv(i, DiffColorG, ASteps - 1), StartColorB + MulDiv(i, DiffColorB, ASteps - 1));
			ACanvas->FillRect(PaintRect);
		}
	}
	else
	{
		int stop = 0;
		Size = ARect.Bottom - ARect.Top;
		PaintRect.Left = ARect.Left;
		PaintRect.Right = ARect.Right;
		for(stop = ASteps - 1, i = 0; i <= stop; i++)
		{
			PaintRect.Top = ARect.Top + MulDiv(i, Size, ASteps);
			PaintRect.Bottom = ARect.Top + MulDiv(i + 1, Size, ASteps);
			ACanvas->Brush->Color = (TColor) RGB(StartColorR + MulDiv(i, DiffColorR, ASteps - 1), StartColorG + MulDiv(i, DiffColorG, ASteps - 1), StartColorB + MulDiv(i, DiffColorB, ASteps - 1));
			ACanvas->FillRect(PaintRect);
		}
	}
}

String __fastcall DefaultFontName()
{
	String result;
	if(CheckWin32Version(6))
		result = L"Consolas";
	else
		result = L"Courier New";
	return result;
}

int __fastcall GrowCollection(int OldCapacity, int NewCount)
{
	int result = 0;
	result = OldCapacity;
	do
	{
		if(result > 64)
			result = (int)((result * 3) / 2);
		else
		{
			if(result > 8)
				result = result + 16;
			else
				result = result + 4;
		}
		if(result < 0)
			OutOfMemoryError();
	}
	while(!(result >= NewCount));
	return result;
}


}  // namespace Syneditmiscprocs

