
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterCss.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace Synhighlighterhashentries;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlightercss
{
#define Synhighlightercss__0 (TSysCharSet() <<  \
          97 << 98 << 99 << 100 << 101 << 102 <<  \
          103 << 104 << 105 << 106 << 107 << 108 <<  \
          109 << 110 << 111 << 112 << 113 << 114 <<  \
          115 << 116 << 117 << 118 << 119 << 120 <<  \
          121 << 122 <<  \
          65 << 66 << 67 << 68 << 69 << 70 <<  \
          71 << 72 << 73 << 74 << 75 << 76 <<  \
          77 << 78 << 79 << 80 << 81 << 82 <<  \
          83 << 84 << 85 << 86 << 87 << 88 <<  \
          89 << 90 << '_' << '-')
#define Synhighlightercss__1 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlightercss__2 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightercss__3 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightercss__4 TFontStyles()
#define Synhighlightercss__5 TFontStyles()
#define Synhighlightercss__6 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightercss__7 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlightercss__8 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlightercss__9 (TSysCharSet() <<  \
          48 << 49 << 50 << 51 << 52 << 53 <<  \
          54 << 55 << 56 << 57 << '.')
#define Synhighlightercss__10 (TSysCharSet() << '(' << ')' << '}' << ';' << ',' << ' ')
#define Synhighlightercss__11 (TSysCharSet() << '}' << ';')
#define Synhighlightercss__12 (TSysCharSet() << ':' << '\"' << '}' << ';')


const String Properties_CSS1 = L"background"
	           L",background-attachment"
	           L",background-color"
	           L",background-image"
	           L",background-position"
	           L",background-repeat"
	           L",border"
	           L",border-bottom"
	           L",border-bottom-color"
	           L",border-bottom-style"
	           L",border-bottom-width"
	           L",border-color"
	           L",border-left"
	           L",border-left-color"
	           L",border-left-style"
	           L",border-left-width"
	           L",border-right"
	           L",border-right-color"
	           L",border-right-style"
	           L",border-right-width"
	           L",border-style"
	           L",border-top"
	           L",border-top-color"
	           L",border-top-style"
	           L",border-top-width"
	           L",border-width"
	           L",clear"
	           L",color"
	           L",display"
	           L",float"
	           L",font"
	           L",font-family"
	           L",font-size"
	           L",font-style"
	           L",font-variant"
	           L",font-weight"
	           L",height"
	           L",letter-spacing"
	           L",line-height"
	           L",list-style"
	           L",list-style-image"
	           L",list-style-position"
	           L",list-style-type"
	           L",margin"
	           L",margin-bottom"
	           L",margin-left"
	           L",margin-right"
	           L",margin-top"
	           L",padding"
	           L",padding-bottom"
	           L",padding-left"
	           L",padding-right"
	           L",padding-top"
	           L",text-align"
	           L",text-decoration"
	           L",text-indent"
	           L",text-transform"
	           L",vertical-align"
	           L",white-space"
	           L",width"
	           L",word-spacing";
const String Properties_CSS2 = L"border-collapse"
	           L",border-spacing"
	           L",bottom"
	           L",caption-side"
	           L",clip"
	           L",content"
	           L",counter-increment"
	           L",counter-reset"
	           L",cursor"
	           L",direction"
	           L",empty-cells"
	           L",left"
	           L",max-height"
	           L",max-width"
	           L",min-height"
	           L",min-width"
	           L",orphans"
	           L",outline"
	           L",outline-color"
	           L",outline-style"
	           L",outline-width"
	           L",overflow"
	           L",page-break-after"
	           L",page-break-before"
	           L",page-break-inside"
	           L",position"
	           L",quotes"
	           L",right"
	           L",table-layout"
	           L",top"
	           L",unicode-bidi"
	           L",visibility"
	           L",widows"
	           L",z-index";
const String Properties_CSS2_Aural = L"azimuth"
	           L",cue"
	           L",cue-after"
	           L",cue-before"
	           L",elevation"
	           L",pause"
	           L",pause-after"
	           L",pause-before"
	           L",pitch"
	           L",pitch-range"
	           L",play-during"
	           L",richness"
	           L",speak"
	           L",speak-header"
	           L",speak-numeral"
	           L",speak-punctuation"
	           L",speech-rate"
	           L",stress"
	           L",voice-family"
	           L",volume";
const String Properties_CSS3 = L"@font-face"
	           L",@font-feature-values"
	           L",@keyframes"
	           L",align-content"
	           L",align-items"
	           L",align-self"
	           L",alignment-adjust"
	           L",alignment-baseline"
	           L",animation"
	           L",animation-delay"
	           L",animation-direction"
	           L",animation-duration"
	           L",animation-fill-mode"
	           L",animation-iteration-count"
	           L",animation-name"
	           L",animation-play-state"
	           L",animation-timing-function"
	           L",appearance"
	           L",backface-visibility"
	           L",background-clip"
	           L",background-origin"
	           L",background-size"
	           L",baseline-shift"
	           L",bookmark-label"
	           L",bookmark-level"
	           L",bookmark-target"
	           L",border-bottom-left-radius"
	           L",border-bottom-right-radius"
	           L",border-image"
	           L",border-image-outset"
	           L",border-image-repeat"
	           L",border-image-slice"
	           L",border-image-source"
	           L",border-image-width"
	           L",border-radius"
	           L",border-top-left-radius"
	           L",border-top-right-radius"
	           L",box-align"
	           L",box-decoration-break"
	           L",box-direction"
	           L",box-flex"
	           L",box-flex-group"
	           L",box-lines"
	           L",box-ordinal-group"
	           L",box-orient"
	           L",box-pack"
	           L",box-shadow"
	           L",box-sizing"
	           L",break-after"
	           L",break-before"
	           L",break-inside"
	           L",color-profile"
	           L",column-count"
	           L",column-fill"
	           L",column-gap"
	           L",column-rule"
	           L",column-rule-color"
	           L",column-rule-style"
	           L",column-rule-width"
	           L",columns"
	           L",column-span"
	           L",column-width"
	           L",crop"
	           L",dominant-baseline"
	           L",drop-initial-after-adjust"
	           L",drop-initial-after-align"
	           L",drop-initial-before-adjust"
	           L",drop-initial-before-align"
	           L",drop-initial-size"
	           L",drop-initial-value"
	           L",filter"
	           L",fit"
	           L",fit-position"
	           L",float-offset"
	           L",flex"
	           L",flex-basis"
	           L",flex-direction"
	           L",flex-flow"
	           L",flex-grow"
	           L",flex-shrink"
	           L",flex-wrap"
	           L",font-size-adjust"
	           L",font-feature-setting"
	           L",font-kerning"
	           L",font-language-override"
	           L",font-synthesis"
	           L",font-variant-alternates"
	           L",font-variant-caps"
	           L",font-variant-east-asian"
	           L",font-variant-ligatures"
	           L",font-variant-numeric"
	           L",font-variant-position"
	           L",font-stretch"
	           L",grid-columns"
	           L",grid-rows"
	           L",hanging-punctuation"
	           L",hyphenate-after"
	           L",hyphenate-before"
	           L",hyphenate-character"
	           L",hyphenate-lines"
	           L",hyphenate-resource"
	           L",hyphens"
	           L",icon"
	           L",image-orientation"
	           L",image-rendering"
	           L",image-resolution"
	           L",ime-mode"
	           L",justify-content"
	           L",inline-box-align"
	           L",line-break"
	           L",line-stacking"
	           L",line-stacking-ruby"
	           L",line-stacking-shift"
	           L",line-stacking-strategy"
	           L",mark"
	           L",mark-after"
	           L",mark-before"
	           L",marks"
	           L",marquee-direction"
	           L",marquee-play-count"
	           L",marquee-speed"
	           L",marquee-style"
	           L",mask"
	           L",mask-type"
	           L",move-to"
	           L",nav-down"
	           L",nav-index"
	           L",nav-left"
	           L",nav-right"
	           L",nav-up"
	           L",object-fit"
	           L",object-position"
	           L",opacity"
	           L",order"
	           L",outline-offset"
	           L",overflow-style"
	           L",overflow-x"
	           L",overflow-y"
	           L",overflow-wrap"
	           L",page"
	           L",page-policy"
	           L",perspective"
	           L",perspective-origin"
	           L",phonemes"
	           L",punctuation-trim"
	           L",rendering-intent"
	           L",resize"
	           L",rest"
	           L",rest-after"
	           L",rest-before"
	           L",rotation"
	           L",rotation-point"
	           L",ruby-align"
	           L",ruby-overhang"
	           L",ruby-position"
	           L",ruby-span"
	           L",size"
	           L",string-set"
	           L",tab-size"
	           L",target"
	           L",target-name"
	           L",target-new"
	           L",target-position"
	           L",text-align-last"
	           L",text-combine-horizontal"
	           L",text-decoration-color"
	           L",text-decoration-line"
	           L",text-decoration-style"
	           L",text-height"
	           L",text-justify"
	           L",text-orientation"
	           L",text-outline"
	           L",text-overflow"
	           L",text-shadow"
	           L",text-underline-position"
	           L",text-wrap"
	           L",transform"
	           L",transform-origin"
	           L",transform-style"
	           L",transition"
	           L",transition-delay"
	           L",transition-duration"
	           L",transition-property"
	           L",transition-timing-function"
	           L",voice-balance"
	           L",voice-duration"
	           L",voice-pitch"
	           L",voice-pitch-range"
	           L",voice-rate"
	           L",voice-stress"
	           L",voice-volume"
	           L",word-break"
	           L",word-wrap"
	           L",writing-mode";

/* TSynCssSyn */

/*$Q-*/

int __fastcall TSynCssSyn::HashKey(PWideChar Str)
{
	int result = 0;
	result = 0;
	while(CharInSet((*Str), Synhighlightercss__0))
	{
		if((*Str) != L'-')
			switch((*Str))
			{
				case L'_':
				result += 27;
				break;
				case L'-':
				result += 28;
				break;
				default:
				result += int(Sysutils::AnsiUpperCase(String((*Str)))[1]) - 64;
				break;
			}
		++Str;
	}
	while(CharInSet((*Str), Synhighlightercss__1))
	{
		result += int((*Str)) - int(L'0');
		++Str;
	}
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynCssSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	TSynHashEntry* Entry = nullptr;
	fToIdent = Maybe;
	Entry = fKeywords->Items[HashKey(Maybe)];
	while(ASSIGNED(Entry))
	{
		if(Entry->KeywordLen > fStringLen)
			break;
		else
		{
			if(Entry->KeywordLen == fStringLen)
			{
				if(IsCurrentToken(Entry->Keyword))
				{
					result = ((TtkTokenKind) Entry->Kind);
					return result;
				}
			}
		}
		Entry = Entry->Next;
	}
	result = tkUndefProperty;
	return result;
}

void __fastcall TSynCssSyn::DoAddKeyword(String AKeyword, int AKind)
{
	int HashValue = 0;
	HashValue = HashKey(ustr2pwchar(AKeyword));
	fKeywords->Items[HashValue] = new TSynHashEntry(AKeyword, AKind);
}

