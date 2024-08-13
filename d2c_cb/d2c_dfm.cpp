#pragma hdrstop
#include "d2c_dfm.h"

//#include "SynEditKeyCmds.h"
#include "SynEdit.h"

#include <memory>

using namespace std;
using namespace Synedit;
using namespace Syneditkeycmds;


void AssignControlIsControl(TControl* xp, bool xb)
{
	class TUnprotectedControl : public TControl
	{
		 public:
		 __property IsControl;
	};

	((TUnprotectedControl*)xp)->IsControl = xb;
}

void AssignFormOldCreateOrder(TForm* xp, bool xb)
{
#if __BCPLUSPLUS__ < 0x0760
	xp->OldCreateOrder = xb;  // not in 11.3
#endif
}

void AssignFrameOldCreateOrder(TFrame* xp, bool xb)
{
#if __BCPLUSPLUS__ < 0x0760
	xp->OldCreateOrder = xb;  // not in 11.3
#endif
}

void AssignDataModuleOldCreateOrder(TDataModule* xp, bool xb)
{
#if __BCPLUSPLUS__ < 0x0760
	xp->OldCreateOrder = xb;  // not in 11.3
#endif
}

void AssignFormTextHeight(TForm* xpForm, int xi)
{
	// do nothing
}

void AssignFormPixelsPerInch(TForm* xp, int xi)
{
	// do nothing
}

void AssignDataModuleHeight(TDataModule* xp, int xi)
{
	// do nothing
}

void AssignDataModulePixelsPerInch(TDataModule* xp, int xi)
{
	// do nothing
}

void AssignDataModuleWidth(TDataModule* xp, int xi)
{
	// do nothing
}

TMenuItem* CreateTMainMenuTMenuItem(TMainMenu* xp)
{
	TMenuItem* pItem = new TMenuItem(xp);
	xp->Items->Add(pItem);
	return pItem;
}

TMenuItem* CreateTMenuItemTMenuItem(TMenuItem* xp)
{
	TMenuItem* pItem = new TMenuItem(xp);
	xp->Add(pItem);
	return pItem;
}

void AssignTStringGridColWidths(TStringGrid* xp, int xi, int xiIndex)
{
	if(xp->ColCount == xiIndex)
	  xp->ColCount += 1;
	xp->ColWidths[xiIndex] = xi;
}

void AssignTStringGridRowHeights(TStringGrid* xp, int xi, int xiIndex)
{
	if(xp->RowCount == xiIndex)
	  xp->RowCount += 1;
	xp->RowHeights[xiIndex] = xi;
}

TListColumn* GetTListColumnsitem(TListColumns* xp, int xiIndex)
{
	if(xp->Count == xiIndex)
		 xp->Add();
	return  xp->Items[xiIndex];
}

TStatusPanel* GetTStatusPanelsitem(TStatusPanels* xp, int xiIndex)
{
	if(xp->Count == xiIndex)
		 xp->Add();
	return  xp->Items[xiIndex];
}

TFieldDef* GetTFieldDefsitem(TFieldDefs* xp, int xiIndex)
{
	if(xp->Count == xiIndex)
	   xp->AddFieldDef();
	return  xp->Items[xiIndex];
}

TActionBarItem* GetTActionManagerActionBars(TActionManager* xp, int xiBar)
{
	if(xp->ActionBars->Count == xiBar)
	   return xp->ActionBars->Add();
	  else
	   return xp->ActionBars->ActionBars[xiBar];
}

TActionClientItem* GetTActionBarItemitem(TActionBarItem* xp, int xiIndex)
{
	if(xp->Items->Count == xiIndex)
	  return xp->Items->Add();
	else
	  return xp->Items->ActionClients[xiIndex];
}

TActionClientItem* GetTActionClientItemitem(TActionClientItem* xp, int xiIndex)
{
	if(xp->Items->Count == xiIndex)
	  return xp->Items->Add();
	else
	  return xp->Items->ActionClients[xiIndex];
}

void OnTSplitterBegin(TSplitter* xp)
{
	xp->ComponentState << csLoading;  // csReading
}

void OnTSplitterEnd(TSplitter* xp)
{
	xp->ComponentState >> csLoading;  // csReading
}

void OnDataSetBegin(TDataSet* xp)
{
	xp->Tag = xp->Active;
	xp->Active = false;
}

void OnDataSetEnd(TDataSet* xp)
{
	xp->Active = xp->Tag;
}


void AssignTIconData(TForm* xp, const System::DynamicArray<System::Byte>& Bytes)
{
#ifdef __clang__
	unique_ptr<TMemoryStream> pStream = make_unique<TMemoryStream>();
#else
	TMemoryStream* pStream = new TMemoryStream();
#endif
	pStream->SetSize(Bytes.Length);
	pStream->WriteData(Bytes, Bytes.Length);
	pStream->Position = 0;
	xp->Icon = new TIcon();

#ifdef __clang__
	xp->Icon->LoadFromStream(pStream.get());
#else
	xp->Icon->LoadFromStream(pStream);
	delete pStream;
#endif

}

void AssignTImageListBitmap(TImageList* xp, const System::DynamicArray<System::Byte>& Bytes)
{
	int i = 0;
	xp->Masked = true;
	TBitmap* pBitmap = new TBitmap;
	String sPath = ExtractFilePath(Application->ExeName);
	String sName = L"Image";
	String sExtension = L".bmp";
	String sFilename;

	while(true)
	{
		sFilename = sPath + sName + IntToStr(i) + sExtension;
		if(!FileExists(sFilename))
		  break;
		pBitmap->LoadFromFile(sFilename);
		xp->AddMasked(pBitmap, clFuchsia);
		i++;
	}

	delete pBitmap;
}


void AssignTPictureData(TImage* pImage, const System::DynamicArray<System::Byte>& xBytes)
{
	System::DynamicArray<System::Byte> Bytes; // = xBytes;
#ifdef __clang__
	unique_ptr<TMemoryStream> pStream = make_unique<TMemoryStream>();
#else
	TMemoryStream* pStream = new TMemoryStream();
#endif
	Byte LNameLen;
	pStream->SetSize(xBytes.Length);
	pStream->WriteData(xBytes, xBytes.Length);
	pStream->Position = 0;
	unsigned int Size = 0;
	pStream->Read(&LNameLen, 1);
	Bytes.set_length(LNameLen);
	pStream->Read(Bytes, LNameLen);
	String LClassName = TEncoding::UTF8->GetString(Bytes);
	if(LClassName == L"TBitmap")
	{
#ifdef __clang__
		unique_ptr<TBitmap> pBitmap = make_unique<TBitmap>();
#else
		TBitmap* pBitmap = new TBitmap();
#endif
		Longint Size;
	#ifdef _WIN64
		pStream->Read(&Size, (NativeInt) sizeof(Size));  // 12342
	#else
		pStream->Read(&Size, sizeof(Size));  // 12342
	#endif

#ifdef __clang__
		pBitmap->LoadFromStream(pStream.get());
		pImage->Picture->Assign(pBitmap.get());
#else
		pBitmap->LoadFromStream(pStream);
		pImage->Picture->Assign(pBitmap);
		delete pBitmap;
#endif
	}
}


void AssignTBitmapData(TSpeedButton* xp, const System::DynamicArray<System::Byte>& xBytes)
{
#ifdef __clang__
	unique_ptr<TMemoryStream> pStream = make_unique<TMemoryStream>();
#else
	TMemoryStream* pStream = new TMemoryStream();
#endif
	pStream->SetSize(xBytes.Length);
	pStream->WriteData(xBytes, xBytes.Length);
	pStream->Position = 0;
	unsigned int Size = 0;
	#ifdef _WIN64
	pStream->Read(&Size, (NativeInt) sizeof(Size));
	#else
	pStream->Read(&Size, sizeof(Size));
	#endif
#ifdef __clang__
	xp->Glyph->LoadFromStream(pStream.get());
#else
	xp->Glyph->LoadFromStream(pStream);
	delete pStream;
#endif
}

void AssignData(TCustomClientDataSet::TPersistDataPacket* pData, const System::DynamicArray<System::Byte>& Bytes)
{
// todo dme	pData->Assign(pStream.get());
}


// requires parent

void AssignTRichEditHideSelection(TRichEdit* xp, bool xb)
{
   xp->HideSelection = xb;
}

void AssignTColorBoxStyle(TColorBox* xp, const System::Set<TColorBoxStyles, cbStandardColors, cbCustomColors>& xSet)
{
	xp->Style = xSet;
}


// user defined

// I (dme) did not find a solution yet, how to set the properties
// "RemovedKeystrokes" and "AddedKeystrokes" at runtime.
// Using _SynEditKeyStrokesHack allows compiling the C++ code obtained through
// automatic translation with Delphi2CB without manual post-editing

static  TSynEditKeyStroke*  _SynEditKeyStrokesHack = new TSynEditKeyStroke(nullptr);

TSynEditKeyStroke* GetTSynEditRemovedKeystrokes(TSynEdit* xp, int xi)
{
//   TSynEditKeyStrokes* Keystrokes = xp->Keystrokes;
//   if(Keystrokes != NULL)
//	 return  Keystrokes->Items[xi];
   return _SynEditKeyStrokesHack;   // todo
}

TSynEditKeyStroke* GetTSynEditAddedKeystrokes(TSynEdit* xp, int xi)
{
   return _SynEditKeyStrokesHack;   // todo
}

//void AssignTCustomActionBarColorMapDisabledFontColor(TActionMainMenuBar* xp, int xi)
//{
//   xp->Color = (TColor) xi;
//}
//
//void AssignTActionManagerStyleName(TActionManager* xp, const String& xs)
//{
//   // doesn't exist
//}

