
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterTclTk.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Uitypes;

namespace Synhighlightertcltk
{
#define SynHighlighterTclTk__0 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterTclTk__1 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterTclTk__2 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterTclTk__3 (TFontStyles() << TFontStyle::fsBold << TFontStyle::fsItalic)
#define SynHighlighterTclTk__4 (TFontStyles() << TFontStyle::fsBold << TFontStyle::fsItalic)
#define SynHighlighterTclTk__5 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define SynHighlighterTclTk__6 (TSysCharSet() <<  \
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
#define SynHighlighterTclTk__7 (TSysCharSet() <<  \
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
#define SynHighlighterTclTk__8 (TSysCharSet() <<  \
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
#define SynHighlighterTclTk__9 (TSysCharSet() <<  \
										97 << 98 << 99 << 100 << 101 << 102 <<  \
										103 << 104 << 105 << 106 << 107 << 108 <<  \
										109 << 110 << 111 << 112 << 113 << 114 <<  \
										115 << 116 << 117 << 118 << 119 << 120 <<  \
										121 << 122 <<  \
										65 << 66 << 67 << 68 << 69 << 70 <<  \
										71 << 72 << 73 << 74 << 75 << 76 <<  \
										77 << 78 << 79 << 80 << 81 << 82 <<  \
										83 << 84 << 85 << 86 << 87 << 88 <<  \
										89 << 90 <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define SynHighlighterTclTk__10 (TSysCharSet() << L'_' <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57 <<  \
										65 << 66 << 67 << 68 << 69 << 70 <<  \
										71 << 72 << 73 << 74 << 75 << 76 <<  \
										77 << 78 << 79 << 80 << 81 << 82 <<  \
										83 << 84 << 85 << 86 << 87 << 88 <<  \
										89 << 90 <<  \
										97 << 98 << 99 << 100 << 101 << 102 <<  \
										103 << 104 << 105 << 106 << 107 << 108 <<  \
										109 << 110 << 111 << 112 << 113 << 114 <<  \
										115 << 116 << 117 << 118 << 119 << 120 <<  \
										121 << 122)


const String TclTkKeys[129/*# range 0..128*/] = {L"after", L"append", L"array", L"auto_execok", L"auto_import", L"auto_load", L"auto_mkindex", L"auto_mkindex_old", L"auto_qualify"
																				, L"auto_reset", L"base", L"bgerror", L"binary", L"body", L"break", L"catch", L"cd", L"class", L"clock", L"close", L"code"
																				, L"concat", L"configbody", L"constructor", L"continue", L"dde", L"delete", L"destructor", L"else", L"elseif", L"encoding", L"ensemble"
																				, L"eof", L"error", L"eval", L"exec", L"exit", L"expr", L"fblocked", L"fconfigure", L"fcopy", L"file", L"fileevent", L"filename"
																				, L"find", L"flush", L"for", L"foreach", L"format", L"gets", L"glob", L"global", L"history", L"http", L"if", L"incr", L"info"
																				, L"inherit", L"interp", L"is", L"join", L"lappend", L"lindex", L"linsert", L"list", L"llength", L"load", L"local", L"lrange", L"lreplace"
																				, L"lsearch", L"lset", L"lsort", L"memory", L"method", L"msgcat", L"namespace", L"open", L"package", L"parray", L"pid"
																				, L"pkg_mkindex", L"private", L"proc", L"protected", L"public", L"puts", L"pwd", L"re_syntax", L"read", L"regexp", L"registry", L"regsub"
																				, L"rename", L"resource", L"return", L"safe", L"safebase", L"scan", L"scope", L"seek", L"set", L"socket", L"source", L"split"
																				, L"string", L"subst", L"switch", L"tcl", L"tcl_endofword", L"tcl_findlibrary", L"tcl_startofnextword", L"tcl_startofpreviousword", L"tcl_wordbreakafter"
																				, L"tcl_wordbreakbefore", L"tcltest", L"tclvars", L"tell", L"then", L"time", L"trace", L"unknown", L"unset"
																				, L"update", L"uplevel", L"upvar", L"variable", L"vwait", L"while"};
const String SecondTclTkKeys[92/*# range 0..91*/] = {L"bell", L"bind", L"bindidproc", L"bindproc", L"bindtags", L"bitmap", L"button", L"canvas", L"checkbutton", L"clipboard"
																				, L"colors", L"combobox", L"console", L"cursors", L"debug", L"destroy", L"entry", L"event", L"exp_after", L"exp_before", L"exp_continue"
																				, L"exp_internal", L"exp_send", L"expect", L"focus", L"font", L"frame", L"grab", L"grid", L"image", L"interact", L"interpreter"
																				, L"keysyms", L"label", L"labelframe", L"listbox", L"loadtk", L"log_file", L"log_user", L"lower", L"menu", L"menubutton"
																				, L"message", L"namespupd", L"option", L"options", L"pack", L"panedwindow", L"photo", L"place", L"radiobutton", L"raise"
																				, L"rgb", L"scale", L"scrollbar", L"selection", L"send", L"send_error", L"send_log", L"send_tty", L"send_user", L"sendout", L"sleep"
																				, L"spawn", L"spinbox", L"stty", L"text", L"tk", L"tk_bisque", L"tk_choosecolor", L"tk_choosedirectory", L"tk_dialog", L"tk_focusfollowsmouse"
																				, L"tk_focusnext", L"tk_focusprev", L"tk_getopenfile", L"tk_getsavefile", L"tk_menusetfocus", L"tk_messagebox"
																				, L"tk_optionmenu", L"tk_popup", L"tk_setpalette", L"tk_textcopy", L"tk_textcut", L"tk_textpaste", L"tkerror"
																				, L"tkvars", L"tkwait", L"toplevel", L"wait", L"winfo", L"wm"};
const String TixKeys[44/*# range 0..43*/] = {L"compound", L"pixmap", L"tix", L"tixballoon", L"tixbuttonbox", L"tixchecklist", L"tixcombobox", L"tixcontrol"
																				, L"tixdestroy", L"tixdirlist", L"tixdirselectdialog", L"tixdirtree", L"tixdisplaystyle", L"tixexfileselectbox", L"tixexfileselectdialog"
																				, L"tixfileentry", L"tixfileselectbox", L"tixfileselectdialog", L"tixform", L"tixgetboolean", L"tixgetint"
																				, L"tixgrid", L"tixhlist", L"tixinputonly", L"tixlabelentry", L"tixlabelframe", L"tixlistnotebook", L"tixmeter", L"tixmwm"
																				, L"tixnbframe", L"tixnotebook", L"tixoptionmenu", L"tixpanedwindow", L"tixpopupmenu", L"tixscrolledhlist", L"tixscrolledlistbox"
																				, L"tixscrolledtext", L"tixscrolledwindow", L"tixselect", L"tixstdbuttonbox", L"tixtlist", L"tixtree", L"tixutils"
																				, L"tixwish"};
const String WidgetKeys[33/*# range 0..32*/] = {L"ArrowButton", L"Button", L"ButtonBox", L"BWidget", L"ComboBox", L"Dialog", L"DragSite", L"DropSite", L"DynamicHelp"
																				, L"Entry", L"Label", L"LabelEntry", L"LabelFrame", L"ListBox", L"MainFrame", L"MessageDlg", L"NoteBook", L"PagesManager"
																				, L"PanedWindow", L"PasswdDlg", L"ProgressBar", L"ProgressDlg", L"ScrollableFrame", L"ScrollableWindow", L"ScrolledWindow"
																				, L"ScrollView", L"SelectColor", L"SelectFont", L"Separator", L"SpinBox", L"TitleFrame", L"Tree", L"Widget"};

bool __fastcall TSynTclTkSyn::InternalIsKeyword(const String AKeyword, TStrings* KeywordList, bool ACaseSensitive/*# = false*/)
{
	bool result = false;
	int First = 0;
	int Last = 0;
	int i = 0;
	int Compare = 0;
	String Token;
	First = 0;
	Last = KeywordList->Count - 1;
	result = false;
	if(ACaseSensitive)
		Token = AKeyword;
	else
		Token = Sysutils::AnsiLowerCase(AKeyword);
	while(First <= Last)
	{
		i = (First + Last) >> 1;
		Compare = CompareStr(KeywordList->Strings[i], Token);
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
}

bool __fastcall TSynTclTkSyn::IsKeyword(const String AKeyword)
{
	bool result = false;
	result = InternalIsKeyword(AKeyword, fWidgetWords, true) || InternalIsKeyword(AKeyword, fTixWords) || InternalIsKeyword(AKeyword, fKeywords) || InternalIsKeyword(AKeyword, fSecondKeys);
	return result;
}

__fastcall TSynTclTkSyn::TSynTclTkSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkSymbol),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fKeyAttri(nullptr),
			fSecondKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fCommentAttri(nullptr),
			fSpaceAttri(nullptr),
			fIdentifierAttri(nullptr),
			fOptionsAttri(nullptr),
			fVariableAttri(nullptr),
			fPathAttri(nullptr),
			fKeywords(nullptr),
			fSecondKeys(nullptr),
			fTixWords(nullptr),
			fTixKeyAttri(nullptr),
			fWidgetWords(nullptr),
			fWidgetKeyAttri(nullptr)
{
	int i = 0;
	int stop = 0;
	FCaseSensitive = false;
	fKeywords = new TStringList();
	((TStringList*) fKeywords)->Sorted = true;
	((TStringList*) fKeywords)->Duplicates = System::Classes::dupIgnore;
	fSecondKeys = new TStringList();
	((TStringList*) fSecondKeys)->Sorted = true;
	((TStringList*) fSecondKeys)->Duplicates = System::Classes::dupIgnore;
	fTixWords = new TStringList();
	((TStringList*) fTixWords)->Sorted = true;
	((TStringList*) fTixWords)->Duplicates = System::Classes::dupIgnore;
	fWidgetWords = new TStringList();
	((TStringList*) fWidgetWords)->Sorted = true;
	((TStringList*) fWidgetWords)->Duplicates = System::Classes::dupIgnore;
	fKeywords->BeginUpdate();
	for(stop = 128 /*# High(TclTkKeys) */, i = 0 /*# Low(TclTkKeys) */; i <= stop; i++)
	{
		fKeywords->Add(TclTkKeys[i]);
	}
	fKeywords->EndUpdate();
	fSecondKeys->BeginUpdate();
	for(stop = 91 /*# High(SecondTclTkKeys) */, i = 0 /*# Low(SecondTclTkKeys) */; i <= stop; i++)
	{
		fSecondKeys->Add(SecondTclTkKeys[i]);
	}
	fSecondKeys->EndUpdate();
	fTixWords->BeginUpdate();
	for(stop = 43 /*# High(TixKeys) */, i = 0 /*# Low(TixKeys) */; i <= stop; i++)
	{
		fTixWords->Add(TixKeys[i]);
	}
	fTixWords->EndUpdate();
	fWidgetWords->BeginUpdate();
	for(stop = 32 /*# High(WidgetKeys) */, i = 0 /*# Low(WidgetKeys) */; i <= stop; i++)
	{
		fWidgetWords->Add(WidgetKeys[i]);
	}
	fWidgetWords->EndUpdate();
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = SynHighlighterTclTk__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = SynHighlighterTclTk__1;
	addAttribute(fKeyAttri);
	fSecondKeyAttri = new TSynHighlighterAttributes(SYNS_AttrSecondReservedWord, SYNS_FriendlyAttrSecondReservedWord);
	fSecondKeyAttri->Style = SynHighlighterTclTk__2;
	addAttribute(fSecondKeyAttri);
	fTixKeyAttri = new TSynHighlighterAttributes(SYNS_AttrTixKeyWords, SYNS_FriendlyAttrTixKeyWords);
	fTixKeyAttri->Style = SynHighlighterTclTk__3;
	addAttribute(fTixKeyAttri);
	fWidgetKeyAttri = new TSynHighlighterAttributes(SYNS_AttrWidgetWords, SYNS_FriendlyAttrWidgetWords);
	fWidgetKeyAttri->Style = SynHighlighterTclTk__4;
	addAttribute(fWidgetKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	fOptionsAttri = new TSynHighlighterAttributes(SYNS_AttrOptions, SYNS_FriendlyAttrOptions);
	addAttribute(fOptionsAttri);
	fVariableAttri = new TSynHighlighterAttributes(SYNS_AttrVariable, SYNS_FriendlyAttrVariable);
	addAttribute(fVariableAttri);
	fPathAttri = new TSynHighlighterAttributes(SYNS_AttrPath, SYNS_FriendlyAttrPath);
	addAttribute(fPathAttri);
	fDefaultFilter = SYNS_FilterTclTk;
}

__fastcall TSynTclTkSyn::~TSynTclTkSyn()
{
	delete fWidgetWords;
	delete fTixWords;
	delete fSecondKeys;
	delete fKeywords;
	//# inherited::Destroy();
}


void __fastcall TSynTclTkSyn::AnsiProc()
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
	while(!IsLineEnd(Run))
		if(fLine[Run] == L'*')
		{
			if(fLine[Run + 1] == L')')
			{
				FRange = rsUnKnown;
				Run += 2;
				break;
			}
			else
			++Run;
		}
		else
		++Run;
}

void __fastcall TSynTclTkSyn::PasStyleProc()
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
	while(!IsLineEnd(Run))
		if(fLine[Run] == L'}')
		{
			FRange = rsUnKnown;
			++Run;
			break;
		}
		else
		++Run;
}

