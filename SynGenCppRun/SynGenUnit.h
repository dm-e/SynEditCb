#ifndef SynGenUnitH
#define SynGenUnitH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include "GenLex.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
//#include "SynUnicode.h"
#include "d2c_sysfile.h"


/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynGenUnit.pas, released 2000-04-19.
Description: Generator for skeletons of HighLighters to use in SynEdit,
drived by a simple grammar.

The Original Code is based on SynGenU.pas by Martin Waldenburg, part of
the mwEdit component suite.
Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
Portions created by Pieter Polak are Copyright (C) 2001 Pieter Polak.
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

$Id: SynGenUnit.pas,v 1.18.2.11 2008/10/25 23:30:31 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Todo:
  - Remember the last opened MSG file
  - Double-click a MSG file opens SynGen
  - Add user-defined default attributes to TSynXXXSyn.Create
  - SynEdit to edit the MSG file (using the highlighter for MSG files)
  - Store language names list and attribute names list in INI file
  - SynEdit with Pascal highlighter to preview the created highlighter source
  - Allow to define different type of keywords in MSG file

Known Issues:
-------------------------------------------------------------------------------*/
extern int mKeyHashTable[256/*# range #0..#255*/];
extern int mSKeyHashTable[256/*# range #0..#255*/];

class TLexKeys : public System::TObject
{
	#include "SynGenUnit_friends.inc"
public:
	typedef TObject inherited;	
	String KeyName;
	unsigned int key;
	String TokenType;
	__fastcall TLexKeys();
};

class TLexCharsets : public System::TObject
{
	#include "SynGenUnit_friends.inc"
public:
	typedef TObject inherited;	
	String SetName;
	String Charset;
	String ProcData;
	String FuncData;
	__fastcall TLexCharsets();
};

class TLexEnclosedBy : public System::TObject
{
	#include "SynGenUnit_friends.inc"
public:
	typedef TObject inherited;	
	String TokenName;
	String ProcName;
	String StartsWith;
	String EndsWith;
	bool MultiLine;
	__fastcall TLexEnclosedBy();
};

class TLexDefaultAttri : public System::TObject
{
	#include "SynGenUnit_friends.inc"
public:
	typedef TObject inherited;	
	String Style;
	String Foreground;
	String Background;
	__fastcall TLexDefaultAttri();
};

class TFrmMain : public TForm
{
__published:
	TButton* BtnStart;
	TOpenDialog* OpenDialog;
	TPageControl* PageControl;
	TTabSheet* TabLanguage;
	TLabel* LblFilter;
	TComboBox* CboFilter;
	TLabel* LblLangName;
	TComboBox* CboLangName;
	TTabSheet* TabAttributes;
	TGroupBox* GrpAttrNames;
	TLabel* LblIdentifier;
	TLabel* LblReservedWord;
	TComboBox* CboAttrIdentifier;
	TComboBox* CboAttrReservedWord;
	TLabel* LblUnknownTokenAttr;
	TComboBox* CboUnknownTokenAttr;
	TTabSheet* TabFields;
	TButton* btnAdd;
	TButton* btnDelete;
	TEdit* EditAddField;
	TListBox* ListBoxFields;
	TMainMenu* MainMenu;
	TMenuItem* MnuFile;
	TMenuItem* MnuOpen;
	TMenuItem* MnuExit;
	TTabSheet* TabHighlighter;
	TLabel* LblAuthor;
	TLabel* LblDescription;
	TLabel* LblVersion;
	TEdit* EditAuthor;
	TEdit* EditDescription;
	TEdit* EditVersion;
	TMenuItem* MnuStart;
	TCheckBox* ChkGetKeyWords;
	TCheckBox* ChkGPLHeader;
	void __fastcall BtnStartClick(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormDestroy(TObject* Sender);
	void __fastcall CboLangNameChange(TObject* Sender);
	void __fastcall ListBoxFieldsClick(TObject* Sender);
	void __fastcall btnAddClick(TObject* Sender);
	void __fastcall btnDeleteClick(TObject* Sender);
	void __fastcall EditAddFieldChange(TObject* Sender);
	void __fastcall EditAddFieldKeyPress(TObject* Sender, Char& key);
	void __fastcall MnuExitClick(TObject* Sender);
	void __fastcall MnuOpenClick(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
private:
	String LexName;
	String IdentPre;
	String IdentStart;
	String IdentContent;
	String FFileName;
	String IniFile;
	d2c_system::TTextRec OutFile;
	bool Sensitivity;
	String LexFileContents;
	TGenLex* Lex;
	TList* KeyList;
	TList* SetList;
	TList* EnclosedList;
	TStringList* SampleSourceList;
	TStringList* IdentList;
	void __fastcall ClearAll();
	String __fastcall GetFilterName();
	String __fastcall GetLangName();
	String __fastcall FilterInvalidChars(const String Value);
	void __fastcall MakeHashTable();
	void __fastcall MakeSensitiveHashTable();
	void __fastcall FillKeyList();
	void __fastcall FillTokenTypeList();
	void __fastcall OutFileCreate(String InName);
	void __fastcall ParseCharsets();
	void __fastcall ParseEnclosedBy();
	void __fastcall ParseSampleSource();
	void __fastcall RetrieveCharset();
	void __fastcall RetrieveEnclosedBy();
	void __fastcall RetrieveSampleSource();
	void __fastcall WriteSettings();
	bool __fastcall PerformFileOpen();
	void __fastcall WriteRest();
	bool __fastcall KeywordsAreAllAlphaNumAndDifferent();
	String __fastcall GetFriendlyLangName();
public:
	typedef Vcl::Forms::TForm inherited;	
	#include "SynGenUnit_friends.inc"
	__fastcall TFrmMain(System::Classes::TComponent* AOwner);
};
extern PACKAGE TFrmMain* FrmMain;
#endif // SynGenUnitH

