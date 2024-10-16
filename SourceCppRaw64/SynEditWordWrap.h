/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is SynEditWordWrap.pas by Flávio Etrusco, released 2003-12-11.
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

$Id: SynEditWordWrap.pas,v 1.8.2.6 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
//todo: Use a single implementation of ReWrapLines that takes starting line and number of lines to rewrap
//todo: Tweak code to try finding better wrapping points. Some support by the highlighters will be needed, probably.
//todo: Document the code
//todo: The length of the last Row of a Line could be calculated from the Line length instead of being stored. This would be only useful when most of the lines aren't wrapped.
#ifndef SynEditWordWrapH
#define SynEditWordWrapH

#include <System.hpp>
#include "d2c_system.h"

#include "SynEditTypes.h"
#include "SynEditTextBuffer.h"
#include "SynEdit.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "SynEditDelphiInstances.hpp"

namespace Syneditwordwrap
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is SynEditWordWrap.pas by Flávio Etrusco, released 2003-12-11.
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

$Id: SynEditWordWrap.pas,v 1.8.2.6 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
//todo: Use a single implementation of ReWrapLines that takes starting line and number of lines to rewrap
//todo: Tweak code to try finding better wrapping points. Some support by the highlighters will be needed, probably.
//todo: Document the code
//todo: The length of the last Row of a Line could be calculated from the Line length instead of being stored. This would be only useful when most of the lines aren't wrapped.


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
const int MaxIndex = (int)(System::MaxInt / /*div*/ 16);
typedef int /*0..MaxIndex*/ TLineIndex;
typedef int /*0..MaxIndex*/ TRowIndex;
typedef WORD TRowLength;
typedef TRowIndex TRowIndexArray[MaxIndex+1/*# TLineIndex*/];
typedef TRowIndexArray* PRowIndexArray;
typedef TRowLength TRowLengthArray[MaxIndex+1/*# TRowIndex*/];
typedef TRowLengthArray* PRowLengthArray;

  // For clarity, I'll refer to buffer coordinates as 'Line' and
  // 'Char' and to display (wrapped) coordinates as 'Row' and 'Column'.

  // fLineOffsets[n] is the index of the first row of the [n+1]th line.
  // e.g. Starting row of first line (0) is 0. Starting row of second line (1)
  // is fLineOffsets[0]. Clear?

class TSynWordWrapPlugin : public System::TCppInterfacedObject<Synedittypes::ISynEditBufferPlugin>
{

public:
	typedef System::TCppInterfacedObject<Synedittypes::ISynEditBufferPlugin> inherited;
private:
	PRowIndexArray fLineOffsets;
	PRowLengthArray fRowLengths;
	int fLineCapacity;
	int fRowCapacity;
	int fLineCount;
	Synedit::TCustomSynEdit* fEditor;
	TRowLength fMinRowLength;
	TRowLength fMaxRowLength;
	void __fastcall GrowLines(int aMinSize);
	void __fastcall MoveLines(TLineIndex aStart, int aMoveBy);
	void __fastcall GrowRows(int aMinSize);
	void __fastcall MoveRows(TRowIndex aStart, int aMoveBy);
	void __fastcall SetEmpty();
protected:
	void __fastcall WrapLines();
	int __fastcall ReWrapLine(TLineIndex aIndex);
	void __fastcall TrimArrays();
	__property PRowIndexArray LineOffsets = { read = fLineOffsets };
	__property PRowLengthArray RowLengths = { read = fRowLengths };
	__property Synedit::TCustomSynEdit* Editor = { read = fEditor };
public:
	__fastcall TSynWordWrapPlugin(Synedit::TCustomSynEdit* aOwner);
	virtual __fastcall ~TSynWordWrapPlugin();
    /* ISynEditBufferPlugin */
	Synedittypes::TDisplayCoord __fastcall BufferToDisplayPos(const TBufferCoord& aPos);
	TBufferCoord __fastcall DisplayToBufferPos(const Synedittypes::TDisplayCoord& aPos);
	int __fastcall RowCount();
	int __fastcall GetRowLength(int aRow);
	int __fastcall LinesInserted(int aIndex, int aCount);
	int __fastcall LinesDeleted(int aIndex, int aCount);
	int __fastcall LinePut(int aIndex, const String OldLine);
	void __fastcall Reset();
	void __fastcall DisplayChanged();
	__fastcall TSynWordWrapPlugin();
};


}  // namespace SynEditWordWrap

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditwordwrap;
#endif

#endif // SynEditWordWrapH

