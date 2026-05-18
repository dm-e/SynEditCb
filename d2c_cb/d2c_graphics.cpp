#pragma hdrstop

#include "d2c_graphics.h"

using namespace std;

//---------------------------------------------------------------------------
TPoint __fastcall SmallPointToPoint(const TSmallPoint& P)
{
	TPoint result;
	result.X = P.x;
	result.Y = P.y;
	return result;
}

// --------------------------------------------------
// Optional safety checks for reinterpret helpers
// --------------------------------------------------

static_assert(sizeof(TPoint) == sizeof(POINT), "TPoint and POINT must have identical size");
static_assert(sizeof(TRect) == sizeof(RECT), "TRect and RECT must have identical size");
static_assert(sizeof(TSize) == sizeof(SIZE), "TSize and SIZE must have identical size");

// --------------------------------------------------
// Value converters
// Delphi -> native
// --------------------------------------------------

POINT __fastcall TPointToPOINT(const TPoint& p)
{
    POINT result;
    result.x = static_cast<LONG>(p.x);
    result.y = static_cast<LONG>(p.y);
    return result;
}

POINTL __fastcall TPointToPOINTL(const TPoint& p)
{
    POINTL result;
    result.x = static_cast<LONG>(p.x);
    result.y = static_cast<LONG>(p.y);
    return result;
}

RECT __fastcall TRectToRECT(const TRect& r)
{
    RECT result;
    result.left = static_cast<LONG>(r.left);
    result.top = static_cast<LONG>(r.top);
    result.right = static_cast<LONG>(r.right);
    result.bottom = static_cast<LONG>(r.bottom);
    return result;
}

RECTL __fastcall TRectToRECTL(const TRect& r)
{
    RECTL result;
    result.left = static_cast<LONG>(r.left);
    result.top = static_cast<LONG>(r.top);
    result.right = static_cast<LONG>(r.right);
    result.bottom = static_cast<LONG>(r.bottom);
    return result;
}

SIZE __fastcall TSizeToSIZE(const TSize& s)
{
    SIZE result;
    result.cx = static_cast<LONG>(s.cx);
    result.cy = static_cast<LONG>(s.cy);
    return result;
}

SIZEL __fastcall TSizeToSIZEL(const TSize& s)
{
    SIZEL result;
    result.cx = static_cast<LONG>(s.cx);
    result.cy = static_cast<LONG>(s.cy);
    return result;
}

// --------------------------------------------------
// Value converters
// native -> Delphi
// --------------------------------------------------

TPoint __fastcall POINTToTPoint(const POINT& p)
{
    TPoint result;
    result.x = static_cast<int>(p.x);
    result.y = static_cast<int>(p.y);
    return result;
}

TPoint __fastcall POINTLToTPoint(const POINTL& p)
{
    TPoint result;
    result.x = static_cast<int>(p.x);
    result.y = static_cast<int>(p.y);
    return result;
}

TRect __fastcall RECTToTRect(const RECT& r)
{
    TRect result;
    result.left = static_cast<int>(r.left);
    result.top = static_cast<int>(r.top);
    result.right = static_cast<int>(r.right);
    result.bottom = static_cast<int>(r.bottom);
    return result;
}

TRect __fastcall RECTLToTRect(const RECTL& r)
{
    TRect result;
    result.left = static_cast<int>(r.left);
    result.top = static_cast<int>(r.top);
    result.right = static_cast<int>(r.right);
    result.bottom = static_cast<int>(r.bottom);
    return result;
}

TSize __fastcall SIZEToTSize(const SIZE& s)
{
    TSize result;
    result.cx = static_cast<int>(s.cx);
    result.cy = static_cast<int>(s.cy);
    return result;
}

TSize __fastcall SIZELToTSize(const SIZEL& s)
{
    TSize result;
    result.cx = static_cast<int>(s.cx);
    result.cy = static_cast<int>(s.cy);
    return result;
}

// --------------------------------------------------
// Pointer reinterpret helpers
// Only for layout-compatible types
// Delphi -> native
// --------------------------------------------------

const POINT* __fastcall TPointPtrToPOINTPtr(const TPoint* p)
{
    return reinterpret_cast<const POINT*>(p);
}

POINT* __fastcall TPointPtrToPOINTPtr(TPoint* p)
{
    return reinterpret_cast<POINT*>(p);
}

const RECT* __fastcall TRectPtrToRECTPtr(const TRect* p)
{
    return reinterpret_cast<const RECT*>(p);
}

RECT* __fastcall TRectPtrToRECTPtr(TRect* p)
{
    return reinterpret_cast<RECT*>(p);
}

const SIZE* __fastcall TSizePtrToSIZEPtr(const TSize* p)
{
    return reinterpret_cast<const SIZE*>(p);
}

SIZE* __fastcall TSizePtrToSIZEPtr(TSize* p)
{
    return reinterpret_cast<SIZE*>(p);
}

// --------------------------------------------------
// Pointer reinterpret helpers
// Only for layout-compatible types
// native -> Delphi
// --------------------------------------------------

const TPoint* __fastcall POINTPtrToTPointPtr(const POINT* p)
{
    return reinterpret_cast<const TPoint*>(p);
}

TPoint* __fastcall POINTPtrToTPointPtr(POINT* p)
{
    return reinterpret_cast<TPoint*>(p);
}

const TRect* __fastcall RECTPtrToTRectPtr(const RECT* p)
{
    return reinterpret_cast<const TRect*>(p);
}

TRect* __fastcall RECTPtrToTRectPtr(RECT* p)
{
    return reinterpret_cast<TRect*>(p);
}

const TSize* __fastcall SIZEPtrToTSizePtr(const SIZE* p)
{
    return reinterpret_cast<const TSize*>(p);
}

TSize* __fastcall SIZEPtrToTSizePtr(SIZE* p)
{
    return reinterpret_cast<TSize*>(p);
}

// --------------------------------------------------
// Temporary array wrappers for converted element types
// Delphi -> native COM/OLE array conversions
// --------------------------------------------------

TPointLArrayTemp::TPointLArrayTemp(const TPoint* pPoints, size_t count)
{
    fData.reserve(count);

    for (size_t i = 0; i < count; ++i)
    {
        fData.push_back(TPointToPOINTL(pPoints[i]));
    }
}

TPointLArrayTemp::TPointLArrayTemp(const std::vector<TPoint>& points)
{
    fData.reserve(points.size());

    for (size_t i = 0; i < points.size(); ++i)
    {
        fData.push_back(TPointToPOINTL(points[i]));
    }
}

const POINTL* __fastcall TPointLArrayTemp::Data() const
{
    return fData.empty() ? nullptr : fData.data();
}

POINTL* __fastcall TPointLArrayTemp::Data()
{
    return fData.empty() ? nullptr : fData.data();
}

size_t __fastcall TPointLArrayTemp::Size() const
{
    return fData.size();
}

TRectLArrayTemp::TRectLArrayTemp(const TRect* pRects, size_t count)
{
    fData.reserve(count);

    for (size_t i = 0; i < count; ++i)
    {
        fData.push_back(TRectToRECTL(pRects[i]));
    }
}

const RECTL* __fastcall TRectLArrayTemp::Data() const
{
    return fData.empty() ? nullptr : fData.data();
}

RECTL* __fastcall TRectLArrayTemp::Data()
{
    return fData.empty() ? nullptr : fData.data();
}

size_t __fastcall TRectLArrayTemp::Size() const
{
    return fData.size();
}

TSizeLArrayTemp::TSizeLArrayTemp(const TSize* pSizes, size_t count)
{
    fData.reserve(count);

    for (size_t i = 0; i < count; ++i)
    {
        fData.push_back(TSizeToSIZEL(pSizes[i]));
    }
}

const SIZEL* __fastcall TSizeLArrayTemp::Data() const
{
    return fData.empty() ? nullptr : fData.data();
}

SIZEL* __fastcall TSizeLArrayTemp::Data()
{
    return fData.empty() ? nullptr : fData.data();
}

size_t __fastcall TSizeLArrayTemp::Size() const
{
    return fData.size();
}
