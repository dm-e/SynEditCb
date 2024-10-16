/* -------------------------------------------------------------------------------
  The contents of this file are subject to the Mozilla Public License
  Version 1.1 (the "License"); you may not use this file except in compliance
  with the License. You may obtain a copy of the License at
  http://www.mozilla.org/MPL/

  Software distributed under the License is distributed on an "AS IS" basis,
  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
  the specific language governing rights and limitations under the License.

  Contributors to the SynEdit and mwEdit projects are listed in the
  Contributors.txt file.

  Alternatively, the contents of this file may be used under the terms of the
  GNU General Public License Version 2 or later (the "GPL"), in which case
  the provisions of the GPL are applicable instead of those above.
  If you wish to allow use of your version of this file only under the terms
  of the GPL and not to allow others to use your version of this file
  under the MPL, indicate your decision by deleting the provisions above and
  replace them with the notice and other provisions required by the GPL.
  If you do not delete the provisions above, a recipient may use your version
  of this file under either the MPL or the GPL.
  ------------------------------------------------------------------------------- */
#ifndef SynEditCodeFoldingH
#define SynEditCodeFoldingH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Generics.Collections.hpp>
#include "SynEditHighlighter.h"
#include "SynEditDelphiInstances.hpp"

namespace Syneditcodefolding
{

/* -------------------------------------------------------------------------------
  The contents of this file are subject to the Mozilla Public License
  Version 1.1 (the "License"); you may not use this file except in compliance
  with the License. You may obtain a copy of the License at
  http://www.mozilla.org/MPL/

  Software distributed under the License is distributed on an "AS IS" basis,
  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
  the specific language governing rights and limitations under the License.

  Contributors to the SynEdit and mwEdit projects are listed in the
  Contributors.txt file.

  Alternatively, the contents of this file may be used under the terms of the
  GNU General Public License Version 2 or later (the "GPL"), in which case
  the provisions of the GPL are applicable instead of those above.
  If you wish to allow use of your version of this file only under the terms
  of the GPL and not to allow others to use your version of this file
  under the MPL, indicate your decision by deleting the provisions above and
  replace them with the notice and other provisions required by the GPL.
  If you do not delete the provisions above, a recipient may use your version
  of this file under either the MPL or the GPL.
  ------------------------------------------------------------------------------- */
/*
   Introduction
   ============
   This unit adds code folding support for SynEdit.
   It blends well with the Synedit highligting infrastructure and provides
   fast and efficient code folding that can cope with files with tens of
   thousands of line without lags.

   Converting existing highlighters
   ================================

   To support code folding a Highlighter must inherit from
   TSynCustomCodeFoldingHighlighter and implement one abstact procedure
   ScanForFoldRanges(FoldRanges: TSynFoldRanges;
      LinesToScan: TStrings; FromLine: Integer; ToLine: Integer);
   For each line ScanForFoldRanges needs to call one of the following:
      FoldRanges.StartFoldRange
      FoldRanges.StopFoldRange
      FoldRanges.NoFoldInfo
   ScanForFoldRanges is called after the standard highlighter scanning has taken
   place so one can use the Range information stored inside LinesToScan, which
   is  a TSynEditStringList, to avoid duplicating effort.

   Initally two hightlighters have been converted SynHighlighterJScript and
   SynHighlighterPython, to serve as examples of adding code folding suppot to
   brace-based and indentation-based languagges.

   Alternatively, code folding support can be provided just by implementing
   the SynEdit OnScanForFoldRangesEvent event.

   Demo of Coding Folding
   ======================
   A Folding demo has been added that demonstrates the use of the JScript and
   Python highlighters as well as the use of the OnScanForFoldRangesEvent event
   to support code folding in C++ files.

   Synedit Commants and Shortcuts
   =========
   The following commands have been added:
     ecFoldAll, ecUnfoldAll, ecFoldNearest, ecUnfoldNearest, ecFoldLevel1,
     ecFoldLevel2, ecFoldLevel3,, ecUnfoldLevel1, ecUnfoldLevel2,
     ecUnfoldLevel3, ecFoldRegions

    The default customisable shortcuts are:
      AddKey(ecFoldAll, VK_OEM_MINUS, [ssCtrl, ssShift]);   //- _
      AddKey(ecUnfoldAll,  VK_OEM_PLUS, [ssCtrl, ssShift]); //= +
      AddKey(ecFoldNearest, VK_OEM_2, [ssCtrl]);  // Divide //'/'
      AddKey(ecUnfoldNearest, VK_OEM_2, [ssCtrl, ssShift]);
      AddKey(ecFoldLevel1, ord('K'), [ssCtrl], Ord('1'), [ssCtrl]);
      AddKey(ecFoldLevel2, ord('K'), [ssCtrl], Ord('2'), [ssCtrl]);
      AddKey(ecFoldLevel3, ord('K'), [ssCtrl], Ord('3'), [ssCtrl]);
      AddKey(ecUnfoldLevel1, ord('K'), [ssCtrl, ssShift], Ord('1'), [ssCtrl, ssShift]);
      AddKey(ecUnfoldLevel2, ord('K'), [ssCtrl, ssShift], Ord('2'), [ssCtrl, ssShift]);
      AddKey(ecUnfoldLevel3, ord('K'), [ssCtrl, ssShift], Ord('3'), [ssCtrl, ssShift]);

   Limitations
   ===========
   -  Code folding can not be used simultaneously with Wordwrap.  Synedit takes
      care of that.
   -  The code uses generic collections, so it cannot be used with Delphi
      versions prior to Delphi 2009.

   Improvements
   ============
   Although the code folding infrastructure is fairly complete, improvements
   can be made in providing the use with more painting options
   (folding hints etc.)

   Technical details
   =================
   The main code folding structure is TSynFoldRanges.  It contains a public
   TList<TSynFoldRange> (sorted by starting line numbers).  This list is used by
   Synedit to paint the gutter and lines, fold and unfold ranges etc.
   Internally, TSynFoldRange maintains a TList<TLineFoldInfo> that is modified
   during scanning.  The TList<TSynFoldRange> is reconstructed from the
   TList<TLineFoldInfo> only when it is necessary.

*/
  // Custom COde Folding Exception

class TSynCodeFoldingException : public System::Sysutils::Exception
{
	#include "SynEditCodeFolding_friends.inc"
public:
	typedef System::Sysutils::Exception inherited;
	__fastcall TSynCodeFoldingException(const String Msg);
	__fastcall TSynCodeFoldingException(const String Msg, const TVarRec* Args, int Args_maxidx);
	__fastcall TSynCodeFoldingException(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall TSynCodeFoldingException(const String Msg, int AHelpContext);
	__fastcall TSynCodeFoldingException(System::NativeUInt Ident);
	__fastcall TSynCodeFoldingException(System::PResStringRec ResStringRec);
	__fastcall TSynCodeFoldingException(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx);
	__fastcall TSynCodeFoldingException(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx);
	__fastcall TSynCodeFoldingException(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall TSynCodeFoldingException(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall TSynCodeFoldingException(System::NativeUInt Ident, int AHelpContext);
	__fastcall TSynCodeFoldingException(System::PResStringRec ResStringRec, int AHelpContext);
};

  // A single fold
  // Important: FromLine, ToLine are 1-based
typedef TSynFoldRange* PSynFoldRange;

  /*Support for indendation based code folding as in Python, F#*/
enum TSynCodeFoldingMode {cfmStandard,
                          cfmIndentation };

  /*
    The main code folding data structure.
    Scanning affects the fFoldInfoList data structure
    SynEdit Painting is based on the fRanges structure
    fRanges gets updated from fFoldInfoList when needed
    Both fRanges and fFoldInfoList are kept sorted by FromLine
    Line indices in both fRanges and fFoldInfoList are 1-based
  */

class TSynFoldRanges : public System::TObject
{
	#include "SynEditCodeFolding_friends.inc"
public:
	typedef System::TObject inherited;
private:
	TSynCodeFoldingMode fCodeFoldingMode;
	bool fRangesNeedFixing;
	TList__1<TSynFoldRange>* fRanges;
	TList__1<int>* fCollapsedState;
	TList__1<TLineFoldInfo>* fFoldInfoList;
	TSynFoldRange __fastcall Get(int Index);
	int __fastcall GetCount();
public:
	__fastcall TSynFoldRanges();
	virtual __fastcall ~TSynFoldRanges();

    /*utility routines*/
	bool __fastcall FoldStartAtLine(int Line);
	bool __fastcall FoldStartAtLine(int Line, int& Index);
	bool __fastcall CollapsedFoldStartAtLine(int Line);
	bool __fastcall CollapsedFoldStartAtLine(int Line, int& Index);
	bool __fastcall FoldEndAtLine(int Line);
	bool __fastcall FoldEndAtLine(int Line, int& Index);
	bool __fastcall FoldAroundLineEx(int Line, bool WantCollapsed, bool AcceptFromLine, bool AcceptToLine, int& Index);
	bool __fastcall CollapsedFoldAroundLine(int Line);
	bool __fastcall CollapsedFoldAroundLine(int Line, int& Index);
	bool __fastcall FoldAroundLine(int Line);
	bool __fastcall FoldAroundLine(int Line, int& Index);
	bool __fastcall FoldHidesLine(int Line);
	bool __fastcall FoldHidesLine(int Line, int& Index);
	System::TArray<int> __fastcall FoldsAtLevel(int Level);
	System::TArray<int> __fastcall FoldsOfType(int aType);

    /*Scanning support*/
	void __fastcall StoreCollapsedState();
	void __fastcall RestoreCollapsedState();
	void __fastcall StoreCollapsedState(TStream* Stream);
	void __fastcall RestoreCollapsedState(TStream* Stream);
	void __fastcall StartScanning();
	bool __fastcall StopScanning(TStrings* Lines); // Returns True of Ranges were updated
	void __fastcall AddLineInfo(int ALine, int AFoldType, TFoldOpenClose AFoldOpenClose, int AIndent);
	void __fastcall StartFoldRange(int ALine, int AFoldType, int AIndent = -1);
	void __fastcall StopFoldRange(int ALine, int AFoldType, int AIndent = -1);
	void __fastcall NoFoldInfo(int ALine);
	int __fastcall GetIndentLevel(int Line);
	void __fastcall RecreateFoldRanges(TStrings* Lines);

    // plugin notifications and support routines
	int __fastcall FoldLineToRow(int Line);
	int __fastcall FoldRowToLine(int Row);
	int __fastcall LinesInserted(int aIndex, int aCount);
	int __fastcall LinesDeleted(int aIndex, int aCount);
	int __fastcall LinePut(int aIndex, const String OldLine);
	void __fastcall Reset();

    /*Access to the internal FoldRange list routines*/
	void __fastcall AddByParts(int AFoldType, int AFromLine, int AToLine = -1);
	void __fastcall AddFoldRange(const TSynFoldRange& FoldRange);
	__property TSynCodeFoldingMode CodeFoldingMode = { read = fCodeFoldingMode, write = fCodeFoldingMode };
	__property int Count = { read = GetCount };
	__property TSynFoldRange FoldRange[int Index] = { read = Get/*# default */ };
	__property TList__1<TSynFoldRange>* Ranges = { read = fRanges };
};
typedef void __fastcall (__closure *TSynCodeFoldingChangeEvent) (TObject*);
    /* Class to store and expose to the designer Code Folding properties */

class TSynCodeFolding : public System::Classes::TPersistent
{
private:
	bool fIndentGuides;
	TColor fCollapsedLineColor;
	TColor fFolderBarLinesColor;
	TColor fIndentGuidesColor;
	bool fShowCollapsedLine;
	bool fShowHintMark;
	int fGutterShapeSize;
	TSynCodeFoldingChangeEvent fOnChange;
	void __fastcall SetIndentGuides(bool Value);
	void __fastcall SetCollapsedLineColor(const TColor Value);
	void __fastcall SetFolderBarLinesColor(const TColor Value);
	void __fastcall SetIndentGuidesColor(const TColor Value);
	void __fastcall SetShowCollapsedLine(bool Value);
	void __fastcall SetShowHintMark(bool Value);
	void __fastcall SetGutterShapeSize(int Value);
public:
	typedef System::Classes::TPersistent inherited;
	#include "SynEditCodeFolding_friends.inc"
	__fastcall TSynCodeFolding();
	virtual void __fastcall Assign(TPersistent* Source);
	int __fastcall ScaledGutterShapeSize(int PPI);
	__property TSynCodeFoldingChangeEvent OnChange = { read = fOnChange, write = fOnChange };
__published:
public:
    // Size of the gutter shapes in pixels at 96 PPI
	__property int GutterShapeSize = { read = fGutterShapeSize, write = SetGutterShapeSize, default = 11 };
	__property TColor CollapsedLineColor = { read = fCollapsedLineColor, write = SetCollapsedLineColor, default = clGrayText };
	__property TColor FolderBarLinesColor = { read = fFolderBarLinesColor, write = SetFolderBarLinesColor, default = clGrayText };
	__property TColor IndentGuidesColor = { read = fIndentGuidesColor, write = SetIndentGuidesColor, default = clGray };
	__property bool IndentGuides = { read = fIndentGuides, write = SetIndentGuides, default = true };
	__property bool ShowCollapsedLine = { read = fShowCollapsedLine, write = SetShowCollapsedLine, default = false };
	__property bool ShowHintMark = { read = fShowHintMark, write = SetShowHintMark, default = true };
};

class TSynCustomCodeFoldingHighlighter : public Synedithighlighter::TSynCustomHighlighter
{
protected:
    // Utility functions
	void* __fastcall GetLineRange(TStrings* Lines, int Line);
	Synedithighlighter::TSynHighlighterAttributes* __fastcall GetHighlighterAttriAtRowCol(TStrings* const Lines, int Line, int Char);
	bool __fastcall GetHighlighterAttriAtRowColEx(TStrings* const Lines, int Line, int Char, String& Token, int& TokenType, int& Start, Synedithighlighter::TSynHighlighterAttributes*& Attri);
	int __fastcall TabWidth(TStrings* LinesToScan);
public:
    // Called when a Highlighter is assigned to Synedit;
    // No need to override except to change the SynCodeFoldingMode
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	#include "SynEditCodeFolding_friends.inc"
	virtual void __fastcall InitFoldRanges(TSynFoldRanges* FoldRanges);
    // Called after Highlighter ranges have been set
	virtual void __fastcall ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine){} // = 0;
    // Called immediately after FoldRanges have been recreated
    // Override only if some finetuning of the FoldRanges is need.
	virtual void __fastcall AdjustFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan);
	__fastcall TSynCustomCodeFoldingHighlighter(TComponent* AOwner);
};
const int FoldRegionType = 99;


}  // namespace SynEditCodeFolding

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditcodefolding;
#endif

#endif // SynEditCodeFoldingH

