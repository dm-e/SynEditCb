#ifndef d2c_graphicsH
#define d2c_graphicsH

#include <System.Types.hpp>
#include <vector>

#if defined(IS_WINDOWS) || defined(_WIN32)
  #include <windows.h>
  #include <oleidl.h>
#endif



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


// Point conversions
TPoint __fastcall SmallPointToPoint(const TSmallPoint& P);

// --------------------------------------------------
// Value converters
// Delphi -> native
// --------------------------------------------------

POINT __fastcall TPointToPOINT(const TPoint& p);
POINTL __fastcall TPointToPOINTL(const TPoint& p);

RECT __fastcall TRectToRECT(const TRect& r);
RECTL __fastcall TRectToRECTL(const TRect& r);

SIZE __fastcall TSizeToSIZE(const TSize& s);
SIZEL __fastcall TSizeToSIZEL(const TSize& s);

// --------------------------------------------------
// Value converters
// native -> Delphi
// --------------------------------------------------

TPoint __fastcall POINTToTPoint(const POINT& p);
TPoint __fastcall POINTLToTPoint(const POINTL& p);

TRect __fastcall RECTToTRect(const RECT& r);
TRect __fastcall RECTLToTRect(const RECTL& r);

TSize __fastcall SIZEToTSize(const SIZE& s);
TSize __fastcall SIZELToTSize(const SIZEL& s);

// --------------------------------------------------
// Pointer reinterpret helpers
// Only for layout-compatible types
// Delphi -> native
// --------------------------------------------------

const POINT* __fastcall TPointPtrToPOINTPtr(const TPoint* p);
POINT* __fastcall TPointPtrToPOINTPtr(TPoint* p);

const RECT* __fastcall TRectPtrToRECTPtr(const TRect* p);
RECT* __fastcall TRectPtrToRECTPtr(TRect* p);

const SIZE* __fastcall TSizePtrToSIZEPtr(const TSize* p);
SIZE* __fastcall TSizePtrToSIZEPtr(TSize* p);

// --------------------------------------------------
// Pointer reinterpret helpers
// Only for layout-compatible types
// native -> Delphi
// --------------------------------------------------

const TPoint* __fastcall POINTPtrToTPointPtr(const POINT* p);
TPoint* __fastcall POINTPtrToTPointPtr(POINT* p);

const TRect* __fastcall RECTPtrToTRectPtr(const RECT* p);
TRect* __fastcall RECTPtrToTRectPtr(RECT* p);

const TSize* __fastcall SIZEPtrToTSizePtr(const SIZE* p);
TSize* __fastcall SIZEPtrToTSizePtr(SIZE* p);

// --------------------------------------------------
// Temporary array wrappers for converted element types
// Delphi -> native COM/OLE array conversions
// --------------------------------------------------

class TPointLArrayTemp
{
private:
    std::vector<POINTL> fData;

public:
    TPointLArrayTemp(const TPoint* pPoints, size_t count);
    TPointLArrayTemp(const std::vector<TPoint>& points);

    const POINTL* __fastcall Data() const;
    POINTL* __fastcall Data();
    size_t __fastcall Size() const;
};

class TRectLArrayTemp
{
private:
    std::vector<RECTL> fData;

public:
    TRectLArrayTemp(const TRect* pRects, size_t count);

    const RECTL* __fastcall Data() const;
    RECTL* __fastcall Data();
    size_t __fastcall Size() const;
};

class TSizeLArrayTemp
{
private:
    std::vector<SIZEL> fData;

public:
    TSizeLArrayTemp(const TSize* pSizes, size_t count);

    const SIZEL* __fastcall Data() const;
    SIZEL* __fastcall Data();
    size_t __fastcall Size() const;
};


#endif



