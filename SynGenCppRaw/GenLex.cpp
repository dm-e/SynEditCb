
#include <vcl.h>
#pragma hdrstop

#include "GenLex.h"

using namespace std;
using namespace d2c_system;
using namespace Longintlist;
using namespace System;
using namespace System::Sysutils;

namespace Genlex
{
#define GenLex__0 (TSysCharSet() << L'_' <<  \
										97 << 98 << 99 << 100 << 101 << 102 <<  \
										103 << 104 << 105 << 106 << 107 << 108 <<  \
										109 << 110 << 111 << 112 << 113 << 114 <<  \
										115 << 116 << 117 << 118 << 119 << 120 <<  \
										121 << 122 <<  \
										65 << 66 << 67 << 68 << 69 << 70 <<  \
										71 << 72 << 73 << 74 << 75 << 76 <<  \
										77 << 78 << 79 << 80 << 81 << 82 <<  \
										83 << 84 << 85 << 86 << 87 << 88 <<  \
										89 << 90)
#define GenLex__1 (TSysCharSet() << L'_' <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57 <<  \
										97 << 98 << 99 << 100 << 101 << 102 <<  \
										103 << 104 << 105 << 106 << 107 << 108 <<  \
										109 << 110 << 111 << 112 << 113 << 114 <<  \
										115 << 116 << 117 << 118 << 119 << 120 <<  \
										121 << 122 <<  \
										65 << 66 << 67 << 68 << 69 << 70 <<  \
										71 << 72 << 73 << 74 << 75 << 76 <<  \
										77 << 78 << 79 << 80 << 81 << 82 <<  \
										83 << 84 << 85 << 86 << 87 << 88 <<  \
										89 << 90)
#define GenLex__2 (TSysCharSet() << L'\x0a' << L'\x0d')
#define GenLex__3 (TSysCharSet() <<  \
										1 << 2 << 3 << 4 << 5 << 6 <<  \
										7 << 8 << 9 << L'\x0b' << L'\x0c' <<  \
										14 << 15 << 16 << 17 << 18 << 19 <<  \
										20 << 21 << 22 << 23 << 24 << 25 <<  \
										26 << 27 << 28 << 29 << 30 << 31 <<  \
										32)


unsigned char Identifiers[256/*# range #0..#255*/];
int mHashTable[256/*# range #0..#255*/];

void __fastcall MakeIdentTable()
{
	Char i = L'\0';
	Char j = L'\0';
	Char stop = 0;
	for(stop = L'\xff', i = L'\x00'; i <= stop; i++)
	{
		switch(i)
		{
			case L'_':
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			Identifiers[i] = true;
			break;
			default:
			Identifiers[i] = false;
			break;
		}
		j = UpperCase(String(i))[1];
		switch(CharInSet(i, GenLex__0))
		{
			case true:
			mHashTable[i] = int(j) - 64;
			break;
			default:
			mHashTable[i] = 0;
			break;
		}
	}
}

void __fastcall TGenLex::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 150, i = 0; i <= stop; i++)
	{
		switch(i)
		{
			case 49:
			fIdentFuncTable[i] = Func49;
			break;
			case 60:
			fIdentFuncTable[i] = Func60;
			break;
			case 67:
			fIdentFuncTable[i] = Func67;
			break;
			case 75:
			fIdentFuncTable[i] = Func75;
			break;
			case 81:
			fIdentFuncTable[i] = Func81;
			break;
			case 89:
			fIdentFuncTable[i] = Func89;
			break;
			case 104:
			fIdentFuncTable[i] = Func104;
			break;
			case 122:
			fIdentFuncTable[i] = Func122;
			break;
			case 130:
			fIdentFuncTable[i] = Func130;
			break;
			case 147:
			fIdentFuncTable[i] = Func147;
			break;
			case 150:
			fIdentFuncTable[i] = Func150;
			break;
			default:
			fIdentFuncTable[i] = AltFunc;
			break;
		}
	}
}

int __fastcall TGenLex::KeyHash(PWideChar ToHash)
{
	int result = 0;
	result = 0;
	while(CharInSet((*ToHash), GenLex__1))
	{
		result += mHashTable[(*ToHash)];
		++ToHash;
	}
	fStringLen = ToHash - fToIdent;
	return result;
} /* KeyHash */

bool __fastcall TGenLex::KeyComp(String AKey)
{
	bool result = false;
	int i = 0;
	PWideChar Temp = nullptr;
	Temp = fToIdent;
	if(AKey.Length() == fStringLen)
	{
		int stop = 0;
		result = true;
		for(stop = fStringLen, i = 1; i <= stop; i++)
		{
			if(mHashTable[(*Temp)] != mHashTable[AKey[i]])
			{
				result = false;
				break;
			}
			++Temp;
		}
	}
	else
	result = false;
	return result;
} /* KeyComp */

