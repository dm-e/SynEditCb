#ifndef SynHighlighterBatH
#define SynHighlighterBatH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterbat
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterBat.pas, released 2000-04-18.
The Original Code is based on the dmBatSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is David H. Muir.
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

$Id: SynHighlighterBat.pas,v 1.14.2.6 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a MS-DOS Batch file highlighter for SynEdit)
@author(David Muir <dhm@dmsoftware.co.uk>)
@created(Late 1999)
@lastmod(May 19, 2000)
The SynHighlighterBat unit provides SynEdit with a MS-DOS Batch file (.bat) highlighter.
The highlighter supports the formatting of keywords and parameters (batch file arguments).
*/
enum TtkTokenKind {tkComment,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkUnknown,
                   tkVariable };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynBatSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TIdentFuncTableFunc fIdentFuncTable[25/*# range 0..24*/];
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVariableAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall FuncCall(int Index);
	TtkTokenKind __fastcall FuncCd(int Index);
	TtkTokenKind __fastcall FuncCls(int Index);
	TtkTokenKind __fastcall FuncCopy(int Index);
	TtkTokenKind __fastcall FuncDel(int Index);
	TtkTokenKind __fastcall FuncDo(int Index);
	TtkTokenKind __fastcall FuncEcho(int Index);
	TtkTokenKind __fastcall FuncErrorlevel(int Index);
	TtkTokenKind __fastcall FuncExist(int Index);
	TtkTokenKind __fastcall FuncFor(int Index);
	TtkTokenKind __fastcall FuncGoto(int Index);
	TtkTokenKind __fastcall FuncIf(int Index);
	TtkTokenKind __fastcall FuncIn(int Index);
	TtkTokenKind __fastcall FuncNot(int Index);
	TtkTokenKind __fastcall FuncOff(int Index);
	TtkTokenKind __fastcall FuncOn(int Index);
	TtkTokenKind __fastcall FuncPause(int Index);
	TtkTokenKind __fastcall FuncSet(int Index);
	TtkTokenKind __fastcall FuncShift(int Index);
	TtkTokenKind __fastcall FuncStart(int Index);
	TtkTokenKind __fastcall FuncTitle(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall InitIdent();
	void __fastcall VariableProc();
	void __fastcall CRProc();
	void __fastcall CommentProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall REMCommentProc();
	void __fastcall SpaceProc();
	void __fastcall UnknownProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	#include "SynHighlighterBat_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynBatSyn(System::Classes::TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
__published:
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* VariableAttri = { read = fVariableAttri, write = fVariableAttri };
};

void SynHighlighterBat_initialization();


}  // namespace SynHighlighterBat

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterbat;
#endif


#endif // SynHighlighterBatH

