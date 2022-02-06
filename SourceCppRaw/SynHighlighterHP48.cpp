
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterHP48.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;

namespace Synhighlighterhp48
{
#define SynHighlighterHP48__0 (TSysCharSet() << L'\x0a' << L'\x0d')
#define SynHighlighterHP48__1 (TSysCharSet() <<  \
										1 << 2 << 3 << 4 << 5 << 6 <<  \
										7 << 8 << 9 << 10 << 11 << 12 <<  \
										13 << 14 << 15 << 16 << 17 << 18 <<  \
										19 << 20 << 21 << 22 << 23 << 24 <<  \
										25 << 26 << 27 << 28 << 29 << 30 <<  \
										31 << 32)
#define SynHighlighterHP48__2 (TSysCharSet() <<  \
										1 << 2 << 3 << 4 << 5 << 6 <<  \
										7 << 8 << 9 << 10 << 11 << 12 <<  \
										13 << 14 << 15 << 16 << 17 << 18 <<  \
										19 << 20 << 21 << 22 << 23 << 24 <<  \
										25 << 26 << 27 << 28 << 29 << 30 <<  \
										31 << 32)

__fastcall TSpeedListObject::TSpeedListObject() {}


const String DefaultAsmKeyWords = L"!RPL\x0d\x0a" L"ENDCODE\x0d\x0a" L"{\x0d\x0a" L"}\x0d\x0a"
	           L"GOTO\x0d\x0a" L"GOSUB\x0d\x0a" L"GOSBVL\x0d\x0a" L"GOVLNG\x0d\x0a" L"GOLONG\x0d\x0a" L"SKIP"
	           L"\x0d\x0a" L"SKIPYES"
	           L"\x0d\x0a" L"->\x0d\x0a" L"SKUB\x0d\x0a" L"SKUBL\x0d\x0a" L"SKC\x0d\x0a" L"SKNC\x0d\x0a" L"SKELSE"
	           L"\x0d\x0a" L"SKEC\x0d\x0a" L"SKENC\x0d\x0a" L"SKLSE\x0d\x0a"
	           L"GOTOL\x0d\x0a" L"GOSUBL\x0d\x0a"
	           L"RTN\x0d\x0a" L"RTNC\x0d\x0a" L"RTNNC\x0d\x0a" L"RTNSC\x0d\x0a" L"RTNCC\x0d\x0a" L"RTNSXM\x0d\x0a" L"RTI";
