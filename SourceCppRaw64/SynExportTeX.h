/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynExportTeX.pas, released 2002-09-12.

The Original Code is partly based on the mwHTMLExport.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Ascher Stefan.
Portions created by Ascher Stefan are Copyright 2002 Ascher Stefan.
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

$Id: SynExportTeX.pas,v 1.8.2.5 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
- LaTeX 2e doesn't support Unicode, so this exporter doesn't either.
  (There are solutions like the package utc.sty but still they don't allow mixing
  of different languages like Arabic and Chinese.
  We'll have to wait for LaTeX 3.)
-------------------------------------------------------------------------------*/
#ifndef SynExportTeXH
#define SynExportTeXH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEditExport.h"
#include "SynEditHighlighter.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>

namespace Synexporttex
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynExportTeX.pas, released 2002-09-12.

The Original Code is partly based on the mwHTMLExport.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Ascher Stefan.
Portions created by Ascher Stefan are Copyright 2002 Ascher Stefan.
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

$Id: SynExportTeX.pas,v 1.8.2.5 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
- LaTeX 2e doesn't support Unicode, so this exporter doesn't either.
  (There are solutions like the package utc.sty but still they don't allow mixing
  of different languages like Arabic and Chinese.
  We'll have to wait for LaTeX 3.)
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/* Common compiler defines                                                      */
/* (remove the dot in front of a define to enable it)                           */
/*------------------------------------------------------------------------------*/

/*$B-,H+*/ // defaults are short evaluation of boolean values and long strings

/*.$DEFINE SYN_DEVELOPMENT_CHECKS*/ // additional tests for debugging
  

/*------------------------------------------------------------------------------*/
/* Pull in all defines from SynEditJedi.inc (must be done after the common      */
/* compiler defines to  work correctly). Use SynEdit-prefix to avoid problems   */
/* with other versions of jedi.inc in the search-path.                          */
/*------------------------------------------------------------------------------*/

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

/*------------------------------------------------------------------------------*/
/*  Please change this to suit your needs (to activate an option remove the dot */
/*  in front of a DEFINE)                                                       */
/*------------------------------------------------------------------------------*/

// "Heredoc" syntax highlighting
// If you enable the following statement and use highlighter(s) that have
// support for "Heredoc" strings as scheme(s) in SynMultiSyn, you must
// implement your own SynMultiSyn OnCustomRange event handler in order to
// properly store Range State information
/*.$DEFINE SYN_HEREDOC*/

// Turn this off if you don't need complex script support, since it is slower
/*.$DEFINE SYN_UNISCRIBE*/

// $Id: SynEdit.inc,v 1.16.2.19 2009/06/14 13:41:44 maelh Exp $

class TSynExporterTeX : public Syneditexport::TSynCustomExporter
{
private:
	int FMargin;
	Synedithighlighter::TSynHighlighterAttributes* fLastAttri;
	String __fastcall AttriToCommand(Synedithighlighter::TSynHighlighterAttributes* Attri, String UniqueAttriName);
	bool __fastcall AttriToCommandCallback(Synedithighlighter::TSynCustomHighlighter* Highlighter, Synedithighlighter::TSynHighlighterAttributes* Attri, String UniqueAttriName, void** Params, int Params_maxidx);
	bool __fastcall CommandNameCallback(Synedithighlighter::TSynCustomHighlighter* Highlighter, Synedithighlighter::TSynHighlighterAttributes* Attri, String UniqueAttriName, void** Params, int Params_maxidx);
	String __fastcall GetCommandName(Synedithighlighter::TSynCustomHighlighter* Highlighter, Synedithighlighter::TSynHighlighterAttributes* Attri);
	String __fastcall GetNewCommands();
	String __fastcall MakeValidName(String Name);
protected:
	bool fCreateTeXFragment;
	int FTabWidth;
	bool fPageStyleEmpty;
    
    // overriding these abstract methods (though they are never called for this
    // specific highlighter) to prevent abstract instance warnings
	virtual void __fastcall FormatAfterLastAttribute();
	virtual void __fastcall FormatAttributeDone(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged);
	virtual void __fastcall FormatAttributeInit(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged);
	virtual void __fastcall FormatBeforeFirstAttribute(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged);
	virtual void __fastcall FormatNewLine();
	virtual void __fastcall FormatToken(String Token);
	virtual String __fastcall GetFooter();
	virtual String __fastcall GetFormatName();
	virtual String __fastcall GetHeader();
	virtual String __fastcall ReplaceReservedChar(WideChar AChar);
	virtual void __fastcall SetTokenAttribute(Synedithighlighter::TSynHighlighterAttributes* Attri);
	virtual bool __fastcall UseBom();
public:
	typedef Syneditexport::TSynCustomExporter inherited;
	#include "SynExportTeX_friends.inc"
	__fastcall TSynExporterTeX(TComponent* AOwner);
	virtual Synunicode::TSynEncodings __fastcall SupportedEncodings();
__published:
public:
	__property int Margin = { read = FMargin, write = FMargin, default = 2 };
	__property int TabWidth = { read = FTabWidth, write = FTabWidth, default = 2 };
	__property  Color;
	__property bool CreateTeXFragment = { read = fCreateTeXFragment, write = fCreateTeXFragment, default = false };
	__property bool PageStyleEmpty = { read = fPageStyleEmpty, write = fPageStyleEmpty, default = false };
	__property  DefaultFilter;
	__property  Encoding;
	__property  Font;
	__property  Highlighter;
	__property  Title;
	__property  UseBackground;
};


}  // namespace SynExportTeX

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synexporttex;
#endif

#endif // SynExportTeXH