void __fastcall TSynTclTkSyn::CStyleProc()
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
	while(!IsLineEnd(Run))
		if(fLine[Run] == L'*')
		{
			if(fLine[Run + 1] == L'/')
			{
				FRange = rsUnKnown;
				Run += 2;
				break;
			}
			else
			++Run;
		}
		else
		++Run;
}

void __fastcall TSynTclTkSyn::BraceOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynTclTkSyn::PointCommaProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynTclTkSyn::CRProc()
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

void __fastcall TSynTclTkSyn::IdentProc()
{
	while(IsIdentChar(fLine[Run]))
		++Run;
	if(InternalIsKeyword(GetToken(), fWidgetWords, true))
		FTokenID = tkWidgetKey;
	else
	{
		if(InternalIsKeyword(GetToken(), fTixWords))
			FTokenID = tkTixKey;
		else
		{
			if(InternalIsKeyword(GetToken(), fKeywords))
				FTokenID = tkKey;
			else
			{
				if(InternalIsKeyword(GetToken(), fSecondKeys))
					FTokenID = tkSecondKey;
				else
					FTokenID = tkIdentifier;
			}
		}
	}
}

void __fastcall TSynTclTkSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynTclTkSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynTclTkSyn::NumberProc()
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

void __fastcall TSynTclTkSyn::RoundOpenProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynTclTkSyn::SlashProc()
{
	if(fLine[Run] == L'#')
	{
		FTokenID = tkComment;
		while(!IsLineEnd(Run))
			++Run;
	}
	else
	{
		FTokenID = tkSymbol;
		++Run;
	}
}

void __fastcall TSynTclTkSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynTclTkSyn::StringProc()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\x22') && (fLine[Run + 2] == L'\x22'))
		Run += 2;
	do
	{
		if(IsLineEnd(Run))
			break;
		++Run;
	}
	while(!((fLine[Run] == L'\x22') && (fLine[Pred(Run)] != L'\\')));
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynTclTkSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynTclTkSyn::Next()
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
		switch(fLine[Run])
		{
			case L'-':
			MinusProc();
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
			case L'[':
			case L']':
			case L')':
			case L'}':
			SymbolProc();
			break;
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			case L'\x0b':
			case L'\x0c':
			case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
			 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
			SpaceProc();
			break;
			case L'\x22':
			StringProc();
			break;
			case L'$':
			VariableProc();
			break;
			case L'.':
			PathProc();
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynTclTkSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynTclTkSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

void* __fastcall TSynTclTkSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynTclTkSyn::GetTokenID()
{
	TtkTokenKind result = tkSymbol;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynTclTkSyn::GetTokenAttribute()
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
		case tkTixKey:
		result = fTixKeyAttri;
		break;
		case tkWidgetKey:
		result = fWidgetKeyAttri;
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
		case tkOptions:
		result = fOptionsAttri;
		break;
		case tkVariable:
		result = fVariableAttri;
		break;
		case tkPath:
		result = fPathAttri;
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

int __fastcall TSynTclTkSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynTclTkSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynTclTkSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(int)Value;
}

void __fastcall TSynTclTkSyn::SetKeyWords(TStrings* const Value)
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
	fKeywords->Assign(Value);
	DefHighlightChange(nullptr);
}

void __fastcall TSynTclTkSyn::SetSecondKeys(TStrings* const Value)
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
	fSecondKeys->Assign(Value);
	DefHighlightChange(nullptr);
}

bool __fastcall TSynTclTkSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterTclTk;
	return result;
}

/*#static*/
String __fastcall TSynTclTkSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangTclTk;
	return result;
}

bool __fastcall TSynTclTkSyn::LoadFromRegistry(HKEY RootKey, String key)
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

bool __fastcall TSynTclTkSyn::SaveToRegistry(HKEY RootKey, String key)
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

bool __fastcall TSynTclTkSyn::IsKeywordListStored()
{
	bool result = false;
	TStringList* Keys = nullptr;
	int DefKey = 0;
	int Index = 0;
	Keys = new TStringList();
	try
	{
		int stop = 0;
		Keys->Assign(Keywords);
		Index = 0;
		for(stop = 128 /*# High(TclTkKeys) */, DefKey = 0 /*# Low(TclTkKeys) */; DefKey <= stop; DefKey++)
		{
			if(!Keys->Find(TclTkKeys[DefKey], Index))
			{
				result = true;
				return result;
			}
			Keys->Delete(Index);
		}
		result = Keys->Count != 0;
	}
	__finally
	{
		delete Keys;
	}
	return result;
}

String __fastcall TSynTclTkSyn::GetSampleSource()
{
	String result;
	result = L"#!/usr/local/tclsh8.0\x0d\x0a"
	           L"if {$argc < 2} {\x0d\x0a"
	           L"	puts stderr \"Usage: $argv0 parameter\"\x0d\x0a"
	           L"	exit 1\x0d\x0a"
	           L"}";
	return result;
}

/*#static*/
String __fastcall TSynTclTkSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangTclTk;
	return result;
}

void __fastcall TSynTclTkSyn::MinusProc()
{
	const TSysCharSet EmptyChars = TSysCharSet() << L' ' << L'\x09' << L'\x00' << L'\x0a' << L'\x0d';
	bool OK = false;
	OK = false;
	++Run;
  /* minus like symbol */
	if(CharInSet(fLine[Run], SynHighlighterTclTk__5))
		FTokenID = tkSymbol;
	else
	{
		if((fLine[Run] == L'-') && CharInSet(fLine[Run + 1], EmptyChars))
  /* special option -- */
		{
			OK = true;
			++Run;
  /* normal options -options */
		}
		else
		{
			if(CharInSet(fLine[Run], SynHighlighterTclTk__6))
			{
				++Run;
				while(CharInSet(fLine[Run], SynHighlighterTclTk__7))
					++Run;
				OK = CharInSet(fLine[Run], EmptyChars);
    /* bad option syntax */
			}
			else
			{
				while(!CharInSet(fLine[Run], EmptyChars))
					++Run;
			}
		}
	}
	if(OK)
		FTokenID = tkOptions;
	else
		FTokenID = tkUnknown;
}

void __fastcall TSynTclTkSyn::PathProc()
{
	if(CharInSet(fLine[Run + 1], SynHighlighterTclTk__8))
	{
		FTokenID = tkPath;
		++Run;
		while(CharInSet(fLine[Run], SynHighlighterTclTk__9))
			++Run;
	}
	else
	{
		FTokenID = tkSymbol;
		++Run;
	}
}

void __fastcall TSynTclTkSyn::VariableProc()
{
	FTokenID = tkVariable;
	++Run;
	while(CharInSet(fLine[Run], SynHighlighterTclTk__10))
		++Run;
}

bool __fastcall TSynTclTkSyn::IsSecondKeywordListStored()
{
	bool result = false;
	TStringList* Keys = nullptr;
	int DefKey = 0;
	int Index = 0;
	Keys = new TStringList();
	try
	{
		int stop = 0;
		Keys->Assign(SecondKeyWords);
		Index = 0;
		for(stop = 91 /*# High(SecondTclTkKeys) */, DefKey = 0 /*# Low(SecondTclTkKeys) */; DefKey <= stop; DefKey++)
		{
			if(!Keys->Find(SecondTclTkKeys[DefKey], Index))
			{
				result = true;
				return result;
			}
			Keys->Delete(Index);
		}
		result = Keys->Count != 0;
	}
	__finally
	{
		delete Keys;
	}
	return result;
}

void __fastcall TSynTclTkSyn::SymbolProc()
{
	FTokenID = tkSymbol;
	++Run;
}
static bool SynHighlighterTclTk_Initialized = false;

void SynHighlighterTclTk_initialization()
{
	if(SynHighlighterTclTk_Initialized)
		return;
	
	SynHighlighterTclTk_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynTclTkSyn));
}
class SynHighlighterTclTk_unit
{
public:
	SynHighlighterTclTk_unit()
	{
		SynHighlighterTclTk_initialization();
	}
};

SynHighlighterTclTk_unit _SynHighlighterTclTk_unit;

}  // namespace SynHighlighterTclTk

