#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "SynEditTextBuffer.hpp"
#include "SynEditTypes.hpp"
#include "uHighlighterProcs.h"
#include "SynEditKeyCmds.hpp"

using namespace std;
using namespace d2c_system;

__fastcall TForm1::TForm1(TComponent* AOwner) : inherited(AOwner) {}


TForm1* Form1 = nullptr;
#pragma resource "*.dfm" 


void __fastcall TForm1::actCodeFoldingExecute(TObject* Sender)
{
	SynEdit1->UseCodeFolding = actCodeFolding->Checked;
}

void __fastcall TForm1::actCPPExecute(TObject* Sender)
{
	SynEditPythonBehaviour1->Editor = nullptr;
	SynEdit1->OnScanForFoldRanges = ScanForFoldRanges;
	SynEdit1->Highlighter = SynCppSyn1;
}

void __fastcall TForm1::actFoldExecute(TObject* Sender)
{
	SynEdit1->ExecuteCommand((TSynEditorCommand) ((TAction*) Sender)->Tag, L' ', nullptr);
}

void __fastcall TForm1::actFoldShapeSizeExecute(TObject* Sender)
{
	String s;
	int Size = 0;
	Size = SynEdit1->CodeFolding->GutterShapeSize;
	s = InputBox(L"New Gutter Square Size", L"New size in pixels (odd number):", IntToStr(Size));
	if(TryStrToInt(s, Size))
		SynEdit1->CodeFolding->GutterShapeSize = Size;
}

void __fastcall TForm1::actFoldUpdate(TObject* Sender)
{
	((TAction*) Sender)->Enabled = SynEdit1->UseCodeFolding;
}

void __fastcall TForm1::actGutterLinesExecute(TObject* Sender)
{
	SynEdit1->Gutter->ShowLineNumbers = actGutterLines->Checked;
}

void __fastcall TForm1::ActionManager1Update(TBasicAction* Action, bool& Handled)
{
	actCodeFolding->Checked = SynEdit1->UseCodeFolding;
	actShowCollapsedMarks->Checked = SynEdit1->CodeFolding->ShowCollapsedLine;
	actShowCollapsedMarks->Checked = SynEdit1->CodeFolding->ShowHintMark;
}

void __fastcall TForm1::actJavaScriptExecute(TObject* Sender)
{
	SynEditPythonBehaviour1->Editor = nullptr;
	SynEdit1->OnScanForFoldRanges = nullptr;
	SynEdit1->Highlighter = SynJScriptSyn1;
}

void __fastcall TForm1::actPythonExecute(TObject* Sender)
{
	SynEditPythonBehaviour1->Editor = SynEdit1;
	SynEditPythonBehaviour1->Editor = nullptr;
	SynEdit1->Highlighter = SynPythonSyn1;
}

void __fastcall TForm1::ActSaveExecute(TObject* Sender)
{
	if(FileName == L"")
		FileSaveAs1->Execute();
	else
		SynEdit1->Lines->SaveToFile(FileName);
}

void __fastcall TForm1::actShowCollapsedLinesExecute(TObject* Sender)
{
	SynEdit1->CodeFolding->ShowCollapsedLine = ((TAction*) Sender)->Checked;
}

void __fastcall TForm1::DialogFontEdit1BeforeExecute(TObject* Sender)
{
	DialogFontEdit1->Dialog->Font = SynEdit1->Font;
}

void __fastcall TForm1::DialogFontEdit1FontDialogApply(TObject* Sender, HWND Wnd)
{
	SynEdit1->Font->Assign(DialogFontEdit1->Dialog->Font);
}

void __fastcall TForm1::DialogPrintDlg1Accept(TObject* Sender)
{
	SynEditPrint1->SynEdit = SynEdit1;
	SynEditPrint1->Print();
}

void __fastcall TForm1::FileOpen1Accept(TObject* Sender)
{
	FileName = FileOpen1->Dialog->FileName;
	SynEdit1->Lines->LoadFromFile(FileName);
	SynEdit1->Highlighter = GetHighlighterFromFileExt(highlighters, ExtractFileExt(FileName));
	if(SynEdit1->Highlighter == SynPythonSyn1)
		SynEditPythonBehaviour1->Editor = SynEdit1;
	else
		SynEditPythonBehaviour1->Editor = nullptr;
	if(SynEdit1->Highlighter == SynCppSyn1)
		SynEdit1->OnScanForFoldRanges = ScanForFoldRanges;
	else
		SynEdit1->OnScanForFoldRanges = nullptr;
	SynEdit1->UseCodeFolding = actCodeFolding->Checked;
}

void __fastcall TForm1::FileSaveAs1Accept(TObject* Sender)
{
	FileName = FileSaveAs1->Dialog->FileName;
	SynEdit1->Lines->SaveToFile(FileName);
}

