
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterHtml.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterhtml
{
#define Synhighlighterhtml__0 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterhtml__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterhtml__2 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterhtml__3 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterhtml__4 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterhtml__5 (TSysCharSet() <<  \
          0 << 1 << 2 << 3 << 4 << 5 <<  \
          6 << 7 << 8 << 9 << 10 << 11 <<  \
          12 << 13 << 14 << 15 << 16 << 17 <<  \
          18 << 19 << 20 << 21 << 22 << 23 <<  \
          24 << 25 << 26 << 27 << 28 << 29 <<  \
          30 << 31 << '<')
#define Synhighlighterhtml__6 (TSysCharSet() << 'X' << 'x')
#define Synhighlighterhtml__7 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterhtml__8 (TSysCharSet() << 'X' << 'x')
#define Synhighlighterhtml__9 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterhtml__10 (TSysCharSet() << '\x00' << '\x09' << '\x0a' << '\x0d')
#define Synhighlighterhtml__11 (System::Set<TRangeState, TRangeState::rsAmpersand, TRangeState::rsDoubleQuoteValue>() << rsDoubleQuoteValue << rsQuoteValue)


//  KeyWords: array[0..201] of string = (
//    '!doctype', '/a', '/abbr', '/acronym', '/address', '/applet', '/b', '/bdo',
//    '/big', '/blink', '/blockquote', '/body', '/button', '/caption', '/center',
//    '/cite', '/code', '/colgroup', '/comment', '/dd', '/del', '/dfn', '/dir',
//    '/div', '/dl', '/dt', '/em', '/embed', '/fieldset', '/font', '/form',
//    '/frameset', '/h1', '/h2', '/h3', '/h4', '/h5', '/h6', '/head', '/html',
//    '/i', '/iframe', '/ilayer', '/ins', '/kbd', '/label', '/layer', '/legend',
//    '/li', '/listing', '/map', '/marquee', '/menu', '/multicol', '/nobr',
//    '/noembed', '/noframes', '/nolayer', '/noscript', '/object', '/ol',
//    '/optgroup', '/option', '/p', '/pre', '/q', '/s', '/samp', '/script',
//    '/select', '/server', '/small', '/span', '/strike', '/strong', '/style',
//    '/sub', '/sup', '/table', '/tbody', '/td', '/textarea', '/tfoot', '/th',
//    '/thead', '/title', '/tr', '/tt', '/u', '/ul', '/var', '/xmp', 'a', 'abbr',
//    'acronym', 'address', 'applet', 'area', 'b', 'base', 'basefont', 'bdo',
//    'bgsound', 'big', 'blink', 'blockquote', 'body', 'br', 'button', 'caption',
//    'center', 'cite', 'code', 'col', 'colgroup', 'comment', 'dd', 'del', 'dfn',
//    'dir', 'div', 'dl', 'dt', 'em', 'embed', 'fieldset', 'font', 'form',
//    'frame', 'frameset', 'h1', 'h2', 'h3', 'h4', 'h5', 'h6', 'head', 'hr',
//    'html', 'i', 'iframe', 'ilayer', 'img', 'input', 'ins', 'isindex', 'kbd',
//    'keygen', 'label', 'layer', 'legend', 'li', 'link', 'listing', 'map',
//    'marquee', 'menu', 'meta', 'multicol', 'nextid', 'nobr', 'noembed',
//    'noframes', 'nolayer', 'noscript', 'object', 'ol', 'optgroup', 'option',
//    'p', 'param', 'plaintext', 'pre', 'q', 's', 'samp', 'script', 'select',
//    'server', 'small', 'spacer', 'span', 'strike', 'strong', 'style', 'sub',
//    'sup', 'table', 'tbody', 'td', 'textarea', 'tfoot', 'th', 'thead', 'title',
//    'tr', 'tt', 'u', 'ul', 'var', 'wbr', 'xmp'
//  );
//
//  KeyIndices: array[0..1542] of Integer = (
//    -1, -1, 182, -1, -1, -1, 97, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, 33, -1, -1, -1, -1, 40, -1, -1, -1, -1, -1, 137, 189, -1, -1,
//    -1, -1, -1, -1, -1, -1, 191, -1, -1, -1, -1, -1, -1, -1, 52, 170, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, 5, 55, -1, 83, -1, -1, 34, -1, 198, -1, -1, -1,
//    -1, -1, -1, -1, 82, -1, -1, -1, -1, -1, 74, 111, -1, 62, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 93, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, 35, 72, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 130,
//    190, -1, 117, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 36, -1, -1, 157, -1, -1, -1,
//    -1, -1, 13, 114, -1, -1, -1, -1, 131, -1, -1, -1, -1, -1, -1, 21, -1, -1,
//    -1, 161, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 139, -1,
//    -1, -1, -1, 37, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 192, -1, -1,
//    132, 103, -1, -1, -1, 199, -1, -1, -1, -1, -1, -1, -1, 129, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, 133, -1, -1, -1, -1, -1, -1, -1, -1, 54,
//    -1, -1, -1, -1, -1, 42, -1, -1, -1, -1, -1, -1, -1, -1, -1, 109, -1, -1, -1,
//    148, -1, -1, -1, -1, -1, -1, -1, 96, -1, -1, -1, -1, -1, -1, -1, -1, 134,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 183, -1, -1, 168, -1, 45,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 179, -1, -1, 63, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, 135, -1, -1, -1, -1, -1, -1, 60, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 71, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, 65, -1, -1, -1, -1, -1, -1, -1, 125, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, 4, -1, -1, 39, -1, -1, -1, -1, 128, 20, -1, -1, 51, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 176, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, 112, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    180, -1, -1, -1, -1, -1, 172, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 107,
//    -1, -1, -1, -1, 66, -1, -1, -1, 59, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, 162, -1, 8, -1, -1, -1, -1, -1, -1, 166, -1,
//    -1, -1, 169, 141, 86, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 95, -1, -1,
//    -1, -1, -1, -1, -1, 56, -1, -1, -1, -1, -1, 124, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, 19, -1, -1, 41, -1, 173, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, 88, -1, -1, -1, -1, -1, 27, -1, -1, -1, -1, -1, -1, -1, -1, -1, 186,
//    -1, -1, -1, -1, -1, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, -1, 200, -1,
//    -1, -1, 87, 181, -1, -1, -1, -1, 119, -1, -1, -1, 57, -1, -1, -1, 104, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 47, -1, 26, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, 174, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, 201, -1, -1, -1, 195, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    58, 50, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 49, -1, -1, -1, 101,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, 116, -1, -1, -1, -1, 113, 187, -1, -1,
//    -1, 94, -1, -1, -1, -1, -1, 165, -1, -1, -1, -1, -1, -1, -1, 69, -1, -1, -1,
//    -1, -1, 167, -1, -1, 163, -1, -1, 197, -1, -1, -1, -1, 78, -1, 68, -1, -1,
//    -1, -1, -1, -1, 145, -1, -1, 196, -1, -1, -1, -1, 12, -1, -1, -1, 160, -1,
//    61, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 123,
//    -1, -1, -1, -1, -1, -1, 76, 120, -1, 140, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, 10, -1, -1, -1, -1, -1, 153, -1, -1, -1, -1, -1, -1, -1, 30, -1, -1,
//    -1, -1, -1, -1, 142, -1, -1, -1, -1, -1, 99, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 152, -1, 171,
//    -1, -1, -1, -1, -1, 11, -1, -1, -1, -1, -1, 150, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    22, -1, -1, -1, -1, -1, 138, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    24, -1, 70, -1, -1, -1, -1, -1, -1, 29, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 38, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 53, -1, -1, 177, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, 7, -1, -1, -1, -1, -1, -1, -1, -1, 100, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, 108, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 144, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 90, -1, -1,
//    -1, 121, 159, 102, -1, -1, -1, -1, -1, -1, -1, -1, -1, 23, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 155, 149, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, 81, 2, -1, 110, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, 146, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    178, -1, -1, -1, -1, -1, 17, -1, -1, -1, -1, -1, 143, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, 164, -1, -1, -1, 48, -1, -1, -1, -1, -1, -1, 9,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 31, -1, 6, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, 188, -1, -1, -1, -1, -1, -1, -1, 25, -1, -1, 73, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 64,
//    79, -1, -1, -1, -1, -1, -1, -1, -1, -1, 127, -1, -1, -1, 18, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, 43, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, 184, -1, -1, -1, 175, -1, -1, 193, -1, 92, 151, 154, -1, -1, -1, -1,
//    106, -1, -1, -1, -1, -1, -1, -1, -1, -1, 194, -1, -1, -1, -1, -1, -1, -1,
//    -1, 75, -1, -1, -1, -1, -1, -1, 84, -1, -1, -1, -1, -1, 28, -1, -1, -1, -1,
//    -1, -1, 98, -1, 80, -1, -1, -1, 85, -1, -1, -1, -1, 67, -1, 118, -1, -1, -1,
//    -1, -1, -1, -1, -1, 126, -1, -1, -1, -1, -1, 77, -1, -1, 122, 44, -1, -1,
//    -1, -1, -1, 89, -1, -1, -1, 115, 136, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    -1, -1, -1, -1, -1, -1, -1, 105, -1, -1, -1, -1, -1, -1, -1, -1, 147, -1,
//    16, 185, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//    158, -1, -1, -1, -1, -1, -1, -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, 91,
//    -1, -1, 156, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
//  );
const String Keywords[257/*# range 0..256*/] = {L"!doctype", L"/!doctype", L"/a", L"/abbr", L"/acronym", L"/address", L"/applet", L"/area", L"/article", L"/aside"
                    , L"/audio", L"/b", L"/base", L"/basefont", L"/bb", L"/bdo", L"/big", L"/blockquote", L"/body", L"/button", L"/canvas", L"/caption"
                    , L"/center", L"/cite", L"/code", L"/col", L"/colgroup", L"/command", L"/datalist", L"/dd", L"/del", L"/details", L"/dfn"
                    , L"/dialog", L"/dir", L"/div", L"/dl", L"/dt", L"/em", L"/embed", L"/fieldset", L"/figcaption", L"/figure", L"/font", L"/footer"
                    , L"/form", L"/frame", L"/frameset", L"/h1", L"/h2", L"/h3", L"/h4", L"/h5", L"/h6", L"/head", L"/header", L"/hgroup", L"/html"
                    , L"/i", L"/iframe", L"/img", L"/input", L"/ins", L"/kbd", L"/keygen", L"/label", L"/layer", L"/legend", L"/li", L"/link", L"/map"
                    , L"/mark", L"/marquee", L"/menu", L"/meta", L"/meter", L"/multicol", L"/nav", L"/nobr", L"/noembed", L"/noframes", L"/nolayer"
                    , L"/noscript", L"/object", L"/ol", L"/optgroup", L"/option", L"/output", L"/p", L"/param", L"/pre", L"/progress", L"/q"
                    , L"/rp", L"/rt", L"/ruby", L"/s", L"/samp", L"/script", L"/section", L"/select", L"/server", L"/small", L"/source", L"/span", L"/strike"
                    , L"/strong", L"/style", L"/sub", L"/summary", L"/sup", L"/table", L"/tbody", L"/td", L"/textarea", L"/tfoot", L"/th", L"/thead"
                    , L"/time", L"/title", L"/tr", L"/track", L"/tt", L"/u", L"/ul", L"/var", L"/video", L"/wbr", L"/xmp", L"a", L"abbr", L"acronym", L"address"
                    , L"applet", L"area", L"article", L"aside", L"audio", L"b", L"base", L"basefont", L"bb", L"bdo", L"big", L"blockquote", L"body"
                    , L"button", L"canvas", L"caption", L"center", L"cite", L"code", L"col", L"colgroup", L"command", L"datalist", L"dd", L"del"
                    , L"details", L"dfn", L"dialog", L"dir", L"div", L"dl", L"dt", L"em", L"embed", L"fieldset", L"figcaption", L"figure", L"font", L"footer"
                    , L"form", L"frame", L"frameset", L"h1", L"h2", L"h3", L"h4", L"h5", L"h6", L"head", L"header", L"hgroup", L"html", L"i", L"iframe"
                    , L"img", L"input", L"ins", L"kbd", L"keygen", L"label", L"layer", L"legend", L"li", L"link", L"map", L"mark", L"marquee", L"menu"
                    , L"meta", L"meter", L"multicol", L"nav", L"nobr", L"noembed", L"noframes", L"nolayer", L"noscript", L"object", L"ol", L"optgroup"
                    , L"option", L"output", L"p", L"param", L"pre", L"progress", L"q", L"rp", L"rt", L"ruby", L"s", L"samp", L"script", L"section", L"select"
                    , L"server", L"small", L"source", L"span", L"strike", L"strong", L"style", L"sub", L"summary", L"sup", L"synedit", L"table", L"tbody"
                    , L"td", L"textarea", L"tfoot", L"th", L"thead", L"time", L"title", L"tr", L"track", L"tt", L"u", L"ul", L"var", L"video", L"wbr"
                    , L"xmp"};
