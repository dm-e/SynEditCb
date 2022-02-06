#ifndef SynHighlighterGeneralH
#define SynHighlighterGeneralH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlightergeneral
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterGeneral.pas, released 2000-04-07.
The Original Code is based on the mwGeneralSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Martin Waldenburg.
Portions written by Martin Waldenburg are copyright 1999 Martin Waldenburg.
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

$Id: SynHighlighterGeneral.pas,v 1.12 2011/04/14 15:12:54 Egg Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a customizable highlighter for SynEdit)
@author(Martin Waldenburg, converted to SynEdit by Michael Hieke)
@created(1999)
@lastmod(2000-06-23)
The SynHighlighterGeneral unit provides a customizable highlighter for SynEdit.
*/
enum TtkTokenKind {tkComment,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkNumber,
                   tkPreprocessor,
                   tkSpace,
                   tkString,
                   tkSymbol,
                   tkUnknown };
enum TCommentStyle {csAnsiStyle,
                    csPasStyle,
                    csCStyle,
                    csAsmStyle,
                    csBasStyle,
                    csCPPStyle };
typedef System::Set<TCommentStyle, csAnsiStyle, csCPPStyle> TCommentStyles;
enum TRangeState {rsANil,
                  rsAnsi,
                  rsPasStyle,
                  rsCStyle,
                  rsUnKnown };
enum TStringDelim {sdSingleQuote,
                   sdDoubleQuote,
                   sdSingleAndDoubleQuote };
typedef void __fastcall (__closure *TGetTokenAttributeEvent) (Synedithighlighter::TSynHighlighterAttributes*);
const WideChar cDefaultIdentChars[] = L"_0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" L"abcdefghijklmnopqrstuvwxyz";

class TSynGeneralSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	String fIdentChars;
	TRangeState FRange;
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fPreprocessorAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	System::Classes::TStrings* fKeywords;
	TCommentStyles fComments;
	TStringDelim fStringDelim;
	bool fDetectPreprocessor;
	TGetTokenAttributeEvent fOnGetTokenAttribute;
	bool FStringMultiLine;
	void __fastcall AsciiCharProc();
	void __fastcall BraceOpenProc();
	void __fastcall PointCommaProc();
	void __fastcall CRProc();
	void __fastcall IdentProc();
	void __fastcall IntegerProc();
	void __fastcall LFProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall RoundOpenProc();
	void __fastcall SlashProc();
	void __fastcall SpaceProc();
	void __fastcall StringProc();
	void __fastcall UnknownProc();
	void __fastcall AnsiProc();
	void __fastcall PasStyleProc();
	void __fastcall CStyleProc();
	void __fastcall SetKeyWords(System::Classes::TStrings* const Value);
	void __fastcall SetComments(TCommentStyles Value);
	TStringDelim __fastcall GetStringDelim();
	void __fastcall SetStringDelim(TStringDelim Value);
	String __fastcall GetIdentifierChars();
	void __fastcall SetIdentifierChars(const String Value);
	bool __fastcall StoreIdentChars();
	void __fastcall SetDetectPreprocessor(bool Value);
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	#include "SynHighlighterGeneral_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	bool __fastcall IsStringDelim(WideChar AChar);
	__fastcall TSynGeneralSyn(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynGeneralSyn();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	TtkTokenKind __fastcall GetTokenID();
	WideChar __fastcall GetCharBeforeToken(int Offset = -1);
	WideChar __fastcall GetCharAfterToken(int Offset = 1);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual bool __fastcall IsKeyword(const String AKeyword);
	virtual bool __fastcall IsWordBreakChar(WideChar AChar);
	virtual void __fastcall Next();
	virtual void __fastcall ResetRange();
	virtual void __fastcall SetRange(void* Value);
	virtual bool __fastcall SaveToRegistry(HKEY RootKey, String key);
	virtual bool __fastcall LoadFromRegistry(HKEY RootKey, String key);
	__property TGetTokenAttributeEvent OnGetTokenAttribute = { read = fOnGetTokenAttribute, write = fOnGetTokenAttribute };
	__property bool StringMultiLine = { read = FStringMultiLine, write = FStringMultiLine };
__published:
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TCommentStyles Comments = { read = fComments, write = SetComments, default = 0 };
	__property bool DetectPreprocessor = { read = fDetectPreprocessor, write = SetDetectPreprocessor };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property String IdentifierChars = { read = GetIdentifierChars, write = SetIdentifierChars, stored = StoreIdentChars };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TStrings* Keywords = { read = fKeywords, write = SetKeyWords };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* PreprocessorAttri = { read = fPreprocessorAttri, write = fPreprocessorAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property TStringDelim StringDelim = { read = GetStringDelim, write = SetStringDelim, default = /*# sdSingleQuote */ 0 };
};

void SynHighlighterGeneral_initialization();


}  // namespace SynHighlighterGeneral

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightergeneral;
#endif


#endif // SynHighlighterGeneralH