void __fastcall TForm1::FormCreate(TObject* Sender)
{
	highlighters = new TStringList();
	GetHighlighters(this, highlighters, false);
	FileOpen1->Dialog->Filter = GetHighlightersFilter(highlighters);
	FileOpen1->Dialog->InitialDir = ExtractFilePath(Application->ExeName);
	FileSaveAs1->Dialog->Filter = FileOpen1->Dialog->Filter;
	actFoldAll->Tag = ecFoldAll;
	actFoldNearest->Tag = ecFoldNearest;
	actFoldRegions->Tag = ecFoldRegions;
	actFoldLevel1->Tag = ecFoldLevel1;
	actFoldLevel2->Tag = ecFoldLevel2;
	actFoldLevel3->Tag = ecFoldLevel3;
	actUnFoldAll->Tag = ecUnfoldAll;
	actUnfoldNearest->Tag = ecUnfoldNearest;
	actUnfoldRegions->Tag = ecUnfoldRegions;
	actUnfoldLevel1->Tag = ecUnfoldLevel1;
	actUnfoldLevel2->Tag = ecUnfoldLevel2;
	actUnfoldLevel3->Tag = ecUnfoldLevel3;
}

void __fastcall TForm1::FormDestroy(TObject* Sender)
{
	delete highlighters;
}

void __fastcall TForm1::ScanForFoldRanges(TObject* Sender, TSynFoldRanges* TopFoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	String CurLine;
	__int64 Line = 0;

	auto InsideComment = [&](int Line, int Col) -> bool 
	{
		bool result = false;
		String Token;
		TSynHighlighterAttributes* Attr = nullptr;
		result = SynEdit1->GetHighlighterAttriAtRowCol(BufferCoord(Col, Line + 1), Token, Attr) && (Attr == SynCppSyn1->CommentAttribute);
		return result;
	};

	auto LineHasChar = [&](int Line, Char Character, int StartCol) -> bool 
	{
		bool result = false;
		int i = 0;
		int stop = 0;
		result = false;
		for(stop = (int) CurLine.Length(), i = StartCol; i <= stop; i++)
		{
			if(CurLine[i] == Character)
        // Char must have proper highlighting (ignore stuff inside comments...)
			{
				if(!InsideComment(Line, i))
				{
					result = true;
					break;
				}
			}
		}
		return result;
	}; // faster than Pos!

	auto FindBraces = [&](int Line) -> bool 
	{
		bool result = false;
		int Col = 0;
		int stop = 0;
		result = false;
		for(stop = (int) CurLine.Length(), Col = 1; Col <= stop; Col++)
		{
      // We've found a starting character
			if(CurLine[Col] == L'{')
        // Char must have proper highlighting (ignore stuff inside comments...)
			{
				if(!InsideComment(Line, Col))
          // And ignore lines with both opening and closing chars in them
				{
					if(!LineHasChar(Line, L'}', Col + 1))
					{
						TopFoldRanges->StartFoldRange(Line + 1, 1);
						result = true;
					}
          // Skip until a newline
					break;
				}
			}
			else
			{
				if(CurLine[Col] == L'}')
        // Char must have symbol attri too
				{
					if(!InsideComment(Line, Col))
          // And ignore lines with both opening and closing chars in them
					{
						if(!LineHasChar(Line, L'{', Col + 1))
						{
							TopFoldRanges->StopFoldRange(Line + 1, 1);
							result = true;
						}
          // Skip until a newline
						break;
					}
				}
			}
		} // for Col
		return result;
	};

	auto FoldRegion = [&](int Line) -> bool 
	{
		bool result = false;
		String s;
		result = false;
		s = TrimLeft(CurLine);
		if(UpperCase(s.SubString(1, 14)) == L"#PRAGMA REGION")
		{
			TopFoldRanges->StartFoldRange(Line + 1, FoldRegionType);
			result = true;
		}
		else
		{
			if(UpperCase(s.SubString(1, 17)) == L"#PRAGMA ENDREGION")
			{
				TopFoldRanges->StopFoldRange(Line + 1, FoldRegionType);
				result = true;
			}
		}
		return result;
	};
	__int64 stop = 0;
	for(stop = ToLine, Line = FromLine; Line <= stop; Line++)
	{
    // Deal first with Multiline comments (Fold Type 2)
		if((Synhighlightercpp::TRangeState)(int)((TSynEditStringList*) LinesToScan)->Ranges[(int) Line] == Synhighlightercpp::rsAnsiC)
		{
			if((Line == 0) || ((Synhighlightercpp::TRangeState)(int)((TSynEditStringList*) LinesToScan)->Ranges[(int) Line - 1] != Synhighlightercpp::rsAnsiC))
				TopFoldRanges->StartFoldRange((int) (Line + 1), 2);
			else
				TopFoldRanges->NoFoldInfo((int) (Line + 1));
			continue;
		}
		else
		{
			if((Line > 0) && ((Synhighlightercpp::TRangeState)(int)((TSynEditStringList*) LinesToScan)->Ranges[(int) Line - 1] == Synhighlightercpp::rsAnsiC))
			{
				TopFoldRanges->StopFoldRange((int) (Line + 1), 2);
				continue;
			}

    // Find Fold regions
		}
		CurLine = LinesToScan->Strings[Line];
		if(FoldRegion((int) Line))
			continue;

    // Find an braces on this line  (Fold Type 1)
		CurLine = LinesToScan->Strings[Line];
		if(!FindBraces((int) Line))
			TopFoldRanges->NoFoldInfo((int) (Line + 1));
	} // while Line
}

void __fastcall TForm1::actShowCollapsedMarksExecute(TObject* Sender)
{
	SynEdit1->CodeFolding->ShowHintMark = ((TAction*) Sender)->Checked;
}
