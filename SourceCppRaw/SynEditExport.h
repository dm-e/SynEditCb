/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditExport.pas, released 2000-04-16.

The Original Code is partly based on the mwExport.pas file from the
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

$Id: SynEditExport.pas,v 1.17.2.8 2008/09/17 13:59:12 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

/* Base class for exporting a programming language source file or part of it to
  a formatted output like HTML or RTF and copying this to the Windows clipboard
  or saving it to a file. */
#ifndef SynEditExportH
#define SynEditExportH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Clipbrd.hpp>
#include "SynEditHighlighter.h"
#include "SynEditTypes.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include "SynEditDelphiInstances.hpp"

namespace Syneditexport
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditExport.pas, released 2000-04-16.

The Original Code is partly based on the mwExport.pas file from the
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

$Id: SynEditExport.pas,v 1.17.2.8 2008/09/17 13:59:12 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

/* Base class for exporting a programming language source file or part of it to
  a formatted output like HTML or RTF and copying this to the Windows clipboard
  or saving it to a file. */

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

class ESynEncoding : public Synedittypes::ESynError
{
	#include "SynEditExport_friends.inc"
public:
	typedef Synedittypes::ESynError inherited;
	__fastcall ESynEncoding(const String Msg);
	__fastcall ESynEncoding(const String Msg, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynEncoding(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynEncoding(const String Msg, int AHelpContext);
	__fastcall ESynEncoding(System::NativeUInt Ident);
	__fastcall ESynEncoding(System::PResStringRec ResStringRec);
	__fastcall ESynEncoding(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynEncoding(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx);
	__fastcall ESynEncoding(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynEncoding(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext);
	__fastcall ESynEncoding(System::NativeUInt Ident, int AHelpContext);
	__fastcall ESynEncoding(System::PResStringRec ResStringRec, int AHelpContext);
};

  /* Base exporter class, implements the buffering and the common functionality
    to track the changes of token attributes, to export to the clipboard or to
    save the output to a file. Descendant classes have to implement only the
    actual formatting of tokens. */

class TSynCustomExporter : public System::Classes::TComponent
{
private:
	TMemoryStream* fBuffer;
	int FCharSize;
	bool fFirstAttribute;
	bool FStreaming;
	void __fastcall AssignFont(TFont* Value);
	void __fastcall SetEncoding(Synunicode::TSynEncoding Value);
	void __fastcall SetExportAsText(bool Value);
	void __fastcall SetFont(TFont* Value);
	void __fastcall SetHighlighter(Synedithighlighter::TSynCustomHighlighter* Value);
	void __fastcall SetTitle(const String Value);
	void __fastcall SetUseBackground(bool Value);
	int __fastcall StringSize(const String AText);
	void __fastcall WriteString(const String AText);
protected:
	TColor fBackgroundColor;
	UINT fClipboardFormat;
	String fDefaultFilter;
	Synunicode::TSynEncoding FEncoding;
	bool fExportAsText;
	TFont* fFont;
	Synedithighlighter::TSynCustomHighlighter* fHighlighter;
	TColor fLastBG;
	TColor fLastFG;
	TFontStyles fLastStyle;
	String fTitle;
	bool fUseBackground;
    /* Adds a string to the output buffer. */
	void __fastcall AddData(const String AText);
    /* Adds a string and a trailing newline to the output buffer. */
	void __fastcall AddDataNewLine(const String AText);
    /* Adds a newline to the output buffer. */
	void __fastcall AddNewLine();
    /* Copies the data under this format to the clipboard. The clipboard has to
      be opened explicitly when more than one format is to be set. */
	void __fastcall CopyToClipboardFormat(UINT AFormat);
	virtual void __fastcall DefineProperties(TFiler* Filer);
    /* Has to be overridden in descendant classes to add the closing format
      strings to the output buffer.  The parameters can be used to track what
      changes are made for the next token. */
	virtual void __fastcall FormatAttributeDone(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged){} // = 0;
    /* Has to be overridden in descendant classes to add the opening format
      strings to the output buffer.  The parameters can be used to track what
      changes have been made in respect to the previous token. */
	virtual void __fastcall FormatAttributeInit(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged){} // = 0;
    /* Has to be overridden in descendant classes to add the closing format
      strings to the output buffer after the last token has been written. */
	virtual void __fastcall FormatAfterLastAttribute(){} // = 0;
    /* Has to be overridden in descendant classes to add the opening format
      strings to the output buffer when the first token is about to be written. */
	virtual void __fastcall FormatBeforeFirstAttribute(bool BackgroundChanged, bool ForegroundChanged, TFontStyles FontStylesChanged){} // = 0;
    /* Has to be overridden in descendant classes to add the formatted text of
      the actual token text to the output buffer. */
	virtual void __fastcall FormatToken(String Token);
    /* Has to be overridden in descendant classes to add a newline in the output
      format to the output buffer. */
	virtual void __fastcall FormatNewLine(){} // = 0;
    /* Returns the size of the formatted text in the output buffer, to be used
      in the format header or footer. */
	int __fastcall GetBufferSize();
    /* The clipboard format the exporter creates as native format. */
	virtual UINT __fastcall GetClipboardFormat();
    /* Has to be overridden in descendant classes to return the correct output
      format footer. */
	virtual String __fastcall GetFooter(){return String();} // = 0;
    /* Has to be overridden in descendant classes to return the name of the
      output format. */
	virtual String __fastcall GetFormatName();
    /* Has to be overridden in descendant classes to return the correct output
      format header. */
	virtual String __fastcall GetHeader(){return String();} // = 0;
    /* Inserts a data block at the given position into the output buffer.  Is
      used to insert the format header after the exporting, since some header
      data may be known only after the conversion is done. */
	void __fastcall InsertData(int APos, const String AText);
	virtual String __fastcall ReplaceReservedChar(WideChar AChar){return String();} // = 0;
    /* Returns a string that has all the invalid chars of the output format
      replaced with the entries in the replacement array. */
	String __fastcall ReplaceReservedChars(String AToken);
    /* Sets the token attribute of the next token to determine the changes
      of colors and font styles so the properties of the next token can be
      added to the output buffer. */
	virtual void __fastcall SetTokenAttribute(Synedithighlighter::TSynHighlighterAttributes* Attri);
	virtual bool __fastcall UseBom(){return false;} // = 0;
public:
    /* Creates an instance of the exporter. */
	typedef System::Classes::TComponent inherited;
	#include "SynEditExport_friends.inc"
	__fastcall TSynCustomExporter(TComponent* AOwner);
    /* Destroys an instance of the exporter. */
	virtual __fastcall ~TSynCustomExporter();
    /* Clears the output buffer and any internal data that relates to the last
      exported text. */
	virtual void __fastcall Clear();
    /* Copies the output buffer contents to the clipboard, as the native format
      or as text depending on the ExportAsText property. */
	void __fastcall CopyToClipboard();
    /* Exports everything in the strings parameter to the output buffer. */
	void __fastcall ExportAll(TStrings* ALines);
    /* Exports the given range of the strings parameter to the output buffer. */
	void __fastcall ExportRange(TStrings* ALines, const TBufferCoord& Start, const TBufferCoord& Stop);
    /* Saves the contents of the output buffer to a file. */
	void __fastcall SaveToFile(const String FileName);
    /* Saves the contents of the output buffer to a stream. */
	void __fastcall SaveToStream(TStream* Stream);
	virtual Synunicode::TSynEncodings __fastcall SupportedEncodings(){return Synunicode::TSynEncodings();} // = 0;
    /* Default background color for text that has no token attribute assigned or
      for token attributes that have the background set to default. */
	__property TColor Color = { read = fBackgroundColor, write = fBackgroundColor };
    /* Filter string for the output format for SaveAs file dialogs. */
	__property String DefaultFilter = { read = fDefaultFilter, write = fDefaultFilter };
	__property Synunicode::TSynEncoding Encoding = { read = FEncoding, write = SetEncoding, default = /*# seUTF8 */ 0 };
	__property bool ExportAsText = { read = fExportAsText, write = SetExportAsText };
    /* The font to be used for the output format. The font color is used for text
      that has no token attribute assigned or for token attributes that have
      the background set to default. */
	__property TFont* Font = { read = fFont, write = SetFont };
    /* The output format of the exporter. */
	__property String FormatName = { read = GetFormatName };
    /* The highlighter to use for exporting. */
	__property Synedithighlighter::TSynCustomHighlighter* Highlighter = { read = fHighlighter, write = SetHighlighter };
    /* The title to embedd into the output header. */
	__property String Title = { read = fTitle, write = SetTitle };
    /* Use the token attribute background for the exporting. */
	__property bool UseBackground = { read = fUseBackground, write = SetUseBackground };
};
const String EncodingStrs[4/*# TSynEncoding*/] = {L"UTF-8", L"UTF-16 Little Endian", L"UTF-16 Big Endian", L"ANSI"};
const System::Char SEncodingError[] = L"%s encoding is not supported by %s-exporter";


}  // namespace SynEditExport

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditexport;
#endif

#endif // SynEditExportH