const String OtherAsmKeyWords[6/*# range 0..5*/] = {L"UP", L"EXIT", L"UPC", L"EXITC", L"UPNC", L"EXITNC"};
const String DefaultRplKeyWords = L"CODEM\x0d\x0a" L"ASSEMBLEM\x0d\x0a" L"CODE\x0d\x0a" L"ASSEMBLE\x0d\x0a" L"IT\x0d\x0a" L"ITE\x0d\x0a" L"case\x0d\x0a" L"::\x0d\x0a" L";\x0d\x0a" L"?SEMI\x0d\x0a" L"\'\x0d\x0a" L"#=case\x0d\x0a" L"{\x0d\x0a" L"}\x0d\x0a" L"NAMELESS\x0d\x0a" L"LOCAL\x0d\x0a" L"LOCALNAME\x0d\x0a" L"LABEL\x0d\x0a"
	           L"LOCALLABEL\x0d\x0a" L"xNAME\x0d\x0a" L"tNAME"
	           L"COLA\x0d\x0a" L"NULLNAME\x0d\x0a" L"xROMID\x0d\x0a" L"#0=ITE\x0d\x0a" L"#<ITE\x0d\x0a" L"#=ITE\x0d\x0a" L"#>ITE\x0d\x0a" L"2'RCOLARPITE\x0d\x0a" L"ANDITE\x0d\x0a" L"COLAITE\x0d\x0a" L"COLARPITE\x0d\x0a" L"DUP#0=ITE\x0d\x0a"
	           L"EQITE\x0d\x0a" L"ITE\x0d\x0a" L"RPITE\x0d\x0a" L"SysITE\x0d\x0a" L"UNxSYMRPITE\x0d\x0a" L"UserITE\x0d\x0a" L"snnSYMRPITE\x0d\x0a" L"snsSYMRPITE\x0d\x0a" L"ssnSYMRPITE\x0d\x0a" L"sssSYMRPITE\x0d\x0a" L"$_EXIT\x0d\x0a" L"DA1OK?NOTIT\x0d\x0a" L"DA2aOK?NOTIT\x0d\x0a"
	           L"DA2bOK?NOTIT\x0d\x0a" L"DA3OK?NOTIT\x0d\x0a" L"DO#EXIT\x0d\x0a" L"DO$EXIT\x0d\x0a" L"DO%EXIT\x0d\x0a" L"DOHXSEXIT\x0d\x0a" L"DUP#0=IT\x0d\x0a" L"EQIT\x0d\x0a" L"GCDHEULPEXIT\x0d\x0a" L"GSPLIT\x0d\x0a" L"NOT_IT\x0d\x0a" L"POINTEXIT\x0d\x0a" L"POLYARIT\x0d\x0a" L"RPIT\x0d\x0a"
	           L"parleftIT\x0d\x0a" L"parrightIT\x0d\x0a" L"\'\x0d\x0a" L"IT\x0d\x0a" L"ITE\x0d\x0a" L"SEMI\x0d\x0a" L"UNTIL\x0d\x0a" L"LOOP\x0d\x0a" L"?SEMI\x0d\x0a" L"NOT?SEMI\x0d\x0a" L"#0=case\x0d\x0a" L"#1=case\x0d\x0a" L"#<>case\x0d\x0a" L"#<case\x0d\x0a" L"#=case\x0d\x0a" L"#=casedrop\x0d\x0a"
	           L"#=casedrpfls\x0d\x0a" L"#>2case\x0d\x0a" L"#>33case\x0d\x0a" L"#>case\x0d\x0a" L"%-1=case\x0d\x0a" L"%0=case\x0d\x0a" L"%1=case\x0d\x0a" L"%2=case\x0d\x0a" L"AEQ1stcase\x0d\x0a" L"AEQopscase\x0d\x0a" L"ANDNOTcase\x0d\x0a" L"ANDcase\x0d\x0a" L"C%-1=case\x0d\x0a"
	           L"C%0=case\x0d\x0a" L"C%1=case\x0d\x0a" L"C%2=case\x0d\x0a" L"COLANOTcase\x0d\x0a" L"COLAcase\x0d\x0a" L"DUP#0=case\x0d\x0a" L"EQUALNOTcase\x0d\x0a" L"EQUALcase\x0d\x0a" L"EQUALcasedrop\x0d\x0a" L"EQUALcasedrp\x0d\x0a" L"EQcase\x0d\x0a" L"EQcaseDROP\x0d\x0a"
	           L"EQcasedrop\x0d\x0a" L"EnvNGcase\x0d\x0a" L"M-1stcasechs\x0d\x0a" L"MEQ*case\x0d\x0a" L"MEQ+case\x0d\x0a" L"MEQ-case\x0d\x0a" L"MEQ/case\x0d\x0a" L"MEQ1stcase\x0d\x0a" L"MEQCHScase\x0d\x0a" L"MEQFCNcase\x0d\x0a" L"MEQINVcase\x0d\x0a" L"MEQSQcase\x0d\x0a" L"MEQ^case\x0d\x0a"
	           L"MEQopscase\x0d\x0a" L"Mid1stcase\x0d\x0a" L"NOTBAKcase\x0d\x0a" L"NOTLIBcase\x0d\x0a" L"NOTLISTcase\x0d\x0a" L"NOTMATRIXcase\x0d\x0a" L"NOTROMPcase\x0d\x0a" L"NOTSECOcase\x0d\x0a" L"NOTTYPEcase\x0d\x0a" L"NOTcase\x0d\x0a" L"NOTcase2DROP\x0d\x0a" L"NOTcase2drop\x0d\x0a"
	           L"NOTcaseDROP\x0d\x0a" L"NOTcaseFALSE\x0d\x0a" L"NOTcaseTRUE\x0d\x0a" L"NOTcasedrop\x0d\x0a" L"NULLargcase\x0d\x0a" L"NcaseSIZEERR\x0d\x0a" L"NcaseTYPEERR\x0d\x0a" L"NoEdit?case\x0d\x0a" L"ORcase\x0d\x0a" L"OVER#=case\x0d\x0a" L"REALcase\x0d\x0a" L"REQcase\x0d\x0a"
	           L"REQcasedrop\x0d\x0a" L"Z-1=case\x0d\x0a" L"Z0=case\x0d\x0a" L"Z1=case\x0d\x0a" L"accNBAKcase\x0d\x0a" L"accNLIBcase\x0d\x0a" L"case\x0d\x0a" L"case2DROP\x0d\x0a" L"case2drop\x0d\x0a" L"case2drpfls\x0d\x0a" L"caseDEADKEY\x0d\x0a" L"caseDROP\x0d\x0a" L"caseDoBadKey\x0d\x0a"
	           L"caseDrpBadKy\x0d\x0a" L"caseERRJMP\x0d\x0a" L"caseFALSE\x0d\x0a" L"caseSIZEERR\x0d\x0a" L"caseTRUE\x0d\x0a" L"casedrop\x0d\x0a" L"casedrpfls\x0d\x0a" L"casedrptru\x0d\x0a" L"caseout\x0d\x0a" L"cxcasecheck\x0d\x0a" L"dARRYcase\x0d\x0a" L"dIDNTNcase\x0d\x0a" L"dLISTcase\x0d\x0a"
	           L"dMATRIXcase\x0d\x0a" L"dREALNcase\x0d\x0a" L"dREALcase\x0d\x0a" L"dZINTNcase\x0d\x0a" L"delimcase\x0d\x0a" L"estcase\x0d\x0a" L"idntcase\x0d\x0a" L"idntlamcase\x0d\x0a" L"j#-1=case\x0d\x0a" L"j#0=case\x0d\x0a" L"j#1=case\x0d\x0a" L"j%-1=case\x0d\x0a" L"j%0=case\x0d\x0a"
	           L"j%1=case\x0d\x0a" L"jEQcase\x0d\x0a" L"jZ-1=case\x0d\x0a" L"jZ0=case\x0d\x0a" L"jZ1=case\x0d\x0a" L"namelscase\x0d\x0a" L"need'case\x0d\x0a" L"negrealcase\x0d\x0a" L"ngsizecase\x0d\x0a" L"nonopcase\x0d\x0a" L"nonrmcase\x0d\x0a" L"num#-1=case\x0d\x0a" L"num#0=case\x0d\x0a"
	           L"num#1=case\x0d\x0a" L"num-1=case\x0d\x0a" L"num0=case\x0d\x0a" L"num0case\x0d\x0a" L"num1=case\x0d\x0a" L"num2=case\x0d\x0a" L"numb1stcase\x0d\x0a" L"rebuildcase\x0d\x0a" L"tok=casedrop\x0d\x0a" L"wildcase\x0d\x0a" L"zerdercase\x0d\x0a";
const String SasmNoField = L"LOOP\x0d\x0a" L"RTNSXM\x0d\x0a" L"RTN\x0d\x0a" L"RTNSC\x0d\x0a" L"RTNCC\x0d\x0a" L"SETDEC\x0d\x0a" L"SETHEX\x0d\x0a" L"RSTK=C\x0d\x0a" L"C=RSTK\x0d\x0a" L"CLRST\x0d\x0a" L"C=ST\x0d\x0a" L"ST=C\x0d\x0a" L"CSTEX\x0d\x0a"
	           L"RTI\x0d\x0a" L"R0=A\x0d\x0a" L"R1=A\x0d\x0a" L"R2=A\x0d\x0a" L"R3=A\x0d\x0a" L"R4=A\x0d\x0a" L"R0=C\x0d\x0a" L"R1=C\x0d\x0a" L"R2=C\x0d\x0a" L"R3=C\x0d\x0a" L"R4=C\x0d\x0a" L"A=R0\x0d\x0a" L"A=R1\x0d\x0a" L"A=R2\x0d\x0a" L"A=R3\x0d\x0a" L"A=R4\x0d\x0a"
	           L"C=R0\x0d\x0a" L"C=R1\x0d\x0a" L"C=R2\x0d\x0a" L"C=R3\x0d\x0a" L"C=R4\x0d\x0a" L"AR0EX\x0d\x0a" L"AR1EX\x0d\x0a" L"AR2EX\x0d\x0a" L"AR3EX\x0d\x0a" L"AR4EX\x0d\x0a" L"CR0EX\x0d\x0a" L"CR1EX\x0d\x0a" L"CR2EX\x0d\x0a" L"CR3EX\x0d\x0a" L"CR4EX\x0d\x0a"
	           L"D0=A\x0d\x0a" L"D0=C\x0d\x0a" L"D1=A\x0d\x0a" L"D1=C\x0d\x0a" L"AD0EX\x0d\x0a" L"AD1EX\x0d\x0a" L"CD0EX\x0d\x0a" L"CD1EX\x0d\x0a" L"D0=AS\x0d\x0a" L"D1=AS\x0d\x0a" L"D0=CS\x0d\x0a" L"D1=CD\x0d\x0a" L"CD1XS\x0d\x0a" L"CD0XS\x0d\x0a" L"AD1XS\x0d\x0a" L"AD0XS\x0d\x0a"
	           L"RTNC\x0d\x0a" L"RTNNC\x0d\x0a" L"OUT=CS\x0d\x0a" L"OUT=C\x0d\x0a" L"A=IN\x0d\x0a" L"C=IN\x0d\x0a" L"SHUTDN\x0d\x0a" L"INTON\x0d\x0a" L"C=ID\x0d\x0a" L"CONFIG\x0d\x0a" L"UNCNFG\x0d\x0a" L"RSI\x0d\x0a" L"PC=(A)\x0d\x0a" L"PC=(C)\x0d\x0a" L"INTOFF\x0d\x0a"
	           L"C+P+1\x0d\x0a" L"RESET\x0d\x0a" L"SREQ?\x0d\x0a" L"ASLC\x0d\x0a" L"BSLC\x0d\x0a" L"CSLC\x0d\x0a" L"DSLC\x0d\x0a" L"ASRC\x0d\x0a" L"BSRC\x0d\x0a" L"CSRC\x0d\x0a" L"DSRC\x0d\x0a" L"ASRB\x0d\x0a" L"BSRB\x0d\x0a" L"CSRB\x0d\x0a" L"DSRB\x0d\x0a" L"PC=A\x0d\x0a" L"PC=C\x0d\x0a"
	           L"A=PC\x0d\x0a" L"C=PC\x0d\x0a" L"APCEX\x0d\x0a" L"CPCEX\x0d\x0a" L"XM=0\x0d\x0a" L"SB=0\x0d\x0a" L"SR=0\x0d\x0a" L"MP=0\x0d\x0a" L"CLRHST\x0d\x0a" L"?XM=0\x0d\x0a" L"?SR=0\x0d\x0a" L"?MP=0\x0d\x0a" L"?SB=0\x0d\x0a" L"RTNYES\x0d\x0a" L"SKIPYES{\x0d\x0a" L"{\x0d\x0a" L"}\x0d\x0a" L"UP\x0d\x0a" L"EXIT\x0d\x0a" L"EXITNC\x0d\x0a" L"EXITC\x0d\x0a" L"UPC\x0d\x0a" L"UPNC"
	           L"}SKELSE{\x0d\x0a" L"SKC{\x0d\x0a" L"SKNC{\x0d\x0a" L"SKUB{\x0d\x0a" L"SKUBL{\x0d\x0a" L"SKIPC{\x0d\x0a" L"SKIPNC{\x0d\x0a" L"EXIT2\x0d\x0a" L"EXIT3\x0d\x0a" L"UP2\x0d\x0a" L"UP3\x0d\x0a" L"}SKLSE{\x0d\x0a" L"}SKEC{\x0d\x0a" L"}SKENC{\x0d\x0a";

int __fastcall StringCrc(String s)
{
	int result = 0;
	int i = 0;
	int stop = 0;
	result = 0;
	for(stop = (int) s.Length(), i = 1; i <= stop; i++)
	{
		result = (result >> 4) ^ (((result ^ int(s[i])) & 0xf) * 0x1081);
		result = (result >> 4) ^ (((result ^ (int(s[i]) >> 4)) & 0xf) * 0x1081);
	}
	return result;
}

/* TSpeedListObject */

__fastcall TSpeedListObject::TSpeedListObject(String Name)
 : FName(Name),
			FSpeedList(nullptr),
			FObject(nullptr)
{
	//# inherited::Create();
}

__fastcall TSpeedListObject::~TSpeedListObject()
{
	if(ASSIGNED(FSpeedList))
		FSpeedList->ObjectDeleted(this);
	//# inherited::Destroy();
}


void __fastcall TSpeedListObject::SetName(const String Value)
{
	FName = Value;
	if(FSpeedList != nullptr)
		FSpeedList->NameChange(this, Value);
}

/* TSpeedStringList */

int __fastcall TSpeedStringList::AddObj(TSpeedListObject* const Value)
{
	int result = 0;
	int crc = 0;
	int i = 0;
	int stop = 0;
	crc = StringCrc(Value->Name) % 127 /*# High(Datas) */ + 1;
	if(DatasUsed[crc] == LengthDatas[crc])
	{
		Datas[crc] = (PSpeedListObjects) ReallocMemory(Datas[crc], (LengthDatas[crc] * 2 + 1) * sizeof((*Datas[1])[0]));
		LengthDatas[crc] = LengthDatas[crc] * 2 + 1;
	}
	(*Datas[crc])[DatasUsed[crc]] = const_cast<TSpeedListObject*>(Value);
	result = SumOfUsed[crc] + DatasUsed[crc];
	++DatasUsed[crc];
	for(stop = 127 /*# High(SumOfUsed) */, i = crc + 1; i <= stop; i++)
	{
		++SumOfUsed[i];
	}
	Value->SpeedList = this;
	return result;
}

TSpeedListObject* __fastcall TSpeedStringList::Add(const String Value)
{
	TSpeedListObject* result = nullptr;
	result = new TSpeedListObject(Value);
	AddObj(result);
	return result;
}

void __fastcall TSpeedStringList::Changed()
{
	if(ASSIGNED(FOnChange))
		FOnChange(this);
}

void __fastcall TSpeedStringList::Clear()
{
	int i = 0;
	int j = 0;
	int stop = 0;
	for(stop = 127 /*# High(Datas) */, i = 0 /*# Low(Datas) */; i <= stop; i++)
	{
		int stop1 = 0;
		for(stop1 = DatasUsed[i] - 1, j = 0; j <= stop1; j++)
		{
			delete (*Datas[i])[j];
		}
		DatasUsed[i] = 0;
		Datas[i] = (PSpeedListObjects) ReallocMemory(Datas[i], 0);
		LengthDatas[i] = 0;
		SumOfUsed[i] = 0;
	}
	Changed();
}

__fastcall TSpeedStringList::TSpeedStringList()
{
	int i = 0;
	int stop = 0;
	//# inherited::Create();
	for(stop = 127 /*# High(Datas) */, i = 0 /*# Low(Datas) */; i <= stop; i++)
	{
		SumOfUsed[i] = 0;
		DatasUsed[i] = 0;
		LengthDatas[i] = 0;
		Datas[i] = nullptr;
	}
}

__fastcall TSpeedStringList::~TSpeedStringList()
{
	Clear();
	//# inherited::Destroy();
}


TSpeedListObject* __fastcall TSpeedStringList::Find(const String Name)
{
	TSpeedListObject* result = nullptr;
	int crc = 0;
	int i = 0;
	int stop = 0;
	crc = StringCrc(Name) % 127 /*# High(Datas) */ + 1;
	for(stop = DatasUsed[crc] - 1, i = 0; i <= stop; i++)
	{
		if((*Datas[crc])[i]->Name == Name)
		{
			result = (*Datas[crc])[i];
			return result;
		}
	}
	result = nullptr;
	return result;
}

String __fastcall TSpeedStringList::Get(int Index)
{
	String result;
	int i = 0;
	int stop = 0;
	for(stop = 127 /*# High(SumOfUsed) */, i = 0 /*# Low(SumOfUsed) */ + 1; i <= stop; i++)
	{
		if(Index > SumOfUsed[i])
		{
			result = (*Datas[i - 1])[Index - SumOfUsed[i - 1]]->Name;
			return result;
		}
	}
	result = L"";
	return result;
}

int __fastcall TSpeedStringList::GetCount()
{
	int result = 0;
	result = SumOfUsed[127 /*# High(Datas) */] + DatasUsed[127 /*# High(Datas) */];
	return result;
}

TObject* __fastcall TSpeedStringList::GetInObject(int Index)
{
	TObject* result = nullptr;
	int i = 0;
	int stop = 0;
	for(stop = 127 /*# High(SumOfUsed) */, i = 0 /*# Low(SumOfUsed) */ + 1; i <= stop; i++)
	{
		if(Index > SumOfUsed[i])
		{
			result = (*Datas[i - 1])[Index - SumOfUsed[i - 1]]->Pointer;
			return result;
		}
	}
	result = nullptr;
	return result;
}

TSpeedListObject* __fastcall TSpeedStringList::GetObject(int Index)
{
	TSpeedListObject* result = nullptr;
	int i = 0;
	int stop = 0;
	for(stop = 127 /*# High(SumOfUsed) */, i = 0 /*# Low(SumOfUsed) */ + 1; i <= stop; i++)
	{
		if(Index > SumOfUsed[i])
		{
			result = (*Datas[i - 1])[Index - SumOfUsed[i - 1]];
			return result;
		}
	}
	result = nullptr;
	return result;
}

TStrings* __fastcall TSpeedStringList::GetStringList()
{
	TStrings* result = nullptr;
	int i = 0;
	int j = 0;
	int stop = 0;
	result = new TStringList();
	for(stop = 127 /*# High(Datas) */, i = 0 /*# Low(Datas) */; i <= stop; i++)
	{
		int stop1 = 0;
		for(stop1 = DatasUsed[i] - 1, j = 0; j <= stop1; j++)
		{
			result->Add((*Datas[i])[j]->Name);
		}
	}
	return result;
}

String __fastcall TSpeedStringList::GetText()
{
	String result;
	/*# with StringList do */
	{
		auto with0 = StringList;
		result = with0->Text;
		delete with0;
	}
	return result;
}

