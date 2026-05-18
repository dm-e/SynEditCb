#include <vcl.h>
#pragma hdrstop

#include "Sample.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;

namespace Sample
{


const System::Char SYNS_FilterSample[] = L"All files (*.*)|*.*";
const System::Char SYNS_LangSample[] = L"Sample";
const System::Char SYNS_FriendlyLangSample[] = L"Sample";
const System::Char SYNS_AttrIdentifier[] = L"Identifier";
const System::Char SYNS_FriendlyAttrIdentifier[] = L"Identifier";
const System::Char SYNS_AttrKey[] = L"Key";
const System::Char SYNS_FriendlyAttrKey[] = L"Key";
const System::Char SYNS_AttrNull[] = L"Null";
const System::Char SYNS_FriendlyAttrNull[] = L"Null";
  // as this language is case-insensitive keywords *must* be in lowercase
const String KeyWords[1/*# range 0..0*/] = {L"hello"};
const int KeyIndices[2/*# range 0..1*/] = {0, -1};

void __fastcall TSynSampleSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 1 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[0] = FuncHello;
}

/*$Q-*/

unsigned int __fastcall TSynSampleSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = result + int((*Str));
		++Str;
	}
	result = static_cast<unsigned int>(result % 2);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynSampleSyn::FuncHello(int Index)
{
	TtkTokenKind result = tkIdentifier;
	if(IsCurrentToken(KeyWords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSampleSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkIdentifier;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynSampleSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkIdentifier;
	unsigned int Key = 0;
	fToIdent = MayBe;
	Key = HashKey(MayBe);
	if(Key <= 1 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[Key](KeyIndices[Key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynSampleSyn::NullProc()
{
	fTokenID = tkNull;
	++Run;
}

void __fastcall TSynSampleSyn::CRProc()
{
	fTokenID = tkUnknown;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynSampleSyn::LFProc()
{
	fTokenID = tkUnknown;
	++Run;
}

__fastcall TSynSampleSyn::TSynSampleSyn(TComponent* AOwner)
 : fRange(rsUnKnown),
			fTokenID(tkIdentifier),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr)
{
}


}  // namespace Sample

