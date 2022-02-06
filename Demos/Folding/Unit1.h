#ifndef Unit1H
#define Unit1H

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Variants.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include "SynEdit.hpp"
#include <Vcl.Menus.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.ActnList.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnPopup.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include "SynEditPrint.hpp"
#include "SynEditPythonBehaviour.hpp"
#include "SynHighlighterPython.hpp"
#include "SynHighlighterJScript.hpp"
#include "SynEditHighlighter.hpp"
#include "SynHighlighterCpp.hpp"
#include "SynEditCodeFolding.hpp"



class TForm1 : public TForm
{
__published:
	TActionManager* ActionManager1;
	TActionMainMenuBar* ActionMainMenuBar1;
	TPopupActionBar* PopupActionBar1;
	TFileOpen* FileOpen1;
	TFileSaveAs* FileSaveAs1;
	TFilePrintSetup* FilePrintSetup1;
	TFilePageSetup* FilePageSetup1;
	TFileExit* FileExit1;
	TPrintDlg* DialogPrintDlg1;
	TEditCut* EditCut1;
	TEditCopy* EditCopy1;
	TEditPaste* EditPaste1;
	TEditSelectAll* EditSelectAll1;
	TEditUndo* EditUndo1;
	TEditDelete* EditDelete1;
	TMenuItem* Cut1;
	TMenuItem* Copy1;
	TMenuItem* Paste1;
	TSynEdit* SynEdit1;
	TFontEdit* DialogFontEdit1;
	TAction* ActSave;
	TSynEditPrint* SynEditPrint1;
	TAction* actGutterLines;
	TSynCppSyn* SynCppSyn1;
	TSynJScriptSyn* SynJScriptSyn1;
	TSynPythonSyn* SynPythonSyn1;
	TSynEditPythonBehaviour* SynEditPythonBehaviour1;
	TAction* actCPP;
	TAction* actJavaScript;
	TAction* actPython;
	TAction* actCodeFolding;
	TAction* actFoldAll;
	TAction* actUnFoldAll;
	TAction* actFoldNearest;
	TAction* actFoldRegions;
	TAction* actFoldLevel1;
	TAction* actFoldLevel2;
	TAction* actFoldLevel3;
	TAction* actUnfoldNearest;
	TAction* actUnfoldRegions;
	TAction* actUnfoldLevel1;
	TAction* actUnfoldLevel2;
	TAction* actUnfoldLevel3;
	TMenuItem* N1;
	TMenuItem* N2;
	TMenuItem* Fold1;
	TMenuItem* All1;
	TMenuItem* Nearest1;
	TMenuItem* Ranges1;
	TMenuItem* N3;
	TMenuItem* Level11;
	TMenuItem* Level21;
	TMenuItem* Level31;
	TMenuItem* Unfold1;
	TMenuItem* All2;
	TMenuItem* Nearest2;
	TMenuItem* Ranges2;
	TMenuItem* N4;
	TMenuItem* Level12;
	TMenuItem* Level22;
	TMenuItem* Level32;
	TAction* actShowCollapsedMarks;
	TAction* actShowCollapsedLines;
	TAction* actFoldShapeSize;
	void __fastcall FileOpen1Accept(TObject* Sender);
	void __fastcall FileSaveAs1Accept(TObject* Sender);
	void __fastcall ActSaveExecute(TObject* Sender);
	void __fastcall DialogPrintDlg1Accept(TObject* Sender);
	void __fastcall DialogFontEdit1FontDialogApply(TObject* Sender, HWND Wnd);
	void __fastcall actGutterLinesExecute(TObject* Sender);
	void __fastcall actCPPExecute(TObject* Sender);
	void __fastcall actJavaScriptExecute(TObject* Sender);
	void __fastcall actPythonExecute(TObject* Sender);
	void __fastcall actCodeFoldingExecute(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormDestroy(TObject* Sender);
	void __fastcall ScanForFoldRanges(TObject* Sender, TSynFoldRanges* TopFoldRanges, TStrings* LinesToScan, int FromLine, int ToLine);
	void __fastcall DialogFontEdit1BeforeExecute(TObject* Sender);
	void __fastcall actFoldExecute(TObject* Sender);
	void __fastcall actFoldUpdate(TObject* Sender);
	void __fastcall ActionManager1Update(TBasicAction* Action, bool& Handled);
	void __fastcall actShowCollapsedLinesExecute(TObject* Sender);
	void __fastcall actShowCollapsedMarksExecute(TObject* Sender);
	void __fastcall actFoldShapeSizeExecute(TObject* Sender);
private:
    /* Private declarations */
	TStringList* highlighters;
public:
    /* Public declarations */
	String FileName;
	typedef TForm inherited;	
	__fastcall TForm1(TComponent* AOwner);
};
extern PACKAGE TForm1* Form1;
#endif // Unit1H

