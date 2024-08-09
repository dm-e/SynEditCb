#include <vcl.h>
#pragma hdrstop



#include "d2c_sysstring.h"
#include <algorithm>

#include "d2c_system.h"
#include <Sysutils.hpp>


using namespace std;

/*****************************************************************************
                    subroutines for String handling
*****************************************************************************/

namespace d2c_system
{


//---------------------------------------------------------------------------
void SetString( UnicodeString& S, wchar_t* Buffer, int Len )
{
	S = UnicodeString(Buffer, Len);
}
//---------------------------------------------------------------------------
int Length(const UnicodeString& S)
{
	return S.Length();
}
//---------------------------------------------------------------------------
d2c_size_t d2c_min(d2c_size_t xi1, d2c_size_t xi2)
{
	return xi1 < xi2 ? xi1 : xi2;
}
//---------------------------------------------------------------------------
// works too, if one parameter is an array pointer
int d2c_wcsncmp(const wchar_t* xs1, const wchar_t* xs2)
{
	d2c_size_t i1 = charLen(xs1);
	d2c_size_t i2 = charLen(xs2);
	if(i1 != i2)
	{
		if(i1 == 0)
			return -1;
		else
		if(i2 == 0)
			return 1;
	}
	return wcsncmp(xs1, xs2, d2c_min(i1, i2));
}
//---------------------------------------------------------------------------
bool CharEqualStr(wchar_t c, UnicodeString s)
{
  return s.Length() == 1 && s[1] == c;
}
//---------------------------------------------------------------------------


} // namespace System

