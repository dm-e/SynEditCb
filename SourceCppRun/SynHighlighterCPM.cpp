
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterCPM.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Synhighlightercpm
{
#define SynHighlighterCPM__0 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterCPM__1 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterCPM__2 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterCPM__3 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterCPM__4 (TFontStyles() << TFontStyle::fsBold)


const String Keywords[146/*# range 0..145*/] = {L"allentities", L"allproducts", L"allproperties", L"allqualityproperties", L"allsuppliers", L"assign"
																				, L"begin", L"block", L"case", L"category", L"centerstr", L"charreplacestr", L"charrlenstr", L"charrllenstr", L"chr"
																				, L"client", L"constants", L"continue", L"copyfile", L"country", L"decr", L"definition", L"distinct_execute", L"divide", L"else"
																				, L"emptysheet", L"end", L"entitycode", L"equalstring", L"equalvalue", L"execute", L"fileappend", L"fileassign", L"fileclose"
																				, L"filecopy", L"filedate", L"filedelete", L"fileend", L"fileexists", L"filereadln", L"filereset", L"filerewrite", L"filesize"
																				, L"filesort", L"filetime", L"filewriteln", L"filterstr", L"firstinstance", L"flow", L"fold", L"foreign", L"globalconstants", L"globals"
																				, L"globalvariables", L"groupdown", L"groupfooter", L"groupheader", L"groupkey", L"groupup", L"if", L"include", L"incr"
																				, L"language", L"lastinstance", L"leftstr", L"length", L"llenstr", L"local", L"locasestr", L"loop", L"lowerlevelstoo", L"ltrunc"
																				, L"matching", L"member", L"merge", L"messagedlg", L"metaflow", L"midstr", L"multiply", L"nextinstance", L"nextrepeatinstance", L"of"
																				, L"options", L"organisation", L"output", L"param", L"parent", L"parseinc", L"pdriver", L"previnstance", L"prevrepeatinstance", L"printer"
																				, L"printfile", L"propertygroup", L"rastr", L"raval", L"readinstance", L"readrepeatinstance", L"repeat", L"repeatcount", L"reportlevel"
																				, L"rightstr", L"rlenstr", L"root", L"round", L"showmessage", L"skipemtpty", L"sortdown", L"sortkey", L"sortup", L"sql_add"
																				, L"sql_asfloat", L"sql_asstring", L"sql_create", L"sql_dump", L"sql_eof", L"sql_execute", L"sql_free", L"sql_mladd", L"sql_mlmultiadd"
																				, L"sql_next", L"sql_setvar", L"sqr", L"stripstr", L"stroptions", L"strpos", L"subtract", L"sum", L"supplier", L"suppliesofmembers"
																				, L"then", L"trunc", L"upcasestr", L"usedby", L"v_date", L"v_false", L"v_nonereal", L"v_par_language", L"v_par_language_count"
																				, L"v_par_language_fields", L"v_time", L"v_true", L"variables", L"varoptions", L"while", L"zerorlenstr"};
const int KeyIndices[797/*# range 0..796*/] = {-1, -1, -1, -1, -1, -1, -1, -1, 45, -1, 26, -1, -1, -1, -1, -1, 74, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, 85, -1, -1, -1, 58, -1, 51, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, 4, 43, 30, -1, 54, 127, -1, -1, -1, 136, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 56, 38, -1, 32, -1, -1, -1, -1, -1, -1, -1, 133, 65, -1, 96, -1, -1, -1, 144, -1, -1, -1, -1, -1, -1
																				, -1, -1, 89, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 23, -1, -1, -1, 35, -1, -1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 75, 41, -1, -1
																				, 36, -1, -1, -1, -1, -1, -1, 143, -1, -1, 105, -1, -1, -1, -1, -1, 86, 142, 99, -1, 131, -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, 83, -1, -1, 67, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, 53, 27, -1, -1, -1, -1, -1, -1, 102, -1, -1, -1, -1, -1, -1, -1, 2, -1, -1, 28, -1, 24, 141, -1, -1, 101, -1, -1, 134, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, 111, -1, 100, -1, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 44, 135, -1, 117, -1, 77, -1, 37, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 69, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, 42, 7, -1, 109, -1, -1, -1, -1, -1, -1, -1, 107, -1, -1, -1, 113, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 13, -1, 73, 34, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, 132, -1, -1, -1, 123, -1, -1, -1, -1, -1, 63, -1, 48, -1, -1, -1, -1, -1, -1, -1, -1, -1, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 66, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, 84, -1, -1, -1, -1, 95, -1, -1, -1, -1, -1, -1, -1, 71, 138, -1, -1, -1, -1, -1, -1, -1, -1, -1, 93, 110, -1, -1, 80, -1, -1, 137, -1, -1, -1, 91, -1, 60, -1, -1, 62, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, 82, -1, -1, -1, -1, -1, 29, -1, -1, 122, -1, -1, -1, -1, 39, -1, 61, -1, -1, -1, -1, -1, 6, -1, -1, -1, -1, -1, -1, 22, 130, -1, -1, -1, -1, -1, 81, -1, 57, -1, -1, 20, 121, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 94, -1, 31, -1, -1, -1, -1, -1, 47, -1, -1, 108, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 33, -1, -1, -1, 64, -1, -1, 1, -1, 118, -1, -1, -1, -1, -1, -1
																				, 87, 49, -1, -1, -1, -1, -1, 79, -1, -1, -1, -1, -1, -1, 119, -1, -1, -1, -1, -1, -1, -1, -1, -1, 46, -1, -1, -1, -1, 125, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 106, -1, 97, -1, 68, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 40, -1, -1, 72, 70, 88, -1, 12, -1, -1, -1, -1, -1, -1, -1, 124, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 114
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 92, -1, -1, 59, -1, -1, -1, -1, -1, 11, -1, -1, 104, -1, -1, -1, -1, -1, -1, -1, 18, 78, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, 129, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 112, -1, -1, 98, -1, 116, 120, -1, 21, -1, 9, -1, -1, -1, 19, -1, -1
																				, -1, 50, -1, -1, -1, 126, -1, -1, 55, -1, 145, -1, -1, -1, -1, 52, 139, -1, 14, -1, -1, 115, -1, -1, -1, 90, -1, -1, -1, 128, -1, -1, -1, 103, -1, -1, -1, -1, -1, 3, -1, -1, 76, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, -1, -1, -1};

/*$Q-*/

unsigned int __fastcall TSynCPMSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 841 + int((*Str)) * 268);
		++Str;
	}
	result = (unsigned int) (result % 797);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynCPMSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 796 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynCPMSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 796 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] ==  - 1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[314] = FuncAllentities;
	fIdentFuncTable[528] = FuncAllproducts;
	fIdentFuncTable[212] = FuncAllproperties;
	fIdentFuncTable[774] = FuncAllqualityproperties;
	fIdentFuncTable[46] = FuncAllsuppliers;
	fIdentFuncTable[127] = FuncAssign;
	fIdentFuncTable[462] = FuncBegin;
	fIdentFuncTable[297] = FuncBlock;
	fIdentFuncTable[169] = FuncCase;
	fIdentFuncTable[728] = FuncCategory;
	fIdentFuncTable[106] = FuncCenterstr;
	fIdentFuncTable[663] = FuncCharreplacestr;
	fIdentFuncTable[607] = FuncCharrlenstr;
	fIdentFuncTable[326] = FuncCharrllenstr;
	fIdentFuncTable[753] = FuncChr;
	fIdentFuncTable[251] = FuncClient;
	fIdentFuncTable[793] = FuncConstants;
	fIdentFuncTable[694] = FuncContinue;
	fIdentFuncTable[674] = FuncCopyfile;
	fIdentFuncTable[732] = FuncCountry;
	fIdentFuncTable[481] = FuncDecr;
	fIdentFuncTable[726] = FuncDefinition;
	fIdentFuncTable[469] = FuncDistinct_execute;
	fIdentFuncTable[120] = FuncDivide;
	fIdentFuncTable[217] = FuncElse;
	fIdentFuncTable[26] = FuncEmptysheet;
	fIdentFuncTable[10] = FuncEnd;
	fIdentFuncTable[197] = FuncEntitycode;
	fIdentFuncTable[215] = FuncEqualstring;
	fIdentFuncTable[446] = FuncEqualvalue;
	fIdentFuncTable[48] = FuncExecute;
	fIdentFuncTable[499] = FuncFileappend;
	fIdentFuncTable[69] = FuncFileassign;
	fIdentFuncTable[521] = FuncFileclose;
	fIdentFuncTable[329] = FuncFilecopy;
	fIdentFuncTable[124] = FuncFiledate;
	fIdentFuncTable[142] = FuncFiledelete;
	fIdentFuncTable[273] = FuncFileend;
	fIdentFuncTable[67] = FuncFileexists;
	fIdentFuncTable[454] = FuncFilereadln;
	fIdentFuncTable[600] = FuncFilereset;
	fIdentFuncTable[139] = FuncFilerewrite;
	fIdentFuncTable[296] = FuncFilesize;
	fIdentFuncTable[47] = FuncFilesort;
	fIdentFuncTable[266] = FuncFiletime;
	fIdentFuncTable[8] = FuncFilewriteln;
	fIdentFuncTable[561] = FuncFilterstr;
	fIdentFuncTable[505] = FuncFirstinstance;
	fIdentFuncTable[356] = FuncFlow;
	fIdentFuncTable[538] = FuncFold;
	fIdentFuncTable[736] = FuncForeign;
	fIdentFuncTable[33] = FuncGlobalconstants;
	fIdentFuncTable[750] = FuncGlobals;
	fIdentFuncTable[196] = FuncGlobalvariables;
	fIdentFuncTable[50] = FuncGroupdown;
	fIdentFuncTable[743] = FuncGroupfooter;
	fIdentFuncTable[66] = FuncGroupheader;
	fIdentFuncTable[478] = FuncGroupkey;
	fIdentFuncTable[31] = FuncGroupup;
	fIdentFuncTable[657] = FuncIf;
	fIdentFuncTable[427] = FuncInclude;
	fIdentFuncTable[456] = FuncIncr;
	fIdentFuncTable[430] = FuncLanguage;
	fIdentFuncTable[354] = FuncLastinstance;
	fIdentFuncTable[525] = FuncLeftstr;
	fIdentFuncTable[78] = FuncLength;
	fIdentFuncTable[379] = FuncLlenstr;
	fIdentFuncTable[177] = FuncLocal;
	fIdentFuncTable[583] = FuncLocasestr;
	fIdentFuncTable[285] = FuncLoop;
	fIdentFuncTable[604] = FuncLowerlevelstoo;
	fIdentFuncTable[403] = FuncLtrunc;
	fIdentFuncTable[603] = FuncMatching;
	fIdentFuncTable[328] = FuncMember;
	fIdentFuncTable[16] = FuncMerge;
	fIdentFuncTable[138] = FuncMessagedlg;
	fIdentFuncTable[777] = FuncMetaflow;
	fIdentFuncTable[271] = FuncMidstr;
	fIdentFuncTable[675] = FuncMultiply;
	fIdentFuncTable[544] = FuncNextinstance;
	fIdentFuncTable[418] = FuncNextrepeatinstance;
	fIdentFuncTable[476] = FuncOf;
	fIdentFuncTable[440] = FuncOptions;
	fIdentFuncTable[174] = FuncOrganisation;
	fIdentFuncTable[390] = FuncOutput;
	fIdentFuncTable[27] = FuncParam;
	fIdentFuncTable[158] = FuncParent;
	fIdentFuncTable[537] = FuncParseinc;
	fIdentFuncTable[605] = FuncPdriver;
	fIdentFuncTable[93] = FuncPrevinstance;
	fIdentFuncTable[760] = FuncPrevrepeatinstance;
	fIdentFuncTable[425] = FuncPrinter;
	fIdentFuncTable[654] = FuncPrintfile;
	fIdentFuncTable[414] = FuncPropertygroup;
	fIdentFuncTable[497] = FuncRastr;
	fIdentFuncTable[395] = FuncRaval;
	fIdentFuncTable[80] = FuncReadinstance;
	fIdentFuncTable[581] = FuncReadrepeatinstance;
	fIdentFuncTable[721] = FuncRepeat;
	fIdentFuncTable[160] = FuncRepeatcount;
	fIdentFuncTable[249] = FuncReportlevel;
	fIdentFuncTable[221] = FuncRightstr;
	fIdentFuncTable[204] = FuncRlenstr;
	fIdentFuncTable[768] = FuncRoot;
	fIdentFuncTable[666] = FuncRound;
	fIdentFuncTable[152] = FuncShowmessage;
	fIdentFuncTable[579] = FuncSkipemtpty;
	fIdentFuncTable[307] = FuncSortdown;
	fIdentFuncTable[508] = FuncSortkey;
	fIdentFuncTable[299] = FuncSortup;
	fIdentFuncTable[415] = FuncSql_add;
	fIdentFuncTable[247] = FuncSql_asfloat;
	fIdentFuncTable[718] = FuncSql_asstring;
	fIdentFuncTable[311] = FuncSql_create;
	fIdentFuncTable[635] = FuncSql_dump;
	fIdentFuncTable[756] = FuncSql_eof;
	fIdentFuncTable[723] = FuncSql_execute;
	fIdentFuncTable[269] = FuncSql_free;
	fIdentFuncTable[530] = FuncSql_mladd;
	fIdentFuncTable[551] = FuncSql_mlmultiadd;
	fIdentFuncTable[724] = FuncSql_next;
	fIdentFuncTable[482] = FuncSql_setvar;
	fIdentFuncTable[449] = FuncSqr;
	fIdentFuncTable[348] = FuncStripstr;
	fIdentFuncTable[615] = FuncStroptions;
	fIdentFuncTable[566] = FuncStrpos;
	fIdentFuncTable[740] = FuncSubtract;
	fIdentFuncTable[51] = FuncSum;
	fIdentFuncTable[764] = FuncSupplier;
	fIdentFuncTable[696] = FuncSuppliesofmembers;
	fIdentFuncTable[470] = FuncThen;
	fIdentFuncTable[162] = FuncTrunc;
	fIdentFuncTable[344] = FuncUpcasestr;
	fIdentFuncTable[77] = FuncUsedby;
	fIdentFuncTable[224] = FuncV_date;
	fIdentFuncTable[267] = FuncV_false;
	fIdentFuncTable[55] = FuncV_nonereal;
	fIdentFuncTable[421] = FuncV_par_language;
	fIdentFuncTable[404] = FuncV_par_language_count;
	fIdentFuncTable[751] = FuncV_par_language_fields;
	fIdentFuncTable[366] = FuncV_time;
	fIdentFuncTable[218] = FuncV_true;
	fIdentFuncTable[159] = FuncVariables;
	fIdentFuncTable[149] = FuncVaroptions;
	fIdentFuncTable[84] = FuncWhile;
	fIdentFuncTable[745] = FuncZerorlenstr;
}

