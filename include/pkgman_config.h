/***************************************************************************//**
 * @file config.h
 * @author Nathan J. Hood <nathanjhood@googlemail.com>
 * @brief Modern C configuration header for pacman/pkgman
 * @version 0.1
 * @date 2023-08-07
 *
 * @copyright Copyright (c) 2023 GNU GPL2.0 - Nathan J. Hood <nathanjhood@googlemail.com>
 *
 * @details
 *
 * Attempts are made at making the entire pkgman codebase C++
 * compatibility-friendly, for example by wrapping our C code in the
 * 'extern "C"{}' keyword. However, using the C++ stdlib definitions of the
 * required library functions on this codebase is untested territory, and C++
 * interoperability should be considered highly experimental, at best.
 *
 * The presence of the 'extern "C"{}' keyword and other compatibility
 * features may be useful in such experimental efforts, while causing no harm at
 * all in all other cases; thus it has been added to the codebase. But,
 * this does NOT indicate any actual official support for C++ implementations.
 *
 ******************************************************************************/

#ifndef PKGMAN_CONFIGURATION_H
#define PKGMAN_CONFIGURATION_H

#define PKGMAN_VERSION_MAJOR 6
#define PKGMAN_VERSION_MINOR 0
#define PKGMAN_VERSION_PATCH 2
#define PKGMAN_VERSION_TWEAK __PM_STRING(81c0a15465cc6197b913e761833d2b486fc0c4fa)
#define PKGMAN_VERSION (PKGMAN_VERSION_MAJOR * 10000 + PKGMAN_VERSION_MINOR * 100 + PKGMAN_VERSION_PATCH)

/***************************************************************************//**
 *  ... C Requirements...
 ******************************************************************************/

#ifndef   _XOPEN_SOURCE
#  define _XOPEN_SOURCE 700
#endif
#ifndef   _XOPEN_VERSION
#  define _XOPEN_VERSION _XOPEN_SOURCE
#endif
#ifndef   _GNU_SOURCE
#  define _GNU_SOURCE 1
#endif
#ifndef   _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE 1
#endif

#ifndef   __need_mode_t
#  define __need_mode_t 1
#endif
#ifndef   __need_uid_t
#  define __need_uid_t 1
#endif
#ifndef   __need_off_t
#  define __need_off_t 1
#endif
#ifndef   __need_pid_t
#  define __need_pid_t 1
#endif
#ifndef   __need_size_t
#  define __need_size_t 1
#endif
#ifndef   __need_ssize_t
#  define __need_ssize_t 1
#endif
#ifndef   __need_int64_t
#  define __need_int64_t 1
#endif
#ifndef   __need_NULL
#  define __need_NULL 1
#endif

/**
 * If the compiler does not have __has_*(), pretend the answer is always no.
 */
#ifndef	__has_attribute
#define	__has_attribute(x)	0
#endif
#ifndef	__has_extension
#define	__has_extension		__has_feature
#endif
#ifndef	__has_feature
#define	__has_feature(x)	0
#endif
#ifndef	__has_include
#define	__has_include(x)	0
#endif
#ifndef	__has_builtin
#define	__has_builtin(x)	0
#endif

/***************************************************************************//**
 *
 *  ... Custom function macros
 *
 ******************************************************************************/

#ifndef _PM_STRINGIZE
#define __PM_STRINGIZE(_Value) #_Value
#define _PM_STRINGIZE(_Value) __PM_STRINGIZE(_Value)
#endif /* _CRT_STRINGIZE */

#ifndef _PM_WIDE
#define __PM_WIDE(_String) L ## _String
#define _PM_WIDE(_String) __PM_WIDE(_String)
#endif /* _PM_WIDE */


#if !defined(__PM_TO_STRING)
#	define __PM_TO_STRING(X) #X
#endif

#if !defined(__PM_STRING)
#	define __PM_STRING(X) __PM_TO_STRING(X)
#endif

/**
 * #if !defined(__to_char)
 * # define __to_char(X) #@X
 * #endif
*/

#if !defined(__char)
#	define __char(X) __to_char(X)
#endif

#if !defined(__to_int)
#	define __to_int(X) X
#endif

#if !defined(__int)
#	define __int(X) __to_int(X)
#endif

/**
 * @name DEC
 * @brief Convert integer to decimal digit literals.
 */
#if !defined(DEC)
#	 define  DEC(n)					  \
	   ('0' + (((n) / 10000000)%10)), \
	   ('0' + (((n) / 1000000)%10)),  \
	   ('0' + (((n) / 100000)%10)),   \
	   ('0' + (((n) / 10000)%10)),    \
	   ('0' + (((n) / 1000)%10)),     \
	   ('0' + (((n) / 100)%10)),      \
	   ('0' + (((n) / 10)%10)),       \
	   ('0' +  ((n) % 10))
#endif

/**
 * @name HEX
 * @brief Convert integer to hex digit literals.
 */
#if !defined(HEX)
#	 define  HEX(n)				 \
	    ('0' + ((n)>>28 & 0xF)), \
	    ('0' + ((n)>>24 & 0xF)), \
	    ('0' + ((n)>>20 & 0xF)), \
	    ('0' + ((n)>>16 & 0xF)), \
	    ('0' + ((n)>>12 & 0xF)), \
	    ('0' + ((n)>>8  & 0xF)), \
		('0' + ((n)>>4  & 0xF)), \
	 	('0' + ((n)     & 0xF))
#endif


/***************************************************************************//**
 *
 *  ... C Standards...
 *
 * C89	__STDC__					ANSI X3.159-1989
 * C90	__STDC__					ISO/IEC 9899:1990
 * C94	__STDC_VERSION__ = 199409L	ISO/IEC 9899-1:1994
 * C99	__STDC_VERSION__ = 199901L	ISO/IEC 9899:1999
 * C11	__STDC_VERSION__ = 201112L	ISO/IEC 9899:2011
 * C18	__STDC_VERSION__ = 201710L	ISO/IEC 9899:2018
 *
 ******************************************************************************/

#if		(__STDC_VERSION__ >= 201710L)
#	define PKGMAN_STANDARD_C_ STRINGIFY(C18)
#elif	(__STDC_VERSION__ >= 201112L)
#	define PKGMAN_STANDARD_C_ STRINGIFY(C11)
#elif	(__STDC_VERSION__ >= 199901L)
#	define PKGMAN_STANDARD_C_ STRINGIFY(C99)
#elif	(__STDC_VERSION__ >= 199409L)
#	define PKGMAN_STANDARD_C_ STRINGIFY(C94)
#endif

#ifdef __STDC__
#  define     PKGMAN_STANDARD_C_1989 1
#  ifdef __STDC_VERSION__
#    if (__STDC_VERSION__ >= 199409L)
#      define PKGMAN_STANDARD_C_1994 1
#    endif
#    if (__STDC_VERSION__ >= 199901L)
#      define PKGMAN_STANDARD_C_1999 1
#    endif
#  endif
#endif

/***************************************************************************//**
 *
 *  ... Platform check macros
 *
 ******************************************************************************/

#if defined(__MSYS__) || defined(MSYS)
#  define PKGMAN_PLATFORM_IS_MSYS 1
#endif

#if defined(__CYGWIN__) || defined (CYGWIN)
#  define PKGMAN_PLATFORM_IS_CYGWIN 1
#endif

#if defined (__MINGW64__) || defined(__MINGW32__) || defined (MINGW)
#  define PKGMAN_PLATFORM_IS_MINGW 1
#endif

#if defined(_WIN64) || defined(_WIN32) || defined (WIN32)
#  define PKGMAN_PLATFORM_IS_WINDOWS 1
#endif

#if  defined(__unix__) || defined(__unix) || defined(unix)
#  define PKGMAN_PLATFORM_IS_UNIX 1
#endif

#ifndef _XOPEN_UNIX
#  if (PKGMAN_PLATFORM_IS_UNIX) && defined(_XOPEN_SOURCE)
#    define _XOPEN_UNIX 1
#  endif
#endif

#ifdef _XOPEN_VERSION
#  if (_XOPEN_VERSION >= 3)
#    define PKGMAN_STANDARD_XOPEN_1989 1
#  endif
#  if (_XOPEN_VERSION >= 4)
#    define PKGMAN_STANDARD_XOPEN_1992 1
#  endif
#  if (_XOPEN_VERSION >= 4) && defined(_XOPEN_UNIX)
#    define PKGMAN_STANDARD_XOPEN_1995
#  endif
#  if (_XOPEN_VERSION >= 500)
#    define PKGMAN_STANDARD_XOPEN_1998 1
#  endif
#  if (_XOPEN_VERSION >= 600)
#    define PKGMAN_STANDARD_XOPEN_2003 1
#  endif
#  if (_XOPEN_VERSION >= 700)
#    define PKGMAN_STANDARD_XOPEN_2008 1
#  endif
#endif

/***************************************************************************//**
 *
 *  ... Inherited variable macros
 *
 ******************************************************************************/

#if defined(__clang__) && !defined(__ibxml__)

#  define PKGMAN_C_COMPILER_IS_CLANG 1

#  define PKGMAN_CLANG_VERSION_MAJOR __clang_major__
#  define PKGMAN_CLANG_VERSION_MINOR __clang_minor__
#  define PKGMAN_CLANG_VERSION_PATCH __clang_patchlevel__
#  define PKGMAN_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)

#  define PKGMAN_C_COMPILER_NAME __PM_STRING(Clang)
#  define PKGMAN_C_COMPILER_VERSION_MAJOR __clang_major__
#  define PKGMAN_C_COMPILER_VERSION_MINOR __clang_minor__
#  define PKGMAN_C_COMPILER_VERSION_PATCH __clang_patchlevel__

#endif

#if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__NVCOMPILER)

#  define PKGMAN_C_COMPILER_IS_GNU 1

#  define PKGMAN_GNU_VERSION_MAJOR __GNUC__
#  define PKGMAN_GNU_VERSION_MINOR __GNUC_MINOR__
#  define PKGMAN_GNU_VERSION_PATCH __GNUC_PATCHLEVEL__
#  define PKGMAN_GNU_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)

#  define PKGMAN_C_COMPILER_NAME __PM_STRING(GNU)
#  define PKGMAN_C_COMPILER_VERSION_MAJOR __GNUC__
#  define PKGMAN_C_COMPILER_VERSION_MINOR __GNUC_MINOR__
#  define PKGMAN_C_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__

#endif

#ifdef __ICL
#	define PKGMAN_ICC_VERSION __ICL
#elif defined(__INTEL_COMPILER)
#	define PKGMAN_ICC_VERSION __INTEL_COMPILER
#else
#	define PKGMAN_ICC_VERSION 0
#endif

#ifdef _MSC_VER
#	define PKGMAN_MSC_VERSION _MSC_VER
#	define PKGMAN_MSC_WARNING(...) __pragma(warning(__VA_ARGS__))
#else
#	define PKGMAN_MSC_VERSION 0
#	define PKGMAN_MSC_WARNING(...)
#endif

#define PKGMAN_C_COMPILER_VERSION (PKGMAN_C_COMPILER_VERSION_MAJOR * 100 + PKGMAN_C_COMPILER_VERSION_MINOR)
#define PKGMAN_C_COMPILER PKGMAN_C_COMPILER_NAME " " __PM_STRING(PKGMAN_C_COMPILER_VERSION_MAJOR) __PM_STRING(.) __PM_STRING(PKGMAN_C_COMPILER_VERSION_MINOR) __PM_STRING(.) __PM_STRING(PKGMAN_C_COMPILER_VERSION_PATCH)

#ifdef _MSVC_LANG
#	define PKGMAN_CPLUSPLUS _MSVC_LANG
#elif defined(__cplusplus)
#	define PKGMAN_CPLUSPLUS __cplusplus
#else
#	undef  PKGMAN_CPLUSPLUS
#endif

#ifdef __has_feature
#	define PKGMAN_HAS_FEATURE(x) __has_feature(x)
#else
#	define PKGMAN_HAS_FEATURE(x) 0
#endif

#if defined(__has_include) || PKGMAN_ICC_VERSION >= 1600 || PKGMAN_MSC_VERSION >= 1900
#	define PKGMAN_HAS_INCLUDE(x) __has_include(x)
#else
#	define PKGMAN_HAS_INCLUDE(x) 0
#endif

#ifdef __has_attribute
#	define PKGMAN_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#	define PKGMAN_HAS_ATTRIBUTE(x) 0
#endif

#ifdef __has_c_attribute
#	define PKGMAN_HAS_C_ATTRIBUTE(x) __has_c_attribute(x)
#else
#	define PKGMAN_HAS_C_ATTRIBUTE(x) 0
#endif

#ifdef __has_cpp_attribute
#	define PKGMAN_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#	define PKGMAN_HAS_CPP_ATTRIBUTE(x) 0
#endif

#ifdef __has_builtin
#	define PKGMAN_HAS_BUILTIN(x) __has_builtin(x)
#else
#	define PKGMAN_HAS_BUILTIN(x) 0
#endif

#ifdef __has_extension
#	define PKGMAN_HAS_EXTENSION(x) __has_extension(x)
#else
#	define PKGMAN_HAS_EXTENSION(x) 0
#endif

#if defined(_DEBUG)
#  define PKGMAN_DEBUG 1
#else
#  define PKGMAN_DEBUG 0
#endif

/**
 * @name PKGMAN_INTELLISENSE_GUARD
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
#define PKGMAN_INTELLISENSE_GUARD __INTELLISENSE__

/**
 * #if !(PKGMAN_INTELLISENSE_GUARD)
 * #cmakedefine PKGMAN_CONFIGURED @CMAKE_C_COMPILER_WORKS@
 * #endif
*/

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
#ifdef PKGMAN_CPLUSPLUS
#  if PKGMAN_HAS_INCLUDE(<cstdlib>)
#    include <cstdlib>
#    define HAVE_CSTDLIB 1
#  else
#    undef HAVE_CSTDLIB
#  endif
#else
#  if (PKGMAN_HAS_INCLUDE(<stdlib.h>))
#    include <stdlib.h>
#    define HAVE_STDLIB_H 1
#  else
#    undef HAVE_STDLIB_H
#  endif
#endif
#if !defined(HAVE_CSTDLIB) && !defined(HAVE_STDLIB_H)
#  error "Cannot find C stdlib!"
#endif

/** STDIO */
#ifdef PKGMAN_CPLUSPLUS
#  if PKGMAN_HAS_INCLUDE(<cstdio>)
#    include <cstdio>
#    define HAVE_CSTDIO 1
#  else
#    undef HAVE_CSTDIO
#  endif
#else
#  if PKGMAN_HAS_INCLUDE(<stdio.h>)
#    include <stdio.h>
#    define HAVE_STDIO_H 1
#  else
#    undef HAVE_STDIO_H
#  endif
#endif
#if !defined(HAVE_CSTDIO) && !defined(HAVE_STDIO_H)
#  error "Cannot find 'stdio.h'!"
#endif


/** STDINT */
#ifdef PKGMAN_CPLUSPLUS
#  if PKGMAN_HAS_INCLUDE(<cstdint>)
#    include <cstdint>
#    define HAVE_CSTDINT 1
#  else
#    undef HAVE_CSTDINT
#  endif
#else
#  if PKGMAN_HAS_INCLUDE(<stdint.h>)
#    include <stdint.h>
#    define HAVE_STDINT_H 1
#  endif
#endif
#if !defined(HAVE_CSTDINT) && !defined(HAVE_STDINT_H)
#  error "Cannot find 'stdint.h'!"
#endif

/** STDDEF */
#ifdef PKGMAN_CPLUSPLUS
#  if PKGMAN_HAS_INCLUDE(<cstddef>)
#    include <cstddef>
#    define HAVE_CSTDDEF 1
#  else
#    undef HAVE_CSTDDEF
#  endif
#else
#  if PKGMAN_HAS_INCLUDE(<stddef.h>)
#    include <stddef.h>
#    define HAVE_STDDEF_H 1
#  else
#    undef HAVE_STDDEF_H
#  endif
#endif
#if !defined(HAVE_CSTDDEF) && !defined(HAVE_STDDEF_H)
#  error "Cannot find 'stddef.h'!"
#endif

/**
 * #ifdef PKGMAN_CPLUSPLUS
 * #  if PKGMAN_HAS_INCLUDE(<cerrno>)
 * #    include <cerrno>
 * #    define HAVE_CERRNO 1
 * #  elif (PKGMAN_HAS_INCLUDE("cerrno"))
 * #    include "cerrno"
 * #    define HAVE_CERRNO 1
 * #  else
 * #    undef HAVE_CERRNO
 * #  endif
 * #else
 * #  if PKGMAN_HAS_INCLUDE(<errno.h>)
 * #    include <errno.h>
 * #    define HAVE_ERRNO_H 1
 * #  elif PKGMAN_HAS_INCLUDE("errno.h")
 * #    include "errno.h"
 * #    define HAVE_ERRNO_H 1
 * #  else
 * #    undef HAVE_ERRNO_H
 * #  endif
 * #endif
 * #if !defined(HAVE_CERRNO) && !defined(HAVE_ERRNO_H)
 * #  error "Cannot find 'errno.h'!"
 * #endif
 *
*/

/** WCHAR - fwprintf(), swprintf(), wprintf() */
#ifdef PKGMAN_CPLUSPLUS
#  if PKGMAN_HAS_INCLUDE(<cwchar>)
#    include <cwchar>
#    define HAVE_CWCHAR 1
#  else
#    undef HAVE_CWCHAR
#  endif
#else
#  if PKGMAN_HAS_INCLUDE(<wchar.h>)
#    include <wchar.h>
#    define HAVE_WCHAR_H 1
#  else
#    undef HAVE_WCHAR_H
#  endif
#endif
#if !defined(HAVE_CWCHAR) && !defined(HAVE_WCHAR_H)
#  error "Cannot find 'wchar.h'!"
#endif

/** Check <sys/headers.h> */
#if (PKGMAN_HAS_INCLUDE(<sys/mnttab.h>))
#  include <sys/mnttab.h>
#  define HAVE_SYS_MNTTAB_H 1
#endif
#if (PKGMAN_HAS_INCLUDE(<sys/mount.h>))
#  include <sys/mount.h>
#  define HAVE_SYS_MOUNT_H 1
#endif
#if (PKGMAN_HAS_INCLUDE(<sys/param.h>))
#  include <sys/param.h>
#  define HAVE_SYS_PARAM_H 1
#endif
#if (PKGMAN_HAS_INCLUDE(<sys/resource.h>))
#  include <sys/resource.h>
#  define HAVE_SYS_RESOURCE_H 1
#endif
#if (PKGMAN_HAS_INCLUDE(<sys/stat.h>))
#  include <sys/stat.h>
#  define HAVE_SYS_STAT_H 1
#endif
#if (PKGMAN_HAS_INCLUDE(<sys/statfs.h>))
#  include <sys/statfs.h>
#  define HAVE_SYS_STATFS_H 1
#endif
#if (PKGMAN_HAS_INCLUDE(<sys/statvfs.h>))
#  include <sys/statvfs.h>
#  define HAVE_SYS_STATVFS_H 1
#endif
#if (PKGMAN_HAS_INCLUDE(<sys/types.h>))
#  include <sys/types.h>
#  define HAVE_SYS_TYPES_H 1
#endif
#if (PKGMAN_HAS_INCLUDE(<sys/time.h>))
#  include <sys/time.h>
#  define HAVE_SYS_TIME_H 1
#endif
#if (PKGMAN_HAS_INCLUDE(<sys/ucred.h>))
#  include <sys/ucred.h>
#  define HAVE_SYS_UCRED_H 1
#endif

/** Additional headers... */
#if PKGMAN_HAS_INCLUDE(<termios.h>)
#    include <termios.h>
#    define HAVE_TERMIOS_H 1
#endif
#if PKGMAN_HAS_INCLUDE(<mntent.h>)
#    include <mntent.h>
#    define HAVE_MNTENT_H 1
#endif

#if (PKGMAN_PLATFORM_IS_UNIX)
#  if PKGMAN_HAS_INCLUDE(<unistd.h>)
#    include <unistd.h>
#    define HAVE_UNISTD_H 1
#  else
#    error "Error! Unix platform in use, but cannot locate standard Unix header <unistd.h>?"
#  endif
#endif


/***************************************************************************//**
 *
 *  ... Dependency check macros
 *
 ******************************************************************************/

#if PKGMAN_HAS_INCLUDE(<curl/curl.h>)
#  include <curl/curl.h>
#  define HAVE_CURL_CURL_H 1
#endif

#if   (HAVE_CURL_CURL_H)
#  define CURL_H_PATH __PM_STRING(C:/msys64/usr/include/curl)
#  if (PKGMAN_PLATFORM_IS_MSYS)
#    define LIBCURL_LIB __PM_STRING(msys-curl-4.dll)
#  else
#    define LIBCURL_LIB __PM_STRING(libcurl-4.dll)
#  endif
#endif

#if PKGMAN_HAS_INCLUDE(<gpgme.h>)
#  include <gpgme.h>
#  define HAVE_GPGME_H 1
#endif

#if   (HAVE_GPGME_H)
#  define GPGME_H_PATH __PM_STRING(C:/msys64/usr/include/gpgme++)
#  if (PKGMAN_PLATFORM_IS_MSYS)
#    define LIBGPGME_LIB __PM_STRING(msys-gpgme-11.dll)
#  else
#    define LIBGPGME_LIB __PM_STRING(libgpgme-11.dll)
#  endif
#endif

/**
 * #if PKGMAN_HAS_INCLUDE(<openssl/crypto.h>)
 * #  include <openssl/crypto.h>
 * #  define OPENSSL_FOUND 1
 * #  define PKGMAN_CRYPTO_LIB __PM_STRING(libcrypto.dll)
 * #endif
*/

#if   (HAVE_LIBNETTLE)
#  define CRYPTO_INCLUDE_SYMBOL __PM_STRING(<nettle/crypto.h>)
#elif (HAVE_LIBSSL)
#  define CRYPTO_INCLUDE_SYMBOL __PM_STRING(<openssl/crypto.h>)
#endif

#if   (HAVE_LIBSSL)
#  define CRYPTO_H_PATH __PM_STRING(C:/msys64/usr/include/openssl)
#elif (HAVE_LIBNETTLE)
#  define CRYPTO_H_PATH __PM_STRING(C:/msys64/usr/include/nettle)
#endif

#if (PKGMAN_PLATFORM_IS_MSYS)
#  define CRYPTO_LIB __PM_STRING(msys-crypto-3.dll)
#else
#  define CRYPTO_LIB __PM_STRING(libcrypto.dll)
#endif

/***************************************************************************//**
 *
 *  ... Function check macros
 *
 * getmntent(),
 * getmntinfo(),
 * strndup(),
 * strnlen(),
 * strsep(),
 * swprintf(),
 * tcflush(),
 *
 * Naturally, we should not only rely on checking for builtin versions...
 * But there dones't seem to be a widely-supported way to check the whole
 * include path without a compile run.
 * More work needed :)
 ******************************************************************************/

#if PKGMAN_HAS_BUILTIN(__builtin_getmntent)
#	define HAVE_GETMNTENT 1
#endif

#if PKGMAN_HAS_BUILTIN(__builtin_getmntinfo)
#	define HAVE_GETMNTINFO 1
#endif

#if PKGMAN_HAS_BUILTIN(__builtin_strndup)
#	define HAVE_STRNDUP 1
#endif

#if PKGMAN_HAS_BUILTIN(__builtin_strnlen)
#	define HAVE_STRNLEN 1
#endif

#if PKGMAN_HAS_BUILTIN(__builtin_strsep)
#	define HAVE_STRSEP 1
#endif

#if PKGMAN_HAS_BUILTIN(__builtin_swprintf)
#	define HAVE_SWPRINTF 1
#endif

#if PKGMAN_HAS_BUILTIN(__builtin_tcflush)
#	define HAVE_TCFLUSH 1
#endif

/***************************************************************************//**
 *
 *  ... Required type definitions
 *
 *     # type       # program prefix              # fallback
 * ['mode_t',   '''#include <sys/types.h>''', 'unsigned int'],
 * ['uid_t',    '''#include <sys/types.h>''', 'unsigned int'],
 * ['off_t',    '''#include <sys/types.h>''', 'signed int'],
 * ['pid_t',    '''#include <sys/types.h>''', 'signed int'],
 * ['size_t',   '''#include <sys/types.h>''', 'unsigned int'],
 * ['ssize_t',  '''#include <sys/types.h>''', 'signed int'],
 * ['int64_t',  '''#include <stdint.h>''',    'signed long int'],
 *
 ******************************************************************************/
#if (PKGMAN_PLATFORM_IS_MSYS)

  #if !defined(_MODE_T_DECLARED)
  #  define	_MODE_T_REQUIRED
  #endif

  #if !defined(_UID_T_DECLARED)
  #  define _UID_T_REQUIRED
  #endif

  #if !defined(_OFF_T_DECLARED)
  #  define _OFF_T_REQUIRED
  #endif

  #if !defined(_PID_T_DECLARED)
  #  define _PID_T_REQUIRED
  #endif

  #if !defined(_SIZE_T_DECLARED)
  #  define _SIZE_T_REQUIRED
  #endif

  #if !defined(_SSIZE_T_DECLARED)
  #  define _SSIZE_T_REQUIRED
  #endif

  #if !defined(_INT64_T_DECLARED)
  #  define _INT64_T_REQUIRED
  #endif

#else /** !(PKGMAN_PLATFORM_IS_MSYS) */

  #if !defined(_MODE_T_)
  #  define	_MODE_T_REQUIRED
  #endif

  #if !defined(_UID_T_)
  #  define _UID_T_REQUIRED
  #endif

  #if !defined(_OFF_T_)
  #  define _OFF_T_REQUIRED
  #endif

  #if !defined(_PID_T_)
  #  define _PID_T_REQUIRED
  #endif

  #if !defined(_SIZE_T_DEFINED)
  #  define _SIZE_T_REQUIRED
  #endif

  #if !defined(_SSIZE_T_DEFINED)
  #  define _SSIZE_T_REQUIRED
  #endif

  #if !defined(__int64)
  #  define _INT64_T_REQUIRED
  #endif

#endif


/***************************************************************************//**
 *
 *  ... Path macros
 *
 ******************************************************************************/

#if !defined(PATH_SEPERATOR)
#  if defined(PKGMAN_PLATFORM_IS_WINDOWS)
#    define PATH_SEPERATOR __PM_STRING(\\) /** @name PATH_SEPERATOR @details This quote keeps the code intact :) */
#  elif defined(PKGMAN_PLATFORM_IS_UNIX)
#    define PATH_SEPERATOR __PM_STRING(/) /** @name PATH_SEPERATOR @details This quote keeps the code intact :) */
#  endif
#endif

#if !defined(STRING_SEPERATOR)
#  if defined(PKGMAN_PLATFORM_IS_WINDOWS)
#    define STRING_SEPERATOR __PM_STRING(;) /** @name STRING_SEPERATOR @details This quote keeps the code intact :) */
#  elif defined(PKGMAN_PLATFORM_IS_UNIX)
#    define STRING_SEPERATOR __PM_STRING(:) /** @name STRING_SEPERATOR @details This quote keeps the code intact :) */
#  endif
#endif

/** Not quite there yet... */
#define ___JOIN_PATHS(A, SEP, B) A ##SEP ##B
#define __JOIN_PATHS(A, SEP, B) ___JOIN_PATHS(A, SEP, B)
#define JOIN_PATHS(A, B) __JOIN_PATHS(A, PATH_SEPERATOR, B)

#if !defined(HOMEDRIVE)
#  if defined(WIN32) || defined(_WIN32) || defined(MINGW)
#    define HOMEDRIVE __PM_STRING(C:) /** @name HOMEDRIVE @details This quote keeps the code intact :) */
#  else
#    define HOMEDRIVE PATH_SEPERATOR /** @name HOMEDRIVE @details This quote keeps the code intact :) */
#  endif
#endif

#if !defined(ROOTDIR)
#  if defined(WIN32) || defined(_WIN32) || defined(MINGW)
#    define ROOTDIR HOMEDRIVE PATH_SEPERATOR /** @name ROOTDIR @brief The location of the root operating directory (default value for Win32/MinGW). */
#  else
#    define ROOTDIR HOMEDRIVE /** < @name ROOTDIR @brief The location of the root operating directory (default value for *nix). */
#  endif
#endif

#if !defined(SYSROOT)
#  if defined(WIN32) || defined(_WIN32) || defined(MINGW)
#    define SYSROOT HOMEDRIVE PATH_SEPERATOR __PM_STRING(msys64) PATH_SEPERATOR __PM_STRING(etc)
#  else
#    define SYSROOT HOMEDRIVE
#  endif
#endif

#if !defined(PREFIX)
#  if defined(WIN32) || defined(_WIN32) || defined(MINGW)
#    define PREFIX HOMEDRIVE PATH_SEPERATOR __PM_STRING(msys64) PATH_SEPERATOR __PM_STRING(usr) /** (default value for Win32/MinGW). */
#  else
#    define PREFIX SYSROOT __PM_STRING(usr) /**  */
#  endif
#endif

#if !defined(SYSCONFDIR)
#  if defined(WIN32) || defined(_WIN32) || defined(MINGW)
#    define SYSCONFDIR HOMEDRIVE PATH_SEPERATOR __PM_STRING(msys64) PATH_SEPERATOR __PM_STRING(etc)
#  else
#    define SYSCONFDIR HOMEDRIVE __PM_STRING(etc)
#  endif
#endif

#if !defined(LOCALSTATEDIR)
#  if defined(WIN32) || defined(_WIN32) || defined(MINGW)
#    define LOCALSTATEDIR HOMEDRIVE PATH_SEPERATOR __PM_STRING(msys64) PATH_SEPERATOR __PM_STRING(var) /** (default value for Win32/MinGW). */
#  else
#    define LOCALSTATEDIR HOMEDRIVE __PM_STRING(var) /** < */
#  endif
#endif

/***************************************************************************//**
 *
 *  ... Other optional macros
 *
 ******************************************************************************/

#define LIB_VERSION __PM_STRING(13.0.2)

#define PACKAGE _PM_STRING(pkgman)

#if !defined(PACKAGE_VERSION)
#  define PACKAGE_VERSION __PM_STRING(PKGMAN_VERSION_MAJOR) __PM_STRING(.) __PM_STRING(PKGMAN_VERSION_MINOR) __PM_STRING(.) __PM_STRING(PKGMAN_VERSION_PATCH)
#endif

#if !defined(EXEC_PREFIX)
#  define EXEC_PREFIX PREFIX
#endif

#if !defined(BINDIR)
#  define BINDIR EXEC_PREFIX PATH_SEPERATOR __PM_STRING(bin)
#endif

#if !defined(SBINDIR)
#  define SBINDIR EXEC_PREFIX PATH_SEPERATOR __PM_STRING(sbin)
#endif

#if !defined(LIBDIR)
#  define LIBDIR EXEC_PREFIX PATH_SEPERATOR __PM_STRING(lib)
#endif

#if !defined(LIBEXECDIR)
#  define LIBEXECDIR EXEC_PREFIX PATH_SEPERATOR __PM_STRING(libexec)
#endif

#if !defined(DATAROOTDIR)
#  define DATAROOTDIR PREFIX PATH_SEPERATOR __PM_STRING(share)
#endif

#if !defined(DATADIR)
#  define DATADIR DATAROOTDIR
#endif

#if !defined(DOCDIR)
#  define DOCDIR DATAROOTDIR PATH_SEPERATOR __PM_STRING(info)
#endif

#if !defined(INFODIR)
#  define INFODIR DATAROOTDIR PATH_SEPERATOR __PM_STRING(info)
#endif

#if !defined(LOCALEDIR)
#  define LOCALEDIR DATAROOTDIR PATH_SEPERATOR __PM_STRING(locale)
#endif

#if !defined(MANDIR)
#  define MANDIR DATAROOTDIR PATH_SEPERATOR __PM_STRING(doc) PATH_SEPERATOR __PM_STRING(pkgman)
#endif

#if !defined(RUNSTATEDIR)
#  define RUNSTATEDIR LOCALSTATEDIR PATH_SEPERATOR __PM_STRING(run)
#endif

#if !defined(LDCONFIG)
#  define LDCONFIG SBINDIR PATH_SEPERATOR __PM_STRING(ldconfig)
#endif

#if !defined(SCRIPTLET_SHELL)
#  define SCRIPTLET_SHELL BINDIR PATH_SEPERATOR __PM_STRING(sh)
#endif

#if !defined(BUILDSCRIPT)
#  define BUILDSCRIPT __PM_STRING(PKGBUILD)
#endif

#if !defined(LIBMAKEPKGDIR)
#  define LIBMAKEPKGDIR DATAROOTDIR PATH_SEPERATOR __PM_STRING(makepkg)
#endif

#if !defined(SYSHOOKDIR)
#  define SYSHOOKDIR DATAROOTDIR PATH_SEPERATOR __PM_STRING(libalpm) PATH_SEPERATOR __PM_STRING(hooks) PATH_SEPERATOR
#endif

#if !defined(CONFFILE)
#  define CONFFILE SYSCONFDIR PATH_SEPERATOR __PM_STRING(pkgman.conf)
#endif

#if !defined(DBPATH)
#  define DBPATH LOCALSTATEDIR PATH_SEPERATOR __PM_STRING(lib) PATH_SEPERATOR __PM_STRING(pkgman) PATH_SEPERATOR
#endif

#if !defined(GPGDIR)
#  define GPGDIR SYSCONFDIR PATH_SEPERATOR __PM_STRING(pacman.d) PATH_SEPERATOR __PM_STRING(gnupg) PATH_SEPERATOR
#endif

#if !defined(CACHEDIR)
#  define CACHEDIR LOCALSTATEDIR PATH_SEPERATOR __PM_STRING(cache) PATH_SEPERATOR __PM_STRING(pacman) PATH_SEPERATOR __PM_STRING(pkg) PATH_SEPERATOR
#endif

#if !defined(LOGFILE)
#  define LOGFILE LOCALSTATEDIR PATH_SEPERATOR __PM_STRING(log) PATH_SEPERATOR __PM_STRING(pkgman.log)
#endif

#if !defined(HOOKDIR)
#  define HOOKDIR SYSCONFDIR PATH_SEPERATOR __PM_STRING(pacman.d) PATH_SEPERATOR __PM_STRING(hooks) PATH_SEPERATOR
#endif

#if !defined(MAKEPKG_TEMPLATE_DIR)
#  define MAKEPKG_TEMPLATE_DIR DATAROOTDIR PATH_SEPERATOR __PM_STRING(makepkg-template)
#endif

#if !defined(PKGDATADIR)
#  define PKGDATADIR DATAROOTDIR PATH_SEPERATOR __PM_STRING(pkgman)
#endif

#if !defined(PKGEXT)
#  define PKGEXT __PM_STRING(.) __PM_STRING(pkg) __PM_STRING(.) __PM_STRING(tar) __PM_STRING(.) __PM_STRING(gz)
#endif

#if !defined(SRCEXT)
#  define SRCEXT __PM_STRING(.) __PM_STRING(src) __PM_STRING(.) __PM_STRING(tar) __PM_STRING(.) __PM_STRING(gz)
#endif

/***************************************************************************//**
 *
 *  ... MSYS installation macros
 *
 ******************************************************************************/

#ifndef MSYS_INSTALL_PATH
#  if (PKGMAN_PLATFORM_IS_CYGWIN)
#    define MSYS_INSTALL_PATH SYSROOT
#  else /** !(PKGMAN_PLATFORM_IS_CYGWIN) */
#    define MSYS_INSTALL_PATH HOMEDRIVE PATH_SEPERATOR __PM_STRING(msys64)
#  endif
#endif

#ifndef MSYS_LIB
#  define MSYS_LIB __PM_STRING(msys-2.0.dll)
#endif

/***************************************************************************//**
 *
 *  ... Downstream required macros
 *
 ******************************************************************************/

#if defined(HAVE_STRUCT_STATVFS_F_FLAG)
#	define FSSTATSTYPE struct statvfs
#elif defined(HAVE_STRUCT_STATFS_F_FLAGS)
#	define FSSTATSTYPE struct statfs
#endif

/***************************************************************************//**
 *
 *  ... Propagation
 *
 ******************************************************************************/

#ifdef PKGMAN_CPLUSPLUS
extern "C" {
#endif

#if defined(PKGMAN_WIN32_SHARED)
#if defined(PKGMAN_WIN32_EXPORTS)
#   define PKGMAN_EXPORT __declspec(dllexport)
#else
#   define PKGMAN_EXPORT __declspec(dllimport)
#endif
#else
#   define PKGMAN_EXPORT
#endif

#if defined(_MODE_T_REQUIRED)
#  define	_MODE_T_
typedef	unsigned int mode_t; /* permissions */
#  define _MODE_T_DECLARED
#  define _MODE_T_DEFINED
#  undef  _MODE_T_REQUIRED
#endif

#if defined(_UID_T_REQUIRED)
#  define _UID_T_
typedef	unsigned int uid_t; /* user id */
#  define _UID_T_DECLARED
#  define _UID_T_DEFINED
#  undef  _UID_T_REQUIRED
#endif

#if defined(_OFF_T_REQUIRED)
#  define _OFF_T_
typedef	signed int off_t; /* file offset */
#  define _OFF_T_DECLARED
#  define _OFF_T_DEFINED
#  undef  _OFF_T_REQUIRED
#endif

#if defined(_PID_T_REQUIRED)
#  define _PID_T_
typedef	signed int pid_t; /* process id */
#  define PKGMAN_MODE_T mode_t
#  define _PID_T_DECLARED
#  define _PID_T_DEFINED
#  undef  _PID_T_REQUIRED
#endif

#if defined(_SIZE_T_REQUIRED)
#  define _SIZE_T_
typedef unsigned int size_t; /** size_t type */
#  define PKGMAN_SIZE_T size_t
#  define _SIZE_T_DECLARED
#  define _SIZE_T_DEFINED
#  undef  _SIZE_T_REQUIRED
#endif

#if defined(_SSIZE_T_REQUIRED)
#  define _SSIZE_T_
typedef signed int ssize_t; /** Signed size_t type */
#  define PKGMAN_SSIZE_T ssize_t
#  define _SSIZE_T_DECLARED
#  define _SSIZE_T_DEFINED
#  undef  _SSIZE_T_REQUIRED
#endif

#if defined(_INT64_T_REQUIRED)
#  define _INT64_T_
typedef	signed long int int64_t;
#  define PKGMAN_INT64_T int64_t
#  define _INT64_T_DECLARED
#  define _INT64_T_DEFINED
#  define __int64
#  undef  _INT64_T_REQUIRED
#endif

#define PKGMAN_MODE_T mode_t
#define PKGMAN_UID_T uid_t
#define PKGMAN_OFF_T off_t
#define PKGMAN_PID_T pid_t
#define PKGMAN_SIZE_T size_t
#define PKGMAN_SSIZE_T ssize_t
#define PKGMAN_INT64_T int64_t

/**
 * @name dec
 * @brief Convert integer to decimal digit literals.
 *
 * double 	pkgman_dec(int n) { return DEC(n); };
 */

/**
 * @name hex
 * @brief Convert integer to hex digit literals.
 *
 * int 	pkgman_hex(int n){ return HEX(n); };
 */


#ifndef HAVE_STRSEP
	/**
	 * @brief Replacement function for strsep()
	 * @link https://stackoverflow.com/questions/58244300/getting-the-error-undefined-reference-to-strsep-with-clang-and-mingw
	 * @param stringp
	 * @param delim
	 * @return char*
	 */
	char *strsep(char **stringp, const char *delim)
	{
		char *rv = *stringp;
		if (rv)
		{
			*stringp += strcspn(*stringp, delim);
			if (**stringp)
				*(*stringp)++ = '\0';
			else
				*stringp = 0;
		}
		return rv;
	}
#  define HAVE_STRSEP 1
#endif

#ifndef HAVE_STRNDUP
	/** Copies a string.
	* Returned string needs to be freed
	* @param s string to be copied
	* @param n maximum number of characters to copy
	* @return pointer to the new string on success, NULL on error
	*/
	char *strndup(const char *s, size_t n)
	{
		size_t len = strnlen(s, n);
		char *new = (char *) malloc(len + 1);

		if(new == NULL)
		{
			return NULL;
		}

		new[len] = '\0';
		return (char *)memcpy(new, s, len);
	}
#  define HAVE_STRNDUP 1
#endif

/**
 * TODO: @StoneyDSP With all this char array macro-string business, everything
 * is fine when relying on these internal definitions. However, if we open the
 * macro definitions to the possibility of command-line instruction, which
 * would be very ideal, then the definitions recieved from the command line
 * ALSO need to be parsed into some 'stringified' format, UNLESS we save
 * the 'stringification' until the assignment to char array. But in this
 * approach, we end up stringifying the macro itself, instead of it's contents!
 *
 * Tricky...
 */

/**
 * command-line options
 * PREFIX = get_option('prefix')
 * DATAROOTDIR = join_paths(PREFIX, get_option('datarootdir'))
 * SYSCONFDIR = join_paths(PREFIX, get_option('sysconfdir'))
 * LOCALSTATEDIR = join_paths(PREFIX, get_option('localstatedir'))
 * LOCALEDIR = join_paths(PREFIX, get_option('localedir'))
 * ROOTDIR = get_option('root-dir')
 * BINDIR = join_paths(PREFIX, get_option('bindir'))
 * MANDIR = join_paths(PREFIX, get_option('mandir'))
 * BUILDSCRIPT = get_option('buildscript')
 * LIBMAKEPKGDIR = join_paths(PREFIX, DATAROOTDIR, 'makepkg')
 * PKGDATADIR = join_paths(PREFIX, DATAROOTDIR, meson.project_name())
 */
struct pkgman_command_line
{
	const char* prefix; 														/** PREFIX = get_option('prefix') */
	const char* datarootdir; 													/** DATAROOTDIR = join_paths(PREFIX, get_option('datarootdir')) */
	const char* sysconfdir; 													/** SYSCONFDIR = join_paths(PREFIX, get_option('sysconfdir')) */
	const char* localstatedir; 													/** LOCALSTATEDIR = join_paths(PREFIX, get_option('localstatedir')) */
	const char* localedir; 														/** LOCALEDIR = join_paths(PREFIX, get_option('localedir')) */
	const char* rootdir; 														/** ROOTDIR = get_option('root-dir') */
	const char* bindir; 														/** BINDIR = join_paths(PREFIX, get_option('bindir')) */
	const char* mandir; 														/** MANDIR = join_paths(PREFIX, get_option('mandir')) */
	const char* buildscript; 													/** BUILDSCRIPT = get_option('buildscript') */
	const char* libmakepkgdir; 													/** LIBMAKEPKGDIR = join_paths(PREFIX, DATAROOTDIR, 'makepkg') */
	const char* pkgdatadir; 													/** PKGDATADIR = join_paths(PREFIX, DATAROOTDIR, meson.project_name()) */

} PkgmanCommandLine = {
		.bindir = BINDIR,
		.buildscript = BUILDSCRIPT,
		.datarootdir = DATAROOTDIR,
		.libmakepkgdir = LIBMAKEPKGDIR,
		.localedir = LOCALEDIR,
		.localstatedir = LOCALSTATEDIR,
		.mandir = MANDIR,
		.pkgdatadir = PKGDATADIR,
		.prefix = PREFIX,
		.rootdir = ROOTDIR,
		.sysconfdir = SYSCONFDIR

	}, *PkgmanGetCommandLine = &PkgmanCommandLine;

struct pkgman_settings
{
	const char* pkgman_version;
	const char* pkgman_c_compiler;

	const char* msysLib;
	const char* msys_install_path;

	const char* path_seperator;
	const char* string_seperator;
	const char* homedrive;

	const char* sysroot;
	const char* sbindir;
	const char* makepkg_template_dir;

	const char* pkg_ext;
	const char* src_ext;
} PkgmanSettings = {
	.homedrive = HOMEDRIVE,
	.makepkg_template_dir = MAKEPKG_TEMPLATE_DIR,
	.msys_install_path = MSYS_INSTALL_PATH,
	.msysLib = MSYS_LIB,
	.path_seperator = PATH_SEPERATOR,
	.pkg_ext = PKGEXT,
	.src_ext = SRCEXT,
	.pkgman_c_compiler = PKGMAN_C_COMPILER,
	.pkgman_version = PACKAGE_VERSION,
	.sbindir = SBINDIR,
	.string_seperator = STRING_SEPERATOR,
	.sysroot = SYSROOT

}, *PkgmanGetSettings = &PkgmanSettings;

/**
 * conf = configuration_data()
 * conf.set_quoted('LOCALEDIR', LOCALEDIR)
 * conf.set_quoted('SCRIPTLET_SHELL', get_option('scriptlet-shell'))
 * conf.set_quoted('LDCONFIG', LDCONFIG)
 * conf.set_quoted('SYSHOOKDIR', join_paths(DATAROOTDIR, 'libalpm/hooks/'))
 * conf.set_quoted('CONFFILE', join_paths(SYSCONFDIR, 'pacman.conf'))
 * conf.set_quoted('DBPATH', join_paths(LOCALSTATEDIR, 'lib/pacman/'))
 * conf.set_quoted('GPGDIR', join_paths(SYSCONFDIR, 'pacman.d/gnupg/'))
 * conf.set_quoted('LOGFILE', join_paths(LOCALSTATEDIR, 'log/pacman.log'))
 * conf.set_quoted('CACHEDIR', join_paths(LOCALSTATEDIR, 'cache/pacman/pkg/'))
 * conf.set_quoted('HOOKDIR', join_paths(SYSCONFDIR, 'pacman.d/hooks/'))
 * conf.set_quoted('ROOTDIR', ROOTDIR)
 */
struct pkgman_conf
{
	int gnu_source; 															/** conf.set('_GNU_SOURCE', true) */
	char package [FILENAME_MAX]; 														/** conf.set_quoted('PACKAGE',  meson.project_name()) */
	char package_version [FILENAME_MAX];												/** conf.set_quoted('PACKAGE_VERSION', PACKAGE_VERSION) */
	char libalpm_version [FILENAME_MAX];												/** conf.set_quoted('LIB_VERSION', libalpm_version) */

	char scriptlet_shell				[PATH_MAX];
	char ldconfig						[PATH_MAX];

	char localedir						[PATH_MAX];
	char syshookdir						[PATH_MAX];
	char conffile						[PATH_MAX];
	char dbpath							[PATH_MAX];
	char gpgdir							[PATH_MAX];
	char logfile						[PATH_MAX];
	char cachedir						[PATH_MAX];
	char hookdir						[PATH_MAX];
	char rootdir						[PATH_MAX];

} PkgmanConf = {
	.cachedir = { CACHEDIR },
	.conffile = { CONFFILE },
	.dbpath = { DBPATH },
	.gnu_source = _GNU_SOURCE,
	.gpgdir = { GPGDIR },
	.hookdir = { HOOKDIR },
	.ldconfig = { LDCONFIG },
	.libalpm_version = { LIB_VERSION },
	.localedir = { LOCALEDIR },
	.logfile = { LOGFILE },
	.package = { __PM_STRING(pkgman) },
	.package_version = { PACKAGE_VERSION },
	.rootdir = { ROOTDIR },
	.scriptlet_shell = { SCRIPTLET_SHELL },
	.syshookdir = { SYSHOOKDIR }

}, *PkgmanGetConf = &PkgmanConf;

enum header_test_result
{
	HEADER_MISSING,
	HEADER_FOUND
};
/** Set flags for portability */
#if defined(HAVE_SYS_MNTTAB_H)
#  define PKGMAN_HAS_SYS_MNTTAB_H (enum header_test_result)HEADER_FOUND
#else
#  define PKGMAN_HAS_SYS_MNTTAB_H (enum header_test_result)HEADER_MISSING
#endif
#if defined(HAVE_SYS_MOUNT_H)
#  define PKGMAN_HAS_SYS_MOUNT_H (enum header_test_result)HEADER_FOUND
#else
#  define PKGMAN_HAS_SYS_MOUNT_H (enum header_test_result)HEADER_MISSING
#endif
#if defined(HAVE_SYS_PARAM_H)
#  define PKGMAN_HAS_SYS_PARAM_H (enum header_test_result)HEADER_FOUND
#else
#  define PKGMAN_HAS_SYS_PARAM_H (enum header_test_result)HEADER_MISSING
#endif
#if defined(HAVE_SYS_RESOURCE_H)
#  define PKGMAN_HAS_SYS_RESOURCE_H (enum header_test_result)HEADER_FOUND
#else
#  define PKGMAN_HAS_SYS_RESOURCE_H (enum header_test_result)HEADER_MISSING
#endif
#if defined(HAVE_SYS_STAT_H)
#  define PKGMAN_HAS_SYS_STAT_H (enum header_test_result)HEADER_FOUND
#else
#  define PKGMAN_HAS_SYS_STAT_H (enum header_test_result)HEADER_MISSING
#endif
#if defined(HAVE_SYS_STATFS_H)
#  define PKGMAN_HAS_SYS_STATFS_H (enum header_test_result)HEADER_FOUND
#else
#  define PKGMAN_HAS_SYS_STATFS_H (enum header_test_result)HEADER_MISSING
#endif
#if defined(HAVE_SYS_STATVFS_H)
#  define PKGMAN_HAS_SYS_STATVFS_H (enum header_test_result)HEADER_FOUND
#else
#  define PKGMAN_HAS_SYS_STATVFS_H (enum header_test_result)HEADER_MISSING
#endif
#if defined(HAVE_SYS_TYPES_H)
#  define PKGMAN_HAS_SYS_TYPES_H (enum header_test_result)HEADER_FOUND
#else
#  define PKGMAN_HAS_SYS_TYPES_H (enum header_test_result)HEADER_MISSING
#endif
#if defined(HAVE_SYS_TIME_H)
#  define PKGMAN_HAS_SYS_TIME_H (enum header_test_result)HEADER_FOUND
#else
#  define PKGMAN_HAS_SYS_TIME_H (enum header_test_result)HEADER_MISSING
#endif
#if defined(HAVE_SYS_UCRED_H)
#  define PKGMAN_HAS_SYS_UCRED_H (enum header_test_result)HEADER_FOUND
#else
#  define PKGMAN_HAS_SYS_UCRED_H (enum header_test_result)HEADER_MISSING
#endif
#if defined(HAVE_TERMIOS_H)
#  define PKGMAN_HAS_TERMIOS_H (enum header_test_result)HEADER_FOUND
#else
#  define PKGMAN_HAS_TERMIOS_H (enum header_test_result)HEADER_MISSING
#endif
#if defined(HAVE_MNTENT_H)
#  define PKGMAN_HAS_MNTENT_H (enum header_test_result)HEADER_FOUND
#else
#  define PKGMAN_HAS_MNTENT_H (enum header_test_result)HEADER_MISSING
#endif

/**
 * int have_mntent_h = 					{ PKGMAN_HAS_MNTENT_H };
 * int have_sys_mnttab_h = 				{ PKGMAN_HAS_SYS_MNTTAB_H };
 * int have_sys_mount_h = 				{ PKGMAN_HAS_SYS_MOUNT_H };
 * int have_sys_param_h = 				{ PKGMAN_HAS_SYS_PARAM_H };
 * int have_sys_resource_h = 			{ PKGMAN_HAS_SYS_RESOURCE_H };
 * int have_sys_stat_h = 				{ PKGMAN_HAS_SYS_STAT_H };
 * int have_sys_statfs_h = 				{ PKGMAN_HAS_SYS_STATFS_H };
 * int have_sys_statvfs_h = 			{ PKGMAN_HAS_SYS_STATVFS_H };
 * int have_sys_types_h = 				{ PKGMAN_HAS_SYS_TYPES_H };
 * int have_sys_time_h = 				{ PKGMAN_HAS_SYS_TIME_H };
 * int have_sys_ucred_h = 				{ PKGMAN_HAS_SYS_UCRED_H };
 * int have_termios_h = 				{ PKGMAN_HAS_TERMIOS_H };
 */
struct pkgman_required_headers
{
	enum header_test_result have_sys_mnt_tab_h; 								/** @returns int have_sys_mnttab_h = 	{ PKGMAN_HAS_SYS_MNTTAB_H }; */
	enum header_test_result have_sys_mount_h; 									/** int have_sys_mount_h; */
	enum header_test_result have_sys_param_h;
	enum header_test_result have_sys_resource_h;
	enum header_test_result have_sys_stat_h;
	enum header_test_result have_sys_statfs_h;
	enum header_test_result have_sys_statvfs_h;
	enum header_test_result have_sys_types_h;
	enum header_test_result have_sys_time_h;
	enum header_test_result have_sys_ucred_h;
	enum header_test_result have_termios_h; 									/** @returns int have_termios_h = 		{ PKGMAN_HAS_TERMIOS_H }; */
	enum header_test_result have_mntent_h; 									/** @returns int have_mntent_h = 		{ PKGMAN_HAS_MNTENT_H }; */

} PkgmanHeaders = {
	.have_mntent_h = PKGMAN_HAS_MNTENT_H,
	.have_sys_mnt_tab_h = PKGMAN_HAS_SYS_MNTTAB_H,
	.have_sys_mount_h = PKGMAN_HAS_SYS_MOUNT_H,
	.have_sys_param_h = PKGMAN_HAS_SYS_PARAM_H,
	.have_sys_resource_h = PKGMAN_HAS_SYS_RESOURCE_H,
	.have_sys_stat_h = PKGMAN_HAS_SYS_STAT_H,
	.have_sys_statfs_h = PKGMAN_HAS_SYS_STATFS_H,
	.have_sys_statvfs_h = PKGMAN_HAS_SYS_STATVFS_H,
	.have_sys_time_h = PKGMAN_HAS_SYS_TIME_H,
	.have_sys_types_h = PKGMAN_HAS_SYS_TYPES_H,
	.have_sys_ucred_h = PKGMAN_HAS_SYS_UCRED_H,
	.have_termios_h = PKGMAN_HAS_TERMIOS_H
};

enum symbol_test_result
{
	SYMBOL_MISSING,
	SYMBOL_FOUND
};

/** Symbols */

#if defined(HAVE_GETMNTENT)
#  define PKGMAN_HAS_GETMNTENT (enum symbol_test_result)SYMBOL_FOUND
#else
#  define PKGMAN_HAS_GETMNTENT (enum symbol_test_result)SYMBOL_MISSING
#endif

#if defined(HAVE_GETMNTINFO)
#  define PKGMAN_HAS_GETMNTINFO (enum symbol_test_result)SYMBOL_FOUND
#else
#  define PKGMAN_HAS_GETMNTINFO (enum symbol_test_result)SYMBOL_MISSING
#endif

#if defined(HAVE_STRNDUP)
#  define PKGMAN_HAS_STRNDUP (enum symbol_test_result)SYMBOL_FOUND
#else
#  define PKGMAN_HAS_STRNDUP (enum symbol_test_result)SYMBOL_MISSING
#endif

#if defined(HAVE_STRNLEN)
#  define PKGMAN_HAS_STRNLEN (enum symbol_test_result)SYMBOL_FOUND
#else
#  define PKGMAN_HAS_STRNLEN (enum symbol_test_result)SYMBOL_MISSING
#endif

#if defined(HAVE_STRSEP)
#  define PKGMAN_HAS_STRSEP (enum symbol_test_result)SYMBOL_FOUND
#else
#  define PKGMAN_HAS_STRSEP (enum symbol_test_result)SYMBOL_MISSING
#endif

#if defined(HAVE_SWPRINTF)
#  define PKGMAN_HAS_SWPRINTF (enum symbol_test_result)SYMBOL_FOUND
#else
#  define PKGMAN_HAS_SWPRINTF (enum symbol_test_result)SYMBOL_MISSING
#endif

#if defined(HAVE_TCFLUSH)
#  define PKGMAN_HAS_TCFLUSH (enum symbol_test_result)SYMBOL_FOUND
#else
#  define PKGMAN_HAS_TCFLUSH (enum symbol_test_result)SYMBOL_MISSING
#endif

struct pkgman_required_symbols
{
	enum symbol_test_result have_getmntent;
	enum symbol_test_result have_getmntinfo;
	enum symbol_test_result have_strndup;
	enum symbol_test_result have_strnlen;
	enum symbol_test_result have_strsep;
	enum symbol_test_result have_swprintf;
	enum symbol_test_result have_tcflush;

} PkgmanSymbols = {
	.have_getmntent = PKGMAN_HAS_GETMNTENT,
	.have_getmntinfo = PKGMAN_HAS_GETMNTINFO,
	.have_strndup = PKGMAN_HAS_STRNDUP,
	.have_strnlen = PKGMAN_HAS_STRNLEN,
	.have_strsep = PKGMAN_HAS_STRSEP,
	.have_swprintf = PKGMAN_HAS_SWPRINTF,
	.have_tcflush = PKGMAN_HAS_TCFLUSH
};

enum member_test_result
{
	MEMBER_MISSING,
	MEMBER_FOUND
};

struct pkgman_required_members
{
	enum member_test_result have_struct_stat_st_blksize;
	enum member_test_result have_struct_statvfs_f_flag;
	enum member_test_result have_struct_statfs_f_flags;

} PkgmanRequiredMembers;

enum type_test_result
{
	TYPE_MISSING,
	TYPE_FOUND
};

const char* pkgman_version = { PACKAGE_VERSION };
const char* msysLib = { MSYS_LIB };
const char* msys_install_path = { MSYS_INSTALL_PATH };

const char* path_seperator = { PATH_SEPERATOR };
const char* string_seperator = { STRING_SEPERATOR };
const char* homedrive = { HOMEDRIVE };
const char* rootdir = { ROOTDIR };

const char* prefix = { PREFIX };
const char* sysconfdir = { SYSCONFDIR };
const char* localstatedir = { LOCALSTATEDIR };
const char* datarootdir = { DATAROOTDIR };

const char* sysroot = { SYSROOT };
const char* bindir = { BINDIR };
const char* sbindir = { SBINDIR };

const char* syshookdir = { SYSHOOKDIR };
const char* conffile = { CONFFILE };
const char* database_dir = { DBPATH };
const char* gpgdir = { GPGDIR };
const char* cachedir = { CACHEDIR };
const char* logfile = { LOGFILE };
const char* hookdir = { HOOKDIR };

const char* libalpm_version = { LIB_VERSION };

const char* ldconfig = { LDCONFIG };
const char* buildscript = { BUILDSCRIPT };
const char* scriptlet_shell = { SCRIPTLET_SHELL };

const char* makepg_template_dir = { MAKEPKG_TEMPLATE_DIR };
const char* pkg_ext = { PKGEXT };
const char* src_ext = { SRCEXT };

const char* pkgman_c_compiler = { PKGMAN_C_COMPILER };

#if !(PKGMAN_INTELLISENSE_GUARD)

/**
 *
 * const char* datadir = DATADIR;
 * const char* includedir = INCLUDEDIR;
 * const char* infodir = INFODIR;
 * const char* libdir = LIBDIR;
 * const char* licensedir = LICENSEDIR;
 * const char* libexecdir = LIBEXECDIR;
 * const char* localedir = LOCALEDIR;
 * const char* mandir = MANDIR;
 * const char* sharedstatedir = SHAREDSTATEDIR;
 *
 * const char* syshookdir = SYSHOOKDIR;
 * const char* logfile = LOGFILE;
 * const char* hookdir = HOOKDIR;
*/
#endif /** !(PKGMAN_INTELLISENSE_GUARD) */


int checkForFile(const char* filename);
int checkForDir(const char* pathToDir);
int checkForLib(const char* libName);
/**
 * It is a good idea to declare the function signatures above even though they
 * can only be called in the source file which we don't plan to pass downstream.
 * They will be encapsulated within the 'extern "C" {}' keyword if a C++
 * compiler is invoked to build the source file.
 *
 * Don't forget that 'path' variables can be constructed using the platform-
 * dependent macros defined above :)
 */

#if defined(__18CXX)
#  define ID_VOID_MAIN
#endif
#if defined(__CLASSIC_C__)
/* cv-qualifiers did not exist in K&R C */
#  define const
#  define volatile
#endif

#if (__CYGWIN__)
#  if defined(ID_VOID_MAIN)
void WinMain();
#  else
#    if defined(__CLASSIC_C__)
int WinMain(argc, argv) int argc; char** argv;
#    else
int WinMain(int argc, char** argv);
#    endif
#  endif
#else
#  if defined(ID_VOID_MAIN)
void main();
#  else
#    if defined(__CLASSIC_C__)
int main(argc, argv) int argc; char** argv;
#    else
int main(int argc, char** argv);
#    endif /** __CLASSIC_C__ */
#  endif /** ID_VOID_MAIN */
#endif

#ifdef PKGMAN_CPLUSPLUS
}
#endif

#endif /** PM_CONFIGURATION_H */
