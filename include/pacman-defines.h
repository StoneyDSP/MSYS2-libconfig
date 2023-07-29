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


/**
 * If the compiler does not have __has_include,
 * pretend the answer is always no.
 */
#if !defined(__has_include)
#	define __has_include(x) 0
#	define PM_HAS_INCLUDE(x) 0
#else
#	define PM_HAS_INCLUDE(x) __has_include(x)
#endif

#if !defined(__has_attribute)
#	define PM_HAS_ATTRIBUTE(x) 0
#else
#	define PM_HAS_ATTRIBUTE(x) __has_attribute(x)
#endif

#if !defined(__has_extension)
#	define PM_HAS_EXTENSION(x) 0
#else
#	define PM_HAS_EXTENSION(x) __has_extension(x)
#endif

#if !defined(__has_builtin)
#	define PM_HAS_BUILTIN(x) 0
#else
#	define PM_HAS_BUILTIN(x) __has_builtin(x)
#endif

#if !defined(__has_feature)
#	define PM_HAS_FEATURE(x) 0
#else
#	define PM_HAS_FEATURE(x) __has_feature(x)
#endif

#if !defined(STRINGIFY_HELPER)
#	define STRINGIFY_HELPER(X) #X
#endif /** STRINGIFY_HELPER */

#if !defined(STRINGIFY)
#	define STRINGIFY(X) STRINGIFY_HELPER(X)
#endif /** STRINGIFY */

#if !defined(DEC)
	/**
	 * @name DEC
	 * @brief Convert integer to decimal digit literals.
	 */
#	define DEC(n)                   \
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
	/**
	 * @name HEX
	 * @brief Convert integer to hex digit literals.
	 */
#	define HEX(n)             \
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
#		define PATH_SEPERATOR STRINGIFY(\\)
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

/**
 * @name ROOTDIR
 * @brief The location of the root operating directory (configured value).
 */
#define ROOTDIR STRINGIFY(@rootdir@)

/**
 * @name PREFIX
 * @brief The location of the installation (configured value).
 */
#define PREFIX STRINGIFY(@prefix@)

/**
 * @name DATAROOTDIR
 * @brief Fix me (configured value)!
 */
#define DATAROOTDIR STRINGIFY(@datarootdir@)

/**
 * @name BINDIR
 * @brief Executable directory (configured value).
 */
#define BINDIR STRINGIFY(@bindir@)

/**
 * @name DATADIR
 * @brief Data file directory (configured value).
 */
#define DATADIR STRINGIFY(@datadir@)

/**
 * @name INCLUDEDIR
 * @brief Include Header file directory (configured value).
 */
#define INCLUDEDIR STRINGIFY(@includedir@)

/**
 * @name INFODIR
 * @brief Info page directory (configured value).
 */
#define INFODIR STRINGIFY(@infodir@)

/**
 * @name LIBDIR
 * @brief Library directory (configured value).
 */
#define LIBDIR STRINGIFY(@libdir@)

/**
 * @name LIBEXECDIR
 * @brief Library executable directory (configured value).
 */
#define LIBEXECDIR STRINGIFY(@libexecdir@)

/**
 * @name LICENSEDIR
 * @brief License information directory (configured value).
 */
#define LICENSEDIR STRINGIFY(@licensedir@)

/**
 * @name LOCALEDIR
 * @brief Locale data directory (configured value).
 */
#define LOCALEDIR STRINGIFY(@localedir@)

/**
 * @name LOCALSTATEDIR
 * @brief Localstate data directory (configured value).
 */
#define LOCALSTATEDIR STRINGIFY(@localstatedir@)

/**
 * @name MANDIR
 * @brief Manual page directory (configured value).
 */
#define MANDIR STRINGIFY(@mandir@)

/**
 * @name SBINDIR
 * @brief System executable directory (configured value).
 */
#define SBINDIR STRINGIFY(@sbindir@)

/**
 * @name SHAREDSTATEDIR
 * @brief Architecture-independent data directory (configured value).
 */
#define SHAREDSTATEDIR STRINGIFY(@sharedstatedir@)

/**
 * @name SYSCONFDIR
 * @brief Sysconf data directory (configured value).
 */
#define SYSCONFDIR STRINGIFY(@sysconfdir@)

/**
 * @name SCRIPTLET_SHELL
 * @brief The full path of the shell used to run install scriptlets (configured value).
 */
#define SCRIPTLET_SHELL STRINGIFY(@scriptlet_shell@)

/**
 * @name LDCONFIG
 * @brief the full path to ldconfig (configured value).
 *
 */
#define LDCONFIG STRINGIFY(@ldconfig@)

#define LIB_VERSION STRINGIFY(@libalpm_version@)
#define SYSHOOKDIR STRINGIFY(@SYSHOOKDIR@)
#define CONFFILE STRINGIFY(@CONFFILE@)
#define DBPATH STRINGIFY(@DBPATH@)
#define GPGDIR STRINGIFY(@GPGDIR@)
#define LOGFILE STRINGIFY(@LOGFILE@)
#define CACHEDIR STRINGIFY(@CACHEDIR@)
#define HOOKDIR STRINGIFY(@HOOKDIR@)

