/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterURI.pas, released 2003-04-10.
The initial author of this file is Maël Hörz.
Unicode translation by Maël Hörz.
All Rights Reserved.

Contributors to the SynEdit project are listed in the Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

-------------------------------------------------------------------------------*/
/*
@abstract(Provides an URI syntax highlighter for SynEdit)
@author(Maël Hörz)
@created(2003)
@lastmod(2004-03-19)
http://www.mh-net.de.vu

The SynHighlighterURI unit implements an URI syntax highlighter for SynEdit.

Recognition of URIs is based on the information provided in the document
"Uniform Resource Identifiers (URI): Generic Syntax" of "The Internet Society",
that can be found at http://www.ietf.org/rfc/rfc2396.txt.

Also interesting is http://www.freesoft.org/CIE/RFC/1738/33.htm which describes
general URL syntax and major protocols.

these protocols are recognized:
-------------------------------
http://
https://
ftp://
mailto:
news: or news://
nntp://
telnet://
gopher://
prospero://
wais://

as well as commonly used shorthands:
------------------------------------
someone@somewhere.org
www.host.org
*/
#ifndef SynHighlighterURIH
#define SynHighlighterURIH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighteruri
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterURI.pas, released 2003-04-10.
The initial author of this file is Maël Hörz.
Unicode translation by Maël Hörz.
All Rights Reserved.

Contributors to the SynEdit project are listed in the Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

-------------------------------------------------------------------------------*/
/*
@abstract(Provides an URI syntax highlighter for SynEdit)
@author(Maël Hörz)
@created(2003)
@lastmod(2004-03-19)
http://www.mh-net.de.vu

The SynHighlighterURI unit implements an URI syntax highlighter for SynEdit.

Recognition of URIs is based on the information provided in the document
"Uniform Resource Identifiers (URI): Generic Syntax" of "The Internet Society",
that can be found at http://www.ietf.org/rfc/rfc2396.txt.

Also interesting is http://www.freesoft.org/CIE/RFC/1738/33.htm which describes
general URL syntax and major protocols.

these protocols are recognized:
-------------------------------
http://
https://
ftp://
mailto:
news: or news://
nntp://
telnet://
gopher://
prospero://
wais://

as well as commonly used shorthands:
------------------------------------
someone@somewhere.org
www.host.org
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
enum TtkTokenKind {tkNull,
                   tkSpace,
                   tkFtpLink,
                   tkGopherLink,
                   tkHttpLink,
                   tkHttpsLink,
                   tkMailtoLink,
                   tkNewsLink,
                   tkNntpLink,
                   tkProsperoLink,
                   tkTelnetLink,
                   tkWaisLink,
                   tkWebLink,
                   tkUnknown,
                   tkNullChar };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;
typedef bool __fastcall (__closure *TAlreadyVisitedURIFunc) (String);

class TSynURISyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	PWideChar fMayBeProtocol;
	TtkTokenKind fTokenID;
	TIdentFuncTableFunc fIdentFuncTable[16/*# range 0..15*/];
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fURIAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVisitedURIAttri;
	TAlreadyVisitedURIFunc fAlreadyVisitedURI;
	int __fastcall HashKey(PWideChar Str);
	void __fastcall InitIdent();
	void __fastcall CRProc();
	void __fastcall LFProc();
	void __fastcall NullProc();
	void __fastcall ProtocolProc();
	void __fastcall SpaceProc();
	void __fastcall UnknownProc();
	TtkTokenKind __fastcall AltFunc(int Key);
	TtkTokenKind __fastcall FuncFtp(int Key);
	TtkTokenKind __fastcall FuncGopher(int Key);
	TtkTokenKind __fastcall FuncHttp(int Key);
	TtkTokenKind __fastcall FuncHttps(int Key);
	TtkTokenKind __fastcall FuncMailto(int Key);
	TtkTokenKind __fastcall FuncNews(int Key);
	TtkTokenKind __fastcall FuncNntp(int Key);
	TtkTokenKind __fastcall FuncProspero(int Key);
	TtkTokenKind __fastcall FuncTelnet(int Key);
	TtkTokenKind __fastcall FuncWais(int Key);
	TtkTokenKind __fastcall FuncWeb(int Key);
	bool __fastcall IsAlphaNum(WideChar AChar);
	bool __fastcall IsMark(WideChar AChar);
	bool __fastcall IsReserved(WideChar AChar);
	bool __fastcall IsUnreserved(WideChar AChar);
	bool __fastcall IsURIChar(WideChar AChar);
	bool __fastcall IsNeverAtEnd(WideChar AChar);
	bool __fastcall IsEMailAddressChar(WideChar AChar);
	bool __fastcall IsNeverAtEMailAddressEnd(WideChar AChar);
	bool __fastcall IsValidEmailAddress();
	bool __fastcall IsValidURI();
	bool __fastcall IsValidWebLink();
	void __fastcall SetURIAttri(Synedithighlighter::TSynHighlighterAttributes* const Value);
	void __fastcall SetVisitedURIAttri(Synedithighlighter::TSynHighlighterAttributes* const Value);
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsCurrentToken(const String Token);
	virtual bool __fastcall IsFilterStored();
	void __fastcall SetAlreadyVisitedURIFunc(TAlreadyVisitedURIFunc Value);
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynURISyn(TComponent* AOwner);
	virtual __fastcall ~TSynURISyn();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual void __fastcall Next();
__published:
public:
	__property Synedithighlighter::TSynHighlighterAttributes* URIAttri = { read = fURIAttri, write = SetURIAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* VisitedURIAttri = { read = fVisitedURIAttri, write = SetVisitedURIAttri };
};
const int SYN_ATTR_URI = 6;
const int SYN_ATTR_VISITEDURI = 7;

void SynHighlighterURI_initialization();


}  // namespace SynHighlighterURI

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighteruri;
#endif


#endif // SynHighlighterURIH

