/*------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterPas.pas, released 2000-04-17.
The Original Code is based on the mwPasSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Martin Waldenburg.
Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
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

$Id: SynHighlighterPas.pas,v 1.27.2.10 2009/02/23 15:43:50 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Pascal/Delphi syntax highlighter for SynEdit)
@author(Martin Waldenburg)
@created(1998, converted to SynEdit 2000-04-07)
@lastmod(2004-03-19)
The SynHighlighterPas unit provides SynEdit with a Object Pascal syntax highlighter.
Two extra properties included (DelphiVersion, PackageSource):
  DelphiVersion - Allows you to enable/disable the highlighting of various
                  language enhancements added in the different Delphi versions.
  PackageSource - Allows you to enable/disable the highlighting of package keywords
*/
#ifndef SynHighlighterPasH
#define SynHighlighterPasH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.RegularExpressions.hpp>
#include "SynEditCodeFolding.h"

namespace Synhighlighterpas
{

/*------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterPas.pas, released 2000-04-17.
The Original Code is based on the mwPasSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Martin Waldenburg.
Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
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

$Id: SynHighlighterPas.pas,v 1.27.2.10 2009/02/23 15:43:50 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Pascal/Delphi syntax highlighter for SynEdit)
@author(Martin Waldenburg)
@created(1998, converted to SynEdit 2000-04-07)
@lastmod(2004-03-19)
The SynHighlighterPas unit provides SynEdit with a Object Pascal syntax highlighter.
Two extra properties included (DelphiVersion, PackageSource):
  DelphiVersion - Allows you to enable/disable the highlighting of various
                  language enhancements added in the different Delphi versions.
  PackageSource - Allows you to enable/disable the highlighting of package keywords
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
                   tkAsm,
                   tkComment,
                   tkIdentifier,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkUnknown,
                   tkFloat,
                   tkHex,
                   tkDirec,
                   tkChar,
                   tkType };
enum TRangeState {rsANil,
                  rsAnsi,
                  rsAnsiAsm,
                  rsAsm,
                  rsBor,
                  rsBorAsm,
                  rsProperty,
                  rsExports,
                  rsDirective,
                  rsDirectiveAsm,
                  rsUnKnown };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;
enum TDelphiVersion {dvDelphi1,
                     dvDelphi2,
                     dvDelphi3,
                     dvDelphi4,
                     dvDelphi5,
                     dvDelphi6,
                     dvDelphi7,
                     dvDelphi8,
                     dvDelphi2005 };
const TDelphiVersion LastDelphiVersion = Synhighlighterpas::dvDelphi2005;
const System::WideChar BDSVersionPrefix[] = L"BDS";
//  TSynPasSyn = class(TSynCustomHighlighter)
//++ CodeFolding

//-- CodeFolding

class TSynPasSyn : public Syneditcodefolding::TSynCustomCodeFoldingHighlighter
{
private:
	bool fAsmStart;
	TRangeState fRange;
	TIdentFuncTableFunc fIdentFuncTable[641/*# range 0..640*/];
	TtkTokenKind fTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCharAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fFloatAttri;
	Synedithighlighter::TSynHighlighterAttributes* fHexAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fAsmAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDirecAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	TDelphiVersion fDelphiVersion;
	bool fPackageSource;
	Synedithighlighter::TSynHighlighterAttributes* fTypeAttri;
//++ CodeFolding
	TRegEx RE_BlockBegin;
	TRegEx RE_BlockEnd;
	TRegEx RE_Code;
//-- CodeFolding
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall KeyWordFunc(int Index);
	TtkTokenKind __fastcall FuncAsm(int Index);
	TtkTokenKind __fastcall FuncAutomated(int Index);
	TtkTokenKind __fastcall FuncCdecl(int Index);
	TtkTokenKind __fastcall FuncContains(int Index);
	TtkTokenKind __fastcall FuncDeprecated(int Index);
	TtkTokenKind __fastcall FuncDispid(int Index);
	TtkTokenKind __fastcall FuncDispinterface(int Index);
	TtkTokenKind __fastcall FuncEnd(int Index);
	TtkTokenKind __fastcall FuncExports(int Index);
	TtkTokenKind __fastcall FuncFinal(int Index);
	TtkTokenKind __fastcall FuncFinalization(int Index);
	TtkTokenKind __fastcall FuncHelper(int Index);
	TtkTokenKind __fastcall FuncImplements(int Index);
	TtkTokenKind __fastcall FuncIndex(int Index);
	TtkTokenKind __fastcall FuncName(int Index);
	TtkTokenKind __fastcall FuncNodefault(int Index);
	TtkTokenKind __fastcall FuncOperator(int Index);
	TtkTokenKind __fastcall FuncOverload(int Index);
	TtkTokenKind __fastcall FuncPackage(int Index);
	TtkTokenKind __fastcall FuncPlatform(int Index);
	TtkTokenKind __fastcall FuncProperty(int Index);
	TtkTokenKind __fastcall FuncRead(int Index);
	TtkTokenKind __fastcall FuncReadonly(int Index);
	TtkTokenKind __fastcall FuncReintroduce(int Index);
	TtkTokenKind __fastcall FuncRequires(int Index);
	TtkTokenKind __fastcall FuncResourcestring(int Index);
	TtkTokenKind __fastcall FuncSafecall(int Index);
	TtkTokenKind __fastcall FuncSealed(int Index);
	TtkTokenKind __fastcall FuncStdcall(int Index);
	TtkTokenKind __fastcall FuncStored(int Index);
	TtkTokenKind __fastcall FuncStringresource(int Index);
	TtkTokenKind __fastcall FuncThreadvar(int Index);
	TtkTokenKind __fastcall FuncWrite(int Index);
	TtkTokenKind __fastcall FuncWriteonly(int Index);
	TtkTokenKind __fastcall FuncType(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar MayBe);
	void __fastcall InitIdent();
	void __fastcall AddressOpProc();
	void __fastcall AsciiCharProc();
	void __fastcall AnsiProc();
	void __fastcall BorProc();
	void __fastcall BraceOpenProc();
	void __fastcall ColonOrGreaterProc();
	void __fastcall CRProc();
	void __fastcall IdentProc();
	void __fastcall IntegerProc();
	void __fastcall LFProc();
	void __fastcall LowerProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall PointProc();
	void __fastcall RoundOpenProc();
	void __fastcall SemicolonProc();
	void __fastcall SlashProc();
	void __fastcall SpaceProc();
	void __fastcall StringProc();
	void __fastcall SymbolProc();
	void __fastcall UnknownProc();
	void __fastcall SetDelphiVersion(TDelphiVersion Value);
	void __fastcall SetPackageSource(bool Value);
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Syneditcodefolding::TSynCustomCodeFoldingHighlighter inherited;
	__classmethod virtual Synedithighlighter::TSynHighlighterCapabilities __fastcall GetCapabilities();
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynPasSyn(TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	TtkTokenKind __fastcall GetTokenID();
	virtual int __fastcall GetTokenKind();
	virtual void __fastcall Next();
	virtual void __fastcall ResetRange();
	virtual void __fastcall SetRange(void* Value);
	virtual bool __fastcall UseUserSettings(int VersionIndex);
	virtual void __fastcall EnumUserSettings(TStrings* DelphiVersions);
//++ CodeFolding
	virtual void __fastcall ScanForFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine);
	virtual void __fastcall AdjustFoldRanges(Syneditcodefolding::TSynFoldRanges* FoldRanges, TStrings* LinesToScan);
//-- CodeFolding
__published:
	__property Synedithighlighter::TSynHighlighterAttributes* AsmAttri = { read = fAsmAttri, write = fAsmAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* DirectiveAttri = { read = fDirecAttri, write = fDirecAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* FloatAttri = { read = fFloatAttri, write = fFloatAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* HexAttri = { read = fHexAttri, write = fHexAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* CharAttri = { read = fCharAttri, write = fCharAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* TypeAttri = { read = fTypeAttri, write = fTypeAttri };
	__property TDelphiVersion DelphiVersion = { read = fDelphiVersion, write = SetDelphiVersion, default = /*# LastDelphiVersion */ 8 };
	__property bool PackageSource = { read = fPackageSource, write = SetPackageSource, default = true };
};

void SynHighlighterPas_initialization();


}  // namespace SynHighlighterPas

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterpas;
#endif


#endif // SynHighlighterPasH

