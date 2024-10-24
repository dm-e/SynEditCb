#include <vcl.h>
#pragma hdrstop

#include "SynEditUndo.h"
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Math.hpp>
#include <System.Generics.Collections.hpp>
#include <Vcl.Controls.hpp>
#include "SynEditTextBuffer.h"
#include "SynEditDelphiInstances.hpp"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Syneditkeycmds;
using namespace Synedittextbuffer;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Generics::Collections;
using namespace System::Math;
using namespace System::Sysutils;
using namespace Vcl::Controls;

namespace Syneditundo
{
#define Syneditundo__0 (TPlugInHandlers() << phLinePut << phLinesInserted << phLinesBeforeDeleted << phLinesDeleted)
#define Syneditundo__1 (TSynLineChangeFlags() << sfModified)


class DELPHICLASS TSynEditUndo;

class TSynLinePutUndoItem : public TSynUndoItem
{
	#include "SynEditUndo_friends.inc"
public:
	typedef TSynUndoItem inherited;
private:
	int FIndex;
	int FStartPos;
	String FOldValue;
	String FNewValue;
	TSynLineChangeFlags FChangeFlags;
	TSynEditorCommand FCommandProcessed;
public:
	bool __fastcall GroupWith(TSynLinePutUndoItem* Item);
	virtual void __fastcall Undo(TCustomSynEdit* Editor);
	virtual void __fastcall Redo(TCustomSynEdit* Editor);
	__fastcall TSynLinePutUndoItem(TCustomSynEdit* Editor, int Index, String OldLine, TSynEditorCommand Command);
	__fastcall TSynLinePutUndoItem() {}
};

class TSynLinesInsertedUndoItem : public TSynUndoItem
{
	#include "SynEditUndo_friends.inc"
public:
	typedef TSynUndoItem inherited;
private:
	int FIndex;
	System::TArray<String> FLines;
public:
	virtual void __fastcall Undo(TCustomSynEdit* Editor);
	virtual void __fastcall Redo(TCustomSynEdit* Editor);
	__fastcall TSynLinesInsertedUndoItem(TCustomSynEdit* Editor, int Index, int Count);
	__fastcall TSynLinesInsertedUndoItem() {}
};

class TSynLinesDeletedUndoItem : public TSynUndoItem
{
	#include "SynEditUndo_friends.inc"
public:
	typedef TSynUndoItem inherited;
private:
	int FIndex;
	System::TArray<String> FLines;
public:
	virtual void __fastcall Undo(TCustomSynEdit* Editor);
	virtual void __fastcall Redo(TCustomSynEdit* Editor);
	__fastcall TSynLinesDeletedUndoItem(TCustomSynEdit* Editor, int Index, System::TArray<String>& DeletedLines);
	__fastcall TSynLinesDeletedUndoItem() {}
};

class TSynCaretAndSelectionUndoItem : public TSynUndoItem
{
	#include "SynEditUndo_friends.inc"
public:
	typedef TSynUndoItem inherited;
private:
	TBufferCoord FBlockBegin;
	TBufferCoord FBlockEnd;
public:
	virtual void __fastcall Undo(TCustomSynEdit* Editor);
	virtual void __fastcall Redo(TCustomSynEdit* Editor);
	__fastcall TSynCaretAndSelectionUndoItem(TCustomSynEdit* Editor);
	__fastcall TSynCaretAndSelectionUndoItem() {}
};

class TSynUndoPlugin : public TSynEditPlugin
{
	#include "SynEditUndo_friends.inc"
public:
	typedef TSynEditPlugin inherited;
private:
	TSynEditUndo* FSynEditUndo;
	System::TArray<String> FDeletedLines;
protected:
	virtual void __fastcall LinesInserted(int FirstLine, int Count);
	virtual void __fastcall LinesBeforeDeleted(int FirstLine, int Count);
	virtual void __fastcall LinesDeleted(int FirstLine, int Count);
	virtual void __fastcall LinePut(int aIndex, const String OldLine);
public:
	__fastcall TSynUndoPlugin(TSynEditUndo* SynEditUndo, TCustomSynEdit* Editor);
	__fastcall TSynUndoPlugin(TCustomSynEdit* AOwner) : inherited(AOwner) {}
	__fastcall TSynUndoPlugin(TCustomSynEdit* AOwner, TPlugInHandlers AHandlers) : inherited(AOwner, AHandlers) {}
	__fastcall TSynUndoPlugin() {}
};

class TSynEditUndoList : public TObjectStack__1<TSynUndoItem*>
{
	#include "SynEditUndo_friends.inc"
public:
	typedef TObjectStack__1<TSynUndoItem*> inherited;
protected:
	TSynEditUndo* FOwner;
	int FBlockChangeNumber;
	int FNextChangeNumber;
	bool FFullUndoImposible;
	void __fastcall EnsureMaxEntries();
	int __fastcall NextChangeNumber();
public:
	__fastcall TSynEditUndoList(TSynEditUndo* Owner);
	void __fastcall Push(TSynUndoItem* const Value);
	__property int BlockChangeNumber = { read = FBlockChangeNumber, write = FBlockChangeNumber };
	__fastcall TSynEditUndoList() {}
	__fastcall TSynEditUndoList(bool AOwnsObjects) : inherited(AOwnsObjects) {}
	__fastcall TSynEditUndoList(TEnumerable__1<TSynUndoItem*>* const Collection, bool AOwnsObjects = true) : inherited(Collection, AOwnsObjects) {}
	__fastcall TSynEditUndoList(IEnumerable__1<TSynUndoItem*>* const Collection) : inherited(Collection) {}
};

class TSynEditUndo : public TCppInterfacedObject<ISynEditUndo>
{
	#include "SynEditUndo_friends.inc"
public:
	typedef TCppInterfacedObject<ISynEditUndo> inherited;
private:
	TSynUndoPlugin* FPlugin;
	bool FGroupUndo;
	int FBlockCount;
	int FLockCount;
	int FInitialChangeNumber;
	int FMaxUndoActions;
	bool FBlockStartModified;
	TSynEditUndoList* FUndoList;
	TSynEditUndoList* FRedoList;
	TNotifyEvent FOnModifiedChanged;
	bool FInsideUndoRedo;
	TSynEditorCommand FCommandProcessed;
	TSynUndoItem* FBlockSelRestoreItem;
	bool __fastcall GetModified();
	bool __fastcall GetCanUndo();
	bool __fastcall GetCanRedo();
	bool __fastcall GetFullUndoImposible();
	TNotifyEvent __fastcall GetOnModifiedChanged();
	void __fastcall SetModified(bool Value);
	void __fastcall SetCommandProcessed(TSynEditorCommand Command);
	void __fastcall SetMaxUndoActions(int Value);
	void __fastcall SetOnModifiedChanged(const TNotifyEvent Value);
	void __fastcall SetGroupUndo(bool Value);
	int __fastcall GetMaxUndoActions();
	void __fastcall BeginBlock(TControl* Editor);
	void __fastcall EndBlock(TControl* Editor);
	void __fastcall Lock();
	void __fastcall Unlock();
	bool __fastcall IsLocked();
	void __fastcall Clear();
	void __fastcall Undo(TControl* Editor);
	void __fastcall Redo(TControl* Editor);
	void __fastcall AddGroupBreak();
	void __fastcall AddUndoItem(TSynUndoItem* Item);
public:
	__fastcall TSynEditUndo(TCustomSynEdit* Editor);
	virtual __fastcall ~TSynEditUndo();
	__fastcall TSynEditUndo() {}
};

/* TSynEditUndoList */

__fastcall TSynEditUndoList::TSynEditUndoList(TSynEditUndo* Owner)
 : inherited(true),
			FOwner(Owner),
			FBlockChangeNumber(0),
			FNextChangeNumber(0),
			FFullUndoImposible(false)
{
	FNextChangeNumber = 1;
}

void __fastcall TSynEditUndoList::EnsureMaxEntries()
{
	int KeepCount = 0;
	System::TArray<TSynUndoItem*> ItemArray;
	__int64 I = 0;
	if(FOwner->FMaxUndoActions <= 0)
		return;
	if(Count > FOwner->FMaxUndoActions)
	{
		__int64 stop = 0;
		FFullUndoImposible = true;
		KeepCount = ((int)(FOwner->FMaxUndoActions / /*div*/ 4)) * 3;
		ItemArray = ToArray();
		for(stop = KeepCount, I = 1; I <= stop; I++)
		{
			Extract();
		}
		Clear();  // Destroys remaining items
		for(stop = ItemArray.Length - 1, I = ItemArray.Length - KeepCount; I <= stop; I++)
		{
			Push(ItemArray[I]);
		}
	}
}

int __fastcall TSynEditUndoList::NextChangeNumber()
{
	int result = 0;
	result = FNextChangeNumber;
	++FNextChangeNumber;
	return result;
}

void __fastcall TSynEditUndoList::Push(TSynUndoItem* const Value)
{
	if(FBlockChangeNumber != 0)
		Value->ChangeNumber = FBlockChangeNumber;
	else
		Value->ChangeNumber = NextChangeNumber();
	inherited::Push(Value);
	EnsureMaxEntries();
}

/* TSynEditUndo */

void __fastcall TSynEditUndo::AddUndoItem(TSynUndoItem* Item)
{
	bool OldModified = false;
	Assert(!FInsideUndoRedo);
	OldModified = GetModified();
	FUndoList->Push(Item);
	FRedoList->Clear();
  // Do not sent unnecessary notifications
	if((FBlockCount == 0) && (OldModified ^ GetModified()) && ASSIGNED(FOnModifiedChanged))
		FOnModifiedChanged(this);
}

void __fastcall TSynEditUndo::AddGroupBreak()
{
	if((FUndoList->Count > 0) && (FBlockCount == 0))
		FUndoList->Peek()->GroupBreak = true;
}

void __fastcall TSynEditUndo::BeginBlock(TControl* Editor)
{
	++FBlockCount;
	if(FBlockCount == 1) // it was 0
	{
		FBlockStartModified = GetModified();
		FUndoList->FBlockChangeNumber = FUndoList->NextChangeNumber();
    // So that position is restored after Redo
		FBlockSelRestoreItem = new TSynCaretAndSelectionUndoItem((TCustomSynEdit*) Editor);
		FUndoList->Push(FBlockSelRestoreItem);
	}
}

void __fastcall TSynEditUndo::Clear()
{
	FUndoList->Clear();
	FRedoList->Clear();
}

__fastcall TSynEditUndo::TSynEditUndo(TCustomSynEdit* Editor)
 : FPlugin(new TSynUndoPlugin(this, Editor)),
			FGroupUndo(false),
			FBlockCount(0),
			FLockCount(0),
			FInitialChangeNumber(0),
			FMaxUndoActions(0),
			FBlockStartModified(false),
			FUndoList(nullptr),
			FRedoList(nullptr),
			FInsideUndoRedo(false),
			FCommandProcessed(0),
			FBlockSelRestoreItem(nullptr)
{
	//# inherited::Create();
	FGroupUndo = true;
	FMaxUndoActions = 0;
	FUndoList = new TSynEditUndoList(this);
	FRedoList = new TSynEditUndoList(this);
}

__fastcall TSynEditUndo::~TSynEditUndo()
{
	delete FUndoList;
	delete FRedoList;
	// inherited;
}

void __fastcall TSynEditUndo::EndBlock(TControl* Editor)
{
	TSynCaretAndSelectionUndoItem* Item = nullptr;
	Assert(FBlockCount > 0);
	if(FBlockCount > 0)
	{
		--FBlockCount;
		if(FBlockCount == 0)
		{
			if(FUndoList->Peek() == FBlockSelRestoreItem)
        // No undo items added from BlockBegin to BlockEnd
				FUndoList->Pop();
			else

        // So that position is restored after Redo
			{
				Item = new TSynCaretAndSelectionUndoItem((TCustomSynEdit*) Editor);
				FUndoList->Push(Item);
			}
			FUndoList->FBlockChangeNumber = 0;
			AddGroupBreak();
			if(FBlockStartModified ^ GetModified() && ASSIGNED(FOnModifiedChanged))
				FOnModifiedChanged(this);
		}
	}
}

bool __fastcall TSynEditUndo::GetCanUndo()
{
	bool result = false;
	result = FUndoList->Count > 0;
	return result;
}

bool __fastcall TSynEditUndo::GetFullUndoImposible()
{
	bool result = false;
	result = FUndoList->FFullUndoImposible;
	return result;
}

int __fastcall TSynEditUndo::GetMaxUndoActions()
{
	int result = 0;
	result = FMaxUndoActions;
	return result;
}

bool __fastcall TSynEditUndo::GetModified()
{
	bool result = false;
	if(FUndoList->Count == 0)
		result = FInitialChangeNumber != 0;
	else
		result = FUndoList->Peek()->ChangeNumber != FInitialChangeNumber;
	return result;
}

TNotifyEvent __fastcall TSynEditUndo::GetOnModifiedChanged()
{
	TNotifyEvent result;
	result = FOnModifiedChanged;
	return result;
}

bool __fastcall TSynEditUndo::IsLocked()
{
	bool result = false;
	result = FLockCount > 0;
	return result;
}

bool __fastcall TSynEditUndo::GetCanRedo()
{
	bool result = false;
	result = FRedoList->Count > 0;
	return result;
}

void __fastcall TSynEditUndo::Lock()
{
	++FLockCount;
}

void __fastcall TSynEditUndo::Redo(TControl* Editor)
{
	TSynUndoItem* Item = nullptr;
	TSynUndoItem* LastItem = nullptr;
	int OldChangeNumber = 0;
	bool OldModified = false;
	bool FKeepGoing = false;
	bool LastItemHasGroupBreak = false;
	Assert((FBlockCount == 0) && (FRedoList->FBlockChangeNumber == 0) && (FRedoList->FBlockChangeNumber == 0));
	if(FRedoList->Count > 0)
	{
		Item = FRedoList->Peek();
		OldModified = GetModified();
		OldChangeNumber = Item->ChangeNumber;
		FUndoList->BlockChangeNumber = FUndoList->NextChangeNumber();
		try
		{
			do
			{
				Item = FRedoList->Extract();
				LastItemHasGroupBreak = Item->GroupBreak;
				LastItem = Item;
				FInsideUndoRedo = true;
				try
				{
					Item->Redo((TCustomSynEdit*) Editor);
				}
				__finally
				{
					FInsideUndoRedo = false;
				}
        // Move it to the UndoList
				FUndoList->Push(Item);
				if(FRedoList->Count == 0)
					break;
				else
					Item = FRedoList->Peek();
				if(Item->ChangeNumber == OldChangeNumber)
					FKeepGoing = true;
				else

            /* Last Item had a group break - Stop redoing */
            /* Group together same undo actions */
					FKeepGoing = FGroupUndo && !LastItemHasGroupBreak && (ObjectIs(LastItem, TSynLinePutUndoItem*)) && (ObjectIs(Item, TSynLinePutUndoItem*)) && ((TSynLinePutUndoItem*) LastItem)->GroupWith(((TSynLinePutUndoItem*) Item));
			}
			while(!!(FKeepGoing));
			if(!(ObjectIs(Item, TSynCaretAndSelectionUndoItem*)))
				((TCustomSynEdit*) Editor)->CaretXY = Item->FCaret;  // removes selection
		}
		__finally
		{
			if((OldModified ^ GetModified()) && ASSIGNED(FOnModifiedChanged))
				FOnModifiedChanged(this);
			FUndoList->BlockChangeNumber = 0;
		}
	}
}

void __fastcall TSynEditUndo::SetCommandProcessed(TSynEditorCommand Command)
{
	FCommandProcessed = Command;
}

void __fastcall TSynEditUndo::SetGroupUndo(bool Value)
{
	FGroupUndo = Value;
}

void __fastcall TSynEditUndo::SetMaxUndoActions(int Value)
{
	if(Value != FMaxUndoActions)
	{
		FMaxUndoActions = Value;
		FUndoList->EnsureMaxEntries();
		FRedoList->EnsureMaxEntries();
	}
}

void __fastcall TSynEditUndo::SetModified(bool Value)
{
	if(!Value)
	{
		if(FUndoList->Count == 0)
			FInitialChangeNumber = 0;
		else
			FInitialChangeNumber = FUndoList->Peek()->ChangeNumber;
	}
	else
	{
		if(FUndoList->Count == 0)
		{
			if(FInitialChangeNumber == 0)
				FInitialChangeNumber = -1;
		}
		else
		{
			if(FUndoList->Peek()->ChangeNumber == FInitialChangeNumber)
				FInitialChangeNumber = -1;
		}
	}
}

void __fastcall TSynEditUndo::SetOnModifiedChanged(const TNotifyEvent Value)
{
	FOnModifiedChanged = Value;
}

void __fastcall TSynEditUndo::Undo(TControl* Editor)
{
	TSynUndoItem* Item = nullptr;
	TSynUndoItem* LastItem = nullptr;
	int OldChangeNumber = 0;
	bool OldModified = false;
	bool FKeepGoing = false;
	Assert((FBlockCount == 0) && (FRedoList->FBlockChangeNumber == 0) && (FRedoList->FBlockChangeNumber == 0));
	if(FUndoList->Count > 0)
	{
		Item = FUndoList->Peek();
		OldModified = GetModified();
		OldChangeNumber = Item->ChangeNumber;
		FRedoList->BlockChangeNumber = FRedoList->NextChangeNumber();
		try
		{
			do
			{
				Item = FUndoList->Extract();
				LastItem = Item;
				FInsideUndoRedo = true;
				try
				{
					Item->Undo((TCustomSynEdit*) Editor);
				}
				__finally
				{
					FInsideUndoRedo = false;
				}
        // Move it to the RedoList
				FRedoList->Push(Item);
				if(FUndoList->Count == 0)
					break;
				else
					Item = FUndoList->Peek();
				if(Item->ChangeNumber == OldChangeNumber)
					FKeepGoing = true;
				else

            /* Last Item had a group break - Stop redoing */
            /* Group together same undo actions */
					FKeepGoing = FGroupUndo && !Item->GroupBreak && (ObjectIs(LastItem, TSynLinePutUndoItem*)) && (ObjectIs(Item, TSynLinePutUndoItem*)) && ((TSynLinePutUndoItem*) Item)->GroupWith(((TSynLinePutUndoItem*) LastItem));
			}
			while(!!(FKeepGoing));
			if(!(ObjectIs(LastItem, TSynCaretAndSelectionUndoItem*)))
				((TCustomSynEdit*) Editor)->SetCaretAndSelection(LastItem->FCaret, LastItem->FCaret, LastItem->FCaret);
		}
		__finally
		{
			if((OldModified ^ GetModified()) && ASSIGNED(FOnModifiedChanged))
				FOnModifiedChanged(this);
			FRedoList->BlockChangeNumber = 0;
		}
	}
}

void __fastcall TSynEditUndo::Unlock()
{
	if(FLockCount > 0)
		--FLockCount;
}

/* Factory Method*/

ISynEditUndo* __fastcall CreateSynEditUndo(TCustomSynEdit* Editor)
{
	ISynEditUndo* result = nullptr;
	result = new TSynEditUndo(Editor);
	return result;
}

/* TSynCaretAndSelectionUndoItem */

__fastcall TSynCaretAndSelectionUndoItem::TSynCaretAndSelectionUndoItem(TCustomSynEdit* Editor)
 : FBlockBegin(Editor->BlockBegin),
			FBlockEnd(Editor->BlockEnd)
{
	//# inherited::Create();
	FCaret = Editor->CaretXY;
}

void __fastcall TSynCaretAndSelectionUndoItem::Redo(TCustomSynEdit* Editor)
{

  // Same as Undo
	Editor->SetCaretAndSelection(FCaret, FBlockBegin, FBlockEnd);
}

void __fastcall TSynCaretAndSelectionUndoItem::Undo(TCustomSynEdit* Editor)
{
	Editor->SetCaretAndSelection(FCaret, FBlockBegin, FBlockEnd);
}

/* TSynLinesDeletedUndoItem */

__fastcall TSynLinesDeletedUndoItem::TSynLinesDeletedUndoItem(TCustomSynEdit* Editor, int Index, System::TArray<String>& DeletedLines)
 : FIndex(Index),
			FLines(DeletedLines)
{
	//# inherited::Create();
}

void __fastcall TSynLinesDeletedUndoItem::Redo(TCustomSynEdit* Editor)
{
	((TSynEditStringList*) Editor->Lines)->DeleteLines(FIndex, FLines.Length);
	FCaret = BufferCoord(1, FIndex + 1);
}

void __fastcall TSynLinesDeletedUndoItem::Undo(TCustomSynEdit* Editor)
{
	((TSynEditStringList*) Editor->Lines)->InsertStrings(FIndex, FLines);
	FCaret = BufferCoord(1, Min(Editor->Lines->Count, FIndex + FLines.Length + 1));
}

/* TSynLinesInsertedUndoItem */

__fastcall TSynLinesInsertedUndoItem::TSynLinesInsertedUndoItem(TCustomSynEdit* Editor, int Index, int Count)
 : FIndex(Index)
{
	int I = 0;
	int stop = 0;
	//# inherited::Create();
	FLines.Length = Count;
	for(stop = Count - 1, I = 0; I <= stop; I++)
	{
		FLines[I] = Editor->Lines->Strings[Index + I];
	}
}

void __fastcall TSynLinesInsertedUndoItem::Redo(TCustomSynEdit* Editor)
{
	((TSynEditStringList*) Editor->Lines)->InsertStrings(FIndex, FLines);
	FCaret = BufferCoord(1, Min(Editor->Lines->Count, FIndex + FLines.Length + 1));
}

void __fastcall TSynLinesInsertedUndoItem::Undo(TCustomSynEdit* Editor)
{
	((TSynEditStringList*) Editor->Lines)->DeleteLines(FIndex, FLines.Length);
	FCaret = BufferCoord(1, FIndex + 1);
}

/* TSynLinePutUndoItem */

bool __fastcall TSynLinePutUndoItem::GroupWith(TSynLinePutUndoItem* Item)
{
	bool result = false;
	if((FNewValue.Length() == Item->FNewValue.Length()) && (FOldValue.Length() == Item->FOldValue.Length()) && (FOldValue.Length() <= 1) && (FNewValue.Length() <= 1) && (Abs(FStartPos - Item->FStartPos) <= 1))
		result = true;
	else
		result = false;
	return result;
}

__fastcall TSynLinePutUndoItem::TSynLinePutUndoItem(TCustomSynEdit* Editor, int Index, String OldLine, TSynEditorCommand Command)
 : FIndex(Index),
			FStartPos(1),
			FOldValue(OldLine.SubString(FStartPos, Len1)),
			FNewValue(Line.SubString(FStartPos, Len2)),
			FCommandProcessed(0)
{
	int Len1 = 0;
	int Len2 = 0;
	String Line;
	FCommandProcessed = Command;
	Line = Editor->Lines->Strings[Index];
	Len1 = OldLine.Length();
	Len2 = Line.Length();
  // Compare from start
	while((Len1 > 0) && (Len2 > 0) && (OldLine[FStartPos] == Line[FStartPos]))
	{
		--Len1;
		--Len2;
		++FStartPos;
	}  
  // Compare from end
	while((Len1 > 0) && (Len2 > 0) && (OldLine[Len1 + FStartPos - 1] == Line[Len2 + FStartPos - 1]))
	{
		--Len1;
		--Len2;
	}
}

void __fastcall TSynLinePutUndoItem::Redo(TCustomSynEdit* Editor)
{
	String Line;
	int Char = 0;
	Line = Editor->Lines->Strings[FIndex];
  // Delete New
	Line.Delete(FStartPos, 	FOldValue.Length());
	Line.Insert(FNewValue,	FStartPos);
	Editor->Lines->Strings[FIndex] = Line;
	switch(FCommandProcessed)
	{
		case ecChar:
		if((FOldValue.Length() == 1) && (FNewValue.Length() == 1))  // Typing in Insert Mode
			Char = FStartPos;
		else
			Char = FStartPos + FNewValue.Length();
		break;
		case ecDeleteChar:
		case ecDeleteWord:
		case ecDeleteEOL:
		Char = FStartPos;
		break;
		default:
		Char = FStartPos + FNewValue.Length();
		break;
	}
	FCaret = BufferCoord(Char, FIndex + 1);
}

void __fastcall TSynLinePutUndoItem::Undo(TCustomSynEdit* Editor)
{
	String Line;
	int Char = 0;
	Line = Editor->Lines->Strings[FIndex];
  // Delete New
	Line.Delete(FStartPos, 	FNewValue.Length());
	Line.Insert(FOldValue,	FStartPos);
	Editor->Lines->Strings[FIndex] = Line;
	((TSynEditStringList*) Editor->Lines)->ChangeFlags[FIndex] = FChangeFlags;
	switch(FCommandProcessed)
	{
		case ecChar:
		if((FOldValue.Length() == 1) && (FNewValue.Length() == 1))   // Typing in Insert Mode
			Char = FStartPos;
		else
			Char = FStartPos + FOldValue.Length();
		break;
		case ecDeleteChar:
		case ecDeleteWord:
		case ecDeleteEOL:
		Char = FStartPos;
		break;
		default:
		Char = FStartPos + FOldValue.Length();
		break;
	}
	FCaret = BufferCoord(Char, FIndex + 1);
}

/* TSynUndoPlugin */

__fastcall TSynUndoPlugin::TSynUndoPlugin(TSynEditUndo* SynEditUndo, TCustomSynEdit* Editor)
 : inherited(Editor, Syneditundo__0),
			FSynEditUndo(SynEditUndo)
{
}

void __fastcall TSynUndoPlugin::LinePut(int aIndex, const String OldLine)
{
	String Line;
	TSynLinePutUndoItem* Item = nullptr;
	if(Editor->IsChained() || FSynEditUndo->IsLocked() || FSynEditUndo->FInsideUndoRedo)
		return;
	Line = Editor->Lines->Strings[aIndex];
	if(Line != OldLine)
	{
		Item = new TSynLinePutUndoItem(Editor, aIndex, OldLine, FSynEditUndo->FCommandProcessed);
		Item->FChangeFlags = ((TSynEditStringList*) Editor->Lines)->ChangeFlags[aIndex];
		((TSynEditStringList*) Editor->Lines)->ChangeFlags[aIndex] = Item->FChangeFlags + Syneditundo__1;
		FSynEditUndo->AddUndoItem(Item);
	}
}

void __fastcall TSynUndoPlugin::LinesBeforeDeleted(int FirstLine, int Count)
{
	int I = 0;
	int stop = 0;
	if(Editor->IsChained() || FSynEditUndo->IsLocked() || FSynEditUndo->FInsideUndoRedo)
		return;
	FDeletedLines.Length = Count;
	for(stop = Count - 1, I = 0; I <= stop; I++)
	{
		FDeletedLines[I] = Editor->Lines->Strings[FirstLine + I];
	}
}

void __fastcall TSynUndoPlugin::LinesDeleted(int FirstLine, int Count)
{
	TSynLinesDeletedUndoItem* Item = nullptr;
	if(Editor->IsChained() || FSynEditUndo->IsLocked() || FSynEditUndo->FInsideUndoRedo)
		return;
	if(Count > 0)
	{
		Item = new TSynLinesDeletedUndoItem(Editor, FirstLine, FDeletedLines);
		FSynEditUndo->AddUndoItem(Item);
	}
}

void __fastcall TSynUndoPlugin::LinesInserted(int FirstLine, int Count)
{
	TSynLinesInsertedUndoItem* Item = nullptr;
	if(Editor->IsChained() || FSynEditUndo->IsLocked() || FSynEditUndo->FInsideUndoRedo)
		return;

  // Consider a file with one empty line as empty
  // Otherwise when you type in a new file and undo it, CanUndo will still
  // return True because the initial insertion will be on the Undo list
	if((FSynEditUndo->FUndoList->Count == 0) && (Editor->Lines->Count == 1) && (Editor->Lines->Strings[0] == L""))
		return;
	if(Count > 0)
	{
		Item = new TSynLinesInsertedUndoItem(Editor, FirstLine, Count);
		FSynEditUndo->AddUndoItem(Item);
	}
}


}  // namespace SynEditUndo

