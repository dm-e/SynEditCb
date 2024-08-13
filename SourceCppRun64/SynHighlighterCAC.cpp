
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterCAC.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;

namespace Synhighlightercac
{
#define Synhighlightercac__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlightercac__1 (TFontStyles() << TFontStyle::fsBold)


const String Keywords[143/*# range 0..142*/] = {L"aadd", L"abs", L"and", L"announce", L"asc", L"at", L"average", L"begin", L"bof", L"break", L"call", L"cancel", L"cdow"
																				, L"chr", L"clear", L"close", L"cmonth", L"col", L"commit", L"continue", L"copy", L"count", L"create", L"ctod", L"date", L"day"
																				, L"declare", L"delete", L"deleted", L"devpos", L"dir", L"display", L"dow", L"dtoc", L"dtos", L"eject", L"else", L"elseif", L"empty"
																				, L"endcase", L"enddo", L"endif", L"eof", L"erase", L"exit", L"exp", L"external", L"fcount", L"field", L"fieldname", L"file"
																				, L"find", L"flock", L"for", L"found", L"function", L"get", L"go", L"if", L"iif", L"index", L"init", L"inkey", L"input", L"int", L"join"
																				, L"keyboard", L"lastrec", L"len", L"list", L"local", L"locate", L"lock", L"log", L"lower", L"ltrim", L"max", L"memvar", L"min"
																				, L"month", L"not", L"note", L"or", L"pack", L"parameters", L"pcol", L"pcount", L"private", L"procedure", L"prompt", L"prow", L"public"
																				, L"quit", L"read", L"recall", L"reccount", L"recno", L"reindex", L"release", L"rename", L"replace", L"replicate", L"request"
																				, L"restore", L"return", L"rlock", L"round", L"row", L"rtrim", L"run", L"save", L"say", L"seconds", L"seek", L"select", L"sequence"
																				, L"setpos", L"skip", L"sort", L"space", L"sqrt", L"static", L"store", L"str", L"substr", L"sum", L"text", L"time", L"total"
																				, L"transform", L"trim", L"type", L"unlock", L"update", L"upper", L"use", L"val", L"valtype", L"wait", L"while", L"word", L"year"
																				, L"zap"};
const int KeyIndices[709/*# range 0..708*/] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, 138, 87, 41, 140, 88, -1, -1, -1, 11, -1, -1, -1, 53, -1, -1, -1, -1, 54, -1, 111, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, 110, -1, -1, -1, 106, -1, -1, -1, -1, -1, -1, 24, -1, 86, -1, -1, -1, 81, -1, -1, -1, -1, -1, 119, -1, -1, 14, -1, -1, -1, 92, -1, -1, -1, -1, -1, 77, 89, 10, 23, -1, -1, 91, 65, -1, 122, -1, -1, -1
																				, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 124, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 46, -1, 27, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 120
																				, -1, 100, 2, -1, -1, -1, -1, 75, 7, -1, -1, -1, -1, -1, -1, -1, 108, 99, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 137, -1, -1, -1, -1, -1, -1, -1, -1, 50, 30, -1, -1
																				, -1, -1, 83, 116, -1, -1, 134, -1, -1, 69, -1, -1, -1, 109, -1, 76, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 142, -1, -1, -1, -1, -1, -1, -1, -1, 85, -1, -1, -1, 127, -1, -1, 102, 48
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 90, -1, -1, -1, -1, -1, -1, -1, -1, 74, -1, -1, -1, -1, 133, -1, 57, 113, -1, -1, -1, -1, -1, -1, 43, -1, 33, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 126, -1
																				, 132, -1, -1, -1, -1, -1, -1, -1, 80, -1, -1, -1, 58, -1, -1, -1, -1, -1, -1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 78, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, 125, -1, -1, -1, -1, -1, 98, -1, 49, 123, -1, -1, -1, -1, -1, -1, -1, -1, 38, -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1, -1, 103, -1, -1, -1, -1, -1, 5, 82, -1
																				, -1, -1, -1, -1, 35, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, -1, -1, -1, -1, -1, -1, 72, -1, -1, -1, -1, -1, -1, -1, 19, 63, -1, 52, -1, -1, -1, -1, -1, 34, -1, -1, -1, -1, -1, -1, -1, 13, -1, -1
																				, -1, 105, -1, -1, -1, -1, -1, -1, 39, -1, -1, -1, 118, -1, -1, -1, -1, -1, 121, 3, 115, -1, -1, 64, -1, -1, 60, -1, 114, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 47, -1, -1, -1, -1, -1, 20, -1, -1, 62
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, 135, -1, -1, -1, -1, 22, -1, -1, -1, -1, -1, 55, -1, 68, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, 94, 112, -1, -1, -1, -1, 59, -1, -1, 21, -1, -1, 66, -1, -1, -1
																				, -1, -1, 107, 28, -1, -1, -1, -1, -1, -1, -1, 96, -1, -1, -1, 56, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 93, -1, -1, -1, -1, 9, -1, -1, -1, -1
																				, 104, -1, -1, -1, 42, -1, -1, -1, -1, 79, 18, 70, -1, 26, 25, 32, -1, -1, 0, 37, -1, 40, -1, -1, -1, -1, 73, -1, 97, -1, -1, -1, 67, 128, -1, -1, -1, -1, -1, -1, 136, 16, 12, -1, -1, -1, -1, -1, -1, 131
																				, 117, -1, -1, -1, -1, -1, -1, 45, -1, -1, -1, -1, -1, -1, 51, -1, 1, -1, -1, -1, -1, -1, 141, -1, 129, -1, 44, -1, -1, 71, -1, 61, -1, -1, -1, -1, -1, -1, -1, 101, -1, -1, -1, -1, 4, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, 130, 139, -1, -1, -1, -1, -1, 95, -1, -1, -1, 31, -1, -1, 84, 8};

/*$Q-*/

unsigned int __fastcall TSynCACSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 123 + int((*Str)) * 763);
		++Str;
	}
	result = (unsigned int) (result % 709);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynCACSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 708 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynCACSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 708 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	for(stop = 708 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(fIdentFuncTable[i] == nullptr)
			fIdentFuncTable[i] = KeyWordFunc;
	}
}

TtkTokenKind __fastcall TSynCACSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkComment;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynCACSyn::KeyWordFunc(int Index)
{
	TtkTokenKind result = tkComment;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

__fastcall TSynCACSyn::TSynCACSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkComment),
			fStringAttri(nullptr),
			fOperatorAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fCommentAttri(nullptr),
			fSpaceAttri(nullptr),
			fIdentifierAttri(nullptr),
			fDirecAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlightercac__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlightercac__1;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fOperatorAttri = new TSynHighlighterAttributes(SYNS_AttrOperator, SYNS_FriendlyAttrOperator);
	addAttribute(fOperatorAttri);
	fDirecAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	addAttribute(fDirecAttri);
	InitIdent();
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterCAClipper;
}

void __fastcall TSynCACSyn::CStyleProc()
{
	FTokenID = tkComment;
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
	while(fLine[Run] != L'\x00')
		switch(fLine[Run])
		{
			case L'*':
			if(fLine[Run + 1] == L'/')
			{
				FRange = rsUnKnown;
				Run += 2;
				goto label0;
			}
			else
			++Run;
			break;
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

void __fastcall TSynCACSyn::CRProc()
{
	FTokenID = tkSpace;
	switch(fLine[Run + 1])
	{
		case L'\x0a':
		Run += 2;
		break;
		default:
		++Run;
		break;
	}
}

void __fastcall TSynCACSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynCACSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynCACSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynCACSyn::NumberProc()
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
			case L'.':
			if(fLine[Run + 1] == L'.')
				goto label3;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label3:;
}

void __fastcall TSynCACSyn::SlashProc()
{
	switch(fLine[Run + 1])
	{
		case L'/':
		{
			Run += 2;
			FTokenID = tkComment;
			while(fLine[Run] != L'\x00')
			{
				switch(fLine[Run])
				{
					case L'\x0a':
					case L'\x0d':
					goto label4;
					default:
					  ;
					break;
				}
				++Run;
			}
			label4:;
		}
		break;
		case L'*':
		{
			FTokenID = tkComment;
			FRange = rsCStyle;
			Run += 2;
			while(fLine[Run] != L'\x00')
				switch(fLine[Run])
				{
					case L'*':
					if(fLine[Run + 1] == L'/')
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
		default:
		{
			++Run;
			FTokenID = tkOperator;
		}
		break;
	}
}

void __fastcall TSynCACSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynCACSyn::SymbolProc()
{
	++Run;
	FTokenID = tkOperator;
}

void __fastcall TSynCACSyn::StringProc()
{
	WideChar ActiveStr = L'\0';
	FTokenID = tkString;
	ActiveStr = fLine[Run];
	if(((fLine[Run + 1] == L'\x27') && (fLine[Run + 2] == L'\x27')) || ((fLine[Run + 1] == L'\x22') && (fLine[Run + 2] == L'\x22')))
		Run += 2;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label8;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == ActiveStr));
	label8:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynCACSyn::DirectiveProc()
{
	FTokenID = tkDirective;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label9;
			case L'/':
			if(fLine[Run + 1] == L'/')
				goto label10;
			break;
			case L'\x22':
			case L'\x27':
			goto label11;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x00'));
	label9:;
	label10:;
	label11:;
}

void __fastcall TSynCACSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynCACSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsCStyle:
		CStyleProc();
		break;
		default:
		switch(fLine[Run])
		{
			case L'@':
			SymbolProc();
			break;
			case L'&':
			SymbolProc();
			break;
			case L'{':
			SymbolProc();
			break;
			case L'}':
			SymbolProc();
			break;
			case L'\x0d':
			CRProc();
			break;
			case L':':
			SymbolProc();
			break;
			case L',':
			SymbolProc();
			break;
			case L'#':
			DirectiveProc();
			break;
			case L'=':
			SymbolProc();
			break;
			case L'>':
			SymbolProc();
			break;
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			IdentProc();
			break;
			case L'$':
			SymbolProc();
			break;
			case L'\x0a':
			LFProc();
			break;
			case L'<':
			SymbolProc();
			break;
			case L'-':
			SymbolProc();
			break;
			case L'!':
			SymbolProc();
			break;
			case L'\x00':
			NullProc();
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			NumberProc();
			break;
			case L'+':
			SymbolProc();
			break;
			case L'.':
			SymbolProc();
			break;
			case L'?':
			SymbolProc();
			break;
			case L')':
			SymbolProc();
			break;
			case L'(':
			SymbolProc();
			break;
			case L';':
			SymbolProc();
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
			case L']':
			SymbolProc();
			break;
			case L'[':
			SymbolProc();
			break;
			case L'*':
			StarProc();
			break;
			case L'\x27':
			case L'\x22':
			StringProc();
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynCACSyn::GetDefaultAttribute(int Index)
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
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynCACSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynCACSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynCACSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynCACSyn::GetTokenAttribute()
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
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkDirective:
		result = fDirecAttri;
		break;
		case tkOperator:
		result = fOperatorAttri;
		break;
		case tkUnknown:
		result = fOperatorAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynCACSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynCACSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynCACSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

bool __fastcall TSynCACSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterCAClipper;
	return result;
}

/*#static*/
String __fastcall TSynCACSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangCAClipper;
	return result;
}

void __fastcall TSynCACSyn::StarProc()
{

// if Run is 0 there could be an access violation
	if((Run == 0) || IsLineEnd(Run - 1))
	{
		FTokenID = tkComment;
		do
		{
			++Run;
		}
		while(!IsLineEnd(Run));
	}
	else
	{
		++Run;
		FTokenID = tkOperator;
	}
}

/*#static*/
String __fastcall TSynCACSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangCAClipper;
	return result;
}
static bool SynHighlighterCAC_Initialized = false;

void SynHighlighterCAC_initialization()
{
	if(SynHighlighterCAC_Initialized)
		return;
	
	SynHighlighterCAC_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynCACSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterCAC

