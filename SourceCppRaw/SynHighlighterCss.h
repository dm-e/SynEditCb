#ifndef SynHighlighterCssH
#define SynHighlighterCssH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynHighlighterHashEntries.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlightercss
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterEnhCSS.pas, released 2001-10-28
Initial modifications to this CSS Highlighter were made by Ashley Brown,
ashley@ashleybrown.co.uk.

The Original Code is based on the SynHighlighterHTML.pas, released 2000-04-10 - 
this in turn was based on the hkHTMLSyn.pas file from the mwEdit component suite
by Martin Waldenburg and other developers, the Initial Author of this file is
Hideo Koiso.
Unicode translation by Ma�l H�rz.
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

You may retrieve the latest version of SynEdit from the SynEdit home page,
located at http://SynEdit.SourceForge.net

You may retrieve the latest version of this file from
http://www.ashleybrown.co.uk/synedit/

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides an improved CSS highlighter for SynEdit)
@author(Ashley Brown, based on HTML highlighter by Hideo Koiso and converted to SynEdit by Michael Hieke)
@created(2001-10-28)
@lastmod(2003-05-11)
The SynHighlighterEnhCSS unit provides SynEdit with an improved CSS highlighter.

http://www.ashleybrown.co.uk/
ashley@ashleybrown.co.uk
*/
enum TtkTokenKind {tkComment,
                   tkAtRule,
                   tkProperty,
                   tkSelector,
                   tkSelectorAttrib,
                   tkNull,
                   tkSpace,
                   tkString,
                   tkSymbol,
                   tkText,
                   tkUndefProperty,
                   tkValue,
                   tkColor,
                   tkNumber,
                   tkImportant };
enum TRangeState {rsComment,
                  rsSelector,
                  rsDeclaration,
                  rsUnKnown,
                  rsProperty,
                  rsValue,
                  rsAttrib,
                  rsParameter };

class TSynCssSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState FRange;
	TRangeState fCommentRange;
	TRangeState fParameterRange;
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fPropertyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fAttributeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSelectorAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fColorAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fTextAttri;
	Synedithighlighter::TSynHighlighterAttributes* fValueAttri;
	Synedithighlighter::TSynHighlighterAttributes* fUndefPropertyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fImportantPropertyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fAtRuleAttri;
	Synhighlighterhashentries::TSynHashEntryList* fKeywords;
	void __fastcall DoAddKeyword(String AKeyword, int AKind);
	int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall AtRuleProc();
	void __fastcall SelectorProc();
	void __fastcall AttributeProc();
	void __fastcall CommentProc();
	void __fastcall BraceCloseProc();
	void __fastcall BraceOpenProc();
	void __fastcall ParenOpenProc();
	void __fastcall ParenCloseProc();
	void __fastcall BracketOpenProc();
	void __fastcall BracketCloseProc();
	void __fastcall CRProc();
	void __fastcall SemiProc();
	void __fastcall StartValProc();
	void __fastcall NumberProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall NullProc();
	void __fastcall SpaceProc();
	void __fastcall StringProc();
	void __fastcall HashProc();
	void __fastcall SlashProc();
	void __fastcall GreaterProc();
	void __fastcall PlusProc();
	void __fastcall TildeProc();
	void __fastcall PipeProc();
	void __fastcall CircumflexProc();
	void __fastcall EqualProc();
	void __fastcall ExclamProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
	void __fastcall NextDeclaration();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynCssSyn(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynCssSyn();
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
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* PropertyAttri = { read = fPropertyAttri, write = fPropertyAttri };
	__property TSynHighlighterAttributes* ColorAttri = { read = fColorAttri, write = fColorAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* AtRuleAttri = { read = fAtRuleAttri, write = fAtRuleAttri };
	__property TSynHighlighterAttributes* SelectorAttri = { read = fSelectorAttri, write = fSelectorAttri };
	__property TSynHighlighterAttributes* AttributeAttri = { read = fAttributeAttri, write = fAttributeAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property TSynHighlighterAttributes* TextAttri = { read = fTextAttri, write = fTextAttri };
	__property TSynHighlighterAttributes* ValueAttri = { read = fValueAttri, write = fValueAttri };
	__property TSynHighlighterAttributes* UndefPropertyAttri = { read = fUndefPropertyAttri, write = fUndefPropertyAttri };
	__property TSynHighlighterAttributes* ImportantPropertyAttri = { read = fImportantPropertyAttri, write = fImportantPropertyAttri };
};

void SynHighlighterCss_initialization();


}  // namespace SynHighlighterCss

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightercss;
#endif


#endif // SynHighlighterCssH

