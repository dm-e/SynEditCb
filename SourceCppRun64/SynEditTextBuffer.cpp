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
#define Synedittextbuffer__3 (TArray() << S)
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
			FFileFormat(sffDos),
			FIndexOfLongestLine(0),
			FTabWidth(0),
			FCharIndexesAreValid(false),
			FDetectUTF8(false),
			FUTF8CheckLen(0)
{
	//# inherited::Create();
	FExpandAtWideGlyphsFunc = AExpandAtWideGlyphsFunc;
	FFileFormat = sffDos;
	FIndexOfLongestLine = -1;
	TabWidth = 8;
	FUTF8CheckLen = -1;
	Options = Options - Synedittextbuffer__0;
	FDetectUTF8 = true;
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
		if(ASSIGNED(FOnDeleted))
			FOnDeleted(this, 0, OldCount);
		if(ASSIGNED(FOnCleared))
			FOnCleared(this);
		EndUpdate();
	}
	FIndexOfLongestLine = -1;
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
		System::Move(&(*FList)[Index + 1], &(*FList)[Index], (size_t) ((FCount - Index) * SynEditStringRecSize));
	}
	FIndexOfLongestLine = -1;
	if(ASSIGNED(FOnDeleted))
		FOnDeleted(this, Index, 1);
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
				System::Move(&(*FList)[Index + NumLines], &(*FList)[Index], (size_t) (LinesAfter * SynEditStringRecSize));
			FCount -= NumLines;
			if(ASSIGNED(FOnDeleted))
				FOnDeleted(this, Index, NumLines);
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
			(*FList)[Index].FExpandedLength = 0;
		}
		else
		{
			result = FConvertTabsProc((*FList)[Index].FString, FTabWidth, HasTabs);
			(*FList)[Index].FExpandedLength = Length(FExpandAtWideGlyphsFunc(result));
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
	int I = 0;
	int N = 0;
	PSynEditStringRec P = nullptr;
	int stop = 0;
	FCharIndexesAreValid = true;
	if(FCount == 0)
		return;
	P = &(*FList)[0];
	N = 0;
	for(stop = FCount, I = 1; I <= stop; I++)
	{
		P->FCharIndex = N;
		N += P->FString.Length();
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
		if(!FCharIndexesAreValid)
			UpdateCharIndexes();
		result = (*FList)[Index].FCharIndex;
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
		result = ConvertSubset<TSynLineChangeFlags>((*FList)[Index].FFlags * Synedittextbuffer__1);
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
			result = (*FList)[Index].FExpandedLength;
	}
	else
	result = 0;
	return result;
}

int __fastcall TSynEditStringList::GetLengthOfLongestLine()
{
	int result = 0;
	int I = 0;
	int MaxLen = 0;
	PSynEditStringRec PRec = nullptr;
	if(FIndexOfLongestLine < 0)
	{
		MaxLen = 0;
		if(FCount > 0)
		{
			int stop = 0;
			PRec = &(*FList)[0];
			for(stop = FCount - 1, I = 0; I <= stop; I++)
			{
				if((*PRec).FFlags.Contains(sfExpandedLengthUnknown))
					ExpandString(I);
				if((*PRec).FExpandedLength > MaxLen)
				{
					MaxLen = (*PRec).FExpandedLength;
					FIndexOfLongestLine = I;
				}
				++PRec;
			}
		}
	}
	if((FIndexOfLongestLine >= 0) && (FIndexOfLongestLine < FCount))
		result = (*FList)[FIndexOfLongestLine].FExpandedLength;
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

String __fastcall TSynEditStringList::GetSeparatedText(String Separators)
{
	String result;
	int I = 0;
	int L = 0;
	int Size = 0;
	int LineBreakSize = 0;
	PChar P = nullptr;
	PChar PLineBreak = nullptr;
	PSynEditStringRec PRec = nullptr;
	int stop = 0;
	if(FCount == 0)
	{
		result = L"";
		return result;
	}
	LineBreakSize = Separators.Length();
	PLineBreak = ustr2pwchar(Separators);

  // compute buffer size
	Size = (FCount - 1) * LineBreakSize + LineCharIndex(FCount - 1) + (*FList)[FCount - 1].FString.Length();
	result.SetLength(Size);
	P = ustr2pwchar(result);
	PRec = &(*FList)[0];

  // handle 1st line separately (to avoid trailing line break)
	L = PRec->FString.Length();
	if(L != 0)
	{
		System::Move(ustr2address(PRec->FString), P, (size_t) (L * sizeof(Char)));
		P += L;
	}
	++PRec;
	for(stop = FCount - 1, I = 1; I <= stop; I++)
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
			System::Move(PLineBreak, P, (size_t) (LineBreakSize * sizeof(Char)));
			P += LineBreakSize;
			break;
		}
		if(ustr2address(PRec->FString) != nullptr)
		{
			L = PRec->FString.Length();
			System::Move(ustr2address(PRec->FString), P, (size_t) (L * sizeof(Char)));
			P += L;
		}
		++PRec;
	}
	return result;
}

void __fastcall TSynEditStringList::Grow()
{
	SetCapacity(GrowCollection(FCapacity, FCount + 1));
}

void __fastcall TSynEditStringList::Insert(int Index, const String S)
{
//	InsertStrings(Index, SynEditTextBuffer__3);
	TArray<String> arr;
	arr.Length = 1;
	arr[0] = S;
	InsertStrings(Index, arr);
}

void __fastcall TSynEditStringList::InsertItem(int Index, const String S)
{
	BeginUpdate();
	if(FCount == FCapacity)
		Grow();
	if(Index < FCount)
	{
		System::Move(&(*FList)[Index], &(*FList)[Index + 1], (size_t) ((FCount - Index) * SynEditStringRecSize));
	}
	FIndexOfLongestLine = -1;
	/*# with FList^[Index] do */
	{
		
		CastAssign<void*>(&(*FList)[Index].FString, nullptr);
		(*FList)[Index].FString = S;
		(*FList)[Index].FObject = nullptr;
		(*FList)[Index].FRange = const_cast<TSynEditRange>(NullRange);
		(*FList)[Index].FExpandedLength = -1;
		(*FList)[Index].FFlags = Synedittextbuffer__4;
	}
	++FCount;
	EndUpdate();
}

void __fastcall TSynEditStringList::InsertStrings(int Index, TArray<String>& Strings, int FromIndex/*# = 0*/)
{
	int I = 0;
	int LineCount = 0;
	if((Index < 0) || (Index > FCount))
		ListIndexOutOfBounds(Index);
	LineCount = Strings.Length - FromIndex;
	if(LineCount > 0)
	{
		BeginUpdate();
		try
		{
			int stop = 0;
			if(FCapacity < FCount + LineCount)
				SetCapacity(GrowCollection(FCapacity, FCount + LineCount));
			if(Index < FCount)
			{
				System::Move(&(*FList)[Index], &(*FList)[Index + LineCount], (size_t) ((FCount - Index) * SynEditStringRecSize));
			}
			for(stop = LineCount - 1, I = 0; I <= stop; I++)
			{
				/*# with FList^[Index + I] do */
				{
					
					CastAssign<void*>(&(*FList)[Index + I].FString, nullptr);
					(*FList)[Index + I].FString = Strings[FromIndex + I];
					(*FList)[Index + I].FObject = nullptr;
					(*FList)[Index + I].FRange = const_cast<TSynEditRange>(NullRange);
					(*FList)[Index + I].FExpandedLength = -1;
					(*FList)[Index + I].FFlags = Synedittextbuffer__5;
				}
			}
			FCount += LineCount;
			if(ASSIGNED(OnInserted))
				OnInserted(this, Index, LineCount);
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
		DynamicArray<String> tmp = TmpStringList->ToStringArray();
		InsertStrings(Index, tmp);
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
	String S;
	TBytes Buffer;
	TBytes Preamble;
	if(Encoding == nullptr)
		Encoding = DefaultEncoding;
	OldLineBreak = LineBreak;
	try
	{
		LineBreak = LineBreakFromFileFormat(FFileFormat);
		S = GetTextStr();
	}
	__finally
	{
		LineBreak = OldLineBreak;
	}
	Cancel = false;
	if((Encoding == TEncoding::ANSI) && ASSIGNED(FOnInfoLoss) && !IsAnsiOnly(S))
	{
		FOnInfoLoss(Encoding, Cancel);
		if(Cancel)
			return;
		if(Encoding != TEncoding::ANSI)
			SetEncoding(Encoding);
	}
	Buffer = Encoding->GetBytes(S);
	if(WriteBOM)
	{
		Preamble = Encoding->GetPreamble();
		if(Preamble.Length > 0)
			Stream->WriteBuffer(Preamble, Preamble.Length);
	}
	Stream->WriteBuffer(Buffer, Buffer.Length);
}

void __fastcall TSynEditStringList::Put(int Index, const String S)
{
	String OldLine;
	BeginUpdate();
	try
	{
		if((Index == 0) && (FCount == 0) || (FCount == Index))
			Add(L"");
		if(((unsigned int) Index) >= ((unsigned int) FCount))
			ListIndexOutOfBounds(Index);
		FIndexOfLongestLine = -1;
		/*# with FList^[Index] do */
		{
			
			(*FList)[Index].FFlags << sfExpandedLengthUnknown;
			(*FList)[Index].FFlags >> sfHasTabs;
			(*FList)[Index].FFlags >> sfHasNoTabs;
			OldLine = (*FList)[Index].FString;
			(*FList)[Index].FString = S;
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
		(*FList)[Index].FFlags = (*FList)[Index].FFlags, (*FList)[Index].FFlags - Synedittextbuffer__6 + ConvertSubset<TSynEditStringFlags>(Value);
}

void __fastcall TSynEditStringList::SetEncoding(TEncoding* const Value)
{
	inherited::SetEncoding(Value);
}

void __fastcall TSynEditStringList::SetTabWidth(int Value)
{
	int I = 0;
	if(Value != FTabWidth)
	{
		int stop = 0;
		FTabWidth = Value;
		FConvertTabsProc = GetBestConvertTabsProcEx(FTabWidth);
		FIndexOfLongestLine = -1;
		for(stop = FCount - 1, I = 0; I <= stop; I++)
		{
			/*# with FList^[I] do */
			{
				
				(*FList)[I].FExpandedLength = -1;
				(*FList)[I].FFlags >> sfHasNoTabs;
				(*FList)[I].FFlags << sfExpandedLengthUnknown;
			}
		}
	}
}

void __fastcall TSynEditStringList::SetTextAndFileFormat(const String Value)
{
	String S;
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
					SetString(S, Start, P - Start);
					InsertItem(FCount, S);
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
	FCharIndexesAreValid = false;
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
	int I = 0;
	int stop = 0;
	FIndexOfLongestLine = -1;
	for(stop = FCount - 1, I = 0; I <= stop; I++)
	{
		/*# with FList^[I] do */
		{
			
			(*FList)[I].FExpandedLength = -1;
			(*FList)[I].FFlags >> sfHasNoTabs;
			(*FList)[I].FFlags << sfExpandedLengthUnknown;
		}
	}
}


}  // namespace SynEditTextBuffer

