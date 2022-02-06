
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterADSP21xx.h"
#include <Winapi.Windows.hpp>
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Synhighlighteradsp21xx
{
#define SynHighlighterADSP21xx__0 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterADSP21xx__1 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterADSP21xx__2 (TSysCharSet() <<  \
										48 << 49)
#define SynHighlighterADSP21xx__3 (TSysCharSet() <<  \
										50 << 51 << 52 << 53 << 54 << 55 <<  \
										56 << 57 <<  \
										65 << 66 << 67 << 68 << 69 << 70 <<  \
										97 << 98 << 99 << 100 << 101 << 102)
#define SynHighlighterADSP21xx__4 (TSynHighlighterCapabilities() << TSynHighlighterCapability::hcUserSettings)


const String Keywords[179/*# range 0..178*/] = {L"abs", L"abstract", L"ac", L"af", L"alt_reg", L"and", L"ar", L"ar_sat", L"ashift", L"astat", L"aux", L"av", L"av_latch"
																				, L"ax0", L"ax1", L"ay0", L"ay1", L"b", L"bit_rev", L"bm", L"boot", L"by", L"cache", L"call", L"ce", L"circ", L"clear", L"clr"
																				, L"clrbit", L"cntl", L"cntr", L"const", L"define", L"dis", L"divq", L"divs", L"dm", L"dmovlay", L"do", L"else", L"emode", L"ena"
																				, L"endif", L"endmacro", L"endmod", L"entry", L"eq", L"exp", L"expadj", L"external", L"fl0", L"fl1", L"fl2", L"flag_in", L"flag_out"
																				, L"for", L"forever", L"ge", L"global", L"go_mode", L"gt", L"h", L"hi", L"i0", L"i1", L"i2", L"i3", L"i4", L"i5", L"i6", L"i7", L"icntl"
																				, L"idle", L"if", L"ifc", L"ifdef", L"ifndef", L"imask", L"in", L"include", L"init", L"io", L"jump", L"l0", L"l1", L"l2", L"l3", L"l4"
																				, L"l5", L"l6", L"l7", L"le", L"lo", L"local", L"loop", L"lshift", L"lt", L"m_mode", L"m0", L"m1", L"m2", L"m3", L"m4", L"m5", L"m6", L"m7"
																				, L"macro", L"mf", L"modify", L"module", L"mr", L"mr0", L"mr1", L"mr2", L"mstat", L"mv", L"mx0", L"mx1", L"my0", L"my1", L"name", L"ne"
																				, L"neg", L"newpage", L"nop", L"norm", L"not", L"of", L"or", L"pass", L"pc", L"pm", L"pop", L"port", L"push", L"ram", L"regbank", L"reset"
																				, L"rnd", L"rom", L"rti", L"rts", L"rx0", L"rx1", L"sat", L"sb", L"sec_reg", L"seg", L"segment", L"set", L"setbit", L"shift", L"shl"
																				, L"shr", L"si", L"sr", L"sr0", L"sr1", L"ss", L"sstat", L"static", L"sts", L"su", L"test", L"testbit", L"tglbit", L"timer", L"toggle"
																				, L"topofpcstack", L"trap", L"true", L"tx0", L"tx1", L"undef", L"until", L"us", L"uu", L"var", L"xor"};
