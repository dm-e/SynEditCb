#ifndef d2c_eventH
#define d2c_eventH

/*
    Copyright (C) 2026 Dr. Detlef Meyer-Eltz
    ----------------------------------------

    This file may be used without restriction in any
    project generated with Delphi2Cpp or Delphi2CB.

    It is a reduced version of the original Delphi2CB
    utility file with the same name.

    This file is required to compile the SynEdit
    components translated from Delphi to C++ using
    Delphi2CB:

        https://www.texttransformer.com/Delphi2CB_en.html
*/

#include <cstddef>
#include <cstring>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>


#include <System.hpp> // System::TMethod, System::DelphiInterface, System::IInterface, TGUID
#include <SysUtils.hpp> // System::Sysutils::{TProc,TProc__N,TFunc__N} and _di_ aliases
#include <atomic>


namespace d2c_system
{

  // Convert a C++Builder __closure value to System::TMethod.
  // Works for Delphi-style method pointers / events whose binary layout matches TMethod.
  template <typename T>
  inline System::TMethod to_method(const T& m) noexcept
  {
    static_assert(std::is_trivially_copyable_v<T>,
      "to_method requires a trivially copyable closure type");
    static_assert(sizeof(T) == sizeof(System::TMethod),
      "to_method requires closure size == System::TMethod size");

    System::TMethod result;
    std::memcpy(&result, &m, sizeof(System::TMethod));
    return result;
  }

  // Convert System::TMethod back to a C++Builder __closure type.
  template <typename T>
  inline T from_method(const System::TMethod& m) noexcept
  {
    static_assert(std::is_trivially_copyable_v<T>,
      "from_method requires a trivially copyable closure type");
    static_assert(sizeof(T) == sizeof(System::TMethod),
      "from_method requires closure size == System::TMethod size");

    T result{};
    std::memcpy(&result, &m, sizeof(System::TMethod));
    return result;
  }

} // namespace d2c_system

// ============================================================================
// Assigned helpers (Delphi-like semantics)
// Keep these ALWAYS available.
// ============================================================================

template <typename T>
inline bool Assigned(T* p) noexcept
{
  return p != nullptr;
}

// Closure pointers and function pointers are comparable to nullptr.
// We restrict to non-pointer scalars because the pointer overload above handles pointers.
template <typename T>
inline auto Assigned(T v) noexcept
  -> std::enable_if_t<!std::is_pointer_v<T>, bool>
{
  return v != nullptr;
}

#ifdef __CODEGEARC__
template <typename I>
inline bool Assigned(const System::DelphiInterface<I>& i) noexcept
{
  return i != nullptr;
}

inline bool Assigned(const System::TMethod& m) noexcept
{
  return m.Code != nullptr;
}
#endif

// d2c_system::event<Sig> (only if it exists)
namespace d2c_system { template <typename Sig> class event; }
template <typename Sig>
inline auto Assigned(const d2c_system::event<Sig>& e) noexcept
  -> decltype(static_cast<bool>(e), bool())
{
  return static_cast<bool>(e);
}

// d2c_system::callback<Sig> (only if it exists)
namespace d2c_system { template <typename Sig> class callback; }
template <typename Sig>
inline auto Assigned(const d2c_system::callback<Sig>& cb) noexcept
  -> decltype(cb.empty(), bool())
{
  return !cb.empty();
}

template <typename R, typename... Args>
inline bool Assigned(const std::function<R(Args...)>& fn) noexcept
{
  return static_cast<bool>(fn);
}

inline bool Assigned(std::nullptr_t) noexcept
{
  return false;
}



#endif // d2c_eventH
