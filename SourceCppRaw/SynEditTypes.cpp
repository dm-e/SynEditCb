#include <vcl.h>
#pragma hdrstop

#include "SynEditTypes.h"
#include <Vcl.Forms.hpp>
#include "SynUnicode.h"

using namespace std;
using namespace d2c_system;
using namespace Synunicode;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace Vcl::Controls;
using namespace Vcl::Forms;

namespace Synedittypes
{

__fastcall ESynError::ESynError(const String Msg) : inherited(Msg) {}
__fastcall ESynError::ESynError(const String Msg, const TVarRec* Args, int Args_maxidx) : inherited(Msg, Args, Args_maxidx) {}
__fastcall ESynError::ESynError(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Msg, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynError::ESynError(const String Msg, int AHelpContext) : inherited(Msg, AHelpContext) {}
__fastcall ESynError::ESynError(System::NativeUInt Ident) : inherited(Ident) {}
__fastcall ESynError::ESynError(System::PResStringRec ResStringRec) : inherited(ResStringRec) {}
__fastcall ESynError::ESynError(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx) : inherited(Ident, Args, Args_maxidx) {}
__fastcall ESynError::ESynError(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx) : inherited(ResStringRec, Args, Args_maxidx) {}
__fastcall ESynError::ESynError(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(ResStringRec, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynError::ESynError(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Ident, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynError::ESynError(System::NativeUInt Ident, int AHelpContext) : inherited(Ident, AHelpContext) {}
__fastcall ESynError::ESynError(System::PResStringRec ResStringRec, int AHelpContext) : inherited(ResStringRec, AHelpContext) {}
__fastcall TSynEditUndoItem::TSynEditUndoItem() {}



TDisplayCoord __fastcall DisplayCoord(int AColumn, int ARow)
{
	TDisplayCoord result = {};
	result.Column = AColumn;
	result.Row = ARow;
	return result;
}

TBufferCoord __fastcall BufferCoord(int AChar, int ALine)
{
	TBufferCoord result = {};
	result.Char = AChar;
	result.Line = ALine;
	return result;
}

/* TBufferCoord */

bool __fastcall operator == (const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	bool result = false;
	result = (A.Char == B.Char) && (A.Line == B.Line);
	return result;
}

bool __fastcall operator > (const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	bool result = false;
	result = (B.Line < A.Line) || ((B.Line == A.Line) && (B.Char < A.Char));
	return result;
}

bool __fastcall operator >= (const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	bool result = false;
	result = (B.Line < A.Line) || ((B.Line == A.Line) && (B.Char <= A.Char));
	return result;
}

bool __fastcall operator < (const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	bool result = false;
	result = (B.Line > A.Line) || ((B.Line == A.Line) && (B.Char > A.Char));
	return result;
}

bool __fastcall operator <= (const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	bool result = false;
	result = (B.Line > A.Line) || ((B.Line == A.Line) && (B.Char >= A.Char));
	return result;
}
bool __fastcall operator != (const TBufferCoord& cA, const TBufferCoord& cB)
{
	TBufferCoord A = cA;
	TBufferCoord B = cB;
	bool result = false;
	result = (A.Char != B.Char) || (A.Line != B.Line);
	return result;
}

/* TDisplayCoord */

bool __fastcall operator == (const TDisplayCoord& cA, const TDisplayCoord& cB)
{
	TDisplayCoord A = cA;
	TDisplayCoord B = cB;
	bool result = false;
	result = (A.Row == B.Row) && (A.Column == B.Column);
	return result;
}

bool __fastcall operator > (const TDisplayCoord& cA, const TDisplayCoord& cB)
{
	TDisplayCoord A = cA;
	TDisplayCoord B = cB;
	bool result = false;
	result = (B.Row < A.Row) || ((B.Row == A.Row) && (B.Column < A.Column));
	return result;
}

bool __fastcall operator >= (const TDisplayCoord& cA, const TDisplayCoord& cB)
{
	TDisplayCoord A = cA;
	TDisplayCoord B = cB;
	bool result = false;
	result = (B.Row < A.Row) || ((B.Row == A.Row) && (B.Column <= A.Column));
	return result;
}

bool __fastcall operator < (const TDisplayCoord& cA, const TDisplayCoord& cB)
{
	TDisplayCoord A = cA;
	TDisplayCoord B = cB;
	bool result = false;
	result = (B.Row > A.Row) || ((B.Row == A.Row) && (B.Column > A.Column));
	return result;
}

bool __fastcall operator <= (const TDisplayCoord& cA, const TDisplayCoord& cB)
{
	TDisplayCoord A = cA;
	TDisplayCoord B = cB;
	bool result = false;
	result = (B.Row > A.Row) || ((B.Row == A.Row) && (B.Column >= A.Column));
	return result;
}

/*#static*/
TDisplayCoord __fastcall TDisplayCoord::Max(const TDisplayCoord& cA, const TDisplayCoord& cB)
{
	TDisplayCoord A = cA;
	TDisplayCoord B = cB;
	TDisplayCoord result = {};
	if((B.Row < A.Row) || ((B.Row == A.Row) && (B.Column < A.Column)))
		result = A;
	else
		result = B;
	return result;
}

/*#static*/
TDisplayCoord __fastcall TDisplayCoord::Min(const TDisplayCoord& cA, const TDisplayCoord& cB)
{
	TDisplayCoord A = cA;
	TDisplayCoord B = cB;
	TDisplayCoord result = {};
	if((B.Row < A.Row) || ((B.Row == A.Row) && (B.Column < A.Column)))
		result = B;
	else
		result = A;
	return result;
}

bool __fastcall operator != (const TDisplayCoord& cA, const TDisplayCoord& cB)
{
	TDisplayCoord A = cA;
	TDisplayCoord B = cB;
	bool result = false;
	result = (A.Row != B.Row) || (A.Column != B.Column);
	return result;
}

String __fastcall LineBreakFromFileFormat(TSynEditFileFormat FileFormat)
{
	String result;
	switch(FileFormat)
	{
		case TSynEditFileFormat::sffDos:
		result = WideCRLF;
		break;
		case TSynEditFileFormat::sffUnix:
		result = WideLF;
		break;
		case TSynEditFileFormat::sffMac:
		result = WideCR;
		break;
		case TSynEditFileFormat::sffUnicode:
		result = WideLineSeparator;
		break;
		default:
		  ;
		break;
	}
	return result;
} 
/* TControlHelper */

int __fastcall TControlHelper::CurrentPPI()
{
	int result = 0;
	result = Screen->PixelsPerInch;
	return result;
}

int __fastcall TControlHelper::FCurrentPPI()
{
	int result = 0;
	result = Screen->PixelsPerInch;
	return result;
}


}  // namespace SynEditTypes

