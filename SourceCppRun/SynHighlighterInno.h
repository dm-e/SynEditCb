#ifndef SynHighlighterInnoH
#define SynHighlighterInnoH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynHighlighterHashEntries.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterinno
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterInno.pas, released 2000-05-01.
The Initial Author of this file is Satya.
Portions created by Satya are Copyright 2000 Satya.
Unicode translation by Maël Hörz.
All Rights Reserved.

Contributors to the SynEdit project are listed in the Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

$Id: SynHighlighterInno.pas,v 1.22.2.9 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides an Inno script file highlighter for SynEdit)
@author(Satya)
@created(2000-05-01)
@lastmod(2001-01-23)
The SynHighlighterInno unit provides an Inno script file highlighter for SynEdit.
Check out http://www.jrsoftware.org for the free Inno Setup program,
and http://www.wintax.nl/isx/ for My Inno Setup Extensions.
*/
enum TtkTokenKind {tkComment,
                   tkConstant,
                   tkIdentifier,
                   tkKey,
                   tkKeyOrParameter,
                   tkNull,
                   tkNumber,
                   tkParameter,
                   tkSection,
                   tkSpace,
                   tkString,
                   tkSymbol,
                   tkUnknown };

class TSynInnoSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fConstantAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSectionAttri;
	Synedithighlighter::TSynHighlighterAttributes* fParamAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fInvalidAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synhighlighterhashentries::TSynHashEntryList* fKeywords;
	int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall SymbolProc();
	void __fastcall CRProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall SectionProc();
	void __fastcall SpaceProc();
	void __fastcall EqualProc();
	void __fastcall ConstantProc();
	void __fastcall SemiColonProc();
	void __fastcall StringProc();
	void __fastcall UnknownProc();
	void __fastcall DoAddKeyword(String AKeyword, int AKind);
protected:
	virtual bool __fastcall IsCurrentToken(const String Token);
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	#include "SynHighlighterInno_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynInnoSyn(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynInnoSyn();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	TtkTokenKind __fastcall GetTokenID();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
__published:
	__property TSynHighlighterAttributes* ConstantAttri = { read = fConstantAttri, write = fConstantAttri };
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* InvalidAttri = { read = fInvalidAttri, write = fInvalidAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* ParameterAttri = { read = fParamAttri, write = fParamAttri };
	__property TSynHighlighterAttributes* SectionAttri = { read = fSectionAttri, write = fSectionAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
};

void SynHighlighterInno_initialization();


}  // namespace SynHighlighterInno

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterinno;
#endif


#endif // SynHighlighterInnoH

