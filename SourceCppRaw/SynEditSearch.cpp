#include <vcl.h>
#pragma hdrstop

#include "SynEditSearch.h"
#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditmiscclasses;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;

namespace Syneditsearch
{



__fastcall TSynEditSearch::TSynEditSearch(TComponent* AOwner)
 : inherited(AOwner),
			Run(nullptr),
			Origin(nullptr),
			TheEnd(nullptr),
			FCount(0),
			fTextLen(0),
			Look_At(0),
			PatLen(0),
			PatLenSucc(0),
			FCaseSensitive(false),
			fWhole(false),
			fResults(nullptr),
			fShiftInitialized(false)
{
	fResults = new System::Classes::TList();
}

bool __fastcall TSynEditSearch::GetFinished()
{
	bool result = false;
	result = (Run >= TheEnd) || (PatLen >= fTextLen);
	return result;
}

int __fastcall TSynEditSearch::GetResult(int Index)
{
	int result = 0;
	result = 0;
	if((Index >= 0) && (Index < fResults->Count))
		result = (int)fResults->Items[Index];
	return result;
}

int __fastcall TSynEditSearch::GetResultCount()
{
	int result = 0;
	result = fResults->Count;
	return result;
}

void __fastcall TSynEditSearch::FixResults(int First, int delta)
{
	int i = 0;
	if((delta != 0) && (fResults->Count > 0))
	{
		i = Pred(fResults->Count);
		while(i >= 0)
		{
			if((int)fResults->Items[i] <= First)
				break;
			fResults->Items[i] = ((void*) ((int)fResults->Items[i] - delta));
			--i;
		}
	}
}

void __fastcall TSynEditSearch::InitShiftTable()
{
	int C = 0;
	int i = 0;
	int stop = 0;
	PatLen = (int) Pat.Length();
	if(PatLen == 0)
		throw new Exception(L"Pattern is empty");
	PatLenSucc = PatLen + 1;
	Look_At = 1;
	for(stop = 65535 /*# High(WideChar) */, C = 0 /*# Low(WideChar) */; C <= stop; C++)
	{
		Shift[C] = PatLenSucc;
	}
	for(stop = PatLen, i = 1; i <= stop; i++)
	{
		Shift[Pat[i]] = PatLenSucc - i;
	}
	while(Look_At < PatLen)
	{
		if(Pat[PatLen] == Pat[PatLen - Look_At])
			break;
		++Look_At;
	}
	fShiftInitialized = true;
}                                

// TODO: would be more intelligent to use IsWordBreakChar for SynEdit

bool __fastcall IsWordBreakChar(WideChar C)
{
	bool result = false;
	switch(C)
	{
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
		 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
		 case 30: case 31: case 32:
		case L'.':
		case L',':
		case L';':
		case L':':
		case L'\"':
		case L'\'':
		case L'?':
		case L'`':
		case L'?':
		case L'^':
		case L'!':
		case L'?':
		case L'&':
		case L'$':
		case L'@':
		case L'?':
		case L'%':
		case L'#':
		case L'~':
		case L'[':
		case L']':
		case L'(':
		case L')':
		case L'{':
		case L'}':
		case L'<':
		case L'>':
		case L'-':
		case L'=':
		case L'+':
		case L'*':
		case L'/':
		case L'\\':
		case L'|':
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

bool __fastcall TSynEditSearch::TestWholeWord()
{
	bool result = false;
	PWideChar Test = nullptr;
	Test = Run - PatLen;
	result = ((Test < Origin) || IsWordBreakChar(Test[0])) && ((Run >= TheEnd) || IsWordBreakChar(Run[1]));
	return result;
}

int __fastcall TSynEditSearch::Next()
{
	int result = 0;
	int i = 0;
	PWideChar j = nullptr;
	result = 0;
	Run += PatLen;
	while(Run < TheEnd)
	{
		if(Pat[PatLen] != (*Run))
			Run += Shift[(*(Run + 1))];
		else
		{
			j = Run - PatLen + 1;
			i = 1;
			while(Pat[i] == (*j))
			{
				if(i == PatLen)
				{
					if(fWhole && !TestWholeWord())
						break;
					++FCount;
					result = Run - Origin - PatLen + 2;
					return result;
				}
				++i;
				++j;
			}
			Run += Look_At;
			if(Run >= TheEnd)
				break;
			Run += Shift[(*Run)] - 1;
		}
	}
	return result;
}

__fastcall TSynEditSearch::~TSynEditSearch()
{
	delete fResults;
	//# inherited::Destroy();
}


void __fastcall TSynEditSearch::SetPattern(const String Value)
{
	if(Pat != Value)
	{
		CasedPat = Value;
		if(CaseSensitive)
			Pat = CasedPat;
		else
			Pat = Sysutils::AnsiLowerCase(CasedPat);
		fShiftInitialized = false;
	}
	FCount = 0;
}

void __fastcall TSynEditSearch::SetCaseSensitive(bool Value)
{
	if(FCaseSensitive != Value)
	{
		FCaseSensitive = Value;
		if(FCaseSensitive)
			Pat = CasedPat;
		else
			Pat = Sysutils::AnsiLowerCase(CasedPat);
		fShiftInitialized = false;
	}
}

int __fastcall TSynEditSearch::FindAll(const String NewText)
{
	int result = 0;
	int Found = 0;
  // never shrink Capacity
	fResults->Count = 0;
	Found = FindFirst(NewText);
	while(Found > 0)
	{
		fResults->Add(((void*) Found));
		Found = Next();
	}
	result = fResults->Count;
	return result;
}

String __fastcall TSynEditSearch::Replace(const String aOccurrence, const String aReplacement)
{
	String result;
	result = aReplacement;
	return result;
}

int __fastcall TSynEditSearch::FindFirst(const String NewText)
{
	int result = 0;
	if(!fShiftInitialized)
		InitShiftTable();
	result = 0;
	fTextLen = (int) NewText.Length();
	if(fTextLen >= PatLen)
	{
		if(CaseSensitive)
			FTextToSearch = NewText;
		else
			FTextToSearch = Sysutils::AnsiLowerCase(NewText);
		Origin = ustr2pwchar(FTextToSearch);
		TheEnd = Origin + fTextLen;
		Run = (Origin - 1);
		result = Next();
	}
	return result;
}

int __fastcall TSynEditSearch::GetLength(int Index)
{
	int result = 0;
	result = PatLen;
	return result;
}

String __fastcall TSynEditSearch::GetPattern()
{
	String result;
	result = CasedPat;
	return result;
}

void __fastcall TSynEditSearch::SetOptions(const TSynSearchOptions Value)
{
	CaseSensitive = Value.Contains(TSynSearchOption::ssoMatchCase);
	Whole = Value.Contains(TSynSearchOption::ssoWholeWord);
}


}  // namespace SynEditSearch

