/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterSDD.pas, released 2001-08-20.
The Initial Author of this file is Pieter Polak.
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

$Id: SynHighlighterSDD.pas,v 1.13.2.6 2008/09/14 16:25:03 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------*/
#ifndef SynHighlighterSDDH
#define SynHighlighterSDDH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlightersdd
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterSDD.pas, released 2001-08-20.
The Initial Author of this file is Pieter Polak.
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

$Id: SynHighlighterSDD.pas,v 1.13.2.6 2008/09/14 16:25:03 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

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
enum TtkTokenKind {tkComment,
                   tkIdentifier,
                   tkKey,
                   tkDatatype,
                   tkNumber,
                   tkNull,
                   tkSpace,
                   tkSymbol,
                   tkUnknown };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;
enum TRangeState {rsComment,
                  rsUnKnown };

class TSynSDDSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState fRange;
	TtkTokenKind fTokenID;
	TIdentFuncTableFunc fIdentFuncTable[37/*# range 0..36*/];
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDatatypeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall FuncArray(int Index);
	TtkTokenKind __fastcall FuncBinarydata(int Index);
	TtkTokenKind __fastcall FuncBlock(int Index);
	TtkTokenKind __fastcall FuncByte(int Index);
	TtkTokenKind __fastcall FuncDatabase(int Index);
	TtkTokenKind __fastcall FuncDate(int Index);
	TtkTokenKind __fastcall FuncEnd(int Index);
	TtkTokenKind __fastcall FuncEndblock(int Index);
	TtkTokenKind __fastcall FuncInteger(int Index);
	TtkTokenKind __fastcall FuncKeys(int Index);
	TtkTokenKind __fastcall FuncLongint(int Index);
	TtkTokenKind __fastcall FuncMemotext(int Index);
	TtkTokenKind __fastcall FuncObject(int Index);
	TtkTokenKind __fastcall FuncObjects(int Index);
	TtkTokenKind __fastcall FuncOf(int Index);
	TtkTokenKind __fastcall FuncOwner(int Index);
	TtkTokenKind __fastcall FuncPartition(int Index);
	TtkTokenKind __fastcall FuncPartitions(int Index);
	TtkTokenKind __fastcall FuncPrimary(int Index);
	TtkTokenKind __fastcall FuncReal(int Index);
	TtkTokenKind __fastcall FuncSecondary(int Index);
	TtkTokenKind __fastcall FuncSpec(int Index);
	TtkTokenKind __fastcall FuncString(int Index);
	TtkTokenKind __fastcall FuncSuperblock(int Index);
	TtkTokenKind __fastcall FuncSuperspec(int Index);
	TtkTokenKind __fastcall FuncTime(int Index);
	TtkTokenKind __fastcall FuncVar(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar MayBe);
	void __fastcall InitIdent();
	void __fastcall BraceOpenProc();
	void __fastcall BraceCommentProc();
	void __fastcall NumberProc();
	void __fastcall CRProc();
	void __fastcall LFProc();
	void __fastcall IdentProc();
	void __fastcall NullProc();
	void __fastcall SpaceProc();
	void __fastcall UnknownProc();
	void __fastcall SymbolProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	virtual void* __fastcall GetRange();
	virtual void __fastcall ResetRange();
	virtual void __fastcall SetRange(void* Value);
	__fastcall TSynSDDSyn(TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
__published:
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* DatatypeAttri = { read = fDatatypeAttri, write = fDatatypeAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
};

void SynHighlighterSDD_initialization();


}  // namespace SynHighlighterSDD

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightersdd;
#endif


#endif // SynHighlighterSDDH

