
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterPython.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Types;
using namespace Vcl::Graphics;

namespace Synhighlighterpython
{
#define Synhighlighterpython__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterpython__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterpython__2 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterpython__3 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterpython__4 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterpython__5 (TSysCharSet() << 'x' << 'X')
#define Synhighlighterpython__6 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterpython__7 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55)
#define Synhighlighterpython__8 (TSysCharSet() << '+' << '-')
#define Synhighlighterpython__9 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterpython__10 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterpython__11 (TSysCharSet() << 'e' << 'E')
#define Synhighlighterpython__12 (TSysCharSet() << 'j' << 'J')
#define Synhighlighterpython__13 (TSysCharSet() << 'e' << 'E')
#define Synhighlighterpython__14 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterpython__15 (TSysCharSet() << 'j' << 'J')
#define Synhighlighterpython__16 (TSysCharSet() << 'e' << 'E')
#define Synhighlighterpython__17 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterpython__18 (TSysCharSet() << 'j' << 'J')
#define Synhighlighterpython__19 (TSysCharSet() <<  \
										97 << 98 << 99 << 100 << 101 << 102 <<  \
										65 << 66 << 67 << 68 << 69 << 70 <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterpython__20 (TSysCharSet() << 'l' << 'L')
#define Synhighlighterpython__21 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterpython__22 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55)
#define Synhighlighterpython__23 (TSysCharSet() << 'l' << 'L')
#define Synhighlighterpython__24 (TSysCharSet() << 'e' << 'E')
#define Synhighlighterpython__25 (TSysCharSet() << 'j' << 'J')
#define Synhighlighterpython__26 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterpython__27 (TSysCharSet() << 'j' << 'J')
#define Synhighlighterpython__28 (TSysCharSet() << 'r' << 'R')
#define Synhighlighterpython__29 (TSysCharSet() << '\'' << '\"')


TStringList* GlobalKeywords = nullptr;

TStringList* __fastcall TSynPythonSyn::GetKeywordIdentifiers()
{
	TStringList* result = nullptr;
  // No need to localise keywords!

  // List of keywords
	const int KEYWORDCOUNT = 29;
	const String Keywords[29/*# range 1..KEYWORDCOUNT*/] = {L"and", L"assert", L"break", L"class", L"continue", L"def", L"del", L"elif", L"else", L"except", L"exec", L"finally"
																				, L"for", L"from", L"global", L"if", L"import", L"in", L"is", L"lambda", L"not", L"or", L"pass", L"print", L"raise", L"return", L"try"
																				, L"while", L"yield"};

  // List of non-keyword identifiers
	const int NONKEYWORDCOUNT = 66;
	const String NONKEYWORDS[66/*# range 1..NONKEYWORDCOUNT*/] = {L"__future__", L"__import__", L"abs", L"apply", L"as", L"buffer", L"callable", L"chr", L"cmp", L"coerce", L"compile"
																				, L"complex", L"delattr", L"dict", L"dir", L"divmod", L"eval", L"execfile", L"False", L"file", L"filter", L"float", L"getattr"
																				, L"globals", L"hasattr", L"hash", L"help", L"hex", L"id", L"input", L"int", L"intern", L"isinstance", L"issubclass", L"iter"
																				, L"len", L"list", L"locals", L"long", L"None", L"NotImplemented", L"map", L"max", L"min", L"oct", L"open", L"ord", L"pow", L"range"
																				, L"raw_input", L"reduce", L"reload", L"repr", L"round", L"self", L"setattr", L"slice", L"str", L"True", L"tuple", L"type", L"unichr"
																				, L"unicode", L"vars", L"xrange", L"zip"};
	int f = 0;
	if(!ASSIGNED(GlobalKeywords))
    // Create the string list of keywords - only once
	{
		int stop = 0;
		GlobalKeywords = new TStringList();
		for(stop = KEYWORDCOUNT, f = 1; f <= stop; f++)
		{
			GlobalKeywords->AddObject(Keywords[f - 1], ((TObject*) ((void*) int(tkKey))));
		}
		for(stop = NONKEYWORDCOUNT, f = 1; f <= stop; f++)
		{
			GlobalKeywords->AddObject(NONKEYWORDS[f - 1], ((TObject*) ((void*) int(tkNonKeyword))));
		}
	} // if
	result = GlobalKeywords;
	return result;
}

TtkTokenKind __fastcall TSynPythonSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	int i = 0;
	PWideChar Temp = nullptr;
	String s;
  // Extract the identifier out - it is assumed to terminate in a
  //   non-alphanumeric character
	fToIdent = Maybe;
	Temp = Maybe;
	while(IsIdentChar((*Temp)))
		++Temp;
	fStringLen = Temp - fToIdent;

