/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

Code template generated with SynGen.
The original code is: SynHighlighterIDL.pas, released 2001-10-15.
Description: CORBA IDL Parser/Highlighter
The initial author of this file is P.L. Polak.
Unicode translation by Maël Hörz.
Copyright (c) 2001, all rights reserved.

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

$Id: SynHighlighterIDL.pas,v 1.8.2.7 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------*/
#ifndef SynHighlighterIDLH
#define SynHighlighterIDLH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighteridl
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
The original code is: SynHighlighterIDL.pas, released 2001-10-15.
Description: CORBA IDL Parser/Highlighter
The initial author of this file is P.L. Polak.
Unicode translation by Maël Hörz.
Copyright (c) 2001, all rights reserved.

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

$Id: SynHighlighterIDL.pas,v 1.8.2.7 2008/09/14 16:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------*/

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
                   tkDataType,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkNumber,
                   tkPreprocessor,
                   tkSpace,
                   tkString,
                   tkSymbol,
                   tkUnknown };
enum TRangeState {rsUnKnown,
                  rsComment,
                  rsString,
                  rsChar };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynIdlSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState FRange;
	TtkTokenKind FTokenID;
	TIdentFuncTableFunc fIdentFuncTable[101/*# range 0..100*/];
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDataTypeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fPreprocessorAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	void __fastcall IdentProc();
	void __fastcall SymbolProc();
	void __fastcall UnknownProc();
	TtkTokenKind __fastcall FuncAbstract(int Index);
	TtkTokenKind __fastcall FuncAny(int Index);
	TtkTokenKind __fastcall FuncAttribute(int Index);
	TtkTokenKind __fastcall FuncBoolean(int Index);
	TtkTokenKind __fastcall FuncCase(int Index);
	TtkTokenKind __fastcall FuncChar(int Index);
	TtkTokenKind __fastcall FuncConst(int Index);
	TtkTokenKind __fastcall FuncContext(int Index);
	TtkTokenKind __fastcall FuncCustom(int Index);
	TtkTokenKind __fastcall FuncDefault(int Index);
	TtkTokenKind __fastcall FuncDouble(int Index);
	TtkTokenKind __fastcall FuncEnum(int Index);
	TtkTokenKind __fastcall FuncException(int Index);
	TtkTokenKind __fastcall FuncFactory(int Index);
	TtkTokenKind __fastcall FuncFalse(int Index);
	TtkTokenKind __fastcall FuncFixed(int Index);
	TtkTokenKind __fastcall FuncFloat(int Index);
	TtkTokenKind __fastcall FuncIn(int Index);
	TtkTokenKind __fastcall FuncInout(int Index);
	TtkTokenKind __fastcall FuncInterface(int Index);
	TtkTokenKind __fastcall FuncLocal(int Index);
	TtkTokenKind __fastcall FuncLong(int Index);
	TtkTokenKind __fastcall FuncModule(int Index);
	TtkTokenKind __fastcall FuncNative(int Index);
	TtkTokenKind __fastcall FuncObject(int Index);
	TtkTokenKind __fastcall FuncOctet(int Index);
	TtkTokenKind __fastcall FuncOneway(int Index);
	TtkTokenKind __fastcall FuncOut(int Index);
	TtkTokenKind __fastcall FuncPrivate(int Index);
	TtkTokenKind __fastcall FuncPublic(int Index);
	TtkTokenKind __fastcall FuncRaises(int Index);
	TtkTokenKind __fastcall FuncReadonly(int Index);
	TtkTokenKind __fastcall FuncSequence(int Index);
	TtkTokenKind __fastcall FuncShort(int Index);
	TtkTokenKind __fastcall FuncString(int Index);
	TtkTokenKind __fastcall FuncStruct(int Index);
	TtkTokenKind __fastcall FuncSupports(int Index);
	TtkTokenKind __fastcall FuncSwitch(int Index);
	TtkTokenKind __fastcall FuncTrue(int Index);
	TtkTokenKind __fastcall FuncTruncatable(int Index);
	TtkTokenKind __fastcall FuncTypedef(int Index);
	TtkTokenKind __fastcall FuncUnion(int Index);
	TtkTokenKind __fastcall FuncUnsigned(int Index);
	TtkTokenKind __fastcall FuncValuebase(int Index);
	TtkTokenKind __fastcall FuncValuetype(int Index);
	TtkTokenKind __fastcall FuncVoid(int Index);
	TtkTokenKind __fastcall FuncWchar(int Index);
	TtkTokenKind __fastcall FuncWstring(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall InitIdent();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall SpaceProc();
	void __fastcall CRProc();
	void __fastcall LFProc();
	void __fastcall CommentOpenProc();
	void __fastcall CommentProc();
	void __fastcall StringOpenProc();
	void __fastcall StringProc();
	void __fastcall CharOpenProc();
	void __fastcall CharProc();
	void __fastcall PreProcessorProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	__fastcall TSynIdlSyn(TComponent* AOwner);
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	virtual void* __fastcall GetRange();
	virtual void __fastcall ResetRange();
	virtual void __fastcall SetRange(void* Value);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual void __fastcall Next();
__published:
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* DataTypeAttri = { read = fDataTypeAttri, write = fDataTypeAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* PreprocessorAttri = { read = fPreprocessorAttri, write = fPreprocessorAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
};

void SynHighlighterIDL_initialization();


}  // namespace SynHighlighterIDL

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighteridl;
#endif


#endif // SynHighlighterIDLH