#define HAVE_LIBCURL @HAVE_LIBCURL@
#define HAVE_LIBGPGME @HAVE_LIBGPGME@
#define HAVE_LIBSSL @HAVE_LIBSSL@
#define HAVE_LIBNETTLE @HAVE_LIBNETTLE@

/** #define _GNU_SOURCE @_GNU_SOURCE@ */
#define PACKAGE STRINGIFY(@PROJECT_NAME@)
#define PACKAGE_VERSION STRINGIFY(@PACKAGE_VERSION@)
#define LIBMAKEPKGDIR STRINGIFY(@LIBMAKEPKGDIR@)
#define PKGDATADIR STRINGIFY(@PKGDATADIR@)

#define HAVE_MNTENT_H @HAVE_MNTENT_H@
#define HAVE_SYS_MNTTAB_H @HAVE_SYS_MNTTAB_H@
#define HAVE_SYS_MOUNT_H @HAVE_SYS_MOUNT_H@
#define HAVE_SYS_PARAM_H @HAVE_SYS_PARAM_H@
#define HAVE_SYS_STATVFS_H @HAVE_SYS_STATVFS_H@
#define HAVE_SYS_TYPES_H @HAVE_SYS_TYPES_H@
#define HAVE_SYS_UCRED_H @HAVE_SYS_UCRED_H@
#define HAVE_TERMIOS_H @HAVE_TERMIOS_H@

#define HAVE_GETMNTENT @HAVE_GETMNTENT@
#define HAVE_GETMNTINFO @HAVE_GETMNTINFO@
#define HAVE_STRNDUP @HAVE_STRNDUP@
#define HAVE_STRNLEN @HAVE_STRNLEN@
#define HAVE_STRSEP @HAVE_STRSEP@
#define HAVE_SWPRINTF @HAVE_SWPRINTF@
#define HAVE_TCFLUSH @HAVE_TCFLUSH@

#define HAVE_STRUCT_STAT_ST_BLKSIZE @HAVE_STRUCT_STAT_ST_BLKSIZE@
#define HAVE_STRUCT_STATVFS_F_FLAG @HAVE_STRUCT_STATVFS_F_FLAG@
#define HAVE_STRUCT_STATFS_F_FLAGS @HAVE_STRUCT_STATFS_F_FLAGS@

#define FSSTATSTYPE STRINGIFY(@FSSTATSTYPE@)

#define PM_HAS_CAST_ALIGN @HAS_CAST_ALIGN@
#define PM_HAS_CLOBBERED @HAS_CLOBBERED@
#define PM_HAS_EMPTY_BODY @HAS_EMPTY_BODY@
#define PM_HAS_FLOAT_EQUAL @HAS_FLOAT_EQUAL@
#define PM_HAS_FORMAT_NONLITERAL @HAS_FORMAT_NONLITERAL@
#define PM_HAS_FORMAT_SECURITY @HAS_FORMAT_SECURITY@
#define PM_HAS_IGNORED_QUALIFIERS @HAS_IGNORED_QUALIFIERS@
#define PM_HAS_IMPLICIT_FALLTHROUGHS @HAS_IMPLICIT_FALLTHROUGHS@
#define PM_HAS_INIT_SELF @HAS_INIT_SELF@
#define PM_HAS_LOGICAL_OP @HAS_LOGICAL_OP@
#define PM_HAS_MISSING_DECLARATIONS @HAS_MISSING_DECLARATIONS@
#define PM_HAS_MISSING_FIELD_INITIALIZERS @HAS_MISSING_FIELD_INITIALIZERS@
#define PM_HAS_MISSING_PARAMETER_TYPE @HAS_MISSING_PARAMETER_TYPE@
#define PM_HAS_MISSING_PROTOTYPES @HAS_MISSING_PROTOTYPES@
#define PM_HAS_OLD_STYLE_DECLARATION @HAS_OLD_STYLE_DECLARATION@
#define PM_HAS_OVERRIDE_INIT @HAS_OVERRIDE_INIT@
#define PM_HAS_POINTER_ARITH @HAS_POINTER_ARITH@
#define PM_HAS_REDUNDANT_DECLS @HAS_REDUNDANT_DECLS@
#define PM_HAS_SHADOW @HAS_SHADOW@
#define PM_HAS_SIGN_COMPARE @HAS_SIGN_COMPARE@
#define PM_HAS_STRICT_ALIASING @HAS_STRICT_ALIASING@
#define PM_HAS_STRICT_OVERFLOW_EQ_5 @HAS_STRICT_OVERFLOW_EQ_5@
#define PM_HAS_STRICT_PROTOTYPES @HAS_STRICT_PROTOTYPES@
#define PM_HAS_TYPE_LIMITS @HAS_TYPE_LIMITS@
#define PM_HAS_UNINITIALIZED @HAS_UNINITIALIZED@
#define PM_HAS_UNUSED_BUT_DET_PARAMETER @HAS_UNUSED_BUT_DET_PARAMETER@
#define PM_HAS_UNUSED_PARAMETER @HAS_UNUSED_PARAMETER@
#define PM_HAS_WRITE_STRINGS @HAS_WRITE_STRINGS@

#define PACMAN_DEBUG @PACMAN_DEBUG@

#if defined(__cplusplus)
};
#endif

#endif /** PM_DEFINES_HEADER_INCLUDED */
