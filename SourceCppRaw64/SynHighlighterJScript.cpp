
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterJScript.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;

namespace Synhighlighterjscript
{
#define Synhighlighterjscript__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterjscript__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterjscript__2 (TSysCharSet() << '=' << '&')
#define Synhighlighterjscript__3 (TSysCharSet() << '=' << '-' << '>')
#define Synhighlighterjscript__4 (TSysCharSet() << '=' << '|')
#define Synhighlighterjscript__5 (TSysCharSet() << '=' << '+')


  // IMPORTANT!!! Cause JavaScript is case sensitive, list must be sorted by ASCII values
const String NonReserwedKeyWords[318/*# range 0..317*/] = {L"All", L"Anchor", L"Applet", L"Area", L"Arguments", L"Array", L"Boolean", L"Button", L"Checkbox", L"Date"
                    , L"E", L"Embed", L"FileUpload", L"Float", L"Form", L"Frame", L"Function", L"Global", L"Hidden", L"History", L"Image", L"Infinity"
                    , L"LN10", L"LN2", L"LOG10E", L"LOG2E", L"Layer", L"Link", L"Location", L"MAX_VALUE", L"MIN_VALUE", L"Math", L"MimeType", L"NEGATIVE_INFINITY"
                    , L"Navigator", L"Null", L"Number", L"Object", L"Option", L"PI", L"POSITIVE_INFINITY", L"Packages", L"Password"
                    , L"Plugin", L"Radio", L"RegExp", L"Reset", L"SQRT1_2", L"SQRT2", L"Select", L"String", L"Submit", L"Text", L"Textarea", L"URL"
                    , L"UTC", L"Undefined", L"Window", L"abs", L"acos", L"action", L"alert", L"align", L"alinkColor", L"all", L"anchor", L"anchors", L"appCodeName"
                    , L"appName", L"appVersion", L"applets", L"arguments", L"asin", L"atan", L"atan2", L"await", L"back", L"background", L"bgColor"
                    , L"big", L"blink", L"blur", L"body", L"bold", L"border", L"bottom", L"call", L"caller", L"captureEvents", L"ceil", L"charAt"
                    , L"charCodeAt", L"checked", L"clear", L"clearInterval", L"clearTimeout", L"click", L"close", L"closed", L"color", L"complete"
                    , L"concat", L"confirm", L"cookie", L"cos", L"current", L"defaultChecked", L"defaultSelected", L"defaultStatus", L"defaultValue"
                    , L"description", L"display", L"document", L"domain", L"elements", L"embeds", L"enabledPlugin", L"encoding", L"escape"
                    , L"eval", L"event", L"exp", L"fgColor", L"filename", L"find", L"fixed", L"floor", L"focus", L"fontcolor", L"fontsize", L"form"
                    , L"forms", L"forward", L"frames", L"fromCharCode", L"getDate", L"getDay", L"getElementById", L"getFullYear", L"getHours", L"getMilliseconds"
                    , L"getMinutes", L"getMonth", L"getSeconds", L"getTime", L"getTimezoneOffset", L"getUTCDate", L"getUTCDay", L"getUTCFullYear"
                    , L"getUTCHours", L"getUTCMilliseconds", L"getUTCMinutes", L"getUTCMonth", L"getUTCSeconds", L"getYear", L"go"
                    , L"handleEvent", L"hash", L"height", L"history", L"home", L"host", L"hostname", L"href", L"hspace", L"images", L"index", L"indexOf"
                    , L"innerHeight", L"innerWidth", L"input", L"isFinite", L"isNaN", L"italics", L"java", L"javaEnabled", L"join", L"lastIndexOf"
                    , L"lastModified", L"layers", L"left", L"length", L"let", L"link", L"linkColor", L"links", L"location", L"locationbar", L"log"
                    , L"logon", L"lowsrc", L"match", L"max", L"menubar", L"method", L"mimeTypes", L"min", L"moveBy", L"moveTo", L"name", L"navigator", L"netscape"
                    , L"next", L"open", L"opener", L"options", L"outerHeight", L"outerWidth", L"pageX", L"pageXOffset", L"pageY", L"pageYOffset"
                    , L"parent", L"parse", L"parseFloat", L"parseInt", L"pathname", L"personalbar", L"platform", L"plugins", L"port"
                    , L"pow", L"previous", L"print", L"prompt", L"protocol", L"random", L"referrer", L"refresh", L"releaseEvents", L"reload", L"replace"
                    , L"reset", L"resizeBy", L"resizeTo", L"reverse", L"right", L"round", L"routeEvent", L"screen", L"scroll", L"scrollBy", L"scrollTo"
                    , L"scrollbars", L"search", L"select", L"selected", L"selectedIndex", L"self", L"setDate", L"setFullYear", L"setHours", L"setInterval"
                    , L"setMilliseconds", L"setMinutes", L"setMonth", L"setSeconds", L"setTime", L"setTimeout", L"setUTCDate", L"setUTCFullYear"
                    , L"setUTCHours", L"setUTCMilliseconds", L"setUTCMinutes", L"setUTCMonth", L"setUTCSeconds", L"setYear", L"sin"
                    , L"slice", L"small", L"sort", L"split", L"sqrt", L"src", L"status", L"statusbar", L"stop", L"strike", L"style", L"sub", L"submit"
                    , L"substr", L"substring", L"suffixes", L"sup", L"tags", L"taint", L"taintEnabled", L"tan", L"target", L"text", L"title", L"toGMTString"
                    , L"toLocaleString", L"toLowerCase", L"toSource", L"toString", L"toUTCString", L"toUpperCase", L"toolbar", L"top"
                    , L"type", L"undefined", L"unescape", L"untaint", L"unwatch", L"userAgent", L"value", L"valueOf", L"visibility", L"vlinkColor", L"vspace"
                    , L"watch", L"width", L"window", L"write", L"writeln", L"zIndex"};
const String Keywords[62/*# range 0..61*/] = {L"abstract", L"boolean", L"break", L"byte", L"callee", L"case", L"catch", L"char", L"const", L"constructor", L"continue"
                    , L"debugger", L"default", L"delete", L"do", L"double", L"else", L"enum", L"export", L"extends", L"false", L"final", L"finally"
                    , L"float", L"for", L"function", L"goto", L"if", L"implements", L"import", L"in", L"instanceof", L"int", L"interface", L"long"
                    , L"NaN", L"native", L"new", L"null", L"package", L"private", L"protected", L"prototype", L"public", L"return", L"short", L"start"
                    , L"static", L"super", L"switch", L"synchronized", L"this", L"throw", L"throws", L"transient", L"true", L"try", L"typeof", L"var"
                    , L"void", L"while", L"with"};
const String Events[20/*# range 0..19*/] = {L"onAbort", L"onBlur", L"onChange", L"onClick", L"onDblClick", L"onError", L"onFocus", L"onKeyDown", L"onKeyPress"
                    , L"onKeyUp", L"onLoad", L"onMouseDown", L"onMouseMove", L"onMouseOut", L"onMouseOver", L"onMouseUp", L"onReset", L"onSelect"
                    , L"onSubmit", L"onUnload"};

bool __fastcall TSynJScriptSyn::IsKeyword(const String AKeyword)
{
	bool result = false;
	int First = 0;
	int Last = 0;
	int i = 0;
	int Compare = 0;
	First = 0;
	Last = 61 /*# High(Keywords) */;
	result = false;
	while(First <= Last)
	{
		i = (First + Last) >> 1;
		Compare = CompareStr(Keywords[i], AKeyword);
		if(Compare == 0)
		{
			result = true;
			break;
		}
		else
		{
			if(Compare < 0)
				First = i + 1;
			else
				Last = i - 1;
		}
	}
	return result;
}

bool __fastcall TSynJScriptSyn::IsEvent(const String AKeyword)
{
	bool result = false;
	int First = 0;
	int Last = 0;
	int i = 0;
	int Compare = 0;
	First = 0;
	Last = 19 /*# High(Events) */;
	result = false;
	while(First <= Last)
	{
		i = (First + Last) >> 1;
		Compare = CompareStr(Events[i], AKeyword);
		if(Compare == 0)
		{
			result = true;
			break;
		}
		else
		{
			if(Compare < 0)
				First = i + 1;
			else
				Last = i - 1;
		}
	}
	return result;
}

bool __fastcall TSynJScriptSyn::IsNonReserwedKeyWord(const String AKeyword)
{
	bool result = false;
	int First = 0;
	int Last = 0;
	int i = 0;
	int Compare = 0;
	First = 0;
	Last = 317 /*# High(NonReserwedKeyWords) */;
	result = false;
	while(First <= Last)
	{
		i = (First + Last) >> 1;
		Compare = CompareStr(NonReserwedKeyWords[i], AKeyword);
		if(Compare == 0)
		{
			result = true;
			break;
		}
		else
		{
			if(Compare < 0)
				First = i + 1;
			else
				Last = i - 1;
		}
	}
	return result;
}

__fastcall TSynJScriptSyn::TSynJScriptSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			fLiteralLevel(0),
			FTokenID(tkSymbol),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNonReservedKeyAttri(nullptr),
			fEventAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fSpecVarAttri(nullptr),
			fTemplateAttri(nullptr)
{
	fLiteralLevel = 0;
	FCaseSensitive = true;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterjscript__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fSpecVarAttri = new TSynHighlighterAttributes(SYNS_AttrSpecialVariable, SYNS_FriendlyAttrSpecialVariable);
	addAttribute(fSpecVarAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterjscript__1;
	addAttribute(fKeyAttri);
	fNonReservedKeyAttri = new TSynHighlighterAttributes(SYNS_AttrNonReservedKeyword, SYNS_FriendlyAttrNonReservedKeyword);
	addAttribute(fNonReservedKeyAttri);
	fEventAttri = new TSynHighlighterAttributes(SYNS_AttrEvent, SYNS_FriendlyAttrEvent);
	addAttribute(fEventAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fTemplateAttri = new TSynHighlighterAttributes(SYNS_AttrTemplate, SYNS_FriendlyAttrTemplate);
	addAttribute(fTemplateAttri);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterJScript;
}

void __fastcall TSynJScriptSyn::AndSymbolProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], Synhighlighterjscript__2))
		++Run;
}

