#include <vcl.h>
#pragma hdrstop

#include "Synedit_initexit.h"
#include "SynUnicode.h"
#include "SynEditHighlighter.h"
#include "SynEditKeyCmds.h"
#include "SynTextDrawer.h"
#include "SynEditDataObject.h"
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
#include "SynURIOpener.h"
#include "SynHighlighterLLVM.h"
#include "SynHighlighterRexx.h"
#include "SynHighlighterWebIDL.h"

using namespace std;
using namespace d2c_system;
using namespace System;

namespace Synedit_initexit
{



void __fastcall Synedit_init()
{
	Synunicode::SynUnicode_initialization();
	Synedithighlighter::SynEditHighlighter_initialization();
	Syneditkeycmds::SynEditKeyCmds_initialization();
	Syneditdataobject::SynEditDataObject_initialization();
	Synhighlighteradsp21xx::SynHighlighterADSP21xx_initialization();
	Synhighlighterasm::SynHighlighterAsm_initialization();
	Synhighlighterawk::SynHighlighterAWK_initialization();
	Synhighlighterbaan::SynHighlighterBaan_initialization();
	Synhighlighterbat::SynHighlighterBat_initialization();
	Synhighlightercac::SynHighlighterCAC_initialization();
	Synhighlightercache::SynHighlighterCache_initialization();
	Synhighlightercobol::SynHighlighterCobol_initialization();
	Synhighlightercpp::SynHighlighterCpp_initialization();
	Synhighlightercs::SynHighlighterCS_initialization();
	Synhighlightercss::SynHighlighterCss_initialization();
	Synhighlighterdfm::SynHighlighterDfm_initialization();
	Synhighlighterdml::SynHighlighterDml_initialization();
	Synhighlighterdot::SynHighlighterDOT_initialization();
	Synhighlighterdws::SynHighlighterDWS_initialization();
	Synhighlightereiffel::SynHighlighterEiffel_initialization();
	Synhighlighterfortran::SynHighlighterFortran_initialization();
	Synhighlighterfoxpro::SynHighlighterFoxpro_initialization();
	Synhighlightergalaxy::SynHighlighterGalaxy_initialization();
	Synhighlightergeneral::SynHighlighterGeneral_initialization();
	Synhighlighterhaskell::SynHighlighterHaskell_initialization();
	Synhighlighterhc11::SynHighlighterHC11_initialization();
	Synhighlighterhp48::SynHighlighterHP48_initialization();
	Synhighlighterhtml::SynHighlighterHtml_initialization();
	Synhighlighterini::SynHighlighterIni_initialization();
	Synhighlighterinno::SynHighlighterInno_initialization();
	Synhighlighterjava::SynHighlighterJava_initialization();
	Synhighlighterjscript::SynHighlighterJScript_initialization();
	Synhighlighterjson::SynHighlighterJSON_initialization();
	Synhighlighterkix::SynHighlighterKix_initialization();
	Synhighlightermodelica::SynHighlighterModelica_initialization();
	Synhighlighterm3::SynHighlighterM3_initialization();
	Synhighlighterpas::SynHighlighterPas_initialization();
	Synhighlighterperl::SynHighlighterPerl_initialization();
	Synhighlighterphp::SynHighlighterPHP_initialization();
	Synhighlighterprogress::SynHighlighterProgress_initialization();
	Synhighlighterpython::SynHighlighterPython_initialization();
	Synhighlighterrc::SynHighlighterRC_initialization();
	Synhighlighterruby::SynHighlighterRuby_initialization();
	Synhighlightersml::SynHighlighterSml_initialization();
	Synhighlightersql::SynHighlighterSQL_initialization();
	Synhighlightertcltk::SynHighlighterTclTk_initialization();
	Synhighlightertex::SynHighlighterTeX_initialization();
	Synhighlighterunixshellscript::SynHighlighterUNIXShellScript_initialization();
	Synhighlighteruri::SynHighlighterURI_initialization();
	Synhighlightervb::SynHighlighterVB_initialization();
	Synhighlightervbscript::SynHighlighterVBScript_initialization();
	Synhighlightervrml97::SynHighlighterVrml97_initialization();
	Synhighlightergws::SynHighlighterGWS_initialization();
	Synhighlightercpm::SynHighlighterCPM_initialization();
	Synhighlightersdd::SynHighlighterSDD_initialization();
	Synhighlighterxml::SynHighlighterXML_initialization();
	Synhighlightermsg::SynHighlighterMsg_initialization();
	Synhighlighteridl::SynHighlighterIDL_initialization();
	Synhighlighterunreal::SynHighlighterUnreal_initialization();
	Synhighlighterst::SynHighlighterST_initialization();
	Synhighlighterldraw::SynHighlighterLDraw_initialization();
	Synuriopener::SynURIOpener_initialization();
	Synhighlighterllvm::SynHighlighterLLVM_initialization();
	Synhighlighterrexx::SynHighlighterRexx_initialization();
	Synhighlighterwebidl::SynHighlighterWebIDL_initialization();
}


void __fastcall Synedit_exit()
{
	Synhighlighterpython::SynHighlighterPython_finalization();
	Syneditdataobject::SynEditDataObject_finalization();
	Syntextdrawer::SynTextDrawer_finalization();
	Synedithighlighter::SynEditHighlighter_finalization();
}


}  // namespace Synedit_initexit


//The following pragmas do not work for all C++Builder compilers
//insert an instance of CSynedit_initexit in the main file instead
#pragma startup Synedit_init
#pragma exit Synedit_exit
