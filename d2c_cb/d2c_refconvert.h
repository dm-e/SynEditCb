#ifndef d2c_refconvertH
#define d2c_refconvertH

#include <type_traits>
#include <utility>

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

template<typename T>
class TPtrRef
{
private:
    T* FPtr;

public:
    explicit TPtrRef(T* ptr);
    operator T&();
    operator const T&() const;
    T& Get();
    const T& Get() const;

private:
    TPtrRef(const TPtrRef&);
	TPtrRef& operator=(const TPtrRef&);
};

// practically the same as TPtrRef
template<typename T>
class TOutPtrRef
{
private:
    T* FPtr;

public:
    explicit TOutPtrRef(T* ptr);
    operator T&();
    operator const T&() const;
    T& Get();
    const T& Get() const;

private:
    TOutPtrRef(const TOutPtrRef&);
    TOutPtrRef& operator=(const TOutPtrRef&);
};

template<typename TSource, typename TTarget>
class TInOutRefConverter
{
private:
    TSource* FSource;
    TTarget FValue;

public:
    explicit TInOutRefConverter(TSource* src);
    ~TInOutRefConverter();

    operator TTarget&();
    operator const TTarget&() const;

    TTarget& Get();
    const TTarget& Get() const;

private:
    TInOutRefConverter(const TInOutRefConverter&);
    TInOutRefConverter& operator=(const TInOutRefConverter&);
};

template<typename TSource, typename TTarget>
class TOutRefConverter
{
private:
    TSource* FSource;
    TTarget FValue;

public:
    explicit TOutRefConverter(TSource* src);
    ~TOutRefConverter();

    operator TTarget&();
    operator const TTarget&() const;

    TTarget& Get();
    const TTarget& Get() const;

private:
    TOutRefConverter(const TOutRefConverter&);
    TOutRefConverter& operator=(const TOutRefConverter&);
};

template<typename T>
inline TPtrRef<T> d2c_ref(T* ptr);

template<typename T>
inline TOutPtrRef<T> d2c_out_ref(T* ptr);

template<typename TTarget, typename TSource>
inline TInOutRefConverter<TSource, TTarget> d2c_inout_ref_conv(TSource* src);

template<typename TTarget, typename TSource>
inline TOutRefConverter<TSource, TTarget> d2c_out_ref_conv(TSource* src);


// TPtrRef

template<typename T>
inline TPtrRef<T>::TPtrRef(T* ptr)
    : FPtr(ptr)
{
}

template<typename T>
inline TPtrRef<T>::operator T&()
{
    return *FPtr;
}

template<typename T>
inline TPtrRef<T>::operator const T&() const
{
    return *FPtr;
}

template<typename T>
inline T& TPtrRef<T>::Get()
{
    return *FPtr;
}

template<typename T>
inline const T& TPtrRef<T>::Get() const
{
    return *FPtr;
}


// TOutPtrRef

template<typename T>
inline TOutPtrRef<T>::TOutPtrRef(T* ptr)
    : FPtr(ptr)
{
}

template<typename T>
inline TOutPtrRef<T>::operator T&()
{
    return *FPtr;
}

template<typename T>
inline TOutPtrRef<T>::operator const T&() const
{
    return *FPtr;
}

template<typename T>
inline T& TOutPtrRef<T>::Get()
{
    return *FPtr;
}

template<typename T>
inline const T& TOutPtrRef<T>::Get() const
{
    return *FPtr;
}


// TInOutRefConverter

template<typename TSource, typename TTarget>
inline TInOutRefConverter<TSource, TTarget>::TInOutRefConverter(TSource* src)
    : FSource(src), FValue(static_cast<TTarget>(*src))
{
}

template<typename TSource, typename TTarget>
inline TInOutRefConverter<TSource, TTarget>::~TInOutRefConverter()
{
    if (FSource != 0)
    {
        *FSource = static_cast<TSource>(FValue);
    }
}

template<typename TSource, typename TTarget>
inline TInOutRefConverter<TSource, TTarget>::operator TTarget&()
{
    return FValue;
}

template<typename TSource, typename TTarget>
inline TInOutRefConverter<TSource, TTarget>::operator const TTarget&() const
{
    return FValue;
}

template<typename TSource, typename TTarget>
inline TTarget& TInOutRefConverter<TSource, TTarget>::Get()
{
    return FValue;
}

template<typename TSource, typename TTarget>
inline const TTarget& TInOutRefConverter<TSource, TTarget>::Get() const
{
    return FValue;
}


// TOutRefConverter

template<typename TSource, typename TTarget>
inline TOutRefConverter<TSource, TTarget>::TOutRefConverter(TSource* src)
    : FSource(src), FValue()
{
}

template<typename TSource, typename TTarget>
inline TOutRefConverter<TSource, TTarget>::~TOutRefConverter()
{
    if (FSource != 0)
    {
        *FSource = static_cast<TSource>(FValue);
    }
}

template<typename TSource, typename TTarget>
inline TOutRefConverter<TSource, TTarget>::operator TTarget&()
{
    return FValue;
}

template<typename TSource, typename TTarget>
inline TOutRefConverter<TSource, TTarget>::operator const TTarget&() const
{
    return FValue;
}

template<typename TSource, typename TTarget>
inline TTarget& TOutRefConverter<TSource, TTarget>::Get()
{
    return FValue;
}

template<typename TSource, typename TTarget>
inline const TTarget& TOutRefConverter<TSource, TTarget>::Get() const
{
    return FValue;
}


// Helper functions

template<typename T>
inline TPtrRef<T> d2c_ref(T* ptr)
{
    return TPtrRef<T>(ptr);
}

template<typename T>
inline TOutPtrRef<T> d2c_out_ref(T* ptr)
{
    return TOutPtrRef<T>(ptr);
}

template<typename TTarget, typename TSource>
inline TInOutRefConverter<TSource, TTarget> d2c_inout_ref_conv(TSource* src)
{
    return TInOutRefConverter<TSource, TTarget>(src);
}

template<typename TTarget, typename TSource>
inline TOutRefConverter<TSource, TTarget> d2c_out_ref_conv(TSource* src)
{
	return TOutRefConverter<TSource, TTarget>(src);
}


template<typename T>
class TTempPtr
{
private:
	T FValue;

public:
	explicit TTempPtr(const T& value)
		: FValue(value)
	{
	}

	operator const T* () const
	{
		return &FValue;
	}
};




#endif // d2c_refconvertH
