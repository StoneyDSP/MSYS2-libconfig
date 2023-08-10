/**
 * @file pkgman_config.cs
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#if (__CYGWIN__)
#  if __has_include(<cygwin/version.h>)
#    include <cygwin/version.h>
#  endif
#endif

/**
 * #if __has_include(<corecrt.h>)
 * #  include <corecrt.h>
 * #endif
*/

#if   (__has_include(<dlfcn.h>))
#  include <dlfcn.h>
#  define HAVE_DLFCN_H 1
#elif (__has_include("dlfcn-win32/dlfcn.h"))
#  include "dlfcn-win32/dlfcn.h"
#  define HAVE_DLFCN_H 1
#else
#  error "Cannot find '<dlfcn.h>' - Please check your package manager for 'dlfcn.h', or go to 'https://github.com/dlfcn-win32/dlfcn-win32' for Windows!"
#endif

#if   (__has_include(<unistd.h>))
#  include <unistd.h>
#endif

#if   (__has_include(<dirent.h>))
#  include <dirent.h>
#endif

#if   (__has_include(<nettle/crypto.h>))
#  include <nettle/crypto.h>
#  define HAVE_LIBNETTLE 1
#elif (__has_include(<openssl/crypto.h>))
#  include <openssl/crypto.h>
#  define HAVE_LIBSSL 1
#else
#  error "No crypto provider found!?"
#endif

#include "pkgman/pkgman_config.h"
#ifndef PKGMAN_CONFIGURATION_H
# error "No config header found?"
#endif

/**
 * #define MINGW_LIB_PATH __PM_STRING(C:/msys64)
 * #define MINGW_LIB __PM_STRING(libmingw32.a)
*/

#define MSVCRT_LIB_PATH __PM_STRING(C:/Windows/System32)
#define MSVCRT_DYNAMIC_LIB __PM_STRING(msvcrt.dll)

#define UCRTBASE_LIB_PATH __PM_STRING(C:/Windows/System32)
#define UCRTBASE_DYNAMIC_LIB __PM_STRING(ucrtbase.dll)

/**
 * Get the chosen lib
*/
int checkForLib(const char* pathToHeader, const char* libName)
{
	/** Check for header path... this could be more thorough, of course... */
	DIR *dip;
	struct dirent *dit;
	struct stat lsbuf;
	char currentPath[FILENAME_MAX];

	const char* header_path = pathToHeader;

	dip = opendir(header_path);

	if (dip == NULL)  {

		perror("opendir()");

		return errno;
	}

	if ((getcwd(currentPath, FILENAME_MAX)) == NULL)  {

		perror("getcwd()");

		return errno;
	}

	/* stat the file - if it exists, do some checks */
	if (stat(currentPath, &lsbuf) == -1)  {

		perror("stat()");

		return errno;

	} else {

		if (S_ISDIR(lsbuf.st_mode))  {

			printf("\"%s\" exists on this system.\n", header_path);

		} else {

			printf("\"%s\" does not exist on this system.\n", header_path);
		}
	}

	/** Get the chosen crypto lib */
	void* handle;
	char *error;

	handle = dlopen(libName, RTLD_LAZY);

	if (!handle)  {

		printf("Loading '%s' attempt failed: %s\n", libName, dlerror());

		return errno;
	}

	dlerror();    /* Clear any existing error */

	error = dlerror();

	if (error != NULL)  {

		printf("Loading '%s' attempt failed: %s\n", libName, error);

		return errno;
	}

	printf("Loaded '%s' successfully.\n", libName);

	dlclose(handle);

	return (0);
}

#if (__CYGWIN__)
int WinMain()
{
#else
int main()
{
#endif

	printf("\n");
	printf("pkgman_config");

	#ifdef PKGMAN_VERSION
		printf(" v%d.%d.%d", PKGMAN_VERSION_MAJOR, PKGMAN_VERSION_MINOR, PKGMAN_VERSION_PATCH);
		printf("-%s", PKGMAN_VERSION_TWEAK);
	#endif

	printf("\n");
	printf("Checking for dependencies...\n");
	printf("\n");

/**
 * #if defined(__CYGWIN__) && CYGWIN_VERSION_API_MINOR < 262
 * void *libc = dlopen ("cygwin1.dll", 0);
 * struct mntent *(*getmntent_r) (FILE *, struct mntent *, char *, int) = dlsym (libc, "getmntent_r");
 * #endif
*/
	int have_ucrtbase;
	int have_libcrypto;
	int have_libcurl;
	int have_libgpgme;

	have_ucrtbase = checkForLib(UCRTBASE_LIB_PATH, UCRTBASE_DYNAMIC_LIB);
	printf("\n");
	checkForLib(MSVCRT_LIB_PATH, MSVCRT_DYNAMIC_LIB);
	printf("\n");
	checkForLib(MSYS_INSTALL_PATH, MSYSLIB);
	printf("\n");
	have_libcrypto = checkForLib(CRYPTO_H_PATH, CRYPTO_LIB);
	printf("\n");
	have_libcurl = checkForLib(CURL_H_PATH, LIBCURL_LIB);
	printf("\n");
	have_libgpgme = checkForLib(GPGME_H_PATH, LIBGPGME_LIB);
	printf("\n");

	#define HAVE_LIBCURL have_libcurl
	#define HAVE_LIBGPGME have_libcurl

	printf("\n");
	printf("Build information:\n\n");

	printf("prefix                  : %s\n", 									PREFIX);
  	printf("sysconfdir              : %s\n", 									SYSCONFDIR);
  	printf("conf file           	: %s/pacman.conf\n", 						SYSCONFDIR);
  	printf("localstatedir           : %s\n", 									LOCALSTATEDIR);
  	printf("database dir        	: %s/lib/pacman/\n", 						LOCALSTATEDIR);
  	printf("cache dir           	: %s/cache/pacman/pkg/\n", 					LOCALSTATEDIR);
  	printf("compiler                : @0@ @1@'.format(cc.get_id(), cc.version())\n");

	printf("\n");

	printf("Architecture            : @0@'.format(carch)\n");
  	printf("Host Type               : @0@'.format(chost)\n");
  	printf("File inode command      : @0@'.format(inodecmd)\n");
  	printf("File seccomp command    : @0@'.format(filecmd)\n");
  	printf("libalpm version         : @0@'.format(libalpm_version)\n");
    printf("pacman version          : @0@'.format(PACKAGE_VERSION)\n");

	printf("\n");

	printf("Directory and file information:\n\n");

	printf("root working directory  : %s\n", 									ROOTDIR);
  	printf("package extension       : %s\n", 									PKGEXT);
    printf("source pkg extension    : %s\n", 									SRCEXT);
    printf("build script name       : %s\n", 									BUILDSCRIPT);
    printf("template directory      : %s\n",	 								MAKEPKG_TEMPLATE_DIR);

	printf("\n");

	printf("Compilation options:\n\n");

	printf("i18n support            : @0@'.format(get_option('i18n'))\n");
    printf("Build docs              : @0@'.format(build_doc)\n");

#if defined(PKGMAN_DEBUG)
  	printf("debug build             : %s\n", "true");
#else
  	printf("debug build             : %s\n", "false");
#endif

#if (have_libcurl != 0)
  	printf("Use libcurl             : false\n");
#else
  	printf("Use libcurl             : true\n");
#endif

#if (have_libgpgme != 0)
  	printf("Use GPGME               : false\n");
#else
  	printf("Use GPGME               : true\n");
#endif

#if defined(HAVE_LIBSSL) && (HAVE_LIBSSL == 1)
  	printf("Use OpenSSL             : true\n");
#else
  	printf("Use OpenSSL             : false\n");
#endif

#if defined(HAVE_LIBNETTLE) && (HAVE_LIBNETTLE == 1)
  	printf("Use nettle              : true\n");
#else
  	printf("Use nettle              : false\n");
#endif

	printf("\n");
	printf("Compiler info:\n");
	printf("\n");

#if defined(PKGMAN_CLANG_VERSION) && (PKGMAN_CLANG_VERSION != 0)
	printf("PKGMAN_CLANG_VERSION: %d\n", PKGMAN_CLANG_VERSION);
#endif

#if defined(PKGMAN_GCC_VERSION) && (PKGMAN_GCC_VERSION != 0)
	printf("PKGMAN_GCC_VERSION: %d\n", PKGMAN_GCC_VERSION);
#endif

#if defined(PKGMAN_ICC_VERSION) && (PKGMAN_ICC_VERSION != 0)
	printf("PKGMAN_ICC_VERSION: %d\n", PKGMAN_ICC_VERSION);
#endif

#if defined(PKGMAN_MSC_VERSION) && (PKGMAN_MSC_VERSION != 0)
	printf("PKGMAN_MSC_VERSION: %d\n", PKGMAN_MSC_VERSION);
#endif

	printf("\n");
	printf("Feature detection macros:\n");
	printf("\n");

#ifdef _POSIX_SOURCE
	printf("_POSIX_SOURCE 			: defined\n");
#else
	printf("_POSIX_SOURCE	 		: undefined\n");
#endif

#ifdef _POSIX_C_SOURCE
	printf("_POSIX_C_SOURCE 		: defined = %jdL\n", (intmax_t) _POSIX_C_SOURCE);
#else
	printf("_POSIX_C_SOURCE 		: undefined\n");
#endif

#ifdef _ISOC99_SOURCE
	printf("_ISOC99_SOURCE 			: defined\n");
#else
	printf("_ISOC99_SOURCE 			: undefined\n");
#endif

#ifdef _ISOC11_SOURCE
	printf("_ISOC11_SOURCE 			: defined\n");
#else
	printf("_ISOC11_SOURCE	 		: undefined\n");
#endif

#ifdef _XOPEN_SOURCE
	printf("_XOPEN_SOURCE 			: defined = %d\n", _XOPEN_SOURCE);
#else
	printf("_XOPEN_SOURCE	 		: undefined\n");
#endif

#ifdef _XOPEN_SOURCE_EXTENDED
	printf("_XOPEN_SOURCE_EXTENDED		: defined\n");
#else
	printf("_XOPEN_SOURCE_EXTENDED		: undefined\n");
#endif

#ifdef _LARGEFILE64_SOURCE
	printf("_LARGEFILE64_SOURCE		: defined\n");
#else
	printf("_LARGEFILE64_SOURCE		: undefined\n");
#endif

#ifdef _FILE_OFFSET_BITS
	printf("_FILE_OFFSET_BITS 		: defined = %d\n", _FILE_OFFSET_BITS);
#else
	printf("_FILE_OFFSET_BITS 		: undefined\n");
#endif

#ifdef _TIME_BITS
	printf("_TIME_BITS 			: defined = %d\n", _TIME_BITS);
#else
	printf("_TIME_BITS		 	: undefined\n");
#endif

#ifdef _BSD_SOURCE
	printf("_BSD_SOURCE 			: defined\n");
#else
	printf("_BSD_SOURCE 			: undefined\n");
#endif

#ifdef _SVID_SOURCE
	printf("_SVID_SOURCE 			: defined\n");
#else
	printf("_SVID_SOURCE 			: undefined\n");
#endif

#ifdef _DEFAULT_SOURCE
	printf("_DEFAULT_SOURCE 		: defined\n");
#else
	printf("_DEFAULT_SOURCE 		: undefined\n");
#endif

#ifdef _ATFILE_SOURCE
	printf("_ATFILE_SOURCE 			: defined\n");
#else
	printf("_ATFILE_SOURCE 			: undefined\n");
#endif

#ifdef _GNU_SOURCE
	printf("_GNU_SOURCE 			: defined\n");
#else
	printf("_GNU_SOURCE		 		: undefined\n");
#endif

#ifdef _REENTRANT
	printf("_REENTRANT 			: defined\n");
#else
	printf("_REENTRANT		 	: undefined\n");
#endif

#ifdef _THREAD_SAFE
	printf("_THREAD_SAFE 			: defined\n");
#else
	printf("_THREAD_SAFE 			: undefined\n");
#endif

#ifdef _FORTIFY_SOURCE
	printf("_FORTIFY_SOURCE 		: defined\n");
#else
	printf("_FORTIFY_SOURCE 		: undefined\n");
#endif

	printf("\n");
	printf("Checking for required system headers...\n");
	printf("\n");

	const char* header_found = { "Success" };
	const char* header_missing = { "Fail" };

#if defined(HAVE_MNTENT_H)
	printf("<mntent.h>			: %s\n", header_found);
#else
	printf("<mntent.h>			: %s\n", header_missing);
#endif

#if defined(HAVE_SYS_MNTTAB_H)
    printf("<sys/mnttab.h>			: %s\n", header_found);
#else
	printf("<sys/mnttab.h>			: %s\n", header_missing);
#endif

#if defined(HAVE_SYS_MOUNT_H)
    printf("<sys/mount.h>			: %s\n", header_found);
#else
    printf("<sys/mount.h>			: %s\n", header_missing);
#endif

#if defined(HAVE_SYS_PARAM_H)
    printf("<sys/param.h>			: %s\n", header_found);
#else
    printf("<sys/param.h>			: %s\n", header_missing);
#endif

#if defined(HAVE_SYS_PARAM_H)
    printf("<sys/param.h>			: %s\n", header_found);
#else
    printf("<sys/param.h>			: %s\n", header_missing);
#endif

#if defined(HAVE_SYS_STATVFS_H)
    printf("<sys/statvfs.h>			: %s\n", header_found);
#else
    printf("<sys/statvfs.h>			: %s\n", header_missing);
#endif

#if defined(HAVE_SYS_TYPES_H)
    printf("<sys/types.h>			: %s\n", header_found);
#else
    printf("<sys/types.h>			: %s\n", header_missing);
#endif

#if defined(HAVE_SYS_UCRED_H)
    printf("<sys/ucred.h>			: %s\n", header_found);
#else
    printf("<sys/ucred.h>			: %s\n", header_missing);
#endif

#if defined(HAVE_TERMIOS_H)
    printf("<termios.h>			: %s\n", header_found);
#else
	printf("<termios.h>			: %s\n", header_missing);
#endif

	printf("...pkgman_config > Exiting successfully.\n");

	return(EXIT_SUCCESS);
}
