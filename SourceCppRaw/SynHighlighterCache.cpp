
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterCache.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Uitypes;

namespace Synhighlightercache
{
#define SynHighlighterCache__0 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterCache__1 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterCache__2 (TSysCharSet() << L'\x20' << L':')
#define SynHighlighterCache__3 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define SynHighlighterCache__4 (TSysCharSet() << L'\x20' << L'#')


const String Keywords[275/*# range 0..274*/] = {L"$a", L"$ascii", L"$c", L"$char", L"$d", L"$data", L"$device", L"$e", L"$ec", L"$ecode", L"$es", L"$estack", L"$et"
																				, L"$etrap", L"$extract", L"$f", L"$find", L"$fn", L"$fnumber", L"$g", L"$get", L"$h", L"$horolog", L"$i", L"$in", L"$increment", L"$inumber"
																				, L"$io", L"$j", L"$job", L"$justify", L"$k", L"$key", L"$l", L"$lb", L"$ld", L"$length", L"$lf", L"$lg", L"$li", L"$list", L"$listbuild"
																				, L"$listdata", L"$listfind", L"$listget", L"$listlength", L"$ll", L"$n", L"$na", L"$name", L"$next", L"$o", L"$order", L"$p"
																				, L"$piece", L"$principal", L"$q", L"$ql", L"$qlength", L"$qs", L"$qsubscript", L"$query", L"$quit", L"$r", L"$random", L"$re"
																				, L"$reverse", L"$s", L"$select", L"$st", L"$stack", L"$storage", L"$t", L"$test", L"$text", L"$tl", L"$tlevel", L"$tr", L"$translate"
																				, L"$vi", L"$view", L"$x", L"$y", L"$za", L"$zabs", L"$zarccos", L"$zarcsin", L"$zarctan", L"$zb", L"$zbitand", L"$zbitcount"
																				, L"$zbitfind", L"$zbitget", L"$zbitlen", L"$zbitnot", L"$zbitor", L"$zbitset", L"$zbitstr", L"$zbitxor", L"$zboolean"
																				, L"$zc", L"$zchild", L"$zconvert", L"$zcos", L"$zcot", L"$zcrc", L"$zcsc", L"$zcvt", L"$zcyc", L"$zdate", L"$zdateh", L"$zdatetime"
																				, L"$zdatetimeh", L"$ze", L"$zeof", L"$zerr", L"$zerror", L"$zexp", L"$zf", L"$zh", L"$zhex", L"$zhorolog", L"$zi", L"$zincr"
																				, L"$zincrement", L"$zio", L"$zis", L"$ziswide", L"$zjob", L"$zla", L"$zlascii", L"$zlc", L"$zlchar", L"$zln", L"$zlog", L"$zmode"
																				, L"$zn", L"$zname", L"$znext", L"$znspace", L"$zo", L"$zorder", L"$zp", L"$zparent", L"$zpi", L"$zpos", L"$zposition", L"$zpower"
																				, L"$zprevious", L"$zr", L"$zreference", L"$zs", L"$zse", L"$zsearch", L"$zsec", L"$zseek", L"$zsin", L"$zsort", L"$zsqr"
																				, L"$zstorage", L"$zstrip", L"$zt", L"$ztan", L"$zth", L"$ztime", L"$ztimeh", L"$ztimestamp", L"$ztrap", L"$zts", L"$zu", L"$zutil"
																				, L"$zv", L"$zversion", L"$zw", L"$zwa", L"$zwascii", L"$zwbp", L"$zwbpack", L"$zwbunp", L"$zwbunpack", L"$zwc", L"$zwchar", L"$zwidth"
																				, L"$zwp", L"$zwpack", L"$zwunp", L"$zwunpack", L"$zz", L"$zzdec", L"$zzenkaku", L"$zzhex", L"&html", L"&sql", L"^$g", L"^$global"
																				, L"^$j", L"^$job", L"^$l", L"^$lock", L"^$r", L"^$routine", L"b", L"break", L"c", L"close", L"d", L"do", L"e", L"else", L"f"
																				, L"for", L"g", L"goto", L"h", L"halt", L"hang", L"i", L"if", L"j", L"job", L"k", L"kill", L"l", L"lock", L"m", L"merge", L"n", L"new", L"o"
																				, L"open", L"p", L"print", L"q", L"quit", L"r", L"read", L"s", L"set", L"tc", L"tcommint", L"tro", L"trollback", L"ts", L"tstart", L"u"
																				, L"use", L"vi", L"view", L"w", L"write", L"x", L"xecute", L"zb", L"zbreak", L"zi", L"zinsert", L"zk", L"zkill", L"zl", L"zload", L"zn"
																				, L"znspace", L"zp", L"zprint", L"zq", L"zquit", L"zr", L"zremove", L"zs", L"zsave", L"zsync", L"ztrap", L"zw", L"zwrite", L"zzdump"};
const int KeyIndices[1997/*# range 0..1996*/] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 139, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 186, -1, -1, -1, -1, -1, -1, -1, 153, -1, 232, -1, 212, 74
																				, -1, -1, -1, -1, -1, 178, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 265, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 77, -1, -1, -1, -1
																				, -1, -1, 272, 259, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 234, -1, -1, -1, 187, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 198, 246, -1, -1, -1, 24, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 76, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 236, -1, 206, 210, -1, -1, 181, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 221, -1, -1, 27, -1, -1, -1, 9, -1, -1, -1, -1, -1, 23, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 116, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 58, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1, -1, 137, -1, -1
																				, -1, -1, -1, -1, 183, -1, -1, -1, 18, 49, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 244, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 83, -1, -1, -1
																				, -1, 102, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 242, 108, 31, -1, -1, 93, -1, -1, -1, -1, -1, -1, 274, -1, -1, -1, -1, -1, -1, 128, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, 191, -1, -1, 5, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, -1, -1, 88, -1, -1, -1, -1, 66, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 249, -1, 33, -1, -1, 185, 59, -1, -1, -1, -1, -1, -1, 124, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 248, -1, -1, -1, 117, -1, -1, 84, -1, -1, -1, -1, -1, 100, -1, 133, -1, -1, 245, -1, -1, -1
																				, 257, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 255, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 250
																				, -1, -1, -1, 152, -1, -1, -1, -1, 239, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 47, -1, -1, 22, 114, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 247, -1
																				, 86, 68, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 252, -1, 80, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6, -1, -1, -1, -1, 113, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 195, -1, -1, -1, -1, -1, -1, 44, -1, -1, -1, -1, 65, -1, 175, -1, -1, 99, -1, -1
																				, -1, -1, -1, -1, -1, -1, 118, -1, -1, -1, -1, -1, 95, 121, -1, 92, 188, -1, -1, -1, -1, -1, -1, -1, -1, 53, -1, -1, -1, -1, -1, -1, -1, -1, 156, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 164
																				, 240, -1, -1, -1, -1, -1, 202, -1, 130, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 179, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 157, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 168, -1, -1
																				, 56, -1, -1, -1, -1, 1, -1, -1, -1, -1, 223, -1, -1, -1, -1, -1, -1, -1, -1, -1, 225, -1, -1, -1, -1, -1, 197, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 125, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, 119, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 64, -1, -1, -1, -1, -1, -1, 63, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 55, -1, -1, -1, -1
																				, -1, 145, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 106, -1, -1, -1, -1, -1, -1, -1, 122, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 67, -1, -1, -1, -1, 85
																				, -1, -1, -1, 261, -1, 182, -1, -1, -1, -1, -1, -1, -1, 41, -1, -1, -1, 158, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26, 154, -1, -1, -1, -1, -1, 201, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, 91, 69, -1, -1, -1, -1, -1, -1, -1, 72, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 34, -1, -1, -1, -1, 123, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 251, -1, -1
																				, -1, 176, -1, -1, -1, -1, -1, 270, -1, -1, -1, -1, -1, -1, -1, 203, -1, -1, -1, -1, -1, -1, 165, -1, -1, -1, 184, -1, -1, -1, -1, -1, -1, -1, 190, 103, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 120
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, 144, -1, -1, 254, -1, -1, -1, -1, -1, -1, -1, 126, -1, -1, -1, -1, -1, -1, 205, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, 192, -1, -1, -1, 104, -1, -1, -1, -1, -1, -1, -1, -1, -1, 196, -1, -1, -1, -1, 35, -1, -1, -1, -1, 115, -1, -1, -1, -1, -1, -1, 134, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, 253, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 207, -1, -1, 166, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 231, -1, -1, -1, -1, -1, 143, -1, 238, -1, -1, -1
																				, -1, -1, 43, -1, -1, -1, -1, -1, 174, -1, -1, -1, -1, -1, 109, 199, -1, -1, -1, -1, -1, -1, 256, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 209, -1, -1, -1, 136, -1, -1, -1, -1, -1, -1
																				, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 81, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 37, -1, -1, -1, -1, -1, -1, -1, -1, 267, -1, 96, -1, -1, -1, -1, -1, -1, -1, 148, -1, 258, -1, -1, -1
																				, -1, -1, 150, -1, -1, -1, -1, 90, -1, -1, -1, 211, -1, -1, -1, 140, -1, -1, -1, -1, -1, -1, -1, -1, 208, -1, -1, -1, -1, -1, -1, -1, -1, 13, 82, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 38, 45, -1
																				, -1, -1, -1, -1, 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 213, -1, -1, -1, 142, -1, -1, -1, 189, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 273, 147, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 89, -1, 172, -1, 177, -1, -1, 260, 112, -1, -1, -1, -1, -1, 40
																				, -1, -1, -1, -1, -1, 36, -1, 216, 61, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 241, -1, -1, -1, -1, -1, -1, -1, -1, 243, -1, -1, -1, -1, -1, -1, 110, 39, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 215, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 194, -1, -1, 218, 54, -1, -1, 149, -1, -1, -1, -1, -1, -1, -1, 167, -1, -1, 129, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 132, -1, -1, -1, -1, -1, -1, -1, -1, 12, -1, 135, -1, -1, 30, -1, -1, -1, 70, 262, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, 220, -1, -1, -1, 151, -1, 170, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 101, -1, 14, -1, -1, 42, -1, -1, -1, -1, -1, 263, -1, -1, 0, -1, -1, 94, -1, -1, -1, -1, -1, -1, 105, -1, -1
																				, -1, -1, -1, -1, 75, -1, -1, -1, -1, -1, -1, 264, -1, -1, -1, -1, 98, -1, -1, -1, -1, -1, -1, -1, -1, -1, 222, -1, -1, -1, 161, -1, -1, 200, -1, -1, -1, -1, -1, -1, 71, 131, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 237, -1, 46, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 204, -1, -1, -1, -1, -1, -1, -1, 266, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, 224, -1, -1, 217, 169, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 229, 235, -1, 233, -1, -1, -1, -1, -1, -1, 2, -1, -1, -1, -1, -1, -1, 141, -1, -1, -1, -1, -1, 62, -1, -1
																				, 155, 97, -1, -1, -1, -1, -1, -1, 268, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 159, 226, -1, 73, -1, 171, -1, -1, 271, -1, 107, -1, 127, -1, -1, -1, -1, -1, -1, -1, -1, 227, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4, -1, 87, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, -1, -1, -1, 146, -1, 138, -1, -1, -1, 228, -1
																				, -1, -1, 173, -1, -1, -1, 50, -1, -1, 78, -1, -1, -1, 60, -1, 219, -1, -1, 269, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52, -1, 7, -1, -1, -1, 57, 79, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, 111, -1, -1, -1, -1, -1, -1, -1, 160, -1, -1, -1, 214, -1, 230, -1, -1, -1, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 162, -1, -1
																				, 163, -1, -1, 15, -1, -1, -1};

/*$Q-*/

unsigned int __fastcall TSynCacheSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 355 + int((*Str)) * 71);
		++Str;
	}
	result = (unsigned int) (result % 1997);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynCacheSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkClass;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 1996 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynCacheSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 1996 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] ==  - 1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[379] = Func38html;
	fIdentFuncTable[1125] = Func38sql;
	for(stop = 1996 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynCacheSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkClass;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCacheSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkClass;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCacheSyn::Func38html(int Index)
{
	TtkTokenKind result = tkClass;
	if(IsCurrentToken(Keywords[Index]))
	{
		result = tkEmbedSQL;
		FRange = rsHTML;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCacheSyn::Func38sql(int Index)
{
	TtkTokenKind result = tkClass;
	if(IsCurrentToken(Keywords[Index]))
	{
		result = tkEmbedSQL;
		FRange = rsSQL;
	}
	else
	result = tkIdentifier;
	return result;
}

__fastcall TSynCacheSyn::TSynCacheSyn(TComponent* AOwner)
 : inherited(AOwner),
			fBrace(0),
			fFirstBrace(false),
			FRange(rsUnKnown),
			FTokenID(tkClass),
			fClassAttri(nullptr),
			fCommentAttri(nullptr),
			fFunctionAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fDirectiveAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fIndirectAttri(nullptr),
			fLabelAttri(nullptr),
			fMacroAttri(nullptr),
			fUserFunctionAttri(nullptr),
			fEmbedSQLAttri(nullptr),
			fEmbedTextAttri(nullptr),
			FCanKey(false)
{
	FCaseSensitive = false;
	fClassAttri = new TSynHighlighterAttributes(SYNS_AttrClass, SYNS_FriendlyAttrClass);
	addAttribute(fClassAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = SynHighlighterCache__0;
	addAttribute(fCommentAttri);
	fFunctionAttri = new TSynHighlighterAttributes(SYNS_AttrFunction, SYNS_FriendlyAttrFunction);
	addAttribute(fFunctionAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = SynHighlighterCache__1;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fDirectiveAttri = new TSynHighlighterAttributes(SYNS_AttrDir, SYNS_FriendlyAttrDir);
	addAttribute(fDirectiveAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fIndirectAttri = new TSynHighlighterAttributes(SYNS_AttrIndirect, SYNS_FriendlyAttrIndirect);
	addAttribute(fIndirectAttri);
	fLabelAttri = new TSynHighlighterAttributes(SYNS_AttrLabel, SYNS_FriendlyAttrLabel);
	addAttribute(fLabelAttri);
	fMacroAttri = new TSynHighlighterAttributes(SYNS_AttrMacro, SYNS_FriendlyAttrMacro);
	addAttribute(fMacroAttri);
	fUserFunctionAttri = new TSynHighlighterAttributes(SYNS_AttrUserFunction, SYNS_FriendlyAttrUserFunction);
	addAttribute(fUserFunctionAttri);
	fEmbedSQLAttri = new TSynHighlighterAttributes(SYNS_AttrEmbedSQL, SYNS_FriendlyAttrEmbedSQL);
	addAttribute(fEmbedSQLAttri);
	fEmbedTextAttri = new TSynHighlighterAttributes(SYNS_AttrEmbedText, SYNS_FriendlyAttrEmbedText);
	addAttribute(fEmbedTextAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterCache;
	FRange = rsUnKnown;
}

void __fastcall TSynCacheSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
	FRange = rsUnKnown;
}

void __fastcall TSynCacheSyn::CommentProc()
{
	FTokenID = tkComment;
	if(fLine[Run + 1] == L';')
		FTokenID = tkEmbedText;
	while(fLine[Run] != L'\x00')
	{
		switch(fLine[Run])
		{
			case L'\x0a':
			case L'\x0d':
			goto label0;
			default:
			  ;
			break;
		}
		++Run;
	}
	label0:;
}

//------------------------------------------------------------------------------
//    higlight keywords and identifiers
//------------------------------------------------------------------------------

void __fastcall TSynCacheSyn::IdentProc()
{
	WideChar fir = L'\0';
	if(fTokenPos == 0)
		FTokenID = tkLabel;
	else
	{
		fir = fLine[Run];
		if(fir == L'^')
			FCanKey = true;
		FRange = rsUnKnown;
		if(FCanKey)
			FTokenID = IdentKind(fLine + Run);
		else
		{
			FTokenID = tkIdentifier;
			while(IsIdentChar(fLine[Run]))
				++Run;
			return;
		}
		FRange = rsCommand;
		Run += fStringLen;
		if(!(IsLineEnd(Run) || CharInSet(fLine[Run], SynHighlighterCache__2)) && (fir != L'^'))
		{
			FTokenID = tkIdentifier;
		}
	}
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynCacheSyn::LFProc()
{
	FTokenID = tkSpace;
	FCanKey = true;
	++Run;
}

void __fastcall TSynCacheSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynCacheSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'.':
			case L'e':
			case L'E':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	if((fTokenPos == 0) && CharInSet(fLine[Run], SynHighlighterCache__3))
	{
		FTokenID = tkLabel;
		while(IsIdentChar(fLine[Run]))
			++Run;
		FCanKey = false;
		return;
	}
	++Run;
	FTokenID = tkNumber;
	while(IsNumberChar())
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Run + 1] == L'.')
				goto label1;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label1:;
	FRange = rsUnKnown;
}

void __fastcall TSynCacheSyn::SpaceProc()
{
	int X = 0;
	X = Run;
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
	FCanKey = true;
	if(FRange == rsCommand)
		FCanKey = (Run - X > 1);
}

void __fastcall TSynCacheSyn::StringProc()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x22') && (fLine[Run + 2] == L'\x22'))
		Run += 2;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label2;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x22'));
	label2:;
	if(fLine[Run] != L'\x00')
		++Run;
	FRange = rsUnKnown;
}

void __fastcall TSynCacheSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynCacheSyn::Next()
{
	fTokenPos = Run;
	if(fLine[Run] == L'\x00')
		NullProc();
	else
		switch(FRange)
		{
			case rsSQL:
			case rsHTML:
			EmbeddedProc();
			break;
			default:
			switch(fLine[Run])
			{
				case L'\x0d':
				CRProc();
				break;
				case L';':
				CommentProc();
				break;
				case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
				 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
				 case 85: case 86: case 87: case 88: case 89: case 90:
				case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
				 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
				 case 117: case 118: case 119: case 120: case 121: case 122:
				case L'%':
				case L'^':
				IdentProc();
				break;
				case L'$':
				FuncProc();
				break;
				case L'@':
				IndirectProc();
				break;
				case L'\x0a':
				LFProc();
				break;
				case L'\x00':
				NullProc();
				break;
				case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
				NumberProc();
				break;
				case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
				case L'\x0b':
				case L'\x0c':
				case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
				 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
				SpaceProc();
				break;
				case L'\x22':
				StringProc();
				break;
				case L'(':
				case L')':
				case L'+':
				case L'-':
				case L'[':
				case L']':
				case L'.':
				case L'<':
				case L'>':
				case L'\'':
				case L'=':
				case L',':
				case L':':
				case L'/':
				case L'\\':
				case L'?':
				case L'!':
				case L'_':
				case L'*':
				SymbolProc();
				break;
				case L'#':
				DirectiveProc();
				break;
				case L'&':
				EmbeddedProc();
				break;
				default:
				UnknownProc();
				break;
			}
			break;
		}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynCacheSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_COMMENT:
		result = fCommentAttri;
		break;
		case SYN_ATTR_KEYWORD:
		result = fKeyAttri;
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

bool __fastcall TSynCacheSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynCacheSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynCacheSyn::GetTokenID()
{
	TtkTokenKind result = tkClass;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynCacheSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkClass:
		result = fClassAttri;
		break;
		case tkComment:
		result = fCommentAttri;
		break;
		case tkFunction:
		result = fFunctionAttri;
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
		case tkDirective:
		result = fDirectiveAttri;
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
		case tkIndirect:
		result = fIndirectAttri;
		break;
		case tkUnknown:
		result = fIdentifierAttri;
		break;
		case tkLabel:
		result = fLabelAttri;
		break;
		case tkMacro:
		result = fMacroAttri;
		break;
		case tkUserFunction:
		result = fUserFunctionAttri;
		break;
		case tkEmbedSQL:
		result = fEmbedSQLAttri;
		break;
		case tkEmbedText:
		result = fEmbedTextAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynCacheSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynCacheSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynCacheSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(int)Value;
}

bool __fastcall TSynCacheSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterCache;
	return result;
}

bool __fastcall TSynCacheSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case L'%':
		case L'^':
		case L'$':
		case L'&':
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

/*#static*/
String __fastcall TSynCacheSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangCache;
	return result;
}

//------------------------------------------------------------------------------
//   highlight indirection syntax:   @ident
//------------------------------------------------------------------------------

void __fastcall TSynCacheSyn::IndirectProc()
{
	FTokenID = tkIndirect;
	++Run;
	while(IsIdentChar(fLine[Run]))
		++Run;
	FRange = rsUnKnown;
}

//------------------------------------------------------------------------------
//  highlight symbols
//------------------------------------------------------------------------------

void __fastcall TSynCacheSyn::SymbolProc()
{
	FTokenID = tkSymbol;
	++Run;
	FRange = rsUnKnown;
}

//------------------------------------------------------------------------------
//  highlight user defined functions and macros
//              function:   $$ident
//              macro   :   $$$ident
//------------------------------------------------------------------------------

void __fastcall TSynCacheSyn::FuncProc()
{
	switch(fLine[Run])
	{
		case L'$':
		switch(fLine[Run + 1])
		{
			case L'$':
			switch(fLine[Run + 2])
			{
				case L'$':
				FTokenID = tkMacro;
				break;
				default:
				FTokenID = tkUserFunction;
				break;
			}
			break;
			default:
			{
				FTokenID = IdentKind((fLine + Run));
				Run += fStringLen;
				if(FTokenID == tkKey)
					FTokenID = tkFunction;
			}
			break;
		}
		break;
		default:
		FTokenID = tkIdentifier;
		break;
	}
	while(IsIdentChar(fLine[Run]))
		++Run;
	FRange = rsUnKnown;
}

//------------------------------------------------------------------------------
//    highlight preprocesor directives and class syntax
//              preprocesor:  #identifier
//              class      :  ##class
//------------------------------------------------------------------------------

void __fastcall TSynCacheSyn::DirectiveProc()
{
	int i = 0;
	if(fLine[Run + 1] == L'#')
		FTokenID = tkClass;
	else
	{
		int stop = 0;
		for(stop = 0, i = fTokenPos; i >= stop; i--)
		{
			if(!CharInSet(fLine[i], SynHighlighterCache__4))
			{
				FTokenID = tkSymbol;
				++Run;
				return;
			}
		}
		FTokenID = tkDirective;
	}
	++Run;
	while(IsIdentChar(fLine[Run]) || (fLine[Run] == L'#'))
		++Run;
	FRange = rsUnKnown;
}

//------------------------------------------------------------------------------
//  highlight embeded SQL and HTML
//                SQL  :    &sql( .... )
//                HTML :    &html<   ..... >
//------------------------------------------------------------------------------

void __fastcall TSynCacheSyn::EmbeddedProc()
{
	switch(FRange)
	{
		case rsUnKnown:
		case rsCommand:
		{
			FTokenID = IdentKind((fLine + Run));
			if(FTokenID != tkEmbedSQL)
			{
				FTokenID = tkSymbol;
				++Run;
			}
			else
			{
				fBrace = 1;
				fFirstBrace = true;
				Run += fStringLen;
			}
		}
		break;
		case rsSQL:
		{
			FTokenID = tkEmbedSQL;
			while((fLine[Run] != L'\x00') && (fBrace != 0))
			{
				switch(fLine[Run])
				{
					case L'(':
					if(!fFirstBrace)
						++fBrace;
					else
						fFirstBrace = false;
					break;
					case L')':
					--fBrace;
					break;
					default:
					  ;
					break;
				}
				++Run;
			}
			if(fBrace == 0)
				FRange = rsUnKnown;
		}
		break;
		case rsHTML:
		{
			FTokenID = tkEmbedSQL;
			while((fLine[Run] != L'\x00') && (fBrace != 0))
			{
				switch(fLine[Run])
				{
					case L'<':
					if(!fFirstBrace)
						++fBrace;
					else
						fFirstBrace = false;
					break;
					case L'>':
					--fBrace;
					break;
					default:
					  ;
					break;
				}
				++Run;
			}
			if(fBrace == 0)
				FRange = rsUnKnown;
		}
		break;
		default:
		  ;
		break;
	}
}

/*#static*/
String __fastcall TSynCacheSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangCache;
	return result;
}
static bool SynHighlighterCache_Initialized = false;

void SynHighlighterCache_initialization()
{
	if(SynHighlighterCache_Initialized)
		return;
	
	SynHighlighterCache_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynCacheSyn));
}
class SynHighlighterCache_unit
{
public:
	SynHighlighterCache_unit()
	{
		SynHighlighterCache_initialization();
	}
};

SynHighlighterCache_unit _SynHighlighterCache_unit;

}  // namespace SynHighlighterCache

