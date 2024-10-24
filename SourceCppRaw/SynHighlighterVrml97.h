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
	TRangeState fRange;
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
	TtkTokenKind __fastcall IdentKind(PWideChar MayBe);
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
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynVrml97Syn(TComponent* AOwner);
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
	__property Synedithighlighter::TSynHighlighterAttributes* NonReservedKeyAttri = { read = fNonReservedKeyAttri, write = fNonReservedKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* EcmaScriptKeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* EcmaScriptEventAttri = { read = fEventAttri, write = fEventAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlAppearanceAttri = { read = fVrmlAppearanceAttri, write = fVrmlAppearanceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlAttributeAttri = { read = fVrmlAttributeAttri, write = fVrmlAttributeAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlDefinitionAttri = { read = fVrmlDefinitionAttri, write = fVrmlDefinitionAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlEventAttri = { read = fVrmlEventAttri, write = fVrmlEventAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlGroupingAttri = { read = fVrmlGroupingAttri, write = fVrmlGroupingAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlInterpolatorAttri = { read = fVrmlInterpolatorAttri, write = fVrmlInterpolatorAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlLightAttri = { read = fVrmlLightAttri, write = fVrmlLightAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlNodeAttri = { read = fVrmlNodeAttri, write = fVrmlNodeAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlParameterAttri = { read = fVrmlParameterAttri, write = fVrmlParameterAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlprotoAttri = { read = fVrmlprotoAttri, write = fVrmlprotoAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlSensorAttri = { read = fVrmlSensorAttri, write = fVrmlSensorAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlShapeAttri = { read = fVrmlShapeAttri, write = fVrmlShapeAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlShape_HintAttri = { read = fVrmlShape_HintAttri, write = fVrmlShape_HintAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlTime_dependentAttri = { read = fVrmlTime_dependentAttri, write = fVrmlTime_dependentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlViewpointAttri = { read = fVrmlViewpointAttri, write = fVrmlViewpointAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VrmlWorldInfoAttri = { read = fVrmlWorldInfoAttri, write = fVrmlWorldInfoAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* X3DDocTypeAttri = { read = fX3DDocTypeAttri, write = fX3DDocTypeAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* X3DHeaderAttri = { read = fX3DHeaderAttri, write = fX3DHeaderAttri };
};

void SynHighlighterVrml97_initialization();


}  // namespace SynHighlighterVrml97

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightervrml97;
#endif


#endif // SynHighlighterVrml97H

