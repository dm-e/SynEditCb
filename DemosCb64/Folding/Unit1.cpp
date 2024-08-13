#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "SynEditTextBuffer.h"
#include "SynEditTypes.h"
#include "uHighlighterProcs.h"
#include "SynEditKeyCmds.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;


TForm1* Form1 = nullptr;

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
		for(stop = CurLine.Length(), i = StartCol; i <= stop; i++)
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
		for(stop = CurLine.Length(), Col = 1; Col <= stop; Col++)
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
		if((Synhighlightercpp::TRangeState)(NativeInt)((TSynEditStringList*) LinesToScan)->Ranges[(int) Line] == Synhighlightercpp::rsAnsiC)
		{
			if((Line == 0) || ((Synhighlightercpp::TRangeState)(NativeInt)((TSynEditStringList*) LinesToScan)->Ranges[(int) Line - 1] != Synhighlightercpp::rsAnsiC))
				TopFoldRanges->StartFoldRange((int) (Line + 1), 2);
			else
				TopFoldRanges->NoFoldInfo((int) (Line + 1));
			continue;
		}
		else
		{
			if((Line > 0) && ((Synhighlightercpp::TRangeState)(NativeInt)((TSynEditStringList*) LinesToScan)->Ranges[(int) Line - 1] == Synhighlightercpp::rsAnsiC))
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

__fastcall TForm1::TForm1(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	ActionManager1(nullptr),
	ActionMainMenuBar1(nullptr),
	PopupActionBar1(nullptr),
	FileOpen1(nullptr),
	FileSaveAs1(nullptr),
	FilePrintSetup1(nullptr),
	FilePageSetup1(nullptr),
	FileExit1(nullptr),
	DialogPrintDlg1(nullptr),
	EditCut1(nullptr),
	EditCopy1(nullptr),
	EditPaste1(nullptr),
	EditSelectAll1(nullptr),
	EditUndo1(nullptr),
	EditDelete1(nullptr),
	Cut1(nullptr),
	Copy1(nullptr),
	Paste1(nullptr),
	SynEdit1(nullptr),
	DialogFontEdit1(nullptr),
	ActSave(nullptr),
	SynEditPrint1(nullptr),
	actGutterLines(nullptr),
	SynCppSyn1(nullptr),
	SynJScriptSyn1(nullptr),
	SynPythonSyn1(nullptr),
	SynEditPythonBehaviour1(nullptr),
	actCPP(nullptr),
	actJavaScript(nullptr),
	actPython(nullptr),
	actCodeFolding(nullptr),
	actFoldAll(nullptr),
	actUnFoldAll(nullptr),
	actFoldNearest(nullptr),
	actFoldRegions(nullptr),
	actFoldLevel1(nullptr),
	actFoldLevel2(nullptr),
	actFoldLevel3(nullptr),
	actUnfoldNearest(nullptr),
	actUnfoldRegions(nullptr),
	actUnfoldLevel1(nullptr),
	actUnfoldLevel2(nullptr),
	actUnfoldLevel3(nullptr),
	N1(nullptr),
	N2(nullptr),
	Fold1(nullptr),
	All1(nullptr),
	Nearest1(nullptr),
	Ranges1(nullptr),
	N3(nullptr),
	Level11(nullptr),
	Level21(nullptr),
	Level31(nullptr),
	Unfold1(nullptr),
	All2(nullptr),
	Nearest2(nullptr),
	Ranges2(nullptr),
	N4(nullptr),
	Level12(nullptr),
	Level22(nullptr),
	Level32(nullptr),
	actShowCollapsedMarks(nullptr),
	actShowCollapsedLines(nullptr),
	actFoldShapeSize(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Left = 0;
	Top = 0;
	Caption = L"Folding Demo";
	ClientHeight = 402;
	ClientWidth = 635;
	Color = clBtnFace;
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = clWindowText;
	Font->Height = -11;
	Font->Name = L"Tahoma";
	Font->Style = (TFontStyles());
	OnCreate = FormCreate;
	OnDestroy = FormDestroy;
	AssignFormTextHeight(this, 13);
	ActionMainMenuBar1 = new TActionMainMenuBar(this);
	ActionMainMenuBar1->Parent = this;
	ActionMainMenuBar1->Left = 0;
	ActionMainMenuBar1->Top = 0;
	ActionMainMenuBar1->Width = 635;
	ActionMainMenuBar1->Height = 25;
	ActionMainMenuBar1->UseSystemFont = false;
	ActionMainMenuBar1->Caption = L"ActionMainMenuBar1";
	ActionMainMenuBar1->Color = clMenuBar;
	ActionMainMenuBar1->ColorMap->DisabledFontColor = 7171437;
	ActionMainMenuBar1->ColorMap->HighlightColor = clWhite;
	ActionMainMenuBar1->ColorMap->BtnSelectedFont = clBlack;
	ActionMainMenuBar1->ColorMap->UnusedColor = clWhite;
	ActionMainMenuBar1->Font->Charset = DEFAULT_CHARSET;
	ActionMainMenuBar1->Font->Color = clBlack;
	ActionMainMenuBar1->Font->Height = -12;
	ActionMainMenuBar1->Font->Name = L"Segoe UI";
	ActionMainMenuBar1->Font->Style = (TFontStyles());
	ActionMainMenuBar1->Spacing = 0;
	ActionManager1 = new TActionManager(this);
	ActionManager1->OnUpdate = ActionManager1Update;
	// non-visible component: Left
	// non-visible component: Top
	ActionManager1->StyleName = L"Platform Default";
	actShowCollapsedLines = new TAction(ActionManager1);
	actShowCollapsedLines->Category = L"Folding Options";
	actShowCollapsedLines->AutoCheck = true;
	actShowCollapsedLines->Caption = L"Collapsed Lines";
	actShowCollapsedLines->OnExecute = actShowCollapsedLinesExecute;
	FileOpen1 = new TFileOpen(ActionManager1);
	FileOpen1->Category = L"File";
	FileOpen1->Caption = L"&Open...";
	FileOpen1->Hint = L"Open|Opens an existing file";
	FileOpen1->ImageIndex = 7;
	FileOpen1->ShortCut = 16463;
	FileOpen1->OnAccept = FileOpen1Accept;
	ActSave = new TAction(ActionManager1);
	ActSave->Category = L"File";
	ActSave->Caption = L"Save";
	ActSave->OnExecute = ActSaveExecute;
	FileSaveAs1 = new TFileSaveAs(ActionManager1);
	FileSaveAs1->Category = L"File";
	FileSaveAs1->Caption = L"Save &As...";
	FileSaveAs1->Dialog->Options = (TOpenOptions() << ofOverwritePrompt << ofHideReadOnly << ofEnableSizing);
	FileSaveAs1->Hint = L"Save As|Saves the active file with a new name";
	FileSaveAs1->ImageIndex = 30;
	FileSaveAs1->OnAccept = FileSaveAs1Accept;
	FilePrintSetup1 = new TFilePrintSetup(ActionManager1);
	FilePrintSetup1->Category = L"File";
	FilePrintSetup1->Caption = L"Print Set&up...";
	FilePrintSetup1->Hint = L"Print Setup";
	FilePageSetup1 = new TFilePageSetup(ActionManager1);
	FilePageSetup1->Category = L"File";
	FilePageSetup1->Caption = L"Page Set&up...";
	FilePageSetup1->Dialog->MinMarginLeft = 0;
	FilePageSetup1->Dialog->MinMarginTop = 0;
	FilePageSetup1->Dialog->MinMarginRight = 0;
	FilePageSetup1->Dialog->MinMarginBottom = 0;
	FilePageSetup1->Dialog->MarginLeft = 2500;
	FilePageSetup1->Dialog->MarginTop = 2500;
	FilePageSetup1->Dialog->MarginRight = 2500;
	FilePageSetup1->Dialog->MarginBottom = 2500;
	FilePageSetup1->Dialog->PageWidth = 21590;
	FilePageSetup1->Dialog->PageHeight = 27940;
	DialogPrintDlg1 = new TPrintDlg(ActionManager1);
	DialogPrintDlg1->Category = L"File";
	DialogPrintDlg1->Caption = L"&Print...";
	DialogPrintDlg1->ImageIndex = 14;
	DialogPrintDlg1->ShortCut = 16464;
	DialogPrintDlg1->OnAccept = DialogPrintDlg1Accept;
	FileExit1 = new TFileExit(ActionManager1);
	FileExit1->Category = L"File";
	FileExit1->Caption = L"E&xit";
	FileExit1->Hint = L"Exit|Quits the application";
	FileExit1->ImageIndex = 43;
	EditCut1 = new TEditCut(ActionManager1);
	EditCut1->Category = L"Edit";
	EditCut1->Caption = L"Cu&t";
	EditCut1->Hint = L"Cut|Cuts the selection and puts it on the Clipboard";
	EditCut1->ImageIndex = 0;
	EditCut1->ShortCut = 16472;
	EditCopy1 = new TEditCopy(ActionManager1);
	EditCopy1->Category = L"Edit";
	EditCopy1->Caption = L"&Copy";
	EditCopy1->Hint = L"Copy|Copies the selection and puts it on the Clipboard";
	EditCopy1->ImageIndex = 1;
	EditCopy1->ShortCut = 16451;
	EditPaste1 = new TEditPaste(ActionManager1);
	EditPaste1->Category = L"Edit";
	EditPaste1->Caption = L"&Paste";
	EditPaste1->Hint = L"Paste|Inserts Clipboard contents";
	EditPaste1->ImageIndex = 2;
	EditPaste1->ShortCut = 16470;
	EditSelectAll1 = new TEditSelectAll(ActionManager1);
	EditSelectAll1->Category = L"Edit";
	EditSelectAll1->Caption = L"Select &All";
	EditSelectAll1->Hint = L"Select All|Selects the entire document";
	EditSelectAll1->ShortCut = 16449;
	EditUndo1 = new TEditUndo(ActionManager1);
	EditUndo1->Category = L"Edit";
	EditUndo1->Caption = L"&Undo";
	EditUndo1->Hint = L"Undo|Reverts the last action";
	EditUndo1->ImageIndex = 3;
	EditUndo1->ShortCut = 16474;
	EditDelete1 = new TEditDelete(ActionManager1);
	EditDelete1->Category = L"Edit";
	EditDelete1->Caption = L"&Delete";
	EditDelete1->Hint = L"Delete|Erases the selection";
	EditDelete1->ImageIndex = 5;
	EditDelete1->ShortCut = 46;
	DialogFontEdit1 = new TFontEdit(ActionManager1);
	DialogFontEdit1->Category = L"View";
	DialogFontEdit1->Caption = L"Select &Font...";
	DialogFontEdit1->Dialog->Font->Charset = DEFAULT_CHARSET;
	DialogFontEdit1->Dialog->Font->Color = clWindowText;
	DialogFontEdit1->Dialog->Font->Height = -11;
	DialogFontEdit1->Dialog->Font->Name = L"Tahoma";
	DialogFontEdit1->Dialog->Font->Style = (TFontStyles());
	DialogFontEdit1->Dialog->Options = (TFontDialogOptions() << fdEffects << fdFixedPitchOnly);
	DialogFontEdit1->Dialog->OnApply = DialogFontEdit1FontDialogApply;
	DialogFontEdit1->Hint = L"Font Select";
	DialogFontEdit1->BeforeExecute = DialogFontEdit1BeforeExecute;
	actGutterLines = new TAction(ActionManager1);
	actGutterLines->Category = L"View";
	actGutterLines->AutoCheck = true;
	actGutterLines->Caption = L"Gutter Lines";
	actGutterLines->OnExecute = actGutterLinesExecute;
	actCPP = new TAction(ActionManager1);
	actCPP->Category = L"Highlighter";
	actCPP->Caption = L"C++";
	actCPP->OnExecute = actCPPExecute;
	actJavaScript = new TAction(ActionManager1);
	actJavaScript->Category = L"Highlighter";
	actJavaScript->Caption = L"JavaScript";
	actJavaScript->OnExecute = actJavaScriptExecute;
	actPython = new TAction(ActionManager1);
	actPython->Category = L"Highlighter";
	actPython->Caption = L"Python";
	actPython->OnExecute = actPythonExecute;
	actCodeFolding = new TAction(ActionManager1);
	actCodeFolding->Category = L"View";
	actCodeFolding->AutoCheck = true;
	actCodeFolding->Caption = L"Code Folding";
	actCodeFolding->OnExecute = actCodeFoldingExecute;
	actFoldAll = new TAction(ActionManager1);
	actFoldAll->Category = L"Fold";
	actFoldAll->Caption = L"All";
	actFoldAll->OnExecute = actFoldExecute;
	actFoldAll->OnUpdate = actFoldUpdate;
	actUnFoldAll = new TAction(ActionManager1);
	actUnFoldAll->Category = L"Unfold";
	actUnFoldAll->Caption = L"All";
	actUnFoldAll->OnExecute = actFoldExecute;
	actUnFoldAll->OnUpdate = actFoldUpdate;
	actFoldNearest = new TAction(ActionManager1);
	actFoldNearest->Category = L"Fold";
	actFoldNearest->Caption = L"Nearest";
	actFoldNearest->OnExecute = actFoldExecute;
	actFoldNearest->OnUpdate = actFoldUpdate;
	actFoldRegions = new TAction(ActionManager1);
	actFoldRegions->Category = L"Fold";
	actFoldRegions->Caption = L"Regions";
	actFoldRegions->OnExecute = actFoldExecute;
	actFoldRegions->OnUpdate = actFoldUpdate;
	actFoldLevel1 = new TAction(ActionManager1);
	actFoldLevel1->Category = L"Fold";
	actFoldLevel1->Caption = L"Level 1";
	actFoldLevel1->OnExecute = actFoldExecute;
	actFoldLevel1->OnUpdate = actFoldUpdate;
	actFoldLevel2 = new TAction(ActionManager1);
	actFoldLevel2->Category = L"Fold";
	actFoldLevel2->Caption = L"Level 2";
	actFoldLevel2->OnExecute = actFoldExecute;
	actFoldLevel2->OnUpdate = actFoldUpdate;
	actFoldLevel3 = new TAction(ActionManager1);
	actFoldLevel3->Category = L"Fold";
	actFoldLevel3->Caption = L"Level 3";
	actFoldLevel3->OnExecute = actFoldExecute;
	actFoldLevel3->OnUpdate = actFoldUpdate;
	actUnfoldNearest = new TAction(ActionManager1);
	actUnfoldNearest->Category = L"Unfold";
	actUnfoldNearest->Caption = L"Nearest";
	actUnfoldNearest->OnExecute = actFoldExecute;
	actUnfoldNearest->OnUpdate = actFoldUpdate;
	actUnfoldRegions = new TAction(ActionManager1);
	actUnfoldRegions->Category = L"Unfold";
	actUnfoldRegions->Caption = L"Regions";
	actUnfoldRegions->OnExecute = actFoldExecute;
	actUnfoldRegions->OnUpdate = actFoldUpdate;
	actUnfoldLevel1 = new TAction(ActionManager1);
	actUnfoldLevel1->Category = L"Unfold";
	actUnfoldLevel1->Caption = L"Level 1";
	actUnfoldLevel1->OnExecute = actFoldExecute;
	actUnfoldLevel1->OnUpdate = actFoldUpdate;
	actUnfoldLevel2 = new TAction(ActionManager1);
	actUnfoldLevel2->Category = L"Unfold";
	actUnfoldLevel2->Caption = L"Level 2";
	actUnfoldLevel2->OnExecute = actFoldExecute;
	actUnfoldLevel2->OnUpdate = actFoldUpdate;
	actUnfoldLevel3 = new TAction(ActionManager1);
	actUnfoldLevel3->Category = L"Unfold";
	actUnfoldLevel3->Caption = L"Level 3";
	actUnfoldLevel3->OnExecute = actFoldExecute;
	actUnfoldLevel3->OnUpdate = actFoldUpdate;
	actShowCollapsedMarks = new TAction(ActionManager1);
	actShowCollapsedMarks->Category = L"Folding Options";
	actShowCollapsedMarks->AutoCheck = true;
	actShowCollapsedMarks->Caption = L"Collapsed Marks";
	actShowCollapsedMarks->Checked = true;
	actShowCollapsedMarks->OnExecute = actShowCollapsedMarksExecute;
	actFoldShapeSize = new TAction(ActionManager1);
	actFoldShapeSize->Category = L"Folding Options";
	actFoldShapeSize->Caption = L"Gutter Square Size..";
	actFoldShapeSize->OnExecute = actFoldShapeSizeExecute;
	ActionManager1->ActionBars->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[0]->Action = FileOpen1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[0]->ImageIndex = 7;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[0]->ShortCut = (TShortCut) 16463;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[1]->Action = ActSave;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[1]->Caption = L"&Save";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[2]->Action = FileSaveAs1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[2]->ImageIndex = 30;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[3]->Caption = L"-";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[4]->Action = FilePrintSetup1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[5]->Action = FilePageSetup1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[5]->Caption = L"Pa&ge Setup...";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[6]->Action = DialogPrintDlg1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[6]->Caption = L"P&rint...";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[6]->ImageIndex = 14;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[6]->ShortCut = (TShortCut) 16464;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[7]->Caption = L"-";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[8]->Action = FileExit1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Items->ActionClients[8]->ImageIndex = 43;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[0]->Caption = L"&File";
	ActionManager1->ActionBars->ActionBars[0]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[0]->Action = EditCut1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[0]->ImageIndex = 0;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[0]->ShortCut = (TShortCut) 16472;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[1]->Action = EditCopy1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[1]->ImageIndex = 1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[1]->ShortCut = (TShortCut) 16451;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[2]->Action = EditPaste1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[2]->ImageIndex = 2;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[2]->ShortCut = (TShortCut) 16470;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[3]->Action = EditSelectAll1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[3]->ShortCut = (TShortCut) 16449;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[4]->Action = EditUndo1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[4]->ImageIndex = 3;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[4]->ShortCut = (TShortCut) 16474;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[5]->Action = EditDelete1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[5]->ImageIndex = 5;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Items->ActionClients[5]->ShortCut = (TShortCut) 46;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[1]->Caption = L"&Edit";
	ActionManager1->ActionBars->ActionBars[0]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[0]->Action = DialogFontEdit1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[1]->Action = actGutterLines;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[1]->Caption = L"&Gutter Lines";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[2]->Caption = L"-";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[3]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[3]->Items->ActionClients[0]->Action = actCPP;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[3]->Items->ActionClients[0]->Caption = L"&C++";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[3]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[3]->Items->ActionClients[1]->Action = actJavaScript;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[3]->Items->ActionClients[1]->Caption = L"&JavaScript";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[3]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[3]->Items->ActionClients[2]->Action = actPython;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[3]->Items->ActionClients[2]->Caption = L"&Python";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[3]->Caption = L"&Highlighter";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[3]->UsageCount = 1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[4]->Caption = L"-";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[5]->Action = actCodeFolding;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[5]->Caption = L"&Code Folding";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->Items->ActionClients[0]->Action = actShowCollapsedLines;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->Items->ActionClients[0]->Caption = L"&Collapsed Lines";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->Items->ActionClients[1]->Action = actShowCollapsedMarks;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->Items->ActionClients[1]->Caption = L"C&ollapsed Marks";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->Items->ActionClients[2]->Caption = L"-";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->Items->ActionClients[3]->Action = actFoldShapeSize;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->Items->ActionClients[3]->Caption = L"&Gutter Square Size..";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->Caption = L"Fo&lding Options";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[6]->UsageCount = 1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[7]->Caption = L"-";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->ActionClients[0]->Action = actFoldAll;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->ActionClients[0]->Caption = L"&All";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->ActionClients[1]->Action = actFoldNearest;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->ActionClients[1]->Caption = L"&Nearest";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->ActionClients[2]->Action = actFoldRegions;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->ActionClients[2]->Caption = L"&Regions";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->ActionClients[3]->Action = actFoldLevel1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->ActionClients[3]->Caption = L"&Level 1";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->ActionClients[4]->Action = actFoldLevel2;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->ActionClients[4]->Caption = L"L&evel 2";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->ActionClients[5]->Action = actFoldLevel3;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Items->ActionClients[5]->Caption = L"Le&vel 3";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->Caption = L"F&old";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[8]->UsageCount = 1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->ActionClients[0]->Action = actUnFoldAll;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->ActionClients[0]->Caption = L"&All";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->ActionClients[1]->Action = actUnfoldNearest;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->ActionClients[1]->Caption = L"&Nearest";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->ActionClients[2]->Action = actUnfoldRegions;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->ActionClients[2]->Caption = L"&Regions";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->ActionClients[3]->Action = actUnfoldLevel1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->ActionClients[3]->Caption = L"&Level 1";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->ActionClients[4]->Action = actUnfoldLevel2;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->ActionClients[4]->Caption = L"L&evel 2";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->Add();
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->ActionClients[5]->Action = actUnfoldLevel3;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Items->ActionClients[5]->Caption = L"Le&vel 3";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->Caption = L"&Unfold";
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Items->ActionClients[9]->UsageCount = 1;
	ActionManager1->ActionBars->ActionBars[0]->Items->ActionClients[2]->Caption = L"&View";
	ActionManager1->ActionBars->ActionBars[0]->ActionBar = ActionMainMenuBar1;
	PopupActionBar1 = new TPopupActionBar(this);
	// non-visible component: Left
	// non-visible component: Top
	N1 = new TMenuItem(PopupActionBar1);
	N1->Caption = L"-";
	Cut1 = new TMenuItem(PopupActionBar1);
	Copy1 = new TMenuItem(PopupActionBar1);
	Paste1 = new TMenuItem(PopupActionBar1);
	N2 = new TMenuItem(PopupActionBar1);
	N2->Caption = L"-";
	Fold1 = new TMenuItem(PopupActionBar1);
	Fold1->Caption = L"Fold";
	All1 = CreateTMenuItemTMenuItem(Fold1);
	Nearest1 = CreateTMenuItemTMenuItem(Fold1);
	Ranges1 = CreateTMenuItemTMenuItem(Fold1);
	N3 = CreateTMenuItemTMenuItem(Fold1);
	N3->Caption = L"-";
	Level11 = CreateTMenuItemTMenuItem(Fold1);
	Level21 = CreateTMenuItemTMenuItem(Fold1);
	Level31 = CreateTMenuItemTMenuItem(Fold1);
	Unfold1 = new TMenuItem(PopupActionBar1);
	Unfold1->Caption = L"Unfold";
	All2 = CreateTMenuItemTMenuItem(Unfold1);
	Nearest2 = CreateTMenuItemTMenuItem(Unfold1);
	Ranges2 = CreateTMenuItemTMenuItem(Unfold1);
	N4 = CreateTMenuItemTMenuItem(Unfold1);
	N4->Caption = L"-";
	Level12 = CreateTMenuItemTMenuItem(Unfold1);
	Level22 = CreateTMenuItemTMenuItem(Unfold1);
	Level32 = CreateTMenuItemTMenuItem(Unfold1);
	ComponentState >> csLoading;
	//----- shifted initializations from the dfm-file ---------------------------
	ActionMainMenuBar1->ActionManager = ActionManager1;
	Cut1->Action = EditCut1;
	Copy1->Action = EditCopy1;
	Paste1->Action = EditPaste1;
	All1->Action = actFoldAll;
	Nearest1->Action = actFoldNearest;
	Ranges1->Action = actFoldRegions;
	Level11->Action = actFoldLevel1;
	Level21->Action = actFoldLevel2;
	Level31->Action = actFoldLevel3;
	All2->Action = actUnFoldAll;
	Nearest2->Action = actUnfoldNearest;
	Ranges2->Action = actUnfoldRegions;
	Level12->Action = actUnfoldLevel1;
	Level22->Action = actUnfoldLevel2;
	Level32->Action = actUnfoldLevel3;
	//----- end of initializations from the dfm-file ----------------------------
}

