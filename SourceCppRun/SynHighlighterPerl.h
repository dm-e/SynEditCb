#ifndef SynHighlighterPerlH
#define SynHighlighterPerlH

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

namespace Synhighlighterperl
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterPerl.pas, released 2000-04-10.
The Original Code is based on the DcjSynPerl.pas file from the
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

$Id: SynHighlighterPerl.pas,v 1.14.2.7 2005/12/16 20:09:37 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
  - Using q, qq, qw, qx, m, s, tr will not properly parse the contained
    information.
  - Not very optimized.
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Perl syntax highlighter for SynEdit)
@author(Michael Trier)
@created(1999, converted to SynEdit 2000-04-10 by Michael Hieke)
@lastmod(2000-06-23)
The SynHighlighterPerl unit provides SynEdit with a Perl syntax highlighter.
*/                                                                      //Fiala

//++ CodeFolding

//++ CodeFolding
enum TtkTokenKind {tkSymbol,
                   tkKey,
                   tkComment,
                   tkIdentifier,
                   tkNull,
                   tkNumber,
                   tkOperator,
                   tkPragma,
                   tkSpace,
                   tkString,
                   tkUnknown,
                   tkVariable };
enum TRangeState {rsUnKnown,
                  rsString,
                  rsQuotedString };


//  TSynPerlSyn = class(TSynCustomHighlighter)
//++ CodeFolding
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;
//-- CodeFolding

class TSynPerlSyn : public Syneditcodefolding::TSynCustomCodeFoldingHighlighter
{
private:
	TRangeState FRange;                                                        //Fiala
	TtkTokenKind FTokenID;
	TIdentFuncTableFunc fIdentFuncTable[2729/*# range 0..2728*/];                     //Fiala
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fInvalidAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fOperatorAttri;
	Synedithighlighter::TSynHighlighterAttributes* fPragmaAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVariableAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall FuncVar(int Index);
	TtkTokenKind __fastcall FuncKey(int Index);
	TtkTokenKind __fastcall FuncOperator(int Index);
	TtkTokenKind __fastcall FuncPragma(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall InitIdent();
	void __fastcall AndSymbolProc();
	void __fastcall CRProc();
	void __fastcall ColonProc();
	void __fastcall CommentProc();
	void __fastcall EqualProc();
	void __fastcall GreaterProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall LowerProc();
	void __fastcall MinusProc();
	void __fastcall NotSymbolProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall OrSymbolProc();
	void __fastcall PlusProc();
	void __fastcall qFunctionProc();
	void __fastcall SlashProc();
	void __fastcall SpaceProc();
	void __fastcall StarProc();
	void __fastcall StringInterpProc();
	void __fastcall StringLiteralProc();
	void __fastcall StringEndProc();
	void __fastcall SymbolProc();
	void __fastcall XOrSymbolProc();
	void __fastcall UnknownProc();
	void __fastcall VariableProc();                                                     //Fiala
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Syneditcodefolding::TSynCustomCodeFoldingHighlighter inherited;	
	#include "SynHighlighterPerl_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynPerlSyn(System::Classes::TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual bool __fastcall IsWordBreakChar(WideChar AChar);               //Fiala
	virtual void __fastcall Next();
	virtual void* __fastcall GetRange();                                      //Fiala
	virtual void __fastcall ResetRange();                                             //Fiala
	virtual void __fastcall SetRange(void* Value);                               //Fiala
//++ CodeFolding
	virtual void __fastcall ScanForFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, System::Classes::TStrings* LinesToScan, int FromLine, int ToLine);
//-- CodeFolding
__published:
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* InvalidAttri = { read = fInvalidAttri, write = fInvalidAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* OperatorAttri = { read = fOperatorAttri, write = fOperatorAttri };
	__property TSynHighlighterAttributes* PragmaAttri = { read = fPragmaAttri, write = fPragmaAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property TSynHighlighterAttributes* VariableAttri = { read = fVariableAttri, write = fVariableAttri };
};

void SynHighlighterPerl_initialization();


}  // namespace SynHighlighterPerl

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterperl;
#endif


#endif // SynHighlighterPerlH