TtkTokenKind __fastcall TSynCPMSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncAllentities(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncAllproducts(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncAllproperties(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncAllqualityproperties(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncAllsuppliers(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncAssign(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncBegin(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncBlock(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncCase(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncCategory(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncCenterstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncCharreplacestr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncCharrlenstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncCharrllenstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncChr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncClient(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncConstants(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncContinue(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncCopyfile(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncCountry(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncDecr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncDefinition(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncDistinct_execute(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncDivide(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncElse(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncEmptysheet(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncEnd(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncEntitycode(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncEqualstring(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncEqualvalue(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncExecute(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFileappend(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFileassign(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFileclose(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFilecopy(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFiledate(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFiledelete(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFileend(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFileexists(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFilereadln(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFilereset(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFilerewrite(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFilesize(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFilesort(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFiletime(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFilewriteln(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFilterstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFirstinstance(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFlow(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncFold(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncForeign(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncGlobalconstants(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncGlobals(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncGlobalvariables(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncGroupdown(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncGroupfooter(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncGroupheader(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncGroupkey(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncGroupup(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncIf(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncInclude(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncIncr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncLanguage(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncLastinstance(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncLeftstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncLength(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncLlenstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncLocal(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncLocasestr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncLoop(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncLowerlevelstoo(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncLtrunc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncMatching(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncMember(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncMerge(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncMessagedlg(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncMetaflow(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncMidstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncMultiply(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncNextinstance(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncNextrepeatinstance(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncOf(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncOptions(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncOrganisation(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncOutput(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncParam(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncParent(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncParseinc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncPdriver(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncPrevinstance(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncPrevrepeatinstance(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncPrinter(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncPrintfile(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncPropertygroup(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncRastr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncRaval(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncReadinstance(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncReadrepeatinstance(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncRepeat(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncRepeatcount(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncReportlevel(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncRightstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncRlenstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncRoot(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncRound(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncShowmessage(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSkipemtpty(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSortdown(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSortkey(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSortup(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSql_add(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSQLKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSql_asfloat(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSQLKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSql_asstring(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSQLKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSql_create(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSQLKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSql_dump(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSQLKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSql_eof(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSQLKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSql_execute(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSQLKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSql_free(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSQLKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSql_mladd(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSQLKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSql_mlmultiadd(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSQLKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSql_next(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSQLKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSql_setvar(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSQLKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSqr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncStripstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncStroptions(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncStrpos(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSubtract(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSum(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSupplier(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncSuppliesofmembers(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncThen(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncTrunc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncUpcasestr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncUsedby(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncV_date(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSpecialVar;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncV_false(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSpecialVar;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncV_nonereal(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSpecialVar;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncV_par_language(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSpecialVar;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncV_par_language_count(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSpecialVar;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncV_par_language_fields(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSpecialVar;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncV_time(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSpecialVar;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncV_true(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSpecialVar;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncVariables(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncVaroptions(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncWhile(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCPMSyn::FuncZerorlenstr(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkSystem;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynCPMSyn::TSynCPMSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			fCommentLevel(0),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fSQLKeyAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fSpecialVarAttri(nullptr),
			fSystemAttri(nullptr),
			fVariableAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Foreground = clNavy;
	fCommentAttri->Style = SynHighlighterCPM__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Foreground = clGreen;
	fKeyAttri->Style = SynHighlighterCPM__1;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fSQLKeyAttri = new TSynHighlighterAttributes(SYNS_AttrSQLKey, SYNS_FriendlyAttrSQLKey);
	fSQLKeyAttri->Foreground = clTeal;
	fSQLKeyAttri->Style = SynHighlighterCPM__2;
	addAttribute(fSQLKeyAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fSpecialVarAttri = new TSynHighlighterAttributes(SYNS_AttrSpecialVariable, SYNS_FriendlyAttrSpecialVariable);
	fSpecialVarAttri->Style = SynHighlighterCPM__3;
	addAttribute(fSpecialVarAttri);
	fSystemAttri = new TSynHighlighterAttributes(SYNS_AttrSystem, SYNS_FriendlyAttrSystem);
	fSystemAttri->Foreground = (TColor) 0x000080FF;
	fSystemAttri->Style = SynHighlighterCPM__4;
	addAttribute(fSystemAttri);
	fVariableAttri = new TSynHighlighterAttributes(SYNS_AttrVariable, SYNS_FriendlyAttrVariable);
	fVariableAttri->Foreground = clMaroon;
	addAttribute(fVariableAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterCPM;
} /* Create */

void __fastcall TSynCPMSyn::BraceOpenProc()
{
	FRange = rsBraceComment;
	BraceCommentProc();
	FTokenID = tkComment;
} /* BraceOpenProc */

void __fastcall TSynCPMSyn::IdentProc()
{
	FTokenID = IdentKind(fLine + Run);
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
} /* IdentProc */

void __fastcall TSynCPMSyn::VariableProc()
{
	FTokenID = IdentKind((fLine + Run));
	if(FTokenID == tkIdentifier)
	{
		if(fLine[Run + 1] == L'_')
			FTokenID = tkVariable;
	}
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
} /* VariableProc */

void __fastcall TSynCPMSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
} /* NullProc */

void __fastcall TSynCPMSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
} /* SpaceProc */

void __fastcall TSynCPMSyn::StringProc()
{
	FTokenID = tkString;
	do
	{
		++Run;
	}
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\"')));
	if(fLine[Run] == L'\"')
	{
		++Run;
		if(fLine[Run] == L'\"')
			++Run;
	}
} /* StringProc */

void __fastcall TSynCPMSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
} /* UnknownProc */

void __fastcall TSynCPMSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsBraceComment:
		BraceCommentProc();
		break;
		default:
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
			case L'\"':
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
			switch(fLine[Run])
			{
				case L'V':
				case L'v':
				case L'S':
				case L's':
				VariableProc();
				break;
				default:
				IdentProc();
				break;
			}
			break;
			case L'{':
			BraceOpenProc();
			break;
			case L'}':
			case L'!':
			case L'%':
			case L'&':
			case 40: case 41: case 42: case 43: case 44: case 45: case 46: case 47:
			case 58: case 59: case 60: case 61: case 62: case 63: case 64:
			case 91: case 92: case 93: case 94:
			case L'`':
			case L'~':
			{
				switch(fLine[Run])
				{
					case L';':
					SemiColonProc();
					break;
					default:
					SymbolProc();
					break;
				}
			}
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
} /* Next */

TSynHighlighterAttributes* __fastcall TSynCPMSyn::GetDefaultAttribute(int Index)
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
} /* GetDefaultAttribute */

bool __fastcall TSynCPMSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
} /* GetEol */

TtkTokenKind __fastcall TSynCPMSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
} /* GetTokenID */

TSynHighlighterAttributes* __fastcall TSynCPMSyn::GetTokenAttribute()
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
		case tkSQLKey:
		result = fSQLKeyAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkSpecialVar:
		result = fSpecialVarAttri;
		break;
		case tkSystem:
		result = fSystemAttri;
		break;
		case tkVariable:
		result = fVariableAttri;
		break;
		case tkUnknown:
		result = fIdentifierAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
} /* GetTokenAttribute */

int __fastcall TSynCPMSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
} /* GetTokenKind */

/*#static*/
String __fastcall TSynCPMSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangCPM;
	return result;
}

void __fastcall TSynCPMSyn::BraceCommentProc()
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
			FTokenID = tkComment;
			do
			{
				if(fLine[Run] == L'{')
					++fCommentLevel;
				else
				{
					if(fLine[Run] == L'}')
					{
						--fCommentLevel;
						if(fCommentLevel < 1)
						{
							++Run;
							FRange = rsUnKnown;
							fCommentLevel = 0;
							break;
						}
					}
				}
				++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
	}
} /* BraceCommentProc */

void __fastcall TSynCPMSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
} /* CRProc */

void __fastcall TSynCPMSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
} /* LFProc */

String __fastcall TSynCPMSyn::GetSampleSource()
{
	String result;
	result = L"{ COAS Product Manager report (RDF) }\x0d\x0a"
	           L"PARAM\x0d\x0a"
	           L"  LANGUAGE;\x0d\x0a"
	           L"  CONTINUE;\x0d\x0a"
	           L"END; { Param }\x0d\x0a"
	           L"\x0d\x0a"
	           L"GLOBALS\x0d\x0a"
	           L"  LANGUAGE = LOCAL;\x0d\x0a"
	           L"END; { Globals }\x0d\x0a"
	           L"\x0d\x0a"
	           L"DEFINITION BLOCK \"MAIN\"\x0d\x0a"
	           L"VARIABLES\x0d\x0a"
	           L"  S_Query = \"\";\x0d\x0a"
	           L"  V_OraErr = -1;\x0d\x0a"
	           L"  V_Count;\x0d\x0a"
	           L"BEGIN\x0d\x0a"
	           L"  ASSIGN(S_Query, \"SELECT * FROM DUAL\");\x0d\x0a"
	           L"  SQL_CREATE(V_OraErr, S_Query);\x0d\x0a"
	           L"  ASSIGN(V_Count, V_NoneReal);\x0d\x0a"
	           L"END;";
	return result;
} /* GetSampleSource */

bool __fastcall TSynCPMSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterCPM;
	return result;
} /* IsFilterStored */

void __fastcall TSynCPMSyn::SemiColonProc()
{
	++Run;
	FTokenID = tkSymbol;
} /* SemiColonProc */

void __fastcall TSynCPMSyn::NumberProc()
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
	++Run;
	FTokenID = tkNumber;
	while(IsNumberChar())
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Run + 1] == L'.')
				goto label0;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label0:;
} /* NumberProc */

void __fastcall TSynCPMSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
} /* SymbolProc */

void __fastcall TSynCPMSyn::ResetRange()
{
	inherited::ResetRange();
	FRange = rsUnKnown;
	fCommentLevel = 0;
} /* ResetRange */

void __fastcall TSynCPMSyn::SetRange(void* Value)
{
	int AValue = 0;
	inherited::SetRange(Value);
	AValue = ((NativeInt) Value);
	fCommentLevel = (int)(AValue / 0x10000);
	FRange = ((TRangeState) (AValue % 0x10000));
} /* SetRange */

void* __fastcall TSynCPMSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) ((fCommentLevel * 0x10000) + ((int) FRange)));
	return result;
} /* GetRange */

/*#static*/
String __fastcall TSynCPMSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangCPM;
	return result;
}
static bool SynHighlighterCPM_Initialized = false;

void SynHighlighterCPM_initialization()
{
	if(SynHighlighterCPM_Initialized)
		return;
	
	SynHighlighterCPM_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynCPMSyn));
}
class SynHighlighterCPM_unit
{
public:
	SynHighlighterCPM_unit()
	{
		SynHighlighterCPM_initialization();
	}
};

SynHighlighterCPM_unit _SynHighlighterCPM_unit;

}  // namespace SynHighlighterCPM