  // Check to see if it is a keyword
	SetString(s, fToIdent, fStringLen);
	if(fKeywords->Find(s, i))
    // TStringList is not case sensitive!
	{
		if(s != fKeywords->Strings[i])
			i = -1;
	}
	else
	i = -1;
	if(i !=  - 1)

  // Check if it is a system identifier (__*__)
		result = (TtkTokenKind) (NativeInt) fKeywords->Objects[i];
	else
	{
		if((fStringLen >= 5) && (Maybe[0] == L'_') && (Maybe[1] == L'_') && (Maybe[2] != L'_') && (Maybe[fStringLen - 1] == L'_') && (Maybe[fStringLen - 2] == L'_') && (Maybe[fStringLen - 3] != L'_'))

  // Else, hey, it is an ordinary run-of-the-mill identifier!
			result = tkSystemDefined;
		else
			result = tkIdentifier;
	}
	return result;
}

__fastcall TSynPythonSyn::TSynPythonSyn(TComponent* AOwner)
 : inherited(AOwner),
			fStringStarter(L'\0'),
			FRange(rsANil),
			FTokenID(tkComment),
			fKeywords(nullptr),
			fStringAttri(nullptr),
			fDocStringAttri(nullptr),
			fNumberAttri(nullptr),
			fHexAttri(nullptr),
			fOctalAttri(nullptr),
			fFloatAttri(nullptr),
			fKeyAttri(nullptr),
			fNonKeyAttri(nullptr),
			fSystemAttri(nullptr),
			fSymbolAttri(nullptr),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fSpaceAttri(nullptr),
			fErrorAttri(nullptr)
{
	FCaseSensitive = true;
	fKeywords = new TStringList();
	fKeywords->Sorted = true;
	fKeywords->Duplicates = System::Types::dupError;
	fKeywords->Assign(GetKeywordIdentifiers());

//++ CodeFolding
	BlockOpenerRE	= TRegEx(L"^(def|class|while|for|if|else|elif|try|except|with"
												 L"|(async[ \\t]+def)|(async[ \\t]+with)|(async[ \\t]+for))\\b", TRegExOptions());
//-- CodeFolding
	FRange = rsUnKnown;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Foreground = clGray;
	fCommentAttri->Style = Synhighlighterpython__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterpython__1;
	addAttribute(fKeyAttri);
	fNonKeyAttri = new TSynHighlighterAttributes(SYNS_AttrNonReservedKeyword, SYNS_FriendlyAttrNonReservedKeyword);
	fNonKeyAttri->Foreground = clNavy;
	fNonKeyAttri->Style = Synhighlighterpython__2;
	addAttribute(fNonKeyAttri);
	fSystemAttri = new TSynHighlighterAttributes(SYNS_AttrSystem, SYNS_FriendlyAttrSystem);
	fSystemAttri->Style = Synhighlighterpython__3;
	addAttribute(fSystemAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = clBlue;
	addAttribute(fNumberAttri);
	fHexAttri = new TSynHighlighterAttributes(SYNS_AttrHexadecimal, SYNS_FriendlyAttrHexadecimal);
	fHexAttri->Foreground = clBlue;
	addAttribute(fHexAttri);
	fOctalAttri = new TSynHighlighterAttributes(SYNS_AttrOctal, SYNS_FriendlyAttrOctal);
	fOctalAttri->Foreground = clBlue;
	addAttribute(fOctalAttri);
	fFloatAttri = new TSynHighlighterAttributes(SYNS_AttrFloat, SYNS_FriendlyAttrFloat);
	fFloatAttri->Foreground = clBlue;
	addAttribute(fFloatAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = clBlue;
	addAttribute(fStringAttri);
	fDocStringAttri = new TSynHighlighterAttributes(SYNS_AttrDocumentation, SYNS_FriendlyAttrDocumentation);
	fDocStringAttri->Foreground = clTeal;
	addAttribute(fDocStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fErrorAttri = new TSynHighlighterAttributes(SYNS_AttrSyntaxError, SYNS_FriendlyAttrSyntaxError);
	fErrorAttri->Foreground = clRed;
	addAttribute(fErrorAttri);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterPython;
} /* Create */

__fastcall TSynPythonSyn::~TSynPythonSyn()
{
	delete fKeywords;
	// inherited;
}

void __fastcall TSynPythonSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynPythonSyn::CRProc()
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

void __fastcall TSynPythonSyn::CommentProc()
{
	FTokenID = tkComment;
	++Run;
	while(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynPythonSyn::GreaterProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;
		default:
		{
		++Run;
		FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPythonSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
}

void __fastcall TSynPythonSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynPythonSyn::LowerProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;
		case L'>':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;
		default:
		{
		++Run;
		FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPythonSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynPythonSyn::NumberProc()
{
	enum TNumberState {nsStart,
                   nsDotFound,
                   nsFloatNeeded,
                   nsHex,
                   nsOct,
                   nsExpFound };
	WideChar Temp = L'\0';
	TNumberState State = nsStart;

	auto CheckSpecialCases = [&]() -> bool 
	{
		bool result = false;
		switch(Temp)
		{
			case L'.':
      // Look for dot (.)

        // .45
			{
				if(CharInSet(fLine[Run], Synhighlighterpython__4))
				{
					++Run;
					FTokenID = tkFloat;
					State = nsDotFound;

        // Non-number dot
				}
				else

          // Ellipsis
				{
					if((fLine[Run] == L'.') && (fLine[Run + 1] == L'.'))
						Run += 2;
					FTokenID = tkSymbol;
					result = false;
					return result;
				} // if
			}
			break; // DOT

      // Look for zero (0)
			case L'0':
			{
				Temp = fLine[Run];
        // 0x123ABC
				if(CharInSet(Temp, Synhighlighterpython__5))
				{
					++Run;
					FTokenID = tkHex;
					State = nsHex;
        // 0.45
				}
				else
				{
					if(Temp == L'.')
					{
						++Run;
						State = nsDotFound;
						FTokenID = tkFloat;
					}
					else
					{
						if(CharInSet(Temp, Synhighlighterpython__6))
						{
							++Run;
          // 0123 or 0123.45
							if(CharInSet(Temp, Synhighlighterpython__7))
							{
								FTokenID = tkOct;
								State = nsOct;
          // 0899.45
							}
							else
							{
								FTokenID = tkFloat;
								State = nsFloatNeeded;
							} // if
						}
					} // if
				}
			}
			break; // ZERO
			default:
			  ;
			break;
		} // case
		result = true;
		return result;
	}; // CheckSpecialCases

	auto HandleBadNumber = [&]() -> bool 
	{
		bool result = false;
		result = false;
		FTokenID = tkUnknown;
    // Ignore all tokens till end of "number"
		while(IsIdentChar(fLine[Run]) || (fLine[Run] == L'.'))
			++Run;
		return result;
	}; // HandleBadNumber

	auto HandleExponent = [&]() -> bool 
	{
		bool result = false;
		State = nsExpFound;
		FTokenID = tkFloat;
    // Skip e[+/-]
		if(CharInSet(fLine[Run + 1], Synhighlighterpython__8))
			++Run;
    // Invalid token : 1.0e
		if(!CharInSet(fLine[Run + 1], Synhighlighterpython__9))
		{
			++Run;
			result = HandleBadNumber();
			return result;
		} // if
		result = true;
		return result;
	}; // HandleExponent

	auto HandleDot = [&]() -> bool 
	{
		bool result = false;
    // Check for ellipsis
		result = (fLine[Run + 1] != L'.') || (fLine[Run + 2] != L'.');
		if(result)
		{
			State = nsDotFound;
			FTokenID = tkFloat;
		} // if
		return result;
	}; // HandleDot

	auto CheckStart = [&]() -> bool 
	{
		bool result = false;
    // 1234
		if(CharInSet(Temp, Synhighlighterpython__10))
		{
			result = true;
    //123e4
		}
		else
		{
			if(CharInSet(Temp, Synhighlighterpython__11))
			{
				result = HandleExponent();
    // 123.45j
			}
			else
			{
				if(CharInSet(Temp, Synhighlighterpython__12))
				{
					++Run;
					FTokenID = tkFloat;
					result = false;
    // 123.45
				}
				else
				{
					if(Temp == L'.')
					{
						result = HandleDot();
    // Error!
					}
					else
					{
						if(IsIdentChar(Temp))
						{
							result = HandleBadNumber();
    // End of number
						}
						else
						{
							result = false;
						}
					}
				}
			} // if
		}
		return result;
	}; // CheckStart

	auto CheckDotFound = [&]() -> bool 
	{
		bool result = false;
    // 1.0e4
		if(CharInSet(Temp, Synhighlighterpython__13))
		{
			result = HandleExponent();
    // 123.45
		}
		else
		{
			if(CharInSet(Temp, Synhighlighterpython__14))
			{
				result = true;
    // 123.45j
			}
			else
			{
				if(CharInSet(Temp, Synhighlighterpython__15))
				{
					++Run;
					result = false;
    // 123.45.45: Error!
				}
				else
				{
					if(Temp == L'.')
					{
						result = false;
						if(HandleDot())
							HandleBadNumber();
    // Error!
					}
					else
					{
						if(IsIdentChar(Temp))
						{
							result = HandleBadNumber();
    // End of number
						}
						else
						{
							result = false;
						}
					}
				}
			} // if
		}
		return result;
	}; // CheckDotFound

	auto CheckFloatNeeded = [&]() -> bool 
	{
		bool result = false;
    // 091.0e4
		if(CharInSet(Temp, Synhighlighterpython__16))
		{
			result = HandleExponent();
    // 0912345
		}
		else
		{
			if(CharInSet(Temp, Synhighlighterpython__17))
			{
				result = true;
    // 09123.45
			}
			else
			{
				if(Temp == L'.')
				{
					result = HandleDot() || HandleBadNumber(); // Bad octal
    // 09123.45j
				}
				else
				{
					if(CharInSet(Temp, Synhighlighterpython__18))
					{
						++Run;
						result = false;
    // End of number (error: Bad oct number) 0912345
					}
					else
					{
						result = HandleBadNumber();
					}
				}
			}
		}
		return result;
	}; // CheckFloatNeeded

	auto CheckHex = [&]() -> bool 
	{
		bool result = false;
    // 0x123ABC
		if(CharInSet(Temp, Synhighlighterpython__19))
		{
			result = true;
    // 0x123ABCL
		}
		else
		{
			if(CharInSet(Temp, Synhighlighterpython__20))
			{
				++Run;
				result = false;
    // 0x123.45: Error!
			}
			else
			{
				if(Temp == L'.')
				{
					result = false;
					if(HandleDot())
						HandleBadNumber();
    // Error!
				}
				else
				{
					if(IsIdentChar(Temp))
					{
						result = HandleBadNumber();
    // End of number
					}
					else
					{
						result = false;
					}
				}
			} // if
		}
		return result;
	}; // CheckHex

	auto CheckOct = [&]() -> bool 
	{
		bool result = false;
    // 012345
		if(CharInSet(Temp, Synhighlighterpython__21))
		{
			if(!CharInSet(Temp, Synhighlighterpython__22))
			{
				State = nsFloatNeeded;
				FTokenID = tkFloat;
			} // if
			result = true;
    // 012345L
		}
		else
		{
			if(CharInSet(Temp, Synhighlighterpython__23))
			{
				++Run;
				result = false;
    // 0123e4
			}
			else
			{
				if(CharInSet(Temp, Synhighlighterpython__24))
				{
					result = HandleExponent();
    // 0123j
				}
				else
				{
					if(CharInSet(Temp, Synhighlighterpython__25))
					{
						++Run;
						FTokenID = tkFloat;
						result = false;
    // 0123.45
					}
					else
					{
						if(Temp == L'.')
						{
							result = HandleDot();
    // Error!
						}
						else
						{
							if(IsIdentChar(Temp))
							{
								result = HandleBadNumber();
    // End of number
							}
							else
							{
								result = false;
							}
						}
					}
				}
			} // if
		}
		return result;
	}; // CheckOct

	auto CheckExpFound = [&]() -> bool 
	{
		bool result = false;
    // 1e+123
		if(CharInSet(Temp, Synhighlighterpython__26))
		{
			result = true;
    // 1e+123j
		}
		else
		{
			if(CharInSet(Temp, Synhighlighterpython__27))
			{
				++Run;
				result = false;
    // 1e4.5: Error!
			}
			else
			{
				if(Temp == L'.')
				{
					result = false;
					if(HandleDot())
						HandleBadNumber();
    // Error!
				}
				else
				{
					if(IsIdentChar(Temp))
					{
						result = HandleBadNumber();
    // End of number
					}
					else
					{
						result = false;
					}
				}
			} // if
		}
		return result;
	}; // CheckExpFound
	State = nsStart;
	FTokenID = tkNumber;
	Temp = fLine[Run];
	++Run;

  // Special cases
	if(!CheckSpecialCases())
		return;

  // Use a state machine to parse numbers
	while(true)
	{
		Temp = fLine[Run];
		switch(State)
		{
			case nsStart:
			if(!CheckStart())
				return;
			break;
			case nsDotFound:
			if(!CheckDotFound())
				return;
			break;
			case nsFloatNeeded:
			if(!CheckFloatNeeded())
				return;
			break;
			case nsHex:
			if(!CheckHex())
				return;
			break;
			case nsOct:
			if(!CheckOct())
				return;
			break;
			case nsExpFound:
			if(!CheckExpFound())
				return;
			break;
			default:
			  ;
			break;
		} // case
		++Run;
	} // while
}

void __fastcall TSynPythonSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynPythonSyn::String2Proc()
{
	int fBackslashCount = 0;
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\"') && (fLine[Run + 2] == L'\"'))
	{
		FTokenID = tkTrippleQuotedString;
		Run += 3;
		FRange = rsMultilineString2;
		while(fLine[Run] != L'\x00')
		{
			switch(fLine[Run])
			{
				case L'\\':
               /* If we're looking at a backslash, and the following character is an
               end quote, and it's preceeded by an odd number of backslashes, then
               it shouldn't mark the end of the string.  If it's preceeded by an
               even number, then it should. !!!THIS RULE DOESNT APPLY IN RAW STRINGS*/
				{
					if(fLine[Run + 1] == L'\"')
					{
						fBackslashCount = 1;
						while(((Run > fBackslashCount) && (fLine[Run - fBackslashCount] == L'\\')))
							fBackslashCount = fBackslashCount + 1;
						if(fBackslashCount % 2 == 1)
							++Run;
					}
					++Run;
				}
				break;// '\':
				case L'\"':
				if((fLine[Run + 1] == L'\"') && (fLine[Run + 2] == L'\"'))
				{
					FRange = rsUnKnown;
					Run += 3;
					return;
				}
				else
				++Run;
				break;
				case L'\x0a':
				return;
				case L'\x0d':
				return;
				default:
				++Run;
				break;
			}
		}
	}
	else
	{
		do
 //if short string
		{
			switch(fLine[Run])
			{
				case L'\x00':
				case L'\x0a':
				case L'\x0d':
				{
					if(fLine[Run - 1] == L'\\')
					{
						fStringStarter = L'\"';
						FRange = rsMultilineString3;
					}
					goto label0;
				}
      /*The same backslash stuff above...*/
				case L'\\':
				{
					if(fLine[Run + 1] == L'\"')
					{
						fBackslashCount = 1;
						while(((Run > fBackslashCount) && (fLine[Run - fBackslashCount] == L'\\')))
							fBackslashCount = fBackslashCount + 1;
						if(fBackslashCount % 2 == 1)
							++Run;
					}
					++Run;
				}
				break;// '\':
				default:
				++Run;
				break;
			} //case
		}
		while(!(fLine[Run] == L'\"'));
		label0:;
	}
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynPythonSyn::PreStringProc()
{
	WideChar Temp = L'\0';
  // Handle python raw strings
  // r""
	Temp = fLine[Run + 1];
	if(Temp == L'\'')
	{
		++Run;
		StringProc();
	}
	else
	{
		if(Temp == L'\"')
		{
			++Run;
			String2Proc();
		}
		else

    // If not followed by quote char, must be ident
		{
			IdentProc();
		} // if
	}
}

void __fastcall TSynPythonSyn::UnicodeStringProc()
{

  // Handle python raw and unicode strings
  // Valid syntax: u"", or ur""
	if(CharInSet(fLine[Run + 1], Synhighlighterpython__28) && CharInSet(fLine[Run + 2], Synhighlighterpython__29))
    // for ur, Remove the "u" and...
	{
		++Run;
	}
  // delegate to raw strings
	PreStringProc();
}

void __fastcall TSynPythonSyn::StringProc()
{
	int fBackslashCount = 0;
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x27') && (fLine[Run + 2] == L'\x27'))
	{
		FTokenID = tkTrippleQuotedString;
		Run += 3;
		FRange = rsMultiLineString;
		while(fLine[Run] != L'\x00')
		{
			switch(fLine[Run])
			{
				case L'\\':
             /* If we're looking at a backslash, and the following character is an
             end quote, and it's preceeded by an odd number of backslashes, then
             it shouldn't mark the end of the string.  If it's preceeded by an
             even number, then it should. !!!THIS RULE DOESNT APPLY IN RAW STRINGS*/
				{
					if(fLine[Run + 1] == L'\x27')
					{
						fBackslashCount = 1;
						while(((Run > fBackslashCount) && (fLine[Run - fBackslashCount] == L'\\')))
							fBackslashCount = fBackslashCount + 1;
						if(fBackslashCount % 2 == 1)
							++Run;
					}
					++Run;
				}
				break;// '\':
				case L'\x27':
				if((fLine[Run + 1] == L'\x27') && (fLine[Run + 2] == L'\x27'))
				{
					FRange = rsUnKnown;
					Run += 3;
					return;
				}
				else
				++Run;
				break;
				case L'\x0a':
				return;
				case L'\x0d':
				return;
				default:
				++Run;
				break;
			}
		}
	}
	else
	{
		do
 //if short string
		{
			switch(fLine[Run])
			{
				case L'\x00':
				case L'\x0a':
				case L'\x0d':
				{
					if(fLine[Run - 1] == L'\\')
					{
						fStringStarter = L'\x27';
						FRange = rsMultilineString3;
					}
					goto label1;
				}

      /*The same backslash stuff above...*/
				case L'\\':
				{
					if(fLine[Run + 1] == L'\x27')
					{
						fBackslashCount = 1;
						while(((Run > fBackslashCount) && (fLine[Run - fBackslashCount] == L'\\')))
							fBackslashCount = fBackslashCount + 1;
						if(fBackslashCount % 2 == 1)
							++Run;
					}
					++Run;
				}
				break;// '\':
				default:
				++Run;
				break;
			} //case
		}
		while(!(fLine[Run] == L'\x27'));
		label1:;
	}
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynPythonSyn::StringEndProc(WideChar EndChar)
{
	int fBackslashCount = 0;
	if(FRange == rsMultilineString3)
		FTokenID = tkString;
	else
		FTokenID = tkTrippleQuotedString;
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
	if(FRange == rsMultilineString3)
	{
		do
		{
			if(fLine[Run] == fStringStarter)
			{
				++Run;
				FRange = rsUnKnown;
				return;
			}
			else
			{
				if(fLine[Run] == L'\\')
					;  /*The same backslash stuff above...*/
			}
			{
			if(fLine[Run + 1] == fStringStarter)
			{
				fBackslashCount = 1;
				while(((Run > fBackslashCount) && (fLine[Run - fBackslashCount] == L'\\')))
					fBackslashCount = fBackslashCount + 1;
				if(fBackslashCount % 2 == 1)
					++Run;
			}// if FLine[Run]...
			}
			++Run;
		}
		while(!IsLineEnd(Run));
		if(fLine[Run - 1] != L'\\')
		{
			FRange = rsUnKnown;
			return;
		}
	}
	else
	{
		do
		{
			if(fLine[Run] == L'\\')
			{
				if(fLine[Run + 1] == EndChar)
				{
					fBackslashCount = 1;
					while(((Run > fBackslashCount) && (fLine[Run - fBackslashCount] == L'\\')))
						fBackslashCount = fBackslashCount + 1;
					if(fBackslashCount % 2 == 1)
						Run += 2;
				}
			}// if FLine[Run]...
			if((fLine[Run] == EndChar) && (fLine[Run + 1] == EndChar) && (fLine[Run + 2] == EndChar))
			{
				Run += 3;
				FRange = rsUnKnown;
				return;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
	}
}

void __fastcall TSynPythonSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynPythonSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsMultiLineString:
		StringEndProc(L'\x27');
		break;
		case rsMultilineString2:
		StringEndProc(L'\"');
		break;
		case rsMultilineString3:
		StringEndProc(fStringStarter);
		break;
		default:
		switch(fLine[Run])
		{
			case L'&':
			case L'}':
			case L'{':
			case L':':
			case L',':
			case L']':
			case L'[':
			case L'*':
			case L'`':
			case L'^':
			case L')':
			case L'(':
			case L';':
			case L'/':
			case L'=':
			case L'-':
			case L'+':
			case L'!':
			case L'\\':
			case L'%':
			case L'|':
			case L'~':
			SymbolProc();
			break;
			case L'\x0d':
			CRProc();
			break;
			case L'#':
			CommentProc();
			break;
			case L'>':
			GreaterProc();
			break;
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81:
			case L'S':
			case L'T':
			case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113:
			case L's':
			case L't':
			case 118: case 119: case 120: case 121: case 122:
			case L'_':
			IdentProc();
			break;
			case L'\x0a':
			LFProc();
			break;
			case L'<':
			LowerProc();
			break;
			case L'\x00':
			NullProc();
			break;
			case L'.':
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			NumberProc();
			break;
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			case L'\x0b':
			case L'\x0c':
			case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
			 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
			SpaceProc();
			break;
			case L'r':
			case L'R':
			PreStringProc();
			break;
			case L'u':
			case L'U':
			UnicodeStringProc();
			break;
			case L'\'':
			StringProc();
			break;
			case L'\"':
			String2Proc();
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynPythonSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynPythonSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynPythonSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynPythonSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynPythonSyn::GetTokenAttribute()
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
		case tkNonKeyword:
		result = fNonKeyAttri;
		break;
		case tkSystemDefined:
		result = fSystemAttri;
		break;
		case tkNumber:
		result = fNumberAttri;
		break;
		case tkHex:
		result = fHexAttri;
		break;
		case tkOct:
		result = fOctalAttri;
		break;
		case tkFloat:
		result = fFloatAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkTrippleQuotedString:
		result = fDocStringAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkUnknown:
		result = fErrorAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynPythonSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynPythonSyn::ResetRange()
{
	FRange = rsUnKnown;
}

//++ CodeFolding

void __fastcall TSynPythonSyn::InitFoldRanges(TSynFoldRanges* FoldRanges)
{
	inherited::InitFoldRanges(FoldRanges);
	FoldRanges->CodeFoldingMode = cfmIndentation;
}

void __fastcall TSynPythonSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	String CurLine;
	String LeftTrimmedLine;
	__int64 Line = 0;
	int Indent = 0;
	int TabW = 0;
	int FoldType = 0;
	const int MultiLineStringFoldType = 2;
	const int ClassDefType = 3;
	const int FunctionDefType = 4;

	auto IsMultiLineString = [&](int Line, TRangeState Range, bool Fold) -> bool 
	{
		bool result = false;
		result = true;
		if((TRangeState)(NativeInt)GetLineRange(LinesToScan, Line) == Range)
		{
			if(((TRangeState)(NativeInt)GetLineRange(LinesToScan, Line - 1) != Range) && Fold)
				FoldRanges->StartFoldRange(Line + 1, MultiLineStringFoldType);
			else
				FoldRanges->NoFoldInfo(Line + 1);
		}
		else
		{
			if(((TRangeState)(NativeInt)GetLineRange(LinesToScan, Line - 1) == Range) && Fold)
			{
				FoldRanges->StopFoldRange(Line + 1, MultiLineStringFoldType);
			}
			else
			result = false;
		}
		return result;
	};

	auto FoldRegion = [&](int Line) -> bool 
	{
		bool result = false;
		result = false;
		if(UpperCase(LeftTrimmedLine.SubString(1, 7)) == L"#REGION")
		{
			FoldRanges->StartFoldRange(Line + 1, FoldRegionType);
			result = true;
		}
		else
		{
			if(UpperCase(LeftTrimmedLine.SubString(1, 10)) == L"#ENDREGION")
			{
				FoldRanges->StopFoldRange(Line + 1, FoldRegionType);
				result = true;
			}
		}
		return result;
	};

	auto LeftSpaces = [&]() -> int 
	{
		int result = 0;
		PWideChar P = nullptr;
		P = ustr2pwchar(CurLine);
		if(ASSIGNED(P))
		{
			result = 0;
			while(((*P) >= L'\x01') && ((*P) <= L'\x20'))
			{
				if((*P) == L'\x09')
					result += TabW;
				else
					++result;
				++P;
			}
		}
		else
		result = 0;
		return result;
	};
  //  Deal with multiline strings
	__int64 stop = 0;
	for(stop = ToLine, Line = FromLine; Line <= stop; Line++)
	{
		if(IsMultiLineString((int) Line, rsMultiLineString, true) || IsMultiLineString((int) Line, rsMultilineString2, true) || IsMultiLineString((int) Line, rsMultilineString3, false))
			continue;

    // Find Fold regions
		CurLine = LinesToScan->Strings[Line];
		LeftTrimmedLine = TrimLeft(CurLine);

    // Skip empty lines
		if(LeftTrimmedLine == L"")
		{
			FoldRanges->NoFoldInfo((int) (Line + 1));
			continue;
		}

    // Find Fold regions
		if(FoldRegion((int) Line))
			continue;
		TabW = TabWidth(LinesToScan);
		Indent = LeftSpaces();

    // find fold openers
		/*# with BlockOpenerRE.Match(LeftTrimmedLine) do */
		{
			auto with0 = BlockOpenerRE.Match(LeftTrimmedLine);
			if(with0.Success)
			{
				if(with0.Groups.Item[1].Value == L"class")
					FoldType = ClassDefType;
				else
				{
					if(Pos(L"def", with0.Groups.Item[1].Value) >= 1)
						FoldType = FunctionDefType;
					else
						FoldType = 1;
				}
				FoldRanges->StartFoldRange((int) (Line + 1), FoldType, Indent);
				continue;
			}
		}
		FoldRanges->StopFoldRange((int) (Line + 1), 1, Indent);
	}
}
//-- CodeFolding

void __fastcall TSynPythonSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

bool __fastcall TSynPythonSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterPython;
	return result;
}

/*#static*/
String __fastcall TSynPythonSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangPython;
	return result;
}

String __fastcall TSynPythonSyn::GetSampleSource()
{
	String result;
	result = L"#!/usr/local/bin/python\x0d\x0a"
	           L"import string, sys\x0d\x0a"
	           L"\"\"\" If no arguments were given, print a helpful message \"\"\"\x0d\x0a"
	           L"if len(sys.argv)==1:\x0d\x0a"
	           L"    print 'Usage: celsius temp1 temp2 ...'\x0d\x0a"
	           L"    sys.exit(0)";
	return result;
}

/*#static*/
String __fastcall TSynPythonSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangPython;
	return result;
}
static bool SynHighlighterPython_Initialized = false;

void SynHighlighterPython_initialization()
{
	if(SynHighlighterPython_Initialized)
		return;
	
	SynHighlighterPython_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynPythonSyn));
}
static bool SynHighlighterPython_Finalized = false;

void SynHighlighterPython_finalization()
{
	if(SynHighlighterPython_Finalized)
		return;
	
	SynHighlighterPython_Finalized = true;
	
	delete GlobalKeywords;
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterPython

