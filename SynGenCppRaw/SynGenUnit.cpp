#include <vcl.h>
#pragma hdrstop

#include "SynGenUnit.h"
#include <System.UITypes.hpp>
#include <System.StrUtils.hpp>
#include <System.Win.Registry.hpp>
#include "HashTableGen.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Genlex;
using namespace System;
using namespace System::Classes;
using namespace System::Strutils;
using namespace System::Sysutils;
using namespace System::Uitypes;
using namespace System::Win::Registry;
using namespace Vcl::Dialogs;
using namespace Vcl::Forms;
using namespace Vcl::Stdctrls;

#define SynGenUnit__0 (TReplaceFlags() << System_Sysutils__95::rfReplaceAll)
#define SynGenUnit__1 (TSysCharSet() << L'_' <<  \
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
#define SynGenUnit__2 (TSysCharSet() << L'_' <<  \
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
#define SynGenUnit__3 (System::Set<TIdTokenKind, IdBeginFunc, IdUnknown>() << TIdTokenKind::IdSensitive << TIdTokenKind::IdIdentStart)
#define SynGenUnit__4 (TMsgDlgButtons() << System::Uitypes::TMsgDlgBtn::mbOK)
#define SynGenUnit__5 (System::Set<TIdTokenKind, IdBeginFunc, IdUnknown>() << TIdTokenKind::IdSpace << TIdTokenKind::IdBraceOpen)
#define SynGenUnit__6 (System::Set<TIdTokenKind, IdBeginFunc, IdUnknown>() << TIdTokenKind::IdSpace << TIdTokenKind::IdBraceOpen << TIdTokenKind::IdCRLF)
#define SynGenUnit__7 (System::Set<TIdTokenKind, IdBeginFunc, IdUnknown>() << TIdTokenKind::IdSpace << TIdTokenKind::IdBraceOpen << TIdTokenKind::IdCRLF)
#define SynGenUnit__8 (System::Set<TIdTokenKind, IdBeginFunc, IdUnknown>() << TIdTokenKind::IdSpace << TIdTokenKind::IdBraceOpen << TIdTokenKind::IdCRLF << TIdTokenKind::IdUnknown)
#define SynGenUnit__9 (System::Set<TIdTokenKind, IdBeginFunc, IdUnknown>() << TIdTokenKind::IdStop << TIdTokenKind::IdCRLF)
#define SynGenUnit__10 (System::Set<TIdTokenKind, IdBeginFunc, IdUnknown>() << TIdTokenKind::IdStop << TIdTokenKind::IdNull)
#define SynGenUnit__11 (System::Set<TIdTokenKind, IdBeginFunc, IdUnknown>() << TIdTokenKind::IdStop << TIdTokenKind::IdNull)
#define SynGenUnit__12 (System::Set<TIdTokenKind, IdBeginFunc, IdUnknown>() << TIdTokenKind::IdCRLF << TIdTokenKind::IdSpace)
#define SynGenUnit__13 (System::Set<TIdTokenKind, IdBeginFunc, IdUnknown>() << TIdTokenKind::IdCRLF << TIdTokenKind::IdNull << TIdTokenKind::IdStop)
#define SynGenUnit__14 (System::Set<TIdTokenKind, IdBeginFunc, IdUnknown>() << TIdTokenKind::IdCRLF << TIdTokenKind::IdSpace)
#define SynGenUnit__15 (System::Set<TIdTokenKind, IdBeginFunc, IdUnknown>() << TIdTokenKind::IdCRLF << TIdTokenKind::IdNull << TIdTokenKind::IdStop)

__fastcall TLexKeys::TLexKeys() {}
__fastcall TLexCharsets::TLexCharsets() {}
__fastcall TFrmMain::TFrmMain(System::Classes::TComponent* AOwner) : inherited(AOwner) {}


int mKeyHashTable[256/*# range #0..#255*/];
int mSKeyHashTable[256/*# range #0..#255*/];
TFrmMain* FrmMain = nullptr;
#pragma resource "*.dfm" 

const String BoolStrs[2/*# boolean*/] = {L"False", L"True"}; // Do not localize

int __fastcall CompareKeys(void* Item1, void* Item2)
{
	int result = 0;
	result = AnsiCompareStr(((TLexKeys*) Item1)->KeyName, ((TLexKeys*) Item2)->KeyName);
	return result;
}

int __fastcall CompareSets(void* Item1, void* Item2)
{
	int result = 0;
	result = 0;
	if(((TLexCharsets*) Item1)->SetName < ((TLexCharsets*) Item2)->SetName)
		result = -1;
	else
	{
		if(((TLexCharsets*) Item1)->SetName > ((TLexCharsets*) Item2)->SetName)
			result = 1;
	}
	return result;
}

String __fastcall AddInt(int AValue)
{
	String result;
	if(AValue < 0)
		result = String(L" - ") + IntToStr(Abs(AValue));
	else
	{
		if(AValue > 0)
			result = String(L" + ") + IntToStr(AValue);
		else
			result = L"";
	}
	return result;
}

String __fastcall StuffString(const String Value)
{
	String result;
	int i = 0;
	int stop = 0;
	result = L"";
	for(stop = (int) Value.Length(), i = 1; i <= stop; i++)
	{
		if(Value[i] == L'\'')
			result = result + L"''";
		else
			result = result + String(Value[i]);
	}
	return result;
}

String __fastcall FirstLetterCap(String s)
{
	String result;
	result = Sysutils::AnsiLowerCase(s);
	if(result.Length() > 0)
		result[1] = Sysutils::AnsiUpperCase(String(s[1]))[1];
	return result;
}

String __fastcall AnsiReplaceStr(const String AText, const String AFromText, const String AToText)
{
	String result;
	result = StringReplace(AText, AFromText, AToText, SynGenUnit__0);
	return result;
}

String __fastcall ToAlphaNum(String s)
{
	String result;
	Char C = L'\0';
	Char stop = 0;
	for(stop = L'\x2f', C = L'\x21'; C <= stop; C++)
	{
		s = ::AnsiReplaceStr(s, String(C), IntToStr(int(C)));
	}
	for(stop = L'\x40', C = L'\x3a'; C <= stop; C++)
	{
		s = ::AnsiReplaceStr(s, String(C), IntToStr(int(C)));
	}
	for(stop = L'\x60', C = L'\x5b'; C <= stop; C++)
	{
		s = ::AnsiReplaceStr(s, String(C), IntToStr(int(C)));
	}
	for(stop = L'\xbf', C = L'\x7b'; C <= stop; C++)
	{
		s = ::AnsiReplaceStr(s, String(C), IntToStr(int(C)));
	}
	result = s;
	return result;
}

bool __fastcall IsASCIIAlphaNum(String s)
{
	bool result = false;
	int i = 0;
	int stop = 0;
	result = true;
	s = ToAlphaNum(s);
	for(stop = (int) s.Length(), i = 1; i <= stop; i++)
	{
		switch(s[i])
		{
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'_':
			;
			break;
			default:
			result = false;
			return result;
			break;
		}
	}
	return result;
}

__fastcall TLexEnclosedBy::TLexEnclosedBy()
 : TokenName(L""),
			ProcName(L""),
			StartsWith(L""),
			EndsWith(L""),
			MultiLine(false)
{
	//# inherited::Create();
}

__fastcall TLexDefaultAttri::TLexDefaultAttri()
 : Style(L""),
			Foreground(L""),
			Background(L"")
{
	//# inherited::Create();
}

void __fastcall TFrmMain::MakeSensitiveHashTable()
{
	Char i = L'\0';
	Char stop = 0;
	for(stop = L'\xff', i = L'\x00'; i <= stop; i++)
	{
		switch(CharInSet(i, SynGenUnit__1))
		{
			case true:
			{
				if((i > L'\x40') && (i < L'\x5b'))
					mSKeyHashTable[i] = int(i) - 64;
				else
				{
					if(i > L'\x60')
						mSKeyHashTable[i] = int(i) - 95;
				}
			}
			break;
			default:
			mSKeyHashTable[i] = 0;
			break;
		}
	}
}

void __fastcall TFrmMain::MakeHashTable()
{
	Char i = L'\0';
	Char j = L'\0';
	Char stop = 0;
	for(stop = L'\xff', i = L'\x00'; i <= stop; i++)
	{
		j = UpperCase(String(i))[1];
		switch(CharInSet(i, SynGenUnit__2))
		{
			case true:
			mKeyHashTable[i] = int(j) - 64;
			break;
			default:
			mKeyHashTable[i] = 0;
			break;
		}
	}
}

void __fastcall TFrmMain::WriteSettings()
{
	/*# with TRegIniFile.Create(IniFile) do */
	{
		auto with0 = new TRegIniFile(IniFile);
		try
		{
			with0->WriteString(L"General", L"OpenDir", OpenDialog->InitialDir);
			with0->WriteBool(FFileName, L"GetKeyWords", ChkGetKeyWords->Checked);
			with0->WriteBool(FFileName, L"ChkGPLHeader", ChkGPLHeader->Checked);
			with0->WriteString(FFileName, L"Author", EditAuthor->Text);
			with0->WriteString(FFileName, L"Description", EditDescription->Text);
			with0->WriteString(FFileName, L"Version", EditVersion->Text);
			with0->WriteString(FFileName, L"Filter", CboFilter->Text);
			with0->WriteString(FFileName, L"Language", CboLangName->Text);
			with0->WriteString(FFileName, L"AttrIdentifier", CboAttrIdentifier->Text);
			with0->WriteString(FFileName, L"AttrReservedWord", CboAttrReservedWord->Text);
			with0->WriteString(FFileName, L"UnknownTokenAttr", CboUnknownTokenAttr->Text);
			with0->WriteString(FFileName, L"Fields", ListBoxFields->Items->CommaText);
		}
		__finally
		{
			delete with0;
		}
	}
}

