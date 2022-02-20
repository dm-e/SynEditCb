#ifndef SynHighlighterUnrealH
#define SynHighlighterUnrealH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include <System.Win.Registry.hpp>
#include <Winapi.Windows.hpp>
#include "SynEditHighlighter.h"
#include "SynEditTypes.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterunreal
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.
                                          PP - 2001/10/24:
The Original Code is based on the UnrealSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Dean Harmon.
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

$Id: SynHighlighterUnreal.pas,v 1.17.2.8 2008/09/14 16:25:03 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Unreal syntax highlighter for SynEdit)
@author(Dean Harmon)
@created(2000)
@lastmod(2001-06-29)
*/ // registry constants
enum TtkTokenKind {tkComment,
                   tkDirective,
                   tkIdentifier,
                   tkKey,
                   tkKey2,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkString2,
                   tkSymbol,
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
enum TRangeState {rsANil,
                  rsAnsiC,
                  rsDirective,
                  rsDirectiveComment,
                  rsUnKnown };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynUnrealSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState FRange;
	int FRoundCount;
	int FSquareCount;
	TtkTokenKind FTokenID;
	TxtkTokenKind FExtTokenID;
	TIdentFuncTableFunc fIdentFuncTable[733/*# range 0..732*/];
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDirecAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fInvalidAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKey2Attri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fString2Attri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall FuncAbstract(int Index);
	TtkTokenKind __fastcall FuncAlways(int Index);
	TtkTokenKind __fastcall FuncArray(int Index);
	TtkTokenKind __fastcall FuncArraycount(int Index);
	TtkTokenKind __fastcall FuncAssert(int Index);
	TtkTokenKind __fastcall FuncAuto(int Index);
	TtkTokenKind __fastcall FuncAutomated(int Index);
	TtkTokenKind __fastcall FuncBool(int Index);
	TtkTokenKind __fastcall FuncBoundingbox(int Index);
	TtkTokenKind __fastcall FuncBoundingvolume(int Index);
	TtkTokenKind __fastcall FuncBreak(int Index);
	TtkTokenKind __fastcall FuncButton(int Index);
	TtkTokenKind __fastcall FuncByte(int Index);
	TtkTokenKind __fastcall FuncCache(int Index);
	TtkTokenKind __fastcall FuncCacheexempt(int Index);
	TtkTokenKind __fastcall FuncCase(int Index);
	TtkTokenKind __fastcall FuncCatch(int Index);
	TtkTokenKind __fastcall FuncClass(int Index);
	TtkTokenKind __fastcall FuncCoerce(int Index);
	TtkTokenKind __fastcall FuncCollapsecategories(int Index);
	TtkTokenKind __fastcall FuncColor(int Index);
	TtkTokenKind __fastcall FuncConfig(int Index);
	TtkTokenKind __fastcall FuncConst(int Index);
	TtkTokenKind __fastcall FuncContinue(int Index);
	TtkTokenKind __fastcall FuncCoords(int Index);
	TtkTokenKind __fastcall FuncCpptext(int Index);
	TtkTokenKind __fastcall FuncCross(int Index);
	TtkTokenKind __fastcall FuncDefault(int Index);
	TtkTokenKind __fastcall FuncDefaultproperties(int Index);
	TtkTokenKind __fastcall FuncDelegate(int Index);
	TtkTokenKind __fastcall FuncDelete(int Index);
	TtkTokenKind __fastcall FuncDependson(int Index);
	TtkTokenKind __fastcall FuncDeprecated(int Index);
	TtkTokenKind __fastcall FuncDo(int Index);
	TtkTokenKind __fastcall FuncDontcollapsecategories(int Index);
	TtkTokenKind __fastcall FuncDot(int Index);
	TtkTokenKind __fastcall FuncEach(int Index);
	TtkTokenKind __fastcall FuncEdfindable(int Index);
	TtkTokenKind __fastcall FuncEditconst(int Index);
	TtkTokenKind __fastcall FuncEditconstarray(int Index);
	TtkTokenKind __fastcall FuncEditinline(int Index);
	TtkTokenKind __fastcall FuncEditinlinenew(int Index);
	TtkTokenKind __fastcall FuncEditinlinenotify(int Index);
	TtkTokenKind __fastcall FuncEditinlineuse(int Index);
	TtkTokenKind __fastcall FuncElse(int Index);
	TtkTokenKind __fastcall FuncEnum(int Index);
	TtkTokenKind __fastcall FuncEnumcount(int Index);
	TtkTokenKind __fastcall FuncEvent(int Index);
	TtkTokenKind __fastcall FuncExec(int Index);
	TtkTokenKind __fastcall FuncExpands(int Index);
	TtkTokenKind __fastcall FuncExplicit(int Index);
	TtkTokenKind __fastcall FuncExport(int Index);
	TtkTokenKind __fastcall FuncExportstructs(int Index);
	TtkTokenKind __fastcall FuncExtends(int Index);
	TtkTokenKind __fastcall FuncFalse(int Index);
	TtkTokenKind __fastcall FuncFinal(int Index);
	TtkTokenKind __fastcall FuncFloat(int Index);
	TtkTokenKind __fastcall FuncFor(int Index);
	TtkTokenKind __fastcall FuncForeach(int Index);
	TtkTokenKind __fastcall FuncFunction(int Index);
	TtkTokenKind __fastcall FuncGlobal(int Index);
	TtkTokenKind __fastcall FuncGlobalconfig(int Index);
	TtkTokenKind __fastcall FuncGoto(int Index);
	TtkTokenKind __fastcall FuncGuid(int Index);
	TtkTokenKind __fastcall FuncHidecategories(int Index);
	TtkTokenKind __fastcall FuncHidedropdown(int Index);
	TtkTokenKind __fastcall FuncHideparent(int Index);
	TtkTokenKind __fastcall FuncIf(int Index);
	TtkTokenKind __fastcall FuncIgnores(int Index);
	TtkTokenKind __fastcall FuncImport(int Index);
	TtkTokenKind __fastcall FuncInit(int Index);
	TtkTokenKind __fastcall FuncInput(int Index);
	TtkTokenKind __fastcall FuncInsert(int Index);
	TtkTokenKind __fastcall FuncInstanced(int Index);
	TtkTokenKind __fastcall FuncInt(int Index);
	TtkTokenKind __fastcall FuncIntrinsic(int Index);
	TtkTokenKind __fastcall FuncInvariant(int Index);
	TtkTokenKind __fastcall FuncIterator(int Index);
	TtkTokenKind __fastcall FuncLatent(int Index);
	TtkTokenKind __fastcall FuncLength(int Index);
	TtkTokenKind __fastcall FuncLocal(int Index);
	TtkTokenKind __fastcall FuncLocalized(int Index);
	TtkTokenKind __fastcall FuncLong(int Index);
	TtkTokenKind __fastcall FuncMesh(int Index);
	TtkTokenKind __fastcall FuncModel(int Index);
	TtkTokenKind __fastcall FuncMutable(int Index);
	TtkTokenKind __fastcall FuncName(int Index);
	TtkTokenKind __fastcall FuncNative(int Index);
	TtkTokenKind __fastcall FuncNativereplication(int Index);
	TtkTokenKind __fastcall FuncNew(int Index);
	TtkTokenKind __fastcall FuncNoexport(int Index);
	TtkTokenKind __fastcall FuncNone(int Index);
	TtkTokenKind __fastcall FuncNoteditinlinenew(int Index);
	TtkTokenKind __fastcall FuncNotplaceable(int Index);
	TtkTokenKind __fastcall FuncNousercreate(int Index);
	TtkTokenKind __fastcall FuncOperator(int Index);
	TtkTokenKind __fastcall FuncOptional(int Index);
	TtkTokenKind __fastcall FuncOut(int Index);
	TtkTokenKind __fastcall FuncParseconfig(int Index);
	TtkTokenKind __fastcall FuncPerobjectconfig(int Index);
	TtkTokenKind __fastcall FuncPlaceable(int Index);
	TtkTokenKind __fastcall FuncPlane(int Index);
	TtkTokenKind __fastcall FuncPointer(int Index);
	TtkTokenKind __fastcall FuncPostoperator(int Index);
	TtkTokenKind __fastcall FuncPreoperator(int Index);
	TtkTokenKind __fastcall FuncPrivate(int Index);
	TtkTokenKind __fastcall FuncProtected(int Index);
	TtkTokenKind __fastcall FuncRegister(int Index);
	TtkTokenKind __fastcall FuncReliable(int Index);
	TtkTokenKind __fastcall FuncRemove(int Index);
	TtkTokenKind __fastcall FuncReplication(int Index);
	TtkTokenKind __fastcall FuncReturn(int Index);
	TtkTokenKind __fastcall FuncRng(int Index);
	TtkTokenKind __fastcall FuncRot(int Index);
	TtkTokenKind __fastcall FuncRotator(int Index);
	TtkTokenKind __fastcall FuncSafereplace(int Index);
	TtkTokenKind __fastcall FuncScale(int Index);
	TtkTokenKind __fastcall FuncScriptconst(int Index);
	TtkTokenKind __fastcall FuncSelf(int Index);
	TtkTokenKind __fastcall FuncShowcategories(int Index);
	TtkTokenKind __fastcall FuncSimulated(int Index);
	TtkTokenKind __fastcall FuncSingular(int Index);
	TtkTokenKind __fastcall FuncSkip(int Index);
	TtkTokenKind __fastcall FuncSound(int Index);
	TtkTokenKind __fastcall FuncState(int Index);
	TtkTokenKind __fastcall FuncStatic(int Index);
	TtkTokenKind __fastcall FuncStop(int Index);
	TtkTokenKind __fastcall FuncString(int Index);
	TtkTokenKind __fastcall FuncStruct(int Index);
	TtkTokenKind __fastcall FuncSuper(int Index);
	TtkTokenKind __fastcall FuncSwitch(int Index);
	TtkTokenKind __fastcall FuncTexture(int Index);
	TtkTokenKind __fastcall FuncTransient(int Index);
	TtkTokenKind __fastcall FuncTravel(int Index);
	TtkTokenKind __fastcall FuncTrue(int Index);
	TtkTokenKind __fastcall FuncUnreliable(int Index);
	TtkTokenKind __fastcall FuncUntil(int Index);
	TtkTokenKind __fastcall FuncVar(int Index);
	TtkTokenKind __fastcall FuncVect(int Index);
	TtkTokenKind __fastcall FuncVector(int Index);
	TtkTokenKind __fastcall FuncVoid(int Index);
	TtkTokenKind __fastcall FuncWhile(int Index);
	TtkTokenKind __fastcall FuncWithin(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall InitIdent();
	void __fastcall AnsiCProc();
	void __fastcall AndSymbolProc();
	void __fastcall AsciiCharProc();
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
	void __fastcall DollarSignProc();
	void __fastcall TildeProc();
	void __fastcall XOrSymbolProc();
	void __fastcall UnknownProc();
protected:
	TxtkTokenKind __fastcall GetExtTokenID();
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
	void __fastcall NextProcedure();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	__classmethod virtual Synedithighlighter::TSynHighlighterCapabilities __fastcall GetCapabilities();
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynUnrealSyn(System::Classes::TComponent* AOwner);
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
__published:
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* DirecAttri = { read = fDirecAttri, write = fDirecAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* InvalidAttri = { read = fInvalidAttri, write = fInvalidAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* Key2Attri = { read = fKey2Attri, write = fKey2Attri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SingleStringAttri = { read = fString2Attri, write = fString2Attri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
};

void SynHighlighterUnreal_initialization();


}  // namespace SynHighlighterUnreal

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterunreal;
#endif


#endif // SynHighlighterUnrealH

