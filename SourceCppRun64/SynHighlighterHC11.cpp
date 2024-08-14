
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterHC11.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace Synhighlighterhashentries;
using namespace System;

namespace Synhighlighterhc11
{
#define Synhighlighterhc11__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterhc11__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterhc11__2 (TSysCharSet() <<  \
          48 << 49 << 50 << 51 << 52 << 53 <<  \
          54 << 55 << 56 << 57 <<  \
          65 << 66 << 67 << 68 << 69 << 70 <<  \
          97 << 98 << 99 << 100 << 101 << 102)
#define Synhighlighterhc11__3 (TSysCharSet() <<  \
										48 << 49)
#define Synhighlighterhc11__4 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterhc11__5 (System::Set<TkwKeyWordType, TkwKeyWordType::kwNone, TkwKeyWordType::kwNoOperand>() << kwOperandOver << kwNoOperand)


  /* TODO: seems as if the Ansi version ignores the underscores and therfore
    highlights more KeyWords than this(=Unicode) version.
    Also the SampleSource uses EQU_ and EQU, so it isn't clear what is
    the correct syntax: with other without the underscores.
  */
const String Keywords = (String(String(String(String(String(String(String(String(String(String(String(String(L"ABA,ABX,ABY,ADCA_,ADCB_,ADDA_,ADDB_,ADDD_,ANDA_,ANDB_,ASLA,ASLB,") + L"ASL_,ASLD,ASRA,ASRB,ASR_,BCC_,BCLR_,BCS_,BEQ_,BGE_,BGT_,BHI_,BHS") + L"_,BITA_,BITB_,BLE_,BLO_,BLS_,BLT_,BMI_,BNE_,BPL_,BRA_,BRCLR_,BRN") + L"_,BRSET_,BSET_,BSR_,BVC_,BVS_,CBA,CLC,CLI,CLRA,CLRB,CLR_,CLV,CMP") + L"A_,CMPB_,COMA,COMB,COM_,CPD_,CPX_,CPY_,DAA,DECA,DECB,DEC_,DES,DE") + L"X,DEY,EORA_,EORB_,FDIV,IDIV,INCA,INCB,INC_,INS,INX,INY,JMP_,JSR_") + L",LDAA_,LDAB_,LDD_,LDS_,LDX_,LDY_,LSLA,LSLB,LSL_,LSLD,LSRA,LSRB,L") + L"SR_,LSRD,MUL,NEGA,NEGB,NEG_,NOP,ORAA_,ORAB_,PSHA,PSHB,PSHX,PSHY,") + L"PULA,PULB,PULX,PULY,ROLA,ROLB,ROL_,RORA,RORB,ROR_,RTI,RTS,SBA,SB") + L"CA_,SBCB_,SEC,SEI,SEV,STAA_,STAB_,STD_,STOP,STS_,STX_,STY_,SUBA_") + L",SUBB_,SUBD_,SWI,TAB,TAP,TBA,TEST,") + L"TPA,TSTA,TSTB,TST_,TSX,TSY,TXS,TYS,WAI,XGDX,XGDY,") + L"FCC_,FCB_,BSZ_,FDB_");
const String Directives = (L"EQU_,OPT_,PAGE,ORG_,RMB_,END");

void __fastcall TSynHC11Syn::DoAddKeyword(String AKeyword, int AKind)
{
	int HashValue = 0;
	HashValue = HashKey(ustr2pwchar(AKeyword));
	fKeywords->Items[HashValue] = new TSynHashEntry(AKeyword, AKind);
}

int __fastcall TSynHC11Syn::HashKey(PWideChar Str)
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
			result = 28 + int((*Str)) - int(L'0');
			break;
			case L'_':
			result = 27;
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
		result = (7 * result + GetOrd()) & 0xFFFFFF;
		++Str;
	}
	result = result & 0xFF; // 255
	fStringLen = Str - fToIdent;
	return result;
}

TtkTokenKind __fastcall TSynHC11Syn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	TSynHashEntry* Entry = nullptr;
	fToIdent = Maybe;
	Entry = fKeywords->Items[HashKey(Maybe)];
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

__fastcall TSynHC11Syn::TSynHC11Syn(TComponent* AOwner)
 : inherited(AOwner),
			FTokenID(tkComment),
			FKeyWordType(kwNone),
			fCommentAttri(nullptr),
			fDirecAttri(nullptr),
			fIdentifierAttri(nullptr),
			fInvalidAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fKeywords(nullptr)
{
	FCaseSensitive = true;
	fKeywords = new TSynHashEntryList();
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterhc11__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fInvalidAttri = new TSynHighlighterAttributes(SYNS_AttrIllegalChar, SYNS_FriendlyAttrIllegalChar);
	addAttribute(fInvalidAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterhc11__1;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fDirecAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	addAttribute(fDirecAttri);
	SetAttributesOnChange(DefHighlightChange);
	EnumerateKeywords(int(tkKey), Keywords, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkDirective), Directives, IsIdentChar, DoAddKeyword);
	fDefaultFilter = SYNS_FilterAsm68HC11;
} /* Create */

__fastcall TSynHC11Syn::~TSynHC11Syn()
{
	delete fKeywords;
	//# inherited::Destroy();
}

void __fastcall TSynHC11Syn::SymAsciiCharProc()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x27') && (fLine[Run + 2] == L'\x27'))
		Run += 2;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			{
				FKeyWordType = kwNone;
				goto label0;
			}
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x27'));
	label0:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynHC11Syn::SymbolProc()
{
	FTokenID = tkSymbol;
	++Run;
}

void __fastcall TSynHC11Syn::SymDollarProc()
{
	FTokenID = tkNumber;
	++Run;
	while(CharInSet(fLine[Run], Synhighlighterhc11__2))
	{
		++Run;
	}
}

void __fastcall TSynHC11Syn::SymCRProc()
{
	FTokenID = tkSpace;
	FKeyWordType = kwNone;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynHC11Syn::SymIdentProc()
{
	FTokenID = IdentKind(fLine + Run);
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynHC11Syn::SymLFProc()
{
	FKeyWordType = kwNone;
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynHC11Syn::SymPercentProc()
{
	++Run;
	FTokenID = tkNumber;
	while(CharInSet(fLine[Run], Synhighlighterhc11__3))
		++Run;
}

void __fastcall TSynHC11Syn::SymNullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynHC11Syn::SymNumberProc()
{
	++Run;
	FTokenID = tkNumber;
	while(CharInSet(fLine[Run], Synhighlighterhc11__4))
		++Run;
}

void __fastcall TSynHC11Syn::SymSpaceProc()
{
	++Run;
	if(Synhighlighterhc11__5.Contains(FKeyWordType))
	{
		FKeyWordType = kwNone;
		FTokenID = tkComment;
		while(!IsLineEnd(Run))
			++Run;
	}
	else
	{
		if(FKeyWordType == kwOperand)
			FKeyWordType = kwOperandOver;
		FTokenID = tkSpace;
		while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
			++Run;
	}
}

void __fastcall TSynHC11Syn::SymStarProc()
{
	++Run;
	if(FKeyWordType == kwOperandOver)
		FTokenID = tkSymbol;
	else
	{
		FTokenID = tkComment;
		while(!IsLineEnd(Run))
			++Run;
	}
}

void __fastcall TSynHC11Syn::SymStringProc()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x22') && (fLine[Run + 2] == L'\x22'))
		Run += 2;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label1;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x22'));
	label1:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynHC11Syn::SymUnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynHC11Syn::Next()
{
	fTokenPos = Run;
	switch(fLine[Run])
	{
		case L'\x27':
		SymAsciiCharProc();
		break;
		case L'$':
		SymDollarProc();
		break;
		case L'\x0d':
		SymCRProc();
		break;
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		case L'_':
		SymIdentProc();
		break;
		case L'\x0a':
		SymLFProc();
		break;
		case L'%':
		SymPercentProc();
		break;
		case L'\x00':
		SymNullProc();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		SymNumberProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SymSpaceProc();
		break;
		case L'*':
		SymStarProc();
		break;
		case L'\x22':
		SymStringProc();
		break;
		case L'#':
		case L':':
		case L',':
		case L';':
		case L'(':
		case L')':
		SymbolProc();
		break;
		default:
		SymUnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynHC11Syn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynHC11Syn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynHC11Syn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkDirective:
		result = fDirecAttri;
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
		case tkSymbol:
		result = fSymbolAttri;
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

int __fastcall TSynHC11Syn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

TtkTokenKind __fastcall TSynHC11Syn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

bool __fastcall TSynHC11Syn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterAsm68HC11;
	return result;
}

/*#static*/
String __fastcall TSynHC11Syn::GetLanguageName()
{
	String result;
	result = SYNS_Lang68HC11;
	return result;
}

String __fastcall TSynHC11Syn::GetSampleSource()
{
	String result;
	result = L"* TX.ASM\x0d\x0a"
	           L"MAINORG EQU_    $F800\x0d\x0a"
	           L"        ORG     $F800\x0d\x0a"
	           L"MAIN    EQU     *        ;Start assembling here\x0d\x0a"
	           L"        STAA    SCCR2\x0d\x0a"
	           L"loop:\x0d\x0a"
	           L"        LDAA    #$05\x0d\x0a"
	           L"	BRA	loop		;Do it again\x0d\x0a"
	           L"	ORG	$FFFE		;Reset vector interrupt setup\x0d\x0a"
	           L"	END";
	return result;
}

/*#static*/
String __fastcall TSynHC11Syn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLang68HC11;
	return result;
}
static bool SynHighlighterHC11_Initialized = false;

void SynHighlighterHC11_initialization()
{
	if(SynHighlighterHC11_Initialized)
		return;
	
	SynHighlighterHC11_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynHC11Syn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterHC11