const int KeyIndices[2179/*# range 0..2178*/] = {-1, -1, -1, 3, -1, -1, 231, 250, -1, -1, -1, 212, -1, -1, -1, -1, -1, -1, -1, -1, 175, -1, -1, -1, -1, -1, 128, -1, -1, -1, -1, 155, -1, -1, -1, -1, -1, -1, -1
                    , 83, -1, 201, 122, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 70, -1, -1, -1, -1, -1, -1, 183
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 216, -1, -1, -1, -1, -1, -1, 31, -1, -1, -1, -1, 89, -1, -1, -1, 234, -1, -1
                    , 188, -1, -1, -1, -1, -1, -1, -1, -1, 107, -1, -1, 61, -1, -1, -1, -1, -1, 21, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 225, -1, -1, 150, -1, -1, 91, -1, -1, -1, 88, -1, -1, -1
                    , 158, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 59, -1, -1, -1, 137, 12, -1, 67, -1, -1, 47, -1, -1, -1, -1, -1, 10, -1, -1, 135, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, 218, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 170, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 174, -1, 7, -1, -1, -1, 142, -1
                    , -1, -1, -1, -1, -1, -1, -1, 133, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 232, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 77, -1, -1, -1, 178, -1, -1, -1, -1, -1, -1
                    , 209, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 130, -1, 162, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 51, -1, -1, -1, 237, -1, -1, -1, 17, -1, -1, -1, -1, -1, 32, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, 79, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 157, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 210, -1, -1, -1, 104, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 206, -1, -1, -1, -1, -1, -1, -1, -1, 165, -1, -1, -1, -1, -1, -1, -1, 254, -1, -1, -1, -1, -1, -1, 73, -1, -1, -1, -1, 126, -1, -1, -1
                    , -1, -1, -1, -1, 24, -1, -1, 238, -1, 96, -1, 38, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 248, -1, -1, -1
                    , 156, -1, 103, -1, -1, -1, -1, -1, -1, -1, -1, 239, 211, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 111, -1, -1, -1, -1, -1, -1, -1, 120, -1, -1, -1, 29, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 71, 84
                    , -1, -1, -1, -1, -1, 87, -1, -1, -1, -1, 186, -1, -1, -1, -1, -1, -1, -1, -1, 243, -1, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, 115, -1, -1, -1, -1, -1, -1, 26, 138, -1, -1, -1, -1, -1, -1, -1, 163, -1
                    , -1, 144, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 181, 22, -1, -1, -1, -1, 255, -1, -1, -1, -1, -1, -1, 36, -1, -1, 240, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 112
                    , -1, -1, -1, -1, -1, -1, 153, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 34, -1, -1, -1, -1, -1, -1, -1, 106, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 256, -1, 164, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, 192, 145, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 65, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 37, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 114, -1
                    , 197, 63, -1, -1, -1, -1, -1, -1, 64, -1, -1, -1, -1, -1, -1, 202, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 75, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 44, -1, 200, -1, -1, 2, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, 151, -1, -1, -1, -1, -1, -1, 242, -1, -1, -1, -1, -1, -1, -1, -1, 193, 176, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 66, -1, -1, -1, -1, -1, 220, -1, -1, -1, 141, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 49, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 81, -1, -1, 93, 76, -1, -1, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 58, -1, -1, -1, -1, 230, -1
                    , 198, -1, -1, -1, -1, -1, -1, 69, -1, -1, -1, -1, 101, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 244, -1, -1, -1, -1, 208, -1, -1, -1, -1, -1, -1, -1, 100, 203, 5, -1, -1
                    , -1, -1, -1, 41, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 116, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, -1, -1, -1, -1, -1, 45, 92, -1, -1, -1, -1, 80, 204, -1, -1, -1
                    , -1, -1, 42, -1, -1, -1, -1, -1, 132, -1, 249, -1, -1, -1, -1, -1, -1, -1, 82, -1, 16, -1, 121, 86, -1, -1, -1, 224, -1, 195, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, 159, -1, -1, 54, -1, -1, -1, -1, -1, -1, -1, -1, 207, -1, -1, 68, -1, -1, -1, -1, -1, -1, 252, -1, 233, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 56, -1, -1, -1, -1, -1, -1, -1, -1, 251, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, 124, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 108, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 179, 18, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, 191, -1, -1, -1, -1, -1, 99, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 90, 171, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, 72, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 168, -1, -1, -1, 226, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 222, -1, -1, -1, -1, -1, 253, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , 246, -1, -1, -1, -1, -1, -1, -1, -1, -1, 196, -1, -1, -1, -1, -1, -1, 199, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6, -1, -1, -1
                    , -1, 0, -1, -1, 229, -1, -1, 228, -1, -1, -1, -1, -1, 215, -1, 125, 102, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 227, -1, 172, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, 194, -1, -1, -1, -1, -1, -1, -1, 184, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 161, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 169, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 213, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, 205, -1, -1, 190, -1, -1, -1, 97, -1, -1, -1, -1, -1, 33, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, 247, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 119, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 55, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 148, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 223, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, 187, -1, -1, -1, 95, -1, 136, -1, 177, -1, -1, -1, -1, -1, -1, -1, -1, -1, 9, -1, -1, -1, 118, -1, -1, -1, -1, -1, -1, 152, -1, -1, -1, -1, -1, -1, 40, -1, -1, -1, -1, -1, -1, 50
                    , -1, -1, -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 143, -1, -1, -1, -1, -1, -1, -1, 214, -1, 166, 60, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 39, -1, -1, -1, -1, 147
                    , -1, -1, -1, -1, -1, 15, -1, -1, 167, -1, -1, 173, -1, -1, -1, -1, -1, -1, -1, 131, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 57, -1, -1, -1, -1, -1, -1, -1, 149, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 235, 35, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 110, -1, -1, -1, -1, -1, -1, -1, 27, -1
                    , -1, -1, -1, -1, -1, -1, 160, -1, -1, -1, -1, -1, 74, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 78, -1, -1, -1, 30, -1, 217, -1, -1, -1, -1, -1, 189, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 154, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 182, -1, 146, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, 139, -1, -1, 98, -1, -1, -1, -1, 129, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, -1, 180, -1, -1, 245, -1, -1, -1, -1, -1, -1, 241, -1, -1, -1, -1, 117, -1, 221, -1, -1, -1
                    , -1, -1, 23, -1, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, 53, -1, 1, -1, -1, -1, -1, -1, -1, -1, 113, -1, -1, 134, -1, -1, -1, 94, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, 185, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 140, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 43, -1, -1, -1, -1, -1, 109, -1, -1, -1, -1, -1, 105, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 85, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 127, -1, -1, -1, 28, -1, -1, -1, -1, 123, -1, -1, -1, -1, -1, -1
                    , -1, 236, -1, 219, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

/*$Q-*/

unsigned int __fastcall TSynHTMLSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
//  Result := 0;
//  while IsIdentChar(Str^) or CharInSet(Str^, ['!', '/']) do
//  begin
//    Result := Result * 932 + Ord(Str^) * 46;
//    inc(Str);
//  end;
//  Result := Result mod 1543;
//  fStringLen := Str - fToIdent;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 627 + int((*Str)) * 829);
		++Str;
	}
	result = (unsigned int) (result % 2179);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynHTMLSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkAmpersand;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 2178 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynHTMLSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 2178 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	for(stop = 2178 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynHTMLSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkAmpersand;
	result = tkUndefKey;
	return result;
}

