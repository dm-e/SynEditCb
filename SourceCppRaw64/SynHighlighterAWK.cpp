
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterAWK.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterawk
{
#define Synhighlighterawk__0 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterawk__1 (TSysCharSet() <<  \
          97 << 98 << 99 << 100 << 101 << 102 <<  \
          103 << 104 << 105 << 106 << 107 << 108 <<  \
          109 << 110 << 111 << 112 << 113 << 114 <<  \
          115 << 116 << 117 << 118 << 119 << 120 <<  \
          121 << 122 <<  \
          65 << 66 << 67 << 68 << 69 << 70 <<  \
          71 << 72 << 73 << 74 << 75 << 76 <<  \
          77 << 78 << 79 << 80 << 81 << 82 <<  \
          83 << 84 << 85 << 86 << 87 << 88 <<  \
          89 << 90)
#define Synhighlighterawk__2 (TSysCharSet() <<  \
          0 << 1 << 2 << 3 << 4 << 5 <<  \
          6 << 7 << 8 << 9 << 10 << 11 <<  \
          12 << 13 << 14 << 15 << 16 << 17 <<  \
          18 << 19 << 20 << 21 << 22 << 23 <<  \
          24 << 25 << 26 << 27 << 28 << 29 <<  \
          30 << 31 << 32 << ';')
#define Synhighlighterawk__3 (TSysCharSet() <<  \
										0 << 1 << 2 << 3 << 4 << 5 <<  \
										6 << 7 << 8 << 9 << 10 << 11 <<  \
										12 << 13 << 14 << 15 << 16 << 17 <<  \
										18 << 19 << 20 << 21 << 22 << 23 <<  \
										24 << 25 << 26 << 27 << 28 << 29 <<  \
										30 << 31)
#define Synhighlighterawk__4 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterawk__5 (TSysCharSet() << '+' << '=')
#define Synhighlighterawk__6 (TSysCharSet() << '-' << '=')
#define Synhighlighterawk__7 (TSysCharSet() << '=' << '~')
#define Synhighlighterawk__8 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterawk__9 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterawk__10 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterawk__11 (TFontStyles() << TFontStyle::fsBold)



void __fastcall TSynAWKSyn::MakeSyntaxList()
{
	/*# with AWKSyntaxList do */
	{
		auto with0 = AWKSyntaxList;
		with0->Sorted = true;

    /* *** Preferably sort and put previously. *** */
		with0->AddObject(L"ARGC", ((TObject*) tkSysVar));
		with0->AddObject(L"ARGIND", ((TObject*) tkSysVar)); /* GNU Extention */
		with0->AddObject(L"ARGV", ((TObject*) tkSysVar));
		with0->AddObject(L"atan2", ((TObject*) tkInterFunc));
		with0->AddObject(L"BEGIN", ((TObject*) tkKey));
		with0->AddObject(L"break", ((TObject*) tkKey));
		with0->AddObject(L"close", ((TObject*) tkInterFunc));
		with0->AddObject(L"continue", ((TObject*) tkKey));
		with0->AddObject(L"CONVFMT", ((TObject*) tkSysVar)); /* POSIX Extention */
		with0->AddObject(L"cos", ((TObject*) tkInterFunc));
		with0->AddObject(L"delete", ((TObject*) tkInterFunc));
		with0->AddObject(L"do", ((TObject*) tkKey));
		with0->AddObject(L"else", ((TObject*) tkKey));
		with0->AddObject(L"END", ((TObject*) tkKey));
		with0->AddObject(L"ENVIRON", ((TObject*) tkSysVar));
		with0->AddObject(L"ERRNO", ((TObject*) tkSysVar)); /* GNU Extention */
		with0->AddObject(L"exit", ((TObject*) tkKey));
		with0->AddObject(L"exp", ((TObject*) tkInterFunc));
		with0->AddObject(L"FIELDWIDTH", ((TObject*) tkSysVar)); /* GNU Extention */
		with0->AddObject(L"FILENAME", ((TObject*) tkSysVar));
		with0->AddObject(L"FNR", ((TObject*) tkSysVar));
		with0->AddObject(L"for", ((TObject*) tkKey));
		with0->AddObject(L"FS", ((TObject*) tkSysVar));
		with0->AddObject(L"function", ((TObject*) tkKey));
		with0->AddObject(L"getline", ((TObject*) tkKey));
		with0->AddObject(L"gsub", ((TObject*) tkInterFunc));
		with0->AddObject(L"if", ((TObject*) tkKey));
		with0->AddObject(L"IGNORECASE", ((TObject*) tkSysVar));
		with0->AddObject(L"index", ((TObject*) tkInterFunc));
		with0->AddObject(L"int", ((TObject*) tkInterFunc));
		with0->AddObject(L"jindex", ((TObject*) tkInterFunc)); /* jgawk */
		with0->AddObject(L"jlength", ((TObject*) tkInterFunc)); /* jgawk */
		with0->AddObject(L"jsubstr", ((TObject*) tkInterFunc)); /* jgawk */
		with0->AddObject(L"length", ((TObject*) tkInterFunc));
		with0->AddObject(L"log", ((TObject*) tkInterFunc));
		with0->AddObject(L"match", ((TObject*) tkInterFunc));
		with0->AddObject(L"next", ((TObject*) tkUnknown)); /* & next file (GNU Extention) */
		with0->AddObject(L"NF", ((TObject*) tkSysVar));
		with0->AddObject(L"NR", ((TObject*) tkSysVar));
		with0->AddObject(L"OFMT", ((TObject*) tkSysVar));
		with0->AddObject(L"OFS", ((TObject*) tkSysVar));
		with0->AddObject(L"ORS", ((TObject*) tkSysVar));
		with0->AddObject(L"print", ((TObject*) tkKey));
		with0->AddObject(L"printf", ((TObject*) tkInterFunc));
		with0->AddObject(L"rand", ((TObject*) tkInterFunc));
		with0->AddObject(L"return", ((TObject*) tkKey));
		with0->AddObject(L"RLENGTH", ((TObject*) tkSysVar));
		with0->AddObject(L"RS", ((TObject*) tkSysVar));
		with0->AddObject(L"RSTART", ((TObject*) tkSysVar));
		with0->AddObject(L"sin", ((TObject*) tkInterFunc));
		with0->AddObject(L"split", ((TObject*) tkInterFunc));
		with0->AddObject(L"sprintf", ((TObject*) tkInterFunc));
		with0->AddObject(L"sqrt", ((TObject*) tkInterFunc));
		with0->AddObject(L"srand", ((TObject*) tkInterFunc));
		with0->AddObject(L"strftime", ((TObject*) tkInterFunc)); /* GNU Extention */
		with0->AddObject(L"sub", ((TObject*) tkInterFunc));
		with0->AddObject(L"SUBSEP", ((TObject*) tkSysVar));
		with0->AddObject(L"substr", ((TObject*) tkInterFunc));
		with0->AddObject(L"system", ((TObject*) tkInterFunc));
		with0->AddObject(L"systime", ((TObject*) tkInterFunc)); /* GNU Extention */
		with0->AddObject(L"tolower", ((TObject*) tkInterFunc));
		with0->AddObject(L"toupper", ((TObject*) tkInterFunc));
		with0->AddObject(L"while", ((TObject*) tkKey));
	}
}

void __fastcall TSynAWKSyn::BraceProc()
{
	FTokenID = tkIdentifier;
	++Run;
}

void __fastcall TSynAWKSyn::NumberProc()
{
	FTokenID = tkNumber;
	++Run;
	while(CharInSet(fLine[Run], Synhighlighterawk__0))
		++Run;
}

void __fastcall TSynAWKSyn::IdentProc()
{
	int i = 0;
	int idx = 0;
	String s;
	i = Run;
	while(CharInSet(fLine[i], Synhighlighterawk__1))
		++i;
	s.SetLength(i - Run);
	StrLCopy(ustr2pwchar(s), fLine + Run, (unsigned int) (i - Run));
	Run = i;
	if(AWKSyntaxList->Find(s, idx) && (AWKSyntaxList->Strings[idx] == s))
	{
		FTokenID = (TtkTokenKind) (NativeInt) AWKSyntaxList->Objects[idx];
		if(FTokenID == tkUnknown)
		{
			FTokenID = tkKey;
			if(fLine[i] == L' ')
			{
				while((fLine[i] == L' '))
					++i;
				if((fLine[i + 0] == L'f') && (fLine[i + 1] == L'i') && (fLine[i + 2] == L'l') && (fLine[i + 3] == L'e') && CharInSet(fLine[i + 4], Synhighlighterawk__2))
				{
					Run = (i + 4);
				}
			}
		}
	}
	else
	FTokenID = tkIdentifier;
}

void __fastcall TSynAWKSyn::Next()
{
	fTokenPos = Run;
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
		case L'\x27':
		StringProc();
		break; /* "..." */
		case L'(':
		case L')':
		case L'[':
		case L']':
		BraceProc();
		break; /* (, ), [ and ] */
		case L'#':
		CommentProc();
		break; /* # ... */
		case L'$':
		FieldRefProc();
		break; /* $0 .. $9 */
		case L'+':
		PlusProc();
		break; /* +, ++ and += */
		case L'-':
		MinusProc();
		break; /* -, -- and -= */
		case L'!':
		ExclamProc();
		break; /* ! and !~ */
		case L'?':
		QuestionProc();
		break; /* ?: */
		case L'|':
		OrProc();
		break; /* || */
		case L'&':
		AndProc();
		break; /* && */
		case L'*':
		case L'/':
		case L'%':
		case L'^':
		case L'<':
		case L'=':
		case L'>':
		OpInputProc();
		break; /* *=, /=, %= ... etc. */
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		IdentProc();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		NumberProc();
		break;
		default:
		SymbolProc();
		break;
	}
	inherited::Next();
}

void __fastcall TSynAWKSyn::StringProc()
{
	do
	{
		++Run;
		if((fLine[Run] == L'\"') && (fLine[Run - 1] != L'\\'))
		{
			FTokenID = tkString;
			++Run;
			return;
		}
	}
	while(!CharInSet(fLine[Run], Synhighlighterawk__3));
	FTokenID = tkIdentifier;
}

void __fastcall TSynAWKSyn::CommentProc()
{
	FTokenID = tkComment;
	while(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynAWKSyn::FieldRefProc()
{

	auto IsAlphaNumChar = [&](int Run) -> bool 
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
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	++Run;
	if(CharInSet(fLine[Run], Synhighlighterawk__4) && !IsAlphaNumChar(Run + 1))
	{
		FTokenID = tkSymbol;
		++Run;
	}
	else
	FTokenID = tkIdentifier;
}

void __fastcall TSynAWKSyn::SymbolProc()
{
	FTokenID = tkSymbol;
	++Run;
}

void __fastcall TSynAWKSyn::PlusProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], Synhighlighterawk__5))
		++Run;
}

void __fastcall TSynAWKSyn::MinusProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], Synhighlighterawk__6))
		++Run;
}

void __fastcall TSynAWKSyn::OpInputProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynAWKSyn::ExclamProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], Synhighlighterawk__7))
		++Run;
}

void __fastcall TSynAWKSyn::QuestionProc()
{
	++Run;
	if(fLine[Run] == L':')
	{
		FTokenID = tkSymbol;
		++Run;
	}
	else
	FTokenID = tkIdentifier;
}

void __fastcall TSynAWKSyn::OrProc()
{
	++Run;
	if(fLine[Run] == L'|')
	{
		FTokenID = tkSymbol;
		++Run;
	}
	else
	FTokenID = tkIdentifier;
}

void __fastcall TSynAWKSyn::AndProc()
{
	++Run;
	if(fLine[Run] == L'&')
	{
		FTokenID = tkSymbol;
		++Run;
	}
	else
	FTokenID = tkIdentifier;
}

__fastcall TSynAWKSyn::TSynAWKSyn(TComponent* AOwner)
 : inherited(AOwner),
			AWKSyntaxList(new TStringList()),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fInterFuncAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fSysVarAttri(nullptr)
{
	fCaseSensitive = true;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Foreground = (TColor) clBlue;
	AddAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fInterFuncAttri = new TSynHighlighterAttributes(SYNS_AttrInternalFunction, SYNS_FriendlyAttrInternalFunction);
	fInterFuncAttri->Foreground = (TColor) 0x00408080;
	fInterFuncAttri->Style = Synhighlighterawk__8;
	AddAttribute(fInterFuncAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Foreground = (TColor) 0x00FF0080;
	fKeyAttri->Style = Synhighlighterawk__9;
	AddAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	AddAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = (TColor) clTeal;
	AddAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	fSymbolAttri->Style = Synhighlighterawk__10;
	AddAttribute(fSymbolAttri);
	fSysVarAttri = new TSynHighlighterAttributes(SYNS_AttrSystemValue, SYNS_FriendlyAttrSystemValue);
	fSysVarAttri->Foreground = (TColor) 0x000080FF;
	fSysVarAttri->Style = Synhighlighterawk__11;
	AddAttribute(fSysVarAttri);
	SetAttributesOnChange(DefHighlightChange);
	MakeSyntaxList();
	fDefaultFilter = SYNS_FilterAWK;
}

__fastcall TSynAWKSyn::~TSynAWKSyn()
{
	delete AWKSyntaxList;
	//# inherited::Destroy();
}

void __fastcall TSynAWKSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynAWKSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynAWKSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynAWKSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

TSynHighlighterAttributes* __fastcall TSynAWKSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_COMMENT:
		result = fCommentAttri;
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

bool __fastcall TSynAWKSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynAWKSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynAWKSyn::GetTokenAttribute()
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
		case tkInterFunc:
		result = fInterFuncAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkNumber:
		result = fNumberAttri;
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
		case tkSysVar:
		result = fSysVarAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynAWKSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

bool __fastcall TSynAWKSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterAWK;
	return result;
}

/*#static*/
String __fastcall TSynAWKSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangAWK;
	return result;
}

/*#static*/
String __fastcall TSynAWKSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangAWK;
	return result;
}
static bool SynHighlighterAWK_Initialized = false;

void SynHighlighterAWK_initialization()
{
	if(SynHighlighterAWK_Initialized)
		return;
	
	SynHighlighterAWK_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynAWKSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterAWK

