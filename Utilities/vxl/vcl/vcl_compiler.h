//-*- c++ -*-------------------------------------------------------------------
#ifndef vcl_compiler_h_
#define vcl_compiler_h_

//:
// \file
//
// It's much better to determine the compiler automatically here than to depend
// on command-line flags being set.

#if defined(__sgi) && !defined(__GNUC__)
# ifndef _COMPILER_VERSION
#  define VCL_SGI_CC_6
# else
#  if (_COMPILER_VERSION >= 700)
#   define VCL_SGI_CC_7
#  else
#   define VCL_SGI_CC_6
#  endif
#  if   (_COMPILER_VERSION >= 730)
#   define VCL_SGI_CC_730
#  elif (_COMPILER_VERSION >= 720)
#   define VCL_SGI_CC_720
#  endif
#  define VCL_SGI_CC
# endif
#endif

#if defined(__SUNPRO_CC)
# define VCL_SUNPRO_CC
# if (__SUNPRO_CC>=0x500)
#  define VCL_SUNPRO_CC_50
# else
#  undef VCL_SUNPRO_CC_50
# endif
# ifdef INSTANTIATE_TEMPLATES
#  define _RWSTD_COMPILE_INSTANTIATE
# endif
#endif

#if defined(__GNUC__)
# define VCL_GCC
# if (__GNUC__<=1)
#  error "forget it."
# elif (__GNUC__==2)
#  if (__GNUC_MINOR__>=100)
#   error "I need some help here."
#  elif (__GNUC_MINOR__>=95)
#   define VCL_GCC_295
#  elif (__GNUC_MINOR__>8)
#   define VCL_EGCS
#  elif (__GNUC_MINOR__>7)
#   define VCL_GCC_28
#  elif (__GNUC_MINOR__>6)
#   define VCL_GCC_27
#  endif
#  if (__GNUC_MINOR__>7)
#   define VCL_GCC_EGCS // so this is the union of EGCS, GCC_28 and GCC_295
#  endif
# elif (__GNUC__==3)
#  define VCL_GCC_30
#  if (__GNUC_MINOR__>0)
#   define VCL_GCC_31
#  endif
#  if (__GNUC_MINOR__>1)
#   define VCL_GCC_32
#  endif
# else
#  error "Dunno about this gcc"
# endif
#endif

#if defined(_WIN32) || defined(WIN32)
# define VCL_WIN32
# if defined(_MSC_VER)
#  define VCL_VC
#  if _MSC_VER >= 1300
#   define VCL_VC_DOTNET 1 // VC is at least version >= 7.0
#   if _MSC_VER >= 1310
#    define VCL_VC71 1     // .NET 2003 = Version 7.1
#   else
#    define VCL_VC70 1     // earlier .NET versions = Version 7.0
#   endif
#  elif _MSC_VER >= 1200   // last version before advent of .NET = Version 6.0
#   define VCL_VC60 1
#  else
#   define VCL_VC50 1
#  endif
# elif defined(__BORLANDC__)
#  define VCL_BORLAND
#  if __BORLANDC__ >= 0x0560
#   define VCL_BORLAND_56
#  elif __BORLANDC__ >= 0x0550
#   define VCL_BORLAND_55
#  endif
# endif
#endif

// win32 or vc++ ?
// awf hack alert:
#ifdef VCL_VC
#  ifdef VCL_VC60
#    pragma warning(disable:4786 4660 4661)
#    pragma warning(disable:4786 4660 4355 4390)
#  elif VCL_VC_DOTNET
// 4786: 'identifier' : identifier was truncated to 'number' characters in the debug information
// 4018: signed/unsigned mismatch
// 4146: unary minus operator applied to unsigned type, result still unsigned
// 4267: conversion related to size_t
// 4355: 'this' : used in base member initializer list
#    pragma warning(disable:4786 4018 4146 4267 4355)
#  endif
#endif

#if defined(__KCC) // KAI compiler
# define VCL_KAI
#endif

#if defined(__ICC) ||defined(__ECC) // Intel compiler?
# define VCL_ICC
#endif

#if defined(como4301) // Comeau C/C++ 4.3.0.1
# define VCL_COMO
#endif


#if defined(__MWERKS__)
// [sic]
# define VCL_METRO_WERKS
#endif

// include header files generated by configure.
#include <vcl_config_manual.h>
#include <vcl_config_compiler.h>
#include <vcl_config_headers.h>

// This *needs* to come after vcl_config_headers.h
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
# ifdef VCL_GCC_30
#  define GNU_LIBSTDCXX_V3 1
# elif !defined(GNU_LIBSTDCXX_V3) && defined(VCL_GCC_295) && VCL_CXX_HAS_HEADER_ISTREAM
// One difference between v2 and v3 is that the former has
// no <istream> header file whereas v3 has the lot.
#  define GNU_LIBSTDCXX_V3 1
# endif
#endif

// -------------------- default template parameters
#if VCL_CAN_DO_COMPLETE_DEFAULT_TYPE_PARAMETER
# define VCL_DFL_TYPE_PARAM_STLDECL(A, a) class A = a
#else
# define VCL_DFL_TYPE_PARAM_STLDECL(A, a) class A
#endif

#if VCL_CAN_DO_TEMPLATE_DEFAULT_TYPE_PARAMETER
# define VCL_DFL_TMPL_PARAM_STLDECL(A, a) class A = a
#else
# define VCL_DFL_TMPL_PARAM_STLDECL(A, a) class A
#endif

#define VCL_DFL_TMPL_ARG(classname) , classname

#if VCL_USE_NATIVE_STL
# define VCL_SUNPRO_ALLOCATOR_HACK(T) T VCL_SUNPRO_CLASS_SCOPE_HACK(std::allocator<T >)
#else
# define VCL_SUNPRO_ALLOCATOR_HACK(T) T // FIXME
#endif

//-------------------- template instantiation

// if the compiler doesn't understand "export", we just leave it out.
// gcc and SunPro 5.0 understand it, but they ignore it noisily.
#if !VCL_HAS_EXPORT || defined(VCL_EGCS) || defined(VCL_GCC_295) || defined(VCL_GCC_30) || defined(VCL_SUNPRO_CC_50)
# define export /* ignore */
#endif

#if VCL_NEEDS_INLINE_INSTANTIATION
# define VCL_INSTANTIATE_INLINE(symbol) template symbol
#else
# define VCL_INSTANTIATE_INLINE(symbol) /* */
#endif

// work-around to get template instantiation to work correctly with SunPro
// check flag to turn on inlining
#undef IUEi_STL_INLINE
#if defined(INLINE_EXPLICIT_FLAG) && defined(VCL_SUNPRO_CC) && defined(INSTANTIATE_TEMPLATES)
# define IUEi_STL_INLINE
#else
# define IUEi_STL_INLINE inline
#endif

//--------------------------------------------------------------------------------

#if VCL_FOR_SCOPE_HACK
# undef for
# define for if (false) { } else for
typedef int saw_VCL_FOR_SCOPE_HACK;
#endif

// fix to instantiate template functions
#define VCL_INSTANTIATE_NONINLINE(fn_decl) template fn_decl

// -------------------- handy macros

//: VCL_COMMA
//
// Handy for passing things with commas in them to CPP macros.  e.g.
// DO_MACRO(pair<A,B>) can be replaced by DO_MACRO(pair<A VCL_COMMA B>).
#define VCL_COMMA ,


//: VCL_VOID_RETURN
//
// VCL_VOID_RETURN is used as a return type where void is expected,
// as in return VCL_VOID_RETURN;
#define VCL_VOID_RETURN /*empty*/

#endif // vcl_compiler_h_
