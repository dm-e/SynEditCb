/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

Code template generated with SynGen.
The original code is: SynHighlighterLDraw.pas, released 2003-04-12.
Description: LDraw Parser/Highlighter
The initial author of this file is Orion Pobursky.
Copyright (c) 2003, all rights reserved.
Unicode translation by Maël Hörz.

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

$Id: SynHighlighterLDraw.pas,v 1.7.2.7 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------*/
/*
@abstract(Provides an LDraw syntax highlighter for SynEdit)
@author(Orion Pobursky)
@created(03/01/2003)
@lastmod(07/05/2003)
The SynHighlighterLDraw unit provides SynEdit with a LEGO LDraw (.ldr / .dat) highlighter.
*/
#ifndef SynHighlighterLDrawH
#define SynHighlighterLDrawH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEditHighlighter.h"
#include "SynEditTypes.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterldraw
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

Code template generated with SynGen.
The original code is: SynHighlighterLDraw.pas, released 2003-04-12.
Description: LDraw Parser/Highlighter
The initial author of this file is Orion Pobursky.
Copyright (c) 2003, all rights reserved.
Unicode translation by Maël Hörz.

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

$Id: SynHighlighterLDraw.pas,v 1.7.2.7 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------*/
/*
@abstract(Provides an LDraw syntax highlighter for SynEdit)
@author(Orion Pobursky)
@created(03/01/2003)
@lastmod(07/05/2003)
The SynHighlighterLDraw unit provides SynEdit with a LEGO LDraw (.ldr / .dat) highlighter.
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
enum TtkTokenKind {tkColor,
                   tkComment,
                   tkFirstTri,
                   tkFourthTri,
                   tkIdentifier,
                   tkKey,
                   tkLine,
                   tkNull,
                   tkOpLine,
                   tkQuad,
                   tkSecondTri,
                   tkThirdTri,
                   tkTriangle,
                   tkUnknown };
enum TRangeState {rsUnKnown };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynLDRSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState fRange;
	TtkTokenKind fTokenID;
	TIdentFuncTableFunc fIdentFuncTable[2/*# range 0..1*/];
	Synedithighlighter::TSynHighlighterAttributes* fColorAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fFirstTriAttri;
	Synedithighlighter::TSynHighlighterAttributes* fFourthTriAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fLineAttri;
	Synedithighlighter::TSynHighlighterAttributes* fOpLineAttri;
	Synedithighlighter::TSynHighlighterAttributes* fQuadAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSecondTriAttri;
	Synedithighlighter::TSynHighlighterAttributes* fThirdTriAttri;
	Synedithighlighter::TSynHighlighterAttributes* fTriangleAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall FuncAuthor(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar MayBe);
	void __fastcall InitIdent();
	void __fastcall IdentProc();
	void __fastcall Number1Proc();
	void __fastcall UnknownProc();
	void __fastcall NullProc();
	void __fastcall CRProc();
	void __fastcall LFProc();
	WideChar __fastcall FirstChar(PWideChar DatLine);
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	__fastcall TSynLDRSyn(TComponent* AOwner);
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	virtual void* __fastcall GetRange();
	virtual void __fastcall ResetRange();
	virtual void __fastcall SetRange(void* Value);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual String __fastcall GetKeyWords(int TokenKind);
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual void __fastcall Next();
__published:
public:
	__property Synedithighlighter::TSynHighlighterAttributes* ColorAttri = { read = fColorAttri, write = fColorAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* FirstTriAttri = { read = fFirstTriAttri, write = fFirstTriAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* FourthTriAttri = { read = fFourthTriAttri, write = fFourthTriAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* LineAttri = { read = fLineAttri, write = fLineAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* OpLineAttri = { read = fOpLineAttri, write = fOpLineAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* QuadAttri = { read = fQuadAttri, write = fQuadAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SecondTriAttri = { read = fSecondTriAttri, write = fSecondTriAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* ThirdTriAttri = { read = fThirdTriAttri, write = fThirdTriAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* TriangleAttri = { read = fTriangleAttri, write = fTriangleAttri };
};

void SynHighlighterLDraw_initialization();


}  // namespace SynHighlighterLDraw

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterldraw;
#endif


#endif // SynHighlighterLDrawH

