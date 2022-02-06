#ifndef SynHighlighterFoxproH
#define SynHighlighterFoxproH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynHighlighterHashEntries.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.RegularExpressions.hpp>
#include "SynEditCodeFolding.h"

namespace Synhighlighterfoxpro
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterFoxpro.pas, released 2000-04-21.
The Original Code is based on the mwFoxproSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is "riceball".
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

$Id: SynHighlighterFoxpro.pas,v 1.12.2.10 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Foxpro Syntax highlighter for SynEdit)
@author(riceball <teditor@mailroom.com>, converted to SynEdit by Bruno Mikkelsen <btm@scientist.com>)
@created(2000, converted to SynEdit 2000-04-21)
@lastmod(2000-06-23)
The SynHighlighterFoxpro unit provides SynEdit with a Foxpro syntax highlighter.
Thanks to Martin Waldenburg.
*/
//++ CodeFolding

//++ CodeFolding
enum TtkTokenKind {tkSymbol,
                   tkKey,
                   tkComment,
                   tkIdentifier,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkUnknown };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;
//  TSynFoxproSyn = class(TSynCustomHighlighter)
//++ CodeFolding

//-- CodeFolding

class TSynFoxproSyn : public Syneditcodefolding::TSynCustomCodeFoldingHighlighter
{
private:
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synhighlighterhashentries::TSynHashEntryList* fKeywords;
//++ CodeFolding
	System::Regularexpressions::TRegEx RE_BlockBegin;
	System::Regularexpressions::TRegEx RE_BlockEnd;
//-- CodeFolding
	void __fastcall DoAddKeyword(String AKeyword, int AKind);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall AndSymbolProc();
	void __fastcall AsciiCharProc();
	void __fastcall AtSymbolProc();
	void __fastcall BraceOpenProc();
	void __fastcall CRProc();
	void __fastcall ColonProc();
	void __fastcall CommaProc();
	void __fastcall EqualProc();
	void __fastcall GreaterProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall LowerProc();
	void __fastcall MinusProc();
	void __fastcall ModSymbolProc();
	void __fastcall NotSymbolProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall OrSymbolProc();
	void __fastcall PlusProc();
	void __fastcall PointProc();
	void __fastcall QuestionProc();
	void __fastcall RoundCloseProc();
	void __fastcall RoundOpenProc();
	void __fastcall SemiColonProc();
	void __fastcall SlashProc();
	void __fastcall SpaceProc();
	void __fastcall SquareCloseProc();
	void __fastcall SquareOpenProc();
	void __fastcall StarProc();
	void __fastcall StringProc();
	void __fastcall TildeProc();
	void __fastcall XOrSymbolProc();
	void __fastcall UnknownProc();
protected:
	virtual bool __fastcall IsFilterStored();
public:
	typedef Syneditcodefolding::TSynCustomCodeFoldingHighlighter inherited;	
	#include "SynHighlighterFoxpro_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynFoxproSyn(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynFoxproSyn();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
//++ CodeFolding
	virtual void __fastcall ScanForFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, System::Classes::TStrings* LinesToScan, int FromLine, int ToLine);
	virtual void __fastcall AdjustFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, System::Classes::TStrings* LinesToScan);
//-- CodeFolding
__published:
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
};

void SynHighlighterFoxpro_initialization();


}  // namespace SynHighlighterFoxpro

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterfoxpro;
#endif


#endif // SynHighlighterFoxproH