const int KeyIndices[821/*# range 0..820*/] = {-1, -1, -1, -1, -1, -1, -1, -1, 110, -1, -1, -1, -1, -1, -1, -1, -1, -1, 67, 15, -1, 48, 100, 132, -1, -1, -1, -1, -1, 133, -1, -1, -1, -1, -1, -1, -1, 152, 93
																				, 155, -1, -1, -1, 70, 62, -1, -1, 103, 0, -1, -1, 10, -1, -1, -1, -1, -1, -1, 171, -1, -1, -1, -1, 120, 162, -1, -1, -1, -1, -1, 82, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 153
																				, -1, -1, -1, 50, -1, -1, -1, -1, -1, -1, 72, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1, -1, -1, 25, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, 156, 83
																				, -1, -1, -1, -1, -1, 77, 106, -1, 45, 27, -1, -1, -1, -1, -1, 7, -1, -1, 43, -1, 74, 14, 174, 73, 86, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 56, -1, -1, -1, -1, 111, -1, -1, 140, -1, -1, -1
																				, 89, -1, -1, -1, -1, 127, -1, -1, -1, 28, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 116, -1, 49, -1, -1, 164, 23, -1, -1, 9, -1, -1, -1, -1, 149, -1, -1, -1, 40, -1, -1, 46, -1, 94, -1
																				, 81, -1, 134, -1, -1, -1, -1, -1, -1, -1, 55, -1, 47, -1, -1, -1, -1, 11, -1, 135, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 109, -1, -1, -1, -1, -1, -1, 65, 142, -1, -1, 98, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, 128, -1, -1, -1, -1, -1, 18, -1, 68, 16, -1, -1, 101, 91, -1, -1, -1, 130, -1, 167, -1, -1, -1, 115, -1, -1, -1, -1, 19, 158, -1, 163, -1, -1, -1, -1, -1, 104, -1, -1
																				, -1, -1, -1, -1, -1, 39, -1, 79, 172, -1, -1, -1, -1, 41, -1, 38, 176, 80, -1, -1, -1, 118, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 71, 75, -1, -1, 51, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, 138, -1, -1, -1, -1, -1, -1, 42, -1, -1, -1, -1, -1, -1, 58, -1, -1, 136, -1, -1, -1, -1, -1, -1, 177, -1, -1, -1, -1, -1, -1, -1, 57, -1, 157, 84, 21, -1, -1, -1, -1, -1, 1, -1, -1, -1
																				, 96, 161, -1, -1, 123, -1, -1, -1, -1, -1, -1, -1, -1, -1, 87, -1, -1, -1, 54, 137, -1, -1, 124, 145, -1, -1, -1, -1, -1, -1, -1, -1, 112, -1, -1, 173, -1, -1, -1, 90, -1, 125, -1, 166, -1, -1
																				, -1, -1, 144, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 117, -1, -1, 170, -1, -1, 35, -1, -1, -1, -1, -1, -1, -1, 148, -1, 44, -1, -1, -1, -1, 159, -1, -1, -1, -1, -1, 150, -1, -1, -1
																				, -1, 31, -1, -1, -1, -1, -1, -1, 63, -1, -1, -1, 178, -1, -1, -1, 141, 60, -1, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 66, 143, -1, -1, 99, -1, -1, 97, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, 37, -1, -1, 26, -1, -1, 69, -1, -1, -1, 102, -1, -1, 121, -1, -1, -1, 61, 129, 95, -1, -1, -1, 122, -1, 139, -1, -1, 36, 175, -1, -1, -1, -1, -1, 105, -1, -1, -1, -1, -1, 108, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, 32, -1, -1, -1, -1, -1, 119, -1, -1, -1, -1, -1, -1, 2, -1, -1, 165, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52, -1, -1, -1, -1, -1, -1, 92, -1, 147, -1, 131, 3, -1, 24
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 168, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, 13, -1, -1, 85, 59, -1, -1, 146, -1, -1, -1, -1, -1, -1, -1, -1, -1, 33, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, 88, -1, -1, 107, -1, -1, -1, -1, -1, -1, 160, -1, -1, -1, -1, -1, -1, -1, 113, 151, -1, -1, -1, -1, 53, -1, -1, -1, -1, -1, 34, 29, 169, 126, 114, -1, -1, 22, -1, -1, -1
																				, 6, -1, -1, -1, -1, -1, -1, -1, 78, -1, -1, -1, -1, -1, -1, -1, -1, -1, 154, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 76, -1, -1, -1, -1, -1, 5, 30, -1, -1, -1, -1, -1, -1, 64, -1, -1, -1
																				, -1, -1, -1};

/*$Q-*/

