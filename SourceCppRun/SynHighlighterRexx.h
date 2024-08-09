/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

Code template generated with SynGen.
The original code is: D:\GDS\rexx\synedit\SynHighlighterRexx.pas, released 2016-03-23.
Description: Syntax Parser/Highlighter
The initial author of this file is gds.
Copyright (c) 2016, all rights reserved.

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

$Id: $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------*/
#ifndef SynHighlighterRexxH
#define SynHighlighterRexxH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterrexx
{


enum TtkTokenKind {tkComment,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkSpace,
                   tkSpecial,
                   tkStdFunction,
                   tkString,
                   tkUnknown };
enum TRangeState {rsUnKnown,
                  rsMultilineComment,
                  rsSinglelineComment,
                  rsStringDouble,
                  rsStringSingle };
typedef void __fastcall (__closure *TProcTableProc) ();
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynRexxSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState FRange;
	TtkTokenKind FTokenID;
	TIdentFuncTableFunc fIdentFuncTable[349/*# range 0..348*/];
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpecialAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStdFunctionAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall FuncAbbrev(int Index);
	TtkTokenKind __fastcall FuncAbs(int Index);
	TtkTokenKind __fastcall FuncAddress(int Index);
	TtkTokenKind __fastcall FuncArg(int Index);
	TtkTokenKind __fastcall FuncB2x(int Index);
	TtkTokenKind __fastcall FuncBitand(int Index);
	TtkTokenKind __fastcall FuncBitor(int Index);
	TtkTokenKind __fastcall FuncBitxor(int Index);
	TtkTokenKind __fastcall FuncC2d(int Index);
	TtkTokenKind __fastcall FuncC2x(int Index);
	TtkTokenKind __fastcall FuncCall(int Index);
	TtkTokenKind __fastcall FuncCenter(int Index);
	TtkTokenKind __fastcall FuncCentre(int Index);
	TtkTokenKind __fastcall FuncChangestr(int Index);
	TtkTokenKind __fastcall FuncCharin(int Index);
	TtkTokenKind __fastcall FuncCharout(int Index);
	TtkTokenKind __fastcall FuncChars(int Index);
	TtkTokenKind __fastcall FuncCompare(int Index);
	TtkTokenKind __fastcall FuncCondition(int Index);
	TtkTokenKind __fastcall FuncCopies(int Index);
	TtkTokenKind __fastcall FuncD2c(int Index);
	TtkTokenKind __fastcall FuncD2x(int Index);
	TtkTokenKind __fastcall FuncDatatype(int Index);
	TtkTokenKind __fastcall FuncDate(int Index);
	TtkTokenKind __fastcall FuncDelstr(int Index);
	TtkTokenKind __fastcall FuncDelword(int Index);
	TtkTokenKind __fastcall FuncDigits(int Index);
	TtkTokenKind __fastcall FuncDo(int Index);
	TtkTokenKind __fastcall FuncDrop(int Index);
	TtkTokenKind __fastcall FuncElse(int Index);
	TtkTokenKind __fastcall FuncEnd(int Index);
	TtkTokenKind __fastcall FuncErrortext(int Index);
	TtkTokenKind __fastcall FuncExit(int Index);
	TtkTokenKind __fastcall FuncForm(int Index);
	TtkTokenKind __fastcall FuncFormat(int Index);
	TtkTokenKind __fastcall FuncFuzz(int Index);
	TtkTokenKind __fastcall FuncIf(int Index);
	TtkTokenKind __fastcall FuncInsert(int Index);
	TtkTokenKind __fastcall FuncInterpret(int Index);
	TtkTokenKind __fastcall FuncIterate(int Index);
	TtkTokenKind __fastcall FuncJustify(int Index);
	TtkTokenKind __fastcall FuncLastpos(int Index);
	TtkTokenKind __fastcall FuncLeave(int Index);
	TtkTokenKind __fastcall FuncLeft(int Index);
	TtkTokenKind __fastcall FuncLength(int Index);
	TtkTokenKind __fastcall FuncLinein(int Index);
	TtkTokenKind __fastcall FuncLineout(int Index);
	TtkTokenKind __fastcall FuncLines(int Index);
	TtkTokenKind __fastcall FuncLinesize(int Index);
	TtkTokenKind __fastcall FuncMax(int Index);
	TtkTokenKind __fastcall FuncMin(int Index);
	TtkTokenKind __fastcall FuncNop(int Index);
	TtkTokenKind __fastcall FuncNumeric(int Index);
	TtkTokenKind __fastcall FuncOptions(int Index);
	TtkTokenKind __fastcall FuncOtherwise(int Index);
	TtkTokenKind __fastcall FuncOverlay(int Index);
	TtkTokenKind __fastcall FuncParse(int Index);
	TtkTokenKind __fastcall FuncPos(int Index);
	TtkTokenKind __fastcall FuncProcedure(int Index);
	TtkTokenKind __fastcall FuncPull(int Index);
	TtkTokenKind __fastcall FuncPush(int Index);
	TtkTokenKind __fastcall FuncQueue(int Index);
	TtkTokenKind __fastcall FuncQueued(int Index);
	TtkTokenKind __fastcall FuncRandom(int Index);
	TtkTokenKind __fastcall FuncReturn(int Index);
	TtkTokenKind __fastcall FuncReverse(int Index);
	TtkTokenKind __fastcall FuncRight(int Index);
	TtkTokenKind __fastcall FuncRxfuncadd(int Index);
	TtkTokenKind __fastcall FuncRxfuncdrop(int Index);
	TtkTokenKind __fastcall FuncRxfuncquery(int Index);
	TtkTokenKind __fastcall FuncSay(int Index);
	TtkTokenKind __fastcall FuncSelect(int Index);
	TtkTokenKind __fastcall FuncSignal(int Index);
	TtkTokenKind __fastcall FuncSourceline(int Index);
	TtkTokenKind __fastcall FuncSpace(int Index);
	TtkTokenKind __fastcall FuncStream(int Index);
	TtkTokenKind __fastcall FuncStrip(int Index);
	TtkTokenKind __fastcall FuncSubstr(int Index);
	TtkTokenKind __fastcall FuncSubword(int Index);
	TtkTokenKind __fastcall FuncSymbol(int Index);
	TtkTokenKind __fastcall FuncThen(int Index);
	TtkTokenKind __fastcall FuncTime(int Index);
	TtkTokenKind __fastcall FuncTrace(int Index);
	TtkTokenKind __fastcall FuncTranslate(int Index);
	TtkTokenKind __fastcall FuncTrunc(int Index);
	TtkTokenKind __fastcall FuncUpper(int Index);
	TtkTokenKind __fastcall FuncValue(int Index);
	TtkTokenKind __fastcall FuncVar(int Index);
	TtkTokenKind __fastcall FuncVerify(int Index);
	TtkTokenKind __fastcall FuncWhen(int Index);
	TtkTokenKind __fastcall FuncWord(int Index);
	TtkTokenKind __fastcall FuncWordindex(int Index);
	TtkTokenKind __fastcall FuncWordlength(int Index);
	TtkTokenKind __fastcall FuncWordpos(int Index);
	TtkTokenKind __fastcall FuncWords(int Index);
	TtkTokenKind __fastcall FuncX2b(int Index);
	TtkTokenKind __fastcall FuncX2c(int Index);
	TtkTokenKind __fastcall FuncX2d(int Index);
	TtkTokenKind __fastcall FuncXrange(int Index);
	void __fastcall IdentProc();
	void __fastcall UnknownProc();
	TtkTokenKind __fastcall AltFunc(int Index);
	void __fastcall InitIdent();
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall NullProc();
	void __fastcall SpaceProc();
	void __fastcall CRProc();
	void __fastcall LFProc();
	void __fastcall MultilineCommentOpenProc();
	void __fastcall MultilineCommentProc();
	void __fastcall SinglelineCommentOpenProc();
	void __fastcall SinglelineCommentProc();
	void __fastcall StringDoubleOpenProc();
	void __fastcall StringDoubleProc();
	void __fastcall StringSingleOpenProc();
	void __fastcall StringSingleProc();
protected:
	virtual UnicodeString __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	__fastcall TSynRexxSyn(TComponent* AOwner);
	__classmethod virtual UnicodeString __fastcall GetFriendlyLanguageName();
	__classmethod virtual String __fastcall GetLanguageName();
	virtual void* __fastcall GetRange();
	virtual void __fastcall ResetRange();
	virtual void __fastcall SetRange(void* Value);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual UnicodeString __fastcall GetKeyWords(int TokenKind);
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual void __fastcall Next();
__published:
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpecialAttri = { read = fSpecialAttri, write = fSpecialAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StdFunctionAttri = { read = fStdFunctionAttri, write = fStdFunctionAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
};

void SynHighlighterRexx_initialization();


}  // namespace SynHighlighterRexx

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterrexx;
#endif


#endif // SynHighlighterRexxH

