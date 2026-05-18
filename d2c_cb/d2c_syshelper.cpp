#include <vcl.h>
#pragma hdrstop

#include "d2c_syshelper.h"
#include <System.SysConst.hpp>
//#include <System.SysUtils.hpp>
#include "d2c_convert.h"
#include "d2c_openarray.h"
//---------------------------------------------------------------------------
/*$ZEROBASEDSTRINGS ON*/

namespace System {
enum TRuntimeError {reNone,
										reOutOfMemory,
										reInvalidPtr,
										reDivByZero,
										reRangeError,
										reIntOverflow,
										reInvalidOp,
										reZeroDivide,
										reOverflow,
										reUnderflow,
										reInvalidCast,
										reAccessViolation,
										rePrivInstruction,
										reControlBreak,
										reStackOverflow,
										reVarTypeCast,
										reVarInvalidOp,
										reVarDispatch,
										reVarArrayCreate,
										reVarNotArray,
										reVarArrayBounds,
										reAssertionFailed,
										reExternalException,
										reIntfCastError,
										reSafeCallError,
										reMonitorNotLocked,
										reNoMonitorSupport,
										rePlatformNotImplemented,
										reObjectDisposed };

// in 23.2 twice void Error(TRuntimeError errorCode)  => linker error  ?
void RError(TRuntimeError errorCode)
{
	throw Sysutils::Exception("");
}

} // namespace system


namespace d2c_system {

#define Stringlist__0 (System::Set<int, 0, 255>() << coIgnoreCase)
#define Stringlist__1 System::Set<int, 0, 255>()
#define Stringlist__2 (System::Set<TCompareOption, TCompareOption::coLingIgnoreCase, TCompareOption::coStringSort>() << TStringSplitOptions::ExcludeEmpty << TStringSplitOptions::ExcludeLastEmpty)
PChar ustr2pwchar(const String& xs, int xiIndex = 0)
{
	return xs.c_str() + xiIndex;
}

void __fastcall ConvertErrorFmt(System::ResourceString* ResString, const TVarRec* Args, int Args_maxidx)
{
	throw EConvertError(ResString, Args, Args_maxidx);
}

void __fastcall ConvertErrorFmt(const String& ResString, const TVarRec* Args, int Args_maxidx)
{
	throw EConvertError(ResString, Args, Args_maxidx);
}

template <typename T>
void Val(const String& S, T* V, int& Code)
{
	std::wistringstream iss(S.c_str());
  iss >> *V;
  Code = 0;
}


//int zbc = 1; // dme zero base correction

/*$ZEROBASEDSTRINGS ON*/

/*static */const String& TStringHelper::Empty = L"";
/*static */const float TSingleHelper::Epsilon = 1.4012984643248170709e-45F;
/*static */const float TSingleHelper::MaxValue = 340282346638528859811704183484516925440.0F;
/*static */const float TSingleHelper::MinValue = -340282346638528859811704183484516925440.0;
/*static */const float TSingleHelper::PositiveInfinity = 1.0F / 0.0F;
/*static */const float TSingleHelper::NegativeInfinity = -1.0F / 0.0F;
/*static */const float TSingleHelper::NaN = 0.0F / 0.0F;
/*static */const double TDoubleHelper::Epsilon = 4.9406564584124654418e-324;
/*static */const double TDoubleHelper::MaxValue = 1.7976931348623157081e+308;
/*static */const double TDoubleHelper::MinValue = -1.7976931348623157081e+308;
/*static */const double TDoubleHelper::PositiveInfinity = 1.0 / 0.0;
/*static */const double TDoubleHelper::NegativeInfinity = -1.0 / 0.0;
/*static */const double TDoubleHelper::NaN = 0.0 / 0.0;
/*static */const long double TExtendedHelper::Epsilon = 4.9406564584124654418e-324L;
/*static */const long double TExtendedHelper::MaxValue = 1.7976931348623157081e+308L;
/*static */const long double TExtendedHelper::MinValue = -1.7976931348623157081e+308;
/*static */const long double TExtendedHelper::PositiveInfinity = 1.0L / 0.0L;
/*static */const long double TExtendedHelper::NegativeInfinity = -1.0L / 0.0L;
/*static */const long double TExtendedHelper::NaN = 0.0L / 0.0L;
/*static */const int TByteHelper::MaxValue = 255;
/*static */const int TByteHelper::MinValue = 0;
/*static */const int TShortIntHelper::MaxValue = 127;
/*static */const int TShortIntHelper::MinValue = -128;
/*static */const int TWordHelper::MaxValue = 65535;
/*static */const int TWordHelper::MinValue = 0;
/*static */const int TSmallIntHelper::MaxValue = 32767;
/*static */const int TSmallIntHelper::MinValue = -32768;
/*static */const int TCardinalHelper::MaxValue = std::numeric_limits<unsigned int>::max(); // 4294967295;
/*static */const int TCardinalHelper::MinValue = 0;
/*static */const int TIntegerHelper::MaxValue = 2147483647;
/*static */const int TIntegerHelper::MinValue = -2147483648;
/*static */const unsigned __int64 TUInt64Helper::MaxValue = std::numeric_limits<unsigned __int64>::max(); //18446744073709551615;
/*static */const unsigned __int64 TUInt64Helper::MinValue = 0;
/*static */const __int64 TInt64Helper::MaxValue = std::numeric_limits<__int64>::max(); //9223372036854775807;
/*static */const __int64 TInt64Helper::MinValue = std::numeric_limits<__int64>::min(); //-9223372036854775808;
/*static */const NativeUInt TNativeUIntHelper::MaxValue = 4294967295;
/*static */const NativeUInt TNativeUIntHelper::MinValue = 0;
/*static */const NativeInt TNativeIntHelper::MaxValue = 2147483647;
/*static */const NativeInt TNativeIntHelper::MinValue = -2147483648;


/*$ZEROBASEDSTRINGS ON*/

Char __fastcall TStringHelper::GetChars(int Index) const
{
  Char result = L'\0';
  result = m_Helped[Index + 1];
  return result;
}

int __fastcall TStringHelper::GetLength() const
{
  int result = 0;
  result = m_Helped.Length();
  return result;
}

String __fastcall TStringHelper::Substring(int StartIndex) const
{
  return m_Helped.SubString(StartIndex + 1, m_Helped.Length() - StartIndex);
}

String __fastcall TStringHelper::Substring(int StartIndex, int Length) const
{
  String result;
  result = m_Helped.SubString(StartIndex + 1, Length);
  return result;
}
/*$ZEROBASEDSTRINGS OFF*/


/*$ZEROBASEDSTRINGS ON*/

/*#static*/
bool __fastcall TStringHelper::CharInArray(Char C, const Char* InArray, int InArray_maxidx)
{
    for (int i = 0; i <= InArray_maxidx; ++i)
      if (InArray[i] == C) return true;
    return false;
}

/*#static*/
int __fastcall TStringHelper::Compare(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length)
{
  int result = 0;
  result = Compare(StrA, IndexA, StrB, IndexB, Length, false, SysLocale.DefaultLCID);
  return result;
}

/*#static*/
int __fastcall TStringHelper::Compare(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length, TLocaleID LocaleID)
{
  int result = 0;
  result = Compare(StrA, IndexA, StrB, IndexB, Length, false, LocaleID);
  return result;
}

/*#static*/
int __fastcall TStringHelper::Compare(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length, bool IgnoreCase)
{
  int result = 0;
  result = Compare(StrA, IndexA, StrB, IndexB, Length, IgnoreCase, SysLocale.DefaultLCID);
  return result;
}

/*#static*/
int __fastcall TStringHelper::InternalCompare(const String& StrA, int IndexA, const String& StrB, int IndexB, int LengthA, int LengthB, bool IgnoreCase, TLocaleID LocaleID)
{
  int result = 0;
  if(IgnoreCase)
    result = InternalCompare(StrA, IndexA, StrB, IndexB, LengthA, LengthB, (TCompareOptions() << coIgnoreCase), LocaleID);
  else
    result = InternalCompare(StrA, IndexA, StrB, IndexB, LengthA, LengthB, TCompareOptions(), LocaleID);
  return result;
}

//  TCompareOption = (coLingIgnoreCase,
//    coLingIgnoreDiacritic, coIgnoreCase, coIgnoreKanatype,
//    coIgnoreNonSpace, coIgnoreSymbols, coIgnoreWidth,
//    coLingCasing, coDigitAsNumbers, coStringSort);

/*#static*/
LongWord __fastcall TStringHelper::InternalMapOptionsToFlags(TCompareOptions AOptions)
{
  LongWord result = 0;
  const LongWord MapFlags[10/*# TCompareOption*/] = {(LongWord) LINGUISTIC_IGNORECASE, (LongWord) LINGUISTIC_IGNOREDIACRITIC, (LongWord) NORM_IGNORECASE, (LongWord) NORM_IGNOREKANATYPE, (LongWord) NORM_IGNORENONSPACE, (LongWord) NORM_IGNORESYMBOLS, (LongWord) NORM_IGNOREWIDTH, (LongWord) NORM_LINGUISTIC_CASING, (LongWord) SORT_DIGITSASNUMBERS, (LongWord) SORT_STRINGSORT};
  TCompareOption option = coLingIgnoreCase;
  int stop = 0;
  result = 0;
  for(stop = (TCompareOption) (TCompareOption) 9 /*# High(TCompareOption) */, option = (TCompareOption) (TCompareOption) 0 /*# Low(TCompareOption) */; option <= stop; Inc(option))
  {
    if(AOptions.Contains(option))
    {
      if(((option != coLingIgnoreCase) || TOSVersion::Check(6, 0)) && ((option != coDigitAsNumbers) || TOSVersion::Check(6, 1)))
      // The first option is not supported until Windows Vista, the second option is not supported until Windows 7
        result = result | MapFlags[option];
    }
  }
  return result;
}

/*#static*/
int __fastcall TStringHelper::InternalCompare(const String& StrA, int IndexA, const String& StrB, int IndexB, int LengthA, int LengthB, TCompareOptions Options, TLocaleID LocaleID)
{
  if ((StrA.Length() == 0) || (StrB.Length() == 0))
  {
    if (StrA.Length() > 0) return 1;
    if (StrB.Length() > 0) return -1;
    return 0;
  }

  const DWORD Flags = InternalMapOptionsToFlags(Options);

  // IndexA/IndexB are 0-based (ZEROBASEDSTRINGS ON),
  // ustr2pwchar expects a 0-based offset -> NO "-1" here.
  const int cmp = ::CompareStringW(
    LocaleID,
    Flags,
    ustr2pwchar(StrA, IndexA), LengthA,
    ustr2pwchar(StrB, IndexB), LengthB);

  if (cmp == 0)
    System::Sysutils::RaiseLastOSError();

  return cmp - CSTR_EQUAL;
}

/*#static*/
int __fastcall TStringHelper::Compare(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length, bool IgnoreCase, TLocaleID LocaleID)
{
  int result = 0;
  result = InternalCompare(StrA, IndexA, StrB, IndexB, Length, Length, IgnoreCase, LocaleID);
  return result;
}

/*#static*/
int __fastcall TStringHelper::Compare(const String& StrA, const String& StrB, bool IgnoreCase)
{
  int result = 0;
  result = InternalCompare(StrA, 0, StrB, 0, (int) StrA.Length(), (int) StrB.Length(), IgnoreCase, SysLocale.DefaultLCID);
  return result;
}

/*#static*/
int __fastcall TStringHelper::Compare(const String& StrA, const String& StrB, bool IgnoreCase, TLocaleID LocaleID)
{
  int result = 0;
  result = InternalCompare(StrA, 0, StrB, 0, (int) StrA.Length(), (int) StrB.Length(), IgnoreCase, LocaleID);
  return result;
}

/*#static*/
int __fastcall TStringHelper::Compare(const String& StrA, const String& StrB, TCompareOptions Options, TLocaleID LocaleID)
{
  int result = 0;
  result = InternalCompare(StrA, 0, StrB, 0, (int) StrA.Length(), (int) StrB.Length(), Options, LocaleID);
  return result;
}

/*#static*/
int __fastcall TStringHelper::Compare(const String& StrA, const String& StrB, TCompareOptions Options)
{
  int result = 0;
  result = InternalCompare(StrA, 0, StrB, 0, (int) StrA.Length(), (int) StrB.Length(), Options, SysLocale.DefaultLCID);
  return result;
}

/*#static*/
int __fastcall TStringHelper::Compare(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length, TCompareOptions Options, TLocaleID LocaleID)
{
  int result = 0;
  result = InternalCompare(StrA, IndexA, StrB, IndexB, Length, Length, Options, LocaleID);
  return result;
}

/*#static*/
int __fastcall TStringHelper::Compare(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length, TCompareOptions Options)
{
  int result = 0;
  result = InternalCompare(StrA, IndexA, StrB, IndexB, Length, Length, Options, SysLocale.DefaultLCID);
  return result;
}

/*#static*/
int __fastcall TStringHelper::Compare(const String& StrA, const String& StrB)
{
  int result = 0;
  result = InternalCompare(StrA, 0, StrB, 0, (int) StrA.Length(), (int) StrB.Length(), TCompareOptions(), SysLocale.DefaultLCID);
  return result;
}

/*#static*/
int __fastcall TStringHelper::Compare(const String& StrA, const String& StrB, TLocaleID LocaleID)
{
  int result = 0;
  result = InternalCompare(StrA, 0, StrB, 0, (int) StrA.Length(), (int) StrB.Length(), TCompareOptions(), LocaleID);
  return result;
}

/*#static*/
int __fastcall TStringHelper::CompareOrdinal(const String& StrA, const String& StrB)
{
  int result = 0;
  int MaxLen = 0;
  if(StrA.Length() > StrB.Length())
    MaxLen = (int) StrA.Length();
  else
    MaxLen = (int) StrB.Length();
  //result = System::Sysutils::StrLComp(ustr2pwchar(StrA, 0 - 1), ustr2pwchar(StrB, 0 - 1), MaxLen);
  result = System::Sysutils::StrLComp(StrA.c_str(), StrB.c_str(), MaxLen);
  return result;
}

/*#static*/
int __fastcall TStringHelper::CompareOrdinal(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length)
{
  int result = 0;
  result = System::Sysutils::StrLComp(ustr2pwchar(StrA, IndexA - 1), ustr2pwchar(StrB, IndexB - 1), Length);
  return result;
}

/*#static*/
int __fastcall TStringHelper::CompareText(const String& StrA, const String& StrB)
{
  int result = 0;
  result = System::Sysutils::CompareText(StrA, StrB);
  return result;
}

/*#static*/
bool __fastcall TStringHelper::ToBoolean(const String& S)
{
  bool result = false;
  result = StrToBool(S);
  return result;
}

/*#static*/
int __fastcall TStringHelper::ToInteger(const String& S)
{
  int result = 0;
  result = TIntegerHelper::Parse(S);
  return result;
}

/*#static*/
__int64 __fastcall TStringHelper::ToInt64(const String& S)
{
  __int64 result = 0;
  result = TInt64Helper::Parse(S);
  return result;
}

/*#static*/
float __fastcall TStringHelper::ToSingle(const String& S)
{
  float result = 0.0F;
  result = TSingleHelper::Parse(S);
  return result;
}

/*#static*/
double __fastcall TStringHelper::ToDouble(const String& S)
{
  double result = 0.0;
  result = TDoubleHelper::Parse(S);
  return result;
}

/*#static*/
long double __fastcall TStringHelper::ToExtended(const String& S)
{
  long double result = 0.0L;
  result = TExtendedHelper::Parse(S);
  return result;
}

/*#static*/
String __fastcall TStringHelper::Parse(int Value)
{
  String result;
  result = IntToStr(Value);
  return result;
}

/*#static*/
String __fastcall TStringHelper::Parse(__int64 Value)
{
  String result;
  result = IntToStr(Value);
  return result;
}

/*#static*/
String __fastcall TStringHelper::Parse(bool Value)
{
  String result;
  result = BoolToStr(Value);
  return result;
}

/*#static*/
String __fastcall TStringHelper::Parse(long double Value)
{
  String result;
  result = FloatToStr(Value);
  return result;
}

/*#static*/
String __fastcall TStringHelper::LowerCase(const String& S)
{
  String result;
  result = System::Sysutils::LowerCase(S);
  return result;
}

/*#static*/
String __fastcall TStringHelper::LowerCase(const String& S, TLocaleOptions LocaleOptions)
{
  String result;
  result = System::Sysutils::LowerCase(S, LocaleOptions);
  return result;
}

/*#static*/
String __fastcall TStringHelper::UpperCase(const String& S)
{
  String result;
  result = System::Sysutils::UpperCase(S);
  return result;
}

/*#static*/
String __fastcall TStringHelper::UpperCase(const String& S, TLocaleOptions LocaleOptions)
{
  String result;
  result = System::Sysutils::UpperCase(S, LocaleOptions);
  return result;
}

int __fastcall TStringHelper::CompareTo(const String& strB) const
{
  int result = 0;
  result = System::Sysutils::StrComp(ustr2pwchar(m_Helped), ustr2pwchar(strB));
  return result;
}

bool __fastcall TStringHelper::Contains(const String& Value) const
{
  bool result = false;
  result = System::Pos(Value, m_Helped) > 0;
  return result;
}

/*#static*/
String __fastcall TStringHelper::Copy(const String& Str)
{
  String result;
  result = Str.SubString(1, Str.Length());
  return result;
}

void __fastcall TStringHelper::CopyTo(int SourceIndex, OpenArrayRef<Char> destination, int DestinationIndex, int Count) const
{
//  System::Move((ustr2pwchar(m_Helped) + SourceIndex), destination.data(), (size_t) (Count * sizeof(Char)));
  System::Move( ustr2pwchar(m_Helped, SourceIndex), destination.data() + DestinationIndex, (size_t)(Count * sizeof(Char)));
}

int __fastcall TStringHelper::CountChar(Char C) const
{
  int result = 0;
  const int L = m_Helped.Length();
  const Char* p = ustr2pwchar(m_Helped); // 0-based pointer

  for (int i = 0; i < L; ++i)
    if (p[i] == C)
      ++result;

  return result;
}

/*#static*/
String __fastcall TStringHelper::Create(Char C, int Count)
{
  String result;
  result = StringOfChar(C, Count);
  return result;
}

/*#static*/
String __fastcall TStringHelper::Create(const Char* Value, int Value_maxidx, int StartIndex, int Length)
{
  String result;
  result.SetLength(Length);
  Move(Value + StartIndex, ustr2address(result), Length * sizeof(Char));
  return result;
}

/*#static*/
String __fastcall TStringHelper::Create(const Char* Value, int Value_maxidx)
{
  String result;
  result.SetLength((Value_maxidx + 1));
  Move(Value, ustr2address(result), (Value_maxidx + 1) * sizeof(Char));
  return result;
}

String __fastcall TStringHelper::DeQuotedString(Char QuoteChar) const
{
  const int L = m_Helped.Length();
  if (L < 2)
    return m_Helped;

  const Char* p = ustr2pwchar(m_Helped); // 0-based
  if (p[0] != QuoteChar || p[L - 1] != QuoteChar)
    return m_Helped;

  D2CArray<Char> Buf;
  Buf.Length = L - 2; // maximum possible
  int outPos = 0;
  bool lastQuoted = false;

  // scan between the outer quotes: indices 1 .. L-2
  for (int i = 1; i <= L - 2; ++i)
  {
    const Char ch = p[i];

    if (ch == QuoteChar)
    {
      if (lastQuoted)
      {
        // doubled quote -> emit one
        Buf[outPos++] = ch;
        lastQuoted = false;
      }
      else
      {
        // first quote of a potential doubled quote
        lastQuoted = true;
      }
    }
    else
    {
      // normal char
      if (lastQuoted)
      {
        // quote was not doubled -> Delphi keeps char, quote effectively removed
        lastQuoted = false;
      }
      Buf[outPos++] = ch;
    }
  }

  // create string from Buf[0..outPos-1]
  // IMPORTANT: your Create(Value, StartIndex, Length) must use Value + StartIndex
  return TStringHelper::Create(DynamicArrayPointer(Buf), Buf.High, 0, outPos);
}

String __fastcall TStringHelper::DeQuotedString() const
{
  String result;
  result = this->DeQuotedString(L'\'');
  return result;
}

/*#static*/
bool __fastcall TStringHelper::EndsText(const String& ASubText, const String& AText)
{
  bool result = false;
  result = TStringHelper(AText).EndsWith(ASubText, true);
  return result;
}

bool __fastcall TStringHelper::EndsWith(const String& Value) const
{
  bool result = false;
  result = EndsWith(Value, false);
  return result;
}

bool __fastcall TStringHelper::EndsWith(const String& Value, bool IgnoreCase) const
{
  if (Value == Empty)
    return true;

  const int subPos0 = m_Helped.Length() - Value.Length(); // 0-based position
  if (subPos0 < 0)
    return false;

  // ByteType is 1-based -> check at (subPos0 + 1)
  if (System::Sysutils::ByteType(m_Helped, subPos0 + 1) == System::Sysutils::mbLeadByte)
    return false;

  TCompareOptions opts;
  if (IgnoreCase)
    opts = (TCompareOptions() << coIgnoreCase);
  else
    opts = TCompareOptions();

  return TStringHelper::Compare(Value, 0, m_Helped, subPos0, (int)Value.Length(), opts) == 0;
}

/*#static*/
bool __fastcall TStringHelper::Equals(const String& a, const String& b)
{
  bool result = false;
  result = a == b;
  return result;
}

bool __fastcall TStringHelper::Equals(const String& Value) const
{
  bool result = false;
  result = m_Helped == Value;
  return result;
}

/*#static*/
String __fastcall TStringHelper::Format(const String& Format, const TVarRec* args, int args_maxidx)
{
  String result;
  result = System::Sysutils::Format(Format, args, args_maxidx);
  return result;
}

int __fastcall TStringHelper::IndexOf(Char Value, int StartIndex, int Count) const
{
  int result = 0;
  //result = System::PosChar(Value, m_Helped, StartIndex + 1) - 1;
  result = System::Pos(Value, m_Helped, StartIndex + 1) - 1;
  if((result + 1) > (StartIndex + Count))
    result = -1;
  return result;
}

int __fastcall TStringHelper::IndexOf(const String& Value, int StartIndex, int Count) const
{
  int result = 0;
  result = System::Pos(Value, m_Helped, StartIndex + 1) - 1;
  if((result + Value.Length()) > (StartIndex + Count))
    result = -1;
  return result;
}

int __fastcall TStringHelper::IndexOf(const String& Value, int StartIndex) const
{
  int result = 0;
  result = System::Pos(Value, m_Helped, StartIndex + 1) - 1;
  return result;
}

int __fastcall TStringHelper::IndexOf(const String& Value) const
{
  int result = 0;
  result = System::Pos(Value, m_Helped) - 1;
  return result;
}

int __fastcall TStringHelper::IndexOf(Char Value) const
{
  int result = 0;
  PChar P = nullptr;
  int I = 0;
  int stop = 0;
  P = ustr2pwchar(m_Helped);
  for(stop = m_Helped.Length() - 1, I = 0; I <= stop; I++)
  {
    if(P[I] == Value)
      return I;
  }
  result = -1;
  return result;
}

int __fastcall TStringHelper::IndexOf(Char Value, int StartIndex) const
{
  int result = 0;
  PChar P = nullptr;
  int I = 0;
  P = ustr2pwchar(m_Helped);
  if(StartIndex >= 0)
  {
    int stop = 0;
    for(stop = m_Helped.Length() - 1, I = StartIndex; I <= stop; I++)
    {
      if(P[I] == Value)
        return I;
    }
  }
  result = -1;
  return result;
}

int __fastcall TStringHelper::IndexOfAny(const Char* AnyOf, int AnyOf_maxidx, int StartIndex, int Count) const
{
  const int L = m_Helped.Length();
  int Max = StartIndex + Count;
  if (Max > L) Max = L;
  if (StartIndex < 0) StartIndex = 0;
  if (StartIndex >= Max) return -1;

  const Char* P = ustr2pwchar(m_Helped); // 0-based

  for (int i = StartIndex; i < Max; ++i)
  {
    const Char ch = P[i];
    for (int j = 0; j <= AnyOf_maxidx; ++j)
    {
      if (ch == AnyOf[j])
        return i;
    }
  }
  return -1;
}

int __fastcall TStringHelper::IndexOfAny(const Char* AnyOf, int AnyOf_maxidx, int StartIndex) const
{
  int result = 0;
  result = IndexOfAny(AnyOf, AnyOf_maxidx, StartIndex, (int) m_Helped.Length());
  return result;
}

int __fastcall TStringHelper::IndexOfAny(const Char* AnyOf, int AnyOf_maxidx)  const
{
  int result = 0;
  result = IndexOfAny(AnyOf, AnyOf_maxidx, 0, (int) m_Helped.Length());
  return result;
}

int __fastcall TStringHelper::IndexOfAnyUnquoted(const Char* AnyOf, int AnyOf_maxidx, Char StartQuote, Char EndQuote) const
{
  int result = 0;
  result = IndexOfAnyUnquoted(AnyOf, AnyOf_maxidx, StartQuote, EndQuote, 0, (int) m_Helped.Length());
  return result;
}

int __fastcall TStringHelper::IndexOfAnyUnquoted(const Char* AnyOf, int AnyOf_maxidx, Char StartQuote, Char EndQuote, int StartIndex) const
{
  int result = 0;
  result = IndexOfAnyUnquoted(AnyOf, AnyOf_maxidx, StartQuote, EndQuote, StartIndex, (int) m_Helped.Length());
  return result;
}

int __fastcall TStringHelper::IndexOfAnyUnquoted(const Char* AnyOf, int AnyOf_maxidx, Char StartQuote, Char EndQuote, int StartIndex, int Count) const
{
  const int L = m_Helped.Length();
  int Max = StartIndex + Count;
  if (Max > L) Max = L;
  if (StartIndex < 0) StartIndex = 0;
  if (StartIndex >= Max) return -1;

  const Char* P = ustr2pwchar(m_Helped); // 0-based

  if (StartQuote != EndQuote)
  {
    int inQuote = 0;
    for (int i = StartIndex; i < Max; ++i)
    {
      const Char ch = P[i];

      if (ch == StartQuote) ++inQuote;
      else if (ch == EndQuote && inQuote > 0) --inQuote;

      if (inQuote == 0)
      {
        for (int j = 0; j <= AnyOf_maxidx; ++j)
          if (ch == AnyOf[j]) return i;
      }
    }
  }
  else
  {
    bool inQuote = false;
    for (int i = StartIndex; i < Max; ++i)
    {
      const Char ch = P[i];
      if (ch == StartQuote) inQuote = !inQuote;

      if (!inQuote)
      {
        for (int j = 0; j <= AnyOf_maxidx; ++j)
          if (ch == AnyOf[j]) return i;
      }
    }
  }

  return -1;
}

String __fastcall TStringHelper::Insert(int StartIndex, const String& Value) const
{
  String Result = m_Helped;            // copy Self
  ::Insert(Value, Result, StartIndex + 1);  // Delphi Insert is 1-based
  return Result;
}

bool __fastcall TStringHelper::IsDelimiter(const String& Delimiters, int Index) const
{
  bool result = false;
  result = false;
  if((Index < 1 /*# Low(string)*/) || (Index > High(m_Helped)) || (ByteType(m_Helped, Index) != mbSingleByte))
    return result;
  result = StrScan(ustr2pwchar(Delimiters), m_Helped[Index]) != nullptr;
  return result;
}

bool __fastcall TStringHelper::IsEmpty() const
{
  bool result = false;
  result = m_Helped == Empty;
  return result;
}

/*#static*/
bool __fastcall TStringHelper::IsNullOrEmpty(const String& Value)
{
  bool result = false;
  result = Value == Empty;
  return result;
}

/*#static*/
bool __fastcall TStringHelper::IsNullOrWhiteSpace(const String& Value)
{
  bool result = false;
  result = TStringHelper(Value).Trim().Length() == 0;
  return result;
}

/*#static*/
String __fastcall TStringHelper::Join(const String& Separator, const String* Values, int Values_maxidx)
{
  String result;
  result = Join(Separator, Values, Values_maxidx, 0, (Values_maxidx + 1));
  return result;
}

/*#static*/
String __fastcall TStringHelper::Join(const String& Separator, const System::_di_IEnumerable__1<String>& Values)
{
  if (Values)
  {
    // explizit generischen Enumerator holen
    System::_di_IEnumerator__1<String> Enum = Values->GetEnumeratorT();
    return Join(Separator, Enum);
  }

  return String();
}

/*#static*/
String __fastcall TStringHelper::Join(const String& Separator, const System::_di_IEnumerator__1<String>& Values)
{
  if (Values && Values->MoveNext())
  {
    String Result = Values->Current;

    while (Values->MoveNext())
    {
      Result = Result + Separator + Values->Current;
    }

    return Result;
  }

  return String();
}



/*#static*/
String __fastcall TStringHelper::Join(const String& Separator, const String* Values, int Values_maxidx, int StartIndex, int Count)
{
  const int Len = Values_maxidx + 1;

  if (Count == 0)
    return String();

  if (Len == 0)
    return String();

  if (Count < 0 || StartIndex < 0 || StartIndex >= Len)
    throw ERangeError(System_Sysconst_SRangeError);

  int Max = StartIndex + Count;
  if (Max > Len)
    Max = Len;

  String Result = Values[StartIndex];
  for (int i = StartIndex + 1; i < Max; ++i)
  {
    Result = Result + Separator + Values[i];
  }

  return Result;
}

static String __fastcall VarRecToString(const TVarRec& val)
{
  switch (val.VType)
  {
    case vtInteger:       return IntToStr(val.VInteger);
    case vtBoolean:       return BoolToStr(val.VBoolean, true);
    case vtChar:          return String((Char)val.VChar);
    case vtPChar:         return UnicodeString(val.VPChar);
    case vtExtended:      return FloatToStr(*val.VExtended);
    case vtObject:        return (val.VObject != nullptr) ? val.VObject->ClassName() : String();
    case vtClass:         return (val.VClass != nullptr) ? val.VClass->ClassName() : String();
    case vtCurrency:      return CurrToStr(*val.VCurrency);
    case vtInt64:         return IntToStr(*val.VInt64);

    case vtUnicodeString:
      // In C++Builder, VUnicodeString typically points to UnicodeString data.
      // The safe way is to dereference as a UnicodeString pointer.
      return *reinterpret_cast<const UnicodeString*>(val.VUnicodeString);

    default:
      return Format(L"(Unknown): %d", ARRAYOFCONST((val.VType)));
  }
}

/*#static*/
String __fastcall TStringHelper::Join(const String& Separator, const TVarRec* Values, int Values_maxidx)
{
  const int Len = Values_maxidx + 1;
  if (Len <= 0)
    return String();

  String Result = VarRecToString(Values[0]);
  for (int i = 1; i < Len; ++i)
  {
    Result = Result + Separator + VarRecToString(Values[i]);
  }
  return Result;
}

int __fastcall TStringHelper::LastIndexOf(const String& Value, int StartIndex) const
{
  int result = 0;
  result = LastIndexOf(Value, StartIndex, StartIndex + 1);
  return result;
}

int __fastcall TStringHelper::LastIndexOf(Char Value, int StartIndex) const
{
  int result = 0;
  result = LastIndexOf(Value, StartIndex, StartIndex + 1);
  return result;
}

int __fastcall TStringHelper::LastIndexOf(Char Value) const
{
  const int Len = (int)m_Helped.Length();
  if (Len == 0)
    return -1;

  return LastIndexOf(Value, Len - 1, Len);
}

int __fastcall TStringHelper::LastIndexOf(const String& Value) const
{
  int result = 0;
  result = LastIndexOf(Value, (int) (m_Helped.Length() - 1), (int) m_Helped.Length());
  return result;
}

int __fastcall TStringHelper::LastDelimiter(const String& Delims) const
{
  const int L = m_Helped.Length();
  if (L == 0 || Delims.IsEmpty())
    return -1;

  const Char* s = ustr2pwchar(m_Helped);  // 0-based
  const Char* d = ustr2pwchar(Delims);    // 0-based
  const int DL = Delims.Length();

  for (int i = L - 1; i >= 0; --i)
  {
    const Char ch = s[i];
    for (int j = 0; j < DL; ++j)
      if (ch == d[j])
        return i; // 0-based
  }

  return -1;
}

int __fastcall TStringHelper::LastDelimiter(const TSysCharSet Delims) const
{
  int result = 0;
  PChar PSt = nullptr;
  PChar P = nullptr;
  PSt = ustr2pwchar(m_Helped);
  if(PSt != nullptr)
  {
    P = PSt + m_Helped.Length() - 1;
    while(P >= PSt)
    {
      if(Delims.Contains((*P)))
        return P - PSt;
      --P;
    }
  }
  result = -1;
  return result;
}

int __fastcall TStringHelper::LastIndexOf(const String& Value, int StartIndex, int Count) const
{
  const int VLen = (int)Value.Length();
  if (VLen == 0)
    return -1;

  const int Len = (int)m_Helped.Length();
  if (Len == 0)
    return -1;

  if (Count <= 0)
    return -1;

  if (StartIndex < 0)
    return -1;

  if (StartIndex >= Len)
    StartIndex = Len - 1;

  // Wenn das Suchwort länger ist als der String, unmöglich
  if (VLen > Len)
    return -1;

  // Startposition für Vergleich: höchstens so, dass Value noch reinpasst
  int I = StartIndex - VLen + 1;
  if (I > Len - VLen)
    I = Len - VLen;

  // Untere Grenze entsprechend Count (Count Zeichen rückwärts inkl. StartIndex)
  int Min = StartIndex - Count + 1;
  if (Min < 0)
    Min = 0;

  if (I < Min)
    return -1;

  const Char* S = ustr2pwchar(m_Helped); // 0-based
  const Char* V = ustr2pwchar(Value);    // 0-based

  while (I >= Min)
  {
    // Vergleiche VLen Zeichen ab S+I mit V
    if (System::Sysutils::StrLComp(S + I, V, (unsigned int)VLen) == 0)
      return I;
    --I;
  }

  return -1;
}

int __fastcall TStringHelper::LastIndexOf(Char Value, int StartIndex, int Count) const
{
   const int Len = (int)m_Helped.Length();
  if (Len == 0)
    return -1;

  if (Count <= 0 || StartIndex < 0)
    return -1;

  if (StartIndex >= Len)
    StartIndex = Len - 1;

  int I = StartIndex;
  int Min = StartIndex - Count + 1;
  if (Min < 0) Min = 0;

  const Char* P = ustr2pwchar(m_Helped); // 0-based
  while (I >= Min)
  {
    if (P[I] == Value)
      return I;
    --I;
  }
  return -1;
}

int __fastcall TStringHelper::LastIndexOfAny(const Char* AnyOf, int AnyOf_maxidx) const
{
  int result = 0;
  result = LastIndexOfAny(AnyOf, AnyOf_maxidx, (int) (m_Helped.Length() - 1), (int) m_Helped.Length());
  return result;
}

int __fastcall TStringHelper::LastIndexOfAny(const Char* AnyOf, int AnyOf_maxidx, int StartIndex, int Count) const
{
  if (m_Helped.Length() == 0)
    return -1;

  int I = (StartIndex < m_Helped.Length()) ? StartIndex : (m_Helped.Length() - 1);
  const int Min = ((StartIndex - Count) < 0) ? 0 : (StartIndex - Count + 1);

  const Char* P = ustr2pwchar(m_Helped); // 0-based
  while (I >= Min)
  {
    const Char ch = P[I];
    for (int j = 0; j <= AnyOf_maxidx; ++j)
      if (ch == AnyOf[j])
        return I;
    --I;
  }

  return -1;
}

int __fastcall TStringHelper::LastIndexOfAny(const Char* AnyOf, int AnyOf_maxidx, int StartIndex) const
{
  int result = 0;
  result = LastIndexOfAny(AnyOf, AnyOf_maxidx, StartIndex, (int) m_Helped.Length());
  return result;
}

String __fastcall TStringHelper::PadLeft(int TotalWidth, Char PaddingChar) const
{
  String result;
  TotalWidth = (int) (TotalWidth - m_Helped.Length());
  if(TotalWidth > 0)
    result = System::StringOfChar(PaddingChar, TotalWidth) + m_Helped;
  else
    result = m_Helped;
  return result;
}

String __fastcall TStringHelper::PadLeft(int TotalWidth) const
{
  String result;
  result = PadLeft(TotalWidth, L' ');
  return result;
}

String __fastcall TStringHelper::PadRight(int TotalWidth, Char PaddingChar) const
{
  String result;
  TotalWidth = (int) (TotalWidth - m_Helped.Length());
  if(TotalWidth > 0)
    result = m_Helped + System::StringOfChar(PaddingChar, TotalWidth);
  else
    result = m_Helped;
  return result;
}

String __fastcall TStringHelper::PadRight(int TotalWidth) const
{
  String result;
  result = PadRight(TotalWidth, L' ');
  return result;
}

String __fastcall TStringHelper::QuotedString(Char QuoteChar) const
{
  String Result = m_Helped; // oder Substring(0)

  const Char* p = ustr2pwchar(Result); // 0-based view (valid until Result changes)

  // Wir müssen rückwärts laufen, aber p wird ungültig sobald Result sich ändert.
  // Daher: pro Iteration Zeichen über Helper/Chars oder SubString-Index holen.
  for (int i = Result.Length() - 1; i >= 0; --i)
  {
    if (TStringHelper(Result).GetChars(i) == QuoteChar) // oder TStringHelper(Result).Chars[i]
    {
      Result = TStringHelper(Result).Insert(i, String(QuoteChar));
    }
  }

  return String(QuoteChar) + Result + String(QuoteChar);
}

String __fastcall TStringHelper::QuotedString() const
{
  return QuotedString(L'\'');
}

String __fastcall TStringHelper::Remove(int StartIndex, int Count) const
{
  String Result = m_Helped;
  if (Count <= 0)
    return Result;          // Delphi: bei Count <= 0 effektiv keine Änderung

  Result.Delete(StartIndex + 1, Count);
  return Result;
}

String __fastcall TStringHelper::Remove(int StartIndex) const
{
  String result;
  result = m_Helped;
  result.Delete(StartIndex + 1,  result.Length());
  return result;
}

String __fastcall TStringHelper::Replace(Char OldChar, Char NewChar) const
{
  String result;
  result = System::Sysutils::StringReplace(m_Helped, String(OldChar), String(NewChar), (TReplaceFlags() << rfReplaceAll));
  return result;
}

String __fastcall TStringHelper::Replace(Char OldChar, Char NewChar, TReplaceFlags ReplaceFlags) const
{
  String result;
  result = System::Sysutils::StringReplace(m_Helped, OldChar, NewChar, ReplaceFlags);
  return result;
}

String __fastcall TStringHelper::Replace(const String& OldValue, const String& NewValue)  const
{
  String result;
  result = System::Sysutils::StringReplace(m_Helped, OldValue, NewValue, (TReplaceFlags() << rfReplaceAll));
  return result;
}

String __fastcall TStringHelper::Replace(const String& OldValue, const String& NewValue, TReplaceFlags ReplaceFlags) const
{
  String result;
  result = System::Sysutils::StringReplace(m_Helped, OldValue, NewValue, ReplaceFlags);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const Char* Separator, int Separator_maxidx, TStringSplitOptions Options) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, MaxInt, Options);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const Char* Separator, int Separator_maxidx, int Count) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, Count, TStringSplitOptions::None);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const Char* Separator, int Separator_maxidx) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, MaxInt, TStringSplitOptions::None);
  return result;
}

