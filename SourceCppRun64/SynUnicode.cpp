
#include <vcl.h>
#pragma hdrstop

#include "SynUnicode.h"
#include "SynEditTextBuffer.h"
#include <System.Math.hpp>
#include <System.SysConst.hpp>
#include <System.RTLConsts.hpp>
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedittextbuffer;
using namespace System;
using namespace System::Classes;
using namespace System::Math;
using namespace System::Rtlconsts;
using namespace System::Sysconst;
using namespace System::Sysutils;

namespace Synunicode
{
#define Synunicode__0 (System::Set<Byte, 0, 255>() <<  \
										128 << 129 << 130 << 131 << 132 << 133 <<  \
										134 << 135 << 136 << 137 << 138 << 139 <<  \
										140 << 141 << 142 << 143 << 144 << 145 <<  \
										146 << 147 << 148 << 149 << 150 << 151 <<  \
										152 << 153 << 154 << 155 << 156 << 157 <<  \
										158 << 159 << 160 << 161 << 162 << 163 <<  \
										164 << 165 << 166 << 167 << 168 << 169 <<  \
										170 << 171 << 172 << 173 << 174 << 175 <<  \
										176 << 177 << 178 << 179 << 180 << 181 <<  \
										182 << 183 << 184 << 185 << 186 << 187 <<  \
										188 << 189 << 190 << 191)
#define Synunicode__1 (System::Set<Byte, 0, 255>() <<  \
										160 << 161 << 162 << 163 << 164 << 165 <<  \
										166 << 167 << 168 << 169 << 170 << 171 <<  \
										172 << 173 << 174 << 175 << 176 << 177 <<  \
										178 << 179 << 180 << 181 << 182 << 183 <<  \
										184 << 185 << 186 << 187 << 188 << 189 <<  \
										190 << 191)
#define Synunicode__2 (System::Set<Byte, 0, 255>() <<  \
										128 << 129 << 130 << 131 << 132 << 133 <<  \
										134 << 135 << 136 << 137 << 138 << 139 <<  \
										140 << 141 << 142 << 143 << 144 << 145 <<  \
										146 << 147 << 148 << 149 << 150 << 151 <<  \
										152 << 153 << 154 << 155 << 156 << 157 <<  \
										158 << 159)
#define Synunicode__3 (System::Set<Byte, 0, 255>() <<  \
										144 << 145 << 146 << 147 << 148 << 149 <<  \
										150 << 151 << 152 << 153 << 154 << 155 <<  \
										156 << 157 << 158 << 159 << 160 << 161 <<  \
										162 << 163 << 164 << 165 << 166 << 167 <<  \
										168 << 169 << 170 << 171 << 172 << 173 <<  \
										174 << 175 << 176 << 177 << 178 << 179 <<  \
										180 << 181 << 182 << 183 << 184 << 185 <<  \
										186 << 187 << 188 << 189 << 190 << 191)
#define Synunicode__4 (System::Set<Byte, 0, 255>() <<  \
										128 << 129 << 130 << 131 << 132 << 133 <<  \
										134 << 135 << 136 << 137 << 138 << 139 <<  \
										140 << 141 << 142 << 143)



PWideChar __fastcall SynCharNext(PWideChar P)
{
	PWideChar result = nullptr;
	result = ::CharNext(P);
	return result;
}

PWideChar __fastcall SynCharNext(PWideChar P, String& Element)
{
	Element; //# clear out parameter
	PWideChar result = nullptr;
	PWideChar Start = nullptr;
	Start = P;
	result = ::CharNext(P);
	SetString(Element, Start, result - Start);
	return result;
}

int __fastcall SynUniElementsCount(String S)
{
	int result = 0;
	PWideChar P = nullptr;
	result = 0;
	P = ustr2pwchar(S);
	while((*P) != L'\x00')
	{
		P = ::CharNext(P);
		++result;
	}
	return result;
}

// exchanges in each character of the given string the low order and high order
// byte to go from LSB to MSB and vice versa.
// EAX contains address of string

void __fastcall StrSwapByteOrder(PWideChar Str)
{
	PWORD P = nullptr;
	P = ((PWORD) Str);
	while((*P) != 0)
	{
		(*P) = MAKEWORD(HIBYTE((*P)), LOBYTE((*P)));
		++P;
	}
}

extern "C" __declspec(dllimport) /*# 'gdi32.dll' Name 'TranslateCharsetInfo'*/ BOOL __stdcall TranslateCharsetInfoEx(PDWORD lpSrc, TCharsetInfo& lpCs, DWORD dwFlags);

