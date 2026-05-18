#ifndef d2c_syshelperH
#define d2c_syshelperH

/*
    Copyright (C) <2026>  <Dr. Detlef Meyer-Eltz>
    ---------------------------------------------

    this file is authorized for unlimited use in any
    project created with Delphi2CB or Delphi2Cpp.

    http://www.texttransformer.com/
*/


#include <System.hpp>
#include <System.SysUtils.hpp>
#include "d2c_system.h"
#include "d2c_openarray.h"
//---------------------------------------------------------------------------

namespace d2c_system {
/*
enum TCompareOption {coLingIgnoreCase,
										 coLingIgnoreDiacritic,
                     coIgnoreCase,
                     coIgnoreKanatype,
                     coIgnoreNonSpace,
										 coIgnoreSymbols,
										 coIgnoreWidth,
                     coLingCasing,
                     coDigitAsNumbers,
										 coStringSort }; */


struct TStringHelper
{
//  TStringHelper(UnicodeString& Helped) : m_Helped(Helped) {}
  TStringHelper(const UnicodeString& Helped) : m_Helped(const_cast<UnicodeString&>(Helped)) {}
//  TStringHelper(const UnicodeString& Helped) = delete;
private:
  enum TSplitKind {StringSeparatorsNoQuoted,
                 StringSeparatorsQuoted,
                 StringSeparatorNoQuoted,
                 CharSeparatorsNoQuoted,
                 CharSeparatorsQuoted,
                 CharSeparatorNoQuoted };
  Char __fastcall GetChars(int Index) const;
  int __fastcall GetLength() const;
  static bool __fastcall CharInArray(Char C, const Char* InArray, int InArray_maxidx);
  System::D2CArray<String> __fastcall InternalSplit(TSplitKind SplitType, const Char* SeparatorC, int SeparatorC_maxidx, const String* SeparatorS, int SeparatorS_maxidx, Char QuoteStart, Char QuoteEnd, int Count, TStringSplitOptions Options) const;
  int __fastcall IndexOfAny(const String* Values, int Values_maxidx, int& Index, int StartIndex) const;
  int __fastcall IndexOfAnyUnquoted(const String* Values, int Values_maxidx, Char StartQuote, Char EndQuote, int& Index, int StartIndex) const;
  int __fastcall IndexOfQuoted(const String& Value, Char StartQuote, Char EndQuote, int StartIndex) const;
  static int __fastcall InternalCompare(const String& StrA, int IndexA, const String& StrB, int IndexB, int LengthA, int LengthB, bool IgnoreCase, TLocaleID LocaleID);
  static int __fastcall InternalCompare(const String& StrA, int IndexA, const String& StrB, int IndexB, int LengthA, int LengthB, TCompareOptions Options, TLocaleID LocaleID);
  static LongWord __fastcall InternalMapOptionsToFlags(TCompareOptions AOptions);
public:
  static const String& Empty;  //  = L"";
    // Methods
  static String __fastcall Create(Char C, int Count);
  static String __fastcall Create(const Char* Value, int Value_maxidx, int StartIndex, int Length);
  static String __fastcall Create(const Char* Value, int Value_maxidx);
  static int __fastcall Compare(const String& StrA, const String& StrB);
  static int __fastcall Compare(const String& StrA, const String& StrB, TLocaleID LocaleID);
  static int __fastcall Compare(const String& StrA, const String& StrB, bool IgnoreCase); //deprecated 'Use same with TCompareOptions';
  static int __fastcall Compare(const String& StrA, const String& StrB, bool IgnoreCase, TLocaleID LocaleID); //deprecated 'Use same with TCompareOptions';
  static int __fastcall Compare(const String& StrA, const String& StrB, TCompareOptions Options);
  static int __fastcall Compare(const String& StrA, const String& StrB, TCompareOptions Options, TLocaleID LocaleID);
  static int __fastcall Compare(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length);
  static int __fastcall Compare(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length, TLocaleID LocaleID);
  static int __fastcall Compare(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length, bool IgnoreCase); //deprecated 'Use same with TCompareOptions';
  static int __fastcall Compare(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length, bool IgnoreCase, TLocaleID LocaleID); //deprecated 'Use same with TCompareOptions';
  static int __fastcall Compare(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length, TCompareOptions Options);
  static int __fastcall Compare(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length, TCompareOptions Options, TLocaleID LocaleID);
  static int __fastcall CompareOrdinal(const String& StrA, const String& StrB);
  static int __fastcall CompareOrdinal(const String& StrA, int IndexA, const String& StrB, int IndexB, int Length);
  static int __fastcall CompareText(const String& StrA, const String& StrB);
  static String __fastcall Parse(int Value);
  static String __fastcall Parse(__int64 Value);
  static String __fastcall Parse(bool Value);
  static String __fastcall Parse(long double Value);
  static bool __fastcall ToBoolean(const String& S);
  static int __fastcall ToInteger(const String& S);
    /// <summary>Class function to Convert a string to an Int64 value</summary>
  static __int64 __fastcall ToInt64(const String& S);
  static float __fastcall ToSingle(const String& S);
  static double __fastcall ToDouble(const String& S);
  static long double __fastcall ToExtended(const String& S);
  static String __fastcall LowerCase(const String& S);
  static String __fastcall LowerCase(const String& S, TLocaleOptions LocaleOptions);
  static String __fastcall UpperCase(const String& S);
  static String __fastcall UpperCase(const String& S, TLocaleOptions LocaleOptions);
  int __fastcall CompareTo(const String& strB) const;
  bool __fastcall Contains(const String& Value) const;
  static String __fastcall Copy(const String& Str);
  void __fastcall CopyTo(int SourceIndex, OpenArrayRef<Char> destination, int DestinationIndex, int Count) const;
  int __fastcall CountChar(Char C) const;
  String __fastcall DeQuotedString() const;
  String __fastcall DeQuotedString(Char QuoteChar) const;
  static bool __fastcall EndsText(const String& ASubText, const String& AText);
  bool __fastcall EndsWith(const String& Value) const;
  bool __fastcall EndsWith(const String& Value, bool IgnoreCase) const;
  bool __fastcall Equals(const String& Value) const;
  static bool __fastcall Equals(const String& a, const String& b);
  static String __fastcall Format(const String& Format, const TVarRec* args, int args_maxidx);
  int __fastcall GetHashCode() const;
  int __fastcall IndexOf(Char Value) const;
  int __fastcall IndexOf(const String& Value) const;
  int __fastcall IndexOf(Char Value, int StartIndex) const;
  int __fastcall IndexOf(const String& Value, int StartIndex) const;
  int __fastcall IndexOf(Char Value, int StartIndex, int Count) const;
  int __fastcall IndexOf(const String& Value, int StartIndex, int Count) const;
  int __fastcall IndexOfAny(const Char* AnyOf, int AnyOf_maxidx) const;
  int __fastcall IndexOfAny(const Char* AnyOf, int AnyOf_maxidx, int StartIndex) const;
  int __fastcall IndexOfAny(const Char* AnyOf, int AnyOf_maxidx, int StartIndex, int Count) const;
    /// <summary>Index of any given chars, excluding those that are between quotes</summary>
  int __fastcall IndexOfAnyUnquoted(const Char* AnyOf, int AnyOf_maxidx, Char StartQuote, Char EndQuote) const;
  int __fastcall IndexOfAnyUnquoted(const Char* AnyOf, int AnyOf_maxidx, Char StartQuote, Char EndQuote, int StartIndex) const;
  int __fastcall IndexOfAnyUnquoted(const Char* AnyOf, int AnyOf_maxidx, Char StartQuote, Char EndQuote, int StartIndex, int Count) const;
  String __fastcall Insert(int StartIndex, const String& Value) const;
  bool __fastcall IsDelimiter(const String& Delimiters, int Index) const;
  bool __fastcall IsEmpty() const;
  static bool __fastcall IsNullOrEmpty(const String& Value);
  static bool __fastcall IsNullOrWhiteSpace(const String& Value);
  static String __fastcall Join(const String& Separator, const TVarRec* Values, int Values_maxidx);
  static String __fastcall Join(const String& Separator, const String* Values, int Values_maxidx);
//  static String __fastcall Join(const String& Separator, System::IEnumerator__1<String>* const Values);
//  static String __fastcall Join(const String& Separator, System::IEnumerable__1<String>* const Values);
  static String __fastcall Join( const String& Separator, const System::_di_IEnumerable__1<String>& Values);
  static String __fastcall Join( const String& Separator, const System::_di_IEnumerator__1<String>& Values);
  static String __fastcall Join(const String& Separator, const String* Values, int Values_maxidx, int StartIndex, int Count);
  int __fastcall LastDelimiter(const String& Delims) const;
  int __fastcall LastDelimiter(const TSysCharSet Delims) const;
  int __fastcall LastIndexOf(Char Value) const;
  int __fastcall LastIndexOf(const String& Value) const;
  int __fastcall LastIndexOf(Char Value, int StartIndex) const;
  int __fastcall LastIndexOf(const String& Value, int StartIndex) const;
  int __fastcall LastIndexOf(Char Value, int StartIndex, int Count) const;
  int __fastcall LastIndexOf(const String& Value, int StartIndex, int Count) const;
  int __fastcall LastIndexOfAny(const Char* AnyOf, int AnyOf_maxidx) const;
  int __fastcall LastIndexOfAny(const Char* AnyOf, int AnyOf_maxidx, int StartIndex) const;
  int __fastcall LastIndexOfAny(const Char* AnyOf, int AnyOf_maxidx, int StartIndex, int Count) const;
  String __fastcall PadLeft(int TotalWidth) const;
  String __fastcall PadLeft(int TotalWidth, Char PaddingChar) const;
  String __fastcall PadRight(int TotalWidth) const;
  String __fastcall PadRight(int TotalWidth, Char PaddingChar) const;
  String __fastcall QuotedString() const;
  String __fastcall QuotedString(Char QuoteChar) const;
  String __fastcall Remove(int StartIndex) const;
  String __fastcall Remove(int StartIndex, int Count) const;
  String __fastcall Replace(Char OldChar, Char NewChar) const;
  String __fastcall Replace(Char OldChar, Char NewChar, TReplaceFlags ReplaceFlags) const;
  String __fastcall Replace(const String& OldValue, const String& NewValue) const;
  String __fastcall Replace(const String& OldValue, const String& NewValue, TReplaceFlags ReplaceFlags) const;
  System::D2CArray<String> __fastcall Split(const Char* Separator, int Separator_maxidx) const;
  System::D2CArray<String> __fastcall Split(const Char* Separator, int Separator_maxidx, int Count) const;
  System::D2CArray<String> __fastcall Split(const Char* Separator, int Separator_maxidx, TStringSplitOptions Options) const;
  System::D2CArray<String> __fastcall Split(const Char* Separator, int Separator_maxidx, int Count, TStringSplitOptions Options) const;
  System::D2CArray<String> __fastcall Split(const String* Separator, int Separator_maxidx) const;
  System::D2CArray<String> __fastcall Split(const String* Separator, int Separator_maxidx, int Count) const;
  System::D2CArray<String> __fastcall Split(const String* Separator, int Separator_maxidx, TStringSplitOptions Options) const;
  System::D2CArray<String> __fastcall Split(const String* Separator, int Separator_maxidx, int Count, TStringSplitOptions Options) const;
  System::D2CArray<String> __fastcall Split(const Char* Separator, int Separator_maxidx, Char Quote) const;
  System::D2CArray<String> __fastcall Split(const Char* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd) const;
  System::D2CArray<String> __fastcall Split(const Char* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd, TStringSplitOptions Options) const;
  System::D2CArray<String> __fastcall Split(const Char* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd, int Count) const;
  System::D2CArray<String> __fastcall Split(const Char* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd, int Count, TStringSplitOptions Options) const;
  System::D2CArray<String> __fastcall Split(const String* Separator, int Separator_maxidx, Char Quote) const;
  System::D2CArray<String> __fastcall Split(const String* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd) const;
  System::D2CArray<String> __fastcall Split(const String* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd, TStringSplitOptions Options) const;
  System::D2CArray<String> __fastcall Split(const String* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd, int Count) const;
  System::D2CArray<String> __fastcall Split(const String* Separator, int Separator_maxidx, Char QuoteStart, Char QuoteEnd, int Count, TStringSplitOptions Options) const;
  static bool __fastcall StartsText(const String& ASubText, const String& AText);
  bool __fastcall StartsWith(const String& Value) const;
  bool __fastcall StartsWith(const String& Value, bool IgnoreCase) const;
  String __fastcall Substring(int StartIndex) const;
  String __fastcall Substring(int StartIndex, int Length) const;
  bool __fastcall ToBoolean() const;
  int __fastcall ToInteger() const;
    /// <summary>Converts the string to an Int64 value</summary>
  __int64 __fastcall ToInt64() const;
  float __fastcall ToSingle() const;
  double __fastcall ToDouble() const;
  long double __fastcall ToExtended() const;
  System::D2CArray<Char> __fastcall ToCharArray() const;
  System::D2CArray<Char> __fastcall ToCharArray(int StartIndex, int Length) const;
  String __fastcall ToLower() const;
  String __fastcall ToLower(TLocaleID LocaleID) const;
  String __fastcall ToLowerInvariant() const;
  String __fastcall ToUpper() const;
  String __fastcall ToUpper(TLocaleID LocaleID) const;
  String __fastcall ToUpperInvariant() const;
  String __fastcall Trim() const;
  String __fastcall TrimLeft() const;
  String __fastcall TrimRight() const;
  String __fastcall Trim(const Char* TrimChars, int TrimChars_maxidx) const;
  String __fastcall TrimLeft(const Char* TrimChars, int TrimChars_maxidx) const;
  String __fastcall TrimRight(const Char* TrimChars, int TrimChars_maxidx) const;
  String __fastcall TrimEnd(const Char* TrimChars, int TrimChars_maxidx) const/*# 'use trimright' */;
  String __fastcall TrimStart(const Char* TrimChars, int TrimChars_maxidx) const/*# 'use trimleft' */;
  __property Char Chars[int Index] = { read = GetChars };
  __property int Length = { read = GetLength };
private:
  const UnicodeString& m_Helped;

};

struct TSingleHelper
{

	TSingleHelper(float& Helped) : m_Helped(Helped) {}
	TSingleHelper(const float& Helped) : m_Helped(const_cast<float&>(Helped)) {}
private:
	UInt8 __fastcall InternalGetBytes(unsigned int Index) const;
	UInt16 __fastcall InternalGetWords(unsigned int Index) const;
	void __fastcall InternalSetBytes(unsigned int Index, const UInt8 Value);
	void __fastcall InternalSetWords(unsigned int Index, const UInt16 Value);
	UInt8 __fastcall GetBytes(unsigned int Index) const;
	UInt16 __fastcall GetWords(unsigned int Index) const;
	unsigned __int64 __fastcall GetExp() const;
	unsigned __int64 __fastcall GetFrac() const;
	bool __fastcall GetSign() const;
  void __fastcall setbytes(unsigned int Index, const UInt8 Value);
  void __fastcall SetWords(unsigned int Index, const UInt16 Value);
  void __fastcall SetExp(unsigned __int64 NewExp);
  void __fastcall SetFrac(unsigned __int64 NewFrac);
  void __fastcall SetSign(bool NewSign);
public:
  static const float Epsilon; //  = 1.4012984643248170709e-45F;
  static const float MaxValue; //  = 340282346638528859811704183484516925440.0F;
  static const float MinValue; //  = -340282346638528859811704183484516925440.0;
  static const float PositiveInfinity; //  = 1.0F / 0.0F;
  static const float NegativeInfinity; //  = -1.0F / 0.0F;
  static const float NaN; //  = 0.0F / 0.0F;
  int __fastcall Exponent();
  long double __fastcall Fraction();
  unsigned __int64 __fastcall mantissa();
  __property bool sign = { read = GetSign, write = SetSign };
  __property unsigned __int64 Exp = { read = GetExp, write = SetExp };
  __property unsigned __int64 Frac = { read = GetFrac, write = SetFrac };
	TFloatSpecial __fastcall SpecialType();
  void __fastcall BuildUp(const bool SignFlag, const unsigned __int64 mantissa, const int Exponent);
  String __fastcall ToString();
  String __fastcall ToString(const TFormatSettings& AFormatSettings);
  String __fastcall ToString(const TFloatFormat Format, const int Precision, const int Digits);
  String __fastcall ToString(const TFloatFormat Format, const int Precision, const int Digits, const TFormatSettings& AFormatSettings);
  bool __fastcall IsNan();
  bool __fastcall IsInfinity();
  bool __fastcall IsNegativeInfinity();
  bool __fastcall IsPositiveInfinity();
  __property UInt8 Bytes[unsigned int Index] = { read = GetBytes, write = setbytes };  // 0..3
  __property UInt16 Words[unsigned int Index] = { read = GetWords, write = SetWords }; // 0..1
  static String __fastcall ToString(const float Value);
  static String __fastcall ToString(const float Value, const TFormatSettings& AFormatSettings);
  static String __fastcall ToString(const float Value, const TFloatFormat Format, const int Precision, const int Digits);
  static String __fastcall ToString(const float Value, const TFloatFormat Format, const int Precision, const int Digits, const TFormatSettings& AFormatSettings);
  static float __fastcall Parse(const String& s);
  static float __fastcall Parse(const String& s, const TFormatSettings& AFormatSettings);
  static bool __fastcall TryParse(const String& s, float& Value);
  static bool __fastcall TryParse(const String& s, float& Value, const TFormatSettings& AFormatSettings);
  static bool __fastcall IsNan(const float Value);
  static bool __fastcall IsInfinity(const float Value);
	static bool __fastcall IsNegativeInfinity(const float Value);
  static bool __fastcall IsPositiveInfinity(const float Value);
  static int __fastcall Size();
private:
  float& m_Helped;

};

struct TDoubleHelper
{
	TDoubleHelper(double& Helped) : m_Helped(Helped) {}
	TDoubleHelper(const double& Helped) : m_Helped(const_cast<double&>(Helped)) {}
private:
	UInt8 __fastcall InternalGetBytes(unsigned int Index) const;
	UInt16 __fastcall InternalGetWords(unsigned int Index) const;
	void __fastcall InternalSetBytes(unsigned int Index, const UInt8 Value);
	void __fastcall InternalSetWords(unsigned int Index, const UInt16 Value);
	UInt8 __fastcall GetBytes(unsigned int Index) const;
	UInt16 __fastcall GetWords(unsigned int Index) const;
	unsigned __int64 __fastcall GetExp() const;
	unsigned __int64 __fastcall GetFrac() const;
	bool __fastcall GetSign() const;
	void __fastcall setbytes(unsigned int Index, const UInt8 Value);
	void __fastcall SetWords(unsigned int Index, const UInt16 Value);
	void __fastcall SetExp(unsigned __int64 NewExp);
	void __fastcall SetFrac(unsigned __int64 NewFrac);
	void __fastcall SetSign(bool NewSign);
public:
  static const double Epsilon; //  = 4.9406564584124654418e-324;
  static const double MaxValue; //  = 1.7976931348623157081e+308;
  static const double MinValue; //  = -1.7976931348623157081e+308;
  static const double PositiveInfinity; //  = 1.0 / 0.0;
  static const double NegativeInfinity; //  = -1.0 / 0.0;
  static const double NaN; //  = 0.0 / 0.0;
  int __fastcall Exponent();
  long double __fastcall Fraction();
  unsigned __int64 __fastcall mantissa();
  __property bool sign = { read = GetSign, write = SetSign };
  __property unsigned __int64 Exp = { read = GetExp, write = SetExp };
  __property unsigned __int64 Frac = { read = GetFrac, write = SetFrac };
  TFloatSpecial __fastcall SpecialType();
  void __fastcall BuildUp(const bool SignFlag, const unsigned __int64 mantissa, const int Exponent);
  String __fastcall ToString();
  String __fastcall ToString(const TFormatSettings& AFormatSettings);
	String __fastcall ToString(const TFloatFormat Format, const int Precision, const int Digits);
  String __fastcall ToString(const TFloatFormat Format, const int Precision, const int Digits, const TFormatSettings& AFormatSettings);
  bool __fastcall IsNan();
  bool __fastcall IsInfinity();
  bool __fastcall IsNegativeInfinity();
  bool __fastcall IsPositiveInfinity();
  __property UInt8 Bytes[unsigned int Index] = { read = GetBytes, write = setbytes };  // 0..7
  __property UInt16 Words[unsigned int Index] = { read = GetWords, write = SetWords }; // 0..3
  static String __fastcall ToString(const double Value);
  static String __fastcall ToString(const double Value, const TFormatSettings& AFormatSettings);
  static String __fastcall ToString(const double Value, const TFloatFormat Format, const int Precision, const int Digits);
  static String __fastcall ToString(const double Value, const TFloatFormat Format, const int Precision, const int Digits, const TFormatSettings& AFormatSettings);
  static double __fastcall Parse(const String& s);
  static double __fastcall Parse(const String& s, const TFormatSettings& AFormatSettings);
  static bool __fastcall TryParse(const String& s, double& Value);
  static bool __fastcall TryParse(const String& s, double& Value, const TFormatSettings& AFormatSettings);
  static bool __fastcall IsNan(const double Value);
  static bool __fastcall IsInfinity(const double Value);
  static bool __fastcall IsNegativeInfinity(const double Value);
  static bool __fastcall IsPositiveInfinity(const double Value);
  static int __fastcall Size();
private:
	double& m_Helped;

};

struct TExtendedHelper
{
	TExtendedHelper(long double& Helped) : m_Helped(Helped) {}
	TExtendedHelper(const long double& Helped) : m_Helped(const_cast<long double&>(Helped)) {}
private:
	UInt8 __fastcall InternalGetBytes(unsigned int Index) const;
	UInt16 __fastcall InternalGetWords(unsigned int Index) const;
	void __fastcall InternalSetBytes(unsigned int Index, const UInt8 Value);
	void __fastcall InternalSetWords(unsigned int Index, const UInt16 Value);
	UInt8 __fastcall GetBytes(unsigned int Index) const;
	UInt16 __fastcall GetWords(unsigned int Index) const;
	unsigned __int64 __fastcall GetExp() const;
	unsigned __int64 __fastcall GetFrac() const;
	bool __fastcall GetSign() const;
	void __fastcall setbytes(unsigned int Index, const UInt8 Value);
	void __fastcall SetWords(unsigned int Index, const UInt16 Value);
	void __fastcall SetExp(unsigned __int64 NewExp);
	void __fastcall SetFrac(unsigned __int64 NewFrac);
	void __fastcall SetSign(bool NewSign);
public:
	static const long double Epsilon; //  = 4.9406564584124654418e-324L;
  static const long double MaxValue; //  = 1.7976931348623157081e+308L;
  static const long double MinValue; //  = -1.7976931348623157081e+308;
  static const long double PositiveInfinity; //  = 1.0L / 0.0L;
  static const long double NegativeInfinity; //  = -1.0L / 0.0L;
  static const long double NaN; //  = 0.0L / 0.0L;
  int __fastcall Exponent();
  long double __fastcall Fraction();
  unsigned __int64 __fastcall mantissa();
  __property bool sign = { read = GetSign, write = SetSign };
  __property unsigned __int64 Exp = { read = GetExp, write = SetExp };
  __property unsigned __int64 Frac = { read = GetFrac, write = SetFrac };
  TFloatSpecial __fastcall SpecialType();
  void __fastcall BuildUp(const bool SignFlag, const unsigned __int64 mantissa, const int Exponent);
  String __fastcall ToString();
  String __fastcall ToString(const TFormatSettings& AFormatSettings);
  String __fastcall ToString(const TFloatFormat Format, const int Precision, const int Digits);
  String __fastcall ToString(const TFloatFormat Format, const int Precision, const int Digits, const TFormatSettings& AFormatSettings);
  bool __fastcall IsNan();
  bool __fastcall IsInfinity();
	bool __fastcall IsNegativeInfinity();
  bool __fastcall IsPositiveInfinity();
  __property UInt8 Bytes[unsigned int Index] = { read = GetBytes, write = setbytes };  // 0..7 or 0..9
  __property UInt16 Words[unsigned int Index] = { read = GetWords, write = SetWords }; // 0..3 or 0..4
  static String __fastcall ToString(const long double Value);
  static String __fastcall ToString(const long double Value, const TFormatSettings& AFormatSettings);
  static String __fastcall ToString(const long double Value, const TFloatFormat Format, const int Precision, const int Digits);
  static String __fastcall ToString(const long double Value, const TFloatFormat Format, const int Precision, const int Digits, const TFormatSettings& AFormatSettings);
  static long double __fastcall Parse(const String& s);
  static long double __fastcall Parse(const String& s, const TFormatSettings& AFormatSettings);
  static bool __fastcall TryParse(const String& s, long double& Value);
  static bool __fastcall TryParse(const String& s, long double& Value, const TFormatSettings& AFormatSettings);
  static bool __fastcall IsNan(const long double Value);
  static bool __fastcall IsInfinity(const long double Value);
  static bool __fastcall IsNegativeInfinity(const long double Value);
  static bool __fastcall IsPositiveInfinity(const long double Value);
  static int __fastcall Size();
private:
  long double& m_Helped;

};

struct TByteHelper
{
	TByteHelper(unsigned char& Helped) : m_Helped(Helped) {}
	TByteHelper(const unsigned char& Helped) : m_Helped(const_cast<unsigned char&>(Helped)) {}
	static const int MaxValue; //  = 255;
	static const int MinValue; //  = 0;
	String __fastcall ToString();
	bool __fastcall ToBoolean();
	String __fastcall ToHexString();
	String __fastcall ToHexString(const int MinDigits);
	float __fastcall ToSingle();
	double __fastcall ToDouble();
	long double __fastcall ToExtended();
	static int __fastcall Size();
	static String __fastcall ToString(const unsigned char Value);
	static unsigned char __fastcall Parse(const String& s);
	static bool __fastcall TryParse(const String& s, unsigned char& Value);
private:
	unsigned char& m_Helped;

};

struct TShortIntHelper
{
	TShortIntHelper(signed char& Helped) : m_Helped(Helped) {}
	TShortIntHelper(const signed char& Helped) : m_Helped(const_cast<signed char&>(Helped)) {}
	static const int MaxValue; //  = 127;
	static const int MinValue; //  = -128;
	String __fastcall ToString();
	bool __fastcall ToBoolean();
	String __fastcall ToHexString();
	String __fastcall ToHexString(const int MinDigits);
	float __fastcall ToSingle();
	double __fastcall ToDouble();
	long double __fastcall ToExtended();
	static int __fastcall Size();
	static String __fastcall ToString(const signed char Value);
  static signed char __fastcall Parse(const String& s);
  static bool __fastcall TryParse(const String& s, signed char& Value);
private:
  signed char& m_Helped;

};

struct TWordHelper
{

	TWordHelper(WORD& Helped) : m_Helped(Helped) {}
	TWordHelper(const WORD& Helped) : m_Helped(const_cast<WORD&>(Helped)) {}
	static const int MaxValue; //  = 65535;
	static const int MinValue; //  = 0;
	String __fastcall ToString();
	bool __fastcall ToBoolean();
	String __fastcall ToHexString();
	String __fastcall ToHexString(const int MinDigits);
	float __fastcall ToSingle();
	double __fastcall ToDouble();
	long double __fastcall ToExtended();
	static int __fastcall Size();
	static String __fastcall ToString(const WORD Value);
	static WORD __fastcall Parse(const String& s);
	static bool __fastcall TryParse(const String& s, WORD& Value);
private:
  WORD& m_Helped;

};

struct TSmallIntHelper
{

	TSmallIntHelper(short int& Helped) : m_Helped(Helped) {}
	TSmallIntHelper(const short int& Helped) : m_Helped(const_cast<short int&>(Helped)) {}
	static const int MaxValue; //  = 32767;
	static const int MinValue; //  = -32768;
	String __fastcall ToString();
	bool __fastcall ToBoolean();
	String __fastcall ToHexString();
	String __fastcall ToHexString(const int MinDigits);
	float __fastcall ToSingle();
	double __fastcall ToDouble();
	long double __fastcall ToExtended();
	static int __fastcall Size();
	static String __fastcall ToString(const short int Value);
	static short int __fastcall Parse(const String& s);
	static bool __fastcall TryParse(const String& s, short int& Value);
private:
  short int& m_Helped;

};

struct TCardinalHelper
{
	TCardinalHelper(unsigned int& Helped) : m_Helped(Helped) {}
	TCardinalHelper(const unsigned int& Helped) : m_Helped(const_cast<unsigned int&>(Helped)) {} /* for LongWord type too */
	static const int MaxValue; //  = 4294967295;
	static const int MinValue; //  = 0;
	String __fastcall ToString();
	bool __fastcall ToBoolean();
	String __fastcall ToHexString();
	String __fastcall ToHexString(const int MinDigits);
	float __fastcall ToSingle();
	double __fastcall ToDouble();
	long double __fastcall ToExtended();
	static int __fastcall Size();
	static String __fastcall ToString(const unsigned int Value);
	static unsigned int __fastcall Parse(const String& s);
	static bool __fastcall TryParse(const String& s, unsigned int& Value);
private:
	unsigned int& m_Helped;

};

struct TIntegerHelper
{

	TIntegerHelper(int& Helped) : m_Helped(Helped) {}
	TIntegerHelper(const int& Helped) : m_Helped(const_cast<int&>(Helped)) {} /* for LongInt type too */
	static const int MaxValue; //  = 2147483647;
	static const int MinValue; //  = -2147483648;
	String __fastcall ToString();
	bool __fastcall ToBoolean();
	String __fastcall ToHexString();
	String __fastcall ToHexString(const int MinDigits);
	float __fastcall ToSingle();
	double __fastcall ToDouble();
	long double __fastcall ToExtended();
	static int __fastcall Size();
	static String __fastcall ToString(const int Value);
	static int __fastcall Parse(const String& s);
	static bool __fastcall TryParse(const String& s, int& Value);
private:
	int& m_Helped;

};

struct TUInt64Helper
{

	TUInt64Helper(unsigned __int64& Helped) : m_Helped(Helped) {}
	TUInt64Helper(const unsigned __int64& Helped) : m_Helped(const_cast<unsigned __int64&>(Helped)) {}
	static const unsigned __int64 MaxValue; //  = 18446744073709551615;
	static const unsigned __int64 MinValue; //  = 0;
	String __fastcall ToString();
	bool __fastcall ToBoolean();
	String __fastcall ToHexString();
	String __fastcall ToHexString(const int MinDigits);
	float __fastcall ToSingle();
	double __fastcall ToDouble();
	long double __fastcall ToExtended();
	static int __fastcall Size();
	static String __fastcall ToString(const unsigned __int64 Value);
	static unsigned __int64 __fastcall Parse(const String& s);
	static bool __fastcall TryParse(const String& s, unsigned __int64& Value);
private:
	unsigned __int64& m_Helped;

};

struct TInt64Helper
{

	TInt64Helper(__int64& Helped) : m_Helped(Helped) {}
	TInt64Helper(const __int64& Helped) : m_Helped(const_cast<__int64&>(Helped)) {}
	static const __int64 MaxValue; //  = 9223372036854775807;
	static const __int64 MinValue; //  = -9223372036854775808;
	String __fastcall ToString();
	bool __fastcall ToBoolean();
	String __fastcall ToHexString();
	String __fastcall ToHexString(const int MinDigits);
	float __fastcall ToSingle();
	double __fastcall ToDouble();
	long double __fastcall ToExtended();
	static int __fastcall Size();
	static String __fastcall ToString(const __int64 Value);
	static __int64 __fastcall Parse(const String& s);
	static bool __fastcall TryParse(const String& s, __int64& Value);
private:
	__int64& m_Helped;

};

struct TNativeUIntHelper
{

	TNativeUIntHelper(NativeUInt& Helped) : m_Helped(Helped) {}
	TNativeUIntHelper(const NativeUInt& Helped) : m_Helped(const_cast<NativeUInt&>(Helped)) {}
	static const NativeUInt MaxValue; //  = 4294967295;
	static const NativeUInt MinValue; //  = 0;
	String __fastcall ToString();
	bool __fastcall ToBoolean();
	String __fastcall ToHexString();
	String __fastcall ToHexString(const int MinDigits);
	float __fastcall ToSingle();
	double __fastcall ToDouble();
	long double __fastcall ToExtended();
	static int __fastcall Size();
	static String __fastcall ToString(const NativeUInt Value);
	static NativeUInt __fastcall Parse(const String& s);
	static bool __fastcall TryParse(const String& s, NativeUInt& Value);
private:
	NativeUInt& m_Helped;

};

struct TNativeIntHelper
{

	TNativeIntHelper(NativeInt& Helped) : m_Helped(Helped) {}
	TNativeIntHelper(const NativeInt& Helped) : m_Helped(const_cast<NativeInt&>(Helped)) {}
	static const NativeInt MaxValue; //  = 2147483647;
	static const NativeInt MinValue; //  = -2147483648;
	String __fastcall ToString();
	bool __fastcall ToBoolean();
	String __fastcall ToHexString();
	String __fastcall ToHexString(const int MinDigits);
	float __fastcall ToSingle();
	double __fastcall ToDouble();
	long double __fastcall ToExtended();
	static int __fastcall Size();
	static String __fastcall ToString(const NativeInt Value);
	static NativeInt __fastcall Parse(const String& s);
	static bool __fastcall TryParse(const String& s, NativeInt& Value);
private:
	NativeInt& m_Helped;

};

	/*$SCOPEDENUMS ON*/
enum TUseBoolStrs {False,
									 True };

	/*$SCOPEDENUMS OFF*/

struct TBooleanHelper
{

	TBooleanHelper(bool& Helped) : m_Helped(Helped) {}
	TBooleanHelper(const bool& Helped) : m_Helped(const_cast<bool&>(Helped)) {}
	int __fastcall ToInteger();
	String __fastcall ToString(TUseBoolStrs UseBoolStrs = TUseBoolStrs::False);
	static int __fastcall Size();
	static String __fastcall ToString(const bool Value, TUseBoolStrs UseBoolStrs = TUseBoolStrs::False);
	static bool __fastcall Parse(const String& s);
	static bool __fastcall TryToParse(const String& s, bool& Value);
private:
	bool& m_Helped;

};

struct TByteBoolHelper
{

	TByteBoolHelper(unsigned char& Helped) : m_Helped(Helped) {}
	TByteBoolHelper(const unsigned char& Helped) : m_Helped(const_cast<unsigned char&>(Helped)) {}
	int __fastcall ToInteger();
	String __fastcall ToString();
	static int __fastcall Size();
	static String __fastcall ToString(const bool Value);
	static bool __fastcall Parse(const String& s);
	static bool __fastcall TryToParse(const String& s, bool& Value);
private:
	unsigned char& m_Helped;

};

struct TWordBoolHelper
{

	TWordBoolHelper(unsigned short& Helped) : m_Helped(Helped) {}
	TWordBoolHelper(const unsigned short& Helped) : m_Helped(const_cast<unsigned short&>(Helped)) {}
	int __fastcall ToInteger();
	String __fastcall ToString();
	static int __fastcall Size();
	static String __fastcall ToString(const bool Value);
	static bool __fastcall Parse(const String& s);
	static bool __fastcall TryToParse(const String& s, bool& Value);
private:
	unsigned short& m_Helped;

};

struct TLongBoolHelper
{

	TLongBoolHelper(BOOL& Helped) : m_Helped(Helped) {}
	TLongBoolHelper(const BOOL& Helped) : m_Helped(const_cast<BOOL&>(Helped)) {}
	int __fastcall ToInteger();
	String __fastcall ToString();
	static int __fastcall Size();
	static String __fastcall ToString(const bool Value);
	static bool __fastcall Parse(const String& s);
	static bool __fastcall TryToParse(const String& s, bool& Value);
private:
	BOOL& m_Helped;

};

} //namespace d2c_system

#endif
