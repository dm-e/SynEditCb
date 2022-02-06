#ifndef SynSpellCheckH
#define SynSpellCheckH

#include <System.hpp>
#include "d2c_system.h"

#include <System.Math.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Winapi.Windows.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <System.StrUtils.hpp>
#include <System.SysUtils.hpp>
#include "SynEdit.h"
#include "SynEditTypes.h"
#include <Vcl.ComCtrls.hpp>
#include "d2c_systypes.h"
#include "SynEditDelphiInstances.hpp"

namespace Synspellcheck
{

////////////////////////////////////////////////////////////////////////////////
// TSynSpellCheck 1.30
//
// Copyright (c) 2002 Jacob Dybala a.k.a. "m3Rlin". All rights reserved.
//
// E-Mail: jacobdybala@synspellcheck.prv.pl
// WWW   : http://www.synspellcheck.prv.pl/ SynSpellCheck Home
//         http://www.delphifaq.net/        Merlin's Delphi Forge
//
// Elf hash algorithm
//   Copyright (c) 1998-2002 Scalabium
//   <http://www.scalabium.com/faq/dct0136.htm>
// SoundEx algorithm
//   Copyright (c) 1995-2001 Borland Software Corporation
// Metaphone Phonetic Hash Algorithm
//   Copyright (c) Tom White <wcstom@yahoo.com>
// Word differences algorithm JHCMP...
//   Copyright (c) Josef Hampl
//
// Created : Jan-10-2002
// Modified: Aug-31-2002
////////////////////////////////////////////////////////////////////////////////
// All dictionaries are located in the 'Program Files\Common\SynSpell' folder.
// This is to limit the number of copies of the same dictionary on a single
// computer to one file.
//
// Dictionaries are flat text files with a single word in each line. All words
// MUST be lowercase. The dictionaries are case insensitive.
////////////////////////////////////////////////////////////////////////////////
// Changes:
//
// 1.30 (Contributed in large by Jan Fiala)
//   * Many, many minor adjustments, optimizations.
//   * Rewritten SetApostrophes().
//   + New word suggestion algorithm: haDiff. Finds words based on differences.
//     haSoundex and haMetaphone *may* be removed in upcoming versions.
//   + New action added: ACTION_UNDO.
//   + New function: GetDictionaryDir(). This allows users to specify their own
//     paths.
//   + Dutch (compiled by Arno Verhoeven) dictionary added.
//
// 1.24 Released privately to certain users.
//   * Bug Fix: PChar and string incompatiblity. Fixed.
//
// 1.23 Released privately to certain users.
//   * Minor code adjustments.
//   + New dictionaries: Norwegian and Spanish.
//
// 1.22
//   * Bug Fix: The Apostrophes property did not allow changing. Fixed.
//     Submitted by R.K. Wittye.
//   * Bug Fix: ClearDictWords did not properly dispose of words creating a
//     rather large memory leak. Fixed. Submitted by Ascher Stefan.
//   * English and Polish dictionaries updated.
//   + Added Value field to TWordRec record. Each word is assigned an Elf value
//     and is checked by it. Major speed optimization. Suggested by Jan Fiala
//     (CRC32).
//
// 1.21
//   * Bug Fix: %ProgramFilesDir%\Common Files was read instead of %CommonFilesDir%.
//     This created problems on non-English versions of Windows. The directory
//     was not found. Fixed.
//   * English and Polish dictionaries updated.
//
// 1.20
//   * FindWord() routine rewritten to make use of cache array. Other functions
//     have only been slightly modified yet no functions have been broken.
//   * LoadDictionary() routine now converts all words to lowercase.
//   * LoadSkipList() does not add the words one-by-one any more. They are
//     assigned in whole.
//   * FSkipList is now cleared when a dictionary is closed.
//   * SaveSkipList() now removes all empty lines before saving to file.
//   + Added cache array to speed up word checks.
//   + ENoDictionaryLoaded is now thrown when no dictionary has been loaded.
//
// 1.19
//   * Bug Fix: Word underlining would also draw on gutter when the word was
//     partially scrolled under it. Fixed.
//   * SoundexLength property converted to HashLength.
//   * PaintUnderLine() code modified to directly color pixels instead of drawing
//     lines.
//   * Dictionary updates: English (1.1.2), Polish (1.1.1). The Polish word list
//     has been *significantly* reduced due to the fact that this word list is
//     being started all over to include words with non-latin characters.
//   + New option: sscoTrimApostrophes.
//   + New properties: Busy and UnderlineStyle (to mimic Corel Wordperfect
//     auto spell checking).
//   + MetaPhone algorithm has been finally implemented. In beta stage (works,
//     but slow on big lists).
//   + AddDictSkipList(), AddDictWordList() routines added.
//   + New dictionaries: German (by Ascher Stefan) and Russian.
//
// 1.18
//   * Bug Fix: OnSkipWord event did not return proper ASkipAll value. Fixed.
//   * Bug Fix: GetDictionaryList() included all copies of dictionaries for a
//     specific language instead of newest. Fixed.
//   * DupeString() has been corrected with proper compiler conditional.
//   * Minor code changes to always pass lowercase words to FindWord().
//   * English dictionary updated to version 1.1.0.
//   * Updated component demo.
//   + New option: sscoMaintainCase. Idea suggested by Jeff Rafter.
//   + New event: OnAddWord.
//   + Added support for words with apostrophes. Idea by Stefan van As.
//   + GetDictionaryList() now returns a sorted list.
//
// 1.17
//   * SelectWordAtCursor() made public.
//   + Added support for localized languages and numbers.
//
// 1.16
//   * Bug Fix: Compiler conditional around SoundEx() routines was broken.
//     Fixed.
//   * Bug Fix: sscoSelectWord did not work when set to False. Fixed.
//   + SelectWordAtCursor() routine added. Contributed by Stefan van As.
//
// 1.15
//   * Bug Fix: PenColor property did not work. Fixed by Jeff Corbets.
//   * Bug Fix: OnAbort event was not called when spell checking was aborted.
//     Fixed.
//   * TSoundEx class has been removed in favor of Borland implementation of
//     SoundEx() function.
//   * Minor code modifications.
//   + Added support for dashed words.
//   + New option: sscoGoUp.
//   + New property: SoundExLength.
//
// 1.14
//   * Bug Fix: If the editor had no text and sscoHourGlass was set the cursor
//     did not revert to it's previous value. Fixed by Jeff Corbets.
//
// 1.13
//   * Bug Fix: When empty lines in base dictionary and user dictionary were
//     added to word list and raised AV when attempting to calculate word hash.
//     Fixed.
//
// 1.12
//   * Bug Fix: GetSuggestions did not properly support words with uppercase
//     characters. Fixed. Found by Jeff Rafter.
//   + Added Metaphon algorithm for word hashes. Not working, just skeleton for
//     now.
//
// 1.11
//   + Added support for multiple editors: AddEditor() and RemoveEditor().
//
// 1.10 (code contributed by Ricardo Cardona)
//   * Bug Fix: When not highlighter was selected and sscoAutoSpellCheck was set
//     in Options the component generated an AV. Fixed.
//   * New property: CheckAttribs.
//   * Improved code for underlining unknown words.
//
// 1.09
//   * Bug Fix: FWordList did not free memory when the component was destroyed.
//     It just cleared the word and hash lists. Fixed.
//
// 1.08
//   * Bug Fix: FindWord() function was case sensitive. Fix contributed by
//     Gerald Nunn.
//   + New events: OnDictClose and OnDictLoad.
//   + New options: sscoAutoSpellCheck (contributed by Ricardo Cardona),
//     sscoIgnoreWordsWithNumbers and sscoIgnoreSingleChars.
//   + New property: PenColor.
//   + Added support for Java documentation.
//
// 1.07
//   * Bug Fix: When spell checking the last word under certain conditions the
//     component would enter an infinite loop. Fixed.
//
// 1.06
//   * Bug Fix: When correcting words in OnCheckWord event the word would not be
//     replaced but added to the beginning of the old one. Fixed.
//   + New dictionary: Danish.
//   + New property: OpenDictionary.
//   + New option: sscoSelectWord.
//
// 1.05
//   + New events: OnCorrectWord and OnSkipWord.
//   + Demo added.
//
// 1.04
//   * Bug Fix: Would not compile under Delphi 6 due to duplicate resource
//     error. Fixed.
//   * GetDictionaryList() now searches for file that match the correct naming
//     scheme - name.major-minor-revision.dic, where major, minor and revision
//     are single characters.
//   + New dictionaries: Italian, Latin, Japanese, Polish, Spanish (Thanks to
//     Ricardo Cardona), and Turkish.
//   + New routines: CloseDictionary(), GetWordCount().
//   + New property: Dictionary.
//   - Removed {$IFDEF SYN_WIN32} directive from GetDictionaryList(). The
//     routines are available under Kylix also.
//   - Removed Version parameter from LoadDictionary.
//
// 1.03
//   + Added /usr/local/SynSpell dir under Linux as the default dictionary
//     directory.
//   + Added Language property.
//   + %ProgramFiles%\Common Files\SynSpell is now dynamically read from system
//     Registry.
//   + Added user dictionary.
//   + Added GetDictionaryList().
//
// 1.02
//   * Bug Fix: When the word list was cleared, the SoundEx list still hogged up
//     the memory =) Fixed.
//   * Bug Fix: When a word was deleted from the dictionary, the SoundEx hash
//     remained undeleted. Therefor, after deleting a word the whole SoundEx
//     hash list after the deleted word was wrong (1 up).
//   * Bug Fix: Suggestions were not passed in ASuggestions in OnCheckWord
//     event. Fixed.
//   * Bug Fix: DeleteSkipWord() fixed to delete form skip word list, not word
//     list ;-)
//   * Bug Fix: editor did not update when searching for words, the screen
//     would "blur". Fixed.
//   * GetSuggestions() changed from procedure to function to return number or
//     words in list.
//   * FWordList is now type of TList instead of TStringList.
//   + If no AAction is specified in the OnCheckWord event, then ACTION_SKIP is
//     default.
//   + Now double words are automatically ignored in FWordList.
//   + Added sscoSuggestWords option.
//   + Added OnAbort event.
//   + Added support for HTML Text.
//   - Removed unsupported options from Options property.
//
// 1.01
//   + Added Options property (support for selecting unknown words in editor,
//     spell checking from cursor, and spell checking only selection, hour glass
//     cursor during spell check, removing cursor visibility during spell
//     check).
//   + Added word suggestion list.
////////////////////////////////////////////////////////////////////////////////

/*-----------------------------------------------------------------
  Usage:

  UserDirectory := 'some paths in user profile';
  LoadDictionary('some DIC file');
  Editor := Synedit1;
  // for words underline like words
  Options := Options + [sscoAutoSpellCheck];

  or you can start SpellCheck with dialog, in this case handle events
  In case you add some words to user dictionary, you can save it

  if SynSpellCheck.Modified then
    SaveUserDictionary;
-----------------------------------------------------------------*/  //don't use Metaphone method to find near word //Fiala
class DELPHICLASS TSynSpellCheck;
typedef int /*1..16*/ THashLength;
typedef int /*1..8*/ TSoundexLength;
typedef DynamicArray<int> TJHCMPLongintArray;
typedef DynamicArray<TJHCMPLongintArray> TJHCMPLongintMatrix;

struct TLanguageRec
{
	SmallString<50> Name;
	SmallString<50> Version;
};
struct TWordRec;
typedef TWordRec* PWordRec;

struct TWordRec
{
	String Word;
	String Hash;  //*
	int Value;
	bool User;
};

class TSynEditEx : public Synedit::TCustomSynEdit
{
public:
	typedef Synedit::TCustomSynEdit inherited;	
	#include "SynSpellCheck_friends.inc"
	String __fastcall GetWordAtRowColEx(const TBufferCoord& XY, Synedittypes::TCategoryMethod SpellIsIdentChar, bool OverrideHighlighterChars);
	TBufferCoord __fastcall SCNextWordPosEx(Synedittypes::TCategoryMethod SpellIsIdentChar, Synedittypes::TCategoryMethod SpellIsWhiteChar);
	TBufferCoord __fastcall SCPrevWordPosEx(Synedittypes::TCategoryMethod SpellIsIdentChar, Synedittypes::TCategoryMethod SpellIsWhiteChar);
	TBufferCoord __fastcall SCWordEndEx(Synedittypes::TCategoryMethod SpellIsWhiteChar);
	TBufferCoord __fastcall SCWordStartEx(Synedittypes::TCategoryMethod SpellIsWhiteChar);
	__fastcall TSynEditEx(System::Classes::TComponent* AOwner);
	__fastcall TSynEditEx(HWND ParentWindow);
};
enum TUnderlineStyle {usCorelWordPerfect,
                      usMicrosoftWord };

class TDrawAutoSpellCheckPlugin : public Synedit::TSynEditPlugin
{
	#include "SynSpellCheck_friends.inc"
public:
	typedef Synedit::TSynEditPlugin inherited;	
private:
	TColor FPenColor;
	TUnderlineStyle FUnderlineStyle;
    /* Procedures */
	void __fastcall SetPenColor(const TColor Value);
	void __fastcall SetUnderlineStyle(TUnderlineStyle Value);
protected:
	TSynSpellCheck* FSynSpellCheck;
    /* Procedures */
	virtual void __fastcall AfterPaint(Vcl::Graphics::TCanvas* ACanvas, const TRect& AClip, int FirstLine, int LastLine);
public:
	__fastcall TDrawAutoSpellCheckPlugin(Synedit::TCustomSynEdit* AOwner);
    /* Properties */
	__property TColor PenColor = { read = FPenColor, write = SetPenColor, default = clRed };
	__property TUnderlineStyle UnderlineStyle = { read = FUnderlineStyle, write = SetUnderlineStyle, default = /*# usMicrosoftWord */ 1 };
	__fastcall TDrawAutoSpellCheckPlugin(Synedit::TCustomSynEdit* AOwner, Synedit::TPlugInHandlers AHandlers);
	__fastcall TDrawAutoSpellCheckPlugin();
};

