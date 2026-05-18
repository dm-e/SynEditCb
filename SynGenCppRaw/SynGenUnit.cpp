#include <vcl.h>
#pragma hdrstop

#include "SynGenUnit.h"
#include <System.UITypes.hpp>
#include <System.StrUtils.hpp>
#include <System.Win.Registry.hpp>
#include "HashTableGen.h"
#include "d2c_sysinterface.h"
#include "d2c_convert.h"
#include "OnLeavingScope.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;
using namespace Genlex;
using namespace System;
using namespace System::Strutils;
using namespace System::Sysutils;
using namespace System::Uitypes;
using namespace System::Win::Registry;
using namespace Vcl::Graphics;

#define Syngenunit__0 (TReplaceFlags() << rfReplaceAll)
#define Syngenunit__1 (TSysCharSet() << '_' <<  \
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
#define Syngenunit__2 (TSysCharSet() << '_' <<  \
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
#define Syngenunit__3 (System::Set<TIdTokenKind, TIdTokenKind::IdBeginFunc, TIdTokenKind::IdUnknown>() << IdSensitive << IdIdentStart)
#define Syngenunit__4 (TMsgDlgButtons() << TMsgDlgBtn::mbOK)
#define Syngenunit__5 (System::Set<TIdTokenKind, TIdTokenKind::IdBeginFunc, TIdTokenKind::IdUnknown>() << IdSpace << IdBraceOpen)
#define Syngenunit__6 (System::Set<TIdTokenKind, TIdTokenKind::IdBeginFunc, TIdTokenKind::IdUnknown>() << IdSpace << IdBraceOpen << IdCRLF)
#define Syngenunit__7 (System::Set<TIdTokenKind, TIdTokenKind::IdBeginFunc, TIdTokenKind::IdUnknown>() << IdSpace << IdBraceOpen << IdCRLF)
#define Syngenunit__8 (System::Set<TIdTokenKind, TIdTokenKind::IdBeginFunc, TIdTokenKind::IdUnknown>() << IdSpace << IdBraceOpen << IdCRLF << IdUnknown)
#define Syngenunit__9 (System::Set<TIdTokenKind, TIdTokenKind::IdBeginFunc, TIdTokenKind::IdUnknown>() << IdStop << IdCRLF)
#define Syngenunit__10 (System::Set<TIdTokenKind, TIdTokenKind::IdBeginFunc, TIdTokenKind::IdUnknown>() << IdStop << IdNull)
#define Syngenunit__11 (System::Set<TIdTokenKind, TIdTokenKind::IdBeginFunc, TIdTokenKind::IdUnknown>() << IdStop << IdNull)
#define Syngenunit__12 (System::Set<TIdTokenKind, TIdTokenKind::IdBeginFunc, TIdTokenKind::IdUnknown>() << IdCRLF << IdSpace)
#define Syngenunit__13 (System::Set<TIdTokenKind, TIdTokenKind::IdBeginFunc, TIdTokenKind::IdUnknown>() << IdCRLF << IdNull << IdStop)
#define Syngenunit__14 (System::Set<TIdTokenKind, TIdTokenKind::IdBeginFunc, TIdTokenKind::IdUnknown>() << IdCRLF << IdSpace)
#define Syngenunit__15 (System::Set<TIdTokenKind, TIdTokenKind::IdBeginFunc, TIdTokenKind::IdUnknown>() << IdCRLF << IdNull << IdStop)

__fastcall TLexKeys::TLexKeys() {}
__fastcall TLexCharsets::TLexCharsets() {}


int mKeyHashTable[256/*# range #0..#255*/];
int mSKeyHashTable[256/*# range #0..#255*/];
TFrmMain* FrmMain = nullptr;
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

String __fastcall AddInt(int aValue)
{
	String result;
	if(aValue < 0)
		result = String(L" - ") + IntToStr(Abs(aValue));
	else
	{
		if(aValue > 0)
			result = String(L" + ") + IntToStr(aValue);
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
	for(stop = Value.Length(), i = 1; i <= stop; i++)
	{
		if(Value[i] == L'\'')
			result = result + L"'";
		else
			result = result + String(Value[i]);
	}
	return result;
}

String __fastcall FirstLetterCap(String S)
{
	String result;
	result = Sysutils::AnsiLowerCase(S);
	if(result.Length() > 0)
		result[1] = Sysutils::AnsiUpperCase(String(S[1]))[1];
	return result;
}

String __fastcall AnsiReplaceStr(const String AText, const String AFromText, const String AToText)
{
	String result;
	result = StringReplace(AText, AFromText, AToText, Syngenunit__0);
	return result;
}

String __fastcall ToAlphaNum(String S)
{
	String result;
	Char c = L'\0';
	WideChar stop = 0;
	for(stop = L'\x2f', c = L'\x21'; c <= stop; c++)
	{
		S = AnsiReplaceStr(S, String(c), IntToStr(int(c)));
	}
	for(stop = L'\x40', c = L'\x3a'; c <= stop; c++)
	{
		S = AnsiReplaceStr(S, String(c), IntToStr(int(c)));
	}
	for(stop = L'\x60', c = L'\x5b'; c <= stop; c++)
	{
		S = AnsiReplaceStr(S, String(c), IntToStr(int(c)));
	}
	for(stop = L'\xbf', c = L'\x7b'; c <= stop; c++)
	{
		S = AnsiReplaceStr(S, String(c), IntToStr(int(c)));
	}
	result = S;
	return result;
}

bool __fastcall IsASCIIAlphaNum(String S)
{
	bool result = false;
	int i = 0;
	int stop = 0;
	result = true;
	S = ToAlphaNum(S);
	for(stop = S.Length(), i = 1; i <= stop; i++)
	{
		switch(S[i])
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
			{
				result = false;
				return result;
			}
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
	Char I = L'\0';
	WideChar stop = 0;
	for(stop = L'\xff', I = L'\x00'; I <= stop; I++)
	{
		switch(CharInSet(I, Syngenunit__1))
		{
			case true:
			{
				if((I > L'\x40') && (I < L'\x5b'))
					mSKeyHashTable[I] = int(I) - 64;
				else
				{
					if(I > L'\x60')
						mSKeyHashTable[I] = int(I) - 95;
				}
			}
			break;
			default:
			mSKeyHashTable[I] = 0;
			break;
		}
	}
}

void __fastcall TFrmMain::MakeHashTable()
{
	Char I = L'\0';
	Char J = L'\0';
	WideChar stop = 0;
	for(stop = L'\xff', I = L'\x00'; I <= stop; I++)
	{
		J = UpperCase(String(I))[1];
		switch(CharInSet(I, Syngenunit__2))
		{
			case true:
			mKeyHashTable[I] = int(J) - 64;
			break;
			default:
			mKeyHashTable[I] = 0;
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
	PChar UserName = nullptr;
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
		UserName = StrAlloc(Count); // allocate memory for the user name
		GetUserName(UserName, &Count); // retrieve the user name
		/*# with TRegIniFile.Create(IniFile) do */
		{
			auto with0 = new TRegIniFile(IniFile);
			try
			{
				EditAuthor->Text = with0->ReadString(FFileName, L"Author", StrPas(UserName));
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
		StrDispose(UserName);
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
	for(stop = 0, i = this->ComponentCount - 1; i >= stop; i--)
	{
		if(ObjectIs(this->Components[i], TComboBox*))
		{
			if(((TComboBox*) this->Components[i])->Parent == GrpAttrNames)
			{
				((TComboBox*) this->Components[i])->Items->Clear();
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrAsm");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrAsmComment");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrAsmKey");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrASP");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrAssembler");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrBlock");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrBrackets");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrCharacter");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrClass");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrComment");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrCondition");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrDir");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrDirective");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrDocumentation");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrEmbedSQL");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrEmbedText");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrEscapeAmpersand");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrForm");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrFunction");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrIcon");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrIdentifier");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrIllegalChar");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrIndirect");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrInvalidSymbol");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrInternalFunction");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrKey");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrLabel");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrMacro");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrMarker");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrMessage");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrMiscellaneous");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrNull");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrNumber");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrOperator");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrPragma");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrPreprocessor");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrQualifier");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrRegister");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrReservedWord");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrRpl");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrRplKey");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrRplComment");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrSASM");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrSASMComment");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrSASMKey");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrSecondReservedWord");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrSection");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrSpace");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrSpecialVariable");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrString");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrSymbol");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrSyntaxError");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrSystem");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrSystemValue");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrText");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrUnknownWord");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrUser");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrUserFunction");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrValue");
				((TComboBox*) this->Components[i])->Items->Add(L"SYNS_AttrVariable");
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
		Position = poScreenCenter; // move form on the screen ("make visible")
	}
	else
	Application->Terminate();
}

void __fastcall TFrmMain::ClearAll()
{
	int I = 0;
  // Clear the contents of KeyList
	int stop = 0;
	for(stop = (KeyList->Count - 1), I = 0; I <= stop; I++)
	{
		delete ((TObject*) KeyList->Items[I]);
	}
	KeyList->Clear();
  // Clear the contents of SetList
	for(stop = (SetList->Count - 1), I = 0; I <= stop; I++)
	{
		delete ((TObject*) SetList->Items[I]);
	}
	SetList->Clear();
  // Clear the contents of EnclosedList
	for(stop = (EnclosedList->Count - 1), I = 0; I <= stop; I++)
	{
		delete ((TObject*) EnclosedList->Items[I]);
	}
	EnclosedList->Clear();
  // Clear the contents of IdentList
	for(stop = (IdentList->Count - 1), I = 0; I <= stop; I++)
	{
		if(ASSIGNED(IdentList->Objects[I]))
			delete IdentList->Objects[I];
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
	while(Lex->RunId != IdIdentifier)
		Lex->Next();
	LexName = Lex->RunToken;
	Lex->Next();
	while(Lex->RunId != IdIdentifier)
		Lex->Next();
	IdentPre = Lex->RunToken;
	OutFileCreate(OpenDialog->FileName);
	try
	{
		while(!(Syngenunit__3.Contains(Lex->RunId)))
			Lex->Next();
		if(Lex->RunId == IdSensitive)
			Sensitivity = true;
		else
			Sensitivity = false;
		Lex->Next();
		while(Lex->RunId != IdCharset)
			Lex->Next();
		IdentStart = Lex->RunToken;
		Lex->Next();
		while(Lex->RunId != IdNull)
		{
			switch(Lex->RunId)
			{
				case IdCharset:
				IdentContent = Lex->RunToken;
				break;
				case IdKeys:
				FillKeyList();
				break;
				case IdTokenTypes:
				FillTokenTypeList();
				break;
				case IdChars:
				ParseCharsets();
				break;
				case IdEnclosedBy:
				ParseEnclosedBy();
				break;
				case IdSampleSource:
				ParseSampleSource();
				break;
				default:
				  ;
				break;
			}
			Lex->Next();
		}
		if(KeyList->Count == 0)
			throw Exception(L"You should specify at least 1 keyword!");
		if(IdentList->Count == 0)
			throw Exception(L"You should specify at least 1 token type");
		if(!KeywordsAreAllAlphaNumAndDifferent())
			throw Exception(L"One or more keywords contain unhandable characters");
		FrmHashTableGen->AssignKeyWords(KeyList, Sensitivity);
		FrmHashTableGen->ShowModal();
		WriteRest();
		while((Lex->RunId != IdNull))
		{
			Lex->Next();
		}
	}
	__finally
	{
		Screen->Cursor = crDefault;
		CloseFile(OutFile);
	}
	MessageDlg(LexName + L" created on " + DateTimeToStr(Now()), TMsgDlgType::mtInformation, Syngenunit__4, 0);
}

void __fastcall TFrmMain::FillKeyList()
{
	TLexKeys* aLexKey = nullptr;
	String aString;
	String aTokenType;
	Lex->Next();
	aTokenType = L"";
	while(Lex->RunId != IdCRLF)
	{
		if(!(Syngenunit__5.Contains(Lex->RunId)))
			aTokenType = aTokenType + Lex->RunToken;
		Lex->Next();
	}
	if(aTokenType == L"")
		aTokenType = L"Key";
	while(Lex->RunId != IdStop)
	{
		while(Syngenunit__6.Contains(Lex->RunId))
			Lex->Next();
		if(Lex->RunId != IdStop)
		{
			aString = L"";
			while(!(Syngenunit__7.Contains(Lex->RunId)))
			{
				aString = aString + Lex->RunToken;
				Lex->Next();
			}
			aLexKey = new TLexKeys();
			aLexKey->TokenType = aTokenType;
			aLexKey->KeyName = aString;
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
	while((Lex->RunId != IdStop))
	{
		while(Syngenunit__8.Contains(Lex->RunId))
			Lex->Next();
		if(Lex->RunId != IdStop)
		{
			sIdent = IdentPre + Lex->RunToken;
			if(!IsValidIdent(sIdent))
				throw Exception(String(L"Invalid identifier for token type: ") + sIdent);
			if(IdentList->IndexOf(sIdent) < 0)
				IdentList->Add(sIdent);
			Lex->Next();
			sLine = L"";
			while((Lex->RunId == IdSpace))
				Lex->Next();
			while(!(Syngenunit__9.Contains(Lex->RunId)))
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
	Winapi::Windows::TSystemTime sysTime = {};
	String ISODate;
	OutName = ChangeFileExt(InName, L".pas");
	UName = ExtractFileName(ChangeFileExt(InName, L""));
	AssignFile(OutFile, OutName);
	Rewrite(OutFile);
	GetSystemTime(&sysTime);
	ISODate = Format(L"%.4d-%.2d-%.2d", ARRAYOFCONST((sysTime.wYear, sysTime.wMonth, sysTime.wDay)));
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
		WriteLn(OutFile, String(L"Copyright (c) ") + Format(L"%d", ARRAYOFCONST((sysTime.wYear)))
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
		WriteLn(OutFile, String(L" | Copyright (c) ") + Format(L"%d", ARRAYOFCONST((sysTime.wYear)))
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
	while(Lex->RunId != IdStop)
	{
		switch(Lex->RunId)
		{
			case IdCharset:
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
	while(!(Syngenunit__10.Contains(Lex->RunId)))
		RetrieveEnclosedBy();
}

void __fastcall TFrmMain::ParseSampleSource()
{
	Lex->Next();
	if(Lex->RunId == IdCRLF)
		Lex->Next();
	while(!(Syngenunit__11.Contains(Lex->RunId)))
		RetrieveSampleSource();
}

void __fastcall TFrmMain::RetrieveCharset()
{
	TLexCharsets* aSet = nullptr;
	aSet = new TLexCharsets();
	aSet->Charset = Lex->RunToken;
	while(Lex->RunId != IdIdentifier)
		Lex->Next();
	aSet->SetName = Lex->RunToken;
	while(Lex->RunId != IdBeginProc)
		Lex->Next();
	Lex->Next();
	while(Syngenunit__12.Contains(Lex->RunId))
		Lex->Next();
	while(!(Lex->RunId == IdEndProc))
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
	while(!(Syngenunit__13.Contains(Lex->RunId)))
	{
		sLine = sLine + Lex->RunToken;
		Lex->Next();
	}
	if(Lex->RunId == IdCRLF)
		Lex->Next();
	SampleSourceList->Add(sLine);
}

void __fastcall TFrmMain::RetrieveEnclosedBy()
{
	TLexEnclosedBy* aThing = nullptr;
	String sLine;
	int iPos = 0;
	while(Syngenunit__14.Contains(Lex->RunId))
		Lex->Next();
	sLine = L"";
	while(!(Syngenunit__15.Contains(Lex->RunId)))
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
		if(Lex->RunId != IdStop)
			Lex->Next();
	}
} /* RetrieveEnclosedBy */

String __fastcall TFrmMain::FilterInvalidChars(const String Value)
{
	String result;
	int i = 0;
	int stop = 0;
	result = L"";
	for(stop = Value.Length(), i = 1; i <= stop; i++)
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
	int I = 0;
	int J = 0;
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
	I = 0;
	while(I < IdentList->Count - 1)
	{
		WriteLn(OutFile, String(L"    ") + IdentList->Strings[I] + L",");
		++I;
	}
	WriteLn(OutFile, String(L"    ") + IdentList->Strings[I] + L");");
	WriteLn(OutFile);
	Write(OutFile, L"  TRangeState = (rsUnKnown");
	for(stop = (EnclosedList->Count - 1), I = 0; I <= stop; I++)
	{
		Write(OutFile, String(L", rs") + ((TLexEnclosedBy*) EnclosedList->Items[I])->ProcName);
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
		for(stop = ListBoxFields->Items->Count - 1, I = 0; I <= stop; I++)
		{
			WriteLn(OutFile, String(L"    ") + ListBoxFields->Items->Strings[I] + L";");
		}
	}
	WriteLn(OutFile, L"    fTokenID: TtkTokenKind;");
	WriteLn(OutFile, String(L"    fIdentFuncTable: array[0..") + IntToStr(FrmHashTableGen->KeyIndicesCount() - 1)
	           + L"]"
	           + L" of TIdentFuncTableFunc;");
	I = 0;
	while(I < IdentList->Count)
	{
		if((IdentList->Strings[I] != String(IdentPre) + L"Null") && (IdentList->Strings[I] != String(IdentPre) + L"Unknown"))
			WriteLn(OutFile, String(L"    f") + IdentList->Strings[I].SubString(IdentPre.Length() + 1, IdentList->Strings[I].Length())
			           + L"Attri: TSynHighlighterAttributes;");
		++I;
	}
	WriteLn(OutFile, L"    function HashKey(Str: PWideChar): Cardinal;");
	I = 0;
	while(I < KeyList->Count)
	{
		WriteLn(OutFile, AnsiString(String(L"    function Func") + ToAlphaNum(FirstLetterCap(((TLexKeys*) KeyList->Items[I])->KeyName))
	           + L"(Index: Integer): T"
	           + IdentPre
	           + L"TokenKind;"));
		++I;
	}
	I = 0;
	while(I < SetList->Count)
	{
		WriteLn(OutFile, String(L"    procedure ") + ((TLexCharsets*) SetList->Items[I])->SetName
		           + L"Proc;");
		++I;
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
	for(stop = (EnclosedList->Count - 1), I = 0; I <= stop; I++)
	{
		WriteLn(OutFile, String(L"    procedure ") + ((TLexEnclosedBy*) EnclosedList->Items[I])->ProcName
		           + L"OpenProc;");
		WriteLn(OutFile, String(L"    procedure ") + ((TLexEnclosedBy*) EnclosedList->Items[I])->ProcName
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
	I = 0;
	while(I < IdentList->Count)
	{
		if((IdentList->Strings[I] != String(IdentPre) + L"Null") && (IdentList->Strings[I] != String(IdentPre) + L"Unknown"))
			WriteLn(OutFile, String(L"    property ") + IdentList->Strings[I].SubString(IdentPre.Length() + 1, IdentList->Strings[I].Length())
			           + L"Attri: TSynHighlighterAttributes read f"
			           + IdentList->Strings[I].SubString(IdentPre.Length() + 1, IdentList->Strings[I].Length())
			           + L"Attri write f"
			           + IdentList->Strings[I].SubString(IdentPre.Length() + 1, IdentList->Strings[I].Length())
			           + L"Attri;");
		++I;
	}
	WriteLn(OutFile, L"  end;");
	WriteLn(OutFile);
	WriteLn(OutFile, L"implementation");
	WriteLn(OutFile);
	WriteLn(OutFile, L"uses");
	WriteLn(OutFile, L"  SynEditStrConst;");
	WriteLn(OutFile);
	if((CboFilter->ItemIndex == -1) || (CboLangName->ItemIndex == -1))
	{
		WriteLn(OutFile, L"resourcestring");
		if(CboFilter->ItemIndex == -1)
			WriteLn(OutFile, String(L"  SYNS_Filter") + FilterInvalidChars(CboLangName->Text)
	           + L" = '"
	           + CboFilter->Text
	           + L"';");
		if(CboLangName->ItemIndex == -1)
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
		I = 0;
		while(I < IdentList->Count)
		{
			AttrTemp = IdentList->Strings[I].SubString(IdentPre.Length() + 1, IdentList->Strings[I].Length());
			if((CboAttrIdentifier->Items->IndexOf(String(L"SYNS_Attr") + AttrTemp) < 0) && (AttrTemp != L"Unknown"))
			{
				WriteLn(OutFile, String(L"  SYNS_Attr") + FilterInvalidChars(AttrTemp) + L" = '" + AttrTemp + L"';");
				WriteLn(OutFile, String(L"  SYNS_FriendlyAttr") + FilterInvalidChars(AttrTemp)
	           + L" = '"
	           + AttrTemp
	           + L"';");
			}
			++I;
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
	I = 0;
	while(I < KeyList->Count)
	{
		if(I < KeyList->Count - 1)
		{
			while(((TLexKeys*) KeyList->Items[I])->Key == ((TLexKeys*) KeyList->Items[I + 1])->Key)
			{
				++I;
				if(I >= KeyList->Count - 1)
					break;
			}
		}
		KeyString = IntToStr(static_cast<__int64>(((TLexKeys*) KeyList->Items[I])->Key));
		WriteLn(OutFile, String(L"  fIdentFuncTable[") + KeyString
	           + L"] := Func"
	           + ToAlphaNum(FirstLetterCap(((TLexKeys*) KeyList->Items[I])->KeyName))
	           + L";");
		++I;
	}
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	Write(OutFile, FrmHashTableGen->GetHashKeyFunctionSource(LexName));
	WriteLn(OutFile);
	I = 0;
	while(I < KeyList->Count)
	{
		KeyString = ToAlphaNum(FirstLetterCap(((TLexKeys*) KeyList->Items[I])->KeyName));
		WriteLn(OutFile, String(L"function ") + LexName
		           + L".Func"
		           + KeyString
		           + L"(Index: Integer): T"
		           + IdentPre
		           + L"TokenKind;");
		WriteLn(OutFile, L"begin");
		if(I < KeyList->Count - 1)
		{
			while(((TLexKeys*) KeyList->Items[I])->Key == ((TLexKeys*) KeyList->Items[I + 1])->Key)
			{
				WriteLn(OutFile, L"  if IsCurrentToken(KeyWords[Index]) then");
				WriteLn(OutFile, String(L"    Result := ") + IdentPre + ((TLexKeys*) KeyList->Items[I])->TokenType);
				WriteLn(OutFile, L"  else");
				++I;
				if(I >= KeyList->Count - 1)
					break;
			}
		}
		WriteLn(OutFile, L"  if IsCurrentToken(KeyWords[Index]) then");
		WriteLn(OutFile, String(L"    Result := ") + IdentPre + ((TLexKeys*) KeyList->Items[I])->TokenType);
		WriteLn(OutFile, L"  else");
		WriteLn(OutFile, String(L"    Result := ") + IdentPre + L"Identifier;");
		WriteLn(OutFile, L"end;");
		WriteLn(OutFile);
		++I;
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
	for(stop = (EnclosedList->Count - 1), I = 0; I <= stop; I++)
	{
		int stop1 = 0;
		WriteLn(OutFile, String(L"procedure ") + LexName
		           + L"."
		           + ((TLexEnclosedBy*) EnclosedList->Items[I])->ProcName
		           + L"OpenProc;");
		WriteLn(OutFile, L"begin");
		WriteLn(OutFile, L"  Inc(Run);");
		if(((TLexEnclosedBy*) EnclosedList->Items[I])->StartsWith.Length() > 1)
		{
			int stop1 = 0;
			Write(OutFile, L"  if ");
			for(stop1 = ((TLexEnclosedBy*) EnclosedList->Items[I])->StartsWith.Length(), J = 2; J <= stop1; J++)
			{
				if(J > 2)
				{
					WriteLn(OutFile, L" and");
					Write(OutFile, L"     ");
				}
				Write(OutFile, String(L"(fLine[Run") + AddInt(J - 2)
	           + L"] = '"
	           + StuffString(String(((TLexEnclosedBy*) EnclosedList->Items[I])->StartsWith[J]))
	           + L"')");
			}
			WriteLn(OutFile, L" then");
			WriteLn(OutFile, L"  begin");
			WriteLn(OutFile, String(L"    Inc(Run, ") + IntToStr(((TLexEnclosedBy*) EnclosedList->Items[I])->StartsWith.Length() - 1)
	           + L");");
			WriteLn(OutFile, String(L"    fRange := rs") + ((TLexEnclosedBy*) EnclosedList->Items[I])->ProcName
			           + L";");
			if(!((TLexEnclosedBy*) EnclosedList->Items[I])->MultiLine)
			{
				WriteLn(OutFile, String(L"    ") + ((TLexEnclosedBy*) EnclosedList->Items[I])->ProcName + L"Proc;");
			}
			WriteLn(OutFile, String(L"    fTokenID := ") + IdentPre
			           + ((TLexEnclosedBy*) EnclosedList->Items[I])->TokenName
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
			WriteLn(OutFile, String(L"  fRange := rs") + ((TLexEnclosedBy*) EnclosedList->Items[I])->ProcName
			           + L";");
			if(!((TLexEnclosedBy*) EnclosedList->Items[I])->MultiLine)
			{
				WriteLn(OutFile, String(L"  ") + ((TLexEnclosedBy*) EnclosedList->Items[I])->ProcName + L"Proc;");
			}
			WriteLn(OutFile, String(L"  fTokenID := ") + IdentPre
			           + ((TLexEnclosedBy*) EnclosedList->Items[I])->TokenName
			           + L";");
		}
		WriteLn(OutFile, L"end;");
		WriteLn(OutFile);
		WriteLn(OutFile, String(L"procedure ") + LexName
		           + L"."
		           + ((TLexEnclosedBy*) EnclosedList->Items[I])->ProcName
		           + L"Proc;");
		WriteLn(OutFile, L"begin");
		if(((TLexEnclosedBy*) EnclosedList->Items[I])->MultiLine)
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
		           + ((TLexEnclosedBy*) EnclosedList->Items[I])->TokenName
		           + L";"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"  repeat"); }
		{ Write(OutFile, sPrefix); Write(OutFile, L"    if "); }
		for(stop1 = ((TLexEnclosedBy*) EnclosedList->Items[I])->EndsWith.Length(), J = 1; J <= stop1; J++)
		{
			if(J > 1)
			{
				WriteLn(OutFile, L" and");
				{ Write(OutFile, sPrefix); Write(OutFile, L"       "); }
			}
			Write(OutFile, String(L"(fLine[Run") + AddInt(J - 1)
	           + L"] = '"
	           + StuffString(String(((TLexEnclosedBy*) EnclosedList->Items[I])->EndsWith[J]))
	           + L"')");
		}
		WriteLn(OutFile, L" then");
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"    begin"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, String(L"      Inc(Run, ") + IntToStr(((TLexEnclosedBy*) EnclosedList->Items[I])->EndsWith.Length())
	           + L");"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"      fRange := rsUnKnown;"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"      Break;"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"    end;"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"    if not IsLineEnd(Run) then"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"      Inc(Run);"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"  until IsLineEnd(Run);"); }
		{ Write(OutFile, sPrefix); WriteLn(OutFile, L"end;"); }
		if(((TLexEnclosedBy*) EnclosedList->Items[I])->MultiLine)
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
	I = 0;
	while(I < IdentList->Count)
	{
		AttrTemp = IdentList->Strings[I].SubString(IdentPre.Length() + 1, IdentList->Strings[I].Length());
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
		if((IdentList->Strings[I] != String(IdentPre) + L"Null") && (IdentList->Strings[I] != String(IdentPre) + L"Unknown"))
		{
			AttrTemp = String(L"f") + AttrTemp + L"Attri";
			WriteLn(OutFile, String(L"  ") + AttrTemp
			           + L" := TSynHighLighterAttributes.Create("
			           + AttrName
			           + L", "
			           + FriendlyAttrName
			           + L");");
			if(ASSIGNED(IdentList->Objects[I]))
			{
				DefAttri = ((TLexDefaultAttri*) IdentList->Objects[I]);
				if(DefAttri->Style != L"")
					WriteLn(OutFile, String(L"  ") + AttrTemp + L".Style := " + DefAttri->Style + L";");
				if(DefAttri->Foreground != L"")
					WriteLn(OutFile, String(L"  ") + AttrTemp + L".Foreground := " + DefAttri->Foreground + L";");
				if(DefAttri->Background != L"")
					WriteLn(OutFile, String(L"  ") + AttrTemp + L".Background := " + DefAttri->Background + L";");
			}
			else
			{
				if(IdentList->Strings[I] == String(IdentPre) + L"Key")
					WriteLn(OutFile, String(L"  ") + AttrTemp + L".Style := [fsBold];");
				else
				{
					if(IdentList->Strings[I] == String(IdentPre) + L"Comment")
					{
						WriteLn(OutFile, String(L"  ") + AttrTemp + L".Style := [fsItalic];");
						WriteLn(OutFile, String(L"  ") + AttrTemp + L".Foreground := clNavy;");
					}
				}
			}
			WriteLn(OutFile, String(L"  AddAttribute(") + AttrTemp + L");");
			WriteLn(OutFile);
		}
		++I;
	}
	WriteLn(OutFile, L"  SetAttributesOnChange(DefHighlightChange);");
	WriteLn(OutFile, L"  InitIdent;");
	WriteLn(OutFile, String(L"  fDefaultFilter := ") + GetFilterName() + L";");
	WriteLn(OutFile, L"  fRange := rsUnknown;");
	WriteLn(OutFile, L"end;");
	WriteLn(OutFile);
	I = 0;
	while(I < SetList->Count)
	{
		WriteLn(OutFile, String(L"procedure ") + LexName
		           + L"."
		           + ((TLexCharsets*) SetList->Items[I])->SetName
		           + L"Proc;");
		WriteLn(OutFile, L"begin");
		Write(OutFile, String(L"  ") + ((TLexCharsets*) SetList->Items[I])->ProcData);
		WriteLn(OutFile, L"end;");
		WriteLn(OutFile);
		++I;
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
		for(stop = (EnclosedList->Count - 1), I = 0; I <= stop; I++)
		{
			if(((TLexEnclosedBy*) EnclosedList->Items[I])->MultiLine)
			{
				WriteLn(OutFile, String(L"    rs") + ((TLexEnclosedBy*) EnclosedList->Items[I])->ProcName
				           + L": "
				           + ((TLexEnclosedBy*) EnclosedList->Items[I])->ProcName
				           + L"Proc;");
			}
		}
		WriteLn(OutFile, L"  else");
		WriteLn(OutFile, L"    case fLine[Run] of");
		WriteLn(OutFile, L"      #0: NullProc;");
		WriteLn(OutFile, L"      #10: LFProc;");
		WriteLn(OutFile, L"      #13: CRProc;");
		for(stop = (EnclosedList->Count - 1), I = 0; I <= stop; I++)
		{
			if(((TLexEnclosedBy*) EnclosedList->Items[I])->StartsWith != L"")
			{
				WriteLn(OutFile, String(L"      '") + StuffString(String(((TLexEnclosedBy*) EnclosedList->Items[I])->StartsWith[1]))
	           + L"': "
	           + ((TLexEnclosedBy*) EnclosedList->Items[I])->ProcName
	           + L"OpenProc;");
			}
		}
		if(IdentList->IndexOf(IdentPre + L"Space") >= 0)
			WriteLn(OutFile, L"      #1..#9, #11, #12, #14..#32: SpaceProc;");
		I = 0;
		while(I < SetList->Count)
		{
			WriteLn(OutFile, String(L"      ") + ((TLexCharsets*) SetList->Items[I])->Charset
			           + L": "
			           + ((TLexCharsets*) SetList->Items[I])->SetName
			           + L"Proc;");
			++I;
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
		I = 0;
		while(I < SetList->Count)
		{
			WriteLn(OutFile, String(L"    ") + ((TLexCharsets*) SetList->Items[I])->Charset
			           + L": "
			           + ((TLexCharsets*) SetList->Items[I])->SetName
			           + L"Proc;");
			++I;
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
			for(stop = KeyList->Count - 1, I = 0; I <= stop; I++)
			{
				TempStringList->Add(((TLexKeys*) KeyList->Items[I])->KeyName);
			}
			if(TempStringList->Count > 0)
			{
				int stop = 0;
				WriteLn(OutFile, L"  Result := ");
				for(stop = Trunc(Int(static_cast<long double>((int)(TempStringList->CommaText.Length() / /*div*/ 70)))) - 1, I = 0; I <= stop; I++)
				{
					if(I == 0)
						LineLength = 69;
					else
						LineLength = 70;
					WriteLn(OutFile, String(L"    " L"\x27") + TempStringList->CommaText.SubString(I * 70, LineLength)
					           + L"\x27"
					           + L"\x20"
					           + L"\x2b");
				}
				I = Trunc(Int(static_cast<long double>((int)(TempStringList->CommaText.Length() / /*div*/ 70))));
				WriteLn(OutFile, String(L"    " L"\x27") + TempStringList->CommaText.SubString(I * 70, TempStringList->CommaText.Length())
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
	I = 0;
	while(I < IdentList->Count)
	{
		if((IdentList->Strings[I] != String(IdentPre) + L"Null") && (IdentList->Strings[I] != String(IdentPre) + L"Unknown"))
			WriteLn(OutFile, String(L"    ") + IdentList->Strings[I]
			           + L": Result := f"
			           + IdentList->Strings[I].SubString(IdentPre.Length() + 1, IdentList->Strings[I].Length())
			           + L"Attri;");
		++I;
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
		for(stop = SampleSourceList->Count - 1, I = 0; I <= stop; I++)
		{
			if((I > 0) && (I < SampleSourceList->Count - 1))
				WriteLn(OutFile, L"#13#10 +");
			if(I < SampleSourceList->Count - 1)
				Write(OutFile, L"    ");
			if(SampleSourceList->Strings[I] != L"")
				{ Write(OutFile, L'\''); Write(OutFile, StuffString(SampleSourceList->Strings[I])); Write(OutFile, L'\''); }
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
	BtnDelete->Enabled = true;
}

void __fastcall TFrmMain::BtnAddClick(TObject* Sender)
{
	ListBoxFields->Items->Add(EditAddField->Text);
	EditAddField->Clear();
}

void __fastcall TFrmMain::BtnDeleteClick(TObject* Sender)
{
	BtnDelete->Enabled = false;
	ListBoxFields->Items->Delete(ListBoxFields->ItemIndex);
}

void __fastcall TFrmMain::EditAddFieldChange(TObject* Sender)
{
	BtnAdd->Enabled = EditAddField->Text != L"";
}

void __fastcall TFrmMain::EditAddFieldKeyPress(TObject* Sender, Char& Key)
{
	if((Key == L';') || (Key == L'\x20'))
		Key = L'\x00';
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
	TStringList* KeyWordList = nullptr;
	int stop = 0;
	result = true;
	KeyWordList = new TStringList();
	{
		auto olsLambda = onLeavingScope([&] 
		{
			delete KeyWordList;
		});
		KeyWordList->Sorted = true;
		KeyWordList->Duplicates = dupError;
		try
		{
			int stop = 0;
			for(stop = KeyList->Count - 1, i = 0; i <= stop; i++)
			{
				KeyWordList->Add(((TLexKeys*) KeyList->Items[i])->KeyName);
			}
		}
		catch(...)
		{
			result = false;
			return result;
		}
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

__fastcall TFrmMain::TFrmMain(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	BtnStart(nullptr),
	OpenDialog(nullptr),
	PageControl(nullptr),
	TabLanguage(nullptr),
	LblFilter(nullptr),
	CboFilter(nullptr),
	LblLangName(nullptr),
	CboLangName(nullptr),
	TabAttributes(nullptr),
	GrpAttrNames(nullptr),
	LblIdentifier(nullptr),
	LblReservedWord(nullptr),
	CboAttrIdentifier(nullptr),
	CboAttrReservedWord(nullptr),
	LblUnknownTokenAttr(nullptr),
	CboUnknownTokenAttr(nullptr),
	TabFields(nullptr),
	BtnAdd(nullptr),
	BtnDelete(nullptr),
	EditAddField(nullptr),
	ListBoxFields(nullptr),
	MainMenu(nullptr),
	MnuFile(nullptr),
	MnuOpen(nullptr),
	MnuExit(nullptr),
	TabHighlighter(nullptr),
	LblAuthor(nullptr),
	LblDescription(nullptr),
	LblVersion(nullptr),
	EditAuthor(nullptr),
	EditDescription(nullptr),
	EditVersion(nullptr),
	MnuStart(nullptr),
	ChkGetKeyWords(nullptr),
	ChkGPLHeader(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Left = 379;
	Top = 238;
	BorderIcons = (TBorderIcons() << biSystemMenu << biMinimize);
	BorderStyle = bsSingle;
	Caption = L"SynGen";
	ClientHeight = 288;
	ClientWidth = 368;
	Color = clBtnFace;
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = clWindowText;
	Font->Height = -11;
	Font->Name = L"MS Sans Serif";
	Font->Style = (TFontStyles());
	AssignFormOldCreateOrder(this, false);
	OnClose = FormClose;
	OnCreate = FormCreate;
	OnDestroy = FormDestroy;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	PageControl = new TPageControl(this);
	PageControl->Parent = this;
	PageControl->Left = 8;
	PageControl->Top = 8;
	PageControl->Width = 353;
	PageControl->Height = 241;
	PageControl->TabOrder = 1;
	PageControl->TabWidth = 80;
	TabHighlighter = new TTabSheet(PageControl);
	TabHighlighter->Parent = PageControl;
	TabHighlighter->PageControl = PageControl;
	TabHighlighter->Caption = L"Highlighter";
	LblAuthor = new TLabel(TabHighlighter);
	LblAuthor->Parent = TabHighlighter;
	LblAuthor->Left = 8;
	LblAuthor->Top = 20;
	LblAuthor->Width = 34;
	LblAuthor->Height = 13;
	LblAuthor->Caption = L"Author:";
	LblDescription = new TLabel(TabHighlighter);
	LblDescription->Parent = TabHighlighter;
	LblDescription->Left = 8;
	LblDescription->Top = 52;
	LblDescription->Width = 56;
	LblDescription->Height = 13;
	LblDescription->Caption = L"Description:";
	LblVersion = new TLabel(TabHighlighter);
	LblVersion->Parent = TabHighlighter;
	LblVersion->Left = 8;
	LblVersion->Top = 84;
	LblVersion->Width = 38;
	LblVersion->Height = 13;
	LblVersion->Caption = L"Version:";
	EditAuthor = new TEdit(TabHighlighter);
	EditAuthor->Parent = TabHighlighter;
	EditAuthor->Left = 80;
	EditAuthor->Top = 16;
	EditAuthor->Width = 257;
	EditAuthor->Height = 21;
	EditAuthor->TabOrder = 0;
	EditDescription = new TEdit(TabHighlighter);
	EditDescription->Parent = TabHighlighter;
	EditDescription->Left = 80;
	EditDescription->Top = 48;
	EditDescription->Width = 257;
	EditDescription->Height = 21;
	EditDescription->TabOrder = 1;
	EditVersion = new TEdit(TabHighlighter);
	EditVersion->Parent = TabHighlighter;
	EditVersion->Left = 80;
	EditVersion->Top = 80;
	EditVersion->Width = 257;
	EditVersion->Height = 21;
	EditVersion->TabOrder = 2;
	ChkGetKeyWords = new TCheckBox(TabHighlighter);
	ChkGetKeyWords->Parent = TabHighlighter;
	ChkGetKeyWords->Left = 8;
	ChkGetKeyWords->Top = 188;
	ChkGetKeyWords->Width = 249;
	ChkGetKeyWords->Height = 17;
	ChkGetKeyWords->Caption = L"Include optional GetKeyWords public method";
	ChkGetKeyWords->Checked = true;
	ChkGetKeyWords->State = cbChecked;
	ChkGetKeyWords->TabOrder = 4;
	ChkGPLHeader = new TCheckBox(TabHighlighter);
	ChkGPLHeader->Parent = TabHighlighter;
	ChkGPLHeader->Left = 8;
	ChkGPLHeader->Top = 168;
	ChkGPLHeader->Width = 249;
	ChkGPLHeader->Height = 17;
	ChkGPLHeader->Caption = L"Use SynEdit standard GPL comment header";
	ChkGPLHeader->Checked = true;
	ChkGPLHeader->State = cbChecked;
	ChkGPLHeader->TabOrder = 3;
	TabLanguage = new TTabSheet(PageControl);
	TabLanguage->Parent = PageControl;
	TabLanguage->PageControl = PageControl;
	TabLanguage->Caption = L"Language";
	LblFilter = new TLabel(TabLanguage);
	LblFilter->Parent = TabLanguage;
	LblFilter->Left = 8;
	LblFilter->Top = 20;
	LblFilter->Width = 59;
	LblFilter->Height = 13;
	LblFilter->Caption = L"Default filter:";
	LblLangName = new TLabel(TabLanguage);
	LblLangName->Parent = TabLanguage;
	LblLangName->Left = 8;
	LblLangName->Top = 52;
	LblLangName->Width = 80;
	LblLangName->Height = 13;
	LblLangName->Caption = L"Language name:";
	CboFilter = new TComboBox(TabLanguage);
	CboFilter->Parent = TabLanguage;
	CboFilter->Left = 96;
	CboFilter->Top = 16;
	CboFilter->Width = 241;
	CboFilter->Height = 21;
	CboFilter->ItemHeight = 13;
	CboFilter->TabOrder = 0;
	CboFilter->Text = L"All files (*.*)|*.*";
	CboFilter->OnChange = CboLangNameChange;
	CboFilter->Items->Add(L"Pascal files (*.pas,*.dpr,*.dpk,*.inc)|*.pas;*.dpr;*.dpk;*.inc");
	CboFilter->Items->Add(L"HP48 files (*.s,*.sou,*.a,*.hp)|*.s;*.sou;*.a;*.hp");
	CboFilter->Items->Add(L"CA-Clipper files (*.prg, *.ch, *.inc)|*.prg;*.ch;*.inc");
	CboFilter->Items->Add(L"C++ files (*.cpp,*.h,*.hpp)|*.cpp;*.h;*.hpp");
	CboFilter->Items->Add(L"Java files (*.java)|*.java");
	CboFilter->Items->Add(L"Perl files (*.pl,*.pm,*.cgi)|*.pl;*.pm;*.cgi");
	CboFilter->Items->Add(L"AWK Script (*.awk)|*.awk");
	CboFilter->Items->Add(L"HTML Document (*.htm,*.html)|*.htm;*.html");
	CboFilter->Items->Add(L"VBScript files (*.vbs)|*.vbs");
	CboFilter->Items->Add(L"Galaxy files (*.gtv,*.galrep,*.txt)|*.gtv;*.galrep;*.txt");
	CboFilter->Items->Add(L"Python files (*.py)|*.py");
	CboFilter->Items->Add(L"SQL files (*.sql)|*.sql");
	CboFilter->Items->Add(L"HP48 files (*.s,*.sou,*.a,*.hp)|*.s;*.sou;*.a;*.hp");
	CboFilter->Items->Add(L"Tcl/Tk files (*.tcl)|*.tcl");
	CboFilter->Items->Add(L"Rich Text Format (*.rtf)|*.rtf");
	CboFilter->Items->Add(L"MS-DOS Batch Files (*.bat)|*.bat");
	CboFilter->Items->Add(L"Delphi/C++ Builder Form Files (*.dfm)|*.dfm");
	CboFilter->Items->Add(L"x86 Assembly Files (*.asm)|*.asm");
	CboFilter->Items->Add(L"GEMBASE files (*.dml,*.gem)|*.dml;*.gem");
	CboFilter->Items->Add(L"INI Files (*.ini)|*.ini");
	CboFilter->Items->Add(L"Standard ML Files (*.sml)|*.sml");
	CboFilter->Items->Add(L"Visual Basic files (*.bas)|*.bas");
	CboFilter->Items->Add(L"DSP files (*.dsp,*.inc)|*.dsp;*.inc");
	CboFilter->Items->Add(L"PHP files (*.php,*.php3,*.phtml,*.inc)|*.php;*.php3;*.phtml;*.inc");
	CboFilter->Items->Add(L"Cache files (*.mac,*.inc,*.int)|*.mac;*.inc;*.int");
	CboFilter->Items->Add(L"Cascading Stylesheets (*.css)|*.css");
	CboFilter->Items->Add(L"Javascript files (*.js)|*.js");
	CboFilter->Items->Add(L"Kix Scripts (*.kix)|*.kix");
	CboFilter->Items->Add(L"Baan 4GL files (*.cln)|*.cln");
	CboFilter->Items->Add(L"Foxpro Files (*.prg)|*.prg");
	CboFilter->Items->Add(L"Fortran Files (*.for)|*.for");
	CboFilter->Items->Add(L"68HC11 Assembler files (*.hc11,*.asm,*.asc)|*.hc11;*.asm;*.asc");
	CboLangName = new TComboBox(TabLanguage);
	CboLangName->Parent = TabLanguage;
	CboLangName->Left = 96;
	CboLangName->Top = 48;
	CboLangName->Width = 241;
	CboLangName->Height = 21;
	CboLangName->ItemHeight = 13;
	CboLangName->TabOrder = 1;
	CboLangName->OnChange = CboLangNameChange;
	CboLangName->Items->Add(L"HP48");
	CboLangName->Items->Add(L"CA-Clipper");
	CboLangName->Items->Add(L"C++");
	CboLangName->Items->Add(L"Java");
	CboLangName->Items->Add(L"Perl");
	CboLangName->Items->Add(L"MS-DOS Batch Language");
	CboLangName->Items->Add(L"Delphi/C++ Builder Form Definitions");
	CboLangName->Items->Add(L"AWK Script");
	CboLangName->Items->Add(L"HTML Document");
	CboLangName->Items->Add(L"MS VBScript");
	CboLangName->Items->Add(L"Galaxy");
	CboLangName->Items->Add(L"General");
	CboLangName->Items->Add(L"ObjectPascal");
	CboLangName->Items->Add(L"x86 Assembly Language");
	CboLangName->Items->Add(L"Python");
	CboLangName->Items->Add(L"Tcl/Tk");
	CboLangName->Items->Add(L"SQL");
	CboLangName->Items->Add(L"Gembase");
	CboLangName->Items->Add(L"INI files");
	CboLangName->Items->Add(L"Standard ML");
	CboLangName->Items->Add(L"Visual Basic");
	CboLangName->Items->Add(L"ADSP21xx");
	CboLangName->Items->Add(L"PHP");
	CboLangName->Items->Add(L"Sybase SQL");
	CboLangName->Items->Add(L"General Multi-Highlighter");
	CboLangName->Items->Add(L"Cache object script");
	CboLangName->Items->Add(L"Cascading Stylesheets");
	CboLangName->Items->Add(L"Javascript");
	CboLangName->Items->Add(L"KIX32");
	CboLangName->Items->Add(L"Baan 4GL");
	CboLangName->Items->Add(L"Foxpro");
	CboLangName->Items->Add(L"Fortran");
	CboLangName->Items->Add(L"68HC11 Assembler");
	TabAttributes = new TTabSheet(PageControl);
	TabAttributes->Parent = PageControl;
	TabAttributes->PageControl = PageControl;
	TabAttributes->Caption = L"Attributes";
	LblUnknownTokenAttr = new TLabel(TabAttributes);
	LblUnknownTokenAttr->Parent = TabAttributes;
	LblUnknownTokenAttr->Left = 8;
	LblUnknownTokenAttr->Top = 120;
	LblUnknownTokenAttr->Width = 164;
	LblUnknownTokenAttr->Height = 13;
	LblUnknownTokenAttr->Caption = L"Assign unknown token to attribute:";
	GrpAttrNames = new TGroupBox(TabAttributes);
	GrpAttrNames->Parent = TabAttributes;
	GrpAttrNames->Left = 8;
	GrpAttrNames->Top = 8;
	GrpAttrNames->Width = 329;
	GrpAttrNames->Height = 96;
	GrpAttrNames->Caption = L"Attribute names";
	GrpAttrNames->TabOrder = 0;
	LblIdentifier = new TLabel(GrpAttrNames);
	LblIdentifier->Parent = GrpAttrNames;
	LblIdentifier->Left = 16;
	LblIdentifier->Top = 32;
	LblIdentifier->Width = 43;
	LblIdentifier->Height = 13;
	LblIdentifier->Caption = L"Identifier:";
	LblReservedWord = new TLabel(GrpAttrNames);
	LblReservedWord->Parent = GrpAttrNames;
	LblReservedWord->Left = 16;
	LblReservedWord->Top = 64;
	LblReservedWord->Width = 75;
	LblReservedWord->Height = 13;
	LblReservedWord->Caption = L"Reserved word:";
	CboAttrIdentifier = new TComboBox(GrpAttrNames);
	CboAttrIdentifier->Parent = GrpAttrNames;
	CboAttrIdentifier->Left = 104;
	CboAttrIdentifier->Top = 28;
	CboAttrIdentifier->Width = 209;
	CboAttrIdentifier->Height = 21;
	CboAttrIdentifier->Style = csDropDownList;
	CboAttrIdentifier->ItemHeight = 13;
	CboAttrIdentifier->TabOrder = 0;
	CboAttrReservedWord = new TComboBox(GrpAttrNames);
	CboAttrReservedWord->Parent = GrpAttrNames;
	CboAttrReservedWord->Left = 104;
	CboAttrReservedWord->Top = 60;
	CboAttrReservedWord->Width = 209;
	CboAttrReservedWord->Height = 21;
	CboAttrReservedWord->Style = csDropDownList;
	CboAttrReservedWord->ItemHeight = 13;
	CboAttrReservedWord->TabOrder = 1;
	CboUnknownTokenAttr = new TComboBox(TabAttributes);
	CboUnknownTokenAttr->Parent = TabAttributes;
	CboUnknownTokenAttr->Left = 184;
	CboUnknownTokenAttr->Top = 116;
	CboUnknownTokenAttr->Width = 153;
	CboUnknownTokenAttr->Height = 21;
	CboUnknownTokenAttr->Style = csDropDownList;
	CboUnknownTokenAttr->ItemHeight = 13;
	CboUnknownTokenAttr->TabOrder = 1;
	CboUnknownTokenAttr->Items->Add(L"Identifier");
	CboUnknownTokenAttr->Items->Add(L"Symbol");
	CboUnknownTokenAttr->Items->Add(L"Miscellaneous");
	TabFields = new TTabSheet(PageControl);
	TabFields->Parent = PageControl;
	TabFields->PageControl = PageControl;
	TabFields->Caption = L"Private Fields";
	ListBoxFields = new TListBox(TabFields);
	ListBoxFields->Parent = TabFields;
	ListBoxFields->Left = 8;
	ListBoxFields->Top = 40;
	ListBoxFields->Width = 249;
	ListBoxFields->Height = 161;
	ListBoxFields->ItemHeight = 13;
	ListBoxFields->Sorted = true;
	ListBoxFields->TabOrder = 3;
	ListBoxFields->OnClick = ListBoxFieldsClick;
	BtnAdd = new TButton(TabFields);
	BtnAdd->Parent = TabFields;
	BtnAdd->Left = 264;
	BtnAdd->Top = 8;
	BtnAdd->Width = 73;
	BtnAdd->Height = 23;
	BtnAdd->Caption = L"Add";
	BtnAdd->Enabled = false;
	BtnAdd->TabOrder = 0;
	BtnAdd->OnClick = BtnAddClick;
	BtnDelete = new TButton(TabFields);
	BtnDelete->Parent = TabFields;
	BtnDelete->Left = 264;
	BtnDelete->Top = 40;
	BtnDelete->Width = 73;
	BtnDelete->Height = 23;
	BtnDelete->Caption = L"Delete";
	BtnDelete->Enabled = false;
	BtnDelete->TabOrder = 1;
	BtnDelete->OnClick = BtnDeleteClick;
	EditAddField = new TEdit(TabFields);
	EditAddField->Parent = TabFields;
	EditAddField->Left = 8;
	EditAddField->Top = 8;
	EditAddField->Width = 249;
	EditAddField->Height = 21;
	EditAddField->TabOrder = 2;
	EditAddField->OnChange = EditAddFieldChange;
	EditAddField->OnKeyPress = EditAddFieldKeyPress;
	BtnStart = new TButton(this);
	BtnStart->Parent = this;
	BtnStart->Left = 288;
	BtnStart->Top = 257;
	BtnStart->Width = 75;
	BtnStart->Height = 23;
	BtnStart->Caption = L"Start!";
	BtnStart->Default = true;
	BtnStart->TabOrder = 0;
	BtnStart->OnClick = BtnStartClick;
	OpenDialog = new TOpenDialog(this);
	OpenDialog->Filter = L"Grammar file (*.msg)|*.msg";
	// non-visible component: Left
	// non-visible component: Top
	MainMenu = new TMainMenu(this);
	// non-visible component: Left
	// non-visible component: Top
	MnuFile = CreateTMainMenuTMenuItem(MainMenu);
	MnuFile->Caption = L"&File";
	MnuOpen = CreateTMenuItemTMenuItem(MnuFile);
	MnuOpen->Caption = L"&Open...";
	MnuOpen->ShortCut = 16463;
	MnuOpen->OnClick = MnuOpenClick;
	MnuExit = CreateTMenuItemTMenuItem(MnuFile);
	MnuExit->Caption = L"E&xit";
	MnuExit->ShortCut = 32883;
	MnuExit->OnClick = MnuExitClick;
	MnuStart = CreateTMainMenuTMenuItem(MainMenu);
	MnuStart->Caption = L"&Start!";
	MnuStart->OnClick = BtnStartClick;
	ComponentState >> csLoading;
	//----- shifted initializations from the dfm-file ---------------------------
	ActiveControl = BtnStart;
	Menu = MainMenu;
	PageControl->ActivePage = TabHighlighter;
	//----- end of initializations from the dfm-file ----------------------------
}

