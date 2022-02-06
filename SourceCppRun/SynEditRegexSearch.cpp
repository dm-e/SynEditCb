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
using namespace System;
using namespace System::Classes;
using namespace System::Regularexpressions;
using namespace System::Regularexpressionsapi;
using namespace System::Regularexpressionscore;
using namespace System::Sysutils;
using namespace Vcl::Consts;

namespace Syneditregexsearch
{
#define SynEditRegexSearch__0 TRegExOptions()
#define SynEditRegexSearch__1 (TReplaceFlags() << System_Sysutils__95::rfReplaceAll)
#define SynEditRegexSearch__2 (TReplaceFlags() << System_Sysutils__95::rfReplaceAll)
#define SynEditRegexSearch__3 TRegExOptions()
#define SynEditRegexSearch__4 (TRegExOptions() << roIgnoreCase)


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
		//auto with0 = m_Helped;
		//with0->FPCREOptions = with0->FPCREOptions | PCREOptions;
	// todo dme	m_Helped.FPCREOptions = m_Helped.FPCREOptions | PCREOptions;
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
//		auto& with0 = m_Helped;
//		TPerlRegExHelper(*with0.FRegEx).SetAdditionalPCREOptions(PCREOptions);
	// todo dme	TPerlRegExHelper(m_Helped.FRegEx).SetAdditionalPCREOptions(PCREOptions);
	}
}

/* TSynEditRegexSearch */

__fastcall TSynEditRegexSearch::TSynEditRegexSearch(TComponent* AOwner)
 : inherited(AOwner)
{
	fOptions = SynEditRegexSearch__0;
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
	result = StringReplace(AReplace, L"\\n", WideCRLF, SynEditRegexSearch__1);
	result = StringReplace(result, L"\\t", L"\x09", SynEditRegexSearch__2);
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
	result = FPattern;
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
	if(Value.Contains(TSynSearchOption::ssoMatchCase))
		fOptions = SynEditRegexSearch__3;
	else
		fOptions = SynEditRegexSearch__4;
	RegEx = TRegEx(FPattern, fOptions);
	TRegExHelper(RegEx).SetAdditionalPCREOptions(PCRE_UCP);
}

void __fastcall TSynEditRegexSearch::SetPattern(const String Value)
{
	FPattern = Value;
	RegEx = TRegEx(FPattern, fOptions);
	TRegExHelper(RegEx).SetAdditionalPCREOptions(PCRE_UCP);
}


}  // namespace SynEditRegexSearch

