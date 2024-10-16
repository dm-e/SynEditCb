
#include <vcl.h>
#pragma hdrstop

#include "SynEditHighlighter.h"
#include "SynEditMiscProcs.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighteroptions;
using namespace Syneditmiscclasses;
using namespace Syneditmiscprocs;
using namespace Syneditstrconst;
using namespace Synunicode;
using namespace System::Classes;
using namespace System::Types;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Synedithighlighter
{
#define Synedithighlighter__0 TFontStyles()
#define Synedithighlighter__1 (TFontStyles() << TFontStyle::fsBold)
#define Synedithighlighter__2 (TFontStyles() << TFontStyle::fsItalic)
#define Synedithighlighter__3 (TFontStyles() << TFontStyle::fsUnderline)
#define Synedithighlighter__4 TFontStyles()
#define Synedithighlighter__5 (TFontStyles() << TFontStyle::fsBold)
#define Synedithighlighter__6 (TFontStyles() << TFontStyle::fsItalic)
#define Synedithighlighter__7 (TFontStyles() << TFontStyle::fsUnderline)
#define Synedithighlighter__8 TFontStyles()
#define Synedithighlighter__9 (TFontStyles() << TFontStyle::fsBold)
#define Synedithighlighter__10 (TFontStyles() << TFontStyle::fsItalic)
#define Synedithighlighter__11 (TFontStyles() << TFontStyle::fsUnderline)
#define Synedithighlighter__12 (TFontStyles() << TFontStyle::fsStrikeOut)
#define Synedithighlighter__13 (TSynHighlighterCapabilities() << hcRegistry)

__fastcall TSynHighlighterAttributes::TSynHighlighterAttributes() {}



/* THighlighterList */

int __fastcall TSynHighlighterList::Count()
{
	int result = 0;
	result = hlList->Count;
	return result;
}

__fastcall TSynHighlighterList::TSynHighlighterList()
 : hlList(new TList())
{
	//# inherited::Create();
}

__fastcall TSynHighlighterList::~TSynHighlighterList()
{
	delete hlList;
	// inherited;
}

int __fastcall TSynHighlighterList::FindByClass(TComponent* Comp)
{
	int result = 0;
	int i = 0;
	int stop = 0;
	result = -1;
	for(stop = Count() - 1, i = 0; i <= stop; i++)
	{
		TSynCustomHighlighterClass pm = Items[i];
		//if(ObjectIs(Comp, pm))
		if(pm == Comp->ClassType()) // todo dme check
		{
			result = i;
			return result;
		}
	}
	return result;
}

int __fastcall TSynHighlighterList::FindByFriendlyName(String FriendlyName)
{
	int result = 0;
	int i = 0;
	int stop = 0;
	result = -1;
	for(stop = Count() - 1, i = 0; i <= stop; i++)
	{
	/* todo dme
		if(Items[i]->GetFriendlyLanguageName == FriendlyName)
		{
			result = i;
			return result;
		}
		*/
	}
	return result;
}

int __fastcall TSynHighlighterList::FindByName(String Name)
{
	int result = 0;
	int i = 0;
	int stop = 0;
	result = -1;
	for(stop = Count() - 1, i = 0; i <= stop; i++)
	{
	/* todo dme
		if(Items[i]->GetLanguageName == Name)
		{
			result = i;
			return result;
		}
		*/
	}
	return result;
}

TSynCustomHighlighterClass __fastcall TSynHighlighterList::GetItem(int Index)
{
	TSynCustomHighlighterClass result = nullptr;
	result = TSynCustomHighlighterClass(hlList->Items[Index]);
	return result;
}
TSynHighlighterList* G_PlaceableHighlighters = nullptr;

TSynHighlighterList* __fastcall GetPlaceableHighlighters()
{
	TSynHighlighterList* result = nullptr;
	result = G_PlaceableHighlighters;
	return result;
}

void __fastcall RegisterPlaceableHighlighter(TSynCustomHighlighterClass highlighter)
{
	if(G_PlaceableHighlighters->hlList->IndexOf(highlighter) < 0)
		G_PlaceableHighlighters->hlList->Add(highlighter);
}

/* TSynHighlighterAttributes */

void __fastcall TSynHighlighterAttributes::Assign(TPersistent* Source)
{
	if(ObjectIs(Source, TSynHighlighterAttributes*))
	{
		fName = ((TSynHighlighterAttributes*) Source)->fName;
		AssignColorAndStyle(((TSynHighlighterAttributes*) Source));
	}
	else
	inherited::Assign(Source);
}

void __fastcall TSynHighlighterAttributes::AssignColorAndStyle(TSynHighlighterAttributes* Source)
{
	bool bChanged = false;
	bChanged = false;
	if(fBackground != Source->fBackground)
	{
		fBackground = Source->fBackground;
		bChanged = true;
	}
	if(fForeground != Source->fForeground)
	{
		fForeground = Source->fForeground;
		bChanged = true;
	}
	if(fStyle != Source->fStyle)
	{
		fStyle = Source->fStyle;
		bChanged = true;
	}
	if(bChanged)
		Changed();
}

void __fastcall TSynHighlighterAttributes::Changed()
{
	if(ASSIGNED(fOnChange))
		fOnChange(this);
}

__fastcall TSynHighlighterAttributes::TSynHighlighterAttributes(String AName, String AFriendlyName)
 : fBackground((TColor) 0),
			fBackgroundDefault((TColor) 0),
			fForeground((TColor) 0),
			fForegroundDefault((TColor) 0)
{
	//# inherited::Create();
	Background = (TColor) clNone;
	Foreground = (TColor) clNone;
	fName = AName;
	fFriendlyName = AFriendlyName;
}

bool __fastcall TSynHighlighterAttributes::GetBackgroundColorStored()
{
	bool result = false;
	result = fBackground != fBackgroundDefault;
	return result;
}

bool __fastcall TSynHighlighterAttributes::GetForegroundColorStored()
{
	bool result = false;
	result = fForeground != fForegroundDefault;
	return result;
}

bool __fastcall TSynHighlighterAttributes::GetFontStyleStored()
{
	bool result = false;
	result = fStyle != fStyleDefault;
	return result;
}

void __fastcall TSynHighlighterAttributes::InternalSaveDefaultValues()
{
	fForegroundDefault = fForeground;
	fBackgroundDefault = fBackground;
	fStyleDefault = fStyle;
}
  // How the highlighting information is stored:
  // Delphi 1.0:
  //   I don't know and I don't care.
  // Delphi 2.0 & 3.0:
  //   In the registry branch HKCU\Software\Borland\Delphi\x.0\Highlight
  //   where x=2 or x=3.
  //   Each entry is one string value, encoded as
  //     <foreground RGB>,<background RGB>,<font style>,<default fg>,<default Background>,<fg index>,<Background index>
  //   Example:
  //     0,16777215,BI,0,1,0,15
  //     foreground color (RGB): 0
  //     background color (RGB): 16777215 ($FFFFFF)
  //     font style: BI (bold italic), possible flags: B(old), I(talic), U(nderline)
  //     default foreground: no, specified color will be used (black (0) is used when this flag is 1)
  //     default background: yes, white ($FFFFFF, 15) will be used for background
  //     foreground index: 0 (foreground index (Pal16), corresponds to foreground RGB color)
  //     background index: 15 (background index (Pal16), corresponds to background RGB color)
  // Delphi 4.0 & 5.0:
  //   In the registry branch HKCU\Software\Borland\Delphi\4.0\Editor\Highlight.
  //   Each entry is subkey containing several values:
  //     Foreground Color: foreground index (Pal16), 0..15 (dword)
  //     Background Color: background index (Pal16), 0..15 (dword)
  //     Bold: fsBold yes/no, 0/True (string)
  //     Italic: fsItalic yes/no, 0/True (string)
  //     Underline: fsUnderline yes/no, 0/True (string)
  //     Default Foreground: use default foreground (clBlack) yes/no, False/-1 (string)
  //     Default Background: use default backround (clWhite) yes/no, False/-1 (string)

bool __fastcall TSynHighlighterAttributes::LoadFromBorlandRegistry(HKEY RootKey, String AttrKey, String AttrName, bool OldStyle)
{
	bool result = false;
	const TColor Pal16[16/*# range 0..15*/] = {(TColor) clBlack, (TColor) clMaroon, (TColor) clGreen, (TColor) clOlive, (TColor) clNavy, (TColor) clPurple, (TColor) clTeal, (TColor) clLtGray, (TColor) clDkGray, (TColor) clRed, (TColor) clLime, (TColor) clYellow, (TColor) clBlue
                    , (TColor) clFuchsia, (TColor) clAqua, (TColor) clWhite};

	auto LoadOldStyle = [&](HKEY RootKey, String AttrKey, String AttrName) -> bool 
	{
		bool result = false;
		String descript;
		String fgColRGB;
		String bgColRGB;
		String fontStyle;
		String fgDefault;
		String bgDefault;
		String fgIndex16;
		String bgIndex16;
		TBetterRegistry* reg = nullptr;

		auto Get = [&](String& Name) -> String 
		{
			String result;
			int p = 0;
			p = Pos(L",", Name);
			if(p == 0)
				p = Name.Length() + 1;
			result = Name.SubString(1, p - 1);
			Name = Name.SubString(p + 1, Name.Length() - p);
			return result;
		}; /* LoadOldStyle */
		result = false;
		try
		{
			reg = new TBetterRegistry();
			reg->RootKey = RootKey;
			try
			{
				/*# with reg do */
				{
					auto with0 = reg;
					if(with0->OpenKeyReadOnly(AttrKey))
					{
						try
						{
							if(with0->ValueExists(AttrName))
							{
								descript = with0->ReadString(AttrName);
								fgColRGB = Get(descript);
								bgColRGB = Get(descript);
								fontStyle = Get(descript);
								fgDefault = Get(descript);
								bgDefault = Get(descript);
								fgIndex16 = Get(descript);
								bgIndex16 = Get(descript);
								if(bgDefault == L"1")
									Background = (TColor) clWindow;
								else
									Background = Pal16[StrToInt(bgIndex16)];
								if(fgDefault == L"1")
									Foreground = (TColor) clWindowText;
								else
									Foreground = Pal16[StrToInt(fgIndex16)];
								Style = Synedithighlighter__0;
								if(Pos(L"B", fontStyle) > 0)
									Style = Style + Synedithighlighter__1;
								if(Pos(L"I", fontStyle) > 0)
									Style = Style + Synedithighlighter__2;
								if(Pos(L"U", fontStyle) > 0)
									Style = Style + Synedithighlighter__3;
								result = true;
							}
						}
						__finally
						{
							with0->CloseKey();
						}
					} // if
				} // with
			}
			__finally
			{
				delete reg;
			}
		}
		catch(...)
		{
			;
		}
		return result;
	}; /* LoadOldStyle */

	auto LoadNewStyle = [&](HKEY RootKey, String AttrKey, String AttrName) -> bool 
	{
		bool result = false;
		int fgColor = 0;
		int bgColor = 0;
		String fontBold;
		String fontItalic;
		String fontUnderline;
		String fgDefault;
		String bgDefault;
		TBetterRegistry* reg = nullptr;

		auto IsTrue = [&](String Value) -> bool 
		{
			bool result = false;
			result = !((UpperCase(Value) == L"FALSE") || (Value == L"0"));
			return result;
		}; /* IsTrue */
		result = false;
		try
		{
			reg = new TBetterRegistry();
			reg->RootKey = RootKey;
			try
			{
				/*# with reg do */
				{
					auto with0 = reg;
					if(with0->OpenKeyReadOnly(AttrKey + L"\\" + AttrName))
					{
						try
						{
							if(with0->ValueExists(L"Foreground Color"))
								fgColor = Pal16[with0->ReadInteger(L"Foreground Color")];
							else
							{
								if(with0->ValueExists(L"Foreground Color New"))
									fgColor = StringToColor(with0->ReadString(L"Foreground Color New"));
								else
									return result;
							}
							if(with0->ValueExists(L"Background Color"))
								bgColor = Pal16[with0->ReadInteger(L"Background Color")];
							else
							{
								if(with0->ValueExists(L"Background Color New"))
									bgColor = StringToColor(with0->ReadString(L"Background Color New"));
								else
									return result;
							}
							if(with0->ValueExists(L"Bold"))
								fontBold = with0->ReadString(L"Bold");
							else
								return result;
							if(with0->ValueExists(L"Italic"))
								fontItalic = with0->ReadString(L"Italic");
							else
								return result;
							if(with0->ValueExists(L"Underline"))
								fontUnderline = with0->ReadString(L"Underline");
							else
								return result;
							if(with0->ValueExists(L"Default Foreground"))
								fgDefault = with0->ReadString(L"Default Foreground");
							else
								return result;
							if(with0->ValueExists(L"Default Background"))
								bgDefault = with0->ReadString(L"Default Background");
							else
								return result;
							if(IsTrue(bgDefault))
								Background = (TColor) clWindow;
							else
								Background = (TColor) bgColor;
							if(IsTrue(fgDefault))
								Foreground = (TColor) clWindowText;
							else
								Foreground = (TColor) fgColor;
							Style = Synedithighlighter__4;
							if(IsTrue(fontBold))
								Style = Style + Synedithighlighter__5;
							if(IsTrue(fontItalic))
								Style = Style + Synedithighlighter__6;
							if(IsTrue(fontUnderline))
								Style = Style + Synedithighlighter__7;
							result = true;
						}
						__finally
						{
							with0->CloseKey();
						}
					} // if
				} // with
			}
			__finally
			{
				delete reg;
			}
		}
		catch(...)
		{
			;
		}
		return result;
	}; /* LoadNewStyle */
	if(OldStyle)
		result = LoadOldStyle(RootKey, AttrKey, AttrName);
	else
		result = LoadNewStyle(RootKey, AttrKey, AttrName);
	return result;
} /* TSynHighlighterAttributes.LoadFromBorlandRegistry */

void __fastcall TSynHighlighterAttributes::SetBackground(TColor Value)
{
	if(fBackground != Value)
	{
		fBackground = Value;
		Changed();
	}
}

void __fastcall TSynHighlighterAttributes::SetColors(TColor Foreground, TColor Background)
{
	if((fForeground != Foreground) || (fBackground != Background))
	{
		fForeground = Foreground;
		fBackground = Background;
		Changed();
	}
}

void __fastcall TSynHighlighterAttributes::SetForeground(TColor Value)
{
	if(fForeground != Value)
	{
		fForeground = Value;
		Changed();
	}
}

void __fastcall TSynHighlighterAttributes::SetStyle(TFontStyles Value)
{
	if(fStyle != Value)
	{
		fStyle = Value;
		Changed();
	}
}

bool __fastcall TSynHighlighterAttributes::LoadFromRegistry(TBetterRegistry* Reg)
{
	bool result = false;
	String Key;
	Key = Reg->CurrentPath;
	if(Reg->OpenKeyReadOnly(Name))
	{
		if(Reg->ValueExists(L"Background"))
			Background = (TColor) Reg->ReadInteger(L"Background");
		if(Reg->ValueExists(L"Foreground"))
			Foreground = (TColor) Reg->ReadInteger(L"Foreground");
		if(Reg->ValueExists(L"Style"))
			IntegerStyle = Reg->ReadInteger(L"Style");
		Reg->OpenKeyReadOnly(String(L"\\") + Key);
		result = true;
	}
	else
	result = false;
	return result;
}

bool __fastcall TSynHighlighterAttributes::SaveToRegistry(TBetterRegistry* Reg)
{
	bool result = false;
	String Key;
	Key = Reg->CurrentPath;
	if(Reg->OpenKey(Name, true))
	{
		Reg->WriteInteger(L"Background", Background);
		Reg->WriteInteger(L"Foreground", Foreground);
		Reg->WriteInteger(L"Style", IntegerStyle);
		Reg->OpenKey(String(L"\\") + Key, false);
		result = true;
	}
	else
	result = false;
	return result;
}

bool __fastcall TSynHighlighterAttributes::LoadFromFile(TCustomIniFile* Ini)
{
	bool result = false;
	TStringList* S = nullptr;
	S = new TStringList();
	try
	{
		Ini->ReadSection(Name, S);
		if(S->Count > 0)
		{
			if(S->IndexOf(L"Background") != -1)
				Background = (TColor) Ini->ReadInteger(Name, L"Background", Background);
			if(S->IndexOf(L"Foreground") != -1)
				Foreground = (TColor) Ini->ReadInteger(Name, L"Foreground", Foreground);
			if(S->IndexOf(L"Style") != -1)
				IntegerStyle = Ini->ReadInteger(Name, L"Style", IntegerStyle);
			result = true;
		}
		else
		result = false;
	}
	__finally
	{
		delete S;
	}
	return result;
}

bool __fastcall TSynHighlighterAttributes::SaveToFile(TCustomIniFile* Ini)
{
	bool result = false;
	Ini->WriteInteger(Name, L"Background", Background);
	Ini->WriteInteger(Name, L"Foreground", Foreground);
	Ini->WriteInteger(Name, L"Style", IntegerStyle);
	result = true;
	return result;
}

int __fastcall TSynHighlighterAttributes::GetStyleFromInt()
{
	int result = 0;
	if(Style.Contains(TFontStyle::fsBold))
		result = 1;
	else
		result = 0;
	if(Style.Contains(TFontStyle::fsItalic))
		result = result + 2;
	if(Style.Contains(TFontStyle::fsUnderline))
		result = result + 4;
	if(Style.Contains(TFontStyle::fsStrikeOut))
		result = result + 8;
	return result;
}

void __fastcall TSynHighlighterAttributes::SetStyleFromInt(int Value)
{
	if((Value & 0x1) == 0)
		Style = Synedithighlighter__8;
	else
		Style = Synedithighlighter__9;
	if((Value & 0x2) != 0)
		Style = Style + Synedithighlighter__10;
	if((Value & 0x4) != 0)
		Style = Style + Synedithighlighter__11;
	if((Value & 0x8) != 0)
		Style = Style + Synedithighlighter__12;
}

/* TSynCustomHighlighter */

__fastcall TSynCustomHighlighter::TSynCustomHighlighter(TComponent* AOwner)
 : inherited(AOwner),
			fAttributes(new TStringList()),
			fAttrChangeHooks(new TSynNotifyEventChain(this)),
			fUpdateCount(0),
			fEnabled(false),
			FOptions(nullptr),
			fCasedLine(nullptr),
			fCaseSensitive(false),
			fExpandedLine(nullptr),
			fExpandedLineLen(0),
			fExpandedTokenPos(0),
			fLine(nullptr),
			fLineLen(0),
			fLineNumber(0),
			fStringLen(0),
			fToIdent(nullptr),
			fTokenPos(0),
			fUpdateChange(false),
			Run(0),
			ExpandedRun(0),
			fOldRun(0)
{
	fAttributes->Duplicates = System::Types::dupError;
	fAttributes->Sorted = true;
	fDefaultFilter = L"";
	fEnabled = true;
	FOptions = new TSynEditHighlighterOptions(); // <-- Codehunter patch
}

__fastcall TSynCustomHighlighter::~TSynCustomHighlighter()
{
	//# inherited::Destroy();
	inherited::RemoveFreeNotifications();
	FreeHighlighterAttributes();
	delete fAttributes;
	delete fAttrChangeHooks;
	delete FOptions; // <-- Codehunter patch
}

void __fastcall TSynCustomHighlighter::BeginUpdate()
{
	++fUpdateCount;
}

void __fastcall TSynCustomHighlighter::EndUpdate()
{
	if(fUpdateCount > 0)
	{
		--fUpdateCount;
		if((fUpdateCount == 0) && fUpdateChange)
		{
			fUpdateChange = false;
			DefHighlightChange(nullptr);
		}
	}
}

void __fastcall TSynCustomHighlighter::FreeHighlighterAttributes()
{
	int i = 0;
	if(fAttributes != nullptr)
	{
		int stop = 0;
		for(stop = 0, i = fAttributes->Count - 1; i >= stop; i--)
		{
			delete ((TSynHighlighterAttributes*) fAttributes->Objects[i]);
		}
		fAttributes->Clear();
	}
}

void __fastcall TSynCustomHighlighter::Assign(TPersistent* Source)
{
	TSynCustomHighlighter* Src = nullptr;
	int i = 0;
	int j = 0;
	String AttriName;
	TSynHighlighterAttributes* SrcAttri = nullptr;
	if((Source != nullptr) && (ObjectIs(Source, TSynCustomHighlighter*)))
	{
		BeginUpdate();
		try
		{
			int stop = 0;
			Src = ((TSynCustomHighlighter*) Source);
			for(stop = AttrCount - 1, i = 0; i <= stop; i++)
			{
        // assign first attribute with the same name
				int stop1 = 0;
				AttriName = Attribute[i]->Name;
				for(stop1 = Src->AttrCount - 1, j = 0; j <= stop1; j++)
				{
					SrcAttri = Src->Attribute[j];
					if(AttriName == SrcAttri->Name)
					{
						Attribute[i]->Assign(SrcAttri);
						break;
					}
				}
			}
      // assign the sample source text only if same or descendant class
			if(Src == (TSynCustomHighlighter*) ClassType())  // todo dme check
				SampleSource = Src->SampleSource;
      //fWordBreakChars := Src.WordBreakChars; //TODO: does this make sense anyway?
			DefaultFilter = Src->DefaultFilter;
			Enabled = Src->Enabled;
		}
		__finally
		{
			EndUpdate();
		}
	}
	else
	inherited::Assign(Source);
}

void __fastcall TSynCustomHighlighter::EnumUserSettings(TStrings* Settings)
{
	Settings->Clear();
}

bool __fastcall TSynCustomHighlighter::UseUserSettings(int settingIndex)
{
	bool result = false;
	result = false;
	return result;
}

bool __fastcall TSynCustomHighlighter::LoadFromRegistry(HKEY RootKey, String Key)
{
	bool result = false;
	TBetterRegistry* r = nullptr;
	int i = 0;
	r = new TBetterRegistry();
	try
	{
		r->RootKey = RootKey;
		if(r->OpenKeyReadOnly(Key))
		{
			int stop = 0;
			result = true;
			for(stop = AttrCount - 1, i = 0; i <= stop; i++)
			{
				result = Attribute[i]->LoadFromRegistry(r) && result;
			}
		}
		else
		result = false;
	}
	__finally
	{
		delete r;
	}
	return result;
}

bool __fastcall TSynCustomHighlighter::SaveToRegistry(HKEY RootKey, String Key)
{
	bool result = false;
	TBetterRegistry* r = nullptr;
	int i = 0;
	r = new TBetterRegistry();
	try
	{
		r->RootKey = RootKey;
		if(r->OpenKey(Key, true))
		{
			int stop = 0;
			result = true;
			for(stop = AttrCount - 1, i = 0; i <= stop; i++)
			{
				result = Attribute[i]->SaveToRegistry(r) && result;
			}
		}
		else
		result = false;
	}
	__finally
	{
		delete r;
	}
	return result;
}

bool __fastcall TSynCustomHighlighter::LoadFromFile(String AFileName)
{
	bool result = false;
	TMemIniFile* AIni = nullptr;
	AIni = new TMemIniFile(AFileName);
	try
	{
		result = LoadFromIniFile(AIni);
	}
	__finally
	{
		delete AIni;
	}
	return result;
}

bool __fastcall TSynCustomHighlighter::SaveToFile(String AFileName)
{
	bool result = false;
	TMemIniFile* AIni = nullptr;
	AIni = new TMemIniFile(AFileName);
	try
	{
		result = SaveToIniFile(AIni);
	}
	__finally
	{
		delete AIni;
	}
	return result;
}

void __fastcall TSynCustomHighlighter::AddAttribute(TSynHighlighterAttributes* Attri)
{
	fAttributes->AddObject(Attri->Name, Attri);
}

void __fastcall TSynCustomHighlighter::DefHighlightChange(TObject* Sender)
{
	if(fUpdateCount > 0)
		fUpdateChange = true;
	else
	{
		if(!(ComponentState.Contains(csLoading)))
		{
			fAttrChangeHooks->Sender = Sender;
			fAttrChangeHooks->Fire();
		}
	}
}

void __fastcall TSynCustomHighlighter::DefineProperties(TFiler* Filer)
{
	inherited::DefineProperties(Filer);
}

int __fastcall TSynCustomHighlighter::GetAttribCount()
{
	int result = 0;
	result = fAttributes->Count;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynCustomHighlighter::GetAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	result = nullptr;
	if((Index >= 0) && (Index < fAttributes->Count))
		result = ((TSynHighlighterAttributes*) fAttributes->Objects[Index]);
	return result;
}

/*#static*/
TSynHighlighterCapabilities __fastcall TSynCustomHighlighter::GetCapabilities()
{
	TSynHighlighterCapabilities result;
	result = Synedithighlighter__13; //registry save/load supported by default
	return result;
}

TSynHighlighterCapabilities __fastcall TSynCustomHighlighter::GetCapabilitiesProp()
{
	TSynHighlighterCapabilities result;
	result = GetCapabilities();
	return result;
}

String __fastcall TSynCustomHighlighter::GetDefaultFilter()
{
	String result;
	result = fDefaultFilter;
	return result;
}

int __fastcall TSynCustomHighlighter::GetExpandedTokenPos()
{
	int result = 0;
	if(fExpandedLine == nullptr)
		result = fTokenPos;
	else
		result = fExpandedTokenPos;
	return result;
}

String __fastcall TSynCustomHighlighter::GetExportName()
{
	String result;
	if(FExportName == L"")
		FExportName = Syneditmiscprocs::DeleteTypePrefixAndSynSuffix(ClassName());
	result = FExportName;
	return result;
}

String __fastcall TSynCustomHighlighter::GetExpandedToken()
{
	String result;
	int Len = 0;
	if(fExpandedLine == nullptr)
	{
		result = GetToken();
		return result;
	}
	Len = ExpandedRun - fExpandedTokenPos;
	result.SetLength(Len);
	if(Len > 0)
		StrLCopy(ustr2pwchar(result, 1 - 1), fExpandedLine + fExpandedTokenPos, (unsigned int) Len);
	return result;
}

/*#static*/
String __fastcall TSynCustomHighlighter::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangUnknown;
	return result;
}

/*#static*/
String __fastcall TSynCustomHighlighter::GetLanguageName()
{
	String result;
	result = SYNS_LangUnknown;
	return result;
}

String __fastcall TSynCustomHighlighter::GetFriendlyLanguageNameProp()
{
	String result;
	result = GetFriendlyLanguageName();
	return result;
}

String __fastcall TSynCustomHighlighter::GetLanguageNameProp()
{
	String result;
	result = GetLanguageName();
	return result;
}

void* __fastcall TSynCustomHighlighter::GetRange()
{
	void* result = nullptr;
	result = nullptr;
	return result;
}

String __fastcall TSynCustomHighlighter::GetToken()
{
	String result;
	int Len = 0;
	Len = Run - fTokenPos;
	result.SetLength(Len);
	if(Len > 0)
		StrLCopy(ustr2pwchar(result, 1 - 1), fCasedLine + fTokenPos, (unsigned int) Len);
	return result;
}

int __fastcall TSynCustomHighlighter::GetTokenPos()
{
	int result = 0;
	result = fTokenPos;
	return result;
}

String __fastcall TSynCustomHighlighter::GetKeyWords(int TokenKind)
{
	String result;
	result = L"";
	return result;
}

String __fastcall TSynCustomHighlighter::GetSampleSource()
{
	String result;
	result = L"";
	return result;
}

