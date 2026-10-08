#include <vcl.h>
#pragma hdrstop

#include "SynEditReg.h"

using namespace std;
using namespace d2c_system;
using namespace Synautocorrect;
using namespace Syncompletionproposal;
using namespace Syndbedit;
using namespace Synedit;
using namespace Syneditexport;
using namespace Synedithighlighter;
using namespace Syneditmiscclasses;
using namespace Syneditplugins;
using namespace Syneditprint;
using namespace Syneditprintpreview;
using namespace Syneditpythonbehaviour;
using namespace Syneditregexsearch;
using namespace Syneditsearch;
using namespace Syneditstrconst;
using namespace Synexporthtml;
using namespace Synexportrtf;
using namespace Synexporttex;
using namespace Synhighlighteradsp21xx;
using namespace Synhighlighterasm;
using namespace Synhighlighterawk;
using namespace Synhighlighterbaan;
using namespace Synhighlighterbat;
using namespace Synhighlightercac;
using namespace Synhighlightercache;
using namespace Synhighlightercobol;
using namespace Synhighlightercpm;
using namespace Synhighlightercpp;
using namespace Synhighlightercs;
using namespace Synhighlightercss;
using namespace Synhighlighterdfm;
using namespace Synhighlighterdml;
using namespace Synhighlighterdot;
using namespace Synhighlighterdws;
using namespace Synhighlightereiffel;
using namespace Synhighlighterfortran;
using namespace Synhighlighterfoxpro;
using namespace Synhighlightergalaxy;
using namespace Synhighlightergeneral;
using namespace Synhighlightergws;
using namespace Synhighlighterhaskell;
using namespace Synhighlighterhc11;
using namespace Synhighlighterhp48;
using namespace Synhighlighterhtml;
using namespace Synhighlighteridl;
using namespace Synhighlighterini;
using namespace Synhighlighterinno;
using namespace Synhighlighterjava;
using namespace Synhighlighterjscript;
using namespace Synhighlighterjson;
using namespace Synhighlighterkix;
using namespace Synhighlighterldraw;
using namespace Synhighlighterm3;
//using namespace Synhighlightermanager;
using namespace Synhighlightermodelica;
using namespace Synhighlightermsg;
using namespace Synhighlightermulti;
using namespace Synhighlighterpas;
using namespace Synhighlighterperl;
using namespace Synhighlighterphp;
using namespace Synhighlighterprogress;
using namespace Synhighlighterpython;
using namespace Synhighlighterrc;
using namespace Synhighlighterruby;
using namespace Synhighlightersdd;
using namespace Synhighlightersml;
using namespace Synhighlightersql;
using namespace Synhighlighterst;
using namespace Synhighlightertcltk;
using namespace Synhighlightertex;
using namespace Synhighlighterunixshellscript;
using namespace Synhighlighterunreal;
using namespace Synhighlighteruri;
using namespace Synhighlightervb;
using namespace Synhighlightervbscript;
using namespace Synhighlightervrml97;
using namespace Synhighlighterxml;
using namespace Synmacrorecorder;
using namespace Synspellcheck;
using namespace Synuriopener;

namespace Syneditreg
{



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

void __fastcall Register()
{

// SynEdit main components
	TComponentClass classesSyneditreg__0[1] = {__classid(TSynEdit)};
	RegisterComponents(SYNS_ComponentsPage, classesSyneditreg__0, 1);
	TComponentClass classesSyneditreg__1[1] = {__classid(TDBSynEdit)};
	RegisterComponents(SYNS_ComponentsPage, classesSyneditreg__1, 1);
	GroupDescendentsWith(__classid(TSynCustomHighlighter), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TSynEditSearchCustom), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TSynCustomExporter), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TSynMultiSyn), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TSynBaseCompletionProposal), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TSynAutoComplete), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TAbstractSynPlugin), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TCustomSynAutoCorrect), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TSynEditPrint), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TSynEditPrintPreview), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TSynEditPythonBehaviour), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TSynHighlighterManager), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TSynEditOptionsDialog), __classid(TSynEdit));
	GroupDescendentsWith(__classid(TSynURIOpener), __classid(TSynEdit));

// SynEdit extra components
	TComponentClass classesSyneditreg__2[15] = {__classid(TSynExporterHTML)
                                 , __classid(TSynExporterRTF)
                                 , __classid(TSynExporterTeX)
                                 , __classid(TSynEditPythonBehaviour)
                                 , __classid(TSynMultiSyn)
                                 , __classid(TSynCompletionProposal)
                                 , __classid(TSynAutoComplete)
                                 , __classid(TSynMacroRecorder)
                                 , __classid(TSynEditPrint)
                                 , __classid(TSynEditPrintPreview)
                                 , __classid(TSynAutoCorrect)
                                 , __classid(TSynEditSearch)
                                 , __classid(TSynEditRegexSearch)
                                 , __classid(TSynEditOptionsDialog)
                                 , __classid(TSynURIOpener)};
	RegisterComponents(SYNS_ComponentsPage, classesSyneditreg__2, 15);
	TComponentClass classesSyneditreg__3[1] = {__classid(TSynHighlighterManager)};
	RegisterComponents(SYNS_ComponentsPage, classesSyneditreg__3, 1);
	TComponentClass classesSyneditreg__4[1] = {__classid(TSynSpellCheck)};
	RegisterComponents(SYNS_ComponentsPage, classesSyneditreg__4, 1);

// SynEdit highlighters

    //classic

    // internet

    //interpreted

    //database

    //assembler

    //data modeling

    //data

    // other
	TComponentClass classesSyneditreg__5[57] = {__classid(TSynCppSyn)
                                 , __classid(TSynEiffelSyn)
                                 , __classid(TSynFortranSyn)
                                 , __classid(TSynGeneralSyn)
                                 , __classid(TSynJavaSyn)
                                 , __classid(TSynM3Syn)
                                 , __classid(TSynPasSyn)
                                 , __classid(TSynVBSyn)
                                 , __classid(TSynCobolSyn)
                                 , __classid(TSynCSSyn)
                                 , __classid(TSynCssSyn)
                                 , __classid(TSynHTMLSyn)
                                 , __classid(TSynJScriptSyn)
                                 , __classid(TSynPHPSyn)
                                 , __classid(TSynVBScriptSyn)
                                 , __classid(TSynXMLSyn)
                                 , __classid(TSynJSONSyn)
                                 , __classid(TSynVrml97Syn)
                                 , __classid(TSynAWKSyn)
                                 , __classid(TSynBatSyn)
                                 , __classid(TSynDWSSyn)
                                 , __classid(TSynKixSyn)
                                 , __classid(TSynPerlSyn)
                                 , __classid(TSynPythonSyn)
                                 , __classid(TSynTclTkSyn)
                                 , __classid(TSynGWScriptSyn)
                                 , __classid(TSynRubySyn)
                                 , __classid(TSynUNIXShellScriptSyn)
                                 , __classid(TSynCACSyn)
                                 , __classid(TSynCacheSyn)
                                 , __classid(TSynFoxproSyn)
                                 , __classid(TSynSQLSyn)
                                 , __classid(TSynSDDSyn)
                                 , __classid(TSynADSP21xxSyn)
                                 , __classid(TSynAsmSyn)
                                 , __classid(TSynHC11Syn)
                                 , __classid(TSynHP48Syn)
                                 , __classid(TSynSTSyn)
                                 , __classid(TSynDmlSyn)
                                 , __classid(TSynModelicaSyn)
                                 , __classid(TSynSMLSyn)
                                 , __classid(TSynDfmSyn)
                                 , __classid(TSynIniSyn)
                                 , __classid(TSynInnoSyn)
                                 , __classid(TSynBaanSyn)
                                 , __classid(TSynGalaxySyn)
                                 , __classid(TSynProgressSyn)
                                 , __classid(TSynMsgSyn)
                                 , __classid(TSynIdlSyn)
                                 , __classid(TSynUnrealSyn)
                                 , __classid(TSynCPMSyn)
                                 , __classid(TSynTeXSyn)
                                 , __classid(TSynHaskellSyn)
                                 , __classid(TSynLDRSyn)
                                 , __classid(TSynURISyn)
                                 , __classid(TSynDOTSyn)
                                 , __classid(TSynRCSyn)};
	RegisterComponents(SYNS_HighlightersPage, classesSyneditreg__5, 57);
}


}  // namespace Syneditreg

