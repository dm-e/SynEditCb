/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterJScript.pas, released 2000-04-14.
The Original Code is based on the mwJScript.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Tony de Buys.
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

$Id: SynHighlighterJScript.pas,v 1.21.2.7 2005/12/16 16:10:37 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a JavaScript/JScript highlighter for SynEdit)
@author(Tony De Buys [tony@lad.co.za], converted to SynEdit by David Muir <david@loanhead45.freeserve.co.uk>)
@created(December 1999, converted to SynEdit April 14, 2000)
@lastmod(2000-06-23)
The SynHighlighterJScript unit provides SynEdit with a JScript/JavaScript (.js) highlighter.
The highlighter formats JavaScript source code highlighting keywords, strings, numbers and characters.
*/
#ifndef SynHighlighterJScriptH
#define SynHighlighterJScriptH

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

namespace Synhighlighterjscript
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterJScript.pas, released 2000-04-14.
The Original Code is based on the mwJScript.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Tony de Buys.
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

$Id: SynHighlighterJScript.pas,v 1.21.2.7 2005/12/16 16:10:37 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a JavaScript/JScript highlighter for SynEdit)
@author(Tony De Buys [tony@lad.co.za], converted to SynEdit by David Muir <david@loanhead45.freeserve.co.uk>)
@created(December 1999, converted to SynEdit April 14, 2000)
@lastmod(2000-06-23)
The SynHighlighterJScript unit provides SynEdit with a JScript/JavaScript (.js) highlighter.
The highlighter formats JavaScript source code highlighting keywords, strings, numbers and characters.
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
                   tkUnknown,
                   tkNonReservedKey,
                   tkEvent,
                   tkSpecVar,
                   tkTemplate };
enum TRangeState {rsUnKnown,
                  rsAnsi,
                  rsLiteral,
                  rsLiteralTemplate };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;
//  TSynJScriptSyn = class(TSynCustomHighLighter)
//++ CodeFolding

//-- CodeFolding

class TSynJScriptSyn : public Syneditcodefolding::TSynCustomCodeFoldingHighlighter
{
private:
	TRangeState FRange;
	int fLiteralLevel;
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNonReservedKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fEventAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpecVarAttri;
	Synedithighlighter::TSynHighlighterAttributes* fTemplateAttri;
	void __fastcall AndSymbolProc();
	void __fastcall CommentProc();
	void __fastcall CRProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall MinusProc();
	void __fastcall ModSymbolProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall OrSymbolProc();
	void __fastcall PlusProc();
	void __fastcall PointProc();
	void __fastcall SlashProc();
	void __fastcall SpaceProc();
	void __fastcall StarProc();
	void __fastcall StringProc();
	void __fastcall LiteralsProc();
	void __fastcall LiteralsRangeProc();
	void __fastcall LiteralsTemplateRangeProc();
	void __fastcall SymbolProc();
	void __fastcall UnderScoreProc();
	void __fastcall UnknownProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Syneditcodefolding::TSynCustomCodeFoldingHighlighter inherited;
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynJScriptSyn(TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsKeyword(const String AKeyword);
	bool __fastcall IsEvent(const String AKeyword);
	bool __fastcall IsNonReserwedKeyWord(const String AKeyword);
	virtual void __fastcall Next();
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
//++ CodeFolding
	virtual void __fastcall ScanForFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine);
//-- CodeFolding
__published:
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
    /* ths attribut will hghlight words start wth underscore */
	__property Synedithighlighter::TSynHighlighterAttributes* SpecVarAttri = { read = fSpecVarAttri, write = fSpecVarAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NonReservedKeyAttri = { read = fNonReservedKeyAttri, write = fNonReservedKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* EventAttri = { read = fEventAttri, write = fEventAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* TemplateAttri = { read = fTemplateAttri, write = fTemplateAttri };
};

void SynHighlighterJScript_initialization();


}  // namespace SynHighlighterJScript

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterjscript;
#endif


#endif // SynHighlighterJScriptH

