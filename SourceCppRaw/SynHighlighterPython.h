#ifndef SynHighlighterPythonH
#define SynHighlighterPythonH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditHighlighter.h"
#include "SynEditTypes.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "SynEditCodeFolding.h"
#include <System.RegularExpressions.hpp>

namespace Synhighlighterpython
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterPython.pas, released 2000-06-23.
The Original Code is based on the odPySyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Olivier Deckmyn.
Portions created by M.Utku Karatas and Dennis Chuah.
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

$Id: SynHighlighterPython.pas,v 1.18.2.7 2008/09/14 16:25:02 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(A Python language highlighter for SynEdit)
@author(Olivier Deckmyn, converted to SynEdit by David Muir <dhmn@dmsoftware.co.uk>)
@created(unknown, converted to SynEdit on 2000-06-23)
@lastmod(2003-02-13)
The SynHighlighterPython implements a highlighter for Python for the SynEdit projects.
*/
//++ CodeFolding

//-- CodeFolding
const System::Set<unsigned char, 0, 255> ALPHA_CHARS = System::Set<unsigned char, 0, 255>() << L'_' <<  \
										97 << 98 << 99 << 100 << 101 << 102 <<  \
										103 << 104 << 105 << 106 << 107 << 108 <<  \
										109 << 110 << 111 << 112 << 113 << 114 <<  \
										115 << 116 << 117 << 118 << 119 << 120 <<  \
										121 << 122 <<  \
										65 << 66 << 67 << 68 << 69 << 70 <<  \
										71 << 72 << 73 << 74 << 75 << 76 <<  \
										77 << 78 << 79 << 80 << 81 << 82 <<  \
										83 << 84 << 85 << 86 << 87 << 88 <<  \
										89 << 90;
enum TtkTokenKind {tkComment,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkSymbol,
                   tkNonKeyword,
                   tkTrippleQuotedString,
                   tkSystemDefined,
                   tkHex,
                   tkOct,
                   tkFloat,
                   tkUnknown };
 //this is to indicate if a string is made multiline by backslash char at line end (as in C++ highlighter)
enum TRangeState {rsANil,
                  rsComment,
                  rsUnKnown,
                  rsMultiLineString,
                  rsMultilineString2,
                  rsMultilineString3 };

//++ CodeFolding

//-- CodeFolding

class TSynPythonSyn : public Syneditcodefolding::TSynCustomCodeFoldingHighlighter
{
private:
	WideChar fStringStarter;  // used only for rsMultilineString3 stuff
	TRangeState FRange;
	TtkTokenKind FTokenID;
	System::Classes::TStringList* fKeywords;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDocStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fHexAttri;
	Synedithighlighter::TSynHighlighterAttributes* fOctalAttri;
	Synedithighlighter::TSynHighlighterAttributes* fFloatAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNonKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSystemAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fErrorAttri;
//++ CodeFolding
	System::Regularexpressions::TRegEx BlockOpenerRE;
//-- CodeFolding
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall SymbolProc();
	void __fastcall CRProc();
	void __fastcall CommentProc();
	void __fastcall GreaterProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall LowerProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall SpaceProc();
	void __fastcall PreStringProc();
	void __fastcall UnicodeStringProc();
	void __fastcall StringProc();
	void __fastcall String2Proc();
	void __fastcall StringEndProc(WideChar EndChar);
	void __fastcall UnknownProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
	System::Classes::TStringList* __fastcall GetKeywordIdentifiers();
	__property System::Classes::TStringList* Keywords = { read = fKeywords };
	__property TtkTokenKind TokenId = { read = FTokenID };
public:
	typedef Syneditcodefolding::TSynCustomCodeFoldingHighlighter inherited;	
	#include "SynHighlighterPython_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynPythonSyn(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynPythonSyn();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
//++ CodeFolding
	virtual void __fastcall InitFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges);
	virtual void __fastcall ScanForFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, System::Classes::TStrings* LinesToScan, int FromLine, int ToLine);
//-- CodeFolding
__published:
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NonKeyAttri = { read = fNonKeyAttri, write = fNonKeyAttri };
	__property TSynHighlighterAttributes* SystemAttri = { read = fSystemAttri, write = fSystemAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* HexAttri = { read = fHexAttri, write = fHexAttri };
	__property TSynHighlighterAttributes* OctalAttri = { read = fOctalAttri, write = fOctalAttri };
	__property TSynHighlighterAttributes* FloatAttri = { read = fFloatAttri, write = fFloatAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* DocStringAttri = { read = fDocStringAttri, write = fDocStringAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property TSynHighlighterAttributes* ErrorAttri = { read = fErrorAttri, write = fErrorAttri };
};

void SynHighlighterPython_initialization();
void SynHighlighterPython_finalization();


}  // namespace SynHighlighterPython

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterpython;
#endif


#endif // SynHighlighterPythonH

