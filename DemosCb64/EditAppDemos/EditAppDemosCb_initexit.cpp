#include <vcl.h>
#pragma hdrstop

#include "EditAppDemosCb_initexit.h"
#include "SynUnicode.h"
#include "SynTextDrawer.h"
#include "SynEditHighlighter.h"
#include "SynEditKeyCmds.h"
#include "SynHighlighterSQL.h"
#include "SynHighlighterPas.h"
#include "SynHighlighterCpp.h"
#include "frmEditor.h"
#include "SynEditDataObject.h"

using namespace std;
using namespace d2c_system;



void __fastcall EditAppDemosCb_init()
{
	SynUnicode_initialization();
	SynEditHighlighter_initialization();
	SynEditKeyCmds_initialization();
	SynHighlighterSQL_initialization();
	SynHighlighterPas_initialization();
	SynHighlighterCpp_initialization();
	frmEditor_initialization();
	SynEditDataObject_initialization();
}


void __fastcall EditAppDemosCb_exit()
{
	SynEditDataObject_finalization();
	frmEditor_finalization();
	SynEditHighlighter_finalization();
//	SynTextDrawer_finalization();
//  frmEditor_unit _frmEditor_unit;  in frmEditor.cpp instead
}

// empirical from Delphi
//void __fastcall EditAppDemosCb_exit()
//{
//	frmEditor_finalization();
//	SynEditHighlighter_finalization();
//	SynEditDataObject_finalization();
//	SynTextDrawer_finalization();
//}


//The following pragmas do not work for all C++Builder compilers
//insert an instance of CEditAppDemosCb_initexit in the main file instead
//#pragma startup EditAppDemosCb_init
//#pragma exit EditAppDemosCb_exit
