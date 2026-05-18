#ifndef d2c_sysmathH
#define d2c_sysmathH

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


#include "d2c_systypes.h"


namespace d2c_system {


int64_t Round( long double d );
int64_t Trunc( long double d );


} // namespace System

#endif