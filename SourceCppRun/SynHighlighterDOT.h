#ifndef SynHighlighterDOTH
#define SynHighlighterDOTH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterdot
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
The original code is: SynHighlighterDOT.pas, released 2002-11-30.
Description: DOT Syntax Parser/Highlighter
The initial author of this file is nissl (nissl@tiscali.it, nissl@mammuth.it)
Unicode translation by Maël Hörz.
Copyright (c) 2002, all rights reserved.

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

$Id: SynHighlighterDOT.pas,v 1.3.2.7 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------*/
/*
@abstract(Provides a ATT DOT highlighter for SynEdit)
@author(Massimo Maria Ghisalberti (nissl@mammuth.it))
@created(november 2002)
@lastmod(2002-11-30)
The SynHighlighterDOT unit provides SynEdit with a DOT Graph Drawing (.dot) highlighter.
The highlighter formats DOT source code ref.: http://www.research.att.com/sw/tools/graphviz/.
*/
enum TtkTokenKind {tkArrowHead,
                   tkAttribute,
                   tkComment,
                   tkDirections,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkShape,
                   tkSpace,
                   tkString,
                   tkUnknown,
                   tkValue,
                   tkSymbol };
enum TRangeState {rsUnKnown,
                  rsCStyleComment,
                  rsString };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynDOTSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState FRange;
	TtkTokenKind FTokenID;
	TIdentFuncTableFunc fIdentFuncTable[787/*# range 0..786*/];
	Synedithighlighter::TSynHighlighterAttributes* fArrowHeadAttri;
	Synedithighlighter::TSynHighlighterAttributes* fAttributeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDirectionsAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fShapeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fValueAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall FuncAll(int Index);
	TtkTokenKind __fastcall FuncAppendix(int Index);
	TtkTokenKind __fastcall FuncArrowhead(int Index);
	TtkTokenKind __fastcall FuncArrowsize(int Index);
	TtkTokenKind __fastcall FuncArrowtail(int Index);
	TtkTokenKind __fastcall FuncAuto(int Index);
	TtkTokenKind __fastcall FuncBack(int Index);
	TtkTokenKind __fastcall FuncBgcolor(int Index);
	TtkTokenKind __fastcall FuncBold(int Index);
	TtkTokenKind __fastcall FuncBoth(int Index);
	TtkTokenKind __fastcall FuncBottomlabel(int Index);
	TtkTokenKind __fastcall FuncBox(int Index);
	TtkTokenKind __fastcall FuncCenter(int Index);
	TtkTokenKind __fastcall FuncCircle(int Index);
	TtkTokenKind __fastcall FuncClusterrank(int Index);
	TtkTokenKind __fastcall FuncColor(int Index);
	TtkTokenKind __fastcall FuncComment(int Index);
	TtkTokenKind __fastcall FuncCompound(int Index);
	TtkTokenKind __fastcall FuncConcentrate(int Index);
	TtkTokenKind __fastcall FuncConstraint(int Index);
	TtkTokenKind __fastcall FuncDecorate(int Index);
	TtkTokenKind __fastcall FuncDiamond(int Index);
	TtkTokenKind __fastcall FuncDigraph(int Index);
	TtkTokenKind __fastcall FuncDir(int Index);
	TtkTokenKind __fastcall FuncDistortion(int Index);
	TtkTokenKind __fastcall FuncDot(int Index);
	TtkTokenKind __fastcall FuncDotted(int Index);
	TtkTokenKind __fastcall FuncDoublecircle(int Index);
	TtkTokenKind __fastcall FuncDoubleoctagon(int Index);
	TtkTokenKind __fastcall FuncE(int Index);
	TtkTokenKind __fastcall FuncEdge(int Index);
	TtkTokenKind __fastcall FuncEgg(int Index);
	TtkTokenKind __fastcall FuncEllipse(int Index);
	TtkTokenKind __fastcall FuncFalse(int Index);
	TtkTokenKind __fastcall FuncFill(int Index);
	TtkTokenKind __fastcall FuncFillcolor(int Index);
	TtkTokenKind __fastcall FuncFilled(int Index);
	TtkTokenKind __fastcall FuncFixedsize(int Index);
	TtkTokenKind __fastcall FuncFontcolor(int Index);
	TtkTokenKind __fastcall FuncFontname(int Index);
	TtkTokenKind __fastcall FuncFontpath(int Index);
	TtkTokenKind __fastcall FuncFontsize(int Index);
	TtkTokenKind __fastcall FuncForward(int Index);
	TtkTokenKind __fastcall FuncGlobal(int Index);
	TtkTokenKind __fastcall FuncGraph(int Index);
	TtkTokenKind __fastcall FuncGroup(int Index);
	TtkTokenKind __fastcall FuncHeadlabel(int Index);
	TtkTokenKind __fastcall FuncHeadport(int Index);
	TtkTokenKind __fastcall FuncHeadurl(int Index);
	TtkTokenKind __fastcall FuncHeight(int Index);
	TtkTokenKind __fastcall FuncHexagon(int Index);
	TtkTokenKind __fastcall FuncHouse(int Index);
	TtkTokenKind __fastcall FuncId(int Index);
	TtkTokenKind __fastcall FuncInv(int Index);
	TtkTokenKind __fastcall FuncInvdot(int Index);
	TtkTokenKind __fastcall FuncInvhouse(int Index);
	TtkTokenKind __fastcall FuncInvodot(int Index);
	TtkTokenKind __fastcall FuncInvtrapezium(int Index);
	TtkTokenKind __fastcall FuncInvtriangle(int Index);
	TtkTokenKind __fastcall FuncLabel(int Index);
	TtkTokenKind __fastcall FuncLabelangle(int Index);
	TtkTokenKind __fastcall FuncLabeldistance(int Index);
	TtkTokenKind __fastcall FuncLabelfloat(int Index);
	TtkTokenKind __fastcall FuncLabelfontcolor(int Index);
	TtkTokenKind __fastcall FuncLabelfontname(int Index);
	TtkTokenKind __fastcall FuncLabelfontsize(int Index);
	TtkTokenKind __fastcall FuncLabeljust(int Index);
	TtkTokenKind __fastcall FuncLabelloc(int Index);
	TtkTokenKind __fastcall FuncLayer(int Index);
	TtkTokenKind __fastcall FuncLayers(int Index);
	TtkTokenKind __fastcall FuncLhead(int Index);
	TtkTokenKind __fastcall FuncLtail(int Index);
	TtkTokenKind __fastcall FuncMargin(int Index);
	TtkTokenKind __fastcall FuncMax(int Index);
	TtkTokenKind __fastcall FuncMcircle(int Index);
	TtkTokenKind __fastcall FuncMclimit(int Index);
	TtkTokenKind __fastcall FuncMdiamond(int Index);
	TtkTokenKind __fastcall FuncMerged(int Index);
	TtkTokenKind __fastcall FuncMin(int Index);
	TtkTokenKind __fastcall FuncMinimum(int Index);
	TtkTokenKind __fastcall FuncMinlen(int Index);
	TtkTokenKind __fastcall FuncMrecord(int Index);
	TtkTokenKind __fastcall FuncMsquare(int Index);
	TtkTokenKind __fastcall FuncMultiples(int Index);
	TtkTokenKind __fastcall FuncN(int Index);
	TtkTokenKind __fastcall FuncNe(int Index);
	TtkTokenKind __fastcall FuncNode(int Index);
	TtkTokenKind __fastcall FuncNodesep(int Index);
	TtkTokenKind __fastcall FuncNone(int Index);
	TtkTokenKind __fastcall FuncNormal(int Index);
	TtkTokenKind __fastcall FuncNslimit(int Index);
	TtkTokenKind __fastcall FuncNw(int Index);
	TtkTokenKind __fastcall FuncOctagon(int Index);
	TtkTokenKind __fastcall FuncOdot(int Index);
	TtkTokenKind __fastcall FuncOnto(int Index);
	TtkTokenKind __fastcall FuncOrdering(int Index);
	TtkTokenKind __fastcall FuncOrientation(int Index);
	TtkTokenKind __fastcall FuncPage(int Index);
	TtkTokenKind __fastcall FuncPagedir(int Index);
	TtkTokenKind __fastcall FuncParallelogram(int Index);
	TtkTokenKind __fastcall FuncPeripheries(int Index);
	TtkTokenKind __fastcall FuncPlaintext(int Index);
	TtkTokenKind __fastcall FuncPoint(int Index);
	TtkTokenKind __fastcall FuncPolygon(int Index);
	TtkTokenKind __fastcall FuncQuantum(int Index);
	TtkTokenKind __fastcall FuncRank(int Index);
	TtkTokenKind __fastcall FuncRankdir(int Index);
	TtkTokenKind __fastcall FuncRanksep(int Index);
	TtkTokenKind __fastcall FuncRatio(int Index);
	TtkTokenKind __fastcall FuncRecord(int Index);
	TtkTokenKind __fastcall FuncRegular(int Index);
	TtkTokenKind __fastcall FuncRemincross(int Index);
	TtkTokenKind __fastcall FuncRotate(int Index);
	TtkTokenKind __fastcall FuncS(int Index);
	TtkTokenKind __fastcall FuncSame(int Index);
	TtkTokenKind __fastcall FuncSamehead(int Index);
	TtkTokenKind __fastcall FuncSametail(int Index);
	TtkTokenKind __fastcall FuncSamplepoints(int Index);
	TtkTokenKind __fastcall FuncSe(int Index);
	TtkTokenKind __fastcall FuncSearchsize(int Index);
	TtkTokenKind __fastcall FuncSection(int Index);
	TtkTokenKind __fastcall FuncShape(int Index);
	TtkTokenKind __fastcall FuncShapefile(int Index);
	TtkTokenKind __fastcall FuncSides(int Index);
	TtkTokenKind __fastcall FuncSink(int Index);
	TtkTokenKind __fastcall FuncSize(int Index);
	TtkTokenKind __fastcall FuncSkew(int Index);
	TtkTokenKind __fastcall FuncSource(int Index);
	TtkTokenKind __fastcall FuncStrict(int Index);
	TtkTokenKind __fastcall FuncStyle(int Index);
	TtkTokenKind __fastcall FuncSubgraph(int Index);
	TtkTokenKind __fastcall FuncSw(int Index);
	TtkTokenKind __fastcall FuncTaillabel(int Index);
	TtkTokenKind __fastcall FuncTailport(int Index);
	TtkTokenKind __fastcall FuncTailurl(int Index);
	TtkTokenKind __fastcall FuncToplabel(int Index);
	TtkTokenKind __fastcall FuncTrapezium(int Index);
	TtkTokenKind __fastcall FuncTriangle(int Index);
	TtkTokenKind __fastcall FuncTripleoctagon(int Index);
	TtkTokenKind __fastcall FuncTrue(int Index);
	TtkTokenKind __fastcall FuncUrl(int Index);
	TtkTokenKind __fastcall FuncW(int Index);
	TtkTokenKind __fastcall FuncWeight(int Index);
	TtkTokenKind __fastcall FuncWhen(int Index);
	TtkTokenKind __fastcall FuncWidth(int Index);
	TtkTokenKind __fastcall FuncZ(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall InitIdent();
	void __fastcall IdentProc();
	void __fastcall UnknownProc();
	void __fastcall NullProc();
	void __fastcall SpaceProc();
	void __fastcall CRProc();
	void __fastcall LFProc();
	void __fastcall CStyleCommentOpenProc();
	void __fastcall CStyleCommentProc();
	void __fastcall StringOpenProc();
	void __fastcall StringProc();
	void __fastcall SymbolProc();
	void __fastcall DirectionsProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	__fastcall TSynDOTSyn(System::Classes::TComponent* AOwner);
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
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual void __fastcall Next();
__published:
	__property TSynHighlighterAttributes* ArrowHeadAttri = { read = fArrowHeadAttri, write = fArrowHeadAttri };
	__property TSynHighlighterAttributes* AttributeAttri = { read = fAttributeAttri, write = fAttributeAttri };
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* DirectionsAttri = { read = fDirectionsAttri, write = fDirectionsAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* ShapeAttri = { read = fShapeAttri, write = fShapeAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* ValueAttri = { read = fValueAttri, write = fValueAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
};

void SynHighlighterDOT_initialization();


}  // namespace SynHighlighterDOT

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterdot;
#endif


#endif // SynHighlighterDOTH