void __fastcall TSynJScriptSyn::CommentProc()
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
				FRange = rsUnKnown;
				Run += 2;
				break;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
	}
}

void __fastcall TSynJScriptSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynJScriptSyn::IdentProc()
{
	while(IsIdentChar(fLine[Run]))
		++Run;
	if(IsEvent(GetToken()))
	{
		FTokenID = tkEvent;
	}
	else
	{
		if(IsKeyword(GetToken()))
		{
			FTokenID = tkKey;
		}
		else
		{
			if(IsNonReserwedKeyWord(GetToken()))
				FTokenID = tkNonReservedKey;
			else
				FTokenID = tkIdentifier;
		}
	}
}

void __fastcall TSynJScriptSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynJScriptSyn::LiteralsProc()
{
	FTokenID = tkString;
	FRange = rsLiteral;
	++Run;
	if(!IsLineEnd(Run))
		LiteralsRangeProc();
}

void __fastcall TSynJScriptSyn::LiteralsRangeProc()
{
	bool OK = false;
	bool myLit = false;
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
		default:
		FTokenID = tkString;
		do
		{
			OK = (fLine[Run] == L'`') && ((Run == 0) || (fLine[Pred(Run)] != L'\\'));
			myLit = (fLine[Run] == L'$') && (fLine[Run + 1] == L'{');
			if(myLit)
			{
				++fLiteralLevel;
				FRange = rsLiteralTemplate;
				break;
			}
			if(OK)
			{
				++Run;
				FRange = rsUnKnown;
				break;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
		break;
	}
}

void __fastcall TSynJScriptSyn::LiteralsTemplateRangeProc()
{
	bool OK = false;
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
		default:
		FTokenID = tkTemplate;
		if((fLine[Run] == L'$') && (fLine[Run + 1] == L'{'))
			Run += 2;
		do
		{
			OK = (fLine[Run] == L'}');
      /* end of Template = switch back to Literal */
			if(OK)
			{
				--fLiteralLevel;
				++Run;
				FRange = rsLiteral;
				break;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
		break;
	}
}

void __fastcall TSynJScriptSyn::MinusProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], Synhighlighterjscript__3))
		++Run;
}

void __fastcall TSynJScriptSyn::ModSymbolProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynJScriptSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynJScriptSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'.':
			case 97: case 98: case 99: case 100: case 101: case 102:
			case 65: case 66: case 67: case 68: case 69: case 70:
			case L'x':
			case L'X':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};

	auto IsHexChar = [&](int Run) -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 97: case 98: case 99: case 100: case 101: case 102:
			case 65: case 66: case 67: case 68: case 69: case 70:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	int idx1 = 0; // token[1]
	bool IsHex = false;
	FTokenID = tkNumber;
	IsHex = false;
	idx1 = Run;
	++Run;
	while(IsNumberChar())
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Succ(Run)] == L'.')
				goto label0;
			break;
			case 97: case 98: case 99: case 100: case 101: case 102:
			case 65: case 66: case 67: case 68: case 69: case 70:
			if(!IsHex)
				goto label1;
			break;
			case L'x':
			case L'X':
			{
				if((fLine[idx1] != L'0') || (Run > Succ(idx1)))
					goto label2;
				if(!IsHexChar(Succ(Run)))
					goto label3;
				IsHex = true;
			}
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label0:;
	label1:;
	label2:;
	label3:;
}

void __fastcall TSynJScriptSyn::OrSymbolProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], Synhighlighterjscript__4))
		++Run;
}

void __fastcall TSynJScriptSyn::PlusProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], Synhighlighterjscript__5))
		++Run;
}

void __fastcall TSynJScriptSyn::PointProc()
{
	FTokenID = tkSymbol;
	++Run;
	if((fLine[Run] == L'.') && (fLine[Run + 1] == L'.'))
		Run += 2;
}

void __fastcall TSynJScriptSyn::SlashProc()
{
	++Run;
  /* we should handle escaped slash \// */
	if((Run > 1) && (fLine[Run - 2] != L'\\') || (Run == 1))
		switch(fLine[Run])
		{
			case L'/':
			{
				FTokenID = tkComment;
				do
				{
					++Run;
				}
				while(!IsLineEnd(Run));
			}
			break;
			case L'*':
			{
				FTokenID = tkComment;
				FRange = rsAnsi;
				do
				{
					++Run;
					if((fLine[Run] == L'*') && (fLine[Run + 1] == L'/'))
					{
						FRange = rsUnKnown;
						Run += 2;
						break;
					}
				}
				while(!IsLineEnd(Run));
			}
			break;
			case L'=':
			{
				++Run;
				FTokenID = tkSymbol;
			}
			break;
			default:
			FTokenID = tkSymbol;
			break;
		}
}

void __fastcall TSynJScriptSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynJScriptSyn::StarProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynJScriptSyn::StringProc()
{
	WideChar l_strChar = L'\0';
	bool IsEscaped = false;
	FTokenID = tkString;
	l_strChar = fLine[Run];   // We could have '"' or #39
  /* we will handle escaped quotes */
	IsEscaped = false;
	if((fLine[Run + 1] == l_strChar) && (fLine[Run + 2] == l_strChar))
		Run += 2;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label4;
			case L'\\':
			IsEscaped = !IsEscaped;
			break;
			default:
			IsEscaped = false;
			break;
		}
		++Run;
	}
	while(!((fLine[Run] == l_strChar) && (fLine[Pred(Run)] != L'\\') && !IsEscaped));
	label4:;
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynJScriptSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynJScriptSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynJScriptSyn::Next()
{
	fTokenPos = Run;
	if(FRange == rsAnsi)
		CommentProc();
	else
	{
		if(FRange == rsLiteralTemplate)
			LiteralsTemplateRangeProc();
		else
		{
			if(FRange == rsLiteral)
				LiteralsRangeProc();
			else
				switch(fLine[Run])
				{
					case L'&':
					AndSymbolProc();
					break;
					case L'\x0d':
					CRProc();
					break;
					case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
					 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
					 case 85: case 86: case 87: case 88: case 89: case 90:
					case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
					 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
					 case 117: case 118: case 119: case 120: case 121: case 122:
					IdentProc();
					break;
					case L'_':
					UnderScoreProc();
					break;
					case L'\x0a':
					LFProc();
					break;
					case L'-':
					MinusProc();
					break;
					case L'%':
					ModSymbolProc();
					break;
					case L'\x00':
					NullProc();
					break;
					case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
					NumberProc();
					break;
					case L'|':
					OrSymbolProc();
					break;
					case L'+':
					PlusProc();
					break;
					case L'.':
					PointProc();
					break;
					case L'/':
					SlashProc();
					break;
					case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
					case L'\x0b':
					case L'\x0c':
					case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
					 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
					SpaceProc();
					break;
					case L'*':
					StarProc();
					break;
					case L'\"':
					case L'\x27':
					StringProc();
					break;
					case L'~':
					case L'{':
					case L'}':
					case L',':
					case L'(':
					case L')':
					case L'[':
					case L']':
					case L'<':
					case L'>':
					case L':':
					case L'?':
					case L';':
					case L'!':
					case L'=':
					SymbolProc();
					break;
					case L'`':
					LiteralsProc();
					break;
					default:
					UnknownProc();
					break;
				}
		}
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynJScriptSyn::GetDefaultAttribute(int Index)
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
		case SYN_ATTR_STRING:
		result = fStringAttri;
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

bool __fastcall TSynJScriptSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynJScriptSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynJScriptSyn::GetTokenID()
{
	TtkTokenKind result = tkSymbol;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynJScriptSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkNonReservedKey:
		result = fNonReservedKeyAttri;
		break;
		case tkEvent:
		result = fEventAttri;
		break;
		case tkNumber:
		result = fNumberAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkSpecVar:
		result = fSpecVarAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkTemplate:
		result = fTemplateAttri;
		break;
		case tkUnknown:
		result = fIdentifierAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynJScriptSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynJScriptSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynJScriptSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

bool __fastcall TSynJScriptSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterJScript;
	return result;
}

/*#static*/
String __fastcall TSynJScriptSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangJScript;
	return result;
}

String __fastcall TSynJScriptSyn::GetSampleSource()
{
	String result;
	result = L"// Syntax highlighting\x0d\x0a"
	           L"function printNumber()\x0d\x0a"
	           L"{\x0d\x0a"
	           L"  var number = 1234;\x0d\x0a"
	           L"  var x;\x0d\x0a"
	           L"  document.write(\"The number is \" + number);\x0d\x0a"
	           L"  for (var i = 0; i <= number; i++)\x0d\x0a"
	           L"  {\x0d\x0a"
	           L"    x++;\x0d\x0a"
	           L"    x--;\x0d\x0a"
	           L"    x += 1.0;\x0d\x0a"
	           L"  }\x0d\x0a"
	           L"  i += @; // illegal character\x0d\x0a"
	           L"}\x0d\x0a"
	           L"body.onLoad = printNumber;";
	return result;
}

/*#static*/
String __fastcall TSynJScriptSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangJScript;
	return result;
}