void __fastcall TSpeedStringList::NameChange(TSpeedListObject* const Obj, const String NewName)
{
	int crc = 0;
	int i = 0;
	int j = 0;
	int stop = 0;
	crc = StringCrc(Obj->Name) % 127 /*# High(Datas) */ + 1;
	for(stop = DatasUsed[crc] - 1, i = 0; i <= stop; i++)
	{
		if((*Datas[crc])[i] == Obj)
		{
			int stop1 = 0;
			for(stop1 = DatasUsed[crc] - 1, j = i + 1; j <= stop1; j++)
			{
				Datas[i - 1] = Datas[i];
			}
			for(stop1 = 127 /*# High(Datas) */, j = crc + 1; j <= stop1; j++)
			{
				--SumOfUsed[j];
			}
			if(DatasUsed[crc] < (int)(LengthDatas[crc] / 2))
			{
				Datas[crc] = (PSpeedListObjects) ReallocMemory(Datas[crc], DatasUsed[crc] * sizeof((*Datas[crc])[0]));
				LengthDatas[crc] = DatasUsed[crc];
			}
			AddObj(Obj);
			return;
		}
	}
}

void __fastcall TSpeedStringList::ObjectDeleted(TSpeedListObject* const Obj)
{
	int crc = 0;
	int i = 0;
	int j = 0;
	int stop = 0;
	crc = StringCrc(Obj->Name) % 127 /*# High(Datas) */ + 1;
	for(stop = DatasUsed[crc] - 1, i = 0; i <= stop; i++)
	{
		if((*Datas[crc])[i] == Obj)
		{
			int stop1 = 0;
			for(stop1 = DatasUsed[crc] - 1, j = i + 1; j <= stop1; j++)
			{
				if(i > 0)
					Datas[i - 1] = Datas[i];
			}
			for(stop1 = 127 /*# High(Datas) */, j = crc + 1; j <= stop1; j++)
			{
				--SumOfUsed[j];
			}
			Obj->FSpeedList = nullptr;
			return;
		}
	}
}

void __fastcall TSpeedStringList::SetInObject(int Index, TObject* const Value)
{
	int i = 0;
	int stop = 0;
	for(stop = 127 /*# High(SumOfUsed) */, i = 0 /*# Low(SumOfUsed) */ + 1; i <= stop; i++)
	{
		if(Index > SumOfUsed[i])
		{
			(*Datas[i - 1])[Index - SumOfUsed[i - 1]]->Pointer = const_cast<TObject*>(Value);
			return;
		}
	}
}

void __fastcall TSpeedStringList::SetStringList(TStrings* const Value)
{
	int i = 0;
	int stop = 0;
	Clear();
	for(stop = Value->Count - 1, i = 0; i <= stop; i++)
	{
		AddObj(new TSpeedListObject(Value->Strings[i]));
	}
}

void __fastcall TSpeedStringList::SetText(const String Value)
{
	TStrings* s = nullptr;
	s = new TStringList();
	try
	{
		s->Text = Value;
		StringList = s;
	}
	__finally
	{
		delete s;
	}
}

/* TSynHP48Syn */

__fastcall TSynHP48Syn::TSynHP48Syn(TComponent* AOwner)
 : inherited(AOwner),
			fTockenKind(tkNull),
			FRange(rsRpl),
			FRplKeyWords(nullptr),
			FAsmKeyWords(nullptr),
			FSAsmNoField(nullptr),
			FBaseRange(rsRpl)
{
	int j = 0;
	int k = 0;
	int stop = 0;
	Attribs[tkNull] = new TSynHighlighterAttributes(SYNS_AttrNull, SYNS_FriendlyAttrNull);
	Attribs[tkAsmKey] = new TSynHighlighterAttributes(SYNS_AttrAsmKey, SYNS_FriendlyAttrAsmKey);
	Attribs[tkAsm] = new TSynHighlighterAttributes(SYNS_AttrAsm, SYNS_FriendlyAttrAsm);
	Attribs[tkAsmComment] = new TSynHighlighterAttributes(SYNS_AttrAsmComment, SYNS_FriendlyAttrAsmComment);
	Attribs[tksAsmKey] = new TSynHighlighterAttributes(SYNS_AttrSASMKey, SYNS_FriendlyAttrSASMKey);
	Attribs[tksAsm] = new TSynHighlighterAttributes(SYNS_AttrSASM, SYNS_FriendlyAttrSASM);
	Attribs[tksAsmComment] = new TSynHighlighterAttributes(SYNS_AttrSASMComment, SYNS_FriendlyAttrSASMComment);
	Attribs[tkRplKey] = new TSynHighlighterAttributes(SYNS_AttrRplKey, SYNS_FriendlyAttrRplKey);
	Attribs[tkRpl] = new TSynHighlighterAttributes(SYNS_AttrRpl, SYNS_FriendlyAttrRpl);
	Attribs[tkRplComment] = new TSynHighlighterAttributes(SYNS_AttrRplComment, SYNS_FriendlyAttrRplComment);
	SetHighLightChange();
	FAsmKeyWords = new TSpeedStringList();
	FAsmKeyWords->Text = DefaultAsmKeyWords;
	for(stop = 5 /*# High(OtherAsmKeyWords) */, j = 0 /*# Low(OtherAsmKeyWords) */; j <= stop; j++)
	{
		int stop1 = 0;
		FAsmKeyWords->AddObj(new TSpeedListObject(OtherAsmKeyWords[j]));
		for(stop1 = 8, k = 1; k <= stop1; k++)
		{
			FAsmKeyWords->AddObj(new TSpeedListObject(OtherAsmKeyWords[j] + IntToStr(k)));
		}
	}
	FRplKeyWords = new TSpeedStringList();
	FRplKeyWords->Text = DefaultRplKeyWords;
	FSAsmNoField = new TSpeedStringList();
	FSAsmNoField->Text = SasmNoField;
	BaseRange = rsRpl;
	FRange = rsRpl;
	fDefaultFilter = SYNS_FilterHP48;
} /* Create */

