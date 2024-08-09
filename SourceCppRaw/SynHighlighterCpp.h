/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterCpp.pas, released 2000-04-10.
The Original Code is based on the dcjCppSyn.pas file from the
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

$Id: SynHighlighterCpp.pas,v 1.22.2.7 2006/05/21 11:59:35 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a C++ syntax highlighter for SynEdit)
@author(Michael Trier)
@created(1998)
@lastmod(2001-11-21)
The SynHighlighterCpp unit provides SynEdit with a C++ syntax highlighter.
Thanks to Martin Waldenburg.
*/
#ifndef SynHighlighterCppH
#define SynHighlighterCppH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include <System.SysUtils.hpp>
#include "SynUnicode.h"
#include <System.Classes.hpp>
#include "SynEditCodeFolding.h"

namespace Synhighlightercpp
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterCpp.pas, released 2000-04-10.
The Original Code is based on the dcjCppSyn.pas file from the
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

$Id: SynHighlighterCpp.pas,v 1.22.2.7 2006/05/21 11:59:35 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a C++ syntax highlighter for SynEdit)
@author(Michael Trier)
@created(1998)
@lastmod(2001-11-21)
The SynHighlighterCpp unit provides SynEdit with a C++ syntax highlighter.
Thanks to Martin Waldenburg.
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
enum TtkTokenKind {tkBracket,
                   tkKey,
                   tkSymbol,
                   tkAsm,
                   tkComment,
                   tkDirective,
                   tkIdentifier,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkUnknown,
                   tkChar,
                   tkFloat,
                   tkHex,
                   tkOctal };
enum TxtkTokenKind {xtkAdd,
                    xtkAddAssign,
                    xtkAnd,
                    xtkAndAssign,
                    xtkArrow,
                    xtkAssign,
                    xtkBitComplement,
                    xtkBraceClose,
                    xtkBraceOpen,
                    xtkColon,
                    xtkComma,
                    xtkDecrement,
                    xtkDivide,
                    xtkDivideAssign,
                    xtkEllipse,
                    xtkGreaterThan,
                    xtkGreaterThanEqual,
                    xtkIncOr,
                    xtkIncOrAssign,
                    xtkIncrement,
                    xtkLessThan,
                    xtkLessThanEqual,
                    xtkLogAnd,
                    xtkLogComplement,
                    xtkLogEqual,
                    xtkLogOr,
                    xtkMod,
                    xtkModAssign,
                    xtkMultiplyAssign,
                    xtkNotEqual,
                    xtkPoint,
                    xtkQuestion,
                    xtkRoundClose,
                    xtkRoundOpen,
                    xtkScopeResolution,
                    xtkSemiColon,
                    xtkShiftLeft,
                    xtkShiftLeftAssign,
                    xtkShiftRight,
                    xtkShiftRightAssign,
                    xtkSquareClose,
                    xtkSquareOpen,
                    xtkStar,
                    xtkSubtract,
                    xtkSubtractAssign,
                    xtkXor,
                    xtkXorAssign };
enum TRangeState {rsUnKnown,
                  rsAnsiC,
                  rsAnsiCAsm,
                  rsAnsiCAsmBlock,
                  rsAsm,
                  rsAsmBlock,
                  rsDirective,
                  rsDirectiveComment,
                  rsString34,
                  rsString39,
                  rsMultiLineString,
                  rsMultiLineDirective };


//  TSynCppSyn = class(TSynCustomHighlighter)
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynCppSyn : public Syneditcodefolding::TSynCustomCodeFoldingHighlighter
{
private:
	bool fAsmStart;
	TRangeState FRange;
	TtkTokenKind FTokenID;
	TxtkTokenKind FExtTokenID;
	TIdentFuncTableFunc fIdentFuncTable[641/*# range 0..640*/];
	Synedithighlighter::TSynHighlighterAttributes* fAsmAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDirecAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fInvalidAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fFloatAttri;
	Synedithighlighter::TSynHighlighterAttributes* fHexAttri;
	Synedithighlighter::TSynHighlighterAttributes* fOctalAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCharAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fBracketAttri;
	bool FNewPreprocesorStyle;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall KeyWordFunc(int Index);
	TtkTokenKind __fastcall FuncAsm(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall InitIdent();
	void __fastcall AnsiCProc();
	void __fastcall AndSymbolProc();
	void __fastcall AsciiCharProc();
	void __fastcall AtSymbolProc();
	void __fastcall BraceCloseProc();
	void __fastcall BraceOpenProc();
	void __fastcall CRProc();
	void __fastcall ColonProc();
	void __fastcall CommaProc();
	void __fastcall DirectiveProc();
	void __fastcall DirectiveEndProc();
	void __fastcall EqualProc();
	void __fastcall GreaterProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall LowerProc();
	void __fastcall MinusProc();
	void __fastcall ModSymbolProc();
	void __fastcall NotSymbolProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall OrSymbolProc();
	void __fastcall PlusProc();
	void __fastcall PointProc();
	void __fastcall QuestionProc();
	void __fastcall RoundCloseProc();
	void __fastcall RoundOpenProc();
	void __fastcall SemiColonProc();
	void __fastcall SlashProc();
	void __fastcall SpaceProc();
	void __fastcall SquareCloseProc();
	void __fastcall SquareOpenProc();
	void __fastcall StarProc();
	void __fastcall StringProc();
	void __fastcall TildeProc();
	void __fastcall XOrSymbolProc();
	void __fastcall UnknownProc();
	void __fastcall StringEndProc();
	void __fastcall SetNewPreprocesorStyle(bool Value);
protected:
	TxtkTokenKind __fastcall GetExtTokenID();
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Syneditcodefolding::TSynCustomCodeFoldingHighlighter inherited;
	__classmethod virtual Synedithighlighter::TSynHighlighterCapabilities __fastcall GetCapabilities();
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynCppSyn(TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
	virtual bool __fastcall UseUserSettings(int settingIndex);
	virtual void __fastcall EnumUserSettings(TStrings* Settings);
	__property TxtkTokenKind ExtTokenID = { read = GetExtTokenID };
	__property bool NewPreprocesorStyle = { read = FNewPreprocesorStyle, write = SetNewPreprocesorStyle };
//++ CodeFolding
	virtual void __fastcall ScanForFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine);
//-- CodeFolding
__published:
	__property Synedithighlighter::TSynHighlighterAttributes* AsmAttri = { read = fAsmAttri, write = fAsmAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* BracketAttri = { read = fBracketAttri, write = fBracketAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* DirecAttri = { read = fDirecAttri, write = fDirecAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* InvalidAttri = { read = fInvalidAttri, write = fInvalidAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* FloatAttri = { read = fFloatAttri, write = fFloatAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* HexAttri = { read = fHexAttri, write = fHexAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* OctalAttri = { read = fOctalAttri, write = fOctalAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* CharAttri = { read = fCharAttri, write = fCharAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
};

void SynHighlighterCpp_initialization();


}  // namespace SynHighlighterCpp

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightercpp;
#endif


#endif // SynHighlighterCppH

