#ifndef d2c_sysstringH
#define d2c_sysstringH

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
#include <iterator>





namespace d2c_system
{
	int d2c_wcsncmp(const wchar_t* xs1, const wchar_t* xs2);
	
	// -------------------------------------------------
// Insert / Delete
// -------------------------------------------------

	void Insert(const UnicodeString& source, UnicodeString& dest, int index);
	void Delete(UnicodeString& s, int index, int size);

} // namespace d2c_string



namespace System
{
	void SetString( UnicodeString& S, wchar_t* Buf, int Len );
	int Length(const UnicodeString& S);
	bool CharEqualStr(wchar_t c, UnicodeString s);

// Creates a 1-character UnicodeString from a WideChar.
	inline UnicodeString CharToStr(WideChar c)
	{
		UnicodeString tmp;
		tmp.SetLength(1);
		tmp[1] = c; // UnicodeString is 1-based in C++Builder
		return tmp;
	}


	// Pos for a single character, Delphi-compatible.
	inline int PosChar(WideChar c, const UnicodeString& s, int offset = 1)
	{
		return System::Pos(CharToStr(c), s, offset);
	}

	UnicodeString Copy(const UnicodeString& s, int index, int count);

} // namespace System

#endif