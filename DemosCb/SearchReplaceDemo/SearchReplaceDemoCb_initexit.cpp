#include <vcl.h>
#pragma hdrstop

#include "SearchReplaceDemoCb_initexit.h"

using namespace std;
using namespace d2c_system;



void __fastcall SearchReplaceDemoCb_init()
{
}


void __fastcall SearchReplaceDemoCb_exit()
{
}

//The following pragmas do not work for all C++Builder compilers
//insert an instance of CSearchReplaceDemoCb_initexit in the main file instead
#pragma startup SearchReplaceDemoCb_init
#pragma exit SearchReplaceDemoCb_exit
