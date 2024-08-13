#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------

using namespace std;



void __fastcall CompletionProposalDemoCb_init()
{
}


void __fastcall CompletionProposalDemoCb_exit()
{
}

//The following pragmas do not work for all C++Builder compilers
//insert an instance of CCompletionProposalDemoCb_initexit in the main file instead
#pragma startup CompletionProposalDemoCb_init
#pragma exit CompletionProposalDemoCb_exit
