/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditSearch.pas, released 2000-04-07.

The Original Code is based on the mwEditSearch.pas file from the mwEdit
component suite by Martin Waldenburg and other developers.
Portions created by Martin Waldenburg are Copyright 1999 Martin Waldenburg.
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

$Id: SynEditSearch.pas,v 1.12.2.6 2009/09/29 00:16:46 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef SynEditSearchH
#define SynEditSearchH

#include <System.hpp>
#include "d2c_system.h"

#include "SynEditTypes.h"
#include "SynEditMiscClasses.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>

namespace Syneditsearch
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditSearch.pas, released 2000-04-07.

The Original Code is based on the mwEditSearch.pas file from the mwEdit
component suite by Martin Waldenburg and other developers.
Portions created by Martin Waldenburg are Copyright 1999 Martin Waldenburg.
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

$Id: SynEditSearch.pas,v 1.12.2.6 2009/09/29 00:16:46 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
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

class TSynEditSearch : public Syneditmiscclasses::TSynEditSearchCustom
{
private:
	PWideChar Run;
	PWideChar Origin;
	PWideChar TheEnd;
	String Pat;
	String CasedPat;
	int FCount;
	int fTextLen;
	int Look_At;
	int PatLen;
	int PatLenSucc;
	int Shift[65536/*# WideChar*/];
	bool FCaseSensitive;
	bool fWhole;
	TList* fResults;
	bool fShiftInitialized;
	String FTextToSearch;
	bool __fastcall GetFinished();
	void __fastcall InitShiftTable();
	void __fastcall SetCaseSensitive(bool Value);
protected:
	bool __fastcall TestWholeWord();
	virtual void __fastcall SetPattern(const String Value);
	virtual String __fastcall GetPattern();
	virtual int __fastcall GetLength(int Index);
	virtual int __fastcall GetResult(int Index);
	virtual int __fastcall GetResultCount();
	virtual void __fastcall SetOptions(const Synedittypes::TSynSearchOptions Value);
public:
	typedef Syneditmiscclasses::TSynEditSearchCustom inherited;
	#include "SynEditSearch_friends.inc"
	__fastcall TSynEditSearch(TComponent* AOwner);
	virtual __fastcall ~TSynEditSearch();
	virtual int __fastcall FindAll(const String NewText);
	virtual String __fastcall Replace(const String aOccurrence, const String aReplacement);
	int __fastcall FindFirst(const String NewText);
	void __fastcall FixResults(int First, int delta);
	int __fastcall Next();
	__property int Count = { read = FCount, write = FCount };
	__property bool Finished = { read = GetFinished };
	__property  Pattern = { read = CasedPat };
	__property bool CaseSensitive = { read = FCaseSensitive, write = SetCaseSensitive };
	__property bool Whole = { read = fWhole, write = fWhole };
};


}  // namespace SynEditSearch

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditsearch;
#endif

#endif // SynEditSearchH

