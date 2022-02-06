//---------------------------------------------------------------------------

#pragma hdrstop

#include "d2c_syshelper.h"
#include <System.SysConst.hpp>
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


void Error(TRuntimeError errorCode)
{
	throw Sysutils::Exception("");
}

} // namespace system


namespace d2c_system {

#define Sysutils__38 (TCompareOptions() << coIgnoreCase)
#define Sysutils__39 TCompareOptions()
#define Sysutils__40 TCompareOptions()
#define Sysutils__41 TCompareOptions()
#define Sysutils__42 TCompareOptions()
#define Sysutils__43 TCompareOptions()
#define Sysutils__44 (TReplaceFlags() << rfReplaceAll)
#define Sysutils__45 (TReplaceFlags() << rfReplaceAll)
#define Sysutils__46 (System::Set<int, 0, 255>() << 0 << 1)
#define Sysutils__47 (System::Set<int, 0, 255>() << 0 << 1)


PChar ustr2pwchar(const String xs, int xiIndex = 0)
{
	return xs.c_str() + xiIndex;
}

void __fastcall ConvertErrorFmt(System::ResourceString* ResString, const TVarRec* Args, int Args_maxidx)
{
	throw EConvertError(ResString, Args, Args_maxidx);
}

void __fastcall ConvertErrorFmt(const String ResString, const TVarRec* Args, int Args_maxidx)
{
	throw EConvertError(ResString, Args, Args_maxidx);
}

template <typename T>
void Val(const String S, T* V, int& Code)
{
	std::wistringstream iss(S.c_str());
  iss >> *V;
  Code = 0;
}


int zbc = 1; // dme zero base correction

/*static */const WideChar TStringHelper::Empty[] = L"";


#ifdef needed
/*$ZEROBASEDSTRINGS ON*/

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
/*static */const int TCardinalHelper::MaxValue = 4294967295;
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

#endif // needed

int __fastcall TStringHelper::GetLength() const
{
	int result = 0;
	result = (int) m_Helped.Length();
	return result;
}

/*#static*/ bool __fastcall TStringHelper::CharInArray(const Char C, const Char* InArray, int InArray_maxidx)
{
  bool result = false;
	//Char AChar = L'\0';
	for(int i = 0; i < InArray_maxidx; i++)
  {
    WideChar AChar = InArray[i];
		if(AChar == C)
			return true;
  }
	result = false;
  return result;
}

/*#static*/ int __fastcall TStringHelper::Compare(const String StrA, int IndexA, const String StrB, int IndexB, int Length)
{
  int result = 0;
  result = Compare(StrA, IndexA, StrB, IndexB, Length, false, SysLocale.DefaultLCID);
  return result;
}

/*#static*/ int __fastcall TStringHelper::Compare(const String StrA, int IndexA, const String StrB, int IndexB, int Length, TLocaleID LocaleID)
{
  int result = 0;
  result = Compare(StrA, IndexA, StrB, IndexB, Length, false, LocaleID);
  return result;
}

/*#static*/ int __fastcall TStringHelper::Compare(const String StrA, int IndexA, const String StrB, int IndexB, int Length, bool IgnoreCase)
{
  int result = 0;
  result = Compare(StrA, IndexA, StrB, IndexB, Length, IgnoreCase, SysLocale.DefaultLCID);
  return result;
}

/*#static*/ int __fastcall TStringHelper::InternalCompare(const String StrA, int IndexA, const String StrB, int IndexB, int LengthA, int lengthb, bool IgnoreCase, TLocaleID LocaleID)
{
  int result = 0;
  if(IgnoreCase)
		result = InternalCompare(StrA, IndexA, StrB, IndexB, LengthA, lengthb, Sysutils__38, LocaleID);
  else
    result = InternalCompare(StrA, IndexA, StrB, IndexB, LengthA, lengthb, Sysutils__39, LocaleID);
  return result;
}

//  TCompareOption = (coLingIgnoreCase,
//    coLingIgnoreDiacritic, coIgnoreCase, coIgnoreKanatype,
//    coIgnoreNonSpace, coIgnoreSymbols, coIgnoreWidth,
//    coLingCasing, coDigitAsNumbers, coStringSort);

/*#static*/ unsigned long __fastcall TStringHelper::InternalMapOptionsToFlags(TCompareOptions AOptions)
{
  unsigned long result = 0;
  const unsigned long MapFlags[10/*# TCompareOption*/] = {(unsigned long) LINGUISTIC_IGNORECASE, (unsigned long) LINGUISTIC_IGNOREDIACRITIC, (unsigned long) NORM_IGNORECASE, (unsigned long) NORM_IGNOREKANATYPE, (unsigned long) NORM_IGNORENONSPACE, (unsigned long) NORM_IGNORESYMBOLS, (unsigned long) NORM_IGNOREWIDTH, (unsigned long) NORM_LINGUISTIC_CASING, (unsigned long) SORT_DIGITSASNUMBERS, (unsigned long) SORT_STRINGSORT};
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

/*#static*/ int __fastcall TStringHelper::InternalCompare(const String StrA, int IndexA, const String StrB, int IndexB, int LengthA, int lengthb, TCompareOptions Options, TLocaleID LocaleID)
{
  int result = 0;
  DWORD Flags = 0;
  if((StrA.Length() == 0) || (StrB.Length() == 0))
  {
    if(StrA.Length() > 0)
      result = 1;
    else
    {
      if(StrB.Length() > 0)
        result = -1;
      else
        result = 0;
    }
  }
  else
  {
    Flags = InternalMapOptionsToFlags(Options);
//		result = CompareStringW(LocaleID, Flags, ustr2pwchar(StrA, IndexA - 1), LengthA, ustr2pwchar(StrB, IndexB - 1), lengthb) - CSTR_EQUAL;
		result = CompareStringW(LocaleID, Flags, ustr2pwchar(StrA, IndexA), LengthA, ustr2pwchar(StrB, IndexB), lengthb) - CSTR_EQUAL;
	}
  return result;
}

/*#static*/ int __fastcall TStringHelper::Compare(const String StrA, int IndexA, const String StrB, int IndexB, int Length, bool IgnoreCase, TLocaleID LocaleID)
{
  int result = 0;
  result = InternalCompare(StrA, IndexA, StrB, IndexB, Length, Length, IgnoreCase, LocaleID);
  return result;
}

/*#static*/ int __fastcall TStringHelper::Compare(const String StrA, const String StrB, bool IgnoreCase)
{
  int result = 0;
  result = InternalCompare(StrA, 0, StrB, 0, StrA.Length(), StrB.Length(), IgnoreCase, SysLocale.DefaultLCID);
  return result;
}

/*#static*/ int __fastcall TStringHelper::Compare(const String StrA, const String StrB, bool IgnoreCase, TLocaleID LocaleID)
{
  int result = 0;
  result = InternalCompare(StrA, 0, StrB, 0, StrA.Length(), StrB.Length(), IgnoreCase, LocaleID);
  return result;
}

/*#static*/ int __fastcall TStringHelper::Compare(const String StrA, const String StrB, TCompareOptions Options, TLocaleID LocaleID)
{
  int result = 0;
  result = InternalCompare(StrA, 0, StrB, 0, StrA.Length(), StrB.Length(), Options, LocaleID);
  return result;
}

/*#static*/ int __fastcall TStringHelper::Compare(const String StrA, const String StrB, TCompareOptions Options)
{
  int result = 0;
  result = InternalCompare(StrA, 0, StrB, 0, StrA.Length(), StrB.Length(), Options, SysLocale.DefaultLCID);
  return result;
}

/*#static*/ int __fastcall TStringHelper::Compare(const String StrA, int IndexA, const String StrB, int IndexB, int Length, TCompareOptions Options, TLocaleID LocaleID)
{
  int result = 0;
  result = InternalCompare(StrA, IndexA, StrB, IndexB, Length, Length, Options, LocaleID);
  return result;
}

/*#static*/ int __fastcall TStringHelper::Compare(const String StrA, int IndexA, const String StrB, int IndexB, int Length, TCompareOptions Options)
{
  int result = 0;
  result = InternalCompare(StrA, IndexA, StrB, IndexB, Length, Length, Options, SysLocale.DefaultLCID);
  return result;
}

/*#static*/ int __fastcall TStringHelper::Compare(const String StrA, const String StrB)
{
  int result = 0;
  result = InternalCompare(StrA, 0, StrB, 0, StrA.Length(), StrB.Length(), Sysutils__40, SysLocale.DefaultLCID);
  return result;
}

/*#static*/ int __fastcall TStringHelper::Compare(const String StrA, const String StrB, TLocaleID LocaleID)
{
  int result = 0;
  result = InternalCompare(StrA, 0, StrB, 0, StrA.Length(), StrB.Length(), Sysutils__41, LocaleID);
  return result;
}

/*#static*/ int __fastcall TStringHelper::CompareOrdinal(const String StrA, const String StrB)
{
  int result = 0;
  int MaxLen = 0;
  if(StrA.Length() > StrB.Length())
    MaxLen = StrA.Length();
  else
    MaxLen = StrB.Length();
	result = StrLComp(ustr2pwchar(StrA, 0 - 1), ustr2pwchar(StrB, 0 - 1), (unsigned int) MaxLen);
  return result;
}

/*#static*/ int __fastcall TStringHelper::CompareOrdinal(const String StrA, int IndexA, const String StrB, int IndexB, int Length)
{
  int result = 0;
	result = StrLComp(ustr2pwchar(StrA, IndexA - 1), ustr2pwchar(StrB, IndexB - 1), (unsigned int) Length);
  return result;
}

/*#static*/ int __fastcall TStringHelper::CompareText(const String StrA, const String StrB)
{
  int result = 0;
  result = System::Sysutils::CompareText(StrA, StrB);
	return result;
}

/*#static*/ bool __fastcall TStringHelper::ToBoolean(const String s)
{
  bool result = false;
  result = StrToBool(s);
  return result;
}
#ifdef needed

/*#static*/ int __fastcall TStringHelper::ToInteger(const String s)
{
  int result = 0;
	result = TIntegerHelper::Parse(s);
  return result;
}

/*#static*/ __int64 __fastcall TStringHelper::ToInt64(const String s)
{
  __int64 result = 0;
  result = TInt64Helper::Parse(s);
  return result;
}

/*#static*/ float __fastcall TStringHelper::ToSingle(const String s)
{
  float result = 0.0F;
  result = TSingleHelper::Parse(s);
  return result;
}

/*#static*/ double __fastcall TStringHelper::ToDouble(const String s)
{
  double result = 0.0;
	result = TDoubleHelper::Parse(s);
  return result;
}

/*#static*/ long double __fastcall TStringHelper::ToExtended(const String s)
{
  long double result = 0.0L;
  result = TExtendedHelper::Parse(s);
  return result;
}

/*#static*/ String __fastcall TStringHelper::Parse(const int Value)
{
  String result;
  result = IntToStr(Value);
  return result;
}

/*#static*/ String __fastcall TStringHelper::Parse(const __int64 Value)
{
  String result;
  result = IntToStr(Value);
  return result;
}

/*#static*/ String __fastcall TStringHelper::Parse(const bool Value)
{
  String result;
  result = BoolToStr(Value);
  return result;
}

/*#static*/ String __fastcall TStringHelper::Parse(const long double Value)
{
  String result;
  result = FloatToStr(Value);
  return result;
}

/*#static*/ String __fastcall TStringHelper::LowerCase(const String s)
{
  String result;
  result = System::Sysutils::LowerCase(s);
  return result;
}

/*#static*/ String __fastcall TStringHelper::LowerCase(const String s, TLocaleOptions LocaleOptions)
{
  String result;
  result = System::Sysutils::LowerCase(s, LocaleOptions);
  return result;
}

/*#static*/ String __fastcall TStringHelper::UpperCase(const String s)
{
  String result;
  result = System::Sysutils::UpperCase(s);
  return result;
}

/*#static*/ String __fastcall TStringHelper::UpperCase(const String s, TLocaleOptions LocaleOptions)
{
  String result;
  result = System::Sysutils::UpperCase(s, LocaleOptions);
  return result;
}

int __fastcall TStringHelper::CompareTo(const String StrB)
{
  int result = 0;
	result = StrComp(ustr2pwchar(m_Helped), ustr2pwchar(StrB));
  return result;
}

bool __fastcall TStringHelper::Contains(const String Value)
{
	bool result = false;
	result = m_Helped.Pos(Value) > 0;
	return result;
}

/*#static*/ String __fastcall TStringHelper::Copy(const String Str)
{
  String result;
	result = Str.SubString(1-1, Str.Length());
  return result;
}
/*
void __fastcall TStringHelper::CopyTo(int sourceIndex, Char* Destination, int Destination_maxidx, int DestinationIndex, int Count)
{
	d2c_Move(ustr2pwchar(m_Helped) + sourceIndex, Destination, DestinationIndex, Count * sizeof(Char));
}  */

void __fastcall TStringHelper::CopyTo(int sourceIndex, OpenArrayRef<WideChar> Destination, int DestinationIndex, int Count)
{
	Move((void*) (m_Helped.c_str() + sourceIndex), Destination.data() + DestinationIndex, Count * sizeof(Char));
}

int __fastcall TStringHelper::CountChar(const Char C)
{
  int result = 0;
	int i = 0;
	int stop = 0;
  result = 0;
	for(stop = High(m_Helped), i = 1 /*# Low(self)*/; i <= stop; i++)
  {
    if(m_Helped[i - 1] == C)
      ++result;
  }
	return result;
}

/*#static*/ String __fastcall TStringHelper::Create(Char C, int Count)
{
  String result;
  result = StringOfChar(C, Count);
  return result;
}

/*#static*/ String __fastcall TStringHelper::Create(const Char* Value, int Value_maxidx, int StartIndex, int Length)
{
	String result;
	result.SetLength(Length);
	Move(Value + StartIndex, ustr2pwchar(result), Length * sizeof(Char));
	return result;
}

/*#static*/ String __fastcall TStringHelper::Create(const Char* Value, int Value_maxidx)
{
	String result;
	result.SetLength((int) Value_maxidx + 1);
	Move(Value + 0, ustr2pwchar(result), Value_maxidx + 1 * sizeof(Char));
  return result;
}

String __fastcall TStringHelper::DeQuotedString(const Char QuoteChar)
{
  String result;
  int i = 0;
  bool LastQuoted = false;
  int LPosDest = 0;
	DynamicArray<Char> LResult;
  if((m_Helped.Length() >= 2) && (m_Helped[1 /*# Low(self)*/ - 1] == QuoteChar) && (m_Helped[High(m_Helped) - 1] == QuoteChar))
  {
    int stop = 0;
    LastQuoted = false;
    LPosDest = 0;
		LResult.Length = m_Helped.Length() - 2;
    for(stop = High(m_Helped) - 1, i = 1 /*# Low(self)*/ + 1; i <= stop; i++)
    {
      if(m_Helped[i - 1] == QuoteChar)
      {
        if(LastQuoted)
        {
          LastQuoted = false;
					LResult[LPosDest] = m_Helped[i - 1];
          ++LPosDest;
        }
        else
        LastQuoted = true;
      }
      else
      {
        if(LastQuoted)
        {
          LastQuoted = false;
          // The quoted char is not doubled, should we put in the resulting string?
				}
				LResult[LPosDest] = m_Helped[i - 1];
        ++LPosDest;
      }
    }
		result = TStringHelper::Create(OpenArrayEx<Char>(LResult), LResult.Length, 0, LPosDest);
	}
	else
	result = m_Helped;
	return result;
}

String __fastcall TStringHelper::DeQuotedString()
{
  String result;
  result = this->DeQuotedString(L'\'');
  return result;
}

/*#static*/ bool __fastcall TStringHelper::EndsText(const String ASubText, const String AText)
{
  bool result = false;
  int SubTextLocation = 0;
  if(ASubText == Empty)
    result = true;
  else
  {
    SubTextLocation = AText.Length() - ASubText.Length();
		if((SubTextLocation >= 0) && (ByteType(AText, SubTextLocation) != mbTrailByte))
//			result = AnsiStrIComp(ustr2pwchar(ASubText), ustr2pwchar(AText, SubTextLocation - 1)) == 0;
			result = AnsiStrIComp(ustr2pwchar(ASubText), ustr2pwchar(AText, SubTextLocation)) == 0;
		else
			result = false;
  }
  return result;
}

bool __fastcall TStringHelper::EndsWith(const String Value, bool IgnoreCase)
{
  bool result = false;
  int SubTextLocation = 0;
	if(IgnoreCase)
    result = EndsText(Value, m_Helped);
  else
  {
    if(Value == Empty)
      result = true;
    else
    {
      SubTextLocation = m_Helped.Length() - Value.Length();
      if((SubTextLocation >= 0) && (ByteType(m_Helped, SubTextLocation) != mbTrailByte))
        result = TStringHelper::Compare(Value, 0, m_Helped, SubTextLocation, Value.Length(), Sysutils__43) == 0;
      else
        result = false;
    }
  }
  return result;
}

bool __fastcall TStringHelper::EndsWith(const String Value)
{
  bool result = false;
	result = EndsWith(Value, false);
  return result;
}

/*#static*/ bool __fastcall TStringHelper::Equals(const String A, const String B)
{
  bool result = false;
  result = A == B;
  return result;
}

bool __fastcall TStringHelper::Equals(const String Value)
{
  bool result = false;
  result = m_Helped == Value;
  return result;
}

/*#static*/ String __fastcall TStringHelper::Format(const String Format, const TVarRec* Args, int Args_maxidx)
{
  String result;
	result = System::Sysutils::Format(Format, Args, Args_maxidx);
  return result;
}
/*
Char __fastcall TStringHelper::GetChars(int Index) const
{
	Char result = L'\0';
	result = m_Helped[Index + 1];
  return result;
}
*/
int __fastcall TStringHelper::GetHashCode()
{
  int result = 0;
  UInt32 LRESULT = 0;
  int i = 0;
  String Temp;
// Used HashNameMBCS function
  int stop = 0;
	Temp = this->ToUpper(); // ToUpperInvariant ????
  LRESULT = 0;
  for(stop = Temp.Length() - 1, i = 0; i <= stop; i++)
  {
    LRESULT = (unsigned int) ((LRESULT << 5) | (LRESULT >> 27)); //ROL Result, 5
    LRESULT = (unsigned int) (LRESULT ^ ((UInt32) Temp[i - 1]));
  }
  result = (int) LRESULT;
  return result;
}

int __fastcall TStringHelper::IndexOf(Char Value, int StartIndex, int Count) const
{
  int result = 0;
  result = (int) (System::Pos(Value, m_Helped, StartIndex + 1) - 1);
  if((result + 1) > (StartIndex + Count))
    result = -1;
  return result;
}

int __fastcall TStringHelper::IndexOf(const String Value, int StartIndex, int Count) const
{
  int result = 0;
  result = (int) (System::Pos(Value, m_Helped, StartIndex + 1) - 1);
  if((result + Value.Length()) > (StartIndex + Count))
    result = -1;
  return result;
}

int __fastcall TStringHelper::IndexOf(const String Value, int StartIndex) const
{
  int result = 0;
  result = (int) (System::Pos(Value, m_Helped, StartIndex + 1) - 1);
  return result;
}

int __fastcall TStringHelper::IndexOf(const String Value) const
{
  int result = 0;
	result = (int) (m_Helped.Pos(Value) - 1);
  return result;
}

int __fastcall TStringHelper::IndexOf(Char Value) const
{
	int result = 0;
	result = (int) (m_Helped.Pos(String(Value)) - 1);
  return result;
}

int __fastcall TStringHelper::IndexOf(Char Value, int StartIndex) const
{
  int result = 0;
  result = (int) (System::Pos(Value, m_Helped, StartIndex + 1) - 1);
  return result;
}

int __fastcall TStringHelper::IndexOfAny(const Char* AnyOf, int AnyOf_maxidx, int StartIndex, int Count)
{
  int result = 0;
  int i = 0;
	//Char C = L'\0';
  int Max = 0;
	if((StartIndex + Count) >= m_Helped.Length())
    Max = m_Helped.Length();
  else
    Max = StartIndex + Count;
  i = StartIndex;
	while(i < Max)
	{
		for(int k = 0; k < AnyOf_maxidx + 1; k++)
		{
			WideChar C = AnyOf[k];
			if(m_Helped[i + 1] == C)
			{
				result = i;
				return result;
			}
		}
		++i;
  }
	result = -1;
	return result;
}

int __fastcall TStringHelper::IndexOfAny(const Char* AnyOf, int AnyOf_maxidx, int StartIndex)
{
  int result = 0;
	result = IndexOfAny(AnyOf, AnyOf_maxidx, StartIndex, m_Helped.Length());
	return result;
}

int __fastcall TStringHelper::IndexOfAny(const Char* AnyOf, int AnyOf_maxidx)
{
  int result = 0;
	result = IndexOfAny(AnyOf, AnyOf_maxidx, 0, m_Helped.Length());
  return result;
}

int __fastcall TStringHelper::IndexOfAnyUnquoted(const Char* AnyOf, int AnyOf_maxidx, Char StartQuote, Char EndQuote)
{
  int result = 0;
	result = IndexOfAnyUnquoted(AnyOf, AnyOf_maxidx, StartQuote, EndQuote, 0, m_Helped.Length());
  return result;
}

int __fastcall TStringHelper::IndexOfAnyUnquoted(const Char* AnyOf, int AnyOf_maxidx, Char StartQuote, Char EndQuote, int StartIndex)
{
  int result = 0;
	result = IndexOfAnyUnquoted(AnyOf, AnyOf_maxidx, StartQuote, EndQuote, StartIndex, m_Helped.Length());
  return result;
}

int __fastcall TStringHelper::IndexOfAnyUnquoted(const Char* AnyOf, int AnyOf_maxidx, Char StartQuote, Char EndQuote, int StartIndex, int Count)
{
  int result = 0;
  int i = 0;
	//Char C = L'\0';
  int Max = 0;
  int LInQuote = 0;
  bool LInQuoteBool = false;
	if((StartIndex + Count) >= m_Helped.Length())
		Max = m_Helped.Length();
  else
    Max = StartIndex + Count;
	i = StartIndex;
	if(StartQuote != EndQuote)
	{
    LInQuote = 0;
    while(i < Max)
    {
      if(m_Helped[i - 1] == StartQuote)
        ++LInQuote;
      else
      {
        if((m_Helped[i - 1] == EndQuote) && (LInQuote > 0))
          --LInQuote;
      }
      if(LInQuote == 0)
      {
        for(int i = 0; i < AnyOf_maxidx; i++)
				{
          WideChar C = AnyOf[i];
          if(m_Helped[i] == C)
            return i;
				}
      }
      ++i;
    }
  }
  else
  {
    LInQuoteBool = false;
    while(i < Max)
    {
      if(m_Helped[i] == StartQuote)
        LInQuoteBool = !LInQuoteBool;
      if(!LInQuoteBool)
      {
        for(int i = 0; i < AnyOf_maxidx; i++)
        {
          WideChar C = AnyOf[i];
          if(m_Helped[i] == C)
						return i;
        }
      }
      ++i;
    }
  }
  result = -1;
  return result;
}

String __fastcall TStringHelper::Insert(int StartIndex, const String Value)
{
  String result;
  m_Helped.Insert(Value,StartIndex + 1-1);
  result = m_Helped;
	return result;
}

bool __fastcall TStringHelper::IsDelimiter(const String Delimiters, int Index)
{
  bool result = false;
  result = false;
  if((Index < 1 /*# Low(String)*/) || (Index > High(m_Helped)) || (ByteType(m_Helped, Index) != mbSingleByte))
    return result;
	result = StrScan(ustr2pwchar(Delimiters), m_Helped[Index - 1]) != NULL;
  return result;
}

bool __fastcall TStringHelper::IsEmpty()
{
  bool result = false;
  result = m_Helped == Empty;
  return result;
}

/*#static*/ bool __fastcall TStringHelper::IsNullOrEmpty(const String Value)
{
  bool result = false;
  result = Value == Empty;
  return result;
}

/*#static*/ bool __fastcall TStringHelper::IsNullOrWhiteSpace(const String Value)
{
  bool result = false;
  result = TStringHelper(TStringHelper(Value).Trim()).Length == 0;
  return result;
}

/*#static*/ String __fastcall TStringHelper::Join(const String separator, const String* Values, int Values_maxidx)
{
  String result;
	result = Join(separator, Values, Values_maxidx, 0, (int) Values_maxidx + 1);
  return result;
}

/*#static String __fastcall TStringHelper::Join(const String separator, IEnumerable<String>* const Values)
{
  String result;
  if(Values != NULL)
    result = Join(separator, Values->GetEnumerator());
  else
    result = L"";
  return result;
}

/*#static String __fastcall TStringHelper::Join(const String separator, IEnumerator<String>* const Values)
{
  String result;
  if((Values != NULL) && Values->MoveNext)
  {
    result = Values->current;
    while(Values->MoveNext)
      result = result + separator + Values->current;
  }
  else
	result = L"";
  return result;
}
*/
/*#static*/ String __fastcall TStringHelper::Join(const String separator, const String* Values, int Values_maxidx, int StartIndex, int Count)
{
  String result;
  int i = 0;
  int Max = 0;
	if((Count == 0) || ((Values_maxidx + 1 == 0) && (StartIndex == 0)))
    result = L"";
  else
  {
    int stop = 0;
    if((Count < 0) || (StartIndex >= Values_maxidx + 1))
			throw new ERangeError(System_Sysconst_SRangeError);
		if((StartIndex + Count) > Values_maxidx + 1)
			Max = (int) Values_maxidx + 1;
		else
			Max = StartIndex + Count;
		result = Values[StartIndex];
		for(stop = Max - 1, i = StartIndex + 1; i <= stop; i++)
		{
			result = result + separator + Values[i];
		}
	}
	return result;
}

String ValueToString(const TVarRec& Val)
{
	String result;
	switch(Val.VType)
	{
		case  vtInteger:
		result = IntToStr(Val.VInteger);
		break;
		case  vtBoolean:
		result = BoolToStr(Val.VBoolean, true);
		break;
		case  vtChar:
		result = ((Char) Val.VChar);
		break;
		case  vtPChar:
		result = Val.VPChar;
		break;
		case  vtExtended:
		result = FloatToStr((*Val.VExtended));
		break;
		case  vtObject:
		result = Val.VObject->ClassName();
		break;
		case  vtClass:
		result = Val.VClass->ClassName();
		break;
		case  vtCurrency:
		result = CurrToStr((*Val.VCurrency));
		break;
		case  vtInt64:
		result = IntToStr((*((PInt64) Val.VInt64)));
		break;
		case  vtUnicodeString:
		result = *(UnicodeString*)Val.VUnicodeString;
		break;
		default:
		result = Format(L"(Unknown) : %d", ARRAYOFCONST((Val.VType)));
		break;
	}
	return result;
};


/*#static*/ String __fastcall TStringHelper::Join(const String separator, const TVarRec* Values, int Values_maxidx)
{
  String result;
  int i = 0;
  int Len = 0;

	Len = (int) Values_maxidx + 1;
	if(Len == 0)
		result = L"";
	else
	{
		int stop = 0;
		result = ValueToString(Values[0]);
		for(stop = Len - 1, i = 1; i <= stop; i++)
		{
			result = result + separator + ValueToString(Values[i]);
		}
  }
  return result;
}

int __fastcall TStringHelper::LastIndexOf(const String Value, int StartIndex)
{
  int result = 0;
  result = LastIndexOf(Value, StartIndex, StartIndex + 1);
  return result;
}

int __fastcall TStringHelper::LastIndexOf(Char Value, int StartIndex)
{
  int result = 0;
  result = LastIndexOf(Value, StartIndex, StartIndex + 1);
  return result;
}

int __fastcall TStringHelper::LastIndexOf(Char Value)
{
  int result = 0;
  result = LastIndexOf(Value, m_Helped.Length() - 1, m_Helped.Length());
  return result;
}

int __fastcall TStringHelper::LastIndexOf(const String Value)
{
  int result = 0;
  result = LastIndexOf(Value, m_Helped.Length() - 1, m_Helped.Length());
  return result;
}

int __fastcall TStringHelper::LastDelimiter(const String delims)
{
  int result = 0;
  int i = 0;
  int j = 0;
  i = High(m_Helped);
  while(i >= 1 /*# Low(String)*/)
  {
    int stop = 0;
    for(stop = High(delims), j = 1 /*# Low(String)*/; j <= stop; j++)
    {
      if(this->Chars[i] == TStringHelper(delims).Chars[j])
        return i;
    }
    --i;
  }
  result = -1;
  return result;
}

int __fastcall TStringHelper::LastIndexOf(const String Value, int StartIndex, int Count)
{
  int result = 0;
  int i = 0;
  int Min = 0;
  if(Value.Length() == 0)
    return -1;
  if(StartIndex < m_Helped.Length())
    i = StartIndex - Value.Length() + 1;
  else
    i = m_Helped.Length() - Value.Length();
  if((StartIndex - Count) < 0)
    Min = 0;
  else
    Min = StartIndex - Count + 1;
  while(i >= Min)
  {
    if(StrLComp(&ustr2pwchar(m_Helped)[i], ustr2pwchar(Value), (unsigned int) Value.Length()) == 0)
      return i;
    --i;
  }
  result = -1;
  return result;
}

int __fastcall TStringHelper::LastIndexOf(Char Value, int StartIndex, int Count)
{
  int result = 0;
  int i = 0;
  int Min = 0;
  if(StartIndex < m_Helped.Length())
    i = StartIndex;
  else
    i = m_Helped.Length() - 1;
  if((StartIndex - Count) < 0)
    Min = 0;
  else
    Min = StartIndex - Count + 1;
  while(i >= Min)
  {
    if(m_Helped[i - 1] == Value)
      return i;
    --i;
  }
  result = -1;
  return result;
}

int __fastcall TStringHelper::LastIndexOfAny(const Char* AnyOf, int AnyOf_maxidx)
{
  int result = 0;
	result = LastIndexOfAny(AnyOf, AnyOf_maxidx, m_Helped.Length() - 1, m_Helped.Length());
  return result;
}

int __fastcall TStringHelper::LastIndexOfAny(const Char* AnyOf, int AnyOf_maxidx, int StartIndex, int Count)
{
  int result = 0;
  int i = 0;
  int Min = 0;
  Char C = L'\0';
  if(StartIndex < m_Helped.Length())
    i = StartIndex;
  else
    i = m_Helped.Length() - 1;
  if((StartIndex - Count) < 0)
    Min = 0;
  else
    Min = StartIndex - Count + 1;
  while(i >= Min)
  {
		//for(WideChar element_0 : *(Char(*)[AnyOf_maxidx])AnyOf)
		for(int i = 0; i < AnyOf_maxidx + 1; i++)
    {
			C = AnyOf[i];
      if(m_Helped[i - 1] == C)
				return i;
    }
    --i;
  }
  result = -1;
  return result;
}

int __fastcall TStringHelper::LastIndexOfAny(const Char* AnyOf, int AnyOf_maxidx, int StartIndex)
{
  int result = 0;
	result = LastIndexOfAny(AnyOf, AnyOf_maxidx, StartIndex, m_Helped.Length());
  return result;
}

String __fastcall TStringHelper::PadLeft(int TotalWidth)
{
  String result;
  result = PadLeft(TotalWidth, L' ');
  return result;
}

String __fastcall TStringHelper::PadLeft(int TotalWidth, Char PaddingChar)
{
  String result;
	TotalWidth = TotalWidth - m_Helped.Length();
  if(TotalWidth > 0)
    result = System::StringOfChar(PaddingChar, TotalWidth) + m_Helped;
  else
    result = m_Helped;
  return result;
}

String __fastcall TStringHelper::PadRight(int TotalWidth)
{
  String result;
  result = PadRight(TotalWidth, L' ');
  return result;
}

String __fastcall TStringHelper::PadRight(int TotalWidth, Char PaddingChar)
{
  String result;
	TotalWidth = TotalWidth - m_Helped.Length();
  if(TotalWidth > 0)
    result = m_Helped + System::StringOfChar(PaddingChar, TotalWidth);
  else
		result = m_Helped;
	return result;
}

String __fastcall TStringHelper::QuotedString(const Char QuoteChar)
{
  String result;
  int i = 0;
  int stop = 0;
	result = TStringHelper(m_Helped).SubString(0);
  for(stop = 0, i = result.Length() - 1; i >= stop; i--)
  {
		if(TStringHelper(result).Chars[i] == QuoteChar)
			result = result.Insert(QuoteChar, i);
  }
	result = String(QuoteChar) + result + String(QuoteChar);
	return result;
}

String __fastcall TStringHelper::QuotedString()
{
  String result;
  int i = 0;
  int stop = 0;
	result = TStringHelper(m_Helped).SubString(0);
  for(stop = 0, i = result.Length() - 1; i >= stop; i--)
  {
    if(TStringHelper(result).Chars[i] == L'\'')
			result = result.Insert(L'\'', i);
  }
  result = String(L"\'") + result + L"\'";
  return result;
}

String __fastcall TStringHelper::Remove(int StartIndex, int Count)
{
  String result;
  result = m_Helped;
	result.Delete(StartIndex + 1-1,  Count);
  return result;
}

String __fastcall TStringHelper::Remove(int StartIndex)
{
  String result;
	result = m_Helped;
	result.Delete(StartIndex + 1-1,  result.Length());
  return result;
}

String __fastcall TStringHelper::Replace(Char OldChar, Char NewChar)
{
  String result;
  result = System::Sysutils::StringReplace(m_Helped, String(OldChar), String(NewChar), Sysutils__44);
  return result;
}

String __fastcall TStringHelper::Replace(Char OldChar, Char NewChar, TReplaceFlags ReplaceFlags)
{
  String result;
  result = System::Sysutils::StringReplace(m_Helped, String(OldChar), String(NewChar), ReplaceFlags);
  return result;
}

String __fastcall TStringHelper::Replace(const String OldValue, const String NewValue)
{
  String result;
  result = System::Sysutils::StringReplace(m_Helped, OldValue, NewValue, Sysutils__45);
  return result;
}

String __fastcall TStringHelper::Replace(const String OldValue, const String NewValue, TReplaceFlags ReplaceFlags)
{
  String result;
  result = System::Sysutils::StringReplace(m_Helped, OldValue, NewValue, ReplaceFlags);
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const Char* separator, int separator_maxidx, TStringSplitOptions Options)
{
	TArray<String> result;
  result = Split(separator, separator_maxidx, MaxInt, Options);
	return result;
}

TArray<String> __fastcall TStringHelper::Split(const Char* separator, int separator_maxidx, int Count)
{
	TArray<String> result;
	result = Split(separator, separator_maxidx, Count, TStringSplitOptions::None);
	return result;
}

TArray<String> __fastcall TStringHelper::Split(const Char* separator, int separator_maxidx)
{
	TArray<String> result;
	result = Split(separator, separator_maxidx, MaxInt, TStringSplitOptions::None);
  return result;
}

int __fastcall TStringHelper::IndexOfAny(const String* Values, int Values_maxidx, int& Index, int StartIndex)
{
  int result = 0;
  int C = 0;
  int P = 0;
  int IoA = 0;
  int stop = 0;
  IoA = -1;
	for(stop = (int) Values_maxidx /*# High(Values) */, C = 0; C <= stop; C++)
  {
    P = IndexOf(Values[C], StartIndex);
    if((P >= 0) && ((P < IoA) || (IoA ==  - 1)))
    {
			IoA = P;
      Index = C;
    }
  }
  result = IoA;
  return result;
}

int __fastcall TStringHelper::IndexOfAnyUnquoted(const String* Values, int Values_maxidx, Char StartQuote, Char EndQuote, int& Index, int StartIndex)
{
  int result = 0;
  int C = 0;
  int P = 0;
	int IoA = 0;
  int stop = 0;
  IoA = -1;
  for(stop = (int) Values_maxidx /*# High(Values) */, C = 0; C <= stop; C++)
  {
    P = IndexOfQuoted(Values[C], StartQuote, EndQuote, StartIndex);
    if((P >= 0) && ((P < IoA) || (IoA ==  - 1)))
    {
      IoA = P;
      Index = C;
    }
  }
  result = IoA;
  return result;
}

int __fastcall PosX(const UnicodeString Substr, const UnicodeString Str, int Offset)
{
  int result = 0;
  int i = 0;
  int LIterCnt = 0;
  int l = 0;
  int j = 0;
  PWideChar PSubStr = NULL;
  PWideChar ps = NULL;
  l = (int) Substr.Length();
  LIterCnt = (int) (Str.Length() - Offset - l + 1);
  if((Offset > 0) && (LIterCnt >= 0) && (l > 0))
  {
    int stop = 0;
    PSubStr = ustr2pwchar(Substr);
    ps = ustr2pwchar(Str);
    ps += Offset;
    for(stop = LIterCnt, i = 0; i <= stop; i++)
    {
      j = 0;
      while((j >= 0) && (j < l))
      {
        if(ps[i + j] == PSubStr[j])
          ++j;
        else
          j = -1;
      }
      if(j >= l)
        return i + Offset;
    }
  }
  result = 0;
  return result;
}

int __fastcall TStringHelper::IndexOfQuoted(const String Value, Char StartQuote, Char EndQuote, int StartIndex)
{
  int result = 0;
  int i = 0;
  int LIterCnt = 0;
  int l = 0;
  int j = 0;
  PWideChar PSubStr = NULL;
  PWideChar ps = NULL;
  int LInQuote = 0;
  bool LInQuoteBool = false;
  l = Value.Length();
  LIterCnt = m_Helped.Length() - StartIndex - l + 1;
  if((StartIndex >= 0) && (LIterCnt >= 0) && (l > 0))
  {
    PSubStr = ustr2pwchar(Value);
    ps = ustr2pwchar(m_Helped);
    ps += StartIndex;
    if(StartQuote != EndQuote)
    {
      int stop = 0;
      LInQuote = 0;
      for(stop = LIterCnt, i = 0; i <= stop; i++)
      {
        j = 0;
        while((j >= 0) && (j < l))
        {
          if(ps[i + j] == StartQuote)
            ++LInQuote;
          else
          {
            if(ps[i + j] == EndQuote)
              --LInQuote;
          }
          if(LInQuote > 0)
            j = -1;
          else
          {
            if(ps[i + j] == PSubStr[j])
              ++j;
            else
              j = -1;
          }
        }
        if(j >= l)
          return i + StartIndex;
      }
    }
    else
    {
      int stop = 0;
      LInQuoteBool = false;
      for(stop = LIterCnt, i = 0; i <= stop; i++)
      {
        j = 0;
        while((j >= 0) && (j < l))
        {
          if(ps[i + j] == StartQuote)
            LInQuoteBool = !LInQuoteBool;
          if(LInQuoteBool)
            j = -1;
          else
          {
            if(ps[i + j] == PSubStr[j])
              ++j;
            else
              j = -1;
          }
        }
        if(j >= l)
          return i + StartIndex;
      }
    }
  }
  result = -1;
  return result;
}

TArray<String> __fastcall TStringHelper::InternalSplit(TSplitKind SplitType, const Char* SeparatorC, int SeparatorC_maxidx, const String* separators, int separators_maxidx, Char QuoteStart, Char QuoteEnd, int Count, TStringSplitOptions Options)
{
	TArray<String> result;
  const int DeltaGrow = 32;
  int NextSeparator = 0;
	int LastIndex = 0;
  int total = 0;
  int CurrentLength = 0;
  int SeparatorIndex = 0;
  String s;
  total = 0;
  LastIndex = 0;
  CurrentLength = 0;
  SeparatorIndex = 0;
  switch(SplitType)
  {
    case  TSplitKind::StringSeparatorNoQuoted:
    NextSeparator = IndexOfAny(separators, separators_maxidx, SeparatorIndex, LastIndex);
    break;
    case  TSplitKind::StringSeparatorQuoted:
    NextSeparator = IndexOfAnyUnquoted(separators, separators_maxidx, QuoteStart, QuoteEnd, SeparatorIndex, LastIndex);
    break;
    case  TSplitKind::CharSeparatorNoQuoted:
    NextSeparator = IndexOfAny(SeparatorC, SeparatorC_maxidx, LastIndex);
    break;
    case  TSplitKind::CharSeparatorQuoted:
    NextSeparator = IndexOfAnyUnquoted(SeparatorC, SeparatorC_maxidx, QuoteStart, QuoteEnd, LastIndex);
    break;
    default:
    NextSeparator = -1;
    break;
  }
  while((NextSeparator >= 0) && (total < Count))
  {
		s = m_Helped.SubString(LastIndex + 1, NextSeparator - LastIndex);
		if((s != L"") || ((s == L"") && (Options != TStringSplitOptions::ExcludeEmpty)))
    {
      ++total;
      if(CurrentLength < total)
      {
        CurrentLength = total + DeltaGrow;
        result.Length = CurrentLength;
      }
			result[total - 1] = s;
    }
    switch(SplitType)
    {
      case  TSplitKind::StringSeparatorNoQuoted:
      {
        LastIndex = NextSeparator + separators[SeparatorIndex].Length();
        NextSeparator = IndexOfAny(separators, separators_maxidx, SeparatorIndex, LastIndex);
      }
      break;
      case  TSplitKind::StringSeparatorQuoted:
      {
        LastIndex = NextSeparator + separators[SeparatorIndex].Length();
        NextSeparator = IndexOfAnyUnquoted(separators, separators_maxidx, QuoteStart, QuoteEnd, SeparatorIndex, LastIndex);
      }
      break;
			case  TSplitKind::CharSeparatorNoQuoted:
      {
        LastIndex = NextSeparator + 1;
        NextSeparator = IndexOfAny(SeparatorC, SeparatorC_maxidx, LastIndex);
      }
      break;
      case  TSplitKind::CharSeparatorQuoted:
      {
        LastIndex = NextSeparator + 1;
        NextSeparator = IndexOfAnyUnquoted(SeparatorC, SeparatorC_maxidx, QuoteStart, QuoteEnd, LastIndex);
      }
      break;
      default:
        ;
      break;
    }
  }
  if((LastIndex < m_Helped.Length()) && (total < Count))
  {
    ++total;
    result.Length = total;
    result[total - 1] = m_Helped.SubString(LastIndex, m_Helped.Length() - LastIndex);
	}
  else
  result.Length = total;
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const String* separator, int separator_maxidx, int Count, TStringSplitOptions Options)
{
	TArray<String> result;
	result = InternalSplit(TSplitKind::StringSeparatorNoQuoted, NULL, 0, separator, separator_maxidx, ((Char) 0), ((Char) 0), Count, Options);
	return result;
}

TArray<String> __fastcall TStringHelper::Split(const String* separator, int separator_maxidx, Char QuoteStart, Char QuoteEnd, int Count, TStringSplitOptions Options)
{
	TArray<String> result;
	result = InternalSplit(TSplitKind::StringSeparatorQuoted, NULL, 0, separator, separator_maxidx, QuoteStart, QuoteEnd, Count, Options);
	return result;
}

TArray<String> __fastcall TStringHelper::Split(const Char* separator, int separator_maxidx, int Count, TStringSplitOptions Options)
{
	TArray<String> result;
	result = InternalSplit(TSplitKind::CharSeparatorNoQuoted, separator, separator_maxidx, NULL, 0, ((Char) 0), ((Char) 0), Count, Options);
	return result;
}

TArray<String> __fastcall TStringHelper::Split(const Char* separator, int separator_maxidx, Char QuoteStart, Char QuoteEnd, int Count, TStringSplitOptions Options)
{
  TArray<String> result;
	result = InternalSplit(TSplitKind::CharSeparatorQuoted, separator, separator_maxidx, NULL, 0, QuoteStart, QuoteEnd, Count, Options);
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const Char* separator, int separator_maxidx, Char QuoteStart, Char QuoteEnd)
{
  TArray<String> result;
  result = Split(separator, separator_maxidx, QuoteStart, QuoteEnd, MaxInt, TStringSplitOptions::None);
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const Char* separator, int separator_maxidx, Char Quote)
{
  TArray<String> result;
	result = Split(separator, separator_maxidx, Quote, Quote, MaxInt, TStringSplitOptions::None);
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const Char* separator, int separator_maxidx, Char QuoteStart, Char QuoteEnd, int Count)
{
  TArray<String> result;
	result = Split(separator, separator_maxidx, QuoteStart, QuoteEnd, Count, TStringSplitOptions::None);
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const Char* separator, int separator_maxidx, Char QuoteStart, Char QuoteEnd, TStringSplitOptions Options)
{
  TArray<String> result;
  result = Split(separator, separator_maxidx, QuoteStart, QuoteEnd, MaxInt, Options);
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const String* separator, int separator_maxidx)
{
  TArray<String> result;
	result = Split(separator, separator_maxidx, MaxInt, TStringSplitOptions::None);
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const String* separator, int separator_maxidx, int Count)
{
  TArray<String> result;
	result = Split(separator, separator_maxidx, Count, TStringSplitOptions::None);
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const String* separator, int separator_maxidx, TStringSplitOptions Options)
{
  TArray<String> result;
  result = Split(separator, separator_maxidx, MaxInt, Options);
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const String* separator, int separator_maxidx, Char Quote)
{
  TArray<String> result;
	result = Split(separator, separator_maxidx, Quote, Quote, MaxInt, TStringSplitOptions::None);
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const String* separator, int separator_maxidx, Char QuoteStart, Char QuoteEnd)
{
  TArray<String> result;
	result = Split(separator, separator_maxidx, QuoteStart, QuoteEnd, MaxInt, TStringSplitOptions::None);
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const String* separator, int separator_maxidx, Char QuoteStart, Char QuoteEnd, TStringSplitOptions Options)
{
  TArray<String> result;
  result = Split(separator, separator_maxidx, QuoteStart, QuoteEnd, MaxInt, Options);
  return result;
}

TArray<String> __fastcall TStringHelper::Split(const String* separator, int separator_maxidx, Char QuoteStart, Char QuoteEnd, int Count)
{
	TArray<String> result;
	result = Split(separator, separator_maxidx, QuoteStart, QuoteEnd, Count, TStringSplitOptions::None);
	return result;
}

bool __fastcall TStringHelper::StartsWith(const String Value)
{
  bool result = false;
  result = StartsWith(Value, false);
  return result;
}

bool __fastcall TStringHelper::StartsWith(const String Value, bool IgnoreCase)
{
  bool result = false;
  if(Value == L"")
    result = true;
  else
	{
    if(!IgnoreCase)
			result = StrLComp(ustr2pwchar(m_Helped), ustr2pwchar(Value), (unsigned int) Value.Length()) == 0;
    else
			result = StrLIComp(ustr2pwchar(m_Helped), ustr2pwchar(Value), (unsigned int) Value.Length()) == 0;
  }
	return result;
}

String __fastcall TStringHelper::SubString(int StartIndex)
{
	String result;
	result = m_Helped.SubString(StartIndex + 1, m_Helped.Length() - StartIndex);
	return result;
}

String __fastcall TStringHelper::SubString(int StartIndex, int Length)
{
  String result;
	result = m_Helped.SubString(StartIndex + 1, Length);
  return result;
}

bool __fastcall TStringHelper::ToBoolean()
{
  bool result = false;
  result = StrToBool(m_Helped);
  return result;
}

int __fastcall TStringHelper::ToInteger()
{
  int result = 0;
	result = TIntegerHelper::Parse(m_Helped);
  return result;
}

__int64 __fastcall TStringHelper::ToInt64()
{
  __int64 result = 0;
  result = TInt64Helper::Parse(m_Helped);
  return result;
}

float __fastcall TStringHelper::ToSingle()
{
  float result = 0.0F;
  result = TSingleHelper::Parse(m_Helped);
  return result;
}

double __fastcall TStringHelper::ToDouble()
{
  double result = 0.0;
  result = TDoubleHelper::Parse(m_Helped);
  return result;
}

long double __fastcall TStringHelper::ToExtended()
{
  long double result = 0.0L;
  result = TExtendedHelper::Parse(m_Helped);
  return result;
}

TArray<Char> __fastcall TStringHelper::ToCharArray()
{
	TArray<Char> result;
  result = ToCharArray(0, m_Helped.Length());
	return result;
}

TArray<Char> __fastcall TStringHelper::ToCharArray(int StartIndex, int Length)
{
	TArray<Char> result;
	result.Length = Length;
	d2c_Move(ustr2pwchar(m_Helped) + StartIndex, result, 0, Length * sizeof(Char));
  return result;
}
#endif // needed
String __fastcall TStringHelper::ToLower()
{
	String result;
  result = ToLower(SysLocale.DefaultLCID);
  return result;
}

String __fastcall TStringHelper::ToLower(TLocaleID LocaleID)
{
  String result;
  result = m_Helped;
  if(result != L"")
  {
    UniqueString(result);
		if(LCMapStringW(LocaleID, (DWORD) (LCMAP_LOWERCASE | LCMAP_LINGUISTIC_CASING), ustr2pwchar(m_Helped), m_Helped.Length(), ustr2pwchar(result), result.Length()) == 0)
      RaiseLastOSError();
  }
  return result;
}

String __fastcall TStringHelper::ToLowerInvariant()
{
	String result;
  result = m_Helped;
  if(result != L"")
  {
    UniqueString(result);
		if(LCMapStringW(LOCALE_INVARIANT, (DWORD) LCMAP_LOWERCASE, ustr2pwchar(m_Helped), m_Helped.Length(), ustr2pwchar(result), result.Length()) == 0) /*or LCMAP_LINGUISTIC_CASING*/
      RaiseLastOSError();
  }
  return result;
}

String __fastcall TStringHelper::ToUpper()
{
  String result;
  result = ToUpper(SysLocale.DefaultLCID);
  return result;
}

String __fastcall TStringHelper::ToUpper(TLocaleID LocaleID)
{
  String result;
  result = m_Helped;
  if(result != L"")
  {
    UniqueString(result);
		if(LCMapStringW(LocaleID, (DWORD) (LCMAP_UPPERCASE | LCMAP_LINGUISTIC_CASING), ustr2pwchar(m_Helped), m_Helped.Length(), ustr2pwchar(result), result.Length()) == 0)
      RaiseLastOSError();
	}
  return result;
}

String __fastcall TStringHelper::ToUpperInvariant()
{
  String result;
  LCID MapLocale = 0;
  result = m_Helped;
  if(result != L"")
  {
    UniqueString(result);
    if(TOSVersion::Check(5, 1))
      MapLocale = (unsigned long) LOCALE_INVARIANT;
    else
      MapLocale = (unsigned long) LOCALE_SYSTEM_DEFAULT;
		if(LCMapStringW(MapLocale, (DWORD) LCMAP_UPPERCASE, ustr2pwchar(m_Helped), m_Helped.Length(), ustr2pwchar(result), result.Length()) == 0) /*or LCMAP_LINGUISTIC_CASING*/
			RaiseLastOSError();
  }
  return result;
}

String __fastcall TStringHelper::Trim()
{
  String result;
  int i = 0;
  int l = 0;
  l = m_Helped.Length() - 1;
  i = 0;
  if((l >  - 1) && (m_Helped[i - 1] > L' ') && (m_Helped[l - 1] > L' '))
    return m_Helped;
  while((i <= l) && (m_Helped[i - 1] <= L' '))
    ++i;
  if(i > l)
    return L"";
  while(m_Helped[l - 1] <= L' ')
    --l;
  result = m_Helped.SubString(i, l - i + 1);
  return result;
}

String __fastcall TStringHelper::TrimLeft()
{
  String result;
  int i = 0;
  int l = 0;
  l = m_Helped.Length() - 1;
  i = 0;
  while((i <= l) && (m_Helped[i - 1] <= L' '))
    ++i;
  if(i > 0)
    result = m_Helped.SubString(i, m_Helped.Length() - i);
  else
    result = m_Helped;
  return result;
}

String __fastcall TStringHelper::TrimRight()
{
  String result;
  int i = 0;
  i = m_Helped.Length() - 1;
  if((i >= 0) && (m_Helped[i - 1] > L' '))
    result = m_Helped;
  else
  {
		//while((i >= 0) && (this->Chars[i] <= L' '))
		while((i >= 0) && (m_Helped[i + 1] <= L' '))
			--i;
    result = m_Helped.SubString(0, i + 1);
  }
  return result;
}

String __fastcall TStringHelper::Trim(const Char* TrimChars, int TrimChars_maxidx)
{
	String result;
  int i = 0;
	int l = 0;
  l = m_Helped.Length() - 1;
  i = 0;
	if((l > 0) && (!CharInArray(m_Helped[i - 1], TrimChars, TrimChars_maxidx)) && (!CharInArray(m_Helped[l - 1], TrimChars, TrimChars_maxidx)))
		return m_Helped;
  while((i <= l) && (CharInArray(m_Helped[i - 1], TrimChars, TrimChars_maxidx)))
		++i;
  if(i > l)
    return L"";
  while(CharInArray(m_Helped[l - 1], TrimChars, TrimChars_maxidx))
    --l;
	result = m_Helped.SubString(i, l - i + 1);
  return result;
}

String __fastcall TStringHelper::TrimLeft(const Char* TrimChars, int TrimChars_maxidx)
{
  String result;
  int i = 0;
  int l = 0;
  l = m_Helped.Length();
  i = 0;
  while((i < l) && (CharInArray(m_Helped[i - 1], TrimChars, TrimChars_maxidx)))
    ++i;
	if(i > 0)
		result = m_Helped.SubString(i, m_Helped.Length() - i);
  else
    result = m_Helped;
  return result;
}

String __fastcall TStringHelper::TrimRight(const Char* TrimChars, int TrimChars_maxidx)
{
  String result;
  int i = 0;
	i = m_Helped.Length() - 1;
  if((i >= 0) && (!CharInArray(m_Helped[i - 1], TrimChars, TrimChars_maxidx)))
    return m_Helped;
  --i;
  while((i >= 0) && (CharInArray(m_Helped[i - 1], TrimChars, TrimChars_maxidx)))
    --i;
	result = m_Helped.SubString(0, i + 1);
  return result;
}

String __fastcall TStringHelper::TrimEnd(const Char* TrimChars, int TrimChars_maxidx)
{
  String result;
  result = this->TrimRight(TrimChars, TrimChars_maxidx);
  return result;
}

String __fastcall TStringHelper::TrimStart(const Char* TrimChars, int TrimChars_maxidx)
{
  String result;
  result = this->TrimLeft(TrimChars, TrimChars_maxidx);
  return result;
}
/*$ZEROBASEDSTRINGS OFF*/ // Desktop platforms use One-based string

#ifdef needed

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

/*#static*/ float __fastcall TSingleHelper::Parse(const String s)
{
	float result = 0.0F;
	if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidFloat2, ARRAYOFCONST((s, String(L"Single"))));
  return result;
}

/*#static*/ float __fastcall TSingleHelper::Parse(const String s, const TFormatSettings& AFormatSettings)
{
	float result = 0.0F;
	if(!TryParse(s, result, AFormatSettings))
		ConvertErrorFmt(System_Sysconst_SInvalidFloat2, ARRAYOFCONST((s, L"Single")));
  return result;
}

/*#static*/ bool __fastcall TSingleHelper::TryParse(const String s, float& Value)
{
  bool result = false;
  long double e = 0.0L;
	result = TryStrToFloat(s, e);
  result = result && (TSingleHelper::MinValue <= e) && (e <= TSingleHelper::MaxValue);
  if(result)
    Value = (float) e;
  return result;
}

/*#static*/ bool __fastcall TSingleHelper::TryParse(const String s, float& Value, const TFormatSettings& AFormatSettings)
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
// todo		System::Error(System::TRuntimeError::reRangeError);
	result = InternalGetBytes(Index);
  return result;
}

UInt16 __fastcall TSingleHelper::GetWords(unsigned int Index) const
{
  UInt16 result = 0;
// todo	if(Index >= 2)
// todo		System::Error(TRuntimeError::reRangeError);
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
		System::Error(reRangeError);
  InternalSetBytes(Index, Value);
}

void __fastcall TSingleHelper::SetWords(unsigned int Index, const UInt16 Value)
{
	if(Index >= 2)
		System::Error(reRangeError);
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

/*#static*/ double __fastcall TDoubleHelper::Parse(const String s)
{
  double result = 0.0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidFloat2, ARRAYOFCONST((s, L"Double")));
  return result;
}

/*#static*/ double __fastcall TDoubleHelper::Parse(const String s, const TFormatSettings& AFormatSettings)
{
  double result = 0.0;
  if(!TryParse(s, result, AFormatSettings))
		ConvertErrorFmt(System_Sysconst_SInvalidFloat2, ARRAYOFCONST((s, L"Double")));
  return result;
}

/*#static*/ bool __fastcall TDoubleHelper::TryParse(const String s, double& Value)
{
  bool result = false;
  result = TryStrToFloat(s, Value);
  return result;
}

/*#static*/ bool __fastcall TDoubleHelper::TryParse(const String s, double& Value, const TFormatSettings& AFormatSettings)
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
		System::Error(reRangeError);
  result = InternalGetBytes(Index);
  return result;
}

UInt16 __fastcall TDoubleHelper::GetWords(unsigned int Index) const
{
  UInt16 result = 0;
  if(Index >= 4)
    System::Error(reRangeError);
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
    System::Error(reRangeError);
  InternalSetBytes(Index, Value);
}

void __fastcall TDoubleHelper::SetWords(unsigned int Index, const UInt16 Value)
{
  if(Index >= 4)
    System::Error(reRangeError);
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

/*#static*/ long double __fastcall TExtendedHelper::Parse(const String s)
{
  long double result = 0.0L;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidFloat2, ARRAYOFCONST((s, L"Extended")));
  return result;
}

/*#static*/ long double __fastcall TExtendedHelper::Parse(const String s, const TFormatSettings& AFormatSettings)
{
  long double result = 0.0L;
	if(!TryParse(s, result, AFormatSettings))
		ConvertErrorFmt(System_Sysconst_SInvalidFloat2, ARRAYOFCONST((s, L"Extended")));
  return result;
}

/*#static*/ bool __fastcall TExtendedHelper::TryParse(const String s, long double& Value)
{
  bool result = false;
  result = TryStrToFloat(s, Value);
  return result;
}

/*#static*/ bool __fastcall TExtendedHelper::TryParse(const String s, long double& Value, const TFormatSettings& AFormatSettings)
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
    System::Error(reRangeError);
  result = InternalGetBytes(Index);
  return result;
}

