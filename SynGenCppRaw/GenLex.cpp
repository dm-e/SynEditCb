
#include <vcl.h>
#pragma hdrstop

#include "GenLex.h"

using namespace std;
using namespace d2c_system;
using namespace Longintlist;
using namespace System;

namespace Genlex
{
#define Genlex__0 (TSysCharSet() << '_' <<  \
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
#define Genlex__1 (TSysCharSet() << '_' <<  \
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
#define Genlex__2 (TSysCharSet() << '\x0a' << '\x0d')
#define Genlex__3 (TSysCharSet() <<  \
          1 << 2 << 3 << 4 << 5 << 6 <<  \
          7 << 8 << 9 << '\x0b' << '\x0c' <<  \
          14 << 15 << 16 << 17 << 18 << 19 <<  \
          20 << 21 << 22 << 23 << 24 << 25 <<  \
          26 << 27 << 28 << 29 << 30 << 31 <<  \
          32)


unsigned char Identifiers[256/*# range #0..#255*/];
int mHashTable[256/*# range #0..#255*/];

void __fastcall MakeIdentTable()
{
	Char I = L'\0';
	Char J = L'\0';
	WideChar stop = 0;
	for(stop = L'\xff', I = L'\x00'; I <= stop; I++)
	{
		switch(I)
		{
			case L'_':
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			Identifiers[I] = true;
			break;
			default:
			Identifiers[I] = false;
			break;
		}
		J = UpperCase(String(I))[1];
		switch(CharInSet(I, Genlex__0))
		{
			case true:
			mHashTable[I] = int(J) - 64;
			break;
			default:
			mHashTable[I] = 0;
			break;
		}
	}
}

void __fastcall TGenLex::InitIdent()
{
	int I = 0;
	int stop = 0;
	for(stop = 150, I = 0; I <= stop; I++)
	{
		switch(I)
		{
			case 49:
			fIdentFuncTable[I] = Func49;
			break;
			case 60:
			fIdentFuncTable[I] = Func60;
			break;
			case 67:
			fIdentFuncTable[I] = Func67;
			break;
			case 75:
			fIdentFuncTable[I] = Func75;
			break;
			case 81:
			fIdentFuncTable[I] = Func81;
			break;
			case 89:
			fIdentFuncTable[I] = Func89;
			break;
			case 104:
			fIdentFuncTable[I] = Func104;
			break;
			case 122:
			fIdentFuncTable[I] = Func122;
			break;
			case 130:
			fIdentFuncTable[I] = Func130;
			break;
			case 147:
			fIdentFuncTable[I] = Func147;
			break;
			case 150:
			fIdentFuncTable[I] = Func150;
			break;
			default:
			fIdentFuncTable[I] = AltFunc;
			break;
		}
	}
}

int __fastcall TGenLex::KeyHash(PWideChar ToHash)
{
	int result = 0;
	result = 0;
	while(CharInSet((*ToHash), Genlex__1))
	{
		result += mHashTable[(*ToHash)];
		++ToHash;
	}
	fStringLen = ToHash - fToIdent;
	return result;
} /* KeyHash */

