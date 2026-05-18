#ifndef d2c_supportsH
#define d2c_supportsH


// C++Builder Supports helpers using __uuidof and Builder DelphiInterface.
// Requires: <System.hpp>, d2c_diout.h

#include <type_traits>
#include <System.hpp>
#include "d2c_diout.h"

namespace System
{

// IInterface* -> DI<T>  (QI + DiOut; commit now)
template <class TInterface>
inline bool Supports(IInterface* iface, DelphiInterface<TInterface>& out) noexcept
{
  static_assert(std::is_base_of<IInterface, TInterface>::value, "TInterface must derive from IInterface");
  out = nullptr;
  if (!iface) return false;
  DiOut<TInterface> d(out);
  if (iface->QueryInterface(__uuidof(TInterface), d) != S_OK) return false;
  d.commit();
  return out != nullptr;
}

template <class TInterface>
inline bool Supports(const IInterface* iface, DelphiInterface<TInterface>& out) noexcept
{
  return Supports(const_cast<IInterface*>(iface), out);
}

// DI<From> -> DI<To>  (QI + DiOut; commit now)
template<class To, class From>
inline bool Supports(const DelphiInterface<From>& src, DelphiInterface<To>& out) noexcept
{
  static_assert(std::is_base_of<IInterface, From>::value, "From must derive from IInterface");
  static_assert(std::is_base_of<IInterface, To>::value,   "To must derive from IInterface");
  out = nullptr;
  if (!src) return false;
  DiOut<To> d(out);
  if (src->QueryInterface(__uuidof(To), d) != S_OK) return false;
  d.commit();
  return out != nullptr;
}

// TObject* -> DI<T>  (GetInterface does NOT AddRef; DI assignment AddRef -> net +1)
template <class TInterface, class TObjectPtr>
inline std::enable_if_t<
  std::is_pointer<TObjectPtr>::value &&
  std::is_base_of<TObject, std::remove_pointer_t<TObjectPtr>>::value,
  bool>
Supports(TObjectPtr obj, DelphiInterface<TInterface>& out) noexcept
{
  static_assert(std::is_base_of<IInterface, TInterface>::value, "TInterface must derive from IInterface");
  out = nullptr;
  if (!obj) return false;
  void* p = nullptr;
  if (!obj->GetInterface(__uuidof(TInterface), &p) || !p) return false;
  // p has no extra AddRef; assigning to DI will AddRef once -> net +1
  out = static_cast<TInterface*>(p);
  return true;
}

// Prefer these to avoid explicit casts at call sites:
inline bool Supports(TInterfacedObject* obj, const GUID& iid) noexcept
{
  return obj ? obj->GetInterface(iid, nullptr) : false;
}
template<class TInterface>
inline bool Supports(TInterfacedObject* obj, DelphiInterface<TInterface>& out) noexcept
{
  return Supports<TObject*>(obj, out);
}

#ifdef _CPPRTTI
// C++Builder RTTI usually enabled; TCppInterfacedObject derives from TInterfacedObject.
// Provide symmetric overloads to kill ambiguity.
class TCppInterfacedObject; // forward (Builder RTL)

inline bool Supports(TCppInterfacedObject* obj, const GUID& iid) noexcept
{
  return obj ? obj->GetInterface(iid, nullptr) : false;
}
template<class TInterface>
inline bool Supports(TCppInterfacedObject* obj, DelphiInterface<TInterface>& out) noexcept
{
  return Supports<TObject*>(obj, out);
}
#endif

} // namespace System

#endif // d2c_supportsH
