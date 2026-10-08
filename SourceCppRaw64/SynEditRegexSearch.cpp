#include <vcl.h>
#pragma hdrstop

#include "SynEditRegexSearch.h"
#include <System.RegularExpressionsAPI.hpp>
#include <System.SysUtils.hpp>
#include <Vcl.Consts.hpp>

using namespace std;
using namespace d2c_system;
using namespace Syneditmiscclasses;
using namespace Synedittypes;
using namespace Synunicode;
using namespace System::Regularexpressions;
using namespace System::Regularexpressionsapi;
using namespace System::Regularexpressionscore;
using namespace System::Sysutils;
using namespace Vcl::Consts;

namespace Syneditregexsearch
{
#define Syneditregexsearch__0 TRegExOptions()
#define Syneditregexsearch__1 (TReplaceFlags() << rfReplaceAll)
#define Syneditregexsearch__2 (TReplaceFlags() << rfReplaceAll)
#define Syneditregexsearch__3 TRegExOptions()
#define Syneditregexsearch__4 (TRegExOptions() << roIgnoreCase)



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditRegexSearch.pas, released 2002-07-26.

Original Code by Eduardo Mauro, Gerald Nunn and Flávio Etrusco.
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

$Id: SynEditRegexSearch.pas,v 1.5.2.2 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
  /* TPerlRegExHelper */

struct TPerlRegExHelper
{
	#include "SynEditRegexSearch_friends.inc"
	TPerlRegExHelper(TPerlRegEx& Helped) : m_Helped(Helped) {}
	TPerlRegExHelper(const TPerlRegEx& Helped) : m_Helped(const_cast<TPerlRegEx&>(Helped)) {}
	void __fastcall SetAdditionalPCREOptions(int PCREOptions);
private:
	TPerlRegEx& m_Helped;

};

void __fastcall TPerlRegExHelper::SetAdditionalPCREOptions(int PCREOptions)
{
	/*# with Self do */
	{
		auto with0 = m_Helped;
		FPCREOptions = FPCREOptions | PCREOptions;
	}
}

struct TRegExHelper
{
	#include "SynEditRegexSearch_friends.inc"
	TRegExHelper(TRegEx& Helped) : m_Helped(Helped) {}
	TRegExHelper(const TRegEx& Helped) : m_Helped(const_cast<TRegEx&>(Helped)) {}
	void __fastcall SetAdditionalPCREOptions(int PCREOptions);
private:
	TRegEx& m_Helped;

};

void __fastcall TRegExHelper::SetAdditionalPCREOptions(int PCREOptions)
{
	/*# with Self do */
	{
		auto& with0 = m_Helped;
		FRegEx.SetAdditionalPCREOptions(PCREOptions);
	}
}

/* TSynEditRegexSearch */

__fastcall TSynEditRegexSearch::TSynEditRegexSearch(TComponent* AOwner)
 : inherited(AOwner)
{
	fOptions = Syneditregexsearch__0;
}

int __fastcall TSynEditRegexSearch::FindAll(const String NewText)
{
	int result = 0;
	fMatchCollection = RegEx.Matches(NewText);
	result = fMatchCollection.Count;
	return result;
}

// replace new line and tab symbol to real chars

String __fastcall TSynEditRegexSearch::PreprocessReplaceExpression(const String AReplace)
{
	String result;
	result = StringReplace(AReplace, L"\\n", WideCRLF, Syneditregexsearch__1);
	result = StringReplace(result, L"\\t", L"\x09", Syneditregexsearch__2);
	return result;
}

String __fastcall TSynEditRegexSearch::Replace(const String aOccurrence, const String aReplacement)
{
	String result;
	result = RegEx.Replace(aOccurrence, aReplacement);
	return result;
}

int __fastcall TSynEditRegexSearch::GetLength(int Index)
{
	int result = 0;
	result = fMatchCollection.Item[Index].Length;
	return result;
}

String __fastcall TSynEditRegexSearch::GetPattern()
{
	String result;
	result = fPattern;
	return result;
}

int __fastcall TSynEditRegexSearch::GetResult(int Index)
{
	int result = 0;
	result = fMatchCollection.Item[Index].Index;
	return result;
}

int __fastcall TSynEditRegexSearch::GetResultCount()
{
	int result = 0;
	result = fMatchCollection.Count;
	return result;
}

void __fastcall TSynEditRegexSearch::SetOptions(const TSynSearchOptions Value)
{
	if(Value.Contains(ssoMatchCase))
		fOptions = Syneditregexsearch__3;
	else
		fOptions = Syneditregexsearch__4;
	RegEx = TRegEx(fPattern, fOptions);
	TRegExHelper(RegEx).SetAdditionalPCREOptions(PCRE_UCP);
}

void __fastcall TSynEditRegexSearch::SetPattern(const String Value)
{
	fPattern = Value;
	RegEx = TRegEx(fPattern, fOptions);
	TRegExHelper(RegEx).SetAdditionalPCREOptions(PCRE_UCP);
}


}  // namespace Syneditregexsearch

