#include <vcl.h>
#pragma hdrstop

#include "SynEditTypes.h"
#include "SynUnicode.h"

using namespace std;
using namespace d2c_system;
using namespace Synunicode;
using namespace System;
using namespace System::Sysutils;

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
/*
/* TBufferCoord * /

/* TBufferCoord */

bool __fastcall operator == (const TBufferCoord& ca, const TBufferCoord& cb)
{
	TBufferCoord a = ca;
	TBufferCoord b = cb;
	bool result = false;
	result = (a.Char == b.Char) && (a.Line == b.Line);
	return result;
}

bool __fastcall operator > (const TBufferCoord& ca, const TBufferCoord& cb)
{
	TBufferCoord a = ca;
	TBufferCoord b = cb;
	bool result = false;
	result = (b.Line < a.Line) || ((b.Line == a.Line) && (b.Char < a.Char));
	return result;
}

bool __fastcall operator >= (const TBufferCoord& ca, const TBufferCoord& cb)
{
	TBufferCoord a = ca;
	TBufferCoord b = cb;
	bool result = false;
	result = (b.Line < a.Line) || ((b.Line == a.Line) && (b.Char <= a.Char));
	return result;
}

bool __fastcall operator < (const TBufferCoord& ca, const TBufferCoord& cb)
{
	TBufferCoord a = ca;
	TBufferCoord b = cb;
	bool result = false;
	result = (b.Line > a.Line) || ((b.Line == a.Line) && (b.Char > a.Char));
	return result;
}

bool __fastcall operator <= (const TBufferCoord& ca, const TBufferCoord& cb)
{
	TBufferCoord a = ca;
	TBufferCoord b = cb;
	bool result = false;
	result = (b.Line > a.Line) || ((b.Line == a.Line) && (b.Char >= a.Char));
	return result;
}



bool __fastcall operator != (const TBufferCoord& ca, const TBufferCoord& cb)
{
	TBufferCoord a = ca;
	TBufferCoord b = cb;
	bool result = false;
	result = (a.Char != b.Char) || (a.Line != b.Line);
	return result;
}

/* TDisplayCoord */

bool __fastcall operator == (const TDisplayCoord& ca, const TDisplayCoord& cb)
{
	TDisplayCoord a = ca;
	TDisplayCoord b = cb;
	bool result = false;
	result = (a.Row == b.Row) && (a.Column == b.Column);
	return result;
}

bool __fastcall operator > (const TDisplayCoord& ca, const TDisplayCoord& cb)
{
	TDisplayCoord a = ca;
	TDisplayCoord b = cb;
	bool result = false;
	result = (b.Row < a.Row) || ((b.Row == a.Row) && (b.Column < a.Column));
	return result;
}

bool __fastcall operator >= (const TDisplayCoord& ca, const TDisplayCoord& cb)
{
	TDisplayCoord a = ca;
	TDisplayCoord b = cb;
	bool result = false;
	result = (b.Row < a.Row) || ((b.Row == a.Row) && (b.Column <= a.Column));
	return result;
}

bool __fastcall operator < (const TDisplayCoord& ca, const TDisplayCoord& cb)
{
	TDisplayCoord a = ca;
	TDisplayCoord b = cb;
	bool result = false;
	result = (b.Row > a.Row) || ((b.Row == a.Row) && (b.Column > a.Column));
	return result;
}

bool __fastcall operator <= (const TDisplayCoord& ca, const TDisplayCoord& cb)
{
	TDisplayCoord a = ca;
	TDisplayCoord b = cb;
	bool result = false;
	result = (b.Row > a.Row) || ((b.Row == a.Row) && (b.Column >= a.Column));
	return result;
}

/*#static*/
TDisplayCoord __fastcall TDisplayCoord::Max(const TDisplayCoord& ca, const TDisplayCoord& cb)
{
	TDisplayCoord a = ca;
	TDisplayCoord b = cb;
	TDisplayCoord result = {};
	if((b.Row < a.Row) || ((b.Row == a.Row) && (b.Column < a.Column)))
		result = a;
	else
		result = b;
	return result;
}

/*#static*/
TDisplayCoord __fastcall TDisplayCoord::Min(const TDisplayCoord& ca, const TDisplayCoord& cb)
{
	TDisplayCoord a = ca;
	TDisplayCoord b = cb;
	TDisplayCoord result = {};
	if((b.Row < a.Row) || ((b.Row == a.Row) && (b.Column < a.Column)))
		result = b;
	else
		result = a;
	return result;
}

bool __fastcall operator != (const TDisplayCoord& ca, const TDisplayCoord& cb)
{
	TDisplayCoord a = ca;
	TDisplayCoord b = cb;
	bool result = false;
	result = (a.Row != b.Row) || (a.Column != b.Column);
	return result;
}

String __fastcall LineBreakFromFileFormat(TSynEditFileFormat FileFormat)
{
	String result;
	switch(FileFormat)
	{
		case sffDos:
		result = WideCRLF;
		break;
		case sffUnix:
		result = WideLF;
		break;
		case sffMac:
		result = WideCR;
		break;
		case sffUnicode:
		result = WideLineSeparator;
		break;
		default:
		  ;
		break;
	}
	return result;
}


}  // namespace SynEditTypes

