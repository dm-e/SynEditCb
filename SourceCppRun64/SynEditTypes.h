/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditTypes.pas, released 2000-04-07.
The Original Code is based on parts of mwCustomEdit.pas by Martin Waldenburg,
part of the mwEdit component suite.
Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
Unicode translation by Ma�l H�rz.
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

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef SynEditTypesH
#define SynEditTypesH

#include <System.hpp>
#include "d2c_system.h"

#include <System.Types.hpp>
#include <System.Math.hpp>
#include <Vcl.Controls.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "SynEditDelphiInstances.hpp"

namespace Synedittypes
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditTypes.pas, released 2000-04-07.
The Original Code is based on parts of mwCustomEdit.pas by Martin Waldenburg,
part of the mwEdit component suite.
Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
Unicode translation by Ma�l H�rz.
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

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

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

// These might need to be localized depending on the characterset because they might be
// interpreted as valid ident characters.
const System::WideChar SynTabGlyph = L'\x2192';       //'->'
const System::WideChar SynSoftBreakGlyph = L'\xac'; //'�'
const System::WideChar SynLineBreakGlyph = L'\xb6'; //'�'
const System::WideChar SynSpaceGlyph = L'\x2219';     //'�'

class ESynError : public System::Sysutils::Exception
{
	#include "SynEditTypes_friends.inc"
public:
	typedef System::Sysutils::Exception inherited;
	__fastcall ESynError(const String Msg);
	__fastcall ESynError(const String Msg, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynError(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynError(const String Msg, int AHelpContext);
	__fastcall ESynError(System::NativeUInt Ident);
	__fastcall ESynError(System::PResStringRec ResStringRec);
	__fastcall ESynError(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynError(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynError(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynError(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynError(System::NativeUInt Ident, int AHelpContext);
	__fastcall ESynError(System::PResStringRec ResStringRec, int AHelpContext);
};

  // DOS: CRLF, UNIX: LF, Mac: CR, Unicode: LINE SEPARATOR
enum TSynEditFileFormat {sffDos,
                         sffUnix,
                         sffMac,
                         sffUnicode };
enum TSynSearchOption {ssoMatchCase,
                       ssoWholeWord,
                       ssoBackwards,
                       ssoEntireScope,
                       ssoSelectedOnly,
                       ssoReplace,
                       ssoReplaceAll,
                       ssoPrompt };
typedef System::Set<TSynSearchOption, TSynSearchOption::ssoMatchCase, TSynSearchOption::ssoPrompt> TSynSearchOptions;
typedef bool __fastcall (__closure *TCategoryMethod) (WideChar);
typedef WORD TSynEditorCommand;
typedef void __fastcall (__closure *THookedCommandEvent) (TObject*, bool, bool&, TSynEditorCommand&, WideChar&, void*, void*);
typedef void __fastcall (__closure *TSynInfoLossEvent) (TEncoding*&, bool);
enum TSynSelectionMode {smNormal,
                        smLine,
                        smColumn };
typedef TSynSelectionMode* PSynSelectionMode;

struct TDisplayCoord
{
	int Column;
	int Row;
	friend bool __fastcall operator == (const TDisplayCoord& a, const TDisplayCoord& b);
	friend bool __fastcall operator != (const TDisplayCoord& a, const TDisplayCoord& b);
	friend bool __fastcall operator < (const TDisplayCoord& a, const TDisplayCoord& b);
	friend bool __fastcall operator <= (const TDisplayCoord& a, const TDisplayCoord& b);
	friend bool __fastcall operator > (const TDisplayCoord& a, const TDisplayCoord& b);
	friend bool __fastcall operator >= (const TDisplayCoord& a, const TDisplayCoord& b);
	static TDisplayCoord __fastcall Min(const TDisplayCoord& a, const TDisplayCoord& b);
	static TDisplayCoord __fastcall Max(const TDisplayCoord& a, const TDisplayCoord& b);
};

  /*  Helper methods for TControl - for backwward compatibility */
TDisplayCoord __fastcall DisplayCoord(int AColumn, int ARow);
TBufferCoord __fastcall BufferCoord(int AChar, int ALine);
String __fastcall LineBreakFromFileFormat(TSynEditFileFormat FileFormat);
/* ************************* For Word Wrap *********************************/

  // aIndex parameters of Line notifications are 0-based.
  // aRow parameter of GetRowLength() is 1-based.

    // conversion methods
__interface ISynEditBufferPlugin
{
	virtual TDisplayCoord __fastcall BufferToDisplayPos(const TBufferCoord& aPos) = 0;
	virtual TBufferCoord __fastcall DisplayToBufferPos(const TDisplayCoord& aPos) = 0;
	virtual int __fastcall RowCount() = 0;
	virtual int __fastcall GetRowLength(int aRow) = 0;
    // plugin notifications
	virtual int __fastcall LinesInserted(int aIndex, int aCount) = 0;
	virtual int __fastcall LinesDeleted(int aIndex, int aCount) = 0;
	virtual int __fastcall LinePut(int aIndex, const String OldLine) = 0;
    // font or size change
	virtual void __fastcall DisplayChanged() = 0;
    // pretty clear, heh?
	virtual void __fastcall Reset() = 0;
};

/* ************************* For Undo Redo *********************************/

  // Note: several undo entries can be chained together via the ChangeNumber
  // see also TCustomSynEdit.[Begin|End]UndoBlock methods
 // just restore the Caret, allowing better Undo behavior
 // restore Selection

    // for undo/redo of adding a character past EOL and repositioning the caret
enum TSynChangeReason {crNothing,
                       crInsert,
                       crDelete,
                       crSilentDelete,
                       crLineBreak,
                       crIndent,
                       crUnindent,
                       crCaret,
                       crSelection,
                       crWhiteSpaceAdd };

class TSynEditUndoItem : public System::TObject
{
	#include "SynEditTypes_friends.inc"
public:
	typedef System::TObject inherited;
	TBufferCoord ChangeStartPos;
	TBufferCoord ChangeEndPos;
	String ChangeStr;
	int ChangeNumber;
	TSynChangeReason ChangeReason;
	TSynSelectionMode ChangeSelMode;
    // the following undo item cannot be grouped with this one  when undoing
    // don't group the previous one with this one when redoing
	bool GroupBreak;
	__fastcall TSynEditUndoItem();
};

  /* Handles undo/redo and manages Modified status */
__interface ISynEditUndo
{
	virtual bool __fastcall GetModified() = 0;
	virtual int __fastcall GetMaxUndoActions() = 0;
	virtual bool __fastcall GetCanUndo() = 0;
	virtual bool __fastcall GetCanRedo() = 0;
	virtual bool __fastcall GetFullUndoImposible() = 0;
	virtual TNotifyEvent __fastcall GetOnModifiedChanged() = 0;
	virtual void __fastcall SetModified(bool Value) = 0;
	virtual void __fastcall SetMaxUndoActions(int Value) = 0;
	virtual void __fastcall SetGroupUndo(bool Value) = 0;
	virtual void __fastcall SetOnModifiedChanged(const TNotifyEvent Event) = 0;
	virtual void __fastcall SetCommandProcessed(TSynEditorCommand Command) = 0;
    /*  Begin/EndBlock pairs group undo actions together and also
       store/restore editor caret and selection
       We need to pass the Editor so that they works with chained SynEdits
    */
	virtual void __fastcall BeginBlock(TControl* Editor) = 0;
	virtual void __fastcall EndBlock(TControl* Editor) = 0;
    /* Lock disables undo/redo - useful if you are about to do a large number of
      changes and planning to clear undo afterwards */
	virtual void __fastcall Lock() = 0;
	virtual void __fastcall Unlock() = 0;
	virtual void __fastcall Clear() = 0;
    /* Call AddGroupBreak to signal that the next undo action
      cannot be grouped with the current one */
	virtual void __fastcall AddGroupBreak() = 0;
    /*Note: Undo/Redo are not reentrant*/
	virtual void __fastcall Undo(TControl* Editor) = 0;
	virtual void __fastcall Redo(TControl* Editor) = 0;
	__property bool CanRedo = { read = GetCanRedo };
	__property bool CanUndo = { read = GetCanUndo };
	__property bool GroupUndo = { write = SetGroupUndo };
	__property bool Modified = { read = GetModified, write = SetModified };
    /* Used by SynEdit to inform the Undo system about the command being
      processed */
	__property TSynEditorCommand CommandProcessed = { write = SetCommandProcessed };
    /* MaxUndoActions zero or less indicates unlimited undo. It grows as needed.
      If it is a positive number, when the limit is reached 1/4 of the
      Undo history is discarded to make space for following undo actions */
	__property int MaxUndoActions = { read = GetMaxUndoActions, write = SetMaxUndoActions };
	__property bool FullUndoImpossible = { read = GetFullUndoImposible };
	__property TNotifyEvent OnModifiedChanged = { read = GetOnModifiedChanged, write = SetOnModifiedChanged };
};


}  // namespace SynEditTypes

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synedittypes;
#endif

#endif // SynEditTypesH