void __fastcall TSynJScriptSyn::UnderScoreProc()
{
	if((Run == 0) || !IsIdentChar(fLine[Run - 1]))
		FTokenID = tkSpecVar;
	else
		FTokenID = tkIdentifier;
	++Run;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

//++ CodeFolding

void __fastcall TSynJScriptSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	String CurLine;
	__int64 Line = 0;

	auto LineHasChar = [&](int Line, Char Character, int StartCol) -> bool 
	{
		bool result = false;
		int i = 0;
		int stop = 0;
		result = false;
		for(stop = CurLine.Length(), i = StartCol; i <= stop; i++)
		{
			if(CurLine[i] == Character)
        // Char must have proper highlighting (ignore stuff inside comments...)
			{
				if(GetHighlighterAttriAtRowCol(LinesToScan, Line, i) != fCommentAttri)
				{
					result = true;
					break;
				}
			}
		}
		return result;
	}; // faster than Pos!

	auto FindBraces = [&](int Line) -> bool 
	{
		bool result = false;
		int Col = 0;
		int stop = 0;
		result = false;
		for(stop = CurLine.Length(), Col = 1; Col <= stop; Col++)
		{
      // We've found a starting character
			if(CurLine[Col] == L'{')
        // Char must have proper highlighting (ignore stuff inside comments...)
			{
				if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Col) != fCommentAttri)
          // And ignore lines with both opening and closing chars in them
				{
					if(!LineHasChar(Line, L'}', Col + 1))
					{
						FoldRanges->StartFoldRange(Line + 1, 1);
						result = true;
					}
          // Skip until a newline
					break;
				}
			}
			else
			{
				if(CurLine[Col] == L'}')
				{
					if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Col) != fCommentAttri)
          // And ignore lines with both opening and closing chars in them
					{
						if(!LineHasChar(Line, L'{', Col + 1))
						{
							FoldRanges->StopFoldRange(Line + 1, 1);
							result = true;
						}
          // Skip until a newline
						break;
					}
				}
			}
		} // for Col
		return result;
	};

	auto FoldRegion = [&](int Line) -> bool 
	{
		bool result = false;
		String s;
		result = false;
		s = TrimLeft(CurLine);
		if(UpperCase(s.SubString(1, 9)) == L"//#REGION")
		{
			FoldRanges->StartFoldRange(Line + 1, FoldRegionType);
			result = true;
		}
		else
		{
			if(UpperCase(s.SubString(1, 12)) == L"//#ENDREGION")
			{
				FoldRanges->StopFoldRange(Line + 1, FoldRegionType);
				result = true;
			}
		}
		return result;
	};
	__int64 stop = 0;
	for(stop = ToLine, Line = FromLine; Line <= stop; Line++)
	{
    // Deal first with Multiline comments (Fold Type 2)
		if((TRangeState)(NativeInt)GetLineRange(LinesToScan, (int) Line) == rsAnsi)
		{
			if((TRangeState)(NativeInt)GetLineRange(LinesToScan, (int) (Line - 1)) != rsAnsi)
				FoldRanges->StartFoldRange((int) (Line + 1), 2);
			else
				FoldRanges->NoFoldInfo((int) (Line + 1));
			continue;
		}
		else
		{
			if((TRangeState)(NativeInt)GetLineRange(LinesToScan, (int) (Line - 1)) == rsAnsi)
			{
				FoldRanges->StopFoldRange((int) (Line + 1), 2);
				continue;
			}
		}
		CurLine = LinesToScan->Strings[Line];

    // Skip empty lines
		if(CurLine == L"")
		{
			FoldRanges->NoFoldInfo((int) (Line + 1));
			continue;
		}

    // Find Fold regions
		if(FoldRegion((int) Line))
			continue;

    // Find an braces on this line  (Fold Type 1)
		if(!FindBraces((int) Line))
			FoldRanges->NoFoldInfo((int) (Line + 1));
	} // while Line
}
//-- CodeFolding
static bool SynHighlighterJScript_Initialized = false;

void SynHighlighterJScript_initialization()
{
	if(SynHighlighterJScript_Initialized)
		return;
	
	SynHighlighterJScript_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynJScriptSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterJScript

