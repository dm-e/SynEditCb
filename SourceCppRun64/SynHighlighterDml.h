/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterDml.pas, released 2000-04-17.
The Original Code is based on the mwDmlSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Peter Adam.
Unicode translation by Ma�l H�rz.
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

$Id: SynHighlighterDml.pas,v 1.11.2.7 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
  - There are no metadata qualifiers.
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Dml highlighter for SynEdit)
@author(Peter Adam)
@created(1999)
@lastmod(2000-06-23)
The SynHighlighterDml unit provides SynEdit with a Dml highlighter.
*/
#ifndef SynHighlighterDmlH
#define SynHighlighterDmlH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterdml
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterDml.pas, released 2000-04-17.
The Original Code is based on the mwDmlSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Peter Adam.
Unicode translation by Ma�l H�rz.
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

$Id: SynHighlighterDml.pas,v 1.11.2.7 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
  - There are no metadata qualifiers.
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Dml highlighter for SynEdit)
@author(Peter Adam)
@created(1999)
@lastmod(2000-06-23)
The SynHighlighterDml unit provides SynEdit with a Dml highlighter.
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
enum TtkTokenKind {tkBlock,
                   tkComment,
                   tkForm,
                   tkFunction,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkNumber,
                   tkQualifier,
                   tkSpace,
                   tkSpecial,
                   tkString,
                   tkSymbol,
                   tkUnknown,
                   tkVariable };
enum TRangeState {rsANil,
                  rsAdd,
                  rsFind,
                  rsUnKnown };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynDmlSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState fRange;
	TIdentFuncTableFunc fIdentFuncTable[2439/*# range 0..2438*/];
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fFormAttri;
	Synedithighlighter::TSynHighlighterAttributes* fBlockAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fQualiAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fFunctionAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVariableAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpecialAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall FuncAbs(int Index);
	TtkTokenKind __fastcall FuncAbsolute_position(int Index);
	TtkTokenKind __fastcall FuncAccount(int Index);
	TtkTokenKind __fastcall FuncAcos(int Index);
	TtkTokenKind __fastcall FuncActual_break(int Index);
	TtkTokenKind __fastcall FuncAdd(int Index);
	TtkTokenKind __fastcall FuncAdd_form(int Index);
	TtkTokenKind __fastcall FuncAlternate_form(int Index);
	TtkTokenKind __fastcall FuncAscii(int Index);
	TtkTokenKind __fastcall FuncAsin(int Index);
	TtkTokenKind __fastcall FuncAtan(int Index);
	TtkTokenKind __fastcall FuncAtan2(int Index);
	TtkTokenKind __fastcall FuncAttributes(int Index);
	TtkTokenKind __fastcall FuncBack(int Index);
	TtkTokenKind __fastcall FuncBase(int Index);
	TtkTokenKind __fastcall FuncBatch(int Index);
	TtkTokenKind __fastcall FuncBegin_block(int Index);
	TtkTokenKind __fastcall FuncBegin_case(int Index);
	TtkTokenKind __fastcall FuncBegin_disable_trigger(int Index);
	TtkTokenKind __fastcall FuncBegin_row(int Index);
	TtkTokenKind __fastcall FuncBegin_signal_to_status(int Index);
	TtkTokenKind __fastcall FuncBell(int Index);
	TtkTokenKind __fastcall FuncBinary_to_poly(int Index);
	TtkTokenKind __fastcall FuncBottom_line(int Index);
	TtkTokenKind __fastcall FuncBreak(int Index);
	TtkTokenKind __fastcall FuncBreak0(int Index);
	TtkTokenKind __fastcall FuncCall(int Index);
	TtkTokenKind __fastcall FuncCase(int Index);
	TtkTokenKind __fastcall FuncCeil(int Index);
	TtkTokenKind __fastcall FuncCheck(int Index);
	TtkTokenKind __fastcall FuncCheck_domain(int Index);
	TtkTokenKind __fastcall FuncChr(int Index);
	TtkTokenKind __fastcall FuncClear_buffer(int Index);
	TtkTokenKind __fastcall FuncCli(int Index);
	TtkTokenKind __fastcall FuncClose(int Index);
	TtkTokenKind __fastcall FuncClose_text(int Index);
	TtkTokenKind __fastcall FuncCol(int Index);
	TtkTokenKind __fastcall FuncColumn_heading_row(int Index);
	TtkTokenKind __fastcall FuncColumn_headings(int Index);
	TtkTokenKind __fastcall FuncColumn_spacing(int Index);
	TtkTokenKind __fastcall FuncCommit(int Index);
	TtkTokenKind __fastcall FuncCommit_rate(int Index);
	TtkTokenKind __fastcall FuncCompile(int Index);
	TtkTokenKind __fastcall FuncCompress(int Index);
	TtkTokenKind __fastcall FuncCompress_all(int Index);
	TtkTokenKind __fastcall FuncConfirm(int Index);
	TtkTokenKind __fastcall FuncConnect(int Index);
	TtkTokenKind __fastcall FuncContinue(int Index);
	TtkTokenKind __fastcall FuncCos(int Index);
	TtkTokenKind __fastcall FuncCosh(int Index);
	TtkTokenKind __fastcall FuncCross_reference(int Index);
	TtkTokenKind __fastcall FuncDate(int Index);
	TtkTokenKind __fastcall FuncDate_seconds(int Index);
	TtkTokenKind __fastcall FuncDay_of_week(int Index);
	TtkTokenKind __fastcall FuncDays(int Index);
	TtkTokenKind __fastcall FuncDcl(int Index);
	TtkTokenKind __fastcall FuncDefault_tag(int Index);
	TtkTokenKind __fastcall FuncDelete(int Index);
	TtkTokenKind __fastcall FuncDelete_form(int Index);
	TtkTokenKind __fastcall FuncDescription(int Index);
	TtkTokenKind __fastcall FuncDir(int Index);
	TtkTokenKind __fastcall FuncDisconnect(int Index);
	TtkTokenKind __fastcall FuncDisplay(int Index);
	TtkTokenKind __fastcall FuncDisplay_length(int Index);
	TtkTokenKind __fastcall FuncDocumentation(int Index);
	TtkTokenKind __fastcall FuncDomain(int Index);
	TtkTokenKind __fastcall FuncEdit(int Index);
	TtkTokenKind __fastcall FuncElse(int Index);
	TtkTokenKind __fastcall FuncElse_if(int Index);
	TtkTokenKind __fastcall FuncEnd_block(int Index);
	TtkTokenKind __fastcall FuncEnd_case(int Index);
	TtkTokenKind __fastcall FuncEnd_disable_trigger(int Index);
	TtkTokenKind __fastcall FuncEnd_execute(int Index);
	TtkTokenKind __fastcall FuncEnd_form(int Index);
	TtkTokenKind __fastcall FuncEnd_if(int Index);
	TtkTokenKind __fastcall FuncEnd_row(int Index);
	TtkTokenKind __fastcall FuncEnd_signal_to_status(int Index);
	TtkTokenKind __fastcall FuncEnd_while(int Index);
	TtkTokenKind __fastcall FuncErase(int Index);
	TtkTokenKind __fastcall FuncError(int Index);
	TtkTokenKind __fastcall FuncExecute(int Index);
	TtkTokenKind __fastcall FuncExit(int Index);
	TtkTokenKind __fastcall FuncExit_forward(int Index);
	TtkTokenKind __fastcall FuncExpand(int Index);
	TtkTokenKind __fastcall FuncExternal(int Index);
	TtkTokenKind __fastcall FuncFacility(int Index);
	TtkTokenKind __fastcall FuncFailure(int Index);
	TtkTokenKind __fastcall FuncFetch(int Index);
	TtkTokenKind __fastcall FuncFiles(int Index);
	TtkTokenKind __fastcall FuncFind(int Index);
	TtkTokenKind __fastcall FuncFind_form(int Index);
	TtkTokenKind __fastcall FuncFinish(int Index);
	TtkTokenKind __fastcall FuncFirst(int Index);
	TtkTokenKind __fastcall FuncFloor(int Index);
	TtkTokenKind __fastcall FuncFooting(int Index);
	TtkTokenKind __fastcall FuncFooting_form(int Index);
	TtkTokenKind __fastcall FuncForm(int Index);
	TtkTokenKind __fastcall FuncGenerate(int Index);
	TtkTokenKind __fastcall FuncGoto(int Index);
	TtkTokenKind __fastcall FuncGrouped_by(int Index);
	TtkTokenKind __fastcall FuncHeading(int Index);
	TtkTokenKind __fastcall FuncHeading_form(int Index);
	TtkTokenKind __fastcall FuncHeight(int Index);
	TtkTokenKind __fastcall FuncIdentifier(int Index);
	TtkTokenKind __fastcall FuncIf(int Index);
	TtkTokenKind __fastcall FuncIn(int Index);
	TtkTokenKind __fastcall FuncInput_block(int Index);
	TtkTokenKind __fastcall FuncInput_mask(int Index);
	TtkTokenKind __fastcall FuncInput_row_height(int Index);
	TtkTokenKind __fastcall FuncInt(int Index);
	TtkTokenKind __fastcall FuncInvoke(int Index);
	TtkTokenKind __fastcall FuncItem(int Index);
	TtkTokenKind __fastcall FuncItem_block(int Index);
	TtkTokenKind __fastcall FuncItem_if(int Index);
	TtkTokenKind __fastcall FuncJoined_to(int Index);
	TtkTokenKind __fastcall FuncLeft(int Index);
	TtkTokenKind __fastcall FuncLen(int Index);
	TtkTokenKind __fastcall FuncLfooting(int Index);
	TtkTokenKind __fastcall FuncLheading(int Index);
	TtkTokenKind __fastcall FuncLine(int Index);
	TtkTokenKind __fastcall FuncLines_after(int Index);
	TtkTokenKind __fastcall FuncLines_before(int Index);
	TtkTokenKind __fastcall FuncList(int Index);
	TtkTokenKind __fastcall FuncLoad(int Index);
	TtkTokenKind __fastcall FuncLock(int Index);
	TtkTokenKind __fastcall FuncLog(int Index);
	TtkTokenKind __fastcall FuncLog10(int Index);
	TtkTokenKind __fastcall FuncLov(int Index);
	TtkTokenKind __fastcall FuncLov_auto_select(int Index);
	TtkTokenKind __fastcall FuncLov_col(int Index);
	TtkTokenKind __fastcall FuncLov_data(int Index);
	TtkTokenKind __fastcall FuncLov_first(int Index);
	TtkTokenKind __fastcall FuncLov_height(int Index);
	TtkTokenKind __fastcall FuncLov_noheading(int Index);
	TtkTokenKind __fastcall FuncLov_nosearch(int Index);
	TtkTokenKind __fastcall FuncLov_reduced_to(int Index);
	TtkTokenKind __fastcall FuncLov_row(int Index);
	TtkTokenKind __fastcall FuncLov_secondary(int Index);
	TtkTokenKind __fastcall FuncLov_selection(int Index);
	TtkTokenKind __fastcall FuncLov_sorted_by(int Index);
	TtkTokenKind __fastcall FuncLov_width(int Index);
	TtkTokenKind __fastcall FuncLov_with(int Index);
	TtkTokenKind __fastcall FuncLowercase(int Index);
	TtkTokenKind __fastcall FuncLtrim(int Index);
	TtkTokenKind __fastcall FuncMail(int Index);
	TtkTokenKind __fastcall FuncMenu(int Index);
	TtkTokenKind __fastcall FuncMenu_block(int Index);
	TtkTokenKind __fastcall FuncMenu_form(int Index);
	TtkTokenKind __fastcall FuncMessage(int Index);
	TtkTokenKind __fastcall FuncMid(int Index);
	TtkTokenKind __fastcall FuncMod(int Index);
	TtkTokenKind __fastcall FuncModify_form(int Index);
	TtkTokenKind __fastcall FuncNew(int Index);
	TtkTokenKind __fastcall FuncNo_domain(int Index);
	TtkTokenKind __fastcall FuncNobell(int Index);
	TtkTokenKind __fastcall FuncNoclear_buffer(int Index);
	TtkTokenKind __fastcall FuncNodeadlock_exit(int Index);
	TtkTokenKind __fastcall FuncNoerase(int Index);
	TtkTokenKind __fastcall FuncNoerror(int Index);
	TtkTokenKind __fastcall FuncNoexit_forward(int Index);
	TtkTokenKind __fastcall FuncNoheading(int Index);
	TtkTokenKind __fastcall FuncNolov_data(int Index);
	TtkTokenKind __fastcall FuncNorepeat(int Index);
	TtkTokenKind __fastcall FuncNostatus(int Index);
	TtkTokenKind __fastcall FuncNototals(int Index);
	TtkTokenKind __fastcall FuncNounderlines(int Index);
	TtkTokenKind __fastcall FuncNowait(int Index);
	TtkTokenKind __fastcall FuncOpen(int Index);
	TtkTokenKind __fastcall FuncOpen_text(int Index);
	TtkTokenKind __fastcall FuncOpt(int Index);
	TtkTokenKind __fastcall FuncOptions(int Index);
	TtkTokenKind __fastcall FuncOutput(int Index);
	TtkTokenKind __fastcall FuncOutput_block(int Index);
	TtkTokenKind __fastcall FuncOutput_mask(int Index);
	TtkTokenKind __fastcall FuncPause(int Index);
	TtkTokenKind __fastcall FuncPause_block(int Index);
	TtkTokenKind __fastcall FuncPerform(int Index);
	TtkTokenKind __fastcall FuncPoly_to_binary(int Index);
	TtkTokenKind __fastcall FuncPos(int Index);
	TtkTokenKind __fastcall FuncPrint(int Index);
	TtkTokenKind __fastcall FuncProcedure_form(int Index);
	TtkTokenKind __fastcall FuncPrompt(int Index);
	TtkTokenKind __fastcall FuncProtect(int Index);
	TtkTokenKind __fastcall FuncQuery(int Index);
	TtkTokenKind __fastcall FuncQuery_form(int Index);
	TtkTokenKind __fastcall FuncRandom(int Index);
	TtkTokenKind __fastcall FuncRead_line(int Index);
	TtkTokenKind __fastcall FuncRead_only(int Index);
	TtkTokenKind __fastcall FuncReceive(int Index);
	TtkTokenKind __fastcall FuncReceive_arguments(int Index);
	TtkTokenKind __fastcall FuncReceive_data(int Index);
	TtkTokenKind __fastcall FuncReceive_table(int Index);
	TtkTokenKind __fastcall FuncReduced_to(int Index);
	TtkTokenKind __fastcall FuncRelease(int Index);
	TtkTokenKind __fastcall FuncRemain(int Index);
	TtkTokenKind __fastcall FuncRepeat(int Index);
	TtkTokenKind __fastcall FuncReport(int Index);
	TtkTokenKind __fastcall FuncReport_form(int Index);
	TtkTokenKind __fastcall FuncReposition(int Index);
	TtkTokenKind __fastcall FuncRewind_text(int Index);
	TtkTokenKind __fastcall FuncRfooting(int Index);
	TtkTokenKind __fastcall FuncRheading(int Index);
	TtkTokenKind __fastcall FuncRight(int Index);
	TtkTokenKind __fastcall FuncRollback(int Index);
	TtkTokenKind __fastcall FuncRound(int Index);
	TtkTokenKind __fastcall FuncRow(int Index);
	TtkTokenKind __fastcall FuncRow_height(int Index);
	TtkTokenKind __fastcall FuncSearch(int Index);
	TtkTokenKind __fastcall FuncSecondary(int Index);
	TtkTokenKind __fastcall FuncSeconds(int Index);
	TtkTokenKind __fastcall FuncSelection(int Index);
	TtkTokenKind __fastcall FuncSend(int Index);
	TtkTokenKind __fastcall FuncSend_data(int Index);
	TtkTokenKind __fastcall FuncSend_message(int Index);
	TtkTokenKind __fastcall FuncSend_table(int Index);
	TtkTokenKind __fastcall FuncSequence(int Index);
	TtkTokenKind __fastcall FuncSeverity(int Index);
	TtkTokenKind __fastcall FuncSin(int Index);
	TtkTokenKind __fastcall FuncSinh(int Index);
	TtkTokenKind __fastcall FuncSorted_by(int Index);
	TtkTokenKind __fastcall FuncSource(int Index);
	TtkTokenKind __fastcall FuncSource_if(int Index);
	TtkTokenKind __fastcall FuncSqrt(int Index);
	TtkTokenKind __fastcall FuncStart_stream(int Index);
	TtkTokenKind __fastcall FuncStart_transaction(int Index);
	TtkTokenKind __fastcall FuncStatistic(int Index);
	TtkTokenKind __fastcall FuncStatus(int Index);
	TtkTokenKind __fastcall FuncStream_name(int Index);
	TtkTokenKind __fastcall FuncString(int Index);
	TtkTokenKind __fastcall FuncSuccess(int Index);
	TtkTokenKind __fastcall FuncSwitch(int Index);
	TtkTokenKind __fastcall FuncSwitch_base(int Index);
	TtkTokenKind __fastcall FuncSystem(int Index);
	TtkTokenKind __fastcall FuncTable(int Index);
	TtkTokenKind __fastcall FuncTable_form(int Index);
	TtkTokenKind __fastcall FuncTable_search(int Index);
	TtkTokenKind __fastcall FuncTag(int Index);
	TtkTokenKind __fastcall FuncTag_length(int Index);
	TtkTokenKind __fastcall FuncTan(int Index);
	TtkTokenKind __fastcall FuncTanh(int Index);
	TtkTokenKind __fastcall FuncTarget(int Index);
	TtkTokenKind __fastcall FuncText(int Index);
	TtkTokenKind __fastcall FuncText_only(int Index);
	TtkTokenKind __fastcall FuncTitle(int Index);
	TtkTokenKind __fastcall FuncTo(int Index);
	TtkTokenKind __fastcall FuncTop_line(int Index);
	TtkTokenKind __fastcall FuncTotal(int Index);
	TtkTokenKind __fastcall FuncTransfer(int Index);
	TtkTokenKind __fastcall FuncTrigger(int Index);
	TtkTokenKind __fastcall FuncTrim(int Index);
	TtkTokenKind __fastcall FuncTsuppress(int Index);
	TtkTokenKind __fastcall FuncUnload(int Index);
	TtkTokenKind __fastcall FuncUppercase(int Index);
	TtkTokenKind __fastcall FuncUse_if(int Index);
	TtkTokenKind __fastcall FuncUser_key(int Index);
	TtkTokenKind __fastcall FuncUsing(int Index);
	TtkTokenKind __fastcall FuncUtilities(int Index);
	TtkTokenKind __fastcall FuncWait(int Index);
	TtkTokenKind __fastcall FuncWhile(int Index);
	TtkTokenKind __fastcall FuncWidth(int Index);
	TtkTokenKind __fastcall FuncWith(int Index);
	TtkTokenKind __fastcall FuncWrite(int Index);
	TtkTokenKind __fastcall FuncWrite_line(int Index);
	TtkTokenKind __fastcall FuncYesno_block(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar MayBe);
	void __fastcall InitIdent();
	void __fastcall SymbolProc();
	void __fastcall AddressOpProc();
	void __fastcall AsciiCharProc();
	void __fastcall CRProc();
	void __fastcall GreaterProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall LowerProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall PointProc();
	void __fastcall SpaceProc();
	void __fastcall StringProc();
	void __fastcall UnknownProc();
	void __fastcall RemProc();
	bool __fastcall IsQuali();
	bool __fastcall IsSpecial();
protected:
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynDmlSyn(TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
__published:
public:
	__property Synedithighlighter::TSynHighlighterAttributes* BlockAttri = { read = fBlockAttri, write = fBlockAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* FormAttri = { read = fFormAttri, write = fFormAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* FunctionAttri = { read = fFunctionAttri, write = fFunctionAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* QualiAttri = { read = fQualiAttri, write = fQualiAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpecialAttri = { read = fSpecialAttri, write = fSpecialAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VariableAttri = { read = fVariableAttri, write = fVariableAttri };
};

void SynHighlighterDml_initialization();


}  // namespace SynHighlighterDml

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterdml;
#endif


#endif // SynHighlighterDmlH