void __fastcall TSynCustomHighlighter::HookAttrChangeEvent(TNotifyEvent ANotifyEvent)
{
	fAttrChangeHooks->Add(ANotifyEvent);
}

bool __fastcall TSynCustomHighlighter::IsCurrentToken(const String Token)
{
	bool result = false;
	int I = 0;
	PWideChar Temp = nullptr;
	Temp = fToIdent;
	if(Token.Length() == fStringLen)
	{
		int stop = 0;
		result = true;
		for(stop = fStringLen, I = 1; I <= stop; I++)
		{
			if((*Temp) != Token[I])
			{
				result = false;
				break;
			}
			++Temp;
		}
	}
	else
	result = false;
	return result;
}

bool __fastcall TSynCustomHighlighter::IsFilterStored()
{
	bool result = false;
	result = true;
	return result;
}

bool __fastcall TSynCustomHighlighter::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'_':
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		result = true;
		break;
		default:
		result = false;
		break;
	}
	result = result || CharInSet(AChar, FAdditionalIdentChars);
	result = result && !IsWordBreakChar(AChar);
	return result;
}

bool __fastcall TSynCustomHighlighter::IsKeyword(const String AKeyword)
{
	bool result = false;
	result = false;
	return result;
}

bool __fastcall TSynCustomHighlighter::IsLineEnd(int Run)
{
	bool result = false;
	result = (Run >= fLineLen) || (fLine[Run] == L'\x0a') || (fLine[Run] == L'\x0d');
	return result;
}

bool __fastcall TSynCustomHighlighter::IsWhiteChar(WideChar AChar)
{
	bool result = false;
	switch(int(AChar))
	{
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
		 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
		 case 30: case 31: case 32:
		result = true;
		break;
		default:
		result = !(IsIdentChar(AChar) || IsWordBreakChar(AChar));
		break;
	}
	return result;
}

bool __fastcall TSynCustomHighlighter::IsWordBreakChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'.':
		case L',':
		case L';':
		case L':':
		case L'\"':
		case L'\'':
		case L'´':
		case L'`':
		case L'°':
		case L'^':
		case L'!':
		case L'?':
		case L'&':
		case L'$':
		case L'@':
		case L'§':
		case L'%':
		case L'#':
		case L'~':
		case L'[':
		case L']':
		case L'(':
		case L')':
		case L'{':
		case L'}':
		case L'<':
		case L'>':
		case L'-':
		case L'=':
		case L'+':
		case L'*':
		case L'/':
		case L'\\':
		case L'|':
		result = true;
		break;
		default:
		{
			switch(int(AChar))
			{
				case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
				 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
				 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
				 case 30: case 31: case 32:
				result = true;
				break;
				default:
				result = false;
				break;
			}
		}
		break;
	}
	result = result || CharInSet(AChar, FAdditionalWordBreakChars);
	result = result && !CharInSet(AChar, FAdditionalIdentChars);
	return result;
}

bool __fastcall TSynCustomHighlighter::SaveToIniFile(TCustomIniFile* AIni)
{
	bool result = false;
	int i = 0;
	/*# with AIni do */
	{
		auto with0 = AIni;
		int stop = 0;
		result = true;
		for(stop = AttrCount - 1, i = 0; i <= stop; i++)
		{
			result = Attribute[i]->SaveToFile(AIni) && result;
		}
	}
	AIni->UpdateFile();
	return result;
}

bool __fastcall TSynCustomHighlighter::LoadFromIniFile(TCustomIniFile* AIni)
{
	bool result = false;
	int i = 0;
	/*# with AIni do */
	{
		auto with0 = AIni;
		int stop = 0;
		result = true;
		for(stop = AttrCount - 1, i = 0; i <= stop; i++)
		{
			result = Attribute[i]->LoadFromFile(AIni) && result;
		}
	}
	return result;
}

void __fastcall TSynCustomHighlighter::Next()
{
	int Delta = 0;
	if(fOldRun == Run)
		return;
	fExpandedTokenPos = ExpandedRun;
	if(fExpandedLine == nullptr)
		return;
	Delta = Run - fOldRun;
	while(Delta > 0)
	{
		while(fExpandedLine[ExpandedRun] == FillerChar)
			++ExpandedRun;
		++ExpandedRun;
		--Delta;
	}
	fOldRun = Run;
}

