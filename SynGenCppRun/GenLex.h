/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: GenLex.pas, released 2000-04-19.
Description: Tokenlist used by the generator.

The Original Code is based on mGenLex.pas by Martin Waldenburg, part of
the mwEdit component suite.
Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
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

$Id: GenLex.pas,v 1.4.2.4 2008/10/25 23:30:31 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef GenLexH
#define GenLexH

#include <System.hpp>
#include "d2c_system.h"

#include <System.SysUtils.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include "LongIntList.h"
#include "SynUnicode.h"

namespace Genlex
{

extern unsigned char Identifiers[256/*# range #0..#255*/];
extern int mHashTable[256/*# range #0..#255*/];
enum TIdTokenKind {IdBeginFunc,
                   IdBeginProc,
                   IdBraceOpen,
                   IdChars,
                   IdCharset,
                   IdCRLF,
                   IdEndFunc,
                   IdEndProc,
                   IdIdent,
                   IdIdentifier,
                   IdIdentStart,
                   IdKeys,
                   IdTokenTypes,
                   IdNull,
                   IdSensitive,
                   IdSpace,
                   IdStop,
                   IdEnclosedBy,
                   IdSampleSource,
                   IdUnknown };

class TGenLex : public System::TObject
{
	#include "GenLex_friends.inc"
public:
	typedef System::TObject inherited;
private:
	bool fIgnoreComments;
	System::PWideChar fOrigin;
	typedef void __fastcall (__closure *GenlexProc__0)();
	GenlexProc__0 fProcTable[256/*# range #0..#255*/];
	typedef TIdTokenKind __fastcall (__closure *GenlexProc__1)();
	GenlexProc__1 fFuncTable[256/*# range #0..#255*/];
	int Run;
	int Walker;
	int Running;
	int fStringLen;
	System::PWideChar fToIdent;
	bool fTokenizing;
	Longintlist::TLongIntList* FLinePosList;
	Longintlist::TLongIntList* FTokenPositionsList;
	typedef TIdTokenKind __fastcall (__closure *GenlexProc__2)();
	GenlexProc__2 fIdentFuncTable[151/*# range 0..150*/];
	int __fastcall KeyHash(System::PWideChar ToHash);
	bool __fastcall KeyComp(String aKey);
	TIdTokenKind __fastcall Func49();
	TIdTokenKind __fastcall Func60();
	TIdTokenKind __fastcall Func67();
	TIdTokenKind __fastcall Func75();
	TIdTokenKind __fastcall Func81();
	TIdTokenKind __fastcall Func89();
	TIdTokenKind __fastcall Func104();
	TIdTokenKind __fastcall Func122();
	TIdTokenKind __fastcall Func130();
	TIdTokenKind __fastcall Func147();
	TIdTokenKind __fastcall Func150();
	void __fastcall BraceOpenProc();
	TIdTokenKind __fastcall BraceOpenFunc();
	void __fastcall CRLFProc();
	TIdTokenKind __fastcall CRLFFunc();
	void __fastcall CharsetProc();
	TIdTokenKind __fastcall CharsetFunc();
	void __fastcall IdentProc();
	TIdTokenKind __fastcall IdentFunc();
	void __fastcall NullProc();
	TIdTokenKind __fastcall NullFunc();
	void __fastcall SpaceProc();
	TIdTokenKind __fastcall SpaceFunc();
	void __fastcall StopProc();
	TIdTokenKind __fastcall StopFunc();
	void __fastcall UnknownProc();
	TIdTokenKind __fastcall UnknownFunc();
	TIdTokenKind __fastcall AltFunc();
	void __fastcall InitIdent();
	TIdTokenKind __fastcall IdentKind(System::PWideChar MayBe);
	void __fastcall SetOrigin(System::PWideChar NewValue);
	void __fastcall SetRunPos(int Value);
	void __fastcall MakeMethodTables();
	TIdTokenKind __fastcall GetRunId();
	String __fastcall GetRunToken();
protected:
public:
	__fastcall TGenLex();
	virtual __fastcall ~TGenLex();
	void __fastcall Tokenize();
	void __fastcall Next();
	__property bool IgnoreComments = { read = fIgnoreComments, write = fIgnoreComments };
	__property System::PWideChar Origin = { read = fOrigin, write = SetOrigin };
	__property int RunPos = { read = Run, write = SetRunPos };
	String __fastcall NextToken();
	bool __fastcall Eof();
	__property TIdTokenKind RunId = { read = GetRunId };
	__property String RunToken = { read = GetRunToken };
};

void GenLex_initialization();


}  // namespace Genlex

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Genlex;
#endif


#endif // GenLexH

