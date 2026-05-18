#include <vcl.h>
#pragma hdrstop

#include "LongIntList.h"

using namespace std;
using namespace d2c_system;
using namespace System;

namespace Longintlist
{



__fastcall TLongIntList::TLongIntList()
 : FCapacity(0),
			FCount(0),
			FLongIntList(nullptr)
{
	//# inherited::Create();
} /* Create */

__fastcall TLongIntList::~TLongIntList()
{
	Clear();
	//# inherited::Destroy();
} /* Destroy */

/* Based on a non-recursive QuickSort from the SWAG-Archive.
  ( TV Sorting Unit by Brad Williams ) */

void __fastcall TLongIntList::Sort()
{
	int Left = 0;
	int Right = 0;
	int SubArray = 0;
	int SubLeft = 0;
	int SubRight = 0;
	int Temp = 0;
	int Pivot = 0;

	struct LongintlistRec__0
	{
		int First;
		int Last;
	};	
	LongintlistRec__0 Stack[32/*# range 1..32*/];
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

int __fastcall TLongIntList::GetItems(int Index)
{
	int result = 0;
	result = (*FLongIntList)[Index];
	return result;
} /* GetItems */

void __fastcall TLongIntList::SetCapacity(int NewCapacity)
{
	if(NewCapacity < FCount)
		FCount = NewCapacity;
	if(NewCapacity != FCapacity)
	{
		FLongIntList = (PLongIntArray) ReallocMemory(FLongIntList, NewCapacity * sizeof(int));
		FCapacity = NewCapacity;
	}
} /* SetCapacity */

void __fastcall TLongIntList::SetCount(int NewCount)
{
	if(NewCount > FCapacity)
		SetCapacity(NewCount);
	FCount = NewCount;
} /* SetCount */

void __fastcall TLongIntList::SetItems(int Index, int Item)
{
	(*FLongIntList)[Index] = Item;
} /* SetItems */

int __fastcall TLongIntList::Add(int Item)
{
	int result = 0;
	result = FCount;
	if(result + 1 >= FCapacity)
		SetCapacity(FCapacity + 1024);
	(*FLongIntList)[result] = Item;
	++FCount;
	return result;
} /* Add */

void __fastcall TLongIntList::Clear()
{
	SetCount(0);
	SetCapacity(0);
} /* Clear */

void __fastcall TLongIntList::Delete(int Index)
{
	--FCount;
	if(Index < FCount)
		System::Move(&(*FLongIntList)[Index + 1], &(*FLongIntList)[Index], static_cast<size_t>((FCount - Index) * sizeof(int)));
} /* Delete */

void __fastcall TLongIntList::DeleteGroup(int StartIndex, int GroupCount)
{
	FCount -= GroupCount;
	if(StartIndex < FCount)
		System::Move(&(*FLongIntList)[StartIndex + GroupCount], &(*FLongIntList)[StartIndex], static_cast<size_t>((FCount - StartIndex) * sizeof(int)));
} /* DeleteGroup */

void __fastcall TLongIntList::Exchange(int Index1, int Index2)
{
	int Item = 0;
	Item = (*FLongIntList)[Index1];
	(*FLongIntList)[Index1] = (*FLongIntList)[Index2];
	(*FLongIntList)[Index2] = Item;
} /* Exchange */

int __fastcall TLongIntList::First()
{
	int result = 0;
	result = GetItems(0);
	return result;
} /* First */

int __fastcall TLongIntList::IndexOf(int Item)
{
	int result = 0;
	result = 0;
	while((result < FCount) && ((*FLongIntList)[result] != Item))
		++result;
	if(result == FCount)
		result = -1;
	return result;
} /* IndexOf */

void __fastcall TLongIntList::Insert(int Index, int Item)
{
	if(FCount == FCapacity)
		SetCapacity(FCapacity + 1024);
	if(Index < FCount)
		System::Move(&(*FLongIntList)[Index], &(*FLongIntList)[Index + 1], static_cast<size_t>((FCount - Index) * sizeof(int)));
	(*FLongIntList)[Index] = Item;
	++FCount;
} /* Insert */

int __fastcall TLongIntList::Last()
{
	int result = 0;
	result = GetItems(FCount - 1);
	return result;
} /* Last */

void __fastcall TLongIntList::Move(int CurIndex, int NewIndex)
{
	int Item = 0;
	if(CurIndex != NewIndex)
	{
		Item = GetItems(CurIndex);
		Delete(CurIndex);
		Insert(NewIndex, Item);
	}
} /* Move */

int __fastcall TLongIntList::Remove(int Item)
{
	int result = 0;
	result = IndexOf(Item);
	if(result != -1)
		Delete(result);
	return result;
} /* Remove */


}  // namespace Longintlist

