#ifndef d2c_castH
#define d2c_castH

// Casting helpers for C++Builder
// as_di, qi_as_throw, QI_as, and "hard" as<TInterface>(source)

#include <type_traits>
#include <System.hpp>
#include <System.SysUtils.hpp>
#include "d2c_diout.h"
#include "d2c_supports.h"

namespace System
{

inline void d2c_throw_intfcast()
{
  throw Sysutils::EIntfCastError(L"Interface cast failed");
}

// Core: from raw IInterface* (QI -> +1; DI AddRef -> +2; balance)
template<class T>
inline DelphiInterface<T> as_di(IInterface* src)
{
  static_assert(std::is_base_of<IInterface, T>::value, "T must derive from IInterface");
  if (!src) d2c_throw_intfcast();
  void* p = nullptr;
  if (src->QueryInterface(__uuidof(T), &p) != S_OK || !p) d2c_throw_intfcast();
  T* raw = static_cast<T*>(p);          // QI +1
  DelphiInterface<T> res;
  res = raw;                            // AddRef -> +2
  raw->Release();                       // balance -> +1 in res
  return res;
}

// From DI<From>
template<class T, class From>
inline DelphiInterface<T> as_di(const DelphiInterface<From>& src)
{
  static_assert(std::is_base_of<IInterface, From>::value, "From must derive from IInterface");
  static_assert(std::is_base_of<IInterface, T>::value,    "T must derive from IInterface");
  return as_di<T>(static_cast<From*>(src)); // Builder DI implicit conv to raw
}

// From TObject* via GetInterface (no AddRef there)
template<class T, class TObjectPtr,
         class = std::enable_if_t<
           std::is_pointer<TObjectPtr>::value &&
           std::is_base_of<TObject, std::remove_pointer_t<TObjectPtr>>::value>>
inline DelphiInterface<T> as_di(TObjectPtr obj)
{
  static_assert(std::is_base_of<IInterface, T>::value, "T must derive from IInterface");
  if (!obj) d2c_throw_intfcast();
  void* p = nullptr;
  if (!obj->GetInterface(__uuidof(T), &p) || !p) d2c_throw_intfcast();
  T* raw = static_cast<T*>(p);          // GetInterface: no AddRef
  DelphiInterface<T> res;
  res = raw;                            // AddRef -> +1 in res
  return res;
}

// Throwing QI-based cast between interfaces
template<class TTargetIntf, class TSourceIntf>
inline DelphiInterface<TTargetIntf>
qi_as_throw(const DelphiInterface<TSourceIntf>& src)
{
  if (!src) return nullptr; // Delphi semantics: nil in -> nil out
  DelphiInterface<TTargetIntf> out;
  DiOut<TTargetIntf> d(out);
  if (src->QueryInterface(__uuidof(TTargetIntf), d) != S_OK) d2c_throw_intfcast();
  d.commit();
  if (!out) d2c_throw_intfcast();
  return out;
}

// Non-throwing helper: QI_as(obj, out)
template<class IFace, class AnyQI>
inline bool QI_as(AnyQI* obj, DelphiInterface<IFace>& out) noexcept
{
  static_assert(std::is_base_of<IInterface, IFace>::value, "IFace must derive from IInterface");
  out = nullptr;
  if (!obj) return false;
  DiOut<IFace> d(out);
  if (obj->QueryInterface(__uuidof(IFace), d) != S_OK) return false;
  d.commit();
  return out != nullptr;
}

// "Hard" cast like Delphi's IFoo(Source) that throws
template <typename TInterface, typename TSource>
TInterface* as(const TSource* source)
{
  static_assert(std::is_base_of<IInterface, TInterface>::value, "TInterface must derive from IInterface");
  if (!source) throw std::bad_cast();

  void* result = nullptr;
  if constexpr (std::is_base_of<TObject, TSource>::value)
  {
    if (const_cast<TObject*>(static_cast<const TObject*>(source))
          ->GetInterface(__uuidof(TInterface), &result))
      return static_cast<TInterface*>(result);
  }
  else
  {
    if (const_cast<TSource*>(source)
          ->QueryInterface(__uuidof(TInterface), &result) == S_OK)
      return static_cast<TInterface*>(result);
  }
  throw std::bad_cast();
}

} // namespace System



#endif // d2c_castH
