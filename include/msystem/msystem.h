/**
 * @file msystem.h
 * @author your name (you@domain.com)
 * @brief MSYSTEM Environment Information
 * @version 0.1
 * @date 2023-08-08
 *
 * @copyright Copyright (C) 2016 Renato Silva
 *
 * Licensed under public domain
 *
 */

#ifndef MSYSTEM_H
#define MSYSTEM_H

/**
 * @name MSYSTEM_USING_CXX
 * @brief This macro is defined when this header is being processed
 * by a C++ compiler; it is undefined otherwise.
 *
 * It can be useful for logic and control-flow, among other things.
 *
 */
#ifdef _MSVC_LANG
#	define MSYSTEM_USING_CXX _MSVC_LANG
#elif defined(__cplusplus)
#	define MSYSTEM_USING_CXX __cplusplus
#else
#	undef  MSYSTEM_USING_CXX
#endif


#ifdef __has_feature
#	define MSYSTEM_HAS_FEATURE(x) __has_feature(x)
#else
#	define MSYSTEM_HAS_FEATURE(x) 0
#endif

#if defined(__has_include) || MSYSTEM_ICC_VERSION >= 1600 || MSYSTEM_MSC_VERSION >= 1900
#	define MSYSTEM_HAS_INCLUDE(x) __has_include(x)
#else
#	define MSYSTEM_HAS_INCLUDE(x) 0
#endif

#ifdef __has_attribute
#	define MSYSTEM_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#	define MSYSTEM_HAS_ATTRIBUTE(x) 0
#endif

#ifdef __has_c_attribute
#	define MSYSTEM_HAS_C_ATTRIBUTE(x) __has_c_attribute(x)
#else
#	define MSYSTEM_HAS_C_ATTRIBUTE(x) 0
#endif

#ifdef __has_cpp_attribute
#	define MSYSTEM_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#	define MSYSTEM_HAS_CPP_ATTRIBUTE(x) 0
#endif

#ifdef __has_builtin
#	define MSYSTEM_HAS_BUILTIN(x) __has_builtin(x)
#else
#	define MSYSTEM_HAS_BUILTIN(x) 0
#endif

#ifdef __has_extension
#	define MSYSTEM_HAS_EXTENSION(x) __has_extension(x)
#else
#	define MSYSTEM_HAS_EXTENSION(x) 0
#endif


/**
 * @name MSYSTEM_INTELLISENSE_GUARD
 * @brief This macro is set to a truthy value by your IDE
 * when generating intellisense data. It is useful to block
 * code from the intellisense engine in your IDE, if for example
 * the blocked code is expected (by the user) to be altered
 * during a configuration step, such as with '#cmakedefine'.
 *
 * Note with caution that the value will be '0' during the actual
 * compile runs on your code, thus anything this macro handles should
 * resolve into actual code that the compiler can parse - it may be
 * worth implementing extra checks/guards depending in the nature of
 * your code.
 *
 * Use with care!
 *
 */
#define MSYSTEM_INTELLISENSE_GUARD __INTELLISENSE__


/***************************************************************************//**
 *
 *  ... Include header macros
 *
 * If using a C++ compiler, the include definitions below will attemp to pick
 * up '<c[header]>' instead of the C-native '<[header].h>' file, to ensure our
 * downstream code is calling true C-style functions as expected.
 *
 ******************************************************************************/

/** STDLIB */
#ifdef MSYSTEM_USING_CXX
#  if MSYSTEM_HAS_INCLUDE(<cstdlib>)
#    include <cstdlib>
#    define HAVE_CSTDLIB 1
#  else
#    undef HAVE_CSTDLIB
#  endif
#else
#  if MSYSTEM_HAS_INCLUDE(<stdlib.h>)
#    include <stdlib.h>
#    define HAVE_STDLIB_H 1
#  else
#    undef HAVE_STDLIB_H
#  endif
#endif

/** STDIO */
#ifdef MSYSTEM_USING_CXX
#  if MSYSTEM_HAS_INCLUDE(<cstdio>)
#    include <cstdio>
#    define HAVE_CSTDIO 1
#  else
#    undef HAVE_CSTDIO
#  endif
#else
#  if MSYSTEM_HAS_INCLUDE(<stdio.h>)
#    include <stdio.h>
#    define HAVE_STDIO_H 1
#  else
#    undef HAVE_STDIO_H
#  endif
#endif

/** STDINT */
#ifdef PKGMAN_CPLUSPLUS
#  if MSYSTEM_HAS_INCLUDE(<cstdint>)
#    include <cstdint>
#    define HAVE_CSTDINT 1
#  else
#    undef HAVE_CSTDINT
#  endif
#else
#  if MSYSTEM_HAS_INCLUDE(<stdint.h>)
#    include <stdint.h>
#    define HAVE_STDINT_H 1
#  endif
#endif

/** STDDEF */
#ifdef PKGMAN_CPLUSPLUS
#  if MSYSTEM_HAS_INCLUDE(<cstddef>)
#    include <cstddef>
#    define HAVE_CSTDDEF 1
#  else
#    undef HAVE_CSTDDEF
#  endif
#else
#  if MSYSTEM_HAS_INCLUDE(<stddef.h>)
#    include <stddef.h>
#    define HAVE_STDDEF_H 1
#  else
#    undef HAVE_STDDEF_H
#  endif
#endif

/** WCHAR - fwprintf(), swprintf(), wprintf() */
#ifdef PKGMAN_CPLUSPLUS
#  if MSYSTEM_HAS_INCLUDE(<cwchar>)
#    include <cwchar>
#    define HAVE_CWCHAR 1
#  else
#    undef HAVE_CWCHAR
#  endif
#else
#  if MSYSTEM_HAS_INCLUDE(<wchar.h>)
#    include <wchar.h>
#    define HAVE_WCHAR_H 1
#  else
#    undef HAVE_WCHAR_H
#  endif
#endif

/** Check <sys/headers.h> */
#if MSYSTEM_HAS_INCLUDE(<sys/mnttab.h>)
#    include <sys/mnttab.h>
#    define HAVE_SYS_MNTTAB_H 1
#endif
#if MSYSTEM_HAS_INCLUDE(<sys/mount.h>)
#    include <sys/mount.h>
#    define HAVE_SYS_MOUNT_H 1
#endif
#if MSYSTEM_HAS_INCLUDE(<sys/param.h>)
#    include <sys/param.h>
#    define HAVE_SYS_PARAM_H 1
#endif
#if MSYSTEM_HAS_INCLUDE(<sys/stat.h>)
#    include <sys/stat.h>
#    define HAVE_SYS_STAT_H 1
#endif
#if MSYSTEM_HAS_INCLUDE(<sys/statfs.h>)
#    include <sys/statfs.h>
#    define HAVE_SYS_STATFS_H 1
#endif
#if MSYSTEM_HAS_INCLUDE(<sys/statvfs.h>)
#    include <sys/statvfs.h>
#    define HAVE_SYS_STATVFS_H 1
#endif
#if MSYSTEM_HAS_INCLUDE(<sys/types.h>)
#    include <sys/types.h>
#    define HAVE_SYS_TYPES_H 1
#endif
#if MSYSTEM_HAS_INCLUDE(<sys/ucred.h>)
#    include <sys/ucred.h>
#    define HAVE_SYS_UCRED_H 1
#endif

/** Additional headers... */
#if MSYSTEM_HAS_INCLUDE(<termios.h>)
#    include <termios.h>
#    define HAVE_TERMIOS_H 1
#endif
#if MSYSTEM_HAS_INCLUDE(<mntent.h>)
#    include <mntent.h>
#    define HAVE_MNTENT_H 1
#endif

/**
 * #if !(MSYSTEM_INTELLISENSE_GUARD)
 * #cmakedefine MSYSTEM_CONFIGURED @CMAKE_C_COMPILER_WORKS@
 * #endif
*/

#if !defined(__TO_STRING)
#	define __TO_STRING(X) #X
#endif

#if !defined(__STRING)
#	define __STRING(X) __TO_STRING(X)
#endif

#define MSYSTEM_RUNTIME_LIBRARY __TO_STRING(msys-2.0.dll)

/** export MSYSTEM="${MSYSTEM:-MSYS}" */

#define MSYS 0
#define UCRT64 1
#define MINGW64 2
#define MINGW32 3
#define CLANG64 4
#define CLANG32 5
#define CLANGARM64 6

#ifndef MSYSTEM_DEFAULT
#  define MSYSTEM_DEFAULT UCRT64
#endif

#ifndef MSYSTEM
#  define MSYSTEM MSYSTEM_DEFAULT
#endif

#undef MSYSTEM_PREFIX
#undef MSYSTEM_CARCH
#undef MSYSTEM_CHOST

#undef MINGW_CHOST
#undef MINGW_PREFIX
#undef MINGW_PACKAGE_PREFIX


#if (MSYSTEM == MINGW32)
#  define MSYSTEM_PREFIX __TO_STRING(/mingw32)
#  define MSYSTEM_CARCH __TO_STRING(i686)
#  define MSYSTEM_CHOST __TO_STRING(i686-w64-mingw32)
#  define MINGW_CHOST MSYSTEM_CHOST
#  define MINGW_PREFIX MSYSTEM_PREFIX
#  define MINGW_PACKAGE_PREFIX __TO_STRING(mingw-w64-i686)
#elif (MSYSTEM == MINGW64)
#  define MSYSTEM_PREFIX __TO_STRING(/mingw64)
#  define MSYSTEM_CARCH __TO_STRING(x86_64)
#  define MSYSTEM_CHOST __TO_STRING(x86_64-w64-mingw64)
#  define MINGW_CHOST MSYSTEM_CHOST
#  define MINGW_PREFIX MSYSTEM_PREFIX
#  define MINGW_PACKAGE_PREFIX __TO_STRING(mingw-w64-x86_64)
#elif (MSYSTEM == CLANG32)
#  define MSYSTEM_PREFIX __TO_STRING(/clang32)
#  define MSYSTEM_CARCH __TO_STRING(i686)
#  define MSYSTEM_CHOST __TO_STRING(i686-w64-mingw32)
#  define MINGW_CHOST MSYSTEM_CHOST
#  define MINGW_PREFIX MSYSTEM_PREFIX
#  define MINGW_PACKAGE_PREFIX __TO_STRING(mingw-w64-clang-i686)
#elif (MSYSTEM == CLANG64)
#  define MSYSTEM_PREFIX __TO_STRING(/clang64)
#  define MSYSTEM_CARCH __TO_STRING(x86_64)
#  define MSYSTEM_CHOST __TO_STRING(x86_64-w64-mingw32)  /** The originalMSYSTEM.sh has this down as '-mingw32' ?*/
#  define MINGW_CHOST MSYSTEM_CHOST
#  define MINGW_PREFIX MSYSTEM_PREFIX
#  define MINGW_PACKAGE_PREFIX __TO_STRING(mingw-w64-clang-x86_64)
#elif (MSYSTEM == CLANGARM64)
#  define MSYSTEM_PREFIX __TO_STRING(/clangarm64)
#  define MSYSTEM_CARCH __TO_STRING(aarch64)
#  define MSYSTEM_CHOST __TO_STRING(aarch64-w64-mingw32)  /** The originalMSYSTEM.sh has this down as '-mingw32' ?*/
#  define MINGW_CHOST MSYSTEM_CHOST
#  define MINGW_PREFIX MSYSTEM_PREFIX
#  define MINGW_PACKAGE_PREFIX __TO_STRING(mingw-w64-clang-aarch64)
#elif (MSYSTEM == UCRT64) /** #  define MSYSTEM_PREFIX __TO_STRING(/ucrt64) */

#  define MSYSTEM_PREFIX __TO_STRING(/ucrt64)
#  define MSYSTEM_CARCH __TO_STRING(x86_64)
#  define MSYSTEM_CHOST __TO_STRING(x86_64-w64-mingw32)  /** The originalMSYSTEM.sh has this down as '-mingw32' ?*/
#  define MINGW_CHOST MSYSTEM_CHOST
#  define MINGW_PREFIX MSYSTEM_PREFIX
#  define MINGW_PACKAGE_PREFIX __TO_STRING(mingw-w64-ucrt-x86_64)
#elif (MSYSTEM == MSYS)
#  define MSYSTEM_PREFIX __TO_STRING(/usr)
#  define MSYSTEM_CARCH __TO_STRING(x86_64-pc-msys) /** $(/usr/bin/uname -m) or invoke config.guess? */
#  define MSYSTEM_CHOST __TO_STRING(x86_64-pc-msys)
#endif

/***************************************************************************//**
 *
 *  ... First-Level Checks
 *
 * 'MSYSTEM' is checked to directly determine some intial logical variables.
 *
 ******************************************************************************/

#if (MSYSTEM == MSYS) || (MSYSTEM == UCRT64) || (MSYSTEM == MINGW64) || (MSYSTEM == MINGW32)
#  define MSYSTEM_TOOLCHAIN_IS_GNU 1
#elif (MSYSTEM == CLANG64) || (MSYSTEM == CLANG32) || (MSYSTEM == CLANGARM64)
#  define MSYSTEM_TOOLCHAIN_IS_LLVM 1
#else
#  define MSYSTEM_TOOLCHAIN_IS_UNKNOWN 1 /** Or rather, MSYSTEM appears to be undefined, somehow? */
#endif

#if (MSYSTEM == MSYS)
#  define MSYSTEM_C_LIBRARY_IS_CYGWIN 1
#elif (MSYSTEM == UCRT64) || (MSYSTEM == CLANG32) || (MSYSTEM == CLANGARM64) || (MSYSTEM == CLANGARM64)
#  define MSYSTEM_C_LIBRARY_IS_UCRT 1
#elif (MSYSTEM == MINGW64) || (MSYSTEM == MINGW32)
#  define MSYSTEM_C_LIBRARY_IS_MSVCRT 1
#else
#  define MSYSTEM_C_LIBRARY_IS_UNKNOWN 1 /** Or rather, 'MSYSTEM' appears to be undefined, somehow? */
#endif

#if (MSYSTEM == MSYS) || (MSYSTEM == UCRT64) || (MSYSTEM == MINGW64) || (MSYSTEM == MINGW32)
#  define MSYSTEM_CXX_LIBRARY_IS_LIBSTDCXX 1
#elif (MSYSTEM == CLANG64) || (MSYSTEM == CLANG32) || (MSYSTEM == CLANGARM64)
#  define MSYSTEM_CXX_LIBRARY_IS_LIBCXX 1
#else
#  define MSYSTEM_CXX_LIBRARY_IS_UNKNOWN 1 /** Or rather, 'MSYSTEM' appears to be undefined, somehow? */
#endif


/***************************************************************************//**
 *
 *  ... Second-Level Checks
 *
 * 'MSYSTEM' is not checked directly from here onwards; instead, we use the
 * logical variables we just defined.
 *
 * This will allow us to keep some seperation between stages in case anything
 * goes wrong or changes at the wrong place and time.
 *
 ******************************************************************************/
#if (MSYSTEM_TOOLCHAIN_IS_GNU)
#  define MSYSTEM_TOOLCHAIN __STRING(GNU)
#elif (MSYSTEM_TOOLCHAIN_IS_LLVM)
#  define MSYSTEM_TOOLCHAIN __STRING(LLVM)
#else
#  define MSYSTEM_TOOLCHAIN __STRING(UNKNOWN) /** Or rather, 'MSYSTEM_TOOLCHAIN_IS_*' appears to be undefined, somehow? */
#endif

#if (MSYSTEM_C_LIBRARY_IS_CYGWIN)
#  define MSYSTEM_C_LIBRARY __STRING(cygwin)
#elif (MSYSTEM_C_LIBRARY_IS_UCRT)
#  define MSYSTEM_C_LIBRARY __STRING(ucrt)
#elif (MSYSTEM_C_LIBRARY_IS_MSVCRT)
#  define MSYSTEM_C_LIBRARY __STRING(msvcrt)
#else
#  define MSYSTEM_C_LIBRARY __STRING(UNKNOWN) /** Or rather, 'MSYSTEM_C_LIBRARY_IS_*' appears to be undefined, somehow? */
#endif

#if (MSYSTEM_CXX_LIBRARY_IS_LIBSTDCXX)
#  define MSYSTEM_CXX_LIBRARY __STRING(libstdc++)
#elif (MSYSTEM_CXX_LIBRARY_IS_LIBCXX)
#  define MSYSTEM_CXX_LIBRARY __STRING(libc++)
#else
#  define MSYSTEM_CXX_LIBRARY __STRING(UNKNOWN) /** Or rather, 'MSYSTEM_CXX_LIBRARY_IS_*' appears to be undefined, somehow? */
#endif


/***************************************************************************//**
 *
 *  ... Propagation
 *
 ******************************************************************************/
#ifdef MSYSTEM_USING_CXX
extern "C" {
#endif

#if (MSYSTEM != MSYS)
const char* mingw_prefix[] = 		{ MINGW_PREFIX, '\0'  };
const char* mingw_chost[] = 			{ MINGW_CHOST, '\0'  };
const char* mingw_package_prefix[] = 	{ MINGW_PACKAGE_PREFIX, '\0'  };
#endif

const char* msystem_prefix[] = 		{ MSYSTEM_PREFIX, '\0' };
const char* msystem_carch[] = 		{ MSYSTEM_CARCH, '\0'  };
const char* msystem_chost[] = 		{ MSYSTEM_CHOST, '\0'  };

const char* msystem_toolchain[] = 	{ MSYSTEM_TOOLCHAIN, '\0'  };
const char* msystem_c_library[] = 	{ MSYSTEM_C_LIBRARY, '\0'  };
const char* msystem_cxx_library[] = 	{ MSYSTEM_CXX_LIBRARY, '\0'  };

#ifdef MSYSTEM_USING_CXX
}
#endif

#endif /** MSYSTEM_H */
