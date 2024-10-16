
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterDOT.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace Vcl::Graphics;

namespace Synhighlighterdot
{
#define Synhighlighterdot__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterdot__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterdot__2 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterdot__3 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterdot__4 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterdot__5 (TFontStyles() << TFontStyle::fsBold)


const String KeyWords[146/*# range 0..145*/] = {L"all", L"appendix", L"arrowhead", L"arrowsize", L"arrowtail", L"auto", L"back", L"bgcolor", L"bold", L"both"
                    , L"bottomlabel", L"box", L"center", L"circle", L"clusterrank", L"color", L"comment", L"compound", L"concentrate", L"constraint"
                    , L"decorate", L"diamond", L"digraph", L"dir", L"distortion", L"dot", L"dotted", L"doublecircle", L"doubleoctagon", L"e"
                    , L"edge", L"egg", L"ellipse", L"false", L"fill", L"fillcolor", L"filled", L"fixedsize", L"fontcolor", L"fontname", L"fontpath", L"fontsize"
                    , L"forward", L"global", L"graph", L"group", L"headlabel", L"headport", L"headurl", L"height", L"hexagon", L"house", L"id"
                    , L"inv", L"invdot", L"invhouse", L"invodot", L"invtrapezium", L"invtriangle", L"label", L"labelangle", L"labeldistance", L"labelfloat"
                    , L"labelfontcolor", L"labelfontname", L"labelfontsize", L"labeljust", L"labelloc", L"layer", L"layers", L"lhead"
                    , L"ltail", L"margin", L"max", L"mcircle", L"mclimit", L"mdiamond", L"merged", L"min", L"minimum", L"minlen", L"mrecord", L"msquare"
                    , L"multiples", L"n", L"ne", L"node", L"nodesep", L"none", L"normal", L"nslimit", L"nw", L"octagon", L"odot", L"onto", L"ordering"
                    , L"orientation", L"page", L"pagedir", L"parallelogram", L"peripheries", L"plaintext", L"point", L"polygon", L"quantum"
                    , L"rank", L"rankdir", L"ranksep", L"ratio", L"record", L"regular", L"remincross", L"rotate", L"s", L"same", L"samehead", L"sametail"
                    , L"samplepoints", L"se", L"searchsize", L"section", L"shape", L"shapefile", L"sides", L"sink", L"size", L"skew", L"source"
                    , L"strict", L"style", L"subgraph", L"sw", L"taillabel", L"tailport", L"tailurl", L"toplabel", L"trapezium", L"triangle", L"tripleoctagon"
                    , L"true", L"url", L"w", L"weight", L"when", L"width", L"z"};
const int KeyIndices[787/*# range 0..786*/] = {-1, -1, -1, -1, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 141, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, 88, 50, -1, -1, -1, -1, -1, -1, -1, -1, 40, -1, -1, -1, -1, 4, -1, -1, -1, -1, 90, -1, 3, -1, 110, 86, -1, -1, 49, 23, -1, 92, -1, -1, -1, 15, -1, 122, -1, -1, 28, -1
                    , 78, -1, -1, -1, -1, -1, -1, -1, -1, -1, 85, -1, 27, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 140, -1, 103, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 142, -1, 7, -1, 0, -1, -1, 97, -1, -1, -1, -1, -1, 43
                    , -1, -1, -1, 131, -1, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 101, -1, 10, -1, 47, 68, -1, 132, -1, -1, 52, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, -1, -1, -1
                    , 64, -1, -1, 124, -1, -1, -1, -1, -1, -1, 87, -1, -1, -1, 12, -1, 84, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 42, -1, 38, -1, -1, -1, 143
                    , -1, -1, -1, 145, 106, -1, 127, -1, -1, -1, 99, 75, -1, -1, 102, -1, 58, -1, -1, 56, -1, -1, -1, -1, 9, -1, -1, -1, -1, -1, 22, -1, 73, -1, -1, -1, 17, -1, 54, 112, -1, -1, -1, -1, -1, -1, -1, 113
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 96, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 69, 116, -1, -1, 32, -1, -1, -1, -1, -1, -1, -1, 16, -1, -1, -1, -1, -1, 126, -1, -1, -1, -1, -1
                    , -1, -1, 71, -1, -1, -1, -1, -1, -1, -1, -1, -1, 137, -1, -1, 117, -1, -1, -1, -1, -1, -1, -1, -1, 111, 93, -1, -1, -1, -1, 108, -1, -1, 119, -1, -1, -1, -1, 29, -1, -1, -1, -1, -1, -1, -1, -1, 89
                    , -1, -1, -1, -1, 76, -1, -1, -1, -1, -1, -1, -1, 77, -1, -1, 104, -1, -1, -1, -1, -1, -1, 33, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26, -1, -1, -1, 79, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, 39, -1
                    , -1, -1, 115, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 109, 35, -1, -1, 70, -1, -1, 57, -1, 72, -1, -1, 83, -1, -1, -1, -1, 130, -1, -1, -1, 18, -1, 118, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, 81, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 61, 37, 1, -1, -1, -1, -1, 138, -1, -1, -1, -1, -1, 129, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, -1, -1
                    , 8, -1, -1, -1, 125, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 91, -1, -1, -1, -1, -1, 60, -1, -1, -1, -1, -1, -1, -1, 95, -1, -1, -1, -1, 136, -1, -1, 20, -1, 62, -1, -1, -1, -1, 134, -1, -1, -1, 63, -1
                    , -1, -1, 121, 80, -1, -1, -1, -1, -1, -1, 135, -1, -1, 120, -1, -1, -1, 53, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 31, -1, -1, -1, -1, -1, -1, 24, -1, -1, 139, 67, -1, -1, 59, -1, -1, 36, -1, -1, -1
                    , -1, -1, -1, -1, -1, 128, 34, -1, -1, -1, -1, -1, -1, -1, -1, 65, -1, 114, -1, -1, -1, -1, -1, -1, -1, 55, -1, -1, 94, -1, -1, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , 41, -1, -1, -1, -1, -1, -1, -1, 44, -1, -1, -1, -1, -1, 74, -1, 51, 144, -1, -1, 82, 98, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 100, 66, -1, 25, -1, -1, -1, 45, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, 6, 105, -1, -1, 133, 123, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 107, -1, -1, -1, -1, -1, -1, -1, -1, -1, 30
                    , -1, -1, -1};

/*$Q-*/

unsigned int __fastcall TSynDOTSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 63 + int((*Str)) * 331);
		++Str;
	}
	result = (unsigned int) (result % 787);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynDOTSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkArrowHead;
	unsigned int Key = 0;
	fToIdent = MayBe;
	Key = HashKey(MayBe);
	if(Key <= 786 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[Key](KeyIndices[Key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynDOTSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 786 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[132] = FuncAll;
	fIdentFuncTable[509] = FuncAppendix;
	fIdentFuncTable[188] = FuncArrowhead;
	fIdentFuncTable[72] = FuncArrowsize;
	fIdentFuncTable[65] = FuncArrowtail;
	fIdentFuncTable[149] = FuncAuto;
	fIdentFuncTable[752] = FuncBack;
	fIdentFuncTable[130] = FuncBgcolor;
	fIdentFuncTable[536] = FuncBold;
	fIdentFuncTable[266] = FuncBoth;
	fIdentFuncTable[169] = FuncBottomlabel;
	fIdentFuncTable[4] = FuncBox;
	fIdentFuncTable[206] = FuncCenter;
	fIdentFuncTable[666] = FuncCircle;
	fIdentFuncTable[533] = FuncClusterrank;
	fIdentFuncTable[85] = FuncColor;
	fIdentFuncTable[327] = FuncComment;
	fIdentFuncTable[278] = FuncCompound;
	fIdentFuncTable[481] = FuncConcentrate;
	fIdentFuncTable[425] = FuncConstraint;
	fIdentFuncTable[573] = FuncDecorate;
	fIdentFuncTable[302] = FuncDiamond;
	fIdentFuncTable[272] = FuncDigraph;
	fIdentFuncTable[79] = FuncDir;
	fIdentFuncTable[621] = FuncDistortion;
	fIdentFuncTable[726] = FuncDot;
	fIdentFuncTable[419] = FuncDotted;
	fIdentFuncTable[104] = FuncDoublecircle;
	fIdentFuncTable[90] = FuncDoubleoctagon;
	fIdentFuncTable[377] = FuncE;
	fIdentFuncTable[783] = FuncEdge;
	fIdentFuncTable[614] = FuncEgg;
	fIdentFuncTable[319] = FuncEllipse;
	fIdentFuncTable[409] = FuncFalse;
	fIdentFuncTable[641] = FuncFill;
	fIdentFuncTable[461] = FuncFillcolor;
	fIdentFuncTable[631] = FuncFilled;
	fIdentFuncTable[508] = FuncFixedsize;
	fIdentFuncTable[237] = FuncFontcolor;
	fIdentFuncTable[435] = FuncFontname;
	fIdentFuncTable[60] = FuncFontpath;
	fIdentFuncTable[685] = FuncFontsize;
	fIdentFuncTable[235] = FuncForward;
	fIdentFuncTable[141] = FuncGlobal;
	fIdentFuncTable[693] = FuncGraph;
	fIdentFuncTable[730] = FuncGroup;
	fIdentFuncTable[212] = FuncHeadlabel;
	fIdentFuncTable[171] = FuncHeadport;
	fIdentFuncTable[749] = FuncHeadurl;
	fIdentFuncTable[78] = FuncHeight;
	fIdentFuncTable[51] = FuncHexagon;
	fIdentFuncTable[701] = FuncHouse;
	fIdentFuncTable[177] = FuncId;
	fIdentFuncTable[603] = FuncInv;
	fIdentFuncTable[280] = FuncInvdot;
	fIdentFuncTable[660] = FuncInvhouse;
	fIdentFuncTable[261] = FuncInvodot;
	fIdentFuncTable[467] = FuncInvtrapezium;
	fIdentFuncTable[258] = FuncInvtriangle;
	fIdentFuncTable[628] = FuncLabel;
	fIdentFuncTable[557] = FuncLabelangle;
	fIdentFuncTable[507] = FuncLabeldistance;
	fIdentFuncTable[575] = FuncLabelfloat;
	fIdentFuncTable[584] = FuncLabelfontcolor;
	fIdentFuncTable[192] = FuncLabelfontname;
	fIdentFuncTable[650] = FuncLabelfontsize;
	fIdentFuncTable[724] = FuncLabeljust;
	fIdentFuncTable[625] = FuncLabelloc;
	fIdentFuncTable[172] = FuncLayer;
	fIdentFuncTable[315] = FuncLayers;
	fIdentFuncTable[464] = FuncLhead;
	fIdentFuncTable[341] = FuncLtail;
	fIdentFuncTable[469] = FuncMargin;
	fIdentFuncTable[274] = FuncMax;
	fIdentFuncTable[699] = FuncMcircle;
	fIdentFuncTable[253] = FuncMclimit;
	fIdentFuncTable[391] = FuncMdiamond;
	fIdentFuncTable[399] = FuncMerged;
	fIdentFuncTable[92] = FuncMin;
	fIdentFuncTable[423] = FuncMinimum;
	fIdentFuncTable[589] = FuncMinlen;
	fIdentFuncTable[493] = FuncMrecord;
	fIdentFuncTable[705] = FuncMsquare;
	fIdentFuncTable[472] = FuncMultiples;
	fIdentFuncTable[208] = FuncN;
	fIdentFuncTable[102] = FuncNe;
	fIdentFuncTable[75] = FuncNode;
	fIdentFuncTable[202] = FuncNodesep;
	fIdentFuncTable[50] = FuncNone;
	fIdentFuncTable[386] = FuncNormal;
	fIdentFuncTable[70] = FuncNslimit;
	fIdentFuncTable[551] = FuncNw;
	fIdentFuncTable[81] = FuncOctagon;
	fIdentFuncTable[364] = FuncOdot;
	fIdentFuncTable[663] = FuncOnto;
	fIdentFuncTable[565] = FuncOrdering;
	fIdentFuncTable[300] = FuncOrientation;
	fIdentFuncTable[135] = FuncPage;
	fIdentFuncTable[706] = FuncPagedir;
	fIdentFuncTable[252] = FuncParallelogram;
	fIdentFuncTable[723] = FuncPeripheries;
	fIdentFuncTable[167] = FuncPlaintext;
	fIdentFuncTable[256] = FuncPoint;
	fIdentFuncTable[117] = FuncPolygon;
	fIdentFuncTable[402] = FuncQuantum;
	fIdentFuncTable[753] = FuncRank;
	fIdentFuncTable[246] = FuncRankdir;
	fIdentFuncTable[773] = FuncRanksep;
	fIdentFuncTable[369] = FuncRatio;
	fIdentFuncTable[460] = FuncRecord;
	fIdentFuncTable[74] = FuncRegular;
	fIdentFuncTable[363] = FuncRemincross;
	fIdentFuncTable[281] = FuncRotate;
	fIdentFuncTable[289] = FuncS;
	fIdentFuncTable[652] = FuncSame;
	fIdentFuncTable[439] = FuncSamehead;
	fIdentFuncTable[316] = FuncSametail;
	fIdentFuncTable[354] = FuncSamplepoints;
	fIdentFuncTable[483] = FuncSe;
	fIdentFuncTable[372] = FuncSearchsize;
	fIdentFuncTable[599] = FuncSection;
	fIdentFuncTable[588] = FuncShape;
	fIdentFuncTable[87] = FuncShapefile;
	fIdentFuncTable[757] = FuncSides;
	fIdentFuncTable[195] = FuncSink;
	fIdentFuncTable[540] = FuncSize;
	fIdentFuncTable[333] = FuncSkew;
	fIdentFuncTable[248] = FuncSource;
	fIdentFuncTable[640] = FuncStrict;
	fIdentFuncTable[520] = FuncStyle;
	fIdentFuncTable[477] = FuncSubgraph;
	fIdentFuncTable[145] = FuncSw;
	fIdentFuncTable[174] = FuncTaillabel;
	fIdentFuncTable[756] = FuncTailport;
	fIdentFuncTable[580] = FuncTailurl;
	fIdentFuncTable[596] = FuncToplabel;
	fIdentFuncTable[570] = FuncTrapezium;
	fIdentFuncTable[351] = FuncTriangle;
	fIdentFuncTable[514] = FuncTripleoctagon;
	fIdentFuncTable[624] = FuncTrue;
	fIdentFuncTable[115] = FuncUrl;
	fIdentFuncTable[39] = FuncW;
	fIdentFuncTable[128] = FuncWeight;
	fIdentFuncTable[241] = FuncWhen;
	fIdentFuncTable[702] = FuncWidth;
	fIdentFuncTable[245] = FuncZ;
}

TtkTokenKind __fastcall TSynDOTSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkArrowHead;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncAll(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncAppendix(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncArrowhead(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncArrowsize(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncArrowtail(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncAuto(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncBack(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncBgcolor(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncBold(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncBoth(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncBottomlabel(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncBox(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncCenter(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncCircle(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncClusterrank(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncColor(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncComment(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncCompound(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncConcentrate(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncConstraint(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncDecorate(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncDiamond(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncDigraph(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncDir(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncDistortion(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncDot(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArrowHead;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncDotted(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncDoublecircle(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncDoubleoctagon(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncE(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncEdge(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncEgg(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncEllipse(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncFalse(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncFill(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncFillcolor(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncFilled(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))  // TODO: ANSI source isn't clear if tkValue or tkAttribute
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncFixedsize(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncFontcolor(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncFontname(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncFontpath(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncFontsize(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncForward(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncGlobal(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncGraph(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncGroup(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncHeadlabel(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncHeadport(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncHeadurl(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncHeight(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncHexagon(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncHouse(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncId(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncInv(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArrowHead;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncInvdot(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArrowHead;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncInvhouse(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncInvodot(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArrowHead;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncInvtrapezium(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncInvtriangle(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLabel(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLabelangle(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLabeldistance(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLabelfloat(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLabelfontcolor(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLabelfontname(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLabelfontsize(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLabeljust(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLabelloc(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLayer(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))  // TODO: ANSI source isn't clear if tkAttribute or tkKey
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLayers(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))  // TODO: ANSI source isn't clear if tkAttribute or tkKey
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLhead(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncLtail(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncMargin(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncMax(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncMcircle(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncMclimit(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncMdiamond(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncMerged(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncMin(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncMinimum(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncMinlen(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncMrecord(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncMsquare(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncMultiples(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncN(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncNe(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncNode(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncNodesep(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncNone(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
	{
		if(IsCurrentToken(KeyWords[Index]))
			result = tkArrowHead;
		else
			result = tkIdentifier;
	}
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncNormal(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArrowHead;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncNslimit(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncNw(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncOctagon(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncOdot(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkArrowHead;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncOnto(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncOrdering(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncOrientation(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncPage(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
	{
		if(IsCurrentToken(KeyWords[Index]))
			result = tkValue;
		else
			result = tkIdentifier;
	}
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncPagedir(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncParallelogram(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncPeripheries(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncPlaintext(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncPoint(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncPolygon(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncQuantum(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncRank(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncRankdir(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncRanksep(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncRatio(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncRecord(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncRegular(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncRemincross(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncRotate(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncS(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSame(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSamehead(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSametail(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSamplepoints(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSe(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSearchsize(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSection(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncShape(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncShapefile(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSides(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSink(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSize(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSkew(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSource(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncStrict(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncStyle(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSubgraph(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncSw(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncTaillabel(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncTailport(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncTailurl(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncToplabel(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncTrapezium(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncTriangle(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncTripleoctagon(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkShape;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncTrue(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncUrl(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncW(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkValue;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncWeight(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncWhen(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
	{
		if(IsCurrentToken(KeyWords[Index]))
			result = tkAttribute;
		else
			result = tkIdentifier;
	}
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncWidth(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::FuncZ(int Index)
{
	TtkTokenKind result = tkArrowHead;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkAttribute;
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynDOTSyn::SpaceProc()
{
	++Run;
	fTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynDOTSyn::NullProc()
{
	fTokenID = tkNull;
	++Run;
}

void __fastcall TSynDOTSyn::CRProc()
{
	fTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynDOTSyn::LFProc()
{
	fTokenID = tkSpace;
	++Run;
}

void __fastcall TSynDOTSyn::DirectionsProc()
{
	++Run;
	if((fLine[Run] == L'>') || (fLine[Run] == L'-'))
	{
		fTokenID = tkDirections;
		++Run;
	}
	else
	fTokenID = tkSymbol;
}

void __fastcall TSynDOTSyn::CStyleCommentOpenProc()
{
	++Run;
	if(fLine[Run] == L'/')
	{
		fTokenID = tkComment;
		Run += 2;
		while(!IsLineEnd(Run))
			++Run;
		return;
	}
	if(fLine[Run] == L'*')
	{
		fRange = rsCStyleComment;
		CStyleCommentProc();
		fTokenID = tkComment;
	}
	else
	fTokenID = tkIdentifier;
}

void __fastcall TSynDOTSyn::CStyleCommentProc()
{
	switch(fLine[Run])
	{
		case L'\x00':
		NullProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		default:
		{
			fTokenID = tkComment;
			do
			{
				if((fLine[Run] == L'*') && (fLine[Run + 1] == L'/'))
				{
					Run += 2;
					fRange = rsUnKnown;
					break;
				}
				if(!IsLineEnd(Run))
					++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
	}
}

void __fastcall TSynDOTSyn::StringOpenProc()
{
	++Run;
	fRange = rsString;
	StringProc();
	fTokenID = tkString;
}

void __fastcall TSynDOTSyn::StringProc()
{
	fTokenID = tkString;
	do
	{
		if(fLine[Run] == L'\'')
		{
			Run += 1;
			fRange = rsUnKnown;
			break;
		}
		if(!IsLineEnd(Run))
			++Run;
	}
	while(!IsLineEnd(Run));
}

__fastcall TSynDOTSyn::TSynDOTSyn(TComponent* AOwner)
 : inherited(AOwner),
			fRange(rsUnKnown),
			fTokenID(tkArrowHead),
			fArrowHeadAttri(nullptr),
			fAttributeAttri(nullptr),
			fCommentAttri(nullptr),
			fDirectionsAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fShapeAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fValueAttri(nullptr),
			fSymbolAttri(nullptr)
{
	fCaseSensitive = false;
	fArrowHeadAttri = new TSynHighlighterAttributes(SYNS_AttrArrowHead, SYNS_FriendlyAttrArrowHead);
	fArrowHeadAttri->Foreground = (TColor) clRed;
	AddAttribute(fArrowHeadAttri);
	fAttributeAttri = new TSynHighlighterAttributes(SYNS_AttrAttribute, SYNS_FriendlyAttrAttribute);
	AddAttribute(fAttributeAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterdot__0;
	fCommentAttri->Foreground = (TColor) clNavy;
	AddAttribute(fCommentAttri);
	fDirectionsAttri = new TSynHighlighterAttributes(SYNS_AttrDirections, SYNS_FriendlyAttrDirections);
	fDirectionsAttri->Style = Synhighlighterdot__1;
	fDirectionsAttri->Foreground = (TColor) clYellow;
	AddAttribute(fDirectionsAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterdot__2;
	AddAttribute(fKeyAttri);
	fShapeAttri = new TSynHighlighterAttributes(SYNS_AttrShape, SYNS_FriendlyAttrShape);
	fShapeAttri->Style = Synhighlighterdot__3;
	fShapeAttri->Foreground = (TColor) clRed;
	AddAttribute(fShapeAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	AddAttribute(fStringAttri);
	fValueAttri = new TSynHighlighterAttributes(SYNS_AttrValue, SYNS_FriendlyAttrValue);
	fValueAttri->Style = Synhighlighterdot__4;
	fValueAttri->Foreground = (TColor) clRed;
	AddAttribute(fValueAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	fSymbolAttri->Style = Synhighlighterdot__5;
	fSymbolAttri->Foreground = (TColor) clGreen;
	AddAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterDOT;
}

void __fastcall TSynDOTSyn::IdentProc()
{
	fTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynDOTSyn::UnknownProc()
{
	++Run;
	fTokenID = tkUnknown;
}

void __fastcall TSynDOTSyn::SymbolProc()
{
	++Run;
	fTokenID = tkSymbol;
}

void __fastcall TSynDOTSyn::Next()
{
	fTokenPos = Run;
	switch(fRange)
	{
		case rsCStyleComment:
		CStyleCommentProc();
		break;
		default:
		{
			fRange = rsUnKnown;
			switch(fLine[Run])
			{
				case L'\x00':
				NullProc();
				break;
				case L'\x0a':
				LFProc();
				break;
				case L'\x0d':
				CRProc();
				break;
				case L'/':
				CStyleCommentOpenProc();
				break;
				case L'-':
				DirectionsProc();
				break;
				case L'\'':
				StringOpenProc();
				break;
				case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
				case L'\x0b':
				case L'\x0c':
				case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
				 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
				SpaceProc();
				break;
				case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
				 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
				 case 85: case 86: case 87: case 88: case 89: case 90:
				case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
				 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
				 case 117: case 118: case 119: case 120: case 121: case 122:
				case L'_':
				IdentProc();
				break;
				case L'~':
				case L'{':
				case L'}':
				case L',':
				case L'(':
				case L')':
				case L'[':
				case L']':
				case L'<':
				case L'>':
				case L':':
				case L'?':
				case L';':
				case L'!':
				case L'=':
				SymbolProc();
				break;
				default:
				UnknownProc();
				break;
			}
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynDOTSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_COMMENT:
		result = fCommentAttri;
		break;
		case SYN_ATTR_IDENTIFIER:
		result = fIdentifierAttri;
		break;
		case SYN_ATTR_KEYWORD:
		result = fKeyAttri;
		break;
		case SYN_ATTR_STRING:
		result = fStringAttri;
		break;
		case SYN_ATTR_WHITESPACE:
		result = fSpaceAttri;
		break;
		case SYN_ATTR_SYMBOL:
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynDOTSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

String __fastcall TSynDOTSyn::GetKeyWords(int TokenKind)
{
	String result;
	result = L"--,->,all,appendix,arrowhead,arrowsize,arrowtail,auto,back,bgcolor,bo"
	           L"ld,both,bottomlabel,box,center,circle,clusterrank,color,comment,compou"
	           L"nd,concentrate,constraint,decorate,diamond,digraph,dir,distortion,dot,"
	           L"dotted,doublecircle,doubleoctagon,e,edge,egg,ellipse,false,fill,fillco"
	           L"lor,filled,fixedsize,fontcolor,fontname,fontpath,fontsize,forward,glob"
	           L"al,graph,group,headlabel,headport,headURL,height,hexagon,house,id,inv,"
	           L"invdot,invhouse,invodot,invtrapezium,invtriangle,label,labelangle,labe"
	           L"ldistance,labelfloat,labelfontcolor,labelfontname,labelfontsize,labelj"
	           L"ust,labelloc,layer,layers,lhead,ltail,margin,max,mcircle,mclimit,mdiam"
	           L"ond,merged,min,minimum,minlen,mrecord,msquare,multiples,n,ne,node,node"
	           L"sep,none,normal,nslimit,nw,octagon,odot,onto,ordering,orientation,page"
	           L",pagedir,parallelogram,peripheries,plaintext,point,polygon,quantum,ran"
	           L"k,rankdir,ranksep,ratio,record,regular,remincross,rotate,s,same,samehe"
	           L"ad,sametail,samplepoints,se,searchsize,section,shape,shapefile,sides,s"
	           L"ink,size,skew,source,strict,style,subgraph,sw,taillabel,tailport,tailU"
	           L"RL,toplabel,trapezium,triangle,tripleoctagon,true,url,w,weight,when,wi"
	           L"dth,z";
	return result;
}

TtkTokenKind __fastcall TSynDOTSyn::GetTokenID()
{
	TtkTokenKind result = tkArrowHead;
	result = fTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynDOTSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkArrowHead:
		result = fArrowHeadAttri;
		break;
		case tkAttribute:
		result = fAttributeAttri;
		break;
		case tkComment:
		result = fCommentAttri;
		break;
		case tkDirections:
		result = fDirectionsAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkShape:
		result = fShapeAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkValue:
		result = fValueAttri;
		break;
		case tkUnknown:
		result = fIdentifierAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynDOTSyn::GetTokenKind()
{
	int result = 0;
	result = int(fTokenID);
	return result;
}

String __fastcall TSynDOTSyn::GetSampleSource()
{
	String result;
	result = L"// ATT DOT Graphic description language\x0d\x0a"
	           L"digraph asde91 {\x0d\x0a"
	           L"  ranksep=.75; size = \"7.5,7.5\";\x0d\x0a"
	           L"  {\x0d\x0a"
	           L"      node [shape=plaintext, fontsize=16];\x0d\x0a"
	           L"      /* the time-line graph */\x0d\x0a"
	           L"      past -> 1978 -> 1980 -> 1982 -> 1983 -> 1985 -> 1986 ->\x0d\x0a"
	           L"      1987 -> 1988 -> 1989 -> 1990 -> \"future\";\x0d\x0a"
	           L"      /* ancestor programs */\x0d\x0a"
	           L"      \"Bourne sh\"; \"make\"; \"SCCS\"; \"yacc\"; \"cron\"; \"Reiser cpp\";\x0d\x0a"
	           L"      \"Cshell\"; \"emacs\"; \"build\"; \"vi\"; \"<curses>\"; \"RCS\"; \"C*\";\x0d\x0a"
	           L"  }\x0d\x0a"
	           L"      { rank = same;\x0d\x0a"
	           L"      \"Software IS\"; \"Configuration Mgt\"; \"Architecture & Libraries\";\x0d\x0a"
	           L"      \"Process\";\x0d\x0a"
	           L"  };\x0d\x0a"
	           L"    node [shape=box];\x0d\x0a"
	           L"    { rank = same; \"past\"; \"SCCS\"; \"make\"; \"Bourne sh\"; \"yacc\"; \"cron\"; }\x0d\x0a"
	           L"    { rank = same; 1978; \"Reiser cpp\"; \"Cshell\"; }\x0d\x0a"
	           L"    { rank = same; 1980; \"build\"; \"emacs\"; \"vi\"; }\x0d\x0a"
	           L"    { rank = same; 1982; \"RCS\"; \"<curses>\"; \"IMX\"; \"SYNED\"; }\x0d\x0a"
	           L"    { rank = same; 1983; \"ksh\"; \"IFS\"; \"TTU\"; }\x0d\x0a"
	           L"    { rank = same; 1985; \"nmake\"; \"Peggy\"; }\x0d\x0a"
	           L"    { rank = same; 1986; \"C*\"; \"ncpp\"; \"ksh-i\"; \"<curses-i>\"; \"PG2\"; }\x0d\x0a"
	           L"    { rank = same; 1987; \"Ansi cpp\"; \"nmake 2.0\"; \"3D File System\"; \"fdelta\";\x0d\x0a"
	           L"        \"DAG\"; \"CSAS\";}\x0d\x0a"
	           L"    { rank = same; 1988; \"CIA\"; \"SBCS\"; \"ksh-88\"; \"PEGASUS/PML\"; \"PAX\";\x0d\x0a"
	           L"        \"backtalk\"; }\x0d\x0a"
	           L"    { rank = same; 1989; \"CIA++\"; \"APP\"; \"SHIP\"; \"DataShare\"; \"ryacc\";\x0d\x0a"
	           L"        \"Mosaic\"; }\x0d\x0a"
	           L"    { rank = same; 1990; \"libft\"; \"CoShell\"; \"DIA\"; \"IFS-i\"; \"kyacc\"; \"sfio\";\x0d\x0a"
	           L"        \"yeast\"; \"ML-X\"; \"DOT\"; }\x0d\x0a"
	           L"    { rank = same; \"future\"; \"Adv. Software Technology\"; }\x0d\x0a"
	           L"    \"PEGASUS/PML\" -> \"ML-X\";\x0d\x0a"
	           L"    \"SCCS\" -> \"nmake\";\x0d\x0a"
	           L"    \"SCCS\" -> \"3D File System\";\x0d\x0a"
	           L"    \"SCCS\" -> \"RCS\";\x0d\x0a"
	           L"    \"make\" -> \"nmake\";\x0d\x0a"
	           L"    \"make\" -> \"build\";\x0d\x0a"
	           L"}";
	return result;
}

bool __fastcall TSynDOTSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterDOT;
	return result;
}

bool __fastcall TSynDOTSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'_':
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

/*#static*/
String __fastcall TSynDOTSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangDOT;
	return result;
}

void __fastcall TSynDOTSyn::ResetRange()
{
	fRange = rsUnKnown;
}

void __fastcall TSynDOTSyn::SetRange(void* Value)
{
	fRange = (TRangeState)(NativeInt)Value;
}

void* __fastcall TSynDOTSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) fRange);
	return result;
}

/*#static*/
String __fastcall TSynDOTSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangDOT;
	return result;
}
static bool SynHighlighterDOT_Initialized = false;

void SynHighlighterDOT_initialization()
{
	if(SynHighlighterDOT_Initialized)
		return;
	
	SynHighlighterDOT_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynDOTSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterDOT

