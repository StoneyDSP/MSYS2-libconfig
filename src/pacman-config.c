/**
 *	@file cnf.c
 *	@author your name (you@domain.com)
 *	@brief
 *	@version 0.1
 *	@date 2023-07-19
 *
 *	@copyright Copyright (c) 2023
 *
**/

#include "pacman-config.h"

#if !defined(__has_attribute)
#	define PM_HAS_ATTRIBUTE(x) 0
#else
#	define PM_HAS_ATTRIBUTE(x) __has_attribute(x)
#endif

#if !defined(__has_builtin)
#	define PM_HAS_BUILTIN(x) 0
#else
#	define PM_HAS_BUILTIN(x) __has_builtin(x)
#endif

#if !defined(__has_c_attribute)
#	define PM_HAS_C_ATTRIBUTE(x) 0
#else
#	define PM_HAS_C_ATTRIBUTE(x) __has_c_attribute(x)
#endif

#if !defined(__has_cpp_attribute)
#	define PM_HAS_CXX_ATTRIBUTE(x) 0
#else
#	define PM_HAS_CXX_ATTRIBUTE(x) __has_cpp_attribute(x)
#endif

#if !defined(__has_extension)
#	define PM_HAS_EXTENSION(x) 0
#else
#	define PM_HAS_EXTENSION(x) __has_extension(x)
#endif

#if !defined(__has_feature)
#	define PM_HAS_FEATURE(x) 0
#else
#	define PM_HAS_FEATURE(x) __has_feature(x)
#endif

#if !defined(__has_include)
#	define __has_include(x) 0
#	define PM_HAS_INCLUDE(x) 0
#else
#	define PM_HAS_INCLUDE(x) __has_include(x)
#endif

#if !defined(__has_include_next)
#	define __has_include_next(x) 0
#	define PM_HAS_INCLUDE_NEXT(x) 0
#else
#	define PM_HAS_INCLUDE_NEXT(x) __has_include_next(x)
#endif

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
#endif

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
#endif

#if !defined(PATH_SEPERATOR)
#	if defined(WIN32)
		/**
		 * @name PATH_SEPERATOR
		 * @brief
		 */
#		define PATH_SEPERATOR __string(\\)
#	else
		/**
		 * @name PATH_SEPERATOR
		 * @brief
		 */
#		define PATH_SEPERATOR __string(/)
#	endif
#endif

#if !defined(STRING_SEPERATOR)
#	if defined(WIN32)
		/**
		 * @name STRING_SEPERATOR
		 * @brief
		 */
#		define STRING_SEPERATOR __string(;)
#	else
		/**
		 * @name STRING_SEPERATOR
		 * @brief
		 */
#		define STRING_SEPERATOR __string(:)
#	endif
#endif

#if !defined(HOMEDRIVE)
#	if defined(WIN32) || defined(MINGW)
		/**
		 * @name HOMEDRIVE
		 * @brief
		 */
#		define HOMEDRIVE __string(C:)
#	else
		/**
		 * @name HOMEDRIVE
		 * @brief
		 */
#		define HOMEDRIVE PATH_SEPERATOR
#	endif
#endif

#if !defined(ROOTDIR)
#	if defined(WIN32) || defined(MINGW)
		/**
		 * @name ROOTDIR
		 * @brief The location of the root operating directory (default value for Win32/MinGW).
		 */
#		define ROOTDIR HOMEDRIVE PATH_SEPERATOR
#	else
		/**
		 * @name ROOTDIR
		 * @brief The location of the root operating directory (default value for *nix).
		 */
#		define ROOTDIR HOMEDRIVE
#	endif
#endif

#if !defined(PREFIX)
	/**
	 * @name PREFIX
	 * @brief The location of the installation (default value).
	 */
#	define PREFIX HOMEDRIVE __string(usr)
#endif

#if !defined(DATAROOTDIR)
	/**
	 * @name DATAROOTDIR
	 * @brief Fix me (default value)!
	 */
#	define DATAROOTDIR PATH_SEPERATOR __string(share)
#endif

#if !defined(BINDIR)
	/**
	 * @name BINDIR
	 * @brief Executable directory (default value).
	 */
#	define BINDIR PATH_SEPERATOR __string(bin)
#endif

#if !defined(DATADIR)
	/**
	 * @name DATADIR
	 * @brief Data file directory (default value).
	 */
#	define DATADIR PATH_SEPERATOR __string(share)
#endif

#if !defined(INCLUDEDIR)
	/**
	 * @name INCLUDEDIR
	 * @brief Include Header file directory (default value).
	 */
#	define INCLUDEDIR PATH_SEPERATOR __string(include)
#endif

#if !defined(INFODIR)
	/**
	 * @name INFODIR
	 * @brief Info page directory (default value).
	 */
#	define INFODIR DATADIR PATH_SEPERATOR __string(info)
#endif

#if !defined(LIBDIR)
	/**
	 * @name LIBDIR
	 * @brief Library directory (default value).
	 */
#	define LIBDIR PATH_SEPERATOR __string(lib)
#endif

#if !defined(LIBEXECDIR)
	/**
	 * @name LIBEXECDIR
	 * @brief Library executable directory (default value).
	 */
#	define LIBEXECDIR PATH_SEPERATOR __string(libexec)
#endif

#if !defined(LICENSEDIR)
	/**
	 * @name LICENSEDIR
	 * @brief License information directory (default value).
	 */
#	define LICENSEDIR PATH_SEPERATOR __string(license)
#endif

#if !defined(LOCALEDIR)
	/**
	 * @name LOCALEDIR
	 * @brief Locale data directory (default value).
	 */
#	define LOCALEDIR DATADIR PATH_SEPERATOR __string(locale)
#endif

#if !defined(LOCALSTATEDIR)
	/**
	 * @name LOCALSTATEDIR
	 * @brief Localstate data directory (default value).
	 */
#	define LOCALSTATEDIR PATH_SEPERATOR __string(var)
#endif

#if !defined(MANDIR)
	/**
	 * @name MANDIR
	 * @brief Manual page directory (default value).
	 */
#	define MANDIR DATADIR PATH_SEPERATOR __string(man)
#endif

#if !defined(SBINDIR)
	/**
	 * @name SBINDIR
	 * @brief System executable directory (default value).
	 */
#	define SBINDIR PATH_SEPERATOR __string(sbin)
#endif

#if !defined(SHAREDSTATEDIR)
	/**
	 * @name SHAREDSTATEDIR
	 * @brief Architecture-independent data directory (default value).
	 */
#	define SHAREDSTATEDIR PATH_SEPERATOR __string(com)
#endif

#if !defined(SYSCONFDIR)
	/**
	 * @name SYSCONFDIR
	 * @brief Sysconf data directory (default value).
	 */
#	define SYSCONFDIR PATH_SEPERATOR __string(etc)
#endif


#if !defined(SCRIPTLET_SHELL)
	/**
	 * @name SCRIPTLET_SHELL
	 * @brief The full path of the shell used to run install scriptlets (default value).
	 */
#	define SCRIPTLET_SHELL BINDIR PATH_SEPERATOR __string(sh)
#endif

#if !defined(LDCONFIG)
	/**
	 * @name LDCONFIG
	 * @brief The full path to ldconfig (default value).
	 */
#	define LDCONFIG SBINDIR PATH_SEPERATOR __string(ldconfig)
#endif

#if !defined(LIB_VERSION)
#	define LIB_VERSION __string(13.0.2)
#endif

#if !defined(SYSHOOKDIR)
#	define SYSHOOKDIR DATAROOTDIR PATH_SEPERATOR __string(libalpm) PATH_SEPERATOR __string(hooks)
#endif

#if !defined(CONFFILE)
#	define CONFFILE SYSCONFDIR PATH_SEPERATOR __string(pacman.conf)
#endif

#if !defined(DBPATH)
#	define DBPATH LOCALSTATEDIR PATH_SEPERATOR __string(lib) PATH_SEPERATOR __string(pacman) PATH_SEPERATOR
#endif

#if !defined(GPGDIR)
#	define GPGDIR SYSCONFDIR PATH_SEPERATOR __string(pacman.d) PATH_SEPERATOR __string(gnupg) PATH_SEPERATOR
#endif

#if !defined(LOGFILE)
#	define LOGFILE LOCALSTATEDIR PATH_SEPERATOR __string(log) PATH_SEPERATOR __string(pacman.log)
#endif

#if !defined(CACHEDIR)
#	define CACHEDIR LOCALSTATEDIR PATH_SEPERATOR __string(cache) PATH_SEPERATOR __string(pacman) PATH_SEPERATOR __string(pkg) PATH_SEPERATOR
#endif

#if !defined(HOOKDIR)
#	define HOOKDIR SYSCONFDIR PATH_SEPERATOR __string(pacman.d) PATH_SEPERATOR __string(hooks)
#endif


/** HAVE_LIBCURL */
#if !defined(HAVE_LIBCURL)
# 	define HAVE_LIBCURL false
#elif (HAVE_LIBCURL + 0) != 0 || (1 - HAVE_LIBCURL - 1) == 2
#	undef HAVE_LIBCURL
#  	define HAVE_LIBCURL true
#else
#	undef HAVE_LIBCURL
#	define HAVE_LIBCURL false
#endif

/** HAVE_LIBGPGME */
#if !defined(HAVE_LIBGPGME)
# 	define HAVE_LIBGPGME false
#elif (HAVE_LIBGPGME + 0) != 0 || (1 - HAVE_LIBGPGME - 1) == 2
#	undef HAVE_LIBGPGME
# 	define HAVE_LIBGPGME true
#else
#	undef HAVE_LIBGPGME
# 	define HAVE_LIBGPGME false
#endif

/** HAVE_LIBSSL */
#if !defined(HAVE_LIBSSL)
#	define HAVE_LIBSSL 0
#elif (HAVE_LIBSSL + 0) != 0 || (1 - HAVE_LIBSSL - 1) == 2
#	define HAVE_LIBSSL 1
#else
#	define HAVE_LIBSSL 0
#endif

/** HAVE_LIBNETTLE */
#if !defined(HAVE_LIBNETTLE)
#	define HAVE_LIBNETTLE 0
#elif (HAVE_LIBNETTLE + 0) != 0 || (1 - HAVE_LIBNETTLE - 1) == 2
#	define HAVE_LIBNETTLE 1
#else
#	define HAVE_LIBNETTLE 0
#endif

/**
 * @brief Check for system headers here
 *
**/

#if PM_HAS_INCLUDE(<mntent.h>)
#	define HAVE_MNTENT_H 1
#else
#	undef  HAVE_MNTENT_H
#endif

#if PM_HAS_INCLUDE(<sys/mnttab.h>)
#	define HAVE_SYS_MNTTAB_H 1
#else
#	undef  HAVE_SYS_MNTTAB_H
#endif

#if PM_HAS_INCLUDE(<sys/mount.h>)
#	define HAVE_SYS_MOUNT_H 1
#else
#	undef  HAVE_SYS_MOUNT_H
#endif

#if PM_HAS_INCLUDE(<sys/param.h>)
#	define HAVE_SYS_PARAM_H 1
#else
#	undef  HAVE_SYS_PARAM_H
#endif

#if PM_HAS_INCLUDE(<sys/stavfs.h>)
#	define HAVE_SYS_STATVFS_H 1
#else
#	undef  HAVE_SYS_STATVFS
#endif

#if PM_HAS_INCLUDE(<sys/types.h>)
#	define HAVE_SYS_TYPES_H 1
#else
#	undef  HAVE_SYS_TYPES_H
#endif

#if PM_HAS_INCLUDE(<sys/ucred.h>)
#	define HAVE_SYS_UCRED_H 1
#else
#	undef  HAVE_SYS_UCRED_H
#endif

#if PM_HAS_INCLUDE(<termios.h>)
#	define HAVE_TERMIOS_H 1
#else
#	undef  HAVE_TERMIOS_H
#endif

/**
 * @brief Function checks
 *
 * @code
 *
 * #if PM_HAS_BUILTIN(__builtin_object_size)
 * #	define builtin_object_size(ptr) __builtin_object_size (ptr, 2)
 * #endif
 * #if !defined(builtin_object_size)
 * #	define builtin_object_size(ptr) ((size_t) - 1)
 * #endif
 *
 * @endcode
 *
**/


/** HAVE_GETMNTENT */
#if !defined(HAVE_GETMNTENT)
#	define HAVE_GETMNTENT 0
#elif (HAVE_GETMNTENT + 0) != 0 || (1 - HAVE_GETMNTENT - 1) == 2
#	define HAVE_GETMNTENT 1
#else
#	define HAVE_GETMNTENT 0
#endif

/** HAVE_GETMNTINFO */
#if !defined(HAVE_GETMNTINFO)
#	define HAVE_GETMNTINFO 0
#elif (HAVE_GETMNTINFO + 0) != 0 || (1 - HAVE_GETMNTINFO - 1) == 2
#	define HAVE_GETMNTINFO 1
#else
#	define HAVE_GETMNTINFO 0
#endif

/** HAVE_STRNDUP */
#if !defined(HAVE_STRNDUP)
#	define HAVE_STRNDUP 0
#elif (HAVE_STRNDUP + 0) != 0 || (1 - HAVE_STRNDUP - 1) == 2
#	define HAVE_STRNDUP 1
#else
#	define HAVE_STRNDUP 0
#endif

/** HAVE_STRLEN */
#if !defined(HAVE_STRNLEN)
#	define HAVE_STRNLEN 0
#elif (HAVE_STRNLEN + 0) != 0 || (1 - HAVE_STRNLEN - 1) == 2
#	define HAVE_STRNLEN 1
#else
#	define HAVE_STRNLEN 0
#endif

/** HAVE_STRSEP */
#if !defined(HAVE_STRSEP)
#	define HAVE_STRSEP 0
#elif (HAVE_STRSEP + 0) != 0 || (1 - HAVE_STRSEP - 1) == 2
#	define HAVE_STRSEP 1
#else
#	define HAVE_STRSEP 0
#endif

/** HAVE_SWPRINTF */
#if !defined(HAVE_SWPRINTF)
#	define HAVE_SWPRINTF 0
#elif (HAVE_SWPRINTF + 0) != 0 || (1 - HAVE_SWPRINTF - 1) == 2
#	define HAVE_SWPRINTF 1
#else
#	define HAVE_SWPRINTF 0
#endif

/** HAVE_TCFLUSH */
#if !defined(HAVE_TCFLUSH)
#	define HAVE_TCFLUSH 0
#elif (HAVE_TCFLUSH + 0) != 0 || (1 - HAVE_TCFLUSH - 1) == 2
#	define HAVE_TCFLUSH 1
#else
#	define HAVE_TCFLUSH 0
#endif

/**
 * @name dec
 * @brief Convert integer to decimal digit literals.
 */
double 	dec(int n) { return DEC(n); };
/**
 * @name hex
 * @brief Convert integer to hex digit literals.
 */
int 	hex(int n){ return HEX(n); };


const char* path_seperator = PATH_SEPERATOR;
const char* string_seperator = STRING_SEPERATOR;
const char* homedrive = HOMEDRIVE;
const char* rootdir = ROOTDIR;

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

/** These two are configured as bool, but of course C doesn't have boolean data types... */
// const bool have_libcurl = HAVE_LIBCURL;
// const bool have_libgpgme = HAVE_LIBGPGME;

/** int */
const int* have_libssl = HAVE_LIBSSL;
const int* have_libnettle = HAVE_LIBNETTLE;
