#include <vcl.h>
#pragma hdrstop

#include "SynDBEdit.h"
#include "d2c_sysinterface.h"

using namespace std;
using namespace d2c_system;
using namespace Data::Db;
using namespace Synedit;
using namespace Syneditkeycmds;
using namespace Synedittypes;
using namespace System;

namespace Syndbedit
{
#define Syndbedit__0 (System::Set<TBlobType, ftBlob, ftWideMemo>() << static_cast<TBlobType>(ftWideMemo) << static_cast<TBlobType>(ftWideString))

__fastcall TCustomDBSynEdit::TCustomDBSynEdit(HWND ParentWindow) : inherited(ParentWindow) {}
__fastcall TDBSynEdit::TDBSynEdit(TComponent* AOwner) : inherited(AOwner) {}
__fastcall TDBSynEdit::TDBSynEdit(HWND ParentWindow) : inherited(ParentWindow) {}



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynDBEdit.pas, released 2000-05-05.
The Original Code is based on DBmwEdit.pas by Vladimir Kuznetsov, part of
the mwEdit component suite.
Portions created by Vladimir Kuznetsov are Copyright (C) 1999 Vladimir Kuznetsov.
Unicode translation by Maël Hörz.
All Rights Reserved.

Contributors to the SynEdit and mwEdit projects are listed in the
Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

$Id: SynDBEdit.pas,v 1.11.2.2 2009/06/14 13:33:38 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

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
		if(Assigned(FLoadData))
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
	catch(const EInvalidOperation& E)
	{
		Lines->Text = Format(L"(%s)", ARRAYOFCONST((E.Message)));
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


}  // namespace Syndbedit

