#ifndef SynEditHighlighterH
#define SynEditHighlighterH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include <Winapi.Windows.hpp>
#include <System.Win.Registry.hpp>
#include <System.IniFiles.hpp>
#include "SynEditTypes.h"
#include "SynEditMiscClasses.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "SynEditHighlighterOptions.h"

namespace Synedithighlighter
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/
Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditHighlighter.pas, released 2000-04-07.

The Original Code is based on mwHighlighter.pas by Martin Waldenburg, part of
the mwEdit component suite.
Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
Unicode translation by Maël Hörz.
Options property added by CodehunterWorks
All Rights Reserved.

Contributors to the SynEdit and mwEdit projects are listed in the
Contributors.txt file.

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
typedef Syneditmiscclasses::TBetterRegistry TBetterRegistry;

class TSynHighlighterAttributes : public System::Classes::TPersistent
{
private:
	TColor FBackground;
	TColor fBackgroundDefault;
	TColor FForeground;
	TColor fForegroundDefault;
	String FFriendlyName;
	String FName;
	TFontStyles FStyle;
	TFontStyles fStyleDefault;
	System::Classes::TNotifyEvent FOnChange;
	virtual void __fastcall Changed();
	bool __fastcall GetBackgroundColorStored();
	bool __fastcall GetForegroundColorStored();
	bool __fastcall GetFontStyleStored();
	void __fastcall SetBackground(TColor Value);
	void __fastcall SetForeground(TColor Value);
	void __fastcall SetStyle(TFontStyles Value);
	int __fastcall GetStyleFromInt();
	void __fastcall SetStyleFromInt(int Value);
public:
	typedef System::Classes::TPersistent inherited;	
	#include "SynEditHighlighter_friends.inc"
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall AssignColorAndStyle(TSynHighlighterAttributes* Source);
	__fastcall TSynHighlighterAttributes(String AName, String AFriendlyName);
	void __fastcall InternalSaveDefaultValues();
	virtual bool __fastcall LoadFromBorlandRegistry(HKEY RootKey, String AttrKey, String AttrName, bool OldStyle);
	bool __fastcall LoadFromRegistry(TBetterRegistry* reg);
	bool __fastcall SaveToRegistry(TBetterRegistry* reg);
	bool __fastcall LoadFromFile(System::Inifiles::TCustomIniFile* Ini);
	bool __fastcall SaveToFile(System::Inifiles::TCustomIniFile* Ini);
	void __fastcall SetColors(TColor Foreground, TColor Background);
	__property String FriendlyName = { read = FFriendlyName };
	__property int IntegerStyle = { read = GetStyleFromInt, write = SetStyleFromInt };
	__property String Name = { read = FName };
	__property System::Classes::TNotifyEvent OnChange = { read = FOnChange, write = FOnChange };
__published:
	__property TColor Background = { read = FBackground, write = SetBackground, stored = GetBackgroundColorStored };
	__property TColor Foreground = { read = FForeground, write = SetForeground, stored = GetForegroundColorStored };
	__property TFontStyles Style = { read = FStyle, write = SetStyle, stored = GetFontStyleStored };
public:
	__fastcall TSynHighlighterAttributes();
}; // supports Enum/UseUserSettings
      // supports LoadFrom/SaveToRegistry
enum TSynHighlighterCapability {hcUserSettings,
                                hcRegistry };
typedef System::Set<TSynHighlighterCapability, hcUserSettings, hcRegistry> TSynHighlighterCapabilities;
const int SYN_ATTR_COMMENT = 0;
const int SYN_ATTR_IDENTIFIER = 1;
const int SYN_ATTR_KEYWORD = 2;
const int SYN_ATTR_STRING = 3;
const int SYN_ATTR_WHITESPACE = 4;
const int SYN_ATTR_SYMBOL = 5;

class TSynCustomHighlighter : public System::Classes::TComponent
{
private:
	System::Classes::TStringList* fAttributes;
	Syneditmiscclasses::TSynNotifyEventChain* fAttrChangeHooks;
	int FUpdateCount;
	bool FEnabled;
	System::Sysutils::TSysCharSet FAdditionalWordBreakChars;
	System::Sysutils::TSysCharSet FAdditionalIdentChars;
	String FExportName;
	Synedithighlighteroptions::TSynEditHighlighterOptions* fOptions;
	String __fastcall GetExportName();
	void __fastcall SetEnabled(bool Value);
	void __fastcall SetAdditionalIdentChars(const System::Sysutils::TSysCharSet Value);
	void __fastcall SetAdditionalWordBreakChars(const System::Sysutils::TSysCharSet Value);
protected:
	PWideChar fCasedLine;
	String fCasedLineStr;
	bool FCaseSensitive;
	String fDefaultFilter;
	PWideChar fExpandedLine;
	int fExpandedLineLen;
	String fExpandedLineStr;
	int fExpandedTokenPos;
	PWideChar fLine;
	int fLineLen;
	String fLineStr;
	int fLineNumber;
	int fStringLen;
	PWideChar fToIdent;
	int fTokenPos;
	bool fUpdateChange;
	int Run;
	int ExpandedRun;
	int fOldRun;
	virtual void __fastcall Loaded();
	void __fastcall addAttribute(TSynHighlighterAttributes* Attri);
	void __fastcall DefHighlightChange(TObject* Sender);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	void __fastcall FreeHighlighterAttributes();
	virtual int __fastcall GetAttribCount();
	virtual TSynHighlighterAttributes* __fastcall getAttribute(int Index);
	virtual TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index){return nullptr;} // = 0;
	virtual String __fastcall GetDefaultFilter();
	virtual String __fastcall GetSampleSource();
	virtual void __fastcall DoSetLine(const String Value, int LineNumber);
	virtual bool __fastcall IsCurrentToken(const String Token);
	virtual bool __fastcall IsFilterStored();
	virtual bool __fastcall IsLineEnd(int Run);
	void __fastcall SetAttributesOnChange(System::Classes::TNotifyEvent AEvent);
	virtual void __fastcall SetDefaultFilter(String Value);
	virtual void __fastcall SetSampleSource(String Value);
	TSynHighlighterCapabilities __fastcall GetCapabilitiesProp();
	String __fastcall GetFriendlyLanguageNameProp();
	String __fastcall GetLanguageNameProp();
public:
	typedef System::Classes::TComponent inherited;	
	#include "SynEditHighlighter_friends.inc"
	__classmethod virtual TSynHighlighterCapabilities __fastcall GetCapabilities();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__classmethod virtual String __fastcall GetLanguageName();
	__fastcall TSynCustomHighlighter(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynCustomHighlighter();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	virtual bool __fastcall GetEol(){return false;} // = 0;
	virtual String __fastcall GetExpandedToken();
	virtual int __fastcall GetExpandedTokenPos();
	virtual String __fastcall GetKeyWords(int TokenKind);
	virtual void* __fastcall GetRange();
	virtual String __fastcall GetToken();
	virtual TSynHighlighterAttributes* __fastcall GetTokenAttribute(){return nullptr;} // = 0;
	virtual int __fastcall GetTokenKind(){return 0;} // = 0;
	virtual int __fastcall GetTokenPos();
	virtual bool __fastcall IsKeyword(const String AKeyword);
	virtual void __fastcall Next();
	void __fastcall NextToEol();
	int __fastcall PosToExpandedPos(int Pos);
	virtual void __fastcall SetLineExpandedAtWideGlyphs(const String Line, const String ExpandedLine, int LineNumber);
	virtual void __fastcall SetLine(const String Value, int LineNumber);
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
	virtual bool __fastcall UseUserSettings(int settingIndex);
	virtual void __fastcall EnumUserSettings(System::Classes::TStrings* Settings);
	virtual bool __fastcall LoadFromRegistry(HKEY RootKey, String key);
	virtual bool __fastcall SaveToRegistry(HKEY RootKey, String key);
	bool __fastcall LoadFromIniFile(System::Inifiles::TCustomIniFile* AIni);
	bool __fastcall SaveToIniFile(System::Inifiles::TCustomIniFile* AIni);
	bool __fastcall LoadFromFile(String AFileName);
	bool __fastcall SaveToFile(String AFileName);
	void __fastcall HookAttrChangeEvent(System::Classes::TNotifyEvent ANotifyEvent);
	void __fastcall UnhookAttrChangeEvent(System::Classes::TNotifyEvent ANotifyEvent);
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual bool __fastcall IsWhiteChar(WideChar AChar);
	virtual bool __fastcall IsWordBreakChar(WideChar AChar);
	__property String FriendlyLanguageName = { read = GetFriendlyLanguageNameProp };
	__property String LanguageName = { read = GetLanguageNameProp };
	__property System::Sysutils::TSysCharSet AdditionalIdentChars = { read = FAdditionalIdentChars, write = SetAdditionalIdentChars };
	__property System::Sysutils::TSysCharSet AdditionalWordBreakChars = { read = FAdditionalWordBreakChars, write = SetAdditionalWordBreakChars };
	__property int AttrCount = { read = GetAttribCount };
	__property TSynHighlighterAttributes* Attribute[int Index] = { read = getAttribute };
	__property TSynHighlighterCapabilities Capabilities = { read = GetCapabilitiesProp };
	__property String SampleSource = { read = GetSampleSource, write = SetSampleSource };
	__property TSynHighlighterAttributes* CommentAttribute = { index = SYN_ATTR_COMMENT, read = GetDefaultAttribute };
	__property TSynHighlighterAttributes* IdentifierAttribute = { index = SYN_ATTR_IDENTIFIER, read = GetDefaultAttribute };
	__property TSynHighlighterAttributes* KeywordAttribute = { index = SYN_ATTR_KEYWORD, read = GetDefaultAttribute };
	__property TSynHighlighterAttributes* StringAttribute = { index = SYN_ATTR_STRING, read = GetDefaultAttribute };
	__property TSynHighlighterAttributes* SymbolAttribute = { index = SYN_ATTR_SYMBOL, read = GetDefaultAttribute };
	__property TSynHighlighterAttributes* WhitespaceAttribute = { index = SYN_ATTR_WHITESPACE, read = GetDefaultAttribute };
	__property String ExportName = { read = GetExportName };
__published:
	__property String DefaultFilter = { read = GetDefaultFilter, write = SetDefaultFilter, stored = IsFilterStored };
	__property bool Enabled = { read = FEnabled, write = SetEnabled, default = true };
	__property TSynEditHighlighterOptions* Options = { read = fOptions, write = fOptions }; // <-- Codehunter patch
};

typedef System::TMetaClass* TSynCustomHighlighterClass;

class TSynHighlighterList : public System::Classes::TList
{
	#include "SynEditHighlighter_friends.inc"
	friend void __fastcall RegisterPlaceableHighlighter(TSynCustomHighlighterClass Highlighter);
public:
	typedef System::Classes::TList inherited;	
private:
	System::Classes::TList* hlList;
	TSynCustomHighlighterClass __fastcall GetItem(int Index);
public:
	__fastcall TSynHighlighterList();
	virtual __fastcall ~TSynHighlighterList();
	int __fastcall Count();
	int __fastcall FindByFriendlyName(String FriendlyName);
	int __fastcall FindByName(String Name);
	int __fastcall FindByClass(System::Classes::TComponent* Comp);
	__property TSynCustomHighlighterClass Items[int Index] = { read = GetItem/*# default */ };
};
void __fastcall RegisterPlaceableHighlighter(TSynCustomHighlighterClass Highlighter);
TSynHighlighterList* __fastcall GetPlaceableHighlighters();

void SynEditHighlighter_initialization();
void SynEditHighlighter_finalization();


}  // namespace SynEditHighlighter

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synedithighlighter;
#endif


#endif // SynEditHighlighterH

