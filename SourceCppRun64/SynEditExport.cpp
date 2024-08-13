#include <vcl.h>
#pragma hdrstop

#include "SynEditExport.h"
#include <System.Math.hpp>
#include "SynEditMiscProcs.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditmiscprocs;
using namespace Syneditstrconst;
using namespace Synedittypes;
using namespace Synunicode;
using namespace System;
using namespace System::Classes;
using namespace System::Math;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Syneditexport
{
#define Syneditexport__0 TFontStyles()
#define Syneditexport__1 TFontStyles()
#define Syneditexport__2 (System::Set<TSynEncoding, TSynEncoding::seUTF8, TSynEncoding::seAnsi>() << seUTF8 << seAnsi)
#define Syneditexport__3 (System::Set<TSynEncoding, TSynEncoding::seUTF8, TSynEncoding::seAnsi>() << seUTF16LE << seUTF16BE)

__fastcall ESynEncoding::ESynEncoding(const String Msg) : inherited(Msg) {}
__fastcall ESynEncoding::ESynEncoding(const String Msg, const TVarRec* Args, int Args_maxidx) : inherited(Msg, Args, Args_maxidx) {}
__fastcall ESynEncoding::ESynEncoding(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Msg, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynEncoding::ESynEncoding(const String Msg, int AHelpContext) : inherited(Msg, AHelpContext) {}
__fastcall ESynEncoding::ESynEncoding(System::NativeUInt Ident) : inherited(Ident) {}
__fastcall ESynEncoding::ESynEncoding(System::PResStringRec ResStringRec) : inherited(ResStringRec) {}
__fastcall ESynEncoding::ESynEncoding(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx) : inherited(Ident, Args, Args_maxidx) {}
__fastcall ESynEncoding::ESynEncoding(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx) : inherited(ResStringRec, Args, Args_maxidx) {}
__fastcall ESynEncoding::ESynEncoding(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(ResStringRec, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynEncoding::ESynEncoding(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Ident, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynEncoding::ESynEncoding(System::NativeUInt Ident, int AHelpContext) : inherited(Ident, AHelpContext) {}
__fastcall ESynEncoding::ESynEncoding(System::PResStringRec ResStringRec, int AHelpContext) : inherited(ResStringRec, AHelpContext) {}



/* TSynCustomExporter */

__fastcall TSynCustomExporter::TSynCustomExporter(TComponent* AOwner)
 : inherited(AOwner),
			FBuffer(new TMemoryStream()),
			FCharSize(1),
			fFirstAttribute(false),
			FStreaming(false),
			FBackgroundColor((TColor) 0),
			FClipboardFormat(0),
			FEncoding(seUTF8),
			fExportAsText(false),
			FFont(nullptr),
			fHighlighter(nullptr),
			fLastBG((TColor) 0),
			fLastFG((TColor) 0),
			fUseBackground(false)
{
	FClipboardFormat = (UINT) CF_TEXT;
	FEncoding = seUTF8;
	FFont = new TFont();
	FBackgroundColor = clWindow;
	AssignFont(nullptr);
	Clear();
	FTitle = SYNS_Untitled;
}

__fastcall TSynCustomExporter::~TSynCustomExporter()
{
	delete FFont;
	delete FBuffer;
	//# inherited::Destroy();
}

void __fastcall TSynCustomExporter::AddData(const String AText)
{
	if(AText != L"")
	{
		WriteString(AText);
		FBuffer->SetSize(FBuffer->Position);
	}
}

void __fastcall TSynCustomExporter::AddDataNewLine(const String AText)
{
	AddData(AText);
	AddNewLine();
}

void __fastcall TSynCustomExporter::AddNewLine()
{
	WriteString(WideCRLF);
	FBuffer->SetSize(FBuffer->Position);
}

void __fastcall TSynCustomExporter::AssignFont(TFont* Value)
{
	if(Value != nullptr)
		FFont->Assign(Value);
	else
	{
		FFont->Name = DefaultFontName();
		FFont->Size = 10;
		FFont->Color = clWindowText;
		FFont->Style = Syneditexport__0;
	}
}

void __fastcall TSynCustomExporter::Clear()
{
	FBuffer->Position = 0;
  // Size is ReadOnly in Delphi 2
	FBuffer->SetSize(0);
	fLastStyle = Syneditexport__1;
	fLastBG = clWindow;
	fLastFG = clWindowText;
}

void __fastcall SetClipboardText(String Text)
{
	HGLOBAL Mem = 0;
	PByte P = nullptr;
	int SLen = 0;
	SLen = Text.Length();
	Clipboard()->Open();
	try
	{
		Clipboard()->Clear();

    // set unicode text, this also works on Win9X, even if the clipboard-viewer
    // can't show it, Word 2000+ can paste it including the unicode only characters
		Mem = GlobalAlloc((UINT) (GMEM_MOVEABLE | GMEM_DDESHARE), (SLen + 1) * sizeof(WideChar));
		if(Mem != 0)
		{
			P = ((unsigned char*) GlobalLock(Mem));
			try
			{
				if(P != nullptr)
				{
					Move(ustr2address(Text), P, (size_t) ((SLen + 1) * sizeof(WideChar)));
					Clipboard()->SetAsHandle((UINT) CF_UNICODETEXT, (THandle) Mem);
				}
			}
			__finally
			{
				GlobalUnlock(Mem);
			}
		}
    // Don't free Mem!  It belongs to the clipboard now, and it will free it
    // when it is done with it.
	}
	__finally
	{
		Clipboard()->Close();
	}
}

void __fastcall TSynCustomExporter::CopyToClipboard()
{
	const unsigned char Nulls[2/*# range 0..1*/] = {0, 0};
	String s;
	if(fExportAsText)
	{
		FBuffer->Position = FBuffer->Size;
		FBuffer->Write(&Nulls, FCharSize);
		switch(Encoding)
		{
			case seUTF16LE:
			s = (wchar_t*) FBuffer->Memory /*# check length*/;
			break;
			case seUTF16BE:
			{
				s = (wchar_t*) FBuffer->Memory /*# check length*/;
				StrSwapByteOrder(ustr2pwchar(s));
			}
			break;
			case TSynEncoding::seUTF8:
// linker error			s = UTF8ToUnicodeString(((const System::PAnsiChar) FBuffer->Memory));
			s = UnicodeString((char*)FBuffer->Memory /*# check length*/);    // todo dme
			break;
			case seAnsi:
			s = UnicodeString((char*)FBuffer->Memory /*# check length*/);
			break;
			default:
			  ;
			break;
		}
		SetClipboardText(s);
	}
	else
	CopyToClipboardFormat(GetClipboardFormat());
}

void __fastcall TSynCustomExporter::CopyToClipboardFormat(UINT AFormat)
{
	THandle hData = 0;
	UINT hDataSize = 0;
	PByte PtrData = nullptr;
	hDataSize = (UINT) (GetBufferSize() + 1);
	hData = (THandle) GlobalAlloc((UINT) (GMEM_MOVEABLE | GMEM_ZEROINIT | GMEM_SHARE), hDataSize);
	if(hData != 0)
		try
		{
			PtrData = ((unsigned char*) GlobalLock((HGLOBAL) hData));
			if(ASSIGNED(PtrData))
			{
				try
				{
					FBuffer->Position = 0;
					FBuffer->Read((void**)PtrData, (TNativeCount) (hDataSize - 1)); // trailing #0
				}
				__finally
				{
					GlobalUnlock((HGLOBAL) hData);
				}
				Clipboard()->SetAsHandle(AFormat, hData);
			}
			else
			Abort();
		}
		catch(...)
		{
			GlobalFree((HGLOBAL) hData);
			OutOfMemoryError();
		}
}

void __fastcall TSynCustomExporter::DefineProperties(TFiler* Filer)
{
	inherited::DefineProperties(Filer);
}

void __fastcall TSynCustomExporter::ExportAll(TStrings* ALines)
{
	ExportRange(ALines, BufferCoord(1, 1), BufferCoord(MaxInt, MaxInt));
}

void __fastcall TSynCustomExporter::ExportRange(TStrings* ALines, const TBufferCoord& cStart, const TBufferCoord& cStop)
{
	TBufferCoord Start = cStart;
	TBufferCoord Stop = cStop;
	int i = 0;
	String Line;
	String Token;
	TSynHighlighterAttributes* Attri = nullptr;
	FStreaming = true;
	try

    // abort if not all necessary conditions are met
	{
		int stop = 0;
		if(!ASSIGNED(ALines) || !ASSIGNED(Highlighter) || (ALines->Count == 0) || (Start.Line > ALines->Count) || (Start.Line > Stop.Line))
			Abort();
		Stop.Line = Max(1, Min(Stop.Line, ALines->Count));
		Stop.Char = Max(1, Min(Stop.Char, ALines->Strings[Stop.Line - 1].Length() + 1));
		Start.Char = Max(1, Min(Start.Char, ALines->Strings[Start.Line - 1].Length() + 1));
		if((Start.Line == Stop.Line) && (Start.Char >= Stop.Char))
			Abort();
    // initialization
		FBuffer->Position = 0;
    // Size is ReadOnly in Delphi 2
		FBuffer->SetSize(Max(0x1000, (Stop.Line - Start.Line) * 128) * FCharSize);
		Highlighter->ResetRange();
    // export all the lines into fBuffer
		fFirstAttribute = true;
		for(stop = Stop.Line, i = Start.Line; i <= stop; i++)
		{
			Line = ALines->Strings[i - 1];
      // order is important, since Start.Y might be equal to Stop.Y
			if(i == Stop.Line)
				Line.Delete(Stop.Char, 	MaxInt);
			if((i == Start.Line) && (Start.Char > 1))
				Line.Delete(1, Start.Char - 1);
      // export the line
			Highlighter->SetLine(Line, i);
			while(!Highlighter->GetEol())
			{
				Attri = Highlighter->GetTokenAttribute();
				if(ASSIGNED(Attri)) // The .pas highlighter, for example, can return a nil Attri above for a trailing EOF/null that was loaded from a stream
				{
					Token = ReplaceReservedChars(Highlighter->GetToken());
					SetTokenAttribute(Attri);
					FormatToken(Token);
				}
				Highlighter->Next();
			}
			FormatNewLine();
		}
		if(!fFirstAttribute)
			FormatAfterLastAttribute();

    // insert header
		insertData(0, GetHeader());
    // add footer
		AddData(GetFooter());
	}
	__finally
	{
		FStreaming = false;
	}
}

void __fastcall TSynCustomExporter::FormatToken(String Token)
{
	AddData(Token);
}

int __fastcall TSynCustomExporter::GetBufferSize()
{
	int result = 0;
	result = (int) FBuffer->Size;
	return result;
}

UINT __fastcall TSynCustomExporter::GetClipboardFormat()
{
	UINT result = 0;
	result = FClipboardFormat;
	return result;
}

String __fastcall TSynCustomExporter::GetFormatName()
{
	String result;
	result = L"";
	return result;
}

void __fastcall TSynCustomExporter::insertData(int APos, const String AText)
{
	int Size = 0;
	int ToMove = 0;
	int SizeNeeded = 0;
	PByte Dest = nullptr;
	Size = StringSize(AText);
	if(Size > 0)
	{
		ToMove = (int) FBuffer->Position;
		SizeNeeded = ToMove + Size;
		if(FBuffer->Size < SizeNeeded)
      // Size is ReadOnly in Delphi 2
			FBuffer->SetSize((SizeNeeded + 0x1800) & ~0xFFF); // increment in pages
		Dest = ((unsigned char*) FBuffer->Memory);
		Dest += Size;
		Move(FBuffer->Memory, Dest, ToMove);
		FBuffer->Position = 0;
		WriteString(AText);
		FBuffer->Position = ToMove + Size;
		FBuffer->SetSize(FBuffer->Position);
	}
}

String __fastcall TSynCustomExporter::ReplaceReservedChars(String AToken)
{
	String result;
	int i = 0;
	int ISrc = 0;
	int IDest = 0;
	int SrcLen = 0;
	int DestLen = 0;
	String Replace;
	WideChar C = L'\0';
	if(AToken != L"")
	{
		SrcLen = AToken.Length();
		ISrc = 1;
		DestLen = SrcLen;
		IDest = 1;
		result.SetLength(DestLen);
		while(ISrc <= SrcLen)
		{
			int stop = 0;
			C = AToken[ISrc];
			Replace = ReplaceReservedChar(C);
			if(Replace != L"")
				++ISrc;
			else
			{
				if(IDest > DestLen)
				{
					DestLen += 32;
					result.SetLength(DestLen);
				}
				result[IDest] = C;
				++ISrc;
				++IDest;
				continue;
			}
			if(IDest + Replace.Length() - 1 > DestLen)
			{
				DestLen += Max(32, IDest + Replace.Length() - DestLen);
				result.SetLength(DestLen);
			}
			for(stop = Replace.Length(), i = 1; i <= stop; i++)
			{
				result[IDest] = Replace[i];
				++IDest;
			}
		}
		result.SetLength(IDest - 1);
	}
	else
	result = L"";
	return result;
}

void __fastcall TSynCustomExporter::SaveToFile(const String FileName)
{
	TStream* Stream = nullptr;
	Stream = new TFileStream(FileName, (WORD) fmCreate);
	try
	{
		SaveToStream(Stream);
	}
	__finally
	{
		delete Stream;
	}
}

void __fastcall TSynCustomExporter::SaveToStream(TStream* Stream)
{
	if(UseBom())
		switch(Encoding)
		{
			case seUTF8:
			Stream->WriteBuffer(UTF8BOM, 3);
			break;
			case seUTF16LE:
			Stream->WriteBuffer(UTF16BOMLE, 2);
			break;
			case seUTF16BE:
			Stream->WriteBuffer(UTF16BOMBE, 2);
			break;
			default:
			  ;
			break;
		}
	FBuffer->Position = 0;
	FBuffer->SaveToStream(Stream);
}

void __fastcall TSynCustomExporter::SetEncoding(TSynEncoding Value)
{

  // don't change encoding while streaming as this could corrupt output data
	if(FStreaming)
		return;
	if(!(SupportedEncodings().Contains(Value)))
		throw new ESynEncoding(SEncodingError, ARRAYOFCONST((EncodingStrs[Value], GetFormatName())));
	FEncoding = Value;
	if(Syneditexport__2.Contains(Value))
		FCharSize = 1;
	else
	{
		if(Syneditexport__3.Contains(Value))
			FCharSize = 2;
	}
}

void __fastcall TSynCustomExporter::SetExportAsText(bool Value)
{
	if(fExportAsText != Value)
	{
		fExportAsText = Value;
		Clear();
	}
}

void __fastcall TSynCustomExporter::SetFont(TFont* Value)
{
	AssignFont(Value);
}

void __fastcall TSynCustomExporter::SetHighlighter(TSynCustomHighlighter* Value)
{
	if(fHighlighter != Value)
	{
		if(fHighlighter != nullptr)
			fHighlighter->FreeNotification(this);
		fHighlighter = Value;
		Clear();
		if(ASSIGNED(fHighlighter) && ASSIGNED(fHighlighter->WhitespaceAttribute) && fUseBackground)
			FBackgroundColor = fHighlighter->WhitespaceAttribute->Background;
	}
}

void __fastcall TSynCustomExporter::SetTitle(const String Value)
{
	if(FTitle != Value)
	{
		if(Value != L"")
			FTitle = Value;
		else
			FTitle = SYNS_Untitled;
	}
}

void __fastcall TSynCustomExporter::SetTokenAttribute(TSynHighlighterAttributes* Attri)
{
	bool ChangedBG = false;
	bool ChangedFG = false;
	TFontStyles ChangedStyles;

	auto ValidatedColor = [&](TColor AColor, TColor ADefColor) -> TColor 
	{
		TColor result = (TColor) 0;
		if(AColor == clNone)
			result = (TColor) ColorToRGB(ADefColor);
		else
			result = (TColor) ColorToRGB(AColor);
		return result;
	};
	if(fFirstAttribute)
	{
		fFirstAttribute = false;
		fLastBG = ValidatedColor(Attri->Background, FBackgroundColor);
		fLastFG = ValidatedColor(Attri->Foreground, FFont->Color);
		fLastStyle = Attri->Style;
		FormatBeforeFirstAttribute(UseBackground && (fLastBG != FBackgroundColor), fLastFG != FFont->Color, Attri->Style);
	}
	else
	{
		ChangedBG = UseBackground && (fLastBG != ValidatedColor(Attri->Background, FBackgroundColor));
		ChangedFG = (fLastFG != ValidatedColor(Attri->Foreground, FFont->Color));
    // which font style bits are to be reset?
		ChangedStyles = fLastStyle - Attri->Style;
		if(ChangedBG || ChangedFG || (fLastStyle != Attri->Style))
		{
			FormatAttributeDone(ChangedBG, ChangedFG, ChangedStyles);
      // which font style bits are to be set?
			ChangedStyles = Attri->Style - fLastStyle;
			fLastBG = ValidatedColor(Attri->Background, FBackgroundColor);
			fLastFG = ValidatedColor(Attri->Foreground, FFont->Color);
			fLastStyle = Attri->Style;
			FormatAttributeInit(ChangedBG, ChangedFG, ChangedStyles);
		}
	}
}

void __fastcall TSynCustomExporter::SetUseBackground(bool Value)
{
	fUseBackground = Value;
	if(ASSIGNED(fHighlighter) && ASSIGNED(fHighlighter->WhitespaceAttribute) && fUseBackground)
		FBackgroundColor = fHighlighter->WhitespaceAttribute->Background;
}

int __fastcall TSynCustomExporter::StringSize(const String AText)
{
	int result = 0;
	switch(Encoding)
	{
		case seUTF8:
		result = UTF8Encode(AText).Length();
		break;
		case seUTF16LE:
		case seUTF16BE:
		result = AText.Length();
		break;
		case seAnsi:
		result = AnsiString(AText).Length();
		break;
		default:
		result = AText.Length();
		break;
	}
	result = result * FCharSize;
	return result;
}

void __fastcall TSynCustomExporter::WriteString(const String AText)
{
	UTF8String UTF8Str;
	AnsiString AnsiStr;
	switch(Encoding)
	{
		case seUTF8:
		{
			UTF8Str = UTF8Encode(AText);
			FBuffer->WriteBuffer(astr2pchar(UTF8Str, 1 - 1), UTF8Str.Length());
		}
		break;
		case seUTF16LE:
		FBuffer->WriteBuffer(ustr2pwchar(AText, 1 - 1), (NativeInt) (AText.Length() * sizeof(WideChar)));
		break;
		case seUTF16BE:
		{
			StrSwapByteOrder(ustr2pwchar(AText));
			FBuffer->WriteBuffer(ustr2pwchar(AText, 1 - 1), (NativeInt) (AText.Length() * sizeof(WideChar)));
		}
		break;
		case seAnsi:
		{
			AnsiStr = AnsiString(AText.c_str());
			FBuffer->WriteBuffer(astr2pchar(AnsiStr, 1 - 1), AnsiStr.Length());
		}
		break;
		default:
		  ;
		break;
	}
}


}  // namespace SynEditExport

