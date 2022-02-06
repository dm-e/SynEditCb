#ifndef LongIntListH
#define LongIntListH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Messages.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>

namespace Longintlist
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/
Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: LongIntList.pas, released 2000-04-19.

The Original Code is based on mwTLongIntList.pas by Martin Waldenburg, part of
the mwEdit component suite.
Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
All Rights Reserved.

Contributors:

  For a list of the contributors to the mwEdit project see the
  accompanying Contributors.mwEdit.txt file.

$Id: LongIntList.pas,v 1.1.1.1.2.1 2006/12/12 07:37:55 etrusco Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
const int MaxListSize = (int)(System::MaxInt / 16);
typedef int TLongIntArray[134217728/*# range 0..MaxListSize*/];
typedef TLongIntArray* PLongIntArray;

class TLongintList : public System::TObject
{
	#include "LongIntList_friends.inc"
public:
	typedef TObject inherited;	
private:
	int FCapacity;
	int FCount;
	PLongIntArray FLongIntList;
protected:
	int __fastcall GetItems(int Index);
	void __fastcall SetCapacity(int NewCapacity);
	void __fastcall SetCount(int NewCount);
	void __fastcall SetItems(int Index, int Item);
public:
	__fastcall TLongintList();
	virtual __fastcall ~TLongintList();
	int __fastcall Add(int Item);
	void __fastcall Clear();
	void __fastcall Delete(int Index);
	void __fastcall Exchange(int Index1, int Index2);
	int __fastcall First();
	int __fastcall IndexOf(int Item);
	void __fastcall Insert(int Index, int Item);
	int __fastcall Last();
	void __fastcall Move(int CurIndex, int NewIndex);
	int __fastcall Remove(int Item);
	void __fastcall Sort();
	void __fastcall DeleteGroup(int StartIndex, int GroupCount);
	__property int Capacity = { read = FCapacity, write = SetCapacity };
	__property int Count = { read = FCount, write = SetCount };
	__property int Items[int Index] = { read = GetItems, write = SetItems/*# default */ };
	__property PLongIntArray LongIntList = { read = FLongIntList };
}; /* TLongIntList */


}  // namespace LongIntList

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Longintlist;
#endif

#endif // LongIntListH