void __fastcall TSynCustomHighlighter::NextToEol()
{
	while(!GetEol())
		Next();
}

void __fastcall TSynCustomHighlighter::ResetRange()
{
}

void __fastcall TSynCustomHighlighter::SetAdditionalIdentChars(const TSysCharSet Value)
{
	FAdditionalIdentChars = Value;
}

void __fastcall TSynCustomHighlighter::SetAdditionalWordBreakChars(const TSysCharSet Value)
{
	FAdditionalWordBreakChars = Value;
}

void __fastcall TSynCustomHighlighter::SetAttributesOnChange(TNotifyEvent AEvent)
{
	int i = 0;
	TSynHighlighterAttributes* Attri = nullptr;
	int stop = 0;
	for(stop = 0, i = fAttributes->Count - 1; i >= stop; i--)
	{
		Attri = ((TSynHighlighterAttributes*) fAttributes->Objects[i]);
		if(Attri != nullptr)
		{
			Attri->OnChange = AEvent;
			Attri->InternalSaveDefaultValues();
		}
	}
}

void __fastcall TSynCustomHighlighter::SetLineExpandedAtWideGlyphs(const String Line, const String ExpandedLine, int LineNumber)
{
	fExpandedLineStr = ExpandedLine;
	fExpandedLine = ustr2pwchar(fExpandedLineStr);
	fExpandedLineLen = fExpandedLineStr.Length();
	DoSetLine(Line, LineNumber);
	Next();
}

