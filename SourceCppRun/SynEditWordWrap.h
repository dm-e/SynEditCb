#ifndef SynEditWordWrapH
#define SynEditWordWrapH

#include <System.hpp>
#include "d2c_system.h"

#include "SynEditTypes.h"
#include "SynEditTextBuffer.h"
#include "SynEdit.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

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

The Original Code is SynEditWordWrap.pas by Fl�vio Etrusco, released 2003-12-11.
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

$Id: SynEditWordWrap.pas,v 1.8.2.6 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
//todo: Use a single implementation of ReWrapLines that takes starting line and number of lines to rewrap
//todo: Tweak code to try finding better wrapping points. Some support by the highlighters will be needed, probably.
//todo: Document the code
//todo: The length of the last Row of a Line could be calculated from the Line length instead of being stored. This would be only useful when most of the lines aren't wrapped.
const int MaxIndex = (int)(System::MaxInt / 16);
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
	#include "SynEditWordWrap_friends.inc"
public:
	typedef System::TCppInterfacedObject<Synedittypes::ISynEditBufferPlugin> inherited;
	INTFOBJECT_IMPL_IUNKNOWN(System::TInterfacedObject)
private:
	PRowIndexArray fLineOffsets;
	PRowLengthArray fRowLengths;
	int fLineCapacity;
	int fRowCapacity;
	int fLineCount;
	Synedit::TCustomSynEdit* FEditor;
	TRowLength fMinRowLength;
	TRowLength fMaxRowLength;
	void __fastcall GrowLines(int aMinSize);
	void __fastcall MoveLines(TLineIndex AStart, int aMoveBy);
	void __fastcall GrowRows(int aMinSize);
	void __fastcall MoveRows(TRowIndex AStart, int aMoveBy);
	void __fastcall SetEmpty();
protected:
	void __fastcall WrapLines();
	int __fastcall ReWrapLine(TLineIndex AIndex);
	void __fastcall TrimArrays();
	__property PRowIndexArray LineOffsets = { read = fLineOffsets };
	__property PRowLengthArray RowLengths = { read = fRowLengths };
	__property Synedit::TCustomSynEdit* Editor = { read = FEditor };
public:
	__fastcall TSynWordWrapPlugin(Synedit::TCustomSynEdit* AOwner);
	virtual __fastcall ~TSynWordWrapPlugin();
    /* ISynEditBufferPlugin */
	Synedit::TDisplayCoord __fastcall BufferToDisplayPos(const Synedit::TBufferCoord& APos);
	Synedit::TBufferCoord __fastcall DisplayToBufferPos(const Synedit::TDisplayCoord& APos);
	int __fastcall RowCount();
	int __fastcall GetRowLength(int ARow);
	int __fastcall LinesInserted(int AIndex, int ACount);
	int __fastcall LinesDeleted(int AIndex, int ACount);
	int __fastcall LinePut(int AIndex, const String OldLine);
	void __fastcall Reset();
	void __fastcall DisplayChanged();
	__fastcall TSynWordWrapPlugin();
};


}  // namespace SynEditWordWrap

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditwordwrap;
#endif

#endif // SynEditWordWrapH

