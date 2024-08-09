/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterSQL.pas, released 2000-04-21.
The Original Code is based on the wmSQLSyn.pas and wmSybaseSyn.pas files from
the mwEdit component suite by Martin Waldenburg and other developers, the
Initial Author of these files is Willo van der Merwe. Initial Author of
SynHighlighterSQL.pas is Michael Hieke.
Portions created by Willo van der Merwe are Copyright 1999 Willo van der Merwe.
Portions created by Michael Hieke are Copyright 2000 Michael Hieke.
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

$Id: SynHighlighterSQL.pas,v 1.39.2.14 2008/09/14 16:25:03 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(SQL highlighter for SynEdit with support for different dialects.)
@author(Michael Hieke)
@created(2000-04-21)
@lastmod(2000-11-16)
The SynHighlighterSQL implements a highlighter for SQL for the SynEdit projects.
Different SQL dialects can be selected via the Dialect property.
*/
#ifndef SynHighlighterSQLH
#define SynHighlighterSQLH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include <System.Win.Registry.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynHighlighterHashEntries.h"
#include "SynUnicode.h"
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlightersql
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterSQL.pas, released 2000-04-21.
The Original Code is based on the wmSQLSyn.pas and wmSybaseSyn.pas files from
the mwEdit component suite by Martin Waldenburg and other developers, the
Initial Author of these files is Willo van der Merwe. Initial Author of
SynHighlighterSQL.pas is Michael Hieke.
Portions created by Willo van der Merwe are Copyright 1999 Willo van der Merwe.
Portions created by Michael Hieke are Copyright 2000 Michael Hieke.
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

$Id: SynHighlighterSQL.pas,v 1.39.2.14 2008/09/14 16:25:03 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(SQL highlighter for SynEdit with support for different dialects.)
@author(Michael Hieke)
@created(2000-04-21)
@lastmod(2000-11-16)
The SynHighlighterSQL implements a highlighter for SQL for the SynEdit projects.
Different SQL dialects can be selected via the Dialect property.
*/

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
                   tkDataType,
                   tkDefaultPackage,
                   tkException,
                   tkFunction,
                   tkIdentifier,
                   tkKey,
                   tkNull,
                   tkNumber,
                   tkSpace,
                   tkPLSQL,
                   tkSQLPlus,
                   tkString,
                   tkSymbol,
                   tkTableName,
                   tkUnknown,
                   tkVariable,
                   tkConditionalComment,
                   tkDelimitedIdentifier,
                   tkProcName,
                   tkConsoleOutput };
enum TRangeState {rsUnKnown,
                  rsComment,
                  rsString,
                  rsConditionalComment,
                  rsConsoleOutput };
enum TSQLDialect {sqlStandard,
                  sqlInterbase6,
                  sqlMSSQL7,
                  sqlMySQL,
                  sqlOracle,
                  sqlSybase,
                  sqlIngres,
                  sqlMSSQL2K,
                  sqlPostgres,
                  sqlNexus,
                  sqlInformix };

class TSynSQLSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState FRange;
	TtkTokenKind FTokenID;
	Synhighlighterhashentries::TSynHashEntryList* fKeywords;
	TStrings* FProcNames;
	TStrings* fTableNames;
	TDictionary__2<String, bool>* FTableDict;
	TStrings* fFunctionNames;
	TSQLDialect fDialect;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fConditionalCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fConsoleOutputAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDataTypeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDefaultPackageAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDelimitedIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fExceptionAttri;
	Synedithighlighter::TSynHighlighterAttributes* fFunctionAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fPLSQLAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSQLPlusAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synedithighlighter::TSynHighlighterAttributes* fTableNameAttri;
	Synedithighlighter::TSynHighlighterAttributes* fProcNameAttri;
	Synedithighlighter::TSynHighlighterAttributes* fVariableAttri;
	int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall DoAddKeyword(String AKeyword, int AKind);
	void __fastcall SetDialect(TSQLDialect Value);
	void __fastcall SetTableNames(TStrings* const Value);
	void __fastcall SetFunctionNames(TStrings* const Value);
	void __fastcall PutFunctionNamesInKeywordList();
	void __fastcall FunctionNamesChanged(TObject* Sender);
	void __fastcall ProcNamesChanged(TObject* Sender);
	void __fastcall TableNamesChanged(TObject* Sender);
	void __fastcall InitializeKeywordLists();
	void __fastcall PutProcNamesInKeywordList();
	void __fastcall PutTableNamesInKeywordList();
	void __fastcall AndSymbolProc();
	void __fastcall AsciiCharProc();
	void __fastcall CRProc();
	void __fastcall EqualProc();
	void __fastcall GreaterProc();
	void __fastcall IdentProc();
	void __fastcall LFProc();
	void __fastcall LowerProc();
	void __fastcall MinusProc();
	void __fastcall HashProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall OrSymbolProc();
	void __fastcall PlusProc();
	void __fastcall SlashProc();
	void __fastcall SpaceProc();
	void __fastcall QuoteProc();
	void __fastcall BacktickProc();
	void __fastcall BracketProc();
	void __fastcall SymbolProc();
	void __fastcall SymbolAssignProc();
	void __fastcall VariableProc();
	void __fastcall UnknownProc();
	void __fastcall AnsiCProc();
	void __fastcall SetProcNames(TStrings* const Value);
protected:
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynSQLSyn(TComponent* AOwner);
	virtual __fastcall ~TSynSQLSyn();
	virtual void __fastcall Assign(TPersistent* Source);
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual bool __fastcall GetEol();
	virtual String __fastcall GetKeyWords(int TokenKind);
	virtual void* __fastcall GetRange();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	TtkTokenKind __fastcall GetTokenID();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual bool __fastcall IsKeyword(const String AKeyword);
	virtual void __fastcall Next();
	virtual void __fastcall ResetRange();
	virtual void __fastcall SetRange(void* Value);
__published:
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* ConditionalCommentAttri = { read = fConditionalCommentAttri, write = fConditionalCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* ConsoleOutputAttri = { read = fConsoleOutputAttri, write = fConsoleOutputAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* DataTypeAttri = { read = fDataTypeAttri, write = fDataTypeAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* DefaultPackageAttri = { read = fDefaultPackageAttri, write = fDefaultPackageAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* DelimitedIdentifierAttri = { read = fDelimitedIdentifierAttri, write = fDelimitedIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* ExceptionAttri = { read = fExceptionAttri, write = fExceptionAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* FunctionAttri = { read = fFunctionAttri, write = fFunctionAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* PLSQLAttri = { read = fPLSQLAttri, write = fPLSQLAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SQLPlusAttri = { read = fSQLPlusAttri, write = fSQLPlusAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* ProcNameAttri = { read = fProcNameAttri, write = fProcNameAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* TableNameAttri = { read = fTableNameAttri, write = fTableNameAttri };
	__property TStrings* ProcNames = { read = FProcNames, write = SetProcNames };
	__property TStrings* TableNames = { read = fTableNames, write = SetTableNames };
	__property TStrings* FunctionNames = { read = fFunctionNames, write = SetFunctionNames };
	__property Synedithighlighter::TSynHighlighterAttributes* VariableAttri = { read = fVariableAttri, write = fVariableAttri };
	__property TSQLDialect SQLDialect = { read = fDialect, write = SetDialect, default = /*# sqlStandard */ 0 };
};

void SynHighlighterSQL_initialization();


}  // namespace SynHighlighterSQL

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlightersql;
#endif


#endif // SynHighlighterSQLH