bool __fastcall TGenLex::KeyComp(String aKey)
{
	bool result = false;
	int I = 0;
	PWideChar Temp = nullptr;
	Temp = fToIdent;
	if(aKey.Length() == fStringLen)
	{
		int stop = 0;
		result = true;
		for(stop = fStringLen, I = 1; I <= stop; I++)
		{
			if(mHashTable[(*Temp)] != mHashTable[aKey[I]])
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
	TIdTokenKind result = IdBeginFunc;
	if(KeyComp(L"Chars"))
		result = IdChars;
	else
		result = IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func60()
{
	TIdTokenKind result = IdBeginFunc;
	if(KeyComp(L"Keys"))
		result = IdKeys;
	else
		result = IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func67()
{
	TIdTokenKind result = IdBeginFunc;
	if(KeyComp(L"EndFunc"))
		result = IdEndFunc;
	else
		result = IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func75()
{
	TIdTokenKind result = IdBeginFunc;
	if(KeyComp(L"EndProc"))
		result = IdEndProc;
	else
		result = IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func81()
{
	TIdTokenKind result = IdBeginFunc;
	if(KeyComp(L"BeginFunc"))
		result = IdBeginFunc;
	else
		result = IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func89()
{
	TIdTokenKind result = IdBeginFunc;
	if(KeyComp(L"BeginProc"))
		result = IdBeginProc;
	else
		result = IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func104()
{
	TIdTokenKind result = IdBeginFunc;
	if(KeyComp(L"EnclosedBy"))
		result = IdEnclosedBy;
	else
		result = IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func122()
{
	TIdTokenKind result = IdBeginFunc;
	if(KeyComp(L"Sensitive"))
		result = IdSensitive;
	else
		result = IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func130()
{
	TIdTokenKind result = IdBeginFunc;
	if(KeyComp(L"IdentStart"))
		result = IdIdentStart;
	else
		result = IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func147()
{
	TIdTokenKind result = IdBeginFunc;
	if(KeyComp(L"SAMPLESOURCE"))
		result = IdSampleSource;
	else
		result = IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::Func150()
{
	TIdTokenKind result = IdBeginFunc;
	if(KeyComp(L"TOKENTYPES"))
		result = IdTokenTypes;
	else
		result = IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::AltFunc()
{
	TIdTokenKind result = IdBeginFunc;
	result = IdIdentifier;
	return result;
}

TIdTokenKind __fastcall TGenLex::IdentKind(PWideChar MayBe)
{
	TIdTokenKind result = IdBeginFunc;
	int HashKey = 0;
	fToIdent = MayBe;
	HashKey = KeyHash(MayBe);
	if(HashKey < 151)
		result = fIdentFuncTable[HashKey]();
	else
		result = IdIdentifier;
	return result;
}

void __fastcall TGenLex::MakeMethodTables()
{
	Char I = L'\0';
	WideChar stop = 0;
	for(stop = L'\xff', I = L'\x00'; I <= stop; I++)
	{
		switch(I)
		{
			case L'{':
			{
				fProcTable[I] = BraceOpenProc;
				fFuncTable[I] = BraceOpenFunc;
			}
			break;
			case L'\x0a':
			case L'\x0d':
			{
				fProcTable[I] = CRLFProc;
				fFuncTable[I] = CRLFFunc;
			}
			break;
			case L'\x27':
			case L'#':
			{
				fProcTable[I] = CharsetProc;
				fFuncTable[I] = CharsetFunc;
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
				fProcTable[I] = IdentProc;
				fFuncTable[I] = IdentFunc;
			}
			break;
			case L'\x00':
			{
				fProcTable[I] = NullProc;
				fFuncTable[I] = NullFunc;
			}
			break;
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			case L'\x0b':
			case L'\x0c':
			case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
			 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
			{
				fProcTable[I] = SpaceProc;
				fFuncTable[I] = SpaceFunc;
			}
			break;
			case L'|':
			{
				fProcTable[I] = StopProc;
				fFuncTable[I] = StopFunc;
			}
			break;
			default:
			{
				fProcTable[I] = UnknownProc;
				fFuncTable[I] = UnknownFunc;
			}
			break;
		}
	}
}

__fastcall TGenLex::TGenLex()
 : fIgnoreComments(false),
			fOrigin(nullptr),
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
	FTokenPositionsList = new Longintlist::TLongIntList();
	FLinePosList = new Longintlist::TLongIntList();
} /* Create */

__fastcall TGenLex::~TGenLex()
{
	//# inherited::Destroy();
	delete FTokenPositionsList;
	delete FLinePosList;
} /* Destroy */

void __fastcall TGenLex::SetOrigin(PWideChar NewValue)
{
	fOrigin = NewValue;
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
		while(fOrigin[Walker] != L'\x00')
		{
			switch(fOrigin[Walker])
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
					if(fOrigin[Walker + 1] == L'\x0a')
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
	TIdTokenKind result = IdBeginFunc;
	result = IdBraceOpen;
	return result;
}

void __fastcall TGenLex::CRLFProc()
{
	switch(fOrigin[Walker])
	{
		case L'\x0a':
		++Walker;
		break;
		case L'\x0d':
		switch(fOrigin[Walker + 1])
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
	TIdTokenKind result = IdBeginFunc;
	result = IdCRLF;
	return result;
}

void __fastcall TGenLex::CharsetProc()
{
	while(fOrigin[Walker] != L'\x00')
	{
		switch(fOrigin[Walker])
		{
			case L'\x0a':
			case L'\x0d':
			goto label1;
			case L':':
			if(fOrigin[Walker + 1] == L':')
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
	TIdTokenKind result = IdBeginFunc;
	result = IdCharset;
	return result;
}

void __fastcall TGenLex::IdentProc()
{
	++Walker;
	while(Identifiers[fOrigin[Walker]])
		++Walker;
}

TIdTokenKind __fastcall TGenLex::IdentFunc()
{
	TIdTokenKind result = IdBeginFunc;
	result = IdentKind((fOrigin + Running));
	return result;
}

void __fastcall TGenLex::NullProc()
{
	if(fTokenizing)
	{
		if(!CharInSet(fOrigin[Walker - 1], Genlex__2))
			FLinePosList->Add(Walker);
	}
}

TIdTokenKind __fastcall TGenLex::NullFunc()
{
	TIdTokenKind result = IdBeginFunc;
	result = IdNull;
	return result;
}

void __fastcall TGenLex::SpaceProc()
{
	while(CharInSet(fOrigin[Walker], Genlex__3))
		++Walker;
}

TIdTokenKind __fastcall TGenLex::SpaceFunc()
{
	TIdTokenKind result = IdBeginFunc;
	result = IdSpace;
	return result;
}

void __fastcall TGenLex::StopProc()
{
	++Walker;
	while(fOrigin[Walker] != L'\x00')
	{
		switch(fOrigin[Walker])
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
	TIdTokenKind result = IdBeginFunc;
	result = IdUnknown;
	if(fOrigin[Running + 1] == L'>')
	{
		if(fOrigin[Running + 2] == L'<')
		{
			if(fOrigin[Running + 3] == L'|')
				result = IdStop;
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
	TIdTokenKind result = IdBeginFunc;
	result = IdUnknown;
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
	TIdTokenKind result = IdBeginFunc;
	Running = FTokenPositionsList->Items[Run];
	result = fFuncTable[fOrigin[Running]]();
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
	SetString(result, (fOrigin + StartPos), StringLen);
	return result;
}

void __fastcall TGenLex::Tokenize()
{
	fTokenizing = true;
	do
	{
		fProcTable[fOrigin[Walker]]();
		FTokenPositionsList->Add(Walker);
	}
	while(!(fOrigin[Walker] == L'\x00'));
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
	SetString(result, (fOrigin + StartPos), Len);
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

}  // namespace Genlex