  /* Procedure types */
typedef void __fastcall (__closure *TOnAddWord) (TObject*, String);
typedef void __fastcall (__closure *TOnCheckWord) (TObject*, String, System::Classes::TStringList*, String&, int&, bool/*# = true*/);
typedef void __fastcall (__closure *TOnCorrectWord) (TObject*, String, String);

  /* Sets */
typedef void __fastcall (__closure *TOnSkipWord) (TObject*, String, bool);
enum HashAlgorithms {haSoundEx,
                     haMetaphone,
                     haDiff };
enum SynSpellCheckOptions {sscoAutoSpellCheck,
                           sscoGoUp,
                           sscoHideCursor,
                           sscoHourGlass,
                           sscoIgnoreSingleChars,
                           sscoIgnoreWordsWithNumbers,
                           sscoMaintainCase,
                           sscoSelectWord,
                           sscoStartFromCursor,
                           sscoSuggestWords,
                           sscoTrimApostrophes };
typedef System::Set<SynSpellCheckOptions, sscoAutoSpellCheck, sscoTrimApostrophes> TSynSpellCheckOptions;

class TSynSpellCheck : public System::Classes::TComponent
{
private:
	Char FAnsi2Ascii[128/*# range 128..255*/];  //*
	unsigned int FCacheArray[65536/*# range 0..65535*/][2/*# range 0..1*/];
//    FIdentChars: set of Char;
	bool FBusy;
	bool FModified;
	bool FOpenDictionary;
	bool FUseUserDictionary;
	HashAlgorithms FHashAlgorithm;
	int FMaxWordLength;
	String FApostrophes;
	String FDictPath;
	String FUserFileName;
	String FUserDictPath;
	String FDictionary;
	TColor FPenColor;
	TCursor FCursor;
	Synedit::TCustomSynEdit* FEditor;
	TDrawAutoSpellCheckPlugin* FDrawAutoSpellCheck;
	THashLength FHashLength;
	TOnAddWord FOnAddWord;
	TLanguageRec FLanguage;
	System::Classes::TList* fEditors;
	System::Classes::TList* fPlugins;
	System::Classes::TList* FWordList;
	System::Classes::TNotifyEvent FOnAbort;
	System::Classes::TNotifyEvent FOnDictClose;
	System::Classes::TNotifyEvent FOnDictLoad;
	System::Classes::TNotifyEvent FOnDone;
	System::Classes::TNotifyEvent FOnStart;
	TOnCheckWord FOnCheckWord;
	TOnCorrectWord FOnCorrectWord;
	TOnSkipWord FOnSkipWord;
	System::Classes::TStringList* FCheckAttribs;
	System::Classes::TStringList* FSkipList;
	TSynSpellCheckOptions fOptions;
	TUnderlineStyle FUnderlineStyle;
	System::Sysutils::TEncoding* FIntEnc;                                                         //Fiala
	    /* Functions */
	int __fastcall FindWord(String sWord);
	String __fastcall GetDefaultDictionaryDir();
	String __fastcall GetDictionaryDir();
	String __fastcall GetUserDictionaryDir();
    /* Procedures */
	void __fastcall CalculateCacheArray();
	void __fastcall JHCMPInit(int Max1, int Max2, TJHCMPLongintMatrix& Differences);
	void __fastcall SetSkipList(System::Classes::TStringList* Value);  //*
	void __fastcall SortWordList();
	void __fastcall SetCheckAttribs(System::Classes::TStringList* const Value);
	void __fastcall SetEditor(Synedit::TCustomSynEdit* const Value);
	void __fastcall SetHashAlgorithm(HashAlgorithms Value);
	void __fastcall SetPenColor(const TColor Value);
	void __fastcall SetHashLength(const THashLength Value);
	void __fastcall SetUnderlineStyle(TUnderlineStyle Value);
public:
/*begin moved from private*/                                                      //Fiala
    // Compare table alocation
    // Compare str1 and str2 and Max1 and Max2 are their max lengths
	typedef System::Classes::TComponent inherited;	
	#include "SynSpellCheck_friends.inc"
	int __fastcall JHCMPDiffCount(const String Str1, const String Str2);
	int __fastcall JHCMPDiffCount(const String Str1, const String Str2, TJHCMPLongintMatrix& Differences);
	int __fastcall JHCMPFindSimilar(const String Word, int MaxDiffCount, int MaxDiffLength, System::Classes::TStrings* Similar);
    // Count number of differences str1 and str2 (case sensitive)
	bool __fastcall JHCMPIsSimilar(const String Str1, const String Str2, int MaxDiffCount);
	bool __fastcall JHCMPIsSimilar(const String Str1, const String Str2, int MaxDiffCount, TJHCMPLongintMatrix& Differences);
/*end*/                                                                           //Fiala
	__fastcall TSynSpellCheck(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynSpellCheck();
    /* Functions */
	bool __fastcall SpellIsIdentChar(WideChar AChar);
	bool __fastcall SpellIsWhiteChar(WideChar AChar);
	int __fastcall AddEditor(Synedit::TCustomSynEdit* AEditor);
	String __fastcall Ansi2Ascii(const String SString);       //*
	bool __fastcall CheckWord(String Word);
	bool __fastcall DictionaryExists(String Language, String Path = L"");
	String __fastcall GetNewestDictionary(String Language);
	int __fastcall GetSuggestions(String Word, System::Classes::TStringList* SuggestionList);
	int __fastcall GetWordCount();
	String __fastcall GetWordFromASCIIWord(String sWord);
	bool __fastcall IsDictWord(String Word);
	bool __fastcall IsSkipWord(String Word);
	bool __fastcall RemoveEditor(Synedit::TCustomSynEdit* AEditor);
    /* Procedures */
	void __fastcall AddDiacritic(Vcl::Comctrls::TProgressBar* Progress);
	void __fastcall AddDictWord(String Word);
	void __fastcall AddDictWordList(System::Classes::TStringList* WordList);
	void __fastcall AddSkipWord(String Word);
	void __fastcall AddSkipWordList(System::Classes::TStringList* WordList);
	void __fastcall ClearDictWords();
	void __fastcall ClearSkipWords();
	void __fastcall CloseDictionary();
	void __fastcall DeleteDictWord(String Word);
	void __fastcall DeleteSkipWord(String Word);
	void __fastcall FixLists();
	void __fastcall GetDictionaryList(System::Classes::TStringList*& tslList);
	void __fastcall LoadDictionary(String Language, String FileName = L"");
	void __fastcall LoadSkipList(String FileName);
	void __fastcall SaveSkipList(String FileName);
	void __fastcall SaveUserDictionary();
	void __fastcall SelectWordAtCursor();
	void __fastcall SpellCheck();
__published:
    /* Properties */
	__property HashAlgorithms Algorithm = { read = FHashAlgorithm, write = SetHashAlgorithm, default = /*# haDiff */ 2 };
	__property String Apostrophes = { read = FApostrophes, write = FApostrophes };
	__property bool Busy = { read = FBusy, default = false };
	__property TStringList* CheckAttribs = { read = FCheckAttribs, write = SetCheckAttribs };
	__property String Dictionary = { read = FDictionary };
	__property String DictionaryPath = { read = GetDictionaryDir, write = FDictPath };
	__property TCustomSynEdit* Editor = { read = FEditor, write = SetEditor };
	__property THashLength HashLength = { read = FHashLength, write = SetHashLength, default = 4 };
	__property TLanguageRec Language = { read = FLanguage };
	__property bool Modified = { read = FModified, write = FModified, default = false };
	__property bool OpenDictionary = { read = FOpenDictionary };
	__property TSynSpellCheckOptions Options = { read = fOptions, write = fOptions };
	__property TColor PenColor = { read = FPenColor, write = SetPenColor, default = clRed };
	__property TStringList* SkipList = { read = FSkipList, write = SetSkipList };
	__property TUnderlineStyle UnderlineStyle = { read = FUnderlineStyle, write = SetUnderlineStyle, default = /*# usMicrosoftWord */ 1 };
	__property String UserDirectory = { read = GetUserDictionaryDir, write = FUserDictPath };
	__property bool UseUserDictionary = { read = FUseUserDictionary, write = FUseUserDictionary, default = true };
    /* Events */
	__property TNotifyEvent OnAbort = { read = FOnAbort, write = FOnAbort };
	__property TOnAddWord OnAddWord = { read = FOnAddWord, write = FOnAddWord };
	__property TOnCheckWord OnCheckWord = { read = FOnCheckWord, write = FOnCheckWord };
	__property TOnCorrectWord OnCorrectWord = { read = FOnCorrectWord, write = FOnCorrectWord };
	__property TNotifyEvent OnDictClose = { read = FOnDictClose, write = FOnDictClose };
	__property TNotifyEvent OnDictLoad = { read = FOnDictLoad, write = FOnDictLoad };
	__property TNotifyEvent OnDone = { read = FOnDone, write = FOnDone };
	__property TOnSkipWord OnSkipWord = { read = FOnSkipWord, write = FOnSkipWord };
	__property TNotifyEvent OnStart = { read = FOnStart, write = FOnStart };
};

class ENoDictionaryLoaded : public System::Sysutils::EExternal
{
	#include "SynSpellCheck_friends.inc"
public:
	typedef System::Sysutils::EExternal inherited;	
	__fastcall ENoDictionaryLoaded(const String Msg);
	__fastcall ENoDictionaryLoaded(const String Msg, const TVarRec* Args, int Args_maxidx);
	__fastcall ENoDictionaryLoaded(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ENoDictionaryLoaded(const String Msg, int AHelpContext);
	__fastcall ENoDictionaryLoaded(System::NativeUInt Ident);
	__fastcall ENoDictionaryLoaded(System::PResStringRec ResStringRec);
	__fastcall ENoDictionaryLoaded(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx);
	__fastcall ENoDictionaryLoaded(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx);
	__fastcall ENoDictionaryLoaded(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ENoDictionaryLoaded(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ENoDictionaryLoaded(System::NativeUInt Ident, int AHelpContext);
	__fastcall ENoDictionaryLoaded(System::PResStringRec ResStringRec, int AHelpContext);
};
const System::Char SNoDictionaryLoaded[] = L"No dictionary is loaded.";
String __fastcall DupeString(const String AText, int ACount);
int __fastcall ElfHash(const String Value);
String __fastcall TrimEx(const String sWord, WideChar chChar);
  //////////////////////////////////////////////////////////////////////////////
  // Action constants
  //////////////////////////////////////////////////////////////////////////////
const int ACTION_ABORT = -1;
const int ACTION_SKIP = 0;
const int ACTION_SKIPALL = 1;
const int ACTION_CORRECT = 2;
const int ACTION_ADD = 3;
const int ACTION_UNDO = -2;
void __fastcall Register();


}  // namespace SynSpellCheck

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synspellcheck;
#endif

#endif // SynSpellCheckH

