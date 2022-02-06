#ifndef d2c_sysstringH
#define d2c_sysstringH

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
#include <iterator>





namespace d2c_system
{


void SetString( UnicodeString& S, wchar_t* Buf, int Len );
int Length(const UnicodeString& S);
int d2c_wcsncmp(const wchar_t* xs1, const wchar_t* xs2);


} // namespace d2c_string

#endif