#ifndef d2c_openarrayH
#define d2c_openarrayH

/*
This is a shortened version of the Delphi2CB utility file of the same name.
The file is required in order to be able to compile the code of the SynEdit
components, which were translated to C++ with Delphi2CB:

	https://www.texttransformer.com/Delphi2CB_en.html

The translated code and this file are subject to the same license terms
as the original SynEdit code. These terms are precisely specified in

	Source\Source\SynEditJedi.inc.
*/


#include "sysdyn.h"
#include <string>
#include <vector>
//---------------------------------------------------------------------------

		template<class T> class OpenArrayEx
		{
		public:
			__fastcall OpenArrayEx()
			{
				Array = NULL;
				Count = 0;
			}

			__fastcall OpenArrayEx(const DynamicArray<T>& src)
			{
				Array = new T[Count = src.Length];
				for (int i = 0; i < Count; i++)
					Array[i] = src[i];
			}

			__fastcall OpenArrayEx(const OpenArrayEx& src)
			{
				Array = new T[Count = src.Count];
				for (int i = 0; i < Count; i++)
					Array[i] = src.Array[i];
			}

			__fastcall ~OpenArrayEx()
			{
				delete [] Array;
			}

			OpenArrayEx& __fastcall operator =(const OpenArrayEx& rhs);

			__fastcall operator T*()
			{
					return Array;
			}
			int __fastcall GetHigh()
			{
					return Count - 1;
			}

		__fastcall OpenArrayEx(const T* pArr, int Count)
		{
			Array = new T[Count];
			for(int i = 0; i < Count; i++)
				Array[i] = pArr[i];
		}

		template <class InputIterator>
		__fastcall OpenArrayEx(InputIterator first, InputIterator last)
		{
			int i = 0;
			Array = new T[std::distance(first, last)];

			for(InputIterator t = first; t != last; i++, ++t)
				Array[i] = *t;
		}
#ifdef Cpp11
		__fastcall OpenArrayEx(const std::initializer_list<T>& List, int Count)
		{
			Array = new T[Count];
			auto t = List.begin();
			auto tEnd = List.end();
			for(int i = 0; t != tEnd; i++, ++t)
				Array[i] = *t;
		}
#endif
		private:
			T* Array;
			long Count;
		};

		template<class T>
		OpenArrayEx<T>& __fastcall
		OpenArrayEx<T>::operator =(const OpenArrayEx& rhs)
		{
			if (this != &rhs)
			{
				delete[] Array;
				Array = new T[Count = rhs.Count];
				for (int i = 0; i < Count; i++)
					Array[i] = rhs.Array[i];
			}
			return *this;
	}


	template <class T>
	class OpenArrayRef
	{
	public:
		OpenArrayRef(T* Data, int Size) : m_pData(Data), m_iSize(Size) {}
		OpenArrayRef(std::vector<T>& v) : m_pData(v.data()), m_iSize(v.size()) {}
		OpenArrayRef(DynamicArray<T>& arr) : m_pData(&arr[0]), m_iSize(arr.Length ) {}
		OpenArrayRef(std::basic_string<T>& s) : m_pData((T*) s.c_str()), m_iSize(s.size()) {}

		inline T operator [] (const unsigned char xiIndex) const
		{
			return m_pData[xiIndex];
		}
		
		inline T& operator [](const unsigned char xiIndex)
		{
			return m_pData[xiIndex];
		}

		inline T* data() { return m_pData; }

		inline int  size()  const { return m_iSize; }
		inline bool IsEmpty() const { return m_iSize == 0; }

	protected:
		T*   m_pData;
		int  m_iSize;
	};

	template <class T, int N>
	class OpenArrayRef2 : public OpenArrayRef<T>
	{
		typedef OpenArrayRef<T> inherited;
	public:
		OpenArrayRef2(T(&arr)[N]) : inherited((T*)arr, N) {}
	};

	template <unsigned char N>
	class OpenArrayRef3 : public OpenArrayRef<char>
	{
		typedef OpenArrayRef<char> inherited;
	public:
		OpenArrayRef3(System::SmallString<N>& Str) : inherited((char*) Str.c_str(), N) {}
	};




#endif  // d2c_openarrayH
