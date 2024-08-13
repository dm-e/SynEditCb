/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is SynUnicode.pas by Maël Hörz, released 2004-05-30.
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

------------------------------------------------------------------------------*/
#ifndef SynUnicodeH
#define SynUnicodeH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Clipbrd.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.TypInfo.hpp>

namespace Synunicode
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is SynUnicode.pas by Maël Hörz, released 2004-05-30.
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

------------------------------------------------------------------------------*/

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
const unsigned char UTF8BOM[3/*# range 0..2*/] = {0xEF, 0xBB, 0xBF};
const unsigned char UTF16BOMLE[2/*# range 0..1*/] = {0xFF, 0xFE};
const unsigned char UTF16BOMBE[2/*# range 0..1*/] = {0xFE, 0xFF};
const unsigned char UTF32BOMLE[4/*# range 0..3*/] = {0xFF, 0xFE, 0x00, 0x00};
const unsigned char UTF32BOMBE[4/*# range 0..3*/] = {0x00, 0x00, 0xFE, 0xFF};
  // constants describing range of the Unicode Private Use Area (Unicode 3.2)
const System::WideChar PrivateUseLow = ((System::WideChar) 0xE000);
const System::WideChar PrivateUseHigh = ((System::WideChar) 0xF8FF);
  // filler char: helper for painting wide glyphs
const System::WideChar FillerChar = PrivateUseLow;
const System::WideChar WideNull = L'\x00';
const System::WideChar WideTabulator = L'\x09';
const System::WideChar WideSpace = L'\x20';

  // logical line breaks
const System::WideChar WideLF = L'\x0a';
const System::WideChar WideLineFeed = L'\x0a';
const System::WideChar WideVerticalTab = L'\x0b';
const System::WideChar WideFormFeed = L'\x0c';
const System::WideChar WideCR = L'\x0d';
const System::WideChar WideCarriageReturn = L'\x0d';
const System::UnicodeString WideCRLF = UnicodeString(L"\x0d\x0a");
const System::WideChar WideLineSeparator = ((System::WideChar) 0x2028);
const System::WideChar WideParagraphSeparator = ((System::WideChar) 0x2029);
typedef int /*0..255*/ TFontCharset;
PWideChar __fastcall SynCharNext(PWideChar P);
PWideChar __fastcall SynCharNext(PWideChar P, String& Element);
int __fastcall SynUniElementsCount(String s);

/* functions taken from JCLUnicode.pas */
void __fastcall StrSwapByteOrder(PWideChar Str);
TFontCharset __fastcall CharSetFromLocale(LCID Language);
int __fastcall CodePageFromLocale(LCID Language);
WORD __fastcall KeyboardCodePage();

/* functions providing same behavior on Win9x and WinNT based systems*/
TSize __fastcall GetTextSize(HDC DC, PWideChar Str, int Count);

/* Unicode streaming-support */
enum TSynEncoding {seUTF8,
                   seUTF16LE,
                   seUTF16BE,
                   seAnsi };
typedef System::Set<TSynEncoding, TSynEncoding::seUTF8, TSynEncoding::seAnsi> TSynEncodings;
bool __fastcall IsAnsiOnly(const String WS);
bool __fastcall IsUTF8(TStream* Stream, bool& WithBOM, int BytesToCheck = 0x4000);
bool __fastcall IsUTF8(const String FileName, bool& WithBOM, int BytesToCheck = 0x4000);
bool __fastcall IsUTF8(const TBytes& Bytes, int Start = 0, int BytesToCheck = 0x4000);
TEncoding* __fastcall GetEncoding(const String FileName, bool& WithBOM);
TEncoding* __fastcall GetEncoding(TStream* Stream, bool& WithBOM);
bool __fastcall ClipboardProvidesText();
String __fastcall GetClipboardText();
void __fastcall SetClipboardText(const String Text);

/* misc functions */
bool __fastcall IsWideCharMappableToAnsi(WideChar WC);

void SynUnicode_initialization();


}  // namespace SynUnicode

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synunicode;
#endif


#endif // SynUnicodeH

