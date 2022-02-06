#ifndef SynHighlighterHashEntriesH
#define SynHighlighterHashEntriesH

#include <System.hpp>
#include "d2c_system.h"

#include "SynEditTypes.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>

namespace Synhighlighterhashentries
{

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
  /* Class to hold the keyword to recognize, its length and its token kind. The
    keywords that have the same hashvalue are stored in a single-linked list,
    with the Next property pointing to the next entry. The entries are ordered
    over the keyword length. */

class TSynHashEntry : public System::TObject
{
	#include "SynHighlighterHashEntries_friends.inc"
public:
	typedef TObject inherited;	
protected:
    /* Points to the next keyword entry with the same hashvalue. */
	TSynHashEntry* FNext;
    /* Length of the keyword. */
	int fKeyLen;
    /* The keyword itself. */
	String fKeyword;
    /* Keyword token kind, has to be typecasted to the real token kind type. */
	int FKind;
public:
    /* Adds a keyword entry with the same hashvalue. Depending on the length of
      the two keywords it might return Self and store NewEntry in the Next
      pointer, or return NewEntry and make the Next property of NewEntry point
      to Self. This way the order of keyword length is preserved. */
	virtual TSynHashEntry* __fastcall AddEntry(TSynHashEntry* NewEntry);
    /* Creates a keyword entry for the given keyword and token kind. */
	__fastcall TSynHashEntry(const String AKey, int AKind);
    /* Destroys the keyword entry and all other keyword entries Next points to. */
	virtual __fastcall ~TSynHashEntry();
    /* The keyword itself. */
	__property String Keyword = { read = fKeyword };
    /* Length of the keyword. */
	__property int KeywordLen = { read = fKeyLen };
    /* Keyword token kind, has to be typecasted to the real token kind type. */
	__property int Kind = { read = FKind };
    /* Points to the next keyword entry with the same hashvalue. */
	__property TSynHashEntry* Next = { read = FNext };
	__fastcall TSynHashEntry();
};

  /* A list of keyword entries, stored as single-linked lists under the hashvalue
    of the keyword. */

class TSynHashEntryList : public System::Classes::TList
{
	#include "SynHighlighterHashEntries_friends.inc"
public:
	typedef System::Classes::TList inherited;	
protected:
    /* Returns the first keyword entry for a given hashcalue, or nil. */
	TSynHashEntry* __fastcall Get(int HashKey);
    /* Adds a keyword entry under its hashvalue. Will grow the list count when
      necessary, so the maximum hashvalue should be limited outside. The correct
      order of keyword entries is maintained. */
	void __fastcall Put(int HashKey, TSynHashEntry* Entry);
public:
    /* Clears the list and frees all contained keyword entries. */
	virtual void __fastcall Clear();
    /* Type-safe access to the first keyword entry for a hashvalue. */
	__property TSynHashEntry* Items[int Index] = { read = Get, write = Put/*# default */ };
	__fastcall TSynHashEntryList();
};

  /* Procedural type for adding keyword entries to a TSynHashEntryList when
    iterating over all the keywords contained in a string. */

/* This procedure will call AKeywordProc for all keywords in KeywordList. A
  keyword is considered any number of successive chars that are contained in
  Identifiers, with chars not contained in Identifiers before and after them. */
typedef void __fastcall (__closure *TEnumerateKeywordEvent) (String, int);
void __fastcall EnumerateKeywords(int AKind, String KeywordList, Synedittypes::TCategoryMethod IsIdentChar, TEnumerateKeywordEvent AKeywordProc);


}  // namespace SynHighlighterHashEntries

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterhashentries;
#endif

#endif // SynHighlighterHashEntriesH

