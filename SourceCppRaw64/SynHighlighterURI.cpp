
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterURI.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighteruri
{
#define Synhighlighteruri__0 (TSysCharSet() <<  \
          65 << 66 << 67 << 68 << 69 << 70 <<  \
          71 << 72 << 73 << 74 << 75 << 76 <<  \
          77 << 78 << 79 << 80 << 81 << 82 <<  \
          83 << 84 << 85 << 86 << 87 << 88 <<  \
          89 << 90 <<  \
          97 << 98 << 99 << 100 << 101 << 102 <<  \
          103 << 104 << 105 << 106 << 107 << 108 <<  \
          109 << 110 << 111 << 112 << 113 << 114 <<  \
          115 << 116 << 117 << 118 << 119 << 120 <<  \
          121 << 122)
#define Synhighlighteruri__1 (TFontStyles() << TFontStyle::fsUnderline)
#define Synhighlighteruri__2 (TFontStyles() << TFontStyle::fsUnderline)


const String Keywords[16/*# range 0..15*/] = {L"", L"http://", L"", L"https://", L"news:", L"gopher://", L"", L"prospero://", L"news://", L"www", L"nntp://", L"ftp://"
                    , L"wais://", L"", L"telnet://", L"mailto:"};

int __fastcall TSynURISyn::HashKey(PWideChar Str)
{
	int result = 0;
	result = 0;
	while(CharInSet((*Str), Synhighlighteruri__0))
	{
		result = (result * 3 + (int)(int((*Str)) / /*div*/ 9)) % 16;
		++Str;
	}
	if((*Str) == L':')
	{
		result = (result * 3 + (int)(int((*Str)) / /*div*/ 9)) % 16;
		++Str;
	}
	if((*Str) == L'/')
	{
		result = (result * 3 + (int)(int((*Str)) / /*div*/ 9)) % 16;
		++Str;
	}
	if((*Str) == L'/')
	{
		result = (result * 3 + (int)(int((*Str)) / /*div*/ 9)) % 16;
		++Str;
	}
	fStringLen = Str - fMayBeProtocol;
	return result;
}

void __fastcall TSynURISyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 15 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[11] = FuncFtp;
	fIdentFuncTable[5] = FuncGopher;
	fIdentFuncTable[1] = FuncHttp;
	fIdentFuncTable[3] = FuncHttps;
	fIdentFuncTable[15] = FuncMailto;
	fIdentFuncTable[4] = FuncNews;
	fIdentFuncTable[8] = FuncNews;
	fIdentFuncTable[10] = FuncNntp;
	fIdentFuncTable[7] = FuncProspero;
	fIdentFuncTable[14] = FuncTelnet;
	fIdentFuncTable[12] = FuncWais;
	fIdentFuncTable[9] = FuncWeb;
}

bool __fastcall TSynURISyn::IsCurrentToken(const String Token)
{
	bool result = false;
	int i = 0;
	PWideChar Temp = nullptr;
	Temp = fMayBeProtocol;
	if(Token.Length() == fStringLen)
	{
		int stop = 0;
		result = true;
		for(stop = fStringLen, i = 1; i <= stop; i++)
		{
			if((*Temp) != Token[i])
			{
				result = false;
				break;
			}
			++Temp;
		}
	}
	else
	result = false;
	return result;
}

TtkTokenKind __fastcall TSynURISyn::AltFunc(int key)
{
	TtkTokenKind result = tkNull;
	result = tkUnknown;
	return result;
}

__fastcall TSynURISyn::TSynURISyn(TComponent* AOwner)
 : inherited(AOwner),
			fMayBeProtocol(nullptr),
			FTokenID(tkNull),
			fIdentifierAttri(nullptr),
			fSpaceAttri(nullptr),
			fURIAttri(nullptr),
			fVisitedURIAttri(nullptr)
{
	FCaseSensitive = false;
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	fURIAttri = new TSynHighlighterAttributes(SYNS_AttrURI, SYNS_FriendlyAttrURI);
	fURIAttri->Foreground = clBlue;
	fURIAttri->Style = Synhighlighteruri__1;
	addAttribute(fURIAttri);
	fVisitedURIAttri = new TSynHighlighterAttributes(SYNS_AttrVisitedURI, SYNS_FriendlyAttrVisitedURI);
	fVisitedURIAttri->Foreground = clPurple;
	fVisitedURIAttri->Style = Synhighlighteruri__2;
	addAttribute(fVisitedURIAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterURI;
}

__fastcall TSynURISyn::~TSynURISyn()
{
	// inherited;
  //the other attributes are automatically freed because of AddAttribute()
	delete fSpaceAttri;
	delete fIdentifierAttri;
}

void __fastcall TSynURISyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynURISyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynURISyn::NullProc()
{
	if(Run < fLineLen + 1)
	{
		++Run;
		FTokenID = tkNullChar;
	}
	else
	FTokenID = tkNull;
}

void __fastcall TSynURISyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynURISyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynURISyn::Next()
{
	fTokenPos = Run;
	switch(fLine[Run])
	{
		case L'\x0d':
		CRProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'\x00':
		NullProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		ProtocolProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynURISyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_IDENTIFIER:
		result = fIdentifierAttri;
		break;
		case SYN_ATTR_WHITESPACE:
		result = fSpaceAttri;
		break;
		case SYN_ATTR_URI:
		result = fURIAttri;
		break;
		case SYN_ATTR_VISITEDURI:
		result = fVisitedURIAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynURISyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynURISyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	bool Visited = false;
	switch(GetTokenID())
	{
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkFtpLink:
		case tkGopherLink:
		case tkHttpLink:
		case tkHttpsLink:
		case tkMailtoLink:
		case tkNewsLink:
		case tkNntpLink:
		case tkProsperoLink:
		case tkTelnetLink:
		case tkWaisLink:
		case tkWebLink:
		{
			Visited = false;
			if(ASSIGNED(fAlreadyVisitedURI))
				Visited = fAlreadyVisitedURI(GetToken());
			if(Visited)
				result = fVisitedURIAttri;
			else
				result = fURIAttri;
		}
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

TtkTokenKind __fastcall TSynURISyn::GetTokenID()
{
	TtkTokenKind result = tkNull;
	result = FTokenID;
	return result;
}

int __fastcall TSynURISyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

/*#static*/
String __fastcall TSynURISyn::GetLanguageName()
{
	String result;
	result = SYNS_LangURI;
	return result;
}

String __fastcall TSynURISyn::GetSampleSource()
{
	String result;
	result = L"Universal Resource Identifier highlighting\x0d\x0a\x0d\x0a"
	           L"http://www.somewhere.org\x0d\x0a"
	           L"ftp://superhost.org/downloads/gems.zip\x0d\x0a"
	           L"www.w3c.org\x0d\x0a"
	           L"mailto:big@lebowski.edu\x0d\x0a"
	           L"douglas@adams.lod\x0d\x0a"
	           L"news:comp.lang.pascal.borland";
	return result;
}

bool __fastcall TSynURISyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterURI;
	return result;
}

bool __fastcall TSynURISyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	result = IsCharAlphaNumeric(AChar);
	return result;
}

void __fastcall TSynURISyn::SetAlreadyVisitedURIFunc(TAlreadyVisitedURIFunc Value)
{
	fAlreadyVisitedURI = Value;
}

void __fastcall TSynURISyn::SetURIAttri(TSynHighlighterAttributes* const Value)
{
	fURIAttri->Assign((TPersistent*) Value);
}

void __fastcall TSynURISyn::SetVisitedURIAttri(TSynHighlighterAttributes* const Value)
{
	fVisitedURIAttri->Assign((TPersistent*) Value);
}

void __fastcall TSynURISyn::ProtocolProc()
{
	int key = 0;
	if(IsValidEmailAddress())
		FTokenID = tkMailtoLink;
	else
	{
		fMayBeProtocol = fLine + Run;
		key = HashKey(fMayBeProtocol);
		Run += fStringLen;
		if(key <= 15)
			FTokenID = fIdentFuncTable[key](key);
		else
			FTokenID = tkUnknown;
	}
}

TtkTokenKind __fastcall TSynURISyn::FuncFtp(int key)
{
	TtkTokenKind result = tkNull;
	if(IsCurrentToken(Keywords[key]) && IsValidURI())
		result = tkFtpLink;
	else
		result = tkUnknown;
	return result;
}

TtkTokenKind __fastcall TSynURISyn::FuncGopher(int key)
{
	TtkTokenKind result = tkNull;
	if(IsCurrentToken(Keywords[key]) && IsValidURI())
		result = tkGopherLink;
	else
		result = tkUnknown;
	return result;
}

TtkTokenKind __fastcall TSynURISyn::FuncHttp(int key)
{
	TtkTokenKind result = tkNull;
	if(IsCurrentToken(Keywords[key]) && IsValidURI())
		result = tkHttpLink;
	else
		result = tkUnknown;
	return result;
}

TtkTokenKind __fastcall TSynURISyn::FuncHttps(int key)
{
	TtkTokenKind result = tkNull;
	if(IsCurrentToken(Keywords[key]) && IsValidURI())
		result = tkHttpsLink;
	else
		result = tkUnknown;
	return result;
}

TtkTokenKind __fastcall TSynURISyn::FuncMailto(int key)
{
	TtkTokenKind result = tkNull;
	if(IsCurrentToken(Keywords[key]) && IsValidURI())
		result = tkMailtoLink;
	else
		result = tkUnknown;
	return result;
}

TtkTokenKind __fastcall TSynURISyn::FuncNews(int key)
{
	TtkTokenKind result = tkNull;
	if(IsCurrentToken(Keywords[key]) && IsValidURI())
		result = tkNewsLink;
	else
		result = tkUnknown;
	return result;
}

TtkTokenKind __fastcall TSynURISyn::FuncNntp(int key)
{
	TtkTokenKind result = tkNull;
	if(IsCurrentToken(Keywords[key]) && IsValidURI())
		result = tkNntpLink;
	else
		result = tkUnknown;
	return result;
}

TtkTokenKind __fastcall TSynURISyn::FuncProspero(int key)
{
	TtkTokenKind result = tkNull;
	if(IsCurrentToken(Keywords[key]) && IsValidURI())
		result = tkProsperoLink;
	else
		result = tkUnknown;
	return result;
}

TtkTokenKind __fastcall TSynURISyn::FuncTelnet(int key)
{
	TtkTokenKind result = tkNull;
	if(IsCurrentToken(Keywords[key]) && IsValidURI())
		result = tkTelnetLink;
	else
		result = tkUnknown;
	return result;
}

TtkTokenKind __fastcall TSynURISyn::FuncWais(int key)
{
	TtkTokenKind result = tkNull;
	if(IsCurrentToken(Keywords[key]) && IsValidURI())
		result = tkWaisLink;
	else
		result = tkUnknown;
	return result;
}

TtkTokenKind __fastcall TSynURISyn::FuncWeb(int key)
{
	TtkTokenKind result = tkNull;
	if(IsCurrentToken(Keywords[key]) && IsValidWebLink())
		result = tkWebLink;
	else
		result = tkUnknown;
	return result;
}

bool __fastcall TSynURISyn::IsAlphaNum(WideChar AChar)
{
	bool result = false;
	result = IsCharAlphaNumeric(AChar);
	return result;
}

bool __fastcall TSynURISyn::IsMark(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'-':
		case L'_':
		case L'.':
		case L'!':
		case L'~':
		case L'*':
		case L'\'':
		case L'(':
		case L')':
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

bool __fastcall TSynURISyn::IsReserved(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L';':
		case L'/':
		case L'?':
		case L':':
		case L'@':
		case L'&':
		case L'=':
		case L'+':
		case L'$':
		case L',':
		case L'%':
		case L'#':
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

bool __fastcall TSynURISyn::IsUnreserved(WideChar AChar)
{
	bool result = false;
	result = IsAlphaNum(AChar) || IsMark(AChar);
	return result;
}

bool __fastcall TSynURISyn::IsURIChar(WideChar AChar)
{
	bool result = false;
	result = IsReserved(AChar) || IsUnreserved(AChar);
	return result;
}

bool __fastcall TSynURISyn::IsNeverAtEnd(WideChar AChar)
{
	bool result = false;
	result = (IsMark(AChar) && (AChar != L'\'')) || (IsReserved(AChar) && (AChar != L'/') && (AChar != L'$'));
	return result;
}

bool __fastcall TSynURISyn::IsEMailAddressChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'.':
		case L'_':
		case L'-':
		case L'@':
		result = true;
		break;
		default:
		result = IsAlphaNum(AChar);
		break;
	}
	return result;
}

bool __fastcall TSynURISyn::IsNeverAtEMailAddressEnd(WideChar AChar)
{
	bool result = false;
	result = (AChar == L'.') || (AChar == L'@');
	return result;
}

bool __fastcall TSynURISyn::IsValidEmailAddress()
{
	bool result = false;
	int StartPos = 0;
	int AtPos = 0;
	int DotPos = 0;
	StartPos = Run;
	AtPos = -1;
	DotPos = -1;
	while(IsEMailAddressChar(fLine[Run]))
	{
		if(fLine[Run] == L'@')
			AtPos = Run;
		else
		{
			if(fLine[Run] == L'.')
			{
				if((Run == StartPos) || (DotPos >= 0) && (DotPos == Run - 1))
					break;
				else
					DotPos = Run;
			}
		}
		++Run;
	}
	while((Run > StartPos) && (IsNeverAtEMailAddressEnd(fLine[Run - 1])))
		--Run;
	while((DotPos >= Run) || (DotPos > -1) && (fLine[DotPos] != L'.'))
		--DotPos;
	result = (StartPos < AtPos) && (AtPos < Run - 1) && (DotPos > AtPos + 1);
	if(!result)
		Run = StartPos;
	return result;
}

bool __fastcall TSynURISyn::IsValidURI()
{
	bool result = false;
	int ProtocolEndPos = 0;
	int DotPos = 0;

	auto IsRelativePath = [&]() -> bool 
	{
		bool result = false;
		result = (DotPos - 1 >= 0) && ((fLine[DotPos - 1] == L'/') && (fLine[DotPos + 2] == L'/')) || ((fLine[DotPos - 1] == L'\\') && (fLine[DotPos + 2] == L'\\'));
		return result;
	};
	ProtocolEndPos = Run;
	DotPos = -1;
	while(IsURIChar(fLine[Run]))
	{
		if(fLine[Run] == L'.')
		{
			if((DotPos >= 0) && (DotPos == Run - 1) && !IsRelativePath())
				break;
			else
				DotPos = Run;
		}
		++Run;
	}
	while((Run > ProtocolEndPos) && IsNeverAtEnd(fLine[Run - 1]))
		--Run;
	result = Run > ProtocolEndPos;
	return result;
}

bool __fastcall TSynURISyn::IsValidWebLink()
{
	bool result = false;
	int WWWEndPos = 0;
	int DotPos = 0;
	int SecondDotPos = 0;

	auto IsRelativePath = [&]() -> bool 
	{
		bool result = false;
		result = (DotPos - 1 >= 0) && ((fLine[DotPos - 1] == L'/') && (fLine[DotPos + 2] == L'/')) || ((fLine[DotPos - 1] == L'\\') && (fLine[DotPos + 2] == L'\\'));
		return result;
	};
	WWWEndPos = Run;
	DotPos = -1;
	SecondDotPos = -1;
	while(IsURIChar(fLine[Run]))
	{
		if(fLine[Run] == L'.')
		{
			if((DotPos >= 0) && (DotPos == Run - 1) && !IsRelativePath())
				break;
			else
			{
				DotPos = Run;
				if(SecondDotPos == -2)
					SecondDotPos = DotPos;
				if(SecondDotPos == -1)
					SecondDotPos = -2;
			}
		}
		++Run;
	}
	while((Run > WWWEndPos) && IsNeverAtEnd(fLine[Run - 1]))
		--Run;
	result = (Run > WWWEndPos) && (fLine[WWWEndPos] == L'.') && (SecondDotPos > WWWEndPos + 1) && (SecondDotPos < Run);
	return result;
}

/*#static*/
String __fastcall TSynURISyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangURI;
	return result;
}
static bool SynHighlighterURI_Initialized = false;

void SynHighlighterURI_initialization()
{
	if(SynHighlighterURI_Initialized)
		return;
	
	SynHighlighterURI_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynURISyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterURI

