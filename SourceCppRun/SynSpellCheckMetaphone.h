#ifndef SynSpellCheckMetaphoneH
#define SynSpellCheckMetaphoneH

#include <System.hpp>
#include "d2c_system.h"


namespace Synspellcheckmetaphone
{

PWideChar __stdcall metaphone(PWideChar A, int lg);


}  // namespace SynSpellCheckMetaphone

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synspellcheckmetaphone;
#endif

#endif // SynSpellCheckMetaphoneH

