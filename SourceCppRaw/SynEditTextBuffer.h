#ifndef SynEditTextBufferH
#define SynEditTextBufferH

#include <System.hpp>
#include "d2c_system.h"

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include "SynEditTypes.h"
#include "SynEditMiscProcs.h"
#include "SynUnicode.h"

namespace Synedittextbuffer
{

/* -------------------------------------------------------------------------------
  The contents of this file are subject to the Mozilla Public License
  Version 1.1 (the "License"); you may not use this file except in compliance
  with the License. You may obtain a copy of the License at
  http://www.mozilla.org/MPL/

  Software distributed under the License is distributed on an "AS IS" basis,
  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
  the specific language governing rights and limitations under the License.

  The Original Code is: SynEditTextBuffer.pas, released 2000-04-07.
  The Original Code is based on parts of mwCustomEdit.pas by Martin Waldenburg,
  part of the mwEdit component suite.
  Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
  Unicode translation by Ma?l H?rz.
  All Rights Reserved.

  Contributors to the SynEdit and mwEdit projects are listed in the
  Contributors.txt file.

  Alternatively, the contents of this file may be used under the terms of the
  GNU General Public License Version 2 or later (the "GPL"), in which case
  the provisions of the GPL are applicable instead of those above.
  If you wish to allow use of your version of this file only under the terms
  of the GPL and not to allow others to use your version of this file
  under the MPL, indicate your decision by deleting the provisions above and
  replace them with the notice and other provisions required by the GPL.
  If you do not delete the provisions above, a recipient may use your version
  of this file under either the MPL or the GPL.

  Known Issues:
  ------------------------------------------------------------------------------- */
// todo: Avoid calculating expanded string unncessarily (just calculate expandedLength instead).
typedef void* TSynEditRange;
enum TSynEditStringFlag {sfHasTabs,
                         sfHasNoTabs,
                         sfExpandedLengthUnknown,
                         sfModified,
                         sfSaved,
                         sfAsSaved };
typedef System::Set<TSynEditStringFlag, sfHasTabs, sfAsSaved> TSynEditStringFlags;

  // Managed by Undo
typedef int /*# guessed*/ /*sfModified..sfAsSaved*/ TSynLineChangeFlag;
typedef System::Set<TSynLineChangeFlag, sfModified, sfAsSaved> TSynLineChangeFlags;
struct TSynEditStringRec;
typedef TSynEditStringRec* PSynEditStringRec;

struct TSynEditStringRec
{
	String FString;
	TObject* FObject;
	TSynEditRange FRange;
	int fExpandedLength;
	int fCharIndex;
	TSynEditStringFlags FFlags;
};

struct TSynEditTwoWideChars
{
	WideChar One;
	WideChar Two;
};
typedef TSynEditTwoWideChars* PSynEditTwoWideChars;
const int SynEditStringRecSize = sizeof(TSynEditStringRec);
const int MaxSynEditStrings = (int)(System::MaxInt / SynEditStringRecSize);
const void* const NullRange = ((TSynEditRange) -1);
typedef TSynEditStringRec TSynEditStringRecList[(MaxSynEditStrings - 1)+1 - 0/*# range 0..MaxSynEditStrings-1*/];
typedef TSynEditStringRecList* PSynEditStringRecList;
typedef void __fastcall (__closure *TStringListChangeEvent) (TObject*, int, int);
typedef void __fastcall (__closure *TStringListPutEvent) (TObject*, int, const String);
typedef String __fastcall (__closure *TExpandAtWideGlyphsFunc) (const String);

class TSynEditStringList : public System::Classes::TStrings
{
private:
	PSynEditStringRecList FList;
	int FCount;
	int FCapacity;
	Synedittypes::TSynEditFileFormat fFileFormat;
	Syneditmiscprocs::TConvertTabsProcEx fConvertTabsProc;
	int fIndexOfLongestLine;
	int FTabWidth;
	TExpandAtWideGlyphsFunc fExpandAtWideGlyphsFunc;
	bool fCharIndexesAreValid;
	bool fDetectUTF8;
	int fUTF8CheckLen;
	System::Classes::TNotifyEvent FOnChange;
	System::Classes::TNotifyEvent FOnChanging;
	System::Classes::TNotifyEvent fOnCleared;
	TStringListChangeEvent FOnBeforeDeleted;
	TStringListChangeEvent fOnDeleted;
	TStringListChangeEvent fOnInserted;
	TStringListPutEvent FOnPut;
	Synedittypes::TSynInfoLossEvent fOnInfoLoss;
	String __fastcall ExpandString(int Index);
	String __fastcall GetExpandedString(int Index);
	int __fastcall GetExpandedStringLength(int Index);
	int __fastcall GetLengthOfLongestLine();
	TSynEditRange __fastcall GetRange(int Index);
	void __fastcall Grow();
	void __fastcall InsertItem(int Index, const String s);
	void __fastcall PutRange(int Index, TSynEditRange ARange);
	TSynLineChangeFlags __fastcall GetChangeFlags(int Index);
	void __fastcall SetChangeFlags(int Index, const TSynLineChangeFlags Value);
protected:
    // TStrings overriden protected methods
	virtual String __fastcall Get(int Index);
	virtual int __fastcall GetCapacity();
	virtual int __fastcall GetCount();
	virtual TObject* __fastcall GetObject(int Index);
	virtual void __fastcall Put(int Index, const String s);
	virtual void __fastcall PutObject(int Index, TObject* AObject);
	virtual void __fastcall SetCapacity(int NewCapacity);
	virtual void __fastcall SetTextStr(const String Value);
	virtual void __fastcall SetUpdateState(bool Updating);
    // Other protected methods
	void __fastcall SetTabWidth(int Value);
	void __fastcall UpdateCharIndexes();
public:
    // TStrings overriden public methods
	typedef System::Classes::TStrings inherited;	
	#include "SynEditTextBuffer_friends.inc"
	virtual void __fastcall Clear();
	virtual void __fastcall Delete(int Index);
	void __fastcall DeleteLines(int Index, int NumLines);
	virtual void __fastcall Insert(int Index, const String s);
	virtual void __fastcall LoadFromStream(System::Classes::TStream* Stream, System::Sysutils::TEncoding* Encoding);
	virtual void __fastcall SaveToStream(System::Classes::TStream* Stream, System::Sysutils::TEncoding* Encoding);
	virtual void __fastcall SetEncoding(System::Sysutils::TEncoding* const Value); // just to elevate
    // Other public methods
	__fastcall TSynEditStringList(TExpandAtWideGlyphsFunc AExpandAtWideGlyphsFunc);
	virtual __fastcall ~TSynEditStringList();
	void __fastcall InsertStrings(int Index, System::TArray<String>& Strings, int FromIndex = 0);
	void __fastcall InsertText(int Index, String NewText);
	String __fastcall GetSeparatedText(String SeparatorS);
	void __fastcall FontChanged();
	int __fastcall LineCharLength(int Index);
	int __fastcall LineCharIndex(int Index);
	void __fastcall SetTextAndFileFormat(const String Value);
	__property Synedittypes::TSynEditFileFormat FileFormat = { read = fFileFormat, write = fFileFormat };
	__property String ExpandedStrings[int Index] = { read = GetExpandedString };
	__property int ExpandedStringLengths[int Index] = { read = GetExpandedStringLength };
	__property int LengthOfLongestLine = { read = GetLengthOfLongestLine };
	__property TSynEditRange Ranges[int Index] = { read = GetRange, write = PutRange };
	__property int TabWidth = { read = FTabWidth, write = SetTabWidth };
	__property int UTF8CheckLen = { read = fUTF8CheckLen, write = fUTF8CheckLen };
	__property bool DetectUTF8 = { read = fDetectUTF8, write = fDetectUTF8 };
	__property TSynLineChangeFlags ChangeFlags[int Index] = { read = GetChangeFlags, write = SetChangeFlags };
	__property System::Classes::TNotifyEvent OnChange = { read = FOnChange, write = FOnChange };
	__property System::Classes::TNotifyEvent OnChanging = { read = FOnChanging, write = FOnChanging };
	__property System::Classes::TNotifyEvent OnCleared = { read = fOnCleared, write = fOnCleared };
	__property TStringListChangeEvent OnBeforeDeleted = { read = FOnBeforeDeleted, write = FOnBeforeDeleted };
	__property TStringListChangeEvent OnDeleted = { read = fOnDeleted, write = fOnDeleted };
	__property TStringListChangeEvent OnInserted = { read = fOnInserted, write = fOnInserted };
	__property TStringListPutEvent OnPut = { read = FOnPut, write = FOnPut };
	__property Synedittypes::TSynInfoLossEvent OnInfoLoss = { read = fOnInfoLoss, write = fOnInfoLoss };
	__fastcall TSynEditStringList();
};

class ESynEditStringList : public System::Sysutils::Exception
{
	#include "SynEditTextBuffer_friends.inc"
public:
	typedef System::Sysutils::Exception inherited;	
	__fastcall ESynEditStringList(const String Msg);
	__fastcall ESynEditStringList(const String Msg, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynEditStringList(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynEditStringList(const String Msg, int AHelpContext);
	__fastcall ESynEditStringList(System::NativeUInt Ident);
	__fastcall ESynEditStringList(System::PResStringRec ResStringRec);
	__fastcall ESynEditStringList(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynEditStringList(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynEditStringList(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynEditStringList(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynEditStringList(System::NativeUInt Ident, int AHelpContext);
	__fastcall ESynEditStringList(System::PResStringRec ResStringRec, int AHelpContext);
};


}  // namespace SynEditTextBuffer

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synedittextbuffer;
#endif

#endif // SynEditTextBufferH

