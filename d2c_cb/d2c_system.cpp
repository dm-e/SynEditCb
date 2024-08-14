#include <vcl.h>
#pragma hdrstop

/*
    Copyright (C) <2019>  <Dr. Detlef Meyer-Eltz>
    ---------------------------------------------

    this file is authorized for unlimited use in any
    project created with Delphi2C# or DelphiXE2Cpp11.

    http://www.texttransformer.com/
*/




#include "d2c_system.h"
#include "d2c_sysmath.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <iomanip>

#if defined(windows) && defined (_WIDESTRING)
#include <ShellAPI.h> // CommandLineToArgvW
#endif

using namespace std;



// #define _CRT_NON_CONFORMING_SWPRINTFS 1




namespace d2c_system
{

void FillChar( void* X, int Count, unsignedchar Value )
{
	memset(X, Value, Count);
}

void Assert( bool expr )
{
  if(!expr)
    throw runtime_error("assertion failed");
}

void Assert( bool expr, const AnsiString& Msg )
{
	if(!expr)
		throw runtime_error(Msg.c_str());
}

void Initialize(void** V, int Count /*= -1*/)
{
	//https://docwiki.embarcadero.com/Libraries/Sydney/de/System.Initialize
}

void Finalize(void** V, int Count /*= -1*/)
{
  // https://docwiki.embarcadero.com/Libraries/Sydney/de/System.Finalize
}


}  // namespace System
