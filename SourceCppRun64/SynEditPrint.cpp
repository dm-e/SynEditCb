#include <vcl.h>
#pragma hdrstop

#include "SynEditPrint.h"
#include <System.Math.hpp>
#include <System.UITypes.hpp>
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Synedithighlighter;
using namespace Syneditmiscprocs;
using namespace Syneditprintheaderfooter;
using namespace Syneditprintmargins;
using namespace Syneditprinttypes;
using namespace Syneditprinterinfo;
using namespace Synedittypes;
using namespace Synunicode;
using namespace System;
using namespace System::Classes;
using namespace System::Math;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Syneditprint
{
#define Syneditprint__0 (TFontStyles() << TFontStyle::fsBold << TFontStyle::fsItalic << TFontStyle::fsUnderline << TFontStyle::fsStrikeOut)
#define Syneditprint__1 (TSysCharSet() << ' ' << '-' << '\x09' << ',')
#define Syneditprint__2 (TSysCharSet() << ';' << ')' << '.')
#define Syneditprint__3 TFontStyles()
#define Syneditprint__4 (TSysCharSet() << ' ' << '-' << '\x09' << ',')
#define Syneditprint__5 (TSysCharSet() << ';' << ')' << '.')

__fastcall TPageLine::TPageLine() {}



/* TSynEditPrint */

__fastcall TSynEditPrint::TSynEditPrint(TComponent* AOwner)
 : inherited(AOwner),
			FCopies(1),
			FFooter(new TFooter()),
			FHeader(new Syneditprintheaderfooter::THeader()),
			FLines(new TStringList()),
			FMargins(new TSynEditPrintMargins()),
			FPageCount(0),
			FFont(nullptr),
			FPrinterInfo(nullptr),
			FPages(nullptr),
			FCanvas(nullptr),
			fCharWidth(0),
			FMaxLeftChar(0),
			FWrap(false),
			FYPos(0),
			FLineHeight(0),
			fHighlight(false),
			FColors(false),
			fHighlighter(nullptr),
			FOldFont(nullptr),
			FSynOK(false),
			FLineNumbers(false),
			fLineNumber(0),
			FLineOffset(0),
			FAbort(false),
			FPrinting(false),
			FDefaultBG((TColor) 0),
			FPageOffset(0),
			FRangesOK(false),
			FMaxWidth(0),
			FMaxCol(0),
			FPagesCounted(false),
			FLineNumbersInMargin(false),
			FTabWidth(0),
			FFontColor((TColor) 0),
			fSelectedOnly(false),
			fSelAvail(false),
			fSelMode(smNormal),
			FETODist(nullptr)
{
	FPrinterInfo = new TSynEditPrinterInfo();
	FFont = new TFont();
	FOldFont = new TFont();
	MaxLeftChar = 1024;
	FWrap = true;
	fHighlight = true;
	FColors = false;
	FLineNumbers = false;
	FLineOffset = 0;
	FPageOffset = 0;
	FLineNumbersInMargin = false;
	FPages = new TList();
	FTabWidth = 8;
	FDefaultBG = clWhite;
}

__fastcall TSynEditPrint::~TSynEditPrint()
{
	int i = 0;
	int stop = 0;
	delete FFooter;
	delete FHeader;
	delete FLines;
	delete FMargins;
	delete FPrinterInfo;
	delete FFont;
	delete FOldFont;
	for(stop = FPages->Count - 1, i = 0; i <= stop; i++)
	{
		delete ((TPageLine*) FPages->Items[i]);
	}
	delete FPages;
	FreeMemory(FETODist);
	// inherited;
}

void __fastcall TSynEditPrint::DefineProperties(TFiler* Filer)
{
	inherited::DefineProperties(Filer);
}

void __fastcall TSynEditPrint::SetLines(TStrings* const Value)
{
	int i = 0;
	int j = 0;
	TConvertTabsProc ConvertTabsProc;
	String TmpString;
	ConvertTabsProc = GetBestConvertTabsProc(FTabWidth);
	/*# with FLines do */
	{
		auto with0 = FLines;
		with0->BeginUpdate();
		try
		{
			int stop = 0;
			with0->Clear();
			for(stop = Value->Count - 1, i = 0; i <= stop; i++)
			{
				TmpString = ConvertTabsProc(Value->Strings[i], FTabWidth);
				j = Pos(L"\x09", TmpString);
				while(j > 0)
				{
					TmpString[j] = L' ';
					j = Pos(L"\x09", TmpString);
				}
				with0->Add(TmpString);
			}
		}
		__finally
		{
			with0->EndUpdate();
		}
	}
	FRangesOK = false;
	FPagesCounted = false;
}

void __fastcall TSynEditPrint::SetFont(TFont* const Value)
{
	FFont->Assign((TPersistent*) Value);
	FPagesCounted = false;
}

void __fastcall TSynEditPrint::SetCharWidth(int Value)
{
	fCharWidth = Value;
}

void __fastcall TSynEditPrint::SetMaxLeftChar(int Value)
{
	FMaxLeftChar = Value;
}

void __fastcall TSynEditPrint::SetHighlighter(TSynCustomHighlighter* const Value)
{
	fHighlighter = const_cast<TSynCustomHighlighter*>(Value);
	FRangesOK = false;
	FPagesCounted = false;
}

// Inserts filling chars into a string containing chars that display as glyphs
// wider than an average glyph. (This is often the case with Asian glyphs, which
// are usually wider than latin glpyhs)
// This is only to simplify paint-operations and has nothing to do with
// multi-byte chars.

String __fastcall TSynEditPrint::ExpandAtWideGlyphs(const String s)
{
	String result;
	int i = 0;
	int j = 0;
	int CountOfAvgGlyphs = 0;
	int stop = 0;
	FCanvas->Font = Font;
	j = 0;
	result.SetLength(s.Length() * 2); // speed improvement
	for(stop = s.Length(), i = 1; i <= stop; i++)
	{
		++j;
    // Introduce a small tolerance Issue 54
		CountOfAvgGlyphs = Ceil(double(FCanvas->TextWidth(String(s[i]))) / fCharWidth - 0.04);
		if(j + CountOfAvgGlyphs > result.Length())
			result.SetLength(result.Length() + 128);

    // insert CountOfAvgGlyphs filling chars
		while(CountOfAvgGlyphs > 1)
		{
			result[j] = FillerChar;
			++j;
			--CountOfAvgGlyphs;
		}
		result[j] = s[i];
	}
	result.SetLength(j);
	return result;
}
/* Initialize Font.PixelsPerInch, Character widths, Margins, Total Page count,
  headers and footers*/

void __fastcall TSynEditPrint::InitPrint()
{
	int TmpSize = 0;
	TTextMetric TmpTextMetrics = {};
//  FDefaultBG := FCanvas.Brush.Color;                                          
	FFontColor = FFont->Color;
	FCanvas->Font->Assign(FFont);
	if(!FPrinting)
	{
		SetPixelsPrInch();
		TmpSize = FCanvas->Font->Size;
		FCanvas->Font->PixelsPerInch = FFont->PixelsPerInch;
		FCanvas->Font->Size = TmpSize;
	}
  // Calculate TextMetrics with the (probably) most wider text styles so text is
  // never clipped (although potentially wasting space)
	FCanvas->Font->Style = Syneditprint__0;
	GetTextMetrics(FCanvas->Handle, &TmpTextMetrics);
	CharWidth = TmpTextMetrics.tmAveCharWidth;
	FLineHeight = TmpTextMetrics.tmHeight + TmpTextMetrics.tmExternalLeading;
	FCanvas->Font->Style = FFont->Style;
	FMargins->InitPage(FCanvas, 1, FPrinterInfo, FLineNumbers, FLineNumbersInMargin, FLines->Count - 1 + FLineOffset);
	CalcPages();
	FHeader->InitPrint(FCanvas, FPageCount, FTitle, FMargins);
	FFooter->InitPrint(FCanvas, FPageCount, FTitle, FMargins);
	FSynOK = Highlight && ASSIGNED(fHighlighter) && (FLines->Count > 0);
}

void __fastcall TSynEditPrint::SetPixelsPrInch()
{
	int TmpSize = 0;
	FHeader->SetPixPrInch(FPrinterInfo->YPixPrInch);
	FFooter->SetPixPrInch(FPrinterInfo->YPixPrInch);
  //This should be necessary - else size would be changed...
	TmpSize = FFont->Size;
	FFont->PixelsPerInch = FPrinterInfo->YPixPrInch;
	FFont->Size = TmpSize;
}
//Initialize ranges in Highlighter

void __fastcall TSynEditPrint::InitRanges()
{
	int i = 0;
	if(!FRangesOK && ASSIGNED(fHighlighter) && (Lines->Count > 0))
	{
		fHighlighter->ResetRange();
		FLines->Objects[0] = ((TObject*) fHighlighter->GetRange());
		i = 1;
		while(i < Lines->Count)
		{
			fHighlighter->SetLine(FLines->Strings[i - 1], i - 1);
			fHighlighter->NextToEol();
			FLines->Objects[i] = ((TObject*) fHighlighter->GetRange());
			++i;
		}
		FRangesOK = true;
	}
}

// Calculates the total number of pages

void __fastcall TSynEditPrint::CalcPages()
{
	String AStr;
	String Text;
	int StrWidth = 0;
	__int64 i = 0;
	int j = 0;
	TList* AList = nullptr;
	int YPos = 0;
	TPageLine* PageLine = nullptr;

  //Counts the number of lines a line is wrapped to

	auto CountWrapped = [&]() -> void 
	{
		int j = 0;
		int stop = 0;
		for(stop = AList->Count - 1, j = 0; j <= stop; j++)
		{
			YPos = YPos + FLineHeight;
		}
	};
	int iStartLine = 0;
	int iEndLine = 0;
	int iSelStart = 0;
	int iSelLen = 0;
	__int64 stop = 0;
	InitRanges();
	for(stop = FPages->Count - 1, i = 0; i <= stop; i++)
	{
		delete ((TPageLine*) FPages->Items[i]);
	}
	FPages->Clear();
	FMaxWidth = FMargins->PRight - FMargins->PLeft;
	AStr = L"";
	FMaxCol = 0;
	while(FCanvas->TextWidth(AStr) < FMaxWidth)
	{
		AStr = AStr + L"W";
		FMaxCol = FMaxCol + 1;
	}
	FMaxCol = FMaxCol - 1;
  /*FTestString is used to Calculate MaxWidth when prewiewing and printing -
   else the length is not calculated correctly when prewiewing and the
   zoom is different from 0.25,0.5,1,2,4 (as for example 1.20) - WHY???*/
//  fTestString := StringofChar('W', FMaxCol);
	AStr = StringOfChar(L'W', FMaxCol);
	FMaxWidth = FCanvas->TextWidth(AStr);
	FPageCount = 1;
	PageLine = new TPageLine();
	PageLine->FirstLine = 0;
	FPages->Add(PageLine);
	YPos = FMargins->PTop;
	if(SelectedOnly)
	{
		iStartLine = fBlockBegin.Line - 1;
		iEndLine = fBlockEnd.Line - 1;
	}
	else
	{
		iStartLine = 0;
		iEndLine = Lines->Count - 1;
	}
	for(stop = iEndLine, i = iStartLine; i <= stop; i++)
	{
		if(!fSelectedOnly || (fSelMode == smLine))
			Text = Lines->Strings[i];
		else
		{
			if((fSelMode == smColumn) || (i == fBlockBegin.Line - 1))
				iSelStart = fBlockBegin.Char;
			else
				iSelStart = 1;
			if((fSelMode == smColumn) || (i == fBlockEnd.Line - 1))
				iSelLen = fBlockEnd.Char - iSelStart;
			else
				iSelLen = MaxInt;
			Text = Lines->Strings[i].SubString(iSelStart, iSelLen);
		}
      /*if new page then increase FPageCount and save the top-line number in
       FPages*/
		if(YPos + FLineHeight > FMargins->PBottom)
		{
			YPos = FMargins->PTop;
			FPageCount = FPageCount + 1;
			PageLine = new TPageLine();
			PageLine->FirstLine = (int) i;
			FPages->Add(PageLine);
		}
		StrWidth = FCanvas->TextWidth(Text);
    /*Check for wrap*/
		if(Wrap && (StrWidth > FMaxWidth))
		{
			int stop1 = 0;
			AList = new TList();
			if(WrapTextEx(Text, Syneditprint__1, FMaxCol, AList))
				CountWrapped();
			else

              /*If WrapTextToList didn't succed with the first set of breakchars
               then try this one:*/
			{
				if(WrapTextEx(Text, Syneditprint__2, FMaxCol, AList))
					CountWrapped();
				else

                  /*If WrapTextToList didn't succed at all, then do it the
                   primitive way*/
				{
					while(Text.Length() > 0)
					{
						AStr = Text.SubString(1, FMaxCol);
						Text.Delete(1, 	FMaxCol);
						if(Text.Length() > 0)
							YPos = YPos + FLineHeight;
					}
				}
			}
			for(stop1 = AList->Count - 1, j = 0; j <= stop1; j++)
			{
				delete ((TWrapPos*) AList->Items[j]);
			}
			delete AList;
		}
		YPos = YPos + FLineHeight;
	}
	FPagesCounted = true;
}

/* Writes the line number. FMargins. PLeft is the position of the left margin
  (which is automatically incremented by the length of the linenumber text, if
  the linenumbers should not be placed in the margin) */

void __fastcall TSynEditPrint::WriteLineNumber()
{
	String AStr;
	SaveCurrentFont();
	AStr = IntToStr(fLineNumber + FLineOffset) + L": ";
	FCanvas->Brush->Color = FDefaultBG;
	FCanvas->Font->Style = Syneditprint__3;
	FCanvas->Font->Color = clBlack;
	FCanvas->TextOut(FMargins->PLeft - FCanvas->TextWidth(AStr), FYPos, AStr);
	RestoreCurrentFont();
}

void __fastcall TSynEditPrint::HandleWrap(const String Text, int MaxWidth)
{
	String AStr;
	TList* AList = nullptr;
	int j = 0;

	auto WrapPrimitive = [&]() -> void 
	{
		int i = 0;
		TWrapPos* WrapPos = nullptr;
		i = 1;
		while(i <= Text.Length())
		{
			AStr = L"";
			while((AStr.Length() < FMaxCol) && (i <= Text.Length()))
			{
				AStr = AStr + String(Text[i]);
				i = i + 1;
			}
			WrapPos = new TWrapPos();
			WrapPos->Index = i - 1;
			AList->Add(WrapPos);
			if((AStr.Length() - i) <= FMaxCol)
				break;
		}
	};
	int stop = 0;
	AStr = L"";
  //First try to break the string at the following chars:
	AList = new TList();
	if(WrapTextEx(Text, Syneditprint__4, FMaxCol, AList))
		TextOut(Text, AList);
	else

      //Then try to break the string at the following chars:
	{
		if(WrapTextEx(Text, Syneditprint__5, FMaxCol, AList))
			TextOut(Text, AList);
		else
		{
			WrapPrimitive();
			TextOut(Text, AList);
		}
	}
	for(stop = AList->Count - 1, j = 0; j <= stop; j++)
	{
		delete ((TWrapPos*) AList->Items[j]);
	}
	delete AList;
}

void __fastcall TSynEditPrint::SaveCurrentFont()
{
	FOldFont->Assign(FCanvas->Font);
}

void __fastcall TSynEditPrint::RestoreCurrentFont()
{
	FCanvas->Font->Assign(FOldFont);
}

String __fastcall TSynEditPrint::ClipLineToRect(String s, const TRect& cR)
{
	TRect R = cR;
	String result;
	while(FCanvas->TextWidth(s) > FMaxWidth)
		s.SetLength(s.Length() - 1);
	result = s;
	return result;
}

//Does the actual printing

void __fastcall TSynEditPrint::TextOut(const String Text, TList* AList)
{
	String Token;
	int TokenPos = 0;
	TSynHighlighterAttributes* Attr = nullptr;
	TColor AColor = (TColor) 0;
	int TokenStart = 0;
	int LCount = 0;
	bool Handled = false;
	String AStr;
	int i = 0;
	int WrapPos = 0;
	int OldWrapPos = 0;
	TStringList* Lines = nullptr;
	TRect ClipRect = {};
	String sLine;
	String sLineExpandedAtWideGlyphs;
	int ExpandedPos = 0;

	auto InitETODist = [&](int CharWidth, const String Text) -> void 
	{
		TSize Size = {};
		int i = 0;
		int stop = 0;
		FETODist = (pIntArray) ReallocMemory(FETODist, Text.Length() * sizeof(int));
		for(stop = Text.Length() - 1, i = 0; i <= stop; i++)
		{
			Size = GetTextSize(FCanvas->Handle, ustr2pwchar(Text, i + 1 - 1), 1);
      // Introduce a small tolerance (#54)
			(*FETODist)[i] = Ceil(double(Size.cx) / CharWidth - 0.04) * CharWidth;
		}
	};

	auto ClippedTextOut = [&](int X, int Y, String Text) -> void 
	{
		Text = ClipLineToRect(Text, ClipRect);
		InitETODist(fCharWidth, Text);
		::ExtTextOutW(FCanvas->Handle, X, Y, 0, nullptr, ustr2pwchar(Text), Text.Length(), ((PInteger) FETODist));
	};

	auto SplitToken = [&]() -> void 
	{
		String AStr;
		int Last = 0;
		int FirstPos = 0;
		int TokenEnd = 0;
		Last = TokenPos;
		FirstPos = TokenPos;
		TokenEnd = TokenPos + Token.Length();
		while((LCount < AList->Count) && (TokenEnd > ((TWrapPos*) AList->Items[LCount])->Index))
		{
			AStr = Text.SubString(Last + 1, ((TWrapPos*) AList->Items[LCount])->Index - Last);
			Last = ((TWrapPos*) AList->Items[LCount])->Index;
			ExpandedPos = fHighlighter->PosToExpandedPos(FirstPos);
			ClippedTextOut(FMargins->PLeft + ExpandedPos * fCharWidth, FYPos, AStr);
			FirstPos = 0;
			LCount = LCount + 1;
			FYPos = FYPos + FLineHeight;
		}
		AStr = Text.SubString(Last + 1, TokenEnd - Last);
		ExpandedPos = fHighlighter->PosToExpandedPos(FirstPos);
		ClippedTextOut(FMargins->PLeft + ExpandedPos * fCharWidth, FYPos, AStr);
    //Ready for next token:
		TokenStart = TokenPos + Token.Length() - AStr.Length();
	};
	/*# with FMargins do */
	{
		auto with0 = FMargins;
		ClipRect = Rect(with0->PLeft, with0->PTop, with0->PRight, with0->PBottom);
	}
	if(FSynOK)
	{
		SaveCurrentFont();
		fHighlighter->SetRange(FLines->Objects[fLineNumber - 1]);
		sLine = Text;
		sLineExpandedAtWideGlyphs = ExpandAtWideGlyphs(sLine);
		fHighlighter->SetLineExpandedAtWideGlyphs(sLine, sLineExpandedAtWideGlyphs, fLineNumber);
		Token = L"";
		TokenStart = 0;
		LCount = 0;
		while(!fHighlighter->GetEol())
		{
			Token = fHighlighter->GetToken();
			TokenPos = fHighlighter->GetTokenPos();
			Attr = fHighlighter->GetTokenAttribute();
			if(ASSIGNED(Attr))
			{
				FCanvas->Font->Style = Attr->Style;
				if(FColors)
				{
					AColor = Attr->Foreground;
					if(AColor == clNone)
						AColor = FFont->Color;
					FCanvas->Font->Color = AColor;
					AColor = Attr->Background;
					if(AColor == clNone)
						AColor = FDefaultBG;
					FCanvas->Brush->Color = AColor;
				}
				else
				{
					FCanvas->Font->Color = FFontColor;
					FCanvas->Brush->Color = FDefaultBG;
				}
			}
			else
			{
				FCanvas->Font->Color = FFontColor;
				FCanvas->Brush->Color = FDefaultBG;
			}
			Handled = false;
			if(ASSIGNED(AList))
			{
				if(LCount < AList->Count)
          //Split between tokens:
				{
					if(TokenPos >= ((TWrapPos*) AList->Items[LCount])->Index)
					{
						LCount = LCount + 1;
						TokenStart = TokenPos;
						FYPos = FYPos + FLineHeight;
					}
					else

            //Split in the middle of a token:
					{
						if(TokenPos + Token.Length() > ((TWrapPos*) AList->Items[LCount])->Index)
						{
							Handled = true;
							SplitToken();
						}
					}
				}
			}
			if(!Handled)
			{
				ExpandedPos = fHighlighter->PosToExpandedPos(TokenPos - TokenStart);
				ClippedTextOut(FMargins->PLeft + ExpandedPos * fCharWidth, FYPos, Token);
			}
			fHighlighter->Next();
		}
		RestoreCurrentFont();
	}
	else
	{
		Lines = new TStringList();
		try
		{
			int stop = 0;
			OldWrapPos = 0;
			if(ASSIGNED(AList))
			{
				int stop = 0;
				for(stop = AList->Count - 1, i = 0; i <= stop; i++)
				{
					WrapPos = ((TWrapPos*) AList->Items[i])->Index;
					if(i == 0)
						AStr = Text.SubString(1, WrapPos);
					else
						AStr = Text.SubString(OldWrapPos + 1, WrapPos - OldWrapPos);
					Lines->Add(AStr);
					OldWrapPos = WrapPos;
				}
			}
			if(Text.Length() > 0)
				Lines->Add(Text.SubString(OldWrapPos + 1, MaxInt));
			for(stop = Lines->Count - 1, i = 0; i <= stop; i++)
			{
				ClippedTextOut(FMargins->PLeft, FYPos, Lines->Strings[i]);
				if(i < Lines->Count - 1)
					FYPos = FYPos + FLineHeight;
			}
		}
		__finally
		{
			delete Lines;
		}
	}
}

void __fastcall TSynEditPrint::WriteLine(const String Text)
{
	int StrWidth = 0;
	if(FLineNumbers)
		WriteLineNumber();
	StrWidth = FCanvas->TextWidth(Text);
  /*Note that MaxWidth is calculated, using FTestString found in CalcPages -
   else the length is not calculated correctly when prewiewing and the
   zoom is different from 0.25,0.5,1,2,4 (as for example 1.20) - WHY???
  */
	if(Wrap && (StrWidth > FMaxWidth))
		HandleWrap(Text, FMaxWidth);
	else
		TextOut(Text, nullptr);
	FYPos = FYPos + FLineHeight;
}
//Prints a page

void __fastcall TSynEditPrint::PrintPage(int Num)
{
	__int64 i = 0;
	int IEND = 0;
	int iSelStart = 0;
	int iSelLen = 0;
	PrintStatus(psNewPage, Num, FAbort);
	if(!FAbort)
	{
		FCanvas->Brush->Color = Color;
		/*# with FMargins do */
		{
			auto with0 = FMargins;
			FCanvas->FillRect(Rect(with0->PLeft, with0->PTop, with0->PRight, with0->PBottom));
		}
		FMargins->InitPage(FCanvas, Num, FPrinterInfo, FLineNumbers, FLineNumbersInMargin, FLines->Count - 1 + FLineOffset);
		FHeader->Print(FCanvas, Num + FPageOffset);
		if(FPages->Count > 0)
		{
			__int64 stop = 0;
			FYPos = FMargins->PTop;
			if(Num == FPageCount)
				IEND = FLines->Count - 1;
			else
				IEND = ((TPageLine*) FPages->Items[Num])->FirstLine - 1;
			for(stop = IEND, i = ((TPageLine*) FPages->Items[Num - 1])->FirstLine; i <= stop; i++)
			{
				fLineNumber = (int) (i + 1);
				if(!fSelectedOnly || ((i >= fBlockBegin.Line - 1) && (i <= fBlockEnd.Line - 1)))
				{
					if(!fSelectedOnly || (fSelMode == smLine))
						WriteLine(Lines->Strings[i]);
					else
					{
						if((fSelMode == smColumn) || (i == fBlockBegin.Line - 1))
							iSelStart = fBlockBegin.Char;
						else
							iSelStart = 1;
						if((fSelMode == smColumn) || (i == fBlockEnd.Line - 1))
							iSelLen = fBlockEnd.Char - iSelStart;
						else
							iSelLen = MaxInt;
						WriteLine(Lines->Strings[i].SubString(iSelStart, iSelLen));
					}
					PrintLine((int) (i + 1), Num);
				}
			}
		}
		FFooter->Print(FCanvas, Num + FPageOffset);
	}
}
//Update pages (called explicitly by preview component)

void __fastcall TSynEditPrint::UpdatePages(TCanvas* ACanvas)
{
	FCanvas = ACanvas;
	FPrinterInfo->UpdatePrinter();
	InitPrint();
}
//Print to specified canvas. Used by preview component

void __fastcall TSynEditPrint::PrintToCanvas(TCanvas* ACanvas, int PageNumber)
{
	FAbort = false;
	FPrinting = false;
	FCanvas = ACanvas;
	PrintPage(PageNumber);
}

void __fastcall TSynEditPrint::Print()
{
	PrintRange(1, -1);
}
//Prints the pages in the specified range

void __fastcall TSynEditPrint::PrintRange(int StartPage, int EndPage)
{
	int i = 0;
	int II = 0;
	int stop = 0;
	if(fSelectedOnly && !fSelAvail)
		return;
	FPrinting = true;
	FAbort = false;
  // The next part sets the document title that is used by the printer queue.
	if(FDocTitle != L"")
		Printer()->Title = FDocTitle;
	else
		Printer()->Title = FTitle;
	Printer()->BeginDoc();
	PrintStatus(psBegin, StartPage, FAbort);
	UpdatePages(Printer()->Canvas);
	for(stop = Copies, II = 1; II <= stop; II++)
	{
		i = StartPage;
		if(EndPage < 0)
			EndPage = FPageCount;
		while((i <= EndPage) && (!FAbort))
		{
			PrintPage(i);
			if(((i < EndPage) || (II < Copies)) && !FAbort)
				Printer()->NewPage();
			i = i + 1;
		}
	}
	if(!FAbort)
		PrintStatus(psEnd, EndPage, FAbort);
	Printer()->EndDoc();
	FPrinting = false;
}
//Fires the OnPrintLine event

void __fastcall TSynEditPrint::PrintLine(int LineNumber, int PageNumber)
{
	if(ASSIGNED(FOnPrintLine))
		FOnPrintLine(this, LineNumber, PageNumber);
}
//Fires the OnPrintStatus event

void __fastcall TSynEditPrint::PrintStatus(TSynPrintStatus Status, int PageNumber, bool& Abort)
{
	Abort = false;
	if(ASSIGNED(FOnPrintStatus))
		FOnPrintStatus(this, Status, PageNumber, Abort);
	if(Abort)
	{
		if(FPrinting)
			Printer()->Abort();
	}
}
/*Returns total page count. If pages hasn't been counted before,
 then a UpdatePages is called with a temporary canvas*/

int __fastcall TSynEditPrint::GetPageCount()
{
	int result = 0;
	TCanvas* TmpCanvas = nullptr;
	HDC DC = 0;
	result = 0;
	if(FPagesCounted)
		result = FPageCount;
	else
	{
		TmpCanvas = new TCanvas();
		try
		{
			DC = GetDC(0);
			try
			{
				if(DC != 0)
				{
					TmpCanvas->Handle = DC;
					UpdatePages(TmpCanvas);
					TmpCanvas->Handle = 0;
					result = FPageCount;
					FPagesCounted = true;
				}
			}
			__finally
			{
				ReleaseDC(0, DC);
			}
		}
		__finally
		{
			delete TmpCanvas;
		}
	}
	return result;
}

void __fastcall TSynEditPrint::SetSynEdit(TCustomSynEdit* const Value)
{

//  Lines := Value.Lines;
	Highlighter = Value->Highlighter;
	Font = Value->Font;
	FTabWidth = Value->TabWidth;
	Lines = Value->Lines;
	fSelAvail = Value->SelAvail;
	fBlockBegin = Value->BlockBegin;
	fBlockEnd = Value->BlockEnd;
	fSelMode = Value->SelectionMode;
}

void __fastcall TSynEditPrint::LoadFromStream(TStream* AStream)
{
	int Len = 0;
	int BufferSize = 0;
	PWideChar Buffer = nullptr;
	FHeader->LoadFromStream(AStream);
	FFooter->LoadFromStream(AStream);
	FMargins->LoadFromStream(AStream);
	/*# with AStream do */
	{
		auto with0 = AStream;
		with0->Read((void**)&Len, (NativeInt) sizeof(Len));
		BufferSize = (int) (Len * sizeof(WideChar));
		Buffer = (PWideChar) GetMemory(BufferSize + sizeof(WideChar));
		try
		{
			with0->Read((void**)Buffer, BufferSize);
			Buffer[(unsigned __int64)(BufferSize / /*div*/ sizeof(WideChar))] = L'\x00';
			FTitle = Buffer;
		}
		__finally
		{
			FreeMemory(Buffer);
		}
		with0->Read((void**)&Len, (NativeInt) sizeof(Len));
		BufferSize = (int) (Len * sizeof(WideChar));
		Buffer = (PWideChar) GetMemory(BufferSize + sizeof(WideChar));
		try
		{
			with0->Read((void**)Buffer, BufferSize);
			Buffer[(unsigned __int64)(BufferSize / /*div*/ sizeof(WideChar))] = L'\x00';
			FDocTitle = Buffer;
		}
		__finally
		{
			FreeMemory(Buffer);
		}
		with0->Read((void**)&FWrap, (NativeInt) sizeof(FWrap));
		with0->Read((void**)&fHighlight, (NativeInt) sizeof(fHighlight));
		with0->Read((void**)&FColors, (NativeInt) sizeof(FColors));
		with0->Read((void**)&FLineNumbers, (NativeInt) sizeof(FLineNumbers));
		with0->Read((void**)&FLineOffset, (NativeInt) sizeof(FLineOffset));
		with0->Read((void**)&FPageOffset, (NativeInt) sizeof(FPageOffset));
	}
}

void __fastcall TSynEditPrint::SaveToStream(TStream* AStream)
{
	int ALen = 0;
	FHeader->SaveToStream(AStream);
	FFooter->SaveToStream(AStream);
	FMargins->SaveToStream(AStream);
	/*# with AStream do */
	{
		auto with0 = AStream;
		ALen = FTitle.Length();
		with0->Write(&ALen, (NativeInt) sizeof(ALen));
		with0->Write(FTitle.c_str(), (NativeInt) (ALen * sizeof(WideChar)));
		ALen = FDocTitle.Length();
		with0->Write(&ALen, (NativeInt) sizeof(ALen));
		with0->Write(FDocTitle.c_str(), (NativeInt) (ALen * sizeof(WideChar)));
		with0->Write(&FWrap, (NativeInt) sizeof(FWrap));
		with0->Write(&fHighlight, (NativeInt) sizeof(fHighlight));
		with0->Write(&FColors, (NativeInt) sizeof(FColors));
		with0->Write(&FLineNumbers, (NativeInt) sizeof(FLineNumbers));
		with0->Write(&FLineOffset, (NativeInt) sizeof(FLineOffset));
		with0->Write(&FPageOffset, (NativeInt) sizeof(FPageOffset));
	}
}

void __fastcall TSynEditPrint::SetFooter(TFooter* const Value)
{
	FFooter->Assign((TPersistent*) Value);
}

void __fastcall TSynEditPrint::SetHeader(Syneditprintheaderfooter::THeader* const Value)
{
	FHeader->Assign((TPersistent*) Value);
}

void __fastcall TSynEditPrint::SetMargins(TSynEditPrintMargins* const Value)
{
	FMargins->Assign((TPersistent*) Value);
}


}  // namespace SynEditPrint

