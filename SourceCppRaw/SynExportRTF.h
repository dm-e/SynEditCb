#ifndef SynExportRTFH
#define SynExportRTFH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include <Winapi.RichEdit.hpp>
#include "SynEditExport.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>

namespace Synexportrtf
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynExportRTF.pas, released 2000-04-16.

The Original Code is partly based on the mwRTFExport.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Michael Hieke.
Portions created by Michael Hieke are Copyright 2000 Michael Hieke.
Portions created by James D. Jacobson are Copyright 1999 Martin Waldenburg.
Unicode translation by Maël Hörz.
All Rights Reserved.

Contributors to the SynEdit project are listed in the Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

$Id: SynExportRTF.pas,v 1.10.2.3 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

class TSynExporterRTF : public Syneditexport::TSynCustomExporter
{
private:
	bool fAttributesChanged;
	System::Classes::TList* fListColors;
	String __fastcall ColorToRTF(TColor AColor);
	int __fastcall GetColorIndex(TColor AColor);
protected:
	virtual void __fastcall FormatAfterLastAttribute();
	virtual void __fastcall FormatAttributeDone(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged);
	virtual void __fastcall FormatAttributeInit(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged);
	virtual void __fastcall FormatBeforeFirstAttribute(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged);
	virtual void __fastcall FormatNewLine();
	virtual String __fastcall GetFooter();
	virtual String __fastcall GetFormatName();
	virtual String __fastcall GetHeader();
	virtual String __fastcall ReplaceReservedChar(WideChar AChar);
	virtual bool __fastcall UseBom();
public:
	typedef Syneditexport::TSynCustomExporter inherited;	
	#include "SynExportRTF_friends.inc"
	__fastcall TSynExporterRTF(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynExporterRTF();
	virtual void __fastcall Clear();
	virtual Synunicode::TSynEncodings __fastcall SupportedEncodings();
__published:
	__property  Color;
	__property  DefaultFilter;
	__property  Encoding;
	__property  Font;
	__property  Highlighter;
	__property  Title;
	__property  UseBackground;
};


}  // namespace SynExportRTF

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synexportrtf;
#endif

#endif // SynExportRTFH

