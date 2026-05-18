#ifndef SynSpellCheckMetaphoneH
#define SynSpellCheckMetaphoneH

#include <System.hpp>
#include "d2c_system.h"


namespace Synspellcheckmetaphone
{

System::PWideChar __stdcall metaphone(System::PWideChar a, int lg);


}  // namespace Synspellcheckmetaphone

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synspellcheckmetaphone;
#endif

#endif // SynSpellCheckMetaphoneH

