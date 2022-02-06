
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterProgress.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace Synhighlighterhashentries;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace Vcl::Graphics;

namespace Synhighlighterprogress
{
#define SynHighlighterProgress__0 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)



int __fastcall TSynProgressSyn::HashKey(PWideChar Str)
{
	int result = 0;

	auto GetOrd = [&]() -> int 
	{
		int result = 0;
		switch((*Str))
		{
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			result = 1 + int((*Str)) - int(L'a');
			break;
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			result = 1 + int((*Str)) - int(L'A');
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			result = 27 + int((*Str)) - int(L'0');
			break;
			case L'_':
			result = 37;
			break;
			case L'-':
			result = 38;
			break;
			default:
			result = 0;
			break;
		}
		return result;
	};
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (3 * result + GetOrd()) & 0xFFFFFF;
		++Str;
	}
	result = result & 0x3FF;
	fStringLen = Str - fToIdent;
	return result;
}

TtkTokenKind __fastcall TSynProgressSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	TSynHashEntry* Entry = nullptr;
	fToIdent = Maybe;
	Entry = fHashList->Items[HashKey(Maybe)];
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
	result = tkIdentifier;
	return result;
}

void __fastcall TSynProgressSyn::DoAddKeyword(String AKeyword, int AKind)
{
	int HashValue = 0;
	HashValue = HashKey(ustr2pwchar(AKeyword));
	fHashList->Items[HashValue] = new TSynHashEntry(AKeyword, AKind);
}

