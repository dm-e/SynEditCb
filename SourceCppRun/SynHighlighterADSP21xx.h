#ifndef SynHighlighterADSP21xxH
#define SynHighlighterADSP21xxH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighteradsp21xx
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterADSP21xx.pas, released 2000-04-17.
The Original Code is based on the wbADSP21xxSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Wynand Breytenbach.
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

$Id: SynHighlighterADSP21xx.pas,v 1.16.2.7 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a ADSP21xx highlighter for SynEdit)
@author(Wynand Breytenbach, converted to SynEdit by David Muir <dhm@dmsoftware.co.uk>)
@created(1999)
@lastmod(2000-06-23)
The SynHighlighterADSP21xx unit provides a ADSP21xx DSP assembler highlighter for SynEdit.
*/
enum TtkTokenKind {tkComment,
                   tkCondition,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkNumber,
                   tkRegister,
                   tkSpace,
                   tkString,
                   tkSymbol,
                   tkUnknown };
enum TRangeState {rsUnKnown,
                  rsPascalComment,
                  rsCComment,
                  rsHexNumber,
                  rsBinaryNumber,
                  rsInclude };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynADSP21xxSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState FRange;
	TIdentFuncTableFunc fIdentFuncTable[821/*# range 0..820*/];
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fRegisterAttri;
	Synedithighlighter::TSynHighlighterAttributes* fConditionAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNullAttri;
	Synedithighlighter::TSynHighlighterAttributes* fUnknownAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall FuncAbs(int Index);
	TtkTokenKind __fastcall FuncAbstract(int Index);
	TtkTokenKind __fastcall FuncAc(int Index);
	TtkTokenKind __fastcall FuncAf(int Index);
	TtkTokenKind __fastcall FuncAlt95reg(int Index);
	TtkTokenKind __fastcall FuncAnd(int Index);
	TtkTokenKind __fastcall FuncAr(int Index);
	TtkTokenKind __fastcall FuncAr95sat(int Index);
	TtkTokenKind __fastcall FuncAshift(int Index);
	TtkTokenKind __fastcall FuncAstat(int Index);
	TtkTokenKind __fastcall FuncAux(int Index);
	TtkTokenKind __fastcall FuncAv(int Index);
	TtkTokenKind __fastcall FuncAv95latch(int Index);
	TtkTokenKind __fastcall FuncAx0(int Index);
	TtkTokenKind __fastcall FuncAx1(int Index);
	TtkTokenKind __fastcall FuncAy0(int Index);
	TtkTokenKind __fastcall FuncAy1(int Index);
	TtkTokenKind __fastcall FuncB(int Index);
	TtkTokenKind __fastcall FuncBit95rev(int Index);
	TtkTokenKind __fastcall FuncBm(int Index);
	TtkTokenKind __fastcall FuncBoot(int Index);
	TtkTokenKind __fastcall FuncBy(int Index);
	TtkTokenKind __fastcall FuncCache(int Index);
	TtkTokenKind __fastcall FuncCall(int Index);
	TtkTokenKind __fastcall FuncCe(int Index);
	TtkTokenKind __fastcall FuncCirc(int Index);
	TtkTokenKind __fastcall FuncClear(int Index);
	TtkTokenKind __fastcall FuncClr(int Index);
	TtkTokenKind __fastcall FuncClrbit(int Index);
	TtkTokenKind __fastcall FuncCntl(int Index);
	TtkTokenKind __fastcall FuncCntr(int Index);
	TtkTokenKind __fastcall FuncConst(int Index);
	TtkTokenKind __fastcall FuncDefine(int Index);
	TtkTokenKind __fastcall FuncDis(int Index);
	TtkTokenKind __fastcall FuncDivq(int Index);
	TtkTokenKind __fastcall FuncDivs(int Index);
	TtkTokenKind __fastcall FuncDm(int Index);
	TtkTokenKind __fastcall FuncDmovlay(int Index);
	TtkTokenKind __fastcall FuncDo(int Index);
	TtkTokenKind __fastcall FuncElse(int Index);
	TtkTokenKind __fastcall FuncEmode(int Index);
	TtkTokenKind __fastcall FuncEna(int Index);
	TtkTokenKind __fastcall FuncEndif(int Index);
	TtkTokenKind __fastcall FuncEndmacro(int Index);
	TtkTokenKind __fastcall FuncEndmod(int Index);
	TtkTokenKind __fastcall FuncEntry(int Index);
	TtkTokenKind __fastcall FuncEq(int Index);
	TtkTokenKind __fastcall FuncExp(int Index);
	TtkTokenKind __fastcall FuncExpadj(int Index);
	TtkTokenKind __fastcall FuncExternal(int Index);
	TtkTokenKind __fastcall FuncFl0(int Index);
	TtkTokenKind __fastcall FuncFl1(int Index);
	TtkTokenKind __fastcall FuncFl2(int Index);
	TtkTokenKind __fastcall FuncFlag95in(int Index);
	TtkTokenKind __fastcall FuncFlag95out(int Index);
	TtkTokenKind __fastcall FuncFor(int Index);
	TtkTokenKind __fastcall FuncForever(int Index);
	TtkTokenKind __fastcall FuncGe(int Index);
	TtkTokenKind __fastcall FuncGlobal(int Index);
	TtkTokenKind __fastcall FuncGo95mode(int Index);
	TtkTokenKind __fastcall FuncGt(int Index);
	TtkTokenKind __fastcall FuncH(int Index);
	TtkTokenKind __fastcall FuncHi(int Index);
	TtkTokenKind __fastcall FuncI0(int Index);
	TtkTokenKind __fastcall FuncI1(int Index);
	TtkTokenKind __fastcall FuncI2(int Index);
	TtkTokenKind __fastcall FuncI3(int Index);
	TtkTokenKind __fastcall FuncI4(int Index);
	TtkTokenKind __fastcall FuncI5(int Index);
	TtkTokenKind __fastcall FuncI6(int Index);
	TtkTokenKind __fastcall FuncI7(int Index);
	TtkTokenKind __fastcall FuncIcntl(int Index);
	TtkTokenKind __fastcall FuncIdle(int Index);
	TtkTokenKind __fastcall FuncIf(int Index);
	TtkTokenKind __fastcall FuncIfc(int Index);
	TtkTokenKind __fastcall FuncIfdef(int Index);
	TtkTokenKind __fastcall FuncIfndef(int Index);
	TtkTokenKind __fastcall FuncImask(int Index);
	TtkTokenKind __fastcall FuncIn(int Index);
	TtkTokenKind __fastcall FuncInclude(int Index);
	TtkTokenKind __fastcall FuncInit(int Index);
	TtkTokenKind __fastcall FuncIo(int Index);
	TtkTokenKind __fastcall FuncJump(int Index);
	TtkTokenKind __fastcall FuncL0(int Index);
	TtkTokenKind __fastcall FuncL1(int Index);
	TtkTokenKind __fastcall FuncL2(int Index);
	TtkTokenKind __fastcall FuncL3(int Index);
	TtkTokenKind __fastcall FuncL4(int Index);
	TtkTokenKind __fastcall FuncL5(int Index);
	TtkTokenKind __fastcall FuncL6(int Index);
	TtkTokenKind __fastcall FuncL7(int Index);
	TtkTokenKind __fastcall FuncLe(int Index);
	TtkTokenKind __fastcall FuncLo(int Index);
	TtkTokenKind __fastcall FuncLocal(int Index);
	TtkTokenKind __fastcall FuncLoop(int Index);
	TtkTokenKind __fastcall FuncLshift(int Index);
	TtkTokenKind __fastcall FuncLt(int Index);
	TtkTokenKind __fastcall FuncM95mode(int Index);
	TtkTokenKind __fastcall FuncM0(int Index);
	TtkTokenKind __fastcall FuncM1(int Index);
	TtkTokenKind __fastcall FuncM2(int Index);
	TtkTokenKind __fastcall FuncM3(int Index);
	TtkTokenKind __fastcall FuncM4(int Index);
	TtkTokenKind __fastcall FuncM5(int Index);
	TtkTokenKind __fastcall FuncM6(int Index);
	TtkTokenKind __fastcall FuncM7(int Index);
	TtkTokenKind __fastcall FuncMacro(int Index);
	TtkTokenKind __fastcall FuncMf(int Index);
	TtkTokenKind __fastcall FuncModify(int Index);
	TtkTokenKind __fastcall FuncModule(int Index);
	TtkTokenKind __fastcall FuncMr(int Index);
	TtkTokenKind __fastcall FuncMr0(int Index);
	TtkTokenKind __fastcall FuncMr1(int Index);
	TtkTokenKind __fastcall FuncMr2(int Index);
	TtkTokenKind __fastcall FuncMstat(int Index);
	TtkTokenKind __fastcall FuncMv(int Index);
	TtkTokenKind __fastcall FuncMx0(int Index);
	TtkTokenKind __fastcall FuncMx1(int Index);
	TtkTokenKind __fastcall FuncMy0(int Index);
	TtkTokenKind __fastcall FuncMy1(int Index);
	TtkTokenKind __fastcall FuncName(int Index);
	TtkTokenKind __fastcall FuncNe(int Index);
	TtkTokenKind __fastcall FuncNeg(int Index);
	TtkTokenKind __fastcall FuncNewpage(int Index);
	TtkTokenKind __fastcall FuncNop(int Index);
	TtkTokenKind __fastcall FuncNorm(int Index);
	TtkTokenKind __fastcall FuncNot(int Index);
	TtkTokenKind __fastcall FuncOf(int Index);
	TtkTokenKind __fastcall FuncOr(int Index);
	TtkTokenKind __fastcall FuncPass(int Index);
	TtkTokenKind __fastcall FuncPc(int Index);
	TtkTokenKind __fastcall FuncPm(int Index);
	TtkTokenKind __fastcall FuncPop(int Index);
	TtkTokenKind __fastcall FuncPort(int Index);
	TtkTokenKind __fastcall FuncPush(int Index);
	TtkTokenKind __fastcall FuncRam(int Index);
	TtkTokenKind __fastcall FuncRegbank(int Index);
	TtkTokenKind __fastcall FuncReset(int Index);
	TtkTokenKind __fastcall FuncRnd(int Index);
	TtkTokenKind __fastcall FuncRom(int Index);
	TtkTokenKind __fastcall FuncRti(int Index);
	TtkTokenKind __fastcall FuncRts(int Index);
	TtkTokenKind __fastcall FuncRx0(int Index);
	TtkTokenKind __fastcall FuncRx1(int Index);
	TtkTokenKind __fastcall FuncSat(int Index);
	TtkTokenKind __fastcall FuncSb(int Index);
	TtkTokenKind __fastcall FuncSec95reg(int Index);
	TtkTokenKind __fastcall FuncSeg(int Index);
	TtkTokenKind __fastcall FuncSegment(int Index);
	TtkTokenKind __fastcall FuncSet(int Index);
	TtkTokenKind __fastcall FuncSetbit(int Index);
	TtkTokenKind __fastcall FuncShift(int Index);
	TtkTokenKind __fastcall FuncShl(int Index);
	TtkTokenKind __fastcall FuncShr(int Index);
	TtkTokenKind __fastcall FuncSi(int Index);
	TtkTokenKind __fastcall FuncSr(int Index);
	TtkTokenKind __fastcall FuncSr0(int Index);
	TtkTokenKind __fastcall FuncSr1(int Index);
	TtkTokenKind __fastcall FuncSs(int Index);
	TtkTokenKind __fastcall FuncSstat(int Index);
	TtkTokenKind __fastcall FuncStatic(int Index);
	TtkTokenKind __fastcall FuncSts(int Index);
	TtkTokenKind __fastcall FuncSu(int Index);
	TtkTokenKind __fastcall FuncTest(int Index);
	TtkTokenKind __fastcall FuncTestbit(int Index);
	TtkTokenKind __fastcall FuncTglbit(int Index);
	TtkTokenKind __fastcall FuncTimer(int Index);
	TtkTokenKind __fastcall FuncToggle(int Index);
	TtkTokenKind __fastcall FuncTopofpcstack(int Index);
	TtkTokenKind __fastcall FuncTrap(int Index);
	TtkTokenKind __fastcall FuncTrue(int Index);
	TtkTokenKind __fastcall FuncTx0(int Index);
	TtkTokenKind __fastcall FuncTx1(int Index);
	TtkTokenKind __fastcall FuncUndef(int Index);
	TtkTokenKind __fastcall FuncUntil(int Index);
	TtkTokenKind __fastcall FuncUs(int Index);
	TtkTokenKind __fastcall FuncUu(int Index);
	TtkTokenKind __fastcall FuncVar(int Index);
	TtkTokenKind __fastcall FuncXor(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall InitIdent();
	void __fastcall PascalCommentProc();
	void __fastcall BraceCloseProc();
	void __fastcall BraceOpenProc();
	void __fastcall CCommentProc();
	void __fastcall CRProc();
	void __fastcall ExclamationProc();
	void __fastcall IdentProc();
	void __fastcall IntegerProc();
	void __fastcall IncludeCloseProc();
	void __fastcall LFProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall BinaryNumber();
	void __fastcall HexNumber();
	void __fastcall SlashProc();
	void __fastcall SpaceProc();
	void __fastcall StringProc();
	void __fastcall UnknownProc();
protected:
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	__classmethod virtual Synedithighlighter::TSynHighlighterCapabilities __fastcall GetCapabilities();
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynADSP21xxSyn(System::Classes::TComponent* AOwner);
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
__published:
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* ConditionAttri = { read = fConditionAttri, write = fConditionAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* RegisterAttri = { read = fRegisterAttri, write = fRegisterAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
};

void SynHighlighterADSP21xx_initialization();


}  // namespace SynHighlighterADSP21xx

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighteradsp21xx;
#endif


#endif // SynHighlighterADSP21xxH

