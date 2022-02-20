#ifndef SynHighlighterXMLH
#define SynHighlighterXMLH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Win.Registry.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterxml
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterXML.pas, released 2000-11-20.
The Initial Author of this file is Jeff Rafter.
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

$Id: SynHighlighterXML.pas,v 1.11.2.6 2008/09/14 16:25:03 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

History:
-------------------------------------------------------------------------------
2000-11-30 Removed mHashTable and MakeIdentTable per Michael Hieke

Known Issues:
- Nothing is really constrained (properly) to valid name chars
- Entity Refs are not constrained to valid name chars
- Support for "Combining Chars and Extender Chars" in names are lacking
- The internal DTD is not parsed (and not handled correctly)
-------------------------------------------------------------------------------*/
/*
@abstract(Provides an XML highlighter for SynEdit)
@author(Jeff Rafter-- Phil 4:13, based on SynHighlighterHTML by Hideo Koiso)
@created(2000-11-17)
@lastmod(2001-03-12)
The SynHighlighterXML unit provides SynEdit with an XML highlighter.
*/
    //

    //These are unused at the moment

    /*tkDocTypeAposAttrValue, tkDocTypeAposEntityRef, tkDocTypeAttribute,
     tkDocTypeElement, tkDocTypeEqual tkDocTypeQuoteAttrValue,
     tkDocTypeQuoteEntityRef*/
enum TtkTokenKind {tkAposAttrValue,
                   tkAposEntityRef,
                   tkAttribute,
                   tkCDATA,
                   tkComment,
                   tkElement,
                   tkEntityRef,
                   tkEqual,
                   tkNull,
                   tkProcessingInstruction,
                   tkQuoteAttrValue,
                   tkQuoteEntityRef,
                   tkSpace,
                   tkSymbol,
                   tkText,
                   tknsAposAttrValue,
                   tknsAposEntityRef,
                   tknsAttribute,
                   tknsEqual,
                   tknsQuoteAttrValue,
                   tknsQuoteEntityRef,
                   tkDocType };

    //

    //These are unused at the moment

    /*rsDocTypeAposAttrValue, rsDocTypeAposEntityRef, rsDocTypeAttribute,
     rsDocTypeElement, rsDocTypeEqual, rsDocTypeQuoteAttrValue,
     rsDocTypeQuoteEntityRef*/
enum TRangeState {rsAposAttrValue,
                  rsAPosEntityRef,
                  rsAttribute,
                  rsCDATA,
                  rsComment,
                  rsElement,
                  rsEntityRef,
                  rsEqual,
                  rsProcessingInstruction,
                  rsQuoteAttrValue,
                  rsQuoteEntityRef,
                  rsText,
                  rsnsAposAttrValue,
                  rsnsAPosEntityRef,
                  rsnsEqual,
                  rsnsQuoteAttrValue,
                  rsnsQuoteEntityRef,
                  rsDocType,
                  rsDocTypeSquareBraces };

class TSynXMLSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState FRange;
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fElementAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fTextAttri;
	Synedithighlighter::TSynHighlighterAttributes* fEntityRefAttri;
	Synedithighlighter::TSynHighlighterAttributes* fProcessingInstructionAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCDATAAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDocTypeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fAttributeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fnsAttributeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fAttributeValueAttri;
	Synedithighlighter::TSynHighlighterAttributes* fnsAttributeValueAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	bool FWantBracesParsed;
	void __fastcall NullProc();
	void __fastcall CarriageReturnProc();
	void __fastcall LineFeedProc();
	void __fastcall SpaceProc();
	void __fastcall LessThanProc();
	void __fastcall GreaterThanProc();
	void __fastcall CommentProc();
	void __fastcall ProcessingInstructionProc();
	void __fastcall DocTypeProc();
	void __fastcall CDATAProc();
	void __fastcall TextProc();
	void __fastcall ElementProc();
	void __fastcall AttributeProc();
	void __fastcall QAttributeValueProc();
	void __fastcall AAttributeValueProc();
	void __fastcall EqualProc();
	void __fastcall IdentProc();
	void __fastcall NextProcedure();
	bool __fastcall NextTokenIs(String Token);
	void __fastcall EntityRefProc();
	void __fastcall QEntityRefProc();
	void __fastcall AEntityRefProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
	virtual bool __fastcall IsNameChar();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynXMLSyn(System::Classes::TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
__published:
	__property TSynHighlighterAttributes* ElementAttri = { read = fElementAttri, write = fElementAttri };
	__property TSynHighlighterAttributes* AttributeAttri = { read = fAttributeAttri, write = fAttributeAttri };
	__property TSynHighlighterAttributes* NamespaceAttributeAttri = { read = fnsAttributeAttri, write = fnsAttributeAttri };
	__property TSynHighlighterAttributes* AttributeValueAttri = { read = fAttributeValueAttri, write = fAttributeValueAttri };
	__property TSynHighlighterAttributes* NamespaceAttributeValueAttri = { read = fnsAttributeValueAttri, write = fnsAttributeValueAttri };
	__property TSynHighlighterAttributes* TextAttri = { read = fTextAttri, write = fTextAttri };
	__property TSynHighlighterAttributes* CDATAAttri = { read = fCDATAAttri, write = fCDATAAttri };
	__property TSynHighlighterAttributes* EntityRefAttri = { read = fEntityRefAttri, write = fEntityRefAttri };
	__property TSynHighlighterAttributes* ProcessingInstructionAttri = { read = fProcessingInstructionAttri, write = fProcessingInstructionAttri };
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* DocTypeAttri = { read = fDocTypeAttri, write = fDocTypeAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property bool WantBracesParsed = { read = FWantBracesParsed, write = FWantBracesParsed, default = true };
};

void SynHighlighterXML_initialization();


}  // namespace SynHighlighterXML

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterxml;
#endif


#endif // SynHighlighterXMLH

