#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterManager.h"
#include "DesignIntf.hpp"
#include <Winapi.Windows.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.CheckLst.hpp>
#include "SynEditHighlighter.h"
#include "SynEditStrConst.h"
#include <System.SysUtils.hpp>

using namespace std;
using namespace d2c_system;
using namespace Designintf;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Uitypes;
using namespace Vcl::Checklst;
using namespace Vcl::Controls;
using namespace Vcl::Forms;
using namespace Vcl::Stdctrls;




class TSynHighlighterForm : public TForm
{
__published:
public:
	TCheckListBox* clbHighlighters;
	TButton* btnSelectAll;
	TButton* btnDeselectAll;
	TButton* btnOK;
	TButton* btnCancel;
	TSynHighlighterList* Highlight;
	HIDESBASE __fastcall TSynHighlighterForm(TSynHighlighterList* highlighters)/*# reintroduce */;
	void __fastcall LoadForm();
	void __fastcall SelectAll(TObject* Sender);
	void __fastcall DeselectAll(TObject* Sender);
public:
	typedef TForm inherited;
	#include "SynHighlighterManager_friends.inc"
	__fastcall TSynHighlighterForm(TComponent* AOwner) : inherited(AOwner) {}
};
typedef IDesigner TDesignerClass;

/* TSynHighlighterManager */

__fastcall TSynHighlighterManager::TSynHighlighterManager(TComponent* AOwner)
 : inherited(AOwner)
{
	TCustomForm* Form = nullptr;
	TDesignerClass* dsgn = nullptr;
	TSynHighlighterList* Highlight = nullptr;
	TSynHighlighterForm* synForm = nullptr;

	auto CheckExisting = [&]() -> void 
	{
		int i = 0;
		int j = 0;
		int stop = 0;
		for(stop = Form->ComponentCount - 1, i = 0; i <= stop; i++)
		{
			j = Highlight->FindByClass(Form->Components[i]);
			if(j >= 0)
			{
// todo dme				j = synForm->clbHighlighters->Items->IndexOf(Highlight->Items[j]->GetFriendlyLanguageName);
				if(j >= 0)
					synForm->clbHighlighters->Checked[j] = true;
			}
		} //for
	};

	auto FindHighlighterComp = [&](TSynCustomHighlighterClass hlClass) -> int 
	{
		int result = 0;
		int i = 0;
		int stop = 0;
		result = -1;
		for(stop = Form->ComponentCount - 1, i = 0; i <= stop; i++)
		{
// todo dme			if(ObjectIs(Form->Components[i], hlClass))
			{
				result = i;
				return result;
			}
		} //for
		return result;
	};

	auto PlaceNew = [&]() -> void 
	{
		int i = 0;
		int High = 0;
		int Comp = 0;
		int XPos = 0;
		int YPos = 0;
		int XStart = 0;

		auto GetStartCoordinates = [&]() -> void 
		{
			int compTop = 0;
			int compLeft = 0;
			int i = 0;
			int stop = 0;
			XPos = -1;
			YPos = -1;
			for(stop = Form->ComponentCount - 1, i = 0; i <= stop; i++)
			{
// todo dme				if(ObjectIs(Form->Components[i], TSynCustomHighlighterClass**))
				{
					compLeft = (int) ((LongRec*) &Form->Components[i]->DesignInfo)->Lo;
					compTop = (int) ((LongRec*) &Form->Components[i]->DesignInfo)->Hi;
					if((XPos < 0) || (compLeft < XPos))
						XPos = compLeft;
					if((YPos < 0) || (compTop < YPos))
						YPos = compTop;
				}
			} //for
			if(XPos < 0)
				XPos = 8;
			if(YPos < 0)
				YPos = 8;
			XStart = XPos;
		};

		auto IncCoordinates = [&]() -> void 
		{
			XPos += 32;
// todo dme			if((XPos + 32) >= Form->ClientWidth)
			{
				XPos = XStart;
				YPos += 32;
			}
		};

		auto CoordinatesTaken = [&]() -> bool 
		{
			bool result = false;
			int compTop = 0;
			int compLeft = 0;
			TRect compRect = {};
			TRect testRect = {};
			TRect interRect = {};
			int i = 0;
			int stop = 0;
			result = false;
			testRect = Rect(XPos, YPos, XPos + 31, YPos + 31);
			for(stop = Form->ComponentCount - 1, i = 0; i <= stop; i++)
			{
				if((Form->Components[i] != this) && (!(ObjectIs(Form->Components[i], TControl*))))
				{
					compLeft = (int) ((LongRec*) &Form->Components[i]->DesignInfo)->Lo;
					compTop = (int) ((LongRec*) &Form->Components[i]->DesignInfo)->Hi;
					compRect = Rect(compLeft, compTop, compLeft + 31, compTop + 31);
					if(IntersectRect(&interRect, &testRect, &compRect))
					{
						result = true;
						return result;
					}
				}
			} //for
			return result;
		};

		auto GetFreeCoordinates = [&]() -> void 
		{
			while(CoordinatesTaken())
				IncCoordinates();
		};
		int stop = 0;
		GetStartCoordinates();
    // Iterate over TCheckListBox, not over GetPlaceableHighlighters to ensure
    // inserted highlighters to be sorted by name.
    // Iterate twice - delete highlighters in first pass (to make place), create
    // in second.
		for(stop = synForm->clbHighlighters->Items->Count - 1, i = 0; i <= stop; i++)
		{
			if(!synForm->clbHighlighters->Checked[i]) // unchecked - remove
			{
				High = Highlight->FindByFriendlyName(synForm->clbHighlighters->Items->Strings[i]);
				if(High >= 0)
				{
					Comp = FindHighlighterComp(Highlight->Items[High]);
					if(Comp >= 0)
						delete Form->Components[Comp];
				}
			}
		} //for
		for(stop = synForm->clbHighlighters->Items->Count - 1, i = 0; i <= stop; i++)
		{
			if(synForm->clbHighlighters->Checked[i]) // checked - add
			{
				High = Highlight->FindByFriendlyName(synForm->clbHighlighters->Items->Strings[i]);
				if(High >= 0)
				{
					if(FindHighlighterComp(Highlight->Items[High]) < 0)
					{
						GetFreeCoordinates();
						dsgn->CreateComponent(Highlight->Items[High], AOwner, XPos, YPos, 24, 24);
						IncCoordinates();
					}
				}
			}
		} //for
	};
	if((ComponentState.Contains(csDesigning)) && (ObjectIs(AOwner, TCustomForm*)))
	{
		Form = ((TCustomForm*) AOwner);
// todo dme		dsgn = (TDesignerClass*) Form->Designer;
		Highlight = GetPlaceableHighlighters();
		if(Highlight->Count() == 0)
			Application->MessageBox(L"No highlighters found!", L"Highlighter Manager", MB_OK + MB_ICONEXCLAMATION);
		else
		{
			synForm = new TSynHighlighterForm(Highlight);
			try
			{
				CheckExisting();
				if(synForm->ShowModal() == System::Uitypes::mrOk)
					PlaceNew();
			}
			__finally
			{
				delete synForm;
			}
		}
	}
	Sysutils::Abort();
}

/* TSynHighlighterForm */

__fastcall TSynHighlighterForm::TSynHighlighterForm(TSynHighlighterList* highlighters)
 : /*#CreateNew*/ inherited(nullptr, 0), 
clbHighlighters(new TCheckListBox(this)),
			btnSelectAll(new TButton(this)),
			btnDeselectAll(new TButton(this)),
			btnOK(new TButton(this)),
			btnCancel(new TButton(this)),
			Highlight(nullptr)
{
	Caption = L"Highlighter Manager";
	Width = 410;
	Height = 243;
	Position = poScreenCenter;
	BorderStyle = bsDialog;
	Highlight = highlighters;
  
//object clbHighlighters: TCheckListBox
//  Left = 8
//  Top = 8
//  Width = 305
//  Height = 201
//  ItemHeight = 13
//  TabOrder = 0
//end

//object btnSelectAll: TButton
//  Left = 320
//  Top = 8
//  Width = 75
//  Height = 25
//  Caption = '&Select All'
//  TabOrder = 1
//end

//object btnDeselectAll: TButton
//  Left = 320
//  Top = 40
//  Width = 75
//  Height = 25
//  Caption = '&Deselect All'
//  TabOrder = 2
//end

//object btnOK: TButton
//  Left = 320
//  Top = 152
//  Width = 75
//  Height = 25
//  Caption = 'OK'
//  Default = True
//  ModalResult = 1
//  TabOrder = 3
//end

//object btnCancel: TButton
//  Left = 320
//  Top = 184
//  Width = 75
//  Height = 25
//  Caption = 'Cancel'
//  ModalResult = 2
//  TabOrder = 4
//end
	/*# with clbHighlighters do */
	{
		auto with0 = clbHighlighters;
		with0->Name = L"clbHighlighters";
		with0->Parent = this;
		with0->Left = 8;
		with0->Top = 8;
		with0->Width = 305;
		with0->Height = 201;
		with0->ItemHeight = 13;
		with0->Sorted = true;
		with0->TabOrder = (TTabOrder) 0;
	}
	/*# with btnSelectAll do */
	{
		auto with1 = btnSelectAll;
		with1->Name = L"btnSelectAll";
		with1->Parent = this;
		with1->Left = 320;
		with1->Top = 8;
		with1->Width = 75;
		with1->Height = 25;
		with1->Caption = L"&Select All";
		with1->TabOrder = (TTabOrder) 1;
		with1->OnClick = SelectAll;
	}
	/*# with btnDeselectAll do */
	{
		auto with2 = btnDeselectAll;
		with2->Name = L"btnDeselectAll";
		with2->Parent = this;
		with2->Left = 320;
		with2->Top = 40;
		with2->Width = 75;
		with2->Height = 25;
		with2->Caption = L"&Deselect All";
		with2->TabOrder = (TTabOrder) 2;
		with2->OnClick = DeselectAll;
	}
	/*# with btnOK do */
	{
		auto with3 = btnOK;
		with3->Name = L"btnOK";
		with3->Parent = this;
		with3->Left = 320;
		with3->Top = 152;
		with3->Width = 75;
		with3->Height = 25;
		with3->Caption = L"OK";
		with3->Default = true;
		with3->ModalResult = (TModalResult) 1;
		with3->TabOrder = (TTabOrder) 3;
	}
	/*# with btnCancel do */
	{
		auto with4 = btnCancel;
		with4->Name = L"btnCancel";
		with4->Parent = this;
		with4->Left = 320;
		with4->Top = 184;
		with4->Width = 75;
		with4->Height = 25;
		with4->Caption = L"Cancel";
		with4->ModalResult = (TModalResult) 2;
		with4->TabOrder = (TTabOrder) 4;
	}
	LoadForm();
}

void __fastcall TSynHighlighterForm::DeselectAll(TObject* Sender)
{
	int i = 0;
	int stop = 0;
	for(stop = clbHighlighters->Items->Count - 1, i = 0; i <= stop; i++)
	{
		clbHighlighters->Checked[i] = false;
	}
}

void __fastcall TSynHighlighterForm::LoadForm()
{
	int i = 0;
	int stop = 0;
	clbHighlighters->Clear();
	for(stop = Highlight->Count() - 1, i = 0; i <= stop; i++)
	{
// todo dme		clbHighlighters->Items->Add(Highlight->Items[i]->GetFriendlyLanguageName);
	} //for
}

void __fastcall TSynHighlighterForm::SelectAll(TObject* Sender)
{
	int i = 0;
	int stop = 0;
	for(stop = clbHighlighters->Items->Count - 1, i = 0; i <= stop; i++)
	{
		clbHighlighters->Checked[i] = true;
	}
}
