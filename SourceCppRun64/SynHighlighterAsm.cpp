
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterAsm.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace Synhighlighterhashentries;
using namespace System;

namespace Synhighlighterasm
{
#define Synhighlighterasm__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterasm__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterasm__2 (TSysCharSet() << '=' << '>')


const String Mnemonics = L"aaa,aad,aam,adc,add,and,arpl,bound,bsf,bsr,bswap,bt,btc,"
	           L"btr,bts,call,cbw,cdq,clc,cld,cli,clts,cmc,cmp,cmps,cmpsb,cmpsd,cmpsw,"
	           L"cmpxchg,cwd,cwde,daa,das,dec,div,emms,enter,f2xm1,fabs,fadd,faddp,fbld,"
	           L"fbstp,fchs,fclex,fcmovb,fcmovbe,fcmove,fcmovnb,fcmovnbe,fcmovne,fcmovnu,"
	           L"fcmovu,fcom,fcomi,fcomip,fcomp,fcompp,fcos,fdecstp,fdiv,fdivp,fdivr,"
	           L"fdivrp,femms,ffree,fiadd,ficom,ficomp,fidiv,fidivr,fild,fimul,fincstp,"
	           L"finit,fist,fistp,fisub,fisubr,fld,fld1,fldcw,fldenv,fldl2e,fldl2t,fldlg2,"
	           L"fldln2,fldpi,fldz,fmul,fmulp,fnclex,fninit,fnop,fnsave,fnstcw,fnstenv,"
	           L"fnstsw,fpatan,fprem1,fptan,frndint,frstor,fsave,fscale,fsin,fsincos,"
	           L"fsqrt,fst,fstcw,fstenv,fstp,fstsw,fsub,fsubp,fsubr,fsubrp,ftst,"
	           L"fucom,fucomi,fucomip,fucomp,fucompp,fwait,fxch,fxtract,fyl2xp1,hlt,idiv,"
	           L"imul,in,inc,ins,insb,insd,insw,int,into,invd,invlpg,iret,iretd,iretw,"
	           L"ja,jae,jb,jbe,jc,jcxz,je,jecxz,jg,jge,jl,jle,jmp,jna,jnae,jnb,jnbe,jnc,"
	           L"jne,jng,jnge,jnl,jnle,jno,jnp,jns,jnz,jo,jp,jpe,jpo,js,jz,lahf,lar,lds,"
	           L"lea,leave,les,lfs,lgdt,lgs,lidt,lldt,lmsw,lock,lods,lodsb,lodsd,lodsw,"
	           L"loop,loope,loopne,loopnz,loopz,lsl,lss,ltr,mov,movd,movq, movs,movsb,"
	           L"movsd,movsw,movsx,movzx,mul,neg,nop,not,or,out,outs,outsb,outsd,outsw,"
	           L"packssdw,packsswb,packuswb,paddb,paddd,paddsb,paddsw,paddusb,paddusw,"
	           L"paddw,pand,pandn,pavgusb,pcmpeqb,pcmpeqd,pcmpeqw,pcmpgtb,pcmpgtd,pcmpgtw,"
	           L"pf2id,pfacc,pfadd,pfcmpeq,pfcmpge,pfcmpgt,pfmax,pfmin,pfmul,pfrcp,"
	           L"pfrcpit1,pfrcpit2,pfrsqit1,pfrsqrt,pfsub,pfsubr,pi2fd,pmaddwd,pmulhrw,"
	           L"pmulhw,pmullw,pop,popa,popad,popaw,popf,popfd,popfw,por,prefetch,prefetchw,"
	           L"pslld,psllq,psllw,psrad,psraw,psrld,psrlq,psrlw,psubb,psubd,psubsb,"
	           L"psubsw,psubusb,psubusw,psubw,punpckhbw,punpckhdq,punpckhwd,punpcklbw,"
	           L"punpckldq,punpcklwd,push,pusha,pushad,pushaw,pushf,pushfd,pushfw,pxor,"
	           L"rcl,rcr,rep,repe,repne,repnz,repz,ret,rol,ror,sahf,sal,sar,sbb,scas,"
	           L"scasb,scasd,scasw,seta,setae,setb,setbe,setc,sete,setg,setge,setl,setle,"
	           L"setna,setnae,setnb,setnbe,setnc,setne,setng,setnge,setnl,setnle,setno,"
	           L"setnp,setns,setnz,seto,setp,setpo,sets,setz,sgdt,shl,shld,shr,shrd,sidt,"
	           L"sldt,smsw,stc,std,sti,stos,stosb,stosd,stosw,str,sub,test,verr,verw,"
	           L"wait,wbinvd,xadd,xchg,xlat,xlatb,xor";

void __fastcall TSynAsmSyn::DoAddKeyword(String AKeyword, int AKind)
{
	unsigned int HashValue = 0;
	HashValue = HashKey(ustr2pwchar(AKeyword));
	fKeywords->Items[HashValue] = new TSynHashEntry(AKeyword, AKind);
}

/*$Q-*/

unsigned int __fastcall TSynAsmSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 197 + int((*Str)) * 14);
		++Str;
	}
	result = (unsigned int) (result % 4561);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynAsmSyn::IdentKind(PWideChar MayBe)
{
	TtkTokenKind result = tkComment;
	TSynHashEntry* Entry = nullptr;
	fToIdent = MayBe;
	Entry = fKeywords->Items[HashKey(MayBe)];
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

__fastcall TSynAsmSyn::TSynAsmSyn(TComponent* AOwner)
 : inherited(AOwner),
			fTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fKeywords(nullptr)
{
	fCaseSensitive = false;
	fKeywords = new TSynHashEntryList();
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterasm__0;
	AddAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	AddAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterasm__1;
	AddAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	AddAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	AddAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	AddAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	AddAttribute(fSymbolAttri);
	EnumerateKeywords(int(tkKey), Mnemonics, IsIdentChar, DoAddKeyword);
	SetAttributesOnChange(DefHighlightChange);
	fDefaultFilter = SYNS_FilterX86Assembly;
}

__fastcall TSynAsmSyn::~TSynAsmSyn()
{
	delete fKeywords;
	//# inherited::Destroy();
}

void __fastcall TSynAsmSyn::CommentProc()
{
	fTokenID = tkComment;
	do
	{
		++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynAsmSyn::CRProc()
{
	fTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynAsmSyn::GreaterProc()
{
	++Run;
	fTokenID = tkSymbol;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynAsmSyn::IdentProc()
{
	fTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynAsmSyn::LFProc()
{
	fTokenID = tkSpace;
	++Run;
}

void __fastcall TSynAsmSyn::LowerProc()
{
	++Run;
	fTokenID = tkSymbol;
	if(CharInSet(fLine[Run], Synhighlighterasm__2))
		++Run;
}

void __fastcall TSynAsmSyn::NullProc()
{
	fTokenID = tkNull;
	++Run;
}

void __fastcall TSynAsmSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'.':
			case 97: case 98: case 99: case 100: case 101: case 102:
			case L'h':
			case 65: case 66: case 67: case 68: case 69: case 70:
			case L'H':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	++Run;
	fTokenID = tkNumber;
	while(IsNumberChar())
		++Run;
}

void __fastcall TSynAsmSyn::SlashProc()
{
	++Run;
	if(fLine[Run] == L'/')
	{
		fTokenID = tkComment;
		do
		{
			++Run;
		}
		while(!IsLineEnd(Run));
	}
	else
	fTokenID = tkSymbol;
}

void __fastcall TSynAsmSyn::SpaceProc()
{
	fTokenID = tkSpace;
	do
	{
		++Run;
	}
	while(!((fLine[Run] > L'\x20') || IsLineEnd(Run)));
}

void __fastcall TSynAsmSyn::StringProc()
{
	fTokenID = tkString;
	if((fLine[Run + 1] == L'\x22') && (fLine[Run + 2] == L'\x22'))
		Run += 2;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label0;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x22'));
	label0:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynAsmSyn::SingleQuoteStringProc()
{
	fTokenID = tkString;
	if((fLine[Run + 1] == L'\x27') && (fLine[Run + 2] == L'\x27'))
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
	while(!(fLine[Run] == L'\x27'));
	label1:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynAsmSyn::SymbolProc()
{
	++Run;
	fTokenID = tkSymbol;
}

void __fastcall TSynAsmSyn::UnknownProc()
{
	++Run;
	fTokenID = tkIdentifier;
}

void __fastcall TSynAsmSyn::Next()
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
		case L'\x22':
		StringProc();
		break;
		case L'\x27':
		SingleQuoteStringProc();
		break;
		case L'>':
		GreaterProc();
		break;
		case L'<':
		LowerProc();
		break;
		case L'/':
		SlashProc();
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
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'#':
		case L';':
		CommentProc();
		break;
		case L'.':
		case L':':
		case L'&':
		case L'{':
		case L'}':
		case L'=':
		case L'^':
		case L'-':
		case L'+':
		case L'(':
		case L')':
		case L'*':
		SymbolProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynAsmSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynAsmSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynAsmSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(fTokenID)
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

int __fastcall TSynAsmSyn::GetTokenKind()
{
	int result = 0;
	result = int(fTokenID);
	return result;
}

TtkTokenKind __fastcall TSynAsmSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = fTokenID;
	return result;
}

/*#static*/
String __fastcall TSynAsmSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangX86Asm;
	return result;
}

bool __fastcall TSynAsmSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterX86Assembly;
	return result;
}

String __fastcall TSynAsmSyn::GetSampleSource()
{
	String result;
	result = L"; x86 assembly sample source\x0d\x0a"
	           L"  CODE	SEGMENT	BYTE PUBLIC\x0d\x0a"
	           L"    ASSUME	CS:CODE\x0d\x0a"
	           L"\x0d\x0a"
	           L"    PUSH SS\x0d\x0a"
	           L"    POP DS\x0d\x0a"
	           L"    MOV AX, AABBh\x0d\x0a"
	           L"    MOV	BYTE PTR ES:[DI], 255\x0d\x0a"
	           L"    JMP SHORT AsmEnd\x0d\x0a"
	           L"\x0d\x0a"
	           L"  welcomeMsg DB 'Hello World', 0\x0d\x0a"
	           L"\x0d\x0a"
	           L"  AsmEnd:\x0d\x0a"
	           L"    MOV AX, 0\x0d\x0a"
	           L"\x0d\x0a"
	           L"  CODE	ENDS\x0d\x0a"
	           L"END";
	return result;
}

/*#static*/
String __fastcall TSynAsmSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangX86Asm;
	return result;
}
static bool SynHighlighterAsm_Initialized = false;

void SynHighlighterAsm_initialization()
{
	if(SynHighlighterAsm_Initialized)
		return;
	
	SynHighlighterAsm_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynAsmSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterAsm

