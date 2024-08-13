#include <vcl.h>
#pragma hdrstop

#include "FoldingCb_initexit.h"

using namespace std;
using namespace d2c_system;



void __fastcall FoldingCb_init()
{
}


void __fastcall FoldingCb_exit()
{
}

//The following pragmas do not work for all C++Builder compilers
//insert an instance of CFoldingCb_initexit in the main file instead
#pragma startup FoldingCb_init
#pragma exit FoldingCb_exit
