#ifndef d2c_configH
#define d2c_configH

/*
    Copyright (C) 2026 Dr. Detlef Meyer-Eltz
    ----------------------------------------

    This file may be used without restriction in any
    project generated with Delphi2Cpp or Delphi2CB.

*/

// ---- d2c_arch.h ----
#ifndef IS_64BIT
  #if defined(_WIN64)                     /* Windows 64-bit (MSVC/clang/bcc64) */
    #define IS_64BIT 1
  #elif defined(__LP64__)                 /* LP64 (POSIX/GCC/Clang) */
    #define IS_64BIT 1
  #elif defined(__x86_64__) || defined(_M_X64) \
     || defined(__aarch64__) || defined(_M_ARM64) \
     || defined(__ia64__) || defined(_M_IA64) \
     || defined(__ppc64__) || defined(__PPC64__)
    #define IS_64BIT 1
  #elif defined(__SIZEOF_POINTER__) && (__SIZEOF_POINTER__ == 8)
    #define IS_64BIT 1
  #else
    #define IS_64BIT 0
  #endif
#endif

#ifndef IS_32BIT
  #define IS_32BIT (!IS_64BIT)
#endif


#ifndef _T
#ifdef IS_64BIT
#define __T(x) L##x
#define _T(x) __T(x)
#else
#define _T(x) x
#endif
#endif

// ---- d2c_nullptr.h ----
#ifndef D2C_NULLPTR
  #if defined(__clang__)
    // bcc32c/bcc64 (Clang) o.ä.: Feature-Test
    #if __has_feature(cxx_nullptr)
	  #define D2C_NULLPTR nullptr
      #define D2C_HAS_NULLPTR 1
    #else
      #define D2C_NULLPTR 0
      #define D2C_HAS_NULLPTR 0
    #endif
  #elif defined(__cpp_nullptr) || (defined(__cplusplus) && __cplusplus >= 201103L)
    // Andere C++11-Compiler
    #define D2C_NULLPTR nullptr
    #define D2C_HAS_NULLPTR 1
  #else
    // Classic bcc32 & Co.
    #define D2C_NULLPTR 0
    #define D2C_HAS_NULLPTR 0
  #endif
#endif

// "NULL" für C++-Code: lieber 0 statt ((void*)0), um Funktions-/Member-Pointer nicht zu brechen.
#ifndef D2C_NULL
  #define D2C_NULL 0
#endif


// In einem zentralen Header (einmalig):
#ifndef D2C_NOEXCEPT
  #if defined(__clang__)
    // C++Builder Clang compilers (bcc32c/bcc64) have __has_feature
    #if __has_feature(cxx_noexcept)
      #define D2C_NOEXCEPT noexcept
    #else
      #define D2C_NOEXCEPT
    #endif
  #elif defined(__cpp_noexcept) || (defined(__cplusplus) && __cplusplus >= 201103L)
    // Other compilers with C++11 noexcept
    #define D2C_NOEXCEPT noexcept
  #else
    // C++Builder classic (bcc32) or similar – no noexcept
    #define D2C_NOEXCEPT
  #endif
#endif



#endif //  d2c_configH