TtkTokenKind __fastcall TSynHTMLSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkAmpersand;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkUndefKey;
	return result;
}

__fastcall TSynHTMLSyn::TSynHTMLSyn(TComponent* AOwner)
 : inherited(AOwner),
			fAndCode(-1),
			FRange(rsAmpersand),
			FTokenID(tkAmpersand),
			fAndAttri(nullptr),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fSpaceAttri(nullptr),
			fSymbolAttri(nullptr),
			fTextAttri(nullptr),
			fUndefKeyAttri(nullptr),
			fValueAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	fIdentifierAttri->Style = Synhighlighterhtml__0;
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterhtml__1;
	fKeyAttri->Foreground = (TColor) 0x00FF0080;
	addAttribute(fKeyAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	fSymbolAttri->Style = Synhighlighterhtml__2;
	addAttribute(fSymbolAttri);
	fTextAttri = new TSynHighlighterAttributes(SYNS_AttrText, SYNS_FriendlyAttrText);
	addAttribute(fTextAttri);
	fUndefKeyAttri = new TSynHighlighterAttributes(SYNS_AttrUnknownWord, SYNS_FriendlyAttrUnknownWord);
	fUndefKeyAttri->Style = Synhighlighterhtml__3;
	fUndefKeyAttri->Foreground = clRed;
	addAttribute(fUndefKeyAttri);
	fValueAttri = new TSynHighlighterAttributes(SYNS_AttrValue, SYNS_FriendlyAttrValue);
	fValueAttri->Foreground = (TColor) 0x00FF8000;
	addAttribute(fValueAttri);
	fAndAttri = new TSynHighlighterAttributes(SYNS_AttrEscapeAmpersand, SYNS_FriendlyAttrEscapeAmpersand);
	fAndAttri->Style = Synhighlighterhtml__4;
	fAndAttri->Foreground = (TColor) 0x0000FF00;
	addAttribute(fAndAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	FRange = rsText;
	fDefaultFilter = SYNS_FilterHTML;
}

void __fastcall TSynHTMLSyn::BraceCloseProc()
{
	FRange = rsText;
	FTokenID = tkSymbol;
	++Run;
}

void __fastcall TSynHTMLSyn::CommentProc()
{
	FTokenID = tkComment;
	if(IsLineEnd(Run))
	{
		NextProcedure();
		return;
	}
	while(!IsLineEnd(Run))
	{
		if((fLine[Run] == L'>') && (fLine[Run - 1] == L'-') && (fLine[Run - 2] == L'-'))
		{
			FRange = rsText;
			++Run;
			break;
		}
		++Run;
	}
}

void __fastcall TSynHTMLSyn::BraceOpenProc()
{
	++Run;
	if((fLine[Run] == L'!') && (fLine[Run + 1] == L'-') && (fLine[Run + 2] == L'-'))
	{
		FRange = rsComment;
		FTokenID = tkComment;
		Run += 3;
	}
	else
	{
		FRange = rsKey;
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynHTMLSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynHTMLSyn::EqualProc()
{
	FRange = rsValue;
	FTokenID = tkSymbol;
	++Run;
}

void __fastcall TSynHTMLSyn::IdentProc()
{
	switch(FRange)
	{
		case rsKey:
		{
			FRange = rsParam;
			FTokenID = IdentKind((fLine + Run));
			Run += fStringLen;
		}
		break;
		case rsValue:
		{
			FRange = rsParam;
			FTokenID = tkValue;
			do
			{
				++Run;
			}
			while(!((fLine[Run] <= L'\x20') || (fLine[Run] == L'>')));
		}
		break;
		default:
		FTokenID = tkIdentifier;
		do
		{
			++Run;
		}
		while(!((fLine[Run] <= L'\x20') || (fLine[Run] == L'=') || (fLine[Run] == L'\"') || (fLine[Run] == L'>')));
		break;
	}
}

void __fastcall TSynHTMLSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynHTMLSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynHTMLSyn::TextProc()
{

	auto IsStopChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
			 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
			 case 30: case 31:
			case L'<':
			case L'&':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	int i = 0;
	if(CharInSet(fLine[Run], Synhighlighterhtml__5))
	{
		NextProcedure();
		return;
	}
	FTokenID = tkText;
	while(true)
	{
		while(!IsStopChar())
			++Run;
		if(fLine[Run] == L'&')
		{
			if(fLine[Run + 1] == L'#')
			{
				fAndCode = -1;
				i = Run;
				Run += 2;
				if(CharInSet(fLine[Run], Synhighlighterhtml__6))
				{
					++Run;
					while(IsNumberChar())
						++Run;
				}
				else
				{
					while(CharInSet(fLine[Run], Synhighlighterhtml__7))
						++Run;
				}
				if(fLine[Run] == L';')
				{
					++Run;
					Run = i;
					FRange = rsAmpersand;
				}
				break;
			}
			else
			{
				int stop = 0;
				for(stop = 248 /*# High(EscapeAmps) */, i = 0 /*# Low(EscapeAmps) */; i <= stop; i++)
				{
					if(AnsiStrLComp((fLine + Run), const_cast<PWideChar>(EscapeAmps[i]), (unsigned int) String(EscapeAmps[i]).Length()) == 0)
					{
						fAndCode = i;
						FRange = rsAmpersand;
						return;
					}
				}
			}
			++Run;
		}
		else
		break;
	}
}

void __fastcall TSynHTMLSyn::AmpersandProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	if(FRange != rsAmpersand)
	{
		if(FRange == rsKey)
		{
			++Run;
			FRange = rsText;
			FTokenID = tkText;
		}
		else
		IdentProc();
		return;
	}
	switch(fAndCode)
	{
		case 0:
		{
			FTokenID = tkAmpersand;
			Run += String(EscapeAmps[fAndCode]).Length();
		}
		break;
		default:
		{
			if(fLine[Run + 1] == L'#')
			{
				fAndCode = -1;
				Run += 2;
				if(CharInSet(fLine[Run], Synhighlighterhtml__8))
				{
					++Run;
					while(IsNumberChar())
						++Run;
				}
				else
				{
					while(CharInSet(fLine[Run], Synhighlighterhtml__9))
						++Run;
				}
				if(fLine[Run] == L';')
				{
					++Run;
					FTokenID = tkAmpersand;
				}
				else
				FTokenID = tkText;
			}
		}
		break;
	}
	fAndCode = -1;
	FRange = rsText;
}

void __fastcall TSynHTMLSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while(fLine[Run] <= L'\x20')
	{
		if(CharInSet(fLine[Run], Synhighlighterhtml__10))
			break;
		++Run;
	}
}

void __fastcall TSynHTMLSyn::StringProc()
{
	WideChar iOpenChar = L'\0';
	switch(FRange)
	{
		case rsQuoteValue:
		{
			iOpenChar = L'\x27';
			FTokenID = tkValue;
		}
		break;
		case rsDoubleQuoteValue:
		{
			iOpenChar = L'\"';
			FTokenID = tkValue;
		}
		break;
		default:
		{
			iOpenChar = fLine[Run];
			if(FRange == rsValue)
			{
				if(iOpenChar == L'\"')
					FRange = rsDoubleQuoteValue;
				else
					FRange = rsQuoteValue;
				FTokenID = tkValue;
			}
			else
			{
				IdentProc();
				return;
			}
			++Run; /* jumps over the opening char */
		}
		break;
	}
	while(!IsLineEnd(Run))
	{
		if(fLine[Run] == iOpenChar)
		{
			++Run;  /* jumps over the closing char */
			if(Synhighlighterhtml__11.Contains(FRange))
				FRange = rsParam;
			else
				FRange = rsText;
			break;
		}
		++Run;
	}
}

bool __fastcall TSynHTMLSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'_':
		case L'/':
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

void __fastcall TSynHTMLSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsText:
		TextProc();
		break;
		case rsComment:
		CommentProc();
		break;
		case rsQuoteValue:
		case rsDoubleQuoteValue:
		if(IsLineEnd(Run))
			NextProcedure();
		else
			StringProc();
		break;
		default:
		NextProcedure();
		break;
	}

  // ensure that one call of Next is enough to reach next token
	if((fOldRun == Run) && !GetEol())
		Next();
	inherited::Next();
}

