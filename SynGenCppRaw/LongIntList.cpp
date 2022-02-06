#include <vcl.h>
#pragma hdrstop

#include "LongIntList.h"

using namespace std;
using namespace d2c_system;
using namespace System;

namespace Longintlist
{



__fastcall TLongintList::TLongintList()
 : FCapacity(0),
			FCount(0),
			FLongIntList(nullptr)
{
	//# inherited::Create();
} /* Create */

__fastcall TLongintList::~TLongintList()
{
	Clear();
	//# inherited::Destroy();
}
 /* Destroy */

/* Based on a non-recursive QuickSort from the SWAG-Archive.
  ( TV Sorting Unit by Brad Williams ) */

void __fastcall TLongintList::Sort()
{
	int Left = 0;
	int Right = 0;
	int SubArray = 0;
	int SubLeft = 0;
	int SubRight = 0;
	int Temp = 0;
	int Pivot = 0;

	struct LongIntListRec__0
	{
		int First;
		int Last;
	};	
	LongIntListRec__0 Stack[32/*# range 1..32*/];
	if(Count > 1)
	{
		SubArray = 1;
		Stack[SubArray - 1].First = 0;
		Stack[SubArray - 1].Last = Count - 1;
		do
		{
			Left = Stack[SubArray - 1].First;
			Right = Stack[SubArray - 1].Last;
			--SubArray;
			do
			{
				SubLeft = Left;
				SubRight = Right;
				Pivot = (*FLongIntList)[(Left + Right) >> 1];
				do
				{
					while((*FLongIntList)[SubLeft] < Pivot)
						++SubLeft;
					while((*FLongIntList)[SubRight] > Pivot)
						--SubRight;
					if(SubLeft <= SubRight)
					{
						Temp = (*FLongIntList)[SubLeft];
						(*FLongIntList)[SubLeft] = (*FLongIntList)[SubRight];
						(*FLongIntList)[SubRight] = Temp;
						++SubLeft;
						--SubRight;
					}
				}
				while(!(SubLeft > SubRight));
				if(SubLeft < Right)
				{
					++SubArray;
					Stack[SubArray - 1].First = SubLeft;
					Stack[SubArray - 1].Last = Right;
				}
				Right = SubRight;
			}
			while(!(Left >= Right));
		}
		while(!(SubArray == 0));
	}
} /* Sort */

int __fastcall TLongintList::GetItems(int Index)
{
	int result = 0;
	result = (*FLongIntList)[Index];
	return result;
} /* GetItems */

void __fastcall TLongintList::SetCapacity(int NewCapacity)
{
	if(NewCapacity < FCount)
		FCount = NewCapacity;
	if(NewCapacity != FCapacity)
	{
		FLongIntList = (PLongIntArray) ReallocMemory(FLongIntList, NewCapacity * sizeof(int));
		FCapacity = NewCapacity;
	}
} /* SetCapacity */

void __fastcall TLongintList::SetCount(int NewCount)
{
	if(NewCount > FCapacity)
		SetCapacity(NewCount);
	FCount = NewCount;
} /* SetCount */

void __fastcall TLongintList::SetItems(int Index, int Item)
{
	(*FLongIntList)[Index] = Item;
} /* SetItems */

int __fastcall TLongintList::Add(int Item)
{
	int result = 0;
	result = FCount;
	if(result + 1 >= FCapacity)
		SetCapacity(FCapacity + 1024);
	(*FLongIntList)[result] = Item;
	++FCount;
	return result;
} /* Add */

void __fastcall TLongintList::Clear()
{
	SetCount(0);
	SetCapacity(0);
} /* Clear */

void __fastcall TLongintList::Delete(int Index)
{
	--FCount;
	if(Index < FCount)
		System::Move(&(*FLongIntList)[Index + 1], &(*FLongIntList)[Index], (FCount - Index) * sizeof(int));
} /* Delete */

void __fastcall TLongintList::DeleteGroup(int StartIndex, int GroupCount)
{
	FCount -= GroupCount;
	if(StartIndex < FCount)
		System::Move(&(*FLongIntList)[StartIndex + GroupCount], &(*FLongIntList)[StartIndex], (FCount - StartIndex) * sizeof(int));
} /* DeleteGroup */

void __fastcall TLongintList::Exchange(int Index1, int Index2)
{
	int Item = 0;
	Item = (*FLongIntList)[Index1];
	(*FLongIntList)[Index1] = (*FLongIntList)[Index2];
	(*FLongIntList)[Index2] = Item;
} /* Exchange */

int __fastcall TLongintList::First()
{
	int result = 0;
	result = GetItems(0);
	return result;
} /* First */

int __fastcall TLongintList::IndexOf(int Item)
{
	int result = 0;
	result = 0;
	while((result < FCount) && ((*FLongIntList)[result] != Item))
		++result;
	if(result == FCount)
		result = -1;
	return result;
} /* IndexOf */

void __fastcall TLongintList::Insert(int Index, int Item)
{
	if(FCount == FCapacity)
		SetCapacity(FCapacity + 1024);
	if(Index < FCount)
		System::Move(&(*FLongIntList)[Index], &(*FLongIntList)[Index + 1], (FCount - Index) * sizeof(int));
	(*FLongIntList)[Index] = Item;
	++FCount;
} /* Insert */

int __fastcall TLongintList::Last()
{
	int result = 0;
	result = GetItems(FCount - 1);
	return result;
} /* Last */

void __fastcall TLongintList::Move(int CurIndex, int NewIndex)
{
	int Item = 0;
	if(CurIndex != NewIndex)
	{
		Item = GetItems(CurIndex);
		Delete(CurIndex);
		Insert(NewIndex, Item);
	}
} /* Move */

int __fastcall TLongintList::Remove(int Item)
{
	int result = 0;
	result = IndexOf(Item);
	if(result !=  - 1)
		Delete(result);
	return result;
} /* Remove */


}  // namespace LongIntList

