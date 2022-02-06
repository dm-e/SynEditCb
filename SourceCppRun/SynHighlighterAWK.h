#ifndef SynHighlighterAWKH
#define SynHighlighterAWKH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterawk
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterAWK.pas, released 2000-06-18.
The Original Code is based on the hkAWKSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Hideo Koiso.
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

$Id: SynHighlighterAWK.pas,v 1.10.2.6 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a AWK Script highlighter for SynEdit)
@author(Hideo Koiso <sprhythm@fureai.or.jp>, converted to SynEdit by David Muir <dhm@dmsoftware.co.uk>)
@created(7 November 1999, converted to SynEdit April 18, 2000)
@lastmod(June 19, 2000)
The SynHighlighterAWK unit provides SynEdit with a AWK Script (.awk) highlighter.
*/
enum TtkTokenKind {tkComment,
                   tkIdentifier,
                   tkInterFunc,
                   tkKey,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkSymbol,
                   tkSysVar,
                   tkUnknown };

class TSynAWKSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	System::Classes::TStringList* AWKSyntaxList;
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fInterFuncAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSysVarAttri;
	void __fastcall AndProc();
	void __fastcall CommentProc();
	void __fastcall CRProc();
	void __fastcall ExclamProc();
	void __fastcall FieldRefProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall MakeSyntaxList();
	void __fastcall MinusProc();
	void __fastcall NullProc();
	void __fastcall OpInputProc();
	void __fastcall OrProc();
	void __fastcall PlusProc();
	void __fastcall QuestionProc();
	void __fastcall SpaceProc();
	void __fastcall StringProc();
	void __fastcall SymbolProc();
	void __fastcall NumberProc();
	void __fastcall BraceProc();
protected:
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	#include "SynHighlighterAWK_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynAWKSyn(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynAWKSyn();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
__published:
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* InterFuncAttri = { read = fInterFuncAttri, write = fInterFuncAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property TSynHighlighterAttributes* SysVarAttri = { read = fSysVarAttri, write = fSysVarAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
};

void SynHighlighterAWK_initialization();


}  // namespace SynHighlighterAWK

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterawk;
#endif


#endif // SynHighlighterAWKH

