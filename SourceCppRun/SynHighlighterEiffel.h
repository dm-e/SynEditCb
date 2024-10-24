/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

Code template generated with SynGen.
The original code is: SynHighlighterEiffel.pas, released 2004-03-08.
Description: Eiffel Syntax Parser/Highlighter
The initial author of this file is Massimo Maria Ghisalberti (nissl).
Unicode translation by Maël Hörz.
Copyright (c) 2004, all rights reserved.

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

$Id: SynHighlighterEiffel.pas,v 1.3.2.8 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------*/
/*
@abstract(Provides an Eiffel highlighter for SynEdit)
@author(Massimo Maria Ghisalberti (nissl@mammuth.it, nissl@linee.it - www.linee.it)
@created(03-08-2004)
@lastmod(03-08-2004)
The SynHighlighterEiffel unit provides SynEdit with an Eiffel highlighter.
*/
#ifndef SynHighlighterEiffelH
#define SynHighlighterEiffelH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlightereiffel
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

Code template generated with SynGen.
The original code is: SynHighlighterEiffel.pas, released 2004-03-08.
Description: Eiffel Syntax Parser/Highlighter
The initial author of this file is Massimo Maria Ghisalberti (nissl).
Unicode translation by Maël Hörz.
Copyright (c) 2004, all rights reserved.

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

$Id: SynHighlighterEiffel.pas,v 1.3.2.8 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------*/
/*
@abstract(Provides an Eiffel highlighter for SynEdit)
@author(Massimo Maria Ghisalberti (nissl@mammuth.it, nissl@linee.it - www.linee.it)
@created(03-08-2004)
@lastmod(03-08-2004)
The SynHighlighterEiffel unit provides SynEdit with an Eiffel highlighter.
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
enum TtkTokenKind {tkBasicTypes,
                   tkComment,
                   tkIdentifier,
                   tkKey,
                   tkLace,
                   tkNull,
                   tkOperatorAndSymbols,
                   tkPredefined,
                   tkResultValue,
                   tkSpace,
                   tkString,
                   tkUnknown };
enum TRangeState {rsUnKnown,
                  rsEiffelComment,
                  rsString,
                  rsOperatorAndSymbolProc };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynEiffelSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState fRange;
	TtkTokenKind fTokenID;
	TIdentFuncTableFunc fIdentFuncTable[503/*# range 0..502*/];
	Synedithighlighter::TSynHighlighterAttributes* fBasicTypesAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fLaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fOperatorAndSymbolsAttri;
	Synedithighlighter::TSynHighlighterAttributes* fPredefinedAttri;
	Synedithighlighter::TSynHighlighterAttributes* fResultValueAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall OperatorFunc(int Index);
	TtkTokenKind __fastcall Func37u(int Index);
	TtkTokenKind __fastcall FuncAdapt(int Index);
	TtkTokenKind __fastcall FuncAlias(int Index);
	TtkTokenKind __fastcall FuncAll(int Index);
	TtkTokenKind __fastcall FuncAnd(int Index);
	TtkTokenKind __fastcall FuncArray(int Index);
	TtkTokenKind __fastcall FuncAs(int Index);
	TtkTokenKind __fastcall FuncAssertion(int Index);
	TtkTokenKind __fastcall FuncBit(int Index);
	TtkTokenKind __fastcall FuncBoolean(int Index);
	TtkTokenKind __fastcall FuncCharacter(int Index);
	TtkTokenKind __fastcall FuncCheck(int Index);
	TtkTokenKind __fastcall FuncClass(int Index);
	TtkTokenKind __fastcall FuncCluster(int Index);
	TtkTokenKind __fastcall FuncColon(int Index);
	TtkTokenKind __fastcall FuncComma(int Index);
	TtkTokenKind __fastcall FuncCreation(int Index);
	TtkTokenKind __fastcall FuncCurrent(int Index);
	TtkTokenKind __fastcall FuncDebug(int Index);
	TtkTokenKind __fastcall FuncDefault(int Index);
	TtkTokenKind __fastcall FuncDeferred(int Index);
	TtkTokenKind __fastcall FuncDo(int Index);
	TtkTokenKind __fastcall FuncDouble(int Index);
	TtkTokenKind __fastcall FuncElse(int Index);
	TtkTokenKind __fastcall FuncElseif(int Index);
	TtkTokenKind __fastcall FuncEnd(int Index);
	TtkTokenKind __fastcall FuncEnsure(int Index);
	TtkTokenKind __fastcall FuncExclude(int Index);
	TtkTokenKind __fastcall FuncExecutable(int Index);
	TtkTokenKind __fastcall FuncExpanded(int Index);
	TtkTokenKind __fastcall FuncExport(int Index);
	TtkTokenKind __fastcall FuncExternal(int Index);
	TtkTokenKind __fastcall FuncFalse(int Index);
	TtkTokenKind __fastcall FuncFeature(int Index);
	TtkTokenKind __fastcall FuncFrom(int Index);
	TtkTokenKind __fastcall FuncFrozen(int Index);
	TtkTokenKind __fastcall FuncGenerate(int Index);
	TtkTokenKind __fastcall FuncIdentifier(int Index);
	TtkTokenKind __fastcall FuncIf(int Index);
	TtkTokenKind __fastcall FuncIgnore(int Index);
	TtkTokenKind __fastcall FuncImplies(int Index);
	TtkTokenKind __fastcall FuncInclude(int Index);
	TtkTokenKind __fastcall FuncInclude95path(int Index);
	TtkTokenKind __fastcall FuncIndexing(int Index);
	TtkTokenKind __fastcall FuncInfix(int Index);
	TtkTokenKind __fastcall FuncInherit(int Index);
	TtkTokenKind __fastcall FuncInspect(int Index);
	TtkTokenKind __fastcall FuncInteger(int Index);
	TtkTokenKind __fastcall FuncInvariant(int Index);
	TtkTokenKind __fastcall FuncIs(int Index);
	TtkTokenKind __fastcall FuncLike(int Index);
	TtkTokenKind __fastcall FuncLocal(int Index);
	TtkTokenKind __fastcall FuncLoop(int Index);
	TtkTokenKind __fastcall FuncMake(int Index);
	TtkTokenKind __fastcall FuncNo(int Index);
	TtkTokenKind __fastcall FuncNot(int Index);
	TtkTokenKind __fastcall FuncObject(int Index);
	TtkTokenKind __fastcall FuncObsolete(int Index);
	TtkTokenKind __fastcall FuncOld(int Index);
	TtkTokenKind __fastcall FuncOnce(int Index);
	TtkTokenKind __fastcall FuncOptimize(int Index);
	TtkTokenKind __fastcall FuncOption(int Index);
	TtkTokenKind __fastcall FuncOr(int Index);
	TtkTokenKind __fastcall FuncPointer(int Index);
	TtkTokenKind __fastcall FuncPrecompiled(int Index);
	TtkTokenKind __fastcall FuncPrecursor(int Index);
	TtkTokenKind __fastcall FuncPrefix(int Index);
	TtkTokenKind __fastcall FuncReal(int Index);
	TtkTokenKind __fastcall FuncRedefine(int Index);
	TtkTokenKind __fastcall FuncRename(int Index);
	TtkTokenKind __fastcall FuncRequire(int Index);
	TtkTokenKind __fastcall FuncRescue(int Index);
	TtkTokenKind __fastcall FuncResult(int Index);
	TtkTokenKind __fastcall FuncRetry(int Index);
	TtkTokenKind __fastcall FuncRoot(int Index);
	TtkTokenKind __fastcall FuncSelect(int Index);
	TtkTokenKind __fastcall FuncSeparate(int Index);
	TtkTokenKind __fastcall FuncString(int Index);
	TtkTokenKind __fastcall FuncStrip(int Index);
	TtkTokenKind __fastcall FuncSystem(int Index);
	TtkTokenKind __fastcall FuncThen(int Index);
	TtkTokenKind __fastcall FuncTrace(int Index);
	TtkTokenKind __fastcall FuncTrue(int Index);
	TtkTokenKind __fastcall FuncUndefine(int Index);
	TtkTokenKind __fastcall FuncUnique(int Index);
	TtkTokenKind __fastcall FuncUntil(int Index);
	TtkTokenKind __fastcall FuncUse(int Index);
	TtkTokenKind __fastcall FuncVariant(int Index);
	TtkTokenKind __fastcall FuncVisible(int Index);
	TtkTokenKind __fastcall FuncVoid(int Index);
	TtkTokenKind __fastcall FuncWhen(int Index);
	TtkTokenKind __fastcall FuncXor(int Index);
	TtkTokenKind __fastcall FuncYes(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar MayBe);
	void __fastcall IdentProc();
	void __fastcall InitIdent();
	void __fastcall OperatorAndSymbolProc();
	void __fastcall UnknownProc();
	void __fastcall NullProc();
	void __fastcall SpaceProc();
	void __fastcall CRProc();
	void __fastcall LFProc();
	void __fastcall EiffelCommentOpenProc();
	void __fastcall EiffelCommentProc();
	void __fastcall StringOpenProc();
	void __fastcall StringProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	__fastcall TSynEiffelSyn(TComponent* AOwner);
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	virtual void* __fastcall GetRange();
	virtual void __fastcall ResetRange();
	virtual void __fastcall SetRange(void* Value);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual String __fastcall GetKeyWords(int TokenKind);
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
	bool __fastcall IsOperatorChar(WideChar AChar);
__published:
	__property Synedithighlighter::TSynHighlighterAttributes* BasicTypesAttri = { read = fBasicTypesAttri, write = fBasicTypesAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* LaceAttri = { read = fLaceAttri, write = fLaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* OperatorAndSymbolsAttri = { read = fOperatorAndSymbolsAttri, write = fOperatorAndSymbolsAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* PredefinedAttri = { read = fPredefinedAttri, write = fPredefinedAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* ResultValueAttri = { read = fResultValueAttri, write = fResultValueAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
};

void SynHighlighterEiffel_initialization();


}  // namespace SynHighlighterEiffel

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightereiffel;
#endif


#endif // SynHighlighterEiffelH

