
/*
    Copyright (C) <2020>  <Dr. Detlef Meyer-Eltz>
    ---------------------------------------------

    this file is authorized for unlimited use in any
    project created with Delphi2C# or DelphiXE2Cpp11.

    http://www.texttransformer.com/
*/



#ifndef d2c_systypesH
#define d2c_systypesH


#include <System.hpp>
//#include <string>  => strange compiler error
#include <vector>
#include <limits>
#include <stdint.h>
#include <string>
//#include <sysdyn.h>  #error Beziehen Sie diese Datei nicht direkt ein.  Beziehen Sie 'System.hpp' ein.

// definitions in one word are needed at the C++Builder for properties
typedef short int shortint;
typedef unsigned char unsignedchar;
typedef signed char signedchar;
typedef unsigned int unsignedint;
typedef unsigned short unsignedshort;
// see sysmac.h typedef SmallString<255> ShortString;

namespace System {

typedef std::wstring::size_type d2c_size_t;
const d2c_size_t d2c_npos = std::wstring::npos;

template <int v>
struct Int2Type
{
	enum { value = v };
};

typedef Int2Type<0> uniquetype;

/*
template <typename T, size_t N1>
T* mbegin(T(&arr)[N1]) {
	return reinterpret_cast<T*>(arr);
}
template <typename T, size_t N1>
T* mend(T(&arr)[N1]) {
	return reinterpret_cast<T*>(arr) + N1;
}

template <size_t Count, typename Array>
void ArrAssign(Array& Dest, const Array& Src)
{
	//for (int i = 0; i < Count; i++)
	//	Dest[i] = Src[i];
	std::copy(mbegin(Src), mend(Src), mbegin(Dest));
}

template <int Count1, int Count2, typename Array>
void ArrAssign(Array& Dest, const Array& Src)
{
	//	for (int i = 0; i < Count1; i++)
	//		for (int j = 0; j < Count2; j++)
	//			Dest[i][j] = Src[i][j];
	for (int i = 0; i < Count1; i++)
		ArrAssign<Count2>(Dest[i], Src[i]);
}
*/
template <size_t Count, typename Elem>
void ArrAssign(Elem* Dest, const Elem* Src)
{
	for (int i = 0; i < Count; i++)
		Dest[i] = Src[i];
	//std::copy(mbegin(Src), mend(Src), mbegin(Dest));
}

template <int Count1, int Count2, typename Elem>
void ArrAssign(Elem (*Dest)[Count2], const Elem (*Src)[Count2])
{
	//	for (int i = 0; i < Count1; i++)
	//		for (int j = 0; j < Count2; j++)
	//			Dest[i][j] = Src[i][j];
	for (int i = 0; i < Count1; i++)
		ArrAssign<Count2>(Dest[i], Src[i]);
}



template <class T>
void Initialize(DynamicArray<T>& DynArr, const T* pArr, int Count)
{
	for(int i = 0; i < Count; i++)
		DynArr[i] = pArr[i];
}

template <class T>
DynamicArray<T> CreateDynArray(const T* pArr, int Count)
{
	DynamicArray<T> DynArr;
	DynArr.Length = Count;
	for(int i = 0; i < Count; i++)
		DynArr[i] = pArr[i];
	return DynArr;
}

template <class T, class InputIterator>
DynamicArray<T> CreateDynArray(InputIterator first, InputIterator last)
{
	int i = 0;
	DynamicArray<T> DynArray;
	DynArray.Length = std::distance(first, last);;

	for(InputIterator t = first; t != last; i++, ++t)
	{
		DynArray[i] = *t;
	}
	return DynArray;
}
#ifdef Cpp11
template <class T>
DynamicArray<T> CreateDynArray(const std::initializer_list<T>& List, int Count)
{
	DynamicArray<T> DynArr;
	DynArr.Length = Count;
//	DynArr.Length = List.size();
	auto t = List.begin();
	auto tEnd = List.end();
	for(int i = 0; t != tEnd; i++, ++t)
		DynArr[i] = *t;
  return DynArr;
}

template<typename T> using TArray = DynamicArray<T>;
#else
#define TArray DynamicArray
#endif


template <class T>
void SetLength(DynamicArray<DynamicArray<T> >& MultiDimArr, int Dim1, int Dim2)
{
	MultiDimArr.Length = Dim1;
  for(int i = 0; i < Dim1; i++)
		MultiDimArr[i].Length = Dim2;
}


} // namespace System 



#endif //  d2c_systypesH