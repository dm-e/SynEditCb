#ifndef FoldingCb_initexitH
#define FoldingCb_initexitH

#include <System.hpp>
#include "d2c_system.h"


void __fastcall FoldingCb_init();
void __fastcall FoldingCb_exit();

#endif // FoldingCb_initexitH



class CFoldingCb_initexit {
public:
  CFoldingCb_initexit()  {FoldingCb_init();}
  ~CFoldingCb_initexit() {FoldingCb_exit();}
};

// insert an instance of CFoldingCb_initexit into the main file, e.g. CFoldingCb_initexit _UnitsInitExit;
