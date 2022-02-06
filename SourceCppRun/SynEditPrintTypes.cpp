#include <vcl.h>
#pragma hdrstop

#include "SynEditPrintTypes.h"

using namespace std;
using namespace d2c_system;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;

namespace Syneditprinttypes
{

__fastcall TWrapPos::TWrapPos() {}



//Returns wrapping positions in AList.

bool __fastcall WrapTextEx(const String Line, TSysCharSet BreakChars, int MaxCol, System::Classes::TList* AList)
{
	bool result = false;
	TWrapPos* WrapPos = nullptr;
	int Pos = 0;
	int PreviousPos = 0;
	bool Found = false;
	if(Line.Length() <= MaxCol)
	{
		result = true;
		return result;
	}
	result = false;
	Pos = 1;
	PreviousPos = 0;
	WrapPos = new TWrapPos();
	while(Pos <= Line.Length())
	{
		Found = (Pos - PreviousPos > MaxCol) && (WrapPos->Index != 0);
		if(!Found && (Line[Pos] <= 65535 /*# High(Char) */) && CharInSet(Line[Pos], BreakChars)) // We found a possible break
			WrapPos->Index = Pos;
		if(Found)
		{
			result = true;
			AList->Add(WrapPos);
			PreviousPos = WrapPos->Index;

      // If more wraps needed and not end of line then a new wrap is created
			if(((Line.Length() - PreviousPos) > MaxCol) && (Pos < Line.Length()))
				WrapPos = new TWrapPos();
			else
				break;
		}
		Pos = Pos + 1;
	}
	if((AList->Count == 0) || (AList->Last() != WrapPos))
		delete WrapPos;
	return result;
}

//Integer to Roman - copied from SWAG

String __fastcall IntToRoman(int Value)
{
	String result;
	result = L"";
	while(Value >= 1000)
	{
		result = result + L"M";
		Value = Value - 1000;
	}
	if(Value >= 900)
	{
		result = result + L"CM";
		Value = Value - 900;
	}
	while(Value >= 500)
	{
		result = result + L"D";
		Value = Value - 500;
	}
	if(Value >= 400)
	{
		result = result + L"CD";
		Value = Value - 400;
	}
	while(Value >= 100)
	{
		result = result + L"C";
		Value = Value - 100;
	}
	if(Value >= 90)
	{
		result = result + L"XC";
		Value = Value - 90;
	}
	while(Value >= 50)
	{
		result = result + L"L";
		Value = Value - 50;
	}
	if(Value >= 40)
	{
		result = result + L"XL";
		Value = Value - 40;
	}
	while(Value >= 10)
	{
		result = result + L"X";
		Value = Value - 10;
	}
	if(Value >= 9)
	{
		result = result + L"IX";
		Value = Value - 9;
	}
	while(Value >= 5)
	{
		result = result + L"V";
		Value = Value - 5;
	}
	if(Value >= 4)
	{
		result = result + L"IV";
		Value = Value - 4;
	}
	while(Value > 0)
	{
		result = result + L"I";
		--Value;
	}
	return result;
}


}  // namespace SynEditPrintTypes