bool __fastcall TFrmMain::PerformFileOpen()
{
	bool result = false;
	PChar Username = nullptr;
	unsigned int Count = 0;
	if(OpenDialog->Execute())
	{
		Count = 0;
		result = true;
		FFileName = ExtractFileName(OpenDialog->FileName);
		Caption = String(L"SynGen - ") + FFileName;
		Application->Title = Caption;
		OpenDialog->InitialDir = ExtractFilePath(OpenDialog->FileName);
		GetUserName(nullptr, &Count);
    // retrieve the required size of the user name buffer
		Username = StrAlloc(Count); // allocate memory for the user name
		GetUserName(Username, &Count); // retrieve the user name
		/*# with TRegIniFile.Create(IniFile) do */
		{
			auto with0 = new TRegIniFile(IniFile);
			try
			{
				EditAuthor->Text = with0->ReadString(FFileName, L"Author", StrPas(Username));
				EditDescription->Text = with0->ReadString(FFileName, L"Description", L"Syntax Parser/Highlighter");
				EditVersion->Text = with0->ReadString(FFileName, L"Version", L"0.1");
				CboFilter->Text = with0->ReadString(FFileName, L"Filter", L"All files (*.*)|*.*");
				CboLangName->Text = with0->ReadString(FFileName, L"Language", L"");
				ChkGetKeyWords->Checked = with0->ReadBool(FFileName, L"GetKeyWords", true);
				ChkGPLHeader->Checked = with0->ReadBool(FFileName, L"ChkGPLHeader", true);
				CboAttrIdentifier->ItemIndex = CboAttrIdentifier->Items->IndexOf(with0->ReadString(FFileName, L"AttrIdentifier", L"SYNS_AttrIdentifier"));
				CboAttrReservedWord->ItemIndex = CboAttrReservedWord->Items->IndexOf(with0->ReadString(FFileName, L"AttrReservedWord", L"SYNS_AttrReservedWord"));
				CboUnknownTokenAttr->ItemIndex = CboUnknownTokenAttr->Items->IndexOf(with0->ReadString(FFileName, L"UnknownTokenAttr", L"Identifier"));
				ListBoxFields->Items->CommaText = with0->ReadString(FFileName, L"Fields", L"");
			}
			__finally
			{
				delete with0;
			}
		}
		StrDispose(Username);
		CboLangNameChange(this);
	}
	else
	result = false;
	return result;
}

void __fastcall TFrmMain::FormCreate(TObject* Sender)
{
	int i = 0;
	int stop = 0;
	for(stop = 0, i = FrmMain->ComponentCount - 1; i >= stop; i--)
	{
		if(ObjectIs(FrmMain->Components[i], TComboBox*))
		{
			if(((TComboBox*) FrmMain->Components[i])->Parent == GrpAttrNames)
			{
				((TComboBox*) FrmMain->Components[i])->Items->Clear();
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrAsm");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrAsmComment");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrAsmKey");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrASP");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrAssembler");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrBlock");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrBrackets");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrCharacter");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrClass");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrComment");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrCondition");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrDir");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrDirective");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrDocumentation");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrEmbedSQL");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrEmbedText");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrEscapeAmpersand");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrForm");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrFunction");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrIcon");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrIdentifier");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrIllegalChar");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrIndirect");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrInvalidSymbol");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrInternalFunction");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrKey");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrLabel");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrMacro");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrMarker");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrMessage");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrMiscellaneous");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrNull");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrNumber");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrOperator");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrPragma");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrPreprocessor");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrQualifier");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrRegister");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrReservedWord");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrRpl");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrRplKey");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrRplComment");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrSASM");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrSASMComment");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrSASMKey");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrSecondReservedWord");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrSection");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrSpace");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrSpecialVariable");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrString");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrSymbol");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrSyntaxError");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrSystem");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrSystemValue");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrText");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrUnknownWord");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrUser");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrUserFunction");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrValue");
				((TComboBox*) FrmMain->Components[i])->Items->Add(L"SYNS_AttrVariable");
			}
		}
	}
	PageControl->ActivePage = PageControl->Pages[0];
	Lex = new TGenLex();
	KeyList = new TList();
	SetList = new TList();
	EnclosedList = new TList();
	SampleSourceList = new TStringList();
	IdentList = new TStringList();
  // read ini file
	IniFile = ExtractFileName(Application->ExeName).SubString(0, ExtractFileName(Application->ExeName).Length() - ExtractFileExt(Application->ExeName).Length())
	           + L".ini";
	/*# with TRegIniFile.Create(IniFile) do */
	{
		auto with0 = new TRegIniFile(IniFile);
		try
		{
			OpenDialog->InitialDir = with0->ReadString(L"General", L"OpenDir", ExtractFilePath(Application->ExeName));
		}
		__finally
		{
			delete with0;
		}
	}

  /* Move form off the screen, but show already, to activate it correctly when
    OpenFileDialog is closed with OK. */
	Left = -10000;
	Show();
	if(PerformFileOpen())
	{
		MakeHashTable();
		MakeSensitiveHashTable();
		Position = TPosition::poScreenCenter; // move form on the screen ("make visible")
	}
	else
	Application->Terminate();
}

void __fastcall TFrmMain::ClearAll()
{
	int i = 0;
  // Clear the contents of KeyList
	int stop = 0;
	for(stop = (KeyList->Count - 1), i = 0; i <= stop; i++)
	{
		delete ((TObject*) KeyList->Items[i]);
	}
	KeyList->Clear();
  // Clear the contents of SetList
	for(stop = (SetList->Count - 1), i = 0; i <= stop; i++)
	{
		delete ((TObject*) SetList->Items[i]);
	}
	SetList->Clear();
  // Clear the contents of EnclosedList
	for(stop = (EnclosedList->Count - 1), i = 0; i <= stop; i++)
	{
		delete ((TObject*) EnclosedList->Items[i]);
	}
	EnclosedList->Clear();
  // Clear the contents of IdentList
	for(stop = (IdentList->Count - 1), i = 0; i <= stop; i++)
	{
		if(ASSIGNED(IdentList->Objects[i]))
			delete IdentList->Objects[i];
	}
	IdentList->Clear();
  // Clear the contents of SampleSourceList
	SampleSourceList->Clear();
}

void __fastcall TFrmMain::FormDestroy(TObject* Sender)
{
	ClearAll();
	delete Lex;
	delete IdentList;
	delete KeyList;
	delete SetList;
	delete EnclosedList;
}

void __fastcall TFrmMain::BtnStartClick(TObject* Sender)
{
	TUnicodeStringList LexFileLines;
	ClearAll();
	Screen->Cursor = crHourGlass;
	LexFileLines = new TUnicodeStringList();
	try
	{
		LexFileLines.LoadFromFile(OpenDialog->FileName.c_str());
		LexFileContents = LexFileLines.Text;
	}
	__finally
	{
		delete LexFileLines;
	}
	Lex->Origin = ustr2pwchar(LexFileContents);
	Lex->Tokenize();
	while(Lex->RunId != TIdTokenKind::IdIdentifier)
		Lex->Next();
	LexName = Lex->RunToken;
	Lex->Next();
	while(Lex->RunId != TIdTokenKind::IdIdentifier)
		Lex->Next();
	IdentPre = Lex->RunToken;
	OutFileCreate(OpenDialog->FileName);
	try
	{
		while(!(SynGenUnit__3.Contains(Lex->RunId)))
			Lex->Next();
		if(Lex->RunId == TIdTokenKind::IdSensitive)
			Sensitivity = true;
		else
			Sensitivity = false;
		Lex->Next();
		while(Lex->RunId != TIdTokenKind::IdCharset)
			Lex->Next();
		IdentStart = Lex->RunToken;
		Lex->Next();
		while(Lex->RunId != TIdTokenKind::IdNull)
		{
			switch(Lex->RunId)
			{
				case TIdTokenKind::IdCharset:
				IdentContent = Lex->RunToken;
				break;
				case TIdTokenKind::IdKeys:
				FillKeyList();
				break;
				case TIdTokenKind::IdTokenTypes:
				FillTokenTypeList();
				break;
				case TIdTokenKind::IdChars:
				ParseCharsets();
				break;
				case TIdTokenKind::IdEnclosedBy:
				ParseEnclosedBy();
				break;
				case TIdTokenKind::IdSampleSource:
				ParseSampleSource();
				break;
				default:
				  ;
				break;
			}
			Lex->Next();
		}
		if(KeyList->Count == 0)
			throw new Exception(L"You should specify at least 1 keyword!");
		if(IdentList->Count == 0)
			throw new Exception(L"You should specify at least 1 token type");
		if(!KeywordsAreAllAlphaNumAndDifferent())
			throw new Exception(L"One or more keywords contain unhandable characters");
		FrmHashTableGen->AssignKeyWords(KeyList, Sensitivity);
		FrmHashTableGen->ShowModal();
		WriteRest();
		while((Lex->RunId != TIdTokenKind::IdNull))
		{
			Lex->Next();
		}
	}
	__finally
	{
		Screen->Cursor = crDefault;
		CloseFile(OutFile);
	}
	MessageDlg(LexName + L" created on " + DateTimeToStr(Now()), System::Uitypes::TMsgDlgType::mtInformation, SynGenUnit__4, 0);
}

void __fastcall TFrmMain::FillKeyList()
{
	TLexKeys* aLexKey = nullptr;
	String AString;
	String aTokenType;
	Lex->Next();
	aTokenType = L"";
	while(Lex->RunId != TIdTokenKind::IdCRLF)
	{
		if(!(SynGenUnit__5.Contains(Lex->RunId)))
			aTokenType = aTokenType + Lex->RunToken;
		Lex->Next();
	}
	if(aTokenType == L"")
		aTokenType = L"Key";
	while(Lex->RunId != TIdTokenKind::IdStop)
	{
		while(SynGenUnit__6.Contains(Lex->RunId))
			Lex->Next();
		if(Lex->RunId != TIdTokenKind::IdStop)
		{
			AString = L"";
			while(!(SynGenUnit__7.Contains(Lex->RunId)))
			{
				AString = AString + Lex->RunToken;
				Lex->Next();
			}
			aLexKey = new TLexKeys();
			aLexKey->TokenType = aTokenType;
			aLexKey->KeyName = AString;
			KeyList->Add(aLexKey);
		}
		else
		break;
		Lex->Next();
	}
	KeyList->Sort(CompareKeys);
}

void __fastcall TFrmMain::FillTokenTypeList()
{
	int i = 0;
	TStringList* List = nullptr;
	String sIdent;
	String sLine;
	TLexDefaultAttri* DefAttri = nullptr;
	Lex->Next();
	IdentList->Add(IdentPre + L"Unknown");
	IdentList->Add(IdentPre + L"Null");
	while((Lex->RunId != TIdTokenKind::IdStop))
	{
		while(SynGenUnit__8.Contains(Lex->RunId))
			Lex->Next();
		if(Lex->RunId != TIdTokenKind::IdStop)
		{
			sIdent = IdentPre + Lex->RunToken;
			if(!IsValidIdent(sIdent))
				throw new Exception(String(L"Invalid identifier for token type: ") + sIdent);
			if(IdentList->IndexOf(sIdent) < 0)
				IdentList->Add(sIdent);
			Lex->Next();
			sLine = L"";
			while((Lex->RunId == TIdTokenKind::IdSpace))
				Lex->Next();
			while(!(SynGenUnit__9.Contains(Lex->RunId)))
 /* is there more data on this line? */
			{
				sLine = sLine + Lex->RunToken;
				Lex->Next();
			}
			if(sLine != L"") /* The Msg file specifies default attributes */
			{
				List = new TStringList();
				try
				{
					while((sLine != L""))
					{
						i = Pos(L"|", sLine);
						if(i > 0)
						{
							List->Add(sLine.SubString(1, i - 1));
							sLine.Delete(1, 	i);
						}
						else
						{
							List->Add(sLine);
							sLine = L"";
						}
					}
					i = IdentList->IndexOf(sIdent);
					if(i >= 0)
					{
						DefAttri = new TLexDefaultAttri();
						DefAttri->Style = List->Values[L"Style"];
						DefAttri->Foreground = List->Values[L"Foreground"];
						DefAttri->Background = List->Values[L"Background"];
						IdentList->Objects[i] = DefAttri;
					}
				}
				__finally
				{
					delete List;
				}
			}
		}
		else
		break;
	}
}

void __fastcall TFrmMain::OutFileCreate(String InName)
{
	String OutName;
	String UName;
	TSystemTime SysTime = {};
	String ISODate;
	OutName = ChangeFileExt(InName, L".pas");
	UName = ExtractFileName(ChangeFileExt(InName, L""));
	AssignFile(OutFile, OutName);
	Rewrite(OutFile);
	GetSystemTime(&SysTime);
	ISODate = Format(L"%.4d-%.2d-%.2d", ARRAYOFCONST((SysTime.wYear, SysTime.wMonth, SysTime.wDay)));
	if(ChkGPLHeader->Checked)
	{
		WriteLn(OutFile, L"{-------------------------------------------------------------------------------");
		WriteLn(OutFile, L"The contents of this file are subject to the Mozilla Public License");
		WriteLn(OutFile, L"Version 1.1 (the \"License\"); you may not use this file except in compliance");
		WriteLn(OutFile, L"with the License. You may obtain a copy of the License at");
		WriteLn(OutFile, L"http://www.mozilla.org/MPL/");
		WriteLn(OutFile);
		WriteLn(OutFile, L"Software distributed under the License is distributed on an \"AS IS\" basis,");
		WriteLn(OutFile, L"WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for");
		WriteLn(OutFile, L"the specific language governing rights and limitations under the License.");
		WriteLn(OutFile);
		WriteLn(OutFile, L"Code template generated with SynGen.");
		WriteLn(OutFile, String(L"The original code is: ") + OutName
		           + L", released "
		           + ISODate
		           + L".");
		WriteLn(OutFile, String(L"Description: ") + EditDescription->Text);
		WriteLn(OutFile, String(L"The initial author of this file is ") + EditAuthor->Text
		           + L".");
		WriteLn(OutFile, String(L"Copyright (c) ") + Format(L"%d", ARRAYOFCONST((SysTime.wYear)))
	           + L", all rights reserved.");
		WriteLn(OutFile);
		WriteLn(OutFile, L"Contributors to the SynEdit and mwEdit projects are listed in the");
		WriteLn(OutFile, L"Contributors.txt file.");
		WriteLn(OutFile);
		WriteLn(OutFile, L"Alternatively, the contents of this file may be used under the terms of the");
		WriteLn(OutFile, L"GNU General Public License Version 2 or later (the \"GPL\"), in which case");
		WriteLn(OutFile, L"the provisions of the GPL are applicable instead of those above.");
		WriteLn(OutFile, L"If you wish to allow use of your version of this file only under the terms");
		WriteLn(OutFile, L"of the GPL and not to allow others to use your version of this file");
		WriteLn(OutFile, L"under the MPL, indicate your decision by deleting the provisions above and");
		WriteLn(OutFile, L"replace them with the notice and other provisions required by the GPL.");
		WriteLn(OutFile, L"If you do not delete the provisions above, a recipient may use your version");
		WriteLn(OutFile, L"of this file under either the MPL or the GPL.");
		WriteLn(OutFile);
		WriteLn(OutFile, L"$" L"Id: " L"$");
		WriteLn(OutFile);
		WriteLn(OutFile, L"You may retrieve the latest version of this file at the SynEdit home page,");
		WriteLn(OutFile, L"located at http://SynEdit.SourceForge.net");
		WriteLn(OutFile);
		WriteLn(OutFile, L"-------------------------------------------------------------------------------}");
	}
	else
	{
		WriteLn(OutFile, L"{+-----------------------------------------------------------------------------+");
		WriteLn(OutFile, String(L" | Class:       ") + LexName);
		WriteLn(OutFile, String(L" | Created:     ") + ISODate);
		WriteLn(OutFile, String(L" | Last change: ") + ISODate);
		WriteLn(OutFile, String(L" | Author:      ") + EditAuthor->Text);
		WriteLn(OutFile, String(L" | Description: ") + EditDescription->Text);
		WriteLn(OutFile, String(L" | Version:     ") + EditVersion->Text);
		WriteLn(OutFile, L" |");
		WriteLn(OutFile, String(L" | Copyright (c) ") + Format(L"%d", ARRAYOFCONST((SysTime.wYear)))
	           + L"\x20"
	           + EditAuthor->Text
	           + L". All rights reserved.");
		WriteLn(OutFile, L" |");
		WriteLn(OutFile, L" | Generated with SynGen.");
		WriteLn(OutFile, L" +----------------------------------------------------------------------------+}");
	}
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"unit ") + UName + L";");
	WriteLn(OutFile);
	WriteLn(OutFile, L"interface");
	WriteLn(OutFile);
	WriteLn(OutFile, L"uses");
	WriteLn(OutFile, L"  Graphics,");
	WriteLn(OutFile, L"  SynEditTypes,");
	WriteLn(OutFile, L"  SynEditHighlighter,");
	WriteLn(OutFile, L"  SynUnicode,");
	WriteLn(OutFile, L"  SysUtils,");
	WriteLn(OutFile, L"  Classes;");
	WriteLn(OutFile);
	WriteLn(OutFile, L"type");
	WriteLn(OutFile, String(L"  T") + IdentPre + L"TokenKind = (");
}

void __fastcall TFrmMain::ParseCharsets()
{
	Lex->Next();
	while(Lex->RunId != TIdTokenKind::IdStop)
	{
		switch(Lex->RunId)
		{
			case TIdTokenKind::IdCharset:
			RetrieveCharset();
			break;
			default:
			Lex->Next();
			break;
		}
	}
}

void __fastcall TFrmMain::ParseEnclosedBy()
{
	Lex->Next();
	while(!(SynGenUnit__10.Contains(Lex->RunId)))
		RetrieveEnclosedBy();
}

void __fastcall TFrmMain::ParseSampleSource()
{
	Lex->Next();
	if(Lex->RunId == TIdTokenKind::IdCRLF)
		Lex->Next();
	while(!(SynGenUnit__11.Contains(Lex->RunId)))
		RetrieveSampleSource();
}

