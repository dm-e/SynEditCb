#include <vcl.h>
#pragma hdrstop

#include "SyneditLCM.h"
#include "GenLex.h"

using namespace std;
using namespace d2c_system;

namespace Syneditlcm
{



void __fastcall Synedit_init()
{
	Genlex::GenLex_initialization();
}


void __fastcall Synedit_exit()
{
}


}  // namespace Syneditlcm


//The following pragmas do not work for all C++Builder compilers
//insert an instance of CSyneditLifecycleManager in the main file instead
#pragma startup Synedit_init
#pragma exit Synedit_exit
