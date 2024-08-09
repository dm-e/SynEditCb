/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterJava.pas, released 2000-04-10.
The Original Code is based on the DcjSynJava.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Michael Trier.
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

$Id: SynHighlighterJava.pas,v 1.18.2.8 2005/12/16 20:09:37 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Java highlighter for SynEdit)
@author(Michael Trier)
@created(December 1998, converted to SynEdit 2000-04-10 by Michael Hieke)
@lastmod(2000-06-23)
The SynHighlighterJava unit provides SynEdit with a Java source (.java) highlighter.
*/
#ifndef SynHighlighterJavaH
#define SynHighlighterJavaH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include "SynUnicode.h"
#include <System.Classes.hpp>
#include "SynEditCodeFolding.h"

namespace Synhighlighterjava
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterJava.pas, released 2000-04-10.
The Original Code is based on the DcjSynJava.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Michael Trier.
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

$Id: SynHighlighterJava.pas,v 1.18.2.8 2005/12/16 20:09:37 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Java highlighter for SynEdit)
@author(Michael Trier)
@created(December 1998, converted to SynEdit 2000-04-10 by Michael Hieke)
@lastmod(2000-06-23)
The SynHighlighterJava unit provides SynEdit with a Java source (.java) highlighter.
*/

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

//++ CodeFolding

//++ CodeFolding
enum TtkTokenKind {tkSymbol,
                   tkKey,
                   tkComment,
                   tkDocument,
                   tkIdentifier,
                   tkInvalid,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkUnknown };
enum TxtkTokenKind {xtkAdd,
                    xtkAddAssign,
                    xtkAnd,
                    xtkAndAssign,
                    xtkAssign,
                    xtkBitComplement,
                    xtkBraceClose,
                    xtkBraceOpen,
                    xtkColon,
                    xtkCondAnd,
                    xtkCondOr,
                    xtkDecrement,
                    xtkDivide,
                    xtkDivideAssign,
                    xtkGreaterThan,
                    xtkGreaterThanEqual,
                    xtkIncOr,
                    xtkIncOrAssign,
                    xtkIncrement,
                    xtkLessThan,
                    xtkLessThanEqual,
                    xtkLogComplement,
                    xtkLogEqual,
                    xtkMultiply,
                    xtkMultiplyAssign,
                    xtkNotEqual,
                    xtkPoint,
                    xtkQuestion,
                    xtkRemainder,
                    xtkRemainderAssign,
                    xtkRoundClose,
                    xtkRoundOpen,
                    xtkSemiColon,
                    xtkShiftLeft,
                    xtkShiftLeftAssign,
                    xtkShiftRight,
                    xtkShiftRightAssign,
                    xtkSquareClose,
                    xtkSquareOpen,
                    xtkSubtract,
                    xtkSubtractAssign,
                    xtkUnsignShiftRight,
                    xtkUnsignShiftRightAssign,
                    xtkXor,
                    xtkXorAssign,
                    xtkComma };
enum TRangeState {rsANil,
                  rsComment,
                  rsDocument,
                  rsUnKnown };


//  TSynJavaSyn = class(TSynCustomHighlighter)
//++ CodeFolding
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;
//-- CodeFolding

class TSynJavaSyn : public Syneditcodefolding::TSynCustomCodeFoldingHighlighter
{
private:
	TRangeState FRange;
	int FRoundCount;
	int FSquareCount;
	TtkTokenKind FTokenID;
	TxtkTokenKind FExtTokenID;
	TIdentFuncTableFunc fIdentFuncTable[113/*# range 0..112*/];
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDocumentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fInvalidAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall KeyWordFunc(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall InitIdent();
	void __fastcall CommentProc();
	void __fastcall AndSymbolProc();
	void __fastcall AsciiCharProc();
	void __fastcall AtSymbolProc();
	void __fastcall BraceCloseProc();
	void __fastcall BraceOpenProc();
	void __fastcall CRProc();
	void __fastcall ColonProc();
	void __fastcall CommaProc();
	void __fastcall EqualProc();
	void __fastcall GreaterProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall LowerProc();
	void __fastcall MinusProc();
	void __fastcall MultiplyProc();
	void __fastcall NotSymbolProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall OrSymbolProc();
	void __fastcall PlusProc();
	void __fastcall PointProc();
	void __fastcall PoundProc();
	void __fastcall QuestionProc();
	void __fastcall RemainderSymbolProc();
	void __fastcall RoundCloseProc();
	void __fastcall RoundOpenProc();
	void __fastcall SemiColonProc();
	void __fastcall SlashProc();
	void __fastcall SpaceProc();
	void __fastcall SquareCloseProc();
	void __fastcall SquareOpenProc();
	void __fastcall StringProc();
	void __fastcall TildeProc();
	void __fastcall XOrSymbolProc();
	void __fastcall UnknownProc();
protected:
	virtual String __fastcall GetSampleSource();
	TxtkTokenKind __fastcall GetExtTokenID();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Syneditcodefolding::TSynCustomCodeFoldingHighlighter inherited;
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynJavaSyn(TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual void __fastcall Next();
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
	__property TxtkTokenKind ExtTokenID = { read = GetExtTokenID };
//++ CodeFolding
	virtual void __fastcall ScanForFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine);
//-- CodeFolding
__published:
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* DocumentAttri = { read = fDocumentAttri, write = fDocumentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* InvalidAttri = { read = fInvalidAttri, write = fInvalidAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
};

void SynHighlighterJava_initialization();


}  // namespace SynHighlighterJava

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterjava;
#endif


#endif // SynHighlighterJavaH

