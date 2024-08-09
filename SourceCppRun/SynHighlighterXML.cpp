
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterXML.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterxml
{
#define Synhighlighterxml__0 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterxml__1 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterxml__2 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterxml__3 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterxml__4 TFontStyles()
#define Synhighlighterxml__5 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterxml__6 TFontStyles()
#define Synhighlighterxml__7 TFontStyles()
#define Synhighlighterxml__8 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterxml__9 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterxml__10 (TFontStyles() << TFontStyle::fsBold << TFontStyle::fsItalic)
#define Synhighlighterxml__11 TFontStyles()
#define Synhighlighterxml__12 (TSysCharSet() << '\x00' << '\x09' << '\x0a' << '\x0d')
#define Synhighlighterxml__13 (TSysCharSet() << '\x22' << '\x27')



__fastcall TSynXMLSyn::TSynXMLSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsText),
			FTokenID(tkAposAttrValue),
			fElementAttri(nullptr),
			fSpaceAttri(nullptr),
			fTextAttri(nullptr),
			fEntityRefAttri(nullptr),
			fProcessingInstructionAttri(nullptr),
			fCDATAAttri(nullptr),
			fCommentAttri(nullptr),
			fDocTypeAttri(nullptr),
			fAttributeAttri(nullptr),
			fnsAttributeAttri(nullptr),
			fAttributeValueAttri(nullptr),
			fnsAttributeValueAttri(nullptr),
			fSymbolAttri(nullptr),
			FWantBracesParsed(false)
{
	FCaseSensitive = true;
	fElementAttri = new TSynHighlighterAttributes(SYNS_AttrElementName, SYNS_FriendlyAttrElementName);
	fTextAttri = new TSynHighlighterAttributes(SYNS_AttrText, SYNS_FriendlyAttrText);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrWhitespace, SYNS_FriendlyAttrWhitespace);
	fEntityRefAttri = new TSynHighlighterAttributes(SYNS_AttrEntityReference, SYNS_FriendlyAttrEntityReference);
	fProcessingInstructionAttri = new TSynHighlighterAttributes(SYNS_AttrProcessingInstr, SYNS_FriendlyAttrProcessingInstr);
	fCDATAAttri = new TSynHighlighterAttributes(SYNS_AttrCDATASection, SYNS_FriendlyAttrCDATASection);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fDocTypeAttri = new TSynHighlighterAttributes(SYNS_AttrDOCTYPESection, SYNS_FriendlyAttrDOCTYPESection);
	fAttributeAttri = new TSynHighlighterAttributes(SYNS_AttrAttributeName, SYNS_FriendlyAttrAttributeName);
	fnsAttributeAttri = new TSynHighlighterAttributes(SYNS_AttrNamespaceAttrName, SYNS_FriendlyAttrNamespaceAttrName);
	fAttributeValueAttri = new TSynHighlighterAttributes(SYNS_AttrAttributeValue, SYNS_FriendlyAttrAttributeValue);
	fnsAttributeValueAttri = new TSynHighlighterAttributes(SYNS_AttrNamespaceAttrValue, SYNS_FriendlyAttrNamespaceAttrValue);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	fElementAttri->Foreground = clMaroon;
	fElementAttri->Style = Synhighlighterxml__0;
	fDocTypeAttri->Foreground = clBlue;
	fDocTypeAttri->Style = Synhighlighterxml__1;
	fCDATAAttri->Foreground = clOlive;
	fCDATAAttri->Style = Synhighlighterxml__2;
	fEntityRefAttri->Foreground = clBlue;
	fEntityRefAttri->Style = Synhighlighterxml__3;
	fProcessingInstructionAttri->Foreground = clBlue;
	fProcessingInstructionAttri->Style = Synhighlighterxml__4;
	fTextAttri->Foreground = clBlack;
	fTextAttri->Style = Synhighlighterxml__5;
	fAttributeAttri->Foreground = clMaroon;
	fAttributeAttri->Style = Synhighlighterxml__6;
	fnsAttributeAttri->Foreground = clRed;
	fnsAttributeAttri->Style = Synhighlighterxml__7;
	fAttributeValueAttri->Foreground = clNavy;
	fAttributeValueAttri->Style = Synhighlighterxml__8;
	fnsAttributeValueAttri->Foreground = clRed;
	fnsAttributeValueAttri->Style = Synhighlighterxml__9;
	fCommentAttri->Background = clSilver;
	fCommentAttri->Foreground = clGray;
	fCommentAttri->Style = Synhighlighterxml__10;
	fSymbolAttri->Foreground = clBlue;
	fSymbolAttri->Style = Synhighlighterxml__11;
	addAttribute(fSymbolAttri);
	addAttribute(fProcessingInstructionAttri);
	addAttribute(fDocTypeAttri);
	addAttribute(fCommentAttri);
	addAttribute(fElementAttri);
	addAttribute(fAttributeAttri);
	addAttribute(fnsAttributeAttri);
	addAttribute(fAttributeValueAttri);
	addAttribute(fnsAttributeValueAttri);
	addAttribute(fEntityRefAttri);
	addAttribute(fCDATAAttri);
	addAttribute(fSpaceAttri);
	addAttribute(fTextAttri);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterXML;
}

void __fastcall TSynXMLSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynXMLSyn::CarriageReturnProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynXMLSyn::LineFeedProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynXMLSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while(fLine[Run] <= L'\x20')
	{
		if(CharInSet(fLine[Run], Synhighlighterxml__12))
			break;
		++Run;
	}
}

void __fastcall TSynXMLSyn::LessThanProc()
{
	++Run;
	if(fLine[Run] == L'/')
		++Run;
	if(fLine[Run] == L'!')
	{
		if(NextTokenIs(L"--"))
		{
			FTokenID = tkSymbol;
			FRange = rsComment;
			Run += 3;
		}
		else
		{
			if(NextTokenIs(L"DOCTYPE"))
			{
				FTokenID = tkDocType;
				FRange = rsDocType;
				Run += 7;
			}
			else
			{
				if(NextTokenIs(L"[CDATA["))
				{
					FTokenID = tkCDATA;
					FRange = rsCDATA;
					Run += 7;
				}
				else
				{
					FTokenID = tkSymbol;
					FRange = rsElement;
					++Run;
				}
			}
		}
	}
	else
	{
		if(fLine[Run] == L'?')
		{
			FTokenID = tkProcessingInstruction;
			FRange = rsProcessingInstruction;
			++Run;
		}
		else
		{
			FTokenID = tkSymbol;
			FRange = rsElement;
		}
	}
}

void __fastcall TSynXMLSyn::GreaterThanProc()
{
	FTokenID = tkSymbol;
	FRange = rsText;
	++Run;
}

void __fastcall TSynXMLSyn::CommentProc()
{
	if((fLine[Run] == L'-') && (fLine[Run + 1] == L'-') && (fLine[Run + 2] == L'>'))
	{
		FTokenID = tkSymbol;
		FRange = rsText;
		Run += 3;
		return;
	}
	FTokenID = tkComment;
	if(IsLineEnd(Run))
	{
		NextProcedure();
		return;
	}
	while(!IsLineEnd(Run))
	{
		if((fLine[Run] == L'-') && (fLine[Run + 1] == L'-') && (fLine[Run + 2] == L'>'))
		{
			FRange = rsComment;
			break;
		}
		++Run;
	}
}

void __fastcall TSynXMLSyn::ProcessingInstructionProc()
{
	FTokenID = tkProcessingInstruction;
	if(IsLineEnd(Run))
	{
		NextProcedure();
		return;
	}
	while(!IsLineEnd(Run))
	{
		if((fLine[Run] == L'>') && (fLine[Run - 1] == L'?'))
		{
			FRange = rsText;
			++Run;
			break;
		}
		++Run;
	}
}

void __fastcall TSynXMLSyn::DocTypeProc()
{
	FTokenID = tkDocType;
	if(IsLineEnd(Run))
	{
		NextProcedure();
		return;
	}
	switch(FRange)
	{
		case rsDocType:
		{
			while(!IsLineEnd(Run))
			{
				switch(fLine[Run])
				{
					case L'[':
					{
						while(true)
						{
							++Run;
							switch(fLine[Run])
							{
								case L']':
								{
									++Run;
									return;
								}
								case L'\x00':
								case L'\x0a':
								case L'\x0d':
								{
									FRange = rsDocTypeSquareBraces;
									return;
								}
								default:
								  ;
								break;
							}
						}
					}
					break;
					case L'>':
					{
						FRange = rsAttribute;
						++Run;
						goto label0;
					}
					default:
					  ;
					break;
				}
				++Run;
			}
			label0:;
		}
		break;
		case rsDocTypeSquareBraces:
		{
			while(!IsLineEnd(Run))
			{
				if(fLine[Run] == L']')
				{
					FRange = rsDocType;
					++Run;
					return;
				}
				++Run;
			}
		}
		break;
		default:
		  ;
		break;
	}
}

void __fastcall TSynXMLSyn::CDATAProc()
{
	FTokenID = tkCDATA;
	if(IsLineEnd(Run))
	{
		NextProcedure();
		return;
	}
	while(!IsLineEnd(Run))
	{
		if((fLine[Run] == L'>') && (fLine[Run - 1] == L']'))
		{
			FRange = rsText;
			++Run;
			break;
		}
		++Run;
	}
}

void __fastcall TSynXMLSyn::ElementProc()
{
	if(fLine[Run] == L'/')
		++Run;
	while(IsNameChar())
		++Run;
	FRange = rsAttribute;
	FTokenID = tkElement;
}

void __fastcall TSynXMLSyn::AttributeProc()
{

  //Check if we are starting on a closing quote
	if(CharInSet(fLine[Run], Synhighlighterxml__13))
	{
		FTokenID = tkSymbol;
		FRange = rsAttribute;
		++Run;
		return;
	}
  //Read the name
	while(IsNameChar())
		++Run;
  //Check if this is an xmlns: attribute
	if(Pos(L"xmlns", GetToken()) > 0)
	{
		FTokenID = tknsAttribute;
		FRange = rsnsEqual;
	}
	else
	{
		FTokenID = tkAttribute;
		FRange = rsEqual;
	}
}

void __fastcall TSynXMLSyn::EqualProc()
{
	if(FRange == rsnsEqual)
		FTokenID = tknsEqual;
	else
		FTokenID = tkEqual;
	while(!IsLineEnd(Run))
	{
		if(fLine[Run] == L'/')
		{
			FTokenID = tkSymbol;
			FRange = rsElement;
			++Run;
			return;
		}
		else
		{
			if(fLine[Run] == L'\x22')
			{
				if(FRange == rsnsEqual)
					FRange = rsnsQuoteAttrValue;
				else
					FRange = rsQuoteAttrValue;
				++Run;
				return;
			}
			else
			{
				if(fLine[Run] == L'\x27')
				{
					if(FRange == rsnsEqual)
						FRange = rsnsAposAttrValue;
					else
						FRange = rsAposAttrValue;
					++Run;
					return;
				}
			}
		}
		++Run;
	}
}

void __fastcall TSynXMLSyn::QAttributeValueProc()
{
	if(FRange == rsnsQuoteAttrValue)
		FTokenID = tknsQuoteAttrValue;
	else
		FTokenID = tkQuoteAttrValue;
	while(!(IsLineEnd(Run) || (fLine[Run] == L'&') || (fLine[Run] == L'\x22')))
		++Run;
	if(fLine[Run] == L'&')
	{
		if(FRange == rsnsQuoteAttrValue)
			FRange = rsnsQuoteEntityRef;
		else
			FRange = rsQuoteEntityRef;
		return;
	}
	else
	{
		if(fLine[Run] != L'\x22')
			return;
	}
	FRange = rsAttribute;
}

void __fastcall TSynXMLSyn::AAttributeValueProc()
{
	if(FRange == rsnsAposAttrValue)
		FTokenID = tknsAposAttrValue;
	else
		FTokenID = tkAposAttrValue;
	while(!(IsLineEnd(Run) || (fLine[Run] == L'&') || (fLine[Run] == L'\x27')))
		++Run;
	if(fLine[Run] == L'&')
	{
		if(FRange == rsnsAposAttrValue)
			FRange = rsnsAPosEntityRef;
		else
			FRange = rsAPosEntityRef;
		return;
	}
	else
	{
		if(fLine[Run] != L'\x27')
			return;
	}
	FRange = rsAttribute;
}

void __fastcall TSynXMLSyn::TextProc()
{
	if((fLine[Run] <= L'\x1f') || (fLine[Run] == L'<'))
	{
		NextProcedure();
		return;
	}
	FTokenID = tkText;
	while(!((fLine[Run] <= L'\x1f') || (fLine[Run] == L'<') || (fLine[Run] == L'&')))
		++Run;
	if(fLine[Run] == L'&')
	{
		FRange = rsEntityRef;
		return;
	}
}

void __fastcall TSynXMLSyn::EntityRefProc()
{
	FTokenID = tkEntityRef;
	FRange = rsEntityRef;
	while(!((fLine[Run] <= L'\x20') || (fLine[Run] == L';')))
		++Run;
	if(fLine[Run] == L';')
		++Run;
	FRange = rsText;
}

void __fastcall TSynXMLSyn::QEntityRefProc()
{
	if(FRange == rsnsQuoteEntityRef)
		FTokenID = tknsQuoteEntityRef;
	else
		FTokenID = tkQuoteEntityRef;
	while(!((fLine[Run] <= L'\x20') || (fLine[Run] == L';')))
		++Run;
	if(fLine[Run] == L';')
		++Run;
	if(FRange == rsnsQuoteEntityRef)
		FRange = rsnsQuoteAttrValue;
	else
		FRange = rsQuoteAttrValue;
}

void __fastcall TSynXMLSyn::AEntityRefProc()
{
	if(FRange == rsnsAPosEntityRef)
		FTokenID = tknsAposEntityRef;
	else
		FTokenID = tkAposEntityRef;
	while(!((fLine[Run] <= L'\x20') || (fLine[Run] == L';')))
		++Run;
	if(fLine[Run] == L';')
		++Run;
	if(FRange == rsnsAPosEntityRef)
		FRange = rsnsAposAttrValue;
	else
		FRange = rsAposAttrValue;
}

void __fastcall TSynXMLSyn::IdentProc()
{
	switch(FRange)
	{
		case rsElement:
		{
			ElementProc();
		}
		break;
		case rsAttribute:
		{
			AttributeProc();
		}
		break;
		case rsEqual:
		case rsnsEqual:
		{
			EqualProc();
		}
		break;
		case rsQuoteAttrValue:
		case rsnsQuoteAttrValue:
		{
			QAttributeValueProc();
		}
		break;
		case rsAposAttrValue:
		case rsnsAposAttrValue:
		{
			AAttributeValueProc();
		}
		break;
		case rsQuoteEntityRef:
		case rsnsQuoteEntityRef:
		{
			QEntityRefProc();
		}
		break;
		case rsAPosEntityRef:
		case rsnsAPosEntityRef:
		{
			AEntityRefProc();
		}
		break;
		case rsEntityRef:
		{
			EntityRefProc();
		}
		break;
		default:
		;
		break;
	}
}

void __fastcall TSynXMLSyn::Next()
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
		case rsProcessingInstruction:
		ProcessingInstructionProc();
		break;
		case rsDocType:
		case rsDocTypeSquareBraces:
		DocTypeProc();
		break;
		case rsCDATA:
		CDATAProc();
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

void __fastcall TSynXMLSyn::NextProcedure()
{
	switch(fLine[Run])
	{
		case L'\x00':
		NullProc();
		break;
		case L'\x0a':
		LineFeedProc();
		break;
		case L'\x0d':
		CarriageReturnProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'<':
		LessThanProc();
		break;
		case L'>':
		GreaterThanProc();
		break;
		default:
		IdentProc();
		break;
	}
}

bool __fastcall TSynXMLSyn::NextTokenIs(String Token)
{
	bool result = false;
	__int64 i = 0;
	int Len = 0;
	__int64 stop = 0;
	result = true;
	Len = Token.Length();
	for(stop = Len, i = 1; i <= stop; i++)
	{
		if(fLine[Run + i] != Token[i])
		{
			result = false;
			break;
		}
	}
	return result;
}

TSynHighlighterAttributes* __fastcall TSynXMLSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_COMMENT:
		result = fCommentAttri;
		break;
		case SYN_ATTR_IDENTIFIER:
		result = fAttributeAttri;
		break;
		case SYN_ATTR_KEYWORD:
		result = fElementAttri;
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

bool __fastcall TSynXMLSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynXMLSyn::GetTokenID()
{
	TtkTokenKind result = tkAposAttrValue;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynXMLSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
	{
		case tkElement:
		result = fElementAttri;
		break;
		case tkAttribute:
		result = fAttributeAttri;
		break;
		case tknsAttribute:
		result = fnsAttributeAttri;
		break;
		case tkEqual:
		result = fSymbolAttri;
		break;
		case tknsEqual:
		result = fSymbolAttri;
		break;
		case tkQuoteAttrValue:
		result = fAttributeValueAttri;
		break;
		case tkAposAttrValue:
		result = fAttributeValueAttri;
		break;
		case tknsQuoteAttrValue:
		result = fnsAttributeValueAttri;
		break;
		case tknsAposAttrValue:
		result = fnsAttributeValueAttri;
		break;
		case tkText:
		result = fTextAttri;
		break;
		case tkCDATA:
		result = fCDATAAttri;
		break;
		case tkEntityRef:
		result = fEntityRefAttri;
		break;
		case tkQuoteEntityRef:
		result = fEntityRefAttri;
		break;
		case tkAposEntityRef:
		result = fEntityRefAttri;
		break;
		case tknsQuoteEntityRef:
		result = fEntityRefAttri;
		break;
		case tknsAposEntityRef:
		result = fEntityRefAttri;
		break;
		case tkProcessingInstruction:
		result = fProcessingInstructionAttri;
		break;
		case tkComment:
		result = fCommentAttri;
		break;
		case tkDocType:
		result = fDocTypeAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynXMLSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void* __fastcall TSynXMLSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

void __fastcall TSynXMLSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynXMLSyn::ResetRange()
{
	FRange = rsText;
}

bool __fastcall TSynXMLSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterXML;
	return result;
}

/* TODO: In fact every Number also non-arabics and every letter also German umlauts
  can be used. Something like IsAlphaNumericCharW should be used instead. */

bool __fastcall TSynXMLSyn::IsNameChar()
{
	bool result = false;
	switch(fLine[Run])
	{
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case L'_':
		case L'.':
		case L':':
		case L'-':
		result = true;
		break;
		default:
		if(fLine[Run] > L'À') // TODO: this here is very vague, see above
			result = true;
		else
			result = false;
		break;
	}
	return result;
}

/*#static*/
String __fastcall TSynXMLSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangXML;
	return result;
}

String __fastcall TSynXMLSyn::GetSampleSource()
{
	String result;
	result = L"<?xml version=\"1.0\"?>\x0d\x0a"
	           L"<!DOCTYPE root [\x0d\x0a"
	           L"  ]>\x0d\x0a"
	           L"<!-- Comment -->\x0d\x0a"
	           L"<root version=\"&test;\">\x0d\x0a"
	           L"  <![CDATA[ **CDATA section** ]]>\x0d\x0a"
	           L"</root>";
	return result;
}

/*#static*/
String __fastcall TSynXMLSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangXML;
	return result;
}
static bool SynHighlighterXML_Initialized = false;

void SynHighlighterXML_initialization()
{
	if(SynHighlighterXML_Initialized)
		return;
	
	SynHighlighterXML_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynXMLSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterXML

