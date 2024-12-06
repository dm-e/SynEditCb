#include <vcl.h>
#pragma hdrstop

#include "SynSpellCheckMetaphone.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synunicode;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;

namespace Synspellcheckmetaphone
{

 // If FromStr is at begining of word
 // If FromStr is just after arg
 // If FromStr is just before arg
 // If FromStr is not preceded by vowel
 // If FromStr is not followed by vowel
 // If FromStr is between two chars specified in Args
 // Not at end of word after string in Args
 // Not at end of word just before string in args
 // Before "args", but no vowel thereafter
 // After, but not before vowel
 // At end of word just bofore "Arg"
enum TRuleType {mrBeginningOfWord,
                mrAfter,
                mrBefore,
                mrNotAfterVowel,
                mrNotBeforeVowel,
                mrBetween,
                mrNotEndAfter,
                mrNotEndBefore,
                mrBeforeNoVowel,
                mrAfterVowelNotBeforeVowel,
                mrAtEndBefore,
                mrNone };
 // Rule always applies

struct TRule
{
	UnicodeString sFrom;
	UnicodeString sTo;
	TRuleType RuleType;
	UnicodeString Args;
};
const int RuleCount = 67;

  // Note - always make the default rule the LAST
const TRule Rules[67/*# range 1..RuleCount*/] = {{(L"AE"), (L"E"), mrBeginningOfWord, (L"")}
                    ,                     {(L"GN"), (L"N"), mrBeginningOfWord, (L"")}
                    ,                     {(L"KN"), (L"N"), mrBeginningOfWord, (L"")}
                    ,                     {(L"PN"), (L"N"), mrBeginningOfWord, (L"")}
                    ,                     {(L"WR"), (L"R"), mrBeginningOfWord, (L"")}
                    ,                     {(L"PS"), (L"S"), mrBeginningOfWord, (L"")}
                    ,                     {(L"WH"), (L"W"), mrBeginningOfWord, (L"")}
      // 8 rules
    // B
                    ,                     {(L"B"), (L"B"), mrNotEndAfter, (L"M")}
                    ,                     {(L"B"), (L"B"), mrNone, (L"")}
    // C
                    ,                     {(L"C"), (L"X"), mrBetween, (L"CA")}
                    ,                     {(L"C"), (L"X"), mrBefore, (L"H")}
                    ,                     {(L"C"), (L"S"), mrBefore, (L"I")}
                    ,                     {(L"C"), (L"S"), mrBefore, (L"E")}
                    ,                     {(L"C"), (L"S"), mrBefore, (L"Y")}
                    ,                     {(L"C"), (L""), mrBetween, (L"SE")}
                    ,                     {(L"C"), (L""), mrBetween, (L"SI")} // 10
                    ,                     {(L"C"), (L"K"), mrNone, (L"")}
    // D
                    ,                     {(L"D"), (L"J"), mrBefore, (L"GE")}
                    ,                     {(L"D"), (L"J"), mrBefore, (L"GY")}
                    ,                     {(L"D"), (L"J"), mrBefore, (L"GI")}
                    ,                     {(L"D"), (L"T"), mrNone, (L"")}
    //F
                    ,                     {(L"F"), (L"F"), mrNone, (L"")}
    // GG - changed to "1" in phase 1
                    ,                     {(L"1"), (L"K"), mrNone, (L"")}
    // G
                    ,                     {(L"G"), (L"G"), mrBefore, (L"G")}
                    ,                     {(L"G"), (L""), mrAfter, (L"G")}
                    ,                     {(L"G"), (L""), mrBeforeNoVowel, (L"H")}
                    ,                     {(L"G"), (L""), mrAtEndBefore, (L"N")}
                    ,                     {(L"G"), (L""), mrAtEndBefore, (L"NED")}
                    ,                     {(L"G"), (L""), mrBetween, (L"DE")}
      // Paired with D rule
                    ,                     {(L"G"), (L"J"), mrBefore, (L"I")}
                    ,                     {(L"G"), (L"J"), mrBefore, (L"E")}
                    ,                     {(L"G"), (L"J"), mrBefore, (L"Y")}
                    ,                     {(L"G"), (L"K"), mrNone, (L"")} // 16
    // H
                    ,                     {(L"H"), (L""), mrAfterVowelNotBeforeVowel, (L"")}
                    ,                     {(L"H"), (L""), mrAfter, (L"C")}
                    ,                     {(L"H"), (L""), mrAfter, (L"S")}
                    ,                     {(L"H"), (L""), mrAfter, (L"P")}
                    ,                     {(L"H"), (L""), mrAfter, (L"T")}
                    ,                     {(L"H"), (L""), mrAfter, (L"G")}
                    ,                     {(L"H"), (L""), mrNone, (L"")}
    // J
                    ,                     {(L"J"), (L"J"), mrNone, (L"")}
    // K
                    ,                     {(L"K"), (L""), mrAfter, (L"C")}
                    ,                     {(L"K"), (L"K"), mrNone, (L"")} // 10
    // L
                    ,                     {(L"L"), (L"L"), mrNone, (L"")}
    // M
                    ,                     {(L"M"), (L"M"), mrNone, (L"")}
    // N
                    ,                     {(L"N"), (L"N"), mrNone, (L"")}
    // P
                    ,                     {(L"P"), (L"F"), mrBefore, (L"H")}
                    ,                     {(L"P"), (L"P"), mrNone, (L"")}
    // Q
                    ,                     {(L"Q"), (L"K"), mrNone, (L"")}
    // R
                    ,                     {(L"R"), (L"R"), mrNone, (L"")}
    // S
                    ,                     {(L"S"), (L"X"), mrBefore, (L"H")}
                    ,                     {(L"S"), (L"X"), mrBetween, (L"SO")}
                    ,                     {(L"S"), (L"X"), mrBetween, (L"SA")}
                    ,                     {(L"S"), (L"S"), mrNone, (L"")} //11
    // T
                    ,                     {(L"T"), (L"X"), mrBefore, (L"IA")}
                    ,                     {(L"T"), (L"X"), mrBefore, (L"IO")}
                    ,                     {(L"T"), (L""), mrBefore, (L"CH")}
                    ,                     {(L"T"), (L"0"), mrBefore, (L"H")}
                    ,                     {(L"T"), (L"T"), mrNone, (L"")}
    // V
                    ,                     {(L"V"), (L"F"), mrNone, (L"")}
    // W
                    ,                     {(L"W"), (L"W"), mrNotBeforeVowel, (L"")}
                    ,                     {(L"W"), (L""), mrNone, (L"")}
    // X
                    ,                     {(L"X"), (L"S"), mrBeginningOfWord, (L"")}
                    ,                     {(L"X"), (L"KS"), mrNone, (L"")}
    // Y
                    ,                     {(L"Y"), (L"Y"), mrNotBeforeVowel, (L"")}
                    ,                     {(L"Y"), (L""), mrNone, (L"")}
    // Z
                    ,                     {(L"Z"), (L"S"), mrNone, (L"")}}; // 12
const WideChar AllowChar[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const WideChar Vowels[] = L"AEIOU";
TStringList* OutStr;

void __fastcall ApplyRules(UnicodeString ScanStr, const TRule* RuleBase, int RuleBase_maxidx)
{

	auto RuleApplicable = [&](const TRule& cRule, int CharIndex) -> bool 
	{
		TRule Rule = cRule;
		bool result = false;
		int RemChar = 0;
		int PrevChar = 0;
		int ArgLength = 0;
		int InpLength = 0;
		InpLength = ScanStr.Length();
		RemChar = InpLength - CharIndex;
		PrevChar = CharIndex - 1;
		ArgLength = Rule.Args.Length();
		result = false;
		if(((RemChar + 1) >= Rule.sFrom.Length()) && (ScanStr.SubString(CharIndex, Rule.sFrom.Length()) == Rule.sFrom))
			switch(Rule.RuleType)
			{
				case mrBeginningOfWord:
				if(CharIndex == 1) //if sFrom is at beggining of word
					result = true;
				break; //If sFrom is just after arg
				case mrAfter:
				if((PrevChar >= ArgLength) && (ScanStr.SubString(CharIndex - ArgLength - 1, ArgLength) == Rule.Args))
					result = true;
				break; //If sFrom is just before arg
				case mrBefore:
				if((RemChar >= ArgLength) && (ScanStr.SubString(CharIndex + 1, ArgLength) == Rule.Args))
					result = true;
				break; //If sFrom is not preceded by vowel
				case mrNotAfterVowel:
				if((RemChar >= 1) && (Pos(ScanStr.SubString(CharIndex + 1, 1), String(Vowels)) > 0))
					result = true;
				break; //If sFrom is not followed by vowel
				case mrNotBeforeVowel:
				if((PrevChar >= 1) && (Pos(ScanStr.SubString(CharIndex + 1, 1), String(Vowels)) > 0))
					result = true;
				break; //If sFrom is between two chars specified in Args
				case mrBetween:
				if((PrevChar >= 1) && (RemChar >= 1) && (Rule.Args.Length() == 2) && (ScanStr.SubString(CharIndex - 1, 1) == Rule.Args.SubString(1, 1)) && (ScanStr.SubString(CharIndex + 1, 1) == Rule.Args.SubString(2, 1)))
					result = true;
				break; //Not at end of word after string in Args
				case mrNotEndAfter:
				if((CharIndex < InpLength) && (PrevChar >= Rule.Args.Length()) && (ScanStr.SubString(CharIndex - ArgLength - 1, ArgLength) == Rule.Args))
					result = true;
				break; //Not at end of word just before string in args
				case mrNotEndBefore:
				if((ArgLength > RemChar) && (ScanStr.SubString(CharIndex + 1, ArgLength) == Rule.Args))
					result = true;
				break; //Before "args", but no vowel thereafter
				case mrBeforeNoVowel:
				if((ArgLength + 1 <= RemChar) && (ScanStr.SubString(CharIndex + 1, ArgLength) == Rule.Args) && (Pos(Vowels, ScanStr.SubString(CharIndex + 1 + ArgLength, 1)) > 0))
					result = true;
				break; //after, but not before vowel
				case mrAfterVowelNotBeforeVowel:
				if((PrevChar > 0) && (RemChar > 0) && (Pos(Vowels, ScanStr.SubString(CharIndex - 1, 1)) > 0) && (Pos(Vowels, ScanStr.SubString(CharIndex + 1, 1)) == 0))
					result = true;
				break; //At end of word just before "Arg"
				case mrAtEndBefore:
				if((ArgLength == RemChar) && (ScanStr.SubString(CharIndex + 1, ArgLength) == Rule.Args))
					result = true;
				break; //Rule always applies
				case mrNone:
				result = true;
				break;
				default:
				  ;
				break;
			} //case
		return result;
	}; //function RuleApplicable
	int iI = 0;
	int t = 0;
	UnicodeString SkipRule;
	bool SkipFlag = false;
	t = 0 /*# Low(RuleBase) */;
	while(t <= RuleBase_maxidx /*# High(RuleBase) */)
	{
		int stop = 0;
		SkipFlag = false;
		for(stop = ScanStr.Length(), iI = 1; iI <= stop; iI++)
		{
			if(RuleApplicable(RuleBase[t], iI))
			{
				OutStr->AddObject(RuleBase[t].sTo, ((TObject*) iI));
				SkipFlag = true;
				SkipRule = RuleBase[t].sFrom;
			}
		}
		if(SkipFlag)
		{
			while(RuleBase[t].sFrom == SkipRule)
				++t;
		}
		else
		++t; // Normal increment
	}
}

UnicodeString __fastcall FindRel(int xx)
{
	UnicodeString result;
	int iI = 0;
	int stop = 0;
	for(stop = OutStr->Count - 1, iI = 0; iI <= stop; iI++)
	{
		if(((int) OutStr->Objects[iI]) == xx)
			result = result + Format(L"%3.3s %d ", ARRAYOFCONST((OutStr[iI], iI)));
	}
	return result;
}

PWideChar __stdcall metaphone(PWideChar a, int lg)
{
	PWideChar result = nullptr;
	UnicodeString sResult;
	UnicodeString InStr;
	UnicodeString TempStr;
	int x = 0;
	int y = 0;
	int SmallestIndex = 0;
	int SmallestValue = 0; //for selection sort
	bool FirstFlag = false;
	OutStr = new TStringList();
	try
	{
		int stop = 0;
		TempStr = WideUpperCase(a);
		InStr = L"";
		for(stop = TempStr.Length(), x = 1; x <= stop; x++)
		{
			if(Pos(TempStr.SubString(x, 1), String(AllowChar)) > 0)
				InStr = InStr + TempStr.SubString(x, 1);
		}

    //remove doubles EXCEPT FOR G (ugly exception)
		if(InStr.Length() > 0)
		{
			int stop = 0;
			TempStr = InStr.SubString(1, 1);
			for(stop = InStr.Length(), x = 2; x <= stop; x++)
			{
				if(InStr.SubString(x, 1) == L"G")
					TempStr = TempStr + InStr.SubString(x, 1);
				else
				{
					if(InStr.SubString(x, 1) != InStr.SubString(x - 1, 1))
						TempStr = TempStr + InStr.SubString(x, 1);
				}
			}
			InStr = TempStr;
		}

    //scan input and create result for each rule in output array
		ApplyRules(InStr, Rules, 66);

    //get result - order output stringlist, then translate to string
    //do selection sort - or something like that, anyway :-)
		for(stop = OutStr->Count - 1, x = 0; x <= stop; x++)
		{
			int stop1 = 0;
			SmallestIndex = x;
			SmallestValue = ((int) OutStr->Objects[x]);
			for(stop1 = OutStr->Count - 1, y = x; y <= stop1; y++)
			{
				if(((int) OutStr->Objects[y]) < SmallestValue)
				{
					SmallestIndex = y;
					SmallestValue = ((int) OutStr->Objects[y]);
				}
			}
			if(SmallestIndex > x) //do swap with smallest
				OutStr->Exchange(x, SmallestIndex);
		}
		FirstFlag = false;
		for(stop = OutStr->Count - 1, x = 0; x <= stop; x++)
		{
			sResult = sResult + OutStr->Strings[x];
			if(((int) OutStr->Objects[x]) == 1)
				FirstFlag = true;
		}

    //the following is a fix for words beginning with vowels
    //if there isn't a translation of the first character,
    //it adds whatever the first character is
		if((!FirstFlag) && (InStr.Length() > 0))
			sResult = InStr.SubString(1, 1) + sResult;
		result = ustr2pwchar(sResult);
	}
	__finally
	{
		delete OutStr;
	}
	return result;
}


}  // namespace SynSpellCheckMetaphone

