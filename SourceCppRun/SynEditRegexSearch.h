#ifndef SynEditRegexSearchH
#define SynEditRegexSearchH

#include <System.hpp>
#include "d2c_system.h"

#include "SynEditTypes.h"
#include <System.RegularExpressions.hpp>
#include <System.RegularExpressionsCore.hpp>
#include "SynEditMiscClasses.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>

namespace Syneditregexsearch
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditRegexSearch.pas, released 2002-07-26.

Original Code by Eduardo Mauro, Gerald Nunn and Flávio Etrusco.
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

$Id: SynEditRegexSearch.pas,v 1.5.2.2 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

class TSynEditRegexSearch : public Syneditmiscclasses::TSynEditSearchCustom
{
private:
	System::Regularexpressions::TRegEx RegEx;
	System::Regularexpressions::TMatchCollection fMatchCollection;
	System::Regularexpressions::TRegExOptions fOptions;
	String FPattern;
protected:
	virtual String __fastcall GetPattern();
	virtual void __fastcall SetPattern(const String Value);
	virtual void __fastcall SetOptions(const Synedittypes::TSynSearchOptions Value);
	virtual int __fastcall GetLength(int Index);
	virtual int __fastcall GetResult(int Index);
	virtual int __fastcall GetResultCount();
public:
	typedef Syneditmiscclasses::TSynEditSearchCustom inherited;	
	#include "SynEditRegexSearch_friends.inc"
	__fastcall TSynEditRegexSearch(System::Classes::TComponent* AOwner);
	virtual int __fastcall FindAll(const String NewText);
	virtual String __fastcall PreprocessReplaceExpression(const String AReplace);
	virtual String __fastcall Replace(const String aOccurrence, const String aReplacement);
};
typedef System::Regularexpressionscore::ERegularExpressionError ESynRegEx;


}  // namespace SynEditRegexSearch

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditregexsearch;
#endif

#endif // SynEditRegexSearchH

