


#include "d2c_convert.h"
#include "d2c_systypes.h"

/*
    Copyright (C) <2019>  <Dr. Detlef Meyer-Eltz>
    ---------------------------------------------

    this file is authorized for unlimited use in any
    project created with Delphi2C# or DelphiXE2Cpp11.

    http://www.texttransformer.com/
*/


using namespace std;
using namespace System;




PAnsiChar astr2pchar(const AnsiString& xs, int index /*=0*/)
{
	return const_cast<char*>(xs.c_str()) + index;
}


PWideChar ustr2pwchar(const UnicodeString& xs, int index /*=0*/)
{
	return const_cast<WideChar*>(xs.c_str() + index);
}

void* ustr2address(const UnicodeString& xs, int index /*=0*/)
{
	return static_cast<void*>(const_cast<WideChar*>(xs.c_str()) + index);
}

