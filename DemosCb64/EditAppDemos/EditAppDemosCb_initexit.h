#ifndef EditAppDemosCb_initexitH
#define EditAppDemosCb_initexitH

#include <System.hpp>
#include "d2c_system.h"


void __fastcall EditAppDemosCb_init();
void __fastcall EditAppDemosCb_exit();

#endif // EditAppDemosCb_initexitH



class CEditAppDemosCb_initexit {
public:
  CEditAppDemosCb_initexit()  {EditAppDemosCb_init();}
  ~CEditAppDemosCb_initexit() {EditAppDemosCb_exit();}
};

// insert an instance of CEditAppDemosCb_initexit into the main file, e.g. CEditAppDemosCb_initexit _UnitsInitExit;
