
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterUNIXShellScript.h"
#include "SynEditMiscProcs.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditmiscprocs;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Synhighlighterunixshellscript
{
#define SynHighlighterUNIXShellScript__0 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterUNIXShellScript__1 (TSysCharSet() <<  \
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


const String ShellScriptKeys[110/*# range 0..109*/] = {L"awk", L"banner", L"basename", L"bdiff", L"bg", L"break", L"case", L"cat", L"cc", L"cd", L"chdir", L"chgrp", L"chmod"
																				, L"chown", L"clear", L"compress", L"continue", L"cp", L"cpio", L"cut", L"date", L"dd", L"df", L"diff", L"do", L"done", L"dtpad", L"echo"
																				, L"elif", L"else", L"esac", L"eval", L"exit", L"export", L"expr", L"fg", L"fi", L"finger", L"fold", L"for", L"ftp", L"g++", L"gcc"
																				, L"getopts", L"grep", L"gzip", L"hash", L"head", L"if", L"in", L"jobs", L"kill", L"ld", L"ln", L"login", L"ls", L"make", L"mkdir", L"mt"
																				, L"mv", L"newgrp", L"nohup", L"od", L"paste", L"perl", L"pg", L"ping", L"pr", L"ps", L"pwd", L"rcp", L"read", L"remsh", L"return", L"rm"
																				, L"rsh", L"rwho", L"sed", L"set", L"sh", L"shift", L"stop", L"strings", L"strip", L"sync", L"tail", L"tar", L"telnet", L"test", L"then"
																				, L"times", L"tput", L"trap", L"true", L"tty", L"type", L"ulimit", L"umask", L"unset", L"until", L"uudecode", L"uuencode", L"vi"
																				, L"wait", L"wc", L"while", L"who", L"xtern", L"zcat", L"zip"};
const String ShellScriptSecondKeys[23/*# range 0..22*/] = {L"cdpath", L"editor", L"home", L"ifs", L"lang", L"lc_messages", L"lc_type", L"ld_library_path", L"logname", L"mail"
																				, L"mailcheck", L"mailpath", L"manpath", L"path", L"ps1", L"ps2", L"pwd", L"shacct", L"shell", L"shlib_path", L"term", L"termcap"
																				, L"tz"};

bool __fastcall TSynUNIXShellScriptSyn::IsKeyword(const String AKeyword)
{
	bool result = false;
	int First = 0;
	int Last = 0;
	int i = 0;
	int Compare = 0;
	String Token;
	First = 0;
	Last = 109 /*# High(ShellScriptKeys) */;
	result = false;
	Token = Sysutils::AnsiLowerCase(AKeyword);
	while(First <= Last)
	{
		i = (First + Last) >> 1;
		Compare = CompareStr(ShellScriptKeys[i], Token);
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

bool __fastcall TSynUNIXShellScriptSyn::IsSecondKeyWord(String AToken)
{
	bool result = false;
	int First = 0;
	int Last = 0;
	int i = 0;
	int Compare = 0;
	String Token;
	First = 0;
	Last = 22 /*# High(ShellScriptSecondKeys) */;
	result = false;
	Token = Sysutils::AnsiLowerCase(AToken);
	while(First <= Last)
	{
		i = (First + Last) >> 1;
		Compare = CompareStr(ShellScriptSecondKeys[i], Token);
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
} /* IsSecondKeyWord */

__fastcall TSynUNIXShellScriptSyn::TSynUNIXShellScriptSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkComment),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fKeyAttri(nullptr),
			fSecondKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fCommentAttri(nullptr),
			fSpaceAttri(nullptr),
			fIdentifierAttri(nullptr),
			fVarAttri(nullptr)
{
	FCaseSensitive = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Foreground = clGreen;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Foreground = clNavy;
	fKeyAttri->Style = SynHighlighterUNIXShellScript__0;
	addAttribute(fKeyAttri);
	fSecondKeyAttri = new TSynHighlighterAttributes(SYNS_AttrSecondReservedWord, SYNS_FriendlyAttrSecondReservedWord);
	addAttribute(fSecondKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = clBlue;
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = clMaroon;
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	fSymbolAttri->Foreground = clRed;
	addAttribute(fSymbolAttri);
	fVarAttri = new TSynHighlighterAttributes(SYNS_AttrVariable, SYNS_FriendlyAttrVariable);
	fVarAttri->Foreground = clPurple;
	addAttribute(fVarAttri);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterUNIXShellScript;
} /* Create */

__fastcall TSynUNIXShellScriptSyn::~TSynUNIXShellScriptSyn()
{
	//# inherited::Destroy();
}
 /* Destroy */

void __fastcall TSynUNIXShellScriptSyn::DollarProc()
{
	WideChar cc = L'\0';
	++Run;
	FTokenID = tkVariable;
	if(IsLineEnd(Run))
		return;
	cc = fLine[Run];
	++Run;
	if(cc == L'{')
    // ${var}
	{
		while(IsIdentChar(fLine[Run]))
		{
			if(IsLineEnd(Run))
				break;
			++Run;
		}
		if(fLine[Run] == L'}')
			++Run;
	}
	else
	{
		while(IsIdentChar(fLine[Run]))

    // $var
			++Run;
	}
}

void __fastcall TSynUNIXShellScriptSyn::DotProc()
{

	auto TestDot = [&]() -> bool 
	{
		bool result = false;
		int i = 0;
		result = false;
		i = Run;
		++i;
		while(CharInSet(fLine[i], SynHighlighterUNIXShellScript__1))
			++i;
		if(i > (Run + 1))
			result = true;
		if(result)
			Run = i;
		return result;
	};
  // Don't highlight filenames like filename.zip
	if(TestDot())
		FTokenID = tkIdentifier;
	else
	{
		++Run;
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynUNIXShellScriptSyn::BraceOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynUNIXShellScriptSyn::PointCommaProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynUNIXShellScriptSyn::CRProc()
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

void __fastcall TSynUNIXShellScriptSyn::IdentProc()
{
	while(IsIdentChar(fLine[Run]))
		++Run;
	if(IsKeyword(GetToken()))
	{
		FTokenID = tkKey;
		return;
	}
	else
	FTokenID = tkIdentifier;
	if(IsSecondKeyWord(GetToken()))
		FTokenID = tkSecondKey;
	else
	{
		if(fLine[Run] == L'=')
			FTokenID = tkVariable;
		else
			FTokenID = tkIdentifier;
	}
}

void __fastcall TSynUNIXShellScriptSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynUNIXShellScriptSyn::LowerProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynUNIXShellScriptSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynUNIXShellScriptSyn::NumberProc()
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

void __fastcall TSynUNIXShellScriptSyn::RoundOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynUNIXShellScriptSyn::SlashProc()
{
	if(fLine[Run] == L'#')
    // Perl Styled Comment
	{
		++Run;
		FTokenID = tkComment;
		while(!IsLineEnd(Run))
		{
			++Run;
		}
	}
	else
	{
		++Run;
		FTokenID = tkSymbol;
	}
}

void __fastcall TSynUNIXShellScriptSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynUNIXShellScriptSyn::StringProc()
{
	WideChar QuoteChar = L'\0';
// Single and Double Quotes.
	FTokenID = tkString;
	QuoteChar = fLine[Run];      // either " or '
	if((fLine[Run + 1] == QuoteChar) && (fLine[Run + 2] == QuoteChar))
		Run += 2;
	do
	{
		if(IsLineEnd(Run))
			break;
		++Run;
	}
	while(!(fLine[Run] == QuoteChar));
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynUNIXShellScriptSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynUNIXShellScriptSyn::Next()
{
	fTokenPos = Run;
	NextProcedure();
	inherited::Next();
}

void __fastcall TSynUNIXShellScriptSyn::NextProcedure()
{
	switch(fLine[Run])
	{
		case L'<':
		LowerProc();
		break;
		case L'#':
		SlashProc();
		break;
		case L'{':
		BraceOpenProc();
		break;
		case L';':
		PointCommaProc();
		break;
		case L'.':
		DotProc();
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
		case L'$':
		DollarProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'\x22':
		case L'\x27':
		StringProc();
		break;
		case L'}':
		case L')':
		case L'!':
		case L'%':
		case L'&':
		case L':':
		case L'@':
		case L'[':
		case L']':
		case L'^':
		case L'`':
		case L'~':
		SymbolProc();
		break;
		default:
		UnknownProc();
		break;
	}
}

TSynHighlighterAttributes* __fastcall TSynUNIXShellScriptSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynUNIXShellScriptSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynUNIXShellScriptSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynUNIXShellScriptSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynUNIXShellScriptSyn::GetTokenAttribute()
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
		case tkSecondKey:
		result = fSecondKeyAttri;
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
		case tkVariable:
		result = fVarAttri;
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

int __fastcall TSynUNIXShellScriptSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynUNIXShellScriptSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynUNIXShellScriptSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(int)Value;
}

bool __fastcall TSynUNIXShellScriptSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterUNIXShellScript;
	return result;
}

/*#static*/
String __fastcall TSynUNIXShellScriptSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangNameUNIXShellScript;
	return result;
}

String __fastcall TSynUNIXShellScriptSyn::GetSampleSource()
{
	String result;
	result = L"######################################\x0d\x0a"
	           L"# Here is a comment about some stuff #\x0d\x0a"
	           L"######################################\x0d\x0a"
	           L"\x0d\x0a"
	           L"case $BUILD_MODE in\x0d\x0a"
	           L"  full )\x0d\x0a"
	           L"      MyFirstFunction\x0d\x0a"
	           L"      ;;\x0d\x0a"
	           L"  rekit)\x0d\x0a"
	           L"      MySecondFunction\x0d\x0a"
	           L"    ;;\x0d\x0a"
	           L"  installer)\x0d\x0a"
	           L"      MyThirdFunction\x0d\x0a"
	           L"    ;;\x0d\x0a"
	           L"esac";
	return result;
}

/*#static*/
String __fastcall TSynUNIXShellScriptSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangNameUNIXShellScript;
	return result;
}

void __fastcall TSynUNIXShellScriptSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}
static bool SynHighlighterUNIXShellScript_Initialized = false;

void SynHighlighterUNIXShellScript_initialization()
{
	if(SynHighlighterUNIXShellScript_Initialized)
		return;
	
	SynHighlighterUNIXShellScript_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynUNIXShellScriptSyn));
}
class SynHighlighterUNIXShellScript_unit
{
public:
	SynHighlighterUNIXShellScript_unit()
	{
		SynHighlighterUNIXShellScript_initialization();
	}
};

SynHighlighterUNIXShellScript_unit _SynHighlighterUNIXShellScript_unit;

}  // namespace SynHighlighterUNIXShellScript

