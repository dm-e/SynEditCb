/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditKeyCmds.pas, released 2000-04-07.
The Original Code is based on the mwKeyCmds.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Brad Stowers.
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

$Id: SynEditKeyCmds.pas,v 1.23.2.4 2008/09/14 16:24:58 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
// TODO: introduce friendly Names for the Commands (EditorCommandStrs is not good enough for end-users)
#ifndef SynEditKeyCmdsH
#define SynEditKeyCmdsH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Menus.hpp>
#include "SynUnicode.h"
#include <System.Classes.hpp>
#include "SynEditTypes.h"
#include <System.SysUtils.hpp>

namespace Syneditkeycmds
{

#define Syneditkeycmds__0 TShiftState()
/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditKeyCmds.pas, released 2000-04-07.
The Original Code is based on the mwKeyCmds.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Brad Stowers.
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

$Id: SynEditKeyCmds.pas,v 1.23.2.4 2008/09/14 16:24:58 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
// TODO: introduce friendly Names for the Commands (EditorCommandStrs is not good enough for end-users)


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

  //****************************************************************************
  // NOTE!  If you add an editor command, you must also update the
  //    EditorCommandStrs constant array in implementation section below, or the
  //    command will not show up in the IDE.
  //****************************************************************************

  // "Editor Commands".  Key strokes are translated from a table into these
  // I used constants instead of a set so that additional commands could be
  // added in descendants (you can't extend a set)

  // There are two ranges of editor commands: the ecViewXXX commands are always
  // valid, while the ecEditXXX commands are ignored when the editor is in
  // read-only mode
const int ecNone = 0; // Nothing. Useful for user event to handle command
const int ecViewCommandFirst = 0;
const int ecViewCommandLast = 500;
const int ecEditCommandFirst = 501;
const int ecEditCommandLast = 1000;
const int ecLeft = 1;    // Move cursor left one char
const int ecRight = 2;    // Move cursor right one char
const int ecUp = 3;    // Move cursor up one line
const int ecDown = 4;    // Move cursor down one line
const int ecWordLeft = 5;    // Move cursor left one word
const int ecWordRight = 6;    // Move cursor right one word
const int ecLineStart = 7;    // Move cursor to beginning of line
const int ecLineEnd = 8;    // Move cursor to end of line
const int ecPageUp = 9;    // Move cursor up one page
const int ecPageDown = 10;   // Move cursor down one page
const int ecPageLeft = 11;   // Move cursor right one page
const int ecPageRight = 12;   // Move cursor left one page
const int ecPageTop = 13;   // Move cursor to top of page
const int ecPageBottom = 14;   // Move cursor to bottom of page
const int ecEditorTop = 15;   // Move cursor to absolute beginning
const int ecEditorBottom = 16;   // Move cursor to absolute end
const int ecGotoXY = 17;   // Move cursor to specific coordinates, Data = PPoint

//******************************************************************************
// Maybe the command processor should just take a boolean that signifies if
// selection is affected or not?
//******************************************************************************
const int ecSelection = 100;  // Add this to ecXXX command to get equivalent
                            // command, but with selection enabled. This is not
                            // a command itself.
  // Same as commands above, except they affect selection, too
const int ecSelLeft = ecLeft + ecSelection;
const int ecSelRight = ecRight + ecSelection;
const int ecSelUp = ecUp + ecSelection;
const int ecSelDown = ecDown + ecSelection;
const int ecSelWordLeft = ecWordLeft + ecSelection;
const int ecSelWordRight = ecWordRight + ecSelection;
const int ecSelLineStart = ecLineStart + ecSelection;
const int ecSelLineEnd = ecLineEnd + ecSelection;
const int ecSelPageUp = ecPageUp + ecSelection;
const int ecSelPageDown = ecPageDown + ecSelection;
const int ecSelPageLeft = ecPageLeft + ecSelection;
const int ecSelPageRight = ecPageRight + ecSelection;
const int ecSelPageTop = ecPageTop + ecSelection;
const int ecSelPageBottom = ecPageBottom + ecSelection;
const int ecSelEditorTop = ecEditorTop + ecSelection;
const int ecSelEditorBottom = ecEditorBottom + ecSelection;
const int ecSelGotoXY = ecGotoXY + ecSelection;  // Data = PPoint
const int ecSelWord = 198;
const int ecSelectAll = 199;  // Select entire contents of editor, cursor to end
const int ecCopy = 201;  // Copy selection to clipboard
const int ecScrollUp = 211;  // Scroll up one line leaving cursor position unchanged.
const int ecScrollDown = 212;  // Scroll down one line leaving cursor position unchanged.
const int ecScrollLeft = 213;  // Scroll left one char leaving cursor position unchanged.
const int ecScrollRight = 214;  // Scroll right one char leaving cursor position unchanged.
const int ecInsertMode = 221;  // Set insert mode
const int ecOverwriteMode = 222;  // Set overwrite mode
const int ecToggleMode = 223;  // Toggle ins/ovr mode
const int ecNormalSelect = 231;  // Normal selection mode
const int ecColumnSelect = 232;  // Column selection mode
const int ecLineSelect = 233;  // Line selection mode
const int ecMatchBracket = 250;  // Go to matching bracket
const int ecCommentBlock = 251;  // Comment Block
const int ecGotoMarker0 = 301;  // Goto marker
const int ecGotoMarker1 = 302;  // Goto marker
const int ecGotoMarker2 = 303;  // Goto marker
const int ecGotoMarker3 = 304;  // Goto marker
const int ecGotoMarker4 = 305;  // Goto marker
const int ecGotoMarker5 = 306;  // Goto marker
const int ecGotoMarker6 = 307;  // Goto marker
const int ecGotoMarker7 = 308;  // Goto marker
const int ecGotoMarker8 = 309;  // Goto marker
const int ecGotoMarker9 = 310;  // Goto marker
const int ecSetMarker0 = 351;  // Set marker, Data = PPoint - X, Y Pos
const int ecSetMarker1 = 352;  // Set marker, Data = PPoint - X, Y Pos
const int ecSetMarker2 = 353;  // Set marker, Data = PPoint - X, Y Pos
const int ecSetMarker3 = 354;  // Set marker, Data = PPoint - X, Y Pos
const int ecSetMarker4 = 355;  // Set marker, Data = PPoint - X, Y Pos
const int ecSetMarker5 = 356;  // Set marker, Data = PPoint - X, Y Pos
const int ecSetMarker6 = 357;  // Set marker, Data = PPoint - X, Y Pos
const int ecSetMarker7 = 358;  // Set marker, Data = PPoint - X, Y Pos
const int ecSetMarker8 = 359;  // Set marker, Data = PPoint - X, Y Pos
const int ecSetMarker9 = 360;  // Set marker, Data = PPoint - X, Y Pos
const int ecGotFocus = 480;
const int ecLostFocus = 481;
const int ecContextHelp = 490;  // Help on Word, Data = Word
const int ecDeleteLastChar = 501;  // Delete last char (i.e. backspace key)
const int ecDeleteChar = 502;  // Delete char at cursor (i.e. delete key)
const int ecDeleteWord = 503;  // Delete from cursor to end of word
const int ecDeleteLastWord = 504;  // Delete from cursor to start of word
const int ecDeleteBOL = 505;  // Delete from cursor to beginning of line
const int ecDeleteEOL = 506;  // Delete from cursor to end of line
const int ecDeleteLine = 507;  // Delete current line
const int ecClearAll = 508;  // Delete everything
const int ecLineBreak = 509;  // Break line at current position, move caret to new line
const int ecInsertLine = 510;  // Break line at current position, leave caret
const int ecChar = 511;  // Insert a character at current position
const int ecImeStr = 550;  // Insert character(s) from IME
const int ecUndo = 601;  // Perform undo if available
const int ecRedo = 602;  // Perform redo if available
const int ecCut = 603;  // Cut selection to clipboard
const int ecPaste = 604;  // Paste clipboard to current position
const int ecBlockIndent = 610;  // Indent selection
const int ecBlockUnindent = 611;  // Unindent selection
const int ecTab = 612;  // Tab key
const int ecShiftTab = 613;  // Shift+Tab key
const int ecUpperCase = 620; // apply to the current selction or word
const int ecLowerCase = 621;
const int ecToggleCase = 622;
const int ecTitleCase = 623;
const int ecString = 630;  //Insert a whole string
const int ecAutoCompletion = 650;
const int ecCopyLineUp = 661;
const int ecCopyLineDown = 662;
const int ecMoveLineUp = 663;
const int ecMoveLineDown = 664;

  //++ CodeFolding
const int ecFoldAll = 701;
const int ecUnfoldAll = 702;
const int ecFoldNearest = 705;
const int ecUnfoldNearest = 706;
const int ecFoldLevel1 = 711;
const int ecFoldLevel2 = 712;
const int ecFoldLevel3 = 713;
const int ecUnfoldLevel1 = 721;
const int ecUnfoldLevel2 = 722;
const int ecUnfoldLevel3 = 723;
const int ecFoldRegions = 731;
const int ecUnfoldRegions = 732;
  //-- CodeFolding
const int ecUserFirst = 1001; // Start of user-defined commands

class ESynKeyError : public System::Sysutils::Exception
{
	#include "SynEditKeyCmds_friends.inc"
public:
	typedef System::Sysutils::Exception inherited;
	__fastcall ESynKeyError(const String Msg);
	__fastcall ESynKeyError(const String Msg, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynKeyError(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynKeyError(const String Msg, int AHelpContext);
	__fastcall ESynKeyError(System::NativeUInt Ident);
	__fastcall ESynKeyError(System::PResStringRec ResStringRec);
	__fastcall ESynKeyError(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynKeyError(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynKeyError(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynKeyError(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynKeyError(System::NativeUInt Ident, int AHelpContext);
	__fastcall ESynKeyError(System::PResStringRec ResStringRec, int AHelpContext);
};

class TSynEditKeyStroke : public System::Classes::TCollectionItem
{
private:
	WORD FKey;          // Virtual keycode, i.e. VK_xxx
	TShiftState FShift;
	WORD FKey2;
	TShiftState FShift2;
	Synedittypes::TSynEditorCommand FCommand;
	TShortCut __fastcall GetShortCut();
	TShortCut __fastcall GetShortCut2();
	void __fastcall SetCommand(Synedittypes::TSynEditorCommand Value);
	void __fastcall SetKey(WORD Value);
	void __fastcall SetKey2(WORD Value);
	void __fastcall SetShift(const TShiftState Value);
	void __fastcall SetShift2(const TShiftState Value);
	void __fastcall SetShortCut(const TShortCut Value);
	void __fastcall SetShortCut2(const TShortCut Value);
protected:
	virtual String __fastcall GetDisplayName();
public:
	typedef System::Classes::TCollectionItem inherited;
	#include "SynEditKeyCmds_friends.inc"
	virtual void __fastcall Assign(TPersistent* Source);
	void __fastcall LoadFromStream(TStream* AStream);
	void __fastcall SaveToStream(TStream* AStream);
    // No duplicate checking is done if assignment made via these properties!
	__property WORD key = { read = FKey, write = SetKey };
	__property WORD Key2 = { read = FKey2, write = SetKey2 };
	__property TShiftState Shift = { read = FShift, write = SetShift };
	__property TShiftState Shift2 = { read = FShift2, write = SetShift2 };
__published:
	__property Synedittypes::TSynEditorCommand Command = { read = FCommand, write = SetCommand };
	__property TShortCut ShortCut = { read = GetShortCut, write = SetShortCut, default = 0 };
	__property TShortCut ShortCut2 = { read = GetShortCut2, write = SetShortCut2, default = 0 };
public:
	__fastcall TSynEditKeyStroke(TCollection* Collection);
};

class TSynEditKeyStrokes : public System::Classes::TCollection
{
private:
	TPersistent* FOwner;
	TSynEditKeyStroke* __fastcall GetItem(int Index);
	void __fastcall SetItem(int Index, TSynEditKeyStroke* Value);
protected:
	DYNAMIC TPersistent* __fastcall GetOwner();
public:
	typedef System::Classes::TCollection inherited;
	#include "SynEditKeyCmds_friends.inc"
	__fastcall TSynEditKeyStrokes(TPersistent* AOwner);
	TSynEditKeyStroke* __fastcall Add();
//++ CodeFolding
	void __fastcall AddKey(Synedittypes::TSynEditorCommand ACmd, WORD AKey, const TShiftState AShift, WORD AKey2 = 0, const TShiftState AShift2 = Syneditkeycmds__0);
//-- CodeFolding
	virtual void __fastcall Assign(TPersistent* Source);
	int __fastcall FindCommand(Synedittypes::TSynEditorCommand cmd);
	int __fastcall FindKeycode(WORD Code, TShiftState Ss);
	int __fastcall FindKeycode2(WORD Code1, TShiftState SS1, WORD Code2, TShiftState SS2);
	int __fastcall FindShortcut(TShortCut SC);
	int __fastcall FindShortcut2(TShortCut SC, TShortCut SC2);
	void __fastcall LoadFromStream(TStream* AStream);
	void __fastcall ResetDefaults();
	void __fastcall SaveToStream(TStream* AStream);
	__property TSynEditKeyStroke* Items[int Index] = { read = GetItem, write = SetItem/*# default */ };
	__fastcall TSynEditKeyStrokes(TCollectionItemClass ItemClass);
};

// These are mainly for the TSynEditorCommand property editor, but could be
// useful elsewhere.
String __fastcall EditorCommandToDescrString(Synedittypes::TSynEditorCommand cmd);
String __fastcall EditorCommandToCodeString(Synedittypes::TSynEditorCommand cmd);
void __fastcall GetEditorCommandValues(TGetStrProc Proc);
void __fastcall GetEditorCommandExtended(TGetStrProc Proc);
bool __fastcall IdentToEditorCommand(const String Ident, int& cmd);
bool __fastcall EditorCommandToIdent(int cmd, String& Ident);
String __fastcall ConvertCodeStringToExtended(String AString);
String __fastcall ConvertExtendedToCodeString(String AString);
Synedittypes::TSynEditorCommand __fastcall ConvertExtendedToCommand(String AString);
Synedittypes::TSynEditorCommand __fastcall ConvertCodeStringToCommand(String AString);
int __fastcall IndexToEditorCommand(int AIndex);

void SynEditKeyCmds_initialization();


}  // namespace SynEditKeyCmds

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditkeycmds;
#endif


#endif // SynEditKeyCmdsH