TFontCharSet __fastcall CharSetFromLocale(LCID Language)
{
	TFontCharSet result = (TFontCharSet) 0;
	unsigned int CP = 0;
	TCharsetInfo CSI = {};
	CP = (unsigned int) CodePageFromLocale(Language);
	TranslateCharsetInfo(((unsigned long*) ((void*) CP)), &CSI, (DWORD) TCI_SRCCODEPAGE);
	result = (TFontCharSet) CSI.ciCharset;
	return result;
}

// determines the code page for a given locale

int __fastcall CodePageFromLocale(LCID Language)
{
	int result = 0;
	Char Buf[7/*# range 0..6*/];
	GetLocaleInfo(Language, (LCTYPE) LOCALE_IDEFAULTANSICODEPAGE, Buf, 6);
	result = StrToIntDef(Buf, (int) GetACP());
	return result;
}

WORD __fastcall KeyboardCodePage()
{
	WORD result = 0;
	//result = (WORD) CodePageFromLocale((LCID) (GetKeyboardLayout(0) & 0xFFFF));
	//https://stackoverflow.com/questions/12379713/cant-get-current-keyboard-layout
	HKL Layout = GetKeyboardLayout(0);
//	DWORD Language = (DWORD)Layout & 0x0000FFFF;
	DWORD Language = static_cast<DWORD>((NativeInt)Layout & 0x0000FFFF);
	result = CodePageFromLocale(Language);;
	return result;
}

TSize __fastcall GetTextSize(HDC DC, PWideChar Str, int Count)
{
	TSize result = {};
	result.cx = 0;
	result.cy = 0;
	{
		GetTextExtentPoint32W(DC, Str, Count, &result);
	}
	return result;
}

bool __fastcall IsAnsiOnly(const String WS)
{
	bool result = false;
	BOOL UsedDefaultChar = false;
	WideCharToMultiByte((UINT) DefaultSystemCodePage, 0, ustr2pwchar(WS), WS.Length(), nullptr, 0, nullptr, &UsedDefaultChar);
	result = !UsedDefaultChar;
	return result;
}

bool __fastcall IsUTF8(const String FileName, bool& WithBOM, int BytesToCheck/*# = 0x4000*/)
{
	WithBOM = false; //# clear out parameter
	bool result = false;
	TStream* Stream = nullptr;
	Stream = new TFileStream(FileName, (WORD) (fmOpenRead | fmShareDenyWrite));
	try
	{
		result = IsUTF8(Stream, WithBOM, BytesToCheck);
	}
	__finally
	{
		delete Stream;
	}
	return result;
}

// checks for a BOM in UTF-8 format or searches the first 4096 bytes for
// typical UTF-8 octet sequences

bool __fastcall IsUTF8(TStream* Stream, bool& WithBOM, int BytesToCheck/*# = 0x4000*/)
{
	WithBOM = false; //# clear out parameter
	bool result = false;
	TBytes Buffer;
	int BufferSize = 0;
	int BomLen = 0;
	TEncoding* Encoding = nullptr;
  // if Stream is nil, let Delphi raise the exception, by accessing Stream,
  // to signal an invalid result

  // start analysis at actual Stream.Position
	BufferSize = (int) Min((__int64) BytesToCheck, Stream->Size - Stream->Position);

  // if no special characteristics are found it is not UTF-8
	result = false;
	WithBOM = false;
	if(BufferSize > 0)
	{
		Buffer.Length = BufferSize;
		Stream->Read(Buffer, 0, BufferSize);
		Stream->Seek(-BufferSize, (WORD) soFromCurrent);

    /* first search for BOM */
		Encoding = nullptr;
		BomLen = TEncoding::GetBufferEncoding(Buffer, Encoding);
		WithBOM = BomLen > 0;
		if(Encoding == TEncoding::UTF8)
			return true;
		else
		{
			if(WithBOM)
				return false;

    /* Now check the content for UTF8 sequences */
		}
		result = IsUTF8(Buffer, 0, BytesToCheck);
	}
	return result;
}

