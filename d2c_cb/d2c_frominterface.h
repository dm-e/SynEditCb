#ifndef d2c_frominterfaceH
#define d2c_frominterfaceH

// Fetch implementing TObject* from any interface via a light-weight helper interface.
// Also provides from_interface_or_throw and ObjectIs macro.

#include <System.hpp>
#include <System.SysUtils.hpp>
#include "d2c_supports.h"

namespace System
{

__interface INTERFACE_UUID("{51A5C420-B2B4-4EF2-9228-9B6D63ED3E00}")
IHasSelf : public IInterface
{
  virtual TObject* __fastcall GetSelfPointer() = 0;
};

// Returns TObject* or nullptr if not available.
template<class TFrom>
inline TObject* FromInterface(const DelphiInterface<TFrom>& intf)
{
  static_assert(std::is_base_of<IInterface, TFrom>::value, "TFrom must derive from IInterface");
  if (!intf) return nullptr;

  void* raw = nullptr;
  if (static_cast<IInterface*>(static_cast<TFrom*>(intf))
        ->QueryInterface(__uuidof(IHasSelf), &raw) != S_OK || !raw)
    return nullptr;

  auto selfIfc = static_cast<IHasSelf*>(raw);
  TObject* self = selfIfc->GetSelfPointer();
  selfIfc->Release(); // balance QI +1
  return self;
}

// Convert DI<TI> to T*, throw if cast fails.
template<class T, class TI>
inline T* from_interface_or_throw(const DelphiInterface<TI>& di)
{
  TObject* obj = FromInterface(di);
  if (auto* p = dynamic_cast<T*>(obj)) return p;
  throw Sysutils::EInvalidCast(L"Invalid interface cast");
}

// Delphi-style RTTI check
#ifndef ObjectIs
#define ObjectIs(OBJ_PTR, CLASSPTR) (dynamic_cast<CLASSPTR>(OBJ_PTR) != nullptr)
#endif

} // namespace System


#endif // d2c_frominterfaceH