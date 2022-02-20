#ifndef SynHighlighterCacheH
#define SynHighlighterCacheH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlightercache
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterCache.pas, released 2000-04-21.
The Original Code is based on the mwCacheSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Pavel Krehula.
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

$Id: SynHighlighterCache.pas,v 1.13.2.6 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Cache object script files highlighter for SynEdit)
@author(Pavel Krehula <pavel@mas.cz>, converted to SynEdit by Bruno Mikkelsen <btm@scientist.com>)
@created(1999-12-17, converted to SynEdit 2000-04-21)
@lastmod(2000-06-23)
The SynHighlighterCache unit provides SynEdit with a Cache object script files highlighter.
Thanks to Martin Waldenburg.
*/
enum TtkTokenKind {tkClass,
                   tkComment,
                   tkFunction,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkNumber,
                   tkDirective,
                   tkSpace,
                   tkString,
                   tkSymbol,
                   tkIndirect,
                   tkLabel,
                   tkMacro,
                   tkUserFunction,
                   tkEmbedSQL,
                   tkEmbedText,
                   tkUnknown };
enum TRangeState {rsUnKnown,
                  rsSQL,
                  rsHTML,
                  rsCommand };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynCacheSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	int fBrace;
	bool fFirstBrace;
	TRangeState FRange;
	TtkTokenKind FTokenID;
	TIdentFuncTableFunc fIdentFuncTable[1997/*# range 0..1996*/];
	Synedithighlighter::TSynHighlighterAttributes* fClassAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fFunctionAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDirectiveAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIndirectAttri;
	Synedithighlighter::TSynHighlighterAttributes* fLabelAttri;
	Synedithighlighter::TSynHighlighterAttributes* fMacroAttri;
	Synedithighlighter::TSynHighlighterAttributes* fUserFunctionAttri;
	Synedithighlighter::TSynHighlighterAttributes* fEmbedSQLAttri;
	Synedithighlighter::TSynHighlighterAttributes* fEmbedTextAttri;
	bool FCanKey;    // if true, the next token can be a keyword
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall KeyWordFunc(int Index);
	TtkTokenKind __fastcall Func38html(int Index);
	TtkTokenKind __fastcall Func38sql(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall InitIdent();
	void __fastcall CRProc();
	void __fastcall CommentProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall SpaceProc();
	void __fastcall StringProc();
	void __fastcall UnknownProc();
	void __fastcall IndirectProc();
	void __fastcall SymbolProc();
	void __fastcall FuncProc();
	void __fastcall DirectiveProc();
	void __fastcall EmbeddedProc();
protected:
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynCacheSyn(System::Classes::TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual void __fastcall Next();
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
__published:
	__property TSynHighlighterAttributes* ClassAttri = { read = fClassAttri, write = fClassAttri };
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* FunctionAttri = { read = fFunctionAttri, write = fFunctionAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* PreprocesorAttri = { read = fDirectiveAttri, write = fDirectiveAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property TSynHighlighterAttributes* IndirectAttri = { read = fIndirectAttri, write = fIndirectAttri };
	__property TSynHighlighterAttributes* LabelAttri = { read = fLabelAttri, write = fLabelAttri };
	__property TSynHighlighterAttributes* MacroAttri = { read = fMacroAttri, write = fMacroAttri };
	__property TSynHighlighterAttributes* UserFunctionAttri = { read = fUserFunctionAttri, write = fUserFunctionAttri };
	__property TSynHighlighterAttributes* EmbededSQLandHTMLAttri = { read = fEmbedSQLAttri, write = fEmbedSQLAttri };
	__property TSynHighlighterAttributes* EmbededTextAttri = { read = fEmbedTextAttri, write = fEmbedTextAttri };
};

void SynHighlighterCache_initialization();


}  // namespace SynHighlighterCache

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightercache;
#endif


#endif // SynHighlighterCacheH

