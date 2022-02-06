#ifndef SynHighlighterVrml97H
#define SynHighlighterVrml97H

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.Win.Registry.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynHighlighterHashEntries.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlightervrml97
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterVrml.pas, released 2002-10-21.
The Original Code is based on: SynHighlighterJScript.pas, released 2000-04-14.
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

$Id: SynHighlighterVrml97.pas,v 1.6.2.8 2008/09/14 16:25:03 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Vrml97/X3D/JavaScript highlighter for SynEdit)
@author(Massimo Maria Ghisalberti (nissl@mammuth.it)
@created(november 2002 [December 1999, converted to SynEdit April 14, 2000])
@lastmod(2002-11-03)
The SynHighlighterVrml97 unit provides SynEdit with a Vrml97/X3D/JavaScript (.wrl;*.x3d) highlighter.
The highlighter formats Vrml97/X3D source code highlighting keywords, strings, numbers and characters.
*/

/* TODO: The Ansi version kept unclear to the status of following tokens:

  Token       Ambiguity
  =====       =========
  bottom      tkVrmlAttribute or tkNonReservedKey
  description tkVrmlAttribute or tkNonReservedKey
  height      tkVrmlAttribute or tkNonReservedKey
  location    tkVrmlAttribute or tkNonReservedKey
  style       tkVrmlAttribute or tkNonReservedKey
  type        tkVrmlAttribute or tkNonReservedKey

  NULL        tkVrmlParameter or tkVrmlProto
  FALSE       tkVrmlParameter or tkVrmlProto
  
  Text        tkVrmlShape or tkNonReservedKey

  I took always the first one as this produces the same results as in the
  Ansi-version, because the other cases were never reached (due to the way
  the if construct was used).
*/
enum TtkTokenKind {tkComment,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkSymbol,
                   tkUnknown,
                   tkNonReservedKey,
                   tkEvent,
                   tkVrmlAppearance,
                   tkVrmlAttribute,
                   tkVrmlDefinition,
                   tkVrmlEvent,
                   tkVrmlGrouping,
                   tkVrmlInterpolator,
                   tkVrmlLight,
                   tkVrmlNode,
                   tkVrmlParameter,
                   tkVrmlproto,
                   tkVrmlSensor,
                   tkVrmlShape,
                   tkVrmlShape_Hint,
                   tkVrmlTime_dependent,
                   tkVrmlViewpoint,
                   tkVrmlWorldInfo,
                   tkX3DDocType,
                   tkX3DHeader };
enum TRangeState {rsNormalText,
                  rsComment,
                  rsX3DHeader,
                  rsX3DDocType };

class TSynVrml97Syn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState FRange;
	bool isDoctype;
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
	Synedithighlighter::TSynHighlighterAttributes* fVrmlAppearanceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlAttributeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlDefinitionAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlEventAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlGroupingAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlInterpolatorAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlLightAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlNodeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlParameterAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlprotoAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlSensorAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlShapeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlShape_HintAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlTime_dependentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlViewpointAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVrmlWorldInfoAttri;
	Synedithighlighter::TSynHighlighterAttributes* fX3DDocTypeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fX3DHeaderAttri;
	Synhighlighterhashentries::TSynHashEntryList* fKeywords;
	void __fastcall DoAddKeyword(String AKeyword, int AKind);
	int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall AndSymbolProc();
	void __fastcall CommentProc();
	void __fastcall DiesisCommentProc();
	void __fastcall X3DDocTypeOpenProc();
	void __fastcall X3DDocTypeProc();
	void __fastcall X3DHeaderOpenProc();
	void __fastcall X3DHeaderProc();
	void __fastcall InCommentProc();
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
	void __fastcall SymbolProc();
	void __fastcall UnknownProc();
	bool __fastcall NextTokenIs(String T);
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	#include "SynHighlighterVrml97_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynVrml97Syn(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynVrml97Syn();
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
	__property TSynHighlighterAttributes* NonReservedKeyAttri = { read = fNonReservedKeyAttri, write = fNonReservedKeyAttri };
	__property TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* EcmaScriptKeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* EcmaScriptEventAttri = { read = fEventAttri, write = fEventAttri };
	__property TSynHighlighterAttributes* VrmlAppearanceAttri = { read = fVrmlAppearanceAttri, write = fVrmlAppearanceAttri };
	__property TSynHighlighterAttributes* VrmlAttributeAttri = { read = fVrmlAttributeAttri, write = fVrmlAttributeAttri };
	__property TSynHighlighterAttributes* VrmlDefinitionAttri = { read = fVrmlDefinitionAttri, write = fVrmlDefinitionAttri };
	__property TSynHighlighterAttributes* VrmlEventAttri = { read = fVrmlEventAttri, write = fVrmlEventAttri };
	__property TSynHighlighterAttributes* VrmlGroupingAttri = { read = fVrmlGroupingAttri, write = fVrmlGroupingAttri };
	__property TSynHighlighterAttributes* VrmlInterpolatorAttri = { read = fVrmlInterpolatorAttri, write = fVrmlInterpolatorAttri };
	__property TSynHighlighterAttributes* VrmlLightAttri = { read = fVrmlLightAttri, write = fVrmlLightAttri };
	__property TSynHighlighterAttributes* VrmlNodeAttri = { read = fVrmlNodeAttri, write = fVrmlNodeAttri };
	__property TSynHighlighterAttributes* VrmlParameterAttri = { read = fVrmlParameterAttri, write = fVrmlParameterAttri };
	__property TSynHighlighterAttributes* VrmlprotoAttri = { read = fVrmlprotoAttri, write = fVrmlprotoAttri };
	__property TSynHighlighterAttributes* VrmlSensorAttri = { read = fVrmlSensorAttri, write = fVrmlSensorAttri };
	__property TSynHighlighterAttributes* VrmlShapeAttri = { read = fVrmlShapeAttri, write = fVrmlShapeAttri };
	__property TSynHighlighterAttributes* VrmlShape_HintAttri = { read = fVrmlShape_HintAttri, write = fVrmlShape_HintAttri };
	__property TSynHighlighterAttributes* VrmlTime_dependentAttri = { read = fVrmlTime_dependentAttri, write = fVrmlTime_dependentAttri };
	__property TSynHighlighterAttributes* VrmlViewpointAttri = { read = fVrmlViewpointAttri, write = fVrmlViewpointAttri };
	__property TSynHighlighterAttributes* VrmlWorldInfoAttri = { read = fVrmlWorldInfoAttri, write = fVrmlWorldInfoAttri };
	__property TSynHighlighterAttributes* X3DDocTypeAttri = { read = fX3DDocTypeAttri, write = fX3DDocTypeAttri };
	__property TSynHighlighterAttributes* X3DHeaderAttri = { read = fX3DHeaderAttri, write = fX3DHeaderAttri };
};

void SynHighlighterVrml97_initialization();


}  // namespace SynHighlighterVrml97

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightervrml97;
#endif


#endif // SynHighlighterVrml97H

