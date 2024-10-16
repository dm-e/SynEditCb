#include <vcl.h>
#pragma hdrstop

#include "SynEditPrintHeaderFooter.h"
#include <System.UITypes.hpp>
#include <System.Math.hpp>
#include "SynEditMiscProcs.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditmiscprocs;
using namespace Syneditprintmargins;
using namespace Syneditprinttypes;
using namespace System;
using namespace System::Classes;
using namespace System::Math;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Syneditprintheaderfooter
{
#define Syneditprintheaderfooter__0 (TFrameTypes() << ftLine)
#define Syneditprintheaderfooter__1 TFrameTypes()
#define Syneditprintheaderfooter__2 (TFrameTypes() << ftBox << ftShaded)
#define Syneditprintheaderfooter__3 TFrameTypes()

__fastcall TLineInfo::TLineInfo() {}



// Helper routine for AsString processing.

String __fastcall GetFirstEl(String& Value, WideChar Delim)
{
	String result;
	int p = 0;
	p = Pos(Delim, Value);
	if(p == 0)
		p = Value.Length() + 1;
	result = Value.SubString(1, p - 1);
	Value.Delete(1, 	p);
	return result;
}


/* THeaderFooterItem */

__fastcall THeaderFooterItem::THeaderFooterItem()
 : FFont(nullptr),
			FLineNumber(0),
			FAlignment(taLeftJustify),
			FIndex(0)
{
	// inherited;
	FFont = new TFont();
}

__fastcall THeaderFooterItem::~THeaderFooterItem()
{
	// inherited;
	delete FFont;
}

// Returns string representation of THeaderFooterItem to alleviate storing
// items into external storage (registry, ini file).

String __fastcall THeaderFooterItem::GetAsString()
{
	String result;
	result = EncodeString(FText)
	           + L"/"
	           + IntToStr(FFont->Charset)
	           + L"/"
	           + IntToStr(FFont->Color)
	           + L"/"
	           + IntToStr(FFont->Height)
	           + L"/"
	           + EncodeString(FFont->Name)
	           + L"/"
	           + IntToStr(int(FFont->Pitch))
	           + L"/"
	           + IntToStr(FFont->PixelsPerInch)
	           + L"/"
	           + IntToStr(FFont->Size)
	           + L"/"
	           + IntToStr((int) ToByte(FFont->Style))
	           + L"/"
	           + IntToStr(FLineNumber)
	           + L"/"
	           + IntToStr(int(FAlignment));
	return result;
}


/* This is basically copied from original SynEditPrint.pas. Returns the
  header/footer text with macros expanded */

String __fastcall THeaderFooterItem::GetText(int NumPages, int PageNum, bool Roman, String Title, String ATime, String ADate)
{
	String result;
	int Len = 0;
	int Start = 0;
	int Run = 0;
	String AStr;

	auto DoAppend = [&](String AText) -> void 
	{
		result = result + AText;
	};

	auto TryAppend = [&](int& First, int After) -> void 
	{
		if(After > First)
		{
			DoAppend(AStr.SubString(First, After - First));
			First = After;
		}
	};

	auto TryExecuteMacro = [&]() -> bool 
	{
		bool result = false;
		String Macro;
		result = true;
		Macro = Sysutils::AnsiUpperCase(FText.SubString(Start, Run - Start + 1));
		if(Macro == L"$PAGENUM$")
		{
			if(Roman)
				DoAppend(IntToRoman(PageNum));
			else
				DoAppend(IntToStr(PageNum));
			return result;
		}
		if(Macro == L"$PAGECOUNT$")
		{
			if(Roman)
				DoAppend(IntToRoman(NumPages));
			else
				DoAppend(IntToStr(NumPages));
			return result;
		}
		if(Macro == L"$TITLE$")
		{
			DoAppend(Title);
			return result;
		}
		if(Macro == L"$DATE$")
		{
			DoAppend(ADate);
			return result;
		}
		if(Macro == L"$TIME$")
		{
			DoAppend(ATime);
			return result;
		}
		if(Macro == L"$DATETIME$")
		{
			DoAppend(ADate + L" " + ATime);
			return result;
		}
		if(Macro == L"$TIMEDATE$")
		{
			DoAppend(ATime + L" " + ADate);
			return result;
		}
		result = false;
		return result;
	};
	result = L"";
	AStr = FText;
	if(Trim(AStr) == L"")
		return result;
  // parse the line
	Len = AStr.Length();
	if(Len > 0)
      // start with left-aligned text
	{
		Start = 1;
		Run = 1;
		while(Run <= Len)

          // test for embedded macro
		{
			if(AStr[Run] == L'$')
			{
				TryAppend(Start, Run);
				++Run;
          // search for next '$' which could mark the end of a macro
				while(Run <= Len)
				{
					if(AStr[Run] == L'$')
            // if this is a macro execute it and skip the chars from output
					{
						if(TryExecuteMacro())
						{
							++Run; // also the '$'
							Start = Run;
							break;
						}
						else

                // this '$' might again be the start of a macro
						{
							TryAppend(Start, Run);
							++Run;                                                         //ek 2001-08-02
						}
					}
					else
					++Run;
				}
			}
			else
			++Run;
		}
		TryAppend(Start, Run);
	}
	return result;
}

void __fastcall THeaderFooterItem::LoadFromStream(TStream* AStream)
{
	System::Uitypes::TFontCharset aCharset = (System::Uitypes::TFontCharset) 0;
	TColor aColor = (TColor) 0;
	int aHeight = 0;
	TFontName aName;
	TFontPitch aPitch = TFontPitch::fpDefault;
	int aSize = 0;
	TFontStyles aStyle;
	int Len = 0;
	int BufferSize = 0;
	void* Buffer = nullptr;
	/*# with AStream do */
	{
		auto with0 = AStream;
		with0->Read((void**)&Len, (NativeInt) sizeof(Len));
		BufferSize = (int) (Len * sizeof(WideChar));
		Buffer = (void*) GetMemory(BufferSize + sizeof(WideChar));
		try
		{
			with0->Read((void**) Buffer, BufferSize);
			((PWideChar) Buffer)[(unsigned __int64)(BufferSize / /*div*/ sizeof(WideChar))] = L'\x00';
			FText = (wchar_t*) Buffer /*# check length*/;
		}
		__finally
		{
			FreeMemory(Buffer);
		}
		with0->Read((void**)&FLineNumber, (NativeInt) sizeof(FLineNumber));
    // font
		with0->Read((void**)&aCharset, (NativeInt) sizeof(aCharset));
		with0->Read((void**)&aColor, (NativeInt) sizeof(aColor));
		with0->Read((void**)&aHeight, (NativeInt) sizeof(aHeight));
		with0->Read((void**)&BufferSize, (NativeInt) sizeof(BufferSize));
		Buffer = (void*) GetMemory(BufferSize + 1);
		try
		{
			with0->Read((void**) Buffer, BufferSize);
			((PAnsiChar) Buffer)[(unsigned __int64)(BufferSize / /*div*/ sizeof(AnsiChar))] = '\x00';
			aName = UnicodeString((char*)Buffer /*# check length*/);
		}
		__finally
		{
			FreeMemory(Buffer);
		}
		with0->Read((void**)&aPitch, (NativeInt) sizeof(aPitch));
		with0->Read((void**)&aSize, (NativeInt) sizeof(aSize));
		with0->Read((void**)&aStyle, (NativeInt) sizeof(aStyle));
		FFont->Charset = aCharset;
		FFont->Color = aColor;
		FFont->Height = aHeight;
		FFont->Name = aName;
		FFont->Pitch = aPitch;
		FFont->Size = aSize;
		FFont->Style = aStyle;
		with0->Read((void**)&FAlignment, (NativeInt) sizeof(FAlignment));
	}
}

void __fastcall THeaderFooterItem::SaveToStream(TStream* AStream)
{
	System::Uitypes::TFontCharset aCharset = (System::Uitypes::TFontCharset) 0;
	TColor aColor = (TColor) 0;
	int aHeight = 0;
	TFontName aName;
	TFontPitch aPitch = TFontPitch::fpDefault;
	int aSize = 0;
	TFontStyles aStyle;
	int aLen = 0;
	/*# with AStream do */
	{
		auto with0 = AStream;
		aLen = FText.Length();
		with0->Write(&aLen, (NativeInt) sizeof(aLen));
		with0->Write(FText.c_str(), (NativeInt) (aLen * sizeof(WideChar)));
		with0->Write(&FLineNumber, (NativeInt) sizeof(FLineNumber));
    // font
		aCharset = FFont->Charset;
		aColor = FFont->Color;
		aHeight = FFont->Height;
		aName = FFont->Name;
		aPitch = FFont->Pitch;
		aSize = FFont->Size;
		aStyle = FFont->Style;
		with0->Write(&aCharset, (NativeInt) sizeof(aCharset));
		with0->Write(&aColor, (NativeInt) sizeof(aColor));
		with0->Write(&aHeight, (NativeInt) sizeof(aHeight));
		aLen = aName.Length();
		with0->Write(&aLen, (NativeInt) sizeof(aLen));
		with0->Write(AnsiString(aName).c_str(), aLen);
		with0->Write(&aPitch, (NativeInt) sizeof(aPitch));
		with0->Write(&aSize, (NativeInt) sizeof(aSize));
		with0->Write(&aStyle, (NativeInt) sizeof(aStyle));
		with0->Write(&FAlignment, (NativeInt) sizeof(FAlignment));
	}
}

void __fastcall THeaderFooterItem::SetAsString(const String Value)
{
	String s;
	TFontStyles sty;
	s = Value;
	FText = DecodeString(GetFirstEl(s, L'/'));
	FFont->Charset = (System::Uitypes::TFontCharset) StrToIntDef(GetFirstEl(s, L'/'), 0);
	FFont->Color = (TColor) StrToIntDef(GetFirstEl(s, L'/'), 0);
	FFont->Height = StrToIntDef(GetFirstEl(s, L'/'), 0);
	FFont->Name = DecodeString(GetFirstEl(s, L'/'));
	FFont->Pitch = ((TFontPitch) StrToIntDef(GetFirstEl(s, L'/'), 0));
	FFont->PixelsPerInch = StrToIntDef(GetFirstEl(s, L'/'), 0);
	FFont->Size = StrToIntDef(GetFirstEl(s, L'/'), 0);
	CastAssign<Byte>(&sty, StrToIntDef(GetFirstEl(s, L'/'), 0));
	FFont->Style = sty;
	FLineNumber = StrToIntDef(GetFirstEl(s, L'/'), 0);
	FAlignment = ((TAlignment) StrToIntDef(GetFirstEl(s, L'/'), 0));
}

void __fastcall THeaderFooterItem::SetFont(TFont* const Value)
{
	FFont->Assign((TPersistent*) Value);
}

/* THeaderFooter */

__fastcall THeaderFooter::THeaderFooter()
 : FType(hftHeader),
			FShadedColor((TColor) 0),
			FLineColor((TColor) 0),
			FItems(nullptr),
			FDefaultFont(nullptr),
			FNumPages(0),
			FMargins(nullptr),
			FFrameHeight(0),
			FOldPen(nullptr),
			FOldBrush(nullptr),
			FOldFont(nullptr),
			FRomanNumbers(false),
			FLineInfo(nullptr),
			FLineCount(0),
			FMirrorPosition(false)
{
	// inherited;
	FFrameTypes = Syneditprintheaderfooter__0;
	FShadedColor = clSilver;
	FLineColor = clBlack;
	FItems = new TList();
	FDefaultFont = new TFont();
	FOldPen = new TPen();
	FOldBrush = new TBrush();
	FOldFont = new TFont();
	FRomanNumbers = false;
	FMirrorPosition = false;
	FLineInfo = new TList();
	/*# with FDefaultFont do */
	{
		auto with0 = FDefaultFont;
		with0->Name = L"Arial";
		with0->Size = 10;
		with0->Color = clBlack;
	}
}

__fastcall THeaderFooter::~THeaderFooter()
{
	int i = 0;
	int stop = 0;
	Clear();
	delete FItems;
	delete FDefaultFont;
	delete FOldPen;
	delete FOldBrush;
	delete FOldFont;
	for(stop = FLineInfo->Count - 1, i = 0; i <= stop; i++)
	{
		delete ((TLineInfo*) FLineInfo->Items[i]);
	}
	delete FLineInfo;
	// inherited;
}

int __fastcall THeaderFooter::Add(String Text, TFont* Font, TAlignment Alignment, int LineNumber)
{
	int result = 0;
	THeaderFooterItem* AItem = nullptr;
	AItem = new THeaderFooterItem();
	if(Font == nullptr)
		AItem->Font = FDefaultFont;
	else
		AItem->Font = Font;
	AItem->Alignment = Alignment;
	AItem->LineNumber = LineNumber;
	AItem->FIndex = FItems->Add(AItem);
	AItem->Text = Text;
	result = AItem->FIndex;
	return result;
}

void __fastcall THeaderFooter::Delete(int Index)
{
	int i = 0;
	int stop = 0;
	for(stop = FItems->Count - 1, i = 0; i <= stop; i++)
	{
		if(((THeaderFooterItem*) FItems->Items[i])->FIndex == Index)
		{
			FItems->Delete(i);
			break;
		}
	}
}

void __fastcall THeaderFooter::Clear()
{
	int i = 0;
	int stop = 0;
	for(stop = FItems->Count - 1, i = 0; i <= stop; i++)
	{
		delete ((THeaderFooterItem*) FItems->Items[i]);
	}
	FItems->Clear();
}

void __fastcall THeaderFooter::SetDefaultFont(TFont* const Value)
{
	FDefaultFont->Assign((TPersistent*) Value);
}

/* Counts number of lines in header/footer and changes the line-number so they
  start with 1 (the user might add header/footer items starting at line 2) */

void __fastcall THeaderFooter::FixLines()
{
	int i = 0;
	int CurLine = 0;
	TLineInfo* LineInfo = nullptr;
	int stop = 0;
	for(stop = FLineInfo->Count - 1, i = 0; i <= stop; i++)
	{
		delete ((TLineInfo*) FLineInfo->Items[i]);
	}
	FLineInfo->Clear();
	CurLine = 0;
	FLineCount = 0;
	for(stop = FItems->Count - 1, i = 0; i <= stop; i++)
	{
		if(((THeaderFooterItem*) FItems->Items[i])->LineNumber != CurLine)
		{
			CurLine = ((THeaderFooterItem*) FItems->Items[i])->LineNumber;
			FLineCount = FLineCount + 1;
			LineInfo = new TLineInfo();
			FLineInfo->Add(LineInfo);
		}
		((THeaderFooterItem*) FItems->Items[i])->LineNumber = FLineCount;
	}
}

/* Calculates the hight of the header/footer, finds the line height for each line
  and calculates the font baseline where text is to be written */

void __fastcall THeaderFooter::CalcHeight(TCanvas* ACanvas)
{
	int i = 0;
	int CurLine = 0;
	THeaderFooterItem* AItem = nullptr;
	int FOrgHeight = 0;
	TTextMetric TextMetric = {};
	int stop = 0;
	FFrameHeight = -1;
	if(FItems->Count <= 0)
		return;
	CurLine = 1;
	FFrameHeight = 0;
	FOrgHeight = FFrameHeight;
	for(stop = FItems->Count - 1, i = 0; i <= stop; i++)
	{
		AItem = ((THeaderFooterItem*) FItems->Items[i]);
		if(AItem->LineNumber != CurLine)
		{
			CurLine = AItem->LineNumber;
			FOrgHeight = FFrameHeight;
		}
		ACanvas->Font->Assign(AItem->Font);
		GetTextMetrics(ACanvas->Handle, &TextMetric);
		/*# with TLineInfo(FLineInfo[CurLine-1]), TextMetric do */
		{
			auto with0 = ((TLineInfo*) FLineInfo->Items[CurLine - 1]);
			auto& with1 = TextMetric;
			with0->LineHeight = Max(with0->LineHeight, ACanvas->TextHeight(L"W"));
			with0->MaxBaseDist = Max(with0->MaxBaseDist, with1.tmHeight - with1.tmDescent);
		}
		FFrameHeight = Max(FFrameHeight, FOrgHeight + ACanvas->TextHeight(L"W"));
	}
	FFrameHeight = FFrameHeight + 2 * FMargins->PHFInternalMargin;
}

int __fastcall CompareItems(void* Item1, void* Item2)
{
	int result = 0;
	result = ((THeaderFooterItem*) Item1)->LineNumber - ((THeaderFooterItem*) Item2)->LineNumber;
	if(result == 0)
		result = *(int*) Item1 - *(int*) Item2;
	return result;
}
//Used to sort header/footer items

void __fastcall THeaderFooter::SetPixPrInch(int Value)
{
	int i = 0;
	int TmpSize = 0;
	TFont* AFont = nullptr;
	int stop = 0;
	for(stop = FItems->Count - 1, i = 0; i <= stop; i++)
	{
		AFont = ((THeaderFooterItem*) FItems->Items[i])->Font;
		TmpSize = AFont->Size;
		AFont->PixelsPerInch = Value;
		AFont->Size = TmpSize;
	}
}

void __fastcall THeaderFooter::InitPrint(TCanvas* ACanvas, int NumPages, String Title, TSynEditPrintMargins* Margins)
{
	SaveFontPenBrush(ACanvas);
	FDate = DateToStr(Now());
	FTime = TimeToStr(Now());
	FNumPages = NumPages;
	FMargins = Margins;
	FTitle = Title;
	FItems->Sort(CompareItems);
	FixLines();
	CalcHeight(ACanvas);
	RestoreFontPenBrush(ACanvas);
}

void __fastcall THeaderFooter::SaveFontPenBrush(TCanvas* ACanvas)
{
	FOldFont->Assign(ACanvas->Font);
	FOldPen->Assign(ACanvas->Pen);
	FOldBrush->Assign(ACanvas->Brush);
}

void __fastcall THeaderFooter::RestoreFontPenBrush(TCanvas* ACanvas)
{
	ACanvas->Font->Assign(FOldFont);
	ACanvas->Pen->Assign(FOldPen);
	ACanvas->Brush->Assign(FOldBrush);
}
//Draws frame around header/footer

void __fastcall THeaderFooter::DrawFrame(TCanvas* ACanvas)
{
	if(FrameTypes == Syneditprintheaderfooter__1)
		return;
	/*# with ACanvas, FMargins do */
	{
		auto with0 = ACanvas;
		auto with1 = FMargins;
		with0->Pen->Color = LineColor;
		with0->Brush->Color = ShadedColor;
		if(FrameTypes.Contains(ftShaded))
			with0->Brush->Style = bsSolid;
		else
			with0->Brush->Style = bsClear;
		if(FrameTypes.Contains(ftBox))
			with0->Pen->Style = psSolid;
		else
			with0->Pen->Style = psClear;
		if(FrameTypes * Syneditprintheaderfooter__2 != Syneditprintheaderfooter__3)
		{
			if(FType == hftHeader)
				with0->Rectangle(with1->PLeft, with1->PHeader - FFrameHeight, with1->PRight, with1->PHeader);
			else
				with0->Rectangle(with1->PLeft, with1->PFooter, with1->PRight, with1->PFooter + FFrameHeight);
		}
		if(FrameTypes.Contains(ftLine))
		{
			with0->Pen->Style = psSolid;
			if(FType == hftHeader)
			{
				with0->MoveTo(with1->PLeft, with1->PHeader);
				with0->LineTo(with1->PRight, with1->PHeader);
			}
			else
			{
				with0->MoveTo(with1->PLeft, with1->PFooter);
				with0->LineTo(with1->PRight, with1->PFooter);
			}
		}
	}
}

void __fastcall THeaderFooter::Print(TCanvas* ACanvas, int PageNum)
{
	int i = 0;
	int X = 0;
	int Y = 0;
	int CurLine = 0;
	String AStr;
	THeaderFooterItem* AItem = nullptr;
	UINT OldAlign = 0;
	TAlignment TheAlignment = taLeftJustify;
	int stop = 0;
	if(FFrameHeight <= 0)
		return; // No header/footer
	SaveFontPenBrush(ACanvas);
	DrawFrame(ACanvas);
	ACanvas->Brush->Style = bsClear;
	if(FType == hftHeader)
		Y = FMargins->PHeader - FFrameHeight;
	else
		Y = FMargins->PFooter;
	Y = Y + FMargins->PHFInternalMargin; // Add the specified internal margin
	CurLine = 1;
	for(stop = FItems->Count - 1, i = 0; i <= stop; i++)
	{
		AItem = ((THeaderFooterItem*) FItems->Items[i]);
		ACanvas->Font = AItem->Font;
		if(AItem->LineNumber != CurLine)
		{
			Y = Y + ((TLineInfo*) FLineInfo->Items[CurLine - 1])->LineHeight;
			CurLine = AItem->LineNumber;
		}
		AStr = AItem->GetText(FNumPages, PageNum, FRomanNumbers, FTitle, FTime, FDate);
      //Find the alignment of the header/footer item - check for MirrorPosition
		TheAlignment = AItem->Alignment;
		if(MirrorPosition && ((PageNum % 2) == 0))
		{
			switch(AItem->Alignment)
			{
				case taRightJustify:
				TheAlignment = taLeftJustify;
				break;
				case taLeftJustify:
				TheAlignment = taRightJustify;
				break;
				default:
				  ;
				break;
			}
		}
      //Find X-position of text
		/*# with FMargins do */
		{
			auto with0 = FMargins;
			X = with0->PLeftHFTextIndent;
			switch(TheAlignment)
			{
				case taRightJustify:
				X = with0->PRightHFTextIndent - ACanvas->TextWidth(AStr);
				break;
				case taCenter:
				X = (int)((with0->PLeftHFTextIndent + with0->PRightHFTextIndent - ACanvas->TextWidth(AStr)) / /*div*/ 2);
				break;
				default:
				  ;
				break;
			}
		}
      /*Aligning at base line - Fonts can have different size in headers and footers*/
		OldAlign = SetTextAlign(ACanvas->Handle, (UINT) TA_BASELINE);
		ExtTextOutW(ACanvas->Handle, X, Y + ((TLineInfo*) FLineInfo->Items[CurLine - 1])->MaxBaseDist, 0, nullptr, ustr2pwchar(AStr), AStr.Length(), nullptr);
		SetTextAlign(ACanvas->Handle, OldAlign);
	}
	RestoreFontPenBrush(ACanvas);
}

void __fastcall THeaderFooter::Assign(TPersistent* Source)
{
	THeaderFooter* Src = nullptr;
	int i = 0;
	if((Source != nullptr) && (ObjectIs(Source, THeaderFooter*)))
	{
		int stop = 0;
		Src = ((THeaderFooter*) Source);
		Clear();
		FType = Src->FType;
		FFrameTypes = Src->FFrameTypes;
		FShadedColor = Src->FShadedColor;
		FLineColor = Src->FLineColor;
		for(stop = Src->FItems->Count - 1, i = 0; i <= stop; i++)
		{
			/*# with THeaderFooterItem(Src.FItems[i]) do */
			{
				auto with0 = ((THeaderFooterItem*) Src->FItems->Items[i]);
				Add(with0->Text, with0->Font, with0->Alignment, with0->LineNumber);
			}
		}
		FDefaultFont->Assign(Src->FDefaultFont);
		FRomanNumbers = Src->FRomanNumbers;
		FMirrorPosition = Src->FMirrorPosition;
	}
	else
	inherited::Assign(Source);
}

int __fastcall THeaderFooter::Count()
{
	int result = 0;
	result = FItems->Count;
	return result;
}

THeaderFooterItem* __fastcall THeaderFooter::Get(int Index)
{
	THeaderFooterItem* result = nullptr;
	result = ((THeaderFooterItem*) FItems->Items[Index]);
	return result;
}

String __fastcall THeaderFooter::GetAsString()
{
	String result;
	int i = 0;
	int stop = 0;
	FixLines();
	result = L"";
	for(stop = FItems->Count - 1, i = 0; i <= stop; i++)
	{
		if(result != L"")
			result = result + L"/";
		result = result + EncodeString(((THeaderFooterItem*) FItems->Items[i])->AsString);
	} //for
	return result;
}

void __fastcall THeaderFooter::SetAsString(const String Value)
{
	THeaderFooterItem* item = nullptr;
	String s;
	Clear();
	item = new THeaderFooterItem();
	try
	{
		s = Value;
		while(s != L"")
		{
			item->AsString = DecodeString(GetFirstEl(s, L'/'));
			Add(item->Text, item->Font, item->Alignment, item->LineNumber);
		}
	}
	__finally
	{
		delete item;
	}
}

void __fastcall THeaderFooter::LoadFromStream(TStream* AStream)
{
	int Num = 0;
	int i = 0;
	System::Uitypes::TFontCharset aCharset = (System::Uitypes::TFontCharset) 0;
	TColor aColor = (TColor) 0;
	int aHeight = 0;
	TFontName aName;
	TFontPitch aPitch = TFontPitch::fpDefault;
	int aSize = 0;
	TFontStyles aStyle;
	int bufSize = 0;
	PAnsiChar buffer = nullptr;
	/*# with AStream do */
	{
		auto with0 = AStream;
    // read header/footer properties first
		with0->Read((void**)&FFrameTypes, (NativeInt) sizeof(FFrameTypes));
		with0->Read((void**)&FShadedColor, (NativeInt) sizeof(FShadedColor));
		with0->Read((void**)&FLineColor, (NativeInt) sizeof(FLineColor));
		with0->Read((void**)&FRomanNumbers, (NativeInt) sizeof(FRomanNumbers));
		with0->Read((void**)&FMirrorPosition, (NativeInt) sizeof(FMirrorPosition));
    // font
		with0->Read((void**)&aCharset, (NativeInt) sizeof(aCharset));
		with0->Read((void**)&aColor, (NativeInt) sizeof(aColor));
		with0->Read((void**)&aHeight, (NativeInt) sizeof(aHeight));
		with0->Read((void**)&bufSize, (NativeInt) sizeof(bufSize));
		buffer = (PAnsiChar) GetMemory(bufSize + 1);
		try
		{
			with0->Read((void**)buffer, bufSize);
			buffer[bufSize] = '\x00';
			aName = UnicodeString(buffer);
		}
		__finally
		{
			FreeMemory(buffer);
		}
		with0->Read((void**)&aPitch, (NativeInt) sizeof(aPitch));
		with0->Read((void**)&aSize, (NativeInt) sizeof(aSize));
		with0->Read((void**)&aStyle, (NativeInt) sizeof(aStyle));
		FDefaultFont->Charset = aCharset;
		FDefaultFont->Color = aColor;
		FDefaultFont->Height = aHeight;
		FDefaultFont->Name = aName;
		FDefaultFont->Pitch = aPitch;
		FDefaultFont->Size = aSize;
		FDefaultFont->Style = aStyle;
    // now read in the items
		with0->Read((void**)&Num, (NativeInt) sizeof(Num));
		while(Num > 0)

      // load headerfooter items from stream
		{
			i = Add(L"", nullptr, taLeftJustify, 1);
			Get(i)->LoadFromStream(AStream);
			--Num;
		}
	}
}

void __fastcall THeaderFooter::SaveToStream(TStream* AStream)
{
	int i = 0;
	int Num = 0;
	System::Uitypes::TFontCharset aCharset = (System::Uitypes::TFontCharset) 0;
	TColor aColor = (TColor) 0;
	int aHeight = 0;
	TFontName aName;
	TFontPitch aPitch = TFontPitch::fpDefault;
	int aSize = 0;
	TFontStyles aStyle;
	int aLen = 0;
	/*# with AStream do */
	{
		auto with0 = AStream;
    // write the header/footer properties first
		int stop = 0;
		with0->Write(&FFrameTypes, (NativeInt) sizeof(FFrameTypes));
		with0->Write(&FShadedColor, (NativeInt) sizeof(FShadedColor));
		with0->Write(&FLineColor, (NativeInt) sizeof(FLineColor));
		with0->Write(&FRomanNumbers, (NativeInt) sizeof(FRomanNumbers));
		with0->Write(&FMirrorPosition, (NativeInt) sizeof(FMirrorPosition));
    // font
		aCharset = FDefaultFont->Charset;
		aColor = FDefaultFont->Color;
		aHeight = FDefaultFont->Height;
		aName = FDefaultFont->Name;
		aPitch = FDefaultFont->Pitch;
		aSize = FDefaultFont->Size;
		aStyle = FDefaultFont->Style;
		with0->Write(&aCharset, (NativeInt) sizeof(aCharset));
		with0->Write(&aColor, (NativeInt) sizeof(aColor));
		with0->Write(&aHeight, (NativeInt) sizeof(aHeight));
		aLen = aName.Length();
		with0->Write(&aLen, (NativeInt) sizeof(aLen));
		with0->Write(AnsiString(aName).c_str(), aName.Length());
		with0->Write(&aPitch, (NativeInt) sizeof(aPitch));
		with0->Write(&aSize, (NativeInt) sizeof(aSize));
		with0->Write(&aStyle, (NativeInt) sizeof(aStyle));

    // now write the items
		Num = Count();
		with0->Write(&Num, (NativeInt) sizeof(Num));
		for(stop = Num - 1, i = 0; i <= stop; i++)
		{
			Get(i)->SaveToStream(AStream);
		}
	}
}

/* THeader */

__fastcall THeader::THeader()
{
	// inherited;
	FType = hftHeader;
}

/* TFooter */

__fastcall TFooter::TFooter()
{
	// inherited;
	FType = hftFooter;
}


}  // namespace SynEditPrintHeaderFooter