void __fastcall TSynHTMLSyn::NextProcedure()
{
	switch(fLine[Run])
	{
		case L'\x00':
		NullProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'&':
		AmpersandProc();
		break;
		case L'\"':
		case L'\x27':
		StringProc();
		break;
		case L'<':
		BraceOpenProc();
		break;
		case L'>':
		BraceCloseProc();
		break;
		case L'=':
		EqualProc();
		break;
		default:
		IdentProc();
		break;
	}
}

TSynHighlighterAttributes* __fastcall TSynHTMLSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_COMMENT:
		result = fCommentAttri;
		break;
		case SYN_ATTR_IDENTIFIER:
		result = fIdentifierAttri;
		break;
		case SYN_ATTR_KEYWORD:
		result = fKeyAttri;
		break;
		case SYN_ATTR_WHITESPACE:
		result = fSpaceAttri;
		break;
		case SYN_ATTR_SYMBOL:
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynHTMLSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynHTMLSyn::GetTokenID()
{
	TtkTokenKind result = tkAmpersand;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynHTMLSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
	{
		case tkAmpersand:
		result = fAndAttri;
		break;
		case tkComment:
		result = fCommentAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkText:
		result = fTextAttri;
		break;
		case tkUndefKey:
		result = fUndefKeyAttri;
		break;
		case tkValue:
		result = fValueAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynHTMLSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void* __fastcall TSynHTMLSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

void __fastcall TSynHTMLSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynHTMLSyn::ResetRange()
{
	FRange = rsText;
}

bool __fastcall TSynHTMLSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterHTML;
	return result;
}

/*#static*/
String __fastcall TSynHTMLSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangHTML;
	return result;
}

String __fastcall TSynHTMLSyn::GetSampleSource()
{
	String result;
	result = L"<!-- Syntax highlighting -->\x0d\x0a"
	           L"\x0d\x0a"
	           L"<html>\x0d\x0a"
	           L"<body bgcolor=\"red\">\x0d\x0a"
	           L"  <form name=\"frmLogin\" action=\"doSomething.asp\">\x0d\x0a"
	           L"    <input name=\"user\" value='any\x0d\x0a"
	           L"      value'>\x0d\x0a"
	           L"  </form>\x0d\x0a"
	           L"  <invalid>Sample HTML code &copy; 2001</invalid>\x0d\x0a"
	           L"</body>\x0d\x0a"
	           L"</html>";
	return result;
}

/*#static*/
String __fastcall TSynHTMLSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangHTML;
	return result;
}
static bool SynHighlighterHtml_Initialized = false;

void SynHighlighterHtml_initialization()
{
	if(SynHighlighterHtml_Initialized)
		return;
	
	SynHighlighterHtml_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynHTMLSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterHtml

