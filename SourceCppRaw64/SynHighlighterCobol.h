/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

Code template generated with SynGen.
The original code is: SynHighlighterCobol.pas, released 2002-08-26.
Description: COBOL Syntax Parser/Highlighter
The author of this file is Andrey Ustinov.
Copyright (c) 2002 Software Mining, http://www.softwaremining.com/.
Unicode translation by Ma�l H�rz.
All rights reserved.

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

$Id: SynHighlighterCobol.pas,v 1.5.2.7 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------*/
#ifndef SynHighlighterCobolH
#define SynHighlighterCobolH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynHighlighterHashEntries.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlightercobol
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

Code template generated with SynGen.
The original code is: SynHighlighterCobol.pas, released 2002-08-26.
Description: COBOL Syntax Parser/Highlighter
The author of this file is Andrey Ustinov.
Copyright (c) 2002 Software Mining, http://www.softwaremining.com/.
Unicode translation by Ma�l H�rz.
All rights reserved.

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

$Id: SynHighlighterCobol.pas,v 1.5.2.7 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

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
enum TtkTokenKind {tkComment,
                   tkIdentifier,
                   tkAIdentifier,
                   tkPreprocessor,
                   tkKey,
                   tkBoolean,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkString,
                   tkSequence,
                   tkIndicator,
                   tkTagArea,
                   tkDebugLines,
                   tkUnknown };
enum TRangeState {rsUnknown,
                  rsQuoteString,
                  rsApostString,
                  rsPseudoText,
                  rsQuoteStringMayBe,
                  rsApostStringMayBe };

class TSynCobolSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState fRange;
	TtkTokenKind fTokenID;
	WideChar fIndicator;
	int fCodeStartPos;
	int fCodeMediumPos;
	int fCodeEndPos;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fAIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fPreprocessorAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fBooleanAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSequenceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIndicatorAttri;
	Synedithighlighter::TSynHighlighterAttributes* fTagAreaAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDebugLinesAttri;
	Synhighlighterhashentries::TSynHashEntryList* fKeywords;
	void __fastcall DoAddKeyword(String AKeyword, int AKind);
	int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar MayBe);
	void __fastcall IdentProc();
	void __fastcall UnknownProc();
	void __fastcall NullProc();
	void __fastcall SpaceProc();
	void __fastcall CRProc();
	void __fastcall LFProc();
	void __fastcall NumberProc();
	void __fastcall PointProc();
	void __fastcall StringOpenProc();
	void __fastcall StringProc();
	void __fastcall StringEndProc();
	void __fastcall FirstCharsProc();
	void __fastcall LastCharsProc();
	void __fastcall CommentProc();
	void __fastcall DebugProc();
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
	void __fastcall NextProcedure();
	void __fastcall SetCodeStartPos(int Value);
	void __fastcall SetCodeMediumPos(int Value);
	void __fastcall SetCodeEndPos(int Value);
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	__fastcall TSynCobolSyn(TComponent* AOwner);
	virtual __fastcall ~TSynCobolSyn();
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	virtual void* __fastcall GetRange();
	virtual void __fastcall ResetRange();
	virtual void __fastcall SetRange(void* Value);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual void __fastcall Next();
__published:
public:
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* AreaAIdentifierAttri = { read = fAIdentifierAttri, write = fAIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* PreprocessorAttri = { read = fPreprocessorAttri, write = fPreprocessorAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* BooleanAttri = { read = fBooleanAttri, write = fBooleanAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SequenceAttri = { read = fSequenceAttri, write = fSequenceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IndicatorAttri = { read = fIndicatorAttri, write = fIndicatorAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* TagAreaAttri = { read = fTagAreaAttri, write = fTagAreaAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* DebugLinesAttri = { read = fDebugLinesAttri, write = fDebugLinesAttri };
	__property int AreaAStartPos = { read = fCodeStartPos, write = SetCodeStartPos };
	__property int AreaBStartPos = { read = fCodeMediumPos, write = SetCodeMediumPos };
	__property int CodeEndPos = { read = fCodeEndPos, write = SetCodeEndPos };
};

void SynHighlighterCobol_initialization();


}  // namespace SynHighlighterCobol

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightercobol;
#endif


#endif // SynHighlighterCobolH

