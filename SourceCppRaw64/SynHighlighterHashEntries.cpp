#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterHashEntries.h"
#include <System.SysUtils.hpp>
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;

namespace Synhighlighterhashentries
{

__fastcall TSynHashEntry::TSynHashEntry() {}
__fastcall TSynHashEntryList::TSynHashEntryList() {}



void __fastcall EnumerateKeywords(int AKind, String KeywordList, TCategoryMethod IsIdentChar, TEnumerateKeywordEvent AKeywordProc)
{
	PWideChar pStart = nullptr;
	PWideChar pEnd = nullptr;
	String Keyword;
	if(ASSIGNED(AKeywordProc) && (KeywordList != L""))
	{
		pEnd = ustr2pwchar(KeywordList);
		pStart = pEnd;
		do

      // skip over chars that are not in Identifiers
		{
			while(((*pStart) != L'\x00') && !IsIdentChar((*pStart)))
				++pStart;
			if((*pStart) == L'\x00')
				break;
      // find the last char that is in Identifiers
			pEnd = pStart + 1;
			while(((*pEnd) != L'\x00') && IsIdentChar((*pEnd)))
				++pEnd;
      // call the AKeywordProc with the keyword
			SetString(Keyword, pStart, pEnd - pStart);
			AKeywordProc(Keyword, AKind);
			Keyword = L"";
      // pEnd points to a char not in Identifiers, restart after that
			pStart = pEnd + 1;
		}
		while(!(((*pStart) == L'\x00') || ((*pEnd) == L'\x00')));
	}
}

/* TSynHashEntry */

__fastcall TSynHashEntry::TSynHashEntry(const String AKey, int AKind)
 : fNext(nullptr),
			fKeyLen(0),
			fKind(0)
{
	//# inherited::Create();
	fKeyLen = AKey.Length();
	fKeyword = AKey;
	fKind = AKind;
}

__fastcall TSynHashEntry::~TSynHashEntry()
{
	delete fNext;
	//# inherited::Destroy();
}

TSynHashEntry* __fastcall TSynHashEntry::AddEntry(TSynHashEntry* NewEntry)
{
	TSynHashEntry* result = nullptr;
	result = this;
	if(ASSIGNED(NewEntry))
	{
		if(CompareText(NewEntry->Keyword, fKeyword) == 0)
			throw new Exception(L"Keyword \"%s\" already in list", ARRAYOFCONST((fKeyword)));
		if(NewEntry->fKeyLen < fKeyLen)
		{
			NewEntry->fNext = this;
			result = NewEntry;
		}
		else
		{
			if(ASSIGNED(fNext))
				fNext = fNext->AddEntry(NewEntry);
			else
				fNext = NewEntry;
		}
	}
	return result;
}

/* TSynHashEntryList */

void __fastcall TSynHashEntryList::Clear()
{
	int i = 0;
	int stop = 0;
	for(stop = Count - 1, i = 0; i <= stop; i++)
	{
		delete Items[i];
	}
	inherited::Clear();
}

TSynHashEntry* __fastcall TSynHashEntryList::Get(int HashKey)
{
	TSynHashEntry* result = nullptr;
	if((HashKey >= 0) && (HashKey < Count))
		result = ((TSynHashEntry*) inherited::Items[HashKey]);
	else
		result = nullptr;
	return result;
}

void __fastcall TSynHashEntryList::Put(int HashKey, TSynHashEntry* Entry)
{
	TSynHashEntry* ListEntry = nullptr;
	if(HashKey >= Count)
		Count = HashKey + 1;
	ListEntry = ((TSynHashEntry*) inherited::Items[HashKey]);
  // if there is already a hashentry for this hashvalue let it decide
  // where to put the new entry in its single linked list
	if(ASSIGNED(ListEntry))
		Entry = ListEntry->AddEntry(Entry);
	inherited::Items[HashKey] = Entry;
}


}  // namespace SynHighlighterHashEntries

