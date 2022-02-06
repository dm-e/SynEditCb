#ifndef SynHighlighterDWSH
#define SynHighlighterDWSH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "SynEditCodeFolding.h"
#include <System.RegularExpressions.hpp>
#include <System.Character.hpp>

namespace Synhighlighterdws
{

/*------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterPas.pas, released 2000-04-17.
The Original Code is based on the mwPasSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Martin Waldenburg.
Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
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

$Id: SynHighlighterDWS.pas,v 1.11 2011/12/28 09:24:20 Egg Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a DWScript syntax highlighter for SynEdit)
*/
//++ CodeFolding

//-- CodeFolding
enum TtkTokenKind {tkAsm,
                   tkComment,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkSymbol,
                   tkUnknown,
                   tkFloat,
                   tkHex,
                   tkDirec,
                   tkChar };
enum TRangeState {rsANil,
                  rsAnsi,
                  rsAnsiAsm,
                  rsAsm,
                  rsBor,
                  rsBorAsm,
                  rsProperty,
                  rsExports,
                  rsDirective,
                  rsDirectiveAsm,
                  rsHereDocSingle,
                  rsHereDocDouble,
                  rsType,
                  rsUnKnown };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) ();
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TAnsiStringList : public System::Classes::TStringList
{
__published:
	virtual int __fastcall CompareStrings(const String S1, const String S2);
public:
	typedef System::Classes::TStringList inherited;	
	#include "SynHighlighterDWS_friends.inc"
	__fastcall TAnsiStringList();
	__fastcall TAnsiStringList(bool OwnsObjects);
	__fastcall TAnsiStringList(Char QuoteChar, Char Delimiter);
	__fastcall TAnsiStringList(Char QuoteChar, Char Delimiter, System::Classes::TStringsOptions Options);
	__fastcall TAnsiStringList(System::Classes::TDuplicates Duplicates, bool Sorted, bool CaseSensitive);
};
//++ CodeFolding

//-- CodeFolding

class TSynDWSSyn : public Syneditcodefolding::TSynCustomCodeFoldingHighlighter
{
private:
	bool fAsmStart;
	TRangeState FRange;
	Char fCommentClose;
	TIdentFuncTableFunc fIdentFuncTable[389/*# range 0..388*/];
	TAnsiStringList* fKeywords;
	TAnsiStringList* FKeywordsPropertyScoped;
	TAnsiStringList* FKeywordsTypeScoped;
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCharAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fFloatAttri;
	Synedithighlighter::TSynHighlighterAttributes* fHexAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fAsmAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDirecAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
//++ CodeFolding
	System::Regularexpressions::TRegEx RE_BlockBegin;
	System::Regularexpressions::TRegEx RE_BlockEnd;
	System::Regularexpressions::TRegEx RE_Code;
//-- CodeFolding
	TtkTokenKind __fastcall AltFunc();
	TtkTokenKind __fastcall KeyWordFunc();
	TtkTokenKind __fastcall FuncAsm();
	TtkTokenKind __fastcall FuncEnd();
	TtkTokenKind __fastcall FuncPropertyScoped();
	TtkTokenKind __fastcall FuncProperty();
	TtkTokenKind __fastcall FuncTypeScoped();
	TtkTokenKind __fastcall FuncType();
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall InitIdent();
	void __fastcall AddressOpProc();
	void __fastcall AsciiCharProc();
	void __fastcall AnsiProc();
	void __fastcall BorProc();
	void __fastcall BraceOpenProc();
	void __fastcall ColonOrGreaterProc();
	void __fastcall CRProc();
	void __fastcall IdentProc();
	void __fastcall IntegerProc();
	void __fastcall LFProc();
	void __fastcall LowerProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall PointProc();
	void __fastcall RoundOpenProc();
	void __fastcall SemiColonProc();
	void __fastcall SlashProc();
	void __fastcall SpaceProc();
	void __fastcall StringAposProc();
	void __fastcall StringAposMultiProc();
	void __fastcall StringQuoteProc();
	void __fastcall SymbolProc();
	void __fastcall UnknownProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
	virtual bool __fastcall IsCurrentToken(const String Token);
public:
	typedef Syneditcodefolding::TSynCustomCodeFoldingHighlighter inherited;	
	#include "SynHighlighterDWS_friends.inc"
	__classmethod virtual Synedithighlighter::TSynHighlighterCapabilities __fastcall GetCapabilities();
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynDWSSyn(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynDWSSyn();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	TtkTokenKind __fastcall GetTokenID();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
	virtual void __fastcall ResetRange();
	virtual void __fastcall SetRange(void* Value);
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual void __fastcall LoadDelphiStyle();
    // ^^^
    // This routine can be called to install a Delphi style of colors
    // and highlighting. It modifies the basic TSynDWSSyn to reproduce
    // the most recent Delphi editor highlighting.

//++ CodeFolding
	virtual void __fastcall ScanForFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, System::Classes::TStrings* LinesToScan, int FromLine, int ToLine);
	virtual void __fastcall AdjustFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, System::Classes::TStrings* LinesToScan);
//-- CodeFolding
__published:
	__property TSynHighlighterAttributes* AsmAttri = { read = fAsmAttri, write = fAsmAttri };
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* DirectiveAttri = { read = fDirecAttri, write = fDirecAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* FloatAttri = { read = fFloatAttri, write = fFloatAttri };
	__property TSynHighlighterAttributes* HexAttri = { read = fHexAttri, write = fHexAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* CharAttri = { read = fCharAttri, write = fCharAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
};

void SynHighlighterDWS_initialization();


}  // namespace SynHighlighterDWS

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterdws;
#endif


#endif // SynHighlighterDWSH

