#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "SynEditTextBuffer.h"
#include "SynEditTypes.h"
#include "uHighlighterProcs.h"
#include "SynEditKeyCmds.h"

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
	SynEdit1 = new TSynEdit(this);
	SynEdit1->Parent = this;
	SynEdit1->Left = 0;
	SynEdit1->Top = 25;
	SynEdit1->Width = 635;
	SynEdit1->Height = 377;
	SynEdit1->Align = alClient;
	SynEdit1->Font->Charset = DEFAULT_CHARSET;
	SynEdit1->Font->Color = clWindowText;
	SynEdit1->Font->Height-13;
	SynEdit1->Font->Name = "Consolas";
	SynEdit1->Font->Pitch = TFontPitch::fpFixed;
	//SynEdit1->Font->Style;
	SynEdit1->Font->Quality = TFontQuality::fqClearTypeNatural;
	SynEdit1->PopupMenu = PopupActionBar1;
	SynEdit1->TabOrder = 1;
	SynEdit1->UseCodeFolding = False;

	SynEdit1->Gutter->AutoSize = True;
	SynEdit1->Gutter->Font->Charset = DEFAULT_CHARSET;
	SynEdit1->Gutter->Font->Color = clWindowText;
	SynEdit1->Gutter->Font->Height-13;
	SynEdit1->Gutter->Font->Name = "Consolas";
	//SynEdit1->Gutter->Font->Style;

	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("This project demonstrates the code folding capabilities of Synedit.");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("Use the menu to open one of the demo files in the project directory.");
	SynEdit1->Lines->Add("- demo.cpp");
	SynEdit1->Lines->Add("- demo.js");
	SynEdit1->Lines->Add("- demo.py");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("Then select \"View, Code Folding\" to activate Code Foldind and try the ");
	SynEdit1->Lines->Add("SynEdit folding commands and their default shorcuts:");
	SynEdit1->Lines->Add("  AddKey(ecFoldAll, VK_OEM_MINUS, [ssCtrl, ssShift]);");
	SynEdit1->Lines->Add("  AddKey(ecUnfoldAll,  VK_OEM_PLUS, [ssCtrl, ssShift]);");
	SynEdit1->Lines->Add("  AddKey(ecFoldNearest, VK_OEM_2, [ssCtrl]);  // Divide '/'");
	SynEdit1->Lines->Add("  AddKey(ecUnfoldNearest, VK_OEM_2, [ssCtrl, ssShift]);");
	SynEdit1->Lines->Add("  AddKey(ecFoldLevel1, ord('K'), [ssCtrl], Ord('1'), [ssCtrl]);");
	SynEdit1->Lines->Add("  AddKey(ecFoldLevel2, ord('K'), [ssCtrl], Ord('2'), [ssCtrl]);");
	SynEdit1->Lines->Add("  AddKey(ecFoldLevel3, ord('K'), [ssCtrl], Ord('3'), [ssCtrl]);");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("  AddKey(ecUnfoldLevel1, ord('K'), [ssCtrl, ssShift], Ord('1'), [ssCtrl, ssShift]);");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("  AddKey(ecUnfoldLevel2, ord('K'), [ssCtrl, ssShift], Ord('2'), [ssCtrl, ssShift]);");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("  AddKey(ecUnfoldLevel3, ord('K'), [ssCtrl, ssShift], Ord('3'), [ssCtrl, ssShift]);");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("Note: The JavaScript, and Python highlighters are Code Folding enabled, but");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("the C++ highlighter is not.  Code folding for C++ is provided by a Synedit ");
	SynEdit1->Lines->Add("event handler (ScanForFoldRanges).");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("You can find technical information about the implementation of code folding");
	SynEdit1->Lines->Add("in the unit SynEditCodeFolding.pas.");
	SynEdit1->Options = TSynEditorOptions() << eoAutoIndent << eoDragDropEditing << eoEnhanceEndKey << eoGroupUndo << eoShowScrollHint << eoSmartTabDelete << eoSmartTabs << eoTabIndent << eoTabsToSpaces << eoTrimTrailingSpaces;
	SynEdit1->TabWidth = 4;
	SynEditPrint1 = new TSynEditPrint(this);
	//SynEditPrint1->Parent = this;
	SynEditPrint1->Copies = 1;
	SynEditPrint1->Header->DefaultFont->Charset = DEFAULT_CHARSET;
	SynEditPrint1->Header->DefaultFont->Color = clBlack;
	SynEditPrint1->Header->DefaultFont->Height-13;
	SynEditPrint1->Header->DefaultFont->Name = "Arial";
	//SynEditPrint1->Header->DefaultFont->Style;
	SynEditPrint1->Footer->DefaultFont->Charset = DEFAULT_CHARSET;
	SynEditPrint1->Footer->DefaultFont->Color = clBlack;
	SynEditPrint1->Footer->DefaultFont->Height-13;
	SynEditPrint1->Footer->DefaultFont->Name = "Arial";
	//SynEditPrint1->Footer->DefaultFont->Style;
	SynEditPrint1->Margins->Left = 25.000000000000000000;
	SynEditPrint1->Margins->Right = 15.000000000000000000;
	SynEditPrint1->Margins->Top = 25.000000000000000000;
	SynEditPrint1->Margins->Bottom = 25.000000000000000000;
	SynEditPrint1->Margins->Header = 15.000000000000000000;
	SynEditPrint1->Margins->Footer = 15.000000000000000000;
	SynEditPrint1->Margins->LeftHFTextIndent = 2.000000000000000000;
	SynEditPrint1->Margins->RightHFTextIndent = 2.000000000000000000;
	SynEditPrint1->Margins->HFInternalMargin = 0.500000000000000000;
	SynEditPrint1->Margins->MirrorMargins = False;
	SynEditPrint1->Font->Charset = DEFAULT_CHARSET;
	SynEditPrint1->Font->Color = clWindowText;
	SynEditPrint1->Font->Height-11;
	SynEditPrint1->Font->Name = "Tahoma";
	//SynEditPrint1->Font->Style;
	SynEditPrint1->TabWidth = 8;
	SynEditPrint1->Color = clWhite;
	//SynEditPrint1->Left = 472;
	//SynEditPrint1->Top = 176;
	SynCppSyn1 = new TSynCppSyn(this);
	//SynCppSyn1->Parent = this;
	SynCppSyn1->Options->AutoDetectEnabled = False;
	SynCppSyn1->Options->AutoDetectLineLimit = 0;
	SynCppSyn1->Options->Visible = False;
	//SynCppSyn1->Left = 524;
	//SynCppSyn1->Top = 80;
	SynJScriptSyn1 = new TSynJScriptSyn(this);
	//SynJScriptSyn1->Parent = this;
	SynJScriptSyn1->Options->AutoDetectEnabled = False;
	SynJScriptSyn1->Options->AutoDetectLineLimit = 0;
	SynJScriptSyn1->Options->Visible = False;
	//SynJScriptSyn1->Left = 472;
	//SynJScriptSyn1->Top = 80;
	SynPythonSyn1 = new TSynPythonSyn(this);
	//SynPythonSyn1->Parent = this;
	SynPythonSyn1->Options->AutoDetectEnabled = False;
	SynPythonSyn1->Options->AutoDetectLineLimit = 0;
	SynPythonSyn1->Options->Visible = False;
	//SynPythonSyn1->Left = 480;
	//SynPythonSyn1->Top = 128;
	SynEditPythonBehaviour1 = new TSynEditPythonBehaviour(this);
	//SynEditPythonBehaviour1->Parent = this;
	SynEditPythonBehaviour1->Editor = SynEdit1;
	//SynEditPythonBehaviour1->Left = 536;
	//SynEditPythonBehaviour1->Top = 128;

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
