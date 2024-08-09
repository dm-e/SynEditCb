/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditReg.pas, released 2000-04-07.
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

$Id: SynEditReg.pas,v 1.33.2.2 2004/10/18 15:25:00 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef SynEditRegH
#define SynEditRegH

#include <System.hpp>
#include "d2c_system.h"

#include "SynEdit.h"
#include "SynDBEdit.h"
#include "SynEditStrConst.h"
#include "SynEditHighlighter.h"
#include "SynEditMiscClasses.h"
#include "SynEditPlugins.h"
#include "SynEditExport.h"
#include "SynExportHTML.h"
#include "SynExportRTF.h"
#include "SynExportTeX.h"
#include "SynHighlighterMulti.h"
#include "SynCompletionProposal.h"
#include "SynEditPythonBehaviour.h"
#include "SynEditPrint.h"
#include "SynEditPrintPreview.h"
#include "SynMacroRecorder.h"
#include "SynAutoCorrect.h"
#include "SynEditSearch.h"
#include "SynEditRegexSearch.h"
#include "SynHighlighterManager.h"
#include "SynEditOptionsDialog.h"
#include "SynHighlighterADSP21xx.h"
#include "SynHighlighterAsm.h"
#include "SynHighlighterAWK.h"
#include "SynHighlighterBaan.h"
#include "SynHighlighterBat.h"
#include "SynHighlighterCAC.h"
#include "SynHighlighterCache.h"
#include "SynHighlighterCobol.h"
#include "SynHighlighterCpp.h"
#include "SynHighlighterCS.h"
#include "SynHighlighterCss.h"
#include "SynHighlighterDfm.h"
#include "SynHighlighterDml.h"
#include "SynHighlighterDOT.h"
#include "SynHighlighterDWS.h"
#include "SynHighlighterEiffel.h"
#include "SynHighlighterFortran.h"
#include "SynHighlighterFoxpro.h"
#include "SynHighlighterGalaxy.h"
#include "SynHighlighterGeneral.h"
#include "SynHighlighterHaskell.h"
#include "SynHighlighterHC11.h"
#include "SynHighlighterHP48.h"
#include "SynHighlighterHtml.h"
#include "SynHighlighterIni.h"
#include "SynHighlighterInno.h"
#include "SynHighlighterJava.h"
#include "SynHighlighterJScript.h"
#include "SynHighlighterJSON.h"
#include "SynHighlighterKix.h"
#include "SynHighlighterModelica.h"
#include "SynHighlighterM3.h"
#include "SynHighlighterPas.h"
#include "SynHighlighterPerl.h"
#include "SynHighlighterPHP.h"
#include "SynHighlighterProgress.h"
#include "SynHighlighterPython.h"
#include "SynHighlighterRC.h"
#include "SynHighlighterRuby.h"
#include "SynHighlighterSml.h"
#include "SynHighlighterSQL.h"
#include "SynHighlighterTclTk.h"
#include "SynHighlighterTeX.h"
#include "SynHighlighterUNIXShellScript.h"
#include "SynHighlighterURI.h"
#include "SynHighlighterVB.h"
#include "SynHighlighterVBScript.h"
#include "SynHighlighterVrml97.h"
#include "SynHighlighterGWS.h"
#include "SynHighlighterCPM.h"
#include "SynHighlighterSDD.h"
#include "SynHighlighterXML.h"
#include "SynHighlighterMsg.h"
#include "SynHighlighterIDL.h"
#include "SynHighlighterUnreal.h"
#include "SynHighlighterST.h"
#include "SynHighlighterLDraw.h"
#include "SynSpellCheck.h"
#include "SynURIOpener.h"
#include <System.Classes.hpp>

namespace Syneditreg
{



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

  // SynEdit components
void __fastcall Register();


}  // namespace SynEditReg

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditreg;
#endif

#endif // SynEditRegH

