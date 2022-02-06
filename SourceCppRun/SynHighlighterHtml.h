#ifndef SynHighlighterHtmlH
#define SynHighlighterHtmlH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterhtml
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterHTML.pas, released 2000-04-10.
The Original Code is based on the hkHTMLSyn.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Hideo Koiso.
Unicode translation by Maël Hörz.
HTML5 tags added by CodehunterWorks
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

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides an HTML highlighter for SynEdit)
@author(Hideo Koiso, converted to SynEdit by Michael Hieke)
@created(1999-11-02, converted to SynEdit 2000-04-10)
@lastmod(2012-09-13)
The SynHighlighterHTML unit provides SynEdit with an HTML highlighter.
*/
const int MAX_ESCAPEAMPS = 249;
const PWideChar EscapeAmps[249/*# range 0..MAX_ESCAPEAMPS-1*/] = {(L"&Alpha;")         /* ?        */  /* greek capital alpha */
																				, (L"&Beta;")          /* ?        */  /* greek capital beta */
																				, (L"&Gamma;")         /* G        */  /* greek capital gamma */
																				, (L"&Delta;")         /* ?        */  /* greek capital delta */
																				, (L"&Epsilon;")       /* ?        */  /* greek capital epsilon */
																				, (L"&Zeta;")          /* ?        */  /* greek capital zeta */
																				, (L"&Eta;")           /* ?        */  /* greek capital eta */
																				, (L"&Theta;")         /* T        */  /* greek capital theta */
																				, (L"&Iota;")          /* ?        */  /* greek capital iota */
																				, (L"&Kappa;")         /* ?        */  /* greek capital kappa */
																				, (L"&Lambda;")        /* ?        */  /* greek capital lambda */
																				, (L"&Mu;")            /* ?        */  /* greek capital mu */
																				, (L"&Nu;")            /* ?        */  /* greek capital nu */
																				, (L"&Xi;")            /* ?        */  /* greek capital xi */
																				, (L"&Omicron;")       /* ?        */  /* greek capital omicron */
																				, (L"&Pi;")            /* ?        */  /* greek capital pi */
																				, (L"&Rho;")           /* ?        */  /* greek capital rho */
																				, (L"&Sigma;")         /* S        */  /* greek capital sigma */
																				, (L"&Tau;")           /* ?        */  /* greek capital tau */
																				, (L"&Upsilon;")       /* ?        */  /* greek capital upsilon */
																				, (L"&Phi;")           /* F        */  /* greek capital phi */
																				, (L"&Chi;")           /* ?        */  /* greek capital chi */
																				, (L"&Psi;")           /* ?        */  /* greek capital psi */
																				, (L"&Omega;")         /* O        */  /* greek capital omega */
																				, (L"&alpha;")         /* a        */  /* greek small alpha */
																				, (L"&beta;")          /* ß        */  /* greek small beta */
																				, (L"&gamma;")         /* ?        */  /* greek small gamma */
																				, (L"&delta;")         /* d        */  /* greek small delta */
																				, (L"&epsilon;")       /* e        */  /* greek small epsilon */
																				, (L"&zeta;")          /* ?        */  /* greek small zeta */
																				, (L"&eta;")           /* ?        */  /* greek small eta */
																				, (L"&theta;")         /* ?        */  /* greek small theta */
																				, (L"&iota;")          /* ?        */  /* greek small iota */
																				, (L"&kappa;")         /* ?        */  /* greek small kappa */
																				, (L"&lambda;")        /* ?        */  /* greek small lambda */
																				, (L"&mu;")            /* µ        */  /* greek small mu */
																				, (L"&nu;")            /* ?        */  /* greek small nu */
																				, (L"&xi;")            /* ?        */  /* greek small xi */
																				, (L"&omicron;")       /* ?        */  /* greek small omicron */
																				, (L"&pi;")            /* p        */  /* greek small pi */
																				, (L"&rho;")           /* ?        */  /* greek small rho */
																				, (L"&sigmaf;")        /* ?        */  /* greek small final sigma */
																				, (L"&sigma;")         /* s        */  /* greek small sigma */
																				, (L"&tau;")           /* t        */  /* greek small tau */
																				, (L"&upsilon;")       /* ?        */  /* greek small upsilon */
																				, (L"&phi;")           /* f        */  /* greek small phi */
																				, (L"&chi;")           /* ?        */  /* greek small chi */
																				, (L"&psi;")           /* ?        */  /* greek small psi */
																				, (L"&omega;")         /* ?        */  /* greek small omega */
																				, (L"&thetasym;")      /* ?        */  /* greek small theta symbol */
																				, (L"&upsih;")         /* ?        */  /* greek upsilon with hook symbol */
																				, (L"&piv;")           /* ?        */  /* greek pi symbol */
																				, (L"&bull;")          /* •        */  /* bullet */
																				, (L"&hellip;")        /* …        */  /* horizontal ellipsis */
																				, (L"&prime;")         /* '        */  /* prime */
																				, (L"&Prime;")         /* "        */  /* double prime */
																				, (L"&oline;")         /* ?        */  /* overline, = spacing overscore */
																				, (L"&frasl;")         /* /        */  /* fraction slash */
																				, (L"&weierp;")        /* P        */  /* script capital P */
																				, (L"&image;")         /* I        */  /* imaginary part */
																				, (L"&real;")          /* R        */  /* real part */
																				, (L"&trade;")         /* ™        */  /* trademark sign */
																				, (L"&alefsym;")       /* ?        */  /* first transfinite cardinal */
																				, (L"&larr;")          /* ?        */  /* leftwards arrow */
																				, (L"&uarr;")          /* ?        */  /* upwards arrow */
																				, (L"&rarr;")          /* ?        */  /* rightwards arrow */
																				, (L"&darr;")          /* ?        */  /* downwards arrow */
																				, (L"&harr;")          /* ?        */  /* left right arrow */
																				, (L"&crarr;")         /* ?        */  /* carriage return arrow */
																				, (L"&lArr;")          /* ?        */  /* leftwards double arrow */
																				, (L"&uArr;")          /* ?        */  /* upwards double arrow */
																				, (L"&rArr;")          /* ?        */  /* rightwards double arrow */
																				, (L"&dArr;")          /* ?        */  /* downwards double arrow */
																				, (L"&hArr;")          /* ?        */  /* left right double arrow */
																				, (L"&forall;")        /* ?        */  /* for all */
																				, (L"&part;")          /* ?        */  /* partial differential */
																				, (L"&exist;")         /* ?        */  /* there exists */
																				, (L"&empty;")         /* Ø        */  /* empty set */
																				, (L"&nabla;")         /* ?        */  /* backward difference */
																				, (L"&isin;")          /* ?        */  /* element of */
																				, (L"&notin;")         /* ?        */  /* not an element of */
																				, (L"&ni;")            /* ?        */  /* contains as member */
																				, (L"&prod;")          /* ?        */  /* n-ary product */
																				, (L"&sum;")           /* ?        */  /* n-ary sumation */
																				, (L"&minus;")         /* -        */  /* minus sign */
																				, (L"&lowast;")        /* *        */  /* asterisk operator */
																				, (L"&radic;")         /* v        */  /* square root */
																				, (L"&prop;")          /* ?        */  /* proportional to */
																				, (L"&infin;")         /* 8        */  /* infinity */
																				, (L"&ang;")           /* ?        */  /* angle */
																				, (L"&and;")           /* ?        */  /* logical and */
																				, (L"&or;")            /* ?        */  /* logical or */
																				, (L"&cap;")           /* n        */  /* intersection */
																				, (L"&cup;")           /* ?        */  /* union */
																				, (L"&int;")           /* ?        */  /* integral */
																				, (L"&there4;")        /* ?        */  /* therefore */
																				, (L"&sim;")           /* ~        */  /* similar to = tilde operator */
																				, (L"&cong;")          /* ?        */  /* approximately equal to */
																				, (L"&asymp;")         /* ˜        */  /* almost euqal to */
																				, (L"&ne;")            /* ?        */  /* not equal to */
																				, (L"&equiv;")         /* =        */  /* identical to */
																				, (L"&le;")            /* =        */  /* less-than or equal to */
																				, (L"&ge;")            /* =        */  /* greater-than or equal to */
																				, (L"&sub;")           /* ?        */  /* subset of */
																				, (L"&sup;")           /* ?        */  /* superset of */
																				, (L"&nsub;")          /* ?        */  /* not a subset of */
																				, (L"&sube;")          /* ?        */  /* subset of or equal to */
																				, (L"&supe;")          /* ?        */  /* superset of or equal to */
																				, (L"&oplus;")         /* ?        */  /* circled plus */
																				, (L"&otimes;")        /* ?        */  /* circled times */
																				, (L"&perp;")          /* ?        */  /* orthogonal to = perpendicular */
																				, (L"&sdot;")          /* ·        */  /* dot operator */
																				, (L"&lceil;")         /* ?        */  /* left ceiling */
																				, (L"&rceil;")         /* ?        */  /* right ceiling */
																				, (L"&lfloor;")        /* ?        */  /* left floor */
																				, (L"&rfloor;")        /* ?        */  /* right floor */
																				, (L"&lang;")          /* <        */  /* left-pointing angle bracket */
																				, (L"&rang;")          /* >        */  /* right-pointing angle bracket */
																				, (L"&loz;")           /* ?        */  /* lozenge */
																				, (L"&spades;")        /* ?        */  /* black spade suit */
																				, (L"&clubs;")         /* ?        */  /* black club suit */
																				, (L"&hearts;")        /* ?        */  /* black heart suit */
																				, (L"&diams;")         /* ?        */  /* black diamond suit */
																				, (L"&lsquo;")         /* ‘        */  /* left single quote  */
																				, (L"&rsquo;")         /* ’        */  /* right single quote */
																				, (L"&sbquo;")         /* ‚        */  /* single low-9 quote */
																				, (L"&ldquo;")         /* “        */  /* left double quote */
																				, (L"&rdquo;")         /* ”        */  /* right double quote */
																				, (L"&bdquo;")         /* „        */  /* double low-9 quote */
																				, (L"&dagger;")        /* †        */  /* dagger */
																				, (L"&Dagger;")        /* ‡        */  /* double dagger */
																				, (L"&permil;")        /* ‰        */  /* per mill sign */
																				, (L"&lsaquo;")        /* ‹        */  /* single left-pointing angle quote */
																				, (L"&rsaquo;")        /* ›        */  /* single right-pointing angle quote */
																				, (L"&quot;")          /* &#034; " */  /* double quotation mark */
																				, (L"&amp;")           /* &#038; & */  /* ampersand */
																				, (L"&lt;")            /* &#060; < */  /* less-than sign */
																				, (L"&gt;")            /* >        */  /* greater-than sign */
																				, (L"&ndash;")         /* &#150; – */  /* en dash */
																				, (L"&mdash;")         /* &#151; — */  /* em dash */
																				, (L"&nbsp;")          /* &#160;   */  /* nonbreaking space */
																				, (L"&thinsp;")        /*          */  /* thin space */
																				, (L"&ensp;")          /*          */  /* en space */
																				, (L"&emsp;")          /*          */  /* em space */
																				, (L"&iexcl;")         /* &#161; ! */  /* inverted exclamation */
																				, (L"&cent;")          /* &#162; c */  /* cent sign */
																				, (L"&pound;")         /* &#163; L */  /* pound sterling */
																				, (L"&curren;")        /* &#164; ¤ */  /* general currency sign */
																				, (L"&yen;")           /* &#165; Y */  /* yen sign */
																				, (L"&brvbar;")        /* &#166; ¦ */  /* broken vertical bar */
																				, (L"&brkbar;")        /* &#166; ¦ */  /* broken vertical bar */
																				, (L"&sect;")          /* &#167; § */  /* section sign */
																				, (L"&uml;")           /* &#168; ¨ */  /* umlaut */
																				, (L"&die;")           /* &#168; ¨ */  /* umlaut */
																				, (L"&copy;")          /* &#169; © */  /* copyright */
																				, (L"&ordf;")          /* &#170; a */  /* feminine ordinal */
																				, (L"&laquo;")         /* &#171; « */  /* left angle quote */
																				, (L"&not;")           /* &#172; ¬ */  /* not sign */
																				, (L"&shy;")           /* &#173; ­ */  /* soft hyphen */
																				, (L"&reg;")           /* &#174; ® */  /* registered trademark */
																				, (L"&macr;")          /* &#175; — */  /* macron accent */
																				, (L"&hibar;")         /* &#175; — */  /* macron accent */
																				, (L"&deg;")           /* &#176; ° */  /* degree sign */
																				, (L"&plusmn;")        /* &#177; ± */  /* plus or minus */
																				, (L"&sup2;")          /* &#178; 2 */  /* superscript two */
																				, (L"&sup3;")          /* &#179; 3 */  /* superscript three */
																				, (L"&acute;")         /* &#180; ´ */  /* acute accent */
																				, (L"&micro;")         /* &#181; µ */  /* micro sign */
																				, (L"&para;")          /* &#182; ¶ */  /* paragraph sign */
																				, (L"&middot;")        /* &#183; · */  /* middle dot */
																				, (L"&cedil;")         /* &#184; ¸ */  /* cedilla */
																				, (L"&sup1;")          /* &#185; 1 */  /* superscript one */
																				, (L"&ordm;")          /* &#186; o */  /* masculine ordinal */
																				, (L"&raquo;")         /* &#187; » */  /* right angle quote */
																				, (L"&frac14;")        /* &#188; 1 */  /* one-fourth */
																				, (L"&frac12;")        /* &#189; 1 */  /* one-half */
																				, (L"&frac34;")        /* &#190; 3 */  /* three-fourths */
																				, (L"&iquest;")        /* &#191; ? */  /* inverted question mark */
																				, (L"&Agrave;")        /* &#192; A */  /* uppercase A, grave accent */
																				, (L"&Aacute;")        /* &#193; Á */  /* uppercase A, acute accent */
																				, (L"&Acirc;")         /* &#194; Â */  /* uppercase A, circumflex accent */
																				, (L"&Atilde;")        /* &#195; A */  /* uppercase A, tilde */
																				, (L"&Auml;")          /* &#196; Ä */  /* uppercase A, umlaut */
																				, (L"&Aring;")         /* &#197; A */  /* uppercase A, ring */
																				, (L"&AElig;")         /* &#198; A */  /* uppercase AE */
																				, (L"&Ccedil;")        /* &#199; Ç */  /* uppercase C, cedilla */
																				, (L"&Egrave;")        /* &#200; E */  /* uppercase E, grave accent */
																				, (L"&Eacute;")        /* &#201; É */  /* uppercase E, acute accent */
																				, (L"&Ecirc;")         /* &#202; E */  /* uppercase E, circumflex accent */
																				, (L"&Euml;")          /* &#203; Ë */  /* uppercase E, umlaut */
																				, (L"&Igrave;")        /* &#204; I */  /* uppercase I, grave accent */
																				, (L"&Iacute;")        /* &#205; Í */  /* uppercase I, acute accent */
																				, (L"&Icirc;")         /* &#206; Î */  /* uppercase I, circumflex accent */
																				, (L"&Iuml;")          /* &#207; I */  /* uppercase I, umlaut */
																				, (L"&ETH;")           /* &#208; ? */  /* uppercase Eth, Icelandic */
																				, (L"&Ntilde;")        /* &#209; N */  /* uppercase N, tilde */
																				, (L"&Ograve;")        /* &#210; O */  /* uppercase O, grave accent */
																				, (L"&Oacute;")        /* &#211; Ó */  /* uppercase O, acute accent */
																				, (L"&Ocirc;")         /* &#212; Ô */  /* uppercase O, circumflex accent */
																				, (L"&Otilde;")        /* &#213; O */  /* uppercase O, tilde */
																				, (L"&Ouml;")          /* &#214; Ö */  /* uppercase O, umlaut */
																				, (L"&times;")         /* &#215; × */  /* multiplication sign */
																				, (L"&Oslash;")        /* &#216; O */  /* uppercase O, slash */
																				, (L"&Ugrave;")        /* &#217; U */  /* uppercase U, grave accent */
																				, (L"&Uacute;")        /* &#218; Ú */  /* uppercase U, acute accent */
																				, (L"&Ucirc;")         /* &#219; U */  /* uppercase U, circumflex accent */
																				, (L"&Uuml;")          /* &#220; Ü */  /* uppercase U, umlaut */
																				, (L"&Yacute;")        /* &#221; Ý */  /* uppercase Y, acute accent */
																				, (L"&THORN;")         /* &#222; ? */  /* uppercase THORN, Icelandic */
																				, (L"&szlig;")         /* &#223; ß */  /* lowercase sharps, German */
																				, (L"&agrave;")        /* &#224; à */  /* lowercase a, grave accent */
																				, (L"&aacute;")        /* &#225; á */  /* lowercase a, acute accent */
																				, (L"&acirc;")         /* &#226; â */  /* lowercase a, circumflex accent */
																				, (L"&atilde;")        /* &#227; ã */  /* lowercase a, tilde */
																				, (L"&auml;")          /* &#228; ä */  /* lowercase a, umlaut */
																				, (L"&aring;")         /* &#229; å */  /* lowercase a, ring */
																				, (L"&aelig;")         /* &#230; a */  /* lowercase ae */
																				, (L"&ccedil;")        /* &#231; ç */  /* lowercase c, cedilla */
																				, (L"&egrave;")        /* &#232; e */  /* lowercase e, grave accent */
																				, (L"&eacute;")        /* &#233; é */  /* lowercase e, acute accent */
																				, (L"&ecirc;")         /* &#234; ê */  /* lowercase e, circumflex accent */
																				, (L"&euml;")          /* &#235; ë */  /* lowercase e, umlaut */
																				, (L"&igrave;")        /* &#236; i */  /* lowercase i, grave accent */
																				, (L"&iacute;")        /* &#237; í */  /* lowercase i, acute accent */
																				, (L"&icirc;")         /* &#238; î */  /* lowercase i, circumflex accent */
																				, (L"&iuml;")          /* &#239; i */  /* lowercase i, umlaut */
																				, (L"&eth;")           /* &#240; ? */  /* lowercase eth, Icelandic */
																				, (L"&ntilde;")        /* &#241; ñ */  /* lowercase n, tilde */
																				, (L"&ograve;")        /* &#242; o */  /* lowercase o, grave accent */
																				, (L"&oacute;")        /* &#243; ó */  /* lowercase o, acute accent */
																				, (L"&ocirc;")         /* &#244; ô */  /* lowercase o, circumflex accent */
																				, (L"&otilde;")        /* &#245; o */  /* lowercase o, tilde */
																				, (L"&ouml;")          /* &#246; ö */  /* lowercase o, umlaut */
																				, (L"&divide;")        /* &#247; ÷ */  /* division sign */
																				, (L"&oslash;")        /* &#248; o */  /* lowercase o, slash */
																				, (L"&ugrave;")        /* &#249; u */  /* lowercase u, grave accent */
																				, (L"&uacute;")        /* &#250; ú */  /* lowercase u, acute accent */
																				, (L"&ucirc;")         /* &#251; u */  /* lowercase u, circumflex accent */
																				, (L"&uuml;")          /* &#252; ü */  /* lowercase u, umlaut */
																				, (L"&yacute;")        /* &#253; ý */  /* lowercase y, acute accent */
																				, (L"&thorn;")         /* &#254; ? */  /* lowercase thorn, Icelandic */
																				, (L"&yuml;")          /* &#255; y */  /* lowercase y, umlaut */
																				, (L"&euro;")          /* €        */  /* euro sign */
																				, (L"&OElig;")         /* Œ        */  /* capital ligature OE */
																				, (L"&oelig;")         /* œ        */  /* small ligature oe */
																				, (L"&scaron;")        /* š        */  /* small S with caron */
																				, (L"&Scaron;")        /* Š        */  /* capital S with caron */
																				, (L"&fnof;")          /* ƒ        */  /* function */
																				, (L"&circ;")           /* ˆ        */  /* circumflex accent */};
enum TtkTokenKind {tkAmpersand,
                   tkComment,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkSpace,
                   tkSymbol,
                   tkText,
                   tkUndefKey,
                   tkValue };
enum TRangeState {rsAmpersand,
                  rsComment,
                  rsKey,
                  rsParam,
                  rsText,
                  rsUnKnown,
                  rsValue,
                  rsQuoteValue,
                  rsDoubleQuoteValue };
typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynHTMLSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	int fAndCode;
	TRangeState FRange;
//    fIdentFuncTable: array[0..1542] of TIdentFuncTableFunc;
	TIdentFuncTableFunc fIdentFuncTable[2179/*# range 0..2178*/];
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fAndAttri;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fTextAttri;
	Synedithighlighter::TSynHighlighterAttributes* fUndefKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fValueAttri;
	TtkTokenKind __fastcall AltFunc(int Index);
	TtkTokenKind __fastcall KeyWordFunc(int Index);
	unsigned int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall InitIdent();
	void __fastcall TextProc();
	void __fastcall CommentProc();
	void __fastcall BraceCloseProc();
	void __fastcall BraceOpenProc();
	void __fastcall CRProc();
	void __fastcall EqualProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall NullProc();
	void __fastcall SpaceProc();
	void __fastcall StringProc();
	void __fastcall AmpersandProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
	void __fastcall NextProcedure();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;	
	#include "SynHighlighterHtml_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynHTMLSyn(System::Classes::TComponent* AOwner);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual void __fastcall Next();
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
__published:
	__property TSynHighlighterAttributes* AndAttri = { read = fAndAttri, write = fAndAttri };
	__property TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property TSynHighlighterAttributes* TextAttri = { read = fTextAttri, write = fTextAttri };
	__property TSynHighlighterAttributes* UndefKeyAttri = { read = fUndefKeyAttri, write = fUndefKeyAttri };
	__property TSynHighlighterAttributes* ValueAttri = { read = fValueAttri, write = fValueAttri };
};

void SynHighlighterHtml_initialization();


}  // namespace SynHighlighterHtml

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterhtml;
#endif


#endif // SynHighlighterHtmlH

