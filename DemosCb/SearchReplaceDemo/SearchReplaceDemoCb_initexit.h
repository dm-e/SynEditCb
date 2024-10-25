#ifndef SearchReplaceDemoCb_initexitH
#define SearchReplaceDemoCb_initexitH

#include <System.hpp>
#include "d2c_system.h"



void __fastcall SearchReplaceDemoCb_init();
void __fastcall SearchReplaceDemoCb_exit();

#endif // SearchReplaceDemoCb_initexitH



class CSearchReplaceDemoCb_initexit {
public:
  CSearchReplaceDemoCb_initexit()  {SearchReplaceDemoCb_init();}
  ~CSearchReplaceDemoCb_initexit() {SearchReplaceDemoCb_exit();}
};

// insert an instance of CSearchReplaceDemoCb_initexit into the main file, e.g. CSearchReplaceDemoCb_initexit _UnitsInitExit;
