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
#define PKGMAN_VERSION_TWEAK
#define PKGMAN_VERSION PKGMAN_VERSION_MAJOR * 10000 + PKGMAN_VERSION_MINOR * 100 + PKGMAN_VERSION_PATCH

#define _GNU_SOURCE 1

#define __need_mode_t
#define __need_uid_t
#define __need_off_t
#define __need_pid_t
#define __need_size_t
#define __need_ssize_t
#define __need_int64_t

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
#if !defined(__to_string)
#	define __to_string(X) #X
#endif

#if !defined(__string)
#	define __string(X) __to_string(X)
#endif

#if !defined(__to_char)
#	define __to_char(X) #@X
#endif

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
#	define _C_STANDARD_ STRINGIFY(C18)
#elif	(__STDC_VERSION__ >= 201112L)
#	define _C_STANDARD_ STRINGIFY(C11)
#elif	(__STDC_VERSION__ >= 199901L)
#	define _C_STANDARD_ STRINGIFY(C99)
#elif	(__STDC_VERSION__ >= 199409L)
#	define _C_STANDARD_ STRINGIFY(C94)
#endif

#if defined(__STDC__)
# define PREDEF_STANDARD_C_1989
# if defined(__STDC_VERSION__)
#  if (__STDC_VERSION__ >= 199409L)
#   define PREDEF_STANDARD_C_1994
#  endif
#  if (__STDC_VERSION__ >= 199901L)
#   define PREDEF_STANDARD_C_1999
#  endif
# endif
#endif

/***************************************************************************//**
 *
 *  ... Inherited variable macros
 *
 ******************************************************************************/

#if defined(__clang__) && !defined(__ibxml__)
#	define PKGMAN_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)
#else
#	define PKGMAN_CLANG_VERSION 0
#endif

#if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__NVCOMPILER)
#	define PKGMAN_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#else
#	define PKGMAN_GCC_VERSION 0
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

#if !(PKGMAN_INTELLISENSE_GUARD)
#cmakedefine PKGMAN_CONFIGURED @CMAKE_C_COMPILER_WORKS@
#endif

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
#  if PKGMAN_HAS_INCLUDE(<stdlib.h>)
#    include <stdlib.h>
#    define HAVE_STDLIB_H 1
#  else
#    undef HAVE_STDLIB_H
#  endif
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

/** Check <sys/headers.h> */
#if PKGMAN_HAS_INCLUDE(<sys/mnttab.h>)
#    include <sys/mnttab.h>
#    define HAVE_SYS_MNTTAB_H 1
#endif
#if PKGMAN_HAS_INCLUDE(<sys/mount.h>)
#    include <sys/mount.h>
#    define HAVE_SYS_MOUNT_H 1
#endif
#if PKGMAN_HAS_INCLUDE(<sys/param.h>)
#    include <sys/param.h>
#    define HAVE_SYS_PARAM_H 1
#endif
#if PKGMAN_HAS_INCLUDE(<sys/stat.h>)
#    include <sys/stat.h>
#    define HAVE_SYS_STAT_H 1
#endif
#if PKGMAN_HAS_INCLUDE(<sys/statfs.h>)
#    include <sys/statfs.h>
#    define HAVE_SYS_STATFS_H 1
#endif
#if PKGMAN_HAS_INCLUDE(<sys/statvfs.h>)
#    include <sys/statvfs.h>
#    define HAVE_SYS_STATVFS_H 1
#endif
#if PKGMAN_HAS_INCLUDE(<sys/types.h>)
#    include <sys/types.h>
#    define HAVE_SYS_TYPES_H 1
#endif
#if PKGMAN_HAS_INCLUDE(<sys/ucred.h>)
#    include <sys/ucred.h>
#    define HAVE_SYS_UCRED_H 1
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

/***************************************************************************//**
 *
 *  ... Dependency check macros
 *
 ******************************************************************************/

#ifdef __CYGWIN__
#  include <dlfcn.h>
#  include <cygwin/version.h>
#endif

#if PKGMAN_HAS_INCLUDE(<curl/curl.h>)
#  include <curl/curl.h>
#  define CURL_FOUND 1
#  define HAVE_LIBCURL 1
#endif

#if PKGMAN_HAS_INCLUDE(<openssl/crypto.h>)
#  include <openssl/crypto.h>
#  define OPENSSL_FOUND 1
#  define HAVE_OPENSSL 1
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

#ifndef _MODE_T_DECLARED
typedef	unsigned int mode_t; /* permissions */
#define _MODE_T_DECLARED
#endif

#ifndef _UID_T_DECLARED
typedef	unsigned int uid_t; /* user id */
#define _UID_T_DECLARED
#endif

#ifndef _OFF_T_DECLARED
typedef	signed int off_t; /* file offset */
#define _OFF_T_DECLARED
#endif

#ifndef _PID_T_DECLARED
typedef	signed int pid_t; /* process id */
#define _PID_T_DECLARED
#endif

#ifndef _SIZE_T_DECLARED
typedef	unsigned int size_t;
#define _SIZE_T_DECLARED
#endif

#ifndef _SSIZE_T_DECLARED
typedef signed int ssize_t;
#define _SSIZE_T_DECLARED
#endif

#ifndef _INT64_T_DECLARED
typedef	signed long int int64_t;
#define _INT64_T_DECLARED
#endif


/***************************************************************************//**
 *
 *  ... Path macros
 *
 ******************************************************************************/

#if !defined(PATH_SEPERATOR)
#  if defined(WIN32) || defined(_WIN32)
#    define PATH_SEPERATOR __string(\\)
#  else
#    define PATH_SEPERATOR __string(/)
#  endif
#endif

#if !defined(STRING_SEPERATOR)
#  if defined(WIN32) || defined(_WIN32)
#    define STRING_SEPERATOR __string(;)
#  else
#    define STRING_SEPERATOR __string(:)
#  endif
#endif

#if !defined(HOMEDRIVE)
#  if defined(WIN32) || defined(_WIN32) || defined(MINGW)
#    define HOMEDRIVE __string(C:)
#  else
#    define HOMEDRIVE PATH_SEPERATOR
#  endif
#endif

#if !defined(ROOTDIR)
#  if defined(WIN32) || defined(_WIN32) || defined(MINGW)
#    define ROOTDIR HOMEDRIVE PATH_SEPERATOR /** @name ROOTDIR @brief The location of the root operating directory (default value for Win32/MinGW). */
#  else
#    define ROOTDIR HOMEDRIVE /** < @name ROOTDIR @brief The location of the root operating directory (default value for *nix). */
#  endif
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

#ifndef HAVE_STRSEP
/**
 * @brief Replacement function for strsep()
 * @link https://stackoverflow.com/questions/58244300/getting-the-error-undefined-reference-to-strsep-with-clang-and-mingw
 * @param stringp
 * @param delim
 * @return char*
 */
char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}
#define HAVE_STRSEP 1
#endif

#if defined(__CYGWIN__) && CYGWIN_VERSION_API_MINOR < 262
  void *libc = dlopen ("cygwin1.dll", 0);
  struct mntent *(*getmntent_r) (FILE *, struct mntent *, char *, int)
    = dlsym (libc, "getmntent_r");
#endif

#if HAVE_LIBCURL
  void *libcurl = dlopen ("libcurl.so.3", 0);
  struct mntent *(*f_init) (FILE *, struct mntent *, char *, int) = dlsym (libcurl, "f_init");
#endif

#if HAVE_OPENSSL
  void *openssl = dlopen ("libcrypto.dll", 0);
  struct mntent *(*getmntent_r) (FILE *, struct mntent *, char *, int) = dlsym (openssl, "getmntent_r");
#endif

const char* path_seperator = PATH_SEPERATOR;
const char* string_seperator = STRING_SEPERATOR;
const char* homedrive = HOMEDRIVE;
const char* rootdir = ROOTDIR;

#if !(PKGMAN_INTELLISENSE_GUARD)

const char* prefix = PREFIX;

const char* bindir = BINDIR;
const char* datadir = DATADIR;
const char* includedir = INCLUDEDIR;
const char* infodir = INFODIR;
const char* libdir = LIBDIR;
const char* licensedir = LICENSEDIR;
const char* libexecdir = LIBEXECDIR;
const char* localedir = LOCALEDIR;
const char* localstatedir = LOCALSTATEDIR;
const char* mandir = MANDIR;
const char* sbindir = SBINDIR;
const char* sharedstatedir = SHAREDSTATEDIR;
const char* sysconfdir = SYSCONFDIR;

const char* scriptletshell = SCRIPTLET_SHELL;
const char* ldconfig = LDCONFIG;
const char* libalpm_version = LIB_VERSION;

const char* syshookdir = SYSHOOKDIR;
const char* conffile = CONFFILE;
const char* dbpath = DBPATH;
const char* gpgdir = GPGDIR;
const char* logfile = LOGFILE;
const char* cachedir = CACHEDIR;
const char* hookdir = HOOKDIR;
#endif /** !(PKGMAN_INTELLISENSE_GUARD) */

#ifdef PKGMAN_CPLUSPLUS
}
#endif

#endif /** PM_CONFIGURATION_H */
