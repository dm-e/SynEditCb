#ifndef d2c_arrayH
#define d2c_arrayH

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

namespace System {

	template<class T>
	using D2CArray = System::DynamicArray<T>;


    template <class T>
    inline const T* DynamicArrayPointer(const D2CArray<T>& DA, unsigned int Index = 0)
    {
        return (DA.Length > 0) ? &DA[Index] : NULL;
    }

    template <class T>
    inline T* DynamicArrayPointer(D2CArray<T>& DA, unsigned int Index = 0)
    {
        return (DA.Length > 0) ? &DA[Index] : NULL;
    }


} // namespace System


#endif // d2c_arrayH
