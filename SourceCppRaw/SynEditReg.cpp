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
using namespace Synhighlighterawk;
using namespace Synhighlighterasm;
using namespace Synhighlighterbaan;
using namespace Synhighlighterbat;
using namespace Synhighlightercac;
using namespace Synhighlightercpm;
using namespace Synhighlightercs;
using namespace Synhighlightercache;
using namespace Synhighlightercobol;
using namespace Synhighlightercpp;
using namespace Synhighlightercss;
using namespace Synhighlighterdot;
using namespace Synhighlighterdws;
using namespace Synhighlighterdfm;
using namespace Synhighlighterdml;
using namespace Synhighlightereiffel;
using namespace Synhighlighterfortran;
using namespace Synhighlighterfoxpro;
using namespace Synhighlightergws;
using namespace Synhighlightergalaxy;
using namespace Synhighlightergeneral;
using namespace Synhighlighterhc11;
using namespace Synhighlighterhp48;
using namespace Synhighlighterhaskell;
using namespace Synhighlighterhtml;
using namespace Synhighlighteridl;
using namespace Synhighlighterini;
using namespace Synhighlighterinno;
using namespace Synhighlighterjson;
using namespace Synhighlighterjscript;
using namespace Synhighlighterjava;
using namespace Synhighlighterkix;
using namespace Synhighlighterldraw;
using namespace Synhighlighterm3;
using namespace Synhighlightermanager;
using namespace Synhighlightermodelica;
using namespace Synhighlightermsg;
using namespace Synhighlightermulti;
using namespace Synhighlighterphp;
using namespace Synhighlighterpas;
using namespace Synhighlighterperl;
using namespace Synhighlighterprogress;
using namespace Synhighlighterpython;
using namespace Synhighlighterrc;
using namespace Synhighlighterruby;
using namespace Synhighlightersdd;
using namespace Synhighlightersql;
using namespace Synhighlighterst;
using namespace Synhighlightersml;
using namespace Synhighlightertcltk;
using namespace Synhighlightertex;
using namespace Synhighlighterunixshellscript;
using namespace Synhighlighteruri;
using namespace Synhighlighterunreal;
using namespace Synhighlightervb;
using namespace Synhighlightervbscript;
using namespace Synhighlightervrml97;
using namespace Synhighlighterxml;
using namespace Synmacrorecorder;
using namespace Synspellcheck;
using namespace Synuriopener;
using namespace System;
using namespace System::Classes;

namespace Syneditreg
{



void __fastcall Register()
{

// SynEdit main components
	TComponentClass classesSynEditReg__0[1] = {__classid(TSynEdit)};
	RegisterComponents(SYNS_ComponentsPage, classesSynEditReg__0, 1);
	TComponentClass classesSynEditReg__1[1] = {__classid(TDBSynEdit)};
	RegisterComponents(SYNS_ComponentsPage, classesSynEditReg__1, 1);
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
	TComponentClass classesSynEditReg__2[15] = {__classid(TSynExporterHTML)
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
	RegisterComponents(SYNS_ComponentsPage, classesSynEditReg__2, 15);
	TComponentClass classesSynEditReg__3[1] = {__classid(TSynHighlighterManager)};
	RegisterComponents(SYNS_ComponentsPage, classesSynEditReg__3, 1);
	TComponentClass classesSynEditReg__4[1] = {__classid(TSynSpellCheck)};
	RegisterComponents(SYNS_ComponentsPage, classesSynEditReg__4, 1);

// SynEdit highlighters

    //classic

    // internet

    //interpreted

    //database

    //assembler

    //data modeling

    //data

    // other
	TComponentClass classesSynEditReg__5[57] = {__classid(TSynCppSyn)
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
	RegisterComponents(SYNS_HighlightersPage, classesSynEditReg__5, 57);
}


}  // namespace SynEditReg

