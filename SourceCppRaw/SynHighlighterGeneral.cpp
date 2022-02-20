
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterGeneral.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Uitypes;

namespace Synhighlightergeneral
{
#define SynHighlighterGeneral__0 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterGeneral__1 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterGeneral__2 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)



bool __fastcall TSynGeneralSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	int i = 0;
	int stop = 0;
	result = false;
	for(stop = (int) fIdentChars.Length(), i = 1; i <= stop; i++)
	{
		if(AChar == fIdentChars[i])
		{
			result = true;
			return result;
		}
	}
	return result;
}

bool __fastcall TSynGeneralSyn::IsKeyword(const String AKeyword)
{
	bool result = false;
	int First = 0;
	int Last = 0;
	int i = 0;
	int Compare = 0;
	String Token;
	First = 0;
	Last = fKeywords->Count - 1;
	result = false;
	Token = Sysutils::AnsiUpperCase(AKeyword);
	while(First <= Last)
	{
		i = (First + Last) >> 1;
		Compare = CompareText(fKeywords->Strings[i], Token);
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
} /* IsKeyWord */

bool __fastcall TSynGeneralSyn::IsWordBreakChar(WideChar AChar)
{
	bool result = false;
	result = inherited::IsWordBreakChar(AChar) && !IsIdentChar(AChar);
	return result;
}

__fastcall TSynGeneralSyn::TSynGeneralSyn(TComponent* AOwner)
 : inherited(AOwner),
			fIdentChars(cDefaultIdentChars),
			FRange(rsUnKnown),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fPreprocessorAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fKeywords(nullptr),
			fStringDelim(sdSingleQuote),
			fDetectPreprocessor(false),
			FStringMultiLine(false)
{
	fKeywords = new TStringList();
	((TStringList*) fKeywords)->Sorted = true;
	((TStringList*) fKeywords)->Duplicates = System::Classes::dupIgnore;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = SynHighlighterGeneral__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = SynHighlighterGeneral__1;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fPreprocessorAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	addAttribute(fPreprocessorAttri);
	SetAttributesOnChange(DefHighlightChange);
	fStringDelim = sdSingleQuote;
} /* Create */

__fastcall TSynGeneralSyn::~TSynGeneralSyn()
{
	delete fKeywords;
	//# inherited::Destroy();
}
 /* Destroy */

void __fastcall TSynGeneralSyn::AnsiProc()
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
		default:
		FTokenID = tkComment;
		do
		{
			if((fLine[Run] == L'*') && (fLine[Run + 1] == L')'))
			{
				FRange = rsUnKnown;
				Run += 2;
				break;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
		break;
	}
}

void __fastcall TSynGeneralSyn::PasStyleProc()
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
		default:
		FTokenID = tkComment;
		do
		{
			if(fLine[Run] == L'}')
			{
				FRange = rsUnKnown;
				++Run;
				break;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
		break;
	}
}

void __fastcall TSynGeneralSyn::CStyleProc()
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
		default:
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
		break;
	}
}

void __fastcall TSynGeneralSyn::AsciiCharProc()
{
	if(fDetectPreprocessor)
	{
		FTokenID = tkPreprocessor;
		do
		{
			++Run;
		}
		while(!IsLineEnd(Run));
	}
	else
	{
		FTokenID = tkString;
		do
		{
			++Run;
		}
		while(!!CharInSet(fLine[Run], SynHighlighterGeneral__2));
	}
}

void __fastcall TSynGeneralSyn::BraceOpenProc()
{
	if(fComments.Contains(csPasStyle))
	{
		FTokenID = tkComment;
		FRange = rsPasStyle;
		++Run;
		while(fLine[Run] != L'\x00')
			switch(fLine[Run])
			{
				case L'}':
				{
					FRange = rsUnKnown;
					++Run;
					goto label0;
				}
				case L'\x0a':
				goto label1;
				case L'\x0d':
				goto label2;
				default:
				++Run;
				break;
			}
		label0:;
		label1:;
		label2:;
	}
	else
	{
		++Run;
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynGeneralSyn::PointCommaProc()
{
	if((fComments.Contains(csAsmStyle)) || (fComments.Contains(csBasStyle)))
	{
		FTokenID = tkComment;
		FRange = rsUnKnown;
		++Run;
		while(fLine[Run] != L'\x00')
		{
			FTokenID = tkComment;
			++Run;
		}
	}
	else
	{
		++Run;
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynGeneralSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynGeneralSyn::IdentProc()
{
	while(IsIdentChar(fLine[Run]))
		++Run;
	if(IsKeyword(GetToken()))
		FTokenID = tkKey;
	else
		FTokenID = tkIdentifier;
}

void __fastcall TSynGeneralSyn::IntegerProc()
{

	auto IsIntegerChar = [&]() -> bool 
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
	++Run;
	FTokenID = tkNumber;
	while(IsIntegerChar())
		++Run;
}

void __fastcall TSynGeneralSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynGeneralSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynGeneralSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'.':
			case L'e':
			case L'E':
			case L'x':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	++Run;
	FTokenID = tkNumber;
	while(IsNumberChar())
	{
		switch(fLine[Run])
		{
			case L'x': // handle C style hex numbers
			{
				IntegerProc();
				goto label3;
			}
			case L'.':
			if(fLine[Run + 1] == L'.')
				goto label4;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label3:;
	label4:;
}

void __fastcall TSynGeneralSyn::RoundOpenProc()
{
	++Run;
	if(fComments.Contains(csAnsiStyle))
	{
		switch(fLine[Run])
		{
			case L'*':
			{
				FTokenID = tkComment;
				FRange = rsAnsi;
				++Run;
				while(fLine[Run] != L'\x00')
					switch(fLine[Run])
					{
						case L'*':
						if(fLine[Run + 1] == L')')
						{
							FRange = rsUnKnown;
							Run += 2;
							goto label5;
						}
						else
						++Run;
						break;
						case L'\x0a':
						goto label6;
						case L'\x0d':
						goto label7;
						default:
						++Run;
						break;
					}
				label5:;
				label6:;
				label7:;
			}
			break;
			case L'.':
			{
				++Run;
				FTokenID = tkSymbol;
			}
			break;
			default:
			{
				FTokenID = tkSymbol;
			}
			break;
		}
	}
	else
	FTokenID = tkSymbol;
}

void __fastcall TSynGeneralSyn::SlashProc()
{
	++Run;
	switch(fLine[Run])
	{
		case L'/':
		{
			if(fComments.Contains(csCPPStyle))
			{
				FTokenID = tkComment;
				++Run;
				while(fLine[Run] != L'\x00')
				{
					switch(fLine[Run])
					{
						case L'\x0a':
						case L'\x0d':
						goto label8;
						default:
						  ;
						break;
					}
					++Run;
				}
				label8:;
			}
			else
			FTokenID = tkSymbol;
		}
		break;
		case L'*':
		{
			if(fComments.Contains(csCStyle))
			{
				FTokenID = tkComment;
				FRange = rsCStyle;
				++Run;
				while(fLine[Run] != L'\x00')
					switch(fLine[Run])
					{
						case L'*':
						if(fLine[Run + 1] == L'/')
						{
							FRange = rsUnKnown;
							Run += 2;
							goto label9;
						}
						else
						++Run;
						break;
						case L'\x0a':
						case L'\x0d':
						goto label10;
						default:
						++Run;
						break;
					}
				label9:;
				label10:;
			}
			else
			FTokenID = tkSymbol;
		}
		break;
		default:
		FTokenID = tkSymbol;
		break;
	}
}

void __fastcall TSynGeneralSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynGeneralSyn::StringProc()
{
	WideChar Delim = L'\0';
	FTokenID = tkString;
	if(IsStringDelim(fLine[Run + 1]) && IsStringDelim(fLine[Run + 2]))
		Run += 2;
	Delim = fLine[Run];
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			goto label11;
			case L'\x0a':
			case L'\x0d':
			if(!StringMultiLine)
				goto label12;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == Delim));
	label11:;
	label12:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynGeneralSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynGeneralSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsAnsi:
		AnsiProc();
		break;
		case rsPasStyle:
		PasStyleProc();
		break;
		case rsCStyle:
		CStyleProc();
		break;
		default:
		if(IsStringDelim(fLine[Run]))
			StringProc();
		else
			switch(fLine[Run])
			{
				case L'#':
				AsciiCharProc();
				break;
				case L'{':
				BraceOpenProc();
				break;
				case L';':
				PointCommaProc();
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
				case L'_':
				IdentProc();
				break;
				case L'$':
				IntegerProc();
				break;
				case L'\x0a':
				LFProc();
				break;
				case L'\x00':
				NullProc();
				break;
				case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
				NumberProc();
				break;
				case L'(':
				RoundOpenProc();
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
				default:
				UnknownProc();
				break;
			}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynGeneralSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynGeneralSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynGeneralSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynGeneralSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

// GetCharBeforeToken
//

WideChar __fastcall TSynGeneralSyn::GetCharBeforeToken(int Offset/*# = -1*/)
{
	WideChar result = L'\0';
	if(fTokenPos + Offset >= 0)
		result = fLine[fTokenPos + Offset];
	else
		result = L'\x00';
	return result;
}

// GetCharAfterToken
//

WideChar __fastcall TSynGeneralSyn::GetCharAfterToken(int Offset/*# = 1*/)
{
	WideChar result = L'\0';
	result = fLine[fTokenPos + Offset];
	return result;
}

TSynHighlighterAttributes* __fastcall TSynGeneralSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
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
		case tkNumber:
		result = fNumberAttri;
		break;
		case tkPreprocessor:
		result = fPreprocessorAttri;
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
		case tkUnknown:
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	if(ASSIGNED(fOnGetTokenAttribute))
		fOnGetTokenAttribute(result);
	return result;
}

int __fastcall TSynGeneralSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynGeneralSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynGeneralSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(int)Value;
}

void __fastcall TSynGeneralSyn::SetKeyWords(TStrings* const Value)
{
	int i = 0;
	if(Value != nullptr)
	{
		int stop = 0;
		Value->BeginUpdate();
		for(stop = Value->Count - 1, i = 0; i <= stop; i++)
		{
			Value->Strings[i] = Sysutils::AnsiUpperCase(Value->Strings[i]);
		}
		Value->EndUpdate();
	}
	((TStringList*) fKeywords)->Sorted = false;
	fKeywords->Assign(Value);
	((TStringList*) fKeywords)->Sorted = true;
	DefHighlightChange(nullptr);
}

void __fastcall TSynGeneralSyn::SetComments(TCommentStyles Value)
{
	if(fComments != Value)
	{
		fComments = Value;
		DefHighlightChange(this);
	}
}

/*#static*/
String __fastcall TSynGeneralSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangGeneral;
	return result;
}

bool __fastcall TSynGeneralSyn::LoadFromRegistry(HKEY RootKey, String key)
{
	bool result = false;
	TBetterRegistry* R = nullptr;
	R = new TBetterRegistry();
	try
	{
		R->RootKey = RootKey;
		if(R->OpenKeyReadOnly(key))
		{
			if(R->ValueExists(L"KeyWords"))
				Keywords->Text = R->ReadString(L"KeyWords");
			result = inherited::LoadFromRegistry(RootKey, key);
		}
		else
		result = false;
	}
	__finally
	{
		delete R;
	}
	return result;
}

bool __fastcall TSynGeneralSyn::SaveToRegistry(HKEY RootKey, String key)
{
	bool result = false;
	TBetterRegistry* R = nullptr;
	R = new TBetterRegistry();
	try
	{
		R->RootKey = RootKey;
		if(R->OpenKey(key, true))
		{
			R->WriteString(L"KeyWords", Keywords->Text);
			result = inherited::SaveToRegistry(RootKey, key);
		}
		else
		result = false;
	}
	__finally
	{
		delete R;
	}
	return result;
}

TStringDelim __fastcall TSynGeneralSyn::GetStringDelim()
{
	TStringDelim result = sdSingleQuote;
	result = fStringDelim;
	return result;
}

void __fastcall TSynGeneralSyn::SetStringDelim(TStringDelim Value)
{
	fStringDelim = Value;
}

String __fastcall TSynGeneralSyn::GetIdentifierChars()
{
	String result;
	result = fIdentChars;
	return result;
}

void __fastcall TSynGeneralSyn::SetIdentifierChars(const String Value)
{
	fIdentChars = Value;
}

bool __fastcall TSynGeneralSyn::StoreIdentChars()
{
	bool result = false;
	result = (fIdentChars != cDefaultIdentChars);
	return result;
}

void __fastcall TSynGeneralSyn::SetDetectPreprocessor(bool Value)
{
	if(Value != fDetectPreprocessor)
	{
		fDetectPreprocessor = Value;
		DefHighlightChange(this);
	}
}

/*#static*/
String __fastcall TSynGeneralSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangGeneral;
	return result;
}

// IsStringDelim
//

bool __fastcall TSynGeneralSyn::IsStringDelim(WideChar AChar)
{
	bool result = false;
	switch(fStringDelim)
	{
		case sdSingleQuote:
		result = (AChar == L'\'');
		break;
		case sdDoubleQuote:
		result = (AChar == L'\"');
		break;
		default:
		result = (AChar == L'\'') || (AChar == L'\"');
		break;
	}
	return result;
}
static bool SynHighlighterGeneral_Initialized = false;

void SynHighlighterGeneral_initialization()
{
	if(SynHighlighterGeneral_Initialized)
		return;
	
	SynHighlighterGeneral_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynGeneralSyn));
}
class SynHighlighterGeneral_unit
{
public:
	SynHighlighterGeneral_unit()
	{
		SynHighlighterGeneral_initialization();
	}
};

SynHighlighterGeneral_unit _SynHighlighterGeneral_unit;

}  // namespace SynHighlighterGeneral