__fastcall TSynCssSyn::TSynCssSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsSelector),
			fCommentRange(rsComment),
			fParameterRange(rsComment),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fPropertyAttri(nullptr),
			fAttributeAttri(nullptr),
			fSelectorAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fColorAttri(nullptr),
			fNumberAttri(nullptr),
			fSymbolAttri(nullptr),
			fTextAttri(nullptr),
			fValueAttri(nullptr),
			fUndefPropertyAttri(nullptr),
			fImportantPropertyAttri(nullptr),
			fAtRuleAttri(nullptr),
			fKeywords(nullptr)
{
	FCaseSensitive = false;
	fKeywords = new TSynHashEntryList();
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	addAttribute(fCommentAttri);
	fPropertyAttri = new TSynHighlighterAttributes(SYNS_AttrProperty, SYNS_FriendlyAttrProperty);
	fPropertyAttri->Style = Synhighlightercss__2;
	addAttribute(fPropertyAttri);
	fSelectorAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fSelectorAttri->Style = Synhighlightercss__3;
	fSelectorAttri->Foreground = (TColor) 0x00FF0080;
	addAttribute(fSelectorAttri);
	fAttributeAttri = new TSynHighlighterAttributes(SYNS_AttrAttribute, SYNS_FriendlyAttrAttribute);
	fAttributeAttri->Style = Synhighlightercss__4;
	fAttributeAttri->Foreground = (TColor) 0x00FF0080;
	addAttribute(fAttributeAttri);
	fAtRuleAttri = new TSynHighlighterAttributes(SYNS_AttrAtRules, SYNS_FriendlyAttrAttribute);
	fAtRuleAttri->Style = Synhighlightercss__5;
	fAtRuleAttri->Foreground = (TColor) 0x00808000;
	addAttribute(fAtRuleAttri);
	fUndefPropertyAttri = new TSynHighlighterAttributes(SYNS_AttrUndefinedProperty, SYNS_FriendlyAttrUndefinedProperty);
	fUndefPropertyAttri->Style = Synhighlightercss__6;
	fUndefPropertyAttri->Foreground = (TColor) 0x00FF0080;
	addAttribute(fUndefPropertyAttri);
	fImportantPropertyAttri = new TSynHighlighterAttributes(L"Important", L"Important Marker");
	fImportantPropertyAttri->Style = Synhighlightercss__7;
	fImportantPropertyAttri->Foreground = clRed;
	addAttribute(fImportantPropertyAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fColorAttri = new TSynHighlighterAttributes(SYNS_AttrColor, SYNS_FriendlyAttrColor);
	addAttribute(fColorAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fTextAttri = new TSynHighlighterAttributes(SYNS_AttrText, SYNS_FriendlyAttrText);
	addAttribute(fTextAttri);
	fValueAttri = new TSynHighlighterAttributes(SYNS_AttrValue, SYNS_FriendlyAttrValue);
	fValueAttri->Foreground = (TColor) 0x00FF8000;
	addAttribute(fValueAttri);
	SetAttributesOnChange(DefHighlightChange);

  // TODO: differentiating tkProperty for CSS1, CSS2 & CSS3 highlighting
	EnumerateKeywords(int(tkProperty), Properties_CSS1, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkProperty), Properties_CSS2, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkProperty), Properties_CSS2_Aural, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkProperty), Properties_CSS3, IsIdentChar, DoAddKeyword);
	fDefaultFilter = SYNS_FilterCSS;
}

__fastcall TSynCssSyn::~TSynCssSyn()
{
	delete fKeywords;
	//# inherited::Destroy();
}

void __fastcall TSynCssSyn::AttributeProc()
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
			case L']':
			case L'~':
			case L'^':
			case L'$':
			case L'*':
			case L'|':
			case L'=':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	if(IsStopChar())
	{
		switch(fLine[Run])
		{
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
			 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
			 case 30: case 31:
			case L'{':
			case L'/':
			NextDeclaration();
			break;
			case L']':
			BracketCloseProc();
			break;
			case L'~':
			TildeProc();
			break;
			case L'|':
			PipeProc();
			break;
			case L'=':
			EqualProc();
			break;
			case L'^':
			CircumflexProc();
			break;
			default:
			  ;
			break;
		}
		return;
	}
	FTokenID = tkSelectorAttrib;
	while(!IsStopChar())
		++Run;
}

void __fastcall TSynCssSyn::BraceCloseProc()
{
	FRange = rsSelector;
	FTokenID = tkSymbol;
	++Run;
}

void __fastcall TSynCssSyn::BraceOpenProc()
{
	++Run;
	FRange = rsDeclaration;
	FTokenID = tkSymbol;
}

void __fastcall TSynCssSyn::BracketCloseProc()
{
	FTokenID = tkSymbol;
	FRange = rsSelector;
	++Run;
}

void __fastcall TSynCssSyn::BracketOpenProc()
{
	++Run;
	FRange = rsAttrib;
	FTokenID = tkSymbol;
}

void __fastcall TSynCssSyn::CircumflexProc()
{
	++Run;
	if(fLine[Run] == L'=')
	{
		++Run;
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynCssSyn::CommentProc()
{
	if(fLine[Run] == L'\x00')
		NullProc();
	else
	{
		FTokenID = tkComment;
		do
		{
			if((fLine[Run] == L'*') && (fLine[Run + 1] == L'/'))
			{
				FRange = fCommentRange;
				Run += 2;
				break;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
	}
}

void __fastcall TSynCssSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynCssSyn::SemiProc()
{
	FRange = rsUnKnown;
	FTokenID = tkSymbol;
	++Run;
}

void __fastcall TSynCssSyn::StartValProc()
{
	FRange = rsValue;
	FTokenID = tkSymbol;
	++Run;
}

void __fastcall TSynCssSyn::NumberProc()
{
	if((fLine[Run] == L'-') && !CharInSet(fLine[Run + 1], Synhighlightercss__8))
		IdentProc();
	else
	{
		++Run;
		FTokenID = tkNumber;
		while(CharInSet(fLine[Run], Synhighlightercss__9))
		{
			switch(fLine[Run])
			{
				case L'.':
				if(fLine[Run + 1] == L'.')
					goto label0;
				break;
				default:
				  ;
				break;
			}
			++Run;
		}
		label0:;
	}
}

void __fastcall TSynCssSyn::ParenCloseProc()
{
	FRange = fParameterRange;
	FTokenID = tkSymbol;
	++Run;
}

void __fastcall TSynCssSyn::ParenOpenProc()
{
	++Run;
	fParameterRange = FRange;
	FRange = rsParameter;
	FTokenID = tkSymbol;
}

void __fastcall TSynCssSyn::PipeProc()
{
	++Run;
	if(fLine[Run] == L'=')
	{
		++Run;
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynCssSyn::PlusProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynCssSyn::IdentProc()
{
	switch(FRange)
	{
		case rsProperty:
		{
			FRange = rsDeclaration;
			FTokenID = tkSelector;
			Run += fStringLen;
		}
		break;
		case rsValue:
		case rsParameter:
		{
			FTokenID = tkValue;
			while(!IsLineEnd(Run) && !CharInSet(fLine[Run], Synhighlightercss__10))
			{
				++Run;
			}
			if(IsLineEnd(Run) || CharInSet(fLine[Run], Synhighlightercss__11))
				FRange = rsDeclaration;
		}
		break;
		default:
		FTokenID = IdentKind((fLine + Run));
		do
		{
			++Run;
		}
		while(!((fLine[Run] <= L'\x20') || CharInSet(fLine[Run], Synhighlightercss__12)));
		break;
	}
}

void __fastcall TSynCssSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynCssSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynCssSyn::AtRuleProc()
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
			case L'{':
			case L';':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	if(IsStopChar())
	{
		switch(fLine[Run])
		{
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
			 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
			 case 30: case 31:
			case L'{':
			case L';':
			SelectorProc();
			break;
			default:
			  ;
			break;
		}
		return;
	}
	FTokenID = tkAtRule;
	while(!IsStopChar())
		++Run;
}

void __fastcall TSynCssSyn::SelectorProc()
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
			case L'{':
			case L'/':
			case L'[':
			case L']':
			case L'>':
			case L'+':
			case L'~':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	if(fLine[Run] == L'}')
	{
		++Run;
		FTokenID = tkSymbol;
		return;
	}
	if(fLine[Run] == L'@')
	{
		++Run;
		AtRuleProc();
		return;
	}
	if(IsStopChar())
	{
		switch(fLine[Run])
		{
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
			 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
			 case 30: case 31:
			case L'{':
			case L'/':
			NextDeclaration();
			break;
			case L'[':
			BracketOpenProc();
			break;
			case L']':
			BracketCloseProc();
			break;
			case L'>':
			GreaterProc();
			break;
			case L'+':
			PlusProc();
			break;
			case L'~':
			TildeProc();
			break;
			default:
			  ;
			break;
		}
		return;
	}
	FTokenID = tkSelector;
	while(!IsStopChar())
		++Run;
}

void __fastcall TSynCssSyn::TildeProc()
{
	++Run;
	if(fLine[Run] == L'=')
	{
		++Run;
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynCssSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynCssSyn::StringProc()
{
	FTokenID = tkString;
	++Run;  // first '"'
	while(!(IsLineEnd(Run) || (fLine[Run] == L'\"')))
		++Run;
	if(fLine[Run] == L'\"')
		++Run;  // last '"'
}

void __fastcall TSynCssSyn::HashProc()
{

	auto IsHexChar = [&]() -> bool 
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
	FTokenID = tkColor;
	++Run;  // '#'
	while(IsHexChar())
		++Run;
}

void __fastcall TSynCssSyn::EqualProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynCssSyn::ExclamProc()
{
	if((fLine[Run + 1] == L'i') && (fLine[Run + 2] == L'm') && (fLine[Run + 3] == L'p') && (fLine[Run + 4] == L'o') && (fLine[Run + 5] == L'r') && (fLine[Run + 6] == L't') && (fLine[Run + 7] == L'a') && (fLine[Run + 8] == L'n') && (fLine[Run + 9] == L't'))
	{
		FTokenID = tkImportant;
		Run += 10;
	}
	else
	IdentProc();
}

void __fastcall TSynCssSyn::SlashProc()
{
	++Run;
	if(fLine[Run] == L'*')
	{
		FTokenID = tkComment;
		fCommentRange = FRange;
		FRange = rsComment;
		++Run;
		if(!IsLineEnd(Run))
			CommentProc();
	}
	else
	FTokenID = tkSymbol;
}

void __fastcall TSynCssSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsSelector:
		SelectorProc();
		break;
		case rsAttrib:
		AttributeProc();
		break;
		case rsComment:
		CommentProc();
		break;
		default:
		NextDeclaration();
		break;
	}
	inherited::Next();
}

void __fastcall TSynCssSyn::NextDeclaration()
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
		case L'\"':
		StringProc();
		break;
		case L'#':
		HashProc();
		break;
		case L'{':
		BraceOpenProc();
		break;
		case L'}':
		BraceCloseProc();
		break;
		case L'(':
		ParenOpenProc();
		break;
		case L')':
		ParenCloseProc();
		break;
		case L':':
		case L',':
		StartValProc();
		break;
		case L';':
		SemiProc();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		case L'-':
		case L'.':
		NumberProc();
		break;
		case L'/':
		SlashProc();
		break;
		case L'!':
		ExclamProc();
		break;
		default:
		IdentProc();
		break;
	}
}

TSynHighlighterAttributes* __fastcall TSynCssSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_COMMENT:
		result = fCommentAttri;
		break;
		case SYN_ATTR_KEYWORD:
		result = fSelectorAttri;
		break;
		case SYN_ATTR_WHITESPACE:
		result = fSpaceAttri;
		break;
		case SYN_ATTR_STRING:
		result = fStringAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynCssSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynCssSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynCssSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkAtRule:
		result = fAtRuleAttri;
		break;
		case tkProperty:
		result = fPropertyAttri;
		break;
		case tkSelector:
		result = fSelectorAttri;
		break;
		case tkSelectorAttrib:
		result = fAttributeAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkText:
		result = fTextAttri;
		break;
		case tkUndefProperty:
		result = fUndefPropertyAttri;
		break;
		case tkImportant:
		result = fImportantPropertyAttri;
		break;
		case tkValue:
		result = fValueAttri;
		break;
		case tkColor:
		result = fColorAttri;
		break;
		case tkNumber:
		result = fNumberAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynCssSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynCssSyn::GreaterProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void* __fastcall TSynCssSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

void __fastcall TSynCssSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynCssSyn::ResetRange()
{
	FRange = rsSelector;
}

String __fastcall TSynCssSyn::GetSampleSource()
{
	String result;
	result = L"/* Syntax Highlighting */\x0d\x0a"
	           L"body { font-family: Tahoma, Verdana, Arial, Helvetica, sans-serif; font-size: 8pt }\x0d\x0a"
	           L"H1 { font-size: 18pt; color: #000099; made-up-property: 1 }";
	return result;
} /* GetSampleSource */

/*#static*/
String __fastcall TSynCssSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangCSS;
	return result;
}

bool __fastcall TSynCssSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterCSS;
	return result;
}

bool __fastcall TSynCssSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'_':
		case L'-':
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

/*#static*/
String __fastcall TSynCssSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangCSS;
	return result;
}
static bool SynHighlighterCss_Initialized = false;

void SynHighlighterCss_initialization()
{
	if(SynHighlighterCss_Initialized)
		return;
	
	SynHighlighterCss_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynCssSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterCss

