#include <vcl.h>
#pragma hdrstop

#include "SynSpellCheck.h"
#include <Vcl.Dialogs.hpp>
#include <System.Win.Registry.hpp>
#include "SynEditHighlighter.h"
#include "SynEditMiscProcs.h"
#include "SynHighlighterURI.h"
#include <System.UITypes.hpp>
#include "d2c_convert.h"
#include "d2c_sysfile.h"
#include <functional>

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Synedithighlighter;
using namespace Syneditmiscprocs;
using namespace Synedittypes;
using namespace Synhighlighteruri;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Types;
using namespace System::Uitypes;
using namespace System::Win::Registry;
using namespace Vcl::Dialogs;
using namespace Vcl::Graphics;

namespace Synspellcheck
{
#define Synspellcheck__1 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synspellcheck__2 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synspellcheck__3 (TPlugInHandlers() << phAfterPaint)
#define Synspellcheck__4 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)

__fastcall TSynEditEx::TSynEditEx(TComponent* AOwner) : inherited(AOwner) {}
__fastcall TSynEditEx::TSynEditEx(HWND ParentWindow) : inherited(ParentWindow) {}
__fastcall TDrawAutoSpellCheckPlugin::TDrawAutoSpellCheckPlugin(Synedit::TCustomSynEdit* AOwner, Synedit::TPlugInHandlers AHandlers) : inherited(AOwner, AHandlers) {}
__fastcall TDrawAutoSpellCheckPlugin::TDrawAutoSpellCheckPlugin() {}
__fastcall ENoDictionaryLoaded::ENoDictionaryLoaded(const String Msg) : inherited(Msg) {}
__fastcall ENoDictionaryLoaded::ENoDictionaryLoaded(const String Msg, const TVarRec* Args, int Args_maxidx) : inherited(Msg, Args, Args_maxidx) {}
__fastcall ENoDictionaryLoaded::ENoDictionaryLoaded(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Msg, Args, Args_maxidx, AHelpContext) {}
__fastcall ENoDictionaryLoaded::ENoDictionaryLoaded(const String Msg, int AHelpContext) : inherited(Msg, AHelpContext) {}
__fastcall ENoDictionaryLoaded::ENoDictionaryLoaded(System::NativeUInt Ident) : inherited(Ident) {}
__fastcall ENoDictionaryLoaded::ENoDictionaryLoaded(System::PResStringRec ResStringRec) : inherited(ResStringRec) {}
__fastcall ENoDictionaryLoaded::ENoDictionaryLoaded(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx) : inherited(Ident, Args, Args_maxidx) {}
__fastcall ENoDictionaryLoaded::ENoDictionaryLoaded(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx) : inherited(ResStringRec, Args, Args_maxidx) {}
__fastcall ENoDictionaryLoaded::ENoDictionaryLoaded(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(ResStringRec, Args, Args_maxidx, AHelpContext) {}
__fastcall ENoDictionaryLoaded::ENoDictionaryLoaded(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Ident, Args, Args_maxidx, AHelpContext) {}
__fastcall ENoDictionaryLoaded::ENoDictionaryLoaded(System::NativeUInt Ident, int AHelpContext) : inherited(Ident, AHelpContext) {}
__fastcall ENoDictionaryLoaded::ENoDictionaryLoaded(System::PResStringRec ResStringRec, int AHelpContext) : inherited(ResStringRec, AHelpContext) {}



void __fastcall Register()
{
	TComponentClass classesSynspellcheck__0[1] = {__classid(TSynSpellCheck)};
	RegisterComponents(L"SynEdit", classesSynspellcheck__0, 1);
}

bool __fastcall ContainsNumbers(String sWord)
{
	bool result = false;
	int II = 0;
	int stop = 0;
	result = false;
	for(stop = sWord.Length(), II = 1; II <= stop; II++)
	{
		if(CharInSet(sWord[II], Synspellcheck__1))
		{
			result = true;
			break;
		}
	}
	return result;
}

String __fastcall DupeString(const String AText, int ACount)
{
	String result;
	PWideChar P = nullptr;
	int C = 0;
	C = AText.Length();
	result.SetLength(C * ACount);
	P = ustr2pwchar(result);
	if(P == nullptr)
		return result;
	while(ACount > 0)
	{
		Move(ustr2address(AText), P, C * sizeof(WideChar));
		P += C;
		--ACount;
	}
	return result;
}

int __fastcall ElfHash(const String Value)
{
	int result = 0;
	int II = 0;
	int iJ = 0;
	int stop = 0;
	result = 0;
	for(stop = Value.Length(), II = 1; II <= stop; II++)
	{
		result = (result << 4) + int(Value[II]);
		iJ = result & 0xF0000000;
		if(iJ != 0)
			result = result ^ (iJ >> 24);
		result = result & (~iJ);
	}
	return result;
}

void __fastcall JHCMPMatrix(int X, int Y, TJHCMPLongintMatrix& LongintMatrix)
{
	int lI = 0;
	int stop = 0;
	LongintMatrix.Length = X;
	for(stop = LongintMatrix.High, lI = LongintMatrix.Low; lI <= stop; lI++)
	{
		LongintMatrix[lI].Length = Y;
	}
}

void __fastcall JHCMPMatrixInit(TJHCMPLongintMatrix& LongintMatrix)
{
	int lI = 0;
	int stop = 0;
	for(stop = LongintMatrix.High, lI = LongintMatrix.Low; lI <= stop; lI++)
	{
		LongintMatrix[lI][0] = lI;
	}
	for(stop = LongintMatrix[0].High, lI = LongintMatrix[0].Low; lI <= stop; lI++)
	{
		LongintMatrix[0][lI] = lI;
	}
}

int __fastcall JHCMPMin(int A, int B, int C)
{
	int result = 0;
	result = Min(Min(A, B), C);
	return result;
}

/* TSynSpellCheck */

String __fastcall TSynSpellCheck::GetDefaultDictionaryDir()
{
	String result;
	result = L"C:\\Program Files\\Common Files\\SynSpell\\";
	/*# with TRegistry.Create do */
	{
		auto with0 = new TRegistry();
		try
		{
			with0->RootKey = HKEY_LOCAL_MACHINE;
			if(with0->OpenKeyReadOnly(L"Software\\Microsoft\\Windows\\CurrentVersion"))
			{
				if(with0->ValueExists(L"CommonFilesDir"))
					result = with0->ReadString(L"CommonFilesDir") + L"\\SynSpell\\";
				with0->CloseKey();
			}
		}
		__finally
		{
			delete with0;
		}
	}
	return result;
}

String __fastcall TSynSpellCheck::GetDictionaryDir()
{
	String result;
	if(FDictPath != L"")
		result = IncludeTrailingPathDelimiter(FDictPath);
	else
		result = IncludeTrailingPathDelimiter(GetDefaultDictionaryDir());
	return result;
}

String __fastcall TSynSpellCheck::GetUserDictionaryDir()
{
	String result;
	if(FUserDictPath != L"")
		result = IncludeTrailingPathDelimiter(FUserDictPath);
	else
		result = IncludeTrailingPathDelimiter(GetDefaultDictionaryDir());
	return result;
}

bool __fastcall IsNumber(const WideChar* PWORD)
{
	bool result = false;
	int II = 0;
	int stop = 0;
	result = true;
	for(stop = StrLen(PWORD), II = 1; II <= stop; II++)
	{
		if(!CharInSet((PWORD + II)[1], Synspellcheck__2))
		{
			result = false;
			break;
		}
	}
	return result;
}

int __fastcall SortFunc(void* Item1, void* Item2)
{
	int result = 0;
	String S1;
	String S2;
  // this is intentional construction, AnsiCompareText isn't useable here
  // this form of sort is used for indexing later
	S1 = AnsiLowerCase(((TWordRec*) &(*(TWordRec*) Item1))->Word);
	S2 = AnsiLowerCase(((TWordRec*) &(*(TWordRec*) Item2))->Word);
	if(S1 == S2)
		result = 0;
	else
	{
		if(S1 < S2)
			result = -1;
		else
			result = 1;
	}
	return result;
}

String __fastcall TrimEx(const String sWord, WideChar chChar)
{
	String result;
	int II = 0;
	int iLength = 0;
	iLength = sWord.Length();
	II = 1;
	while((II <= iLength) && (sWord[II] <= chChar))
		++II;
	if(II > iLength)
		result = L"";
	else
	{
		while(sWord[iLength] == chChar)
			--iLength;
		result = sWord.SubString(II, iLength - II + 1);
	}
	return result;
}  

/* TDrawAutoSpellCheckPlugin */

__fastcall TDrawAutoSpellCheckPlugin::TDrawAutoSpellCheckPlugin(TCustomSynEdit* AOwner)
 : inherited(AOwner),
			FPenColor(clRed),
			FUnderlineStyle(usMicrosoftWord),
			FSynSpellCheck(nullptr)
{
	FHandlers = Synspellcheck__3;
}

void __fastcall TDrawAutoSpellCheckPlugin::AfterPaint(TCanvas* ACanvas, const TRect& AClip, int FirstLine, int LastLine)
{
	int LH = 0;
	int cx = 0;
	String CurrentWord;
	TSynEdit* Editor = nullptr;
	TBufferCoord CurrentXY = {};
	TPoint TP = {};

	auto PaintUnderLine = [&]() -> void 
	{
		int MaxX = 0;
		int NewPoint = 0;
		int NewY = 0;

		auto DrawPoint = [&]() -> void 
		{

      // Do not draw on gutter.
      // This happens when a word is underlined and part of it is "hidden" under
      // the gutter.
			if(TP.X <= Editor->Gutter->RealGutterWidth())
				return;
			/*# with ACanvas do */
			{
				auto with0 = ACanvas;
				if(NewY == TP.Y - 1)
					with0->Pen->Color = Editor->Color;
				else
					with0->Pen->Color = FPenColor;
				with0->Pixels[TP.X][NewY] = with0->Pen->Color;
			}
		};
    // Microsoft Word style
//  MW_POINTS: array[0..6] of ShortInt = (1, 2, 2, 1, 0, 0, 0);
		const signed char MW_POINTS[4/*# range 0..3*/] = {0, 1, 2, 1};
    // Corel Word Perfect style
//  WP_POINTS: array[0..4] of ShortInt = (3, 2, 1, -1, -1);
		const signed char WP_POINTS[4/*# range 0..3*/] = {2, 1, 0, (signed char) -1};
		TP.Y += LH - 3;
		NewPoint = 0;
		if(FUnderlineStyle == usMicrosoftWord)
			NewY = TP.Y + MW_POINTS[NewPoint];
		else
			NewY = TP.Y + WP_POINTS[NewPoint];
		DrawPoint();
		MaxX = TP.X + ACanvas->TextWidth(CurrentWord);
		while(TP.X <= MaxX)
		{
			DrawPoint();
			++NewPoint;
			if(FUnderlineStyle == usMicrosoftWord)
			{
				if(NewPoint > 3 /*# High(MW_POINTS) */)
					NewPoint = 0;
			}
			else
			{
				if(NewPoint > 3 /*# High(WP_POINTS) */)
					NewPoint = 0;
			}
			DrawPoint();
			++TP.X;
			if(FUnderlineStyle == usMicrosoftWord)
				NewY = TP.Y + MW_POINTS[NewPoint];
			else
				NewY = TP.Y + WP_POINTS[NewPoint];
		}
	};
	String sToken;
	TSynHighlighterAttributes* Attri = nullptr;
	if(!ASSIGNED(FSynSpellCheck) || !ASSIGNED(FSynSpellCheck->Editor) || !(FSynSpellCheck->Options.Contains(sscoAutoSpellCheck)))
		return;
	Editor = ((TSynEdit*) FSynSpellCheck->Editor);
	LH = Editor->LineHeight;
	ACanvas->Font->Assign(Editor->Font);
/*
  if Editor.WordWrap then
  begin
    FirstLine := Editor.DisplayY;
    LastLine := Editor.DisplayY + Editor.LinesInWindow;
  end;
*/
	while(FirstLine <= LastLine)

    // Paint "Bad Words"
	{
		cx = 1;
		while(cx < Editor->Lines->Strings[FirstLine - 1].Length())
		{
			CurrentXY = BufferCoord(cx, FirstLine);
//      CurrentWord := TSynEditEx(Editor).GetWordAtRowColEx(CurrentXY,
//        TSynEditEx(Editor).IsIdentChar, True);
			CurrentWord = ((TSynEditEx*) Editor)->GetWordAtRowColEx(CurrentXY, FSynSpellCheck->SpellIsIdentChar, true);
			TP = Editor->RowColumnToPixels(Editor->BufferToDisplayPos(CurrentXY));
			if(TP.X > ACanvas->ClipRect.Right - ACanvas->ClipRect.Left)
				break;
			if(ASSIGNED(Editor->Highlighter) && !(ObjectIs(Editor->Highlighter, TSynURISyn*)))
			{
				if(Editor->GetHighlighterAttriAtRowCol(CurrentXY, sToken, Attri) == false)
					Attri = Editor->Highlighter->WhitespaceAttribute;
				if(ASSIGNED(Attri) && (FSynSpellCheck->FCheckAttribs->IndexOf(Attri->Name) != -1) && (CurrentWord != L""))
				{
					if(FSynSpellCheck->CheckWord(CurrentWord) == false)
						PaintUnderLine();
				}
			}
			else
			{
				if(FSynSpellCheck->CheckWord(CurrentWord) == false)
					PaintUnderLine();
			}
			cx += CurrentWord.Length();
			++cx;
		}
		++FirstLine;
	}
}

void __fastcall TDrawAutoSpellCheckPlugin::SetPenColor(const TColor Value)
{
	if(FPenColor != Value)
	{
		FPenColor = Value;
//    if Editor <> nil then                                                     //Fiala
//      Editor.Repaint;
	}
}

void __fastcall TDrawAutoSpellCheckPlugin::SetUnderlineStyle(TUnderlineStyle Value)
{
	if(FUnderlineStyle != Value)
	{
		FUnderlineStyle = Value;
		if(Editor != nullptr)
			try
			{
				Editor->Repaint();
			}
			catch(...)
			{
				;
			}
	}
}

/* TSynSpellCheck */

__fastcall TSynSpellCheck::TSynSpellCheck(TComponent* AOwner)
 : inherited(AOwner),
			FBusy(false),
			FModified(false),
			FOpenDictionary(false),
			FUseUserDictionary(false),
			FHashAlgorithm(haSoundEx),
			FMaxWordLength(0),
			FPenColor((TColor) 0),
			FCursor((TCursor) 0),
			FEditor(nullptr),
			FDrawAutoSpellCheck(nullptr),
			FHashLength((THashLength) 0),
			fEditors(nullptr),
			fPlugins(nullptr),
			FWordList(nullptr),
			FCheckAttribs(nullptr),
			FSkipList(nullptr),
			FUnderlineStyle(usCorelWordPerfect),
			FIntEnc(nullptr)
{
	const int CP_ASCII = 20127;
	int II = 0;
	int stop = 0;
	FPenColor = clRed;
	FBusy = false;
	FModified = false;
	FHashAlgorithm = haDiff;
	FHashLength = (THashLength) 4;
	FMaxWordLength = 0;
	FUnderlineStyle = usMicrosoftWord;
	FUseUserDictionary = true;
	FApostrophes = L"'`+";
  //////////////////////////////////////////////////////////////////////////////
  // Lists
  //////////////////////////////////////////////////////////////////////////////
	fEditors = new TList();
	fPlugins = new TList();
	FWordList = new TList();
	FSkipList = new TStringList();
	FSkipList->Duplicates = System::Types::dupIgnore;
	FCheckAttribs = new TStringList();
	/*# with FCheckAttribs do */
	{
		auto with0 = FCheckAttribs;
		with0->Add(L"Comment");
		with0->Add(L"Text");
		with0->Add(L"String");
		with0->Add(L"Documentation");
	}
	for(stop = 255, II = 1; II <= stop; II++)
	{
		FCacheArray[II][0] = 0;
		FCacheArray[II][1] = 0;
	}
	FIntEnc = TEncoding::GetEncoding(CP_ASCII);                                   //Fiala
}

__fastcall TSynSpellCheck::~TSynSpellCheck()
{
	int i = 0;
	int stop = 0;
	for(stop = 0, i = fEditors->Count - 1; i >= stop; i--)
	{
		RemoveEditor(((TCustomSynEdit*) fEditors->Items[i]));
	}
	CloseDictionary();
  //////////////////////////////////////////////////////////////////////////////
  // Free used memory
  //////////////////////////////////////////////////////////////////////////////
	delete FCheckAttribs;
	delete fEditors;
	delete fPlugins;
	delete FSkipList;
	delete FWordList;
	delete FIntEnc;
	// inherited;
}

String __fastcall TSynSpellCheck::Ansi2Ascii(const String SString)
{
	String result;
	TBytes BY;
	BY = TEncoding::Unicode->GetBytes(SString);
	BY = TEncoding::Convert(TEncoding::Unicode, FIntEnc, BY);
	result = FIntEnc->GetString(BY);
	return result;
}

bool __fastcall TSynSpellCheck::DictionaryExists(String Language, String Path/*# = ''*/)
{
	bool result = false;
	String STemp;
	if(Trim(Path) == L"") // Search in shared dictionary directory
		STemp = GetDictionaryDir();
	else
		STemp = Path; // Search in user specified directory
	result = FileExists(STemp + Language + L".dic");                              //Fiala
	return result;
}

String __fastcall TSynSpellCheck::GetNewestDictionary(String Language)
{
	String result;
	TSearchRec srDict = {};
	TStringList* tslTemp = nullptr;
	tslTemp = new TStringList();
	if(FindFirst(GetDictionaryDir() + Language + L".?-?-?.dic", faAnyFile, srDict) == 0)
	{
		if(Pos(L".user.", srDict.Name) == 0)
			tslTemp->Add(WideLowerCase(srDict.Name));
		while(FindNext(srDict) == 0)
		{
			if(Pos(L".user.", srDict.Name) == 0)
				tslTemp->Add(WideLowerCase(srDict.Name));
		}
	}
	/*# with tslTemp do */
	{
		auto with0 = tslTemp;
		if(with0->Count > 0)
		{
			with0->Sort();
			result = with0->Strings[with0->Count - 1];
		}
		delete with0;
	}
	Sysutils::FindClose(srDict);
	return result;
}

int __fastcall TSynSpellCheck::GetWordCount()
{
	int result = 0;
	result = FWordList->Count;
	return result;
}

// Returns word from word without diacritic

String __fastcall TSynSpellCheck::GetWordFromASCIIWord(String sWord)
{
	String result;
	int II = 0;
	int iJ = 0;
	int iLength = 0;
	String sLower;
	String STemp;

	auto CorrectCase = [&](const String AsWord, const String Word) -> String 
	{
		String result;
		String S1;
		String S2;
		String S3;
		String S4;
		int IX = 0;
		int stop = 0;
		S1 = WideUpperCase(AsWord);
		S2 = WideLowerCase(AsWord);
		S3 = WideUpperCase(Word);
		S4 = WideLowerCase(Word);
		result = Word;
		for(stop = (int) Word.Length(), IX = 1; IX <= stop; IX++)
		{
			if(S1[IX] == AsWord[IX])
				result[IX] = S3[IX];
			else
			{
				if(S2[IX] == AsWord[IX])
					result[IX] = S4[IX];
			}
		}
		return result;
	};
  // Are there any words at all starting with this letter?
	int stop = 0;
	sLower = AnsiLowerCase(sWord);
	if(FCacheArray[int(sLower[1])][1] == 0)
		return result;
	if(FindWord(sLower) !=  - 1)
		return result;
	iLength = sLower.Length();
	for(stop = FCacheArray[int(sLower[1])][1], II = FCacheArray[int(sLower[1])][0]; II <= stop; II++)
	{
		STemp = (*((PWordRec) FWordList->Items[II])).Word;
		if(iLength == STemp.Length())
      // Remove diacritic in dictionary and try find word
		{
			if(Ansi2Ascii(STemp) == sLower)
			{
				result = CorrectCase(sWord, STemp);
				return result;
			}
		}
	}

  // Not found in base, first char has diacritic, we must continue search
	for(stop = 254, II = 128; II <= stop; II++)
	{
    // Some optimalization
		if(FAnsi2Ascii[II - 128] == sLower[1])
		{
			int stop1 = 0;
			for(stop1 = FCacheArray[II][1], iJ = FCacheArray[II][0]; iJ <= stop1; iJ++)
			{
				STemp = (*((PWordRec) FWordList->Items[iJ])).Word;
				if(iLength == STemp.Length())
				{
					if(Ansi2Ascii(STemp) == sLower)
          // Remove diacritic in dictionary and try find word
					{
						result = CorrectCase(sWord, STemp);
						return result;
					}
				}
			}
		}
	}
	return result;
}

int __fastcall TSynSpellCheck::JHCMPDiffCount(const String Str1, const String Str2, TJHCMPLongintMatrix& Differences)
{
	int result = 0;
	__int64 I1 = 0;
	__int64 I2 = 0;
	int Length1 = 0;
	int Length2 = 0;
	__int64 stop = 0;
	Length1 = Str1.Length();
	Length2 = Str2.Length();
	for(stop = Length1, I1 = 1; I1 <= stop; I1++)
	{
		int stop1 = 0;
		for(stop1 = Length2, I2 = 1; I2 <= stop1; I2++)
		{
			if(Str1[I1] == Str2[I2])
				Differences[I1][I2] = Differences[I1 - 1][I2 - 1];
			else
				Differences[I1][I2] = JHCMPMin(Differences[I1 - 1][I2], Differences[I1][I2 - 1], Differences[I1 - 1][I2 - 1]) + 1;
		}
	}
	result = Differences[Length1][Length2];
	return result;
}

int __fastcall TSynSpellCheck::JHCMPDiffCount(const String Str1, const String Str2)
{
	int result = 0;
	TJHCMPLongintMatrix Differences;
	JHCMPInit(Str1.Length(), Str2.Length(), Differences);
	result = JHCMPDiffCount(Str1, Str2, Differences);
	return result;
}

void __fastcall TSynSpellCheck::JHCMPInit(int Max1, int Max2, TJHCMPLongintMatrix& Differences)
{
	JHCMPMatrix(Max1 + 1, Max2 + 1, Differences);
	JHCMPMatrixInit(Differences);
}

bool __fastcall TSynSpellCheck::JHCMPIsSimilar(const String Str1, const String Str2, int MaxDiffCount, TJHCMPLongintMatrix& Differences)
{
	bool result = false;
	result = (JHCMPDiffCount(Str1, Str2, Differences) <= MaxDiffCount);
	return result;
}

bool __fastcall TSynSpellCheck::JHCMPIsSimilar(const String Str1, const String Str2, int MaxDiffCount)
{
	bool result = false;
	TJHCMPLongintMatrix Differences;
	JHCMPInit(Str1.Length(), Str2.Length(), Differences);
	result = JHCMPIsSimilar(Str1, Str2, MaxDiffCount, Differences);
	return result;
}

void __fastcall TSynSpellCheck::AddDictWord(String Word)
{
	PWordRec AWordItem = nullptr;

  /* Return list position for insert new word */

	auto GetInsertPos = [&](const String Word) -> int 
	{
		int result = 0;
		int II = 0;
		result = 0;
    // If not any words at all starting with this letter, we find next word
		if(FCacheArray[int(Word[1])][1] == 0)
		{
			int stop = 0;
			for(stop = 255, II = int(Word[1]) + 1; II <= stop; II++)
			{
				if(FCacheArray[II][1] != 0)
				{
					result = (int) FCacheArray[II][0];
					break;
				}
			}
		}
		else
		{
			int stop = 0;
			for(stop = Succ(FCacheArray[int(Word[1])][1]), II = FCacheArray[int(Word[1])][0]; II <= stop; II++)
			{
				if((*((PWordRec) FWordList->Items[II])).Word > Word)
      // Words with this letter exists, we find right pos
				{
					result = II;
					break;
				}
			}
		}
		return result;
	};
	if(Trim(Word) == L"")
		return;
	Word = WideLowerCase(Word);
	if(FindWord(Word) ==  - 1)
	{
		AWordItem = new TWordRec;
		FMaxWordLength = Max(FMaxWordLength, (int) Word.Length());
		(*AWordItem).Word = Word;
		(*AWordItem).User = true;
		(*AWordItem).Value = ElfHash(Word);
    // Quickest way is insert one word than add and than sort whole list
		FWordList->Insert(GetInsertPos(AnsiLowerCase(Word)), AWordItem);
		CalculateCacheArray(); // Calculate cache array to speed up searches
		FModified = true;
		if(ASSIGNED(FOnAddWord))
			FOnAddWord(this, Word);
	}
}

void __fastcall TSynSpellCheck::AddDictWordList(TStringList* WordList)
{
	int II = 0;
	int stop = 0;
	for(stop = WordList->Count - 1, II = 0; II <= stop; II++)
	{
		AddDictWord(String(WordList->Strings[II]));
	}
}

int __fastcall TSynSpellCheck::AddEditor(TCustomSynEdit* AEditor)
{
	int result = 0;
	int i = 0;
	int II = 0;                                                               //Fiala
	TDrawAutoSpellCheckPlugin* Plugin = nullptr;
  // Adds an Editor and returns its index in the list
	result = -1;
	try
	{
		if(ASSIGNED(AEditor))                                                     //Fiala
		{
			int stop = 0;
			II = -1;
			for(stop = fEditors->Count - 1, i = 0; i <= stop; i++)
			{
				if(fEditors->Items[i] == AEditor)
				{
					II = i;
					break;
				}
			}
			if(II ==  - 1)
			{
				Plugin = new TDrawAutoSpellCheckPlugin(AEditor);
				/*# with Plugin do */
				{
					auto with0 = Plugin;
					with0->FSynSpellCheck = this;
					with0->PenColor = this->FPenColor;
					with0->UnderlineStyle = this->FUnderlineStyle;
				}
				II = fEditors->Add(AEditor);
				Sleep(10);
				fPlugins->Add(Plugin);
				result = II;
			}
			else
			result = II;
		}
    // there is problem in x64 editor (not in debug version)                    //Fiala
	}
	catch(...)
	{
		;
	}
	return result;
}

void __fastcall TSynSpellCheck::AddSkipWord(String Word)
{
	if(Trim(Word) != L"")
		FSkipList->Add(WideLowerCase(Word));
}

void __fastcall TSynSpellCheck::AddSkipWordList(TStringList* WordList)
{
	int II = 0;
	int stop = 0;
	for(stop = WordList->Count - 1, II = 0; II <= stop; II++)
	{
		AddSkipWord(String(WordList->Strings[II]));
	}
}

void __fastcall TSynSpellCheck::CalculateCacheArray()
{
	String sOld;
	String sNew;
	Char chOld = L'\0';
	Char chNew = L'\0';  //*
	int II = 0;
	int stop = 0;
	if(FWordList->Count == 0)
		return;
	sOld = AnsiLowerCase(((TWordRec*) &(*(TWordRec*) FWordList->Items[0]))->Word);
	chOld = sOld[1];
	chNew = chOld;
	FCacheArray[int(chOld)][0] = 0;
	FCacheArray[int(chOld)][1] = 0;
	for(stop = FWordList->Count - 1, II = 0; II <= stop; II++)
	{
		sNew = AnsiLowerCase(((TWordRec*) &(*(TWordRec*) FWordList->Items[II]))->Word);
		if(chOld != sNew[1])
		{
			chNew = sNew[1];
			FCacheArray[int(chOld)][1] = (unsigned int) (II - 1); // Last occurence of previous letter
			FCacheArray[int(chNew)][0] = (unsigned int) II; // First occurence of new letter
			chOld = chNew;
		}
	}
  // Last occurence of last letter
	FCacheArray[int(chNew)][1] = (unsigned int) (FWordList->Count - 1);
}

bool __fastcall TSynSpellCheck::CheckWord(String Word)
{
	bool result = false;
	int II = 0;
	Word = Trim(Word);
	if((Word == L"") || (fOptions.Contains(sscoIgnoreSingleChars)) && (Word.Length() == 1))
	{
		result = true;
		return result;
	}
  // It's quicker to check before checking word list
	if(fOptions.Contains(sscoIgnoreWordsWithNumbers))
	{
		int stop = 0;
		for(stop = (int) Word.Length(), II = 1; II <= stop; II++)
		{
			if(CharInSet(Word[II], Synspellcheck__4))
			{
				result = true;
				return result;
			}
		}

  //////////////////////////////////////////////////////////////////////////////
  // Check if word consists only of dashes or apostrophes. Quite often these
  // are used when dividing sections in ASCII text files.
  //////////////////////////////////////////////////////////////////////////////
	}
	if((TrimEx(Word, L'-') == L"") || (TrimEx(Word, L'\'') == L""))
	{
		result = true;
		return result;
	}
	if(fOptions.Contains(sscoTrimApostrophes))
		Word = TrimEx(Word, L'\''); // Trim apostrophes
  //////////////////////////////////////////////////////////////////////////////
  // Main Searching Routine
  //////////////////////////////////////////////////////////////////////////////
	result = (FindWord(AnsiLowerCase(Word)) >  - 1);
	if(!result && (FSkipList->IndexOf(AnsiLowerCase(Word)) !=  - 1))
		result = true;
	return result;
}

void __fastcall TSynSpellCheck::ClearDictWords()
{
	int II = 0;
	PWordRec AWordItem = nullptr;
	int stop = 0;
	for(stop = FWordList->Count - 1, II = 0; II <= stop; II++)
	{
		AWordItem = ((TWordRec*) FWordList->Items[II]);
		delete AWordItem;
	}
	FWordList->Clear();
}

void __fastcall TSynSpellCheck::ClearSkipWords()
{
	FSkipList->Clear();
}

void __fastcall TSynSpellCheck::CloseDictionary()
{
	int II = 0;
	int stop = 0;
	for(stop = 255, II = 0; II <= stop; II++)
	{
		FCacheArray[II][0] = 0;
		FCacheArray[II][1] = 0;
	}
	ClearDictWords();
	FSkipList->Clear();
	FOpenDictionary = false;
	if(ASSIGNED(FOnDictClose))
		FOnDictClose(this);
}

void __fastcall TSynSpellCheck::DeleteDictWord(String Word)
{
	delete ((PWordRec) FWordList->Items[FindWord(WideLowerCase(Word))]);
}

void __fastcall TSynSpellCheck::DeleteSkipWord(String Word)
{
	/*# with FSkipList do */
	{
		auto with0 = FSkipList;
		with0->Delete(with0->IndexOf(WideLowerCase(Word)));
	}
}

bool __fastcall TSynSpellCheck::IsDictWord(String Word)
{
	bool result = false;
	result = (FindWord(WideLowerCase(Word)) !=  - 1);
	return result;
}

bool __fastcall TSynSpellCheck::IsSkipWord(String Word)
{
	bool result = false;
	result = (FSkipList->IndexOf(WideLowerCase(Word)) !=  - 1);
	return result;
}

void __fastcall TSynSpellCheck::FixLists()
{
	int II = 0;
	int stop = 0;
	for(stop = FSkipList->Count - 1, II = 0; II <= stop; II++)
	{
		FSkipList->Strings[II] = WideLowerCase(String(FSkipList->Strings[II]));
	}
}

void __fastcall TSynSpellCheck::GetDictionaryList(TStringList*& tslList)
{
	TSearchRec srDics = {};

	auto AddDictionary = [&]() -> void 
	{
		String sLanguage;
		sLanguage = srDics.Name.SubString(1, Pos(L".", srDics.Name) - 1);
		if((tslList->IndexOf(sLanguage) ==  - 1) && (Pos(L".user.", srDics.Name) == 0))
			tslList->Add(sLanguage);
	};
	int II = 0;
	int stop = 0;
	if(FindFirst(GetDictionaryDir() + L"*.?-?-?.dic", faAnyFile, srDics) == 0)
	{
		AddDictionary();
		while(FindNext(srDics) == 0)
			AddDictionary();
	}
	Sysutils::FindClose(srDics);
	for(stop = tslList->Count - 1, II = 0; II <= stop; II++)
	{
		tslList->Strings[II] = WideUpperCase(String(tslList->Strings[II][1]))
						 + String(tslList->Strings[II]).SubString(2, Length(String(tslList->Strings[II])));
	}
	tslList->Sort();
}

int __fastcall TSynSpellCheck::GetSuggestions(String Word, TStringList* SuggestionList)
{
	int result = 0;
	int II = 0;
	int iLength = 0;
	String sHash;
	String sWord;
	result = 0;
	if(!(fOptions.Contains(sscoSuggestWords)))
		return result;
	if(ASSIGNED(SuggestionList))
    ////////////////////////////////////////////////////////////////////////////
    // Select algorithm
    ////////////////////////////////////////////////////////////////////////////
	{
		int stop = 0;
		iLength = (int) Word.Length();
		for(stop = FWordList->Count - 1, II = 0; II <= stop; II++)
		{
			if((((TWordRec*) &(*(TWordRec*) FWordList->Items[II]))->Hash == sHash) && (Abs((int) (iLength - ((TWordRec*) &(*(TWordRec*) FWordList->Items[II]))->Word.Length())) < 2))
			{
				sWord = ((TWordRec*) &(*(TWordRec*) FWordList->Items[II]))->Word;
				if(fOptions.Contains(sscoMaintainCase))
          //////////////////////////////////////////////////////////////////////
          // Maintain case for uppercase and capitalized words.
          //////////////////////////////////////////////////////////////////////
				{
					if(WideUpperCase(Word) == Word)
						sWord = WideUpperCase(sWord);
					else
					{
						if(WideUpperCase(String(sWord[1]))[1] == Word[1])
							sWord[1] = WideUpperCase(String(sWord[1]))[1];
					}
				}
				SuggestionList->Add(sWord);
			}
		}
		result = SuggestionList->Count;
	}
	return result;
}

int __fastcall TSynSpellCheck::JHCMPFindSimilar(const String Word, int MaxDiffCount, int MaxDiffLength, TStrings* Similar)
{
	int result = 0;
	Char chFirst = L'\0';
	int II = 0;
	int iJ = 0;
	int iLength = 0;
	String sLower;
	String sWord;
	TJHCMPLongintMatrix Differences;
	int stop = 0;
	result = 0;
	if(Trim(Word) == L"")
		return result;
	sLower = AnsiLowerCase(Word);
	chFirst = sLower[1];
	Similar->Clear();
	JHCMPInit((int) Word.Length(), FMaxWordLength, Differences);
	iLength = (int) Word.Length();
	for(stop = FCacheArray[int(chFirst)][1], II = FCacheArray[int(chFirst)][0]; II <= stop; II++)
	{
		sWord = (*((PWordRec) FWordList->Items[II])).Word;
		if(Abs((int) (iLength - sWord.Length())) > MaxDiffLength)
			continue;
		if(JHCMPIsSimilar(sLower, sWord, MaxDiffCount, Differences))
		{
			if(AnsiUpperCase(Word[1])[1] == Word[1])
				sWord[1] = AnsiUpperCase(String(sWord[1]))[1];
			Similar->Add(sWord);
		}
	}

  // Not found in base, first char has diacritic, we must continue search
	for(stop = 254, iJ = 128; iJ <= stop; iJ++)
	{
		if((FAnsi2Ascii[iJ - 128] == chFirst) && (FCacheArray[iJ][1] > 0))
		{
			int stop1 = 0;
			for(stop1 = FCacheArray[iJ][1], II = FCacheArray[iJ][0]; II <= stop1; II++)
			{
    // Some optimalizations
				sWord = (*((PWordRec) FWordList->Items[II])).Word;
				if(Abs((int) (iLength - sWord.Length())) > MaxDiffCount)
					continue;
				if(JHCMPIsSimilar(sLower, sWord, MaxDiffCount, Differences))
				{
					if(AnsiUpperCase(Word[1])[1] == Word[1])
						sWord[1] = AnsiUpperCase(String(sWord[1]))[1];
					Similar->Add(sWord);
				}
			}
		}
	}
	result = Similar->Count;
	return result;
}

void __fastcall TSynSpellCheck::LoadDictionary(String Language, String FileName/*# = ''*/)
{
	PWordRec AWordItem = nullptr;
	String sLine;
	String sName;
	d2c_system::TTextRec fOut = {};

	auto SaveToDriveC = [&]() -> void 
	{
		int i = 0;
		TStringList* sl = nullptr;
		int stop = 0;
		sl = new TStringList();
		for(stop = FWordList->Count - 1, i = 0; i <= stop; i++)
		{
			sl->Add((*((PWordRec) FWordList->Items[i])).Word);
		}
		sl->SaveToFile(L"C:\\Dic.txt");
		delete sl;
	};

	auto AddNewWord = [&](String sWord, bool IsUser) -> void 
	{
		AWordItem = new TWordRec;
		/*# with AWordItem^ do */
		{
			auto& with0 = (*AWordItem);
			with0.Word = sWord;
			with0.User = IsUser;
		}
		FWordList->Add(AWordItem);
	};
	FMaxWordLength = 0;
	FDictionary = ChangeFileExt(Language, L"");
	if(Trim(FileName) == L"")
		sName = GetDictionaryDir() + GetNewestDictionary(Language);
	else
		sName = FileName;
	AssignFile(fOut, sName);
	Reset(fOut);
	while(!Eof(fOut))
	{
		ReadLn(fOut, sLine);
		if(Trim(sLine) != L"")
		{
			FMaxWordLength = Max(FMaxWordLength, sLine.Length());
			AddNewWord(sLine, false);
		}
	}
	CloseFile(fOut);
	sName = ExtractFileName(sName);
	/*# with FLanguage do */
	{
		auto& with1 = FLanguage;
		with1.Name = (AnsiString) FDictionary;
		with1.Version = (AnsiString) sName.SubString(Pos(L".", sName) + 1, 5);
	}
	FUserFileName = (AnsiString) FLanguage.Name + L".user.dic";
  //////////////////////////////////////////////////////////////////////////////
  // Load user's dictionary if present
  //////////////////////////////////////////////////////////////////////////////
	FModified = false;
	if(FUseUserDictionary)
	{
		if(FUserDictPath == L"")
			FUserDictPath = GetUserDictionaryDir();
		sName = IncludeTrailingPathDelimiter(FUserDictPath) + FUserFileName;
		if(FileExists(sName))
		{
			AssignFile(fOut, sName);
			Reset(fOut);
			while(!Eof(fOut))
			{
				ReadLn(fOut, sLine);
				FMaxWordLength = Max(FMaxWordLength, sLine.Length());
				if(Trim(sLine) != L"")
					AddNewWord(sLine, true);
			}
			CloseFile(fOut);
			FModified = false;
		}
	}
	SortWordList(); // Sort the whole word list
	CalculateCacheArray(); // Calculate cache array to speed up searches
	FOpenDictionary = true;
}

int __fastcall TSynSpellCheck::FindWord(String sWord)
{
	int result = 0;
	int l = 0;
	int h = 0;
	int i = 0;
	int C = 0;
	String SW;
	result = -1;
	if(sWord == L"")
		return result;
  // Are there any words at all starting with this letter?
	SW = sWord;
	if(FCacheArray[int(SW[1])][1] == 0)
		return result;
	l = (int) FCacheArray[int(SW[1])][0];
	h = (int) FCacheArray[int(SW[1])][1];
	while(l <= h)
	{
		i = (l + h) >> 1;
    /* weak place, in some cases i was greater than word count */                 //Fiala
		if(i >= FWordList->Count)
		{
			result = -1;
			return result;
		}
    /* must be CompareStr not AnsiCompareStr, because dictionary is ASCII sorted */
		C = CompareStr((*((PWordRec) FWordList->Items[i])).Word, SW);
		if(C < 0)
			l = i + 1;
		else
		{
			h = i - 1;
			if(C == 0)
				result = i;
		}
	}
	return result;
}

void __fastcall TSynSpellCheck::LoadSkipList(String FileName)
{
	if(FileExists(FileName))
		FSkipList->LoadFromFile(FileName);
}

bool __fastcall TSynSpellCheck::RemoveEditor(TCustomSynEdit* AEditor)
{
	bool result = false;
	int i = 0;
	int II = 0;                                                               //Fiala
	result = false;
	try
	{
		if(ASSIGNED(AEditor))                                                     //Fiala
		{
			int stop = 0;
			II = -1;
			for(stop = fEditors->Count - 1, i = 0; i <= stop; i++)
			{
				if(((TCustomSynEdit*) fEditors->Items[i]) == AEditor)
				{
					II = i;
					break;
				}
			}
			if(II >  - 1)
			{
				if(FEditor == AEditor)
				{
					FEditor = nullptr;
					FDrawAutoSpellCheck = nullptr;
				}
				fEditors->Delete(II);
				fPlugins->Delete(II);
				result = true;
			}
		}
    // quiet exception for x64 compiler in 10.4.2                               //Fiala
	}
	catch(...)
	{
		;
	}
	return result;
}

void __fastcall TSynSpellCheck::SaveSkipList(String FileName)
{
	int II = 0;
	int stop = 0;
	for(stop = FSkipList->Count - 1, II = 0; II <= stop; II++)
	{
		if(Trim(String(FSkipList->Strings[II])) == L"")
			FSkipList->Delete(II);
	}
	FSkipList->SaveToFile(FileName);
}

void __fastcall TSynSpellCheck::SaveUserDictionary()
{
	int II = 0;
	d2c_system::TTextRec fIn = {};
	if(!FModified)
		return;
	if(!ForceDirectories(ExtractFileDir(FUserDictPath)))
		return;
	try
	{
		int stop = 0;
		AssignFile(fIn, IncludeTrailingPathDelimiter(FUserDictPath) + FUserFileName);
		Rewrite(fIn);
		for(stop = FWordList->Count - 1, II = 0; II <= stop; II++)
		{
			if(((TWordRec*) &(*(TWordRec*) FWordList->Items[II]))->User)
				WriteLn(fIn, ((TWordRec*) &(*(TWordRec*) FWordList->Items[II]))->Word);
		}
		CloseFile(fIn);
	}
	catch(...)
	{
		;
	}
	FModified = false;
}

void __fastcall TSynSpellCheck::SelectWordAtCursor()
{
	if(FEditor == nullptr)
		return;
	/*# with TSynEditEx(FEditor) do */
	{
		auto with0 = ((TSynEditEx*) FEditor);
		with0->BlockBegin = with0->SCWordStartEx(SpellIsWhiteChar);
		with0->BlockEnd = with0->SCWordEndEx(SpellIsWhiteChar);
	}
}

void __fastcall TSynSpellCheck::SetCheckAttribs(TStringList* const Value)
{
	FCheckAttribs->Assign((TPersistent*) Value);
}

void __fastcall TSynSpellCheck::SetEditor(TCustomSynEdit* const Value)
{
	int II = 0;
	if(Value != FEditor)
	{
		II = AddEditor(const_cast<TCustomSynEdit*>(Value));
		if(II >  - 1)
		{
			FEditor = ((TCustomSynEdit*) fEditors->Items[II]);
			FDrawAutoSpellCheck = ((TDrawAutoSpellCheckPlugin*) fPlugins->Items[II]);
			/*# with FDrawAutoSpellCheck do */
			{
				auto with0 = FDrawAutoSpellCheck;
				with0->FSynSpellCheck = this;
				with0->PenColor = this->FPenColor;
			}
		}
		else
		{
			FEditor = nullptr;
			FDrawAutoSpellCheck = nullptr;
		}
	}
}

void __fastcall TSynSpellCheck::SetHashAlgorithm(HashAlgorithms Value)
{
	FHashAlgorithm = haDiff;
}

void __fastcall TSynSpellCheck::SetHashLength(const THashLength Value)
{
	FHashLength = Value;
}

void __fastcall TSynSpellCheck::SetPenColor(const TColor Value)
{
	FPenColor = Value;
	if(FDrawAutoSpellCheck != nullptr)
		FDrawAutoSpellCheck->PenColor = Value;
}

void __fastcall TSynSpellCheck::SetSkipList(TStringList* Value)
{
	SkipList->Assign(Value);
}

void __fastcall TSynSpellCheck::SetUnderlineStyle(TUnderlineStyle Value)
{
	FUnderlineStyle = Value;
	if(FDrawAutoSpellCheck != nullptr)
		FDrawAutoSpellCheck->UnderlineStyle = Value;
}

void __fastcall TSynSpellCheck::SortWordList()
{
	FWordList->Sort(SortFunc);
}

void __fastcall TSynSpellCheck::SpellCheck()
{
	bool bAborted = false;
	bool bUndoEnabled = false;
	String sToken;
	String sWord;
	TBufferCoord pLastWord = {};
	TBufferCoord pNextWord = {};
	TStringList* tslSuggestions = nullptr;
	TSynHighlighterAttributes* Attri = nullptr;

	auto InternalCheckWord = [&](String Word) -> bool 
	{
		bool result = false;
		int iAction = 0;
		String sCorrectWord;
		result = true;
		if(!CheckWord(WideLowerCase(Word)))
		{
			if(fOptions.Contains(sscoHideCursor))
				FEditor->EndUpdate();
			/*# with FEditor do */
			{
				auto with0 = FEditor;
				with0->Update();
				with0->EnsureCursorPosVisible();
			}
			if(fOptions.Contains(sscoHourGlass))
				Screen->Cursor = FCursor;
			if(ASSIGNED(FOnCheckWord))
        // Get suggestions
			{
				if(fOptions.Contains(sscoSuggestWords))
				{
					if(FHashAlgorithm == haDiff)
						JHCMPFindSimilar(Word, 2, 2, tslSuggestions);
					else
						GetSuggestions(Word, tslSuggestions);
				}
				if(fOptions.Contains(sscoSelectWord))
					SelectWordAtCursor();
				FOnCheckWord(this, Word, tslSuggestions, sCorrectWord, iAction, true);
				tslSuggestions->Clear(); // Remove items to free some memory
				switch(iAction)
				{
					case ACTION_ABORT:
					{
						result = false;
						bAborted = true;
						/*# with FEditor do */
						{
							auto with1 = FEditor;
							with1->BlockBegin = with1->CaretXY;
							with1->BlockEnd = with1->BlockBegin;
						}
					}
					break;
					case ACTION_ADD:
					AddDictWord(sWord);
					break;
					case ACTION_CORRECT:
					{
						SelectWordAtCursor();
						((TSynEditEx*) FEditor)->SelText = sCorrectWord;
						if(ASSIGNED(FOnCorrectWord))
							FOnCorrectWord(this, sWord, sCorrectWord);
					}
					break;
					case ACTION_SKIPALL:
					{
						AddSkipWord(sWord);
						if(ASSIGNED(FOnSkipWord))
							FOnSkipWord(this, sWord, true);
					}
					break;
					case ACTION_SKIP:
					if(ASSIGNED(FOnSkipWord))
						FOnSkipWord(this, sWord, false);
					break;
					case ACTION_UNDO:
					{
						/*# with TSynEditEx(FEditor) do */
						{
							auto with2 = ((TSynEditEx*) FEditor);
							with2->Undo();
							with2->CaretXY = pLastWord;
							if(fOptions.Contains(sscoGoUp))
								with2->CaretXY = with2->SCNextWordPosEx(SpellIsIdentChar, SpellIsWhiteChar);
							else
								with2->CaretXY = with2->SCPrevWordPosEx(SpellIsIdentChar, SpellIsWhiteChar);
							bUndoEnabled = false;
						}
					}
					break;
					default:
					  ;
					break;
				}
			}
			if(fOptions.Contains(sscoHourGlass))
				Screen->Cursor = crHourGlass;
			if(fOptions.Contains(sscoHideCursor))
				FEditor->BeginUpdate();
		}
		return result;
	};
	bUndoEnabled = false;
  // If no dictionary if loaded and spell checking is requested and Exception
  // is thrown.
	if(!FOpenDictionary)
		throw new ENoDictionaryLoaded(SNoDictionaryLoaded);
	FBusy = true;
//  if Assigned(FOnStart) then
//    FOnStart(Self);
	bAborted = false;
	if(fOptions.Contains(sscoHourGlass))
	{
		FCursor = Screen->Cursor;
		Screen->Cursor = crHourGlass;
	}
	tslSuggestions = new TStringList();
	/*# with TSynEditEx(FEditor) do */
	{
		auto with3 = ((TSynEditEx*) FEditor);
		if(Trim(with3->Lines->Text) == L"")
		{
			Screen->Cursor = FCursor;
			FOnDone(this);
			FBusy = false;
			return;
		}
		if(!(fOptions.Contains(sscoStartFromCursor)))
			with3->CaretXY = BufferCoord(1, 1);
		if(fOptions.Contains(sscoHideCursor))
			with3->BeginUpdate();
		if(fOptions.Contains(sscoGoUp))
			pNextWord = with3->SCPrevWordPosEx(SpellIsIdentChar, SpellIsWhiteChar);
		else
			pNextWord = with3->SCNextWordPosEx(SpellIsIdentChar, SpellIsWhiteChar);
		pLastWord = pNextWord;
		while(pNextWord.Char > 0)
		{
			Attri = nullptr;
      //////////////////////////////////////////////////////////////////////////
      // Check if the word is the last word
      // Is cursor at end of text?
      //////////////////////////////////////////////////////////////////////////
			if(fOptions.Contains(sscoGoUp))
			{
				if((with3->SCPrevWordPosEx(SpellIsIdentChar, SpellIsWhiteChar).Char == with3->CaretX) && (with3->Lines->Count == with3->CaretY))
					break;
			}
			else
			{
				if((with3->SCNextWordPosEx(SpellIsIdentChar, SpellIsWhiteChar).Char == with3->CaretX) && (with3->Lines->Count == with3->CaretY))
					break;
			}
      //////////////////////////////////////////////////////////////////////////
      // Make sure we do not get any 'blank' words
      //////////////////////////////////////////////////////////////////////////
			while(Trim(with3->GetWordAtRowColEx(with3->CaretXY, SpellIsIdentChar, true)) == L"")

        /* Just move to next word */
			{
				if(fOptions.Contains(sscoGoUp))
					pNextWord = with3->SCPrevWordPosEx(SpellIsIdentChar, SpellIsWhiteChar);
				else
					pNextWord = with3->SCNextWordPosEx(SpellIsIdentChar, SpellIsWhiteChar);
				with3->CaretXY = pNextWord;
        /* If it the last word then exit loop */
				if(pNextWord.Char == 0)
					break;
			}
			if(pNextWord.Char == 0)
				break;
			sWord = with3->GetWordAtRowColEx(with3->CaretXY, SpellIsIdentChar, true);
      //////////////////////////////////////////////////////////////////////////
      // Check if the word is in the dictionary
      //////////////////////////////////////////////////////////////////////////
			if((with3->Highlighter == nullptr) || (ObjectIs(with3->Highlighter, TSynURISyn*)))
			{
				if(InternalCheckWord(sWord) == false)
					break;
			}
			else
			{
				if(with3->GetHighlighterAttriAtRowCol(with3->CaretXY, sToken, Attri) == false)
					Attri = with3->Highlighter->WhitespaceAttribute;
				if(ASSIGNED(Attri) && (FCheckAttribs->IndexOf(Attri->Name) !=  - 1) && (!InternalCheckWord(sWord)))
					break;
			}
      //////////////////////////////////////////////////////////////////////////
      // Prepare next word position
      //////////////////////////////////////////////////////////////////////////
			if(fOptions.Contains(sscoGoUp))
				pNextWord = with3->SCPrevWordPosEx(SpellIsIdentChar, SpellIsWhiteChar);
			else
				pNextWord = with3->SCNextWordPosEx(SpellIsIdentChar, SpellIsWhiteChar);
			with3->CaretXY = pNextWord;
		}
		if(fOptions.Contains(sscoHideCursor))
			with3->EndUpdate();
	}
	delete tslSuggestions;
	if(fOptions.Contains(sscoHourGlass))
		Screen->Cursor = FCursor;
  //////////////////////////////////////////////////////////////////////////////
  // Remove last word selection
  //////////////////////////////////////////////////////////////////////////////
	/*# with FEditor do */
	{
		auto with4 = FEditor;
		with4->BlockBegin = with4->CaretXY;
		with4->BlockEnd = with4->BlockBegin;
	}
	if(bAborted)
	{
		if(ASSIGNED(FOnAbort))
			FOnAbort(this);
	}
	else
	{
		if(ASSIGNED(FOnDone))
			FOnDone(this);
	}
	FBusy = false;
}

void __fastcall TSynSpellCheck::AddDiacritic(TProgressBar* Progress)
{
	String sToken;
	String sWord;
	TBufferCoord pNextWord = {};
	TSynHighlighterAttributes* Attri = nullptr;
	TBufferCoord blBeg = {};
	TBufferCoord blEnd = {};

	auto InternalCheckWord = [&](String Word) -> void 
	{
		String sCorrectWord;
		sCorrectWord = GetWordFromASCIIWord(Word);
		if(sCorrectWord != L"")
		{
			SelectWordAtCursor();
			((TSynEditEx*) FEditor)->SelText = sCorrectWord;
		}
	};
  // If no dictionary if loaded and spell checking is requested and Exception is
  // thrown.
	if(!FOpenDictionary)
		throw new ENoDictionaryLoaded(SNoDictionaryLoaded);
	if(FEditor == nullptr)
		return;
	if(FEditor->SelAvail)
	{
		if((FEditor->BlockBegin.Line > FEditor->BlockEnd.Line) || ((FEditor->BlockBegin.Line == FEditor->BlockEnd.Line) && (FEditor->BlockBegin.Char > FEditor->BlockEnd.Char)))
		{
			blEnd = FEditor->BlockBegin;
			blBeg = FEditor->BlockEnd;
		}
		else
		{
			blBeg = FEditor->BlockBegin;
			blEnd = FEditor->BlockEnd;
		}
	}
	else
	{
		blBeg = BufferCoord(1, 1);
		blEnd = BufferCoord(0, 0);
	}
	FBusy = true;
	/*# with TSynEditEx(FEditor) do */
	{
		auto with0 = ((TSynEditEx*) FEditor);
		if(Trim(with0->Lines->Text) == L"")
		{
			FBusy = false;
			return;
		}
		with0->CaretXY = blBeg;
		if(Progress != nullptr)
		{
			Progress->Min = 0;
			Progress->Max = with0->Lines->Count;
		}
		pNextWord = with0->SCNextWordPosEx(SpellIsIdentChar, SpellIsWhiteChar);
		while(pNextWord.Char > 0)
		{
			Attri = nullptr;
      //////////////////////////////////////////////////////////////////////////
      // Check if the word is the last word
      // Is cursor at end of text?
      //////////////////////////////////////////////////////////////////////////
			if((with0->SCNextWordPosEx(SpellIsIdentChar, SpellIsWhiteChar).Char == with0->CaretX) && (with0->Lines->Count == with0->CaretY))
				break;
      //////////////////////////////////////////////////////////////////////////
      // Make sure we do not get any 'blank' words
      //////////////////////////////////////////////////////////////////////////
			while(Trim(with0->GetWordAtRowColEx(with0->CaretXY, SpellIsIdentChar, true)) == L"")
			{
				pNextWord = with0->SCNextWordPosEx(SpellIsIdentChar, SpellIsWhiteChar);
				with0->CaretXY = pNextWord;
        /* If it the last word then exit loop */
				if(pNextWord.Char == 0)
					break;
			}
			if(pNextWord.Char == 0)
				continue;
			sWord = with0->GetWordAtRowColEx(with0->CaretXY, SpellIsIdentChar, true);
      //////////////////////////////////////////////////////////////////////////
      // Check if the word is in the dictionary
      //////////////////////////////////////////////////////////////////////////
			if((with0->Highlighter == nullptr) || (ObjectIs(with0->Highlighter, TSynURISyn*)))
				InternalCheckWord(sWord);
			else
			{
				if(with0->GetHighlighterAttriAtRowCol(with0->CaretXY, sToken, Attri) == false)
					Attri = with0->Highlighter->WhitespaceAttribute;
				if(ASSIGNED(Attri) && (FCheckAttribs->IndexOf(Attri->Name) !=  - 1))
					InternalCheckWord(sWord);
			}
      //////////////////////////////////////////////////////////////////////////
      // Prepare next word position
      //////////////////////////////////////////////////////////////////////////
			pNextWord = with0->SCNextWordPosEx(SpellIsIdentChar, SpellIsWhiteChar);

      /* only work on selection */
			if((blEnd.Line > 0) && ((pNextWord.Line > blEnd.Line) || (blEnd.Line == pNextWord.Line) && (pNextWord.Char > blEnd.Char)))
				break;
			with0->CaretXY = pNextWord;
			if(Progress != nullptr)
			{
				if(Progress->Position != with0->CaretY)
				{
					Progress->Position = with0->CaretY;
					Progress->Update();
				}
			}
		}
	}
	FBusy = false;
}

bool __fastcall TSynSpellCheck::SpellIsIdentChar(WideChar AChar)
{
	bool result = false;
	result = IsCharAlphaNumeric(AChar) || (Pos(AChar, FApostrophes) > 0) || (AChar == L'-');
	return result;
}

bool __fastcall TSynSpellCheck::SpellIsWhiteChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
		 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
		 case 30: case 31: case 32:
		result = true;
		break;
		default:
		result = !SpellIsIdentChar(AChar);
		break;
	}
	return result;
}

/* TSynEditEx */

String __fastcall TSynEditEx::GetWordAtRowColEx(const TBufferCoord& cXY, TCategoryMethod SpellIsIdentChar, bool OverrideHighlighterChars)
{
	TBufferCoord XY = cXY;
	String result;
	String Line;
	int Len = 0;
	int Stop = 0;
	result = L"";
	if((XY.Line >= 1) && (XY.Line <= Lines->Count))
	{
		Line = Lines->Strings[XY.Line - 1];
		Len = Line.Length();
		if((XY.Char >= 1) && (XY.Char <= Len + 1))
		{
			Stop = XY.Char;
			while((Stop <= Len) && SpellIsIdentChar(Line[Stop]))
				++Stop;
			while((XY.Char > 1) && SpellIsIdentChar(Line[XY.Char - 1]))
				--XY.Char;
			if(Stop > XY.Char)
				result = Line.SubString(XY.Char, Stop - XY.Char);
		}
	}
	return result;
}
function<void ()> CheckOnNextLine;


TBufferCoord __fastcall TSynEditEx::SCNextWordPosEx(TCategoryMethod SpellIsIdentChar, TCategoryMethod SpellIsWhiteChar)
{
	TBufferCoord result = {};
	int cx = 0;
	int cy = 0;
	int LineLen = 0;
	String Line;

	CheckOnNextLine = [&]() -> void 
	{

    // find first IdentChar or multibyte char in the next line
		if(cy < Lines->Count)
		{
			Line = Lines->Strings[cy];
			++cy;
			cx = StrScanForCharInCategory(Line, 1, SpellIsIdentChar);
			if(cx == 0)
				CheckOnNextLine();
		}
	};
	cx = CaretX;
	cy = CaretY;
  // valid line?
	if((cy >= 1) && (cy <= Lines->Count))
	{
		Line = Lines->Strings[cy - 1];
		LineLen = Line.Length();
		if(cx >= LineLen)
		{
			CheckOnNextLine();
		}
		else

      // find next "whitespace" if current char is an IdentChar
		{
			if(SpellIsIdentChar(Line[cx]))
				cx = StrScanForCharInCategory(Line, cx, SpellIsWhiteChar);

      // if "whitespace" found, find the next IdentChar
			if((cx > 0) && (cx < LineLen))
			{
				cx = StrScanForCharInCategory(Line, cx, SpellIsIdentChar);
        // if one of those failed just position at the end of the line
				if(cx == 0)
					CheckOnNextLine();
			}
			else
			CheckOnNextLine();
		}
	}
	result = BufferCoord(cx, cy);
	return result;
}
function<void ()> CheckForIdentChar;


TBufferCoord __fastcall TSynEditEx::SCPrevWordPosEx(TCategoryMethod SpellIsIdentChar, TCategoryMethod SpellIsWhiteChar)
{
	TBufferCoord result = {};
	int cx = 0;
	int cy = 0;
	String Line;

	CheckForIdentChar = [&]() -> void 
	{
		if(cx <= 1)
			return;
    // If previous char is a "whitespace" search for the last IdentChar
		if(SpellIsWhiteChar(Line[cx - 1]))
			cx = StrRScanForCharInCategory(Line, cx - 1, SpellIsIdentChar);
		if(cx > 0)
      // Search for the first IdentChar of this "word"
			cx = StrRScanForCharInCategory(Line, cx - 1, SpellIsWhiteChar) + 1;
		if(cx == 0)
      // Same as CheckOnPrevLine, but we can't have a circular reference
      //  find last cIdentChar in the previous line
		{
			if(cy > 1)
			{
				--cy;
				Line = Lines->Strings[cy - 1];
				while((cy > 1) && (Line == L""))
				{
					--cy;
					Line = Lines->Strings[cy - 1];
				}
				if(Line == L"")
					cx = 1;
				else
				{
					cx = Line.Length() + 1;
					CheckForIdentChar();
				}
			}
			else
			cx = 1;
		}
	};

	auto CheckOnPrevLine = [&]() -> void 
	{

    // Find last IdentChar in the previous line
		if(cy > 1)
		{
			--cy;
			Line = Lines->Strings[cy - 1];
			cx = Line.Length() + 1;
			CheckForIdentChar();
		}
		else
		cx = 1;
	};
	cx = CaretX;
	cy = CaretY;
  // Valid line?
	if((cy >= 1) && (cy <= Lines->Count))
	{
		Line = Lines->Strings[cy - 1];
		cx = Min(cx, Line.Length() + 1);
		if(cx <= 1)
			CheckOnPrevLine();
		else
			CheckForIdentChar();
	}
	result = BufferCoord(cx, cy);
	return result;
}

TBufferCoord __fastcall TSynEditEx::SCWordEndEx(TCategoryMethod SpellIsWhiteChar)
{
	TBufferCoord result = {};
	int cx = 0;
	int cy = 0;
	String Line;
	cx = CaretX;
	cy = CaretY;
  // Valid line?
	if((cy >= 1) && (cy <= Lines->Count))
	{
		Line = Lines->Strings[cy - 1];
		cx = StrScanForCharInCategory(Line, cx, SpellIsWhiteChar);
    // If no "whitespace" is found just position at the end of the line
		if(cx == 0)
			cx = Line.Length() + 1;
	}
	result = BufferCoord(cx, cy);
	return result;
}

TBufferCoord __fastcall TSynEditEx::SCWordStartEx(TCategoryMethod SpellIsWhiteChar)
{
	TBufferCoord result = {};
	int cx = 0;
	int cy = 0;
	String Line;
	cx = CaretX;
	cy = CaretY;
  // Valid line?
	if((cy >= 1) && (cy <= Lines->Count))
	{
		Line = Lines->Strings[cy - 1];
		cx = Min(cx, Line.Length() + 1);
		if(cx > 1)
		{
			if(!SpellIsWhiteChar(Line[cx - 1])) // Only find previous char, if not already on start of line
      // If previous char isn't a "whitespace" search for the last IdentChar
				cx = StrRScanForCharInCategory(Line, cx - 1, SpellIsWhiteChar) + 1;
		}
	}
	result = BufferCoord(cx, cy);
	return result;
}


}  // namespace SynSpellCheck

