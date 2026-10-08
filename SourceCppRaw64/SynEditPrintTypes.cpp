#include <vcl.h>
#pragma hdrstop

#include "SynEditPrintTypes.h"

using namespace std;
using namespace d2c_system;
using namespace System;

namespace Syneditprinttypes
{

__fastcall TWrapPos::TWrapPos() {}



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPrintTypes.pas, released 2000-06-01.

The Initial Author of the Original Code is Morten J. Skovrup.
Portions written by Morten J. Skovrup are copyright 2000 Morten J. Skovrup.
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

$Id: SynEditPrintTypes.pas,v 1.4.2.3 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
  Wrapping across page boundaries is not supported
-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
CONTENTS:
  Misc types and procedures used in printing and previewing
-------------------------------------------------------------------------------*/


//Returns wrapping positions in AList.

bool __fastcall WrapTextEx(const String Line, TSysCharSet BreakChars, int MaxCol, TList* AList)
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


}  // namespace Syneditprinttypes

