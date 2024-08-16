#ifndef d2c_convertH
#define d2c_convertH

/*
This is a shortened version of the Delphi2CB utility file of the same name.
The file is required in order to be able to compile the code of the SynEdit
components, which were translated to C++ with Delphi2CB:

	https://www.texttransformer.com/Delphi2CB_en.html

The translated code and this file are subject to the same license terms
as the original SynEdit code. These terms are precisely specified in

	Source\Source\SynEditJedi.inc.

*/


#include <System.hpp>  // AnsiString etc.
#include <algorithm>
#include <cctype>
#include <functional> 
#include <locale>
#include <string>
#include <vector>



template <typename Type, Type Low, Type High>
unsigned char ToByte(const System::Set<Type, Low, High>& xset)
{
  unsigned char uc;
  memcpy(&uc, &xset, sizeof(unsigned char));
  return uc;
}

template <class T>
T* array2ptr(const DynamicArray<T>& s, int offset = 0)
{
	return const_cast<T*>(&s[0] + offset); // &s[0]  or  &*s.begin()
}


System::PAnsiChar astr2pchar(const System::AnsiString& xs, int index = 0);
System::PWideChar ustr2pwchar(const System::UnicodeString& xs, int index = 0);
void* ustr2address(const System::UnicodeString& xs, int index = 0);

// provided that the elements of the SourceSet are in the element range of the TagetSet
template<class TargetSet, class TEnum, TEnum minEl2, TEnum maxEl2>
TargetSet ConvertSubset(const System::Set<TEnum, minEl2, maxEl2>& SourceSet)
{
	TargetSet target;

	for (TEnum value = minEl2; value <= maxEl2; value = static_cast<TEnum>(static_cast<int>(value) + 1))
	{
		if (SourceSet.Contains(value))
		{
			target << value;
		}
	}

	return target;
}


#endif // d2c_convertH
