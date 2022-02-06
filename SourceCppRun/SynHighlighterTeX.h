#ifndef SynHighlighterTeXH
#define SynHighlighterTeXH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>

namespace Synhighlightertex
{

/*------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterTex.pas, released 2002-09-18.
Author of this file is Soeren Sproessig.
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

$Id: SynHighlighterTeX.pas,v 1.5.2.5 2008/09/14 16:25:03 maelh Exp $

You may retrieve the latest version of this file from sproessig@bs-webdesign.de

The unit SynHighlighterTeX provides SynEdit with a TeX highlighter.

Known Issues:
-------------------------------------------------------------------------------*/
enum TtkTokenKind {tkBrace,
                   tkBracket,
                   tkNull,
                   tkSpace,
                   tkText,
                   tkComment,
                   tkControlSequence,
                   tkMathMode };

class TSynTeXSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fTextAttri;
	Synedithighlighter::TSynHighlighterAttributes* fControlSequenceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fMathmodeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fBracketAttri;
	Synedithighlighter::TSynHighlighterAttributes* fBraceAttri;
	Synedithighlighter::TSynHighlighterAttributes* __fastcall CreateHighlighterAttributes(String Name, String FriendlyName, TColor Foreground, TColor Background, TFontStyles FontStyles);
	void __fastcall CRProc();
	void __fastcall TextProc();
	void __fastcall LFProc();
	void __fastcall NullProc();
	void __fastcall CommentProc();
	void __fastcall SpaceProc();
	void __fastcall ControlSequenceProc();
	void __fastcall BraceOpenProc();
	void __fastcall BraceCloseProc();
	void __fastcall BracketOpenProc();
	void __fastcall BracketCloseProc();
	void __fastcall MathmodeProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	#include "SynHighlighterTeX_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynTeXSyn(System::Classes::TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
__published:
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* TextAttri = { read = fTextAttri, write = fTextAttri };
	__property TSynHighlighterAttributes* ControlSequenceAttri = { read = fControlSequenceAttri, write = fControlSequenceAttri };
	__property TSynHighlighterAttributes* MathmodeAttri = { read = fMathmodeAttri, write = fMathmodeAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* BraceAttri = { read = fBraceAttri, write = fBraceAttri };
	__property TSynHighlighterAttributes* BracketAttri = { read = fBracketAttri, write = fBracketAttri };
};

void SynHighlighterTeX_initialization();


}  // namespace SynHighlighterTeX

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightertex;
#endif


#endif // SynHighlighterTeXH

