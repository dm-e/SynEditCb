#pragma hdrstop

#include "d2c_graphics.h"

//---------------------------------------------------------------------------
TPoint __fastcall SmallPointToPoint(const TSmallPoint& P)
{
	TPoint result;
	result.X = P.x;
	result.Y = P.y;
	return result;
}

