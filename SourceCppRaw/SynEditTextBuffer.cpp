#include <vcl.h>
#pragma hdrstop

#include "SynEditTextBuffer.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditmiscprocs;
using namespace Synedittypes;
using namespace Synunicode;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;

namespace Synedittextbuffer
{
#define Synedittextbuffer__0 (TStringsOptions() << soWriteBOM << soTrailingLineBreak)
#define Synedittextbuffer__1 (TSynEditStringFlags() <<  \
										sfModified << sfSaved << sfAsSaved)
#define Synedittextbuffer__2 TSynLineChangeFlags()
#define Synedittextbuffer__3 (TArray() << s)
#define Synedittextbuffer__4 (TSynEditStringFlags() << sfExpandedLengthUnknown)
#define Synedittextbuffer__5 (TSynEditStringFlags() << sfExpandedLengthUnknown)
#define Synedittextbuffer__6 (TSynEditStringFlags() <<  \
										sfModified << sfSaved << sfAsSaved)
#define Synedittextbuffer__7 (System::Set<WORD, 0, 255>() << 10 << 13)
#define Synedittextbuffer__8 (TSysCharSet() << '\x0a' << '\x0d')

__fastcall TSynEditStringList::TSynEditStringList() {}
__fastcall ESynEditStringList::ESynEditStringList(const String Msg) : inherited(Msg) {}
__fastcall ESynEditStringList::ESynEditStringList(const String Msg, const TVarRec* Args, int Args_maxidx) : inherited(Msg, Args, Args_maxidx) {}
__fastcall ESynEditStringList::ESynEditStringList(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Msg, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynEditStringList::ESynEditStringList(const String Msg, int AHelpContext) : inherited(Msg, AHelpContext) {}
__fastcall ESynEditStringList::ESynEditStringList(System::NativeUInt Ident) : inherited(Ident) {}
__fastcall ESynEditStringList::ESynEditStringList(System::PResStringRec ResStringRec) : inherited(ResStringRec) {}
__fastcall ESynEditStringList::ESynEditStringList(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx) : inherited(Ident, Args, Args_maxidx) {}
__fastcall ESynEditStringList::ESynEditStringList(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx) : inherited(ResStringRec, Args, Args_maxidx) {}
__fastcall ESynEditStringList::ESynEditStringList(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(ResStringRec, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynEditStringList::ESynEditStringList(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Ident, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynEditStringList::ESynEditStringList(System::NativeUInt Ident, int AHelpContext) : inherited(Ident, AHelpContext) {}
__fastcall ESynEditStringList::ESynEditStringList(System::PResStringRec ResStringRec, int AHelpContext) : inherited(ResStringRec, AHelpContext) {}


const System::Char SListIndexOutOfBounds[] = L"Invalid stringlist index %d";
const System::Char SInvalidCapacity[] = L"Stringlist capacity cannot be smaller than count";

  /* TSynEditStringList */

void __fastcall ListIndexOutOfBounds(int Index)
{
	throw new ESynEditStringList(SListIndexOutOfBounds, ARRAYOFCONST((Index)));
}

__fastcall TSynEditStringList::TSynEditStringList(TExpandAtWideGlyphsFunc AExpandAtWideGlyphsFunc)
 : FList(nullptr),
			FCount(0),
			FCapacity(0),
			fFileFormat(sffDos),
			fIndexOfLongestLine(0),
			FTabWidth(0),
			fCharIndexesAreValid(false),
			fDetectUTF8(false),
			fUTF8CheckLen(0)
{
	//# inherited::Create();
	fExpandAtWideGlyphsFunc = AExpandAtWideGlyphsFunc;
	fFileFormat = sffDos;
	fIndexOfLongestLine = -1;
	TabWidth = 8;
	fUTF8CheckLen = -1;
	Options = Options - Synedittextbuffer__0;
	fDetectUTF8 = true;
}

__fastcall TSynEditStringList::~TSynEditStringList()
{
	FOnChange = nullptr;
	FOnChanging = nullptr;
	//# inherited::Destroy();
	if(FCount != 0)
		Finalize((void**)&(*FList)[0], FCount);
	FCount = 0;
	SetCapacity(0);
}

void __fastcall TSynEditStringList::Clear()
{
	int OldCount = 0;
	if(FCount != 0)
	{
		BeginUpdate();
		OldCount = FCount;
		if(ASSIGNED(FOnBeforeDeleted))
			FOnBeforeDeleted(this, 0, OldCount);
		Finalize((void**)&(*FList)[0], FCount);
		FCount = 0;
		SetCapacity(0);
		if(ASSIGNED(fOnDeleted))
			fOnDeleted(this, 0, OldCount);
		if(ASSIGNED(fOnCleared))
			fOnCleared(this);
		EndUpdate();
	}
	fIndexOfLongestLine = -1;
}

void __fastcall TSynEditStringList::Delete(int Index)
{
	if((Index < 0) || (Index >= FCount))
		ListIndexOutOfBounds(Index);
	BeginUpdate();
	if(ASSIGNED(FOnBeforeDeleted))
		FOnBeforeDeleted(this, Index, 1);
	Finalize((void**)&(*FList)[Index]);
	--FCount;
	if(Index < FCount)
	{
		System::Move(&(*FList)[Index + 1], &(*FList)[Index], (FCount - Index) * SynEditStringRecSize);
	}
	fIndexOfLongestLine = -1;
	if(ASSIGNED(fOnDeleted))
		fOnDeleted(this, Index, 1);
	EndUpdate();
}

void __fastcall TSynEditStringList::DeleteLines(int Index, int NumLines)
{
	int LinesAfter = 0;
	if(NumLines > 0)
	{
		if((Index < 0) || (Index >= FCount))
			ListIndexOutOfBounds(Index);
		BeginUpdate();
		try
		{
			if(ASSIGNED(FOnBeforeDeleted))
				FOnBeforeDeleted(this, Index, NumLines);
			LinesAfter = FCount - (Index + NumLines);
			if(LinesAfter < 0)
				NumLines = FCount - Index;
			Finalize((void**)&(*FList)[Index], NumLines);
			if(LinesAfter > 0)
				System::Move(&(*FList)[Index + NumLines], &(*FList)[Index], LinesAfter * SynEditStringRecSize);
			FCount -= NumLines;
			if(ASSIGNED(fOnDeleted))
				fOnDeleted(this, Index, NumLines);
		}
		__finally
		{
			EndUpdate();
		}
	}
}

String __fastcall TSynEditStringList::ExpandString(int Index)
{
	String result;
	bool HasTabs = false;
	/*# with FList^[Index] do */
	{
		
		if((*FList)[Index].FString.Length() == 0)
		{
			result = L"";
			(*FList)[Index].FFlags >> sfExpandedLengthUnknown;
			(*FList)[Index].FFlags >> sfHasTabs;
			(*FList)[Index].FFlags << sfHasNoTabs;
			(*FList)[Index].fExpandedLength = 0;
		}
		else
		{
			result = fConvertTabsProc((*FList)[Index].FString, FTabWidth, HasTabs);
			(*FList)[Index].fExpandedLength = Length(fExpandAtWideGlyphsFunc(result));
			(*FList)[Index].FFlags >> sfExpandedLengthUnknown;
			(*FList)[Index].FFlags >> sfHasTabs;
			(*FList)[Index].FFlags >> sfHasNoTabs;
			if(HasTabs)
				(*FList)[Index].FFlags << sfHasTabs;
			else
				(*FList)[Index].FFlags << sfHasNoTabs;
		}
	}
	return result;
}

String __fastcall TSynEditStringList::Get(int Index)
{
	String result;
	if(((unsigned int) Index) < ((unsigned int) FCount))
		result = (*FList)[Index].FString;
	else
		result = L"";
	return result;
}

void __fastcall TSynEditStringList::UpdateCharIndexes()
{
	int i = 0;
	int n = 0;
	PSynEditStringRec P = nullptr;
	int stop = 0;
	fCharIndexesAreValid = true;
	if(FCount == 0)
		return;
	P = &(*FList)[0];
	n = 0;
	for(stop = FCount, i = 1; i <= stop; i++)
	{
		P->fCharIndex = n;
		n += P->FString.Length();
		++P;
	}
}

int __fastcall TSynEditStringList::LineCharLength(int Index)
{
	int result = 0;
	if(((unsigned int) Index) < ((unsigned int) FCount))
		result = (*FList)[Index].FString.Length();
	else
		result = 0;
	return result;
}

int __fastcall TSynEditStringList::LineCharIndex(int Index)
{
	int result = 0;
	if(((unsigned int) Index) < ((unsigned int) FCount))
	{
		if(!fCharIndexesAreValid)
			UpdateCharIndexes();
		result = (*FList)[Index].fCharIndex;
	}
	else
	result = 0;
	return result;
}

int __fastcall TSynEditStringList::GetCapacity()
{
	int result = 0;
	result = FCapacity;
	return result;
}

TSynLineChangeFlags __fastcall TSynEditStringList::GetChangeFlags(int Index)
{
	TSynLineChangeFlags result;
	if((Index >= 0) && (Index < FCount))
		result = (*FList)[Index].FFlags * Synedittextbuffer__1;
	else
		result = Synedittextbuffer__2;
	return result;
}

int __fastcall TSynEditStringList::GetCount()
{
	int result = 0;
	result = FCount;
	return result;
}

String __fastcall TSynEditStringList::GetExpandedString(int Index)
{
	String result;
	if((Index >= 0) && (Index < FCount))
	{
		if((*FList)[Index].FFlags.Contains(sfHasNoTabs))
			result = Get(Index);
		else
			result = ExpandString(Index);
	}
	else
	result = L"";
	return result;
}

int __fastcall TSynEditStringList::GetExpandedStringLength(int Index)
{
	int result = 0;
	if((Index >= 0) && (Index < FCount))
	{
		if((*FList)[Index].FFlags.Contains(sfExpandedLengthUnknown))
			result = String(ExpandedStrings[Index]).Length();
		else
			result = (*FList)[Index].fExpandedLength;
	}
	else
	result = 0;
	return result;
}

int __fastcall TSynEditStringList::GetLengthOfLongestLine()
{
	int result = 0;
	int i = 0;
	int MaxLen = 0;
	PSynEditStringRec Prec = nullptr;
	if(fIndexOfLongestLine < 0)
	{
		MaxLen = 0;
		if(FCount > 0)
		{
			int stop = 0;
			Prec = &(*FList)[0];
			for(stop = FCount - 1, i = 0; i <= stop; i++)
			{
				if((*Prec).FFlags.Contains(sfExpandedLengthUnknown))
					ExpandString(i);
				if((*Prec).fExpandedLength > MaxLen)
				{
					MaxLen = (*Prec).fExpandedLength;
					fIndexOfLongestLine = i;
				}
				++Prec;
			}
		}
	}
	if((fIndexOfLongestLine >= 0) && (fIndexOfLongestLine < FCount))
		result = (*FList)[fIndexOfLongestLine].fExpandedLength;
	else
		result = 0;
	return result;
}

TObject* __fastcall TSynEditStringList::GetObject(int Index)
{
	TObject* result = nullptr;
	if((Index >= 0) && (Index < FCount))
		result = (*FList)[Index].FObject;
	else
		result = nullptr;
	return result;
}

TSynEditRange __fastcall TSynEditStringList::GetRange(int Index)
{
	TSynEditRange result = nullptr;
	if((Index >= 0) && (Index < FCount))
		result = (*FList)[Index].FRange;
	else
		result = nullptr;
	return result;
}
/* Optimized by Eric Grange */

String __fastcall TSynEditStringList::GetSeparatedText(String SeparatorS)
{
	String result;
	int i = 0;
	int l = 0;
	int Size = 0;
	int LineBreakSize = 0;
	PChar P = nullptr;
	PChar PLineBreak = nullptr;
	PSynEditStringRec Prec = nullptr;
	int stop = 0;
	if(FCount == 0)
	{
		result = L"";
		return result;
	}
	LineBreakSize = SeparatorS.Length();
	PLineBreak = ustr2pwchar(SeparatorS);

  // compute buffer size
	Size = (FCount - 1) * LineBreakSize + LineCharIndex(FCount - 1) + (*FList)[FCount - 1].FString.Length();
	result.SetLength(Size);
	P = ustr2pwchar(result);
	Prec = &(*FList)[0];

  // handle 1st line separately (to avoid trailing line break)
	l = Prec->FString.Length();
	if(l != 0)
	{
		System::Move(ustr2address(Prec->FString), P, l * sizeof(Char));
		P += l;
	}
	++Prec;
	for(stop = FCount - 1, i = 1; i <= stop; i++)
	{
		switch(LineBreakSize)
		{
			case 0:
			;
			break;
			case 1:
			{
				(*P) = (*PLineBreak);
				++P;
			}
			break;
			case 2:
			{
				(*((PSynEditTwoWideChars) P)) = (*((PSynEditTwoWideChars) PLineBreak));
				P += 2;
			}
			break;
			default:
			System::Move(PLineBreak, P, LineBreakSize * sizeof(Char));
			P += LineBreakSize;
			break;
		}
		if(ustr2address(Prec->FString) != nullptr)
		{
			l = Prec->FString.Length();
			System::Move(ustr2address(Prec->FString), P, l * sizeof(Char));
			P += l;
		}
		++Prec;
	}
	return result;
}

void __fastcall TSynEditStringList::Grow()
{
	SetCapacity(GrowCollection(FCapacity, FCount + 1));
}

void __fastcall TSynEditStringList::Insert(int Index, const String s)
{
	InsertStrings(Index, Synedittextbuffer__3);
}

void __fastcall TSynEditStringList::InsertItem(int Index, const String s)
{
	BeginUpdate();
	if(FCount == FCapacity)
		Grow();
	if(Index < FCount)
	{
		System::Move(&(*FList)[Index], &(*FList)[Index + 1], (FCount - Index) * SynEditStringRecSize);
	}
	fIndexOfLongestLine = -1;
	/*# with FList^[Index] do */
	{
		
		CastAssign<void*>(&(*FList)[Index].FString, nullptr);
		(*FList)[Index].FString = s;
		(*FList)[Index].FObject = nullptr;
		(*FList)[Index].FRange = const_cast<TSynEditRange>(NullRange);
		(*FList)[Index].fExpandedLength = -1;
		(*FList)[Index].FFlags = Synedittextbuffer__4;
	}
	++FCount;
	EndUpdate();
}

void __fastcall TSynEditStringList::InsertStrings(int Index, TArray<String>& Strings, int FromIndex/*# = 0*/)
{
	int i = 0;
	int lineCount = 0;
	if((Index < 0) || (Index > FCount))
		ListIndexOutOfBounds(Index);
	lineCount = Strings.Length - FromIndex;
	if(lineCount > 0)
	{
		BeginUpdate();
		try
		{
			int stop = 0;
			if(FCapacity < FCount + lineCount)
				SetCapacity(GrowCollection(FCapacity, FCount + lineCount));
			if(Index < FCount)
			{
				System::Move(&(*FList)[Index], &(*FList)[Index + lineCount], (FCount - Index) * SynEditStringRecSize);
			}
			for(stop = lineCount - 1, i = 0; i <= stop; i++)
			{
				/*# with FList^[Index + i] do */
				{
					
					CastAssign<void*>(&(*FList)[Index + i].FString, nullptr);
					(*FList)[Index + i].FString = Strings[FromIndex + i];
					(*FList)[Index + i].FObject = nullptr;
					(*FList)[Index + i].FRange = const_cast<TSynEditRange>(NullRange);
					(*FList)[Index + i].fExpandedLength = -1;
					(*FList)[Index + i].FFlags = Synedittextbuffer__5;
				}
			}
			FCount += lineCount;
			if(ASSIGNED(OnInserted))
				OnInserted(this, Index, lineCount);
		}
		__finally
		{
			EndUpdate();
		}
	}
}

void __fastcall TSynEditStringList::InsertText(int Index, String NewText)
{
	TStringList* TmpStringList = nullptr;
	if(NewText == L"")
		return;
	TmpStringList = new TStringList();
	try
	{
		TmpStringList->Text = NewText;
		InsertStrings(Index, TmpStringList->ToStringArray());
	}
	__finally
	{
		delete TmpStringList;
	}
}

void __fastcall TSynEditStringList::LoadFromStream(TStream* Stream, TEncoding* Encoding)
{
	int Size = 0;
	TBytes Buffer;
	String DecodedText;
	BeginUpdate();
	try
	{
		Size = (int) (Stream->Size - Stream->Position);
		Buffer.Length = Size;
		Stream->Read(Buffer, 0, Size);
		Size = TEncoding::GetBufferEncoding(Buffer, Encoding, DefaultEncoding);
		WriteBOM = Size > 0; // Keep WriteBom in case the stream is saved
    // If the encoding is ANSI and DetectUtf8 is True try to Detect UTF8
		if((Encoding == TEncoding::ANSI) && DetectUTF8 && IsUTF8(Buffer, Size))
			Encoding = TEncoding::UTF8;
		SetEncoding(Encoding); // Keep Encoding in case the stream is saved
		DecodedText = Encoding->GetString(Buffer, Size, Buffer.Length - Size);
		Buffer.Length = 0; // Free the buffer here to reduce memory footprint
		SetTextAndFileFormat(DecodedText);
	}
	__finally
	{
		EndUpdate();
	}
}

void __fastcall TSynEditStringList::SaveToStream(TStream* Stream, TEncoding* Encoding)
{
	bool Cancel = false;
	String OldLineBreak;
	String s;
	TBytes Buffer;
	TBytes Preamble;
	if(Encoding == nullptr)
		Encoding = DefaultEncoding;
	OldLineBreak = LineBreak;
	try
	{
		LineBreak = LineBreakFromFileFormat(fFileFormat);
		s = GetTextStr();
	}
	__finally
	{
		LineBreak = OldLineBreak;
	}
	Cancel = false;
	if((Encoding == TEncoding::ANSI) && ASSIGNED(fOnInfoLoss) && !IsAnsiOnly(s))
	{
		fOnInfoLoss(Encoding, Cancel);
		if(Cancel)
			return;
		if(Encoding != TEncoding::ANSI)
			SetEncoding(Encoding);
	}
	Buffer = Encoding->GetBytes(s);
	if(WriteBOM)
	{
		Preamble = Encoding->GetPreamble();
		if(Preamble.Length > 0)
			Stream->WriteBuffer(Preamble, Preamble.Length);
	}
	Stream->WriteBuffer(Buffer, Buffer.Length);
}

void __fastcall TSynEditStringList::Put(int Index, const String s)
{
	String OldLine;
	BeginUpdate();
	try
	{
		if((Index == 0) && (FCount == 0) || (FCount == Index))
			Add(L"");
		if(((unsigned int) Index) >= ((unsigned int) FCount))
			ListIndexOutOfBounds(Index);
		fIndexOfLongestLine = -1;
		/*# with FList^[Index] do */
		{
			
			(*FList)[Index].FFlags << sfExpandedLengthUnknown;
			(*FList)[Index].FFlags >> sfHasTabs;
			(*FList)[Index].FFlags >> sfHasNoTabs;
			OldLine = (*FList)[Index].FString;
			(*FList)[Index].FString = s;
		}
		if(ASSIGNED(FOnPut))
			FOnPut(this, Index, OldLine);
	}
	__finally
	{
		EndUpdate();
	}
}

void __fastcall TSynEditStringList::PutObject(int Index, TObject* AObject)
{
	if(((unsigned int) Index) >= ((unsigned int) FCount))
		ListIndexOutOfBounds(Index);
	BeginUpdate();
	(*FList)[Index].FObject = AObject;
	EndUpdate();
}

void __fastcall TSynEditStringList::PutRange(int Index, TSynEditRange ARange)
{
	if(((unsigned int) Index) >= ((unsigned int) FCount))
		ListIndexOutOfBounds(Index);
	(*FList)[Index].FRange = ARange;
}

void __fastcall TSynEditStringList::SetCapacity(int NewCapacity)
{
	if(NewCapacity < Count)
		new EListError(SInvalidCapacity);
	FList = (PSynEditStringRecList) ReallocMemory(FList, NewCapacity * SynEditStringRecSize);
	FCapacity = NewCapacity;
}

void __fastcall TSynEditStringList::SetChangeFlags(int Index, const TSynLineChangeFlags Value)
{
	if((Index >= 0) && (Index < FCount))
		(*FList)[Index].FFlags = (*FList)[Index].FFlags - Synedittextbuffer__6 + Value;
}

void __fastcall TSynEditStringList::SetEncoding(TEncoding* const Value)
{
	inherited::SetEncoding(Value);
}

void __fastcall TSynEditStringList::SetTabWidth(int Value)
{
	int i = 0;
	if(Value != FTabWidth)
	{
		int stop = 0;
		FTabWidth = Value;
		fConvertTabsProc = GetBestConvertTabsProcEx(FTabWidth);
		fIndexOfLongestLine = -1;
		for(stop = FCount - 1, i = 0; i <= stop; i++)
		{
			/*# with FList^[i] do */
			{
				
				(*FList)[i].fExpandedLength = -1;
				(*FList)[i].FFlags >> sfHasNoTabs;
				(*FList)[i].FFlags << sfExpandedLengthUnknown;
			}
		}
	}
}

void __fastcall TSynEditStringList::SetTextAndFileFormat(const String Value)
{
	String s;
	int Size = 0;
	PChar P = nullptr;
	PChar Start = nullptr;
	PChar Pmax = nullptr;
	bool fCR = false;
	bool fLF = false;
	bool fLINESEPARATOR = false;
	fLINESEPARATOR = false;
	fCR = false;
	fLF = false;
	BeginUpdate();
	try
	{
		Clear();
		P = ustr2pwchar(Value);
		if(P != nullptr)
		{
			Size = Value.Length();
			Pmax = P + Value.Length();
			while((P < Pmax))
			{
				Start = P;
				while((P < Pmax) && ((((WORD) (*P)) > 13) || !((Synedittextbuffer__7.Contains(((WORD) (*P)))) || ((*P) == WideLineSeparator))))
					++P;
				if(P != Start)
				{
					SetString(s, Start, P - Start);
					InsertItem(FCount, s);
				}
				else
				InsertItem(FCount, L"");
				if((*P) == L'\x00')
					++P;
				if((*P) == WideLineSeparator)
				{
					fLINESEPARATOR = true;
					++P;
				}
				if((*P) == WideCR)
				{
					fCR = true;
					++P;
				}
				if((*P) == WideLF)
				{
					fLF = true;
					++P;
				}
			}
      // keep the old format of the file
			if(!TrailingLineBreak && (CharInSet(Value[Size], Synedittextbuffer__8) || (Value[Size] == WideLineSeparator)))
				InsertItem(FCount, L"");
		}
		if(ASSIGNED(OnInserted) && (FCount > 0))
			OnInserted(this, 0, FCount);
	}
	__finally
	{
		EndUpdate();
	}
	if(fLINESEPARATOR)
		FileFormat = sffUnicode;
	else
	{
		if(fCR && !fLF)
			FileFormat = sffMac;
		else
		{
			if(fLF && !fCR)
				FileFormat = sffUnix;
			else
				FileFormat = sffDos;
		}
	}
}

void __fastcall TSynEditStringList::SetTextStr(const String Value)
{
	SetTextAndFileFormat(Value);
}

void __fastcall TSynEditStringList::SetUpdateState(bool Updating)
{
	fCharIndexesAreValid = false;
	if(Updating)
	{
		if(ASSIGNED(FOnChanging))
			FOnChanging(this);
	}
	else
	{
		if(ASSIGNED(FOnChange))
			FOnChange(this);
	}
}

void __fastcall TSynEditStringList::FontChanged()
{
	int i = 0;
	int stop = 0;
	fIndexOfLongestLine = -1;
	for(stop = FCount - 1, i = 0; i <= stop; i++)
	{
		/*# with FList^[i] do */
		{
			
			(*FList)[i].fExpandedLength = -1;
			(*FList)[i].FFlags >> sfHasNoTabs;
			(*FList)[i].FFlags << sfExpandedLengthUnknown;
		}
	}
}


}  // namespace SynEditTextBuffer

