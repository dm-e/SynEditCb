/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterMulti.pas, released 2000-06-23.
The Original Code is based on mwMultiSyn.pas by Willo van der Merwe, part of the
mwEdit component suite.
Unicode translation by Maël Hörz.

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

$Id: SynHighlighterMulti.pas,v 1.34.2.11 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Multiple-highlighter syntax highlighter for SynEdit)
@author(Willo van der Merwe <willo@wack.co.za>, converted to SynEdit by David Muir <dhm@dmsoftware.co.uk>)
@created(1999, converted to SynEdit 2000-06-23)
@lastmod(2000-06-23)
The SynHighlighterMulti unit provides SynEdit with a multiple-highlighter syntax highlighter.
This highlighter can be used to highlight text in which several languages are present, such as HTML.
For example, in HTML as well as HTML tags there can also be JavaScript and/or VBScript present.
*/
#ifndef SynHighlighterMultiH
#define SynHighlighterMultiH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>

namespace Synhighlightermulti
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterMulti.pas, released 2000-06-23.
The Original Code is based on mwMultiSyn.pas by Willo van der Merwe, part of the
mwEdit component suite.
Unicode translation by Maël Hörz.

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

$Id: SynHighlighterMulti.pas,v 1.34.2.11 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Multiple-highlighter syntax highlighter for SynEdit)
@author(Willo van der Merwe <willo@wack.co.za>, converted to SynEdit by David Muir <dhm@dmsoftware.co.uk>)
@created(1999, converted to SynEdit 2000-06-23)
@lastmod(2000-06-23)
The SynHighlighterMulti unit provides SynEdit with a multiple-highlighter syntax highlighter.
This highlighter can be used to highlight text in which several languages are present, such as HTML.
For example, in HTML as well as HTML tags there can also be JavaScript and/or VBScript present.
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
class DELPHICLASS TSynMultiSyn;
typedef void __fastcall (__closure *TOnCheckMarker) (TObject*, int&, int&, String&, int, const String);

class TScheme : public System::Classes::TCollectionItem
{
private:
	String fEndExpr;
	String fStartExpr;
	Synedithighlighter::TSynCustomHighlighter* fHighlighter;
	Synedithighlighter::TSynHighlighterAttributes* fMarkerAttri;
	TComponentName fSchemeName;
	bool fCaseSensitive;
	TOnCheckMarker fOnCheckStartMarker;
	TOnCheckMarker fOnCheckEndMarker;
	String __fastcall ConvertExpression(const String Value);
	void __fastcall MarkerAttriChanged(TObject* Sender);
	void __fastcall SetMarkerAttri(Synedithighlighter::TSynHighlighterAttributes* const Value);
	void __fastcall SetHighlighter(Synedithighlighter::TSynCustomHighlighter* const Value);
	void __fastcall SetEndExpr(const String Value);
	void __fastcall SetStartExpr(const String Value);
	void __fastcall SetCaseSensitive(bool Value);
protected:
	virtual void __fastcall DefineProperties(TFiler* Filer);
	virtual String __fastcall GetDisplayName();
	virtual void __fastcall SetDisplayName(const String Value);
public:
	typedef System::Classes::TCollectionItem inherited;
	#include "SynHighlighterMulti_friends.inc"
	__fastcall TScheme(TCollection* Collection);
	virtual __fastcall ~TScheme();
__published:
	__property bool CaseSensitive = { read = fCaseSensitive, write = SetCaseSensitive, default = true };
	__property String StartExpr = { read = fStartExpr, write = SetStartExpr };
	__property String EndExpr = { read = fEndExpr, write = SetEndExpr };
	__property Synedithighlighter::TSynCustomHighlighter* Highlighter = { read = fHighlighter, write = SetHighlighter };
	__property Synedithighlighter::TSynHighlighterAttributes* MarkerAttri = { read = fMarkerAttri, write = SetMarkerAttri };
	__property TComponentName SchemeName = { read = fSchemeName, write = fSchemeName };
	__property TOnCheckMarker OnCheckStartMarker = { read = fOnCheckStartMarker, write = fOnCheckStartMarker };
	__property TOnCheckMarker OnCheckEndMarker = { read = fOnCheckEndMarker, write = fOnCheckEndMarker };
};

typedef System::TMetaClass* TgmSchemeClass;

class TSchemes : public System::Classes::TCollection
{
private:
	TSynMultiSyn* fOwner;
	TScheme* __fastcall GetItems(int Index);
	void __fastcall SetItems(int Index, TScheme* const Value);
protected:
	DYNAMIC TPersistent* __fastcall GetOwner();
	virtual void __fastcall Update(TCollectionItem* Item);
public:
	typedef System::Classes::TCollection inherited;
	#include "SynHighlighterMulti_friends.inc"
	__fastcall TSchemes(TSynMultiSyn* aOwner);
	__property TScheme* Items[int aIndex] = { read = GetItems, write = SetItems/*# default */ };
	__fastcall TSchemes(TCollectionItemClass ItemClass);
};

class TMarker : public System::TObject
{
	#include "SynHighlighterMulti_friends.inc"
public:
	typedef System::TObject inherited;
protected:
	int fScheme;
	int fStartPos;
	int fMarkerLen;
	String fMarkerText;
	bool fIsOpenMarker;
public:
	__fastcall TMarker(int aScheme, int aStartPos, int aMarkerLen, bool aIsOpenMarker, const String aMarkerText);
	__fastcall TMarker();
};
enum TRangeOperation {roGet,
                      roSet };
typedef System::NativeUInt TRangeUNativeInt;
typedef void __fastcall (__closure *TRangeProc) (TRangeOperation, TRangeUNativeInt&);

  /*
  * Usage notes *
    If you don't need to nest MultiSyns as Schemes, just as DefaultHighlighter,
  you can nest up to 2 MultiSyns, each of them containing up to 7 Schemes. This
  is the way MultiSyn works best. (implemented in NewRangeProc)
    If you need to use a MultiSyn nested as Scheme, then you can nest up to
  5 MultiSyns, but Ranges aren't persisted across occurrences of Schemes that
  have multiple lines. (implemented in OldRangeProc)
    Clarification: when I say "you can nest up to X" MultiSyns, I mean having
  X+1 levels of MultiSyns.

  MultiSyn doesn't work by default with dynamic highlighters; you must use
  OnCustomRange. This is because dynamic highlighters' Ranges are pointers,
  but MultiSyn needs Ranges to be ordinal values smaller than 16 (4 bits).

  OnCustomRange:
    When Operation is roGet, user should store in the 'Range' parameter the
    information to allow restoring the current state of the highlighter.
    When Operation is roSet, user should restore highlighter state (CurrScheme,
    DefaultHighlighter.Range and, if the case, Schemes[CurrScheme].Range)
    according to 'Range' value.
  CurrScheme:
    Index of the scheme that is currently parsing. DefaultHighlighter maps to -1.

  * Implementation notes *
  fTmpRange:
    Using the OldRangeProc, fTmpRange was the only way to restore the Range
    of the DefaultHighlighter after a Scheme spanned across multiple lines.
    With the NewRangeProc, the only use for it is restoring DefaultHighLighter's
    Range in case a nested MultiSyn uses the highlighter too.
  */
typedef void __fastcall (__closure *TCustomRangeEvent) (TSynMultiSyn*, TRangeOperation, void*&);

class TSynMultiSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeProc fRangeProc;
	String fDefaultLanguageName;
	TList* fMarkers;
	TMarker* fMarker;
	int fNextMarker;
	int fCurrScheme;
	void* fTmpRange;
	TCustomRangeEvent fOnCustomRange;
	String fLineStr;
	void __fastcall SetDefaultHighlighter(Synedithighlighter::TSynCustomHighlighter* const Value);
	TMarker* __fastcall GetMarkers(int Index);
	__property TMarker* Markers[int Index] = { read = GetMarkers };
	void __fastcall DoCheckMarker(TScheme* Scheme, int StartPos, int MarkerLen, const String MarkerText, bool Start, int Line, const String LineStr);
	void __fastcall SetOnCustomRange(const TCustomRangeEvent Value);
protected:
	TSchemes* fSchemes;
	Synedithighlighter::TSynCustomHighlighter* fDefaultHighlighter;
	int fLineNumber;
	String fSampleSource;
	virtual void __fastcall Loaded();
	void __fastcall SetSchemes(TSchemes* const Value);
	void __fastcall ClearMarkers();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual int __fastcall GetAttribCount();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetAttribute(int Index);
	void __fastcall HookHighlighter(Synedithighlighter::TSynCustomHighlighter* aHL);
	void __fastcall UnhookHighlighter(Synedithighlighter::TSynCustomHighlighter* aHL);
	virtual void __fastcall Notification(TComponent* aComp, TOperation aOp);
	virtual String __fastcall GetSampleSource();
	virtual void __fastcall SetSampleSource(String Value);
	virtual void __fastcall DoSetLine(const String Value, int LineNumber);
    //
	void __fastcall OldRangeProc(TRangeOperation Operation, TRangeUNativeInt& Range);
	void __fastcall NewRangeProc(TRangeOperation Operation, TRangeUNativeInt& Range);
	void __fastcall UserRangeProc(TRangeOperation Operation, TRangeUNativeInt& Range);
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	#include "SynHighlighterMulti_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynMultiSyn(TComponent* AOwner);
	virtual __fastcall ~TSynMultiSyn();
	virtual bool __fastcall GetEol();
	virtual String __fastcall GetExpandedToken();
	virtual void* __fastcall GetRange();
	virtual String __fastcall GetToken();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
	bool __fastcall UpdateRangeProcs();
	__property int CurrScheme = { read = fCurrScheme, write = fCurrScheme };
	__property String CurrLine = { read = fLineStr };
	virtual bool __fastcall LoadFromRegistry(HKEY RootKey, String Key);
	virtual bool __fastcall SaveToRegistry(HKEY RootKey, String Key);
	virtual bool __fastcall IsIdentChar(WideChar AChar);
__published:
	__property TSchemes* Schemes = { read = fSchemes, write = SetSchemes };
	__property Synedithighlighter::TSynCustomHighlighter* DefaultHighlighter = { read = fDefaultHighlighter, write = SetDefaultHighlighter };
	__property String DefaultLanguageName = { read = fDefaultLanguageName, write = fDefaultLanguageName };
	__property TCustomRangeEvent OnCustomRange = { read = fOnCustomRange, write = SetOnCustomRange };
};


}  // namespace SynHighlighterMulti

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightermulti;
#endif

#endif // SynHighlighterMultiH

