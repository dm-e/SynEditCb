#ifndef Synedit_dme_initexitH
#define Synedit_dme_initexitH

#include <System.hpp>
#include "d2c_system.h"


namespace Synedit_dme_initexit
{


void __fastcall Synedit_dme_init();
void __fastcall Synedit_dme_exit();


}  // namespace Synedit_dme_initexit

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synedit_dme_initexit;
#endif

#endif // Synedit_dme_initexitH



class CSynedit_dme_initexit {
public:
  CSynedit_dme_initexit()  {Synedit_dme_initexit::Synedit_dme_init();}
  ~CSynedit_dme_initexit() {Synedit_dme_initexit::Synedit_dme_exit();}
};

// insert an instance of CSynedit_dme_initexit into the main file, e.g. CSynedit_dme_initexit _UnitsInitExit;
