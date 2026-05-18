#ifndef d2c_dioutH
#define d2c_dioutH

/*
	Copyright (C) <2026>  <Dr. Detlef Meyer-Eltz>
	---------------------------------------------

	this file is authorized for unlimited use in any
	project created with Delphi2Cpp or Delphi2CB.

	This is a shortened version of the Delphi2CB utility file of the same name.
	The file is required in order to be able to compile the code of the SynEdit
	components, which were translated to C++ with Delphi2CB:

		https://www.texttransformer.com/Delphi2CB_en.html
*/

// Lightweight QI out-parameter adapter that adopts the +1 from QueryInterface
// into a DelphiInterface<T> without adding another reference.

#include <type_traits>
#include <utility> // for std::move


namespace System
{

template<class IFace>
class DiOut
{
public:
  // Non-copyable but movable
  DiOut(const DiOut&) = delete;
  DiOut& operator=(const DiOut&) = delete;

  explicit DiOut(DelphiInterface<IFace>& dest) noexcept
    : dest_(dest), raw_(nullptr) {}

  // Movable
  DiOut(DiOut&& other) noexcept
    : dest_(other.dest_), raw_(other.raw_)
  {
    other.raw_ = nullptr;
  }

  DiOut& operator=(DiOut&& other) noexcept
  {
    if (this != &other)
    {
      finalize();
      raw_ = other.raw_;
      other.raw_ = nullptr;
    }
    return *this;
  }

  ~DiOut() { finalize(); }

  // Provide the exact pointer types expected by QI and similar APIs
  operator IFace** () noexcept { return &raw_; }
  operator void**  () noexcept { return reinterpret_cast<void**>(&raw_); }

  // Convenience accessors
  IFace** pp()  noexcept { return &raw_; }
  void**  ppv() noexcept { return reinterpret_cast<void**>(&raw_); }
  IFace*  get() const noexcept { return raw_; }

  // Commit now (instead of waiting for dtor)
  void commit() noexcept
  {
    if (raw_) { assign_and_balance_(); }
  }

  // Drop the captured pointer (if any) and release it to avoid leaks
  void reset() noexcept
  {
    if (raw_) { raw_->Release(); raw_ = nullptr; }
  }

private:
  void finalize() noexcept
  {
    if (raw_) { assign_and_balance_(); }
  }

  // Assign raw_ to DelphiInterface (which AddRef's), then Release raw_
  // so the net effect remains exactly +1 from the original QI.
  void assign_and_balance_() noexcept
  {
    dest_ = raw_;     // AddRef -> temporary +2
    raw_->Release();  // balance back to +1 owned by dest_
    raw_ = nullptr;
  }

  DelphiInterface<IFace>& dest_;
  IFace* raw_;
};

} // namespace System


#endif //  d2c_dioutH