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

__fastcall TSynHashEntryList::TSynHashEntryList() {}



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterHashEntries.pas, released 2000-04-21.

The Initial Author of this file is Michael Hieke.
Portions created by Michael Hieke are Copyright 2000 Michael Hieke.
Unicode translation by Maël Hörz.
All Rights Reserved.

Contributors to the SynEdit project are listed in the Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

$Id: SynHighlighterHashEntries.pas,v 1.5.2.3 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

/*
@abstract(Support classes for SynEdit highlighters that create the keyword lists at runtime.)
@author(Michael Hieke)
@created(2000-04-21)
@lastmod(2001-09-07)
The classes in this unit can be used to use the hashing algorithm while still
having the ability to change the set of keywords.
*/

void __fastcall EnumerateKeywords(int AKind, String KeywordList, const TCategoryMethod& IsIdentChar, const TEnumerateKeywordEvent& AKeywordProc)
{
	PWideChar pStart = nullptr;
	PWideChar pEnd = nullptr;
	String Keyword;
	if(Assigned(AKeywordProc) && (KeywordList != L""))
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
			throw Exception(L"Keyword \"%s\" already in list", ARRAYOFCONST((fKeyword)));
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


}  // namespace Synhighlighterhashentries

