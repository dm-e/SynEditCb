/* -------------------------------------------------------------------------------
  The contents of this file are subject to the Mozilla Public License
  Version 1.1 (the "License"); you may not use this file except in compliance
  with the License. You may obtain a copy of the License at
  http://www.mozilla.org/MPL/

  Software distributed under the License is distributed on an "AS IS" basis,
  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
  the specific language governing rights and limitations under the License.

  The Original Code is: SynEditMiscProcs.pas, released 2000-04-07.
  The Original Code is based on the mwSupportProcs.pas file from the
  mwEdit component suite by Martin Waldenburg and other developers, the Initial
  Author of this file is Michael Hieke.
  Unicode translation by Maël Hörz.
  All Rights Reserved.

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

  $Id: SynEditMiscProcs.pas,v 1.35.2.8 2009/09/28 17:54:20 maelh Exp $

  You may retrieve the latest version of this file at the SynEdit home page,
  located at http://SynEdit.SourceForge.net

  Known Issues:
  ------------------------------------------------------------------------------- */
#ifndef SynEditMiscProcsH
#define SynEditMiscProcsH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <System.Math.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"

namespace Syneditmiscprocs
{

/* -------------------------------------------------------------------------------
  The contents of this file are subject to the Mozilla Public License
  Version 1.1 (the "License"); you may not use this file except in compliance
  with the License. You may obtain a copy of the License at
  http://www.mozilla.org/MPL/

  Software distributed under the License is distributed on an "AS IS" basis,
  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
  the specific language governing rights and limitations under the License.

  The Original Code is: SynEditMiscProcs.pas, released 2000-04-07.
  The Original Code is based on the mwSupportProcs.pas file from the
  mwEdit component suite by Martin Waldenburg and other developers, the Initial
  Author of this file is Michael Hieke.
  Unicode translation by Maël Hörz.
  All Rights Reserved.

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

  $Id: SynEditMiscProcs.pas,v 1.35.2.8 2009/09/28 17:54:20 maelh Exp $

  You may retrieve the latest version of this file at the SynEdit home page,
  located at http://SynEdit.SourceForge.net

  Known Issues:
  ------------------------------------------------------------------------------- */

/*------------------------------------------------------------------------------*/
/* Common compiler defines                                                      */
/* (remove the dot in front of a define to enable it)                           */
/*------------------------------------------------------------------------------*/

/*$B-,H+*/ // defaults are short evaluation of boolean values and long strings

/*.$DEFINE SYN_DEVELOPMENT_CHECKS*/ // additional tests for debugging
  

/*------------------------------------------------------------------------------*/
/* Pull in all defines from SynEditJedi.inc (must be done after the common      */
/* compiler defines to  work correctly). Use SynEdit-prefix to avoid problems   */
/* with other versions of jedi.inc in the search-path.                          */
/*------------------------------------------------------------------------------*/

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

/*------------------------------------------------------------------------------*/
/*  Please change this to suit your needs (to activate an option remove the dot */
/*  in front of a DEFINE)                                                       */
/*------------------------------------------------------------------------------*/

// "Heredoc" syntax highlighting
// If you enable the following statement and use highlighter(s) that have
// support for "Heredoc" strings as scheme(s) in SynMultiSyn, you must
// implement your own SynMultiSyn OnCustomRange event handler in order to
// properly store Range State information
/*.$DEFINE SYN_HEREDOC*/

// Turn this off if you don't need complex script support, since it is slower
/*.$DEFINE SYN_UNISCRIBE*/

// $Id: SynEdit.inc,v 1.16.2.19 2009/06/14 13:41:44 maelh Exp $
const int MaxIntArraySize = (int)(System::MaxInt / /*div*/ 16);
typedef int TIntArray[134217727/*# range 0..MaxIntArraySize-1*/];
typedef TIntArray* PIntArray;
int __fastcall MinMax(int x, int mi, int ma);
void __fastcall SwapInt(int& l, int& r);
void __fastcall InternalFillRect(HDC dc, const TRect& rcPaint);

// Converting tabs to spaces: To use the function several times it's better
// to use a function pointer that is set to the fastest conversion function.
typedef String __fastcall (*TConvertTabsProc) (const String, int);
TConvertTabsProc __fastcall GetBestConvertTabsProc(int TabWidth);
// This is the slowest conversion function which can handle TabWidth <> 2^n.
String __fastcall ConvertTabs(const String Line, int TabWidth);
typedef String __fastcall (*TConvertTabsProcEx) (const String, int, bool&);
TConvertTabsProcEx __fastcall GetBestConvertTabsProcEx(int TabWidth);
// This is the slowest conversion function which can handle TabWidth <> 2^n.
String __fastcall ConvertTabsEx(const String Line, int TabWidth, bool& HasTabs);
int __fastcall GetExpandedLength(const String aStr, int aTabWidth);
int __fastcall CharIndex2CaretPos(int Index, int TabWidth, const String Line);
int __fastcall CaretPos2CharIndex(int Position, int TabWidth, const String Line, bool& InsideTabChar);

// search for the first char of set AChars in Line, starting at index Start
int __fastcall StrScanForCharInCategory(const String Line, int Start, Synedittypes::TCategoryMethod IsOfCategory);
// the same, but searching backwards
int __fastcall StrRScanForCharInCategory(const String Line, int Start, Synedittypes::TCategoryMethod IsOfCategory);
PWideChar __fastcall GetEOL(PChar P);
int __fastcall CountLines(const String S);
System::TArray<String> __fastcall StringToLines(const String Value);

// Remove all '/' characters from string by changing them into '\.'.
// Change all '\' characters into '\\' to allow for unique decoding.
String __fastcall EncodeString(String s);

// Decodes string, encoded with EncodeString.
String __fastcall DecodeString(String s);

  // Enums all child highlighters and their attributes of a TSynMultiSyn through a
  // callback function.
  // This function also handles nested TSynMultiSyns including their MarkerAttri.
typedef bool __fastcall (__closure *THighlighterAttriProc) (Synedithighlighter::TSynCustomHighlighter*, Synedithighlighter::TSynHighlighterAttributes*, String, void**, int Params_maxidx);
bool __fastcall EnumHighlighterAttris(Synedithighlighter::TSynCustomHighlighter* Highlighter, bool SkipDuplicates, THighlighterAttriProc HighlighterAttriProc, void** Params, int Params_maxidx);
void __fastcall SynDrawGradient(TCanvas* const ACanvas, const TColor AStartColor, const TColor AEndColor, int ASteps, const TRect& ARect, bool AHorizontal);
String __fastcall DeleteTypePrefixAndSynSuffix(String s);

// In Windows Vista or later use the Consolas font
String __fastcall DefaultFontName();
int __fastcall GrowCollection(int OldCapacity, int NewCount);


}  // namespace SynEditMiscProcs

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditmiscprocs;
#endif

#endif // SynEditMiscProcsH