int __fastcall TStringHelper::IndexOfAny(const String* Values, int Values_maxidx, int& Index, int StartIndex) const
{
  int result = 0;
  int C = 0;
  int P = 0;
  int IoA = 0;
  int stop = 0;
  IoA = -1;
  for(stop = Values_maxidx /*# High(Values) */, C = 0; C <= stop; C++)
  {
    P = IndexOf(Values[C], StartIndex);
    if((P >= 0) && ((P < IoA) || (IoA == -1)))
    {
      IoA = P;
      Index = C;
    }
  }
  result = IoA;
  return result;
}

int __fastcall TStringHelper::IndexOfAnyUnquoted(const String* Values, int Values_maxidx, Char StartQuote, Char EndQuote, int& Index, int StartIndex) const
{
  int result = 0;
  int C = 0;
  int P = 0;
  int IoA = 0;
  int stop = 0;
  IoA = -1;
  for(stop = Values_maxidx /*# High(Values) */, C = 0; C <= stop; C++)
  {
    P = IndexOfQuoted(Values[C], StartQuote, EndQuote, StartIndex);
    if((P >= 0) && ((P < IoA) || (IoA == -1)))
    {
      IoA = P;
      Index = C;
    }
  }
  result = IoA;
  return result;
}

int __fastcall Posx(const UnicodeString& SubStr, const UnicodeString& Str, int Offset)
{
  // Returns: 1-based position (Delphi Pos semantics), or 0 if not found.
  // Offset is 0-based start index into Str.

  const int SubLen = SubStr.Length();
  const int StrLen = Str.Length();

  if (SubLen <= 0)
    return 0;

  if (Offset < 0)
    Offset = 0;

  if (Offset > StrLen)
    return 0;

  // Number of possible start positions (count), 0 means none
  const int IterCnt = StrLen - Offset - SubLen + 1;
  if (IterCnt <= 0)
    return 0;

  const PWideChar pSub = ustr2pwchar(SubStr); // 0-based
  const PWideChar pStr = ustr2pwchar(Str);    // 0-based
  const PWideChar p = pStr + Offset;

  for (int i = 0; i < IterCnt; ++i)
  {
    int j = 0;
    while (j < SubLen && p[i + j] == pSub[j])
      ++j;

    if (j == SubLen)
      return (Offset + i) + 1; // convert 0-based index -> 1-based position
  }

  return 0;
}


int __fastcall TStringHelper::IndexOfQuoted(const String& Value, Char StartQuote, Char EndQuote, int StartIndex) const
{
  const int SubLen = (int)Value.Length();
  const int StrLen = (int)m_Helped.Length();

  if (SubLen <= 0)
    return -1;

  if (StartIndex < 0)
    StartIndex = 0;

  if (StartIndex > StrLen - SubLen)
    return -1;

  const Char* sub = ustr2pwchar(Value);     // 0-based
  const Char* s   = ustr2pwchar(m_Helped);  // 0-based

  // Quote state while scanning
  int  depth = 0;
  bool inQuote = false;

  // Initialize quote state up to StartIndex (so StartIndex respects existing quotes)
  if (StartIndex > 0)
  {
    if (StartQuote != EndQuote)
    {
      for (int k = 0; k < StartIndex; ++k)
      {
        const Char ch = s[k];
        if (ch == StartQuote) ++depth;
        else if (ch == EndQuote && depth > 0) --depth;
      }
    }
    else
    {
      for (int k = 0; k < StartIndex; ++k)
        if (s[k] == StartQuote) inQuote = !inQuote;
    }
  }

  const int lastStart = StrLen - SubLen;

  for (int i = StartIndex; i <= lastStart; ++i)
  {
    // Update quote state for position i (based on char at i-1)
    // (We already pre-scanned up to StartIndex, so for i==StartIndex nothing to do.)
    if (i > StartIndex)
    {
      const Char prev = s[i - 1];
      if (StartQuote != EndQuote)
      {
        if (prev == StartQuote) ++depth;
        else if (prev == EndQuote && depth > 0) --depth;
      }
      else
      {
        if (prev == StartQuote) inQuote = !inQuote;
      }
    }

    const bool currentlyInQuote = (StartQuote != EndQuote) ? (depth > 0) : inQuote;
    if (currentlyInQuote)
      continue;

    // Try to match Value at position i, but reject if the match touches quote chars
    bool match = true;

    if (StartQuote != EndQuote)
    {
      int localDepth = 0;
      for (int j = 0; j < SubLen; ++j)
      {
        const Char ch = s[i + j];

        // If the candidate window contains quote delimiters, reject it
        if (ch == StartQuote) { match = false; break; }
        if (ch == EndQuote)   { match = false; break; }

        if (ch != sub[j]) { match = false; break; }

        // localDepth stays 0 because we reject quote chars above,
        // kept here to make the intent explicit.
        (void)localDepth;
      }
    }
    else
    {
      for (int j = 0; j < SubLen; ++j)
      {
        const Char ch = s[i + j];

        // Same quote char toggles: reject if it appears in the window
        if (ch == StartQuote) { match = false; break; }

        if (ch != sub[j]) { match = false; break; }
      }
    }

    if (match)
      return i;
  }

  return -1;
}

D2CArray<String> __fastcall TStringHelper::InternalSplit(TSplitKind SplitType, const Char* SeparatorC, int SeparatorC_maxidx, const String* SeparatorS, int SeparatorS_maxidx, Char QuoteStart, Char QuoteEnd, int Count, TStringSplitOptions Options) const
{
  D2CArray<String> Result;

  const int DeltaGrow = 32;

  if (IsEmpty())
    return D2CArray<String>();

  if (Count <= 0)
    return D2CArray<String>();

  // Options
    System::Set<TStringSplitOptions,
                TStringSplitOptions::None,
                TStringSplitOptions::ExcludeLastEmpty> OptSet;

    OptSet << Options;

    const bool ExcludeEmpty =
      OptSet.Contains(TStringSplitOptions::ExcludeEmpty);

    const bool ExcludeLastEmpty =
      OptSet.Contains(TStringSplitOptions::ExcludeLastEmpty);

  int NextSeparator   = -1; // 0-based
  int LastIndex       = 0;  // 0-based start of current segment
  int L               = 0;  // segment length
  int Total           = 0;  // number of segments added
  int CurrentLength   = 0;  // allocated length
  int SeparatorIndex  = 0;  // which separator matched (for string-separators)

  // Find first separator
  switch (SplitType)
  {
    case TSplitKind::StringSeparatorsNoQuoted:
    case TSplitKind::StringSeparatorNoQuoted:
    {
      if (SeparatorS_maxidx == 0)
      {
        SplitType = TSplitKind::StringSeparatorNoQuoted;
        NextSeparator = IndexOf(SeparatorS[0], LastIndex);
      }
      else
      {
        NextSeparator = IndexOfAny(SeparatorS, SeparatorS_maxidx, SeparatorIndex, LastIndex);
      }
    }
    break;

    case TSplitKind::StringSeparatorsQuoted:
    {
      NextSeparator = IndexOfAnyUnquoted(SeparatorS, SeparatorS_maxidx, QuoteStart, QuoteEnd, SeparatorIndex, LastIndex);
    }
    break;

    case TSplitKind::CharSeparatorsNoQuoted:
    case TSplitKind::CharSeparatorNoQuoted:
    {
      if (SeparatorC_maxidx == 0)
      {
        SplitType = TSplitKind::CharSeparatorNoQuoted;
        NextSeparator = IndexOf(SeparatorC[0], LastIndex);
      }
      else
      {
        NextSeparator = IndexOfAny(SeparatorC, SeparatorC_maxidx, LastIndex);
      }
    }
    break;

    case TSplitKind::CharSeparatorsQuoted:
    {
      NextSeparator = IndexOfAnyUnquoted(SeparatorC, SeparatorC_maxidx, QuoteStart, QuoteEnd, LastIndex);
    }
    break;

    default:
      NextSeparator = -1;
    break;
  }

  // Main loop
  while ((NextSeparator >= 0) && (Total < Count))
  {
    L = NextSeparator - LastIndex; // length of token (0..)
    if ((L > 0) || !ExcludeEmpty)
    {
      ++Total;

      if (CurrentLength < Total)
      {
        CurrentLength = Total + DeltaGrow;
        Result.Length = CurrentLength;
      }

      // SubString is 1-based: LastIndex(0-based) -> +1
      Result[Total - 1] = m_Helped.SubString(LastIndex + 1, L);
    }

    // Advance past separator and find next
    switch (SplitType)
    {
      case TSplitKind::StringSeparatorsNoQuoted:
      {
        LastIndex = NextSeparator + (int)SeparatorS[SeparatorIndex].Length();
        NextSeparator = IndexOfAny(SeparatorS, SeparatorS_maxidx, SeparatorIndex, LastIndex);
      }
      break;

      case TSplitKind::StringSeparatorsQuoted:
      {
        LastIndex = NextSeparator + (int)SeparatorS[SeparatorIndex].Length();
        NextSeparator = IndexOfAnyUnquoted(SeparatorS, SeparatorS_maxidx, QuoteStart, QuoteEnd, SeparatorIndex, LastIndex);
      }
      break;

      case TSplitKind::StringSeparatorNoQuoted:
      {
        LastIndex = NextSeparator + (int)SeparatorS[0].Length();
        NextSeparator = IndexOf(SeparatorS[0], LastIndex);
      }
      break;

      case TSplitKind::CharSeparatorsNoQuoted:
      {
        LastIndex = NextSeparator + 1;
        NextSeparator = IndexOfAny(SeparatorC, SeparatorC_maxidx, LastIndex);
      }
      break;

      case TSplitKind::CharSeparatorsQuoted:
      {
        LastIndex = NextSeparator + 1;
        NextSeparator = IndexOfAnyUnquoted(SeparatorC, SeparatorC_maxidx, QuoteStart, QuoteEnd, LastIndex);
      }
      break;

      case TSplitKind::CharSeparatorNoQuoted:
      {
        LastIndex = NextSeparator + 1;
        NextSeparator = IndexOf(SeparatorC[0], LastIndex);
      }
      break;

      default:
        NextSeparator = -1;
      break;
    }
  }

  // Add tail
  L = (int)m_Helped.Length() - LastIndex; // can be 0
  if ((L >= 0) && (Total < Count))
  {
    const bool TailIsEmpty = (L == 0);

    // Add last segment unless excluded by options
    if (!TailIsEmpty || (!ExcludeEmpty && !ExcludeLastEmpty))
    {
      ++Total;
      Result.Length = Total;
      Result[Total - 1] = m_Helped.SubString(LastIndex + 1, L);
    }
    else
    {
      Result.Length = Total;
    }
  }
  else
  {
    Result.Length = Total;
  }

  return Result;
}

D2CArray<String> __fastcall TStringHelper::Split(const String* Separator, int Separator_maxidx, int Count, TStringSplitOptions Options) const
{
  D2CArray<String> result;
  result = InternalSplit(TSplitKind::StringSeparatorsNoQuoted, nullptr, -1, Separator, Separator_maxidx, ((Char) 0), ((Char) 0), Count, Options);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const String* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd, int Count, TStringSplitOptions Options)  const
{
  D2CArray<String> result;
  result = InternalSplit(TSplitKind::StringSeparatorsQuoted, nullptr, -1, Separator, Separator_maxidx, QuoteStart, QuoteEnd, Count, Options);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const Char* Separator, int Separator_maxidx, int Count, TStringSplitOptions Options) const
{
  D2CArray<String> result;
  result = InternalSplit(TSplitKind::CharSeparatorsNoQuoted, Separator, Separator_maxidx, nullptr, -1, ((Char) 0), ((Char) 0), Count, Options);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const Char* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd, int Count, TStringSplitOptions Options) const
{
  D2CArray<String> result;
  result = InternalSplit(TSplitKind::CharSeparatorsQuoted, Separator, Separator_maxidx, nullptr, -1, QuoteStart, QuoteEnd, Count, Options);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const Char* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, QuoteStart, QuoteEnd, MaxInt, TStringSplitOptions::None);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const Char* Separator, int Separator_maxidx, Char Quote) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, Quote, Quote, MaxInt, TStringSplitOptions::None);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const Char* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd, int Count)  const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, QuoteStart, QuoteEnd, Count, TStringSplitOptions::None);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const Char* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd, TStringSplitOptions Options) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, QuoteStart, QuoteEnd, MaxInt, Options);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const String* Separator, int Separator_maxidx) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, MaxInt, TStringSplitOptions::None);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const String* Separator, int Separator_maxidx, int Count) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, Count, TStringSplitOptions::None);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const String* Separator, int Separator_maxidx, TStringSplitOptions Options) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, MaxInt, Options);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const String* Separator, int Separator_maxidx, Char Quote) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, Quote, Quote, MaxInt, TStringSplitOptions::None);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const String* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, QuoteStart, QuoteEnd, MaxInt, TStringSplitOptions::None);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const String* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd, TStringSplitOptions Options) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, QuoteStart, QuoteEnd, MaxInt, Options);
  return result;
}

D2CArray<String> __fastcall TStringHelper::Split(const String* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd, int Count) const
{
  D2CArray<String> result;
  result = Split(Separator, Separator_maxidx, QuoteStart, QuoteEnd, Count, TStringSplitOptions::None);
  return result;
}

/*#static*/
bool __fastcall TStringHelper::StartsText(const String& ASubText, const String& AText)
{
  bool result = false;
  int LSubLen = 0;
  LSubLen = (int) ASubText.Length();
  if(LSubLen == 0)
    result = true;
  else
  {
    if(AText.Length() >= LSubLen)
      result = AnsiStrLIComp(ustr2pwchar(ASubText), ustr2pwchar(AText), LSubLen) == 0;
    else
      result = false;
  }
  return result;
}

bool __fastcall TStringHelper::StartsWith(const String& Value) const
{
  bool result = false;
  result = StartsWith(Value, false);
  return result;
}

bool __fastcall TStringHelper::StartsWith(const String& Value, bool IgnoreCase) const
{
  bool result = false;
  int LValLen = 0;
  LValLen = (int) Value.Length();
  if(LValLen == 0)
    result = true;
  else
  {
    if(IgnoreCase)
      result = StartsText(Value, m_Helped);
    else
    {
      if(m_Helped.Length() >= LValLen)
        result = CompareMem(ustr2address(Value), ustr2address(m_Helped), LValLen * sizeof(Char));
      else
        result = false;
    }
  }
  return result;
}

bool __fastcall TStringHelper::ToBoolean() const
{
  bool result = false;
  result = StrToBool(m_Helped);
  return result;
}

int __fastcall TStringHelper::ToInteger() const
{
  int result = 0;
  result = TIntegerHelper::Parse(m_Helped);
  return result;
}

__int64 __fastcall TStringHelper::ToInt64() const
{
  __int64 result = 0;
  result = TInt64Helper::Parse(m_Helped);
  return result;
}

float __fastcall TStringHelper::ToSingle() const
{
  float result = 0.0F;
  result = TSingleHelper::Parse(m_Helped);
  return result;
}

double __fastcall TStringHelper::ToDouble() const
{
  double result = 0.0;
  result = TDoubleHelper::Parse(m_Helped);
  return result;
}

long double __fastcall TStringHelper::ToExtended() const
{
  long double result = 0.0L;
  result = TExtendedHelper::Parse(m_Helped);
  return result;
}

D2CArray<Char> __fastcall TStringHelper::ToCharArray() const
{
  D2CArray<Char> result;
  result = ToCharArray(0, (int) m_Helped.Length());
  return result;
}

D2CArray<Char> __fastcall TStringHelper::ToCharArray(int StartIndex, int Length) const
{
  D2CArray<Char> result;
  result.Length = Length;
  Move((ustr2pwchar(m_Helped) + StartIndex), DynamicArrayPointer(result, 0), (size_t) (Length * sizeof(Char)));
  return result;
}

String __fastcall TStringHelper::ToLower() const
{
  String result;
  result = ToLower(SysLocale.DefaultLCID);
  return result;
}

String __fastcall TStringHelper::ToLower(TLocaleID LocaleID) const
{
  String result;
  result = m_Helped;
  if(result != L"")
  {
    UniqueString(result);
    if(LCMapString(LocaleID, LCMAP_LOWERCASE | LCMAP_LINGUISTIC_CASING, ustr2pwchar(m_Helped), m_Helped.Length(), ustr2pwchar(result), result.Length()) == 0)
      RaiseLastOSError();
  }
  return result;
}

String __fastcall TStringHelper::ToLowerInvariant() const
{
  String result;
  LCID MapLocale;
  result = m_Helped;
  if(result != L"")
  {
    UniqueString(result);
    if (System::Sysutils::TOSVersion::Check(5, 1))
      MapLocale = LOCALE_INVARIANT;
    else
      MapLocale = LOCALE_SYSTEM_DEFAULT;
    if(LCMapString(MapLocale, LCMAP_LOWERCASE, ustr2pwchar(m_Helped), m_Helped.Length(), ustr2pwchar(result), result.Length()) == 0) /*or LCMAP_LINGUISTIC_CASING*/
      RaiseLastOSError();
  }
  return result;
}

String __fastcall TStringHelper::ToUpper() const
{
  String result;
  result = ToUpper(SysLocale.DefaultLCID);
  return result;
}

String __fastcall TStringHelper::ToUpper(TLocaleID LocaleID) const
{
  String result;
  result = m_Helped;
  if(result != L"")
  {
    UniqueString(result);
    if(LCMapString(LocaleID, LCMAP_UPPERCASE | LCMAP_LINGUISTIC_CASING, ustr2pwchar(m_Helped), m_Helped.Length(), ustr2pwchar(result), result.Length()) == 0)
      RaiseLastOSError();
  }
  return result;
}

String __fastcall TStringHelper::ToUpperInvariant() const
{
  String result;
  LCID MapLocale;
  result = m_Helped;
  if(result != L"")
  {
    UniqueString(result);
    if (System::Sysutils::TOSVersion::Check(5, 1))
      MapLocale = LOCALE_INVARIANT;
    else
      MapLocale = LOCALE_SYSTEM_DEFAULT;
    if(LCMapString(MapLocale, LCMAP_UPPERCASE, ustr2pwchar(m_Helped), m_Helped.Length(), ustr2pwchar(result), result.Length()) == 0) /*or LCMAP_LINGUISTIC_CASING*/
      RaiseLastOSError();
  }
  return result;
}

int __fastcall TStringHelper::GetHashCode() const
{
  UInt32 h = 0;
  const int L = m_Helped.Length();
  const Char* p = ustr2pwchar(m_Helped); // 0-based

  for (int i = 0; i < L; ++i)
  {
    h = (UInt32)((h << 5) | (h >> 27)); // ROL 5
    h ^= (UInt32)p[i];
  }
  return (Int32)h;
}

String __fastcall TStringHelper::Trim() const
{
  const int Len = m_Helped.Length();
  if (Len == 0)
    return m_Helped;

  const Char* p = ustr2pwchar(m_Helped);
  int i = 0;
  int j = Len - 1;

  if (p[i] > L' ' && p[j] > L' ')
    return m_Helped;

  while (i <= j && p[i] <= L' ') ++i;
  if (i > j) return String();

  while (p[j] <= L' ') --j;

  return Substring(i, j - i + 1);
}

String __fastcall TStringHelper::TrimLeft() const
{
  const int Len = m_Helped.Length();
  const Char* p = ustr2pwchar(m_Helped);
  int i = 0;
  while (i < Len && p[i] <= L' ') ++i;
  return (i > 0) ? Substring(i) : m_Helped;
}

String __fastcall TStringHelper::TrimRight() const
{
  const int Len = m_Helped.Length();
  if (Len == 0) return m_Helped;

  const Char* p = ustr2pwchar(m_Helped);
  int j = Len - 1;

  if (p[j] > L' ')
    return m_Helped;

  while (j >= 0 && p[j] <= L' ') --j;
  return Substring(0, j + 1);
}

String __fastcall TStringHelper::Trim(const Char* TrimChars, int TrimChars_maxidx) const
{
  const int Len = m_Helped.Length();
  if (Len == 0)
    return m_Helped;

  const Char* p = ustr2pwchar(m_Helped); // 0-based

  int i = 0;
  int j = Len - 1;

  // Fast path: nothing to trim at both ends
  if (!CharInArray(p[i], TrimChars, TrimChars_maxidx) &&
      !CharInArray(p[j], TrimChars, TrimChars_maxidx))
    return m_Helped;

  while (i <= j && CharInArray(p[i], TrimChars, TrimChars_maxidx))
    ++i;

  if (i > j)
    return String(); // all trimmed

  while (j >= i && CharInArray(p[j], TrimChars, TrimChars_maxidx))
    --j;

  return Substring(i, j - i + 1);
}

String __fastcall TStringHelper::TrimLeft(const Char* TrimChars, int TrimChars_maxidx) const
{
  const int Len = m_Helped.Length();
  if (Len == 0)
    return m_Helped;

  const Char* p = ustr2pwchar(m_Helped); // 0-based

  int i = 0;
  while (i < Len && CharInArray(p[i], TrimChars, TrimChars_maxidx))
    ++i;

  return (i > 0) ? Substring(i) : m_Helped;
}

String __fastcall TStringHelper::TrimRight(const Char* TrimChars, int TrimChars_maxidx) const
{
  const int Len = m_Helped.Length();
  if (Len == 0) return m_Helped;

  const Char* p = ustr2pwchar(m_Helped);
  int j = Len - 1;

  if (!CharInArray(p[j], TrimChars, TrimChars_maxidx))
    return m_Helped;

  while (j >= 0 && CharInArray(p[j], TrimChars, TrimChars_maxidx))
    --j;

  return Substring(0, j + 1);
}

String __fastcall TStringHelper::TrimEnd(const Char* TrimChars, int TrimChars_maxidx) const
{
  String result;
  result = this->TrimRight(TrimChars, TrimChars_maxidx);
  return result;
}

String __fastcall TStringHelper::TrimStart(const Char* TrimChars, int TrimChars_maxidx) const
{
  String result;
  result = this->TrimLeft(TrimChars, TrimChars_maxidx);
  return result;
} 
/*$ZEROBASEDSTRINGS OFF*/ // Desktop platforms use One-based string


/* TSingleHelper */

/*#static*/ String __fastcall TSingleHelper::ToString(const float Value)
{
  String result;
  result = FloatToStr(Value);
  return result;
}

/*#static*/ String __fastcall TSingleHelper::ToString(const float Value, const TFormatSettings& AFormatSettings)
{
  String result;
  result = FloatToStr(Value, AFormatSettings);
  return result;
}

/*#static*/ String __fastcall TSingleHelper::ToString(const float Value, const TFloatFormat Format, const int Precision, const int Digits)
{
  String result;
  result = FloatToStrF(Value, Format, Precision, Digits);
  return result;
}

/*#static*/ String __fastcall TSingleHelper::ToString(const float Value, const TFloatFormat Format, const int Precision, const int Digits, const TFormatSettings& AFormatSettings)
{
  String result;
  result = FloatToStrF(Value, Format, Precision, Digits, AFormatSettings);
  return result;
}

/*#static*/ float __fastcall TSingleHelper::Parse(const String& s)
{
	float result = 0.0F;
	if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidFloat2, ARRAYOFCONST((s, String(L"Single"))));
  return result;
}

/*#static*/ float __fastcall TSingleHelper::Parse(const String& s, const TFormatSettings& AFormatSettings)
{
	float result = 0.0F;
	if(!TryParse(s, result, AFormatSettings))
		ConvertErrorFmt(System_Sysconst_SInvalidFloat2, ARRAYOFCONST((s, L"Single")));
  return result;
}

/*#static*/ bool __fastcall TSingleHelper::TryParse(const String& s, float& Value)
{
  bool result = false;
  long double e = 0.0L;
	result = TryStrToFloat(s, e);
  result = result && (TSingleHelper::MinValue <= e) && (e <= TSingleHelper::MaxValue);
  if(result)
    Value = (float) e;
  return result;
}

/*#static*/ bool __fastcall TSingleHelper::TryParse(const String& s, float& Value, const TFormatSettings& AFormatSettings)
{
  bool result = false;
  long double e = 0.0L;
  result = TryStrToFloat(s, e, AFormatSettings);
  result = result && (TSingleHelper::MinValue <= e) && (e <= TSingleHelper::MaxValue);
  if(result)
    Value = (float) e;
  return result;
}

/*#static*/ bool __fastcall TSingleHelper::IsNan(const float Value)
{
  bool result = false;
  result = (TSingleHelper(Value).SpecialType() == TFloatSpecial::fsNaN);
  return result;
}

/*#static*/ bool __fastcall TSingleHelper::IsInfinity(const float Value)
{
  bool result = false;
  TFloatSpecial FloatType = fsZero;
  FloatType = TSingleHelper(Value).SpecialType();
  result = (FloatType == fsInf) || (FloatType == fsNInf);
  return result;
}

/*#static*/ bool __fastcall TSingleHelper::IsNegativeInfinity(const float Value)
{
  bool result = false;
  result = (TSingleHelper(Value).SpecialType() == TFloatSpecial::fsNInf);
  return result;
}

/*#static*/ bool __fastcall TSingleHelper::IsPositiveInfinity(const float Value)
{
  bool result = false;
  result = (TSingleHelper(Value).SpecialType() == TFloatSpecial::fsInf);
  return result;
}

/*#static*/ int __fastcall TSingleHelper::Size()
{
  int result = 0;
  result = sizeof(float);
  return result;
}

String __fastcall TSingleHelper::ToString()
{
  String result;
  result = FloatToStr(m_Helped);
  return result;
}

String __fastcall TSingleHelper::ToString(const TFormatSettings& AFormatSettings)
{
  String result;
  result = FloatToStr(m_Helped, AFormatSettings);
  return result;
}

String __fastcall TSingleHelper::ToString(const TFloatFormat Format, const int Precision, const int Digits)
{
  String result;
  result = FloatToStrF(m_Helped, Format, Precision, Digits);
  return result;
}

String __fastcall TSingleHelper::ToString(const TFloatFormat Format, const int Precision, const int Digits, const TFormatSettings& AFormatSettings)
{
  String result;
  result = FloatToStrF(m_Helped, Format, Precision, Digits, AFormatSettings);
  return result;
}

bool __fastcall TSingleHelper::IsNan()
{
  bool result = false;
  result = (TSingleHelper(m_Helped).SpecialType() == TFloatSpecial::fsNaN);
  return result;
}

bool __fastcall TSingleHelper::IsInfinity()
{
  bool result = false;
  TFloatSpecial FloatType = fsZero;
  FloatType = TSingleHelper(m_Helped).SpecialType();
  result = (FloatType == fsInf) || (FloatType == fsNInf);
  return result;
}

bool __fastcall TSingleHelper::IsNegativeInfinity()
{
  bool result = false;
  result = (TSingleHelper(m_Helped).SpecialType() == TFloatSpecial::fsNInf);
  return result;
}

bool __fastcall TSingleHelper::IsPositiveInfinity()
{
  bool result = false;
  result = (TSingleHelper(m_Helped).SpecialType() == TFloatSpecial::fsInf);
  return result;
}

void __fastcall TSingleHelper::BuildUp(const bool SignFlag, const unsigned __int64 mantissa, const int Exponent)
{
  m_Helped = 0.0F;
  sign = SignFlag;
  Exp = (unsigned __int64) (Exponent + 0x7F);
  Frac = mantissa & 0x007FFFFF;
}

int __fastcall TSingleHelper::Exponent()
{
  int result = 0;
  unsigned __int64 e = 0L;
  unsigned __int64 F = 0L;
  e = GetExp();
  F = GetFrac();
  if((0L < e) && (e < 0xFF))
    result = (int) (e - 0x7F);
  else
  {
    if((e == 0L) && (F != 0L)) // Denormal
      result = -126;
    else
    {
      if((e == 0L) && (F == 0L)) // +/-Zero
        result = 0;
      else
        result = 0;
    } // +/-INF, NaN
  }
  return result;
}

long double __fastcall TSingleHelper::Fraction()
{
  long double result = 0.0L;
  unsigned __int64 e = 0L;
  unsigned __int64 F = 0L;
  e = GetExp();
  F = GetFrac();
  if(e == 0xFF)
  {
    if(F == 0L) // +/- INF.
      result = TExtendedHelper::PositiveInfinity;
    else
 // NaN
      result = TExtendedHelper::NaN;
  }
  else
  {
    if(e == 0L)
      result = (double(F) / 0x00800000);
    else
      result = 1.0L + (double(F) / 0x00800000);
  }
  return result;
}

unsigned __int64 __fastcall TSingleHelper::mantissa()
{
  unsigned __int64 result = 0L;
  unsigned __int64 e = 0L;
  unsigned __int64 F = 0L;
  e = GetExp();
  F = GetFrac();
  result = F;
  if((0L < e) && (e < 0xFF))
    result = result | (((unsigned __int64) 1L) << 23L);
  return result;
}

UInt8 __fastcall TSingleHelper::InternalGetBytes(unsigned int Index) const
{
  UInt8 result = 0;
  typedef unsigned char TByteArray[32768/*# range 0..32767*/];
  typedef TByteArray* PByteArray;
  result = (*(PByteArray) &m_Helped)[Index];
  return result;
}

UInt16 __fastcall TSingleHelper::InternalGetWords(unsigned int Index) const
{
  UInt16 result = 0;
  typedef WORD TWordArray[16384/*# range 0..16383*/];
  typedef TWordArray* PWordArray;
  result = (*(PWordArray) &m_Helped)[Index];
  return result;
}

void __fastcall TSingleHelper::InternalSetBytes(unsigned int Index, const UInt8 Value)
{
  typedef unsigned char TByteArray[32768/*# range 0..32767*/];
  typedef TByteArray* PByteArray;
  (*(PByteArray) &m_Helped)[Index] = Value;
}

void __fastcall TSingleHelper::InternalSetWords(unsigned int Index, const UInt16 Value)
{
  typedef WORD TWordArray[16384/*# range 0..16383*/];
  typedef TWordArray* PWordArray;
  (*(PWordArray) &m_Helped)[Index] = Value;
}

UInt8 __fastcall TSingleHelper::GetBytes(unsigned int Index) const
{
  UInt8 result = 0;
// todo  if(Index >= 4)
// todo		System::RError(System::TRuntimeError::reRangeError);
	result = InternalGetBytes(Index);
  return result;
}

UInt16 __fastcall TSingleHelper::GetWords(unsigned int Index) const
{
  UInt16 result = 0;
// todo	if(Index >= 2)
// todo		System::RError(TRuntimeError::reRangeError);
  result = InternalGetWords(Index);
  return result;
}

unsigned __int64 __fastcall TSingleHelper::GetExp() const
{
  unsigned __int64 result = 0L;
  result = (unsigned __int64) ((InternalGetWords(1) >> 7) & 0xFF);
  return result;
}

unsigned __int64 __fastcall TSingleHelper::GetFrac() const
{
  unsigned __int64 result = 0L;
  typedef UInt32* PUINT32;
  result = (unsigned __int64) ((*((PUINT32) &m_Helped)) & 0x007FFFFF);
  return result;
}

bool __fastcall TSingleHelper::GetSign() const
{
  bool result = false;
  result = InternalGetBytes(3) >= 0x80;
  return result;
}

void __fastcall TSingleHelper::setbytes(unsigned int Index, const UInt8 Value)
{
	if(Index >= 4)
		System::RError(reRangeError);
  InternalSetBytes(Index, Value);
}

void __fastcall TSingleHelper::SetWords(unsigned int Index, const UInt16 Value)
{
	if(Index >= 2)
		System::RError(reRangeError);
  InternalSetWords(Index, Value);
}

void __fastcall TSingleHelper::SetExp(unsigned __int64 NewExp)
{
  WORD W = 0;
  W = InternalGetWords(1);
  W = (WORD) ((W & 0x807F) | ((NewExp & 0xFF) << 7L));
  InternalSetWords(1, W);
}

void __fastcall TSingleHelper::SetFrac(unsigned __int64 NewFrac)
{
  typedef UInt32* PUINT32;
  UInt32 lw = 0;
  lw = (*((PUINT32) &m_Helped));
  lw = (unsigned int) ((lw & 0xFF800000) | (NewFrac & 0x007FFFFF));
  (*((PUINT32) &m_Helped)) = lw;
}

void __fastcall TSingleHelper::SetSign(bool NewSign)
{
  unsigned char B = 0;
  B = InternalGetBytes(3);
  if(NewSign)
    B = (unsigned char) (B | 0x80);
  else
    B = (unsigned char) (B & 0x7F);
  InternalSetBytes(3, B);
}

TFloatSpecial __fastcall TSingleHelper::SpecialType()
{
  TFloatSpecial result = fsZero;
  typedef UInt32* PUINT32;
  UInt32 i = 0;
  WORD W = 0;
  i = (*((PUINT32) &m_Helped));
  W = InternalGetWords(1);
  if((0x0080 <= W) && (W <= 0x7F7F))
    result = TFloatSpecial::fsPositive;
  else
  {
    if((0x8080 <= W) && (W <= 0xff7f))
      result = TFloatSpecial::fsNegative;
    else
    {
      if(i == 0)
        result = TFloatSpecial::fsZero;
      else
      {
        if(i == 0x80000000)
          result = TFloatSpecial::fsNZero;
        else
        {
          if(W <= 0x007F)
            result = TFloatSpecial::fsDenormal;
          else
          {
            if((0x8000 <= W) && (W <= 0x807F))
              result = TFloatSpecial::fsNDenormal;
            else
            {
              if(i == 0x7F800000)
                result = TFloatSpecial::fsInf;
              else
              {
                if(i == 0xFF800000)
                  result = TFloatSpecial::fsNInf;
                else
                  result = TFloatSpecial::fsNaN;
              }
            }
          }
        }
      }
    }
  }
  return result;
}

/* TDoubleHelper */

/*#static*/ String __fastcall TDoubleHelper::ToString(const double Value)
{
  String result;
  result = FloatToStr(Value);
  return result;
}

/*#static*/ String __fastcall TDoubleHelper::ToString(const double Value, const TFormatSettings& AFormatSettings)
{
  String result;
  result = FloatToStr(Value, AFormatSettings);
  return result;
}

/*#static*/ String __fastcall TDoubleHelper::ToString(const double Value, const TFloatFormat Format, const int Precision, const int Digits)
{
  String result;
  result = FloatToStrF(Value, Format, Precision, Digits);
  return result;
}

/*#static*/ String __fastcall TDoubleHelper::ToString(const double Value, const TFloatFormat Format, const int Precision, const int Digits, const TFormatSettings& AFormatSettings)
{
  String result;
  result = FloatToStrF(Value, Format, Precision, Digits, AFormatSettings);
  return result;
}

/*#static*/ double __fastcall TDoubleHelper::Parse(const String& s)
{
  double result = 0.0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidFloat2, ARRAYOFCONST((s, L"Double")));
  return result;
}

/*#static*/ double __fastcall TDoubleHelper::Parse(const String& s, const TFormatSettings& AFormatSettings)
{
  double result = 0.0;
  if(!TryParse(s, result, AFormatSettings))
		ConvertErrorFmt(System_Sysconst_SInvalidFloat2, ARRAYOFCONST((s, L"Double")));
  return result;
}

/*#static*/ bool __fastcall TDoubleHelper::TryParse(const String& s, double& Value)
{
  bool result = false;
  result = TryStrToFloat(s, Value);
  return result;
}

/*#static*/ bool __fastcall TDoubleHelper::TryParse(const String& s, double& Value, const TFormatSettings& AFormatSettings)
{
  bool result = false;
  result = TryStrToFloat(s, Value, AFormatSettings);
  return result;
}

/*#static*/ bool __fastcall TDoubleHelper::IsNan(const double Value)
{
  bool result = false;
  result = (TDoubleHelper(Value).SpecialType() == TFloatSpecial::fsNaN);
  return result;
}

/*#static*/ bool __fastcall TDoubleHelper::IsInfinity(const double Value)
{
  bool result = false;
  TFloatSpecial FloatType = fsZero;
  FloatType = TDoubleHelper(Value).SpecialType();
  result = (FloatType == fsInf) || (FloatType == fsNInf);
  return result;
}

/*#static*/ bool __fastcall TDoubleHelper::IsNegativeInfinity(const double Value)
{
  bool result = false;
  result = (TDoubleHelper(Value).SpecialType() == TFloatSpecial::fsNInf);
  return result;
}

/*#static*/ bool __fastcall TDoubleHelper::IsPositiveInfinity(const double Value)
{
  bool result = false;
  result = (TDoubleHelper(Value).SpecialType() == TFloatSpecial::fsInf);
  return result;
}

/*#static*/ int __fastcall TDoubleHelper::Size()
{
  int result = 0;
  result = sizeof(double);
  return result;
}

String __fastcall TDoubleHelper::ToString()
{
  String result;
  result = FloatToStr(m_Helped);
  return result;
}

String __fastcall TDoubleHelper::ToString(const TFormatSettings& AFormatSettings)
{
  String result;
  result = FloatToStr(m_Helped, AFormatSettings);
  return result;
}

String __fastcall TDoubleHelper::ToString(const TFloatFormat Format, const int Precision, const int Digits)
{
  String result;
  result = FloatToStrF(m_Helped, Format, Precision, Digits);
  return result;
}

String __fastcall TDoubleHelper::ToString(const TFloatFormat Format, const int Precision, const int Digits, const TFormatSettings& AFormatSettings)
{
  String result;
  result = FloatToStrF(m_Helped, Format, Precision, Digits, AFormatSettings);
  return result;
}

bool __fastcall TDoubleHelper::IsNan()
{
  bool result = false;
  result = (TDoubleHelper(m_Helped).SpecialType() == TFloatSpecial::fsNaN);
  return result;
}

bool __fastcall TDoubleHelper::IsInfinity()
{
  bool result = false;
  TFloatSpecial FloatType = fsZero;
  FloatType = TDoubleHelper(m_Helped).SpecialType();
  result = (FloatType == fsInf) || (FloatType == fsNInf);
  return result;
}

bool __fastcall TDoubleHelper::IsNegativeInfinity()
{
  bool result = false;
  result = (TDoubleHelper(m_Helped).SpecialType() == TFloatSpecial::fsNInf);
  return result;
}

bool __fastcall TDoubleHelper::IsPositiveInfinity()
{
  bool result = false;
  result = (TDoubleHelper(m_Helped).SpecialType() == TFloatSpecial::fsInf);
  return result;
}

void __fastcall TDoubleHelper::BuildUp(const bool SignFlag, const unsigned __int64 mantissa, const int Exponent)
{
  m_Helped = 0.0;
  SetSign(SignFlag);
  SetExp((unsigned __int64) (Exponent + 0x3FF));
	SetFrac(mantissa & 0x000FFFFFFF); //0x000FFFFFFFFFFFFF);
}

int __fastcall TDoubleHelper::Exponent()
{
	int result = 0;
  unsigned __int64 e = 0L;
  unsigned __int64 F = 0L;
  e = GetExp();
  F = GetFrac();
  if((0L < e) && (e < 0x7FF))
    result = (int) (e - 0x3FF);
  else
  {
		if((e == 0L) && (F != 0L)) // Denormal
      result = -1022;
    else
    {
      if((e == 0L) && (F == 0L)) // +/-Zero
        result = 0;
      else
        result = 0;
    } // +/-INF, NaN
  }
  return result;
}

long double __fastcall TDoubleHelper::Fraction()
{
  long double result = 0.0L;
  unsigned __int64 e = 0L;
  unsigned __int64 F = 0L;
  e = GetExp();
  F = GetFrac();
  if(e == 0x7FF)
  {
    if(F == 0L) // +/- INF.
      result = TExtendedHelper::PositiveInfinity;
    else
 // NaN
      result = TExtendedHelper::NaN;
  }
  else
  {
		if(e == 0L)
			result = (double(F) / 0x0010000000);  // 0x0010000000000000);
    else
			result = 1.0L + (double(F) / 0x0010000000);  // 0x0010000000000000);
	}
  return result;
}

unsigned __int64 __fastcall TDoubleHelper::mantissa()
{
  unsigned __int64 result = 0L;
  unsigned __int64 e = 0L;
	unsigned __int64 F = 0L;
  e = GetExp();
  F = GetFrac();
  result = F;
  if((0L < e) && (e < 0x7FF))
    result = result | (((unsigned __int64) 1L) << 52L);
  return result;
}

UInt8 __fastcall TDoubleHelper::InternalGetBytes(unsigned int Index) const
{
  UInt8 result = 0;
  typedef unsigned char TByteArray[32768/*# range 0..32767*/];
  typedef TByteArray* PByteArray;
  result = (*(PByteArray) &m_Helped)[Index];
  return result;
}

UInt16 __fastcall TDoubleHelper::InternalGetWords(unsigned int Index) const
{
  UInt16 result = 0;
  typedef WORD TWordArray[16384/*# range 0..16383*/];
  typedef TWordArray* PWordArray;
  result = (*(PWordArray) &m_Helped)[Index];
  return result;
}

void __fastcall TDoubleHelper::InternalSetBytes(unsigned int Index, const UInt8 Value)
{
  typedef unsigned char TByteArray[32768/*# range 0..32767*/];
  typedef TByteArray* PByteArray;
  (*(PByteArray) &m_Helped)[Index] = Value;
}

void __fastcall TDoubleHelper::InternalSetWords(unsigned int Index, const UInt16 Value)
{
  typedef WORD TWordArray[16384/*# range 0..16383*/];
  typedef TWordArray* PWordArray;
  (*(PWordArray) &m_Helped)[Index] = Value;
}

UInt8 __fastcall TDoubleHelper::GetBytes(unsigned int Index) const
{
  UInt8 result = 0;
	if(Index >= 8)
		System::RError(reRangeError);
  result = InternalGetBytes(Index);
  return result;
}

UInt16 __fastcall TDoubleHelper::GetWords(unsigned int Index) const
{
  UInt16 result = 0;
  if(Index >= 4)
    System::RError(reRangeError);
  result = InternalGetWords(Index);
  return result;
}

unsigned __int64 __fastcall TDoubleHelper::GetExp() const
{
  unsigned __int64 result = 0L;
  result = (unsigned __int64) ((InternalGetWords(3) >> 4) & 0x7FF);
  return result;
}

unsigned __int64 __fastcall TDoubleHelper::GetFrac() const
{
  unsigned __int64 result = 0L;
	result = (unsigned __int64) ((*((PUINT64) &m_Helped)) & 0x000FFFFFFF); //& 0x000FFFFFFFFFFFFF);
  return result;
}

bool __fastcall TDoubleHelper::GetSign() const
{
  bool result = false;
  result = InternalGetBytes(7) >= 0x80;
  return result;
}

void __fastcall TDoubleHelper::setbytes(unsigned int Index, const UInt8 Value)
{
  if(Index >= 8)
    System::RError(reRangeError);
  InternalSetBytes(Index, Value);
}

void __fastcall TDoubleHelper::SetWords(unsigned int Index, const UInt16 Value)
{
  if(Index >= 4)
    System::RError(reRangeError);
  InternalSetWords(Index, Value);
}

void __fastcall TDoubleHelper::SetExp(unsigned __int64 NewExp)
{
  WORD W = 0;
  W = InternalGetWords(3);
  W = (WORD) ((W & 0x800F) | ((NewExp & 0x7FF) << 4L));
  InternalSetWords(3, W);
}

void __fastcall TDoubleHelper::SetFrac(unsigned __int64 NewFrac)
{
  unsigned __int64 U64 = 0L;
	U64 = (*((PUINT64) &m_Helped));
	//U64 = (U64 & 0xFFF0000000000000) | (NewFrac & 0x000FFFFFFFFFFFFF);
	U64 = (U64 & 0xFFF00000) | (NewFrac & 0x000FFFFFFF); 
	(*((PUINT64) &m_Helped)) = U64;
}

void __fastcall TDoubleHelper::SetSign(bool NewSign)
{
  unsigned char B = 0;
  B = InternalGetBytes(7);
	if(NewSign)
		B = (unsigned char) (B | 0x80);
	else
    B = (unsigned char) (B & 0x7F);
  InternalSetBytes(7, B);
}

TFloatSpecial __fastcall TDoubleHelper::SpecialType()
{
  TFloatSpecial result = fsZero;
  unsigned __int64 U64 = 0L;
  WORD W = 0;
  U64 = (*((PUINT64) &m_Helped));
  W = InternalGetWords(3);
  if((0x0010 <= W) && (W <= 0x7FEF))
    result = TFloatSpecial::fsPositive;
  else
  {
    if((0x8010 <= W) && (W <= 0xFFEF))
      result = TFloatSpecial::fsNegative;
    else
    {
      if(U64 == 0L)
        result = TFloatSpecial::fsZero;
      else
      {
				if(U64 == 0x80000000)  // 0x8000000000000000)
          result = TFloatSpecial::fsNZero;
        else
        {
          if(W <= 0x000f)
            result = TFloatSpecial::fsDenormal;
          else
          {
            if((0x8000 <= W) && (W <= 0x800F))
							result = TFloatSpecial::fsNDenormal;
            else
            {
							if(U64 == 0x7FF00000)  // 0x7FF0000000000000)
                result = TFloatSpecial::fsInf;
              else
              {
								if(U64 == 0xFFF00000) // 0xFFF0000000000000)
									result = TFloatSpecial::fsNInf;
                else
                  result = TFloatSpecial::fsNaN;
              }
            }
          }
        }
      }
		}
  }
	return result;
}

/* TExtendedHelper */

/*#static*/ String __fastcall TExtendedHelper::ToString(const long double Value)
{
  String result;
  result = FloatToStr(Value);
  return result;
}

/*#static*/ String __fastcall TExtendedHelper::ToString(const long double Value, const TFormatSettings& AFormatSettings)
{
  String result;
  result = FloatToStr(Value, AFormatSettings);
  return result;
}

/*#static*/ String __fastcall TExtendedHelper::ToString(const long double Value, const TFloatFormat Format, const int Precision, const int Digits)
{
  String result;
  result = FloatToStrF(Value, Format, Precision, Digits);
  return result;
}

/*#static*/ String __fastcall TExtendedHelper::ToString(const long double Value, const TFloatFormat Format, const int Precision, const int Digits, const TFormatSettings& AFormatSettings)
{
  String result;
  result = FloatToStrF(Value, Format, Precision, Digits, AFormatSettings);
  return result;
}

/*#static*/ long double __fastcall TExtendedHelper::Parse(const String& s)
{
  long double result = 0.0L;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidFloat2, ARRAYOFCONST((s, L"Extended")));
  return result;
}

/*#static*/ long double __fastcall TExtendedHelper::Parse(const String& s, const TFormatSettings& AFormatSettings)
{
  long double result = 0.0L;
	if(!TryParse(s, result, AFormatSettings))
		ConvertErrorFmt(System_Sysconst_SInvalidFloat2, ARRAYOFCONST((s, L"Extended")));
  return result;
}

/*#static*/ bool __fastcall TExtendedHelper::TryParse(const String& s, long double& Value)
{
  bool result = false;
  result = TryStrToFloat(s, Value);
  return result;
}

/*#static*/ bool __fastcall TExtendedHelper::TryParse(const String& s, long double& Value, const TFormatSettings& AFormatSettings)
{
  bool result = false;
  result = TryStrToFloat(s, Value, AFormatSettings);
  return result;
}

/*#static*/ bool __fastcall TExtendedHelper::IsNan(const long double Value)
{
  bool result = false;
  result = (TExtendedHelper(Value).SpecialType() == TFloatSpecial::fsNaN);
  return result;
}

/*#static*/ bool __fastcall TExtendedHelper::IsInfinity(const long double Value)
{
  bool result = false;
  TFloatSpecial FloatType = fsZero;
  FloatType = TExtendedHelper(Value).SpecialType();
  result = (FloatType == fsInf) || (FloatType == fsNInf);
  return result;
}

/*#static*/ bool __fastcall TExtendedHelper::IsNegativeInfinity(const long double Value)
{
  bool result = false;
  result = (TExtendedHelper(Value).SpecialType() == TFloatSpecial::fsNInf);
  return result;
}

/*#static*/ bool __fastcall TExtendedHelper::IsPositiveInfinity(const long double Value)
{
  bool result = false;
  result = (TExtendedHelper(Value).SpecialType() == TFloatSpecial::fsInf);
  return result;
}

/*#static*/ int __fastcall TExtendedHelper::Size()
{
  int result = 0;
  result = sizeof(long double);
  return result;
}

String __fastcall TExtendedHelper::ToString()
{
  String result;
  result = FloatToStr(m_Helped);
  return result;
}

String __fastcall TExtendedHelper::ToString(const TFormatSettings& AFormatSettings)
{
  String result;
  result = FloatToStr(m_Helped, AFormatSettings);
  return result;
}

String __fastcall TExtendedHelper::ToString(const TFloatFormat Format, const int Precision, const int Digits)
{
  String result;
  result = FloatToStrF(m_Helped, Format, Precision, Digits);
  return result;
}

String __fastcall TExtendedHelper::ToString(const TFloatFormat Format, const int Precision, const int Digits, const TFormatSettings& AFormatSettings)
{
  String result;
  result = FloatToStrF(m_Helped, Format, Precision, Digits, AFormatSettings);
  return result;
}

bool __fastcall TExtendedHelper::IsNan()
{
  bool result = false;
  result = (TExtendedHelper(m_Helped).SpecialType() == TFloatSpecial::fsNaN);
  return result;
}

bool __fastcall TExtendedHelper::IsInfinity()
{
  bool result = false;
  TFloatSpecial FloatType = fsZero;
  FloatType = TExtendedHelper(m_Helped).SpecialType();
  result = (FloatType == fsInf) || (FloatType == fsNInf);
  return result;
}

bool __fastcall TExtendedHelper::IsNegativeInfinity()
{
  bool result = false;
  result = (TExtendedHelper(m_Helped).SpecialType() == TFloatSpecial::fsNInf);
  return result;
}

bool __fastcall TExtendedHelper::IsPositiveInfinity()
{
  bool result = false;
  result = (TExtendedHelper(m_Helped).SpecialType() == TFloatSpecial::fsInf);
  return result;
}

void __fastcall TExtendedHelper::BuildUp(const bool SignFlag, const unsigned __int64 mantissa, const int Exponent)
{
  m_Helped = 0.0L;
  SetSign(SignFlag);
  SetExp((unsigned __int64) (Exponent + 0x3FF));
	SetFrac(mantissa & 0x000FFFFFFF); //  & 0x000FFFFFFFFFFFFF);
}

int __fastcall TExtendedHelper::Exponent()
{
  int result = 0;
  unsigned __int64 e = 0L;
  unsigned __int64 F = 0L;
  e = GetExp();
  F = GetFrac();
	if((0L < e) && (e < 0x7FF))
    result = (int) (e - 0x3FF);
  else
  {
    if((e == 0L) && (F != 0L)) // Denormal
      result = -1022;
    else
      result = 0; //  +/-Zero, +/-INF and NaN
  }
  return result;
}

long double __fastcall TExtendedHelper::Fraction()
{
  long double result = 0.0L;
  unsigned __int64 e = 0L;
  unsigned __int64 F = 0L;
  e = GetExp();
  F = GetFrac();
  if(e == 0x7FF)
  {
    if(F == 0L) // +/- INF.
    {
      if(sign)
        result = TExtendedHelper::PositiveInfinity;
      else
        result = TExtendedHelper::NegativeInfinity;
    }
    else
 // NaN
    result = TExtendedHelper::NaN;
  }
  else
  {
    if(e == 0L)
			result = (double(F) / 0x0010000000); // 0x0010000000000000);
		else
			result = 1.0L + (double(F) / 0x0010000000); //  0x0010000000000000);
	}
  return result;
}

unsigned __int64 __fastcall TExtendedHelper::mantissa()
{
  unsigned __int64 result = 0L;
  unsigned __int64 e = 0L;
	unsigned __int64 F = 0L;
  e = GetExp();
  F = GetFrac();
	result = F;
  if((0L < e) && (e < 0x7FF))
    result = result | (((unsigned __int64) 1L) << 52L);
  return result;
}

UInt8 __fastcall TExtendedHelper::InternalGetBytes(unsigned int Index) const
{
  UInt8 result = 0;
  typedef unsigned char TByteArray[32768/*# range 0..32767*/];
  typedef TByteArray* PByteArray;
  result = (*(PByteArray) &m_Helped)[Index];
  return result;
}

UInt16 __fastcall TExtendedHelper::InternalGetWords(unsigned int Index) const
{
  UInt16 result = 0;
  typedef WORD TWordArray[16384/*# range 0..16383*/];
  typedef TWordArray* PWordArray;
  result = (*(PWordArray) &m_Helped)[Index];
  return result;
}

void __fastcall TExtendedHelper::InternalSetBytes(unsigned int Index, const UInt8 Value)
{
  typedef unsigned char TByteArray[32768/*# range 0..32767*/];
  typedef TByteArray* PByteArray;
  (*(PByteArray) &m_Helped)[Index] = Value;
}

void __fastcall TExtendedHelper::InternalSetWords(unsigned int Index, const UInt16 Value)
{
  typedef WORD TWordArray[16384/*# range 0..16383*/];
  typedef TWordArray* PWordArray;
  (*(PWordArray) &m_Helped)[Index] = Value;
}

UInt8 __fastcall TExtendedHelper::GetBytes(unsigned int Index) const
{
  UInt8 result = 0;
  if(Index >= 8)
    System::RError(reRangeError);
  result = InternalGetBytes(Index);
  return result;
}

UInt16 __fastcall TExtendedHelper::GetWords(unsigned int Index) const
{
  UInt16 result = 0;
  if(Index >= 4)
    System::RError(reRangeError);
  result = InternalGetWords(Index);
  return result;
}

unsigned __int64 __fastcall TExtendedHelper::GetExp() const
{
  unsigned __int64 result = 0L;
  result = (unsigned __int64) ((InternalGetWords(3) >> 4) & 0x7FF);
  return result;
}

unsigned __int64 __fastcall TExtendedHelper::GetFrac() const
{
  unsigned __int64 result = 0L;
	result = (unsigned __int64) ((*((PUINT64) &m_Helped)) & 0x000FFFFFFF);  //  & 0x000FFFFFFFFFFFFF);
  return result;
}

bool __fastcall TExtendedHelper::GetSign() const
{
  bool result = false;
  result = InternalGetBytes(7) >= 0x80;
  return result;
}

void __fastcall TExtendedHelper::setbytes(unsigned int Index, const UInt8 Value)
{
  if(Index >= 8)
    System::RError(reRangeError);
  InternalSetBytes(Index, Value);
}

void __fastcall TExtendedHelper::SetWords(unsigned int Index, const UInt16 Value)
{
  if(Index >= 4)
		System::RError(reRangeError);
  InternalSetWords(Index, Value);
}

void __fastcall TExtendedHelper::SetExp(unsigned __int64 NewExp)
{
  WORD W = 0;
  W = InternalGetWords(3);
  W = (WORD) ((W & 0x800F) | ((NewExp & 0x7FF) << 4L));
  InternalSetWords(3, W);
}

void __fastcall TExtendedHelper::SetFrac(unsigned __int64 NewFrac)
{
  unsigned __int64 U64 = 0L;
  U64 = (*((PUINT64) &m_Helped));
	//U64 = (U64 & 0xFFF0000000000000) | (NewFrac & 0x000FFFFFFFFFFFFF);
	U64 = (U64 & 0xFFF00000) | (NewFrac & 0x000FFFFFFF);
	(*((PUINT64) &m_Helped)) = U64;
}

void __fastcall TExtendedHelper::SetSign(bool NewSign)
{
  unsigned char B = 0;
  B = InternalGetBytes(7);
  if(NewSign)
    B = (unsigned char) (B | 0x80);
	else
    B = (unsigned char) (B & 0x7F);
  InternalSetBytes(7, B);
}

TFloatSpecial __fastcall TExtendedHelper::SpecialType()
{
  TFloatSpecial result = fsZero;
	unsigned __int64 U64 = 0L;
  WORD W = 0;
  U64 = (*((PUINT64) &m_Helped));
  W = InternalGetWords(3);
  if((0x0010 <= W) && (W <= 0x7FEF))
    result = TFloatSpecial::fsPositive;
  else
  {
    if((0x8010 <= W) && (W <= 0xFFEF))
      result = TFloatSpecial::fsNegative;
    else
    {
      if(U64 == 0L)
        result = TFloatSpecial::fsZero;
      else
			{
				if(U64 == 0x80000000) // 0x8000000000000000)
          result = TFloatSpecial::fsNZero;
        else
        {
          if(W <= 0x000f)
            result = TFloatSpecial::fsDenormal;
          else
          {
            if((0x8000 <= W) && (W <= 0x800F))
              result = TFloatSpecial::fsNDenormal;
            else
						{
							if(U64 == 0x7FF0000) // 0x7FF0000000000000)
								result = TFloatSpecial::fsInf;
              else
							{
								if(U64 == 0xFFF00000) // 0xFFF0000000000000)
                  result = TFloatSpecial::fsNInf;
								else
                  result = TFloatSpecial::fsNaN;
							}
						}
          }
        }
      }
    }
  }
  return result;
}

/* TByteHelper */

/*#static*/ int __fastcall TByteHelper::Size()
{
  int result = 0;
  result = sizeof(unsigned char);
  return result;
}

/*#static*/ String __fastcall TByteHelper::ToString(const unsigned char Value)
{
  String result;
  result = IntToStr((int) Value);
  return result;
}

/*#static*/ unsigned char __fastcall TByteHelper::Parse(const String& s)
{
  unsigned char result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"Byte")));
  return result;
}

/*#static*/ bool __fastcall TByteHelper::TryParse(const String& s, unsigned char& Value)
{
  bool result = false;
  int i = 0;
  int e = 0;
	Val(s, &i, e);
	result = (e == 0) && (MinValue <= i) && (i <= MaxValue);
  if(result)
    Value = (unsigned char) i;
	return result;
}

String __fastcall TByteHelper::ToString()
{
	String result;
  result = IntToStr(m_Helped);
  return result;
}

bool __fastcall TByteHelper::ToBoolean()
{
  bool result = false;
  result = m_Helped != 0;
  return result;
}

String __fastcall TByteHelper::ToHexString()
{
  String result;
  result = IntToHex(m_Helped);
  return result;
}

String __fastcall TByteHelper::ToHexString(const int MinDigits)
{
  String result;
  result = IntToHex(m_Helped, MinDigits);
  return result;
}

float __fastcall TByteHelper::ToSingle()
{
  float result = 0.0F;
  result = m_Helped;
  return result;
}

double __fastcall TByteHelper::ToDouble()
{
  double result = 0.0;
  result = m_Helped;
  return result;
}

long double __fastcall TByteHelper::ToExtended()
{
  long double result = 0.0L;
  result = m_Helped;
  return result;
}

/* TShortIntHelper */

/*#static*/ int __fastcall TShortIntHelper::Size()
{
  int result = 0;
  result = sizeof(signed char);
  return result;
}

/*#static*/ String __fastcall TShortIntHelper::ToString(const signed char Value)
{
  String result;
  result = IntToStr(Value);
  return result;
}

/*#static*/ signed char __fastcall TShortIntHelper::Parse(const String& s)
{
  signed char result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"ShortInt")));
  return result;
}

/*#static*/ bool __fastcall TShortIntHelper::TryParse(const String& s, signed char& Value)
{
	bool result = false;
  int i = 0;
  int e = 0;
	Val(s, &i, e);
  result = (e == 0) && (TShortIntHelper::MinValue <= i) && (i <= TShortIntHelper::MaxValue);
  if(result)
    Value = (signed char) i;
  return result;
}

String __fastcall TShortIntHelper::ToString()
{
  String result;
  result = IntToStr(m_Helped);
  return result;
}

bool __fastcall TShortIntHelper::ToBoolean()
{
  bool result = false;
  result = m_Helped != 0;
  return result;
}

String __fastcall TShortIntHelper::ToHexString()
{
  String result;
  result = IntToHex(m_Helped);
  return result;
}

String __fastcall TShortIntHelper::ToHexString(const int MinDigits)
{
	String result;
	result = IntToHex(m_Helped, MinDigits);
	return result;
}

float __fastcall TShortIntHelper::ToSingle()
{
	float result = 0.0F;
	result = m_Helped;
	return result;
}

double __fastcall TShortIntHelper::ToDouble()
{
  double result = 0.0;
  result = m_Helped;
  return result;
}

long double __fastcall TShortIntHelper::ToExtended()
{
  long double result = 0.0L;
  result = m_Helped;
  return result;
}

/* TWordHelper */

/*#static*/ int __fastcall TWordHelper::Size()
{
  int result = 0;
  result = sizeof(WORD);
  return result;
}

/*#static*/ String __fastcall TWordHelper::ToString(const WORD Value)
{
  String result;
  result = IntToStr((int) Value);
  return result;
}

/*#static*/ WORD __fastcall TWordHelper::Parse(const String& s)
{
  WORD result = 0;
  if(!TryParse(s, result))
    ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"Word")));
  return result;
}

/*#static*/ bool __fastcall TWordHelper::TryParse(const String& s, WORD& Value)
{
  bool result = false;
  int i = 0;
  int e = 0;
	Val(s, &i, e);
  result = (e == 0) && (TWordHelper::MinValue <= i) && (i <= TWordHelper::MaxValue);
  if(result)
    Value = (WORD) i;
  return result;
}

String __fastcall TWordHelper::ToString()
{
  String result;
  result = IntToStr(m_Helped);
  return result;
}

bool __fastcall TWordHelper::ToBoolean()
{
  bool result = false;
  result = m_Helped != 0;
  return result;
}

String __fastcall TWordHelper::ToHexString()
{
  String result;
  result = IntToHex(m_Helped);
  return result;
}

String __fastcall TWordHelper::ToHexString(const int MinDigits)
{
  String result;
  result = IntToHex(m_Helped, MinDigits);
  return result;
}

float __fastcall TWordHelper::ToSingle()
{
  float result = 0.0F;
  result = m_Helped;
  return result;
}

double __fastcall TWordHelper::ToDouble()
{
  double result = 0.0;
  result = m_Helped;
  return result;
}

long double __fastcall TWordHelper::ToExtended()
{
  long double result = 0.0L;
  result = m_Helped;
  return result;
}

/* TSmallIntHelper */

/*#static*/ int __fastcall TSmallIntHelper::Size()
{
  int result = 0;
  result = sizeof(short int);
  return result;
}

/*#static*/ String __fastcall TSmallIntHelper::ToString(const short int Value)
{
  String result;
  result = IntToStr(Value);
  return result;
}

/*#static*/ short int __fastcall TSmallIntHelper::Parse(const String& s)
{
  short int result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"SmallInt")));
  return result;
}

/*#static*/ bool __fastcall TSmallIntHelper::TryParse(const String& s, short int& Value)
{
  bool result = false;
  int i = 0;
  int e = 0;
	Val(s, &i, e);
  result = (e == 0) && (TSmallIntHelper::MinValue <= i) && (i <= TSmallIntHelper::MaxValue);
  if(result)
    Value = (short int) i;
  return result;
}

String __fastcall TSmallIntHelper::ToString()
{
  String result;
  result = IntToStr(m_Helped);
  return result;
}

bool __fastcall TSmallIntHelper::ToBoolean()
{
  bool result = false;
  result = m_Helped != 0;
  return result;
}

String __fastcall TSmallIntHelper::ToHexString()
{
  String result;
  result = IntToHex(m_Helped);
  return result;
}

String __fastcall TSmallIntHelper::ToHexString(const int MinDigits)
{
  String result;
	result = IntToHex(m_Helped, MinDigits);
  return result;
}

float __fastcall TSmallIntHelper::ToSingle()
{
  float result = 0.0F;
  result = m_Helped;
  return result;
}

double __fastcall TSmallIntHelper::ToDouble()
{
  double result = 0.0;
  result = m_Helped;
  return result;
}

long double __fastcall TSmallIntHelper::ToExtended()
{
  long double result = 0.0L;
  result = m_Helped;
  return result;
}

/* TCardinalHelper */

/*#static*/ int __fastcall TCardinalHelper::Size()
{
  int result = 0;
  result = sizeof(unsigned int);
  return result;
}

/*#static*/ String __fastcall TCardinalHelper::ToString(const unsigned int Value)
{
  String result;
  result = IntToStr((__int64) Value);
  return result;
}

/*#static*/ unsigned int __fastcall TCardinalHelper::Parse(const String& s)
{
  unsigned int result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"Cardinal")));
  return result;
}

/*#static*/ bool __fastcall TCardinalHelper::TryParse(const String& s, unsigned int& Value)
{
  bool result = false;
  __int64 i64 = 0;
  int e = 0;
	Val(s, &i64, e);
	result = (e == 0) && (TCardinalHelper::MinValue <= i64) && (i64 <= TCardinalHelper::MaxValue);
  if(result)
    Value = (unsigned int) i64;
  return result;
}

String __fastcall TCardinalHelper::ToString()
{
  String result;
	result = IntToStr((__int64) m_Helped);
	return result;
}

bool __fastcall TCardinalHelper::ToBoolean()
{
	bool result = false;
	result = m_Helped != 0;
  return result;
}

String __fastcall TCardinalHelper::ToHexString()
{
  String result;
	result = IntToHex((unsigned __int64)m_Helped);
  return result;
}

String __fastcall TCardinalHelper::ToHexString(const int MinDigits)
{
  String result;
	result = IntToHex((unsigned __int64)m_Helped, MinDigits);
  return result;
}

float __fastcall TCardinalHelper::ToSingle()
{
  float result = 0.0F;
  result = m_Helped;
  return result;
}

double __fastcall TCardinalHelper::ToDouble()
{
  double result = 0.0;
  result = m_Helped;
  return result;
}

long double __fastcall TCardinalHelper::ToExtended()
{
  long double result = 0.0L;
  result = m_Helped;
  return result;
}

/* TIntegerHelper */

/*#static*/ int __fastcall TIntegerHelper::Size()
{
  int result = 0;
  result = sizeof(int);
  return result;
}

/*#static*/ String __fastcall TIntegerHelper::ToString(const int Value)
{
  String result;
  result = IntToStr(Value);
  return result;
}

/*#static*/ int __fastcall TIntegerHelper::Parse(const String& s)
{
  int result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"Integer")));
  return result;
}

/*#static*/ bool __fastcall TIntegerHelper::TryParse(const String& s, int& Value)
{
  bool result = false;
  int e = 0;
	Val(s, &Value, e);
  result = (e == 0);
  return result;
}

String __fastcall TIntegerHelper::ToString()
{
  String result;
  result = IntToStr(m_Helped);
  return result;
}

bool __fastcall TIntegerHelper::ToBoolean()
{
  bool result = false;
  result = m_Helped != 0;
  return result;
}

String __fastcall TIntegerHelper::ToHexString()
{
  String result;
  result = IntToHex(m_Helped);
  return result;
}

String __fastcall TIntegerHelper::ToHexString(const int MinDigits)
{
  String result;
	result = IntToHex(m_Helped, MinDigits);
  return result;
}

float __fastcall TIntegerHelper::ToSingle()
{
  float result = 0.0F;
  result = m_Helped;
  return result;
}

double __fastcall TIntegerHelper::ToDouble()
{
  double result = 0.0;
  result = m_Helped;
  return result;
}

long double __fastcall TIntegerHelper::ToExtended()
{
  long double result = 0.0L;
  result = m_Helped;
  return result;
}

/* TUInt64Helper */

/*#static*/ int __fastcall TUInt64Helper::Size()
{
  int result = 0;
  result = sizeof(unsigned __int64);
  return result;
}

/*#static*/ String __fastcall TUInt64Helper::ToString(const unsigned __int64 Value)
{
  String result;
  result = UIntToStr(Value);
  return result;
}

/*#static*/ unsigned __int64 __fastcall TUInt64Helper::Parse(const String& s)
{
  unsigned __int64 result = 0L;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"UInt64")));
  return result;
}

/*#static*/ bool __fastcall TUInt64Helper::TryParse(const String& s, unsigned __int64& Value)
{
  bool result = false;
	int e = 0;
	Val(s, &Value, e);
  result = e == 0;
  return result;
}

String __fastcall TUInt64Helper::ToString()
{
  String result;
  result = UIntToStr(m_Helped);
  return result;
}

bool __fastcall TUInt64Helper::ToBoolean()
{
  bool result = false;
  result = m_Helped != 0L;
  return result;
}

String __fastcall TUInt64Helper::ToHexString()
{
  String result;
  result = IntToHex(m_Helped);
  return result;
}

String __fastcall TUInt64Helper::ToHexString(const int MinDigits)
{
  String result;
  result = IntToHex(m_Helped, MinDigits);
  return result;
}

float __fastcall TUInt64Helper::ToSingle()
{
  float result = 0.0F;
  result = m_Helped;
  return result;
}

double __fastcall TUInt64Helper::ToDouble()
{
  double result = 0.0;
  result = m_Helped;
  return result;
}

long double __fastcall TUInt64Helper::ToExtended()
{
  long double result = 0.0L;
  result = m_Helped;
  return result;
}

/* TInt64Helper */

/*#static*/ int __fastcall TInt64Helper::Size()
{
  int result = 0;
  result = sizeof(__int64);
  return result;
}

/*#static*/ String __fastcall TInt64Helper::ToString(const __int64 Value)
{
  String result;
  result = IntToStr(Value);
  return result;
}

/*#static*/ __int64 __fastcall TInt64Helper::Parse(const String& s)
{
  __int64 result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"Int64")));
  return result;
}

/*#static*/ bool __fastcall TInt64Helper::TryParse(const String& s, __int64& Value)
{
  bool result = false;
  int e = 0;
	Val(s, &Value, e);
  result = e == 0;
  return result;
}

String __fastcall TInt64Helper::ToString()
{
  String result;
  result = IntToStr(m_Helped);
  return result;
}

bool __fastcall TInt64Helper::ToBoolean()
{
  bool result = false;
  result = m_Helped != 0;
  return result;
}

String __fastcall TInt64Helper::ToHexString()
{
  String result;
  result = IntToHex(m_Helped);
  return result;
}

String __fastcall TInt64Helper::ToHexString(const int MinDigits)
{
  String result;
	//result = _IntToHex64(m_Helped, MinDigits);
	result = IntToHex((__int64) m_Helped, MinDigits);
	return result;
}

float __fastcall TInt64Helper::ToSingle()
{
  float result = 0.0F;
  result = m_Helped;
  return result;
}

double __fastcall TInt64Helper::ToDouble()
{
  double result = 0.0;
  result = m_Helped;
  return result;
}

long double __fastcall TInt64Helper::ToExtended()
{
  long double result = 0.0L;
  result = m_Helped;
  return result;
}

/* TNativeUIntHelper */

/*#static*/ int __fastcall TNativeUIntHelper::Size()
{
  int result = 0;
  result = sizeof(NativeUInt);
  return result;
}

/*#static*/ String __fastcall TNativeUIntHelper::ToString(const NativeUInt Value)
{
  String result;
  result = UIntToStr(Value);
  return result;
}

/*#static*/ NativeUInt __fastcall TNativeUIntHelper::Parse(const String& s)
{
  NativeUInt result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"NativeUInt")));
  return result;
}

/*#static*/ bool __fastcall TNativeUIntHelper::TryParse(const String& s, NativeUInt& Value)
{
  bool result = false;
  __int64 i64 = 0;
  int e = 0;
	Val(s, &i64, e);
  result = (e == 0) && (TNativeUIntHelper::MinValue <= i64) && (i64 <= TNativeUIntHelper::MaxValue);
  if(result)
    Value = (NativeUInt) i64;
  return result;
}

String __fastcall TNativeUIntHelper::ToString()
{
  String result;
  result = UIntToStr(m_Helped);
  return result;
}

bool __fastcall TNativeUIntHelper::ToBoolean()
{
  bool result = false;
  result = m_Helped != 0;
  return result;
}

String __fastcall TNativeUIntHelper::ToHexString()
{
  String result;
  result = IntToHex(m_Helped);
  return result;
}

String __fastcall TNativeUIntHelper::ToHexString(const int MinDigits)
{
  String result;
	result = IntToHex((unsigned __int64)m_Helped, MinDigits);
  return result;
}

float __fastcall TNativeUIntHelper::ToSingle()
{
  float result = 0.0F;
  result = m_Helped;
  return result;
}

double __fastcall TNativeUIntHelper::ToDouble()
{
  double result = 0.0;
  result = m_Helped;
  return result;
}

long double __fastcall TNativeUIntHelper::ToExtended()
{
  long double result = 0.0L;
  result = m_Helped;
  return result;
}

/* TNativeIntHelper */

/*#static*/ int __fastcall TNativeIntHelper::Size()
{
  int result = 0;
  result = sizeof(NativeInt);
  return result;
}

/*#static*/ String __fastcall TNativeIntHelper::ToString(const NativeInt Value)
{
  String result;
  result = IntToStr(Value);
  return result;
}

/*#static*/ NativeInt __fastcall TNativeIntHelper::Parse(const String& s)
{
  NativeInt result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"NativeInt")));
  return result;
}

/*#static*/ bool __fastcall TNativeIntHelper::TryParse(const String& s, NativeInt& Value)
{
  bool result = false;
  int e = 0;
	Val(s, &Value, e);
  result = e == 0;
  return result;
}

String __fastcall TNativeIntHelper::ToString()
{
  String result;
  result = IntToStr(m_Helped);
  return result;
}

bool __fastcall TNativeIntHelper::ToBoolean()
{
  bool result = false;
  result = m_Helped != 0;
  return result;
}

String __fastcall TNativeIntHelper::ToHexString()
{
  String result;
  result = IntToHex(m_Helped);
  return result;
}

String __fastcall TNativeIntHelper::ToHexString(const int MinDigits)
{
  String result;
	result = IntToHex(m_Helped, MinDigits);
  return result;
}

float __fastcall TNativeIntHelper::ToSingle()
{
  float result = 0.0F;
  result = m_Helped;
  return result;
}

double __fastcall TNativeIntHelper::ToDouble()
{
  double result = 0.0;
  result = m_Helped;
  return result;
}

long double __fastcall TNativeIntHelper::ToExtended()
{
  long double result = 0.0L;
  result = m_Helped;
  return result;
}

/* TBooleanHelper */

/*#static*/ int __fastcall TBooleanHelper::Size()
{
  int result = 0;
  result = sizeof(bool);
  return result;
}

/*#static*/ String __fastcall TBooleanHelper::ToString(const bool Value, TUseBoolStrs UseBoolStrs/*# = TUseBoolStrs.False*/)
{
  String result;
  result = BoolToStr(Value, ((bool) UseBoolStrs));
  return result;
}

/*#static*/ bool __fastcall TBooleanHelper::Parse(const String& s)
{
  bool result = false;
  result = StrToBool(s);
  return result;
}

/*#static*/ bool __fastcall TBooleanHelper::TryToParse(const String& s, bool& Value)
{
  bool result = false;
  result = TryStrToBool(s, Value);
  return result;
}

int __fastcall TBooleanHelper::ToInteger()
{
  int result = 0;
  result = ((int) m_Helped);
  return result;
}

String __fastcall TBooleanHelper::ToString(TUseBoolStrs UseBoolStrs/*# = TUseBoolStrs.False*/)
{
  String result;
  result = BoolToStr(m_Helped, ((bool) UseBoolStrs));
  return result;
}

/* TByteBoolHelper */

/*#static*/ int __fastcall TByteBoolHelper::Size()
{
  int result = 0;
  result = sizeof(unsigned char);
  return result;
}

/*#static*/ String __fastcall TByteBoolHelper::ToString(const bool Value)
{
  String result;
  result = BoolToStr(Value);
  return result;
}

/*#static*/ bool __fastcall TByteBoolHelper::Parse(const String& s)
{
  bool result = false;
  result = StrToBool(s);
  return result;
}

/*#static*/ bool __fastcall TByteBoolHelper::TryToParse(const String& s, bool& Value)
{
  bool result = false;
  result = TryStrToBool(s, Value);
  return result;
}

int __fastcall TByteBoolHelper::ToInteger()
{
  int result = 0;
  result = ((int) m_Helped);
  return result;
}

String __fastcall TByteBoolHelper::ToString()
{
  String result;
  result = BoolToStr(m_Helped);
  return result;
}

/* TWordBoolHelper */

/*#static*/ int __fastcall TWordBoolHelper::Size()
{
  int result = 0;
  result = sizeof(unsigned short);
  return result;
}

/*#static*/ String __fastcall TWordBoolHelper::ToString(const bool Value)
{
  String result;
  result = BoolToStr(Value);
  return result;
}

/*#static*/ bool __fastcall TWordBoolHelper::Parse(const String& s)
{
  bool result = false;
  result = StrToBool(s);
  return result;
}

/*#static*/ bool __fastcall TWordBoolHelper::TryToParse(const String& s, bool& Value)
{
  bool result = false;
  result = TryStrToBool(s, Value);
  return result;
}

int __fastcall TWordBoolHelper::ToInteger()
{
  int result = 0;
  result = ((int) m_Helped);
  return result;
}

String __fastcall TWordBoolHelper::ToString()
{
  String result;
  result = BoolToStr(m_Helped);
  return result;
}

/* TLongBoolHelper */

/*#static*/ int __fastcall TLongBoolHelper::Size()
{
  int result = 0;
  result = sizeof(BOOL);
  return result;
}

/*#static*/ String __fastcall TLongBoolHelper::ToString(const bool Value)
{
  String result;
  result = BoolToStr(Value);
  return result;
}

/*#static*/ bool __fastcall TLongBoolHelper::Parse(const String& s)
{
  bool result = false;
  result = StrToBool(s);
  return result;
}

/*#static*/ bool __fastcall TLongBoolHelper::TryToParse(const String& s, bool& Value)
{
  bool result = false;
  result = TryStrToBool(s, Value);
  return result;
}

int __fastcall TLongBoolHelper::ToInteger()
{
  int result = 0;
	result = ((int) m_Helped);
  return result;
}

String __fastcall TLongBoolHelper::ToString()
{
  String result;
  result = BoolToStr(m_Helped);
  return result;
}

} // namespace d2c_system
