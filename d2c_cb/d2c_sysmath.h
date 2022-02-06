#ifndef d2c_sysmathH
#define d2c_sysmathH

/*
This is a shortened version of the Delphi2CB utility file of the same name.
The file is required in order to be able to compile the code of the SynEdit
components, which were translated to C++ with Delphi2CB:

	https://www.texttransformer.com/Delphi2CB_en.html

The translated code and this file are subject to the same license terms
as the original SynEdit code. These terms are precisely specified in

	Source\Source\SynEditJedi.inc.

*/



#include "d2c_systypes.h"


namespace d2c_system {


int64_t Round( long double d );
int64_t Trunc( long double d );


} // namespace System

#endif