
/*
    Copyright (C) <2026>  <Dr. Detlef Meyer-Eltz>
    ---------------------------------------------

    this file is authorized for unlimited use in any
    project created with Delphi2Cpp or Delphi2CB.

    http://www.texttransformer.com/
*/



#ifndef d2c_systypesH
#define d2c_systypesH


#include <System.hpp>
#include <vector>
#include <limits>
#include <stdint.h>
#include <string>
//#include <sysdyn.h>  #error Do not include this file directly. Include 'System.hpp' instead.
#include "d2c_array.h"

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



} // namespace System 



#endif //  d2c_systypesH