TIdTokenKind __fastcall TGenLex::Func49()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	if(KeyComp(L"Chars"))
		result = TIdTokenKind::IdChars;
	else
		result = TIdTokenKind::IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func60()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	if(KeyComp(L"Keys"))
		result = TIdTokenKind::IdKeys;
	else
		result = TIdTokenKind::IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func67()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	if(KeyComp(L"EndFunc"))
		result = TIdTokenKind::IdEndFunc;
	else
		result = TIdTokenKind::IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func75()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	if(KeyComp(L"EndProc"))
		result = TIdTokenKind::IdEndProc;
	else
		result = TIdTokenKind::IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func81()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	if(KeyComp(L"BeginFunc"))
		result = TIdTokenKind::IdBeginFunc;
	else
		result = TIdTokenKind::IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func89()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	if(KeyComp(L"BeginProc"))
		result = TIdTokenKind::IdBeginProc;
	else
		result = TIdTokenKind::IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func104()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	if(KeyComp(L"EnclosedBy"))
		result = TIdTokenKind::IdEnclosedBy;
	else
		result = TIdTokenKind::IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func122()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	if(KeyComp(L"Sensitive"))
		result = TIdTokenKind::IdSensitive;
	else
		result = TIdTokenKind::IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func130()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	if(KeyComp(L"IdentStart"))
		result = TIdTokenKind::IdIdentStart;
	else
		result = TIdTokenKind::IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func147()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	if(KeyComp(L"SAMPLESOURCE"))
		result = TIdTokenKind::IdSampleSource;
	else
		result = TIdTokenKind::IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func150()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	if(KeyComp(L"TOKENTYPES"))
		result = TIdTokenKind::IdTokenTypes;
	else
		result = TIdTokenKind::IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::AltFunc()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	result = TIdTokenKind::IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::IdentKind(PWideChar Maybe)
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	int HashKey = 0;
	fToIdent = Maybe;
	HashKey = KeyHash(Maybe);
	if(HashKey < 151)
		result = fIdentFuncTable[HashKey]();
	else
		result = TIdTokenKind::IdIdentifier;
	return result;
}

void __fastcall TGenLex::MakeMethodTables()
{
	Char i = L'\0';
	Char stop = 0;
	for(stop = L'\xff', i = L'\x00'; i <= stop; i++)
	{
		switch(i)
		{
			case L'{':
			{
				fProcTable[i] = BraceOpenProc;
				fFuncTable[i] = BraceOpenFunc;
			}
			break;
			case L'\x0a':
			case L'\x0d':
			{
				fProcTable[i] = CRLFProc;
				fFuncTable[i] = CRLFFunc;
			}
			break;
			case L'\x27':
			case L'#':
			{
				fProcTable[i] = CharsetProc;
				fFuncTable[i] = CharsetFunc;
			}
			break;
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			case L'_':
			{
				fProcTable[i] = IdentProc;
				fFuncTable[i] = IdentFunc;
			}
			break;
			case L'\x00':
			{
				fProcTable[i] = NullProc;
				fFuncTable[i] = NullFunc;
			}
			break;
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			case L'\x0b':
			case L'\x0c':
			case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
			 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
			{
				fProcTable[i] = SpaceProc;
				fFuncTable[i] = SpaceFunc;
			}
			break;
			case L'|':
			{
				fProcTable[i] = StopProc;
				fFuncTable[i] = StopFunc;
			}
			break;
			default:
			fProcTable[i] = UnknownProc;
			fFuncTable[i] = UnknownFunc;
			break;
		}
	}
}

__fastcall TGenLex::TGenLex()
 : fIgnoreComments(false),
			FOrigin(nullptr),
			Run(0),
			Walker(0),
			Running(0),
			fStringLen(0),
			fToIdent(nullptr),
			fTokenizing(false),
			FLinePosList(nullptr),
			FTokenPositionsList(nullptr)
{
	//# inherited::Create();
	InitIdent();
	MakeMethodTables();
	FTokenPositionsList = new Longintlist::TLongintList();
	FLinePosList = new Longintlist::TLongintList();
} /* Create */

__fastcall TGenLex::~TGenLex()
{
	//# inherited::Destroy();
	delete FTokenPositionsList;
	delete FLinePosList;
}
 /* Destroy */

void __fastcall TGenLex::SetOrigin(PWideChar NewValue)
{
	FOrigin = NewValue;
	Run = 0;
	Walker = 0;
	FTokenPositionsList->Clear();
	FTokenPositionsList->Add(0);
	FLinePosList->Clear();
	FLinePosList->Add(0);
} /* SetOrigin */

void __fastcall TGenLex::SetRunPos(int Value)
{
	Run = Value;
}

void __fastcall TGenLex::BraceOpenProc()
{
	++Walker;
	if(!fIgnoreComments)
	{
		while(FOrigin[Walker] != L'\x00')
		{
			switch(FOrigin[Walker])
			{
				case L'}':
				{
					++Walker;
					goto label0;
				}
				case L'\x0a':
				{
					++Walker;
					if(fTokenizing)
						FLinePosList->Add(Walker);
				}
				break;
				case L'\x0d':
				{
					if(FOrigin[Walker + 1] == L'\x0a')
						Walker += 2;
					else
						++Walker;
					if(fTokenizing)
						FLinePosList->Add(Walker);
				}
				break;
				default:
				++Walker;
				break;
			}
		}
		label0:;
	}
}

TIdTokenKind __fastcall TGenLex::BraceOpenFunc()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	result = TIdTokenKind::IdBraceOpen;
	return result;
}

void __fastcall TGenLex::CRLFProc()
{
	switch(FOrigin[Walker])
	{
		case L'\x0a':
		++Walker;
		break;
		case L'\x0d':
		switch(FOrigin[Walker + 1])
		{
			case L'\x0a':
			Walker += 2;
			break;
			default:
			++Walker;
			break;
		}
		break;
		default:
		  ;
		break;
	}
	if(fTokenizing)
		FLinePosList->Add(Walker);
}

TIdTokenKind __fastcall TGenLex::CRLFFunc()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	result = TIdTokenKind::IdCRLF;
	return result;
}

void __fastcall TGenLex::CharsetProc()
{
	while(FOrigin[Walker] != L'\x00')
	{
		switch(FOrigin[Walker])
		{
			case L'\x0a':
			case L'\x0d':
			goto label1;
			case L':':
			if(FOrigin[Walker + 1] == L':')
				goto label2;
			else
				++Walker;
			break;
			default:
			++Walker;
			break;
		}
	}
	label1:;
	label2:;
}

TIdTokenKind __fastcall TGenLex::CharsetFunc()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	result = TIdTokenKind::IdCharset;
	return result;
}

void __fastcall TGenLex::IdentProc()
{
	++Walker;
	while(Identifiers[FOrigin[Walker]])
		++Walker;
}

TIdTokenKind __fastcall TGenLex::IdentFunc()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	result = IdentKind((FOrigin + Running));
	return result;
}

void __fastcall TGenLex::NullProc()
{
	if(fTokenizing)
	{
		if(!CharInSet(FOrigin[Walker - 1], GenLex__2))
			FLinePosList->Add(Walker);
	}
}

TIdTokenKind __fastcall TGenLex::NullFunc()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	result = TIdTokenKind::IdNull;
	return result;
}

void __fastcall TGenLex::SpaceProc()
{
	while(CharInSet(FOrigin[Walker], GenLex__3))
		++Walker;
}

TIdTokenKind __fastcall TGenLex::SpaceFunc()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	result = TIdTokenKind::IdSpace;
	return result;
}

void __fastcall TGenLex::StopProc()
{
	++Walker;
	while(FOrigin[Walker] != L'\x00')
	{
		switch(FOrigin[Walker])
		{
			case L'\x0a':
			goto label3;
			case L'\x0d':
			goto label4;
			case L'|':
			{
				++Walker;
				goto label5;
			}
			default:
			++Walker;
			break;
		}
	}
	label3:;
	label4:;
	label5:;
}

TIdTokenKind __fastcall TGenLex::StopFunc()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	result = TIdTokenKind::IdUnknown;
	if(FOrigin[Running + 1] == L'>')
	{
		if(FOrigin[Running + 2] == L'<')
		{
			if(FOrigin[Running + 3] == L'|')
				result = TIdTokenKind::IdStop;
		}
	}
	return result;
}

void __fastcall TGenLex::UnknownProc()
{
	++Walker;
}

TIdTokenKind __fastcall TGenLex::UnknownFunc()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	result = TIdTokenKind::IdUnknown;
	return result;
}

bool __fastcall TGenLex::Eof()
{
	bool result = false;
	result = false;
	return result;
} /* EOF */

TIdTokenKind __fastcall TGenLex::GetRunId()
{
	TIdTokenKind result = TIdTokenKind::IdBeginFunc;
	Running = FTokenPositionsList->Items[Run];
	result = fFuncTable[FOrigin[Running]]();
	return result;
}

String __fastcall TGenLex::GetRunToken()
{
	String result;
	int StartPos = 0;
	int EndPos = 0;
	int StringLen = 0;
	StartPos = FTokenPositionsList->Items[Run];
	EndPos = FTokenPositionsList->Items[Run + 1];
	StringLen = EndPos - StartPos;
	SetString(result, (FOrigin + StartPos), StringLen);
	return result;
}

void __fastcall TGenLex::Tokenize()
{
	fTokenizing = true;
	do
	{
		fProcTable[FOrigin[Walker]]();
		FTokenPositionsList->Add(Walker);
	}
	while(!(FOrigin[Walker] == L'\x00'));
	fTokenizing = false;
}

void __fastcall TGenLex::Next()
{
	++Run;
}

String __fastcall TGenLex::NextToken()
{
	String result;
	int StartPos = 0;
	int EndPos = 0;
	int Len = 0;
	StartPos = FTokenPositionsList->Items[Run];
	EndPos = FTokenPositionsList->Items[Run + 1];
	Len = EndPos - StartPos;
	SetString(result, (FOrigin + StartPos), Len);
	++Run;
	return result;
}
static bool GenLex_Initialized = false;

void GenLex_initialization()
{
	if(GenLex_Initialized)
		return;
	
	GenLex_Initialized = true;
	
	MakeIdentTable();
}
class GenLex_unit
{
public:
	GenLex_unit()
	{
		GenLex_initialization();
	}
};

GenLex_unit _GenLex_unit;

}  // namespace GenLex

