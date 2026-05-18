#ifndef d2c_convertH
#define d2c_convertH

/*
    Copyright (C) 2026 Dr. Detlef Meyer-Eltz
    ----------------------------------------

    This file may be used without restriction in any
    project generated with Delphi2Cpp or Delphi2CB.

    It is a reduced version of the original Delphi2CB
    utility file with the same name.

    This file is required to compile the SynEdit
    components translated from Delphi to C++ using
    Delphi2CB:

        https://www.texttransformer.com/Delphi2CB_en.html
*/


#include <System.hpp>  // AnsiString etc.
#include <algorithm>
#include <cctype>
#include <functional> 
#include <locale>
#include <string>
#include <vector>



void* ustr2address(const System::UnicodeString& xs, int index = 0);
System::PAnsiChar astr2pchar(const System::AnsiString& xs, int index = 0);
System::PWideChar ustr2pwchar(const System::UnicodeString& xs, int index = 0);

template <class T>
T* array2ptr(const DynamicArray<T>& s, int offset = 0)
{
	return const_cast<T*>(&s[0] + offset); // &s[0]  or  &*s.begin()
}


template <typename Type, Type Low, Type High>
unsigned char ToByte(const System::Set<Type, Low, High>& xset)
{
  unsigned char uc;
  memcpy(&uc, &xset, sizeof(unsigned char));
  return uc;
}


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

inline THandle WinHandleToDelphiHandle(const void* h)
{
    return static_cast<THandle>(reinterpret_cast<uintptr_t>(h));
}


#endif // d2c_convertH
