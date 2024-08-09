/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterJSON.pas, released 2015-01-14.
The Initial Author of this file is Christian-W. Budde.
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

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net
*/
#ifndef SynHighlighterJSONH
#define SynHighlighterJSONH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include <System.Win.Registry.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include "SynEditCodeFolding.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterjson
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterJSON.pas, released 2015-01-14.
The Initial Author of this file is Christian-W. Budde.
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

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net
*/
  //++ CodeFolding

  //++ CodeFolding
enum TtkTokenKind {tkString,
                   tkReserved,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkSymbol,
                   tkUnknown };
enum TRangeState {rsUnKnown,
                  rsAttribute,
                  rsObjectValue,
                  rsArrayValue };

//++ CodeFolding

//-- CodeFolding

class TSynJSONSyn : public Syneditcodefolding::TSynCustomCodeFoldingHighlighter
{
private:
	TRangeState FRange;
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* FReservedAttri;
	Synedithighlighter::TSynHighlighterAttributes* fAttributeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fValueAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	void __fastcall CloseArrayProc();
	void __fastcall CloseObjectProc();
	void __fastcall ColonProc();
	void __fastcall CommaProc();
	void __fastcall CRProc();
	void __fastcall LFProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall OpenArrayProc();
	void __fastcall OpenObjectProc();
	void __fastcall ReservedWordProc();
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
	__fastcall TSynJSONSyn(TComponent* AOwner);
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
	virtual void __fastcall ScanForFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine);
//-- CodeFolding
__published:
	__property Synedithighlighter::TSynHighlighterAttributes* AttributeAttri = { read = fAttributeAttri, write = fAttributeAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* ReservedAttri = { read = FReservedAttri, write = FReservedAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* ValueAttri = { read = fValueAttri, write = fValueAttri };
};

void SynHighlighterJSON_initialization();


}  // namespace SynHighlighterJSON

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterjson;
#endif


#endif // SynHighlighterJSONH

