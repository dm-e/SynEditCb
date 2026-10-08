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



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditTypes.pas, released 2000-04-07.
The Original Code is based on parts of mwCustomEdit.pas by Martin Waldenburg,
part of the mwEdit component suite.
Portions created by Martin Waldenburg are Copyright (C) 1998 Martin Waldenburg.
Unicode translation by Maël Hörz.
All Rights Reserved.

Contributors to the SynEdit and mwEdit projects are listed in the
Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

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


}  // namespace Synedittypes

