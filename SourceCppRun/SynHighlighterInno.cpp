
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterInno.h"
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
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Synhighlighterinno
{
#define SynHighlighterInno__0 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterInno__1 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterInno__2 (TFontStyles() << TFontStyle::fsBold << TFontStyle::fsItalic)
#define SynHighlighterInno__3 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterInno__4 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterInno__5 (TSysCharSet() << L'\x09' << L' ')
#define SynHighlighterInno__6 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)


  /*Note: new 'Section names' and the new 'Constants' need not be added
         as they are highlighted automatically*/

  /*Ref:  Keywords and Parameters are updated as they last appeared in
         Inno Setup / ISX version 1.3.26*/
const String Keywords = L"adminprivilegesrequired,allownoicons,allowrootdirectory,allowuncpath,"
	           L"alwayscreateuninstallicon,alwaysrestart,alwaysshowcomponentslist,"
	           L"alwaysshowdironreadypage,alwaysshowgrouponreadypage,"
	           L"alwaysusepersonalgroup,appcopyright,appid,appmutex,appname,apppublisher,"
	           L"apppublisherurl,appsupporturl,appupdatesurl,appvername,appversion,"
	           L"attribs,backcolor,backcolor2,backcolordirection,backsolid,bits,"
	           L"changesassociations,check,codefile,comment,components,compression,compresslevel,copymode,"
	           L"createappdir,createuninstallregkey,defaultdirname,defaultgroupname,"
	           L"description,destdir,destname,direxistswarning,disableappenddir,"
	           L"disabledirexistswarning,disabledirpage,disablefinishedpage,"
	           L"disableprogramgrouppage,disablereadymemo,disablereadypage,"
	           L"disablestartupprompt,diskclustersize,disksize,diskspacemblabel,"
	           L"diskspanning,dontmergeduplicatefiles,enabledirdoesntexistwarning,"
	           L"extradiskspacerequired,filename,flags,flatcomponentslist,fontinstall,"
	           L"groupdescription,hotkey,iconfilename,iconindex,infoafterfile,infobeforefile,"
	           L"installmode,internalcompresslevel,key,licensefile,messagesfile,minversion,name,"
	           L"onlybelowversion,outputbasefilename,outputdir,overwriteuninstregentries,"
	           L"parameters,password,reservebytes,root,runonceid,section,"
	           L"showcomponentsizes,source,sourcedir,statusmsg,subkey,tasks,type,types,"
	           L"uninstalldisplayicon,uninstalldisplayname,uninstallfilesdir,"
	           L"uninstalliconname,uninstalllogmode,uninstallstyle,uninstallable,"
	           L"updateuninstalllogappname,usepreviousappdir,usepreviousgroup,"
	           L"useprevioustasks,useprevioussetuptype,usesetupldr,valuedata,valuename,"
	           L"valuetype,windowresizable,windowshowcaption,windowstartmaximized,"
	           L"windowvisible,wizardimagebackcolor,wizardimagefile,wizardsmallimagefile,"
	           L"wizardstyle,workingdir";
const String Parameters = L"hkcc,hkcr,hkcu,hklm,hku,alwaysoverwrite,alwaysskipifsameorolder,append,"
	           L"binary,classic,closeonexit,comparetimestampalso,confirmoverwrite,"
	           L"createkeyifdoesntexist,createonlyiffileexists,createvalueifdoesntexist,"
	           L"deleteafterinstall,deletekey,deletevalue,dirifempty,dontcloseonexit,"
	           L"dontcreatekey,disablenouninstallwarning,dword,exclusive,expandsz,"
	           L"external,files,filesandordirs,fixed,fontisnttruetype,iscustom,isreadme,"
	           L"modern,multisz,new,noerror,none,normal,nowait,onlyifdestfileexists,"
	           L"onlyifdoesntexist,overwrite,overwritereadonly,postinstall,"
	           L"preservestringtype,regserver,regtypelib,restart,restartreplace,"
	           L"runmaximized,runminimized,sharedfile,shellexec,showcheckbox,"
	           L"skipifnotsilent,skipifsilent,silent,skipifdoesntexist,"
	           L"skipifsourcedoesntexist,unchecked,uninsalwaysuninstall,"
	           L"uninsclearvalue,uninsdeleteentry,uninsdeletekey,uninsdeletekeyifempty,"
	           L"uninsdeletesection,uninsdeletesectionifempty,uninsdeletevalue,"
	           L"uninsneveruninstall,useapppaths,verysilent,waituntilidle";
const String KeyOrParameter = L"string";

int __fastcall TSynInnoSyn::HashKey(PWideChar Str)
{
	int result = 0;

	auto GetOrd = [&]() -> int 
	{
		int result = 0;
		switch((*Str))
		{
			case L'_':
			result = 1;
			break;
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			result = 2 + int((*Str)) - int(L'a');
			break;
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			result = 2 + int((*Str)) - int(L'A');
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
	result = result & 0x1FF; // 511
	fStringLen = Str - fToIdent;
	return result;
}

TtkTokenKind __fastcall TSynInnoSyn::IdentKind(PWideChar Maybe)
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

bool __fastcall TSynInnoSyn::IsCurrentToken(const String Token)
{
	bool result = false;
	int i = 0;
	PWideChar Temp = nullptr;
	Temp = fToIdent;
	if(Token.Length() == fStringLen)
	{
		int stop = 0;
		result = true;
		for(stop = fStringLen, i = 1; i <= stop; i++)
		{
			if(Sysutils::AnsiLowerCase(String((*Temp)))[1] != Sysutils::AnsiLowerCase(String(Token[i]))[1])
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

__fastcall TSynInnoSyn::TSynInnoSyn(TComponent* AOwner)
 : inherited(AOwner),
			FTokenID(tkComment),
			fConstantAttri(nullptr),
			fCommentAttri(nullptr),
			fSectionAttri(nullptr),
			fParamAttri(nullptr),
			fIdentifierAttri(nullptr),
			fInvalidAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fKeywords(nullptr)
{
	FCaseSensitive = false;
	fKeywords = new TSynHashEntryList();
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = SynHighlighterInno__0;
	fCommentAttri->Foreground = clGray;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fInvalidAttri = new TSynHighlighterAttributes(SYNS_AttrIllegalChar, SYNS_FriendlyAttrIllegalChar);
	addAttribute(fInvalidAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = SynHighlighterInno__1;
	fKeyAttri->Foreground = clNavy;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = clMaroon;
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = clBlue;
	addAttribute(fStringAttri);
	fConstantAttri = new TSynHighlighterAttributes(SYNS_AttrDirective, SYNS_FriendlyAttrDirective);
	fConstantAttri->Style = SynHighlighterInno__2;
	fConstantAttri->Foreground = clTeal;
	addAttribute(fConstantAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);

  //Parameters
	fParamAttri = new TSynHighlighterAttributes(SYNS_AttrPreprocessor, SYNS_FriendlyAttrPreprocessor);
	fParamAttri->Style = SynHighlighterInno__3;
	fParamAttri->Foreground = clOlive;
	addAttribute(fParamAttri);
	fSectionAttri = new TSynHighlighterAttributes(SYNS_AttrSection, SYNS_FriendlyAttrSection);
	fSectionAttri->Style = SynHighlighterInno__4;
	fSectionAttri->Foreground = clRed;
	addAttribute(fSectionAttri);
	SetAttributesOnChange(DefHighlightChange);
	EnumerateKeywords(int(tkKey), Keywords, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkParameter), Parameters, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkKeyOrParameter), KeyOrParameter, IsIdentChar, DoAddKeyword);
	fDefaultFilter = SYNS_FilterInno;
}

__fastcall TSynInnoSyn::~TSynInnoSyn()
{
	delete fKeywords;
	//# inherited::Destroy();
}


void __fastcall TSynInnoSyn::SymbolProc()
{
	FTokenID = tkSymbol;
	++Run;
}

void __fastcall TSynInnoSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynInnoSyn::EqualProc()
{

// If any word has equal (=) symbol,
// then the immediately followed text is treated as string
// (though it does not have quotes)
	FTokenID = tkString;
	do
	{
		++Run;
		if(fLine[Run] == L';')
		{
			++Run;
			break;
		}
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynInnoSyn::IdentProc()
{
	int LookAhead = 0;
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	if(FTokenID == tkKeyOrParameter)
	{
		LookAhead = Run;
		while(CharInSet(fLine[LookAhead], SynHighlighterInno__5))
			++LookAhead;
		if(fLine[LookAhead] == L':')
			FTokenID = tkKey;
		else
			FTokenID = tkParameter;
	}
}

void __fastcall TSynInnoSyn::SectionProc()
{

  // if it is not column 0 mark as tkParameter and get out of here
	if(Run > 0)
	{
		FTokenID = tkUnknown;
		++Run;
		return;
	}

  // this is column 0 ok it is a Section
	FTokenID = tkSection;
	do
	{
		++Run;
		if(fLine[Run] == L']')
		{
			++Run;
			break;
		}
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynInnoSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynInnoSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynInnoSyn::NumberProc()
{
	FTokenID = tkNumber;
	do
	{
		++Run;
	}
	while(!!CharInSet(fLine[Run], SynHighlighterInno__6));
}

void __fastcall TSynInnoSyn::ConstantProc()
{
	int BraceLevel = 0;
	int LastOpenBrace = 0;
  /* Much of this is based on code from the SkipPastConst function in IS's
    CmnFunc2 unit. [jr] */
	if(fLine[Run + 1] == L'{')
    /* '{{' is not a constant */
	{
		FTokenID = tkUnknown;
		Run += 2;
		return;
	}
	FTokenID = tkConstant;
	BraceLevel = 1;
	LastOpenBrace = -2147483648 /*# Low(Integer) */;
	do
	{
		++Run;
		switch(fLine[Run])
		{
			case L'{':
			{
				if(LastOpenBrace != Run - 1)
				{
					++BraceLevel;
					LastOpenBrace = Run;
				}
				else

               /* Skip over '{{' when in an embedded constant */
				--BraceLevel;
			}
			break;
			case L'}':
			{
				--BraceLevel;
				if(BraceLevel == 0)
				{
					++Run;
					goto label0;
				}
			}
			break;
			default:
			  ;
			break;
		}
	}
	while(!IsLineEnd(Run));
	label0:;
}

void __fastcall TSynInnoSyn::SpaceProc()
{
	FTokenID = tkSpace;
	do
	{
		++Run;
	}
	while(!((fLine[Run] > L'\x20') || IsLineEnd(Run)));
}

void __fastcall TSynInnoSyn::SemiColonProc()
{
	int i = 0;
	int stop = 0;
	for(stop = 0, i = Run - 1; i >= stop; i--)
	{
		if(fLine[i] > L' ')
      // If the semicolon is not the first non-whitespace character on the
      // line, then it isn't the start of a comment.
		{
			FTokenID = tkUnknown;
			++Run;
			return;
		}
	}
	FTokenID = tkComment;
	do
	{
		++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynInnoSyn::StringProc()
{
	FTokenID = tkString;
	do
	{
		++Run;
		if(fLine[Run] == L'\"')
		{
			++Run;
			if(fLine[Run] != L'\"')
				break;
		}
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynInnoSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynInnoSyn::Next()
{
	fTokenPos = Run;
	switch(fLine[Run])
	{
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
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break; /*';'*/
		case L'\x3b':
		SemiColonProc();
		break; /*'='*/
		case L'\x3d':
		EqualProc();
		break;
		case L'\x22':
		StringProc();
		break;
		case L'#':
		case L':':
		case L',':
		case L'(':
		case L')':
		SymbolProc();
		break;
		case L'{':
		ConstantProc();
		break; /*'['*/
		case L'\x5b':
		SectionProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynInnoSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynInnoSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynInnoSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkParameter:
		result = fParamAttri;
		break;
		case tkSection:
		result = fSectionAttri;
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
		case tkConstant:
		result = fConstantAttri;
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

int __fastcall TSynInnoSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

TtkTokenKind __fastcall TSynInnoSyn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

bool __fastcall TSynInnoSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterInno;
	return result;
}

/*#static*/
String __fastcall TSynInnoSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangInno;
	return result;
}

void __fastcall TSynInnoSyn::DoAddKeyword(String AKeyword, int AKind)
{
	int HashValue = 0;
	HashValue = HashKey(ustr2pwchar(AKeyword));
	fKeywords->Items[HashValue] = new TSynHashEntry(AKeyword, AKind);
}

/*#static*/
String __fastcall TSynInnoSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangInno;
	return result;
}
static bool SynHighlighterInno_Initialized = false;

void SynHighlighterInno_initialization()
{
	if(SynHighlighterInno_Initialized)
		return;
	
	SynHighlighterInno_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynInnoSyn));
}
class SynHighlighterInno_unit
{
public:
	SynHighlighterInno_unit()
	{
		SynHighlighterInno_initialization();
	}
};

SynHighlighterInno_unit _SynHighlighterInno_unit;

}  // namespace SynHighlighterInno

