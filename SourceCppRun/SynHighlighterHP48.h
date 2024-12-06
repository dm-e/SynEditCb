/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterHP48.pas, released 2000-06-23.
The Original Code is based on the cbHPSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Cyrille de Brebisson.
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

$Id: SynHighlighterHP48.pas,v 1.10.2.9 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides SynEdit with a HP48 assembler syntax highlighter.)
@author(Cyrille de Brebisson <cyrille_de-brebisson@aus.hp.com>, converted to SynEdit by David Muir <dhm@dmsoftware.co.uk>)
@created(1998-12, converted to SynEdit 2000-06-23)
@lastmod(2012-09-12)
The unit SynHighlighterHP48 provides SynEdit with a HP48 assembler highlighter.
*/
#ifndef SynHighlighterHP48H
#define SynHighlighterHP48H

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterhp48
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterHP48.pas, released 2000-06-23.
The Original Code is based on the cbHPSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Cyrille de Brebisson.
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

$Id: SynHighlighterHP48.pas,v 1.10.2.9 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides SynEdit with a HP48 assembler syntax highlighter.)
@author(Cyrille de Brebisson <cyrille_de-brebisson@aus.hp.com>, converted to SynEdit by David Muir <dhm@dmsoftware.co.uk>)
@created(1998-12, converted to SynEdit 2000-06-23)
@lastmod(2012-09-12)
The unit SynHighlighterHP48 provides SynEdit with a HP48 assembler highlighter.
*/

/*------------------------------------------------------------------------------*/
/* Common compiler defines                                                      */
/* (remove the dot in front of a define to enable it)                           */
/*------------------------------------------------------------------------------*/

/*$B-,H+*/ // defaults are short evaluation of boolean values and long strings

/*.$DEFINE SYN_DEVELOPMENT_CHECKS*/ // additional tests for debugging
  

/*------------------------------------------------------------------------------*/
/* Pull in all defines from SynEditJedi.inc (must be done after the common      */
/* compiler defines to  work correctly). Use SynEdit-prefix to avoid problems   */
/* with other versions of jedi.inc in the search-path.                          */
/*------------------------------------------------------------------------------*/

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

/*------------------------------------------------------------------------------*/
/*  Please change this to suit your needs (to activate an option remove the dot */
/*  in front of a DEFINE)                                                       */
/*------------------------------------------------------------------------------*/

// "Heredoc" syntax highlighting
// If you enable the following statement and use highlighter(s) that have
// support for "Heredoc" strings as scheme(s) in SynMultiSyn, you must
// implement your own SynMultiSyn OnCustomRange event handler in order to
// properly store Range State information
/*.$DEFINE SYN_HEREDOC*/

// Turn this off if you don't need complex script support, since it is slower
/*.$DEFINE SYN_UNISCRIBE*/

// $Id: SynEdit.inc,v 1.16.2.19 2009/06/14 13:41:44 maelh Exp $
const int NbSubList = 128;
class TSpeedStringList;

class TSpeedListObject : public System::TObject
{
	#include "SynHighlighterHP48_friends.inc"
public:
	typedef System::TObject inherited;
protected:
	String FName;
	TSpeedStringList* FSpeedList;
	TObject* FObject;
	virtual void __fastcall SetName(const String Value);
public:
	__property String Name = { read = FName, write = SetName };
	__fastcall TSpeedListObject(String name);
	virtual __fastcall ~TSpeedListObject();
	__property TSpeedStringList* SpeedList = { read = FSpeedList, write = FSpeedList };
	__property TObject* Pointer = { read = FObject, write = FObject };
	__fastcall TSpeedListObject();
};
typedef TSpeedListObject* TSpeedListObjects[1/*# range 0..0*/];
typedef TSpeedListObjects* PSpeedListObjects;

class TSpeedStringList : public System::TObject
{
	#include "SynHighlighterHP48_friends.inc"
public:
	typedef System::TObject inherited;
private:
	String __fastcall GetText();
	void __fastcall SetText(const String Value);
	TObject* __fastcall GetInObject(int Index);
	void __fastcall SetInObject(int Index, TObject* const Value);
protected:
	TNotifyEvent FOnChange;
	int SumOfUsed[128/*# range 0..NbSubList-1*/];
	int DatasUsed[128/*# range 0..NbSubList-1*/];
	PSpeedListObjects Datas[128/*# range 0..NbSubList-1*/];
	int LengthDatas[128/*# range 0..NbSubList-1*/];
	virtual void __fastcall Changed();
	virtual String __fastcall Get(int Index);
	TSpeedListObject* __fastcall GetObject(int Index);
	int __fastcall GetCount();
	TStrings* __fastcall GetStringList();
	void __fastcall SetStringList(TStrings* const Value);
public:
	void __fastcall NameChange(TSpeedListObject* const obj, const String NewName);
	void __fastcall ObjectDeleted(TSpeedListObject* const obj);
	virtual __fastcall ~TSpeedStringList();
	__fastcall TSpeedStringList();
	int __fastcall AddObj(TSpeedListObject* const Value);
	TSpeedListObject* __fastcall Add(const String Value);
	void __fastcall Clear();
	TSpeedListObject* __fastcall Find(const String Name);
	__property TNotifyEvent OnChange = { read = FOnChange, write = FOnChange };
	__property TSpeedListObject* Objects[int Index] = { read = GetObject };
	__property TObject* InObject[int Index] = { read = GetInObject, write = SetInObject };
	__property String Strings[int Index] = { read = Get/*# default */ };
	__property int Count = { read = GetCount };
	__property TStrings* StringList = { read = GetStringList, write = SetStringList };
	__property String Text = { read = GetText, write = SetText };
};
enum TtkTokenKind {tkNull,
                   tkAsmKey,
                   tkAsm,
                   tkAsmComment,
                   tksAsmKey,
                   tksAsm,
                   tksAsmComment,
                   tkRplKey,
                   tkRpl,
                   tkRplComment };
enum TRangeState {rsRpl,
                  rsComRpl,
                  rssasm1,
                  rssasm2,
                  rssasm3,
                  rsAsm,
                  rsComAsm2,
                  rsComAsm1 };

class TSynHP48Syn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TtkTokenKind fTockenKind;
	TRangeState fRange;
	Synedithighlighter::TSynHighlighterAttributes* Attribs[10/*# TtkTokenKind*/];
	TSpeedStringList* FRplKeyWords;
	TSpeedStringList* FAsmKeyWords;
	TSpeedStringList* FSAsmNoField;
	TRangeState FBaseRange;
	Synedithighlighter::TSynHighlighterAttributes* __fastcall GetAttrib(int Index);
	void __fastcall SetAttrib(int Index, Synedithighlighter::TSynHighlighterAttributes* Value);
	TtkTokenKind __fastcall NullProc();
	TtkTokenKind __fastcall SpaceProc();
	TtkTokenKind __fastcall ParOpenProc();
	TtkTokenKind __fastcall RplComProc();
	TtkTokenKind __fastcall AsmComProc(WideChar c);
	TtkTokenKind __fastcall PersentProc();
	TtkTokenKind __fastcall IdentProc();
	TtkTokenKind __fastcall SlashProc();
	TtkTokenKind __fastcall SasmProc1();
	TtkTokenKind __fastcall SasmProc2();
	TtkTokenKind __fastcall SasmProc3();
	void __fastcall EndOfToken();
	void __fastcall SetHighLightChange();
	TtkTokenKind __fastcall Next1();
	void __fastcall Next2(TtkTokenKind tkk);
	TtkTokenKind __fastcall GetTokenFromRange();
	TtkTokenKind __fastcall StarProc();
protected:
	virtual int __fastcall GetAttribCount();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetAttribute(int idx);
	virtual bool __fastcall IsFilterStored();
	virtual bool __fastcall IsLineEnd(int Run);
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	#include "SynHighlighterHP48_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynHP48Syn(TComponent* AOwner);
	virtual __fastcall ~TSynHP48Syn();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void __fastcall DoSetLine(const String Value, int LineNumber);
	virtual void __fastcall Next();
	virtual String __fastcall GetToken();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void* __fastcall GetRange();
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
	virtual bool __fastcall SaveToRegistry(HKEY RootKey, String Key);
	virtual bool __fastcall LoadFromRegistry(HKEY RootKey, String Key);
	virtual void __fastcall Assign(TPersistent* Source);
	__property TSpeedStringList* AsmKeyWords = { read = FAsmKeyWords };
	__property TSpeedStringList* SAsmFoField = { read = FSAsmNoField };
	__property TSpeedStringList* RplKeyWords = { read = FRplKeyWords };
__published:
	__property Synedithighlighter::TSynHighlighterAttributes* AsmKey = { index = int(Synhighlighterhp48::tkAsmKey), read = GetAttrib, write = SetAttrib };
	__property Synedithighlighter::TSynHighlighterAttributes* AsmTxt = { index = int(Synhighlighterhp48::tkAsm), read = GetAttrib, write = SetAttrib };
	__property Synedithighlighter::TSynHighlighterAttributes* AsmComment = { index = int(Synhighlighterhp48::tkAsmComment), read = GetAttrib, write = SetAttrib };
	__property Synedithighlighter::TSynHighlighterAttributes* sAsmKey = { index = int(Synhighlighterhp48::tksAsmKey), read = GetAttrib, write = SetAttrib };
	__property Synedithighlighter::TSynHighlighterAttributes* sAsmTxt = { index = int(Synhighlighterhp48::tksAsm), read = GetAttrib, write = SetAttrib };
	__property Synedithighlighter::TSynHighlighterAttributes* sAsmComment = { index = int(Synhighlighterhp48::tksAsmComment), read = GetAttrib, write = SetAttrib };
	__property Synedithighlighter::TSynHighlighterAttributes* RplKey = { index = int(Synhighlighterhp48::tkRplKey), read = GetAttrib, write = SetAttrib };
	__property Synedithighlighter::TSynHighlighterAttributes* RplTxt = { index = int(Synhighlighterhp48::tkRpl), read = GetAttrib, write = SetAttrib };
	__property Synedithighlighter::TSynHighlighterAttributes* RplComment = { index = int(Synhighlighterhp48::tkRplComment), read = GetAttrib, write = SetAttrib };
	__property TRangeState BaseRange = { read = FBaseRange, write = FBaseRange };
};

void SynHighlighterHP48_initialization();


}  // namespace SynHighlighterHP48

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterhp48;
#endif


#endif // SynHighlighterHP48H