void __fastcall TSynCustomHighlighter::SetLine(const String Value, int LineNumber)
{
	fExpandedLineStr = L"";
	fExpandedLine = nullptr;
	fExpandedLineLen = 0;
	DoSetLine(Value, LineNumber);
	Next();
}

void __fastcall TSynCustomHighlighter::DoSetLine(const String Value, int LineNumber)
{

	auto DoWideLowerCase = [&](const String value, String& dest) -> void 
	{

    // segregated here so case-insensitive highlighters don't have to pay the overhead
    // of the exception frame for the release of the temporary string
		dest = Sysutils::AnsiLowerCase(value);
	};
  // UnicodeStrings are not reference counted, hence we need to copy
	if(fCaseSensitive)
	{
		fLineStr = Value;
		fCasedLineStr = L"";
		fCasedLine = ustr2pwchar(fLineStr);
	}
	else
	{
		DoWideLowerCase(Value, fLineStr);
		fCasedLineStr = Value;
		fCasedLine = ustr2pwchar(fCasedLineStr);
	}
	fLine = ustr2pwchar(fLineStr);
	fLineLen = fLineStr.Length();
	Run = 0;
	ExpandedRun = 0;
	fOldRun = Run;
	fLineNumber = LineNumber;
}

void __fastcall TSynCustomHighlighter::SetRange(void* Value)
{
}

