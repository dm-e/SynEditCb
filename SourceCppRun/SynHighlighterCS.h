#ifndef SynHighlighterCSH
#define SynHighlighterCSH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynEditMiscClasses.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "SynEditCodeFolding.h"

namespace Synhighlightercs
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterCS.pas, released 2001-10-28.
The Original Code is based on SynHighlighterCpp.pas, released 2000-04-10,
which in turn is based on the dcjCppSyn.pas file from the mwEdit component
suite by Martin Waldenburg and other developers, the Initial Author of this file
is Michael Trier.
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

$Id: SynHighlighterCS.pas,v 1.8.2.7 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of SynEdit from the SynEdit home page,
located at http://SynEdit.SourceForge.net

You may retrieve the latest version of this file from
http://www.ashleybrown.co.uk/synedit/

Known Issues:
  - strings on multiple lines are not supported 
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a C# syntax highlighter for SynEdit)
@author(Ashley Brown)
@created(2001)
@lastmod(2001-10-20)
The SynHighlighterCS unit provides SynEdit with a C# syntax highlighter.
Based on SynHighlighterCpp.pas
*/
//++ CodeFolding

//++ CodeFolding
enum TtkTokenKind {tkSymbol,
                   tkKey,
                   tkAsm,
                   tkComment,
                   tkDirective,
                   tkIdentifier,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkType,
                   tkUnknown };
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
                  rsMultiLineString };


//  TSynCSSyn = class(TSynCustomHighlighter)
//++ CodeFolding
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;
//-- CodeFolding

class TSynCSSyn : public Syneditcodefolding::TSynCustomCodeFoldingHighlighter
{
private:
	bool fAsmStart;
	TRangeState FRange;
	TtkTokenKind FTokenID;
	TxtkTokenKind FExtTokenID;
	TIdentFuncTableFunc fIdentFuncTable[211/*# range 0..210*/];
	Synedithighlighter::TSynHighlighterAttributes* fAsmAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDirecAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fInvalidAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fTypeAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall DataTypeFunc(int Index);
	TtkTokenKind __fastcall FuncAbstract(int Index);
	TtkTokenKind __fastcall FuncAs(int Index);
	TtkTokenKind __fastcall FuncBase(int Index);
	TtkTokenKind __fastcall FuncBreak(int Index);
	TtkTokenKind __fastcall FuncCase(int Index);
	TtkTokenKind __fastcall FuncCatch(int Index);
	TtkTokenKind __fastcall FuncClass(int Index);
	TtkTokenKind __fastcall FuncConst(int Index);
	TtkTokenKind __fastcall FuncContinue(int Index);
	TtkTokenKind __fastcall FuncDefault(int Index);
	TtkTokenKind __fastcall FuncDelegate(int Index);
	TtkTokenKind __fastcall FuncDo(int Index);
	TtkTokenKind __fastcall FuncElse(int Index);
	TtkTokenKind __fastcall FuncEnum(int Index);
	TtkTokenKind __fastcall FuncEvent(int Index);
	TtkTokenKind __fastcall FuncExplicit(int Index);
	TtkTokenKind __fastcall FuncExtern(int Index);
	TtkTokenKind __fastcall FuncFalse(int Index);
	TtkTokenKind __fastcall FuncFinally(int Index);
	TtkTokenKind __fastcall FuncFixed(int Index);
	TtkTokenKind __fastcall FuncFor(int Index);
	TtkTokenKind __fastcall FuncForeach(int Index);
	TtkTokenKind __fastcall FuncGoto(int Index);
	TtkTokenKind __fastcall FuncChecked(int Index);
	TtkTokenKind __fastcall FuncIf(int Index);
	TtkTokenKind __fastcall FuncImplicit(int Index);
	TtkTokenKind __fastcall FuncIn(int Index);
	TtkTokenKind __fastcall FuncInterface(int Index);
	TtkTokenKind __fastcall FuncInternal(int Index);
	TtkTokenKind __fastcall FuncIs(int Index);
	TtkTokenKind __fastcall FuncLock(int Index);
	TtkTokenKind __fastcall FuncNamespace(int Index);
	TtkTokenKind __fastcall FuncNew(int Index);
	TtkTokenKind __fastcall FuncNull(int Index);
	TtkTokenKind __fastcall FuncObject(int Index);
	TtkTokenKind __fastcall FuncOperator(int Index);
	TtkTokenKind __fastcall FuncOut(int Index);
	TtkTokenKind __fastcall FuncOverride(int Index);
	TtkTokenKind __fastcall FuncParams(int Index);
	TtkTokenKind __fastcall FuncPrivate(int Index);
	TtkTokenKind __fastcall FuncProtected(int Index);
	TtkTokenKind __fastcall FuncPublic(int Index);
	TtkTokenKind __fastcall FuncReadonly(int Index);
	TtkTokenKind __fastcall FuncRef(int Index);
	TtkTokenKind __fastcall FuncReturn(int Index);
	TtkTokenKind __fastcall FuncSealed(int Index);
	TtkTokenKind __fastcall FuncSizeof(int Index);
	TtkTokenKind __fastcall FuncStackalloc(int Index);
	TtkTokenKind __fastcall FuncStatic(int Index);
	TtkTokenKind __fastcall FuncStruct(int Index);
	TtkTokenKind __fastcall FuncSwitch(int Index);
	TtkTokenKind __fastcall FuncThis(int Index);
	TtkTokenKind __fastcall FuncThrow(int Index);
	TtkTokenKind __fastcall FuncTrue(int Index);
	TtkTokenKind __fastcall FuncTry(int Index);
	TtkTokenKind __fastcall FuncTypeof(int Index);
	TtkTokenKind __fastcall FuncUnchecked(int Index);
	TtkTokenKind __fastcall FuncUnsafe(int Index);
	TtkTokenKind __fastcall FuncUsing(int Index);
	TtkTokenKind __fastcall FuncVirtual(int Index);
	TtkTokenKind __fastcall FuncVoid(int Index);
	TtkTokenKind __fastcall FuncVolatile(int Index);
	TtkTokenKind __fastcall FuncWhile(int Index);
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
protected:
	TxtkTokenKind __fastcall GetExtTokenID();
	virtual bool __fastcall IsFilterStored();
	virtual String __fastcall GetSampleSource();
	void __fastcall NextProcedure();
public:
	typedef Syneditcodefolding::TSynCustomCodeFoldingHighlighter inherited;	
	#include "SynHighlighterCS_friends.inc"
	__classmethod virtual Synedithighlighter::TSynHighlighterCapabilities __fastcall GetCapabilities();
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynCSSyn(System::Classes::TComponent* AOwner);
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
	virtual void __fastcall EnumUserSettings(System::Classes::TStrings* Settings);
	__property TxtkTokenKind ExtTokenID = { read = GetExtTokenID };
//++ CodeFolding
	virtual void __fastcall ScanForFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, System::Classes::TStrings* LinesToScan, int FromLine, int ToLine);
//-- CodeFolding
__published:
	__property TSynHighlighterAttributes* AsmAttri = { read = fAsmAttri, write = fAsmAttri };
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* DirecAttri = { read = fDirecAttri, write = fDirecAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* InvalidAttri = { read = fInvalidAttri, write = fInvalidAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property TSynHighlighterAttributes* TypeAttri = { read = fTypeAttri, write = fTypeAttri };
};

void SynHighlighterCS_initialization();


}  // namespace SynHighlighterCS

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightercs;
#endif


#endif // SynHighlighterCSH

