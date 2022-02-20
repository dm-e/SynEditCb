#ifndef SynHighlighterVBScriptH
#define SynHighlighterVBScriptH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include <System.Win.Registry.hpp>
#include "SynEditHighlighter.h"
#include "SynEditTypes.h"
#include "SynHighlighterHashEntries.h"
#include <System.SysUtils.hpp>
#include "SynUnicode.h"
#include <System.Classes.hpp>
#include <System.RegularExpressions.hpp>
#include "SynEditCodeFolding.h"

namespace Synhighlightervbscript
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterVBScript.pas, released 2000-04-18.
The Original Code is based on the lbVBSSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Luiz C. Vaz de Brito.
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

$Id: SynHighlighterVBScript.pas,v 1.14.2.6 2005/12/16 17:13:16 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a VBScript highlighter for SynEdit)
@author(Luiz C. Vaz de Brito, converted to SynEdit by David Muir <david@loanhead45.freeserve.co.uk>)
@created(20 January 1999, converted to SynEdit April 18, 2000)
@lastmod(2000-06-23)
The SynHighlighterVBScript unit provides SynEdit with a VisualBasic Script (.vbs) highlighter.
Thanks to Primoz Gabrijelcic and Martin Waldenburg.
*/
//++ CodeFolding

//++ CodeFolding
const System::WideChar SYNS_AttrConst[] = L"Constant";
enum TtkTokenKind {tkSymbol,
                   tkKey,
                   tkComment,
                   tkConst,
                   tkIdentifier,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkFunction,
                   tkUnknown };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;
//  TSynVBScriptSyn = class(TSynCustomHighLighter)
//++ CodeFolding

//-- CodeFolding

class TSynVBScriptSyn : public Syneditcodefolding::TSynCustomCodeFoldingHighlighter
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
	Synedithighlighter::TSynHighlighterAttributes* fFunctionAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCOnstAttri;
	Synhighlighterhashentries::TSynHashEntryList* fKeywords;
//++ CodeFolding
	System::Regularexpressions::TRegEx RE_BlockBegin;
	System::Regularexpressions::TRegEx RE_BlockEnd;
//-- CodeFolding
	void __fastcall DoAddKeyword(String AKeyword, int AKind);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall ApostropheProc();
	void __fastcall CRProc();
	void __fastcall DateProc();
	void __fastcall GreaterProc();
	void __fastcall IdentProc();
	void __fastcall RemProc();
	void __fastcall LFProc();
	void __fastcall LowerProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall SpaceProc();
	void __fastcall StringProc();
	void __fastcall SymbolProc();
	void __fastcall UnknownProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Syneditcodefolding::TSynCustomCodeFoldingHighlighter inherited;	
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynVBScriptSyn(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynVBScriptSyn();
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
	__property TSynHighlighterAttributes* ConstAttri = { read = fCOnstAttri, write = fCOnstAttri };
	__property TSynHighlighterAttributes* FunctionAttri = { read = fFunctionAttri, write = fFunctionAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
};

void SynHighlighterVBScript_initialization();


}  // namespace SynHighlighterVBScript

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightervbscript;
#endif


#endif // SynHighlighterVBScriptH

