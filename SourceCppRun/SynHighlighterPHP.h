#ifndef SynHighlighterPHPH
#define SynHighlighterPHPH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include <System.Win.Registry.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include <System.SysUtils.hpp>
#include "SynUnicode.h"
#include <System.Classes.hpp>
#include "SynEditCodeFolding.h"

namespace Synhighlighterphp
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterPHP.pas, released 2000-04-21.
The Original Code is based on the wmPHPSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Willo van der Merwe.
"Heredoc" syntax highlighting implementation by Marko Njezic.
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

$Id: SynHighlighterPHP.pas,v 1.22.2.7 2005/12/16 20:09:37 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a PHP syntax highlighter for SynEdit)
@author(Willo van der Merwe <willo@wack.co.za>, converted to SynEdit by Bruno Mikkelsen <btm@scientist.com>)
@created(1999, converted to SynEdit 2000-04-21)
@lastmod(2000-06-23)
The SynHighlighterPHP unit provides SynEdit with a PHP syntax highlighter.
Thanks to Martin Waldenburg.
*/
//++ CodeFolding

//++ CodeFolding
enum TtkTokenKind {tkSymbol,
                   tkKey,
                   tkComment,
                   tkDocument,
                   tkIdentifier,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkUnknown,
                   tkVariable };
enum TRangeState {rsUnKnown,
                  rsString39,
                  rsString34,
                  rsString96,
                  rsComment,
                  rsDocument,
                  rsVarExpansion };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;
//  TSynPHPSyn = class(TSynCustomHighlighter)

class TSynPHPSyn : public Syneditcodefolding::TSynCustomCodeFoldingHighlighter
{
private:
	TRangeState FRange;
	TtkTokenKind FTokenID;
	TIdentFuncTableFunc fIdentFuncTable[439/*# range 0..438*/];
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVariableAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDocumentAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall KeyWordFunc(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall InitIdent();
	void __fastcall AndSymbolProc();
	void __fastcall CRProc();
	void __fastcall EqualProc();
	void __fastcall GreaterProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall LowerProc();
	void __fastcall MinusProc();
	void __fastcall MultiplyProc();
	void __fastcall NotSymbolProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall OrSymbolProc();
	void __fastcall PlusProc();
	void __fastcall PoundProc();
	void __fastcall RemainderSymbolProc();
	void __fastcall SymbolProc();
	void __fastcall SlashProc();
	void __fastcall SpaceProc();
	void __fastcall StringProc();
	void __fastcall VarExpansionProc();
	void __fastcall VariableProc();
	void __fastcall XOrSymbolProc();
	void __fastcall UnknownProc();
	void __fastcall AnsiCProc();
	void __fastcall String39Proc();
	void __fastcall String34Proc();
	void __fastcall String96Proc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
	void __fastcall NextProcedure();
public:
	typedef Syneditcodefolding::TSynCustomCodeFoldingHighlighter inherited;	
	#include "SynHighlighterPHP_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynPHPSyn(System::Classes::TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual bool __fastcall IsWordBreakChar(WideChar AChar);
	virtual void __fastcall Next();
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
//++ CodeFolding
	virtual void __fastcall ScanForFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, System::Classes::TStrings* LinesToScan, int FromLine, int ToLine);
//-- CodeFolding
__published:
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* DocumentAttri = { read = fDocumentAttri, write = fDocumentAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property TSynHighlighterAttributes* VariableAttri = { read = fVariableAttri, write = fVariableAttri };
};

void SynHighlighterPHP_initialization();


}  // namespace SynHighlighterPHP

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterphp;
#endif


#endif // SynHighlighterPHPH