UInt16 __fastcall TExtendedHelper::GetWords(unsigned int Index) const
{
  UInt16 result = 0;
  if(Index >= 4)
    System::Error(reRangeError);
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
    System::Error(reRangeError);
  InternalSetBytes(Index, Value);
}

void __fastcall TExtendedHelper::SetWords(unsigned int Index, const UInt16 Value)
{
  if(Index >= 4)
		System::Error(reRangeError);
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

/*#static*/ unsigned char __fastcall TByteHelper::Parse(const String s)
{
  unsigned char result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"Byte")));
  return result;
}

/*#static*/ bool __fastcall TByteHelper::TryParse(const String s, unsigned char& Value)
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

/*#static*/ signed char __fastcall TShortIntHelper::Parse(const String s)
{
  signed char result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"ShortInt")));
  return result;
}

/*#static*/ bool __fastcall TShortIntHelper::TryParse(const String s, signed char& Value)
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

/*#static*/ WORD __fastcall TWordHelper::Parse(const String s)
{
  WORD result = 0;
  if(!TryParse(s, result))
    ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"Word")));
  return result;
}

/*#static*/ bool __fastcall TWordHelper::TryParse(const String s, WORD& Value)
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

/*#static*/ short int __fastcall TSmallIntHelper::Parse(const String s)
{
  short int result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"SmallInt")));
  return result;
}

/*#static*/ bool __fastcall TSmallIntHelper::TryParse(const String s, short int& Value)
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

/*#static*/ unsigned int __fastcall TCardinalHelper::Parse(const String s)
{
  unsigned int result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"Cardinal")));
  return result;
}

/*#static*/ bool __fastcall TCardinalHelper::TryParse(const String s, unsigned int& Value)
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

/*#static*/ int __fastcall TIntegerHelper::Parse(const String s)
{
  int result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"Integer")));
  return result;
}

/*#static*/ bool __fastcall TIntegerHelper::TryParse(const String s, int& Value)
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

/*#static*/ unsigned __int64 __fastcall TUInt64Helper::Parse(const String s)
{
  unsigned __int64 result = 0L;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"UInt64")));
  return result;
}

/*#static*/ bool __fastcall TUInt64Helper::TryParse(const String s, unsigned __int64& Value)
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

/*#static*/ __int64 __fastcall TInt64Helper::Parse(const String s)
{
  __int64 result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"Int64")));
  return result;
}

/*#static*/ bool __fastcall TInt64Helper::TryParse(const String s, __int64& Value)
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

/*#static*/ NativeUInt __fastcall TNativeUIntHelper::Parse(const String s)
{
  NativeUInt result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"NativeUInt")));
  return result;
}

/*#static*/ bool __fastcall TNativeUIntHelper::TryParse(const String s, NativeUInt& Value)
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

/*#static*/ NativeInt __fastcall TNativeIntHelper::Parse(const String s)
{
  NativeInt result = 0;
  if(!TryParse(s, result))
		ConvertErrorFmt(System_Sysconst_SInvalidInteger2, ARRAYOFCONST((s, L"NativeInt")));
  return result;
}

/*#static*/ bool __fastcall TNativeIntHelper::TryParse(const String s, NativeInt& Value)
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

/*#static*/ bool __fastcall TBooleanHelper::Parse(const String s)
{
  bool result = false;
  result = StrToBool(s);
  return result;
}

/*#static*/ bool __fastcall TBooleanHelper::TryToParse(const String s, bool& Value)
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

/*#static*/ bool __fastcall TByteBoolHelper::Parse(const String s)
{
  bool result = false;
  result = StrToBool(s);
  return result;
}

/*#static*/ bool __fastcall TByteBoolHelper::TryToParse(const String s, bool& Value)
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

/*#static*/ bool __fastcall TWordBoolHelper::Parse(const String s)
{
  bool result = false;
  result = StrToBool(s);
  return result;
}

/*#static*/ bool __fastcall TWordBoolHelper::TryToParse(const String s, bool& Value)
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

/*#static*/ bool __fastcall TLongBoolHelper::Parse(const String s)
{
  bool result = false;
  result = StrToBool(s);
  return result;
}

/*#static*/ bool __fastcall TLongBoolHelper::TryToParse(const String s, bool& Value)
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
#endif // needed

} // namespace d2c_system
