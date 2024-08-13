#ifndef d2c_dfmH
#define d2c_dfmH

/*
		Copyright (C) <2023>  <Dr. Detlef Meyer-Eltz>
    ---------------------------------------------

    this file is authorized for unlimited use in any
    project created with Delphi2C# or DelphiCpp.

    http://www.texttransformer.com/
*/

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.ActnList.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnPopup.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Datasnap.DBClient.hpp>




void AssignControlIsControl(TControl* xp, bool xb);
//void AssignNControlIsControl(TControl* xp, bool xb);


void AssignFormOldCreateOrder(TForm* xp, bool xb);
void AssignFrameOldCreateOrder(TFrame* xp, bool xb);
void AssignDataModuleOldCreateOrder(TDataModule* xp, bool xb);
void AssignFormTextHeight(TForm* xpForm, int xi);
void AssignFormPixelsPerInch(TForm* xp, int xi);
void AssignDataModuleHeight(TDataModule* xp, int xi);
void AssignDataModulePixelsPerInch(TDataModule* xp, int xi);
void AssignDataModuleWidth(TDataModule* xp, int xi);

TMenuItem* CreateTMainMenuTMenuItem(TMainMenu* xp);
TMenuItem* CreateTMenuItemTMenuItem(TMenuItem* xp);
void AssignTStringGridColWidths(TStringGrid* xp, int xi, int xiIndex);
void AssignTStringGridRowHeights(TStringGrid* xp, int xi, int xiIndex);

TListColumn* GetTListColumnsitem(TListColumns* xp, int xiIndex);
TStatusPanel* GetTStatusPanelsitem(TStatusPanels* xp, int xiIndex);
TFieldDef* GetTFieldDefsitem(TFieldDefs* xp, int xiIndex);
TActionBarItem* GetTActionManagerActionBars(TActionManager* xp, int xiBar);
TActionClientItem* GetTActionBarItemitem(TActionBarItem* xp, int xiIndex);
TActionClientItem* GetTActionClientItemitem(TActionClientItem* xp, int xiIndex);

void OnTSplitterBegin(TSplitter* xp);
void OnTSplitterEnd(TSplitter* xp);
void OnDataSetBegin(TDataSet* xp);
void OnDataSetEnd(TDataSet* xp);


/////////////////////////////////////////////////////////////////////////////////////
// The creation of the DynamicArray's only works if the clang compiler is enabled  //
/////////////////////////////////////////////////////////////////////////////////////

void AssignTIconData(TForm* xp, const System::DynamicArray<System::Byte>& Bytes);
void AssignTImageListBitmap(TImageList* xp, const System::DynamicArray<System::Byte>& Bytes);
void AssignTPictureData(TImage* pImage, const System::DynamicArray<System::Byte>& Bytes);
void AssignTBitmapData(TSpeedButton* xp, const System::DynamicArray<System::Byte>& xBytes);


// requires parent
void AssignTRichEditHideSelection(TRichEdit* xp, bool xb);
void AssignTColorBoxStyle(TColorBox* xp, const System::Set<TColorBoxStyles, cbStandardColors, cbCustomColors>& xSet);

///  User defined

namespace Synedit
{
	class TSynEdit;
}
namespace Syneditkeycmds
{
	class TSynEditKeyStroke;
}

Syneditkeycmds::TSynEditKeyStroke* GetTSynEditRemovedKeystrokes(Synedit::TSynEdit* xp, int xi);
Syneditkeycmds::TSynEditKeyStroke* GetTSynEditAddedKeystrokes(Synedit::TSynEdit* xp, int xi);

//void AssignTCustomActionBarColorMapDisabledFontColor(TActionMainMenuBar* xp, int xi);
//void AssignTActionManagerStyleName(TActionManager* xp, const String& xs);

//---------------------------------------------------------------------------
#endif
