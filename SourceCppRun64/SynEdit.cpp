#include <vcl.h>
#pragma hdrstop

#include "SynEdit.h"
#include <System.Types.hpp>
#include <Vcl.Consts.hpp>
#include <System.Character.hpp>
#include <Vcl.Clipbrd.hpp>
#include <Winapi.ShellAPI.hpp>
#include "SynEditUndo.h"
#include "SynEditWordWrap.h"
#include "SynEditStrConst.h"
#include "SynEditDataObject.h"
#include "SynEditDragDrop.h"
#include "d2c_convert.h"
#include "d2c_syshelper.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Syneditdataobject;
using namespace Syneditdragdrop;
using namespace Synedithighlighter;
using namespace Syneditkbdhandler;
using namespace Syneditkeycmds;
using namespace Syneditkeyconst;
using namespace Syneditmiscclasses;
using namespace Syneditmiscprocs;
using namespace Syneditstrconst;
using namespace Synedittextbuffer;
using namespace Synedittypes;
using namespace Syneditundo;
using namespace Syneditwordwrap;
using namespace Syntextdrawer;
using namespace Synunicode;
using namespace System;
using namespace System::Character;
using namespace System::Contnrs;
using namespace System::Sysutils;
using namespace System::Types;
using namespace System::Uitypes;
using namespace Vcl::Clipbrd;
using namespace Vcl::Consts;
using namespace Vcl::Controls;
using namespace Vcl::Forms;
using namespace Vcl::Graphics;
using namespace Winapi::Activex;
using namespace Winapi::Imm;
using namespace Winapi::Shellapi;

namespace Synedit
{
// dme
bool RemovedKeystroke(TSynEdit* xpSynEdit, const String xsCmd, int xiShiftState)
{
	int cmd;
	if(IdentToEditorCommand(xsCmd, cmd))
	{
		Word NewKey;
		TShiftState NewShift;
		std::shared_ptr<TSynEditKeyStroke> iKey(new TSynEditKeyStroke(nullptr));
		iKey->Command = cmd;
		ShortCutToKey(xiShiftState, NewKey, NewShift);
		iKey->Key = NewKey;
		iKey->Shift = NewShift;
		int iToDelete = xpSynEdit->Keystrokes->FindShortcut2(iKey->ShortCut, iKey->ShortCut2);
		if (iToDelete >= 0 && xpSynEdit->Keystrokes->Items[iToDelete]->Command == iKey->Command)
			xpSynEdit->Keystrokes->Delete(iToDelete);
	}
}


#define Synedit__1 (TControlStyle() << csOpaque << csSetCaption)
#define Synedit__2 (TControlStyle() << csNeedsBorderPaint)
#define Synedit__3 (TFontStyles() << TFontStyle::fsBold)
#define Synedit__4 (TSynStatusChanges() << scCaretX << scCaretY)
#define Synedit__5 TSynStatusChanges()
#define Synedit__6 TSynStatusChanges()
#define Synedit__7 (TShiftState() << ssDouble)
#define Synedit__8 (TShiftState() << ssLeft << ssDouble)
#define Synedit__9 (System::Set<TMouseButton, TMouseButton::mbLeft, TMouseButton::mbMiddle>() << TMouseButton::mbLeft << TMouseButton::mbRight)
#define Synedit__10 (TShiftState() << ssAlt << ssLeft)
#define Synedit__11 (TShiftState() << ssLeft)
#define Synedit__12 (TShiftState() << ssRight)
#define Synedit__13 (TSynStateFlags() << sfPossibleGutterClick << sfGutterDragging)
#define Synedit__14 (TSynStateFlags() << sfPossibleGutterClick)
#define Synedit__15 TFontStyles()
#define Synedit__16 TFontStyles()
#define Synedit__17 TFontStyles()
#define Synedit__18 TFontStyles()
#define Synedit__19 TTextOutOptions()
#define Synedit__20 TFontStyles()
#define Synedit__21 (TReplaceFlags() << rfReplaceAll)
#define Synedit__22 (TSynStatusChanges() << scSelection)
#define Synedit__23 (TSynStatusChanges() << scSelection)
#define Synedit__24 (TSynStatusChanges() << scLeftChar)
#define Synedit__25 (TComponentState() << csDesigning << csLoading)
#define Synedit__26 (TComponentState() << csDesigning)
#define Synedit__27 (TSynEditorOptions() << eoScrollPastEol << eoTrimTrailingSpaces)
#define Synedit__28 (TSynStatusChanges() << scCaretX)
#define Synedit__29 (TSynStatusChanges() << scCaretX)
#define Synedit__30 (TSynStatusChanges() << scTopLine)
#define Synedit__31 (System::Set<TScrollStyle, TScrollStyle::ssNone, TScrollStyle::ssBoth>() << TScrollStyle::ssBoth << TScrollStyle::ssHorizontal)
#define Synedit__32 (System::Set<TScrollStyle, TScrollStyle::ssNone, TScrollStyle::ssBoth>() << TScrollStyle::ssBoth << TScrollStyle::ssVertical)
#define Synedit__33 (System::Set<int, 0, 255>() <<  \
										0 << 1 << 2 << 3 << 4 << 5 <<  \
										6 << 7 << 8 << 9)
#define Synedit__34 (System::Set<int, 0, 255>() <<  \
										0 << 1 << 2 << 3 << 4 << 5 <<  \
										6 << 7 << 8 << 9)
#define Synedit__35 (System::Set<int, 0, 255>() <<  \
										0 << 1 << 2 << 3 << 4 << 5 <<  \
										6 << 7 << 8 << 9)
#define Synedit__36 (TSynStatusChanges() << scInsertMode)
#define Synedit__37 TShiftState()
#define Synedit__38 (System::Set<WORD, 0, 255>() << ecPageUp << ecSelPageUp)
#define Synedit__39 (System::Set<WORD, 0, 255>() << ecPageUp << ecSelPageUp)
#define Synedit__40 (System::Set<WORD, 0, 255>() << ecPageDown << ecSelPageDown)
#define Synedit__41 (System::Set<WORD, 0, 255>() << ecSelPageUp << ecSelPageDown)
#define Synedit__42 (TSynStatusChanges() << scSelection)
#define Synedit__43 (TComponentState() << csLoading << csDestroying)
#define Synedit__44 TComponentState()
#define Synedit__45 (TFontStyles() << TFontStyle::fsItalic << TFontStyle::fsBold)
#define Synedit__46 (TFontStyles() << TFontStyle::fsItalic << TFontStyle::fsBold)
#define Synedit__47 (TSysCharSet() << '\x20' << '\x09')
#define Synedit__48 (TSysCharSet() << '\x20' << '\x09')
#define Synedit__49 (TSynStatusChanges() << scModified)
#define Synedit__50 (TSynStatusChanges() << scReadOnly)
#define Synedit__51 TSynStatusChanges()
#define Synedit__52 (TSynStatusChanges() << scModified)
#define Synedit__53 (TSynSearchOptions() << ssoReplaceAll)
#define Synedit__54 (TSynSearchOptions() << ssoReplace)
#define Synedit__55 (TSynSearchOptions() << ssoSelectedOnly)
#define Synedit__56 (TSynSearchOptions() << ssoMatchCase)
#define Synedit__57 (TSynSearchOptions() << ssoWholeWord)
#define Synedit__58 (TSynSearchOptions() << ssoBackwards)

__fastcall ESynEditError::ESynEditError(const String Msg) : inherited(Msg) {}
__fastcall ESynEditError::ESynEditError(const String Msg, const TVarRec* Args, int Args_maxidx) : inherited(Msg, Args, Args_maxidx) {}
__fastcall ESynEditError::ESynEditError(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Msg, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynEditError::ESynEditError(const String Msg, int AHelpContext) : inherited(Msg, AHelpContext) {}
__fastcall ESynEditError::ESynEditError(System::NativeUInt Ident) : inherited(Ident) {}
__fastcall ESynEditError::ESynEditError(System::PResStringRec ResStringRec) : inherited(ResStringRec) {}
__fastcall ESynEditError::ESynEditError(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx) : inherited(Ident, Args, Args_maxidx) {}
__fastcall ESynEditError::ESynEditError(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx) : inherited(ResStringRec, Args, Args_maxidx) {}
__fastcall ESynEditError::ESynEditError(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(ResStringRec, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynEditError::ESynEditError(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Ident, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynEditError::ESynEditError(System::NativeUInt Ident, int AHelpContext) : inherited(Ident, AHelpContext) {}
__fastcall ESynEditError::ESynEditError(System::PResStringRec ResStringRec, int AHelpContext) : inherited(ResStringRec, AHelpContext) {}
__fastcall TSynEditMark::TSynEditMark() {}
__fastcall TSynEditMarkList::TSynEditMarkList() {}
__fastcall TSynEditMarkList::TSynEditMarkList(bool AOwnsObjects) : inherited(AOwnsObjects) {}
__fastcall TSynEditPlugin::TSynEditPlugin() {}
__fastcall TCustomSynEdit::TCustomSynEdit(HWND ParentWindow) : inherited(ParentWindow) {}
__fastcall TSynEdit::TSynEdit(TComponent* AOwner) : inherited(AOwner) {}
__fastcall TSynEdit::TSynEdit(HWND ParentWindow) : inherited(ParentWindow) {}


//#pragma resource "SynEdit.res" 


WORD __fastcall CeilOfIntDiv(unsigned int Dividend, WORD Divisor)
{
	WORD result = 0;
	WORD Remainder = 0;
	DivMod(Dividend, Divisor, result, Remainder);
	if(Remainder > 0)
		++result;
	return result;
}

String __fastcall TrimTrailingSpaces(const String S)
{
	String result;
	int I = 0;
	I = S.Length();
	while((I > 0) && ((S[I] == L'\x20') || (S[I] == L'\x09')))
		--I;
	result = S.SubString(1, I);
	return result;
}

/* THookedCommandHandlerEntry */

class THookedCommandHandlerEntry : public TObject
{
	#include "SynEdit_friends.inc"
public:
	typedef TObject inherited;
private:
	THookedCommandEvent fEvent;
	void* fData;
	__fastcall THookedCommandHandlerEntry(THookedCommandEvent AEvent, void* AData);
	HIDESBASE bool __fastcall Equals(THookedCommandEvent AEvent)/*# reintroduce */;
public:
	__fastcall THookedCommandHandlerEntry() {}
};

__fastcall THookedCommandHandlerEntry::THookedCommandHandlerEntry(THookedCommandEvent AEvent, void* AData)
 : fData(nullptr)
{
	//# inherited::Create();
	fEvent = AEvent;
	fData = AData;
}

bool __fastcall THookedCommandHandlerEntry::Equals(THookedCommandEvent AEvent)
{
	bool result = false;
	/*# with TMethod(fEvent) do */
	{
		auto& with0 = *((TMethod*) &fEvent);
		result = (with0.Code == ((TMethod*) &AEvent)->Code) && (with0.Data == ((TMethod*) &AEvent)->Data);
	}
	return result;
}

/* TCustomSynEdit */
// Result is in display coordinates

TDisplayCoord __fastcall TCustomSynEdit::PixelsToNearestRowColumn(int aX, int aY)
{
	TDisplayCoord result = {};
	float f = 0.0F;
	f = (float) (double((aX - fGutterWidth - fTextMargin)) / fCharWidth);
  // don't return a partially visible last line
	if(aY >= fLinesInWindow * fTextHeight)
	{
		aY = fLinesInWindow * fTextHeight - 1;
		if(aY < 0)
			aY = 0;
	}
	result.Column = (int) Max(1, (int) (LeftChar + Round(f)));
	result.Row = Max(1, TopLine + ((int)(aY / /*div*/ fTextHeight)));
	return result;
}

TDisplayCoord __fastcall TCustomSynEdit::PixelsToRowColumn(int aX, int aY)
{
	TDisplayCoord result = {};
	result.Column = Max(1, LeftChar + ((int)((aX - fGutterWidth - fTextMargin) / /*div*/ fCharWidth)));
	result.Row = Max(1, TopLine + ((int)(aY / /*div*/ fTextHeight)));
	return result;
}

TPoint __fastcall TCustomSynEdit::RowColumnToPixels(const TDisplayCoord& RowCol)
{
	TPoint result = {};
	result.X = (RowCol.Column - 1) * fCharWidth + fTextOffset;
	result.Y = (RowCol.Row - fTopLine) * fTextHeight;
	return result;
}
//X,Y are pixel coordinates

void __fastcall TCustomSynEdit::ComputeCaret(int X, int Y)
{
	TDisplayCoord vCaretNearestPos = {};
	vCaretNearestPos = PixelsToNearestRowColumn(X, Y);
	vCaretNearestPos.Row = MinMax(vCaretNearestPos.Row, 1, DisplayLineCount);
	SetInternalDisplayXY(vCaretNearestPos);
}
//X,Y are pixel coordinates

void __fastcall TCustomSynEdit::ComputeScroll(int X, int Y)
{
	TRect iScrollBounds = {}; /* relative to the client area */
	int ScrollAreaSize = 0;
	const int ScrollAreaDefaultSize = 4;
	iScrollBounds = Bounds(fGutterWidth, 0, fCharsInWindow * fCharWidth, fLinesInWindow * fTextHeight);
	ScrollAreaSize = 0;
	if(fStateFlags.Contains(sfOleDragSource))
		ScrollAreaSize += ScrollAreaDefaultSize;
	if(BorderStyle == bsNone)
		ScrollAreaSize += 2;
	InflateRect(iScrollBounds, -MulDiv(ScrollAreaSize, FCurrentPPI, 96), -MulDiv(ScrollAreaSize, FCurrentPPI, 96));
	if((X < iScrollBounds.Left) && (LeftChar > 1))
		fScrollDeltaX = (int)((X - iScrollBounds.Left) / /*div*/ fCharWidth) - 1;
	else
	{
		if(X >= iScrollBounds.Right)
			fScrollDeltaX = (int)((X - iScrollBounds.Right) / /*div*/ fCharWidth) + 1;
		else
			fScrollDeltaX = 0;
	}
	if((Y < iScrollBounds.Top) && (TopLine > 1))
		fScrollDeltaY = (int)((Y - iScrollBounds.Top) / /*div*/ fTextHeight) - 1;
	else
	{
		if(Y >= iScrollBounds.Bottom)
			fScrollDeltaY = (int)((Y - iScrollBounds.Bottom) / /*div*/ fTextHeight) + 1;
		else
			fScrollDeltaY = 0;
	}
	fScrollTimer->Enabled = (fScrollDeltaX != 0) || (fScrollDeltaY != 0);
}

void __fastcall TCustomSynEdit::DoCopyToClipboard(const String SText)
{
	OleSetClipboard(new TSynEditDataObject(this));
}

void __fastcall TCustomSynEdit::CopyToClipboard()
{
	String SText;
	bool ChangeTrim = false;
	if(SelAvail)
	{
		ChangeTrim = (fActiveSelectionMode == smColumn) && (Options.Contains(eoTrimTrailingSpaces));
		try
		{
			if(ChangeTrim)
				fOptions >> eoTrimTrailingSpaces;
			SText = SelText;
		}
		__finally
		{
			if(ChangeTrim)
				fOptions << eoTrimTrailingSpaces;
		}
		DoCopyToClipboard(SText);
	}
}

void __fastcall TCustomSynEdit::CutToClipboard()
{
	if(!ReadOnly && SelAvail)
	{
		BeginUndoBlock();
		try
		{
			DoCopyToClipboard(SelText);
			SelText = L"";
		}
		__finally
		{
			EndUndoBlock();
		}
	}
}

__fastcall TCustomSynEdit::TCustomSynEdit(TComponent* AOwner)
 : inherited(AOwner),
			fUseCodeFolding(false),
			fCodeFolding(nullptr),
			fAllFoldRanges(nullptr),
			fAlwaysShowCaret(false),
			fCaretX(0),
			fLastCaretX(0),
			fCaretY(0),
			fCharsInWindow(0),
			fCharWidth(0),
			fFontDummy(nullptr),
			fFontQuality(TFontQuality::fqDefault),
			fInserting(false),
			fLines(nullptr),
			fOrigLines(nullptr),
			fOrigUndoRedo(nullptr),
			fLinesInWindow(0),
			fLeftChar(0),
			fPaintLock(0),
			fReadOnly(false),
			fRightEdge(0),
			fRightEdgeColor((TColor) 0),
			fScrollHintColor((TColor) 0),
			fScrollHintFormat(shfTopLineOnly),
			FScrollBars(TScrollStyle::ssNone),
			fTextHeight(0),
			fTextMargin(0),
			fTextOffset(0),
			fTopLine(0),
			fHighlighter(nullptr),
			fSelectedColor(nullptr),
			fActiveLineColor((TColor) 0),
			fUndoRedo(nullptr),
			fMouseDownX(0),
			fMouseDownY(0),
			fBookMarkOpt(nullptr),
			fBorderStyle((TBorderStyle) 0),
			fHideSelection(false),
			fMouseWheelAccumulator(0),
			fOverwriteCaret(ctVerticalLine),
			fInsertCaret(ctVerticalLine),
			fKeyStrokes(nullptr),
			fMarkList(nullptr),
			fExtraLineSpacing(0),
			fSelectionMode(smNormal),
			fActiveSelectionMode(smNormal),
			fWantReturns(false),
			fWantTabs(false),
			fWordWrapPlugin(nullptr),
			fWordWrapGlyph(nullptr),
			fCaretAtEOL(false),
			fGutter(nullptr),
			fTabWidth(0),
			fTextDrawer(nullptr),
			fLastKey(0),
			fSearchEngine(nullptr),
			fHookedCommandHandlers(nullptr),
			fKbdHandler(nullptr),
			fFocusList(nullptr),
			fPlugins(nullptr),
			fScrollTimer(nullptr),
			fScrollDeltaX(0),
			fScrollDeltaY(0),
			fClickCount(0),
			FPaintTransientLock(0),
			FIsScrolling(false),
			SelStartBeforeSearch(0),
			SelLengthBeforeSearch(0),
			fChainedEditor(nullptr),
			FIgnoreNextChar(false),
			fGutterWidth(0)
{
	fLines = new TSynEditStringList(ExpandAtWideGlyphs);
	fOrigLines = fLines;
	/*# with TSynEditStringList(fLines) do */
	{
		auto with0 = ((TSynEditStringList*) fLines);
		with0->OnChange = LinesChanged;
		with0->OnChanging = LinesChanging;
		with0->OnCleared = ListCleared;
		with0->OnBeforeDeleted = ListBeforeDeleted;
		with0->OnDeleted = ListDeleted;
		with0->OnInserted = ListInserted;
		with0->OnPut = ListPut;
	}
	fFontDummy = new TFont();
	fUndoRedo = CreateSynEditUndo(this);
	fUndoRedo->OnModifiedChanged = ModifiedChanged;
	fOrigUndoRedo = fUndoRedo;
	DoubleBuffered = false;
	fActiveLineColor = clNone;
	fSelectedColor = new TSynSelectedColor();
	fSelectedColor->OnChange = SelectedColorsChanged;
	fBookMarkOpt = new TSynBookMarkOpt(this);
	fBookMarkOpt->OnChange = BookMarkOptionsChanged;
	fTextMargin = 3;
  // fRightEdge has to be set before FontChanged is called for the first time
	fRightEdge = 80;
	fGutter = new TSynGutter(this);
	fGutter->OnChange = GutterChanged;
	fWordWrapGlyph = new TSynGlyph((THandle) HInstance, L"SynEditWrapped");
	fWordWrapGlyph->OnChange = WordWrapGlyphChange;
	ControlStyle = ControlStyle + Synedit__1;
	ControlStyle = ControlStyle + Synedit__2;
	Height = 150;
	Width = 200;
	Cursor = crIBeam;
	Color = clWindow;
	fFontQuality = TFontQuality::fqClearTypeNatural;
	fFontDummy->Name = DefaultFontName();
	fFontDummy->Size = 10;
	fFontDummy->Charset = (System::Uitypes::TFontCharset) DEFAULT_CHARSET;
	fFontDummy->Quality = fFontQuality;
	fTextDrawer = new TheTextDrawer(Synedit__3, fFontDummy);
	Font->Assign(fFontDummy);
	Font->OnChange = SynFontChanged;
	ParentFont = false;
	ParentColor = false;
	TabStop = true;
	fInserting = true;
	FScrollBars = TScrollStyle::ssBoth;
	fBorderStyle = (TBorderStyle) bsSingle;
	fInsertCaret = ctVerticalLine;
	fOverwriteCaret = ctBlock;
	fSelectionMode = smNormal;
	fActiveSelectionMode = smNormal;
	fFocusList = new TList();
	fKbdHandler = new TSynEditKbdHandler();
	fKeyStrokes = new TSynEditKeyStrokes(this);
	fMarkList = new TSynEditMarkList(this);
	fMarkList->OnChange = MarkListChange;
	SetDefaultKeystrokes();
	fRightEdgeColor = clSilver;
	fWantReturns = true;
	fWantTabs = false;
	fTabWidth = 8;
	fLeftChar = 1;
	fTopLine = 1;
	fCaretX = 1;
	fLastCaretX = 1;
	fCaretY = 1;
	fBlockBegin.Char = 1;
	fBlockBegin.Line = 1;
	fBlockEnd = fBlockBegin;
	fOptions = SYNEDIT_DEFAULT_OPTIONS;
	fScrollTimer = new TTimer(this);
	fScrollTimer->Enabled = false;
	fScrollTimer->Interval = 100;
	fScrollTimer->OnTimer = ScrollTimerHandler;
	fScrollHintColor = clInfoBk;
	fScrollHintFormat = shfTopLineOnly;
//++ CodeFolding
	fCodeFolding = new TSynCodeFolding();
	fCodeFolding->OnChange = OnCodeFoldingChange;
	fAllFoldRanges = new TSynFoldRanges();
//-- CodeFolding
	SynFontChanged(nullptr);
	fTextOffset = fGutterWidth + fTextMargin;
	GutterChanged(nullptr); // to caclulate fGutterWidth also updates fTextOffset
}

void __fastcall TCustomSynEdit::CreateParams(TCreateParams& Params)
{
	const DWORD BorderStyles[bsSingle - bsNone+ 1/*# TBorderStyle*/] = {0, (DWORD) WS_BORDER};
	const unsigned long ClassStylesOff = CS_VREDRAW | CS_HREDRAW;
  // Clear WindowText to avoid it being used as Caption, or else window creation will
  // fail if it's bigger than 64KB. It's useless to set the Caption anyway.
	StrDispose(WindowText);
	WindowText = nullptr;
	inherited::CreateParams(Params);
	/*# with Params do */
	{
		auto& with0 = Params;
		with0.WindowClass.style = with0.WindowClass.style & ~ClassStylesOff;
		with0.Style = with0.Style | BorderStyles[fBorderStyle] | WS_CLIPCHILDREN;
		if(NewStyleControls && Ctl3D && (fBorderStyle == bsSingle))
		{
			with0.Style = with0.Style & ~WS_BORDER;
			with0.ExStyle = with0.ExStyle | WS_EX_CLIENTEDGE;
		}
	}
}

void __fastcall TCustomSynEdit::DecPaintLock()
{
	TDisplayCoord vAuxPos = {};
	Assert(fPaintLock > 0);
	--fPaintLock;
	if((fPaintLock == 0) && HandleAllocated())
	{
		if(fStateFlags.Contains(sfScrollbarChanged))
			UpdateScrollBars();
    // Locks the caret inside the visible area
		if(WordWrap && (Synedit__4 * fStatusChanges != Synedit__5))
		{
			vAuxPos = DisplayXY;
      // This may happen in the last row of a line or in rows which length is
      // greater than CharsInWindow (Tabs and Spaces are allowed beyond
      // CharsInWindow while wrapping the lines)
			if((vAuxPos.Column > CharsInWindow + 1) && (CharsInWindow > 0))
			{
				if(fCaretAtEOL)
					fCaretAtEOL = false;
				else
				{
					if(fStatusChanges.Contains(scCaretY))
					{
						vAuxPos.Column = CharsInWindow + 1;
						fCaretX = DisplayToBufferPos(vAuxPos).Char;
						fStatusChanges << scCaretX;
						UpdateLastCaretX();
					}
				}
				fStateFlags << sfCaretChanged;
			}
		}
		if(fStateFlags.Contains(sfCaretChanged))
			UpdateCaret();
		if(fStatusChanges != Synedit__6)
			DoOnStatusChange(fStatusChanges);
	}
}

__fastcall TCustomSynEdit::~TCustomSynEdit()
{
	Highlighter = nullptr;
	if((fChainedEditor != nullptr) || (fLines != fOrigLines))
		RemoveLinesPointer();
	//# inherited::Destroy();
  // free listeners while other fields are still valid
  // do not use FreeAndNil, it first nils and then freey causing problems with
  // code accessing fHookedCommandHandlers while destruction
	inherited::RemoveFreeNotifications();
	delete fHookedCommandHandlers;
	fHookedCommandHandlers = nullptr;
  // do not use FreeAndNil, it first nils and then frees causing problems with
  // code accessing fPlugins while destruction
	delete fPlugins;
	fPlugins = nullptr;
	delete fMarkList;
	delete fBookMarkOpt;
	delete fKeyStrokes;
	delete fKbdHandler;
	delete fFocusList;
	delete fSelectedColor;
	fUndoRedo = nullptr;
	fOrigUndoRedo = nullptr;
	delete fGutter;
	delete fWordWrapGlyph;
	delete fTextDrawer;
	delete fFontDummy;
	delete fOrigLines;
//++ CodeFolding
	delete fCodeFolding;
	delete fAllFoldRanges;
//-- CodeFolding
}

TBufferCoord __fastcall TCustomSynEdit::GetBlockBegin()
{
	TBufferCoord result = {};
	if((fBlockEnd.Line < fBlockBegin.Line) || ((fBlockEnd.Line == fBlockBegin.Line) && (fBlockEnd.Char < fBlockBegin.Char)))
		result = fBlockEnd;
	else
		result = fBlockBegin;
	return result;
}

TBufferCoord __fastcall TCustomSynEdit::GetBlockEnd()
{
	TBufferCoord result = {};
	if((fBlockEnd.Line < fBlockBegin.Line) || ((fBlockEnd.Line == fBlockBegin.Line) && (fBlockEnd.Char < fBlockBegin.Char)))
		result = fBlockBegin;
	else
		result = fBlockEnd;
	return result;
}

void __fastcall TCustomSynEdit::SynFontChanged(TObject* Sender)
{
	RecalcCharExtent();
	SizeOrFontChanged(true);
}

TFont* __fastcall TCustomSynEdit::GetFont()
{
	TFont* result = nullptr;
	result = inherited::Font;
	return result;
}

String __fastcall TCustomSynEdit::GetLineText()
{
	String result;
	if((CaretY >= 1) && (CaretY <= Lines->Count))
		result = Lines->Strings[CaretY - 1];
	else
		result = L"";
	return result;
}

bool __fastcall TCustomSynEdit::GetSelAvail()
{
	bool result = false;
	result = (fBlockBegin.Char != fBlockEnd.Char) || ((fBlockBegin.Line != fBlockEnd.Line) && (fActiveSelectionMode != smColumn));
	return result;
}

String __fastcall TCustomSynEdit::GetSelText()
{
	String result;

	auto CopyPadded = [&](const String S, int Index, int Count) -> String 
	{
		String result;
		int SrcLen = 0;
		int DstLen = 0;
		int i = 0;
		PWideChar P = nullptr;
		SrcLen = S.Length();
		DstLen = Index + Count;
		if(SrcLen >= DstLen)
			result = S.SubString(Index, Count);
		else
		{
			int stop = 0;
			result.SetLength(DstLen);
			P = ustr2pwchar(result);
			StrCopy(P, ustr2pwchar(S.SubString(Index, Count)));
			P += S.Length();
			for(stop = DstLen - SrcLen - 1, i = 0; i <= stop; i++)
			{
				P[i] = L'\x20';
			}
		}
		return result;
	};

	auto CopyAndForward = [&](const String S, int Index, int Count, PWideChar& P) -> void 
	{
		PWideChar pSrc = nullptr;
		int SrcLen = 0;
		int DstLen = 0;
		SrcLen = S.Length();
		if((Index <= SrcLen) && (Count > 0))
		{
			--Index;
			pSrc = const_cast<PWideChar>(S.c_str() + Index);
			DstLen = Min(SrcLen - Index, Count);
			Move(pSrc, P, (size_t) (DstLen * sizeof(WideChar)));
			P += DstLen;
			(*P) = L'\x00';
		}
	};

	auto CopyPaddedAndForward = [&](const String S, int Index, int Count, PWideChar& P) -> int 
	{
		int result = 0;
		PWideChar OldP = nullptr;
		int Len = 0;
		int i = 0;
		result = 0;
		OldP = P;
		CopyAndForward(S, Index, Count, P);
		Len = Count - (P - OldP);
		if(!(Options.Contains(eoTrimTrailingSpaces)))
		{
			int stop = 0;
			for(stop = Len - 1, i = 0; i <= stop; i++)
			{
				P[i] = L'\x20';
			}
			P += Len;
		}
		else
		result = Len;
		return result;
	};
	int First = 0;
	int Last = 0;
	int TotalLen = 0;
	int ColFrom = 0;
	int ColTo = 0;
	__int64 I = 0;
	int l = 0;
	int r = 0;
	String s;
	PWideChar P = nullptr;
	__int64 cRow = 0;
	TBufferCoord vAuxLineChar = {};
	TDisplayCoord vAuxRowCol = {};
	int vTrimCount = 0;
	if(!SelAvail)
		result = L"";
	else
	{
		ColFrom = BlockBegin.Char;
		First = BlockBegin.Line - 1;
    //
		ColTo = BlockEnd.Char;
		Last = BlockEnd.Line - 1;
    //
		TotalLen = 0;
		switch(fActiveSelectionMode)
		{
			case smNormal:
			if(First == Last)
				result = Lines->Strings[First].SubString(ColFrom, ColTo - ColFrom);
			else

          // step1: calculate total length of result string
			{
				__int64 stop = 0;
				TotalLen = Max(0, Lines->Strings[First].Length() - ColFrom + 1);
				for(stop = Last - 1, I = First + 1; I <= stop; I++)
				{
					TotalLen += Lines->Strings[I].Length();
				}
				TotalLen += ColTo - 1;
				TotalLen += Length(sLineBreak) * (Last - First);
          // step2: build up result string
				result.SetLength(TotalLen);
				P = ustr2pwchar(result);
				CopyAndForward(Lines->Strings[First], ColFrom, MaxInt, P);
				CopyAndForward(sLineBreak, 1, MaxInt, P);
				for(stop = Last - 1, I = First + 1; I <= stop; I++)
				{
					CopyAndForward(Lines->Strings[I], 1, MaxInt, P);
					CopyAndForward(sLineBreak, 1, MaxInt, P);
				}
				CopyAndForward(Lines->Strings[Last], 1, ColTo - 1, P);
			}
			break;
			case smColumn:
			{
				__int64 stop = 0;
				/*# with BufferToDisplayPos(BlockBegin) do */
				{
					auto with0 = BufferToDisplayPos(BlockBegin);
					First = with0.Row;
					ColFrom = with0.Column;
				}
				/*# with BufferToDisplayPos(BlockEnd) do */
				{
					auto with1 = BufferToDisplayPos(BlockEnd);
					Last = with1.Row;
					ColTo = with1.Column;
				}
				if(ColFrom > ColTo)
					SwapInt(ColFrom, ColTo);
          // step1: pre-allocate string large enough for worst case
				TotalLen = ((ColTo - ColFrom) + Length(sLineBreak)) * (Last - First + 1);
				result.SetLength(TotalLen);
				P = ustr2pwchar(result);

          // step2: copy chunks to the pre-allocated string
				TotalLen = 0;
				for(stop = Last, cRow = First; cRow <= stop; cRow++)
				{
					vAuxRowCol.Row = (int) cRow;
					vAuxRowCol.Column = ColFrom;
					vAuxLineChar = DisplayToBufferPos(vAuxRowCol);
					l = vAuxLineChar.Char;
					s = Lines->Strings[vAuxLineChar.Line - 1];
					vAuxRowCol.Column = ColTo;
					r = DisplayToBufferPos(vAuxRowCol).Char;
					vTrimCount = CopyPaddedAndForward(s, l, r - l, P);
					TotalLen = TotalLen + (r - l) - vTrimCount + Length(sLineBreak);
					CopyAndForward(sLineBreak, 1, MaxInt, P);
				}
				result.SetLength(TotalLen - Length(sLineBreak));
			}
			break;
          // If block selection includes LastLine,
          // line break code(s) of the last line will not be added.
          // step1: calculate total length of result string
			case smLine:
			{
				__int64 stop = 0;
				for(stop = Last, I = First; I <= stop; I++)
				{
					TotalLen += Lines->Strings[I].Length() + Length(sLineBreak);
				}
				if(Last == Lines->Count)
					TotalLen -= Length(sLineBreak);
          // step2: build up result string
				result.SetLength(TotalLen);
				P = ustr2pwchar(result);
				for(stop = Last - 1, I = First; I <= stop; I++)
				{
					CopyAndForward(Lines->Strings[I], 1, MaxInt, P);
					CopyAndForward(sLineBreak, 1, MaxInt, P);
				}
				CopyAndForward(Lines->Strings[Last], 1, MaxInt, P);
				if((Last + 1) < Lines->Count)
					CopyAndForward(sLineBreak, 1, MaxInt, P);
			}
			break;
			default:
			  ;
			break;
		}
	}
	return result;
}

String __fastcall TCustomSynEdit::SynGetText()
{
	String result;
	result = Lines->Text;
	return result;
}
/* Can place CaretX beyond the end of line */

void __fastcall TCustomSynEdit::ForceCaretX(int aCaretX)
{
	bool vRestoreScroll = false;
	vRestoreScroll = !(fOptions.Contains(eoScrollPastEol));
	fOptions << eoScrollPastEol;
	try
	{
		InternalCaretX = aCaretX;
	}
	__finally
	{
		if(vRestoreScroll)
			fOptions >> eoScrollPastEol;
	}
}

String __fastcall TCustomSynEdit::GetWordAtCursor()
{
	String result;
	result = GetWordAtRowCol(CaretXY);
	return result;
}

void __fastcall TCustomSynEdit::HideCaret()
{
	if(fStateFlags.Contains(sfCaretVisible))
	{
		if(::HideCaret(Handle))
			fStateFlags >> sfCaretVisible;
	}
}

void __fastcall TCustomSynEdit::IncPaintLock()
{
	++fPaintLock;
}

void __fastcall TCustomSynEdit::InvalidateGutter()
{
	InvalidateGutterLines(-1, -1);
}

void __fastcall TCustomSynEdit::InvalidateGutterLine(int aLine)
{
	if((aLine < 1) || (aLine > Lines->Count))
		return;
	InvalidateGutterLines(aLine, aLine);
}
// note: FirstLine and LastLine don't need to be in correct order

void __fastcall TCustomSynEdit::InvalidateGutterLines(int FirstLine, int LastLine)
{
	TRect rcInval = {};
	if(Visible && HandleAllocated())
	{
		if((FirstLine == -1) && (LastLine == -1))
		{
			rcInval = Rect(0, 0, fGutterWidth, ClientHeight);
			if(fStateFlags.Contains(sfLinesChanging))
//++ Flicker Reduction

//-- Flicker Reduction
				UnionRect(fInvalidateRect, rcInval, fInvalidateRect);
			else
				InvalidateRect(rcInval, false);
		}
		else

      /* find the visible lines first */
		{
			if(LastLine < FirstLine)
				SwapInt(LastLine, FirstLine);
//++ CodeFolding
			if(UseCodeFolding || WordWrap)
//-- CodeFolding
			{
				FirstLine = LineToRow(FirstLine);
				if(LastLine <= Lines->Count)
					LastLine = LineToRow(LastLine);
				else
					LastLine = MaxInt;
			}
			FirstLine = Max(FirstLine, TopLine);
			LastLine = Min(LastLine, TopLine + LinesInWindow);
      /* any line visible? */
			if(LastLine >= FirstLine)
			{
				rcInval = Rect(0, fTextHeight * (FirstLine - TopLine), fGutterWidth, fTextHeight * (LastLine - TopLine + 1));
				if(fStateFlags.Contains(sfLinesChanging))
//++ Flicker Reduction

//-- Flicker Reduction
					UnionRect(fInvalidateRect, rcInval, fInvalidateRect);
				else
					InvalidateRect(rcInval, false);
			}
		}
	}
}
// note: FirstLine and LastLine don't need to be in correct order

void __fastcall TCustomSynEdit::InvalidateLines(int FirstLine, int LastLine)
{
	TRect rcInval = {};
	if(Visible && HandleAllocated())
	{
		if((FirstLine == -1) && (LastLine == -1))
		{
			rcInval = ClientRect;
			rcInval.Left += fGutterWidth;
			if(fStateFlags.Contains(sfLinesChanging))
//++ Flicker Reduction

//-- Flicker Reduction
				UnionRect(fInvalidateRect, rcInval, fInvalidateRect);
			else
				InvalidateRect(rcInval, false);
		}
		else
		{
			FirstLine = Max(FirstLine, 1);
			LastLine = Max(LastLine, 1);
      /* find the visible lines first */
			if(LastLine < FirstLine)
				SwapInt(LastLine, FirstLine);
			if(LastLine >= Lines->Count)
				LastLine = MaxInt; // paint empty space beyond last line

//++ CodeFolding
			if(UseCodeFolding || WordWrap)
			{
				FirstLine = LineToRow(FirstLine);
        // Could avoid this conversion if (First = Last) and
        // (Length < CharsInWindow) but the dependency isn't worth IMO.
				if(LastLine < Lines->Count)
				{
					if(UseCodeFolding)
						LastLine = LineToRow(LastLine);
					else
						LastLine = LineToRow(LastLine + 1) - 1;
				}
			}
//-- CodeFolding

      // TopLine is in display coordinates, so FirstLine and LastLine must be
      // converted previously.
			FirstLine = Max(FirstLine, TopLine);
			LastLine = Min(LastLine, TopLine + LinesInWindow);

      /* any line visible? */
			if(LastLine >= FirstLine)
			{
				rcInval = Rect(fGutterWidth, fTextHeight * (FirstLine - TopLine), ClientWidth, fTextHeight * (LastLine - TopLine + 1));
				if(fStateFlags.Contains(sfLinesChanging))
//++ Flicker Reduction

//++ Flicker Reduction
					UnionRect(fInvalidateRect, rcInval, fInvalidateRect);
				else
					InvalidateRect(rcInval, false);
			}
		}
	}
}

void __fastcall TCustomSynEdit::InvalidateSelection()
{
	InvalidateLines(BlockBegin.Line, BlockEnd.Line);
}

void __fastcall TCustomSynEdit::KeyUp(WORD& Key, TShiftState Shift)
{
	int CharCode = 0;
  /* The following allows the entering of Unicode character codes using the
    Alt + Numpad numbers combination.  When the charcode is less than 256
    this is handled by Windows.
  */
	if((Shift.Contains(ssAlt)) && (Key >= VK_NUMPAD0) && (Key <= VK_NUMPAD9))
		FCharCodeString = FCharCodeString + IntToStr(Key - VK_NUMPAD0);
	if(Key == VK_MENU)
	{
		if((FCharCodeString != L"") && TryStrToInt(FCharCodeString, CharCode) && (CharCode >= 256) && (CharCode <= 65535))
		{
			SendMessage(Handle, (UINT) WM_CHAR, CharCode, 0);
			FIgnoreNextChar = true;
		}
		FCharCodeString = L"";
	}
	inherited::KeyUp(Key, Shift);
	fKbdHandler->ExecuteKeyUp(this, Key, Shift);
}

void __fastcall TCustomSynEdit::KeyDown(WORD& Key, TShiftState Shift)
{
	void* Data = nullptr;
	WideChar C = L'\0';
	TSynEditorCommand Cmd = 0;
	inherited::KeyDown(Key, Shift);
	fKbdHandler->ExecuteKeyDown(this, Key, Shift);
	Data = nullptr;
	C = L'\x00';
	try
	{
		Cmd = TranslateKeyCode(Key, Shift, Data);
		if(Cmd != ecNone)
		{
			Key = 0; // eat it.
			fStateFlags << sfIgnoreNextChar;
			CommandProcessor(Cmd, C, Data);
		}
		else
		fStateFlags >> sfIgnoreNextChar;
	}
	__finally
	{
		if(Data != nullptr)
			FreeMemory(Data);
	}
}

void __fastcall TCustomSynEdit::Loaded()
{
	inherited::Loaded();
	GutterChanged(this);
	UpdateScrollBars();
}

void __fastcall TCustomSynEdit::KeyPress(Char& Key)
{
	if(FIgnoreNextChar)
	{
		FIgnoreNextChar = false;
		return;
	}
	inherited::KeyPress(Key);  // Calls the OnKeyPress event handler if present
	if(Key == L'\x00')
		return;

  // don't fire the event if key is to be ignored
	if(!(fStateFlags.Contains(sfIgnoreNextChar)))
	{
		fKbdHandler->ExecuteKeyPress(this, Key);
		CommandProcessor((TSynEditorCommand) ecChar, Key, nullptr);
	}
	else

    // don't ignore further keys
	fStateFlags >> sfIgnoreNextChar;
}

int __fastcall TCustomSynEdit::LeftSpaces(const String Line, bool ExpandTabs/*# = false*/)
{
	int result = 0;
	PChar P = nullptr;
	result = 0;
	P = ustr2pwchar(Line);
	if(ASSIGNED(P))
	{
		while(((*P) >= L'\x01') && ((*P) <= L'\x20'))
		{
			if(((*P) == L'\x09') && ExpandTabs)
				result += TabWidth - (result % fTabWidth);
			else
				++result;
			++P;
		}
	}
	return result;
}

String __fastcall TCustomSynEdit::GetLeftSpacing(int CharCount, bool WantTabs)
{
	String result;
	if(WantTabs && !(Options.Contains(eoTabsToSpaces)) && (CharCount >= TabWidth))
		result = StringOfChar(L'\x09', (int)(CharCount / /*div*/ TabWidth))
	           + StringOfChar(L'\x20', CharCount % TabWidth);
	else
		result = StringOfChar(L'\x20', CharCount);
	return result;
}

void __fastcall TCustomSynEdit::LinesChanging(TObject* Sender)
{
	fStateFlags << sfLinesChanging;
}

void __fastcall TCustomSynEdit::LinesChanged(TObject* Sender)
{
	TSynSelectionMode vOldMode = smNormal;
	DoLinesChanged();

//++ CodeFolding
	if((fStateFlags.Contains(sfLinesChanging)) && fAllFoldRanges->StopScanning(fLines))
	{
		if(ASSIGNED(fHighlighter) && (ObjectIs(fHighlighter, TSynCustomCodeFoldingHighlighter*)))
			((TSynCustomCodeFoldingHighlighter*) fHighlighter)->AdjustFoldRanges(AllFoldRanges, fLines);
		InvalidateGutter();
		fStateFlags << sfScrollbarChanged;
	}
//-- CodeFolding
	fStateFlags >> sfLinesChanging;
	if(HandleAllocated())
//++ Flicker Reduction
//    UpdateScrollBars;
//-- Flicker Reduction
	{
		vOldMode = fActiveSelectionMode;
    //SetBlockBegin(CaretXY);
		fActiveSelectionMode = vOldMode;
		InvalidateRect(fInvalidateRect, false);
		FillChar((void**)&fInvalidateRect, (int) sizeof(TRect), 0);
		if(!(Options.Contains(eoScrollPastEof)))
			TopLine = TopLine;
	}
	DoChange();
}

void __fastcall TCustomSynEdit::MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
	bool bWasSel = false;
	TBufferCoord TmpBegin = {};
	TBufferCoord TmpEnd = {};
	TPoint P = {};
  // Ole drag drop
	IDropSource* DragSource = nullptr;
	IDataObject* DataObject = nullptr;
	DWORD dwEffect = 0;   // dme
	inherited::MouseDown(Button, Shift, X, Y);
	TmpBegin = fBlockBegin;
	TmpEnd = fBlockEnd;

  //remember selection state, as it will be cleared later
	bWasSel = SelAvail;
	if((Button == TMouseButton::mbLeft) && ((Shift + Synedit__7) == Synedit__8))
	{
		if((fClickCount > 0) && (Abs(fMouseDownX - X) < GetSystemMetrics(SM_CXDRAG)) && (Abs(fMouseDownY - Y) < GetSystemMetrics(SM_CYDRAG)) && (fClickCountTimer.ElapsedMilliseconds < GetDoubleClickTime()))
			++fClickCount;
		else
			fClickCount = 1;
		fMouseDownX = X;
		fMouseDownY = Y;
		if(fClickCount == 3)
			TripleClick();
		if(fClickCount == 4)
			QuadrupleClick();
		fClickCountTimer = TStopwatch::StartNew();
	}
	else
	fClickCount = 0;
	if((Button == TMouseButton::mbLeft) && (fClickCount > 1))
		return;
	fKbdHandler->ExecuteMouseDown(this, Button, Shift, X, Y);
	if(Synedit__9.Contains(Button))
	{
		if(Button == TMouseButton::mbRight)
		{
			if((Options.Contains(eoRightMouseMovesCursor)) && (SelAvail && !IsPointInSelection(DisplayToBufferPos(PixelsToRowColumn(X, Y))) || !SelAvail))
			{
				InvalidateSelection();
				fBlockEnd = fBlockBegin;
				ComputeCaret(X, Y);
			}
			else
			return;
		}
		else
		ComputeCaret(X, Y);
	}
	if(Button == TMouseButton::mbLeft)
    //I couldn't track down why, but sometimes (and definately not all the time)
    //the block positioning is lost.  This makes sure that the block is
    //maintained in case they started a drag operation on the block
	{
		fBlockBegin = TmpBegin;
		fBlockEnd = TmpEnd;
		MouseCapture = true;
    //if mousedown occurred in selected block begin drag operation
		if(bWasSel && (fOptions.Contains(eoDragDropEditing)) && (X >= fGutterWidth + fTextMargin) && (Synedit__10 * Shift == Synedit__11) && IsPointInSelection(DisplayToBufferPos(PixelsToRowColumn(X, Y))))
		{
			if(DragDetect(Handle, Point(X, Y)))
			{
				DataObject = new TSynEditDataObject(this);
				DragSource = new TSynDragSource();
				try
				{
					fStateFlags << sfOleDragSource;
					DoDragDrop(DataObject, DragSource, DROPEFFECT_COPY | DROPEFFECT_MOVE, &dwEffect);
				}
				__finally
				{
					fStateFlags >> sfOleDragSource;
					if(dwEffect == DROPEFFECT_MOVE)
						ClearSelection();
				}
				return;
			}
			else
			{
				if(ControlState.Contains(csLButtonDown))
				{
					GetCursorPos(&P);
					PostMessage(Handle, (UINT) WM_LBUTTONUP, 0, PointToLParam(ScreenToClient(P)));
				}
			}
		}
	}
	if(!(Shift.Contains(ssDouble)))
	{
		if(Shift.Contains(ssShift))
      //BlockBegin and BlockEnd are restored to their original position in the
      //code from above and SetBlockEnd will take care of proper invalidation
			SetBlockEnd(CaretXY);
		else
		{
			if((Options.Contains(eoAltSetsColumnMode)) && (fActiveSelectionMode != smLine))
			{
				if(Shift.Contains(ssAlt))
					SelectionMode = smColumn;
				else
					SelectionMode = smNormal;
			}
      //Selection mode must be set before calling SetBlockBegin
			SetBlockBegin(CaretXY);
		}
	}
	if(X < fGutterWidth)
		fStateFlags << sfPossibleGutterClick;
	if((fStateFlags.Contains(sfPossibleGutterClick)) && (Button == TMouseButton::mbRight))
	{
		DoOnGutterClick(Button, X, Y);
	}
	SetFocus();
	::SetFocus(Handle);
}

void __fastcall TCustomSynEdit::MouseMove(TShiftState Shift, int X, int Y)
{
	TDisplayCoord P = {};
	TBufferCoord BC = {};
	inherited::MouseMove(Shift, X, Y);
	if((Shift.Contains(ssLeft)) && MouseCapture && !IsScrolling)
    // should we begin scrolling?
	{
		ComputeScroll(X, Y);
    /* compute new caret */
		P = PixelsToNearestRowColumn(X, Y);
		P.Row = MinMax(P.Row, 1, DisplayLineCount);
//  Not sure what was the purpose of these
//    if fScrollDeltaX <> 0 then
//      P.Column := DisplayX;
//    if fScrollDeltaY <> 0 then
//      P.Row := DisplayY;
		BC = DisplayToBufferPos(P);
		if(BC == CaretXY)
			return;  // no movement
		if((ActiveSelectionMode == smNormal) && (fClickCount == 2))
			DoMouseSelectWordRange(BC);
		else
		{
			if((ActiveSelectionMode == smNormal) && (fClickCount == 3))
				DoMouseSelectLineRange(BC);
			else
			{
				InternalCaretXY = BC;
				BlockEnd = BC;
			}
		}
		if((fStateFlags.Contains(sfPossibleGutterClick)) && (fBlockBegin.Line != CaretXY.Line))
			fStateFlags << sfGutterDragging;
	}
}

void __fastcall TCustomSynEdit::ScrollTimerHandler(TObject* Sender)
{
	TPoint iMousePos = {};
	TDisplayCoord C = {};
	int X = 0;
	int Y = 0;
	TBufferCoord vCaret = {};
	GetCursorPos(&iMousePos);
	iMousePos = ScreenToClient(iMousePos);
	C = PixelsToRowColumn(iMousePos.X, iMousePos.Y);
	C.Row = MinMax(C.Row, 1, DisplayLineCount);
	if(fScrollDeltaX != 0)
	{
		LeftChar = LeftChar + fScrollDeltaX;
		X = LeftChar;
		if(fScrollDeltaX > 0)  // scrolling right?
			X += CharsInWindow;
		C.Column = X;
	}
	if(fScrollDeltaY != 0)
	{
		if(GetKeyState(SYNEDIT_SHIFT) < 0)
			TopLine = TopLine + fScrollDeltaY * LinesInWindow;
		else
			TopLine = TopLine + fScrollDeltaY;
		Y = TopLine;
		if(fScrollDeltaY > 0)  // scrolling down?
			Y += LinesInWindow - 1;
		C.Row = MinMax(Y, 1, DisplayLineCount);
	}
	vCaret = DisplayToBufferPos(C);
	if((CaretX != vCaret.Char) || (CaretY != vCaret.Line))
    // changes to line / column in one go
	{
		IncPaintLock();
		try
		{
			if(MouseCapture && (fClickCount == 2) && (ActiveSelectionMode == smNormal))
        // Line selection
				DoMouseSelectWordRange(vCaret);
			else
			{
				if(MouseCapture && (fClickCount == 3) && (ActiveSelectionMode == smNormal))
        // Line selection
					DoMouseSelectLineRange(vCaret);
				else
				{
					InternalCaretXY = vCaret;
        // if MouseCapture is True we're changing selection. otherwise we're dragging
					if(MouseCapture)
						SetBlockEnd(CaretXY);
				}
			}
		}
		__finally
		{
			DecPaintLock();
		}
	}
	ComputeScroll(iMousePos.X, iMousePos.Y);
}

void __fastcall TCustomSynEdit::MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y)
{

//++ Code Folding
	TBufferCoord ptLineCol = {};
	TDisplayCoord ptRowCol = {};
	int Index = 0;
	TRect Rect = {};
//-- Code Folding
	inherited::MouseUp(Button, Shift, X, Y);
	fKbdHandler->ExecuteMouseUp(this, Button, Shift, X, Y);
	fScrollTimer->Enabled = false;
	if((Button == TMouseButton::mbRight) && (Shift == Synedit__12) && ASSIGNED(PopupMenu))
		return;
	MouseCapture = false;
	if((fStateFlags * Synedit__13 == Synedit__14) && (X < fGutterWidth) && (Button != TMouseButton::mbRight))
	{
		DoOnGutterClick(Button, X, Y);
	}
	fStateFlags >> sfPossibleGutterClick;
	fStateFlags >> sfGutterDragging;
//++ Code Folding
	ptRowCol = PixelsToRowColumn(X, Y);
	ptLineCol = DisplayToBufferPos(ptRowCol);
	if(UseCodeFolding && CodeFolding->ShowHintMark && fAllFoldRanges->CollapsedFoldStartAtLine(ptLineCol.Line, Index))
	{
		Rect = GetCollapseMarkRect(ptRowCol.Row, ptLineCol.Line);
		if(PtInRect(Rect, Point(X, Y)))
			Uncollapse(Index);
	}
}

void __fastcall TCustomSynEdit::DoOnGutterClick(TMouseButton Button, int X, int Y)
{
	int I = 0;
	int Offs = 0;
	int Line = 0;
	TSynEditMarks Allmrk;
	TSynEditMark* Mark = nullptr;
	TDisplayCoord RowColumn = {};
	TSynGutterBand* Band = nullptr;
	RowColumn = PixelsToRowColumn(X, Y);
	Line = RowToLine(RowColumn.Row);
	if(Line <= Lines->Count)
	{
		Band = fGutter->BandAtX(X);
		if(ASSIGNED(Band))
			Band->DoClick(this, Button, X, Y, RowColumn.Row, Line);
		if(ASSIGNED(fOnGutterClick))
      // Check gutter marks
		{
			int stop = 0;
			Marks->GetMarksForLine(Line, Allmrk);
			Offs = 0;
			Mark = nullptr;
			for(stop = MAX_MARKS, I = 1; I <= stop; I++)
			{
				if(ASSIGNED(Allmrk[I - 1]))
				{
					Offs += BookMarkOptions->Xoffset;
					if(X < Offs)
					{
						Mark = Allmrk[I - 1];
						break;
					}
				}
			} //for
			fOnGutterClick(this, Button, X, Y, Line, Mark);
		}
	}
}

void __fastcall TCustomSynEdit::Paint()
{
	TRect rcClip = {};
	TRect rcDraw = {};
	int nL1 = 0;
	int nL2 = 0;
	int nC1 = 0;
	int nC2 = 0;
  // Get the invalidated rect. Compute the invalid area in lines / columns.
	rcClip = Canvas->ClipRect;
  // columns
	nC1 = LeftChar;
	if(rcClip.Left > fGutterWidth + fTextMargin)
		nC1 += (int)((rcClip.Left - fGutterWidth - fTextMargin) / /*div*/ CharWidth);
	nC2 = LeftChar + (int)((rcClip.Right - fGutterWidth - fTextMargin + CharWidth - 1) / /*div*/ CharWidth);
  // lines
	nL1 = Max(TopLine + (int)(rcClip.Top / /*div*/ fTextHeight), TopLine);
	nL2 = MinMax(TopLine + (int)((rcClip.Bottom + fTextHeight - 1) / /*div*/ fTextHeight), 1, DisplayLineCount);
  // Now paint everything while the caret is hidden.
	HideCaret();
	try

    // First paint the gutter area if it was (partly) invalidated.
	{
		if(rcClip.Left < fGutterWidth)
		{
			rcDraw = rcClip;
			rcDraw.Right = fGutterWidth;
			PaintGutter(rcDraw, nL1, nL2);
		}
    // Then paint the text area if it was (partly) invalidated.
		if(rcClip.Right > fGutterWidth)
		{
			rcDraw = rcClip;
			rcDraw.Left = Max(rcDraw.Left, fGutterWidth);
			PaintTextLines(rcDraw, nL1, nL2, nC1, nC2);
		}
		PluginsAfterPaint(Canvas, rcClip, nL1, nL2);
    // If there is a custom paint handler call it.
		DoOnPaint();
		DoOnPaintTransient(ttAfter);
	}
	__finally
	{
		UpdateCaret();
	}
}

void __fastcall TCustomSynEdit::PaintGutter(const TRect& AClip, int aFirstRow, int aLastRow)
{
	int I = 0;
	int L = 0;
	int W = 0;
	TRect rcBackGround = {};
	TSynGutterBand* Band = nullptr;
	int SaveIndex = 0;
	TRect rcBand = {};
	TSynHighlighterAttributes* Attri = nullptr;
  // First paint gutter background
	int stop = 0;
	W = 0;
	for(stop = fGutter->Bands->Count - 1, I = 0; I <= stop; I++)
	{
		Band = fGutter->Bands->Bands[I];
		if(!Band->Visible)
			continue;
		if(Band->Background == gbbGutter)
			W += fGutter->Bands->Bands[I]->RealWidth();
		else
			break;
	}
	rcBackGround = Rect(0, AClip.Top, W, AClip.Bottom);
	if(fGutter->Gradient)
		SynDrawGradient(Canvas, fGutter->GradientStartColor, fGutter->GradientEndColor, fGutter->GradientSteps, rcBackGround, true);
	else
	{
		Canvas->Brush->Color = fGutter->Color;
		Canvas->FillRect(rcBackGround);
	}

  // Paint Bands with Editor Background
	Canvas->Brush->Color = Color;
	if(Highlighter != nullptr)
	{
		Attri = Highlighter->WhitespaceAttribute;
		if((Attri != nullptr) && (Attri->Background != clNone))
			Canvas->Brush->Color = Attri->Background;
	}
	L = 0;
	for(stop = fGutter->Bands->Count - 1, I = 0; I <= stop; I++)
	{
		Band = fGutter->Bands->Bands[I];
		if(!Band->Visible)
			continue;
		W = Band->RealWidth();
		if(Band->Background == gbbEditor)
		{
			rcBand = Rect(L, AClip.Top, L + W, AClip.Bottom);
			Canvas->FillRect(rcBand);
		}
		L += W;
	}

  // Now paint the bands
	L = 0;
	for(stop = fGutter->Bands->Count - 1, I = 0; I <= stop; I++)
	{
		Band = fGutter->Bands->Bands[I];
		if(!Band->Visible)
			continue;
		W = Band->RealWidth();
		rcBand = Rect(L, AClip.Top, L + W, AClip.Bottom);
		SaveIndex = SaveDC(Canvas->Handle);
		try
		{
			IntersectClipRect(Canvas->Handle, rcBand.Left, rcBand.Top, rcBand.Right, rcBand.Bottom);
			Band->PaintLines(Canvas, rcBand, aFirstRow, aLastRow);
		}
		__finally
		{
			RestoreDC(Canvas->Handle, SaveIndex);
		}
		L += W;
	}
}

// Inserts filling chars into a string containing chars that display as glyphs
// wider than an average glyph. (This is often the case with Asian glyphs, which
// are usually wider than latin glpyhs)
// This is only to simplify paint-operations and has nothing to do with
// multi-byte chars.

String __fastcall TCustomSynEdit::ExpandAtWideGlyphs(const String S)
{
	String result;
	int i = 0;
	int j = 0;
	int CountOfAvgGlyphs = 0;
	int stop = 0;
	result = S;
	j = 0;
	result.SetLength(S.Length() * 2); // speed improvement
	for(stop = S.Length(), i = 1; i <= stop; i++)
	{
		++j;
		if(int(S[i]) <= 0x00FF)
			CountOfAvgGlyphs = 1;
		else
			CountOfAvgGlyphs = (int) CeilOfIntDiv((unsigned int) fTextDrawer->TextWidth(String(S[i])), (WORD) fCharWidth);
		if(j + CountOfAvgGlyphs > result.Length())
			result.SetLength(result.Length() + 128);

    // insert CountOfAvgGlyphs filling chars
		while(CountOfAvgGlyphs > 1)
		{
			result[j] = FillerChar;
			++j;
			--CountOfAvgGlyphs;
		}
		result[j] = S[i];
	}
	result.SetLength(j);
	return result;
}

// does the opposite of ExpandAtWideGlyphs

String __fastcall TCustomSynEdit::ShrinkAtWideGlyphs(const String S, int First, int& CharCount)
{
	String result;
	int i = 0;
	int j = 0;
	result.SetLength(CharCount);
	i = First;
	j = 0;
	while(i < First + CharCount)
	{
		if(S[i] != FillerChar)
		{
			++j;
			result[j] = S[i];
		}
		++i;
	}
	result.SetLength(j);
	CharCount = j;
	return result;
}

void __fastcall TCustomSynEdit::PaintTextLines(const TRect& cAClip, int aFirstRow, int aLastRow, int FirstCol, int LastCol)
{
	TRect AClip = cAClip;
	bool bDoRightEdge = false; // right edge
	int nRightEdge = 0;
    // selection info
	bool bAnySelection = false; // any selection visible?
	TDisplayCoord vSelStart = {}; // start of selected area
	TDisplayCoord vSelEnd = {}; // end of selected area
    // info about normal and selected text and background colors
	bool bSpecialLine = false;
	bool bLineSelected = false;
	bool bCurrentLine = false;
	TColor colFG = (TColor) 0;
	TColor colBG = (TColor) 0;
	TColor colSelFG = (TColor) 0;
	TColor colSelBG = (TColor) 0;
    // info about selection of the current line
	int nLineSelStart = 0;
	int nLineSelEnd = 0;
	bool bComplexLine = false;
    // painting the background and the text
	TRect rcLine = {};
	TRect rcToken = {};
    // Note: s is not managed as a string, it will only grow!!!
    // Never use AppendStr or "+", use Len and MaxLen instead and
    // copy the string chars directly. This is for efficiency.

	struct SyneditRec__0
	{
		int Len;
		int MaxLen;
		int CharsBefore;
		String s;
		String TabString;
		TColor FG;
		TColor BG;
		TFontStyles Style;
	};	
	SyneditRec__0 TokenAccu = {};
	HDC dc = 0;
	String SynTabGlyphString;
	int vFirstLine = 0;
	int vLastLine = 0;

/* local procedures */

	auto colEditorBG = [&]() -> TColor 
	{
		TColor result = (TColor) 0;
		TSynHighlighterAttributes* iAttri = nullptr;
		if((ActiveLineColor != clNone) && (bCurrentLine))
			result = ActiveLineColor;
		else
		{
			result = Color;
			if(Highlighter != nullptr)
			{
				iAttri = Highlighter->WhitespaceAttribute;
				if((iAttri != nullptr) && (iAttri->Background != clNone))
					result = iAttri->Background;
			}
		}
		return result;
	};

	auto ComputeSelectionInfo = [&]() -> void 
	{
		TBufferCoord vStart = {};
		TBufferCoord vEnd = {};
		bAnySelection = false;
    // Only if selection is visible anyway.
		if(!HideSelection || this->Focused())
		{
			bAnySelection = true;
      // Get the *real* start of the selected area.
			if(fBlockBegin.Line < fBlockEnd.Line)
			{
				vStart = fBlockBegin;
				vEnd = fBlockEnd;
			}
			else
			{
				if(fBlockBegin.Line > fBlockEnd.Line)
				{
					vEnd = fBlockBegin;
					vStart = fBlockEnd;
				}
				else
				{
					if(fBlockBegin.Char != fBlockEnd.Char)
        // No selection at all, or it is only on this line.
					{
						vStart.Line = fBlockBegin.Line;
						vEnd.Line = vStart.Line;
						if(fBlockBegin.Char < fBlockEnd.Char)
						{
							vStart.Char = fBlockBegin.Char;
							vEnd.Char = fBlockEnd.Char;
						}
						else
						{
							vStart.Char = fBlockEnd.Char;
							vEnd.Char = fBlockBegin.Char;
						}
					}
					else
					bAnySelection = false;
				}
      // If there is any visible selection so far, then test if there is an
      // intersection with the area to be painted.
			}
			if(bAnySelection)
        // Don't care if the selection is not visible.
			{
				bAnySelection = (vEnd.Line >= vFirstLine) && (vStart.Line <= vLastLine);
				if(bAnySelection)
          // Transform the selection from text space into screen space
				{
					vSelStart = BufferToDisplayPos(vStart);
					vSelEnd = BufferToDisplayPos(vEnd);
          // In the column selection mode sort the begin and end of the selection,
          // this makes the painting code simpler.
					if((fActiveSelectionMode == smColumn) && (vSelStart.Column > vSelEnd.Column))
						SwapInt(vSelStart.Column, vSelEnd.Column);
				}
			}
		}
	};

	auto SetDrawingColors = [&](bool Selected) -> void 
	{
		/*# with fTextDrawer do */
		{
			auto with0 = fTextDrawer;
			if(Selected)
			{
				with0->SetBackColor(colSelBG);
				with0->SetForeColor(colSelFG);
				Canvas->Brush->Color = colSelBG;
			}
			else
			{
				with0->SetBackColor(colBG);
				with0->SetForeColor(colFG);
				Canvas->Brush->Color = colBG;
			}
		}
	};

	auto ColumnToXValue = [&](int Col) -> int 
	{
		int result = 0;
		result = fTextOffset + Pred(Col) * fCharWidth;
		return result;
	};

  //todo: Review SpecialChars and HardTabs painting. Token parameter of PaintToken procedure could very probably be passed by reference.

  // Note: The PaintToken procedure will take care of invalid parameters
  // like empty token rect or invalid indices into TokenLen.
  // CharsBefore tells if Token starts at column one or not

	auto PaintToken = [&](String Token, int TokenLen, int CharsBefore, int First, int Last) -> void 
	{
		String Text;
		int Counter = 0;
		int nX = 0;
		int nCharsToPaint = 0;
		String sTabbedToken;
		bool DoTabPainting = false;
		int i = 0;
		int TabStart = 0;
		int TabLen = 0;
		int CountOfAvgGlyphs = 0;
		int VisibleGlyphPart = 0;
		int FillerCount = 0;
		int NonFillerPos = 0;
		TRect rcTab = {};
		const System::Set<SyntextdrawerEnum__0, SyntextdrawerEnum__0::tooOpaque, SyntextdrawerEnum__0::tooClipped> ETOOptions = System::Set<SyntextdrawerEnum__0, SyntextdrawerEnum__0::tooOpaque, SyntextdrawerEnum__0::tooClipped>() << tooOpaque << tooClipped;
		sTabbedToken = Token;
		DoTabPainting = false;
		Counter = Last - CharsBefore;
		while(Counter > First - CharsBefore - 1)
		{
			if(Token.Length() >= Counter)
			{
				if((fOptions.Contains(eoShowSpecialChars)) && (Token[Counter] == L'\x20'))
					Token[Counter] = SynSpaceGlyph;
				else
				{
					if(Token[Counter] == L'\x09')
					{
						Token[Counter] = L'\x20';  //Tabs painted differently if necessary
						DoTabPainting = fOptions.Contains(eoShowSpecialChars);
					}
				}
			}
			--Counter;
		}
		if((Last >= First) && (rcToken.Right > rcToken.Left))
		{
			nX = ColumnToXValue(First);
			First -= CharsBefore;
			Last -= CharsBefore;
			if(First > TokenLen)
			{
				nCharsToPaint = 0;
				Text = L"";
			}
			else
			{
				FillerCount = 0;
				NonFillerPos = First;
				while(Token[NonFillerPos] == FillerChar)
				{
					++FillerCount;
					++NonFillerPos;
				}
				CountOfAvgGlyphs = (int) CeilOfIntDiv((unsigned int) fTextDrawer->TextWidth(String(Token[NonFillerPos])), (WORD) fCharWidth);

        // first visible part of the glyph (1-based)
        // (the glyph is visually sectioned in parts of size fCharWidth)
				VisibleGlyphPart = CountOfAvgGlyphs - FillerCount;

        // clip off invisible parts
				nX = nX - fCharWidth * (VisibleGlyphPart - 1);
				nCharsToPaint = Min(Last - First + 1, TokenLen - First + 1);

        // clip off partially visible glyphs at line end
				if(WordWrap)
				{
					while(nX + fCharWidth * nCharsToPaint > ClientWidth)
					{
						--nCharsToPaint;
						while((nCharsToPaint > 0) && (Token[First + nCharsToPaint - 1] == FillerChar))
							--nCharsToPaint;
					}

        // same as copy(Token, First, nCharsToPaint) and remove filler chars
				}
				Text = ShrinkAtWideGlyphs(Token, First, nCharsToPaint);
			}
			fTextDrawer->ExtTextOut(nX, rcToken.Top, ETOOptions, rcToken, ustr2pwchar(Text), nCharsToPaint, (fOptions.Contains(eoShowLigatures)) && !bCurrentLine);
			if(DoTabPainting)
        // fix everything before the FirstChar
			{
				int stop = 0;
				for(stop = First - 1, i = 1; i <= stop; i++)
				{
					if(sTabbedToken[i] == L'\x09')               // wipe the text out so we don't
           // count it out of the range
						sTabbedToken[i] = L'\x20';
				}              // we're looking for
				TabStart = Pos(L"\x09", sTabbedToken);
				rcTab.Top = rcToken.Top;
				rcTab.Bottom = rcToken.Bottom;
				while((TabStart > 0) && (TabStart >= First) && (TabStart <= Last))
				{
					int stop = 0;
					TabLen = 1;
					while((TabStart + CharsBefore + TabLen - 1) % fTabWidth != 0)
						++TabLen;
					Text = SynTabGlyphString;
					nX = ColumnToXValue(CharsBefore + TabStart + ((int)(TabLen / /*div*/ 2)) - 1);
					if(TabLen % 2 == 0)
						nX = nX + ((int)(fCharWidth / /*div*/ 2));
					else
						nX = nX + fCharWidth;
					rcTab.Left = nX;
					rcTab.Right = nX + fTextDrawer->GetCharWidth();
					fTextDrawer->ExtTextOut(nX, rcTab.Top, ETOOptions, rcTab, ustr2pwchar(Text), 1);

          //wipe the text out so we don't count it again
					for(stop = Min(TabStart + TabLen - 1, sTabbedToken.Length()), i = TabStart; i <= stop; i++)
					{
						sTabbedToken[i] = L'\x20';
					}
					TabStart = Pos(L"\x09", sTabbedToken);
				}
			}
			rcToken.Left = rcToken.Right;
		}
	};

	auto AdjustEndRect = [&]() -> void 
	{
		unsigned int LastChar = 0;
		int NormalCharWidth = 0;
		int RealCharWidth = 0;
		TABC CharInfo = {};
		TTextMetricA tm = {};
		LastChar = (unsigned int) int(TokenAccu.s[TokenAccu.Len]);
		NormalCharWidth = fTextDrawer->TextWidth(String(((WideChar) LastChar)));
		RealCharWidth = NormalCharWidth;
		if(GetCharABCWidthsW(Canvas->Handle, LastChar, LastChar, &CharInfo))
		{
			RealCharWidth = CharInfo.abcA + ((int) CharInfo.abcB);
			if(CharInfo.abcC >= 0)
				RealCharWidth += CharInfo.abcC;
		}
		else
		{
			if(LastChar < int(High<AnsiChar>()))
			{
				GetTextMetricsA(Canvas->Handle, &tm);
				RealCharWidth = tm.tmAveCharWidth + tm.tmOverhang;
			}
		}
		if(RealCharWidth > NormalCharWidth)
			rcToken.Left += RealCharWidth - NormalCharWidth;
	};
  // trick to avoid clipping the last pixels of text in italic,
  // see also AdjustLastCharWidth() in TheTextDrawer.ExtTextOut()

	auto PaintHighlightToken = [&](bool bFillToEOL) -> void 
	{
		bool bComplexToken = false;
		int nC1 = 0;
		int nC2 = 0;
		int nC1Sel = 0;
		int nC2Sel = 0;
		bool bU1 = false;
		bool bSel = false;
		bool bU2 = false;
		int nX1 = 0;
		int nX2 = 0;
    // Compute some helper variables.
		nC1 = Max(FirstCol, TokenAccu.CharsBefore + 1);
		nC2 = Min(LastCol, TokenAccu.CharsBefore + TokenAccu.Len + 1);
		if(bComplexLine)
		{
			bU1 = (nC1 < nLineSelStart);
			bSel = (nC1 < nLineSelEnd) && (nC2 >= nLineSelStart);
			bU2 = (nC2 >= nLineSelEnd);
			bComplexToken = bSel && (bU1 || bU2);
		}
		else
		{
			bU1 = false; // to shut up Compiler warning Delphi 2
			bSel = bLineSelected;
			bU2 = false; // to shut up Compiler warning Delphi 2
			bComplexToken = false;
		}
    // Any token chars accumulated?
		if(TokenAccu.Len > 0)
      // Initialize the colors and the font style.
		{
			if(!bSpecialLine)
			{
				colBG = TokenAccu.BG;
				colFG = TokenAccu.FG;
			}
			if(bSpecialLine && (fOptions.Contains(eoSpecialLineDefaultFg)))
				colFG = TokenAccu.FG;
			fTextDrawer->SetStyle(TokenAccu.Style);
      // Paint the chars
			if(bComplexToken)
        // first unselected part of the token
			{
				if(bU1)
				{
					SetDrawingColors(false);
					rcToken.Right = ColumnToXValue(nLineSelStart);
					/*# with TokenAccu do */
					{
						auto& with0 = TokenAccu;
						PaintToken(with0.s, with0.Len, with0.CharsBefore, nC1, nLineSelStart);
					}
				}
        // selected part of the token
				SetDrawingColors(true);
				nC1Sel = Max(nLineSelStart, nC1);
				nC2Sel = Min(nLineSelEnd, nC2);
				rcToken.Right = ColumnToXValue(nC2Sel);
				/*# with TokenAccu do */
				{
					auto& with1 = TokenAccu;
					PaintToken(with1.s, with1.Len, with1.CharsBefore, nC1Sel, nC2Sel);
				}
        // second unselected part of the token
				if(bU2)
				{
					SetDrawingColors(false);
					rcToken.Right = ColumnToXValue(nC2);
					/*# with TokenAccu do */
					{
						auto& with2 = TokenAccu;
						PaintToken(with2.s, with2.Len, with2.CharsBefore, nLineSelEnd, nC2);
					}
				}
			}
			else
			{
				SetDrawingColors(bSel);
				rcToken.Right = ColumnToXValue(nC2);
				/*# with TokenAccu do */
				{
					auto& with3 = TokenAccu;
					PaintToken(with3.s, with3.Len, with3.CharsBefore, nC1, nC2);
				}
			}
		}

    // Fill the background to the end of this line if necessary.
		if(bFillToEOL && (rcToken.Left < rcLine.Right))
		{
			if(!bSpecialLine)
				colBG = colEditorBG();
			if(bComplexLine)
			{
				nX1 = ColumnToXValue(nLineSelStart);
				nX2 = ColumnToXValue(nLineSelEnd);
				if(rcToken.Left < nX1)
				{
					SetDrawingColors(false);
					rcToken.Right = nX1;
					if((TokenAccu.Len > 0) && (TokenAccu.Style != Synedit__15))
						AdjustEndRect();
					Canvas->FillRect(rcToken);
					rcToken.Left = nX1;
				}
				if(rcToken.Left < nX2)
				{
					SetDrawingColors(true);
					rcToken.Right = nX2;
					if((TokenAccu.Len > 0) && (TokenAccu.Style != Synedit__16))
						AdjustEndRect();
					Canvas->FillRect(rcToken);
					rcToken.Left = nX2;
				}
				if(rcToken.Left < rcLine.Right)
				{
					SetDrawingColors(false);
					rcToken.Right = rcLine.Right;
					if((TokenAccu.Len > 0) && (TokenAccu.Style != Synedit__17))
						AdjustEndRect();
					Canvas->FillRect(rcToken);
				}
			}
			else
			{
				SetDrawingColors(bLineSelected);
				rcToken.Right = rcLine.Right;
				if((TokenAccu.Len > 0) && (TokenAccu.Style != Synedit__18))
					AdjustEndRect();
				Canvas->FillRect(rcToken);
			}
		}
	};

  // Store the token chars with the attributes in the TokenAccu
  // record. This will paint any chars already stored if there is
  // a (visible) change in the attributes.

	auto AddHighlightToken = [&](const String Token, int CharsBefore, int TokenLen, TColor Foreground, TColor Background, TFontStyles Style) -> void 
	{
		bool bCanAppend = false;
		bool bSpacesTest = false;
		bool bIsSpaces = false;
		__int64 i = 0;

		auto TokenIsSpaces = [&]() -> bool 
		{
			bool result = false;
			PWideChar pTok = nullptr;
			if(!bSpacesTest)
			{
				bSpacesTest = true;
				pTok = ustr2pwchar(Token);
				while((*pTok) != L'\x00')
				{
					if((*pTok) != L'\x20')
						break;
					++pTok;
				}
				bIsSpaces = (*pTok) == L'\x00';
			}
			result = bIsSpaces;
			return result;
		};
		if((Background == clNone) || ((ActiveLineColor != clNone) && (bCurrentLine)))
		{
			Background = colEditorBG();
		}
		if(Foreground == clNone)
			Foreground = Font->Color;
    // Do we have to paint the old chars first, or can we just append?
		bCanAppend = false;
		bSpacesTest = false;
		if(TokenAccu.Len > 0)
      // font style must be the same or token is only spaces
		{
			if((TokenAccu.Style == Style) || (!(Style.Contains(TFontStyle::fsUnderline)) && !(TokenAccu.Style.Contains(TFontStyle::fsUnderline)) && TokenIsSpaces()))
        // either special colors or same colors
			{
				if((bSpecialLine && !(fOptions.Contains(eoSpecialLineDefaultFg))) || bLineSelected || ((TokenAccu.BG == Background) && ((TokenAccu.FG == Foreground) || TokenIsSpaces())))
          // background color must be the same and

          // foreground color must be the same or token is only spaces
				{
					bCanAppend = true;
				}
			}
      // If we can't append it, then we have to paint the old token chars first.
			if(!bCanAppend)
				PaintHighlightToken(false);
		}
    // Don't use AppendStr because it's more expensive.
		if(bCanAppend)
		{
			__int64 stop = 0;
			if(TokenAccu.Len + TokenLen > TokenAccu.MaxLen)
			{
				TokenAccu.MaxLen = TokenAccu.Len + TokenLen + 32;
				TokenAccu.s.SetLength(TokenAccu.MaxLen);
			}
			for(stop = TokenLen, i = 1; i <= stop; i++)
			{
				TokenAccu.s[TokenAccu.Len + i] = Token[i];
			}
			TokenAccu.Len += TokenLen;
		}
		else
		{
			__int64 stop = 0;
			TokenAccu.Len = TokenLen;
			if(TokenAccu.Len > TokenAccu.MaxLen)
			{
				TokenAccu.MaxLen = TokenAccu.Len + 32;
				TokenAccu.s.SetLength(TokenAccu.MaxLen);
			}
			for(stop = TokenLen, i = 1; i <= stop; i++)
			{
				TokenAccu.s[i] = Token[i];
			}
			TokenAccu.CharsBefore = CharsBefore;
			TokenAccu.FG = Foreground;
			TokenAccu.BG = Background;
			TokenAccu.Style = Style;
		}
	};

//++ CodeFolding

	auto PaintFoldAttributes = [&]() -> void 
	{
		int i = 0;
		int TabSteps = 0;
		int LineIndent = 0;
		int LastNonBlank = 0;
		int X = 0;
		int Y = 0;
		__int64 cRow = 0;
		int vLine = 0;
		HPEN DottedPen = 0;
		HPEN OldPen = 0;
		LOGBRUSH DottedPenDesc = {};
		int CollapsedTo = 0;
		TRect HintRect = {};
    // Paint indent guides. Use folds to determine indent value of these
    // Use a separate loop so we can use a custom pen
		if(!UseCodeFolding)
			return;

    // Paint indent guides using custom pen
		if(fCodeFolding->IndentGuides)
		{
			DottedPenDesc.lbStyle = (UINT) BS_SOLID;
			DottedPenDesc.lbColor = fCodeFolding->IndentGuidesColor;
			DottedPen = ExtCreatePen((DWORD) (PS_COSMETIC | PS_ALTERNATE), 1, &DottedPenDesc, 0, nullptr);
			try
			{
				__int64 stop = 0;
				OldPen = (HPEN) SelectObject(Canvas->Handle, DottedPen);

        // Now loop through all the lines. The indices are valid for Lines.
				for(stop = aLastRow, cRow = aFirstRow; cRow <= stop; cRow++)
				{
					vLine = RowToLine((int) cRow);
					if((vLine > Lines->Count) && !(Lines->Count == 0))
						break;

          // Set vertical coord
					Y = (LineToRow(vLine) - TopLine) * fTextHeight; // limit inside clip rect
					if((fTextHeight % 2 == 1) && (vLine % 2 == 0)) // even
						++Y;

        // Get next nonblank line
					LastNonBlank = (int) cRow;
					while((RowToLine(LastNonBlank) <= fLines->Count) && (TrimLeft(fLines->Strings[RowToLine(LastNonBlank) - 1]) == L""))
						++LastNonBlank;
					LineIndent = LeftSpaces(fLines->Strings[RowToLine(LastNonBlank) - 1], true);

   // Step horizontal coord
					TabSteps = TabWidth;
					while(TabSteps < LineIndent)
					{
						X = TabSteps * CharWidth + fTextOffset;
						if(TabSteps >= fLeftChar)
              // Move to top of vertical line
						{
							Canvas->MoveTo(X, Y);
							Y += fTextHeight;

              // Draw down and move back up
							Canvas->LineTo(X, Y);
							Y -= fTextHeight;
						}
						TabSteps += TabWidth;
					}
				}

        // Reset pen
				SelectObject(Canvas->Handle, OldPen);
			}
			__finally
			{
				DeleteObject(DottedPen);
			}
		}

    // Paint collapsed lines using changed pen
		if(fCodeFolding->ShowCollapsedLine || fCodeFolding->ShowHintMark)
		{
			int stop = 0;
			Canvas->Pen->Color = fCodeFolding->CollapsedLineColor;
			CollapsedTo = 0;
			for(stop = fAllFoldRanges->Count - 1, i = 0; i <= stop; i++)
			{
				/*# with fAllFoldRanges.Ranges[i] do */
				{
					
					if(fAllFoldRanges->Ranges->Items[i].FromLine > vLastLine)
						break;
					if(fAllFoldRanges->Ranges->Items[i].Collapsed && (fAllFoldRanges->Ranges->Items[i].FromLine > CollapsedTo) && (fAllFoldRanges->Ranges->Items[i].FromLine >= vFirstLine))
					{
						if(fCodeFolding->ShowCollapsedLine)
              // Get starting and end points
						{
							Y = (LineToRow(fAllFoldRanges->Ranges->Items[i].FromLine) - TopLine + 1) * fTextHeight - 1;
							Canvas->MoveTo(AClip.Left, Y);
							Canvas->LineTo(AClip.Right, Y);
						}
						if(fCodeFolding->ShowHintMark)
						{
							HintRect = GetCollapseMarkRect(LineToRow(fAllFoldRanges->Ranges->Items[i].FromLine), fAllFoldRanges->Ranges->Items[i].FromLine);
							if(InRange(HintRect.Left, 1, ClientWidth - 1))
							{
								fTextDrawer->BeginDrawing(Canvas->Handle);
								SetBkMode(Canvas->Handle, TRANSPARENT);
								fTextDrawer->SetForeColor(fCodeFolding->CollapsedLineColor);
								/*# with HintRect do */
								{
									auto& with1 = HintRect;
									fTextDrawer->ExtTextOut((int)(with1.Left + 2 * CharWidth / /*div*/ 7), with1.Top - (int)(LineHeight / /*div*/ 5), Synedit__19, HintRect, const_cast<PWideChar>(L"..."), 3);
								}
								SetBkMode(Canvas->Handle, OPAQUE);
								Canvas->Pen->Width = IfThen(LineHeight > 30, 2, 1);
								Canvas->Brush->Style = bsClear;
								HintRect.Top += (int)(LineHeight / /*div*/ 7);
								Canvas->Rectangle(HintRect);
								Canvas->Brush->Style = bsSolid;
								Canvas->Pen->Width = 1;
								fTextDrawer->EndDrawing();
							}
						}
					}
					if(fAllFoldRanges->Ranges->Items[i].Collapsed)
						CollapsedTo = Max(CollapsedTo, fAllFoldRanges->Ranges->Items[i].ToLine);
				}
			}
		}
	};
//-- CodeFolding

	auto PaintLines = [&]() -> void 
	{
		__int64 nLine = 0; // line index for the loop
		__int64 cRow = 0;
		String sLine; // the current line (tab expanded)
		String sLineExpandedAtWideGlyphs;
		String sToken; // highlighter token info
		int nTokenPos = 0;
		int nTokenLen = 0;
		TSynHighlighterAttributes* attr = nullptr;
		TDisplayCoord vAuxPos = {};
		int vFirstChar = 0;
		int vLastChar = 0;
		int vStartRow = 0;
		int vEndRow = 0;
    // Initialize rcLine for drawing. Note that Top and Bottom are updated
    // inside the loop. Get only the starting point for this.
		__int64 stop = 0;
		rcLine = AClip;
		rcLine.Left = fGutterWidth + fTextMargin;
		rcLine.Bottom = (aFirstRow - TopLine) * fTextHeight;
    // Make sure the token accumulator string doesn't get reassigned to often.
		if(ASSIGNED(fHighlighter))
		{
			TokenAccu.MaxLen = Max(128, fCharsInWindow);
			TokenAccu.s.SetLength(TokenAccu.MaxLen);
		}
    // Now loop through all the lines. The indices are valid for Lines.
		for(stop = vLastLine, nLine = vFirstLine; nLine <= stop; nLine++)
		{
//++ CodeFolding
			__int64 stop1 = 0;
			if(UseCodeFolding && AllFoldRanges->FoldHidesLine((int) nLine))
				continue;
//-- CodeFolding
			sLine = ((TSynEditStringList*) Lines)->ExpandedStrings[nLine - 1];
			sLineExpandedAtWideGlyphs = ExpandAtWideGlyphs(sLine);
      // determine whether will be painted with ActiveLineColor
			bCurrentLine = CaretY == nLine;
      // Initialize the text and background colors, maybe the line should
      // use special values for them.
			colFG = Font->Color;
			colBG = colEditorBG();
			bSpecialLine = DoOnSpecialLineColors((int) nLine, colFG, colBG);
			if(bSpecialLine)
        // The selection colors are just swapped, like seen in Delphi.
			{
				colSelFG = colBG;
				colSelBG = colFG;
			}
			else
			{
				colSelFG = fSelectedColor->Foreground;
				colSelBG = fSelectedColor->Background;
			}
			vStartRow = Max(LineToRow((int) nLine), aFirstRow);
			vEndRow = Min(LineToRow((int) (nLine + 1)) - 1, aLastRow);
//++ CodeFolding
			vEndRow = Max(vEndRow, vStartRow);
//-- CodeFolding
			for(stop1 = vEndRow, cRow = vStartRow; cRow <= stop1; cRow++)
			{
				if(WordWrap)
				{
					vAuxPos.Row = (int) cRow;
					if(ASSIGNED(fHighlighter))
						vAuxPos.Column = FirstCol;
					else

            // When no highlighter is assigned, we must always start from the
            // first char in a row and PaintToken will do the actual clipping
						vAuxPos.Column = 1;
					vFirstChar = fWordWrapPlugin->DisplayToBufferPos(vAuxPos).Char;
					vAuxPos.Column = LastCol;
					vLastChar = fWordWrapPlugin->DisplayToBufferPos(vAuxPos).Char;
				}
				else
				{
					vFirstChar = FirstCol;
					vLastChar = LastCol;
				}
        // Get the information about the line selection. Three different parts
        // are possible (unselected before, selected, unselected after), only
        // unselected or only selected means bComplexLine will be False. Start
        // with no selection, compute based on the visible columns.
				bComplexLine = false;
				nLineSelStart = 0;
				nLineSelEnd = 0;
        // Does the selection intersect the visible area?
				if(bAnySelection && (cRow >= vSelStart.Row) && (cRow <= vSelEnd.Row))
          // Default to a fully selected line. This is correct for the smLine
          // selection mode and a good start for the smNormal mode.
				{
					nLineSelStart = FirstCol;
					nLineSelEnd = LastCol + 1;
					if((fActiveSelectionMode == smColumn) || ((fActiveSelectionMode == smNormal) && (cRow == vSelStart.Row)))
					{
						if(vSelStart.Column > LastCol)
						{
							nLineSelStart = 0;
							nLineSelEnd = 0;
						}
						else
						{
							if(vSelStart.Column > FirstCol)
							{
								nLineSelStart = vSelStart.Column;
								bComplexLine = true;
							}
						}
					}
					if((fActiveSelectionMode == smColumn) || ((fActiveSelectionMode == smNormal) && (cRow == vSelEnd.Row)))
					{
						if(vSelEnd.Column < FirstCol)
						{
							nLineSelStart = 0;
							nLineSelEnd = 0;
						}
						else
						{
							if(vSelEnd.Column < LastCol)
							{
								nLineSelEnd = vSelEnd.Column;
								bComplexLine = true;
							}
						}
					}
				} //endif bAnySelection

        // Update the rcLine rect to this line.
				rcLine.Top = rcLine.Bottom;
				rcLine.Bottom += fTextHeight;
				bLineSelected = !bComplexLine && (nLineSelStart > 0);
				rcToken = rcLine;
				if(!ASSIGNED(fHighlighter) || !fHighlighter->Enabled)
          // Remove text already displayed (in previous rows)
				{
					if((vFirstChar != FirstCol) || (vLastChar != LastCol))
						sToken = sLineExpandedAtWideGlyphs.SubString(vFirstChar, vLastChar - vFirstChar);
					else
						sToken = sLineExpandedAtWideGlyphs.SubString(1, vLastChar);
					if((fOptions.Contains(eoShowSpecialChars)) && (sLineExpandedAtWideGlyphs.Length() < vLastChar))
						sToken = sToken + String(SynLineBreakGlyph);
					nTokenLen = sToken.Length();
					if(bComplexLine)
					{
						SetDrawingColors(false);
						rcToken.Left = Max(rcLine.Left, ColumnToXValue(FirstCol));
						rcToken.Right = Min(rcLine.Right, ColumnToXValue(nLineSelStart));
						PaintToken(sToken, nTokenLen, 0, FirstCol, nLineSelStart);
						rcToken.Left = Max(rcLine.Left, ColumnToXValue(nLineSelEnd));
						rcToken.Right = Min(rcLine.Right, ColumnToXValue(LastCol));
						PaintToken(sToken, nTokenLen, 0, nLineSelEnd, LastCol);
						SetDrawingColors(true);
						rcToken.Left = Max(rcLine.Left, ColumnToXValue(nLineSelStart));
						rcToken.Right = Min(rcLine.Right, ColumnToXValue(nLineSelEnd));
						PaintToken(sToken, nTokenLen, 0, nLineSelStart, nLineSelEnd - 1);
					}
					else
					{
						SetDrawingColors(bLineSelected);
						PaintToken(sToken, nTokenLen, 0, FirstCol, LastCol);
					}
				}
				else

          // Initialize highlighter with line text and range info. It is
          // necessary because we probably did not scan to the end of the last
          // line - the internal highlighter range might be wrong.
				{
					if(nLine == 1)
						fHighlighter->ResetRange();
					else
						fHighlighter->SetRange(((TSynEditStringList*) Lines)->Ranges[nLine - 2]);
					fHighlighter->SetLineExpandedAtWideGlyphs(sLine, sLineExpandedAtWideGlyphs, (int) (nLine - 1));
          // Try to concatenate as many tokens as possible to minimize the count
          // of ExtTextOutW calls necessary. This depends on the selection state
          // or the line having special colors. For spaces the foreground color
          // is ignored as well.
					TokenAccu.Len = 0;
					nTokenPos = 0;
					nTokenLen = 0;
					attr = nullptr;
          // Test first whether anything of this token is visible.
					while(!fHighlighter->GetEol())
					{
						nTokenPos = fHighlighter->GetExpandedTokenPos();
						sToken = fHighlighter->GetExpandedToken();
						nTokenLen = sToken.Length();
						if(nTokenPos + nTokenLen >= vFirstChar)
						{
							if(nTokenPos + nTokenLen > vLastChar)
							{
								if(nTokenPos > vLastChar)
									break;
								if(WordWrap)
									nTokenLen = vLastChar - nTokenPos - 1;
								else
									nTokenLen = vLastChar - nTokenPos;
							}
              // Remove offset generated by tokens already displayed (in previous rows)
							nTokenPos -= vFirstChar - FirstCol;
              // It's at least partially visible. Get the token attributes now.
							attr = fHighlighter->GetTokenAttribute();
							if(ASSIGNED(attr))
								AddHighlightToken(sToken, nTokenPos, nTokenLen, attr->Foreground, attr->Background, attr->Style);
							else
								AddHighlightToken(sToken, nTokenPos, nTokenLen, colFG, colBG, Font->Style);
						}
            // Let the highlighter scan the next token.
						fHighlighter->Next();
					}
          // Draw anything that's left in the TokenAccu record. Fill to the end
          // of the invalid area with the correct colors.
					if((fOptions.Contains(eoShowSpecialChars)) && fHighlighter->GetEol())
					{
						if((attr == nullptr) || (attr != fHighlighter->CommentAttribute))
							attr = fHighlighter->WhitespaceAttribute;
						AddHighlightToken(String(SynLineBreakGlyph), nTokenPos + nTokenLen, 1, attr->Foreground, attr->Background, Synedit__20);
					}
					PaintHighlightToken(true);
				}
        // Now paint the right edge if necessary. We do it line by line to reduce
        // the flicker. Should not cost very much anyway, compared to the many
        // calls to ExtTextOutW.
				if(bDoRightEdge)
				{
					Canvas->MoveTo(nRightEdge, rcLine.Top);
					Canvas->LineTo(nRightEdge, rcLine.Bottom + 1);
				}
			} //endfor cRow
			bCurrentLine = false;
		} //endfor cLine
	};

/* end local procedures */
	vFirstLine = RowToLine(aFirstRow);
	vLastLine = RowToLine(aLastRow);
	bCurrentLine = false;
  // If the right edge is visible and in the invalid area, prepare to paint it.
  // Do this first to realize the pen when getting the dc variable.
	SynTabGlyphString = SynTabGlyph;
	bDoRightEdge = false;
	if(fRightEdge > 0) // column value
	{
		nRightEdge = fTextOffset + fRightEdge * fCharWidth; // pixel value
		if((nRightEdge >= AClip.Left) && (nRightEdge <= AClip.Right))
		{
			bDoRightEdge = true;
			Canvas->Pen->Color = fRightEdgeColor;
			Canvas->Pen->Width = 1;
		}
	}
  // Do everything else with API calls. This (maybe) realizes the new pen color.
	dc = Canvas->Handle;
  // If anything of the two pixel space before the text area is visible, then
  // fill it with the component background color.
	if(AClip.Left < fGutterWidth + fTextMargin)
	{
		rcToken = AClip;
		rcToken.Left = Max(AClip.Left, fGutterWidth);
		rcToken.Right = fGutterWidth + fTextMargin;
    // Paint whole left edge of the text with same color.
    // (value of WhiteAttribute can vary in e.g. MultiSyn)
		if(Highlighter != nullptr)
			Highlighter->ResetRange();
		Canvas->Brush->Color = colEditorBG();
		Canvas->FillRect(rcToken);
    // Adjust the invalid area to not include this area.
		AClip.Left = rcToken.Right;
	}
  // Paint the visible text lines. To make this easier, compute first the
  // necessary information about the selected area: is there any visible
  // selected area, and what are its lines / columns?
	if(vLastLine >= vFirstLine)
	{
		ComputeSelectionInfo();
		fTextDrawer->Style = Font->Style;
		fTextDrawer->BeginDrawing(dc);
		try
		{
			PaintLines();
		}
		__finally
		{
			fTextDrawer->EndDrawing();
		}
	}
  // If there is anything visible below the last line, then fill this as well.
	rcToken = AClip;
	rcToken.Top = (aLastRow - TopLine + 1) * fTextHeight;
	if(rcToken.Top < rcToken.Bottom)
	{
		if(Highlighter != nullptr)
			Highlighter->ResetRange();
		Canvas->Brush->Color = colEditorBG();
		Canvas->FillRect(rcToken);
    // Draw the right edge if necessary.
		if(bDoRightEdge)
		{
			Canvas->MoveTo(nRightEdge, rcToken.Top);
			Canvas->LineTo(nRightEdge, rcToken.Bottom + 1);
		}
	}

//++ CodeFolding
  // This messes with pen colors, so draw after right margin has been drawn
	PaintFoldAttributes();
//-- CodeFolding
}

void __fastcall TCustomSynEdit::PasteFromClipboard()
{
	TSynSelectionMode PasteMode = smNormal;
	HGLOBAL Mem = 0;
	PByte P = nullptr;
	String ClipText;
	String Spaces;
	if(!CanPaste)
		return;
	DoOnPaintTransient(ttBefore);
	PasteMode = SelectionMode;
  // Check for our special format and read PasteMode.
  // The text is ignored as it is ANSI-only to stay compatible with programs
  // using the ANSI version of SynEdit.
  //
  // Instead we take the text stored in CF_UNICODETEXT or CF_TEXT.
	if(Clipboard()->HasFormat((WORD) SynEditClipboardFormat))
	{
		Clipboard()->Open();
		try
		{
			Mem = (HGLOBAL) Clipboard()->GetAsHandle(SynEditClipboardFormat);
			P = ((Byte*) GlobalLock(Mem));
			try
			{
				if(P != nullptr)
					PasteMode = (*(PSynSelectionMode) (NativeInt) P);
			}
			__finally
			{
				GlobalUnlock(Mem);
			}
		}
		__finally
		{
			Clipboard()->Close();
		}
	}
  // SetSelTextPrimitiveEx Encloses the undo actions in Begin/EndUndoBlock
	ClipText = GetClipboardText();
	if(Options.Contains(eoTabsToSpaces))
	{
		Spaces = StringOfChar(L'\x20', TabWidth);
		ClipText = StringReplace(ClipText, L"\x09", Spaces, Synedit__21);
	}
	SetSelTextPrimitiveEx(PasteMode, ClipText, true);
	EnsureCursorPosVisible();
	DoOnPaintTransient(ttAfter);
}

void __fastcall TCustomSynEdit::SelectAll()
{
	TBufferCoord LastPt = {};
	LastPt.Char = 1;
	LastPt.Line = Lines->Count;
	if(LastPt.Line > 0)
		LastPt.Char += Lines->Strings[LastPt.Line - 1].Length();
	else
		LastPt.Line = 1;
	SetCaretAndSelection(LastPt, BufferCoord(1, 1), LastPt);
}

void __fastcall TCustomSynEdit::SetBlockBegin(const TBufferCoord& cValue)
{
	TBufferCoord Value = cValue;
	int nInval1 = 0;
	int nInval2 = 0;
	bool SelChanged = false;
	ActiveSelectionMode = SelectionMode;
	Value.Char = Max(Value.Char, 1);
	Value.Line = MinMax(Value.Line, 1, Lines->Count);
	if(fActiveSelectionMode == smNormal)
	{
		if((Value.Line >= 1) && (Value.Line <= Lines->Count))
			Value.Char = Min(Value.Char, Lines->Strings[Value.Line - 1].Length() + 1);
		else
			Value.Char = 1;
	}
	if(SelAvail)
	{
		if(fBlockBegin.Line < fBlockEnd.Line)
		{
			nInval1 = Min(Value.Line, fBlockBegin.Line);
			nInval2 = Max(Value.Line, fBlockEnd.Line);
		}
		else
		{
			nInval1 = Min(Value.Line, fBlockEnd.Line);
			nInval2 = Max(Value.Line, fBlockBegin.Line);
		}
		fBlockBegin = Value;
		fBlockEnd = Value;
		InvalidateLines(nInval1, nInval2);
		SelChanged = true;
	}
	else
	{
		SelChanged = (fBlockBegin.Char != Value.Char) || (fBlockBegin.Line != Value.Line) || (fBlockEnd.Char != Value.Char) || (fBlockEnd.Line != Value.Line);
		fBlockBegin = Value;
		fBlockEnd = Value;
	}
	if(SelChanged)
		StatusChanged(Synedit__22);
}

void __fastcall TCustomSynEdit::SetBlockEnd(const TBufferCoord& cValue)
{
	TBufferCoord Value = cValue;
	int nLine = 0;
	ActiveSelectionMode = SelectionMode;
	if(!(Options.Contains(eoNoSelection)))
	{
		Value.Char = Max(Value.Char, 1);
		Value.Line = MinMax(Value.Line, 1, Lines->Count);
		if(fActiveSelectionMode == smNormal)
		{
			if((Value.Line >= 1) && (Value.Line <= Lines->Count))
				Value.Char = Min(Value.Char, Lines->Strings[Value.Line - 1].Length() + 1);
			else
				Value.Char = 1;
		}
		if((Value.Char != fBlockEnd.Char) || (Value.Line != fBlockEnd.Line))
		{
			if((Value.Char != fBlockEnd.Char) || (Value.Line != fBlockEnd.Line))
			{
				if((fActiveSelectionMode == smColumn) && (Value.Char != fBlockEnd.Char))
				{
					InvalidateLines(Min(fBlockBegin.Line, Min(fBlockEnd.Line, Value.Line)), Max(fBlockBegin.Line, Max(fBlockEnd.Line, Value.Line)));
					fBlockEnd = Value;
				}
				else
				{
					nLine = fBlockEnd.Line;
					fBlockEnd = Value;
					if((fActiveSelectionMode != smColumn) || (fBlockBegin.Char != fBlockEnd.Char))
						InvalidateLines(nLine, fBlockEnd.Line);
				}
				StatusChanged(Synedit__23);
			}
		}
	}
}

void __fastcall TCustomSynEdit::SetCaretX(int Value)
{
	SetCaretXY(BufferCoord(Value, fCaretY));
}

void __fastcall TCustomSynEdit::SetCaretY(int Value)
{
	SetCaretXY(BufferCoord(fCaretX, Value));
}

void __fastcall TCustomSynEdit::InternalSetCaretX(int Value)
{
	InternalSetCaretXY(BufferCoord(Value, fCaretY));
}

void __fastcall TCustomSynEdit::InternalSetCaretY(int Value)
{
	InternalSetCaretXY(BufferCoord(fCaretX, Value));
}

TBufferCoord __fastcall TCustomSynEdit::GetCaretXY()
{
	TBufferCoord result = {};
	result.Char = CaretX;
	result.Line = CaretY;
	return result;
}

int __fastcall TCustomSynEdit::GetDisplayX()
{
	int result = 0;
	result = DisplayXY.Column;
	return result;
}

int __fastcall TCustomSynEdit::GetDisplayY()
{
	int result = 0;
//++ CodeFolding
	if(!WordWrap && !UseCodeFolding)
//-- CodeFolding
		result = CaretY;
	else
		result = DisplayXY.Row;
	return result;
}

TDisplayCoord __fastcall TCustomSynEdit::GetDisplayXY()
{
	TDisplayCoord result = {};
	result = BufferToDisplayPos(CaretXY);
	if(WordWrap && fCaretAtEOL)
	{
		if(result.Column == 1)
		{
			--result.Row;
			result.Column = fWordWrapPlugin->GetRowLength(result.Row) + 1;
		}
		else

      // Work-around situations where fCaretAtEOL should have been updated because of
      //text change (it's only valid when Column = 1). Updating it in ProperSetLine()
      //would probably be the right thing, but...
		{
			fCaretAtEOL = false;
		}
	}
	return result;
}
//there are two setCaretXY methods.  One Internal, one External.  The published
//property CaretXY (re)sets the block as well

void __fastcall TCustomSynEdit::SetCaretXY(const TBufferCoord& Value)
{
	IncPaintLock();
	try
	{
		fStatusChanges << scSelection;
		SetCaretXYEx(true, Value);
		if(SelAvail)
			InvalidateSelection();
		fBlockBegin.Char = fCaretX;
		fBlockBegin.Line = fCaretY;
		fBlockEnd = fBlockBegin;
	}
	__finally
	{
		DecPaintLock();
	}
}

void __fastcall TCustomSynEdit::InternalSetCaretXY(const TBufferCoord& Value)
{
	SetCaretXYEx(true, Value);
}

void __fastcall TCustomSynEdit::UpdateLastCaretX()
{
	fLastCaretX = DisplayX;
}

void __fastcall TCustomSynEdit::SetCaretXYEx(bool CallEnsureCursorPos, const TBufferCoord& cValue)
{
	TBufferCoord Value = cValue;
	int nMaxX = 0;
	bool vTriggerPaint = false;
	String S;
	String TS;
	fCaretAtEOL = false;
	vTriggerPaint = HandleAllocated();
	if(vTriggerPaint)
		DoOnPaintTransient(ttBefore);
	nMaxX = MaxInt;
	if(Value.Line > Lines->Count)
		Value.Line = Lines->Count;
	if(Value.Line < 1)
    // this is just to make sure if Lines stringlist should be empty
	{
		Value.Line = 1;
		if(!(fOptions.Contains(eoScrollPastEol)))
			nMaxX = 1;
	}
	else
	{
		if(!(fOptions.Contains(eoScrollPastEol)))
			nMaxX = Lines->Strings[Value.Line - 1].Length() + 1;
	}
	if((Value.Char > nMaxX) && (!(Options.Contains(eoScrollPastEol))))
		Value.Char = nMaxX;
	if(Value.Char < 1)
		Value.Char = 1;

  //Trim here
	if((Value.Line != fCaretY) && (fOptions.Contains(eoTrimTrailingSpaces)) && (fCaretY <= Lines->Count) && (fCaretY >= 1))
	{
		S = Lines->Strings[fCaretY - 1];
		TS = TrimTrailingSpaces(S);
		if(S != TS)
			Lines->Strings[fCaretY - 1] = TS;
	}
	if((Value.Char != fCaretX) || (Value.Line != fCaretY))
	{
		IncPaintLock();
		try

      // simply include the flags, fPaintLock is > 0
		{
			if(fCaretX != Value.Char)
			{
				fCaretX = Value.Char;
				fStatusChanges << scCaretX;
			}
			if(fCaretY != Value.Line)
			{
				if((ActiveLineColor != clNone) || (fOptions.Contains(eoShowLigatures)))
				{
					InvalidateLine(Value.Line);
					InvalidateLine(fCaretY);
				}
				fCaretY = Value.Line;
				fStatusChanges << scCaretY;
//++ CodeFolding
				UncollapseAroundLine(fCaretY);
//-- CodeFolding
			}
      // Call UpdateLastCaretX before DecPaintLock because the event handler it
      // calls could raise an exception, and we don't want fLastCaretX to be
      // left in an undefined state if that happens.
			UpdateLastCaretX();
			if(CallEnsureCursorPos)
				EnsureCursorPosVisible();
			fStateFlags << sfCaretChanged;
//++ Flicker Reduction
//      Include(fStateFlags, sfScrollbarChanged);
//-- Flicker Reduction
		}
		__finally
		{
			DecPaintLock();
		}
	}
	else

    // Also call UpdateLastCaretX if the caret didn't move. Apps don't know
    // anything about fLastCaretX and they shouldn't need to. So, to avoid any
    // unwanted surprises, always update fLastCaretX whenever CaretXY is
    // assigned to.
    // Note to SynEdit developers: If this is undesirable in some obscure
    // case, just save the value of fLastCaretX before assigning to CaretXY and
    // restore it afterward as appropriate.
	{
		UpdateLastCaretX();
	}
	if(vTriggerPaint)
		DoOnPaintTransient(ttAfter);
}

bool __fastcall TCustomSynEdit::CaretInView()
{
	bool result = false;
	TDisplayCoord vCaretRowCol = {};
	vCaretRowCol = DisplayXY;
	result = (vCaretRowCol.Column >= LeftChar) && (vCaretRowCol.Column <= LeftChar + CharsInWindow) && (vCaretRowCol.Row >= TopLine) && (vCaretRowCol.Row <= TopLine + LinesInWindow);
	return result;
}

void __fastcall TCustomSynEdit::SetActiveLineColor(TColor Value)
{
	if(fActiveLineColor != Value)
	{
		fActiveLineColor = Value;
		InvalidateLine(CaretY);
	}
}

void __fastcall TCustomSynEdit::SetFont(TFont* const Value)
{
	HDC DC = 0;
	THandle Save = 0;
	TTextMetric Metrics = {};
	int AveCW = 0;
	int MaxCW = 0;
	Value->Quality = FontQuality;
	DC = GetDC(0);
	Save = (THandle) SelectObject(DC, Value->Handle);
	GetTextMetrics(DC, &Metrics);
	SelectObject(DC, (void*) Save);
	ReleaseDC(0, DC);
	/*# with Metrics do */
	{
		auto& with0 = Metrics;
		AveCW = with0.tmAveCharWidth;
		MaxCW = with0.tmMaxCharWidth;
	}
	switch(AveCW == MaxCW)
	{
		case true:
		inherited::Font = const_cast<TFont*>(Value);
		break;
		case false:
		{
			/*# with fFontDummy do */
			{
				auto with1 = fFontDummy;
				with1->Color = Value->Color;
				with1->Pitch = TFontPitch::fpFixed;
				with1->Size = Value->Size;
				with1->Style = Value->Style;
				with1->Name = Value->Name;
				with1->Quality = Value->Quality;
			}
			inherited::Font = fFontDummy;
		}
		break;
		default:
		  ;
		break;
	}
	((TSynEditStringList*) fLines)->FontChanged();
	if(fGutter->ShowLineNumbers)
		GutterChanged(this);
}

void __fastcall TCustomSynEdit::SetGutterWidth(int Value)
{
	Value = Max(Value, 0);
	if(fGutterWidth != Value)
	{
		fGutterWidth = Value;
		fTextOffset = fGutterWidth + fTextMargin - (LeftChar - 1) * fCharWidth;
		if(HandleAllocated())
		{
			fCharsInWindow = (int)(Max(ClientWidth - fGutterWidth - fTextMargin, 0) / /*div*/ fCharWidth);
			if(WordWrap)
				fWordWrapPlugin->DisplayChanged();
			UpdateScrollBars();
			Invalidate();
		}
	}
}

void __fastcall TCustomSynEdit::SetLeftChar(int Value)
{
	int MaxVal = 0;
	int iDelta = 0;
	TRect iTextArea = {};
	if(WordWrap)
		Value = 1;
	if(Options.Contains(eoScrollPastEol))
		MaxVal = MaxInt - CharsInWindow;
	else
	{
		MaxVal = ((TSynEditStringList*) Lines)->LengthOfLongestLine;
		if(MaxVal > CharsInWindow)
			MaxVal = MaxVal - CharsInWindow + 1;
		else
			MaxVal = 1;
	}
	Value = MinMax(Value, 1, MaxVal);
	if(Value != fLeftChar)
	{
		iDelta = fLeftChar - Value;
		fLeftChar = Value;
		fTextOffset = fGutterWidth + fTextMargin - (LeftChar - 1) * fCharWidth;
		if(Abs(iDelta) < CharsInWindow)
		{
			iTextArea = ClientRect;
			iTextArea.Left += fGutterWidth + fTextMargin;
			ScrollWindow(Handle, iDelta * CharWidth, 0, &iTextArea, &iTextArea);
		}
		else
		InvalidateLines(-1, -1);
		UpdateScrollBars();
		StatusChanged(Synedit__24);
	}
}

void __fastcall TCustomSynEdit::SetLines(TStrings* Value)
{
	Lines->Assign(Value);
}

void __fastcall TCustomSynEdit::SetLineText(String Value)
{
	if((CaretY >= 1) && (CaretY <= Max(1, Lines->Count)))
		Lines->Strings[CaretY - 1] = Value;
}

void __fastcall TCustomSynEdit::SetFontQuality(TFontQuality AValue)
{
	Font->Quality = AValue;
}

void __fastcall TCustomSynEdit::SetName(const TComponentName Value)
{
	bool TextToName = false;
	TextToName = (ComponentState * Synedit__25 == Synedit__26) && (TrimRight(Text) == Name);
	inherited::SetName(Value);
	if(TextToName)
		Text = Value;
}

void __fastcall TCustomSynEdit::SetScrollBars(TScrollStyle Value)
{
	if(FScrollBars != Value)
	{
		FScrollBars = Value;
		UpdateScrollBars();
		Invalidate();
	}
}

void __fastcall TCustomSynEdit::SetSelText(const String Value)
{
	SetSelTextPrimitiveEx(fActiveSelectionMode, Value, true);
}

// This is really a last minute change and I hope I did it right.
// Reason for this modification: next two lines will loose the CaretX position
// if eoScrollPastEol is not set in Options. That is not really a good idea
// as we would typically want the cursor to stay where it is.
// To fix this (in the absence of a better idea), I changed the code in
// DeleteSelection not to trim the string if eoScrollPastEol is not set.

/*
   Works in two stages:
     -  First deletes selection.
     -  Second inserts text taking into account PasteMode.
     -  SilentDelete does not restore selection on undo
     -  The routine takes full care of undo/redo
*/

void __fastcall TCustomSynEdit::SetSelTextPrimitiveEx(TSynSelectionMode PasteMode, String Value, bool AddToUndoList/*# = true*/, bool SilentDelete/*# = false*/)
{
	TBufferCoord BB = {};
	TBufferCoord BE = {};
	String TempString;
	String SelectedText;

	auto DeleteSelection = [&]() -> void 
	{
		int I = 0;
		switch(fActiveSelectionMode)
		{
			case smNormal:
			{
				if(Lines->Count > 0)
              // Create a string that contains everything on the first line up
              // to the selection mark, and everything on the last line after
              // the selection mark.
				{
					TempString = Lines->Strings[BB.Line - 1].SubString(1, BB.Char - 1)
					           + Lines->Strings[BE.Line - 1].SubString(BE.Char, MaxInt);
              // Delete all lines in the selection range.
					((TSynEditStringList*) Lines)->DeleteLines(BB.Line, BE.Line - BB.Line);
              // Put the stuff that was outside of selection back in.
					if(Options.ToInt() >= Synedit__27.ToInt())
						TempString = TrimTrailingSpaces(TempString);
					Lines->Strings[BB.Line - 1] = TempString;
				}
				CaretXY = BB;
			}
			break;
          // swap X if needed
			case smColumn:
			{
				int stop = 0;
				if(BB.Char > BE.Char)
					SwapInt(BB.Char, BE.Char);
          // swap Y if needed
				if(BB.Line > BE.Line)
					SwapInt(BB.Line, BE.Line);
				for(stop = BE.Line - 1, I = BB.Line - 1; I <= stop; I++)
				{
					TempString = Lines->Strings[I];
					TempString.Delete(BB.Char, BE.Char - BB.Char);
					ProperSetLine(I, TempString);
				}
          // Lines never get deleted completely, so keep caret on the begin.
				CaretXY = BB;
          // Column deletion never removes a line entirely, so no mark
          // updating is needed here.
			}
			break;
			case smLine:
			{
				if(BE.Line == Lines->Count)
				{
					Lines->Strings[BE.Line - 1] = L"";
					((TSynEditStringList*) Lines)->DeleteLines(BB.Line, BE.Line - BB.Line);
				}
				else
				((TSynEditStringList*) Lines)->DeleteLines(BB.Line - 1, BE.Line - BB.Line + 1);
          // smLine deletion always resets to first column.
				CaretXY = BufferCoord(1, BB.Line);
			}
			break;
			default:
			  ;
			break;
		}
	};

	auto InsertText = [&]() -> void 
	{

		auto InsertNormal = [&]() -> void 
		{
			String sLeftSide;
			String sRightSide;
			TArray<String> NewLines;
			int LineCount = 0;
			int I = 0;
			NewLines = StringToLines(Value);
			LineCount = NewLines.Length;
			if(LineCount == 0)
				return;
			sLeftSide = LineText.SubString(1, CaretX - 1);
			if(CaretX - 1 > sLeftSide.Length())
			{
				sLeftSide = sLeftSide + StringOfChar(L'\x20', CaretX - 1 - sLeftSide.Length());
			}
			sRightSide = LineText.SubString(CaretX, LineText.Length() - (CaretX - 1));

      // step1: insert the first line of Value into current line
			NewLines[0] = sLeftSide + NewLines[0];
      // step2: insert left lines of Value
			NewLines[LineCount - 1] = NewLines[LineCount - 1] + sRightSide;
			if(Options.Contains(eoTrimTrailingSpaces))
			{
				int stop = 0;
				for(stop = LineCount - 1, I = 0; I <= stop; I++)
				{
					NewLines[I] = TrimTrailingSpaces(NewLines[I]);
				}
			}
			Lines->Strings[CaretY - 1] = NewLines[0];
			if(LineCount > 1)
			{
				((TSynEditStringList*) Lines)->InsertStrings(CaretY, NewLines, 1);
				fCaretY += LineCount - 1;
				fStatusChanges << scCaretY;
			}
			if(Options.Contains(eoTrimTrailingSpaces))
				fCaretX = 1 + Lines->Strings[CaretY - 1].Length() - TrimTrailingSpaces(sRightSide).Length();
			else
				fCaretX = 1 + Lines->Strings[CaretY - 1].Length() - sRightSide.Length();
			StatusChanged(Synedit__28);
		};

		auto InsertColumn = [&]() -> void 
		{
			String Str;
			PWideChar Start = nullptr;
			PWideChar P = nullptr;
			int Len = 0;
			int InsertPos = 0;
      // Insert string at current position
			InsertPos = CaretX;
			Start = ustr2pwchar(Value);
			do
			{
				P = GetEOL(Start);
				if(P != Start)
				{
					Str.SetLength(P - Start);
					Move(Start, ustr2pwchar(Str, 1 - 1), (P - Start) * sizeof(WideChar));
					if(CaretY > Lines->Count)
					{
						TempString = StringOfChar(L'\x20', InsertPos - 1) + Str;
						Lines->Add(L"");
					}
					else
					{
						TempString = Lines->Strings[CaretY - 1];
						Len = TempString.Length();
						if(Len < InsertPos)
						{
							TempString = TempString + StringOfChar(L'\x20', InsertPos - Len - 1) + Str;
						}
						else
						TempString.Insert(Str,	InsertPos);
					}
					ProperSetLine(CaretY - 1, TempString);
				}
				if((*P) == L'\x0d')
				{
					++P;
					if((*P) == L'\x0a')
						++P;
					++fCaretY;
					fStatusChanges << scCaretY;
				}
				Start = P;
			}
			while(!((*P) == L'\x00'));
			fCaretX += Str.Length();
			fStatusChanges << scCaretX;
		};

		auto InsertLine = [&]() -> void 
		{
			String Str;
			TArray<String> NewLines;
			int LineCount = 0;
			int I = 0;
			int Index = 0;
			NewLines = StringToLines(Value);
			LineCount = NewLines.Length;
			if(LineCount == 0)
				return;
			if(LineCount == 1)
      /* When triggered from copy/past in smLineMode Value contains at least
        one LB and theLineCount would be at least 2.  This is the case
        that occurs when text is selected in line mode and say you type
        a single character*/
			{
				Str = NewLines[0];
				if(Options.Contains(eoTrimTrailingSpaces))
					Str = TrimTrailingSpaces(Str);
				if(CaretY <= Lines->Count)
				{
					Str = NewLines[0] + Lines->Strings[CaretY - 1];
					Lines->Strings[CaretY - 1] = Str;
				}
				else
				Lines->Add(Str);
				fCaretX = 1 + Str.Length();
			}
			else
			{
				fCaretX = 1;
        // Remove last empty line
				if(NewLines[LineCount - 1] == L"")
				{
					//Delete(NewLines, LineCount - 1, 1);
					NewLines[LineCount - 1] = L"";
					--LineCount;
				}
				if(Options.Contains(eoTrimTrailingSpaces))
				{
					int stop = 0;
					for(stop = LineCount - 1, I = 0; I <= stop; I++)
					{
						NewLines[I] = TrimTrailingSpaces(NewLines[I]);
					}
				}
				Index = fCaretY - 1;  // zero based
				if(!InsertMode)
          // Delete Lines that will be overwritten
				{
					((TSynEditStringList*) Lines)->DeleteLines(Index, Min(LineCount, Lines->Count - Index));
				}
        // Now add the lines
				((TSynEditStringList*) Lines)->InsertStrings(Index, NewLines);
				fCaretY += LineCount;
				fStatusChanges << scCaretY;
			}
			StatusChanged(Synedit__29);
		};
		if(Value == L"")
			return;
		switch(PasteMode)
		{
			case smNormal:
			InsertNormal();
			break;
			case smColumn:
			InsertColumn();
			break;
			case smLine:
			InsertLine();
			break;
			default:
			  ;
			break;
		}
    // Force caret reset
		CaretXY = CaretXY;
	};
	BB = BlockBegin;
	BE = BlockEnd;
	if((Value.Length() == 0) && (BB == BE))
		return;  // nothing to do
	Lines->BeginUpdate();
	IncPaintLock();
	if(AddToUndoList)
		BeginUndoBlock();
	else
		fUndoRedo->Lock();
	try
	{
		SelectedText = SelText;
		if(SelectedText != L"")
			DeleteSelection();
		if(Value.Length() > 0)
			InsertText();
		if(CaretY < 1)
			CaretY = 1;
	}
	__finally
	{
		if(AddToUndoList)
			EndUndoBlock();
		else
			fUndoRedo->Unlock();
		DecPaintLock();
		Lines->EndUpdate();
	}
}

void __fastcall TCustomSynEdit::SynSetText(const String Value)
{
	Lines->Text = Value;
	UpdateScrollBars();
}

void __fastcall TCustomSynEdit::SetTopLine(int Value)
{
	int Delta = 0;
	if(Options.Contains(eoScrollPastEof))
		Value = Min(Value, DisplayLineCount);
	else
		Value = Min(Value, DisplayLineCount - fLinesInWindow + 1);
	Value = Max(Value, 1);
	if(Value != TopLine)
	{
		Delta = TopLine - Value;
		fTopLine = Value;
		if(Abs(Delta) < fLinesInWindow)
			ScrollWindow(Handle, 0, fTextHeight * Delta, nullptr, nullptr);
		else
			Invalidate();
		UpdateScrollBars();
		StatusChanged(Synedit__30);
	}
}

//++ CodeFolding

void __fastcall TCustomSynEdit::SetUseCodeFolding(bool Value)
{
	bool ValidValue = false;
	ValidValue = Value && ((ASSIGNED(fHighlighter) && (ObjectIs(fHighlighter, TSynCustomCodeFoldingHighlighter*))) || ASSIGNED(fOnScanForFoldRanges));
	if(fUseCodeFolding != ValidValue)
	{
		AllFoldRanges->Reset();
		fUseCodeFolding = ValidValue;
		Invalidate(); // better Invalidate before changing LeftChar and TopLine
		if(ValidValue)
      // !!Mutually exclusive with WordWrap to reduce complexity
		{
			WordWrap = false;
			FullFoldScan();
		}
		OnCodeFoldingChange(this);
		InvalidateGutter();
	}
}

void __fastcall TCustomSynEdit::OleDragEnter(TObject* Sender, IDataObject* DataObject, TShiftState State, const TPoint& cMousePt, int& Effect, HRESULT& Result)
{
	TPoint MousePt = cMousePt;
	if(ReadOnly || !HasFormat(DataObject, (TClipFormat) CF_UNICODETEXT))
		Effect = DROPEFFECT_NONE;
}

void __fastcall TCustomSynEdit::OleDragLeave(TObject* Sender, HRESULT& Result)
{
	fScrollTimer->Enabled = false;
	if(fStateFlags.Contains(sfOleDragSource)) //internal dragging
		ComputeCaret(fMouseDownX, fMouseDownY);
}

void __fastcall TCustomSynEdit::OleDragOver(TObject* Sender, IDataObject* DataObject, TShiftState State, const TPoint& cMousePt, int& Effect, HRESULT& Result)
{
	TPoint MousePt = cMousePt;
	TDisplayCoord vNewPos = {};
	TPoint Pt = {};
	Pt = ScreenToClient(MousePt);
	vNewPos = PixelsToNearestRowColumn(Pt.X, Pt.Y);
	vNewPos.Column = MinMax(vNewPos.Column, LeftChar, LeftChar + CharsInWindow - 1);
	vNewPos.Row = MinMax(vNewPos.Row, TopLine, TopLine + LinesInWindow - 1);
	InternalCaretXY = DisplayToBufferPos(vNewPos);
	ComputeScroll(Pt.X, Pt.Y);
}

void __fastcall TCustomSynEdit::OleDrop(TObject* Sender, IDataObject* DataObject, TShiftState State, const TPoint& cMousePt, int& Effect, HRESULT& Result)
{
	TPoint MousePt = cMousePt;
	TBufferCoord vNewCaret = {};
	bool DoDrop = false;
	bool DropAfter = false;
	bool DropMove = false;
	TBufferCoord vBB = {};
	TBufferCoord vBE = {};
	String DragDropText;
	bool ChangeScrollPastEOL = false;
	tagFORMATETC* FormatEtc;
	tagSTGMEDIUM Medium;
	TPoint Pt = {};
	Pt = ScreenToClient(MousePt);
	DropMove = Effect == DROPEFFECT_MOVE;
	IncPaintLock();
	try
	{
		ComputeCaret(Pt.X, Pt.Y);
		vNewCaret = CaretXY;
		if(!(fStateFlags.Contains(sfOleDragSource)))
		{
			DoDrop = true;
			DropAfter = false;
		}
		else

      // Internal dragging
		{
			vBB = BlockBegin;
			vBE = BlockEnd;
			DropAfter = (vNewCaret.Line > vBE.Line) || ((vNewCaret.Line == vBE.Line) && ((vNewCaret.Char > vBE.Char) || ((!DropMove) && (vNewCaret.Char == vBE.Char))));
			DoDrop = DropAfter || (vNewCaret.Line < vBB.Line) || ((vNewCaret.Line == vBB.Line) && ((vNewCaret.Char < vBB.Char) || ((!DropMove) && (vNewCaret.Char == vBB.Char))));
		}
		if(DoDrop)
		{
			/*# with FormatEtc do */
			{
				auto& with0 = FormatEtc;
				with0->cfFormat = (TClipFormat) CF_UNICODETEXT;
				with0->dwAspect = DVASPECT_CONTENT;
				with0->ptd = nullptr;
				with0->tymed = TYMED_HGLOBAL;
				with0->lindex = -1;
			}
			if(DataObject->GetData(FormatEtc, &Medium) == S_OK)
			{
				if(Medium.hGlobal != 0)
				{
					DragDropText = ((PChar) GlobalLock(Medium.hGlobal));
					GlobalUnlock(Medium.hGlobal);
					DoDrop = DragDropText != L"";
				}
				else
				DoDrop = false;
				ReleaseStgMedium(&Medium);
			}
			else
			DoDrop = false;
		}
		if(DoDrop)
		{
			BeginUndoBlock();
			try

        // delete the selected text if necessary
			{
				if(DropMove)
				{
					if(fStateFlags.Contains(sfOleDragSource))
            // Internal dragging
					{
						Effect = DROPEFFECT_NONE;  // do not clear selection after drop
						SelText = L"";
            // adjust horizontal drop position
						if(DropAfter && (vNewCaret.Line == vBE.Line))
							vNewCaret.Char -= vBE.Char - vBB.Char;
            // adjust vertical drop position
						if(DropAfter && (vBE.Line > vBB.Line))
							vNewCaret.Line -= vBE.Line - vBB.Line;
					}
				}
        // insert the selected text
				ChangeScrollPastEOL = !(fOptions.Contains(eoScrollPastEol));
				try
				{
					if(ChangeScrollPastEOL)
						fOptions << eoScrollPastEol;
					InternalCaretXY = vNewCaret;
					BlockBegin = vNewCaret;
					SelText = DragDropText; // creates undo action
				}
				__finally
				{
					if(ChangeScrollPastEOL)
						fOptions >> eoScrollPastEol;
				}
				SetCaretAndSelection(CaretXY, vNewCaret, CaretXY);
			}
			__finally
			{
				EndUndoBlock();
			}
		}
		else
		Effect = DROPEFFECT_NONE;
	}
	__finally
	{
		DecPaintLock();
	}
}

void __fastcall TCustomSynEdit::OnCodeFoldingChange(TObject* Sender)
{
	GutterChanged(Sender);
}

TRect __fastcall TCustomSynEdit::GetCollapseMarkRect(int Row, int Line/*# = -1*/)
{
	TRect result = {};
	result = Rect(0, 0, 0, 0);
	if(!UseCodeFolding)
		return result;
	if(Line < 0)
		Line = RowToLine(Row);
	if(!AllFoldRanges->CollapsedFoldStartAtLine(Line))
		return result;

  /* Prepare rect */
	/*# with result do */
	{
		auto& with0 = result;
		with0.Top = (Row - fTopLine) * fTextHeight + 1;
		with0.Bottom = with0.Top + fTextHeight - 2;
	}
	result.Left = fTextOffset + (((TSynEditStringList*) fLines)->ExpandedStringLengths[Line - 1] + 1) * fCharWidth;

  /* Fix rect */
	if(fOptions.Contains(eoShowSpecialChars))
		result.Left += fCharWidth;

  // Deal wwth horizontal Scroll
	result.Left = Max(result.Left, fGutterWidth + fCharWidth);
	result.Right = result.Left + fCharWidth * 3 + 4 * ((int)(fCharWidth / /*div*/ 7));
	return result;
}
//-- CodeFolding

void __fastcall TCustomSynEdit::ShowCaret()
{
	if(!(Options.Contains(eoNoCaret)) && !(fStateFlags.Contains(sfCaretVisible)))
	{
		if(::ShowCaret(Handle))
			fStateFlags << sfCaretVisible;
	}
}

void __fastcall TCustomSynEdit::UpdateCaret()
{
	int CX = 0;
	int CY = 0;
	TRect iClientRect = {};
	TDisplayCoord vCaretDisplay = {};
	TPoint vCaretPix = {};
	TCompositionForm cf = {};
	if((PaintLock != 0) || !(Focused() || fAlwaysShowCaret))
		fStateFlags << sfCaretChanged;
	else
	{
		fStateFlags >> sfCaretChanged;
		vCaretDisplay = DisplayXY;
		if(WordWrap && (vCaretDisplay.Column > CharsInWindow + 1))
			vCaretDisplay.Column = CharsInWindow + 1;
		vCaretPix = RowColumnToPixels(vCaretDisplay);
		CX = vCaretPix.X + fCaretOffset.X;
		CY = vCaretPix.Y + fCaretOffset.Y;
		iClientRect = GetClientRect();
		iClientRect.Left += fGutterWidth;
		if((CX >= iClientRect.Left) && (CX < iClientRect.Right) && (CY >= iClientRect.Top) && (CY < iClientRect.Bottom))
		{
			SetCaretPos(CX, CY);
			ShowCaret();
		}
		else
		{
			SetCaretPos(CX, CY);
			HideCaret();
		}
		cf.dwStyle = (DWORD) CFS_POINT;
		cf.ptCurrentPos = Point(CX, CY);
		ImmSetCompositionWindow(ImmGetContext(Handle), &cf);
	}
}

void __fastcall TCustomSynEdit::UpdateScrollBars()
{
	int nMaxScroll = 0;
	TScrollInfo ScrollInfo = {};
	int iRightChar = 0;
	if(!HandleAllocated() || (PaintLock != 0))
		fStateFlags << sfScrollbarChanged;
	else
	{
		fStateFlags >> sfScrollbarChanged;
		if(FScrollBars != TScrollStyle::ssNone)
		{
			ScrollInfo.cbSize = (UINT) sizeof(ScrollInfo);
			ScrollInfo.fMask = (UINT) SIF_ALL;
			if(!(Options.Contains(eoHideShowScrollbars)))
			{
				ScrollInfo.fMask = ScrollInfo.fMask | SIF_DISABLENOSCROLL;
			}

//      if Visible then SendMessage(Handle, WM_SETREDRAW, 0, 0);
			if((Synedit__31.Contains(FScrollBars)) && !WordWrap)
			{
				nMaxScroll = Max(((TSynEditStringList*) Lines)->LengthOfLongestLine, 1);
				if(nMaxScroll <= MAX_SCROLL)
				{
					ScrollInfo.nMin = 1;
					ScrollInfo.nMax = nMaxScroll;
					ScrollInfo.nPage = (UINT) CharsInWindow;
					ScrollInfo.nPos = LeftChar;
				}
				else
				{
					ScrollInfo.nMin = 0;
					ScrollInfo.nMax = MAX_SCROLL;
					ScrollInfo.nPage = (UINT) MulDiv(MAX_SCROLL, CharsInWindow, nMaxScroll);
					ScrollInfo.nPos = MulDiv(MAX_SCROLL, LeftChar, nMaxScroll);
				}
				ShowScrollBar(Handle, SB_HORZ, !(Options.Contains(eoHideShowScrollbars)) || (ScrollInfo.nMin == 0) || (ScrollInfo.nMax > CharsInWindow));
				SetScrollInfo(Handle, SB_HORZ, &ScrollInfo, true);

        //Now for the arrows
				if((Options.Contains(eoDisableScrollArrows)) || (nMaxScroll <= CharsInWindow))
				{
					iRightChar = LeftChar + CharsInWindow - 1;
					if((LeftChar <= 1) && (iRightChar >= nMaxScroll))
					{
						EnableScrollBar(Handle, (UINT) SB_HORZ, (UINT) ESB_DISABLE_BOTH);
					}
					else
					{
						EnableScrollBar(Handle, (UINT) SB_HORZ, (UINT) ESB_ENABLE_BOTH);
						if(LeftChar <= 1)
							EnableScrollBar(Handle, (UINT) SB_HORZ, (UINT) ESB_DISABLE_LEFT);
						else
						{
							if(iRightChar >= nMaxScroll)
								EnableScrollBar(Handle, (UINT) SB_HORZ, (UINT) ESB_DISABLE_RIGHT);
						}
					}
				}
				else
				EnableScrollBar(Handle, (UINT) SB_HORZ, (UINT) ESB_ENABLE_BOTH);
			}
			else
			ShowScrollBar(Handle, SB_HORZ, false);
			if(Synedit__32.Contains(FScrollBars))
			{
				nMaxScroll = DisplayLineCount;
				if(Options.Contains(eoScrollPastEof))
					nMaxScroll += LinesInWindow - 1;
				if(nMaxScroll <= MAX_SCROLL)
				{
					ScrollInfo.nMin = 1;
					ScrollInfo.nMax = Max(1, nMaxScroll);
					ScrollInfo.nPage = (UINT) LinesInWindow;
					ScrollInfo.nPos = TopLine;
				}
				else
				{
					ScrollInfo.nMin = 0;
					ScrollInfo.nMax = MAX_SCROLL;
					ScrollInfo.nPage = (UINT) MulDiv(MAX_SCROLL, LinesInWindow, nMaxScroll);
					ScrollInfo.nPos = MulDiv(MAX_SCROLL, TopLine, nMaxScroll);
				}
				ShowScrollBar(Handle, SB_VERT, !(Options.Contains(eoHideShowScrollbars)) || (ScrollInfo.nMin == 0) || (ScrollInfo.nMax > LinesInWindow));
				SetScrollInfo(Handle, SB_VERT, &ScrollInfo, true);
				if((Options.Contains(eoDisableScrollArrows)) || (nMaxScroll <= LinesInWindow))
				{
					if((TopLine <= 1) && (nMaxScroll <= LinesInWindow))
					{
						EnableScrollBar(Handle, (UINT) SB_VERT, (UINT) ESB_DISABLE_BOTH);
					}
					else
					{
						EnableScrollBar(Handle, (UINT) SB_VERT, (UINT) ESB_ENABLE_BOTH);
						if(TopLine <= 1)
							EnableScrollBar(Handle, (UINT) SB_VERT, (UINT) ESB_DISABLE_UP);
						else
						{
							if((DisplayLineCount - TopLine - LinesInWindow + 1) == 0)
								EnableScrollBar(Handle, (UINT) SB_VERT, (UINT) ESB_DISABLE_DOWN);
						}
					}
				}
				else
				EnableScrollBar(Handle, (UINT) SB_VERT, (UINT) ESB_ENABLE_BOTH);

//        if Visible then SendMessage(Handle, WM_SETREDRAW, -1, 0);
//        if fPaintLock=0 then
//           Invalidate;
				Update();
			}
			else
			ShowScrollBar(Handle, SB_VERT, false); /*endif fScrollBars <> ssNone*/
		}
		else
		ShowScrollBar(Handle, SB_BOTH, false);
	}
}

bool __fastcall TCustomSynEdit::DoMouseWheel(TShiftState Shift, int WheelDelta, const TPoint& cMousePos)
{
	TPoint MousePos = cMousePos;
	bool result = false;
	const int WHEEL_DIVISOR = 120; // Mouse Wheel standard
	int iWheelClicks = 0;
	int iLinesToScroll = 0;
	result = inherited::DoMouseWheel(Shift, WheelDelta, MousePos);
	if(result)
		return result;
	if(GetKeyState(SYNEDIT_CONTROL) < 0)
		iLinesToScroll = LinesInWindow >> int(fOptions.Contains(eoHalfPageScroll));
	else
		iLinesToScroll = 3;
	fMouseWheelAccumulator += WheelDelta;
	iWheelClicks = (int)(fMouseWheelAccumulator / /*div*/ WHEEL_DIVISOR);
	fMouseWheelAccumulator = fMouseWheelAccumulator % WHEEL_DIVISOR;
	TopLine = TopLine - iWheelClicks * iLinesToScroll;
	Update();
	if(ASSIGNED(OnScroll))
		OnScroll(this, sbVertical);
	result = true;
	return result;
}

void __fastcall TCustomSynEdit::WMCaptureChanged(::TMessage& Msg)
{
	fScrollTimer->Enabled = false;
	inherited::Dispatch(&Msg);  //#inherited method "WMCaptureChanged" not not accessible;
}

void __fastcall TCustomSynEdit::WMClear(::TMessage& Msg)
{
	if(!ReadOnly)
		SelText = L"";
}

void __fastcall TCustomSynEdit::WMCopy(::TMessage& Message)
{
	CopyToClipboard();
	Message.Result = int(true);
}

void __fastcall TCustomSynEdit::WMCut(::TMessage& Message)
{
	if(!ReadOnly)
		CutToClipboard();
	Message.Result = int(true);
}

void __fastcall TCustomSynEdit::WMDropFiles(::TMessage& Msg)
{
	int i = 0;
	int iNumberDropped = 0;
	WideChar FileNameW[260/*# range 0..MAX_PATH-1*/];
	TPoint Point = {};
	TStringList* FilesList = nullptr;
	try
	{
		if(ASSIGNED(fOnDropFiles))
		{
			FilesList = new TStringList();
			try
			{
				int stop = 0;
				iNumberDropped = (int) DragQueryFile(((HDROP) Msg.WParam), ((unsigned int) -1), nullptr, 0);
				DragQueryPoint(((HDROP) Msg.WParam), &Point);
				for(stop = iNumberDropped - 1, i = 0; i <= stop; i++)
				{
					DragQueryFileW(((HDROP) Msg.WParam), (UINT) i, FileNameW, (UINT) ((int)(sizeof(FileNameW) / 2)));
					FilesList->Add(FileNameW);
				}
				fOnDropFiles(this, Point.X, Point.Y, FilesList);
			}
			__finally
			{
				delete FilesList;
			}
		}
	}
	__finally
	{
		Msg.Result = 0;
		DragFinish(((HDROP) Msg.WParam));
	}
}

void __fastcall TCustomSynEdit::WMDestroy(TWMDestroy& Message)
{

  // See https://en.delphipraxis.net/topic/456-destroywnd-not-called-at-destruction-of-wincontrols/
	if((fOptions.Contains(eoDropFiles)) && !(ComponentState.Contains(csDesigning)))
		DragAcceptFiles(Handle, false);
	RevokeDragDrop(Handle);
	inherited::Dispatch(&Message);  //#inherited method "WMDestroy" not not accessible;
}

void __fastcall TCustomSynEdit::WMEraseBkgnd(::TMessage& Msg)
{
	Msg.Result = 1;
}

void __fastcall TCustomSynEdit::WMGetDlgCode(TWMGetDlgCode& Msg)
{
	inherited::Dispatch(&Msg);  //#inherited method "WMGetDlgCode" not not accessible;
	Msg.Result = Msg.Result | DLGC_WANTARROWS | DLGC_WANTCHARS;
	if(fWantTabs)
		Msg.Result = Msg.Result | DLGC_WANTTAB;
	if(fWantReturns)
		Msg.Result = Msg.Result | DLGC_WANTALLKEYS;
}

void __fastcall TCustomSynEdit::WMGetText(TWMGetText& Msg)
{
	Msg.Result = (LRESULT) StrLen(StrLCopy(Msg.Text, ustr2pwchar(Text), Msg.TextMax - 1));
}

void __fastcall TCustomSynEdit::WMGetTextLength(TWMGetTextLength& Msg)
{

  // Avoid (useless) temporary copy of WindowText while window is recreated
  // because of docking.
	if(ControlState.Contains(csDocking))
		Msg.Result = 0;
	else
		Msg.Result = Text.Length();
}

void __fastcall TCustomSynEdit::WMHScroll(TWMScroll& Msg)
{
	int iMaxWidth = 0;
	Msg.Result = 0;
	switch(Msg.ScrollCode)
	{
		case SB_LEFT:
      // Scrolls to start / end of the line
		LeftChar = 1;
		break;
      // Simply set LeftChar property to the LengthOfLongestLine,
      // it would do the range checking and constrain the value if necessary
		case SB_RIGHT:
		LeftChar = ((TSynEditStringList*) Lines)->LengthOfLongestLine;
		break;
      // Scrolls one char left / right
		case SB_LINERIGHT:
		LeftChar = LeftChar + 1;
		break;
		case SB_LINELEFT:
		LeftChar = LeftChar - 1;
		break;
      // Scrolls one page of chars left / right
		case SB_PAGERIGHT:
		LeftChar = LeftChar + (fCharsInWindow - int(fOptions.Contains(eoScrollByOneLess)));
		break;
		case SB_PAGELEFT:
		LeftChar = LeftChar - (fCharsInWindow - int(fOptions.Contains(eoScrollByOneLess)));
		break;
      // Scrolls to the current scroll bar position
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
		{
			FIsScrolling = true;
			iMaxWidth = Max(((TSynEditStringList*) Lines)->LengthOfLongestLine, 1);
			if(iMaxWidth > MAX_SCROLL)
				LeftChar = MulDiv(iMaxWidth, Msg.Pos, MAX_SCROLL);
			else
				LeftChar = Msg.Pos;
		}
		break;
		case SB_ENDSCROLL:
		FIsScrolling = false;
		break;
		default:
		  ;
		break;
	}
	if(ASSIGNED(OnScroll))
		OnScroll(this, sbHorizontal);
}

void __fastcall TCustomSynEdit::WMImeChar(::TMessage& Msg)
{

  // do nothing here, the IME string is retrieved in WMImeComposition

  // Handling the WM_IME_CHAR message stops Windows from sending WM_CHAR
  // messages while using the IME
}

void __fastcall TCustomSynEdit::WMImeComposition(::TMessage& Msg)
{
	HIMC imc = 0;
	PWideChar PW = nullptr;
	int ImeCount = 0;
	if((Msg.LParam & GCS_RESULTSTR) != 0)
	{
		imc = ImmGetContext(Handle);
		try
		{
			ImeCount = ImmGetCompositionStringW(imc, (DWORD) GCS_RESULTSTR, nullptr, 0);
      // ImeCount is always the size in bytes, also for Unicode
			PW = (PWideChar) GetMemory(ImeCount + sizeof(WideChar));
			try
			{
				ImmGetCompositionStringW(imc, (DWORD) GCS_RESULTSTR, PW, (DWORD) ImeCount);
				PW[(unsigned __int64)(ImeCount / /*div*/ sizeof(WideChar))] = L'\x00';
				CommandProcessor((TSynEditorCommand) ecImeStr, L'\x00', PW);
			}
			__finally
			{
				FreeMemory(PW);
			}
		}
		__finally
		{
			ImmReleaseContext(Handle, imc);
		}
	}
	inherited::Dispatch(&Msg);  //#inherited method "WMImeComposition" not not accessible;
}

void __fastcall TCustomSynEdit::WMImeNotify(::TMessage& Msg)
{
	HIMC imc = 0;
	TLogFontW LogFontW = {};
	/*# with Msg do */
	{
		auto& with0 = Msg;
		switch(with0.WParam)
		{
			case IMN_SETOPENSTATUS:
			{
				imc = ImmGetContext(Handle);
				if(imc != 0)
				{
					GetObjectW(Font->Handle, (int) sizeof(TLogFontW), &LogFontW);
					ImmSetCompositionFontW(imc, &LogFontW);
					ImmReleaseContext(Handle, imc);
				}
			}
			break;
			default:
			  ;
			break;
		}
	}
	inherited::Dispatch(&Msg);  //#inherited method "WMImeNotify" not not accessible;
}

void __fastcall TCustomSynEdit::WMKillFocus(TWMKillFocus& Msg)
{
	inherited::Dispatch(&Msg);  //#inherited method "WMKillFocus" not not accessible;
	CommandProcessor((TSynEditorCommand) ecLostFocus, L'\x00', nullptr);
  //Added check for focused to prevent caret disappearing problem
	if(Focused() || fAlwaysShowCaret)
		return;
	HideCaret();
	::DestroyCaret();
	if(fHideSelection && SelAvail)
		InvalidateSelection();
}

void __fastcall TCustomSynEdit::WMPaste(::TMessage& Message)
{
	if(!ReadOnly)
		PasteFromClipboard();
	Message.Result = int(true);
}

void __fastcall TCustomSynEdit::WMCancelMode(::TMessage& Message)
{
}

void __fastcall TCustomSynEdit::WMSetFocus(TWMSetFocus& Msg)
{
	CommandProcessor((TSynEditorCommand) ecGotFocus, L'\x00', nullptr);
	InitializeCaret();
	if(fHideSelection && SelAvail)
		InvalidateSelection();
}

void __fastcall TCustomSynEdit::WMSetText(TWMSetText& Msg)
{
	Msg.Result = 1;
	Text = Msg.Text;
}

void __fastcall TCustomSynEdit::WMSize(TWMSize& Msg)
{
	inherited::Dispatch(&Msg);  //#inherited method "WMSize" not not accessible;
	SizeOrFontChanged(false);
}

void __fastcall TCustomSynEdit::WMUndo(::TMessage& Msg)
{
	Undo();
}
THintWindow* ScrollHintWnd = nullptr;

THintWindow* __fastcall GetScrollHint()
{
	THintWindow* result = nullptr;
	if(ScrollHintWnd == nullptr)
		ScrollHintWnd = (THintWindow*) new THintWindow(Application);
	result = ScrollHintWnd;
	return result;
}

void __fastcall TCustomSynEdit::WMVScroll(TWMScroll& Msg)
{
	String s;
	TRect rc = {};
	TPoint pt = {};
	THintWindow* ScrollHint = nullptr;
	int ButtonH = 0;
	TScrollInfo ScrollInfo = {};
	Msg.Result = 0;
	switch(Msg.ScrollCode)
	{
		case SB_TOP:
      // Scrolls to start / end of the text
		TopLine = 1;
		break;
		case SB_BOTTOM:
		TopLine = DisplayLineCount;
		break;
      // Scrolls one line up / down
		case SB_LINEDOWN:
		TopLine = TopLine + 1;
		break;
		case SB_LINEUP:
		TopLine = TopLine - 1;
		break;
      // Scrolls one page of lines up / down
		case SB_PAGEDOWN:
		TopLine = TopLine + (fLinesInWindow - int(fOptions.Contains(eoScrollByOneLess)));
		break;
		case SB_PAGEUP:
		TopLine = TopLine - (fLinesInWindow - int(fOptions.Contains(eoScrollByOneLess)));
		break;
      // Scrolls to the current scroll bar position
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
		{
			FIsScrolling = true;
			if(DisplayLineCount > MAX_SCROLL)
				TopLine = MulDiv(LinesInWindow + DisplayLineCount - 1, Msg.Pos, MAX_SCROLL);
			else
				TopLine = Msg.Pos;
			if(fOptions.Contains(eoShowScrollHint))
			{
				ScrollHint = GetScrollHint();
				ScrollHint->Color = fScrollHintColor;
				switch(fScrollHintFormat)
				{
					case shfTopLineOnly:
					s = Format(SYNS_ScrollInfoFmtTop, ARRAYOFCONST((RowToLine(TopLine))));
					break;
					default:
					s = Format(SYNS_ScrollInfoFmt, ARRAYOFCONST((RowToLine(TopLine), RowToLine(TopLine + Min(LinesInWindow, DisplayLineCount - TopLine)))));
					break;
				}
				rc = ScrollHint->CalcHintRect(200, s, nullptr);
				if(fOptions.Contains(eoScrollHintFollows))
				{
					ButtonH = GetSystemMetrics(SM_CYVSCROLL);
					FillChar((void**)&ScrollInfo, (int) sizeof(ScrollInfo), 0);
					ScrollInfo.cbSize = (UINT) sizeof(ScrollInfo);
					ScrollInfo.fMask = (UINT) SIF_ALL;
					GetScrollInfo(Handle, SB_VERT, &ScrollInfo);                                    //half the size of the hint window
                  //The percentage of the page that has been scrolled
                             //The height minus the arrow buttons
					pt = ClientToScreen(Point(ClientWidth - rc.Right - 4, ((rc.Bottom - rc.Top) >> 1) + Round((double(ScrollInfo.nTrackPos) / ScrollInfo.nMax) * (ClientHeight - (ButtonH * 2))) + ButtonH));                                                 //The height of the top button
				}
				else
				pt = ClientToScreen(Point(ClientWidth - rc.Right - 4, 10));
				OffsetRect(rc, pt.X, pt.Y);
				ScrollHint->ActivateHint(rc, s);
				ScrollHint->Update();
			}
		}
		break;
      // Ends scrolling
		case SB_ENDSCROLL:
		{
			FIsScrolling = false;
			if(fOptions.Contains(eoShowScrollHint))
				ShowWindow(GetScrollHint()->Handle, SW_HIDE);
		}
		break;
		default:
		  ;
		break;
	}
	Update();
	if(ASSIGNED(OnScroll))
		OnScroll(this, sbVertical);
}

int __fastcall TCustomSynEdit::ScanFrom(int Index)
{
	int result = 0;
	TSynEditRange iRange = nullptr;
	result = Index;
	if(result >= Lines->Count)
		return result;
	if(result == 0)
		fHighlighter->ResetRange();
	else
		fHighlighter->SetRange(((TSynEditStringList*) Lines)->Ranges[result - 1]);
	do
	{
		fHighlighter->SetLine(Lines->Strings[result], result);
		fHighlighter->NextToEol();
		iRange = fHighlighter->GetRange();
		if(((TSynEditStringList*) Lines)->Ranges[result] == iRange)
			return result; // avoid the final Decrement
		((TSynEditStringList*) Lines)->Ranges[result] = iRange;
		++result;
	}
	while(!(result == Lines->Count));
	--result;
	return result;
}

void __fastcall TCustomSynEdit::ListCleared(TObject* Sender)
{
	if(WordWrap)
		fWordWrapPlugin->Reset();

//++ CodeFolding
	if(UseCodeFolding)
		AllFoldRanges->Reset();
//-- CodeFolding
	ClearUndo();
  // invalidate the *whole* client area
	FillChar((void**)&fInvalidateRect, (int) sizeof(TRect), 0);
	Invalidate();
  // set caret and selected block to start of text
	CaretXY = BufferCoord(1, 1);
  // scroll to start of text
	TopLine = 1;
	LeftChar = 1;
	fStatusChanges << scAll;
}

void __fastcall TCustomSynEdit::ListBeforeDeleted(TObject* Sender, int aIndex, int aCount)
{
	DoLinesBeforeDeleted(aIndex, aCount);
}
//++ CodeFolding

void __fastcall TCustomSynEdit::ListDeleted(TObject* Sender, int aIndex, int aCount)
{
	int vLastScan = 0;
	if(WordWrap)
		fWordWrapPlugin->LinesDeleted(aIndex, aCount);
	DoLinesDeleted(aIndex, aCount);
	vLastScan = aIndex;
	if(ASSIGNED(fHighlighter) && (Lines->Count > 0))
		vLastScan = ScanFrom(aIndex);
	if(UseCodeFolding)
	{
		AllFoldRanges->LinesDeleted(aIndex, aCount);
    // Scan the same lines the highlighter has scanned
		ReScanForFoldRanges(aIndex, vLastScan);
		InvalidateGutter();
	}
//-- CodeFolding
	InvalidateLines(aIndex + 1, MaxInt);
	InvalidateGutterLines(aIndex + 1, MaxInt);
//++ Flicker Reduction
	fStateFlags << sfScrollbarChanged;
//-- Flicker Reduction
}

void __fastcall TCustomSynEdit::ListInserted(TObject* Sender, int Index, int aCount)
{
	int vLastScan = 0;
//++ CodeFolding
	int FoldIndex = 0;
	if(WordWrap)
		fWordWrapPlugin->LinesInserted(Index, aCount);
	DoLinesInserted(Index, aCount);
	vLastScan = Index;
//-- CodeFolding
	if(ASSIGNED(fHighlighter) && (Lines->Count > 0))
	{
		do
		{
			vLastScan = ScanFrom(vLastScan);
			++vLastScan;
		}
		while(!(vLastScan >= Index + aCount));
	}

//++ CodeFolding
	if(UseCodeFolding)
	{
		if(fAllFoldRanges->CollapsedFoldStartAtLine(Index, FoldIndex))
      // insertion starts at collapsed fold
			Uncollapse(FoldIndex);
		AllFoldRanges->LinesInserted(Index, aCount);
    // Scan the same lines the highlighter has scanned
		ReScanForFoldRanges(Index, vLastScan - 1);
	}
//-- CodeFolding
	InvalidateLines(Index + 1, MaxInt);
	InvalidateGutterLines(Index + 1, MaxInt);
//++ Flicker Reduction
	fStateFlags << sfScrollbarChanged;
//-- Flicker Reduction
}

void __fastcall TCustomSynEdit::ListPut(TObject* Sender, int Index, const String OldLine)
{
	int vEndLine = 0;
//++ CodeFolding
	int vLastScan = 0;
	int FoldIndex = 0;
//-- CodeFolding
	DoLinePut(Index, OldLine);
	vEndLine = Index + 1;
	if(WordWrap)
	{
		if(fWordWrapPlugin->LinePut(Index, OldLine) != 0)
			vEndLine = MaxInt;
		InvalidateGutterLines(Index + 1, vEndLine);
	}
//++ CodeFolding
	vLastScan = Index;
	if(ASSIGNED(fHighlighter))
	{
		vLastScan = ScanFrom(Index);
		vEndLine = Max(vEndLine, vLastScan + 1);
//-- CodeFolding
    // If this editor is chained then the real owner of text buffer will probably
    // have already parsed the changes, so ScanFrom will return immediately.
		if(fLines != fOrigLines)
			vEndLine = MaxInt;
	}

//++ CodeFolding
	if(fUseCodeFolding)
	{
		if(fAllFoldRanges->CollapsedFoldStartAtLine(Index + 1, FoldIndex))
      // modification happens at collapsed fold
			Uncollapse(FoldIndex);
		AllFoldRanges->LinePut(Index, OldLine);
    // Scan the same lines the highlighter has scanned
		ReScanForFoldRanges(Index, vLastScan);
	}
//-- CodeFolding
	InvalidateLines(Index + 1, vEndLine);
	InvalidateGutterLines(Index + 1, vEndLine);
//++ Flicker Reduction
	fStateFlags << sfScrollbarChanged;
//-- Flicker Reduction
}

void __fastcall TCustomSynEdit::ScanRanges()
{
	int i = 0;
	if(ASSIGNED(fHighlighter) && (Lines->Count > 0))
	{
		fHighlighter->ResetRange();
		i = 0;
		do
		{
			fHighlighter->SetLine(Lines->Strings[i], i);
			fHighlighter->NextToEol();
			((TSynEditStringList*) Lines)->Ranges[i] = fHighlighter->GetRange();
			++i;
		}
		while(!(i >= Lines->Count));
	}
}

void __fastcall TCustomSynEdit::SetWordBlock(const TBufferCoord& cValue)
{
	TBufferCoord Value = cValue;
	TBufferCoord vBlockBegin = {};
	TBufferCoord vBlockEnd = {};
	String TempString;

	auto CharScan = [&]() -> void 
	{
		int cRun = 0;
    /* search BlockEnd */
		int stop = 0;
		vBlockEnd.Char = TempString.Length();
		for(stop = TempString.Length(), cRun = Value.Char; cRun <= stop; cRun++)
		{
			if(!IsIdentChar(TempString[cRun]))
			{
				vBlockEnd.Char = cRun;
				break;
			}
		}
    /* search BlockBegin */
		vBlockBegin.Char = 1;
		for(stop = 1, cRun = Value.Char - 1; cRun >= stop; cRun--)
		{
			if(!IsIdentChar(TempString[cRun]))
			{
				vBlockBegin.Char = cRun + 1;
				break;
			}
		}
	};
	Value.Char = Max(Value.Char, 1);
	Value.Line = MinMax(Value.Line, 1, Lines->Count);
	TempString = Lines->Strings[Value.Line - 1] + L"\x00"; //needed for CaretX = LineLength + 1
	if(Value.Char > TempString.Length())
	{
		InternalCaretXY = BufferCoord(TempString.Length(), Value.Line);
		return;
	}
	CharScan();
	vBlockBegin.Line = Value.Line;
	vBlockEnd.Line = Value.Line;
	SetCaretAndSelection(vBlockEnd, vBlockBegin, vBlockEnd);
	InvalidateLine(Value.Line);
}

void __fastcall TCustomSynEdit::DblClick()
{
	TPoint ptMouse = {};
	GetCursorPos(&ptMouse);
	ptMouse = ScreenToClient(ptMouse);
	if(ptMouse.X >= fGutterWidth + fTextMargin)
	{
		if(!(fOptions.Contains(eoNoSelection)))
			SetWordBlock(CaretXY);
		inherited::DblClick();
	}
	else
	inherited::DblClick();
}

bool __fastcall TCustomSynEdit::GetCanUndo()
{
	bool result = false;
	result = !ReadOnly && fUndoRedo->CanUndo;
	return result;
}

bool __fastcall TCustomSynEdit::GetCanRedo()
{
	bool result = false;
	result = !ReadOnly && fUndoRedo->CanRedo;
	return result;
}

bool __fastcall TCustomSynEdit::GetCanPaste()
{
	bool result = false;
	result = !ReadOnly && ClipboardProvidesText();
	return result;
}

void __fastcall TCustomSynEdit::Redo()
{
	if(ReadOnly)
		return;
	DoOnPaintTransientEx(ttBefore, true);
	IncPaintLock();
	Lines->BeginUpdate();
	try
	{
		fUndoRedo->Redo(this);
	}
	__finally
	{
		Lines->EndUpdate();
		DecPaintLock();
		DoOnPaintTransientEx(ttAfter, true);
	}
}

//++ CodeFolding

void __fastcall TCustomSynEdit::Collapse(int FoldRangeIndex, bool Invalidate/*# = true*/)
{
	AllFoldRanges->Ranges->List[FoldRangeIndex].Collapsed = true;
	/*# with AllFoldRanges.Ranges[FoldRangeIndex] do */
	{
		
    // Extract caret from fold
		if((fCaretY > AllFoldRanges->Ranges->Items[FoldRangeIndex].FromLine) && (fCaretY <= AllFoldRanges->Ranges->Items[FoldRangeIndex].ToLine))
			CaretXY = BufferCoord(Lines->Strings[AllFoldRanges->Ranges->Items[FoldRangeIndex].FromLine - 1].Length() + 1, AllFoldRanges->Ranges->Items[FoldRangeIndex].FromLine);
		if(Invalidate)
      // Redraw the collapsed line and below
		{
			InvalidateLines(AllFoldRanges->Ranges->Items[FoldRangeIndex].FromLine, MaxInt);

      // Redraw fold mark
			InvalidateGutterLines(AllFoldRanges->Ranges->Items[FoldRangeIndex].FromLine, MaxInt);
			UpdateScrollBars();
		}
		else

      // Update Scrollbars
		fStateFlags << sfScrollbarChanged;
	}
}

void __fastcall TCustomSynEdit::CollapseAll()
{
	int i = 0;
	int stop = 0;
	if(!fUseCodeFolding)
		return;
	for(stop = 0, i = fAllFoldRanges->Count - 1; i >= stop; i--)
	{
		Collapse(i, false);
	}
	InvalidateLines(-1, -1);
	InvalidateGutterLines(-1, -1);
	EnsureCursorPosVisible();
}

void __fastcall TCustomSynEdit::CollapseLevel(int Level)
{
	int i = 0;
	TArray<int> RangeIndices;
	int stop = 0;
	if(!fUseCodeFolding)
		return;
	RangeIndices = AllFoldRanges->FoldsAtLevel(Level);
	for(stop = RangeIndices.High, i = RangeIndices.Low; i <= stop; i++)
	{
		Collapse(RangeIndices[i], false);
	}
	InvalidateLines(-1, -1);
	InvalidateGutterLines(-1, -1);
	EnsureCursorPosVisible();
}

void __fastcall TCustomSynEdit::CollapseNearest()
{
	int Index = 0;
	if(!fUseCodeFolding)
		return;
	if(AllFoldRanges->FoldAroundLineEx(CaretY, false, true, true, Index))
		Collapse(Index);
	EnsureCursorPosVisible();
}

void __fastcall TCustomSynEdit::CollapseFoldType(int FoldType)
{
	int i = 0;
	TArray<int> RangeIndices;
	int stop = 0;
	if(!fUseCodeFolding)
		return;
	RangeIndices = AllFoldRanges->FoldsOfType(FoldType);
	for(stop = RangeIndices.High, i = RangeIndices.Low; i <= stop; i++)
	{
		Collapse(RangeIndices[i], false);
	}
	InvalidateLines(-1, -1);
	InvalidateGutterLines(-1, -1);
	EnsureCursorPosVisible();
}

void __fastcall TCustomSynEdit::Uncollapse(int FoldRangeIndex, bool Invalidate/*# = true*/)
{
	AllFoldRanges->Ranges->List[FoldRangeIndex].Collapsed = false;
	if(Invalidate)
		/*# with AllFoldRanges.Ranges[FoldRangeIndex] do */
		{
			
    // Redraw the uncollapsed line and below
			InvalidateLines(AllFoldRanges->Ranges->Items[FoldRangeIndex].FromLine, MaxInt);

    // Redraw fold marks
			InvalidateGutterLines(AllFoldRanges->Ranges->Items[FoldRangeIndex].FromLine, MaxInt);

    // Make sure we can see the cursor
    // EnsureCursorPosVisible;
			UpdateScrollBars();
		}
	else

    // Update Scrollbars
		fStateFlags << sfScrollbarChanged;
}

void __fastcall TCustomSynEdit::UncollapseAroundLine(int Line)
{
	int Index = 0;
	if(!fUseCodeFolding)
		return;
  // Open up the closed folds around the focused line until we can see the line we're looking for
	while(AllFoldRanges->FoldHidesLine(Line, Index))
		Uncollapse(Index);
}

void __fastcall TCustomSynEdit::UnCollapseLevel(int Level)
{
	int i = 0;
	TArray<int> RangeIndices;
	int stop = 0;
	if(!fUseCodeFolding)
		return;
	RangeIndices = AllFoldRanges->FoldsAtLevel(Level);
	for(stop = RangeIndices.High, i = RangeIndices.Low; i <= stop; i++)
	{
		Uncollapse(RangeIndices[i], false);
	}
	InvalidateLines(-1, -1);
	InvalidateGutterLines(-1, -1);
	EnsureCursorPosVisible();
}

void __fastcall TCustomSynEdit::UncollapseNearest()
{
	int Index = 0;
	if(!fUseCodeFolding)
		return;
	if(AllFoldRanges->CollapsedFoldStartAtLine(CaretY, Index))
		Uncollapse(Index);
	EnsureCursorPosVisible();
}

void __fastcall TCustomSynEdit::UnCollapseFoldType(int FoldType)
{
	int i = 0;
	TArray<int> RangeIndices;
	int stop = 0;
	if(!fUseCodeFolding)
		return;
	RangeIndices = AllFoldRanges->FoldsOfType(FoldType);
	for(stop = RangeIndices.High, i = RangeIndices.Low; i <= stop; i++)
	{
		Uncollapse(RangeIndices[i], false);
	}
	InvalidateLines(-1, -1);
	InvalidateGutterLines(-1, -1);
	EnsureCursorPosVisible();
}
/* Select whole lines */

void __fastcall TCustomSynEdit::DoMouseSelectLineRange(const TBufferCoord& cNewPos)
{
	TBufferCoord NewPos = cNewPos;
	TBufferCoord BB = {};
	TBufferCoord BE = {};
	BB = BlockBegin;
	BE = BlockEnd;
  //  Set AnchorLine
	if(CaretXY >= BE)
	{
		if(BB.Line < Lines->Count)
			BE = BufferCoord(1, BB.Line + 1);
		else
			BE = BufferCoord(Lines->Strings[BB.Line - 1].Length(), BB.Line);
	}
	else
	{
		BB = BufferCoord(1, Max(1, IfThen(BE.Line < Lines->Count, BE.Line - 1, BE.Line)));
	}
	if(NewPos.Line < BB.Line)
	{
		BB = BufferCoord(1, NewPos.Line);
		NewPos = BB;
	}
	else
	{
		if(NewPos.Line >= BE.Line)
		{
			if(NewPos.Line < Lines->Count)
				BE = BufferCoord(1, NewPos.Line + 1);
			else
				BE = BufferCoord(Lines->Strings[NewPos.Line - 1].Length(), NewPos.Line);
			NewPos = BE;
		}
		else
		NewPos = BE;
	}
	InternalCaretXY = NewPos;
	if(BB != fBlockBegin)
		BlockBegin = BB;
	if(BE != fBlockEnd)
		BlockEnd = BE;
}
/* Select whole words */

void __fastcall TCustomSynEdit::DoMouseSelectWordRange(const TBufferCoord& cNewPos)
{
	TBufferCoord NewPos = cNewPos;
	TBufferCoord BB = {};
	TBufferCoord BE = {};
  //  Set Anchor Selection (Word)
	BB = BlockBegin;
	BE = BlockEnd;
	if(CaretXY > BB)
		BE = WordEndEx(BB);
	else
		BB = WordStartEx(BE);
	NewPos.Char = Min(NewPos.Char, Lines->Strings[NewPos.Line - 1].Length() + 1);
	if(NewPos > BE)
	{
		BE = NewPos;
		if((BE.Char > 1) && IsIdentChar(((String)Lines->Strings[BE.Line - 1])[BE.Char - 1]))
			BE = WordEndEx(BE);
	}
	else
	{
		if(NewPos < BB)
		{
			BB = BE;
			BE = NewPos;
			if((BE.Char < Lines->Strings[BE.Line - 1].Length()) && IsIdentChar(((String)Lines->Strings[BE.Line - 1])[BE.Char]))
				BE = WordStartEx(BE);
		}
	}
	if(BB != fBlockBegin)
		BlockBegin = BB;
	if(BE != fBlockEnd)
		BlockEnd = BE;
	InternalCaretXY = fBlockEnd;
}

void __fastcall TCustomSynEdit::ExecCmdCopyOrMoveLine(TSynEditorCommand Command)
{
	int vCaretRow = 0;
	int SelShift = 0;
	TBufferCoord Caret = {};
	TBufferCoord BB = {};
	TBufferCoord BE = {};
	TBufferCoord StartOfBlock = {};
	TBufferCoord EndOfBlock = {};
	String Text;
	TSynSelectionMode OldSelectionMode = smNormal;
	if(!ReadOnly && ((Command != ecMoveLineUp) || (BlockBegin.Line > 1)) && ((Command != ecMoveLineDown) || (BlockEnd.Line < Lines->Count)))
    // Get Caret and selection
	{
		int stop = 0;
		Caret = CaretXY;
		StartOfBlock = fBlockBegin;
		EndOfBlock = fBlockEnd;
		SelShift = Succ(Abs(fBlockEnd.Line - fBlockBegin.Line));

     //BB and BE define where insertion of Text will take place
    // SelShift is the number lines the Selection is shifted up or down
		switch(Command)
		{
			case ecCopyLineUp:
			{
				BB = BufferCoord(1, BlockBegin.Line);
				BE = BB;
				SelShift = 0;
			}
			break;
			case ecMoveLineUp:
			{
				BB = BufferCoord(1, Pred(BlockBegin.Line));
				if((fBlockBegin.Line != fBlockEnd.Line) && (BlockEnd.Char == 1))
					BE = BufferCoord(Succ(Lines->Strings[BlockEnd.Line - 2].Length()), BlockEnd.Line - 1);
				else
					BE = BufferCoord(Succ(Lines->Strings[BlockEnd.Line - 1].Length()), BlockEnd.Line);
				SelShift = -1;
			}
			break;
			case ecCopyLineDown:
			{
				if((fBlockBegin.Line != fBlockEnd.Line) && (BlockEnd.Char == 1))
				{
					BE = BufferCoord(Succ(Lines->Strings[BlockEnd.Line - 2].Length()), BlockEnd.Line - 1);
					--SelShift;
				}
				else
				BE = BufferCoord(Succ(Lines->Strings[BlockEnd.Line - 1].Length()), BlockEnd.Line);
				BB = BE;
			}
			break;
			case ecMoveLineDown:
			{
				BB = BufferCoord(1, BlockBegin.Line);
				if((fBlockBegin.Line != fBlockEnd.Line) && (BlockEnd.Char == 1))
					BE = BufferCoord(Succ(Lines->Strings[BlockEnd.Line - 1].Length()), BlockEnd.Line);
				else
					BE = BufferCoord(Succ(Lines->Strings[BlockEnd.Line].Length()), BlockEnd.Line + 1);
				SelShift = 1;
			}
			break;
			default:
			return;
			break;
		}
    // store the lines into Text
		Text = L"";
		for(stop = BlockEnd.Line, vCaretRow = BlockBegin.Line; vCaretRow <= stop; vCaretRow++)
		{
			if((vCaretRow == BlockEnd.Line) && (fBlockBegin.Line != fBlockEnd.Line) && (BlockEnd.Char == 1))
				break;
			if((Command == ecCopyLineDown) || (Command == ecMoveLineDown))
				Text = Text + sLineBreak + Lines->Strings[vCaretRow - 1];
			else
				Text = Text + Lines->Strings[vCaretRow - 1] + sLineBreak;
		}
    // Add the line over which we move
		if(Command == ecMoveLineDown)
			Text = Lines->Strings[BE.Line - 1] + Text;
		else
		{
			if(Command == ecMoveLineUp)
				Text = Text + Lines->Strings[BB.Line - 1];

    // Deal with Selection modes
		}
		OldSelectionMode = ActiveSelectionMode;
		ActiveSelectionMode = smNormal;
    // group undo redo actions and reduce transient painting
		DoOnPaintTransientEx(ttBefore, true);
		BeginUndoBlock();
		try

      // Insert/replace text at selection BB-BE
		{
			SetCaretAndSelection(BB, BB, BE);
			SetSelText(Text);

      // Set as new selection the shifted old one
			if(SelShift != 0)
			{
				Caret.Line += SelShift;
				StartOfBlock.Line += SelShift;
				EndOfBlock.Line += SelShift;
			}
			SetCaretAndSelection(Caret, StartOfBlock, EndOfBlock);
		}
		__finally
		{
			EndUndoBlock();
			DoOnPaintTransientEx(ttAfter, true);
		}
    // Restore Selection mode
		ActiveSelectionMode = OldSelectionMode;
	}
}

void __fastcall TCustomSynEdit::ExecCmdDeleteLine()
{
	TSynSelectionMode OldSelectionMode = smNormal;
	if(!ReadOnly && (Lines->Count > 0) && !((BlockBegin.Line == Lines->Count) && (Lines->Strings[BlockBegin.Line - 1].Length() == 0)))
	{
		DoOnPaintTransient(ttBefore);
    // Deal with Selection modes
		OldSelectionMode = ActiveSelectionMode;
		ActiveSelectionMode = smNormal;
		BeginUndoBlock();
		try

      // Nomalize selection
		{
			if(fBlockBegin > fBlockEnd)
				SetCaretAndSelection(BlockBegin, BlockBegin, BlockEnd);
			fBlockBegin.Char = 1;
			if((fBlockBegin.Line == fBlockEnd.Line) || (fBlockEnd.Char > 1))
			{
				if(fBlockEnd.Line == Lines->Count)
					fBlockEnd.Char = Lines->Strings[fBlockEnd.Line - 1].Length() + 1;
				else
					fBlockEnd = BufferCoord(1, Succ(fBlockEnd.Line));
			}
			SetSelText(L"");
			SetCaretAndSelection(fBlockBegin, fBlockBegin, fBlockBegin);
		}
		__finally
		{
			EndUndoBlock();
      // Restore Selection mode
			ActiveSelectionMode = OldSelectionMode;
		}
	}
}

void __fastcall TCustomSynEdit::UncollapseAll()
{
	int i = 0;
	int stop = 0;
	if(!fUseCodeFolding)
		return;
	for(stop = 0, i = fAllFoldRanges->Count - 1; i >= stop; i--)
	{
		Uncollapse(i, false);
	}
	InvalidateLines(-1, -1);
	InvalidateGutterLines(-1, -1);
	EnsureCursorPosVisible();
}

//-- CodeFolding

void __fastcall TCustomSynEdit::Undo()
{
	if(ReadOnly)
		return;
	DoOnPaintTransientEx(ttBefore, true);
	IncPaintLock();
	Lines->BeginUpdate();
	try
	{
		fUndoRedo->Undo(this);
	}
	__finally
	{
		Lines->EndUpdate();
		DecPaintLock();
		DoOnPaintTransientEx(ttAfter, true);
	}
}

void __fastcall TCustomSynEdit::ClearBookMark(int BookMark)
{
	if((Synedit__33.Contains(BookMark)) && ASSIGNED(fBookMarks[BookMark]))
	{
		DoOnClearBookmark(fBookMarks[BookMark]);
		fMarkList->Remove(fBookMarks[BookMark]);
		fBookMarks[BookMark] = nullptr;
	}
}

void __fastcall TCustomSynEdit::GotoBookMark(int BookMark)
{
	TBufferCoord iNewPos = {};
	if((Synedit__34.Contains(BookMark)) && ASSIGNED(fBookMarks[BookMark]) && (fBookMarks[BookMark]->Line <= fLines->Count))
	{
		iNewPos.Char = fBookMarks[BookMark]->Char;
		iNewPos.Line = fBookMarks[BookMark]->Line;
    //call it this way instead to make sure that the caret ends up in the middle
    //if it is off screen (like Delphi does with bookmarks)
		SetCaretXYEx(false, iNewPos);
		EnsureCursorPosVisibleEx(true);
		if(SelAvail)
			InvalidateSelection();
		fBlockBegin.Char = fCaretX;
		fBlockBegin.Line = fCaretY;
		fBlockEnd = fBlockBegin;
	}
}

void __fastcall TCustomSynEdit::GotoLineAndCenter(int ALine)
{
	SetCaretXYEx(false, BufferCoord(1, ALine));
	if(SelAvail)
		InvalidateSelection();
	fBlockBegin.Char = fCaretX;
	fBlockBegin.Line = fCaretY;
	fBlockEnd = fBlockBegin;
	EnsureCursorPosVisibleEx(true);
}

void __fastcall TCustomSynEdit::SetBookMark(int BookMark, int X, int Y)
{
	TSynEditMark* mark = nullptr;
	if((Synedit__35.Contains(BookMark)) && (Y >= 1) && (Y <= Max(1, fLines->Count)))
	{
		mark = new TSynEditMark(this);
		/*# with mark do */
		{
			auto with0 = mark;
			with0->Line = Y;
			with0->Char = X;
			with0->ImageIndex = BookMark;
			with0->BookmarkNumber = BookMark;
			with0->Visible = true;
			with0->InternalImage = (fBookMarkOpt->BookmarkImages == nullptr);
		}
		DoOnPlaceMark(mark);
		if(mark != nullptr)
		{
			if(ASSIGNED(fBookMarks[BookMark]))
				ClearBookMark(BookMark);
			fBookMarks[BookMark] = mark;
			fMarkList->Add(fBookMarks[BookMark]);
		}
	}
}

void __fastcall TCustomSynEdit::WndProc(::TMessage& Msg)
{
	const int ALT_KEY_DOWN = 0x20000000;
  // Prevent Alt-Backspace from beeping
	if((Msg.Msg == WM_SYSCHAR) && (Msg.WParam == VK_BACK) && ((Msg.LParam & ALT_KEY_DOWN) != 0))
		Msg.Msg = 0;
	inherited::WndProc(Msg);
}

void __fastcall TCustomSynEdit::ChainListCleared(TObject* Sender)
{
	if(ASSIGNED(fChainListCleared))
		fChainListCleared(Sender);
	((TSynEditStringList*) fOrigLines)->OnCleared(Sender);
}

void __fastcall TCustomSynEdit::ChainListDeleted(TObject* Sender, int aIndex, int aCount)
{
	if(ASSIGNED(fChainListDeleted))
		fChainListDeleted(Sender, aIndex, aCount);
	((TSynEditStringList*) fOrigLines)->OnDeleted(Sender, aIndex, aCount);
}

void __fastcall TCustomSynEdit::ChainListInserted(TObject* Sender, int aIndex, int aCount)
{
	if(ASSIGNED(fChainListInserted))
		fChainListInserted(Sender, aIndex, aCount);
	((TSynEditStringList*) fOrigLines)->OnInserted(Sender, aIndex, aCount);
}

void __fastcall TCustomSynEdit::ChainListPut(TObject* Sender, int aIndex, const String OldLine)
{
	if(ASSIGNED(fChainListPut))
		fChainListPut(Sender, aIndex, OldLine);
	((TSynEditStringList*) fOrigLines)->OnPut(Sender, aIndex, OldLine);
}

void __fastcall TCustomSynEdit::ChainLinesChanging(TObject* Sender)
{
	if(ASSIGNED(fChainLinesChanging))
		fChainLinesChanging(Sender);
	((TSynEditStringList*) fOrigLines)->OnChanging(Sender);
}

void __fastcall TCustomSynEdit::ChainLinesChanged(TObject* Sender)
{
	if(ASSIGNED(fChainLinesChanged))
		fChainLinesChanged(Sender);
	((TSynEditStringList*) fOrigLines)->OnChange(Sender);
}

void __fastcall TCustomSynEdit::ChainModifiedChanged(TObject* Sender)
{
	if(ASSIGNED(fChainModifiedChanged))
		fChainModifiedChanged(Sender);
	fOrigUndoRedo->OnModifiedChanged(Sender);
}

//++ DPI-Aware

void __fastcall TCustomSynEdit::ChangeScale(int M, int D, bool isDpiChange)
{
	if(isDpiChange)
	{
		fTextMargin = MulDiv(fTextMargin, M, D);
		fGutter->ChangeScale(M, D);
		fBookMarkOpt->ChangeScale(M, D);
		fWordWrapGlyph->ChangeScale(M, D);
	}
	inherited::ChangeScale(M, D, isDpiChange);
}
//-- DPI-Aware

void __fastcall TCustomSynEdit::UnHookTextBuffer()
{
	bool vOldWrap = false;
	Assert(fChainedEditor == nullptr);
	if(fLines == fOrigLines)
		return;
	vOldWrap = WordWrap;
	WordWrap = false;

  //first put back the real methods
	/*# with TSynEditStringList(fLines) do */
	{
		auto with0 = ((TSynEditStringList*) fLines);
		with0->OnCleared = fChainListCleared;
		with0->OnDeleted = fChainListDeleted;
		with0->OnInserted = fChainListInserted;
		with0->OnPut = fChainListPut;
		with0->OnChanging = fChainLinesChanging;
		with0->OnChange = fChainLinesChanged;
	}
	fUndoRedo->OnModifiedChanged = fChainModifiedChanged;
	fChainListCleared = nullptr;
	fChainListDeleted = nullptr;
	fChainListInserted = nullptr;
	fChainListPut = nullptr;
	fChainLinesChanging = nullptr;
	fChainLinesChanged = nullptr;
	fChainModifiedChanged = nullptr;

  //make the switch
	fLines = fOrigLines;
	fUndoRedo = fOrigUndoRedo;
	LinesHookChanged();
	WordWrap = vOldWrap;
}

void __fastcall TCustomSynEdit::HookTextBuffer(TSynEditStringList* aBuffer, ISynEditUndo* aUndoRedo)
{
	bool vOldWrap = false;
	Assert(fChainedEditor == nullptr);
	Assert(fLines == fOrigLines);
	vOldWrap = WordWrap;
	WordWrap = false;
	if(fChainedEditor != nullptr)
		RemoveLinesPointer();
	else
	{
		if(fLines != fOrigLines)
			UnHookTextBuffer();

  //store the current values and put in the chained methods
	}
	fChainListCleared = aBuffer->OnCleared;
	aBuffer->OnCleared = ChainListCleared;
	fChainListDeleted = aBuffer->OnDeleted;
	aBuffer->OnDeleted = ChainListDeleted;
	fChainListInserted = aBuffer->OnInserted;
	aBuffer->OnInserted = ChainListInserted;
	fChainListPut = aBuffer->OnPut;
	aBuffer->OnPut = ChainListPut;
	fChainLinesChanging = aBuffer->OnChanging;
	aBuffer->OnChanging = ChainLinesChanging;
	fChainLinesChanged = aBuffer->OnChange;
	aBuffer->OnChange = ChainLinesChanged;
	fChainModifiedChanged = aUndoRedo->OnModifiedChanged;
	aUndoRedo->OnModifiedChanged = ChainModifiedChanged;

  //make the switch
	fLines = aBuffer;
	fUndoRedo = aUndoRedo;
	LinesHookChanged();
	WordWrap = vOldWrap;
}

void __fastcall TCustomSynEdit::LinesHookChanged()
{
	Invalidate();
	UpdateScrollBars();
}

void __fastcall TCustomSynEdit::SetLinesPointer(TCustomSynEdit* ASynEdit)
{
	HookTextBuffer(((TSynEditStringList*) ASynEdit->Lines), ASynEdit->UndoRedo);
	fChainedEditor = ASynEdit;
	ASynEdit->FreeNotification(this);
}

void __fastcall TCustomSynEdit::RemoveLinesPointer()
{
	if(ASSIGNED(fChainedEditor))
		RemoveFreeNotification(fChainedEditor);
	fChainedEditor = nullptr;
	UnHookTextBuffer();
}

void __fastcall TCustomSynEdit::SetRightEdge(int Value)
{
	if(fRightEdge != Value)
	{
		fRightEdge = Value;
		Invalidate();
	}
}

void __fastcall TCustomSynEdit::SetRightEdgeColor(TColor Value)
{
	int nX = 0;
	TRect rcInval = {};
	if(fRightEdgeColor != Value)
	{
		fRightEdgeColor = Value;
		if(HandleAllocated())
		{
			nX = fTextOffset + fRightEdge * fCharWidth;
			rcInval = Rect(nX - 1, 0, nX + 1, Height);
			InvalidateRect(rcInval, false);
		}
	}
}

int __fastcall TCustomSynEdit::GetMaxUndo()
{
	int result = 0;
	result = fUndoRedo->MaxUndoActions;
	return result;
}

bool __fastcall TCustomSynEdit::GetModified()
{
	bool result = false;
	result = fUndoRedo->Modified;
	return result;
}

void __fastcall TCustomSynEdit::SetMaxUndo(int Value)
{
	fUndoRedo->MaxUndoActions = Value;
}

void __fastcall TCustomSynEdit::Notification(TComponent* AComponent, TOperation Operation)
{
	inherited::Notification(AComponent, Operation);
	if(Operation == opRemove)
	{
		if(AComponent == fSearchEngine)
		{
			SearchEngine = nullptr;
		}
		if(AComponent == fHighlighter)
		{
			Highlighter = nullptr;
		}
		if(AComponent == fChainedEditor)
		{
			RemoveLinesPointer();
		}
		if(fBookMarkOpt != nullptr)
		{
			if(AComponent == fBookMarkOpt->BookmarkImages)
			{
				fBookMarkOpt->BookmarkImages = nullptr;
				InvalidateGutterLines(-1, -1);
			}
		}
	}
}
//++ CodeFolding

void __fastcall TCustomSynEdit::SetHighlighter(TSynCustomHighlighter* const Value)
{
	bool OldUseCodeFolding = false;
//-- CodeFolding
	if(Value != fHighlighter)
	{
		if(ASSIGNED(fHighlighter))
		{
			fHighlighter->UnhookAttrChangeEvent(HighlighterAttrChanged);
			fHighlighter->RemoveFreeNotification(this);
		}
		if(ASSIGNED(Value))
		{
			Value->HookAttrChangeEvent(HighlighterAttrChanged);
			Value->FreeNotification(this);
		}
		fHighlighter = const_cast<TSynCustomHighlighter*>(Value);
		if(!(ComponentState.Contains(csDestroying)))
			HighlighterAttrChanged(fHighlighter);

//++ CodeFolding
    //  Disable Code Folding if not supported by highlighter
		OldUseCodeFolding = fUseCodeFolding;
		UseCodeFolding = false;
		UseCodeFolding = OldUseCodeFolding;
		if(ObjectIs(fHighlighter, TSynCustomCodeFoldingHighlighter*))
			((TSynCustomCodeFoldingHighlighter*) fHighlighter)->InitFoldRanges(fAllFoldRanges);
//-- CodeFolding
	}
}

void __fastcall TCustomSynEdit::SetBorderStyle(TSynBorderStyle Value)
{
	if(fBorderStyle != Value)
	{
		fBorderStyle = Value;
		RecreateWnd();
	}
}

void __fastcall TCustomSynEdit::SetHideSelection(bool Value)
{
	if(fHideSelection != Value)
	{
		fHideSelection = Value;
		InvalidateSelection();
	}
}

void __fastcall TCustomSynEdit::SetInsertMode(bool Value)
{
	if(fInserting != Value)
	{
		fInserting = Value;
		if(!(ComponentState.Contains(csDesigning)))
      // Reset the caret.
			InitializeCaret();
		StatusChanged(Synedit__36);
	}
}

void __fastcall TCustomSynEdit::InitializeCaret()
{
	TSynEditCaretType ct = ctVerticalLine;
	int cw = 0;
	int ch = 0;
  // CreateCaret automatically destroys the previous one, so we don't have to
  // worry about cleaning up the old one here with DestroyCaret.
  // Ideally, we will have properties that control what these two carets look like.
	if(InsertMode)
		ct = fInsertCaret;
	else
		ct = fOverwriteCaret;
	switch(ct)
	{
		case ctHorizontalLine:
		{
			cw = fCharWidth;
			ch = 2;
			fCaretOffset = Point(0, fTextHeight - 2);
		}
		break;
		case ctHalfBlock:
		{
			cw = fCharWidth;
			ch = (int)((fTextHeight - 2) / /*div*/ 2);
			fCaretOffset = Point(0, ch);
		}
		break;
		case ctBlock:
		{
			cw = fCharWidth;
			ch = fTextHeight - 2;
			fCaretOffset = Point(0, 0);
		}
		break;
		default:
		{
			cw = 2;
			ch = fTextHeight - 2;
			fCaretOffset = Point(-1, 0);
		}
		break;
	}
	fStateFlags >> sfCaretVisible;
	if(Focused() || fAlwaysShowCaret)
	{
		CreateCaret(Handle, 0, cw, ch);
		UpdateCaret();
	}
}

void __fastcall TCustomSynEdit::SetInsertCaret(TSynEditCaretType Value)
{
	if(fInsertCaret != Value)
	{
		fInsertCaret = Value;
		InitializeCaret();
	}
}

void __fastcall TCustomSynEdit::SetOverwriteCaret(TSynEditCaretType Value)
{
	if(fOverwriteCaret != Value)
	{
		fOverwriteCaret = Value;
		InitializeCaret();
	}
}

void __fastcall TCustomSynEdit::EnsureCursorPosVisible()
{
	EnsureCursorPosVisibleEx(false);
}

void __fastcall TCustomSynEdit::EnsureCursorPosVisibleEx(bool ForceToMiddle, bool EvenIfVisible/*# = false*/)
{
	int TmpMiddle = 0;
	int VisibleX = 0;
	int vCaretRow = 0;
	HandleNeeded();
	IncPaintLock();
	try

    // Make sure X is visible
	{
		VisibleX = DisplayX;
		if(VisibleX < LeftChar)
			LeftChar = VisibleX;
		else
		{
			if(VisibleX >= CharsInWindow + LeftChar)
				LeftChar = VisibleX - CharsInWindow + 1;
			else
				LeftChar = LeftChar;

    // Make sure Y is visible
		}
		vCaretRow = DisplayY;
		if(ForceToMiddle)
		{
			if(vCaretRow < (TopLine - 1))
			{
				TmpMiddle = (int)(LinesInWindow / /*div*/ 2);
				if(vCaretRow - TmpMiddle < 0)
					TopLine = 1;
				else
					TopLine = vCaretRow - TmpMiddle + 1;
			}
			else
			{
				if(vCaretRow > (TopLine + (LinesInWindow - 2)))
				{
					TmpMiddle = (int)(LinesInWindow / /*div*/ 2);
					TopLine = vCaretRow - (LinesInWindow - 1) + TmpMiddle;
     /* Forces to middle even if visible in viewport */
				}
				else
				{
					if(EvenIfVisible)
					{
						TmpMiddle = (int)(fLinesInWindow / /*div*/ 2);
						TopLine = vCaretRow - TmpMiddle + 1;
					}
				}
			}
		}
		else
		{
			if(vCaretRow < TopLine)
				TopLine = vCaretRow;
			else
			{
				if(vCaretRow > TopLine + Max(1, LinesInWindow) - 1)
					TopLine = vCaretRow - (LinesInWindow - 1);
				else
					TopLine = TopLine;
			}
		}
	}
	__finally
	{
		DecPaintLock();
	}
}

void __fastcall TCustomSynEdit::SetKeystrokes(TSynEditKeyStrokes* const Value)
{
	if(Value == nullptr)
		fKeyStrokes->Clear();
	else
		fKeyStrokes->Assign((TPersistent*) Value);
}

void __fastcall TCustomSynEdit::SetDefaultKeystrokes()
{
	fKeyStrokes->ResetDefaults();
}

// If the translations requires Data, memory will be allocated for it via a
// GetMem call.  The client must call FreeMem on Data if it is not NIL.

TSynEditorCommand __fastcall TCustomSynEdit::TranslateKeyCode(WORD Code, TShiftState Shift, void*& Data)
{
	TSynEditorCommand result = 0;
	int i = 0;
	i = Keystrokes->FindKeycode2(fLastKey, fLastShiftState, Code, Shift);
	if(i >= 0)
		result = Keystrokes->Items[i]->Command;
	else
	{
		i = Keystrokes->FindKeycode(Code, Shift);
		if(i >= 0)
			result = Keystrokes->Items[i]->Command;
		else
			result = (TSynEditorCommand) ecNone;
	}
	if((result == ecNone) && (Code >= VK_ACCEPT) && (Code <= VK_SCROLL))
	{
		fLastKey = Code;
		fLastShiftState = Shift;
	}
	else
	{
		fLastKey = 0;
		fLastShiftState = Synedit__37;
	}
	return result;
}

void __fastcall TCustomSynEdit::TripleClick()
{
	TBufferCoord BB = {};
	TBufferCoord BE = {};
	if(!(fOptions.Contains(eoNoSelection)))
	{
		BB = BufferCoord(1, CaretY);
		if(CaretY < Lines->Count)
			BE = BufferCoord(1, CaretY + 1);
		else
			BE = BufferCoord(Lines->Strings[CaretY - 1].Length() + 1, CaretY);
		SetCaretAndSelection(BE, BB, BE);
	}
	if(ASSIGNED(fOnTripleClick))
		fOnTripleClick(this);
}

void __fastcall TCustomSynEdit::CommandProcessor(TSynEditorCommand Command, WideChar AChar, void* Data)
{

  // first the program event handler gets a chance to process the command
	fUndoRedo->CommandProcessed = Command;
	DoOnProcessCommand(Command, AChar, Data);
	if(Command != ecNone)
    // notify hooked command handlers before the command is executed inside of
    // the class
	{
		NotifyHookedCommandHandlers(false, Command, AChar, Data);
    // internal command handler
		if((Command != ecNone) && (Command < ecUserFirst))
			ExecuteCommand(Command, AChar, Data);
    // notify hooked command handlers after the command was executed inside of
    // the class
		if(Command != ecNone)
			NotifyHookedCommandHandlers(true, Command, AChar, Data);
	}
	DoOnCommandProcessed(Command, AChar, Data);
	fUndoRedo->CommandProcessed = (TSynEditorCommand) ecNone;
}

void __fastcall TCustomSynEdit::ExecuteCommand(TSynEditorCommand Command, WideChar AChar, void* Data)
{
	int CX = 0;
	int Len = 0;
	String Temp;
	String Temp2;
	String Helper;
	String TabBuffer;
	String SpaceBuffer;
	int SpaceCount1 = 0;
	int SpaceCount2 = 0;
	int BackCounter = 0;
	TBufferCoord StartOfBlock = {};
	bool bChangeScroll = false;
	bool moveBkm = false;
	TBufferCoord WP = {};
	TBufferCoord Caret = {};
	TBufferCoord CaretNew = {};
	int CaretXNew = 0;
	int counter = 0;
	int vCaretRow = 0;
	String s;
	int SaveLastCaretX = 0;
	IncPaintLock();
	try
	{
		switch(Command)
		{
			case ecLeft:
			case ecSelLeft:
// horizontal caret movement or selection
			MoveCaretHorz(-1, Command == ecSelLeft);
			break;
			case ecRight:
			case ecSelRight:
			MoveCaretHorz(1, Command == ecSelRight);
			break;
			case ecPageLeft:
			case ecSelPageLeft:
			MoveCaretHorz(-CharsInWindow, Command == ecSelPageLeft);
			break;
			case ecPageRight:
			case ecSelPageRight:
			MoveCaretHorz(CharsInWindow, Command == ecSelPageRight);
			break;
			case ecLineStart:
			case ecSelLineStart:
			{
				DoHomeKey(Command == ecSelLineStart);
			}
			break;
			case ecLineEnd:
			case ecSelLineEnd:
			DoEndKey(Command == ecSelLineEnd);
			break;
// vertical caret movement or selection
			
          /* on the first line we select first line too */
			case ecUp:
			case ecSelUp:
			{
				if(CaretY == 1)
				{
					SaveLastCaretX = fLastCaretX;
					DoHomeKey(Command == ecSelUp);
					fLastCaretX = SaveLastCaretX;
				}
				else
				MoveCaretVert(-1, Command == ecSelUp);
				Update();
			}
			break;
          /* on the last line we will select last line too */
			case ecDown:
			case ecSelDown:
			{
				if(CaretY == Lines->Count)
				{
					SaveLastCaretX = fLastCaretX;
					DoEndKey(Command == ecSelDown);
					fLastCaretX = SaveLastCaretX;
				}
				else
				MoveCaretVert(1, Command == ecSelDown);
				Update();
			}
			break;
			case ecPageUp:
			case ecSelPageUp:
			case ecPageDown:
			case ecSelPageDown:
			{
				counter = fLinesInWindow >> int(fOptions.Contains(eoHalfPageScroll));
				if(fOptions.Contains(eoScrollByOneLess))
					--counter;
				if(Synedit__38.Contains(Command))
					counter = -counter;
				TopLine = TopLine + counter;
          /* on the first line we will select first line too */
				if((Synedit__39.Contains(Command)) && (CaretY == 1))
				{
					SaveLastCaretX = fLastCaretX;
					DoHomeKey(Command == ecSelPageUp);
					fLastCaretX = SaveLastCaretX;
				}
				else
				{
					if((Synedit__40.Contains(Command)) && (CaretY == Lines->Count))
          /* on the last line we will select last line too */
					{
						SaveLastCaretX = fLastCaretX;
						DoEndKey(Command == ecSelPageDown);
						fLastCaretX = SaveLastCaretX;
					}
					else
					MoveCaretVert(counter, Synedit__41.Contains(Command));
				}
				Update();
			}
			break;
			case ecPageTop:
			case ecSelPageTop:
			{
				CaretNew = DisplayToBufferPos(DisplayCoord(DisplayX, TopLine));
				MoveCaretAndSelection(CaretXY, CaretNew, Command == ecSelPageTop);
				Update();
			}
			break;
			case ecPageBottom:
			case ecSelPageBottom:
			{
				CaretNew = DisplayToBufferPos(DisplayCoord(DisplayX, TopLine + LinesInWindow - 1));
				MoveCaretAndSelection(CaretXY, CaretNew, Command == ecSelPageBottom);
				Update();
			}
			break;
			case ecEditorTop:
			case ecSelEditorTop:
			{
				CaretNew.Char = 1;
				CaretNew.Line = 1;
				MoveCaretAndSelection(CaretXY, CaretNew, Command == ecSelEditorTop);
				Update();
			}
			break;
			case ecEditorBottom:
			case ecSelEditorBottom:
			{
				CaretNew.Char = 1;
				CaretNew.Line = Lines->Count;
				if(CaretNew.Line > 0)
					CaretNew.Char = Lines->Strings[CaretNew.Line - 1].Length() + 1;
				MoveCaretAndSelection(CaretXY, CaretNew, Command == ecSelEditorBottom);
				Update();
			}
			break;
// goto special line / column position
			case ecGotoXY:
			case ecSelGotoXY:
			if(ASSIGNED(Data))
			{
				MoveCaretAndSelection(CaretXY, (*(TBufferCoord*) Data), Command == ecSelGotoXY);
				Update();
			}
			break;
// word selection
			case ecWordLeft:
			case ecSelWordLeft:
			{
				CaretNew = PrevWordPos();
				MoveCaretAndSelection(CaretXY, CaretNew, Command == ecSelWordLeft);
			}
			break;
			case ecWordRight:
			case ecSelWordRight:
			{
				CaretNew = NextWordPos();
				MoveCaretAndSelection(CaretXY, CaretNew, Command == ecSelWordRight);
			}
			break;
			case ecSelWord:
			{
				SetSelWord();
			}
			break;
			case ecSelectAll:
			{
				SelectAll();
			}
			break;
			case ecDeleteLastChar:
			if(!ReadOnly)
			{
				DoOnPaintTransientEx(ttBefore, true);
				try
				{
					if(SelAvail)
						SetSelText(L"");
					else
					{
						Temp = LineText;
						TabBuffer = ((TSynEditStringList*) Lines)->ExpandedStrings[CaretY - 1];
						Len = Temp.Length();
						Caret = CaretXY;
						if(CaretX > Len + 1)
						{
							if(fOptions.Contains(eoSmartTabDelete))
                  //It's at the end of the line, move it to the length
							{
								if(Len > 0)
									CaretX = Len + 1;
								else

                    //move it as if there were normal spaces there
								{
									SpaceCount1 = CaretX - 1;
									SpaceCount2 = 0;
                    // unindent
									if(SpaceCount1 > 0)
									{
										BackCounter = CaretY - 2;
										while(BackCounter >= 0)
										{
											SpaceCount2 = LeftSpaces(Lines->Strings[BackCounter]);
											if((SpaceCount2 > 0) && (SpaceCount2 < SpaceCount1))
												break;
											--BackCounter;
										}
										if((BackCounter == -1) && (SpaceCount2 > SpaceCount1))
											SpaceCount2 = 0;
									}
									if(SpaceCount2 == SpaceCount1)
										SpaceCount2 = 0;
									CaretX = fCaretX - (SpaceCount1 - SpaceCount2);
								}
							}
							else

                  // only move caret one column
							{
								CaretX = CaretX - 1;
							} // CaretX > Len + 1
						}
						else
						{
							if(CaretX == 1)
                // join this line with the last line if possible
							{
								if(CaretY > 1)
								{
									BeginUndoBlock();
									try
									{
										CaretXY = BufferCoord(Lines->Strings[CaretY - 2].Length() + 1, CaretY - 1);
										Lines->Delete(CaretY);
										LineText = LineText + Temp;
									}
									__finally
									{
										EndUndoBlock();
									}
								}
							}
							else

                // delete text before the caret
							{
								SpaceCount1 = LeftSpaces(Temp);
								SpaceCount2 = 0;
								if((Temp[CaretX - 1] <= L'\x20') && (SpaceCount1 == CaretX - 1))
								{
									if(fOptions.Contains(eoSmartTabDelete))
                    // unindent
									{
										SpaceCount1 = LeftSpaces(Temp, true);
										Assert(SpaceCount1 > 0);
										BackCounter = CaretY - 2;
										while(BackCounter >= 0)
										{
											Temp2 = Lines->Strings[BackCounter];
											SpaceCount2 = LeftSpaces(Temp2, true);
											if((Temp2.Length() > 0) && (SpaceCount2 < SpaceCount1))
												break;
											--BackCounter;
										}
										if((BackCounter == -1) && (SpaceCount2 >= SpaceCount1))
											SpaceCount2 = 0;
										Temp.Delete(1, 	LeftSpaces(Temp));
										Temp2 = GetLeftSpacing(SpaceCount2, true);
										Temp = Temp2 + Temp;
										CaretXNew = Temp2.Length() + 1;
									}
									else
									{
										SpaceCount2 = SpaceCount1;
                    //how much till the next tab column
										BackCounter = (DisplayX - 1) % fTabWidth;
										if(BackCounter == 0)
											BackCounter = fTabWidth;
										SpaceCount1 = 0;
										CX = DisplayX - BackCounter;
										while((SpaceCount1 < fTabWidth) && (SpaceCount1 < BackCounter) && (TabBuffer[CX] != L'\x09'))
										{
											++SpaceCount1;
											++CX;
										}
										if(TabBuffer[CX] == L'\x09')
											SpaceCount1 = SpaceCount1 + 1;
										if(SpaceCount2 == SpaceCount1)
											Temp.Delete(1, 	SpaceCount1);
										else
											Temp.Delete(SpaceCount2 - SpaceCount1 + 1, 	SpaceCount1);
										SpaceCount2 = 0;
										CaretXNew = fCaretX - (SpaceCount1 - SpaceCount2);
									}
									Lines->Strings[CaretY - 1] = Temp;
									CaretX = CaretXNew;
								}
								else

                  // delete char
								{
									CaretX = CaretX - 1;
									Temp.Delete(CaretX, 	1);
									Lines->Strings[CaretY - 1] = Temp;
								}
							}
						}
					}
					EnsureCursorPosVisible();
				}
				__finally
				{
					DoOnPaintTransientEx(ttAfter, true);
				}
			}
			break;
			case ecDeleteChar:
			if(!ReadOnly)
			{
				DoOnPaintTransient(ttBefore);
				if(SelAvail)
					SetSelText(L"");
				else

            // Call UpdateLastCaretX. Even though the caret doesn't move, the
            // current caret position should "stick" whenever text is modified.
				{
					UpdateLastCaretX();
					Temp = LineText;
					Len = Temp.Length();
					if(CaretX <= Len)
              // delete char
					{
						Temp.Delete(CaretX, 	1);
						Lines->Strings[CaretY - 1] = Temp;
					}
					else

              // join line with the line after
					{
						if(CaretY < Lines->Count)
						{
							BeginUndoBlock();
							try
							{
								Helper = StringOfChar(L'\x20', CaretX - 1 - Len);
								Lines->Strings[CaretY - 1] = Temp + Helper + Lines->Strings[CaretY];
								Lines->Delete(CaretY);
							}
							__finally
							{
								EndUndoBlock();
							}
						}
					}
				}
				DoOnPaintTransient(ttAfter);
			}
			break;
			case ecDeleteWord:
			case ecDeleteEOL:
			if(!ReadOnly)
			{
				Len = LineText.Length();
				if(Command == ecDeleteWord)
            // in case of ident char, we delete word else char
				{
					WP = CaretXY;
            // as first we skip all white chars behind cursor
					if((Len > WP.Char) && IsWhiteChar(LineText[WP.Char]))
					{
						CX = StrScanForCharInCategory(LineText, WP.Char, IsNonWhiteChar);
              // if not found, StrScanForCharInCategory() returns zero
						WP.Char = Max(WP.Char, CX);
					}
            // in case of not ident char we move one char right
					if((Len > WP.Char) && !IsIdentChar(LineText[WP.Char]))
            // in case of ident char, we move to word end
						WP.Char = WP.Char + 1;
					else
						WP = WordEndEx(WP);
            // now we skip whitespaces behind
					if((Len > WP.Char) && IsWhiteChar(LineText[WP.Char]))
					{
						CX = StrScanForCharInCategory(LineText, WP.Char, IsNonWhiteChar);
              // if not found, StrScanForCharInCategory() returns 0
						WP.Char = Max(WP.Char, CX);
					}
				}
				else
				{
					WP.Char = Len + 1;
					WP.Line = CaretY;
				}
				if((WP > CaretXY) && (WP.Line == CaretY))
				{
					DoOnPaintTransient(ttBefore);
					Temp = Lines->Strings[CaretY - 1];
					Temp.Delete(CaretX, WP.Char - CaretX);
					Lines->Strings[CaretY - 1] = Temp;
					DoOnPaintTransient(ttAfter);
				}
			}
			break;
			case ecDeleteLastWord:
			case ecDeleteBOL:
			if(!ReadOnly)
			{
				if(Command == ecDeleteLastWord)
            // we must find word end first
				{
					WP = CaretXY;
            // in case scroll past EOL cursor can be behind the line end
					WP.Char = Min(LineText.Length(), WP.Char);
					if((WP.Char > 1) && IsWordBreakChar(LineText[WP.Char - 1]))
						WP.Char = StrRScanForCharInCategory(LineText, WP.Char - 1, IsIdentChar) + 1;
            // now we move to word start
					WP = WordStartEx(WP);
				}
				else
				{
					WP.Char = 1;
					WP.Line = CaretY;
				}
				if((WP < CaretXY) && (WP.Line == CaretY))
				{
					DoOnPaintTransient(ttBefore);
					Temp = Lines->Strings[CaretY - 1];
					Temp.Delete(WP.Char, CaretX - WP.Char);
					Lines->Strings[CaretY - 1] = Temp;
					CaretXY = WP;
					DoOnPaintTransient(ttAfter);
				}
			}
			break;
			case ecDeleteLine:
			ExecCmdDeleteLine();
			break;
			case ecClearAll:
			{
				if(!ReadOnly)
					ClearAll();
			}
			break;
			case ecInsertLine:
			case ecLineBreak:
			if(!ReadOnly)
			{
				BeginUndoBlock();
				try
				{
					if(SelAvail)
						SetSelText(L"");
					Temp = LineText;
					Temp2 = Temp;
					Len = Temp.Length();
					if((Len > 0) && (CaretX <= Len))
					{
						if(CaretX > 1)
						{
							Temp = LineText.SubString(1, CaretX - 1);
							if(Options.Contains(eoAutoIndent))
								SpaceCount1 = LeftSpaces(Temp, true);
							else
								SpaceCount1 = 0;
							Temp2.Delete(1, CaretX - 1);
							SpaceBuffer = GetLeftSpacing(SpaceCount1, true);
							Lines->Insert(CaretY, SpaceBuffer + Temp2);
							Lines->Strings[CaretY - 1] = Temp;
							if(Command == ecLineBreak)
								CaretXY = BufferCoord(SpaceBuffer.Length() + 1, CaretY + 1);
						}
						else
						{
							Lines->Insert(CaretY - 1, L"");
							if(Command == ecLineBreak)
								CaretY = CaretY + 1;
						} // (Len > 0) and (CaretX < Len)
					}
					else

              // either emtpy or at the end of line: insert new line below
					{
						if(fLines->Count == 0)
							fLines->Add(L"");
						SpaceCount2 = 0;
              /* Autoindent only in case we are not on the line begin */
						if((Options.Contains(eoAutoIndent)) && (CaretX > 1))
						{
							BackCounter = CaretY;
							do
							{
								--BackCounter;
								Temp = Lines->Strings[BackCounter];
								SpaceCount2 = LeftSpaces(Temp, true);
							}
							while(!((BackCounter == 0) || (Temp != L"")));
						}
						SpaceBuffer = GetLeftSpacing(SpaceCount2, true);
						Lines->Insert(CaretY, SpaceBuffer);
						if(Command == ecLineBreak)
							CaretXY = BufferCoord(SpaceBuffer.Length() + 1, CaretY + 1);
					}
					UpdateLastCaretX();
				}
				__finally
				{
					EndUndoBlock();
				}
			}
			break;
			case ecTab:
			if(!ReadOnly)
				DoTabKey();
			break;
			case ecShiftTab:
			if(!ReadOnly)
				DoShiftTabKey();
			break;
			case ecMatchBracket:
			FindMatchingBracket();
			break;
      // #127 is Ctrl + Backspace, #32 is space
			case ecChar:
			if(!ReadOnly && (AChar >= L'\x20') && (AChar != L'\x7f'))
			{
				DoOnPaintTransient(ttBefore);
				if(SelAvail)
					SetSelText(String(AChar));
				else
				{
					Temp = LineText;
					Len = Temp.Length();
					if(Len < CaretX)
					{
						if(Len > 0)
							SpaceBuffer = StringOfChar(L'\x20', CaretX - Len - int(fInserting));
						else
							SpaceBuffer = GetLeftSpacing(CaretX - Len - int(fInserting), true);
						Temp = Temp + SpaceBuffer;
					}
            // Added the check for whether or not we're in insert mode.
            // If we are, we append one less space than we would in overwrite mode.
            // This is because in overwrite mode we have to put in a final space
            // character which will be overwritten with the typed character.  If we put the
            // extra space in in insert mode, it would be left at the end of the line and
            // cause problems unless eoTrimTrailingSpaces is set.
					bChangeScroll = !(fOptions.Contains(eoScrollPastEol));
					try
					{
						if(bChangeScroll)
							fOptions << eoScrollPastEol;
						StartOfBlock = CaretXY;
						if(fInserting)
						{
							Temp.Insert(AChar,	CaretX);
							Lines->Strings[CaretY - 1] = Temp;
							if(Len == 0)
								CaretX = Temp.Length() + 1;
							else
								CaretX = CaretX + 1;
						}
						else

              // Processing of case character covers on LeadByte.
						{
							Temp[CaretX] = AChar;
							Lines->Strings[CaretY - 1] = Temp;
							CaretX = CaretX + 1;
						}
						if(CaretX >= LeftChar + fCharsInWindow)
							LeftChar = LeftChar + Min(25, fCharsInWindow - 1);
					}
					__finally
					{
						if(bChangeScroll)
							fOptions >> eoScrollPastEol;
					}
				}
				DoOnPaintTransient(ttAfter);
			}
			break;
			case Syneditkeycmds::ecUpperCase:
			case Syneditkeycmds::ecLowerCase:
			case ecToggleCase:
			case ecTitleCase:
			ExecCmdCaseChange(Command);
			break;
			case ecUndo:
			{
				if(!ReadOnly)
					Undo();
			}
			break;
			case ecRedo:
			{
				if(!ReadOnly)
					Redo();
			}
			break;
			case 301: case 302: case 303: case 304: case 305: case 306: case 307: case 308: case 309: case 310:
			{
				if(BookMarkOptions->EnableKeys)
					GotoBookMark(Command - ecGotoMarker0);
			}
			break;
			case 351: case 352: case 353: case 354: case 355: case 356: case 357: case 358: case 359: case 360:
			{
				if(BookMarkOptions->EnableKeys)
				{
					CX = Command - ecSetMarker0;
					if(ASSIGNED(Data))
						Caret = (*(TBufferCoord*) Data);
					else
						Caret = CaretXY;
					if(ASSIGNED(fBookMarks[CX]))
					{
						moveBkm = (fBookMarks[CX]->Line != Caret.Line);
						ClearBookMark(CX);
						if(moveBkm)
							SetBookMark(CX, Caret.Char, Caret.Line);
					}
					else
					SetBookMark(CX, Caret.Char, Caret.Line);
				} // if BookMarkOptions.EnableKeys
			}
			break;
			case ecCut:
			{
				if((!ReadOnly) && SelAvail)
					CutToClipboard();
			}
			break;
			case ecCopy:
			{
				CopyToClipboard();
			}
			break;
			case ecPaste:
			{
				if(!ReadOnly)
					PasteFromClipboard();
			}
			break;
			case ecScrollUp:
			case ecScrollDown:
			{
				vCaretRow = DisplayY;
				if((vCaretRow < TopLine) || (vCaretRow >= TopLine + LinesInWindow))
            // If the caret is not in view then, like the Delphi editor, move
            // it in view and do nothing else
					EnsureCursorPosVisible();
				else
				{
					if(Command == ecScrollUp)
					{
						TopLine = TopLine - 1;
						if(vCaretRow > TopLine + LinesInWindow - 1)
							MoveCaretVert((TopLine + LinesInWindow - 1) - vCaretRow, false);
					}
					else
					{
						TopLine = TopLine + 1;
						if(vCaretRow < TopLine)
							MoveCaretVert(TopLine - vCaretRow, false);
					}
					EnsureCursorPosVisible();
					Update();
				}
			}
			break;
			case ecScrollLeft:
			{
				LeftChar = LeftChar - 1;
          // todo: The following code was commented out because it is not MBCS or hard-tab safe.
          //if CaretX > LeftChar + CharsInWindow then
          //  InternalCaretX := LeftChar + CharsInWindow;
				Update();
			}
			break;
			case ecScrollRight:
			{
				LeftChar = LeftChar + 1;
          // todo: The following code was commented out because it is not MBCS or hard-tab safe.
          //if CaretX < LeftChar then
          //  InternalCaretX := LeftChar;
				Update();
			}
			break;
			case ecInsertMode:
			{
				InsertMode = true;
			}
			break;
			case ecOverwriteMode:
			{
				InsertMode = false;
			}
			break;
			case ecToggleMode:
			{
				InsertMode = !InsertMode;
			}
			break;
			case ecBlockIndent:
			if(!ReadOnly)
				DoBlockIndent();
			break;
			case ecBlockUnindent:
			if(!ReadOnly)
				DoBlockUnindent();
			break;
			case ecNormalSelect:
			SelectionMode = smNormal;
			break;
			case ecColumnSelect:
			SelectionMode = smColumn;
			break;
			case ecLineSelect:
			SelectionMode = smLine;
			break;
			case ecContextHelp:
			{
				if(ASSIGNED(fOnContextHelp))
					fOnContextHelp(this, WordAtCursor);
			}
			break;
			case ecImeStr:
			if(!ReadOnly)
			{
				s = (wchar_t*) Data /*# check length*/;
				if(SelAvail)
				{
					SetSelText(s);
					InvalidateGutterLines(-1, -1);
				}
				else
				{
					Temp = LineText;
					Len = Temp.Length();
					if(Len < CaretX)
						Temp = Temp + StringOfChar(L'\x20', CaretX - Len - 1);
					bChangeScroll = !(fOptions.Contains(eoScrollPastEol));
					try
					{
						if(bChangeScroll)
							fOptions << eoScrollPastEol;
						StartOfBlock = CaretXY;
						Len = s.Length();
						if(!fInserting)
							Temp.Delete(CaretX, 	Len);
						Temp.Insert(s,	CaretX);
						CaretX = (CaretX + Len);
						Lines->Strings[CaretY - 1] = Temp;
						if(CaretX >= LeftChar + fCharsInWindow)
							LeftChar = LeftChar + Min(25, fCharsInWindow - 1);
					}
					__finally
					{
						if(bChangeScroll)
							fOptions >> eoScrollPastEol;
					}
				}
			}
			break;
			case ecCopyLineUp:
			case ecCopyLineDown:
			case ecMoveLineUp:
			case ecMoveLineDown:
			ExecCmdCopyOrMoveLine(Command);
			break;
//++ CodeFolding
			case ecFoldAll:
			{
				CollapseAll();
			}
			break;
			case ecUnfoldAll:
			{
				UncollapseAll();
			}
			break;
			case ecFoldNearest:
			{
				CollapseNearest();
			}
			break;
			case ecUnfoldNearest:
			{
				UncollapseNearest();
			}
			break;
			case ecFoldLevel1:
			{
				CollapseLevel(1);
			}
			break;
			case ecFoldLevel2:
			{
				CollapseLevel(2);
			}
			break;
			case ecFoldLevel3:
			{
				CollapseLevel(3);
			}
			break;
			case ecUnfoldLevel1:
			{
				UnCollapseLevel(1);
			}
			break;
			case ecUnfoldLevel2:
			{
				UnCollapseLevel(2);
			}
			break;
			case ecUnfoldLevel3:
			{
				UnCollapseLevel(3);
			}
			break;
			case ecFoldRegions:
			{
				CollapseFoldType(FoldRegionType);
			}
			break;
			case ecUnfoldRegions:
			{
				UnCollapseFoldType(FoldRegionType);
			}
			break;
//-- CodeFolding
			default:
			  ;
			break;
		}
	}
	__finally
	{
		DecPaintLock();
	}
}

void __fastcall TCustomSynEdit::DoOnCommandProcessed(TSynEditorCommand Command, WideChar AChar, void* Data)
{
	if(ASSIGNED(fOnCommandProcessed))
		fOnCommandProcessed(this, Command, AChar, Data);
}

void __fastcall TCustomSynEdit::DoOnProcessCommand(TSynEditorCommand& Command, WideChar& AChar, void* Data)
{
	if(Command < ecUserFirst)
	{
		if(ASSIGNED(fOnProcessCommand))
			fOnProcessCommand(this, Command, AChar, Data);
	}
	else
	{
		if(ASSIGNED(fOnProcessUserCommand))
			fOnProcessUserCommand(this, Command, AChar, Data);
	}
}

void __fastcall TCustomSynEdit::ClearAll()
{
	Lines->Clear();
	fMarkList->Clear(); // fMarkList.Clear also frees all bookmarks,
	FillChar((void**)&fBookMarks, (int) sizeof(fBookMarks), 0); // so fBookMarks should be cleared too
	fUndoRedo->Clear();
	Modified = false;
	UpdateScrollBars();
}

void __fastcall TCustomSynEdit::ClearSelection()
{
	if(SelAvail)
		SelText = L"";
}

TBufferCoord __fastcall TCustomSynEdit::NextWordPosEx(const TBufferCoord& XY)
{
	TBufferCoord result = {};
	int CX = 0;
	int CY = 0;
	int LineLen = 0;
	String Line;
	CX = XY.Char;
	CY = XY.Line;

  // valid line?
	if((CY >= 1) && (CY <= Lines->Count))
	{
		Line = Lines->Strings[CY - 1];
		LineLen = Line.Length();
		if(CX >= LineLen)
      // find first IdentChar or multibyte char in the next line
		{
			if(CY < Lines->Count)
			{
				Line = Lines->Strings[CY];
				++CY;
				CX = StrScanForCharInCategory(Line, 1, IsIdentChar);
				if(CX == 0)
					++CX;
			}
		}
		else

      // find next word-break-char if current char is an IdentChar
		{
			if(IsIdentChar(Line[CX]))
				CX = StrScanForCharInCategory(Line, CX, IsWordBreakChar);
      // if word-break-char found, find the next IdentChar
			if(CX > 0)
				CX = StrScanForCharInCategory(Line, CX, IsIdentChar);
      // if one of those failed just position at the end of the line
			if(CX == 0)
				CX = LineLen + 1;
		}
	}
	result.Char = CX;
	result.Line = CY;
	return result;
}

TBufferCoord __fastcall TCustomSynEdit::WordStartEx(const TBufferCoord& XY)
{
	TBufferCoord result = {};
	int CX = 0;
	int CY = 0;
	String Line;
	CX = XY.Char;
	CY = XY.Line;
  // valid line?
	if((CY >= 1) && (CY <= Lines->Count))
	{
		Line = Lines->Strings[CY - 1];
		CX = Min(CX, Line.Length() + 1);
		if(CX > 1)
      // only find previous char, if not already on start of line
      // if previous char isn't a word-break-char search for the last IdentChar
		{
			if(!IsWordBreakChar(Line[CX - 1]))
				CX = StrRScanForCharInCategory(Line, CX - 1, IsWordBreakChar) + 1;
		}
	}
	result.Char = CX;
	result.Line = CY;
	return result;
}

TBufferCoord __fastcall TCustomSynEdit::WordEndEx(const TBufferCoord& XY)
{
	TBufferCoord result = {};
	int CX = 0;
	int CY = 0;
	String Line;
	CX = XY.Char;
	CY = XY.Line;
  // valid line?
	if((CY >= 1) && (CY <= Lines->Count))
	{
		Line = Lines->Strings[CY - 1];
		CX = StrScanForCharInCategory(Line, CX, IsWordBreakChar);
    // if no word-break-char is found just position at the end of the line
		if(CX == 0)
			CX = Line.Length() + 1;
	}
	result.Char = CX;
	result.Line = CY;
	return result;
}

TBufferCoord __fastcall TCustomSynEdit::PrevWordPosEx(const TBufferCoord& XY)
{
	TBufferCoord result = {};
	int CX = 0;
	int CY = 0;
	String Line;
	CX = XY.Char;
	CY = XY.Line;
  // valid line?
	if((CY >= 1) && (CY <= Lines->Count))
	{
		Line = Lines->Strings[CY - 1];
		CX = Min(CX, Line.Length() + 1);
		if(CX <= 1)
      // find last IdentChar in the previous line
		{
			if(CY > 1)
			{
				--CY;
				Line = Lines->Strings[CY - 1];
				CX = Line.Length() + 1;
			}
		}
		else

      // if previous char is a word-break-char search for the last IdentChar
		{
			if(IsWordBreakChar(Line[CX - 1]))
				CX = StrRScanForCharInCategory(Line, CX - 1, IsIdentChar);
			if(CX > 0)
        // search for the first IdentChar of this "word"
				CX = StrRScanForCharInCategory(Line, CX - 1, IsWordBreakChar) + 1;
			if(CX == 0)
        // else just position at the end of the previous line
			{
				if(CY > 1)
				{
					--CY;
					Line = Lines->Strings[CY - 1];
					CX = Line.Length() + 1;
				}
				else
				CX = 1;
			}
		}
	}
	result.Char = CX;
	result.Line = CY;
	return result;
}

void __fastcall TCustomSynEdit::SetSelectionMode(TSynSelectionMode Value)
{
	if(fSelectionMode != Value)
	{
		fSelectionMode = Value;
		ActiveSelectionMode = Value;
	}
}

void __fastcall TCustomSynEdit::SetActiveSelectionMode(TSynSelectionMode Value)
{
	if(fActiveSelectionMode != Value)
	{
		if(SelAvail)
			InvalidateSelection();
		fActiveSelectionMode = Value;
		if(SelAvail)
			InvalidateSelection();
		StatusChanged(Synedit__42);
	}
}

void __fastcall TCustomSynEdit::SetAdditionalIdentChars(const TSysCharSet Value)
{
	FAdditionalIdentChars = Value;
}

void __fastcall TCustomSynEdit::SetAdditionalWordBreakChars(const TSysCharSet Value)
{
	FAdditionalWordBreakChars = Value;
}

void __fastcall TCustomSynEdit::BeginUndoBlock()
{
	fUndoRedo->BeginBlock(this);
}

void __fastcall TCustomSynEdit::BeginUpdate()
{
	IncPaintLock();
}

void __fastcall TCustomSynEdit::EndUndoBlock()
{
	fUndoRedo->EndBlock(this);
}

void __fastcall TCustomSynEdit::EndUpdate()
{
	DecPaintLock();
}

void __fastcall TCustomSynEdit::AddKey(TSynEditorCommand Command, WORD Key1, TShiftState SS1, WORD Key2/*# = 0*/, TShiftState SS2/*# = []*/)
{
	TSynEditKeyStroke* Key = nullptr;
	Key = Keystrokes->Add();
	Key->Command = Command;
	Key->Key = Key1;
	Key->Shift = SS1;
	Key->Key2 = Key2;
	Key->Shift2 = SS2;
}

/* Called by FMarkList if change */

void __fastcall TCustomSynEdit::MarkListChange(TObject* Sender)
{
	InvalidateGutter();
}

int __fastcall TCustomSynEdit::GetSelStart()
{
	int result = 0;
	if(GetSelAvail())
		result = RowColToCharIndex(BlockBegin);
	else
		result = RowColToCharIndex(CaretXY);
	return result;
}

void __fastcall TCustomSynEdit::SetAlwaysShowCaret(bool Value)
{
	if(fAlwaysShowCaret != Value)
	{
		fAlwaysShowCaret = Value;
		if(!(ComponentState.Contains(csDestroying)) && !(Focused()))
		{
			if(Value)
			{
				InitializeCaret();
			}
			else
			{
				HideCaret();
				::DestroyCaret();
			}
		}
	}
}

void __fastcall TCustomSynEdit::SetSelStart(int Value)
{

  /* if we don't call HandleNeeded, CharsInWindow may be 0 and LeftChar will
  be set to CaretX */
	HandleNeeded();
	InternalCaretXY = CharIndexToRowCol(Value);
	BlockBegin = CaretXY;
}

int __fastcall TCustomSynEdit::GetSelEnd()
{
	int result = 0;
	if(GetSelAvail())
		result = RowColToCharIndex(BlockEnd);
	else
		result = RowColToCharIndex(CaretXY);
	return result;
}

void __fastcall TCustomSynEdit::SetSelEnd(int Value)
{
	HandleNeeded();
	BlockEnd = CharIndexToRowCol(Value);
}

void __fastcall TCustomSynEdit::SetSelWord()
{
	SetWordBlock(CaretXY);
}

void __fastcall TCustomSynEdit::SetExtraLineSpacing(int Value)
{
	fExtraLineSpacing = Value;
	SynFontChanged(this);
}

bool __fastcall TCustomSynEdit::GetBookMark(int BookMark, int& X, int& Y)
{
	bool result = false;
	int i = 0;
	result = false;
	if(ASSIGNED(Marks))
	{
		int stop = 0;
		for(stop = Marks->Count - 1, i = 0; i <= stop; i++)
		{
			if(Marks->Items[i]->IsBookmark && (Marks->Items[i]->BookmarkNumber == BookMark))
			{
				X = Marks->Items[i]->Char;
				Y = Marks->Items[i]->Line;
				result = true;
				return result;
			}
		}
	}
	return result;
}

bool __fastcall TCustomSynEdit::IsBookmark(int BookMark)
{
	bool result = false;
	int x = 0;
	int y = 0;
	result = GetBookMark(BookMark, x, y);
	return result;
}

bool __fastcall TCustomSynEdit::IsChained()
{
	bool result = false;
	result = ASSIGNED(fChainedEditor);
	return result;
}

void __fastcall TCustomSynEdit::ClearUndo()
{
	fUndoRedo->Clear();
}

void __fastcall TCustomSynEdit::SetGutter(TSynGutter* const Value)
{
	fGutter->Assign((TPersistent*) Value);
}

void __fastcall TCustomSynEdit::GutterChanged(TObject* Sender)
{
	int nW = 0;
	if(ComponentState * Synedit__43 == Synedit__44)
	{
		nW = fGutter->RealGutterWidth();
		if(nW == fGutterWidth)
			InvalidateGutter();
		else
			SetGutterWidth(nW);
	}
}

void __fastcall TCustomSynEdit::LockUndo()
{
	fUndoRedo->Lock();
}

void __fastcall TCustomSynEdit::UnlockUndo()
{
	fUndoRedo->Unlock();
}

void __fastcall TCustomSynEdit::WMSetCursor(TWMSetCursor& Msg)
{
	if((Msg.HitTest == HTCLIENT) && (Msg.CursorWnd == Handle) && !(ComponentState.Contains(csDesigning)))
	{
		UpdateMouseCursor();
	}
	else
	inherited::Dispatch(&Msg);  //#inherited method "WMSetCursor" not not accessible;
}

void __fastcall TCustomSynEdit::SetTabWidth(int Value)
{
	Value = MinMax(Value, 1, 256);
	if(Value != fTabWidth)
	{
		fTabWidth = Value;
		((TSynEditStringList*) Lines)->TabWidth = Value;
		Invalidate(); // to redraw text containing tab chars
		if(WordWrap)
		{
			fWordWrapPlugin->Reset();
			InvalidateGutter();
		}
	}
}

void __fastcall TCustomSynEdit::SelectedColorsChanged(TObject* Sender)
{
	InvalidateSelection();
}

// find / replace

int __fastcall TCustomSynEdit::SearchReplace(const String ASearch, const String AReplace, TSynSearchOptions AOptions)
{
	int result = 0;
	TBufferCoord ptStart = {};
	TBufferCoord ptEnd = {}; // start and end of the search range
	TBufferCoord ptCurrent = {}; // current search position
	int nSearchLen = 0;
	int nReplaceLen = 0;
	int n = 0;
	int nFound = 0;
	int nInLine = 0;
	int nEOLCount = 0;
	int i = 0;
	bool bBackward = false;
	bool bFromCursor = false;
	bool bPrompt = false;
	bool bReplace = false;
	bool bReplaceAll = false;
	bool bEndUndoBlock = false;
	TSynReplaceAction nAction = raCancel;
	int iResultOffset = 0;
	String sReplace;

	auto InValidSearchRange = [&](int First, int Last) -> bool 
	{
		bool result = false;
		result = true;
		if((fActiveSelectionMode == smNormal) || !(AOptions.Contains(ssoSelectedOnly)))
		{
			if(((ptCurrent.Line == ptStart.Line) && (First < ptStart.Char)) || ((ptCurrent.Line == ptEnd.Line) && (Last > ptEnd.Char)))
				result = false;
		}
		else
		{
			if(fActiveSelectionMode == smColumn)
      // solves bug in search/replace when smColumn mode active and no selection
				result = (First >= ptStart.Char) && (Last <= ptEnd.Char) || (ptEnd.Char - ptStart.Char < 1);
		}
		return result;
	};
	if(!ASSIGNED(fSearchEngine))
		throw new ESynEditError(L"No search engine has been assigned");
	result = 0;
  // can't search for or replace an empty string
	if(ASearch.Length() == 0)
		return result;
  // get the text range to search in, ignore the "Search in selection only"
  // option if nothing is selected
	bBackward = (AOptions.Contains(ssoBackwards));
	bPrompt = (AOptions.Contains(ssoPrompt));
	bReplace = (AOptions.Contains(ssoReplace));
	bReplaceAll = (AOptions.Contains(ssoReplaceAll));
	bFromCursor = !(AOptions.Contains(ssoEntireScope));
	if(!SelAvail)
		AOptions >> ssoSelectedOnly;
	if(AOptions.Contains(ssoSelectedOnly))
	{
		ptStart = BlockBegin;
		ptEnd = BlockEnd;
    // search the whole line in the line selection mode
		if(fActiveSelectionMode == smLine)
		{
			ptStart.Char = 1;
			ptEnd.Char = Lines->Strings[ptEnd.Line - 1].Length() + 1;
		}
		else
		{
			if(fActiveSelectionMode == smColumn)
			{
				if(ptStart.Char > ptEnd.Char)
      // make sure the start column is smaller than the end column
					SwapInt(ptStart.Char, ptEnd.Char);
			}
    // ignore the cursor position when searching in the selection
		}
		if(bBackward)
			ptCurrent = ptEnd;
		else
			ptCurrent = ptStart;
	}
	else
	{
		ptStart.Char = 1;
		ptStart.Line = 1;
		ptEnd.Line = Lines->Count;
		ptEnd.Char = Lines->Strings[ptEnd.Line - 1].Length() + 1;
		if(bFromCursor)
		{
			if(bBackward)
				ptEnd = CaretXY;
			else
				ptStart = CaretXY;
		}
		if(bBackward)
			ptCurrent = ptEnd;
		else
			ptCurrent = ptStart;
	}
  //  translate \n and \t to real chars for regular expressions
	sReplace = fSearchEngine->PreprocessReplaceExpression(AReplace);

  //count line ends
	nEOLCount = 0;
	i = 1;
	do
	{
		i = Pos(WideCRLF, sReplace, i);
		if(i != 0)
		{
			i = i + WideCRLF.Length();
			++nEOLCount;
		}
	}
	while(!(i == 0));
  // initialize the search engine
	fSearchEngine->Options = AOptions;
	fSearchEngine->Pattern = ASearch;
  // search while the current search position is inside of the search range
	nReplaceLen = 0;
	DoOnPaintTransient(ttBefore);
	if(bReplaceAll && !bPrompt)
	{
		IncPaintLock();
		BeginUndoBlock();
		bEndUndoBlock = true;
	}
	else
	bEndUndoBlock = false;
	try
	{
		while((ptCurrent.Line >= ptStart.Line) && (ptCurrent.Line <= ptEnd.Line))
		{
			nInLine = fSearchEngine->FindAll(Lines->Strings[ptCurrent.Line - 1]);
			iResultOffset = 0;
			if(bBackward)
				n = Pred(fSearchEngine->ResultCount);
			else
				n = 0;
      // Operate on all results in this line.
			while(nInLine > 0)

        // An occurrence may have been replaced with a text of different length
			{
				nFound = fSearchEngine->Results[n] + iResultOffset;
				nSearchLen = fSearchEngine->Lengths[n];
				if(bBackward)
					--n;
				else
					++n;
				--nInLine;
        // Is the search result entirely in the search range?
				if(!InValidSearchRange(nFound, nFound + nSearchLen))
					continue;
				++result;
        // Select the text, so the user can see it in the OnReplaceText event
        // handler or as the search result.
				ptCurrent.Char = nFound;
				BlockBegin = ptCurrent;
        // Be sure to use the Ex version of CursorPos so that it appears in the middle if necessary
				SetCaretXYEx(false, BufferCoord(1, ptCurrent.Line));
        // there is no necessary to see changes without confirmation. It signicatntly slow down replace
				if(!(bReplaceAll))
					EnsureCursorPosVisibleEx(true);
				ptCurrent.Char += nSearchLen;
				BlockEnd = ptCurrent;
				InternalCaretXY = ptCurrent;
				if(bBackward)
					InternalCaretXY = BlockBegin;
				else
					InternalCaretXY = ptCurrent;
        // If it's a search only we can leave the procedure now.
				if(!(bReplace || bReplaceAll))
					return result;
        // Prompt and replace or replace all.  If user chooses to replace
        // all after prompting, turn off prompting.
				if(bPrompt && ASSIGNED(fOnReplaceText))
				{
					nAction = DoOnReplaceText(ASearch, sReplace, ptCurrent.Line, nFound);
					if(nAction == raCancel)
						return result;
				}
				else
				nAction = raReplace;
				if(nAction == raSkip)
					--result;
				else

          // user has been prompted and has requested to silently replace all
          // so turn off prompting
				{
					if(nAction == raReplaceAll)
					{
						if(!bReplaceAll || bPrompt)
						{
							bReplaceAll = true;
							IncPaintLock();
						}
						bPrompt = false;
						if(bEndUndoBlock == false)
							BeginUndoBlock();
						bEndUndoBlock = true;
					}
          // Allow advanced substition in the search engine
					SelText = fSearchEngine->Replace(SelText, sReplace);
					nReplaceLen = CaretX - nFound;
				}
        // fix the caret position and the remaining results
				if(!bBackward)
				{
					InternalCaretX = nFound + nReplaceLen;
					if((nSearchLen != nReplaceLen) && (nAction != raSkip))
					{
						iResultOffset += nReplaceLen - nSearchLen;
						if((fActiveSelectionMode != smColumn) && (CaretY == ptEnd.Line))
						{
							ptEnd.Char += nReplaceLen - nSearchLen;
							BlockEnd = ptEnd;
						}
					}
          //Fix new line ends
					if(nEOLCount > 0)
						ptEnd.Line += nEOLCount;
				}
				if(!bReplaceAll)
					return result;
			}
      // search next / previous line
			if(bBackward)
				--ptCurrent.Line;
			else
				++ptCurrent.Line;
		}
	}
	__finally
	{
		if(bReplaceAll && !bPrompt)
			DecPaintLock();
		if(bEndUndoBlock)
			EndUndoBlock();
		DoOnPaintTransient(ttAfter);
	}
	return result;
}

bool __fastcall TCustomSynEdit::IsPointInSelection(const TBufferCoord& Value)
{
	bool result = false;
	TBufferCoord ptBegin = {};
	TBufferCoord ptEnd = {};
	ptBegin = BlockBegin;
	ptEnd = BlockEnd;
	if((Value.Line >= ptBegin.Line) && (Value.Line <= ptEnd.Line) && ((ptBegin.Line != ptEnd.Line) || (ptBegin.Char != ptEnd.Char)))
	{
		if(fActiveSelectionMode == smLine)
			result = true;
		else
		{
			if(fActiveSelectionMode == smColumn)
			{
				if(ptBegin.Char > ptEnd.Char)
					result = (Value.Char >= ptEnd.Char) && (Value.Char < ptBegin.Char);
				else
				{
					if(ptBegin.Char < ptEnd.Char)
						result = (Value.Char >= ptBegin.Char) && (Value.Char < ptEnd.Char);
					else
						result = false;
				}
			}
			else
			result = ((Value.Line > ptBegin.Line) || (Value.Char >= ptBegin.Char)) && ((Value.Line < ptEnd.Line) || (Value.Char < ptEnd.Char));
		}
	}
	else
	result = false;
	return result;
}

void __fastcall TCustomSynEdit::SetFocus()
{
	if(fFocusList->Count > 0)
	{
		if(((TWinControl*) fFocusList->Last())->CanFocus())
			((TWinControl*) fFocusList->Last())->SetFocus();
		return;
	}
	inherited::SetFocus();
}

void __fastcall TCustomSynEdit::UpdateMouseCursor()
{
	TPoint ptCursor = {};
	TBufferCoord ptLineCol = {};
	TCursor iNewCursor = (TCursor) 0;
	TDisplayCoord ptRowCol = {};
	TRect Rect = {};
	TSynGutterBand* Band = nullptr;
	GetCursorPos(&ptCursor);
	ptCursor = ScreenToClient(ptCursor);
	ptRowCol = PixelsToRowColumn(ptCursor.X, ptCursor.Y);
	ptLineCol = DisplayToBufferPos(ptRowCol);
	if(ptCursor.X < fGutterWidth)
	{
		iNewCursor = Gutter->Cursor;
		Band = fGutter->BandAtX(ptCursor.X);
		if(ASSIGNED(Band) && ASSIGNED(Band))
			Band->DoMouseCursor(this, ptCursor.X, ptCursor.Y, ptRowCol.Row, ptLineCol.Line, iNewCursor);
	}
	else
	{
		if((fOptions.Contains(eoDragDropEditing)) && (!MouseCapture) && IsPointInSelection(ptLineCol))
			iNewCursor = crArrow;
		else
		{
			if(UseCodeFolding && CodeFolding->ShowHintMark && fAllFoldRanges->CollapsedFoldStartAtLine(ptLineCol.Line))
			{
				Rect = GetCollapseMarkRect(ptRowCol.Row, ptLineCol.Line);
				if(PtInRect(Rect, ptCursor))
					iNewCursor = crHandPoint;
			}
			else
			iNewCursor = Cursor;
		}
		if(ASSIGNED(OnMouseCursor))
			OnMouseCursor(this, ptLineCol, iNewCursor);
		fKbdHandler->ExecuteMouseCursor(this, ptLineCol, iNewCursor);
	}
	::SetCursor(Screen->Cursors[iNewCursor]);
}

void __fastcall TCustomSynEdit::BookMarkOptionsChanged(TObject* Sender)
{
	InvalidateGutter();
}

TSynEditorOptions __fastcall TCustomSynEdit::GetOptions()
{
	TSynEditorOptions result;
	result = fOptions;
	return result;
}

void __fastcall TCustomSynEdit::SetOptions(TSynEditorOptions Value)
{
	const System::Set<TSynEditorOption, TSynEditorOption::eoAltSetsColumnMode, TSynEditorOption::eoCopyPlainText> ScrollOptions = System::Set<TSynEditorOption, TSynEditorOption::eoAltSetsColumnMode, TSynEditorOption::eoCopyPlainText>() << eoDisableScrollArrows << eoHideShowScrollbars << eoScrollPastEof << eoScrollPastEol;
	bool bSetDrag = false;
	bool bUpdateScroll = false;
	bool bInvalidate = false;
	if(Value != fOptions)
	{
		bSetDrag = (fOptions.Contains(eoDropFiles)) != (Value.Contains(eoDropFiles));
		bInvalidate = (fOptions.Contains(eoShowSpecialChars)) != (Value.Contains(eoShowSpecialChars));
		bUpdateScroll = (Options * ScrollOptions) != (Value * ScrollOptions);
		fUndoRedo->GroupUndo = Options.Contains(eoGroupUndo);
		if(!(Options.Contains(eoScrollPastEol)))
			LeftChar = LeftChar;
		if(!(Options.Contains(eoScrollPastEof)))
			TopLine = TopLine;
		fOptions = Value;

    // (un)register HWND as drop target
		if(bSetDrag && !(ComponentState.Contains(csDesigning)) && HandleAllocated())
			DragAcceptFiles(Handle, (fOptions.Contains(eoDropFiles)));
		if(bInvalidate)
			Invalidate();
		if(bUpdateScroll)
			UpdateScrollBars();
	}
}

void __fastcall TCustomSynEdit::SizeOrFontChanged(bool bFont)
{
	if(HandleAllocated() && (fCharWidth != 0))
	{
		fCharsInWindow = (int)(Max(ClientWidth - fGutterWidth - fTextMargin, 0) / /*div*/ fCharWidth);
		fLinesInWindow = (int)(ClientHeight / /*div*/ fTextHeight);
		if(WordWrap)
		{
			fWordWrapPlugin->DisplayChanged();
			Invalidate();
		}
		if(bFont)
		{
			if(Gutter->ShowLineNumbers && !Gutter->UseFontStyle)
				GutterChanged(this);
			else
				UpdateScrollBars();
			InitializeCaret();
			fStateFlags >> sfCaretChanged;
			Invalidate();
		}
		else
		UpdateScrollBars();
		if(!(Options.Contains(eoScrollPastEol)))
			LeftChar = LeftChar;
		if(!(Options.Contains(eoScrollPastEof)))
			TopLine = TopLine;
	}
}

void __fastcall TCustomSynEdit::MoveCaretHorz(int DX, bool SelectionCommand)
{
	TBufferCoord ptO = {};
	TBufferCoord ptDst = {};
	String s;
	int nLineLen = 0;
	bool bChangeY = false;
	TDisplayCoord vCaretRowCol = {};
	if(WordWrap)
	{
		if(DX > 0)
		{
			if(fCaretAtEOL)
			{
				fCaretAtEOL = false;
				UpdateLastCaretX();
				IncPaintLock();
				fStateFlags << sfCaretChanged;
				DecPaintLock();
				return;
			}
		}
		else
 // DX < 0. Handle ecLeft/ecPageLeft at BOL.
		{
			if((!fCaretAtEOL) && (CaretX > 1) && (DisplayX == 1))
			{
				fCaretAtEOL = true;
				UpdateLastCaretX();
				if(DisplayX > CharsInWindow + 1)
					SetInternalDisplayXY(DisplayCoord(CharsInWindow + 1, DisplayY));
				else
				{
					IncPaintLock();
					fStateFlags << sfCaretChanged;
					DecPaintLock();
				}
				return;
			}
		}
	}
	ptO = CaretXY;
	ptDst = ptO;
	s = LineText;
	nLineLen = s.Length();
  // only moving or selecting one char can change the line
	bChangeY = !(fOptions.Contains(eoScrollPastEol));
	if(bChangeY && (DX == -1) && (ptO.Char == 1) && (ptO.Line > 1))
    // end of previous line
	{
		--ptDst.Line;
		ptDst.Char = Lines->Strings[ptDst.Line - 1].Length() + 1;
	}
	else
	{
		if(bChangeY && (DX == 1) && (ptO.Char > nLineLen) && (ptO.Line < Lines->Count))
    // start of next line
		{
			++ptDst.Line;
			ptDst.Char = 1;
		}
		else
		{
			ptDst.Char = Max(1, ptDst.Char + DX);
    // don't go past last char when ScrollPastEol option not set
			if((DX > 0) && bChangeY)
				ptDst.Char = Min(ptDst.Char, nLineLen + 1);
		}
  // set caret and block begin / end
	}
	MoveCaretAndSelection(fBlockBegin, ptDst, SelectionCommand);
  // if caret is beyond CharsInWindow move to next row (this means there are
  // spaces/tabs at the end of the row)
	if(WordWrap && (DX > 0) && (CaretX < LineText.Length()))
	{
		vCaretRowCol = DisplayXY;
		if((vCaretRowCol.Column == 1) && (LineToRow(CaretY) != vCaretRowCol.Row))
		{
			fCaretAtEOL = true;
			UpdateLastCaretX();
		}
		else
		{
			if(vCaretRowCol.Column > CharsInWindow + 1)
			{
				++vCaretRowCol.Row;
				vCaretRowCol.Column = 1;
				InternalCaretXY = DisplayToBufferPos(vCaretRowCol);
			}
		}
	}
}

void __fastcall TCustomSynEdit::MoveCaretVert(int DY, bool SelectionCommand)
{
	TDisplayCoord ptO = {};
	TDisplayCoord ptDst = {};
	TDisplayCoord vEOLTestPos = {};
	TBufferCoord vDstLineChar = {};
	int SaveLastCaretX = 0;
	ptO = DisplayXY;
	ptDst = ptO;
	ptDst.Row += DY;
	if(DY >= 0)
	{
		if(RowToLine(ptDst.Row) > Lines->Count)
			ptDst.Row = Max(1, DisplayLineCount);
	}
	else
	{
		if(ptDst.Row < 1)
			ptDst.Row = 1;
	}
	if(ptO.Row != ptDst.Row)
	{
		if(Options.Contains(eoKeepCaretX))
			ptDst.Column = fLastCaretX;
	}
	vDstLineChar = DisplayToBufferPos(ptDst);
	SaveLastCaretX = fLastCaretX;

  // set caret and block begin / end
	IncPaintLock();
	MoveCaretAndSelection(fBlockBegin, vDstLineChar, SelectionCommand);
	if(WordWrap)
	{
		vEOLTestPos = BufferToDisplayPos(vDstLineChar);
		fCaretAtEOL = (vEOLTestPos.Column == 1) && (vEOLTestPos.Row != ptDst.Row);
	}
	DecPaintLock();

  // Restore fLastCaretX after moving caret, since UpdateLastCaretX, called by
  // SetCaretXYEx, changes them. This is the one case where we don't want that.
	fLastCaretX = SaveLastCaretX;
}

void __fastcall TCustomSynEdit::MoveCaretAndSelection(const TBufferCoord& ptBefore, const TBufferCoord& ptAfter, bool SelectionCommand)
{
	if((fOptions.Contains(eoGroupUndo)) && fUndoRedo->CanUndo)
		fUndoRedo->AddGroupBreak();
	IncPaintLock();
	if(SelectionCommand)
	{
		if(!SelAvail)
			SetBlockBegin(ptBefore);
		SetBlockEnd(ptAfter);
	}
	else
	SetBlockBegin(ptAfter);
	InternalCaretXY = ptAfter;
	DecPaintLock();
}

void __fastcall TCustomSynEdit::SetCaretAndSelection(const TBufferCoord& ptCaret, const TBufferCoord& ptBefore, const TBufferCoord& ptAfter)
{
	TSynSelectionMode vOldMode = smNormal;
	vOldMode = fActiveSelectionMode;
	IncPaintLock();
	try
	{
		InternalCaretXY = ptCaret;
		SetBlockBegin(ptBefore);
		SetBlockEnd(ptAfter);
	}
	__finally
	{
		ActiveSelectionMode = vOldMode;
		DecPaintLock();
	}
}

void __fastcall TCustomSynEdit::RecalcCharExtent()
{
	const TFontStyles iFontStyles[4/*# range 0..3*/] = {System::Set<TFontStyle, TFontStyle::fsBold, TFontStyle::fsStrikeOut>(), System::Set<TFontStyle, TFontStyle::fsBold, TFontStyle::fsStrikeOut>() << TFontStyle::fsItalic, System::Set<TFontStyle, TFontStyle::fsBold, TFontStyle::fsStrikeOut>() << TFontStyle::fsBold
                    , System::Set<TFontStyle, TFontStyle::fsBold, TFontStyle::fsStrikeOut>() << TFontStyle::fsItalic << TFontStyle::fsBold};
	bool iHasStyle[4/*# range 0..3*/];
	int cAttr = 0;
	int cStyle = 0;
	TFontStyles iCurr;
	int stop = 0;
	FillChar((void**)&iHasStyle, (int) sizeof(iHasStyle), 0);
	if(ASSIGNED(fHighlighter) && (fHighlighter->AttrCount > 0))
	{
		int stop = 0;
		for(stop = fHighlighter->AttrCount - 1, cAttr = 0; cAttr <= stop; cAttr++)
		{
			int stop1 = 0;
			iCurr = fHighlighter->Attribute[cAttr]->Style * Synedit__45;
			for(stop1 = 3, cStyle = 0; cStyle <= stop1; cStyle++)
			{
				if(iCurr == iFontStyles[cStyle])
				{
					iHasStyle[cStyle] = true;
					break;
				}
			}
		}
	}
	else
	{
		int stop = 0;
		iCurr = Font->Style * Synedit__46;
		for(stop = 3, cStyle = 0; cStyle <= stop; cStyle++)
		{
			if(iCurr == iFontStyles[cStyle])
			{
				iHasStyle[cStyle] = true;
				break;
			}
		}
	}
	fTextHeight = 0;
	fCharWidth = 0;
	fTextDrawer->BaseFont = this->Font;
	for(stop = 3, cStyle = 0; cStyle <= stop; cStyle++)
	{
		if(iHasStyle[cStyle])
		{
			fTextDrawer->BaseStyle = iFontStyles[cStyle];
			fTextHeight = Max(fTextHeight, fTextDrawer->CharHeight);
			fCharWidth = Max(fCharWidth, fTextDrawer->CharWidth);
		}
	}
	fTextHeight += fExtraLineSpacing;
}

void __fastcall TCustomSynEdit::HighlighterAttrChanged(TObject* Sender)
{
	RecalcCharExtent();
	if(ObjectIs(Sender, TSynCustomHighlighter*))
	{
		IncPaintLock();
		try
		{
			ScanRanges();
		}
		__finally
		{
			DecPaintLock();
		}
	}
	else
	Invalidate();
	SizeOrFontChanged(true);
}

void __fastcall TCustomSynEdit::StatusChanged(TSynStatusChanges AChanges)
{
	fStatusChanges = fStatusChanges + AChanges;
	if(PaintLock == 0)
		DoOnStatusChange(fStatusChanges);
}

void __fastcall TCustomSynEdit::ExecCmdCaseChange(TSynEditorCommand Cmd)
{

	auto ToggleCase = [&](const String aStr) -> String 
	{
		String result;
		int i = 0;
		String sLower;
		int stop = 0;
		result = d2c_system::TStringHelper(aStr).ToUpper();
		sLower = d2c_system::TStringHelper(aStr).ToLower();
		for(stop = aStr.Length(), i = 1; i <= stop; i++)
		{
			if(result[i] == aStr[i])
				result[i] = sLower[i];
		}
		return result;
	};

	auto TitleCase = [&](String S) -> String 
	{
		String result;
		int i = 0;
		int stop = 0;
		S[1] = ToUpper(S[1]);
		for(stop = S.Length() - 1, i = 1; i <= stop; i++)
		{
			if(IsWordBreakChar(S[i]))
				S[i + 1] = ToUpper(S[i + 1]);
			else
				S[i + 1] = ToLower(S[i + 1]);
		}
		result = S;
		return result;
	};
	String S;
	TBufferCoord oldCaret = {};
	TBufferCoord oldBlockBegin = {};
	TBufferCoord oldBlockEnd = {};
	Assert((Cmd >= Syneditkeycmds::ecUpperCase) && (Cmd <= ecTitleCase));
	if(ReadOnly)
		return;
	BeginUndoBlock();
	try
	{
		oldBlockBegin = BlockBegin;
		oldBlockEnd = BlockEnd;
		oldCaret = CaretXY;
		try
		{
			if(!SelAvail)
				SetSelWord();
			S = SelText;
			if(S != L"")
			{
				switch(Cmd)
				{
					case Syneditkeycmds::ecUpperCase:
					S = d2c_system::TStringHelper(S).ToUpper();
					break;
					case Syneditkeycmds::ecLowerCase:
					S = d2c_system::TStringHelper(S).ToLower();
					break;
					case ecToggleCase:
					S = ToggleCase(S);
					break;
					case ecTitleCase:
					S = TitleCase(S);
					break;
					default:
					  ;
					break;
				}
				SelText = S;
			}
		}
		__finally
		{
			SetCaretAndSelection(oldCaret, oldBlockBegin, oldBlockEnd);
		}
	}
	__finally
	{
		EndUndoBlock();
	}
}

void __fastcall TCustomSynEdit::DoTabKey()
{
	TBufferCoord StartOfBlock = {};
	int i = 0;
	int MinLen = 0;
	int iLine = 0;
	String PrevLine;
	String Spaces;
	PWideChar p = nullptr;
	int NewCaretX = 0;
	int nPhysX = 0;
	int nDistanceToTab = 0;
	int nSpacesToNextTabStop = 0;
	bool vIgnoreSmartTabs = false;
	bool TrimTrailingActive = false;
  // Provide Visual Studio like block indenting
	if((Options.Contains(eoTabIndent)) && (fBlockBegin.Line != fBlockEnd.Line))
	{
		DoBlockIndent();
		return;
	}
	i = 0;
	iLine = 0;
	MinLen = 0;
	vIgnoreSmartTabs = false;
	if(fOptions.Contains(eoSmartTabs))
	{
		iLine = CaretY - 1;
		if((iLine > 0) && (iLine < Lines->Count))
		{
			--iLine;
			do

        //todo: rethink it
			{
				MinLen = DisplayToBufferPos(DisplayCoord(BufferToDisplayPos(CaretXY).Column, LineToRow(iLine + 1))).Char;
				PrevLine = Lines->Strings[iLine];
				if(PrevLine.Length() >= MinLen)
				{
					p = ustr2pwchar(PrevLine, MinLen - 1);
          // scan over non-whitespaces
					do
					{
						if(((*p) == L'\x09') || ((*p) == L'\x20'))
							break;
						++i;
						++p;
					}
					while(!((*p) == L'\x00'));
          // scan over whitespaces
					if((*p) != L'\x00')
					{
						do
						{
							if(((*p) != L'\x09') && ((*p) != L'\x20'))
								break;
							++i;
							++p;
						}
						while(!((*p) == L'\x00'));
					}
					break;
				}
				--iLine;
			}
			while(!(iLine < 0));
		}
		else
		vIgnoreSmartTabs = true;
	}
	BeginUndoBlock();
	try
	{
		if(SelAvail)
			SetSelText(L"");
		StartOfBlock = CaretXY;
		if(i == 0)
		{
			if(fOptions.Contains(eoTabsToSpaces))
			{
				i = TabWidth - (StartOfBlock.Char - 1) % TabWidth;
				if(i == 0)
					i = TabWidth;
			}
			else
			i = TabWidth;
		}
		if(fOptions.Contains(eoTabsToSpaces))
		{
			Spaces = StringOfChar(L'\x20', i);
			NewCaretX = StartOfBlock.Char + i;
		}
		else
		{
			if((fOptions.Contains(eoSmartTabs)) && !vIgnoreSmartTabs && (iLine > -1))
			{
				Spaces = fLines->Strings[CaretXY.Line - 1].SubString(1, CaretXY.Char - 1);
				while(Pos(L"\x09", Spaces) > 0)
					Spaces.Delete(Pos(L"\x09", Spaces), 	1);
				Spaces = Trim(Spaces);

        //smart tabs are only in the front of the line *NOT IN THE MIDDLE*
				if(Spaces == L"")
				{
					i = BufferToDisplayPos(BufferCoord(MinLen + i, iLine + 1)).Column;
					nPhysX = DisplayX;
					nDistanceToTab = i - nPhysX;
					nSpacesToNextTabStop = TabWidth - ((nPhysX - 1) % TabWidth);
					if(nSpacesToNextTabStop <= nDistanceToTab)
					{
						Spaces = L"\x09";
						nDistanceToTab -= nSpacesToNextTabStop;
					}
					while(nDistanceToTab >= TabWidth)
					{
						Spaces = Spaces + L"\x09";
						nDistanceToTab -= TabWidth;
					}
					if(nDistanceToTab > 0)
						Spaces = Spaces + StringOfChar(L'\x20', nDistanceToTab);
				}
				else
				Spaces = L"\x09";
			}
			else
			{
				Spaces = L"\x09";
			}
			NewCaretX = StartOfBlock.Char + Spaces.Length();
		}
    // Do not Trim
		TrimTrailingActive = Options.Contains(eoTrimTrailingSpaces);
		if(TrimTrailingActive)
			fOptions >> eoTrimTrailingSpaces;
		SetSelText(Spaces);
		if(TrimTrailingActive)
			fOptions << eoTrimTrailingSpaces;
	}
	__finally
	{
		EndUndoBlock();
	}
	ForceCaretX(NewCaretX);
	EnsureCursorPosVisible();
}
// shift-tab key handling

void __fastcall TCustomSynEdit::DoShiftTabKey()
{
	int MaxLen = 0;
	int iLine = 0;
	String PrevLine;
	PWideChar p = nullptr;
	int SpaceCount1 = 0;
	int SpaceCount2 = 0;
	String TempS;
	String TempS2;
	if((Options.Contains(eoSmartTabs)) && !SelAvail)
	{
		iLine = CaretY - 1;
		if((iLine > 0) && (iLine < Lines->Count))
		{
			TempS = Lines->Strings[CaretY - 1];
			SpaceCount1 = LeftSpaces(TempS, true);
			if(SpaceCount1 == 0)
				return;
			--iLine;
			MaxLen = SpaceCount1;
			SpaceCount2 = 0;
			do
			{
				PrevLine = ((TSynEditStringList*) Lines)->ExpandedStrings[iLine];
				if((PrevLine.Length() > 0) && (PrevLine.Length() >= MaxLen))
				{
					p = ustr2pwchar(PrevLine, MaxLen - 1);
          // scan over whitespaces
					do
					{
						if((*p) != L'\x20')
							break;
						++SpaceCount2;
						--p;
					}
					while(!(SpaceCount2 == SpaceCount1));
          // scan over non-whitespaces
					if(SpaceCount2 < SpaceCount1)
					{
						do
						{
							if((*p) == L'\x20')
								break;
							++SpaceCount2;
							--p;
						}
						while(!(SpaceCount2 == SpaceCount1));
					}
					break;
				}
				--iLine;
			}
			while(!(iLine < 0));
			SpaceCount1 = LeftSpaces(TempS);
			TempS.Delete(1, 	SpaceCount1);
			TempS2 = GetLeftSpacing(SpaceCount1 - SpaceCount2, true);
			TempS = TempS2 + TempS;
			Lines->Strings[CaretY - 1] = TempS;
			CaretX = fCaretX + TempS2.Length() - SpaceCount1;
		}
	}
	else
	DoBlockUnindent();
}

void __fastcall TCustomSynEdit::DoHomeKey(bool Selection)
{

	auto LastCharInRow = [&]() -> int 
	{
		int result = 0;
		TDisplayCoord vPos = {};
		if(fLines->Count == 0)
			result = 1;
		else
		{
			vPos = DisplayXY;
			vPos.Column = Min(CharsInWindow, fWordWrapPlugin->GetRowLength(vPos.Row) + 1);
			result = DisplayToBufferPos(vPos).Char;
		}
		return result;
	};
	int newX = 0;
	int first_nonblank = 0;
	String s;
	TDisplayCoord vNewPos = {};
	int vMaxX = 0;
  // home key enhancement
	if((fOptions.Contains(eoEnhanceHomeKey)) && (LineToRow(CaretY) == DisplayY))
	{
		s = fLines->Strings[CaretXY.Line - 1];
		first_nonblank = 1;
		if(WordWrap)
			vMaxX = LastCharInRow() - 1;
		else
			vMaxX = s.Length();
		while((first_nonblank <= vMaxX) && CharInSet(s[first_nonblank], Synedit__47))
			++first_nonblank;
		--first_nonblank;
		newX = CaretXY.Char - 1;
		if((newX > first_nonblank) || (newX == 0))
			newX = first_nonblank + 1;
		else
			newX = 1;
	}
	else
	newX = 1;
	if(WordWrap)
	{
		vNewPos.Row = DisplayY;
		vNewPos.Column = BufferToDisplayPos(BufferCoord(newX, CaretY)).Column;
		MoveCaretAndSelection(CaretXY, DisplayToBufferPos(vNewPos), Selection);
	}
	else
	MoveCaretAndSelection(CaretXY, BufferCoord(newX, CaretY), Selection);
}

void __fastcall TCustomSynEdit::DoEndKey(bool Selection)
{

	auto CaretInLastRow = [&]() -> bool 
	{
		bool result = false;
		int vLastRow = 0;
		if(!WordWrap)
			result = true;
		else
		{
			vLastRow = LineToRow(CaretY + 1) - 1;
      // This check allows good behaviour with empty rows (this can be useful in a diff app ;-)
			while((vLastRow > 1) && (fWordWrapPlugin->GetRowLength(vLastRow) == 0) && (RowToLine(vLastRow) == CaretY))
			{
				--vLastRow;
			}
			result = DisplayY == vLastRow;
		}
		return result;
	};

	auto FirstCharInRow = [&]() -> int 
	{
		int result = 0;
		TDisplayCoord vPos = {};
		vPos.Row = DisplayY;
		vPos.Column = 1;
		result = DisplayToBufferPos(vPos).Char;
		return result;
	};
	String vText;
	int vLastNonBlank = 0;
	int vNewX = 0;
	TDisplayCoord vNewCaret = {};
	int vMinX = 0;
	bool vEnhance = false;
	if((fOptions.Contains(eoEnhanceEndKey)) && CaretInLastRow())
	{
		vEnhance = true;
		vText = LineText;
		vLastNonBlank = vText.Length();
		if(WordWrap)
			vMinX = FirstCharInRow() - 1;
		else
			vMinX = 0;
		while((vLastNonBlank > vMinX) && CharInSet(vText[vLastNonBlank], Synedit__48))
			--vLastNonBlank;
		vNewX = CaretX - 1;
		if(vNewX == vLastNonBlank)
			vNewX = LineText.Length() + 1;
		else
			vNewX = vLastNonBlank + 1;
	}
	else
	{
		vNewX = LineText.Length() + 1;
		vEnhance = false;
	}
	if(WordWrap)
	{
		vNewCaret.Row = DisplayY;
		if(vEnhance)
			vNewCaret.Column = BufferToDisplayPos(BufferCoord(vNewX, CaretY)).Column;
		else
			vNewCaret.Column = fWordWrapPlugin->GetRowLength(vNewCaret.Row) + 1;
		vNewCaret.Column = Min(CharsInWindow + 1, vNewCaret.Column);
		MoveCaretAndSelection(CaretXY, DisplayToBufferPos(vNewCaret), Selection);
    // Updates fCaretAtEOL flag.
		SetInternalDisplayXY(vNewCaret);
	}
	else
	MoveCaretAndSelection(CaretXY, BufferCoord(vNewX, CaretY), Selection);
}

void __fastcall TCustomSynEdit::CreateWnd()
{
	TSynDropTarget* DropTarget = nullptr;
	inherited::CreateWnd();
  //  This is to avoid getting the text of the control while recreating
	WindowText = StrNew(L"SynEdit");  // dummy caption
	if((fOptions.Contains(eoDropFiles)) && !(ComponentState.Contains(csDesigning)))
		DragAcceptFiles(Handle, true);
	if(!(ComponentState.Contains(csDesigning)))
	{
		DropTarget = new TSynDropTarget();
		/*# with DropTarget do */
		{
			auto with0 = DropTarget;
			with0->OnDragEnter = OleDragEnter;
			with0->OnDragOver = OleDragOver;
			with0->OnDragLeave = OleDragLeave;
			with0->OnDrop = OleDrop;
		}
		RegisterDragDrop(Handle, DropTarget);
	}
	UpdateScrollBars();
}

void __fastcall TCustomSynEdit::InvalidateRect(const TRect& aRect, bool aErase)
{
	::InvalidateRect(Handle, &aRect, aErase);
}

void __fastcall TCustomSynEdit::DoBlockIndent()
{
	TBufferCoord OrgCaretPos = {};
	TBufferCoord BB = {};
	TBufferCoord BE = {};
	String Line;
	int EndLine = 0;
	__int64 I = 0;
	String Spaces;
	int InsertPos = 0;
	OrgCaretPos = CaretXY;

  // keep current selection detail
	BB = BlockBegin;
	BE = BlockEnd;

  // build text to insert
	if(BE.Char == 1)
		EndLine = BE.Line - 1;
	else
		EndLine = BE.Line;
	if(Options.Contains(eoTabsToSpaces))
		Spaces = StringOfChar(L'\x20', fTabWidth);
	else
		Spaces = L"\x09";
	Lines->BeginUpdate();
	BeginUndoBlock();
	try
	{
		__int64 stop = 0;
		for(stop = EndLine, I = BB.Line; I <= stop; I++)
		{
			Line = Lines->Strings[I - 1];
			if(fActiveSelectionMode == smColumn)
				InsertPos = Min(BB.Char, BE.Char);
			else
				InsertPos = 1;
			if(Line.Length() >= InsertPos)
			{
				Line.Insert(Spaces,	InsertPos);
				Lines->Strings[I - 1] = Line;
			}
		}
		if(OrgCaretPos.Char > 1)
			OrgCaretPos.Char += Spaces.Length();
		if(BB.Char > 1)
			BB.Char += Spaces.Length();
		if(BE.Char > 1)
			BE.Char += Spaces.Length();
		SetCaretAndSelection(OrgCaretPos, BB, BE);
	}
	__finally
	{
		EndUndoBlock();
		Lines->EndUpdate();
	}
}

void __fastcall TCustomSynEdit::DoBlockUnindent()
{

	auto GetDelLen = [&](PChar Line) -> int 
	{
		int result = 0;
		PChar Run = nullptr;
		result = 0;
		Run = Line;
    //Take care of tab character
		if(Run[0] == L'\x09')
			return 1;
    //Deal with compound tabwidths  Sometimes they have TabChars after a few
    //spaces, yet we need to delete the whole tab width even though the char
    //count might not be FTabWidth because of the TabChar
		while((Run[0] == L'\x20') && (result < fTabWidth))
		{
			++result;
			++Run;
		}
		if((Run[0] == L'\x09') && (result < fTabWidth))
			++result;
		return result;
	};
	TBufferCoord OrgCaretPos = {};
	TBufferCoord BB = {};
	TBufferCoord BE = {};
	String Line;
	PChar PLine = nullptr;
	int EndLine = 0;
	__int64 I = 0;
	int TmpDelLen = 0;
	int DelPos = 0;
	BB = BlockBegin;
	BE = BlockEnd;
	OrgCaretPos = CaretXY;

  // convert selection to complete lines
	if(BE.Char == 1)
		EndLine = BE.Line - 1;
	else
		EndLine = BE.Line;
	Lines->BeginUpdate();
	BeginUndoBlock();
	try
	{
		__int64 stop = 0;
		for(stop = EndLine, I = BB.Line; I <= stop; I++)
		{
			Line = Lines->Strings[I - 1];
      //Instead of doing a StringofChar, we need to get *exactly* what was
      //being deleted incase there is a TabChar
			PLine = ustr2pwchar(Line);
			if(fActiveSelectionMode == smColumn)
				PLine += MinIntValue(OPENARRAY(int, (BB.Char - 1, BE.Char - 1, Line.Length())));
			TmpDelLen = GetDelLen(PLine);
			if(TmpDelLen > 0)
			{
				if(fActiveSelectionMode == smColumn)
					DelPos = Min(BB.Char, BE.Char);
				else
					DelPos = 1;
				Line.Delete(DelPos, 	TmpDelLen);
				Lines->Strings[I - 1] = Line;
				if(fActiveSelectionMode != smColumn)
				{
					if(I == BB.Line)
						BB.Char = Max(BB.Char - TmpDelLen, 1);
					if(I == BE.Line)
						BE.Char = Max(BE.Char - TmpDelLen, 1);
					if(I == OrgCaretPos.Line)
						OrgCaretPos.Char = Max(OrgCaretPos.Char - TmpDelLen, 1);
				}
			}
		}
		SetCaretAndSelection(OrgCaretPos, BB, BE);
	}
	__finally
	{
		EndUndoBlock();
		Lines->EndUpdate();
	}
}

bool __fastcall TCustomSynEdit::ExecuteAction(TBasicAction* Action)
{
	bool result = false;
	if(ObjectIs(Action, TEditAction*))
	{
		result = Focused();
		if(result)
		{
			if(ObjectIs(Action, TEditCut*))
				CommandProcessor((TSynEditorCommand) ecCut, L' ', nullptr);
			else
			{
				if(ObjectIs(Action, TEditCopy*))
					CommandProcessor((TSynEditorCommand) ecCopy, L' ', nullptr);
				else
				{
					if(ObjectIs(Action, TEditPaste*))
						CommandProcessor((TSynEditorCommand) ecPaste, L' ', nullptr);
					else
					{
						if(ObjectIs(Action, TEditDelete*))
						{
							if(SelAvail)
								ClearSelection();
							else
								CommandProcessor((TSynEditorCommand) ecDeleteChar, L' ', nullptr);
						}
						else
						{
							if(ObjectIs(Action, TEditUndo*))
								CommandProcessor((TSynEditorCommand) ecUndo, L' ', nullptr);
							else
							{
								if(ObjectIs(Action, TEditSelectAll*))
									CommandProcessor((TSynEditorCommand) ecSelectAll, L' ', nullptr);
							}
						}
					}
				}
			}
		}
	}
	else
	{
		if(ObjectIs(Action, TSearchAction*))
		{
			result = Focused();
			if(ObjectIs(Action, TSearchFindFirst*))
				DoSearchFindFirstExecute(((TSearchFindFirst*) Action));
			else
			{
				if(ObjectIs(Action, TSearchFind*))
					DoSearchFindExecute(((TSearchFind*) Action));
				else
				{
					if(ObjectIs(Action, TSearchReplace*))
						DoSearchReplaceExecute(((TSearchReplace*) Action));
				}
			}
		}
		else
		{
			if(ObjectIs(Action, TSearchFindNext*))
			{
				result = Focused();
				DoSearchFindNextExecute(((TSearchFindNext*) Action));
			}
			else
			result = inherited::ExecuteAction(Action);
		}
	}
	return result;
}

bool __fastcall TCustomSynEdit::UpdateAction(TBasicAction* Action)
{
	bool result = false;
	if(ObjectIs(Action, TEditAction*))
	{
		result = Focused();
		if(result)
		{
			if(ObjectIs(Action, TEditCut*))
				((TEditAction*) Action)->Enabled = SelAvail && !ReadOnly;
			else
			{
				if(ObjectIs(Action, TEditCopy*))
					((TEditAction*) Action)->Enabled = SelAvail;
				else
				{
					if(ObjectIs(Action, TEditPaste*))
						((TEditAction*) Action)->Enabled = CanPaste;
					else
					{
						if(ObjectIs(Action, TEditDelete*))
							((TEditAction*) Action)->Enabled = !ReadOnly;
						else
						{
							if(ObjectIs(Action, TEditUndo*))
								((TEditAction*) Action)->Enabled = CanUndo;
							else
							{
								if(ObjectIs(Action, TEditSelectAll*))
									((TEditAction*) Action)->Enabled = true;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		if(ObjectIs(Action, TSearchAction*))
		{
			result = Focused();
			if(result)
			{
				if(ObjectIs(Action, TSearchFindFirst*))
					((TSearchAction*) Action)->Enabled = (Text != L"") && ASSIGNED(fSearchEngine);
				else
				{
					if(ObjectIs(Action, TSearchFind*))
						((TSearchAction*) Action)->Enabled = (Text != L"") && ASSIGNED(fSearchEngine);
					else
					{
						if(ObjectIs(Action, TSearchReplace*))
							((TSearchAction*) Action)->Enabled = (Text != L"") && ASSIGNED(fSearchEngine);
					}
				}
			}
		}
		else
		{
			if(ObjectIs(Action, TSearchFindNext*))
			{
				result = Focused();
				if(result)
					((TSearchAction*) Action)->Enabled = (Text != L"") && (((TSearchFindNext*) Action)->SearchFind != nullptr) && (((TSearchFindNext*) Action)->SearchFind->Dialog->FindText != L"");
			}
			else
			result = inherited::UpdateAction(Action);
		}
	}
	return result;
}

void __fastcall TCustomSynEdit::SetModified(bool Value)
{
	if(Value != fUndoRedo->Modified)
	{
		fUndoRedo->Modified = Value;
		if((Options.Contains(eoGroupUndo)) && (!Value) && fUndoRedo->CanUndo)
			fUndoRedo->AddGroupBreak();
		StatusChanged(Synedit__49);
	}
}

bool __fastcall TCustomSynEdit::DoOnSpecialLineColors(int Line, TColor& Foreground, TColor& Background)
{
	bool result = false;
	result = false;
	if(ASSIGNED(fOnSpecialLineColors))
		fOnSpecialLineColors(this, Line, result, Foreground, Background);
	return result;
}

void __fastcall TCustomSynEdit::InvalidateLine(int Line)
{
	TRect rcInval = {};
	if((!HandleAllocated()) || (Line < 1) || (Line > Lines->Count) || (!Visible))
		return;

//++ CodeFolding
	if(UseCodeFolding || WordWrap)
//-- CodeFolding
	{
		InvalidateLines(Line, Line);
		return;
	}
	if((Line >= TopLine) && (Line <= TopLine + LinesInWindow))
    // invalidate text area of this line
	{
		rcInval = Rect(fGutterWidth, fTextHeight * (Line - TopLine), ClientWidth, 0);
		rcInval.Bottom = rcInval.Top + fTextHeight;
		if(fStateFlags.Contains(sfLinesChanging))
//++ Flicker Reduction

//-- Flicker Reduction
			UnionRect(fInvalidateRect, rcInval, fInvalidateRect);
		else
			InvalidateRect(rcInval, false);
	}
}

bool __fastcall TCustomSynEdit::GetReadOnly()
{
	bool result = false;
	result = fReadOnly;
	return result;
}

void __fastcall TCustomSynEdit::SetReadOnly(bool Value)
{
	if(fReadOnly != Value)
	{
		fReadOnly = Value;
		StatusChanged(Synedit__50);
	}
}

void __fastcall TCustomSynEdit::FindMatchingBracket()
{
	InternalCaretXY = GetMatchingBracket();
}

TBufferCoord __fastcall TCustomSynEdit::GetMatchingBracket()
{
	TBufferCoord result = {};
	result = GetMatchingBracketEx(CaretXY);
	return result;
}

TBufferCoord __fastcall TCustomSynEdit::GetMatchingBracketEx(const TBufferCoord& APoint, String Brackets/*# = '()[]{}<>'*/)
{
	TBufferCoord result = {};
	String Line;
	int Index = 0;
	int PosX = 0;
	int PosY = 0;
	int Len = 0;
	WideChar Test = L'\0';
	WideChar BracketInc = L'\0';
	WideChar BracketDec = L'\0';
	int NumBrackets = 0;
	String vDummy;
	TSynHighlighterAttributes* attr = nullptr;
	TBufferCoord p = {};
	bool isCommentOrString = false;
	result.Char = 0;
	result.Line = 0;
  // get char at caret
	PosX = APoint.Char;
	PosY = APoint.Line;
	Line = Lines->Strings[APoint.Line - 1];
	if(Line.Length() >= PosX)
	{
		Test = Line[PosX];
    // is it one of the recognized brackets?
// strange linker error		Index = d2c_system::TStringHelper(Brackets).IndexOf(Test);  // zero based
		Index = (int) (Brackets.Pos(String(Test)) - 1);
		if(Index >= 0)
      // this is the bracket, get the matching one and the direction
		{
// strange linker error
//			BracketInc = d2c_system::TStringHelper(Brackets).Chars[Index];
//			BracketDec = d2c_system::TStringHelper(Brackets).Chars[Index ^ 1]; // 0 -> 1, 1 -> 0, ...
			BracketInc = Brackets[Index + 1];
			BracketDec = Brackets[(Index ^ 1) + 1]; // 0 -> 1, 1 -> 0, ...
			// search for the matching bracket (that is until NumBrackets = 0)
			NumBrackets = 1;
			if(Odd(Index))
			{
				do

          // search until start of line
				{
					while(PosX > 1)
					{
						--PosX;
						Test = Line[PosX];
						p.Char = PosX;
						p.Line = PosY;
						if((Test == BracketInc) || (Test == BracketDec))
						{
							if(GetHighlighterAttriAtRowCol(p, vDummy, attr))
								isCommentOrString = (attr == Highlighter->StringAttribute) || (attr == Highlighter->CommentAttribute);
							else
								isCommentOrString = false;
							if((Test == BracketInc) && (!isCommentOrString))
								++NumBrackets;
							else
							{
								if((Test == BracketDec) && (!isCommentOrString))
								{
									--NumBrackets;
									if(NumBrackets == 0)
                  // matching bracket found, set caret and bail out
									{
										result = p;
										return result;
									}
								}
							}
						}
					}
          // get previous line if possible
					if(PosY == 1)
						break;
					--PosY;
					Line = Lines->Strings[PosY - 1];
					PosX = Line.Length() + 1;
				}
				while(!false);
			}
			else
			{
				do

          // search until end of line
				{
					Len = Line.Length();
					while(PosX < Len)
					{
						++PosX;
						Test = Line[PosX];
						p.Char = PosX;
						p.Line = PosY;
						if((Test == BracketInc) || (Test == BracketDec))
						{
							if(GetHighlighterAttriAtRowCol(p, vDummy, attr))
								isCommentOrString = (attr == Highlighter->StringAttribute) || (attr == Highlighter->CommentAttribute);
							else
								isCommentOrString = false;
							if((Test == BracketInc) && (!isCommentOrString))
								++NumBrackets;
							else
							{
								if((Test == BracketDec) && (!isCommentOrString))
								{
									--NumBrackets;
									if(NumBrackets == 0)
                  // matching bracket found, set caret and bail out
									{
										result = p;
										return result;
									}
								}
							}
						}
					}
          // get next line if possible
					if(PosY == Lines->Count)
						break;
					++PosY;
					Line = Lines->Strings[PosY - 1];
					PosX = 0;
				}
				while(!false);
			}
		}
	}
	return result;
}

bool __fastcall TCustomSynEdit::GetHighlighterAttriAtRowCol(const TBufferCoord& XY, String& Token, TSynHighlighterAttributes*& Attri)
{
	bool result = false;
	int TmpType = 0;
	int TmpStart = 0;
	result = GetHighlighterAttriAtRowColEx(XY, Token, TmpType, TmpStart, Attri);
	return result;
}

bool __fastcall TCustomSynEdit::GetHighlighterAttriAtRowColEx(const TBufferCoord& XY, String& Token, int& TokenType, int& Start, TSynHighlighterAttributes*& Attri)
{
	bool result = false;
	int PosX = 0;
	int PosY = 0;
	String Line;
	PosY = XY.Line - 1;
	if(ASSIGNED(Highlighter) && (PosY >= 0) && (PosY < Lines->Count))
	{
		Line = Lines->Strings[PosY];
		if(PosY == 0)
			Highlighter->ResetRange();
		else
			Highlighter->SetRange(((TSynEditStringList*) Lines)->Ranges[PosY - 1]);
		Highlighter->SetLine(Line, PosY);
		PosX = XY.Char;
		if((PosX > 0) && (PosX <= Line.Length()))
		{
			while(!Highlighter->GetEol())
			{
				Start = Highlighter->GetTokenPos() + 1;
				Token = Highlighter->GetToken();
				if((PosX >= Start) && (PosX < Start + Token.Length()))
				{
					Attri = Highlighter->GetTokenAttribute();
					TokenType = Highlighter->GetTokenKind();
					result = true;
					return result;
				}
				Highlighter->Next();
			}
		}
	}
	Token = L"";
	Attri = nullptr;
	result = false;
	return result;
}

int __fastcall TCustomSynEdit::FindHookedCmdEvent(THookedCommandEvent AHandlerProc)
{
	int result = 0;
	THookedCommandHandlerEntry* Entry = nullptr;
	result = GetHookedCommandHandlersCount() - 1;
	while(result >= 0)
	{
		Entry = ((THookedCommandHandlerEntry*) fHookedCommandHandlers->Items[result]);
		if(Entry->Equals(AHandlerProc))
			break;
		--result;
	}
	return result;
}

int __fastcall TCustomSynEdit::GetHookedCommandHandlersCount()
{
	int result = 0;
	if(ASSIGNED(fHookedCommandHandlers))
		result = fHookedCommandHandlers->Count;
	else
		result = 0;
	return result;
}

void __fastcall TCustomSynEdit::RegisterCommandHandler(const THookedCommandEvent AHandlerProc, void* AHandlerData)
{
	if(!ASSIGNED(AHandlerProc))
	{
		return;
	}
	if(!ASSIGNED(fHookedCommandHandlers))
		fHookedCommandHandlers = new TObjectList();
	if(FindHookedCmdEvent(AHandlerProc) == -1)
		fHookedCommandHandlers->Add(new THookedCommandHandlerEntry(AHandlerProc, AHandlerData));
	else
		;
}

void __fastcall TCustomSynEdit::UnregisterCommandHandler(THookedCommandEvent AHandlerProc)
{
	int i = 0;
	if(!ASSIGNED(AHandlerProc))
	{
		return;
	}
	i = FindHookedCmdEvent(AHandlerProc);
	if(i > -1)
		fHookedCommandHandlers->Delete(i);
	else
		;
}

void __fastcall TCustomSynEdit::NotifyHookedCommandHandlers(bool AfterProcessing, TSynEditorCommand& Command, WideChar& AChar, void* Data)
{
	bool Handled = false;
	int i = 0;
	THookedCommandHandlerEntry* Entry = nullptr;
	int stop = 0;
	Handled = false;
	for(stop = GetHookedCommandHandlersCount() - 1, i = 0; i <= stop; i++)
	{
		Entry = ((THookedCommandHandlerEntry*) fHookedCommandHandlers->Items[i]);
    // NOTE: Command should NOT be set to ecNone, because this might interfere
    // with other handlers.  Set Handled to False instead (and check its value
    // to not process the command twice).
		Entry->fEvent(this, AfterProcessing, Handled, Command, AChar, Data, Entry->fData);
	}
	if(Handled)
		Command = (TSynEditorCommand) ecNone;
}

void __fastcall TCustomSynEdit::DoOnClearBookmark(TSynEditMark*& Mark)
{
	if(ASSIGNED(fOnClearMark))
		fOnClearMark(this, Mark);
}

void __fastcall TCustomSynEdit::DoOnPaintTransientEx(TTransientType TransientType, bool Lock)
{
	bool DoTransient = false;
	int i = 0;
	TSynEditPlugin* Plugin = nullptr;
	DoTransient = (FPaintTransientLock == 0);
	if(Lock)
	{
		if(TransientType == ttBefore)
			++FPaintTransientLock;
		else
		{
			--FPaintTransientLock;
			DoTransient = FPaintTransientLock == 0;
		}
	}
	if(DoTransient)
  // plugins
	{
		if(fPlugins != nullptr)
		{
			int stop = 0;
			for(stop = fPlugins->Count - 1, i = 0; i <= stop; i++)
			{
				Plugin = ((TSynEditPlugin*) fPlugins->Items[i]);
				if(Plugin->Handlers.Contains(phPaintTransient))
					Plugin->PaintTransient(Canvas, TransientType);
			}
    // event
		}
		if(ASSIGNED(fOnPaintTransient))
		{
			Canvas->Font->Assign(Font);
			Canvas->Brush->Color = Color;
			HideCaret();
			try
			{
				fOnPaintTransient(this, Canvas, TransientType);
			}
			__finally
			{
				ShowCaret();
			}
		}
	}
}

void __fastcall TCustomSynEdit::DoOnPaintTransient(TTransientType TransientType)
{
	DoOnPaintTransientEx(TransientType, false);
}

void __fastcall TCustomSynEdit::DoOnPaint()
{
	if(ASSIGNED(fOnPaint))
	{
		Canvas->Font->Assign(Font);
		Canvas->Brush->Color = Color;
		fOnPaint(this, Canvas);
	}
}

void __fastcall TCustomSynEdit::DoOnPlaceMark(TSynEditMark*& Mark)
{
	if(ASSIGNED(fOnPlaceMark))
		fOnPlaceMark(this, Mark);
}

TSynReplaceAction __fastcall TCustomSynEdit::DoOnReplaceText(const String ASearch, const String AReplace, int Line, int Column)
{
	TSynReplaceAction result = raCancel;
	result = raCancel;
	if(ASSIGNED(fOnReplaceText))
		fOnReplaceText(this, ASearch, AReplace, Line, Column, result);
	return result;
}

void __fastcall TCustomSynEdit::DoOnStatusChange(TSynStatusChanges Changes)
{
	if(ASSIGNED(fOnStatusChange))
	{
		fOnStatusChange(this, fStatusChanges);
		fStatusChanges = Synedit__51;
	}
}

void __fastcall TCustomSynEdit::ModifiedChanged(TObject* Sender)
{
	StatusChanged(Synedit__52);
}

String __fastcall TCustomSynEdit::GetWordAtRowCol(const TBufferCoord& cXY)
{
	TBufferCoord XY = cXY;
	String result;
	String Line;
	int Len = 0;
	int Start = 0;
	int Stop = 0;
	result = L"";
	if((XY.Line >= 1) && (XY.Line <= Lines->Count))
	{
		Line = Lines->Strings[XY.Line - 1];
		Len = Line.Length();
		if((Len > 0) && InRange(XY.Char, 1, Len + 1))
		{
			Start = XY.Char;
			while((Start > 1) && IsIdentChar(Line[Start - 1]))
				--Start;
			Stop = XY.Char;
			while((Stop <= Len) && IsIdentChar(Line[Stop]))
				++Stop;
			result = Line.SubString(Start, Stop - Start);
		}
	}
	return result;
}
// BufferToDisplayPos takes a position in the text and transforms it into
// the row and column it appears to be on the screen

TDisplayCoord __fastcall TCustomSynEdit::BufferToDisplayPos(const TBufferCoord& p)
{
	TDisplayCoord result = {};
	String s;
	int i = 0;
	int L = 0;
	int x = 0;
	int CountOfAvgGlyphs = 0;
	result = *(TDisplayCoord*)&p;
	if(p.Line - 1 < Lines->Count)
	{
		int stop = 0;
		s = Lines->Strings[p.Line - 1];
		L = s.Length();
		x = 0;
		for(stop = p.Char - 1, i = 1; i <= stop; i++)
		{
			if((i <= L) && (s[i] == L'\x09'))
				x += TabWidth - (x % TabWidth);
			else
			{
				if(i <= L)
				{
					if(int(s[i]) <= 0x00FF)
						CountOfAvgGlyphs = 1;
					else
						CountOfAvgGlyphs = (int) CeilOfIntDiv((unsigned int) fTextDrawer->TextWidth(String(s[i])), (WORD) fCharWidth);
					x += CountOfAvgGlyphs;
				}
				else
				++x;
			}
		}
		result.Column = x + 1;
	}
	if(WordWrap)
		result = fWordWrapPlugin->BufferToDisplayPos(*(TBufferCoord*)&result);
//++ CodeFolding
	if(UseCodeFolding)
//-- CodeFolding
		result.Row = fAllFoldRanges->FoldLineToRow(result.Row);
	return result;
}
// DisplayToBufferPos takes a position on screen and transfrom it
// into position of text

TBufferCoord __fastcall TCustomSynEdit::DisplayToBufferPos(const TDisplayCoord& p)
{
	TBufferCoord result = {};
	String s;
	int i = 0;
	int L = 0;
	int x = 0;
	int CountOfAvgGlyphs = 0;
	if(WordWrap)
		result = fWordWrapPlugin->DisplayToBufferPos(p);
	else
		result = *(TBufferCoord*)&p;
//++ CodeFolding
	if(UseCodeFolding)
		result.Line = fAllFoldRanges->FoldRowToLine(p.Row);
//-- CodeFolding
	if(result.Line <= Lines->Count)
	{
		s = Lines->Strings[result.Line - 1];
		L = s.Length();
		x = 0;
		i = 0;
		while(x < result.Char)
		{
			++i;
			if((i <= L) && (s[i] == L'\x09'))
				x += TabWidth - (x % TabWidth);
			else
			{
				if(i <= L)
				{
					if(int(s[i]) <= 0x00FF)
						CountOfAvgGlyphs = 1;
					else
						CountOfAvgGlyphs = (int) CeilOfIntDiv((unsigned int) fTextDrawer->TextWidth(String(s[i])), (WORD) fCharWidth);
					x += CountOfAvgGlyphs;
				}
				else
				++x;
			}
		}
		result.Char = i;
	}
	return result;
}

void __fastcall TCustomSynEdit::DoLinesBeforeDeleted(int FirstLine, int Count)
{
	int i = 0;
	TSynEditPlugin* Plugin = nullptr;
  // plugins
	if(fPlugins != nullptr)
	{
		int stop = 0;
		for(stop = fPlugins->Count - 1, i = 0; i <= stop; i++)
		{
			Plugin = ((TSynEditPlugin*) fPlugins->Items[i]);
			if(Plugin->Handlers.Contains(phLinesBeforeDeleted))
				Plugin->LinesBeforeDeleted(FirstLine, Count);
		}
	}
}

void __fastcall TCustomSynEdit::DoLinesChanged()
{
	int i = 0;
	TSynEditPlugin* Plugin = nullptr;
  // plugins
	if(fPlugins != nullptr)
	{
		int stop = 0;
		for(stop = fPlugins->Count - 1, i = 0; i <= stop; i++)
		{
			Plugin = ((TSynEditPlugin*) fPlugins->Items[i]);
			if(Plugin->Handlers.Contains(phLinesChanged))
				Plugin->LinesChanged();
		}
	}
}

void __fastcall TCustomSynEdit::DoLinesDeleted(int FirstLine, int Count)
{
	int i = 0;
	TSynEditPlugin* Plugin = nullptr;
	int stop = 0;
	fGutter->AutoSizeDigitCount();

  // gutter marks
	for(stop = Marks->Count - 1, i = 0; i <= stop; i++)
	{
		if(Marks->Items[i]->Line >= FirstLine + Count)
			Marks->Items[i]->Line = Marks->Items[i]->Line - Count;
		else
		{
			if(Marks->Items[i]->Line > FirstLine)
				Marks->Items[i]->Line = FirstLine;
		}
	}

  // plugins
	if(fPlugins != nullptr)
	{
		int stop = 0;
		for(stop = fPlugins->Count - 1, i = 0; i <= stop; i++)
		{
			Plugin = ((TSynEditPlugin*) fPlugins->Items[i]);
			if(Plugin->Handlers.Contains(phLinesDeleted))
				Plugin->LinesDeleted(FirstLine, Count);
		}
	}
}

void __fastcall TCustomSynEdit::DoLinesInserted(int FirstLine, int Count)
{
	int i = 0;
	TSynEditPlugin* Plugin = nullptr;
	int stop = 0;
	fGutter->AutoSizeDigitCount();
  // gutter marks
	for(stop = Marks->Count - 1, i = 0; i <= stop; i++)
	{
		if(Marks->Items[i]->Line >= FirstLine)
			Marks->Items[i]->Line = Marks->Items[i]->Line + Count;
	}

  // plugins
	if(fPlugins != nullptr)
	{
		int stop = 0;
		for(stop = fPlugins->Count - 1, i = 0; i <= stop; i++)
		{
			Plugin = ((TSynEditPlugin*) fPlugins->Items[i]);
			if(Plugin->Handlers.Contains(phLinesInserted))
				Plugin->LinesInserted(FirstLine, Count);
		}
	}
}

void __fastcall TCustomSynEdit::DoLinePut(int FirstLine, const String OldLine)
{
	int i = 0;
	TSynEditPlugin* Plugin = nullptr;
  // plugins
	if(fPlugins != nullptr)
	{
		int stop = 0;
		for(stop = fPlugins->Count - 1, i = 0; i <= stop; i++)
		{
			Plugin = ((TSynEditPlugin*) fPlugins->Items[i]);
			if(Plugin->Handlers.Contains(phLinePut))
				Plugin->LinePut(FirstLine, OldLine);
		}
	}
}

void __fastcall TCustomSynEdit::PluginsAfterPaint(TCanvas* ACanvas, const TRect& AClip, int FirstLine, int LastLine)
{
	int i = 0;
	TSynEditPlugin* Plugin = nullptr;
	if(fPlugins != nullptr)
	{
		int stop = 0;
		for(stop = fPlugins->Count - 1, i = 0; i <= stop; i++)
		{
			Plugin = ((TSynEditPlugin*) fPlugins->Items[i]);
			if(Plugin->Handlers.Contains(phAfterPaint))
				Plugin->AfterPaint(ACanvas, AClip, FirstLine, LastLine);
		}
	}
}

void __fastcall TCustomSynEdit::ProperSetLine(int ALine, const String ALineText)
{
	if(Options.Contains(eoTrimTrailingSpaces))
		Lines->Strings[ALine] = TrimTrailingSpaces(ALineText);
	else
		Lines->Strings[ALine] = ALineText;
}

void __fastcall TCustomSynEdit::QuadrupleClick()
{
	if(!(fOptions.Contains(eoNoSelection)))
		SelectAll();
	if(ASSIGNED(fOnQudrupleClick))
		fOnQudrupleClick(this);
}

void __fastcall TCustomSynEdit::AddKeyUpHandler(TKeyEvent aHandler)
{
	fKbdHandler->AddKeyUpHandler(aHandler);
}

void __fastcall TCustomSynEdit::RemoveKeyUpHandler(TKeyEvent aHandler)
{
	fKbdHandler->RemoveKeyUpHandler(aHandler);
}

void __fastcall TCustomSynEdit::AddKeyDownHandler(TKeyEvent aHandler)
{
	fKbdHandler->AddKeyDownHandler(aHandler);
}

void __fastcall TCustomSynEdit::RemoveKeyDownHandler(TKeyEvent aHandler)
{
	fKbdHandler->RemoveKeyDownHandler(aHandler);
}

void __fastcall TCustomSynEdit::AddKeyPressHandler(TKeyPressEvent aHandler)
{
	fKbdHandler->AddKeyPressHandler(aHandler);
}

void __fastcall TCustomSynEdit::RemoveKeyPressHandler(TKeyPressEvent aHandler)
{
	fKbdHandler->RemoveKeyPressHandler(aHandler);
}

void __fastcall TCustomSynEdit::AddFocusControl(TWinControl* aControl)
{
	fFocusList->Add(aControl);
}

void __fastcall TCustomSynEdit::RemoveFocusControl(TWinControl* aControl)
{
	fFocusList->Remove(aControl);
}

bool __fastcall TCustomSynEdit::IsIdentChar(WideChar AChar)
{
	bool result = false;
	if(ASSIGNED(Highlighter))
		result = Highlighter->IsIdentChar(AChar);
	else
	{
		switch(AChar)
		{
			case L'_':
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		result = result || CharInSet(AChar, FAdditionalIdentChars);
		result = result && !IsWordBreakChar(AChar);
	}
	return result;
}

bool __fastcall TCustomSynEdit::IsNonWhiteChar(WideChar AChar)
{
	bool result = false;
	result = !IsWhiteChar(AChar);
	return result;
}

bool __fastcall TCustomSynEdit::IsWhiteChar(WideChar AChar)
{
	bool result = false;
	if(ASSIGNED(Highlighter))
		result = Highlighter->IsWhiteChar(AChar);
	else
		switch(AChar)
		{
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
			 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
			 case 30: case 31: case 32:
			result = true;
			break;
			default:
			result = !(IsIdentChar(AChar) || IsWordBreakChar(AChar));
			break;
		}
	return result;
}

bool __fastcall TCustomSynEdit::IsWordBreakChar(WideChar AChar)
{
	bool result = false;
	if(ASSIGNED(Highlighter))
		result = Highlighter->IsWordBreakChar(AChar);
	else
	{
		switch(AChar)
		{
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
			 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
			 case 30: case 31: case 32:
			case L'.':
			case L',':
			case L';':
			case L':':
			case L'\"':
			case L'\'':
			case L'\xb4':
			case L'`':
			case L'\xb0':
			case L'^':
			case L'!':
			case L'?':
			case L'&':
			case L'$':
			case L'@':
			case L'\xa7':
			case L'%':
			case L'#':
			case L'~':
			case L'[':
			case L']':
			case L'(':
			case L')':
			case L'{':
			case L'}':
			case L'<':
			case L'>':
			case L'-':
			case L'=':
			case L'+':
			case L'*':
			case L'/':
			case L'\\':
			case L'|':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		result = result || CharInSet(AChar, FAdditionalWordBreakChars);
		result = result && !CharInSet(AChar, FAdditionalIdentChars);
	}
	return result;
}

void __fastcall TCustomSynEdit::SetSearchEngine(TSynEditSearchCustom* Value)
{
	if(fSearchEngine != Value)
	{
		fSearchEngine = Value;
		if(ASSIGNED(fSearchEngine))
			fSearchEngine->FreeNotification(this);
	}
}

TBufferCoord __fastcall TCustomSynEdit::NextWordPos()
{
	TBufferCoord result = {};
	result = NextWordPosEx(CaretXY);
	return result;
}

TBufferCoord __fastcall TCustomSynEdit::WordStart()
{
	TBufferCoord result = {};
	result = WordStartEx(CaretXY);
	return result;
}

TBufferCoord __fastcall TCustomSynEdit::WordEnd()
{
	TBufferCoord result = {};
	result = WordEndEx(CaretXY);
	return result;
}

TBufferCoord __fastcall TCustomSynEdit::PrevWordPos()
{
	TBufferCoord result = {};
	result = PrevWordPosEx(CaretXY);
	return result;
}
// Get XY caret position of mouse. Returns False if point is outside the
// region of the SynEdit control.

bool __fastcall TCustomSynEdit::GetPositionOfMouse(TBufferCoord& aPos)
{
	aPos = {}; //# clear out parameter
	bool result = false;
	TPoint Point = {};
	GetCursorPos(&Point);                    // mouse position (on screen)
	Point = this->ScreenToClient(Point);    // convert to SynEdit coordinates
  /* Make sure it fits within the SynEdit bounds */
	if((Point.X < 0) || (Point.Y < 0) || (Point.X > this->Width) || (Point.Y > this->Height))
	{
		result = false;
		return result;
	}

  /* inside the editor, get the word under the mouse pointer */
	aPos = DisplayToBufferPos(PixelsToRowColumn(Point.X, Point.Y));
	result = true;
	return result;
}

String __fastcall TCustomSynEdit::GetWordAtMouse()
{
	String result;
	TBufferCoord Point = {};
  /* Return the word under the mouse */
	if(GetPositionOfMouse(Point))        // if point is valid
		result = this->GetWordAtRowCol(Point); // return the point at the mouse position
	return result;
}
/* Index is 0-based; Result.x and Result.y are 1-based */

TBufferCoord __fastcall TCustomSynEdit::CharIndexToRowCol(int Index)
{
	TBufferCoord result = {};
	int x = 0;
	int y = 0;
	int Chars = 0;
	x = 0;
	y = 0;
	Chars = 0;
	while(y < Lines->Count)
	{
		x = Lines->Strings[y].Length();
		if(Chars + x + 2 > Index)
		{
			x = Index - Chars;
			break;
		}
		Chars += x + 2;
		x = 0;
		++y;
	}
	result.Char = x + 1;
	result.Line = y + 1;
	return result;
}
/* Row and Col are 1-based; Result is 0-based */

int __fastcall TCustomSynEdit::RowColToCharIndex(const TBufferCoord& cRowCol)
{
	TBufferCoord RowCol = cRowCol;
	int result = 0;
	TSynEditStringList* synEditStringList = nullptr;
	RowCol.Line = Max(0, Min(Lines->Count, RowCol.Line) - 1);
	synEditStringList = ((TSynEditStringList*) fLines);
  // CharIndexToRowCol assumes a line break size of two
	result = synEditStringList->LineCharIndex(RowCol.Line) + RowCol.Line * 2 + (RowCol.Char - 1);
	return result;
}
/* just to attain interface compatibility with TMemo */

void __fastcall TCustomSynEdit::Clear()
{
	ClearAll();
}

int __fastcall TCustomSynEdit::GetSelLength()
{
	int result = 0;
	if(SelAvail)
		result = RowColToCharIndex(BlockEnd) - RowColToCharIndex(BlockBegin);
	else
		result = 0;
	return result;
}

void __fastcall TCustomSynEdit::SetSelLength(int Value)
{
	int iNewCharIndex = 0;
	TBufferCoord iNewBegin = {};
	TBufferCoord iNewEnd = {};
	iNewCharIndex = RowColToCharIndex(BlockBegin) + Value;
	if((Value >= 0) || (iNewCharIndex < 0))
	{
		if(iNewCharIndex < 0)
		{
			iNewEnd.Char = Lines->Strings[Lines->Count - 1].Length() + 1;
			iNewEnd.Line = Lines->Count;
		}
		else
		iNewEnd = CharIndexToRowCol(iNewCharIndex);
		SetCaretAndSelection(iNewEnd, BlockBegin, iNewEnd);
	}
	else
	{
		iNewBegin = CharIndexToRowCol(iNewCharIndex);
		SetCaretAndSelection(iNewBegin, iNewBegin, BlockBegin);
	}
}

void __fastcall TCustomSynEdit::DefineProperties(TFiler* Filer)
{

	auto CollectionsEqual = [&](TCollection* C1, TCollection* C2) -> bool 
	{
		bool result = false;
		result = Classes::CollectionsEqual(C1, C2, nullptr, nullptr);
		return result;
	};

	auto HasKeyData = [&]() -> bool 
	{
		bool result = false;
		TSynEditKeyStrokes* iDefKeys = nullptr;
		if(Filer->Ancestor != nullptr)
		{
			result = !CollectionsEqual(Keystrokes, ((TCustomSynEdit*) Filer->Ancestor)->Keystrokes);
		}
		else
		{
			iDefKeys = new TSynEditKeyStrokes((TPersistent*)nullptr);
			try
			{
				iDefKeys->ResetDefaults();
				result = !CollectionsEqual(Keystrokes, iDefKeys);
			}
			__finally
			{
				delete iDefKeys;
			}
		}
		return result;
	};
	bool iSaveKeyData = false;
	inherited::DefineProperties(Filer);
	iSaveKeyData = HasKeyData();
	Filer->DefineProperty(L"RemovedKeystrokes", ReadRemovedKeystrokes, WriteRemovedKeystrokes, iSaveKeyData);
	Filer->DefineProperty(L"AddedKeystrokes", ReadAddedKeystrokes, WriteAddedKeystrokes, iSaveKeyData);
}

void __fastcall TCustomSynEdit::DoChange()
{
	if(ASSIGNED(fOnChange))
		fOnChange(this);
}

void __fastcall TCustomSynEdit::ReadAddedKeystrokes(TReader* Reader)
{
	TSynEditKeyStrokes* iAddKeys = nullptr;
	int cKey = 0;
	if(Reader->NextValue() == vaCollection)
		Reader->ReadValue();
	else
		return;
	iAddKeys = new TSynEditKeyStrokes(this);
	try
	{
		int stop = 0;
		Reader->ReadCollection(iAddKeys);
		for(stop = iAddKeys->Count - 1, cKey = 0; cKey <= stop; cKey++)
		{
			Keystrokes->Add()->Assign(iAddKeys->Items[cKey]);
		}
	}
	__finally
	{
		delete iAddKeys;
	}
}

void __fastcall TCustomSynEdit::ReadRemovedKeystrokes(TReader* Reader)
{
	TSynEditKeyStrokes* iDelKeys = nullptr;
	int cKey = 0;
	TSynEditKeyStroke* iKey = nullptr;
	int iToDelete = 0;
	if(Reader->NextValue() == vaCollection)
		Reader->ReadValue();
	else
		return;
	iDelKeys = new TSynEditKeyStrokes((TPersistent*)nullptr);
	try
	{
		int stop = 0;
		Reader->ReadCollection(iDelKeys);
		for(stop = iDelKeys->Count - 1, cKey = 0; cKey <= stop; cKey++)
		{
			iKey = iDelKeys->Items[cKey];
			iToDelete = Keystrokes->FindShortcut2(iKey->ShortCut, iKey->ShortCut2);
			if((iToDelete >= 0) && (Keystrokes->Items[iToDelete]->Command == iKey->Command))
				delete Keystrokes->Items[iToDelete];
		}
	}
	__finally
	{
		delete iDelKeys;
	}
}

void __fastcall TCustomSynEdit::WriteAddedKeystrokes(TWriter* Writer)
{
	TSynEditKeyStrokes* iDefaultKeys = nullptr;
	TSynEditKeyStrokes* iAddedKeys = nullptr;
	int cKey = 0;
	TSynEditKeyStroke* iKey = nullptr;
	int iDelIndex = 0;
	iDefaultKeys = new TSynEditKeyStrokes((TPersistent*)nullptr);
	try
	{
		if(Writer->Ancestor != nullptr)
			iDefaultKeys->Assign(((TSynEdit*) Writer->Ancestor)->Keystrokes);
		else
			iDefaultKeys->ResetDefaults();
		iAddedKeys = new TSynEditKeyStrokes((TPersistent*)nullptr);
		try
		{
			int stop = 0;
			for(stop = Keystrokes->Count - 1, cKey = 0; cKey <= stop; cKey++)
			{
				iKey = Keystrokes->Items[cKey];
				iDelIndex = iDefaultKeys->FindShortcut2(iKey->ShortCut, iKey->ShortCut2);
        //if it's not a default keystroke, add it
				if((iDelIndex < 0) || (iDefaultKeys->Items[iDelIndex]->Command != iKey->Command))
					iAddedKeys->Add()->Assign(iKey);
			}
			Writer->WriteCollection(iAddedKeys);
		}
		__finally
		{
			delete iAddedKeys;
		}
	}
	__finally
	{
		delete iDefaultKeys;
	}
}

void __fastcall TCustomSynEdit::WriteRemovedKeystrokes(TWriter* Writer)
{
	TSynEditKeyStrokes* iRemovedKeys = nullptr;
	int cKey = 0;
	TSynEditKeyStroke* iKey = nullptr;
	int iFoundAt = 0;
	iRemovedKeys = new TSynEditKeyStrokes((TPersistent*)nullptr);
	try
	{
		if(Writer->Ancestor != nullptr)
			iRemovedKeys->Assign(((TSynEdit*) Writer->Ancestor)->Keystrokes);
		else
			iRemovedKeys->ResetDefaults();
		cKey = 0;
		while(cKey < iRemovedKeys->Count)
		{
			iKey = iRemovedKeys->Items[cKey];
			iFoundAt = Keystrokes->FindShortcut2(iKey->ShortCut, iKey->ShortCut2);
			if((iFoundAt >= 0) && (Keystrokes->Items[iFoundAt]->Command == iKey->Command))
				delete iKey;
			else
				++cKey;
		}
		Writer->WriteCollection(iRemovedKeys);
	}
	__finally
	{
		delete iRemovedKeys;
	}
}

void __fastcall TCustomSynEdit::AddMouseDownHandler(TMouseEvent aHandler)
{
	fKbdHandler->AddMouseDownHandler(aHandler);
}

void __fastcall TCustomSynEdit::RemoveMouseDownHandler(TMouseEvent aHandler)
{
	fKbdHandler->RemoveMouseDownHandler(aHandler);
}

void __fastcall TCustomSynEdit::AddMouseUpHandler(TMouseEvent aHandler)
{
	fKbdHandler->AddMouseUpHandler(aHandler);
}

void __fastcall TCustomSynEdit::RemoveMouseUpHandler(TMouseEvent aHandler)
{
	fKbdHandler->RemoveMouseUpHandler(aHandler);
}

//++ CodeFolding

void __fastcall TCustomSynEdit::FullFoldScan()
{
	if(UseCodeFolding)
	{
		ReScanForFoldRanges(0, fLines->Count - 1);
	}
}

void __fastcall TCustomSynEdit::ReScanForFoldRanges(int FromLine, int ToLine)
{
	int AdjustedToLine = 0;
	AdjustedToLine = Max(Min(ToLine, Lines->Count - 1), FromLine);
	fAllFoldRanges->StartScanning();
	ScanForFoldRanges(fAllFoldRanges, fLines, FromLine, AdjustedToLine);
  /*  StopScanning recreates AllFoldRanges.
     Normally at this point (sfLinesChanging in fStateFlags) = True
     and StopScanning will be called when LinesChanged is executed */
	if(!(fStateFlags.Contains(sfLinesChanging)) && fAllFoldRanges->StopScanning(fLines))
	{
		if(ObjectIs(fHighlighter, TSynCustomCodeFoldingHighlighter*))
			((TSynCustomCodeFoldingHighlighter*) fHighlighter)->AdjustFoldRanges(AllFoldRanges, fLines);
		InvalidateGutter();
		fStateFlags << sfScrollbarChanged;
	}
}

void __fastcall TCustomSynEdit::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	if(ObjectIs(fHighlighter, TSynCustomCodeFoldingHighlighter*))
		((TSynCustomCodeFoldingHighlighter*) fHighlighter)->ScanForFoldRanges(FoldRanges, LinesToScan, FromLine, ToLine);
	if(ASSIGNED(fOnScanForFoldRanges))
		fOnScanForFoldRanges(this, FoldRanges, LinesToScan, FromLine, ToLine);
}
//-- CodeFolding

void __fastcall TCustomSynEdit::AddMouseCursorHandler(TMouseCursorEvent aHandler)
{
	fKbdHandler->AddMouseCursorHandler(aHandler);
}

void __fastcall TCustomSynEdit::RemoveMouseCursorHandler(TMouseCursorEvent aHandler)
{
	fKbdHandler->RemoveMouseCursorHandler(aHandler);
}

void __fastcall TCustomSynEdit::DoSearchFindFirstExecute(TSearchFindFirst* Action)
{
	OnFindBeforeSearch = Action->Dialog->OnFind;
	OnCloseBeforeSearch = Action->Dialog->OnClose;
	SelStartBeforeSearch = SelStart;
	SelLengthBeforeSearch = SelLength;
	Action->Dialog->OnFind = FindDialogFindFirst;
	Action->Dialog->OnClose = FindDialogClose;
	Action->Dialog->Execute();
}

void __fastcall TCustomSynEdit::DoSearchFindExecute(TSearchFind* Action)
{
	OnFindBeforeSearch = Action->Dialog->OnFind;
	OnCloseBeforeSearch = Action->Dialog->OnClose;
	Action->Dialog->OnFind = FindDialogFind;
	Action->Dialog->OnClose = FindDialogClose;
	Action->Dialog->Execute();
}

void __fastcall TCustomSynEdit::DoSearchReplaceExecute(TSearchReplace* Action)
{
	OnFindBeforeSearch = Action->Dialog->OnFind;
	OnReplaceBeforeSearch = Action->Dialog->OnReplace;
	OnCloseBeforeSearch = Action->Dialog->OnClose;
	Action->Dialog->OnFind = FindDialogFind;
	Action->Dialog->OnReplace = FindDialogFind;
	Action->Dialog->OnClose = FindDialogClose;
	Action->Dialog->Execute();
}

void __fastcall TCustomSynEdit::DoSearchFindNextExecute(TSearchFindNext* Action)
{
	SearchByFindDialog(Action->SearchFind->Dialog);
}

void __fastcall TCustomSynEdit::FindDialogFindFirst(TObject* Sender)
{
	((TFindDialog*) Sender)->CloseDialog();
	if((SelStart == SelStartBeforeSearch) && (SelLength == SelLengthBeforeSearch))
	{
		SelStart = 0;
		SelLength = 0;
	}
	if(ObjectIs(Sender, TFindDialog*))
	{
		if(!SearchByFindDialog(((TFindDialog*) Sender)) && (SelStart == 0) && (SelLength == 0))
		{
			SelStart = SelStartBeforeSearch;
			SelLength = SelLengthBeforeSearch;
		}
	}
}

void __fastcall TCustomSynEdit::FindDialogFind(TObject* Sender)
{
	if(ObjectIs(Sender, TFindDialog*))
		SearchByFindDialog(((TFindDialog*) Sender));
}

BOOL __fastcall TCustomSynEdit::SearchByFindDialog(TFindDialog* FindDialog)
{
	BOOL result = false;
	TSynSearchOptions Options;
	String ReplaceText;
	String MessageText;
	int OldSelStart = 0;
	int OldSelLength = 0;
	if(FindDialog->Options.Contains(frReplaceAll))
		Options = Synedit__53;
	else
	{
		if(FindDialog->Options.Contains(frReplace))
			Options = Synedit__54;
		else
			Options = Synedit__55;
	}
	if(FindDialog->Options.Contains(frMatchCase))
		Options = Options + Synedit__56;
	if(FindDialog->Options.Contains(frWholeWord))
		Options = Options + Synedit__57;
	if(!(FindDialog->Options.Contains(frDown)))
		Options = Options + Synedit__58;
	if(Options.Contains(ssoSelectedOnly))
		ReplaceText = L"";
	else
		ReplaceText = ((TReplaceDialog*) FindDialog)->ReplaceText;
	OldSelStart = SelStart;
	OldSelLength = SelLength;
	if((UpperCase(SelText) == UpperCase(FindDialog->FindText)) && !(FindDialog->Options.Contains(frReplace)))
		SelStart = SelStart + SelLength;
	else
		SelLength = 0;
	result = SearchReplace(FindDialog->FindText, ReplaceText, Options) > 0;
	if(!result)
	{
		SelStart = OldSelStart;
		SelLength = OldSelLength;
		if(ASSIGNED(OnSearchNotFound))
			OnSearchNotFound(this, FindDialog->FindText);
		else
		{
			MessageText = Format(Vcl_Consts_STextNotFound, ARRAYOFCONST((FindDialog->FindText)));
			ShowMessage(MessageText);
		}
	}
	else
	{
		if(FindDialog->Options.Contains(frReplace))
		{
			SelStart = SelStart - FindDialog->FindText.Length() - 1;
			SelLength = FindDialog->FindText.Length() + 1;
		}
	}
	return result;
}

void __fastcall TCustomSynEdit::FindDialogClose(TObject* Sender)
{
	((TFindDialog*) Sender)->OnFind = OnFindBeforeSearch;
	if(ObjectIs(Sender, TReplaceDialog*))
		((TReplaceDialog*) Sender)->OnReplace = OnReplaceBeforeSearch;
	((TFindDialog*) Sender)->OnClose = OnCloseBeforeSearch;
}

bool __fastcall TCustomSynEdit::GetWordWrap()
{
	bool result = false;
	result = fWordWrapPlugin != nullptr;
	return result;
}

void __fastcall TCustomSynEdit::SetWordWrap(bool Value)
{
	int vOldTopLine = 0;
	bool vShowCaret = false;
	if(WordWrap != Value)
	{
		Invalidate(); // better Invalidate before changing LeftChar and TopLine
		vShowCaret = CaretInView();
		vOldTopLine = RowToLine(TopLine);
//++ CodeFolding
     // !!Mutually exclusive with CodeFolding to reduce complexity
		if(Value && !UseCodeFolding)
//-- CodeFolding
		{
			fWordWrapPlugin = new TSynWordWrapPlugin(this);
			LeftChar = 1;
		}
		else
		fWordWrapPlugin = nullptr;
		TopLine = LineToRow(vOldTopLine);
		UpdateScrollBars();
		if(vShowCaret)
			EnsureCursorPosVisible();
	}
}

int __fastcall TCustomSynEdit::GetDisplayLineCount()
{
	int result = 0;
//++ CodeFolding
	if(fWordWrapPlugin == nullptr)
	{
		if(fUseCodeFolding)
			result = LineToRow(Lines->Count);
		else
			result = Lines->Count;
	}
	else
	{
		if(Lines->Count == 0)
//++ CodeFolding
			result = 0;
		else
		{
			result = fWordWrapPlugin->RowCount();
		}
	}
	return result;
}

int __fastcall TCustomSynEdit::LineToRow(int aLine)
{
	int result = 0;
	TBufferCoord vBufferPos = {};
//++ CodeFolding
	if(!UseCodeFolding && !WordWrap)
//-- CodeFolding
		result = aLine;
	else
	{
		vBufferPos.Char = 1;
		vBufferPos.Line = aLine;
		result = BufferToDisplayPos(vBufferPos).Row;
	}
	return result;
}

int __fastcall TCustomSynEdit::RowToLine(int aRow)
{
	int result = 0;
	TDisplayCoord vDisplayPos = {};
//++ CodeFolding
	if(!UseCodeFolding && !WordWrap)
//-- CodeFolding
		result = aRow;
	else
	{
		vDisplayPos.Column = 1;
		vDisplayPos.Row = aRow;
		result = DisplayToBufferPos(vDisplayPos).Line;
	}
	return result;
}

void __fastcall TCustomSynEdit::SetInternalDisplayXY(const TDisplayCoord& aPos)
{
	IncPaintLock();
	InternalCaretXY = DisplayToBufferPos(aPos);
	fCaretAtEOL = WordWrap && (aPos.Row <= fWordWrapPlugin->RowCount()) && (aPos.Column > fWordWrapPlugin->GetRowLength(aPos.Row)) && (DisplayY != aPos.Row);
	DecPaintLock();
	UpdateLastCaretX();
}

void __fastcall TCustomSynEdit::SetWantReturns(bool Value)
{
	fWantReturns = Value;
}

void __fastcall TCustomSynEdit::SetWantTabs(bool Value)
{
	fWantTabs = Value;
}

void __fastcall TCustomSynEdit::SetWordWrapGlyph(TSynGlyph* const Value)
{
	fWordWrapGlyph->Assign((TPersistent*) Value);
}

void __fastcall TCustomSynEdit::WordWrapGlyphChange(TObject* Sender)
{
	if(!(ComponentState.Contains(csLoading)))
		InvalidateGutter();
}

/* TSynEditMark */

TCustomSynEdit* __fastcall TSynEditMark::GetEdit()
{
	TCustomSynEdit* result = nullptr;
	if(fEdit != nullptr)
		try
		{
			if(fEdit->Marks->IndexOf(this) == -1)
				fEdit = nullptr;
		}
		catch(...)
		{
			fEdit = nullptr;
		}
	result = fEdit;
	return result;
}

bool __fastcall TSynEditMark::GetIsBookmark()
{
	bool result = false;
	result = (fBookmarkNum >= 0);
	return result;
}

void __fastcall TSynEditMark::SetChar(int Value)
{
	fChar = Value;
}

void __fastcall TSynEditMark::SetImage(int Value)
{
	fImage = Value;
	if(fVisible && ASSIGNED(fEdit))
		fEdit->InvalidateGutterLines(fLine, fLine);
}

void __fastcall TSynEditMark::SetInternalImage(bool Value)
{
	fInternalImage = Value;
	if(fVisible && ASSIGNED(fEdit))
		fEdit->InvalidateGutterLines(fLine, fLine);
}

void __fastcall TSynEditMark::SetLine(int Value)
{
	if(fVisible && ASSIGNED(fEdit))
	{
		if(fLine > 0)
			fEdit->InvalidateGutterLines(fLine, fLine);
		fLine = Value;
		fEdit->InvalidateGutterLines(fLine, fLine);
	}
	else
	fLine = Value;
}

void __fastcall TSynEditMark::SetVisible(bool Value)
{
	if(fVisible != Value)
	{
		fVisible = Value;
		if(ASSIGNED(fEdit))
			fEdit->InvalidateGutterLines(fLine, fLine);
	}
}

__fastcall TSynEditMark::TSynEditMark(TCustomSynEdit* AOwner)
 : fLine(0),
			fChar(0),
			fImage(0),
			fEdit(nullptr),
			fVisible(false),
			fInternalImage(false),
			fBookmarkNum(0)
{
	//# inherited::Create();
	fBookmarkNum = -1;
	fEdit = AOwner;
}

/* TSynEditMarkList */

void __fastcall TSynEditMarkList::Notify(void* Ptr, TListNotification Action)
{
	inherited::Notify(Ptr, Action);
	if(ASSIGNED(fOnChange))
		fOnChange(this);
}

TSynEditMark* __fastcall TSynEditMarkList::GetItem(int Index)
{
	TSynEditMark* result = nullptr;
	result = ((TSynEditMark*) inherited::GetItem(Index));
	return result;
}

void __fastcall TSynEditMarkList::SetItem(int Index, TSynEditMark* Item)
{
	inherited::SetItem(Index, Item);
}

__fastcall TSynEditMarkList::TSynEditMarkList(TCustomSynEdit* AOwner)
 : fEdit(AOwner)
{
	//# inherited::Create();
}

TSynEditMark* __fastcall TSynEditMarkList::First()
{
	TSynEditMark* result = nullptr;
	result = ((TSynEditMark*) inherited::First());
	return result;
}

TSynEditMark* __fastcall TSynEditMarkList::Last()
{
	TSynEditMark* result = nullptr;
	result = ((TSynEditMark*) inherited::Last());
	return result;
}

TSynEditMark* __fastcall TSynEditMarkList::Extract(TSynEditMark* Item)
{
	TSynEditMark* result = nullptr;
	result = ((TSynEditMark*) inherited::Extract(Item));
	return result;
}

void __fastcall TSynEditMarkList::ClearLine(int line)
{
	int i = 0;
	int stop = 0;
	for(stop = 0, i = Count - 1; i >= stop; i--)
	{
		if(!Items[i]->IsBookmark && (Items[i]->Line == line))
			Delete(i);
	}
}
//Returns up to maxMarks book/gutter marks for a chosen line.

void __fastcall TSynEditMarkList::GetMarksForLine(int line, TSynEditMarks& Marks)
{
	int cnt = 0;
	int i = 0;
	int stop = 0;
	FillChar((void**)&Marks, (int) sizeof(Marks), 0);
	cnt = 0;
	for(stop = Count - 1, i = 0; i <= stop; i++)
	{
		if(Items[i]->Line == line)
		{
			++cnt;
			Marks[cnt - 1] = Items[i];
			if(cnt == MAX_MARKS)
				break;
		}
	}
}

void __fastcall TSynEditMarkList::Place(TSynEditMark* mark)
{
	if(ASSIGNED(fEdit))
	{
		if(ASSIGNED(fEdit->OnPlaceBookmark))
			fEdit->OnPlaceBookmark(fEdit, mark);
	}
	if(ASSIGNED(mark))
		Add(mark);
}

/* TSynEditPlugin */

__fastcall TSynEditPlugin::TSynEditPlugin(TCustomSynEdit* AOwner)
 : fOwner(nullptr)
{
	const System::Set<TPluginHandler, TPluginHandler::phLinesInserted, TPluginHandler::phAfterPaint> AllPlugInHandlers = System::Set<TPluginHandler, TPluginHandler::phLinesInserted, TPluginHandler::phAfterPaint>() << phLinesInserted << phLinesBeforeDeleted << phLinesDeleted << phLinePut << phLinesChanged << phPaintTransient << phAfterPaint;
	//# inherited::Create();
	if(AOwner != nullptr)
	{
		fOwner = AOwner;
		if(fOwner->fPlugins == nullptr)
			fOwner->fPlugins = new TObjectList();
		fOwner->fPlugins->Add(this);
	}
	FHandlers = AllPlugInHandlers;  // for backward compatibility
}

__fastcall TSynEditPlugin::TSynEditPlugin(TCustomSynEdit* AOwner, TPlugInHandlers AHandlers)
 : TSynEditPlugin(AOwner)  //# delegation
{
	FHandlers = AHandlers;
}
/*    [ld.lld Error] ld.lld: error: undefined symbol: Synedit::TSynEditPlugin::~TSynEditPlugin()
__fastcall TSynEditPlugin::~TSynEditPlugin()
{
	if(FOwner != nullptr)
		FOwner->fPlugins->Extract(this); // we are being destroyed, fOwner should not free us
	//# inherited::Destroy();
}
*/
__fastcall void TSynEditPlugin::OnSynEditPluginDestruction()
{
	if(fOwner != nullptr)
		fOwner->fPlugins->Extract(this); // we are being destroyed, fOwner should not free us
	//# inherited::Destroy();
}

void __fastcall TSynEditPlugin::AfterPaint(TCanvas* ACanvas, const TRect& AClip, int FirstLine, int LastLine)
{

  // nothing
}

void __fastcall TSynEditPlugin::PaintTransient(TCanvas* ACanvas, TTransientType ATransientType)
{

  // nothing
}

void __fastcall TSynEditPlugin::LinesChanged()
{

  // nothing
}

void __fastcall TSynEditPlugin::LinesInserted(int FirstLine, int Count)
{

  // nothing
}

void __fastcall TSynEditPlugin::LinePut(int aIndex, const String OldLine)
{

  // nothing
}

void __fastcall TSynEditPlugin::LinesBeforeDeleted(int FirstLine, int Count)
{

  // nothing
}

void __fastcall TSynEditPlugin::LinesDeleted(int FirstLine, int Count)
{

  // nothing
}


}  // namespace SynEdit

