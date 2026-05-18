#ifndef d2c_sysinterfaceH
#define d2c_sysinterfaceH

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

// C++Builder facade for interface helpers.

#include <System.hpp>
#include <System.SysUtils.hpp>

#include "d2c_diout.h"           // must come first
#include "d2c_supports.h"
#include "d2c_cast.h"
#include "d2c_frominterface.h"

template<typename T>
typename std::enable_if<
    std::is_base_of<System::IInterface, typename std::remove_pointer<T>::type>::value,
    bool
>::type
InterfaceIs(System::IInterface* obj)
{
    if (!obj)
        return false;
    T out = nullptr;
    return obj->QueryInterface(__uuidof(typename std::remove_pointer<T>::type),
                               reinterpret_cast<void**>(&out)) == S_OK;
}

// normally in d2c_supports.h
// Checks if obj is instance of AClass or any subclass
inline bool IsInstanceOf(System::TObject* obj, System::TClass AClass)
{
  return obj != nullptr && obj->InheritsFrom(AClass);
}

#define D2C_IS(obj, cls) ((obj) != nullptr && (obj)->InheritsFrom(cls))


// Delphi: obj is TMyClass
template<class T>
inline bool IsInstanceOf(System::TObject* obj)
{
  return dynamic_cast<T*>(obj) != nullptr;
}

// Delphi: obj.ClassType = TMyClass
inline bool IsExactClass(System::TObject* obj, System::TClass AClass)
{
  return obj != nullptr && obj->ClassType() == AClass;
}


#endif  // d2c_sysinterfaceH
