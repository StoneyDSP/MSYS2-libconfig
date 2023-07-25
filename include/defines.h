/**
 * @file defines.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-07-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#if !defined(PM_DEFINES_HEADER_INCLUDED)
#define PM_DEFINES_HEADER_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(STRINGIFY_HELPER)
#	define STRINGIFY_HELPER(X) #X
#endif /** STRINGIFY_HELPER */

#if !defined(STRINGIFY)
#	define STRINGIFY(X) STRINGIFY_HELPER(X)
#endif /** STRINGIFY */

#if !defined(DEC)
/* Convert integer to decimal digit literals.  */
#define DEC(n)                   \
  ('0' + (((n) / 10000000)%10)), \
  ('0' + (((n) / 1000000)%10)),  \
  ('0' + (((n) / 100000)%10)),   \
  ('0' + (((n) / 10000)%10)),    \
  ('0' + (((n) / 1000)%10)),     \
  ('0' + (((n) / 100)%10)),      \
  ('0' + (((n) / 10)%10)),       \
  ('0' +  ((n) % 10))
#endif /** DEC */

#if !defined(HEX)
/* Convert integer to hex digit literals.  */
#define HEX(n)             \
  ('0' + ((n)>>28 & 0xF)), \
  ('0' + ((n)>>24 & 0xF)), \
  ('0' + ((n)>>20 & 0xF)), \
  ('0' + ((n)>>16 & 0xF)), \
  ('0' + ((n)>>12 & 0xF)), \
  ('0' + ((n)>>8  & 0xF)), \
  ('0' + ((n)>>4  & 0xF)), \
  ('0' + ((n)     & 0xF))
#endif /** HEX */


#if !defined(PATH_SEPERATOR)
#	if defined(WIN32)
#		define PATH_SEPERATOR STRINGIFY(\)
#	else
#		define PATH_SEPERATOR STRINGIFY(/)
#	endif
#endif

#if !defined(STRING_SEPERATOR)
#	if defined(WIN32)
#		define STRING_SEPERATOR STRINGIFY(;)
#	else
#		define STRING_SEPERATOR STRINGIFY(:)
#	endif
#endif

#if !defined(HOMEDRIVE)
#	if defined(WIN32) || defined(MINGW)
#		define HOMEDRIVE STRINGIFY(C:)
#	else
#		define HOMEDRIVE PATH_SEPERATOR
#	endif
#endif

#define ROOTDIR STRINGIFY(@ROOTDIR@)

#define PREFIX STRINGIFY(@PREFIX@)

#define BINDIR STRINGIFY(@BINDIR@)
#define DATADIR STRINGIFY(@DATADIR@)
#define INCLUDEDIR STRINGIFY(@INCLUDEDIR@)
#define INFODIR STRINGIFY(@INFODIR@)
#define LIBDIR STRINGIFY(@LIBDIR@)
#define LICENSEDIR STRINGIFY(@LICENSEDIR@)
#define LIBEXECDIR STRINGIFY(@LIBEXECDIR@)
#define LOCALEDIR STRINGIFY(@LOCALEDIR@)
#define LOCALSTATEDIR STRINGIFY(@LOCALSTATEDIR@)
#define MANDIR STRINGIFY(@MANDIR@)
#define SBINDIR STRINGIFY(@SBINDIR@)
#define SHAREDSTATEDIR STRINGIFY(@SHAREDSTATEDIR@)
#define SYSCONFDIR STRINGIFY(@SYSCONFDIR@)

#define HAVE_LIBCURL STRINGIFY(@HAVE_LIBCURLCURL@)
#define HAVE_LIBGPGME STRINGIFY(@HAVE_LIBGPGME@)
#define HAVE_LIBSSL STRINGIFY(@HAVE_LIBSSL@)
#define HAVE_LIBNETTLE STRINGIFY(@HAVE_LIBNETTLE@)

#define LIBMAKEPKGDIR STRINGIFY(@LIBMAKEPKGDIR@)
#define PKGDATADIR STRINGIFY(@PKGDATADIR@)

/** #cmakedefine _GNU_SOURCE @_GNU_SOURCE@ */
#define PACKAGE STRINGIFY(@PROJECT_NAME@)
#define PACKAGE_VERSION STRINGIFY(@PACKAGE_VERSION@)

#cmakedefine SCRIPTLET_SHELL STRINGIFY(@SCRIPTLET_SHELL@)
#cmakedefine LDCONFIG STRINGIFY(@LDCONFIG@)
#cmakedefine LIB_VERSION STRINGIFY(@LIB_VERSION@)
#cmakedefine SYSHOOKDIR STRINGIFY(@SYSHOOKDIR@)
#cmakedefine CONFFILE STRINGIFY(@CONFFILE@)
#cmakedefine DBPATH STRINGIFY(@DBPATH@)
#cmakedefine GPGDIR STRINGIFY(@GPGDIR@)
#cmakedefine LOGFILE STRINGIFY(@LOGFILE@)
#cmakedefine CACHEDIR STRINGIFY(@CACHEDIR@)
#cmakedefine HOOKDIR STRINGIFY(@HOOKDIR@)



#cmakedefine01 HAVE_MNTENT_H
#cmakedefine01 HAVE_SYS_MNTTAB_H
#cmakedefine01 HAVE_SYS_MOUNT_H
#cmakedefine01 HAVE_SYS_PARAM_H
#cmakedefine01 HAVE_SYS_STATVFS_H
#cmakedefine01 HAVE_SYS_TYPES_H
#cmakedefine01 HAVE_SYS_UCRED_H
#cmakedefine01 HAVE_TERMIOS_H

#cmakedefine01 HAVE_GETMNTENT
#cmakedefine01 HAVE_GETMNTINFO
#cmakedefine01 HAVE_STRNDUP
#cmakedefine01 HAVE_STRNLEN
#cmakedefine01 HAVE_STRSEP
#cmakedefine01 HAVE_SWPRINTF
#cmakedefine01 HAVE_TCFLUSH

#cmakedefine HAVE_STRUCT_STAT_ST_BLKSIZE @HAVE_STRUCT_STAT_ST_BLKSIZE@
#cmakedefine HAVE_STRUCT_STATVFS_F_FLAG @HAVE_STRUCT_STATVFS_F_FLAG@
#cmakedefine HAVE_STRUCT_STATFS_F_FLAGS @HAVE_STRUCT_STATFS_F_FLAGS@

#cmakedefine FSSTATSTYPE STRINGIFY(@FSSTATSTYPE@)

#cmakedefine01 HAS_CAST_ALIGN
#cmakedefine01 HAS_CLOBBERED
#cmakedefine01 HAS_EMPTY_BODY
#cmakedefine01 HAS_FLOAT_EQUAL
#cmakedefine01 HAS_FORMAT_NONLITERAL
#cmakedefine01 HAS_FORMAT_SECURITY
#cmakedefine01 HAS_IGNORED_QUALIFIERS
#cmakedefine01 HAS_IMPLICIT_FALLTHROUGHS
#cmakedefine01 HAS_INIT_SELF
#cmakedefine01 HAS_LOGICAL_OP
#cmakedefine01 HAS_MISSING_DECLARATIONS
#cmakedefine01 HAS_MISSING_FIELD_INITIALIZERS
#cmakedefine01 HAS_MISSING_PARAMETER_TYPE
#cmakedefine01 HAS_MISSING_PROTOTYPES
#cmakedefine01 HAS_OLD_STYLE_DECLARATION
#cmakedefine01 HAS_OVERRIDE_INIT
#cmakedefine01 HAS_POINTER_ARITH
#cmakedefine01 HAS_REDUNDANT_DECLS
#cmakedefine01 HAS_SHADOW
#cmakedefine01 HAS_SIGN_COMPARE
#cmakedefine01 HAS_STRICT_ALIASING
#cmakedefine01 HAS_STRICT_OVERFLOW_EQ_5
#cmakedefine01 HAS_STRICT_PROTOTYPES
#cmakedefine01 HAS_TYPE_LIMITS
#cmakedefine01 HAS_UNINITIALIZED
#cmakedefine01 HAS_UNUSED_BUT_DET_PARAMETER
#cmakedefine01 HAS_UNUSED_PARAMETER
#cmakedefine01 HAS_WRITE_STRINGS

#cmakedefine PACMAN_DEBUG @PACMAN_DEBUG@

#if defined(__cplusplus)
};
#endif

#endif /** PM_DEFINES_HEADER_INCLUDED */
