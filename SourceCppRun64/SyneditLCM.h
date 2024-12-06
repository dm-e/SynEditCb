#ifndef SyneditLCMH
#define SyneditLCMH

#include <System.hpp>
#include "d2c_system.h"


namespace Syneditlcm
{


void __fastcall Synedit_init();
void __fastcall Synedit_exit();


}  // namespace SyneditLCM

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditlcm;
#endif




class CSyneditLifecycleManager {
public:
  CSyneditLifecycleManager()  {Syneditlcm::Synedit_init();}
  ~CSyneditLifecycleManager() {Syneditlcm::Synedit_exit();}
};

// insert an instance of CSyneditLifecycleManager into the main file, e.g. CSyneditLifecycleManager _UnitsInitExit;

#endif // SyneditLCMH
