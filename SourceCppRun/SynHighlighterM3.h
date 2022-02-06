#ifndef SynHighlighterM3H
#define SynHighlighterM3H

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include <System.Win.Registry.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynHighlighterHashEntries.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterm3
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterM3.pas, released 2000-11-23.
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

$Id: SynHighlighterM3.pas,v 1.11.2.5 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Modula-3 syntax highlighter for SynEdit)
@author(Martin Pley <synedit@pley.de>)
@created(January 2000, converted to SynEdit November 23, 2000)
@lastmod(2000-11-23)
The SynHighlighterM3 unit provides SynEdit with a Modula-3 (.m3) highlighter.
*/
enum TtkTokenKind {tkComment,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkNumber,
                   tkPragma,
                   tkReserved,
                   tkSpace,
                   tkString,
                   tkSymbol,
                   tkUnknown,
                   tkSyntaxError };
enum TTokenRange {trNone,
                  trComment,
                  trPragma };
#pragma pack (push, 1)


struct TRangeState
{
	union {
		/*# false*/
		struct 
		{
			void* P;
		};		
		/*# true*/
		struct 
		{
			WORD TokenRange;
			WORD Level;
		};		
	};
};
#pragma pack (pop)


class TSynM3Syn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState FRange;
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fPragmaAttri;
	Synedithighlighter::TSynHighlighterAttributes* FReservedAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSyntaxErrorAttri;
	Synhighlighterhashentries::TSynHashEntryList* fKeywords;
	void __fastcall DoAddKeyword(String AKeyword, int AKind);
	int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall SymAsciiCharProc();
	void __fastcall SymCommentHelpProc();
	void __fastcall SymCRProc();
	void __fastcall SymIdentProc();
	void __fastcall SymLFProc();
	void __fastcall SymNestedHelperProc(WideChar AOpenChar, WideChar ACloseChar);
	void __fastcall SymNullProc();
	void __fastcall SymNumberProc();
	void __fastcall SymPragmaProc();
	void __fastcall SymPragmaHelpProc();
	void __fastcall SymRoundOpenProc();
	void __fastcall SymSpaceProc();
	void __fastcall SymStringProc();
	void __fastcall SymSymbolProc();
	void __fastcall SymUnknownProc();
protected:
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	#include "SynHighlighterM3_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynM3Syn(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynM3Syn();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
	virtual void __fastcall ResetRange();
	virtual void __fastcall SetRange(void* Value);
__published:
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* PragmaAttri = { read = fPragmaAttri, write = fPragmaAttri };
	__property TSynHighlighterAttributes* ReservedAttri = { read = FReservedAttri, write = FReservedAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property TSynHighlighterAttributes* SyntaxErrorAttri = { read = fSyntaxErrorAttri, write = fSyntaxErrorAttri };
};

void SynHighlighterM3_initialization();


}  // namespace SynHighlighterM3

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterm3;
#endif


#endif // SynHighlighterM3H

