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

#ifdef __CYGWIN__
#  include <dlfcn.h>
#  include <dirent.h>
#  include <unistd.h>
#  include <cygwin/version.h>
#endif

// #include <sys/types.h>
// #include <sys/stat.h>




#if __has_include(<nettle/crypto.h>)
#  include <nettle/crypto.h>
#  define HAVE_LIBNETTLE 1
#elif __has_include(<openssl/crypto.h>)
#  include <openssl/crypto.h>
#  define HAVE_LIBSSL 1
#else
#  error "No crypto provider found!?"
#endif

#include "pkgman/pkgman_config.h"
#ifndef PKGMAN_CONFIGURATION_H
# error "No config header found?"
#endif

#if (HAVE_LIBNETTLE)
#  define CRYPTO_INCLUDE_SYMBOL __PM_STRING(<nettle/crypto.h>)
#elif (HAVE_LIBSSL)
#  define CRYPTO_INCLUDE_SYMBOL __PM_STRING(<openssl/crypto.h>)
#endif

#define CRYPTO_LIB __PM_STRING(libcrypto.dll)

#if HAVE_LIBSSL
#  define CRYPTO_H_PATH __PM_STRING(C:/msys64/usr/include/openssl)
#elif HAVE_LIBNETTLE
#  define CRYPTO_H_PATH __PM_STRING(C:/msys64/usr/include/nettle)
#endif



/**
 * Get the chosen crypto lib
*/
int checkForLibCrytpo()
{
	/** Check for header path... this could be more thorough, of course... */
	DIR *dip;
	struct dirent *dit;
	struct stat lsbuf;
	char currentPath[__FILENAME_MAX__];

	const char* crypto_header_path = { CRYPTO_H_PATH };

	dip = opendir(CRYPTO_H_PATH);

	if((dip) == NULL)
	{
		perror("opendir()");
		return errno;
	}

	if((getcwd(currentPath, FILENAME_MAX)) == NULL)
	{
		perror("getcwd()");
		return errno;
	}

	/* stat the file - if it exists, do some checks */
		if(stat(currentPath, &lsbuf) == -1)
	{
		perror("stat()");
		return errno;

	} else {

		if(S_ISDIR(lsbuf.st_mode)) {

			printf("\"%s\" exists on this system.\n", CRYPTO_H_PATH);

		} else {

			printf("\"%s\" does not exist on this system.\n", CRYPTO_H_PATH);

			printf("\n");

			exit(EXIT_FAILURE);
		}

		printf("Included '%s' successfully.\n", CRYPTO_INCLUDE_SYMBOL);
	}

	/** Get the chosen crypto lib */
	void* handle;
	char *error;

	handle = dlopen(CRYPTO_LIB, RTLD_LAZY);
	error = dlerror();

	if (!handle || error != NULL)
	{
		fprintf(stderr, "Loading 'libcrypto.dll' attempt failed: %s\n", error);

		exit(EXIT_FAILURE);

	} else {

		printf("Loaded '%s' successfully.\n", CRYPTO_LIB);
	}

	dlclose(handle);

	return (0);
}



/**
 * Get the chosen lib
*/
int checkForLib(const char* pathToHeader, const char* libName)
{
	/** Check for header path... this could be more thorough, of course... */
	DIR *dip;
	struct dirent *dit;
	struct stat lsbuf;
	char currentPath[__FILENAME_MAX__];

	const char* header_path = pathToHeader;

	dip = opendir(header_path);

	if((dip) == NULL)
	{
		perror("opendir()");
		return errno;
	}

	if((getcwd(currentPath, FILENAME_MAX)) == NULL)
	{
		perror("getcwd()");
		return errno;
	}

	/* stat the file - if it exists, do some checks */
		if(stat(currentPath, &lsbuf) == -1)
	{
		perror("stat()");
		return errno;

	} else {

		if(S_ISDIR(lsbuf.st_mode)) {

			printf("\"%s\" exists on this system.\n", header_path);

		} else {

			printf("\"%s\" does not exist on this system.\n", header_path);

			printf("\n");
		}
	}

	/** Get the chosen crypto lib */
	void* handle;
	char *error;

	handle = dlopen(libName, RTLD_LAZY);
	error = dlerror();

	if (!handle || error != NULL)
	{
		/** fprintf(stderr, "Loading 'libcrypto.dll' attempt failed: %s\n", error); */

		printf("Loading '%s' attempt failed.\n", libName);

		/** exit(EXIT_FAILURE); */

	} else {

		printf("Loaded '%s' successfully.\n", libName);
	}

	dlclose(handle);

	return (0);
}


	printf("\n");

	printf("\n");
	printf("Compiler info:\n");
	printf("\n");

#ifdef PKGMAN_CLANG_VERSION
	printf("PKGMAN_CLANG_VERSION: %d\n", PKGMAN_CLANG_VERSION);
#endif

#ifdef PKGMAN_GCC_VERSION
	printf("PKGMAN_GCC_VERSION: %d\n", PKGMAN_GCC_VERSION);
#endif

#ifdef PKGMAN_ICC_VERSION
	printf("PKGMAN_ICC_VERSION: %d\n", PKGMAN_ICC_VERSION);
#endif

#ifdef PKGMAN_MSC_VERSION
	printf("PKGMAN_MSC_VERSION: %d\n", PKGMAN_MSC_VERSION);
#endif

	printf("\n");

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

	printf("\n");
	printf("Checking for dependencies...\n");
	printf("\n");

	/** checkForLibCrytpo(); */

	/** printf("\n"); */

	checkForLib(CRYPTO_H_PATH, CRYPTO_LIB);

	return(EXIT_SUCCESS);
}