__fastcall TSynProgressSyn::TSynProgressSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsNone),
			fCommentLevel(0),
			fIncludeLevel(0),
			fPreProcessorLevel(0),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fEventAttri(nullptr),
			fIdentifierAttri(nullptr),
			fIncludeAttri(nullptr),
			fKeyAttri(nullptr),
			fNonReservedKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fPreprocessorAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fDataTypeAttri(nullptr),
			fSymbolAttri(nullptr),
			fHashList(nullptr)
{
	FCaseSensitive = false;
	fHashList = new TSynHashEntryList();
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Foreground = clRed;
	addAttribute(fCommentAttri);
	fEventAttri = new TSynHighlighterAttributes(SYNS_AttrEvent, SYNS_FriendlyAttrEvent);
	fEventAttri->Foreground = clOlive;
	addAttribute(fEventAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	fIdentifierAttri->Foreground = clNavy;
	addAttribute(fIdentifierAttri);
	fIncludeAttri = new TSynHighlighterAttributes(SYNS_AttrInclude, SYNS_FriendlyAttrInclude);
	fIncludeAttri->Foreground = clPurple;
	addAttribute(fIncludeAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Foreground = clMaroon;
	addAttribute(fKeyAttri);
	fNonReservedKeyAttri = new TSynHighlighterAttributes(SYNS_AttrNonReservedKeyword, SYNS_FriendlyAttrNonReservedKeyword);
	fNonReservedKeyAttri->Foreground = clTeal;
	addAttribute(fNonReservedKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = clMaroon;
	addAttribute(fNumberAttri);
	fPreprocessorAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	fPreprocessorAttri->Foreground = clPurple;
	addAttribute(fPreprocessorAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fDataTypeAttri = new TSynHighlighterAttributes(SYNS_AttrDataType, SYNS_FriendlyAttrDataType);
	fDataTypeAttri->Foreground = clSilver;
	addAttribute(fDataTypeAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = clBlue;
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fDefaultFilter = SYNS_FilterProgress;
	EnumerateKeywords(int(tkKey), DefaultKeywords, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkNonReserved), DefaultNonReservedKeywords, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkEvent), DefaultEvents, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkDataType), DefaultDataTypes, IsIdentChar, DoAddKeyword);
	SetAttributesOnChange(DefHighlightChange);
}

__fastcall TSynProgressSyn::~TSynProgressSyn()
{
	delete fHashList;
	//# inherited::Destroy();
}


void __fastcall TSynProgressSyn::IdentProc()
{
	FTokenID = IdentKind(fLine + Run);
	Run += fStringLen;
}

void __fastcall TSynProgressSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynProgressSyn::NumberProc()
{
	PWideChar P = nullptr;
	FTokenID = tkNumber;
	P = &fLine[Run];
	do
	{
		++P;
	}
	while(!!CharInSet((*P), SynHighlighterProgress__0));
	Run = P - fLine;
}

void __fastcall TSynProgressSyn::PreprocessorDefinitionProc()
{
	PWideChar P = nullptr;
	FTokenID = tkPreprocessor;
	P = &fLine[Run];
	while((*P) != L'\x00')
	{
		switch((*P))
		{
			case L'~':
			if((*(P + 1)) == L'\x00')
				FRange = rsPreprocessorDef;
			break;
			default:
			  ;
			break;
		}
		++P;
	}
	Run = P - fLine;
}

void __fastcall TSynProgressSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynProgressSyn::StringProc()
{
	PWideChar P = nullptr;
	FTokenID = tkString;
	P = &fLine[Run];
	do
	{
		++P;
	}
	while(!(((*P) == L'\x00') || ((*P) == L'\"')));
	if((*P) == L'\"')
		++P;
	Run = P - fLine;
}

void __fastcall TSynProgressSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynProgressSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynProgressSyn::AsciiCharProc()
{
	PWideChar P = nullptr;
	FTokenID = tkString;
	P = &fLine[Run];
	do
	{
		++P;
	}
	while(!(((*P) == L'\x00') || ((*P) == L'\'')));
	if((*P) == L'\'')
		++P;
	Run = P - fLine;
}

void __fastcall TSynProgressSyn::SlashProc()
{
	PWideChar P = nullptr;
	P = &fLine[Run];
	++P;
	switch((*P))
	{
		case L'*':  /*c style comments*/
		{
			FTokenID = tkComment;
			FRange = rsComment;
			fCommentLevel = 1;
			++P;
			while(((*P) != L'\x00') && (FRange == rsComment))
			{
				switch((*P))
				{
					case L'*':
					{
						++P;
						if((*P) == L'/')
						{
							++P;
							--fCommentLevel;
							if(fCommentLevel == 0)
								FRange = rsNone;
						}
					}
					break;
					case L'/':
					{
						++P;
						if((*P) == L'*')
						{
							++P;
							++fCommentLevel; // Max 65535 commentlevels.
						}
					}
					break;
					default:
					++P;
					break;
				}
			}
		}
		break;  /*division*/
		default:
		FTokenID = tkSymbol;
		break;
	}
	Run = P - fLine;
}

void __fastcall TSynProgressSyn::CommentRangeProc()
{
	PWideChar P = nullptr;
	FTokenID = tkComment;
	P = &fLine[Run];
	if((*P) == L'\x00')
	{
		NullProc();
		return;
	}
	while(((*P) != L'\x00') && (FRange == rsComment))
	{
		switch((*P))
		{
			case L'*':
			{
				++P;
				if((*P) == L'/')
				{
					++P;
					--fCommentLevel;
					if(fCommentLevel == 0)
						FRange = rsNone;
				}
			}
			break;
			case L'/':
			{
				++P;
				if((*P) == L'*')
				{
					++P;
					++fCommentLevel;
				}
			}
			break;
			default:
			++P;
			break;
		}
	}
	Run = P - fLine;
}

void __fastcall TSynProgressSyn::IncludeRangeProc()
{
	PWideChar P = nullptr;
	FTokenID = tkInclude;
	P = &fLine[Run];
	if((*P) == L'\x00')
	{
		NullProc();
		return;
	}
	while((*P) != L'\x00')
	{
		switch((*P))
		{
			case L'}':
			{
				--fIncludeLevel;
				if(fIncludeLevel == 0)
				{
					FRange = rsNone;
					goto label0;
				}
				else
				++P;
			}
			break;
			default:
			++P;
			break;
		}
	}
	label0:;
	Run = P - fLine;
}

void __fastcall TSynProgressSyn::PreprocessorRangeProc()
{
	PWideChar P = nullptr;
	FTokenID = tkPreprocessor;
	P = &fLine[Run];
	if((*P) == L'\x00')
	{
		NullProc();
		return;
	}
	while(((*P) != L'\x00') && (FRange == rsPreprocessor))
	{
		switch((*P))
		{
			case L'{':
			++fPreProcessorLevel;
			break;
			case L'}':
			{
				--fPreProcessorLevel;
				if(fPreProcessorLevel == 0)
					FRange = rsNone;
			}
			break;
			default:
			  ;
			break;
		}
		++P;
	}
	Run = P - fLine;
}

void __fastcall TSynProgressSyn::PreprocessorDefinitionRangeProc()
{
	PWideChar P = nullptr;
	FTokenID = tkPreprocessor;
	P = &fLine[Run];
	if(Run == 0)
		FRange = rsNone;
	if((*P) == L'\x00')
	{
		NullProc();
		return;
	}
	while((*P) != L'\x00')
	{
		switch((*P))
		{
			case L'~':
			if((*(P + 1)) == L'\x00')
				FRange = rsPreprocessorDef;
			break;
			default:
			  ;
			break;
		}
		++P;
	}
	Run = P - fLine;
}

void __fastcall TSynProgressSyn::BraceOpenProc()
{
	PWideChar P = nullptr;

	auto LevelCount = [&]() -> int 
	{
		int result = 0;
		if(FTokenID == tkInclude)
			result = fIncludeLevel;
		else
			result = fPreProcessorLevel;
		return result;
	};
	P = &fLine[Run];
	++P;
	switch((*P))
	{
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		case L'_':
		FTokenID = tkInclude;
		break;
		case L'&':
		FTokenID = tkPreprocessor;
		break;
		default:
		FTokenID = tkUnknown;
		break;
	}
	switch(FTokenID)
	{
		case tkInclude:
		fIncludeLevel = 1;
		break;
		case tkPreprocessor:
		fPreProcessorLevel = 1;
		break;
		default:
		  ;
		break;
	}
	while(LevelCount() > 0)
	{
		switch((*P))
		{
			case L'\x00':
			{
				if(FTokenID == tkInclude)
					FRange = rsInclude;
				else
					FRange = rsPreprocessor;
				goto label1;
			}
			case L'}':
			switch(FTokenID)
			{
				case tkInclude:
				--fIncludeLevel;
				break;
				case tkPreprocessor:
				--fPreProcessorLevel;
				break;
				default:
				  ;
				break;
			}
			break;
			case L'{':
			switch(FTokenID)
			{
				case tkInclude:
				++fIncludeLevel;
				break;
				case tkPreprocessor:
				++fPreProcessorLevel;
				break;
				default:
				  ;
				break;
			}
			break;
			default:
			  ;
			break;
		}
		++P;
	}
	label1:;
	Run = P - fLine;
}

void __fastcall TSynProgressSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsInclude:
		IncludeRangeProc();
		break;
		case rsPreprocessor:
		PreprocessorRangeProc();
		break;
		case rsPreprocessorDef:
		PreprocessorDefinitionRangeProc();
		break;
		case rsComment:
		CommentRangeProc();
		break;
		default:
		switch(fLine[Run])
		{
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
			case L'_':
			IdentProc();
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			NumberProc();
			break;
			case L'\'':
			AsciiCharProc();
			break;
			case L'\"':
			StringProc();
			break;
			case L'{':
			BraceOpenProc();
			break;
			case L'+':
			case L'-':
			case L'*':
			case L'@':
			case L':':
			case L'=':
			case L'<':
			case L'>':
			case L'.':
			case L'^':
			case L'(':
			case L')':
			case L'[':
			case L']':
			SymbolProc();
			break;
			case L'&':
			PreprocessorDefinitionProc();
			break;
			case L'/':
			SlashProc();
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynProgressSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	result = nullptr;
	return result;
}

bool __fastcall TSynProgressSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynProgressSyn::GetRange()
{
	void* result = nullptr;
	TRangeInfo rng = {};
	rng.Range = (WORD) int(FRange);
	rng.Level = 0;
	switch(FRange)
	{
		case rsComment:
		rng.Level = (WORD) fCommentLevel;
		break;
		case rsInclude:
		rng.Level = (WORD) fIncludeLevel;
		break;
		case rsPreprocessor:
		rng.Level = (WORD) fPreProcessorLevel;
		break;
		default:
		  ;
		break;
	}
	result = rng.Ptr;
	return result;
}

TtkTokenKind __fastcall TSynProgressSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynProgressSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkEvent:
		result = fEventAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkInclude:
		result = fIncludeAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkNonReserved:
		result = fNonReservedKeyAttri;
		break;
		case tkNumber:
		result = fNumberAttri;
		break;
		case tkPreprocessor:
		result = fPreprocessorAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkDataType:
		result = fDataTypeAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkUnknown:
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynProgressSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynProgressSyn::ResetRange()
{
	FRange = rsNone;
	fCommentLevel = 0;
	fIncludeLevel = 0;
	fPreProcessorLevel = 0;
}

void __fastcall TSynProgressSyn::SetRange(void* Value)
{
	TRangeInfo rng = {};
	rng = *((TRangeInfo*) Value);
	FRange = ((TRangeState) rng.Range);
	fCommentLevel = 0;
	fIncludeLevel = 0;
	fPreProcessorLevel = 0;
	switch(FRange)
	{
		case rsComment:
		fCommentLevel = (int) rng.Level;
		break;
		case rsInclude:
		fIncludeLevel = (int) rng.Level;
		break;
		case rsPreprocessor:
		fPreProcessorLevel = (int) rng.Level;
		break;
		default:
		  ;
		break;
	}
}

bool __fastcall TSynProgressSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterProgress;
	return result;
}

bool __fastcall TSynProgressSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'-':
		case L'_':
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
String __fastcall TSynProgressSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangProgress;
	return result;
}

String __fastcall TSynProgressSyn::GetSampleSource()
{
	String result;
	result = L"&scoped-define FirstChar 65\x0d\x0a"
	           L"&scoped-define LastChar  90\x0d\x0a"
	           L"\x0d\x0a"
	           L"def var i as int no-undo.\x0d\x0a"
	           L"def var s as char no-undo.\x0d\x0a"
	           L"\x0d\x0a"
	           L"function GetRandomChar returns char (input SomeValue as int):\x0d\x0a"
	           L"  return chr(random({&FirstChar}, {&LastChar})).\x0d\x0a"
	           L"end.\x0d\x0a"
	           L"\x0d\x0a"
	           L"procedure ClearString:\x0d\x0a"
	           L"  def input-output param str as char no-undo.\x0d\x0a"
	           L"  str = \"\".\x0d\x0a"
	           L"end.\x0d\x0a"
	           L"\x0d\x0a"
	           L"run ClearString(input-output s).\x0d\x0a"
	           L"do i = 1 to 100:\x0d\x0a"
	           L"  s = s + GetRandomChar(17).\x0d\x0a"
	           L"end.\x0d\x0a"
	           L"display s.";
	return result;
}

/*#static*/
String __fastcall TSynProgressSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangProgress;
	return result;
}
static bool SynHighlighterProgress_Initialized = false;

void SynHighlighterProgress_initialization()
{
	if(SynHighlighterProgress_Initialized)
		return;
	
	SynHighlighterProgress_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynProgressSyn));
}
class SynHighlighterProgress_unit
{
public:
	SynHighlighterProgress_unit()
	{
		SynHighlighterProgress_initialization();
	}
};

SynHighlighterProgress_unit _SynHighlighterProgress_unit;

}  // namespace SynHighlighterProgress

