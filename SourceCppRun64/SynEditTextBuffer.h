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
  Unicode translation by Maël Hörz.
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
  Unicode translation by Maël Hörz.
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


/*------------------------------------------------------------------------------*/
/* Common compiler defines                                                      */
/* (remove the dot in front of a define to enable it)                           */
/*------------------------------------------------------------------------------*/

/*$B-,H+*/ // defaults are short evaluation of boolean values and long strings

/*.$DEFINE SYN_DEVELOPMENT_CHECKS*/ // additional tests for debugging
  

/*------------------------------------------------------------------------------*/
/* Pull in all defines from SynEditJedi.inc (must be done after the common      */
/* compiler defines to  work correctly). Use SynEdit-prefix to avoid problems   */
/* with other versions of jedi.inc in the search-path.                          */
/*------------------------------------------------------------------------------*/

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

/*------------------------------------------------------------------------------*/
/*  Please change this to suit your needs (to activate an option remove the dot */
/*  in front of a DEFINE)                                                       */
/*------------------------------------------------------------------------------*/

// "Heredoc" syntax highlighting
// If you enable the following statement and use highlighter(s) that have
// support for "Heredoc" strings as scheme(s) in SynMultiSyn, you must
// implement your own SynMultiSyn OnCustomRange event handler in order to
// properly store Range State information
/*.$DEFINE SYN_HEREDOC*/

// Turn this off if you don't need complex script support, since it is slower
/*.$DEFINE SYN_UNISCRIBE*/

// $Id: SynEdit.inc,v 1.16.2.19 2009/06/14 13:41:44 maelh Exp $
typedef void* TSynEditRange;
enum TSynEditStringFlag {sfHasTabs,
                         sfHasNoTabs,
                         sfExpandedLengthUnknown,
                         sfModified,
                         sfSaved,
                         sfAsSaved };
typedef System::Set<TSynEditStringFlag, TSynEditStringFlag::sfHasTabs, TSynEditStringFlag::sfAsSaved> TSynEditStringFlags;

  // Managed by Undo
typedef TSynEditStringFlag /*sfModified..sfAsSaved*/ TSynLineChangeFlag;
typedef System::Set<TSynLineChangeFlag, sfModified, sfAsSaved> TSynLineChangeFlags;
struct TSynEditStringRec;
typedef TSynEditStringRec* PSynEditStringRec;

struct TSynEditStringRec
{
	String FString;
	TObject* FObject;
	TSynEditRange FRange;
	int FExpandedLength;
	int FCharIndex;
	TSynEditStringFlags FFlags;
};

struct TSynEditTwoWideChars
{
	WideChar One;
	WideChar Two;
};
typedef TSynEditTwoWideChars* PSynEditTwoWideChars;
const unsigned __int64 SynEditStringRecSize = sizeof(TSynEditStringRec);
const unsigned __int64 MaxSynEditStrings = (unsigned __int64)(System::MaxInt / /*div*/ SynEditStringRecSize);
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
	Synedittypes::TSynEditFileFormat FFileFormat;
	Syneditmiscprocs::TConvertTabsProcEx FConvertTabsProc;
	int FIndexOfLongestLine;
	int FTabWidth;
	TExpandAtWideGlyphsFunc FExpandAtWideGlyphsFunc;
	bool FCharIndexesAreValid;
	bool FDetectUTF8;
	int FUTF8CheckLen;
	TNotifyEvent FOnChange;
	TNotifyEvent FOnChanging;
	TNotifyEvent FOnCleared;
	TStringListChangeEvent FOnBeforeDeleted;
	TStringListChangeEvent FOnDeleted;
	TStringListChangeEvent FOnInserted;
	TStringListPutEvent FOnPut;
	Synedittypes::TSynInfoLossEvent FOnInfoLoss;
	String __fastcall ExpandString(int Index);
	String __fastcall GetExpandedString(int Index);
	int __fastcall GetExpandedStringLength(int Index);
	int __fastcall GetLengthOfLongestLine();
	TSynEditRange __fastcall GetRange(int Index);
	void __fastcall Grow();
	void __fastcall InsertItem(int Index, const String S);
	void __fastcall PutRange(int Index, TSynEditRange ARange);
	TSynLineChangeFlags __fastcall GetChangeFlags(int Index);
	void __fastcall SetChangeFlags(int Index, const TSynLineChangeFlags Value);
protected:
    // TStrings overriden protected methods
	virtual String __fastcall Get(int Index);
	virtual int __fastcall GetCapacity();
	virtual int __fastcall GetCount();
	virtual TObject* __fastcall GetObject(int Index);
	virtual void __fastcall Put(int Index, const String S);
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
	virtual void __fastcall Insert(int Index, const String S);
	virtual void __fastcall LoadFromStream(TStream* Stream, TEncoding* Encoding);
	virtual void __fastcall SaveToStream(TStream* Stream, TEncoding* Encoding);
	virtual void __fastcall SetEncoding(TEncoding* const Value); // just to elevate
    // Other public methods
	__fastcall TSynEditStringList(TExpandAtWideGlyphsFunc AExpandAtWideGlyphsFunc);
	virtual __fastcall ~TSynEditStringList();
	void __fastcall InsertStrings(int Index, System::TArray<String>& Strings, int FromIndex = 0);
	void __fastcall InsertText(int Index, String NewText);
	String __fastcall GetSeparatedText(String Separators);
	void __fastcall FontChanged();
	int __fastcall LineCharLength(int Index);
	int __fastcall LineCharIndex(int Index);
	void __fastcall SetTextAndFileFormat(const String Value);
	__property Synedittypes::TSynEditFileFormat FileFormat = { read = FFileFormat, write = FFileFormat };
	__property String ExpandedStrings[int Index] = { read = GetExpandedString };
	__property int ExpandedStringLengths[int Index] = { read = GetExpandedStringLength };
	__property int LengthOfLongestLine = { read = GetLengthOfLongestLine };
	__property TSynEditRange Ranges[int Index] = { read = GetRange, write = PutRange };
	__property int TabWidth = { read = FTabWidth, write = SetTabWidth };
	__property int UTF8CheckLen = { read = FUTF8CheckLen, write = FUTF8CheckLen };
	__property bool DetectUTF8 = { read = FDetectUTF8, write = FDetectUTF8 };
	__property TSynLineChangeFlags ChangeFlags[int Index] = { read = GetChangeFlags, write = SetChangeFlags };
	__property TNotifyEvent OnChange = { read = FOnChange, write = FOnChange };
	__property TNotifyEvent OnChanging = { read = FOnChanging, write = FOnChanging };
	__property TNotifyEvent OnCleared = { read = FOnCleared, write = FOnCleared };
	__property TStringListChangeEvent OnBeforeDeleted = { read = FOnBeforeDeleted, write = FOnBeforeDeleted };
	__property TStringListChangeEvent OnDeleted = { read = FOnDeleted, write = FOnDeleted };
	__property TStringListChangeEvent OnInserted = { read = FOnInserted, write = FOnInserted };
	__property TStringListPutEvent OnPut = { read = FOnPut, write = FOnPut };
	__property Synedittypes::TSynInfoLossEvent OnInfoLoss = { read = FOnInfoLoss, write = FOnInfoLoss };
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

