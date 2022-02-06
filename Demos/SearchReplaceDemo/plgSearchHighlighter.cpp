#include <vcl.h>
#pragma hdrstop

#include "plgSearchHighlighter.h"

using namespace std;
using namespace d2c_system;

__fastcall TSearchTextHightlighterSynEditPlugin::TSearchTextHightlighterSynEditPlugin(TCustomSynEdit* AOwner) : inherited(AOwner) {}
__fastcall TSearchTextHightlighterSynEditPlugin::TSearchTextHightlighterSynEditPlugin(TCustomSynEdit* AOwner, TPlugInHandlers AHandlers) : inherited(AOwner, AHandlers) {}
__fastcall TSearchTextHightlighterSynEditPlugin::TSearchTextHightlighterSynEditPlugin() : inherited(nullptr) {}



/* TEditorFrameSynEditPlugin */

void __fastcall TSearchTextHightlighterSynEditPlugin::AfterConstruction()
{
	inherited::AfterConstruction();
	FAttribute = new TSynHighlighterAttributes(L"SearchText", L"Search Text Highlighter");
}

__fastcall TSearchTextHightlighterSynEditPlugin::~TSearchTextHightlighterSynEditPlugin()
{
	delete FAttribute;
	// inherited;
}


void __fastcall TSearchTextHightlighterSynEditPlugin::AfterPaint(TCanvas* ACanvas, const TRect& AClip, int FirstLine, int LastLine)
{
	String SearchText;
	String SearchResultText;
	TPoint Pt = {};
	TRect Rct = {};
	TFont* OldFont = nullptr;
	__int64 LineIndex = 0;
	int Count = 0;
	int ItemIndex = 0;
	TBufferCoord CurrCoord = {};
	inherited::AfterPaint(ACanvas, AClip, FirstLine, LastLine);
	if(!ASSIGNED(Editor->SearchEngine))
		return;
	SearchText = Editor->SearchEngine->Pattern;
	if(SearchText == L"")
		return;
	OldFont = new TFont();
	try
	{
		__int64 stop = 0;
		OldFont->Assign(ACanvas->Font);
		if(Attribute->Background != clNone)
		{
			ACanvas->Brush->Color = Attribute->Background;
			ACanvas->Brush->Style = bsSolid;
		}
		else
		ACanvas->Brush->Style = bsClear;
		if(Attribute->Foreground != clNone)
		{
			ACanvas->Pen->Color = Attribute->Foreground;
			ACanvas->Pen->Style = psSolid;
		}
		else
		ACanvas->Pen->Style = psClear;
		for(stop = LastLine, LineIndex = FirstLine; LineIndex <= stop; LineIndex++)
		{
			int stop1 = 0;
			Count = Editor->SearchEngine->FindAll(Editor->Lines->Strings[LineIndex - 1]);
			for(stop1 = Count - 1, ItemIndex = 0; ItemIndex <= stop1; ItemIndex++)
			{
				CurrCoord = BufferCoord(Editor->SearchEngine->Results[ItemIndex], (int) LineIndex);
				if(CurrCoord == Editor->BlockBegin)
					continue;
				SearchResultText = Editor->Lines->Strings[LineIndex - 1].SubString(Editor->SearchEngine->Results[ItemIndex], Editor->SearchEngine->Lengths[ItemIndex]);
				Pt = Editor->RowColumnToPixels(Editor->BufferToDisplayPos(CurrCoord));
				Rct = Rect(Pt.X, Pt.Y, (int) (Pt.X + Editor->CharWidth * SearchResultText.Length()), Pt.Y + Editor->LineHeight);
				ACanvas->FillRect(Rct);
				ACanvas->TextRect(Rct, Pt.X, Pt.Y, SearchResultText);
			}
		}
		ACanvas->Font->Assign(OldFont);
	}
	__finally
	{
		delete OldFont;
	}
}
