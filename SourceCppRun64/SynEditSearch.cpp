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
using namespace System::Sysutils;

namespace Syneditsearch
{



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditSearch.pas, released 2000-04-07.

The Original Code is based on the mwEditSearch.pas file from the mwEdit
component suite by Martin Waldenburg and other developers.
Portions created by Martin Waldenburg are Copyright 1999 Martin Waldenburg.
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

$Id: SynEditSearch.pas,v 1.12.2.6 2009/09/29 00:16:46 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

__fastcall TSynEditSearch::TSynEditSearch(TComponent* aOwner)
 : inherited(aOwner),
			Run(nullptr),
			Origin(nullptr),
			TheEnd(nullptr),
			fCount(0),
			fTextLen(0),
			Look_At(0),
			PatLen(0),
			PatLenSucc(0),
			fCaseSensitive(false),
			fWhole(false),
			fResults(nullptr),
			fShiftInitialized(false)
{
	fResults = new TList();
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
		result = (NativeInt)fResults->Items[Index];
	return result;
}

int __fastcall TSynEditSearch::GetResultCount()
{
	int result = 0;
	result = fResults->Count;
	return result;
}

void __fastcall TSynEditSearch::FixResults(int First, int Delta)
{
	int i = 0;
	if((Delta != 0) && (fResults->Count > 0))
	{
		i = Pred(fResults->Count);
		while(i >= 0)
		{
			if((NativeInt)fResults->Items[i] <= First)
				break;
			fResults->Items[i] = ((void*) ((NativeInt)fResults->Items[i] - Delta));
			--i;
		}
	}
}

void __fastcall TSynEditSearch::InitShiftTable()
{

	int C = 0;
	int I = 0;
	int stop = 0;
	PatLen = Pat.Length();
	if(PatLen == 0)
		throw Exception(L"Pattern is empty");
	PatLenSucc = PatLen + 1;
	Look_At = 1;
	for(stop = High<WideChar>(), C = Low<WideChar>(); C <= stop; C++)
	{
		Shift[C] = PatLenSucc;
	}
	for(stop = PatLen, I = 1; I <= stop; I++)
	{
		Shift[Pat[I]] = PatLenSucc - I;
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
		case L'´':
		case L'`':
		case L'°':
		case L'^':
		case L'!':
		case L'?':
		case L'&':
		case L'$':
		case L'@':
		case L'§':
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
	int I = 0;
	PWideChar J = nullptr;
	result = 0;
	Run += PatLen;
	while(Run < TheEnd)
	{
		if(Pat[PatLen] != (*Run))
			Run += Shift[(*(Run + 1))];
		else
		{
			J = Run - PatLen + 1;
			I = 1;
			while(Pat[I] == (*J))
			{
				if(I == PatLen)
				{
					if(fWhole && !TestWholeWord())
						break;
					++fCount;
					result = Run - Origin - PatLen + 2;
					return result;
				}
				++I;
				++J;
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
	if(CasedPat != Value)  // dme
	{
		CasedPat = Value;
		if(CaseSensitive)
			Pat = CasedPat;
		else
			Pat = Sysutils::AnsiLowerCase(CasedPat);
		fShiftInitialized = false;
	}
	fCount = 0;
}

void __fastcall TSynEditSearch::SetCaseSensitive(bool Value)
{
	if(fCaseSensitive != Value)
	{
		fCaseSensitive = Value;
		if(fCaseSensitive)
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
	fTextLen = NewText.Length();
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
	CaseSensitive = Value.Contains(ssoMatchCase);
	Whole = Value.Contains(ssoWholeWord);
}


}  // namespace Syneditsearch