void __fastcall TFrmMain::RetrieveCharset()
{
	TLexCharsets* aSet = nullptr;
	aSet = new TLexCharsets();
	aSet->Charset = Lex->RunToken;
	while(Lex->RunId != TIdTokenKind::IdIdentifier)
		Lex->Next();
	aSet->SetName = Lex->RunToken;
	while(Lex->RunId != TIdTokenKind::IdBeginProc)
		Lex->Next();
	Lex->Next();
	while(SynGenUnit__12.Contains(Lex->RunId))
		Lex->Next();
	while(!(Lex->RunId == TIdTokenKind::IdEndProc))
	{
		aSet->ProcData = aSet->ProcData + Lex->RunToken;
		Lex->Next();
	}
	SetList->Add(aSet);
	Lex->Next();
}

void __fastcall TFrmMain::RetrieveSampleSource()
{
	String sLine;
	sLine = L"";
	while(!(SynGenUnit__13.Contains(Lex->RunId)))
	{
		sLine = sLine + Lex->RunToken;
		Lex->Next();
	}
	if(Lex->RunId == TIdTokenKind::IdCRLF)
		Lex->Next();
	SampleSourceList->Add(sLine);
}

void __fastcall TFrmMain::RetrieveEnclosedBy()
{
	TLexEnclosedBy* aThing = nullptr;
	String sLine;
	int iPos = 0;
	while(SynGenUnit__14.Contains(Lex->RunId))
		Lex->Next();
	sLine = L"";
	while(!(SynGenUnit__15.Contains(Lex->RunId)))
	{
		sLine = sLine + Lex->RunToken;
		Lex->Next();
	}
	if(sLine != L"")
	{
		aThing = new TLexEnclosedBy();
		iPos = Pos(L",", sLine);
		aThing->TokenName = sLine.SubString(1, iPos - 1);
		sLine.Delete(1, 	iPos);
		iPos = Pos(L",", sLine);
		aThing->ProcName = sLine.SubString(1, iPos - 1);
		sLine.Delete(1, 	iPos);
		iPos = Pos(L",", sLine);
		aThing->StartsWith = sLine.SubString(1, iPos - 1);
		sLine.Delete(1, 	iPos);
		iPos = Pos(L",", sLine);
		if(iPos > 0)
		{
			aThing->EndsWith = sLine.SubString(1, iPos - 1);
			sLine.Delete(1, 	iPos);
			if(Pos(L"MULTILINE", UpperCase(sLine)) == 1)
				aThing->MultiLine = true;
		}
		else
		aThing->EndsWith = sLine;
		EnclosedList->Add(aThing);
	}
	else
	{
		if(Lex->RunId != TIdTokenKind::IdStop)
			Lex->Next();
	}
} /* RetrieveEnclosedBy */

String __fastcall TFrmMain::FilterInvalidChars(const String Value)
{
	String result;
	int i = 0;
	int stop = 0;
	result = L"";
	for(stop = (int) Value.Length(), i = 1; i <= stop; i++)
	{
		if(IsValidIdent(result + String(Value[i])))
			result = result + String(Value[i]);
	}
	return result;
} /* FilterInvalidChars */

String __fastcall TFrmMain::GetFilterName()
{
	String result;
	String FilterName;
	FilterName = L"";
	switch(CboFilter->ItemIndex)
	{
		case -1:
		FilterName = String(L"SYNS_Filter") + FilterInvalidChars(CboLangName->Text);
		break;
		case 0:
		FilterName = L"SYNS_FilterPascal";
		break;
		case 1:
		FilterName = L"SYNS_FilterHP48";
		break;
		case 2:
		FilterName = L"SYNS_FilterCAClipper";
		break;
		case 3:
		FilterName = L"SYNS_FilterCPP";
		break;
		case 4:
		FilterName = L"SYNS_FilterJava";
		break;
		case 5:
		FilterName = L"SYNS_FilterPerl";
		break;
		case 6:
		FilterName = L"SYNS_FilterAWK";
		break;
		case 7:
		FilterName = L"SYNS_FilterHTML";
		break;
		case 8:
		FilterName = L"SYNS_FilterVBScript";
		break;
		case 9:
		FilterName = L"SYNS_FilterGalaxy";
		break;
		case 10:
		FilterName = L"SYNS_FilterPython";
		break;
		case 11:
		FilterName = L"SYNS_FilterSQL";
		break;
		case 12:
		FilterName = L"SYNS_FilterTclTk";
		break;
		case 13:
		FilterName = L"SYNS_FilterRTF";
		break;
		case 14:
		FilterName = L"SYNS_FilterBatch";
		break;
		case 15:
		FilterName = L"SYNS_FilterDFM";
		break;
		case 16:
		FilterName = L"SYNS_FilterX86Asm";
		break;
		case 17:
		FilterName = L"SYNS_FilterGembase";
		break;
		case 18:
		FilterName = L"SYNS_FilterINI";
		break;
		case 19:
		FilterName = L"SYNS_FilterML";
		break;
		case 20:
		FilterName = L"SYNS_FilterVisualBASIC";
		break;
		case 21:
		FilterName = L"SYNS_FilterADSP21xx";
		break;
		case 22:
		FilterName = L"SYNS_FilterPHP";
		break;
		case 23:
		FilterName = L"SYNS_FilterCache";
		break;
		case 24:
		FilterName = L"SYNS_FilterCSS";
		break;
		case 25:
		FilterName = L"SYNS_FilterJScript";
		break;
		case 26:
		FilterName = L"SYNS_FilterKIX";
		break;
		case 27:
		FilterName = L"SYNS_FilterBaan";
		break;
		case 28:
		FilterName = L"SYNS_FilterFoxpro";
		break;
		case 29:
		FilterName = L"SYNS_FilterFortran";
		break;
		case 30:
		FilterName = L"SYNS_FilterAsm68HC11";
		break;
		default:
		  ;
		break;
	}
	result = FilterName;
	return result;
}

String __fastcall TFrmMain::GetFriendlyLangName()
{
	String result;
	String LangName;
	switch(CboLangName->ItemIndex)
	{
		case -1:
		LangName = String(L"SYNS_FriendlyLang") + FilterInvalidChars(CboLangName->Text);
		break;
		case 0:
		LangName = L"SYNS_FriendlyLangHP48";
		break;
		case 1:
		LangName = L"SYNS_FriendlyLangCAClipper";
		break;
		case 2:
		LangName = L"SYNS_FriendlyLangCPP";
		break;
		case 3:
		LangName = L"SYNS_FriendlyLangJava";
		break;
		case 4:
		LangName = L"SYNS_FriendlyLangPerl";
		break;
		case 5:
		LangName = L"SYNS_FriendlyLangBatch";
		break;
		case 6:
		LangName = L"SYNS_FriendlyLangDfm";
		break;
		case 7:
		LangName = L"SYNS_FriendlyLangAWK";
		break;
		case 8:
		LangName = L"SYNS_FriendlyLangHTML";
		break;
		case 9:
		LangName = L"SYNS_FriendlyLangVBSScript";
		break;
		case 10:
		LangName = L"SYNS_FriendlyLangGalaxy";
		break;
		case 11:
		LangName = L"SYNS_FriendlyLangGeneral";
		break;
		case 12:
		LangName = L"SYNS_FriendlyLangPascal";
		break;
		case 13:
		LangName = L"SYNS_FriendlyLangX86Asm";
		break;
		case 14:
		LangName = L"SYNS_FriendlyLangPython";
		break;
		case 15:
		LangName = L"SYNS_FriendlyLangTclTk";
		break;
		case 16:
		LangName = L"SYNS_FriendlyLangSQL";
		break;
		case 17:
		LangName = L"SYNS_FriendlyLangGembase";
		break;
		case 18:
		LangName = L"SYNS_FriendlyLangINI";
		break;
		case 19:
		LangName = L"SYNS_FriendlyLangML";
		break;
		case 20:
		LangName = L"SYNS_FriendlyLangVisualBASIC";
		break;
		case 21:
		LangName = L"SYNS_FriendlyLangADSP21xx";
		break;
		case 22:
		LangName = L"SYNS_FriendlyLangPHP";
		break;
		case 23:
		LangName = L"SYNS_FriendlyLangSybaseSQL";
		break;
		case 24:
		LangName = L"SYNS_FriendlyLangGeneralMulti";
		break;
		case 25:
		LangName = L"SYNS_FriendlyLangCache";
		break;
		case 26:
		LangName = L"SYNS_FriendlyLangCSS";
		break;
		case 27:
		LangName = L"SYNS_FriendlyLangJScript";
		break;
		case 28:
		LangName = L"SYNS_FriendlyLangKIX";
		break;
		case 29:
		LangName = L"SYNS_FriendlyLangBaan";
		break;
		case 30:
		LangName = L"SYNS_FriendlyLangFoxpro";
		break;
		case 31:
		LangName = L"SYNS_FriendlyLangFortran";
		break;
		case 32:
		LangName = L"SYNS_FriendlyLang68HC11";
		break;
		default:
		  ;
		break;
	}
	result = LangName;
	return result;
}

String __fastcall TFrmMain::GetLangName()
{
	String result;
	String LangName;
	switch(CboLangName->ItemIndex)
	{
		case -1:
		LangName = String(L"SYNS_Lang") + FilterInvalidChars(CboLangName->Text);
		break;
		case 0:
		LangName = L"SYNS_LangHP48";
		break;
		case 1:
		LangName = L"SYNS_LangCAClipper";
		break;
		case 2:
		LangName = L"SYNS_LangCPP";
		break;
		case 3:
		LangName = L"SYNS_LangJava";
		break;
		case 4:
		LangName = L"SYNS_LangPerl";
		break;
		case 5:
		LangName = L"SYNS_LangBatch";
		break;
		case 6:
		LangName = L"SYNS_LangDfm";
		break;
		case 7:
		LangName = L"SYNS_LangAWK";
		break;
		case 8:
		LangName = L"SYNS_LangHTML";
		break;
		case 9:
		LangName = L"SYNS_LangVBSScript";
		break;
		case 10:
		LangName = L"SYNS_LangGalaxy";
		break;
		case 11:
		LangName = L"SYNS_LangGeneral";
		break;
		case 12:
		LangName = L"SYNS_LangPascal";
		break;
		case 13:
		LangName = L"SYNS_LangX86Asm";
		break;
		case 14:
		LangName = L"SYNS_LangPython";
		break;
		case 15:
		LangName = L"SYNS_LangTclTk";
		break;
		case 16:
		LangName = L"SYNS_LangSQL";
		break;
		case 17:
		LangName = L"SYNS_LangGembase";
		break;
		case 18:
		LangName = L"SYNS_LangINI";
		break;
		case 19:
		LangName = L"SYNS_LangML";
		break;
		case 20:
		LangName = L"SYNS_LangVisualBASIC";
		break;
		case 21:
		LangName = L"SYNS_LangADSP21xx";
		break;
		case 22:
		LangName = L"SYNS_LangPHP";
		break;
		case 23:
		LangName = L"SYNS_LangSybaseSQL";
		break;
		case 24:
		LangName = L"SYNS_LangGeneralMulti";
		break;
		case 25:
		LangName = L"SYNS_LangCache";
		break;
		case 26:
		LangName = L"SYNS_LangCSS";
		break;
		case 27:
		LangName = L"SYNS_LangJScript";
		break;
		case 28:
		LangName = L"SYNS_LangKIX";
		break;
		case 29:
		LangName = L"SYNS_LangBaan";
		break;
		case 30:
		LangName = L"SYNS_LangFoxpro";
		break;
		case 31:
		LangName = L"SYNS_LangFortran";
		break;
		case 32:
		LangName = L"SYNS_Lang68HC11";
		break;
		default:
		  ;
		break;
	}
	result = LangName;
	return result;
}

void __fastcall TFrmMain::WriteRest()
{
	int i = 0;
	int j = 0;
	int LineLength = 0;
	String KeyString;
	String AttrName;
	String FriendlyAttrName;
	String AttrTemp;
	TStringList* TempStringList = nullptr;
	String sPrefix;
	TLexDefaultAttri* DefAttri = nullptr;
	int stop = 0;
	IdentList->Sort();
	SetList->Sort(CompareSets);
	i = 0;
	while(i < IdentList->Count - 1)
	{
		WriteLn(OutFile, String(L"    ") + IdentList->Strings[i] + L",");
		++i;
	}
	WriteLn(OutFile, String(L"    ") + IdentList->Strings[i] + L");");
	WriteLn(OutFile);
	Write(OutFile, L"  TRangeState = (rsUnKnown");
	for(stop = (EnclosedList->Count - 1), i = 0; i <= stop; i++)
	{
		Write(OutFile, String(L", rs") + ((TLexEnclosedBy*) EnclosedList->Items[i])->ProcName);
	}
	WriteLn(OutFile, L");");
	WriteLn(OutFile);
	WriteLn(OutFile, L"  TProcTableProc = procedure of object;");
	WriteLn(OutFile);
	WriteLn(OutFile, L"  PIdentFuncTableFunc = ^TIdentFuncTableFunc;");
	WriteLn(OutFile, String(L"  TIdentFuncTableFunc = function (Index: Integer): T") + IdentPre
	           + L"TokenKind of object;");
	WriteLn(OutFile);
	WriteLn(OutFile, L"type");
	WriteLn(OutFile, String(L"  ") + LexName + L" = class(TSynCustomHighlighter)");
	WriteLn(OutFile, L"  private");
	WriteLn(OutFile, L"    fRange: TRangeState;");
	if(ListBoxFields->Items->Count > 0)
	{
		int stop = 0;
		for(stop = ListBoxFields->Items->Count - 1, i = 0; i <= stop; i++)
		{
			WriteLn(OutFile, String(L"    ") + ListBoxFields->Items->Strings[i] + L";");
		}
	}
	WriteLn(OutFile, L"    fTokenID: TtkTokenKind;");
	WriteLn(OutFile, String(L"    fIdentFuncTable: array[0..") + IntToStr(FrmHashTableGen->KeyIndicesCount() - 1)
	           + L"]"
	           + L" of TIdentFuncTableFunc;");
	i = 0;
	while(i < IdentList->Count)
	{
		if((IdentList->Strings[i] != String(IdentPre) + L"Null") && (IdentList->Strings[i] != String(IdentPre) + L"Unknown"))
			WriteLn(OutFile, String(L"    f") + IdentList->Strings[i].SubString(IdentPre.Length() + 1, IdentList->Strings[i].Length())
			           + L"Attri: TSynHighlighterAttributes;");
		++i;
	}
	WriteLn(OutFile, L"    function HashKey(Str: PWideChar): Cardinal;");
	i = 0;
	while(i < KeyList->Count)
	{
		WriteLn(OutFile, AnsiString(String(L"    function Func") + ToAlphaNum(FirstLetterCap(((TLexKeys*) KeyList->Items[i])->KeyName))
	           + L"(Index: Integer): T"
	           + IdentPre
	           + L"TokenKind;"));
		++i;
	}
	i = 0;
	while(i < SetList->Count)
	{
		WriteLn(OutFile, String(L"    procedure ") + ((TLexCharsets*) SetList->Items[i])->SetName
		           + L"Proc;");
		++i;
	}
	WriteLn(OutFile, L"    procedure UnknownProc;");
	WriteLn(OutFile, String(L"    function AltFunc(Index: Integer): T") + IdentPre
	           + L"TokenKind;");
	WriteLn(OutFile, L"    procedure InitIdent;");
	WriteLn(OutFile, String(L"    function IdentKind(MayBe: PWideChar): T") + IdentPre
	           + L"TokenKind;");
	WriteLn(OutFile, L"    procedure NullProc;");
	if(IdentList->IndexOf(IdentPre + L"Space") >= 0)
		WriteLn(OutFile, L"    procedure SpaceProc;");
	WriteLn(OutFile, L"    procedure CRProc;");
	WriteLn(OutFile, L"    procedure LFProc;");
	for(stop = (EnclosedList->Count - 1), i = 0; i <= stop; i++)
	{
		WriteLn(OutFile, String(L"    procedure ") + ((TLexEnclosedBy*) EnclosedList->Items[i])->ProcName
		           + L"OpenProc;");
		WriteLn(OutFile, String(L"    procedure ") + ((TLexEnclosedBy*) EnclosedList->Items[i])->ProcName
		           + L"Proc;");
	}
	WriteLn(OutFile, L"  protected");
	WriteLn(OutFile, L"    function GetSampleSource: string; override;");
	WriteLn(OutFile, L"    function IsFilterStored: Boolean; override;");
	WriteLn(OutFile, L"  public");
	WriteLn(OutFile, L"    constructor Create(AOwner: TComponent); override;");
	WriteLn(OutFile, L"    class function GetFriendlyLanguageName: string; override;");
	WriteLn(OutFile, L"    class function GetLanguageName: string; override;");
	WriteLn(OutFile, L"    function GetRange: Pointer; override;");
	WriteLn(OutFile, L"    procedure ResetRange; override;");
	WriteLn(OutFile, L"    procedure SetRange(Value: Pointer); override;");
	WriteLn(OutFile, L"    function GetDefaultAttribute(Index: Integer): TSynHighlighterAttributes; override;");
	WriteLn(OutFile, L"    function GetEol: Boolean; override;");
	if(ChkGetKeyWords->Checked)
		WriteLn(OutFile, L"    function GetKeyWords(TokenKind: Integer): string; override;");
	WriteLn(OutFile, L"    function GetTokenID: TtkTokenKind;");
	WriteLn(OutFile, L"    function GetTokenAttribute: TSynHighlighterAttributes; override;");
	WriteLn(OutFile, L"    function GetTokenKind: Integer; override;");
	WriteLn(OutFile, L"    function IsIdentChar(AChar: WideChar): Boolean; override;");
	WriteLn(OutFile, L"    procedure Next; override;");
	WriteLn(OutFile, L"  published");
	i = 0;
	while(i < IdentList->Count)
	{
		if((IdentList->Strings[i] != String(IdentPre) + L"Null") && (IdentList->Strings[i] != String(IdentPre) + L"Unknown"))
			WriteLn(OutFile, String(L"    property ") + IdentList->Strings[i].SubString(IdentPre.Length() + 1, IdentList->Strings[i].Length())
			           + L"Attri: TSynHighlighterAttributes read f"
			           + IdentList->Strings[i].SubString(IdentPre.Length() + 1, IdentList->Strings[i].Length())
			           + L"Attri write f"
			           + IdentList->Strings[i].SubString(IdentPre.Length() + 1, IdentList->Strings[i].Length())
			           + L"Attri;");
		++i;
	}
	WriteLn(OutFile, L"  end;");
	WriteLn(OutFile);
	WriteLn(OutFile, L"implementation");
	WriteLn(OutFile);
	WriteLn(OutFile, L"uses");
	WriteLn(OutFile, L"  SynEditStrConst;");
	WriteLn(OutFile);
	if((CboFilter->ItemIndex ==  - 1) || (CboLangName->ItemIndex ==  - 1))
	{
		WriteLn(OutFile, L"resourcestring");
		if(CboFilter->ItemIndex ==  - 1)
			WriteLn(OutFile, String(L"  SYNS_Filter") + FilterInvalidChars(CboLangName->Text)
	           + L" = '"
	           + CboFilter->Text
	           + L"';");
		if(CboLangName->ItemIndex ==  - 1)
		{
			WriteLn(OutFile, String(L"  SYNS_Lang") + FilterInvalidChars(CboLangName->Text)
	           + L" = '"
	           + CboLangName->Text
	           + L"';");
			WriteLn(OutFile, String(L"  SYNS_FriendlyLang") + FilterInvalidChars(CboLangName->Text)
	           + L" = '"
	           + CboLangName->Text
	           + L"';");
		}
		i = 0;
		while(i < IdentList->Count)
		{
			AttrTemp = IdentList->Strings[i].SubString(IdentPre.Length() + 1, IdentList->Strings[i].Length());
			if((CboAttrIdentifier->Items->IndexOf(String(L"SYNS_Attr") + AttrTemp) < 0) && (AttrTemp != L"Unknown"))
			{
				WriteLn(OutFile, String(L"  SYNS_Attr") + FilterInvalidChars(AttrTemp) + L" = '" + AttrTemp + L"';");
				WriteLn(OutFile, String(L"  SYNS_FriendlyAttr") + FilterInvalidChars(AttrTemp)
	           + L" = '"
	           + AttrTemp
	           + L"';");
			}
			++i;
		}
		WriteLn(OutFile);
	}
	WriteLn(OutFile, L"const");
	Write(OutFile, FrmHashTableGen->GetKeyWordConstantsSource(Sensitivity));
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"procedure ") + LexName + L".InitIdent;");
	WriteLn(OutFile, L"var");
	WriteLn(OutFile, L"  i: Integer;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  for i := Low(fIdentFuncTable) to High(fIdentFuncTable) do");
	WriteLn(OutFile, L"    if KeyIndices[i] = -1 then");
	WriteLn(OutFile, L"      fIdentFuncTable[i] := AltFunc;");
	WriteLn(OutFile, L"");
	i = 0;
	while(i < KeyList->Count)
	{
		if(i < KeyList->Count - 1)
		{
			while(((TLexKeys*) KeyList->Items[i])->key == ((TLexKeys*) KeyList->Items[i + 1])->key)
			{
				++i;
				if(i >= KeyList->Count - 1)
					break;
			}
		}
		KeyString = IntToStr((__int64) ((TLexKeys*) KeyList->Items[i])->key);
		WriteLn(OutFile, String(L"  fIdentFuncTable[") + KeyString
	           + L"] := Func"
	           + ToAlphaNum(FirstLetterCap(((TLexKeys*) KeyList->Items[i])->KeyName))
	           + L";");
		++i;
	}
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	Write(OutFile, FrmHashTableGen->GetHashKeyFunctionSource(LexName));
	WriteLn(OutFile);
	i = 0;
	while(i < KeyList->Count)
	{
		KeyString = ToAlphaNum(FirstLetterCap(((TLexKeys*) KeyList->Items[i])->KeyName));
		WriteLn(OutFile, String(L"function ") + LexName
		           + L".Func"
		           + KeyString
		           + L"(Index: Integer): T"
		           + IdentPre
		           + L"TokenKind;");
		WriteLn(OutFile, L"begin");
		if(i < KeyList->Count - 1)
		{
			while(((TLexKeys*) KeyList->Items[i])->key == ((TLexKeys*) KeyList->Items[i + 1])->key)
			{
				WriteLn(OutFile, L"  if IsCurrentToken(KeyWords[Index]) then");
				WriteLn(OutFile, String(L"    Result := ") + IdentPre + ((TLexKeys*) KeyList->Items[i])->TokenType);
				WriteLn(OutFile, L"  else");
				++i;
				if(i >= KeyList->Count - 1)
					break;
			}
		}
		WriteLn(OutFile, L"  if IsCurrentToken(KeyWords[Index]) then");
		WriteLn(OutFile, String(L"    Result := ") + IdentPre + ((TLexKeys*) KeyList->Items[i])->TokenType);
		WriteLn(OutFile, L"  else");
		WriteLn(OutFile, String(L"    Result := ") + IdentPre + L"Identifier;");
		WriteLn(OutFile, L"end;");
		WriteLn(OutFile);
		++i;
	}
	WriteLn(OutFile, String(L"function ") + LexName
	           + L".AltFunc(Index: Integer): T"
	           + IdentPre
	           + L"TokenKind;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, String(L"  Result := ") + IdentPre + L"Identifier;");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"function ") + LexName
	           + L".IdentKind(MayBe: PWideChar): T"
	           + IdentPre
	           + L"TokenKind;");
	WriteLn(OutFile, L"var");
	WriteLn(OutFile, L"  Key: Cardinal;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  fToIdent := MayBe;");
	WriteLn(OutFile, L"  Key := HashKey(MayBe);");
	WriteLn(OutFile, L"  if Key <= High(fIdentFuncTable) then");
	WriteLn(OutFile, L"    Result := fIdentFuncTable[Key](KeyIndices[Key])");
	WriteLn(OutFile, L"  else");
	WriteLn(OutFile, String(L"    Result := ") + IdentPre + L"Identifier;");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	if(IdentList->IndexOf(IdentPre + L"Space") >= 0)
	{
		WriteLn(OutFile, String(L"procedure ") + LexName + L".SpaceProc;");
		WriteLn(OutFile, L"begin");
		WriteLn(OutFile, L"  inc(Run);");
		WriteLn(OutFile, String(L"  fTokenID := ") + IdentPre + L"Space;");
		WriteLn(OutFile, L"  while (FLine[Run] <= #32) and not IsLineEnd(Run) do inc(Run);");
		WriteLn(OutFile, L"end;");
		WriteLn(OutFile);
	}
	WriteLn(OutFile, String(L"procedure ") + LexName + L".NullProc;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, String(L"  fTokenID := ") + IdentPre + L"Null;");
	WriteLn(OutFile, L"  inc(Run);");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"procedure ") + LexName + L".CRProc;");
	WriteLn(OutFile, L"begin");
	if(IdentList->IndexOf(IdentPre + L"Space") >= 0)
		WriteLn(OutFile, String(L"  fTokenID := ") + IdentPre + L"Space;");
	else
		WriteLn(OutFile, String(L"  fTokenID := ") + IdentPre + L"Unknown;");
	WriteLn(OutFile, L"  inc(Run);");
	WriteLn(OutFile, L"  if fLine[Run] = #10 then");
	WriteLn(OutFile, L"    inc(Run);");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"procedure ") + LexName + L".LFProc;");
	WriteLn(OutFile, L"begin");
	if(IdentList->IndexOf(IdentPre + L"Space") >= 0)
		WriteLn(OutFile, String(L"  fTokenID := ") + IdentPre + L"Space;");
	else
		WriteLn(OutFile, String(L"  fTokenID := ") + IdentPre + L"Unknown;");
	WriteLn(OutFile, L"  inc(Run);");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	for(stop = (EnclosedList->Count - 1), i = 0; i <= stop; i++)
	{
		int stop1 = 0;
		WriteLn(OutFile, String(L"procedure ") + LexName
		           + L"."
		           + ((TLexEnclosedBy*) EnclosedList->Items[i])->ProcName
		           + L"OpenProc;");
		WriteLn(OutFile, L"begin");
		WriteLn(OutFile, L"  Inc(Run);");
		if(((TLexEnclosedBy*) EnclosedList->Items[i])->StartsWith.Length() > 1)
		{
			int stop1 = 0;
			Write(OutFile, L"  if ");
			for(stop1 = (int) ((TLexEnclosedBy*) EnclosedList->Items[i])->StartsWith.Length(), j = 2; j <= stop1; j++)
			{
				if(j > 2)
				{
					WriteLn(OutFile, L" and");
					Write(OutFile, L"     ");
				}
				Write(OutFile, String(L"(fLine[Run") + AddInt(j - 2)
	           + L"] = '"
	           + StuffString(String(((TLexEnclosedBy*) EnclosedList->Items[i])->StartsWith[j]))
	           + L"')");
			}
			WriteLn(OutFile, L" then");
			WriteLn(OutFile, L"  begin");
			WriteLn(OutFile, String(L"    Inc(Run, ") + IntToStr((int) (((TLexEnclosedBy*) EnclosedList->Items[i])->StartsWith.Length() - 1))
	           + L");");
			WriteLn(OutFile, String(L"    fRange := rs") + ((TLexEnclosedBy*) EnclosedList->Items[i])->ProcName
			           + L";");
			if(!((TLexEnclosedBy*) EnclosedList->Items[i])->MultiLine)
			{
				WriteLn(OutFile, String(L"    ") + ((TLexEnclosedBy*) EnclosedList->Items[i])->ProcName + L"Proc;");
			}
			WriteLn(OutFile, String(L"    fTokenID := ") + IdentPre
			           + ((TLexEnclosedBy*) EnclosedList->Items[i])->TokenName
			           + L";");
			WriteLn(OutFile, L"  end");
			WriteLn(OutFile, L"  else");
			if(IdentList->IndexOf(IdentPre + L"Symbol") >= 0)
				WriteLn(OutFile, String(L"    fTokenID := ") + IdentPre + L"Symbol;");
			else
				WriteLn(OutFile, String(L"    fTokenID := ") + IdentPre + L"Identifier;");
		}
		else
		{
			WriteLn(OutFile, String(L"  fRange := rs") + ((TLexEnclosedBy*) EnclosedList->Items[i])->ProcName
			           + L";");
			if(!((TLexEnclosedBy*) EnclosedList->Items[i])->MultiLine)
			{
				WriteLn(OutFile, String(L"  ") + ((TLexEnclosedBy*) EnclosedList->Items[i])->ProcName + L"Proc;");
			}
			WriteLn(OutFile, String(L"  fTokenID := ") + IdentPre
			           + ((TLexEnclosedBy*) EnclosedList->Items[i])->TokenName
			           + L";");
		}
		WriteLn(OutFile, L"end;");
		WriteLn(OutFile);
		WriteLn(OutFile, String(L"procedure ") + LexName
		           + L"."
		           + ((TLexEnclosedBy*) EnclosedList->Items[i])->ProcName
		           + L"Proc;");
		WriteLn(OutFile, L"begin");
		if(((TLexEnclosedBy*) EnclosedList->Items[i])->MultiLine)
		{
			WriteLn(OutFile, L"  case fLine[Run] of");
			WriteLn(OutFile, L"     #0: NullProc;");
			WriteLn(OutFile, L"    #10: LFProc;");
			WriteLn(OutFile, L"    #13: CRProc;");
			WriteLn(OutFile, L"  else");
			WriteLn(OutFile, L"    begin");
			sPrefix = L"    ";
		}
		else
		sPrefix = L"";
		{ Write(OutFile, sPrefix); WriteLn(OutFile, String(L"  fTokenID := ") + IdentPre
		           + ((TLexEnclosedBy*) EnclosedList->Items[i])->TokenName
		           + L";"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"  repeat"); }
		{ Write(OutFile, sPrefix); Write(OutFile, L"    if "); }
		for(stop1 = (int) ((TLexEnclosedBy*) EnclosedList->Items[i])->EndsWith.Length(), j = 1; j <= stop1; j++)
		{
			if(j > 1)
			{
				WriteLn(OutFile, L" and");
				{ Write(OutFile, sPrefix); Write(OutFile, L"       "); }
			}
			Write(OutFile, String(L"(fLine[Run") + AddInt(j - 1)
	           + L"] = '"
	           + StuffString(String(((TLexEnclosedBy*) EnclosedList->Items[i])->EndsWith[j]))
	           + L"')");
		}
		WriteLn(OutFile, L" then");
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"    begin"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, String(L"      Inc(Run, ") + IntToStr((int) ((TLexEnclosedBy*) EnclosedList->Items[i])->EndsWith.Length())
	           + L");"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"      fRange := rsUnKnown;"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"      Break;"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"    end;"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"    if not IsLineEnd(Run) then"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"      Inc(Run);"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"  until IsLineEnd(Run);"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"end;"); }
		if(((TLexEnclosedBy*) EnclosedList->Items[i])->MultiLine)
		{
			WriteLn(OutFile, L"  end;");
			WriteLn(OutFile, L"end;");
		}
		WriteLn(OutFile);
	}
	WriteLn(OutFile, String(L"constructor ") + LexName + L".Create(AOwner: TComponent);");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  inherited Create(AOwner);");
	WriteLn(OutFile, String(L"  fCaseSensitive := ") + BoolStrs[Sensitivity] + L";");
	WriteLn(OutFile);
	i = 0;
	while(i < IdentList->Count)
	{
		AttrTemp = IdentList->Strings[i].SubString(IdentPre.Length() + 1, IdentList->Strings[i].Length());
		if(AttrTemp == L"Key")
			AttrName = CboAttrReservedWord->Text;
		else
		{
			if(AttrTemp == L"Identifier")
				AttrName = CboAttrIdentifier->Text;
			else
				AttrName = String(L"SYNS_Attr") + FilterInvalidChars(AttrTemp);
		}
		if(Pos(L"SYNS_", AttrName) == 1)
		{
			FriendlyAttrName = AttrName;
			FriendlyAttrName.Insert(L"Friendly",wcslen(L"SYNS_") + 1);
		}
		else
		FriendlyAttrName = String(L"Friendly") + AttrName;
		if((IdentList->Strings[i] != String(IdentPre) + L"Null") && (IdentList->Strings[i] != String(IdentPre) + L"Unknown"))
		{
			AttrTemp = String(L"f") + AttrTemp + L"Attri";
			WriteLn(OutFile, String(L"  ") + AttrTemp
			           + L" := TSynHighLighterAttributes.Create("
			           + AttrName
			           + L", "
			           + FriendlyAttrName
			           + L");");
			if(ASSIGNED(IdentList->Objects[i]))
			{
				DefAttri = ((TLexDefaultAttri*) IdentList->Objects[i]);
				if(DefAttri->Style != L"")
					WriteLn(OutFile, String(L"  ") + AttrTemp + L".Style := " + DefAttri->Style + L";");
				if(DefAttri->Foreground != L"")
					WriteLn(OutFile, String(L"  ") + AttrTemp + L".Foreground := " + DefAttri->Foreground + L";");
				if(DefAttri->Background != L"")
					WriteLn(OutFile, String(L"  ") + AttrTemp + L".Background := " + DefAttri->Background + L";");
			}
			else
			{
				if(IdentList->Strings[i] == String(IdentPre) + L"Key")
					WriteLn(OutFile, String(L"  ") + AttrTemp + L".Style := [fsBold];");
				else
				{
					if(IdentList->Strings[i] == String(IdentPre) + L"Comment")
					{
						WriteLn(OutFile, String(L"  ") + AttrTemp + L".Style := [fsItalic];");
						WriteLn(OutFile, String(L"  ") + AttrTemp + L".Foreground := clNavy;");
					}
				}
			}
			WriteLn(OutFile, String(L"  AddAttribute(") + AttrTemp + L");");
			WriteLn(OutFile);
		}
		++i;
	}
	WriteLn(OutFile, L"  SetAttributesOnChange(DefHighlightChange);");
	WriteLn(OutFile, L"  InitIdent;");
	WriteLn(OutFile, String(L"  fDefaultFilter := ") + GetFilterName() + L";");
	WriteLn(OutFile, L"  fRange := rsUnknown;");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	i = 0;
	while(i < SetList->Count)
	{
		WriteLn(OutFile, String(L"procedure ") + LexName
		           + L"."
		           + ((TLexCharsets*) SetList->Items[i])->SetName
		           + L"Proc;");
		WriteLn(OutFile, L"begin");
		Write(OutFile, String(L"  ") + ((TLexCharsets*) SetList->Items[i])->ProcData);
		WriteLn(OutFile, L"end;");
		WriteLn(OutFile);
		++i;
	}
	WriteLn(OutFile, String(L"procedure ") + LexName + L".UnknownProc;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  inc(Run);");
	WriteLn(OutFile, String(L"  fTokenID := ") + IdentPre + L"Unknown;");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"procedure ") + LexName + L".Next;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  fTokenPos := Run;");
	if(EnclosedList->Count > 0)
	{
		int stop = 0;
		WriteLn(OutFile, L"  case fRange of");
		for(stop = (EnclosedList->Count - 1), i = 0; i <= stop; i++)
		{
			if(((TLexEnclosedBy*) EnclosedList->Items[i])->MultiLine)
			{
				WriteLn(OutFile, String(L"    rs") + ((TLexEnclosedBy*) EnclosedList->Items[i])->ProcName
				           + L": "
				           + ((TLexEnclosedBy*) EnclosedList->Items[i])->ProcName
				           + L"Proc;");
			}
		}
		WriteLn(OutFile, L"  else");
		WriteLn(OutFile, L"    case fLine[Run] of");
		WriteLn(OutFile, L"      #0: NullProc;");
		WriteLn(OutFile, L"      #10: LFProc;");
		WriteLn(OutFile, L"      #13: CRProc;");
		for(stop = (EnclosedList->Count - 1), i = 0; i <= stop; i++)
		{
			if(((TLexEnclosedBy*) EnclosedList->Items[i])->StartsWith != L"")
			{
				WriteLn(OutFile, String(L"      '") + StuffString(String(((TLexEnclosedBy*) EnclosedList->Items[i])->StartsWith[1]))
	           + L"': "
	           + ((TLexEnclosedBy*) EnclosedList->Items[i])->ProcName
	           + L"OpenProc;");
			}
		}
		if(IdentList->IndexOf(IdentPre + L"Space") >= 0)
			WriteLn(OutFile, L"      #1..#9, #11, #12, #14..#32: SpaceProc;");
		i = 0;
		while(i < SetList->Count)
		{
			WriteLn(OutFile, String(L"      ") + ((TLexCharsets*) SetList->Items[i])->Charset
			           + L": "
			           + ((TLexCharsets*) SetList->Items[i])->SetName
			           + L"Proc;");
			++i;
		}
		WriteLn(OutFile, L"    else");
		WriteLn(OutFile, L"      UnknownProc;");
		WriteLn(OutFile, L"    end;");
		WriteLn(OutFile, L"  end;");
	}
	else
	{
		WriteLn(OutFile, L"  case fLine[Run] of");
		WriteLn(OutFile, L"    #0: NullProc;");
		WriteLn(OutFile, L"    #10: LFProc;");
		WriteLn(OutFile, L"    #13: CRProc;");
		if(IdentList->IndexOf(IdentPre + L"Space") >= 0)
			WriteLn(OutFile, L"    #1..#9, #11, #12, #14..#32: SpaceProc;");
		i = 0;
		while(i < SetList->Count)
		{
			WriteLn(OutFile, String(L"    ") + ((TLexCharsets*) SetList->Items[i])->Charset
			           + L": "
			           + ((TLexCharsets*) SetList->Items[i])->SetName
			           + L"Proc;");
			++i;
		}
		WriteLn(OutFile, L"  else");
		WriteLn(OutFile, L"    UnknownProc;");
		WriteLn(OutFile, L"  end;");
	}
	WriteLn(OutFile, L"  inherited;");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"function ") + LexName
	           + L".GetDefaultAttribute(Index: Integer): TSynHighLighterAttributes;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  case Index of");
	if(IdentList->IndexOf(IdentPre + L"Comment") >= 0)
		WriteLn(OutFile, L"    SYN_ATTR_COMMENT: Result := fCommentAttri;");
	if(IdentList->IndexOf(IdentPre + L"Identifier") >= 0)
		WriteLn(OutFile, L"    SYN_ATTR_IDENTIFIER: Result := fIdentifierAttri;");
	if(IdentList->IndexOf(IdentPre + L"Key") >= 0)
		WriteLn(OutFile, L"    SYN_ATTR_KEYWORD: Result := fKeyAttri;");
	if(IdentList->IndexOf(IdentPre + L"String") >= 0)
		WriteLn(OutFile, L"    SYN_ATTR_STRING: Result := fStringAttri;");
	if(IdentList->IndexOf(IdentPre + L"Space") >= 0)
		WriteLn(OutFile, L"    SYN_ATTR_WHITESPACE: Result := fSpaceAttri;");
	if(IdentList->IndexOf(IdentPre + L"Symbol") >= 0)
		WriteLn(OutFile, L"    SYN_ATTR_SYMBOL: Result := fSymbolAttri;");
	WriteLn(OutFile, L"  else");
	WriteLn(OutFile, L"    Result := nil;");
	WriteLn(OutFile, L"  end;");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"function ") + LexName + L".GetEol: Boolean;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  Result := Run = fLineLen + 1;");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	if(ChkGetKeyWords->Checked)
	{
		WriteLn(OutFile, String(L"function ") + LexName + L".GetKeyWords(TokenKind: Integer): string;");
		WriteLn(OutFile, L"begin");
		TempStringList = new TStringList();
		try
		{
			int stop = 0;
			TempStringList->Sorted = true;
			for(stop = KeyList->Count - 1, i = 0; i <= stop; i++)
			{
				TempStringList->Add(((TLexKeys*) KeyList->Items[i])->KeyName);
			}
			if(TempStringList->Count > 0)
			{
				int stop = 0;
				WriteLn(OutFile, L"  Result := ");
				for(stop = Trunc(Int((long double) ((size_t)(TempStringList->CommaText.Length() / 70)))) - 1, i = 0; i <= stop; i++)
				{
					if(i == 0)
						LineLength = 69;
					else
						LineLength = 70;
					WriteLn(OutFile, String(L"    " L"\x27") + TempStringList->CommaText.SubString(i * 70, LineLength)
					           + L"\x27"
					           + L"\x20"
					           + L"\x2b");
				}
				i = Trunc(Int((long double) ((size_t)(TempStringList->CommaText.Length() / 70))));
				WriteLn(OutFile, String(L"    " L"\x27") + TempStringList->CommaText.SubString(i * 70, TempStringList->CommaText.Length())
				           + L"\x27"
				           + L";");
			}
			else
			WriteLn(OutFile, L"  Result := " L"\x27" L"\x27" L";");
		}
		__finally
		{
			delete TempStringList;
		}
		WriteLn(OutFile, L"end;");
		WriteLn(OutFile);
	}
	WriteLn(OutFile, String(L"function ") + LexName + L".GetTokenID: TtkTokenKind;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  Result := fTokenId;");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"function ") + LexName + L".GetTokenAttribute: TSynHighLighterAttributes;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  case GetTokenID of");
	i = 0;
	while(i < IdentList->Count)
	{
		if((IdentList->Strings[i] != String(IdentPre) + L"Null") && (IdentList->Strings[i] != String(IdentPre) + L"Unknown"))
			WriteLn(OutFile, String(L"    ") + IdentList->Strings[i]
			           + L": Result := f"
			           + IdentList->Strings[i].SubString(IdentPre.Length() + 1, IdentList->Strings[i].Length())
			           + L"Attri;");
		++i;
	}
	WriteLn(OutFile, String(L"    ") + IdentPre + L"Unknown: Result := f" + CboUnknownTokenAttr->Text + L"Attri;");
	WriteLn(OutFile, L"  else");
	WriteLn(OutFile, L"    Result := nil;");
	WriteLn(OutFile, L"  end;");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"function ") + LexName + L".GetTokenKind: Integer;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  Result := Ord(fTokenId);");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"function ") + LexName + L".IsIdentChar(AChar: WideChar): Boolean;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  case AChar of");
	WriteLn(OutFile, String(L"    ") + IdentContent + L":");
	WriteLn(OutFile, L"      Result := True;");
	WriteLn(OutFile, L"    else");
	WriteLn(OutFile, L"      Result := False;");
	WriteLn(OutFile, L"  end;");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"function ") + LexName + L".GetSampleSource: string;");
	WriteLn(OutFile, L"begin");
	if(SampleSourceList->Count == 0)
	{
		WriteLn(OutFile, L"  Result := ");
		WriteLn(OutFile, L"    'Sample source for: '#13#10 +");
		WriteLn(OutFile, String(L"    '") + EditDescription->Text + L"';");
	}
	else
	{
		int stop = 0;
		WriteLn(OutFile, L"  Result := ");
		for(stop = SampleSourceList->Count - 1, i = 0; i <= stop; i++)
		{
			if((i > 0) && (i < SampleSourceList->Count - 1))
				WriteLn(OutFile, L"#13#10 +");
			if(i < SampleSourceList->Count - 1)
				Write(OutFile, L"    ");
			if(SampleSourceList->Strings[i] != L"")
				{ Write(OutFile, L'\''); Write(OutFile, StuffString(SampleSourceList->Strings[i])); Write(OutFile, L'\''); }
		}
		WriteLn(OutFile, L';');
	}
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"function ") + LexName + L".IsFilterStored: Boolean;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, String(L"  Result := fDefaultFilter <> ") + GetFilterName() + L";");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"class function ") + LexName + L".GetFriendlyLanguageName: string;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, String(L"  Result := ") + GetFriendlyLangName() + L";");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"class function ") + LexName + L".GetLanguageName: string;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, String(L"  Result := ") + GetLangName() + L";");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"procedure ") + LexName + L".ResetRange;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  fRange := rsUnknown;");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"procedure ") + LexName + L".SetRange(Value: Pointer);");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  fRange := TRangeState(Value);");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, String(L"function ") + LexName + L".GetRange: Pointer;");
	WriteLn(OutFile, L"begin");
	WriteLn(OutFile, L"  Result := Pointer(fRange);");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	WriteLn(OutFile, L"initialization");
	WriteLn(OutFile, L"{$IFNDEF SYN_CPPB_1}");
	WriteLn(OutFile, String(L"  RegisterPlaceableHighlighter(") + LexName + L");");
	WriteLn(OutFile, L"{$ENDIF}");
	WriteLn(OutFile, L"end.");
}

void __fastcall TFrmMain::CboLangNameChange(TObject* Sender)
{
	if((CboLangName->Text != L"") && (CboFilter->Text != L""))
		BtnStart->Enabled = true;
	else
		BtnStart->Enabled = false;
}

void __fastcall TFrmMain::ListBoxFieldsClick(TObject* Sender)
{
	btnDelete->Enabled = true;
}

void __fastcall TFrmMain::btnAddClick(TObject* Sender)
{
	ListBoxFields->Items->Add(EditAddField->Text);
	EditAddField->Clear();
}

void __fastcall TFrmMain::btnDeleteClick(TObject* Sender)
{
	btnDelete->Enabled = false;
	ListBoxFields->Items->Delete(ListBoxFields->ItemIndex);
}

void __fastcall TFrmMain::EditAddFieldChange(TObject* Sender)
{
	btnAdd->Enabled = EditAddField->Text != L"";
}

void __fastcall TFrmMain::EditAddFieldKeyPress(TObject* Sender, Char& key)
{
	if((key == L';') || (key == L'\x20'))
		key = L'\x00';
}

void __fastcall TFrmMain::MnuExitClick(TObject* Sender)
{
	Close();
}

void __fastcall TFrmMain::MnuOpenClick(TObject* Sender)
{
	WriteSettings();
	PerformFileOpen();
}

void __fastcall TFrmMain::FormClose(TObject* Sender, TCloseAction& Action)
{
	WriteSettings();
}

bool __fastcall TFrmMain::KeywordsAreAllAlphaNumAndDifferent()
{
	bool result = false;
	int i = 0;
	TStringList* KeywordList = nullptr;
	int stop = 0;
	result = true;
	KeywordList = new TStringList();
	try
	{
		KeywordList->Sorted = true;
		KeywordList->Duplicates = System::Classes::dupError;
		try
		{
			int stop = 0;
			for(stop = KeyList->Count - 1, i = 0; i <= stop; i++)
			{
				KeywordList->Add(((TLexKeys*) KeyList->Items[i])->KeyName);
			}
		}
		catch(...)
		{
			result = false;
			return result;
		}
	}
	__finally
	{
		delete KeywordList;
	}
	for(stop = KeyList->Count - 1, i = 0; i <= stop; i++)
	{
		if(!IsASCIIAlphaNum(((TLexKeys*) KeyList->Items[i])->KeyName))
		{
			result = false;
			return result;
		}
	}
	return result;
}