unsigned int __fastcall TSynADSP21xxSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 641 + int((*Str)) * 282);
		++Str;
	}
	result = (unsigned int) (result % 821);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynADSP21xxSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 820 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynADSP21xxSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 820 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] ==  - 1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[48] = FuncAbs;
	fIdentFuncTable[426] = FuncAbstract;
	fIdentFuncTable[642] = FuncAc;
	fIdentFuncTable[667] = FuncAf;
	fIdentFuncTable[693] = FuncAlt95reg;
	fIdentFuncTable[806] = FuncAnd;
	fIdentFuncTable[767] = FuncAr;
	fIdentFuncTable[153] = FuncAr95sat;
	fIdentFuncTable[126] = FuncAshift;
	fIdentFuncTable[220] = FuncAstat;
	fIdentFuncTable[51] = FuncAux;
	fIdentFuncTable[253] = FuncAv;
	fIdentFuncTable[99] = FuncAv95latch;
	fIdentFuncTable[698] = FuncAx0;
	fIdentFuncTable[159] = FuncAx1;
	fIdentFuncTable[19] = FuncAy0;
	fIdentFuncTable[301] = FuncAy1;
	fIdentFuncTable[543] = FuncB;
	fIdentFuncTable[298] = FuncBit95rev;
	fIdentFuncTable[320] = FuncBm;
	fIdentFuncTable[118] = FuncBoot;
	fIdentFuncTable[420] = FuncBy;
	fIdentFuncTable[763] = FuncCache;
	fIdentFuncTable[217] = FuncCall;
	fIdentFuncTable[669] = FuncCe;
	fIdentFuncTable[122] = FuncCirc;
	fIdentFuncTable[579] = FuncClear;
	fIdentFuncTable[147] = FuncClr;
	fIdentFuncTable[196] = FuncClrbit;
	fIdentFuncTable[757] = FuncCntl;
	fIdentFuncTable[807] = FuncCntr;
	fIdentFuncTable[525] = FuncConst;
	fIdentFuncTable[629] = FuncDefine;
	fIdentFuncTable[715] = FuncDis;
	fIdentFuncTable[756] = FuncDivq;
	fIdentFuncTable[499] = FuncDivs;
	fIdentFuncTable[604] = FuncDm;
	fIdentFuncTable[576] = FuncDmovlay;
	fIdentFuncTable[347] = FuncDo;
	fIdentFuncTable[337] = FuncElse;
	fIdentFuncTable[229] = FuncEmode;
	fIdentFuncTable[345] = FuncEna;
	fIdentFuncTable[391] = FuncEndif;
	fIdentFuncTable[156] = FuncEndmacro;
	fIdentFuncTable[509] = FuncEndmod;
	fIdentFuncTable[146] = FuncEntry;
	fIdentFuncTable[232] = FuncEq;
	fIdentFuncTable[248] = FuncExp;
	fIdentFuncTable[21] = FuncExpadj;
	fIdentFuncTable[213] = FuncExternal;
	fIdentFuncTable[91] = FuncFl0;
	fIdentFuncTable[373] = FuncFl1;
	fIdentFuncTable[655] = FuncFl2;
	fIdentFuncTable[750] = FuncFlag95in;
	fIdentFuncTable[448] = FuncFlag95out;
	fIdentFuncTable[246] = FuncFor;
	fIdentFuncTable[175] = FuncForever;
	fIdentFuncTable[416] = FuncGe;
	fIdentFuncTable[398] = FuncGlobal;
	fIdentFuncTable[702] = FuncGo95mode;
	fIdentFuncTable[541] = FuncGt;
	fIdentFuncTable[593] = FuncH;
	fIdentFuncTable[44] = FuncHi;
	fIdentFuncTable[532] = FuncI0;
	fIdentFuncTable[814] = FuncI1;
	fIdentFuncTable[275] = FuncI2;
	fIdentFuncTable[557] = FuncI3;
	fIdentFuncTable[18] = FuncI4;
	fIdentFuncTable[300] = FuncI5;
	fIdentFuncTable[582] = FuncI6;
	fIdentFuncTable[43] = FuncI7;
	fIdentFuncTable[369] = FuncIcntl;
	fIdentFuncTable[98] = FuncIdle;
	fIdentFuncTable[161] = FuncIf;
	fIdentFuncTable[158] = FuncIfc;
	fIdentFuncTable[370] = FuncIfdef;
	fIdentFuncTable[800] = FuncIfndef;
	fIdentFuncTable[143] = FuncImask;
	fIdentFuncTable[775] = FuncIn;
	fIdentFuncTable[339] = FuncInclude;
	fIdentFuncTable[349] = FuncInit;
	fIdentFuncTable[236] = FuncIo;
	fIdentFuncTable[70] = FuncJump;
	fIdentFuncTable[137] = FuncL0;
	fIdentFuncTable[419] = FuncL1;
	fIdentFuncTable[701] = FuncL2;
	fIdentFuncTable[162] = FuncL3;
	fIdentFuncTable[444] = FuncL4;
	fIdentFuncTable[726] = FuncL5;
	fIdentFuncTable[187] = FuncL6;
	fIdentFuncTable[469] = FuncL7;
	fIdentFuncTable[305] = FuncLe;
	fIdentFuncTable[662] = FuncLo;
	fIdentFuncTable[38] = FuncLocal;
	fIdentFuncTable[234] = FuncLoop;
	fIdentFuncTable[595] = FuncLshift;
	fIdentFuncTable[430] = FuncLt;
	fIdentFuncTable[564] = FuncM95mode;
	fIdentFuncTable[279] = FuncM0;
	fIdentFuncTable[561] = FuncM1;
	fIdentFuncTable[22] = FuncM2;
	fIdentFuncTable[304] = FuncM3;
	fIdentFuncTable[586] = FuncM4;
	fIdentFuncTable[47] = FuncM5;
	fIdentFuncTable[329] = FuncM6;
	fIdentFuncTable[611] = FuncM7;
	fIdentFuncTable[144] = FuncMacro;
	fIdentFuncTable[729] = FuncMf;
	fIdentFuncTable[617] = FuncModify;
	fIdentFuncTable[268] = FuncModule;
	fIdentFuncTable[8] = FuncMr;
	fIdentFuncTable[180] = FuncMr0;
	fIdentFuncTable[462] = FuncMr1;
	fIdentFuncTable[744] = FuncMr2;
	fIdentFuncTable[760] = FuncMstat;
	fIdentFuncTable[315] = FuncMv;
	fIdentFuncTable[211] = FuncMx0;
	fIdentFuncTable[493] = FuncMx1;
	fIdentFuncTable[353] = FuncMy0;
	fIdentFuncTable[635] = FuncMy1;
	fIdentFuncTable[63] = FuncName;
	fIdentFuncTable[589] = FuncNe;
	fIdentFuncTable[599] = FuncNeg;
	fIdentFuncTable[434] = FuncNewpage;
	fIdentFuncTable[452] = FuncNop;
	fIdentFuncTable[471] = FuncNorm;
	fIdentFuncTable[759] = FuncNot;
	fIdentFuncTable[192] = FuncOf;
	fIdentFuncTable[292] = FuncOr;
	fIdentFuncTable[594] = FuncPass;
	fIdentFuncTable[309] = FuncPc;
	fIdentFuncTable[666] = FuncPm;
	fIdentFuncTable[23] = FuncPop;
	fIdentFuncTable[29] = FuncPort;
	fIdentFuncTable[238] = FuncPush;
	fIdentFuncTable[255] = FuncRam;
	fIdentFuncTable[401] = FuncRegbank;
	fIdentFuncTable[449] = FuncReset;
	fIdentFuncTable[384] = FuncRnd;
	fIdentFuncTable[601] = FuncRom;
	fIdentFuncTable[183] = FuncRti;
	fIdentFuncTable[540] = FuncRts;
	fIdentFuncTable[276] = FuncRx0;
	fIdentFuncTable[558] = FuncRx1;
	fIdentFuncTable[478] = FuncSat;
	fIdentFuncTable[453] = FuncSb;
	fIdentFuncTable[705] = FuncSec95reg;
	fIdentFuncTable[664] = FuncSeg;
	fIdentFuncTable[507] = FuncSegment;
	fIdentFuncTable[225] = FuncSet;
	fIdentFuncTable[520] = FuncSetbit;
	fIdentFuncTable[745] = FuncShift;
	fIdentFuncTable[37] = FuncShl;
	fIdentFuncTable[87] = FuncShr;
	fIdentFuncTable[785] = FuncSi;
	fIdentFuncTable[39] = FuncSr;
	fIdentFuncTable[136] = FuncSr0;
	fIdentFuncTable[418] = FuncSr1;
	fIdentFuncTable[321] = FuncSs;
	fIdentFuncTable[514] = FuncSstat;
	fIdentFuncTable[736] = FuncStatic;
	fIdentFuncTable[431] = FuncSts;
	fIdentFuncTable[64] = FuncSu;
	fIdentFuncTable[323] = FuncTest;
	fIdentFuncTable[216] = FuncTestbit;
	fIdentFuncTable[645] = FuncTglbit;
	fIdentFuncTable[473] = FuncTimer;
	fIdentFuncTable[311] = FuncToggle;
	fIdentFuncTable[683] = FuncTopofpcstack;
	fIdentFuncTable[758] = FuncTrap;
	fIdentFuncTable[496] = FuncTrue;
	fIdentFuncTable[58] = FuncTx0;
	fIdentFuncTable[340] = FuncTx1;
	fIdentFuncTable[465] = FuncUndef;
	fIdentFuncTable[160] = FuncUntil;
	fIdentFuncTable[605] = FuncUs;
	fIdentFuncTable[348] = FuncUu;
	fIdentFuncTable[408] = FuncVar;
	fIdentFuncTable[536] = FuncXor;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAbs(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAbstract(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAf(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAlt95reg(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAnd(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAr95sat(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAshift(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAstat(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAux(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAv(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAv95latch(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAx0(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAx1(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAy0(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncAy1(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncB(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(fLine[Run + 1] == L'#')
		{
			result = tkNumber;
			FRange = rsBinaryNumber;
		}
		else
		{
			result = tkIdentifier;
		}
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncBit95rev(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncBm(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncBoot(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncBy(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncCache(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncCall(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncCe(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncCirc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncClear(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncClr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncClrbit(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncCntl(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncCntr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncConst(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncDefine(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncDis(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncDivq(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncDivs(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncDm(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncDmovlay(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncDo(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncElse(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncEmode(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncEna(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncEndif(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncEndmacro(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncEndmod(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncEntry(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncEq(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncExp(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncExpadj(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncExternal(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncFl0(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncFl1(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncFl2(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncFlag95in(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncFlag95out(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncFor(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncForever(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncGe(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncGlobal(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncGo95mode(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncGt(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncH(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(fLine[Run + 1] == L'#')
		{
			result = tkNumber;
			FRange = rsHexNumber;
		}
		else
		{
			result = tkIdentifier;
		}
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncHi(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncI0(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncI1(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncI2(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncI3(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncI4(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncI5(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncI6(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncI7(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncIcntl(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncIdle(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncIf(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncIfc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncIfdef(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncIfndef(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncImask(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncIn(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncInclude(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncInit(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncIo(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncJump(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncL0(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncL1(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncL2(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncL3(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncL4(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncL5(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncL6(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncL7(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncLe(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncLo(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncLocal(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncLoop(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncLshift(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncLt(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncM95mode(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncM0(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncM1(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncM2(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncM3(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncM4(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncM5(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncM6(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncM7(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncMacro(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncMf(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncModify(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncModule(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncMr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncMr0(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncMr1(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncMr2(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncMstat(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncMv(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncMx0(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncMx1(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncMy0(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncMy1(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncName(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncNe(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncNeg(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncNewpage(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncNop(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncNorm(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncNot(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncOf(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncOr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncPass(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncPc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncPm(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncPop(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncPort(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncPush(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncRam(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncRegbank(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncReset(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncRnd(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncRom(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncRti(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncRts(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncRx0(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncRx1(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSat(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSb(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSec95reg(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSeg(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSegment(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSet(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSetbit(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncShift(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncShl(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncShr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSi(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSr0(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSr1(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSs(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSstat(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncStatic(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSts(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncSu(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncTest(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncTestbit(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncTglbit(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncTimer(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncToggle(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncTopofpcstack(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncTrap(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncTrue(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncTx0(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncTx1(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkRegister;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncUndef(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncUntil(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncUs(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncUu(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkCondition;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncVar(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::FuncXor(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynADSP21xxSyn::TSynADSP21xxSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkComment),
			fNumberAttri(nullptr),
			fStringAttri(nullptr),
			fKeyAttri(nullptr),
			fSymbolAttri(nullptr),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fSpaceAttri(nullptr),
			fRegisterAttri(nullptr),
			fConditionAttri(nullptr),
			fNullAttri(nullptr),
			fUnknownAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Foreground = clTeal;
	fCommentAttri->Style = SynHighlighterADSP21xx__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = SynHighlighterADSP21xx__1;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = clOlive;
	addAttribute(fNumberAttri);
	fRegisterAttri = new TSynHighlighterAttributes(SYNS_AttrRegister, SYNS_FriendlyAttrRegister);
	fRegisterAttri->Foreground = clBlue;
	addAttribute(fRegisterAttri);
	fConditionAttri = new TSynHighlighterAttributes(SYNS_AttrCondition, SYNS_FriendlyAttrCondition);
	fConditionAttri->Foreground = clFuchsia;
	addAttribute(fConditionAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fNullAttri = new TSynHighlighterAttributes(SYNS_AttrNull, SYNS_FriendlyAttrNull);
	addAttribute(fNullAttri);
	fUnknownAttri = new TSynHighlighterAttributes(SYNS_AttrUnknownWord, SYNS_FriendlyAttrUnknownWord);
	addAttribute(fUnknownAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterADSP21xx;
}

void __fastcall TSynADSP21xxSyn::BraceCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynADSP21xxSyn::StringProc()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x27') && (fLine[Run + 2] == L'\x27'))
		Run += 2;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label0;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x27'));
	label0:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynADSP21xxSyn::PascalCommentProc()
{
	FTokenID = tkComment;
	switch(fLine[Run])
	{
		case L'\x00':
		{
			NullProc();
			return;
		}
		case L'\x0a':
		{
			LFProc();
			return;
		}
		case L'\x0d':
		{
			CRProc();
			return;
		}
		default:
		  ;
		break;
	}
	while(fLine[Run] != L'\x00')
		switch(fLine[Run])
		{
			case L'}':
			{
				FRange = rsUnKnown;
				++Run;
				goto label1;
			}
			case L'\x0a':
			goto label2;
			case L'\x0d':
			goto label3;
			default:
			++Run;
			break;
		}
	label1:;
	label2:;
	label3:;
}

void __fastcall TSynADSP21xxSyn::CCommentProc()
{
	FTokenID = tkComment;
	switch(fLine[Run])
	{
		case L'\x00':
		{
			NullProc();
			return;
		}
		case L'\x0a':
		{
			LFProc();
			return;
		}
		case L'\x0d':
		{
			CRProc();
			return;
		}
		default:
		  ;
		break;
	}
	while(fLine[Run] != L'\x00')
		switch(fLine[Run])
		{
			case L'*':
			{
				if(fLine[Run + 1] == L'/')
				{
					FRange = rsUnKnown;
					Run += 2;
					goto label4;
				}
				else
				++Run;
			}
			break;
			case L'\x0a':
			goto label5;
			case L'\x0d':
			goto label6;
			default:
			++Run;
			break;
		}
	label4:;
	label5:;
	label6:;
}

void __fastcall TSynADSP21xxSyn::BraceOpenProc()
{
	FTokenID = tkComment;
	FRange = rsPascalComment;
	++Run;
	while(fLine[Run] != L'\x00')
		switch(fLine[Run])
		{
			case L'}':
			{
				FRange = rsUnKnown;
				++Run;
				goto label7;
			}
			case L'\x0a':
			goto label8;
			case L'\x0d':
			goto label9;
			default:
			++Run;
			break;
		}
	label7:;
	label8:;
	label9:;
}

void __fastcall TSynADSP21xxSyn::IncludeCloseProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynADSP21xxSyn::CRProc()
{
	FTokenID = tkSpace;
	switch(fLine[Run + 1])
	{
		case L'\x0a':
		Run += 2;
		break;
		default:
		++Run;
		break;
	}
}

void __fastcall TSynADSP21xxSyn::ExclamationProc()
{
	FTokenID = tkComment;
	do
	{
		++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynADSP21xxSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynADSP21xxSyn::IntegerProc()
{

	auto IsIntegerChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	++Run;
	FTokenID = tkNumber;
	while(IsIntegerChar())
		++Run;
}

void __fastcall TSynADSP21xxSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynADSP21xxSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynADSP21xxSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			case L'x':
			case L'X':
			case L'.':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	++Run;
	FTokenID = tkNumber;
	while(IsNumberChar())
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Run + 1] == L'.')
				goto label10;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label10:;
}

void __fastcall TSynADSP21xxSyn::HexNumber()
{

	auto IsHexChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	++Run;
	FTokenID = tkNumber;
	FRange = rsUnKnown;
	while(IsHexChar())
	{
		++Run;
	}
}

void __fastcall TSynADSP21xxSyn::BinaryNumber()
{
	++Run;
	FRange = rsUnKnown;
	while(CharInSet(fLine[Run], SynHighlighterADSP21xx__2))
	{
		++Run;
	}
	if(CharInSet(fLine[Run], SynHighlighterADSP21xx__3))
	{
		FTokenID = tkIdentifier;
	}
	else
	FTokenID = tkNumber;
}

void __fastcall TSynADSP21xxSyn::SlashProc()
{
	if(fLine[Run + 1] == L'*')
	{
		FTokenID = tkComment;
		FRange = rsCComment;
		Run += 2;
		while(fLine[Run] != L'\x00')
			switch(fLine[Run])
			{
				case L'*':
				{
					if(fLine[Run + 1] == L'/')
					{
						Run += 2;
						FRange = rsUnKnown;
						goto label11;
					}
					else
					++Run;
				}
				break;
				case L'\x0a':
				goto label12;
				case L'\x0d':
				goto label13;
				default:
				++Run;
				break;
			}
		label11:;
		label12:;
		label13:;
	}
	else
	{
		++Run;
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynADSP21xxSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynADSP21xxSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynADSP21xxSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsPascalComment:
		PascalCommentProc();
		break;
		case rsCComment:
		CCommentProc();
		break;
		case rsHexNumber:
		HexNumber();
		break;
		case rsBinaryNumber:
		BinaryNumber();
		break;
		default:
		FRange = rsUnKnown;
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
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			case L'\x0b':
			case L'\x0c':
			case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
			 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
			SpaceProc();
			break;
			case L'$':
			IntegerProc();
			break;
			case L'\x27':
			StringProc();
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			NumberProc();
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
			case L'{':
			BraceOpenProc();
			break;
			case L'}':
			BraceCloseProc();
			break;
			case L'/':
			SlashProc();
			break;
			case L'>':
			IncludeCloseProc();
			break;
			case L'!':
			ExclamationProc();
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynADSP21xxSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynADSP21xxSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynADSP21xxSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

int __fastcall TSynADSP21xxSyn::GetTokenKind()
{
	int result = 0;
	result = int(GetTokenID());
	return result;
}

TSynHighlighterAttributes* __fastcall TSynADSP21xxSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkNumber:
		result = fNumberAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkRegister:
		result = fRegisterAttri;
		break;
		case tkCondition:
		result = fConditionAttri;
		break;
		case tkUnknown:
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

void* __fastcall TSynADSP21xxSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

void __fastcall TSynADSP21xxSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(int)Value;
}

void __fastcall TSynADSP21xxSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynADSP21xxSyn::EnumUserSettings(TStrings* Settings)
{

  /* returns the user settings that exist in the registry */
	/*# with TBetterRegistry.Create do */
	{
		auto with0 = new TBetterRegistry();
		try
		{
			with0->RootKey = HKEY_CURRENT_USER;
      // we need some method to make the following statement more universal!
			if(with0->OpenKeyReadOnly(L"\\SOFTWARE\\Wynand\\DSPIDE\\1.0"))
			{
				try
				{
					with0->GetKeyNames(Settings);
				}
				__finally
				{
					with0->CloseKey();
				}
			}
		}
		__finally
		{
			delete with0;
		}
	}
}
// Possible parameter values:
//   index into TStrings returned by EnumUserSettings
// Possible return values:
//   true : settings were read and used
//   false: problem reading settings or invalid version specified - old settings
//          were preserved

bool __fastcall TSynADSP21xxSyn::UseUserSettings(int settingIndex)
{
	bool result = false;

	auto ReadDspIDESetting = [&](String settingTag, TSynHighlighterAttributes* Attri, String key) -> bool 
	{
		bool result = false;
		try
		{
			result = Attri->LoadFromBorlandRegistry(HKEY_CURRENT_USER, L"\\Software\\Wynand\\DspIDE\\1.0\\Editor\\Highlight", key, false);
		}
		catch(...)
		{
			result = false;
		}
		return result;
	};
	TSynHighlighterAttributes* tmpNumberAttri = nullptr;
	TSynHighlighterAttributes* tmpKeyAttri = nullptr;
	TSynHighlighterAttributes* tmpSymbolAttri = nullptr;
	TSynHighlighterAttributes* tmpCommentAttri = nullptr;
	TSynHighlighterAttributes* tmpConditionAttri = nullptr;
	TSynHighlighterAttributes* tmpIdentifierAttri = nullptr;
	TSynHighlighterAttributes* tmpSpaceAttri = nullptr;
	TSynHighlighterAttributes* tmpRegisterAttri = nullptr;
	TStringList* StrLst = nullptr;  // UseUserSettings
	StrLst = new TStringList();
	try
	{
		EnumUserSettings(StrLst);
		if(settingIndex >= StrLst->Count)
			result = false;
		else
		{
			tmpNumberAttri = new TSynHighlighterAttributes(L"", L"");
			tmpKeyAttri = new TSynHighlighterAttributes(L"", L"");
			tmpSymbolAttri = new TSynHighlighterAttributes(L"", L"");
			tmpCommentAttri = new TSynHighlighterAttributes(L"", L"");
			tmpConditionAttri = new TSynHighlighterAttributes(L"", L"");
			tmpIdentifierAttri = new TSynHighlighterAttributes(L"", L"");
			tmpSpaceAttri = new TSynHighlighterAttributes(L"", L"");
			tmpRegisterAttri = new TSynHighlighterAttributes(L"", L"");
			tmpNumberAttri->Assign(fNumberAttri);
			tmpKeyAttri->Assign(fKeyAttri);
			tmpSymbolAttri->Assign(fSymbolAttri);
			tmpCommentAttri->Assign(fCommentAttri);
			tmpConditionAttri->Assign(fConditionAttri);
			tmpIdentifierAttri->Assign(fIdentifierAttri);
			tmpSpaceAttri->Assign(fSpaceAttri);
			tmpRegisterAttri->Assign(fRegisterAttri);
			result = ReadDspIDESetting(StrLst->Strings[settingIndex], fCommentAttri, L"Comment") && ReadDspIDESetting(StrLst->Strings[settingIndex], fIdentifierAttri, L"Identifier") && ReadDspIDESetting(StrLst->Strings[settingIndex], fKeyAttri, L"Reserved word") && ReadDspIDESetting(StrLst->Strings[settingIndex], fNumberAttri, L"BinaryNumber") && ReadDspIDESetting(StrLst->Strings[settingIndex], fSpaceAttri, L"Whitespace") && ReadDspIDESetting(StrLst->Strings[settingIndex], fSymbolAttri, L"Symbol") && ReadDspIDESetting(StrLst->Strings[settingIndex], fConditionAttri, L"Condition") && ReadDspIDESetting(StrLst->Strings[settingIndex], fRegisterAttri, L"Symbol");
			if(!result)
			{
				fNumberAttri->Assign(tmpNumberAttri);
				fKeyAttri->Assign(tmpKeyAttri);
				fSymbolAttri->Assign(tmpSymbolAttri);
				fCommentAttri->Assign(tmpCommentAttri);
				fConditionAttri->Assign(tmpConditionAttri);
				fIdentifierAttri->Assign(tmpIdentifierAttri);
				fSpaceAttri->Assign(tmpSpaceAttri);
				fConditionAttri->Assign(tmpConditionAttri);
				fRegisterAttri->Assign(tmpRegisterAttri);
			}
			delete tmpNumberAttri;
			delete tmpKeyAttri;
			delete tmpSymbolAttri;
			delete tmpCommentAttri;
			delete tmpConditionAttri;
			delete tmpIdentifierAttri;
			delete tmpSpaceAttri;
			delete tmpRegisterAttri;
		}
	}
	__finally
	{
		delete StrLst;
	}
	return result;
}

bool __fastcall TSynADSP21xxSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterADSP21xx;
	return result;
}

/*#static*/
String __fastcall TSynADSP21xxSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangADSP21xx;
	return result;
}

/*#static*/
TSynHighlighterCapabilities __fastcall TSynADSP21xxSyn::GetCapabilities()
{
	TSynHighlighterCapabilities result;
	result = inherited::GetCapabilities() + SynHighlighterADSP21xx__4;
	return result;
}

/*#static*/
String __fastcall TSynADSP21xxSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangADSP21xx;
	return result;
}
static bool SynHighlighterADSP21xx_Initialized = false;

void SynHighlighterADSP21xx_initialization()
{
	if(SynHighlighterADSP21xx_Initialized)
		return;
	
	SynHighlighterADSP21xx_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynADSP21xxSyn));
}
class SynHighlighterADSP21xx_unit
{
public:
	SynHighlighterADSP21xx_unit()
	{
		SynHighlighterADSP21xx_initialization();
	}
};

SynHighlighterADSP21xx_unit _SynHighlighterADSP21xx_unit;

}  // namespace SynHighlighterADSP21xx

