/**
 *	@file cnf.h
 *	@author your name (you@domain.com)
 *	@brief
 *	@version 0.1
 *	@date 2023-07-19
 *
 *	@copyright Copyright (c) 2023
 *
 */

#if !defined(PM_CONFIG_HEADER_INCLUDED)
#define PM_CONFIG_HEADER_INCLUDED

#include "defines.h"

#if defined(__cplusplus)
# warning "A C++ compiler has been selected for C."
extern "C" {
#endif


/**
 * @brief
 *
 * 'prefix' defaults to "C:/" on Windows, and "/usr/local" otherwise.
 *
 * You should always override this value.
 *
 * 'libdir' is automatically detected based on your platform.
 *
 * It should be correct when doing "native" (build machine == host machine)
 * compilation.
 *
 * For cross compiles it may not be accurate, especially on Linux where
 * different distributions have different defaults. Using a cross file,
 * particularly the paths section may be necessary.
 *
 * 'licensedir' is empty by default.
 *
 * If set, it defines the default location to install a dependency manifest and project licenses.
 *
 */

#if !defined(ROOTDIR)
#	if defined(WIN32) || defined(MINGW)
		/**
		 * @name ROOTDIR
		 * @brief The location of the root operating directory.
		 */
#		define ROOTDIR HOMEDRIVE PATH_SEPERATOR
#	else
		/**
		 * @name ROOTDIR
		 * @brief The location of the root operating directory.
		 */
#		define ROOTDIR HOMEDRIVE
#	endif
#endif

#if !defined(PREFIX)
#	define PREFIX HOMEDRIVE STRINGIFY(usr)
#endif

#if !defined(DATAROOTDIR)
	/**
	 * @name DATAROOTDIR
	 * @brief Fix me!
	 */
#	define DATAROOTDIR PATH_SEPERATOR STRINGIFY(share)
#endif

#if !defined(BINDIR)
	/**
	 * @name BINDIR
	 * @brief Executable directory.
	 */
#	define BINDIR PATH_SEPERATOR STRINGIFY(bin)
#endif

#if !defined(DATADIR)
	/**
	 * @name DATADIR
	 * @brief Data file directory.
	 */
#	define DATADIR PATH_SEPERATOR STRINGIFY(share)
#endif

#if !defined(INCLUDEDIR)
	/**
	 * @name INCLUDEDIR
	 * @brief Include Header file directory.
	 */
#	define INCLUDEDIR PATH_SEPERATOR STRINGIFY(include)
#endif

#if !defined(INFODIR)
	/**
	 * @name INFODIR
	 * @brief Info page directory.
	 */
#	define INFODIR DATADIR PATH_SEPERATOR STRINGIFY(info)
#endif

#if !defined(LIBDIR)
	/**
	 * @name LIBDIR
	 * @brief Library directory.
	 */
#	define LIBDIR PATH_SEPERATOR STRINGIFY(lib)
#endif

#if !defined(LIBEXECDIR)
	/**
	 * @name LIBEXECDIR
	 * @brief Library executable directory.
	 */
#	define LIBEXECDIR PATH_SEPERATOR STRINGIFY(libexec)
#endif

#if !defined(LICENSEDIR)
	/**
	 * @name LICENSEDIR
	 * @brief
	 */
#	define LICENSEDIR PATH_SEPERATOR
#endif

#if !defined(LOCALEDIR)
	/**
	 * @name LOCALEDIR
	 * @brief Locale data directory.
	 */
#	define LOCALEDIR DATADIR PATH_SEPERATOR STRINGIFY(locale)
#endif

#if !defined(LOCALSTATEDIR)
	/**
	 * @name LOCALSTATEDIR
	 * @brief Localstate data directory.
	 */
#	define LOCALSTATEDIR PATH_SEPERATOR STRINGIFY(var)
#endif

#if !defined(MANDIR)
	/**
	 * @name MANDIR
	 * @brief Manual page directory.
	 */
#	define MANDIR DATADIR PATH_SEPERATOR STRINGIFY(man)
#endif

#if !defined(SBINDIR)
	/**
	 * @name SBINDIR
	 * @brief System executable directory.
	 */
#	define SBINDIR PATH_SEPERATOR STRINGIFY(sbin)
#endif

#if !defined(SHAREDSTATEDIR)
	/**
	 * @name SHAREDSTATEDIR
	 * @brief Architecture-independent data directory.
	 */
#	define SHAREDSTATEDIR PATH_SEPERATOR STRINGIFY(com)
#endif

#if !defined(SYSCONFDIR)
	/**
	 * @name SYSCONFDIR
	 * @brief Sysconf data directory.
	 */
#	define SYSCONFDIR PATH_SEPERATOR STRINGIFY(etc)
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


/** HAVE_MNTENT_H */
#if !defined(HAVE_MNTENT_H)
#	undef HAVE_MNTENT_H
#elif (HAVE_MNTENT_H + 0) != 0 || (1 - HAVE_MNTENT_H - 1) == 2
#	undef HAVE_MNTENT_H
#	define HAVE_MNTENT_H true
#else
#	undef HAVE_MNTENT_H
#endif

/** HAVE_SYS_MNTTAB_H */
#if !defined(HAVE_SYS_MNTTAB_H)
#	undef HAVE_SYS_MNTTAB_H
#elif (HAVE_SYS_MNTTAB_H + 0) != 0 || (1 - HAVE_SYS_MNTTAB_H - 1) == 2
#	undef HAVE_SYS_MNTTAB_H
#	define HAVE_SYS_MNTTAB_H true
#else
#	undef HAVE_SYS_MNTTAB_H
#endif

/** HAVE_SYS_MOUNT_H */
#if !defined(HAVE_SYS_MOUNT_H)
#	undef HAVE_SYS_MOUNT_H
#elif (HAVE_SYS_MOUNT_H + 0) != 0 || (1 - HAVE_SYS_MOUNT_H - 1) == 2
#	undef HAVE_SYS_MOUNT_H
#	define HAVE_SYS_MOUNT_H true
#else
#	undef HAVE_SYS_MOUNT_H
#endif

/** HAVE_SYS_PARAM_H */
#if !defined(HAVE_SYS_PARAM_H)
#	undef HAVE_SYS_PARAM_H
#elif (HAVE_SYS_PARAM_H + 0) != 0 || (1 - HAVE_SYS_PARAM_H - 1) == 2
#	undef HAVE_SYS_PARAM_H
#	define HAVE_SYS_PARAM_H true
#else
#	undef HAVE_SYS_PARAM_H
#endif

/** HAVE_SYS_STATVFS_H */
#if !defined(HAVE_SYS_STATVFS_H)
#	undef HAVE_SYS_STATVFS_H
#elif (HAVE_SYS_STATVFS_H + 0) != 0 || (1 - HAVE_SYS_STATVFS_H - 1) == 2
#	undef HAVE_SYS_STATVFS_H
#	define HAVE_SYS_STATVFS_H true
#else
#	undef HAVE_SYS_STATVFS_H
#endif

/** HAVE_SYS_TYPES_H */
#if !defined(HAVE_SYS_TYPES_H)
#	undef HAVE_SYS_TYPES_H
#elif (HAVE_SYS_TYPES_H + 0) != 0 || (1 - HAVE_SYS_TYPES_H - 1) == 2
#	undef HAVE_SYS_TYPES_H
#	define HAVE_SYS_TYPES_H true
#else
#	undef HAVE_SYS_TYPES_H
#endif

/** HAVE_SYS_UCRED_H */
#if !defined(HAVE_SYS_UCRED_H)
#	undef HAVE_SYS_UCRED_H
#elif (HAVE_SYS_UCRED_H + 0) != 0 || (1 - HAVE_SYS_UCRED_H - 1) == 2
#	undef HAVE_SYS_UCRED_H
#	define HAVE_SYS_UCRED_H true
#else
#	undef HAVE_SYS_UCRED_H
#endif

/** HAVE_TERMIOS_H */
#if !defined(HAVE_TERMIOS_H)
#	undef HAVE_TERMIOS_H
#elif (HAVE_TERMIOS_H + 0) != 0 || (1 - HAVE_TERMIOS_H - 1) == 2
#	undef HAVE_TERMIOS_H
#	define HAVE_TERMIOS_H true
#else
#	undef HAVE_TERMIOS_H
#endif


/**
 *	@brief We are defining as 0 or 1
 *	getmntent,
 *	getmntinfo,
 *	strndup,
 *	strnlen,
 *	strsep,
 *	swprintf,
 *	tcflush,
 *
 */

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


struct system {

	const char* path_seperator = PATH_SEPERATOR;
	const char* string_seperator = STRING_SEPERATOR;
	const char* homedrive = HOMEDRIVE;
	const char* rootdir = ROOTDIR;

};

struct paths {

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

};

#if defined(__cplusplus)
};
#endif

#endif /** PM_CONFIG_H */
