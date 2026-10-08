#include <vcl.h>
#pragma hdrstop

#include "SynEditWildcardSearch.h"
#include <Vcl.Consts.hpp>

using namespace std;
using namespace d2c_system;
using namespace Syneditregexsearch;
using namespace Synedittypes;
using namespace Vcl::Consts;

namespace Syneditwildcardsearch
{



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditWildcardSearch.pas, released 2003-06-21.

The original author of this file is Michael Elsdoerfer.
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

$Id: SynEditWildcardSearch.pas,v 1.2.2.2 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

/* TSynEditWildcardSearch */

__fastcall TSynEditWildcardSearch::TSynEditWildcardSearch(TComponent* AOwner)
 : inherited(AOwner),
			fPattern(L"")
{
}

__fastcall TSynEditWildcardSearch::~TSynEditWildcardSearch()
{
	// inherited;
}

int __fastcall TSynEditWildcardSearch::FindAll(const UnicodeString NewText)
{
	int result = 0;
	result = inherited::FindAll(NewText);
	return result;
}

UnicodeString __fastcall TSynEditWildcardSearch::Replace(const UnicodeString aOccurrence, const UnicodeString aReplacement)
{
	UnicodeString result;
	result = inherited::Replace(aOccurrence, aReplacement);
	return result;
}

int __fastcall TSynEditWildcardSearch::GetLength(int Index)
{
	int result = 0;
	result = inherited::GetLength(Index);
	return result;
}

UnicodeString __fastcall TSynEditWildcardSearch::GetPattern()
{
	UnicodeString result;
	result = fPattern;
	return result;
}

int __fastcall TSynEditWildcardSearch::GetResult(int Index)
{
	int result = 0;
	result = inherited::GetResult(Index);
	return result;
}

int __fastcall TSynEditWildcardSearch::GetResultCount()
{
	int result = 0;
	result = inherited::GetResultCount();
	return result;
}

void __fastcall TSynEditWildcardSearch::SetOptions(const TSynSearchOptions Value)
{
	inherited::SetOptions(Value);
}

void __fastcall TSynEditWildcardSearch::SetPattern(const UnicodeString Value)
{
	fPattern = Value;
  // Convert into a real regular expression and assign it
	inherited::SetPattern(WildCardToRegExpr(Value));
}

UnicodeString __fastcall TSynEditWildcardSearch::WildCardToRegExpr(UnicodeString AWildCard)
{
	UnicodeString result;
	int i = 0;
	int stop = 0;
	result = L"";
	for(stop = AWildCard.Length(), i = 1; i <= stop; i++)
	{
		switch(AWildCard[i])
		{
			case L'*':
			result = result + L".*";
			break;
			case L'?':
			result = result + L".?";
			break;
			default:
			result = result + String(AWildCard[i]);
			break;
		}
	}
	return result;
}


}  // namespace Syneditwildcardsearch

