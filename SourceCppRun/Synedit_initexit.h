#ifndef Synedit_initexitH
#define Synedit_initexitH

#include <System.hpp>
#include "d2c_system.h"


namespace Synedit_initexit
{


void __fastcall Synedit_init();
void __fastcall Synedit_exit();


}  // namespace Synedit_initexit

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synedit_initexit;
#endif

#endif // Synedit_initexitH



class CSynedit_initexit {
public:
  CSynedit_initexit()  {Synedit_initexit::Synedit_init();}
  ~CSynedit_initexit() {Synedit_initexit::Synedit_exit();}
};

// insert an instance of CSynedit_initexit into the main file, e.g. CSynedit_initexit _UnitsInitExit;
