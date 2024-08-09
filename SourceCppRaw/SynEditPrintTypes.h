/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPrintTypes.pas, released 2000-06-01.

The Initial Author of the Original Code is Morten J. Skovrup.
Portions written by Morten J. Skovrup are copyright 2000 Morten J. Skovrup.
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

$Id: SynEditPrintTypes.pas,v 1.4.2.3 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
  Wrapping across page boundaries is not supported
-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
CONTENTS:
  Misc types and procedures used in printing and previewing
-------------------------------------------------------------------------------*/
#ifndef SynEditPrintTypesH
#define SynEditPrintTypesH

#include <System.hpp>
#include "d2c_system.h"

#include "SynUnicode.h"
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

namespace Syneditprinttypes
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPrintTypes.pas, released 2000-06-01.

The Initial Author of the Original Code is Morten J. Skovrup.
Portions written by Morten J. Skovrup are copyright 2000 Morten J. Skovrup.
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

$Id: SynEditPrintTypes.pas,v 1.4.2.3 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
  Wrapping across page boundaries is not supported
-------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------
CONTENTS:
  Misc types and procedures used in printing and previewing
-------------------------------------------------------------------------------*/
const int DefLeft = 25; //Default left margin [mm]
const int DefRight = 15; //Default right margin [mm]
const int DefTop = 25; //Default top margin [mm]
const int DefBottom = 25; //Default bottom margin [mm]
const int DefHeader = 15; //Default margin from top of paper to bottom of header [mm]
const int DefFooter = 15; //Default margin from top of footer to bottom of paper [mm]
const int DefLeftHFTextIndent = 2; //Default Header/footer indent from left margin [mm]
const int DefRightHFTextIndent = 2; //Default Header/footer indent from right margin [mm]
const double DefHFInternalMargin = 0.5; //Default Internal margin between Header/footer text and lines [mm]
const int DefGutter = 0; //Default Binding gutter - added to left or right margin [mm]

//Frame around header/footer
enum TFrameType {ftLine,
                 ftBox,
                 ftShaded };
typedef System::Set<TFrameType, TFrameType::ftLine, TFrameType::ftShaded> TFrameTypes;
//Margin units (internally is allways used [mm])
enum TUnitSystem {usMM,
                  usCM,
                  usInch,
                  muThousandthsOfInches };

//Print status events
enum TSynPrintStatus {psBegin,
                      psNewPage,
                      psEnd };

//Event raised when a line is printed (can be used to generate Table of Contents)
typedef void __fastcall (__closure *TPrintStatusEvent) (TObject*, TSynPrintStatus, int, bool&);
typedef void __fastcall (__closure *TPrintLineEvent) (TObject*, int, int);

class TWrapPos : public System::TObject
{
	#include "SynEditPrintTypes_friends.inc"
public:
	typedef System::TObject inherited;
	int Index;
	__fastcall TWrapPos();
};
String __fastcall IntToRoman(int Value);

// TODO: BreakChars is ANSI only but SynEditPrint only uses Ansi chars and should be rewritten to use WordWrap of SynEdit anyway
bool __fastcall WrapTextEx(const String Line, TSysCharSet BreakChars, int MaxCol, TList* AList);


}  // namespace SynEditPrintTypes

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditprinttypes;
#endif

#endif // SynEditPrintTypesH