void __fastcall TSynCustomHighlighter::SetDefaultFilter(String Value)
{
	fDefaultFilter = Value;
}

void __fastcall TSynCustomHighlighter::SetSampleSource(String Value)
{

  // TODO: sure this should be empty?
}

void __fastcall TSynCustomHighlighter::UnhookAttrChangeEvent(TNotifyEvent ANotifyEvent)
{
	fAttrChangeHooks->Remove(ANotifyEvent);
}

void __fastcall TSynCustomHighlighter::SetEnabled(bool Value)
{
	if(fEnabled != Value)
	{
		fEnabled = Value;
		DefHighlightChange(nullptr);
	}
}

void __fastcall TSynCustomHighlighter::Loaded()
{
	inherited::Loaded();
	DefHighlightChange(nullptr);
}

// Pos and Result are 1-based (i.e. positions in a string not a PWideChar)

int __fastcall TSynCustomHighlighter::PosToExpandedPos(int Pos)
{
	int result = 0;
	int i = 0;
	if(fExpandedLine == nullptr)
	{
		result = Pos;
		return result;
	}
	result = 0;
	i = 0;
	while(i < Pos)
	{
		while(fExpandedLine[result] == FillerChar)
			++result;
		++result;
		++i;
	}
	return result;
}
static bool SynEditHighlighter_Initialized = false;

void SynEditHighlighter_initialization()
{
	if(SynEditHighlighter_Initialized)
		return;
	
	SynEditHighlighter_Initialized = true;
	
	G_PlaceableHighlighters = new TSynHighlighterList();
}
static bool SynEditHighlighter_Finalized = false;

void SynEditHighlighter_finalization()
{
	if(SynEditHighlighter_Finalized)
		return;
	
	SynEditHighlighter_Finalized = true;
	
	delete G_PlaceableHighlighters;
	G_PlaceableHighlighters = nullptr;
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynEditHighlighter

