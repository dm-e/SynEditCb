
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterGalaxy.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditmiscclasses;
using namespace Syneditstrconst;
using namespace System::Types;

namespace Synhighlightergalaxy
{
#define Synhighlightergalaxy__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlightergalaxy__1 (TFontStyles() << TFontStyle::fsBold)



bool __fastcall TSynGalaxySyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'_':
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case L'#':
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

bool __fastcall TSynGalaxySyn::IsKeyword(const String AKeyword)
{
	bool result = false;
	int First = 0;
	int Last = 0;
	int I = 0;
	int Compare = 0;
	String Token;
	First = 0;
	Last = fKeyWords->Count - 1;
	result = false;
	Token = Sysutils::AnsiUpperCase(AKeyword);
	while(First <= Last)
	{
		I = (First + Last) >> 1;
		Compare = CompareStr(fKeyWords->Strings[I], Token);
		if(Compare == 0)
		{
			result = true;
			break;
		}
		else
		{
			if(Compare < 0)
				First = I + 1;
			else
				Last = I - 1;
		}
	}
	return result;
} /* IsKeyWord */

__fastcall TSynGalaxySyn::TSynGalaxySyn(TComponent* AOwner)
 : inherited(AOwner),
			fRange(rsUnKnown),
			FTokenID(tkComment),
			fMessageAttri(nullptr),
			fSymbolAttri(nullptr),
			fKeyAttri(nullptr),
			fCommentAttri(nullptr),
			fSpaceAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyWords(nullptr)
{
	fCaseSensitive = false;
	fKeyWords = new TStringList();
	((TStringList*) fKeyWords)->Sorted = true;
	((TStringList*) fKeyWords)->Duplicates = System::Types::dupIgnore;
	((TStringList*) fKeyWords)->CommaText = L"#end,#galaxy,a,anonymous,autounload,b,battleprotocol,c,cap,cargo,col,"
	           L"compress,d,drive,e,emp,f,fleet,fleettables,g,galaxytv,gplus,groupforecast,"
	           L"h,i,j,l,m,machinereport,mat,n,namecase,no,o,options,p,planetforecast,"
	           L"prodtable,produce,q,r,routesforecast,s,send,shields,shiptypeforecast,"
	           L"sortgroups,t,twocol,u,underscores,v,w,war,weapons,x,y,z";
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlightergalaxy__0;
	AddAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlightergalaxy__1;
	AddAttribute(fKeyAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fMessageAttri = new TSynHighlighterAttributes(SYNS_AttrMessage, SYNS_FriendlyAttrMessage);
	AddAttribute(fMessageAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	AddAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterGalaxy;
} /* Create */

__fastcall TSynGalaxySyn::~TSynGalaxySyn()
{
	delete fKeyWords;
	//# inherited::Destroy();
} /* Destroy */

void __fastcall TSynGalaxySyn::MessageStyleProc()
{
	FTokenID = tkMessage;
	switch(fLine[Run])
	{
		case L'\x00':
		{
			NullProc();
			return;
		}
		case L'\x0a':
		{
			LFProc();
			return;
		}
		case L'\x0d':
		{
			CRProc();
			return;
		}
		default:
		  ;
		break;
	}
	if((Run == 0) && (fLine[Run] == L'@'))
	{
		fRange = rsUnKnown;
		++Run;
	}
	else
	{
		while(fLine[Run] != L'\x00')
			++Run;
	}
}

void __fastcall TSynGalaxySyn::PointCommaProc()
{
	FTokenID = tkComment;
	fRange = rsUnKnown;
	do
	{
		++Run;
	}
	while(!(fLine[Run] == L'\x00'));
}

void __fastcall TSynGalaxySyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynGalaxySyn::IdentProc()
{
	while(IsIdentChar(fLine[Run]))
		++Run;
	if(IsKeyword(GetToken()))
		FTokenID = tkKey;
	else
		FTokenID = tkIdentifier;
}

void __fastcall TSynGalaxySyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynGalaxySyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynGalaxySyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynGalaxySyn::StringProc()
{
	if((Run == 0) && (FTokenID != tkMessage))
	{
		FTokenID = tkMessage;
		fRange = rsMessageStyle;
	}
	++Run;
}

void __fastcall TSynGalaxySyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynGalaxySyn::Next()
{
	fTokenPos = Run;
	if(fRange == rsMessageStyle)
		MessageStyleProc();
	else
		switch(fLine[Run])
		{
			case L';':
			PointCommaProc();
			break;
			case L'\x0d':
			CRProc();
			break;
			case L'#':
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			case L'_':
			IdentProc();
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
			case L'@':
			StringProc();
			break;
			default:
			UnknownProc();
			break;
		}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynGalaxySyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynGalaxySyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynGalaxySyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) fRange);
	return result;
}

TtkTokenKind __fastcall TSynGalaxySyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynGalaxySyn::GetTokenAttribute()
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
		case tkMessage:
		result = fMessageAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
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

int __fastcall TSynGalaxySyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynGalaxySyn::ResetRange()
{
	fRange = rsUnKnown;
}

void __fastcall TSynGalaxySyn::SetRange(void* Value)
{
	fRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynGalaxySyn::SetKeyWords(TStrings* const Value)
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
	fKeyWords->Assign((TPersistent*) Value);
	DefHighlightChange(nullptr);
}

bool __fastcall TSynGalaxySyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterGalaxy;
	return result;
}

/*#static*/
String __fastcall TSynGalaxySyn::GetLanguageName()
{
	String result;
	result = SYNS_LangGalaxy;
	return result;
}

bool __fastcall TSynGalaxySyn::LoadFromRegistry(HKEY RootKey, String Key)
{
	bool result = false;
	TBetterRegistry* r = nullptr;
	r = new TBetterRegistry();
	try
	{
		r->RootKey = RootKey;
		if(r->OpenKeyReadOnly(Key))
		{
			if(r->ValueExists(L"KeyWords"))
				KeyWords->Text = r->ReadString(L"KeyWords");
			result = inherited::LoadFromRegistry(RootKey, Key);
		}
		else
		result = false;
	}
	__finally
	{
		delete r;
	}
	return result;
}

bool __fastcall TSynGalaxySyn::SaveToRegistry(HKEY RootKey, String Key)
{
	bool result = false;
	TBetterRegistry* r = nullptr;
	r = new TBetterRegistry();
	try
	{
		r->RootKey = RootKey;
		if(r->OpenKey(Key, true))
		{
			r->WriteString(L"KeyWords", KeyWords->Text);
			result = inherited::SaveToRegistry(RootKey, Key);
		}
		else
		result = false;
	}
	__finally
	{
		delete r;
	}
	return result;
}

/*#static*/
String __fastcall TSynGalaxySyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangGalaxy;
	return result;
}

	static bool SynHighlighterGalaxy_Initialized = false;
	
	void SynHighlighterGalaxy_initialization()
	{
		if(SynHighlighterGalaxy_Initialized)
			return;
		
		SynHighlighterGalaxy_Initialized = true;
		
		RegisterPlaceableHighlighter(__classid(TSynGalaxySyn));
	}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterGalaxy

