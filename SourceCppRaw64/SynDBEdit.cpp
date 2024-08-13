#include <vcl.h>
#pragma hdrstop

#include "SynDBEdit.h"

using namespace std;
using namespace d2c_system;
using namespace Data::Db;
using namespace Synedit;
using namespace Syneditkeycmds;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;

namespace Syndbedit
{
#define Syndbedit__0 (System::Set<TBlobType, ftBlob, ftWideMemo>() << ftWideMemo << ftWideString)

__fastcall TCustomDBSynEdit::TCustomDBSynEdit(HWND ParentWindow) : inherited(ParentWindow) {}
__fastcall TDBSynEdit::TDBSynEdit(TComponent* AOwner) : inherited(AOwner) {}
__fastcall TDBSynEdit::TDBSynEdit(HWND ParentWindow) : inherited(ParentWindow) {}



__fastcall TCustomDBSynEdit::TCustomDBSynEdit(TComponent* AOwner)
 : inherited(AOwner),
			FDataLink(new TFieldDataLink()),
			fEditing(false),
			FBeginEdit(false)
{
	FDataLink->Control = this;
	FDataLink->OnDataChange = DataChange;
	FDataLink->OnEditingChange = EditingChange;
	FDataLink->OnUpdateData = UpdateData;
}

__fastcall TCustomDBSynEdit::~TCustomDBSynEdit()
{
	delete FDataLink;
	FDataLink = nullptr;
	//# inherited::Destroy();
}

void __fastcall TCustomDBSynEdit::CMEnter(TCMEnter& Msg)
{
	SetEditing(true);
	inherited::Dispatch(&Msg);  //#inherited method "CMEnter" not not accessible;
}

void __fastcall TCustomDBSynEdit::CMExit(TCMExit& Msg)
{
	try
	{
		FDataLink->UpdateRecord();
	}
	catch(...)
	{
		SetFocus();
		throw ;
	}
	SetEditing(false);
	inherited::Dispatch(&Msg);  //#inherited method "CMExit" not not accessible;
}

void __fastcall TCustomDBSynEdit::CMGetDataLink(::TMessage& Msg)
{
	Msg.Result = (NativeInt) FDataLink;
}

void __fastcall TCustomDBSynEdit::DataChange(TObject* Sender)
{
	if(FDataLink->Field != nullptr)
	{
		if(FBeginEdit)
		{
			FBeginEdit = false;
			return;
		}
		if(FDataLink->Field->IsBlob())
			LoadMemo();
		else
			Text = FDataLink->Field->Text;
		if(ASSIGNED(FLoadData))
			FLoadData(this);
	}
	else
	{
		if(ComponentState.Contains(csDesigning))
			Text = Name;
		else
			Text = L"";
	}
}

void __fastcall TCustomDBSynEdit::DragDrop(TObject* Source, int X, int Y)
{
	FDataLink->Edit();
	inherited::DragDrop(Source, X, Y);
}

void __fastcall TCustomDBSynEdit::EditingChange(TObject* Sender)
{
	if(FDataLink->Editing)
	{
		if(ASSIGNED(FDataLink->DataSource) && (FDataLink->DataSource->State != dsInsert))
			FBeginEdit = true;
	}
}

void __fastcall TCustomDBSynEdit::ExecuteCommand(TSynEditorCommand Command, WideChar AChar, void* Data)
{

  // cancel on [ESC]
	if((Command == ecChar) && (AChar == L'\x1b'))
		FDataLink->Reset();
	else
	{
		if((Command >= ecEditCommandFirst) && (Command <= ecEditCommandLast))
		{
			if(!FDataLink->Edit())
				return;
		}
	}
	inherited::ExecuteCommand(Command, AChar, Data);
}

String __fastcall TCustomDBSynEdit::GetDataField()
{
	String result;
	result = FDataLink->FieldName;
	return result;
}

TDataSource* __fastcall TCustomDBSynEdit::GetDataSource()
{
	TDataSource* result = nullptr;
	result = FDataLink->DataSource;
	return result;
}

TField* __fastcall TCustomDBSynEdit::GetField()
{
	TField* result = nullptr;
	result = FDataLink->Field;
	return result;
}

bool __fastcall TCustomDBSynEdit::GetReadOnly()
{
	bool result = false;
	result = FDataLink->ReadOnly;
	return result;
}

void __fastcall TCustomDBSynEdit::Loaded()
{
	inherited::Loaded();
	if(ComponentState.Contains(csDesigning))
		DataChange(this);
}

void __fastcall TCustomDBSynEdit::LoadMemo()
{
	TStream* BlobStream = nullptr;
	try
	{
		BlobStream = FDataLink->DataSet->CreateBlobStream(FDataLink->Field, bmRead);
		Lines->BeginUpdate();
		if((ObjectIs(FDataLink->Field, TBlobField*)) && (Syndbedit__0.Contains(((TBlobField*) FDataLink->Field)->BlobType)))
			Lines->LoadFromStream(BlobStream, TEncoding::Unicode);
		else

      //For UTF8 use: System.SysUtils.TEncoding.UTF8
			Lines->LoadFromStream(BlobStream, TEncoding::Default);
		Lines->EndUpdate();
		delete BlobStream;
		Modified = false;
		ClearUndo();
    // Memo too large 
	}
	catch(EInvalidOperation* e)
	{
		Lines->Text = Format(L"(%s)", ARRAYOFCONST((e->Message)));
	}
	EditingChange(this);
}

void __fastcall TCustomDBSynEdit::DoChange()
{
	FDataLink->Modified();
	inherited::DoChange();
}

void __fastcall TCustomDBSynEdit::Notification(TComponent* AComponent, TOperation Operation)
{
	inherited::Notification(AComponent, Operation);
	if((Operation == opRemove) && (FDataLink != nullptr) && (AComponent == DataSource))
		DataSource = nullptr;
}

void __fastcall TCustomDBSynEdit::SetDataField(const String Value)
{
	FDataLink->FieldName = Value;
}

void __fastcall TCustomDBSynEdit::SetDataSource(TDataSource* Value)
{
	if(!(FDataLink->DataSourceFixed && (ComponentState.Contains(csLoading))))
		FDataLink->DataSource = Value;
	if(Value != nullptr)
		Value->FreeNotification(this);
}

void __fastcall TCustomDBSynEdit::SetEditing(bool Value)
{
	if(fEditing != Value)
	{
		fEditing = Value;
		if(!ASSIGNED(FDataLink->Field) || !FDataLink->Field->IsBlob())
			FDataLink->Reset();
	}
}

void __fastcall TCustomDBSynEdit::SetReadOnly(bool Value)
{
	FDataLink->ReadOnly = Value;
}

void __fastcall TCustomDBSynEdit::UpdateData(TObject* Sender)
{
	TStream* BlobStream = nullptr;
	if(FDataLink->Field->IsBlob())
	{
		BlobStream = FDataLink->DataSet->CreateBlobStream(FDataLink->Field, bmWrite);
		Lines->SaveToStream(BlobStream);
		delete BlobStream;
	}
	else
	FDataLink->Field->AsString = Text;
}


}  // namespace SynDBEdit

