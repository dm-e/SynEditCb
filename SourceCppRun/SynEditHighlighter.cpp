
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
using namespace System;
using namespace System::Classes;
using namespace System::Inifiles;
using namespace System::Sysutils;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Synedithighlighter
{
#define SynEditHighlighter__0 TFontStyles()
#define SynEditHighlighter__1 (TFontStyles() << TFontStyle::fsBold)
#define SynEditHighlighter__2 (TFontStyles() << TFontStyle::fsItalic)
#define SynEditHighlighter__3 (TFontStyles() << TFontStyle::fsUnderline)
#define SynEditHighlighter__4 TFontStyles()
#define SynEditHighlighter__5 (TFontStyles() << TFontStyle::fsBold)
#define SynEditHighlighter__6 (TFontStyles() << TFontStyle::fsItalic)
#define SynEditHighlighter__7 (TFontStyles() << TFontStyle::fsUnderline)
#define SynEditHighlighter__8 TFontStyles()
#define SynEditHighlighter__9 (TFontStyles() << TFontStyle::fsBold)
#define SynEditHighlighter__10 (TFontStyles() << TFontStyle::fsItalic)
#define SynEditHighlighter__11 (TFontStyles() << TFontStyle::fsUnderline)
#define SynEditHighlighter__12 (TFontStyles() << TFontStyle::fsStrikeOut)
#define SynEditHighlighter__13 (TSynHighlighterCapabilities() << TSynHighlighterCapability::hcRegistry)

__fastcall TSynHighlighterAttributes::TSynHighlighterAttributes() {}



/* THighlighterList */

int __fastcall TSynHighlighterList::Count()
{
	int result = 0;
	result = hlList->Count;
	return result;
}

__fastcall TSynHighlighterList::TSynHighlighterList()
 : hlList(new System::Classes::TList())
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

void __fastcall RegisterPlaceableHighlighter(TSynCustomHighlighterClass Highlighter)
{
	if(G_PlaceableHighlighters->hlList->IndexOf(Highlighter) < 0)
		G_PlaceableHighlighters->hlList->Add(Highlighter);
}

/* TSynHighlighterAttributes */

void __fastcall TSynHighlighterAttributes::Assign(TPersistent* Source)
{
	if(ObjectIs(Source, TSynHighlighterAttributes*))
	{
		FName = ((TSynHighlighterAttributes*) Source)->FName;
		AssignColorAndStyle(((TSynHighlighterAttributes*) Source));
	}
	else
	inherited::Assign(Source);
}

void __fastcall TSynHighlighterAttributes::AssignColorAndStyle(TSynHighlighterAttributes* Source)
{
	bool bChanged = false;
	bChanged = false;
	if(FBackground != Source->FBackground)
	{
		FBackground = Source->FBackground;
		bChanged = true;
	}
	if(FForeground != Source->FForeground)
	{
		FForeground = Source->FForeground;
		bChanged = true;
	}
	if(FStyle != Source->FStyle)
	{
		FStyle = Source->FStyle;
		bChanged = true;
	}
	if(bChanged)
		Changed();
}

void __fastcall TSynHighlighterAttributes::Changed()
{
	if(ASSIGNED(FOnChange))
		FOnChange(this);
}

__fastcall TSynHighlighterAttributes::TSynHighlighterAttributes(String AName, String AFriendlyName)
 : FBackground((TColor) 0),
			fBackgroundDefault((TColor) 0),
			FForeground((TColor) 0),
			fForegroundDefault((TColor) 0)
{
	//# inherited::Create();
	Background = clNone;
	Foreground = clNone;
	FName = AName;
	FFriendlyName = AFriendlyName;
}

bool __fastcall TSynHighlighterAttributes::GetBackgroundColorStored()
{
	bool result = false;
	result = FBackground != fBackgroundDefault;
	return result;
}

bool __fastcall TSynHighlighterAttributes::GetForegroundColorStored()
{
	bool result = false;
	result = FForeground != fForegroundDefault;
	return result;
}

bool __fastcall TSynHighlighterAttributes::GetFontStyleStored()
{
	bool result = false;
	result = FStyle != fStyleDefault;
	return result;
}

void __fastcall TSynHighlighterAttributes::InternalSaveDefaultValues()
{
	fForegroundDefault = FForeground;
	fBackgroundDefault = FBackground;
	fStyleDefault = FStyle;
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
	const TColor Pal16[16/*# range 0..15*/] = {clBlack, clMaroon, clGreen, clOlive, clNavy, clPurple, clTeal, clLtGray, clDkGray, clRed, clLime, clYellow, clBlue
																				, clFuchsia, clAqua, clWhite};

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
			int P = 0;
			P = Pos(L",", Name);
			if(P == 0)
				P = (int) (Name.Length() + 1);
			result = Name.SubString(1, P - 1);
			Name = Name.SubString(P + 1, Name.Length() - P);
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
									Background = clWindow;
								else
									Background = Pal16[StrToInt(bgIndex16)];
								if(fgDefault == L"1")
									Foreground = clWindowText;
								else
									Foreground = Pal16[StrToInt(fgIndex16)];
								Style = SynEditHighlighter__0;
								if(Pos(L"B", fontStyle) > 0)
									Style = Style + SynEditHighlighter__1;
								if(Pos(L"I", fontStyle) > 0)
									Style = Style + SynEditHighlighter__2;
								if(Pos(L"U", fontStyle) > 0)
									Style = Style + SynEditHighlighter__3;
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
		int FgColor = 0;
		int BGColor = 0;
		String FONTBOLD;
		String FONTITALIC;
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
								FgColor = Pal16[with0->ReadInteger(L"Foreground Color")];
							else
							{
								if(with0->ValueExists(L"Foreground Color New"))
									FgColor = StringToColor(with0->ReadString(L"Foreground Color New"));
								else
									return result;
							}
							if(with0->ValueExists(L"Background Color"))
								BGColor = Pal16[with0->ReadInteger(L"Background Color")];
							else
							{
								if(with0->ValueExists(L"Background Color New"))
									BGColor = StringToColor(with0->ReadString(L"Background Color New"));
								else
									return result;
							}
							if(with0->ValueExists(L"Bold"))
								FONTBOLD = with0->ReadString(L"Bold");
							else
								return result;
							if(with0->ValueExists(L"Italic"))
								FONTITALIC = with0->ReadString(L"Italic");
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
								Background = clWindow;
							else
								Background = (TColor) BGColor;
							if(IsTrue(fgDefault))
								Foreground = clWindowText;
							else
								Foreground = (TColor) FgColor;
							Style = SynEditHighlighter__4;
							if(IsTrue(FONTBOLD))
								Style = Style + SynEditHighlighter__5;
							if(IsTrue(FONTITALIC))
								Style = Style + SynEditHighlighter__6;
							if(IsTrue(fontUnderline))
								Style = Style + SynEditHighlighter__7;
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
	if(FBackground != Value)
	{
		FBackground = Value;
		Changed();
	}
}

void __fastcall TSynHighlighterAttributes::SetColors(TColor Foreground, TColor Background)
{
	if((FForeground != Foreground) || (FBackground != Background))
	{
		FForeground = Foreground;
		FBackground = Background;
		Changed();
	}
}

void __fastcall TSynHighlighterAttributes::SetForeground(TColor Value)
{
	if(FForeground != Value)
	{
		FForeground = Value;
		Changed();
	}
}

void __fastcall TSynHighlighterAttributes::SetStyle(TFontStyles Value)
{
	if(FStyle != Value)
	{
		FStyle = Value;
		Changed();
	}
}

bool __fastcall TSynHighlighterAttributes::LoadFromRegistry(TBetterRegistry* reg)
{
	bool result = false;
	String key;
	key = reg->CurrentPath;
	if(reg->OpenKeyReadOnly(Name))
	{
		if(reg->ValueExists(L"Background"))
			Background = (TColor) reg->ReadInteger(L"Background");
		if(reg->ValueExists(L"Foreground"))
			Foreground = (TColor) reg->ReadInteger(L"Foreground");
		if(reg->ValueExists(L"Style"))
			IntegerStyle = reg->ReadInteger(L"Style");
		reg->OpenKeyReadOnly(String(L"\\") + key);
		result = true;
	}
	else
	result = false;
	return result;
}

bool __fastcall TSynHighlighterAttributes::SaveToRegistry(TBetterRegistry* reg)
{
	bool result = false;
	String key;
	key = reg->CurrentPath;
	if(reg->OpenKey(Name, true))
	{
		reg->WriteInteger(L"Background", Background);
		reg->WriteInteger(L"Foreground", Foreground);
		reg->WriteInteger(L"Style", IntegerStyle);
		reg->OpenKey(String(L"\\") + key, false);
		result = true;
	}
	else
	result = false;
	return result;
}

bool __fastcall TSynHighlighterAttributes::LoadFromFile(TCustomIniFile* Ini)
{
	bool result = false;
	TStringList* s = nullptr;
	s = new TStringList();
	try
	{
		Ini->ReadSection(Name, s);
		if(s->Count > 0)
		{
			if(s->IndexOf(L"Background") !=  - 1)
				Background = (TColor) Ini->ReadInteger(Name, L"Background", Background);
			if(s->IndexOf(L"Foreground") !=  - 1)
				Foreground = (TColor) Ini->ReadInteger(Name, L"Foreground", Foreground);
			if(s->IndexOf(L"Style") !=  - 1)
				IntegerStyle = Ini->ReadInteger(Name, L"Style", IntegerStyle);
			result = true;
		}
		else
		result = false;
	}
	__finally
	{
		delete s;
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
		Style = SynEditHighlighter__8;
	else
		Style = SynEditHighlighter__9;
	if((Value & 0x2) != 0)
		Style = Style + SynEditHighlighter__10;
	if((Value & 0x4) != 0)
		Style = Style + SynEditHighlighter__11;
	if((Value & 0x8) != 0)
		Style = Style + SynEditHighlighter__12;
}

/* TSynCustomHighlighter */

__fastcall TSynCustomHighlighter::TSynCustomHighlighter(TComponent* AOwner)
 : inherited(AOwner),
			fAttributes(new TStringList()),
			fAttrChangeHooks(new TSynNotifyEventChain(this)),
			FUpdateCount(0),
			FEnabled(false),
			fOptions(nullptr),
			fCasedLine(nullptr),
			FCaseSensitive(false),
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
	fAttributes->Duplicates = System::Classes::dupError;
	fAttributes->Sorted = true;
	fDefaultFilter = L"";
	FEnabled = true;
	fOptions = new TSynEditHighlighterOptions(); // <-- Codehunter patch
}

__fastcall TSynCustomHighlighter::~TSynCustomHighlighter()
{
	//# inherited::Destroy();
	FreeHighlighterAttributes();
	delete fAttributes;
	delete fAttrChangeHooks;
	delete fOptions; // <-- Codehunter patch
}


void __fastcall TSynCustomHighlighter::BeginUpdate()
{
	++FUpdateCount;
}

void __fastcall TSynCustomHighlighter::EndUpdate()
{
	if(FUpdateCount > 0)
	{
		--FUpdateCount;
		if((FUpdateCount == 0) && fUpdateChange)
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

bool __fastcall TSynCustomHighlighter::LoadFromRegistry(HKEY RootKey, String key)
{
	bool result = false;
	TBetterRegistry* R = nullptr;
	int i = 0;
	R = new TBetterRegistry();
	try
	{
		R->RootKey = RootKey;
		if(R->OpenKeyReadOnly(key))
		{
			int stop = 0;
			result = true;
			for(stop = AttrCount - 1, i = 0; i <= stop; i++)
			{
				result = Attribute[i]->LoadFromRegistry(R) && result;
			}
		}
		else
		result = false;
	}
	__finally
	{
		delete R;
	}
	return result;
}

bool __fastcall TSynCustomHighlighter::SaveToRegistry(HKEY RootKey, String key)
{
	bool result = false;
	TBetterRegistry* R = nullptr;
	int i = 0;
	R = new TBetterRegistry();
	try
	{
		R->RootKey = RootKey;
		if(R->OpenKey(key, true))
		{
			int stop = 0;
			result = true;
			for(stop = AttrCount - 1, i = 0; i <= stop; i++)
			{
				result = Attribute[i]->SaveToRegistry(R) && result;
			}
		}
		else
		result = false;
	}
	__finally
	{
		delete R;
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

void __fastcall TSynCustomHighlighter::addAttribute(TSynHighlighterAttributes* Attri)
{
	fAttributes->AddObject(Attri->Name, Attri);
}

void __fastcall TSynCustomHighlighter::DefHighlightChange(TObject* Sender)
{
	if(FUpdateCount > 0)
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

TSynHighlighterAttributes* __fastcall TSynCustomHighlighter::getAttribute(int Index)
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
	result = SynEditHighlighter__13; //registry save/load supported by default
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
	int i = 0;
	PWideChar Temp = nullptr;
	Temp = fToIdent;
	if(Token.Length() == fStringLen)
	{
		int stop = 0;
		result = true;
		for(stop = fStringLen, i = 1; i <= stop; i++)
		{
			if((*Temp) != Token[i])
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
	int delta = 0;
	if(fOldRun == Run)
		return;
	fExpandedTokenPos = ExpandedRun;
	if(fExpandedLine == nullptr)
		return;
	delta = Run - fOldRun;
	while(delta > 0)
	{
		while(fExpandedLine[ExpandedRun] == FillerChar)
			++ExpandedRun;
		++ExpandedRun;
		--delta;
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
	fExpandedLineLen = (int) fExpandedLineStr.Length();
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

	auto DoWideLowerCase = [&](const String Value, String& Dest) -> void 
	{

    // segregated here so case-insensitive highlighters don't have to pay the overhead
    // of the exception frame for the release of the temporary string
		Dest = Sysutils::AnsiLowerCase(Value);
	};
  // UnicodeStrings are not reference counted, hence we need to copy
	if(FCaseSensitive)
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
	fLineLen = (int) fLineStr.Length();
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
	if(FEnabled != Value)
	{
		FEnabled = Value;
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
class SynEditHighlighter_unit
{
public:
	SynEditHighlighter_unit()
	{
		SynEditHighlighter_initialization();
	}
	~SynEditHighlighter_unit(){SynEditHighlighter_finalization(); }
};

SynEditHighlighter_unit _SynEditHighlighter_unit;

}  // namespace Synedithighlighter