__fastcall TSynHP48Syn::~TSynHP48Syn()
{
	TtkTokenKind i = tkNull;
	int stop = 0;
	for(stop = (TtkTokenKind) 9 /*# High(TtkTokenKind) */, i = (TtkTokenKind) 0 /*# Low(TtkTokenKind) */; i <= stop; Inc(i))
	{
		delete Attribs[i];
	}
	delete FAsmKeyWords;
	delete FRplKeyWords;
	delete FSAsmNoField;
	//# inherited::Destroy();
}
 /* Destroy */

TtkTokenKind __fastcall TSynHP48Syn::AsmComProc(WideChar C)
{
	TtkTokenKind result = tkNull;
	result = tkAsmComment;
	if(Run > fLineStr.Length())
		result = NullProc();
	else
	{
		while(Run <= fLineStr.Length())
			if(((Run == 1) || (fLineStr[Run - 1] <= L' ')) && (fLineStr[Run] == L'*') && ((Run < fLineStr.Length()) && (fLineStr[Run + 1] == C)) && ((Run + 1 == fLineStr.Length()) || (fLineStr[Run + 2] <= L' ')))
			{
				Run += 2;
				FRange = rsAsm;
				break;
			}
			else
			++Run;
	}
	return result;
}

TtkTokenKind __fastcall TSynHP48Syn::RplComProc()
{
	TtkTokenKind result = tkNull;
	result = tkRplComment;
	if(Run > fLineStr.Length())
		result = NullProc();
	else
	{
		while(Run <= fLineStr.Length())
			if(fLineStr[Run] == L')')
			{
				++Run;
				FRange = rsRpl;
				break;
			}
			else
			++Run;
	}
	return result;
}

TtkTokenKind __fastcall TSynHP48Syn::SlashProc()
{
	TtkTokenKind result = tkNull;
	if(FRange == rsRpl)
		result = IdentProc();
	else
	{
		if(((Run == 1) || (fLineStr[Run - 1] <= L' ')) && (fLineStr[Run] == L'/') && (Run < fLineStr.Length()) && (fLineStr[Run + 1] == L'*') && ((Run + 1 == fLineStr.Length()) || (fLineStr[Run + 2] <= L' ')))
		{
			Run += 2;
			result = tkAsmComment;
			FRange = rsComAsm2;
		}
		else
		{
			if((Run < fLineStr.Length()) && (fLineStr[Run + 1] == L'/'))
			{
				Run += 2;
				result = tkAsmComment;
				while((Run <= fLineStr.Length()))
					if(CharInSet(fLineStr[Run], SynHighlighterHP48__0))
					{
						++Run;
						break;
					}
					else
					++Run;
			}
			else
			result = IdentProc();
		}
	}
	return result;
}

TtkTokenKind __fastcall TSynHP48Syn::ParOpenProc()
{
	TtkTokenKind result = tkNull;
	if(FRange == rsRpl)
	{
		if(((Run == 1) && ((fLineStr.Length() == 1) || (fLineStr[Run + 1] <= L' '))) || ((fLineStr[Run - 1] <= L' ') && ((fLineStr.Length() == Run) || (fLineStr[Run + 1] <= L' '))))
		{
			++Run;
			result = tkRplComment;
			FRange = rsComRpl;
		}
		else
		result = IdentProc();
	}
	else
	{
		if(((Run == 1) || (fLineStr[Run - 1] <= L' ')) && (fLineStr[Run] == L'(') && (Run < fLineStr.Length()) && (fLineStr[Run + 1] == L'*') && ((Run + 2 > fLineStr.Length()) || (fLineStr[Run + 2] <= L' ')))
		{
			Run += 2;
			result = tkAsmComment;
			FRange = rsComAsm1;
		}
		else
		result = IdentProc();
	}
	return result;
}

TtkTokenKind __fastcall TSynHP48Syn::PersentProc()
{
	TtkTokenKind result = tkNull;
	if(FRange == rsAsm)
	{
		++Run;
		result = tkAsmComment;
		while((Run <= fLineStr.Length()))
			switch(fLineStr[Run])
			{
				case L'\x0a':
				case L'\x0d':
				{
					++Run;
					goto label0;
				}
				default:
				++Run;
				break;
			}
		label0:;
	}
	else
	result = IdentProc();
	return result;
}

TtkTokenKind __fastcall TSynHP48Syn::StarProc()
{
	TtkTokenKind result = tkNull;
	if(FRange == rsRpl)
	{
		++Run;
		result = tkRplComment;
		while((Run <= fLineStr.Length()))
			switch(fLineStr[Run])
			{
				case L'\x0a':
				case L'\x0d':
				{
					++Run;
					goto label1;
				}
				default:
				++Run;
				break;
			}
		label1:;
	}
	else
	result = IdentProc();
	return result;
}

TtkTokenKind __fastcall TSynHP48Syn::IdentProc()
{
	TtkTokenKind result = tkNull;
	int i = 0;
	String s;
	i = Run;
	EndOfToken();
	s = fLineStr.SubString(i, Run - i);
	if(FRange == rsAsm)
	{
		if(FAsmKeyWords->Find(s) != nullptr)
		{
			if((s == L"!RPL") || (s == L"ENDCODE"))
			{
				FRange = rsRpl;
				result = tkAsmKey;
			}
			else
			result = tkAsmKey;
		}
		else
		{
			if(fLineStr[i] != L'*')
				result = tkAsm;
			else
				result = tkAsmKey;
		}
	}
	else
	{
		if(FRplKeyWords->Find(s) != nullptr)
		{
			if((s == L"CODEM") || (s == L"ASSEMBLEM"))
			{
				FRange = rsAsm;
				result = tkAsmKey;
			}
			else
			{
				if((s == L"CODE") || (s == L"ASSEMBLE"))
				{
					FRange = rssasm1;
					result = tksAsmKey;
				}
				else
				result = tkRplKey;
			}
		}
		else
		result = tkRpl;
	}
	return result;
}

TtkTokenKind __fastcall TSynHP48Syn::GetTokenFromRange()
{
	TtkTokenKind result = tkNull;
	switch(FRange)
	{
		case rsAsm:
		result = tkAsm;
		break;
		case rssasm1:
		result = tksAsmKey;
		break;
		case rssasm2:
		result = tksAsm;
		break;
		case rssasm3:
		result = tksAsmComment;
		break;
		case rsRpl:
		result = tkRpl;
		break;
		case rsComRpl:
		result = tkRplComment;
		break;
		case rsComAsm1:
		case rsComAsm2:
		result = tkAsmComment;
		break;
		default:
		result = tkNull;
		break;
	}
	return result;
}

TtkTokenKind __fastcall TSynHP48Syn::NullProc()
{
	TtkTokenKind result = tkNull;
	result = tkNull;
	++Run;
	return result;
}

TtkTokenKind __fastcall TSynHP48Syn::SpaceProc()
{
	TtkTokenKind result = tkNull;
	++Run;
	while((Run <= fLineStr.Length()) && CharInSet(fLineStr[Run], SynHighlighterHP48__1))
		++Run;
	result = GetTokenFromRange();
	return result;
}

TtkTokenKind __fastcall TSynHP48Syn::Next1()
{
	TtkTokenKind result = tkNull;
	fTokenPos = Run - 1;
	if(Run > fLineStr.Length())
		result = NullProc();
	else
	{
		if(FRange == rsComRpl)
			result = RplComProc();
		else
		{
			if(FRange == rsComAsm1)
				result = AsmComProc(L')');
			else
			{
				if(FRange == rsComAsm2)
					result = AsmComProc(L'/');
				else
				{
					if(FRange == rssasm1)
						result = SasmProc1();
					else
					{
						if(FRange == rssasm2)
							result = SasmProc2();
						else
						{
							if(FRange == rssasm3)
								result = SasmProc3();
							else
							{
								if(CharInSet(fLineStr[Run], SynHighlighterHP48__2))
									result = SpaceProc();
								else
								{
									if(fLineStr[Run] == L'(')
										result = ParOpenProc();
									else
									{
										if(fLineStr[Run] == L'%')
											result = PersentProc();
										else
										{
											if(fLineStr[Run] == L'/')
												result = SlashProc();
											else
											{
												if((Run == 1) && (FRange == rsRpl) && (fLineStr[1] == L'*'))
													result = StarProc();
												else
													result = IdentProc();
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return result;
}

void __fastcall TSynHP48Syn::Next2(TtkTokenKind tkk)
{
	fTockenKind = tkk;
}

void __fastcall TSynHP48Syn::Next()
{
	Next2(Next1());
	inherited::Next();
}

bool __fastcall TSynHP48Syn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 2;
	return result;
}

void* __fastcall TSynHP48Syn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

void __fastcall TSynHP48Syn::SetRange(void* Value)
{
	FRange = (TRangeState)(int)Value;
}

void __fastcall TSynHP48Syn::ResetRange()
{
	FRange = BaseRange;
}

TSynHighlighterAttributes* __fastcall TSynHP48Syn::GetAttrib(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	result = Attribs[((TtkTokenKind) Index)];
	return result;
}

void __fastcall TSynHP48Syn::SetAttrib(int Index, TSynHighlighterAttributes* Value)
{
	Attribs[((TtkTokenKind) Index)]->Assign(Value);
}

void __fastcall TSynHP48Syn::EndOfToken()
{
	while((Run <= fLineStr.Length()) && (fLineStr[Run] > L' '))
		++Run;
}

bool __fastcall TSynHP48Syn::LoadFromRegistry(HKEY RootKey, String key)
{
	bool result = false;
	TBetterRegistry* R = nullptr;
	R = new TBetterRegistry();
	try
	{
		R->RootKey = RootKey;
		if(R->OpenKeyReadOnly(key))
		{
			if(R->ValueExists(L"AsmKeyWordList"))
				AsmKeyWords->Text = R->ReadString(L"AsmKeyWordList");
			if(R->ValueExists(L"RplKeyWordList"))
				RplKeyWords->Text = R->ReadString(L"RplKeyWordList");
			result = inherited::LoadFromRegistry(RootKey, key);
		}
		else
		result = false;
	}
	__finally
	{
		delete R;
	}
	return result;
}

bool __fastcall TSynHP48Syn::SaveToRegistry(HKEY RootKey, String key)
{
	bool result = false;
	TBetterRegistry* R = nullptr;
	R = new TBetterRegistry();
	try
	{
		R->RootKey = RootKey;
		if(R->OpenKey(key, true))
		{
			R->WriteString(L"AsmKeyWordList", AsmKeyWords->Text);
			R->WriteString(L"RplKeyWordList", RplKeyWords->Text);
			result = inherited::SaveToRegistry(RootKey, key);
		}
		else
		result = false;
	}
	__finally
	{
		delete R;
	}
	return result;
}

void __fastcall TSynHP48Syn::Assign(TPersistent* Source)
{
	TtkTokenKind i = tkNull;
	if(ObjectIs(Source, TSynHP48Syn*))
	{
		int stop = 0;
		for(stop = 9 /*# High(Attribs) */, i = 0 /*# Low(Attribs) */; i <= stop; Inc(i))
		{
			Attribs[i]->Background = ((TSynHP48Syn*) Source)->Attribs[i]->Background;
			Attribs[i]->Foreground = ((TSynHP48Syn*) Source)->Attribs[i]->Foreground;
			Attribs[i]->Style = ((TSynHP48Syn*) Source)->Attribs[i]->Style;
		}
		AsmKeyWords->Text = ((TSynHP48Syn*) Source)->AsmKeyWords->Text;
		RplKeyWords->Text = ((TSynHP48Syn*) Source)->RplKeyWords->Text;
	}
	else
	inherited::Assign(Source);
}

int __fastcall TSynHP48Syn::GetAttribCount()
{
	int result = 0;
	result = int(9 /*# High(Attribs) */) - int(0 /*# Low(Attribs) */) + 1;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynHP48Syn::getAttribute(int Idx)
{
	TSynHighlighterAttributes* result = nullptr; // sorted by name
	if(Idx <= int((TtkTokenKind) 9 /*# High(TtkTokenKind) */))
		result = Attribs[((TtkTokenKind) Idx)];
	else
		result = nullptr;
	return result;
}

bool __fastcall TSynHP48Syn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterHP48;
	return result;
}

/*#static*/
String __fastcall TSynHP48Syn::GetLanguageName()
{
	String result;
	result = SYNS_LangHP48;
	return result;
}

void __fastcall TSynHP48Syn::SetHighLightChange()
{
	TtkTokenKind i = tkNull;
	int stop = 0;
	for(stop = 9 /*# High(Attribs) */, i = 0 /*# Low(Attribs) */; i <= stop; Inc(i))
	{
		Attribs[i]->OnChange = DefHighlightChange;
		Attribs[i]->InternalSaveDefaultValues();
	}
}

TtkTokenKind __fastcall TSynHP48Syn::SasmProc1()
{
	TtkTokenKind result = tkNull;
	int i = 0;
	String s;
	result = tksAsmKey;
	if(Run > fLineStr.Length())
		return result;
	if(fLineStr[Run] == L'*')
	{
		FRange = rssasm3;
		result = tksAsmComment;
		return result;
	}
	if(fLineStr[Run] >= L' ')
	{
		i = Run;
		while((Run <= fLineStr.Length()) && (fLineStr[Run] > L' '))
			++Run;
		s = fLineStr.SubString(i, Run - i);
		if((s == L"RPL") || (s == L"ENDCODE"))
		{
			FRange = rsRpl;
			return result;
		}
	}
	while((Run <= fLineStr.Length()) && (fLineStr[Run] <= L' ') && (fLineStr[Run] != L'\x0a'))
		++Run;
	if(Run <= fLineStr.Length())
		FRange = rssasm2;
	else
		FRange = rssasm1;
	return result;
}

TtkTokenKind __fastcall TSynHP48Syn::SasmProc2()
{
	TtkTokenKind result = tkNull;
	int i = 0;
	String s;
	result = tksAsm;
	while((Run <= fLineStr.Length()) && (fLineStr[Run] <= L' ') && (fLineStr[Run] != L'\x0a'))
		++Run;
	if(Run > 30)
	{
		FRange = rssasm3;
		return result;
	}
	i = Run;
	while((Run <= fLineStr.Length()) && (fLineStr[Run] > L' '))
		++Run;
	s = fLineStr.SubString(i, Run - i);
	if((s == L"ENDCODE") || (s == L"RPL"))
	{
		FRange = rsRpl;
		result = tksAsmKey;
	}
	else
	{
		if(FSAsmNoField->Find(s) == nullptr)
		{
			while((Run <= fLineStr.Length()) && (fLineStr[Run] <= L' ') && (fLineStr[Run] != L'\x0a'))
				++Run;
			while((Run <= fLineStr.Length()) && (fLineStr[Run] > L' '))
				++Run;
			while((Run <= fLineStr.Length()) && (fLineStr[Run] <= L' ') && (fLineStr[Run] != L'\x0a'))
				++Run;
		}
		if(Run <= fLineStr.Length())
			FRange = rssasm3;
		else
			FRange = rssasm1;
	}
	return result;
}

TtkTokenKind __fastcall TSynHP48Syn::SasmProc3()
{
	TtkTokenKind result = tkNull;
	result = tksAsmComment;
	while((Run <= fLineStr.Length()) && (fLineStr[Run] != L'\x0a'))
		++Run;
	if(Run <= fLineStr.Length())
		++Run;
	FRange = rssasm1;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynHP48Syn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	result = GetAttrib(int(fTockenKind));
	return result;
}

int __fastcall TSynHP48Syn::GetTokenKind()
{
	int result = 0;
	result = int(fTockenKind);
	return result;
}

TSynHighlighterAttributes* __fastcall TSynHP48Syn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	result = nullptr;
	return result;
}

// reimplement functions to handle the non-standard use of 1-based Run
// (instead of the standard 0-based Run)

void __fastcall TSynHP48Syn::DoSetLine(const String Value, int LineNumber)
{
	inherited::DoSetLine(Value, LineNumber);
	Run = 1;
	fOldRun = Run;
}

String __fastcall TSynHP48Syn::GetToken()
{
	String result;
	int Len = 0;
	Len = (Run - 1) - fTokenPos;
	result.SetLength(Len);
	if(Len > 0)
		StrLCopy(ustr2pwchar(result, 1 - 1), fCasedLine + fTokenPos, (unsigned int) Len);
	return result;
}

bool __fastcall TSynHP48Syn::IsLineEnd(int Run)
{
	bool result = false;
	result = (Run - 1 >= fLineLen) || (fLine[Run - 1] == L'\x0a') || (fLine[Run - 1] == L'\x0d');
	return result;
}

/*#static*/
String __fastcall TSynHP48Syn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangHP48;
	return result;
}
static bool SynHighlighterHP48_Initialized = false;

void SynHighlighterHP48_initialization()
{
	if(SynHighlighterHP48_Initialized)
		return;
	
	SynHighlighterHP48_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynHP48Syn));
}
class SynHighlighterHP48_unit
{
public:
	SynHighlighterHP48_unit()
	{
		SynHighlighterHP48_initialization();
	}
};

SynHighlighterHP48_unit _SynHighlighterHP48_unit;

}  // namespace SynHighlighterHP48

