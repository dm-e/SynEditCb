#ifndef CompletionProposalDemoCb_initexitH
#define CompletionProposalDemoCb_initexitH

#include <System.hpp>
#include "d2c_system.h"



void __fastcall CompletionProposalDemoCb_init();
void __fastcall CompletionProposalDemoCb_exit();

#endif // CompletionProposalDemoCb_initexitH



class CCompletionProposalDemoCb_initexit {
public:
  CCompletionProposalDemoCb_initexit()  {CompletionProposalDemoCb_init();}
  ~CCompletionProposalDemoCb_initexit() {CompletionProposalDemoCb_exit();}
};

// insert an instance of CCompletionProposalDemoCb_initexit into the main file, e.g. CCompletionProposalDemoCb_initexit _UnitsInitExit;
