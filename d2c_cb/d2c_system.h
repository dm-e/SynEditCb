#ifndef d2c_systemH
#define d2c_systemH

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


#include <exception>
#include <stdlib.h>
#include <sstream>

#include "d2c_config.h"
#include "d2c_systypes.h"
#include "d2c_sysmath.h"
#include "d2c_sysstring.h"
#include "d2c_sysfile.h"
#include "d2c_event.h"
#include <algorithm>
#include <type_traits>
#include <System.hpp>   // for System::NativeInt and memory APIs
#include <new>          // for std::bad_alloc

#define MAXIDX(x) (sizeof(x)/sizeof(x[0]))-1

// macro ASSIGNED works both for pointers and events
#define ASSIGNED(x) (x != NULL)


using namespace d2c_system;


namespace d2c_system
{

#define ObjectIs(Intf, Cls) (dynamic_cast<Cls>(Intf) != D2C_NULLPTR)
//#define ObjectIs(OBJ_PTR, CLASSPTR) (dynamic_cast<CLASSPTR>(OBJ_PTR) != nullptr)

template <class T>
T High()
{
#undef max
  return std::numeric_limits< T >::max();
}

template <class T>
T High(const T& X)
{
#undef max
  return std::numeric_limits< T >::max();
}

inline int High(const AnsiString& s)
{
	return s.Length();
}

inline int High(const WideString& s)
{
	return s.Length();
}

inline int High(const UnicodeString& s)
{
	return s.Length();
}


template <class T>
T Low()
{
#undef min
  return std::numeric_limits< T >::min();
}

template <class T>
T Low(const T& X)
{
#undef min
  return std::numeric_limits< T >::min();
}


template <class T>
T Abs(const T xT)
{
	return xT < 0 ? -xT : xT;
}

template <typename CH>
int charLen(const CH* src)
{
  int len = 0;
  if (src)
  {
    while (*src++)
      ++len;
  }
  return len;
}

template <class T>
void d2c_memcpy(void* dest, const T& src, size_t num)
{
	const void* p = &src;
	memcpy(dest, p, num);
}

template <class T>
T Inc(T& xT)
{
  int t = (int) xT;  // typecast to "int" allows incrementation of enumerated values
  t++;
  xT = (T) t;
  return xT;
}

template <class T>
T Inc(T& xT, int xi)
{
	int t = (int) xT;  // typecast to "int" allows incrementation of enumerated values
	t += xi;
	xT = (T) t;
	return xT;
}

template <class T>
T Dec(T& xT)
{
	int t = (int) xT;  // typecast to "int" allows incrementation of enumerated values
	t--;
	xT = (T) t;
	return xT;
}

template <class T>
T Dec(T& xT, int xi)
{
	int t = (int) xT;  // typecast to "int" allows incrementation of enumerated values
	t -= xi;
	xT = (T) t;
	return xT;
}

template <class T>
T Pred(const T& xT)
{
	int t = (int) xT;  // typecast to "int" allows incrementation of enumerated values
	return (T) --t;
}

template <class T>
T Succ(const T& xT)
{
	int t = (int) xT;  // typecast to "int" allows incrementation of enumerated values
	return (T) ++t;
}

template <class T>
bool Odd(const T xT)
{
	return xT % 2 ? true : false;
}

template <typename T>
void Val(const UnicodeString& S, T& V, int& Code)
{
	std::wistringstream iss(S.c_str());
	iss >> V;
	Code = 0;
}

template <class TargetType, class SouceType, class Value>
void CastAssign(SouceType* target, Value v)
{
	TargetType* pValue = reinterpret_cast<TargetType*>(&v);
	memcpy(target, pValue, sizeof(TargetType));
}

template<class T, T minEl, T maxEl>
bool __fastcall operator >=(const Set<T, minEl, maxEl>& set1, const Set<T, minEl, maxEl>& set2)     //Union
{
	for(int i = (int) minEl; i <= (int) maxEl; i++)
	{
		if(set2.Contains((T) i) && !set1.Contains((T) i))
			return false;
	}
	return true;
}

template<class T, T minEl, T maxEl>
bool __fastcall operator <=(const Set<T, minEl, maxEl>& set1, const Set<T, minEl, maxEl>& set2)     //Union
{
	for(int i = (int) minEl; i <= (int) maxEl; i++)
	{
		if(set1.Contains((T) i) && !set2.Contains((T) i))
			return false;
	}
	return true;
}


void FillChar( void* X, int Count, unsignedchar Value );
void Assert( bool expr );
void Assert( bool expr, const AnsiString& Msg );
void Initialize(void** V, int Count = -1);

template <class T>
void Finalize(T* array)
{
	// default does nothing / doesn't compile array[0].~T();
}
//
template <class T>
void Finalize(T** array)
{
	// default does nothing delete array[0];
}

template <class T>
void Finalize(T* array, int count)
{
	for (int i = 0; i < count; ++i)
	{
		// default does nothing / doesn't compile array[i].~T();
	}
}

template <class T>
void Finalize(T** array, int count)
{
    if(array == nullptr)
      return;

	for (int i = 0; i < count; ++i)
	{
		// default does nothing delete array[i];
		//array[i] = nullptr;
	}
}

class AbstractMethodError : public std::logic_error
{
public:
	explicit AbstractMethodError(const std::string& methodName)
		: std::logic_error("abstract method called: "),
		m_sMethodName(methodName)
	{
	}

	const std::string& getMethodName() const D2C_NOEXCEPT { return m_sMethodName; }
	std::string whatW() const D2C_NOEXCEPT { return std::string("Cannot call abstract method: ") + m_sMethodName; }

private:
	std::string m_sMethodName;
};

void ThrowAbstractMethodError(const String& xsMethodName); // d2c

}  // namespace d2c_system

#endif //  lpl_systemH