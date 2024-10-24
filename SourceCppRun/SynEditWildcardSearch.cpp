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


}  // namespace SynEditWildcardSearch

