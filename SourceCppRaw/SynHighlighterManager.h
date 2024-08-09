/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterManager.pas, released 2000-04-14.

The Original Code is based on mwHighlighterManager.pas by Primoz Gabrijelcic,
part of the mwEdit component suite.
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

$Id: SynHighlighterManager.pas,v 1.7.2.2 2008/03/01 18:32:02 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
  - does not work when dropped on a frame in Delphi 5
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a component to manage many highlighters in a single project.)
@author(Primoz Gabrijelcic)
@created(1999, converted to SynEdit 2000-04-14)
@lastmod(2000-04-14)
Provides a component to manage many highlighters in a single project.
*/
#ifndef SynHighlighterManagerH
#define SynHighlighterManagerH

#include <System.hpp>
#include "d2c_system.h"

#include <System.Classes.hpp>


/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterManager.pas, released 2000-04-14.

The Original Code is based on mwHighlighterManager.pas by Primoz Gabrijelcic,
part of the mwEdit component suite.
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

$Id: SynHighlighterManager.pas,v 1.7.2.2 2008/03/01 18:32:02 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
  - does not work when dropped on a frame in Delphi 5
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a component to manage many highlighters in a single project.)
@author(Primoz Gabrijelcic)
@created(1999, converted to SynEdit 2000-04-14)
@lastmod(2000-04-14)
Provides a component to manage many highlighters in a single project.
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

  /*:Highlighter manager.<p>
    Design-only component, designed to simplify work with highlighter components.<p>
    When placed on the form, SynHighlighterManager scans the form for highlighter
    components (descendants of TSynCustomHighlighter). Next it presents the user with
    small form containing checkboxed list and some buttons. User can select (by
    checking/unchecking list items) highlighter that should be placed onto the
    form. After user clicks OK, SynHighlighterManager synchronises highlighter
    components on the form with required state.<p>
    Built-in tricks:<br>
    - SynHighlighterManager never covers existing TComponent with a highlighter.<br>
    - SynHighlighterManager scans the form for TSynCustomHighlighter descendants and
      uses topmost and leftmost component as a starting point for insertion. If
      no TSynCustomHighlighter components are found, first highlighter will be placed
      at coordinates (8,8).<p>
    Known issues:<br>
    - If you place TSynHighlighterManager by double-clicking its icon in
      component palette, it will function normally, except that when all is
      done, Delphi will disply small window with title "Error" and message
      "Operation aborted". Purely cosmetic issue for which there is no obvious
      workaround. Live with it.<p>
    Last change: 2000-01-21

    @author Primoz Gabrijelcic
    @version 0.1
    @component
    @see TSynEditHighlighter
  :*/

class TSynHighlighterManager : public System::Classes::TComponent
{
public:
	typedef System::Classes::TComponent inherited;
	#include "SynHighlighterManager_friends.inc"
	__fastcall TSynHighlighterManager(TComponent* AOwner);
__published:
};
#endif // SynHighlighterManagerH

