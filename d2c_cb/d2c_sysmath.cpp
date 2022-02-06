#include <vcl.h>
#pragma hdrstop

/*
    Copyright (C) <2019>  <Dr. Detlef Meyer-Eltz>
    ---------------------------------------------

    this file is authorized for unlimited use in any
    project created with Delphi2C# or DelphiXE2Cpp11.

    http://www.texttransformer.com/
*/



#include "d2c_sysmath.h"
#include "math.h"


namespace d2c_system
{

//---------------------------------------------------------------------------
int64_t Round( long double X )
{
	return (int64_t) ( X < 0 ? X -.5 : X + .5) ;  //floor(X + 0.5);
}
//---------------------------------------------------------------------------
int64_t Trunc( long double X )
{
	long double ld;
	modfl(X, &ld);
	return (int64_t) ld;
}

}  // namespace System
