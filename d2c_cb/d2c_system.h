#ifndef d2c_systemH
#define d2c_systemH

/*
This is a shortened version of the Delphi2CB utility file of the same name.
The file is required in order to be able to compile the code of the SynEdit
components, which were translated to C++ with Delphi2CB:

	https://www.texttransformer.com/Delphi2CB_en.html

The translated code and this file are subject to the same license terms
as the original SynEdit code. These terms are precisely specified in

	Source\Source\SynEditJedi.inc.

*/



#include <exception>
#include <stdlib.h>
#include <sstream>

#include "d2c_systypes.h"
#include "d2c_sysmath.h"
#include "d2c_sysstring.h"
#include "d2c_sysfile.h"


#define MAXIDX(x) (sizeof(x)/sizeof(x[0]))-1

// macro ASSIGNED works both for pointers and events
#define ASSIGNED(x) (x != NULL)


using namespace d2c_system;


namespace d2c_system
{

#define ObjectIs(xObj, xIs) dynamic_cast< xIs >( xObj )

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
void Finalize(void** V, int Count = -1);

}  // namespace d2c_system

#endif //  lpl_systemH