#include <vcl.h>
#pragma hdrstop

#include "frmMainMDI.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;


TMDIMainForm* MDIMainForm = nullptr;

/* TMDIMainForm */

IEditor* __fastcall TMDIMainForm::DoCreateEditor(String AFileName)
{
	IEditor* result = nullptr;
	if(GI_EditorFactory != nullptr)
		result = GI_EditorFactory->CreateMDIChild(this);
	else
		result = nullptr;
	return result;
}

void __fastcall TMDIMainForm::FormCreate(TObject* Sender)
{
	inherited::FormCreate(Sender);
	CmdLineOpenFiles(true);
}

__fastcall TMDIMainForm::TMDIMainForm(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	actlWindow(nullptr),
	actWindowTileHorz(nullptr),
	actWindowTileVert(nullptr),
	actWindowArrange(nullptr),
	actWindowCascade(nullptr),
	mWindow(nullptr),
	miWindowCascade(nullptr),
	miWindowTile(nullptr),
	miWindowTileVert(nullptr),
	miWindowArrange(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Caption = L"Multiple Document Edit Demo";
	FormStyle = fsMDIForm;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	mWindow = CreateTMainMenuTMenuItem(/*inherited*/mnuMain);
	mWindow->Caption = L"&Window";
	miWindowCascade = CreateTMenuItemTMenuItem(mWindow);
	miWindowTile = CreateTMenuItemTMenuItem(mWindow);
	miWindowTileVert = CreateTMenuItemTMenuItem(mWindow);
	miWindowArrange = CreateTMenuItemTMenuItem(mWindow);
	actlWindow = new TActionList(this);
	// non-visible component: Left
	// non-visible component: Top
	actWindowTileHorz = new TWindowTileHorizontal(actlWindow);
	actWindowTileHorz->Category = L"Window";
	actWindowTileHorz->Caption = L"&Tile";
	actWindowTileHorz->Enabled = false;
	actWindowTileHorz->ImageIndex = 15;
	actWindowTileVert = new TWindowTileVertical(actlWindow);
	actWindowTileVert->Category = L"Window";
	actWindowTileVert->Caption = L"Tile &Vertically";
	actWindowTileVert->Enabled = false;
	actWindowTileVert->ImageIndex = 16;
	actWindowArrange = new TWindowArrange(actlWindow);
	actWindowArrange->Category = L"Window";
	actWindowArrange->Caption = L"&Arrange Icons";
	actWindowArrange->Enabled = false;
	actWindowCascade = new TWindowCascade(actlWindow);
	actWindowCascade->Category = L"Window";
	actWindowCascade->Caption = L"&Cascade";
	actWindowCascade->Enabled = false;
	actWindowCascade->ImageIndex = 17;
	ComponentState >> csLoading;
	//----- shifted initializations from the dfm-file ---------------------------
	WindowMenu = mWindow;
	miWindowCascade->Action = actWindowCascade;
	miWindowTile->Action = actWindowTileHorz;
	miWindowTileVert->Action = actWindowTileVert;
	miWindowArrange->Action = actWindowArrange;
	//----- end of initializations from the dfm-file ----------------------------
}