bool __fastcall IsUTF8(const TBytes& Bytes, int Start/*# = 0*/, int BytesToCheck/*# = 0x4000*/)
{
	bool result = false;
	const int MinimumCountOfUTF8Strings = 1;
	int Len = 0;
	int i = 0;
	int FoundUTF8Strings = 0;

  // 3 trailing bytes are the maximum in valid UTF-8 streams,
  // so a count of 4 trailing bytes is enough to detect invalid UTF-8 streams

	auto CountOfTrailingBytes = [&]() -> int 
	{
		int result = 0;
		result = 0;
		++i;
		while((i < Len) && (result < 4))
		{
			if(Synunicode__0.Contains(Bytes[i]))
				++result;
			else
				break;
			++i;
		}
		return result;
	};
   /*  NOTE: There is no 100% save way to detect UTF-8 streams. The bigger
            MinimumCountOfUTF8Strings, the lower is the probability of
            a false positive. On the other hand, a big MinimumCountOfUTF8Strings
            makes it unlikely to detect files with only little usage of non
            US-ASCII chars, like usual in European languages. */
	result = false;
	Len = Min(Start + BytesToCheck, (int) Bytes.Length);
	FoundUTF8Strings = 0;
	i = Start;
	while(i < Len)
	{
		switch(Bytes[i])
		{
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
			 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
			 case 30: case 31: case 32: case 33: case 34: case 35: case 36: case 37: case 38: case 39:
			 case 40: case 41: case 42: case 43: case 44: case 45: case 46: case 47: case 48: case 49:
			 case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57: case 58: case 59:
			 case 60: case 61: case 62: case 63: case 64: case 65: case 66: case 67: case 68: case 69:
			 case 70: case 71: case 72: case 73: case 74: case 75: case 76: case 77: case 78: case 79:
			 case 80: case 81: case 82: case 83: case 84: case 85: case 86: case 87: case 88: case 89:
			 case 90: case 91: case 92: case 93: case 94: case 95: case 96: case 97: case 98: case 99:
			 case 100: case 101: case 102: case 103: case 104: case 105: case 106: case 107: case 108: case 109:
			 case 110: case 111: case 112: case 113: case 114: case 115: case 116: case 117: case 118: case 119:
			 case 120: case 121: case 122: case 123: case 124: case 125: case 126: case 127: // skip US-ASCII characters as they could belong to various charsets
			;
			break;
			case 194: case 195: case 196: case 197: case 198: case 199: case 200: case 201: case 202: case 203:
			 case 204: case 205: case 206: case 207: case 208: case 209: case 210: case 211: case 212: case 213:
			 case 214: case 215: case 216: case 217: case 218: case 219: case 220: case 221: case 222: case 223:
			if(CountOfTrailingBytes() == 1)
				++FoundUTF8Strings;
			else
				goto label0;
			break;
			case 0xE0:
			{
				++i;
				if((i < Len) && (Synunicode__1.Contains(Bytes[i])) && (CountOfTrailingBytes() == 1))
					++FoundUTF8Strings;
				else
					goto label1;
			}
			break;
			case 225: case 226: case 227: case 228: case 229: case 230: case 231: case 232: case 233: case 234:
			 case 235: case 236:
			case 238: case 239:
			if(CountOfTrailingBytes() == 2)
				++FoundUTF8Strings;
			else
				goto label2;
			break;
			case 0xED:
			{
				++i;
				if((i < Len) && (Synunicode__2.Contains(Bytes[i])) && (CountOfTrailingBytes() == 1))
					++FoundUTF8Strings;
				else
					goto label3;
			}
			break;
			case 0xF0:
			{
				++i;
				if((i < Len) && (Synunicode__3.Contains(Bytes[i])) && (CountOfTrailingBytes() == 2))
					++FoundUTF8Strings;
				else
					goto label4;
			}
			break;
			case 241: case 242: case 243:
			if(CountOfTrailingBytes() == 3)
				++FoundUTF8Strings;
			else
				goto label5;
			break;
			case 0xF4:
			{
				++i;
				if((i < Len) && (Synunicode__4.Contains(Bytes[i])) && (CountOfTrailingBytes() == 2))
					++FoundUTF8Strings;
				else
					goto label6;
			}
			break; // invalid UTF-8 bytes
			case 0xC0:
			case 0xC1:
			case 245: case 246: case 247: case 248: case 249: case 250: case 251: case 252: case 253: case 254:
			 case 255:
			goto label7; // trailing bytes are consumed when handling leading bytes,
                   // any occurence of "orphaned" trailing bytes is invalid UTF-8
			case 128: case 129: case 130: case 131: case 132: case 133: case 134: case 135: case 136: case 137:
			 case 138: case 139: case 140: case 141: case 142: case 143: case 144: case 145: case 146: case 147:
			 case 148: case 149: case 150: case 151: case 152: case 153: case 154: case 155: case 156: case 157:
			 case 158: case 159: case 160: case 161: case 162: case 163: case 164: case 165: case 166: case 167:
			 case 168: case 169: case 170: case 171: case 172: case 173: case 174: case 175: case 176: case 177:
			 case 178: case 179: case 180: case 181: case 182: case 183: case 184: case 185: case 186: case 187:
			 case 188: case 189: case 190: case 191:
			goto label8;
			default:
			  ;
			break;
		}
		if(FoundUTF8Strings >= MinimumCountOfUTF8Strings)
		{
			result = true;
			break;
		}
		++i;
	}
	label0:;
	label1:;
	label2:;
	label3:;
	label4:;
	label5:;
	label6:;
	label7:;
	label8:;
	return result;
}

TEncoding* __fastcall GetEncoding(const String FileName, bool& WithBOM)
{
	WithBOM = false; //# clear out parameter
	TEncoding* result = nullptr;
	TStream* Stream = nullptr;
	Stream = new TFileStream(FileName, (WORD) (fmOpenRead | fmShareDenyWrite));
	try
	{
		result = GetEncoding(Stream, WithBOM);
	}
	__finally
	{
		delete Stream;
	}
	return result;
}

TEncoding* __fastcall GetEncoding(TStream* Stream, bool& WithBOM)
{
	WithBOM = false; //# clear out parameter
	TEncoding* result = nullptr;

	auto TBytesEqual = [&](TBytes& A, TBytes& B, int Len) -> bool 
	{
		bool result = false;
		int I = 0;
		int stop = 0;
		result = true;
		for(stop = Len - 1, I = 0; I <= stop; I++)
		{
			if(A[I] != B[I])
				return false;
		}
		return result;
	};
	TBytes Buffer;
	int Size = 0;
	TBytes Preamble;
  // if Stream is nil, let Delphi raise the exception, by accessing Stream,
  // to signal an invalid result

  // start analysis at actual Stream.Position
	Size = (int) (Stream->Size - Stream->Position);

  // if no special characteristics are found it is probably ANSI
	result = TEncoding::ANSI;
	if(IsUTF8(Stream, WithBOM))
		return TEncoding::UTF8;

  /* try to detect UTF-16 by finding a BOM in UTF-16 format */

  // Check for Unicode
	Preamble = TEncoding::Unicode->GetPreamble();
	if(Size >= Preamble.Length)
	{
		Buffer.Length = Preamble.Length;
		Stream->Read(Buffer, 0, (int) Preamble.Length);
		Stream->Seek((int) -Preamble.Length, (WORD) soFromCurrent);
		if(TBytesEqual(Preamble, Buffer, (int) Preamble.Length))
		{
			WithBOM = true;
			return TEncoding::Unicode;
		}
	}
  // Check for BigEndianUnicode
	Preamble = TEncoding::BigEndianUnicode->GetPreamble();
	if(Size >= Preamble.Length)
	{
		Buffer.Length = Preamble.Length;
		Stream->Read(Buffer, 0, (int) Preamble.Length);
		Stream->Seek((int) -Preamble.Length, (WORD) soFromCurrent);
		if(TBytesEqual(Preamble, Buffer, (int) Preamble.Length))
		{
			WithBOM = true;
			return TEncoding::BigEndianUnicode;
		}
	}
	return result;
}

bool __fastcall ClipboardProvidesText()
{
	bool result = false;
	result = IsClipboardFormatAvailable((UINT) CF_UNICODETEXT);
	return result;
}

String __fastcall GetClipboardText()
{
	String result;
	result = Clipboard()->AsText;
	return result;
}

void __fastcall SetClipboardText(const String Text)
{
	Clipboard()->AsText = Text;
}

bool __fastcall IsWideCharMappableToAnsi(WideChar WC)
{
	bool result = false;
	BOOL UsedDefaultChar = false;
	WideCharToMultiByte((UINT) DefaultSystemCodePage, 0, (PWideChar)&WC, 1, nullptr, 0, nullptr, &UsedDefaultChar);
	result = !UsedDefaultChar;
	return result;
}
static bool SynUnicode_Initialized = false;

void SynUnicode_initialization()
{
	if(SynUnicode_Initialized)
		return;
	
	SynUnicode_Initialized = true;
	
	Assert(Win32Platform() == VER_PLATFORM_WIN32_NT, L"Unsupported Windows version");
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynUnicode

