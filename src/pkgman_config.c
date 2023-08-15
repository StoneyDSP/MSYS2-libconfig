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

#include <errno.h>

#include "pkgman_config.h"
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

/***************************************************************************//**
 *
 *   ... System Header flags
 *
 ******************************************************************************/

/** Set flags for portability */
#if defined(HAVE_SYS_MNTTAB_H)
#  define _PKGMAN_HAS_SYS_MNTTAB_H (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_SYS_MNTTAB_H (enum pkgman_test_result)TEST_FAIL
#endif
#if defined(HAVE_SYS_MOUNT_H)
#  define _PKGMAN_HAS_SYS_MOUNT_H (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_SYS_MOUNT_H (enum pkgman_test_result)TEST_FAIL
#endif
#if defined(HAVE_SYS_PARAM_H)
#  define _PKGMAN_HAS_SYS_PARAM_H (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_SYS_PARAM_H (enum pkgman_test_result)TEST_FAIL
#endif
#if defined(HAVE_SYS_RESOURCE_H)
#  define _PKGMAN_HAS_SYS_RESOURCE_H (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_SYS_RESOURCE_H (enum pkgman_test_result)TEST_FAIL
#endif
#if defined(HAVE_SYS_STAT_H)
#  define _PKGMAN_HAS_SYS_STAT_H (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_SYS_STAT_H (enum pkgman_test_result)TEST_FAIL
#endif
#if defined(HAVE_SYS_STATFS_H)
#  define _PKGMAN_HAS_SYS_STATFS_H (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_SYS_STATFS_H (enum pkgman_test_result)TEST_FAIL
#endif
#if defined(HAVE_SYS_STATVFS_H)
#  define _PKGMAN_HAS_SYS_STATVFS_H (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_SYS_STATVFS_H (enum pkgman_test_result)TEST_FAIL
#endif
#if defined(HAVE_SYS_TYPES_H)
#  define _PKGMAN_HAS_SYS_TYPES_H (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_SYS_TYPES_H (enum pkgman_test_result)TEST_FAIL
#endif
#if defined(HAVE_SYS_TIME_H)
#  define _PKGMAN_HAS_SYS_TIME_H (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_SYS_TIME_H (enum pkgman_test_result)TEST_FAIL
#endif
#if defined(HAVE_SYS_UCRED_H)
#  define _PKGMAN_HAS_SYS_UCRED_H (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_SYS_UCRED_H (enum pkgman_test_result)TEST_FAIL
#endif
#if defined(HAVE_TERMIOS_H)
#  define _PKGMAN_HAS_TERMIOS_H (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_TERMIOS_H (enum pkgman_test_result)TEST_FAIL
#endif
#if defined(HAVE_MNTENT_H)
#  define _PKGMAN_HAS_MNTENT_H (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_MNTENT_H (enum pkgman_test_result)TEST_FAIL
#endif

/***************************************************************************//**
 *
 *   ... Dependency Header flags
 *
 ******************************************************************************/

#if defined(HAVE_ARCHIVE_H)
#  define PKGMAN_HAS_LIBARCHIVE_LIB (enum pkgman_test_result)TEST_PASS
#else
#  define PKGMAN_HAS_LIBARCHIVE_LIB (enum pkgman_test_result)TEST_FAIL
#endif

#if defined(HAVE_CURL_CURL_H)
#  define PKGMAN_HAS_LIBCURL_LIB (enum pkgman_test_result)TEST_PASS
#else
#  define PKGMAN_HAS_LIBCURL_LIB (enum pkgman_test_result)TEST_FAIL
#endif

#if defined(HAVE_GPGME_H)
#  define PKGMAN_HAS_LIBGPGME_LIB (enum pkgman_test_result)TEST_PASS
#else
#  define PKGMAN_HAS_LIBGPGME_LIB (enum pkgman_test_result)TEST_FAIL
#endif

#if defined(HAVE_LIBINTL_H)
#  define PKGMAN_HAS_LIBINTL_LIB (enum pkgman_test_result)TEST_PASS
#else
#  define PKGMAN_HAS_LIBINTL_LIB (enum pkgman_test_result)TEST_FAIL
#endif

/***************************************************************************//**
 *
 *   ... Function Symbol flags
 *
 ******************************************************************************/

#if defined(HAVE_GETMNTENT)
#  define _PKGMAN_HAS_GETMNTENT (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_GETMNTENT (enum pkgman_test_result)TEST_FAIL
#endif

#if defined(HAVE_GETMNTINFO)
#  define _PKGMAN_HAS_GETMNTINFO (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_GETMNTINFO (enum pkgman_test_result)TEST_FAIL
#endif

#if defined(HAVE_STRNDUP)
#  define _PKGMAN_HAS_STRNDUP (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_STRNDUP (enum pkgman_test_result)TEST_FAIL
#endif

#if defined(HAVE_STRNLEN)
#  define _PKGMAN_HAS_STRNLEN (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_STRNLEN (enum pkgman_test_result)TEST_FAIL
#endif

#if defined(HAVE_STRSEP)
#  define _PKGMAN_HAS_STRSEP (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_STRSEP (enum pkgman_test_result)TEST_FAIL
#endif

#if defined(HAVE_SWPRINTF)
#  define _PKGMAN_HAS_SWPRINTF (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_SWPRINTF (enum pkgman_test_result)TEST_FAIL
#endif

#if defined(HAVE_TCFLUSH)
#  define _PKGMAN_HAS_TCFLUSH (enum pkgman_test_result)TEST_PASS
#else
#  define _PKGMAN_HAS_TCFLUSH (enum pkgman_test_result)TEST_FAIL
#endif


#if !defined(HAVE_STRUCT_STATVFS_F_FLAG)
#  define _PKGMAN_HAS_STRUCT_STATVFS_F_FLAG (enum pkgman_test_result)TEST_FAIL
#else
#  define _PKGMAN_HAS_STRUCT_STATVFS_F_FLAG (enum pkgman_test_result)TEST_PASS
#endif

#if !defined(HAVE_STRUCT_STATFS_F_FLAGS)
#  define _PKGMAN_HAS_STRUCT_STATFS_F_FLAGS (enum pkgman_test_result)TEST_FAIL
#else
#  define _PKGMAN_HAS_STRUCT_STATFS_F_FLAGS (enum pkgman_test_result)TEST_PASS
#endif

#if !defined(HAVE_STRUCT_STAT_ST_BLKSIZE)
#  define _PKGMAN_HAS_STRUCT_STAT_ST_BLKSIZE (enum pkgman_test_result)TEST_FAIL
#else
#  define _PKGMAN_HAS_STRUCT_STAT_ST_BLKSIZE (enum pkgman_test_result)TEST_PASS
#endif


/**
 * @name checkForFile
 * @brief Uses 'stat()' to check if a file exists on disk and can be opened during runtime.
 * Returns 0 if the file is found and opened successfully, or the associated error value otherwise.
 * @param filename The fully-qualified file name to check for, including the path.
 * @return int = { 0 || errno }
 */
int checkForFile(const char* filename)
{
	struct stat buffer;
	int fileCheckResult;

	fileCheckResult = stat(filename, &buffer);

	if ((fileCheckResult) != 0)  {

		printf("Fail    :: '%s' [%d]\n", filename, fileCheckResult);

	} else {

		printf("Success :: '%s'\n", filename);
	}

	return (fileCheckResult);
}

/**
 * @name checkForDir
 * @brief Uses 'opendir()' to check if a directory exists on disk and can be opened during runtime.
 * Returns 0 if the dir is found and opened successfully, or the associated error value otherwise.
 * @param pathToDir The fully-qualified path to the directory to be checked.
 * @return int = { 0 || errno }
 */
int checkForDir(const char* pathToDir)
{
	/** Check for dir path... this could be more thorough, of course... */
	DIR *dip;
	struct dirent *dit;
	struct stat lsbuf;
	char currentPath[FILENAME_MAX];

	const char* dir_path = pathToDir;

	dip = opendir(dir_path);

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
	}

	if (!(S_ISDIR(lsbuf.st_mode)))  {

		printf("\"%s\" does not exist on this system.\n", dir_path);

		return (-1);
	}

	printf("\"%s\" exists on this system.\n", dir_path);

	return (0);
}


/**
 * @name checkForLib
 * @brief Uses 'dlopen()' to check if a dynamic library exists/can be opened during runtime.
 * Returns 0 if the lib is found and opened successfully, or the associated error value otherwise.
 * @param libName The fully-qualified lib name to check for.
 * @return int = { 0 || errno }
 */
int checkForLib(const char* libName)
{
	void* handle;
	char *error;

	handle = dlopen(libName, RTLD_LAZY);

	dlerror(); /* Clear any existing error */

	error = dlerror();

	if ((!handle) || (error != NULL))  {

		printf("Fail    :: '%s' [%d]: %s\n", libName, errno, error);

		return errno;
	}

	dlclose(handle);

	printf("Success :: '%s'\n", libName);

	return (0);
}


#if (__CYGWIN__)
#  if defined(ID_VOID_MAIN)
void WinMain() {}
#  elif defined(__CLASSIC_C__)
int WinMain(argc, argv) int argc; char** argv;
#    else
int WinMain(int argc, char** argv)
#    endif
#else
#  if defined(ID_VOID_MAIN)
void main() {}
#  elif defined(__CLASSIC_C__)
int main(argc, argv) int argc; char** argv;
#    else
int main(int argc, char** argv)
#    endif
#endif
{
	/**
	 * int i = 0;
	 * for (i = 0; i < argc; i++) printf("%s\n", argv[i]);
	 *
	*/



	printf("\n");
	printf("pkgman_config");

	#ifdef PKGMAN_VERSION
		printf(" v%d.%d.%d", PKGMAN_VERSION_MAJOR, PKGMAN_VERSION_MINOR, PKGMAN_VERSION_PATCH);
		printf("-%s", PKGMAN_VERSION_TWEAK);
	#endif
	printf("\n"); /** Needed for nice formatting! */

	printf("\n");
	printf("Checking for msys installation...\n");
	printf("\n");

	char* msys_cmd = { "C:/msys64/msys2_shell.cmd" };
	char* msys_autorebase = { "C:/msys64/autorebase.bat" };

	int have_msys_cmd 			= checkForFile(msys_cmd);
	int have_msys_autorebase 	= checkForFile(msys_autorebase);

	printf("\n");
	printf("Checking for required system headers...\n");
	printf("\n");

	struct pkgman_required_headers* PkgmanGetHeaders = &PkgmanHeaders;

	if (PKGMAN_HAS_MNTENT_H)
		PkgmanHeaders.have_mntent_h = HEADER_FOUND;

	if (PKGMAN_HAS_SYS_MNTTAB_H)
		PkgmanHeaders.have_sys_mnt_tab_h = HEADER_FOUND;

	if (PKGMAN_HAS_SYS_PARAM_H)
		PkgmanHeaders.have_sys_param_h = HEADER_FOUND;

	if (PKGMAN_HAS_SYS_RESOURCE_H)
		PkgmanHeaders.have_sys_resource_h = HEADER_FOUND;

	if (PKGMAN_HAS_SYS_STAT_H)
		PkgmanHeaders.have_sys_stat_h = HEADER_FOUND;

	if (PKGMAN_HAS_SYS_STATFS_H)
		PkgmanHeaders.have_sys_statfs_h = HEADER_FOUND;

	if (PKGMAN_HAS_SYS_STATVFS_H)
		PkgmanHeaders.have_sys_statvfs_h = HEADER_FOUND;

	if (PKGMAN_HAS_SYS_TIME_H)
		PkgmanHeaders.have_sys_time_h = HEADER_FOUND;

	if (PKGMAN_HAS_SYS_TYPES_H)
		PkgmanHeaders.have_sys_types_h = HEADER_FOUND;

	if (PKGMAN_HAS_SYS_UCRED_H)
		PkgmanHeaders.have_sys_ucred_h = HEADER_FOUND;

	if (PkgmanGetHeaders->have_mntent_h == HEADER_FOUND)
	{
		printf("Success :: '%s'\n", "<mntent.h>");
	} else {
		printf("Failed  :: '%s'\n", "<mntent.h>");
	}

	if(PkgmanGetHeaders->have_sys_mnt_tab_h == HEADER_FOUND)
	{
		printf("Success :: '%s'\n", "<sys/mnttab.h>");
	} else {
		printf("Failed  :: '%s'\n", "<sys/mnttab.h>");
	}

	if (PkgmanGetHeaders->have_sys_mount_h == HEADER_FOUND)
	{
		printf("Success :: '%s'\n", "<sys/mount.h>");
	} else {
    	printf("Failed  :: '%s'\n", "<sys/mount.h>");
	}


	if (PkgmanGetHeaders->have_sys_param_h == HEADER_FOUND)
	{
		printf("Success :: '%s'\n", "<sys/param.h>");
	} else {
		printf("Failed  :: '%s'\n", "<sys/param.h>");
	}

	if (PkgmanGetHeaders->have_sys_stat_h == HEADER_FOUND)
	{
		printf("Success :: '%s'\n", "<sys/stat.h>");
	} else {
		printf("Failed  :: '%s'\n", "<sys/stat.h>");
	}


	if (PkgmanGetHeaders->have_sys_statvfs_h == HEADER_FOUND)
	{
		printf("Success :: '%s'\n", "<sys/statvfs.h>");
	} else {
		printf("Failed  :: '%s'\n", "<sys/statvfs.h>");
	}

	if (PkgmanGetHeaders->have_sys_types_h == HEADER_FOUND)
	{
		printf("Success :: '%s'\n", "<sys/types.h>");
	} else {
		printf("Failed  :: '%s'\n", "<sys/types.h>");
	}

	if (PkgmanGetHeaders->have_sys_ucred_h == HEADER_FOUND)
	{
		printf("Success :: '%s'\n", "<sys/ucred.h>");
	} else {
		printf("Failed  :: '%s'\n", "<sys/ucred.h>");
	}

	if (PkgmanGetHeaders->have_termios_h == HEADER_FOUND)
	{
		printf("Success :: '%s'\n", "<termios.h>");
	} else {
		printf("Failed  :: '%s'\n", "<termios.h>");
	}

	printf("\n");
	printf("Checking for required library dependencies...\n");
	printf("\n");

	int have_ucrtbase = checkForLib(UCRTBASE_DYNAMIC_LIB); /** UCRTBASE_LIB_PATH */
	int have_msvcrt = checkForLib(MSVCRT_DYNAMIC_LIB); /** MSVCRT_LIB_PATH */
	int have_lib_msys = checkForLib(MSYS_LIB); /** MSYS_INSTALL_PATH */
	int have_libcrypto = checkForLib(CRYPTO_LIB); /** CRYPTO_H_PATH */
	int have_libcurl = checkForLib(LIBCURL_LIB); /** CURL_H_PATH */
	int have_libgpgme = checkForLib(LIBGPGME_LIB); /** GPGME_H_PATH */

	#define HAVE_LIBCURL have_libcurl
	#define HAVE_LIBGPGME have_libcurl

	printf("\n");
	printf("Checking for required functions...\n");
	printf("\n");

	struct pkgman_required_symbols* PkgmanGetSymbols = &PkgmanSymbols;

	if (PKGMAN_HAS_GETMNTENT)
		PkgmanSymbols.have_getmntent = SYMBOL_FOUND;

	if (PKGMAN_HAS_GETMNTINFO)
		PkgmanSymbols.have_getmntinfo = SYMBOL_FOUND;

	if (PKGMAN_HAS_STRNDUP)
		PkgmanSymbols.have_strndup = SYMBOL_FOUND;

	if (PKGMAN_HAS_STRNLEN)
		PkgmanSymbols.have_strnlen = SYMBOL_FOUND;

	if (PKGMAN_HAS_STRSEP)
		PkgmanSymbols.have_strsep = SYMBOL_FOUND;

	if (PKGMAN_HAS_SWPRINTF)
		PkgmanSymbols.have_swprintf = SYMBOL_FOUND;

	if (PKGMAN_HAS_TCFLUSH)
		PkgmanSymbols.have_tcflush = SYMBOL_FOUND;

	if (PkgmanGetSymbols->have_getmntent == SYMBOL_FOUND)
	{
		printf("Success :: '%s'\n", "getmntent()");
	} else {
		printf("Failed  :: '%s'\n", "getmntent()");
	}

	if (PkgmanGetSymbols->have_getmntinfo == SYMBOL_FOUND)
	{
		printf("Success :: '%s'\n", "getmntinfo()");
	} else {
		printf("Failed  :: '%s'\n", "getmntinfo()");
	}

	if (PkgmanGetSymbols->have_strndup == SYMBOL_FOUND)
	{
		printf("Success :: '%s'\n", "strndup()");
	} else {
		printf("Failed  :: '%s'\n", "strndup()");
	}

	if (PkgmanGetSymbols->have_strnlen == SYMBOL_FOUND)
	{
		printf("Success :: '%s'\n", "strnlen()");
	} else {
		printf("Failed  :: '%s'\n", "strnlen()");
	}

	if (PkgmanGetSymbols->have_strsep == SYMBOL_FOUND)
	{
		printf("Success :: '%s'\n", "strsep()");
	} else {
		printf("Failed  :: '%s'\n", "strsep()");
	}

	if (PkgmanGetSymbols->have_swprintf == SYMBOL_FOUND)
	{
		printf("Success :: '%s'\n", "swprintf()");
	} else {
		printf("Failed  :: '%s'\n", "swprintf()");
	}

	if (PkgmanGetSymbols->have_tcflush == SYMBOL_FOUND)
	{
		printf("Success :: '%s'\n", "tcflush()");
	} else {
		printf("Failed  :: '%s'\n", "tcflush()");
	}

/**
 * #if defined(__CYGWIN__) && CYGWIN_VERSION_API_MINOR < 262
 * void *libc = dlopen ("cygwin1.dll", 0);
 * struct mntent *(*getmntent_r) (FILE *, struct mntent *, char *, int) = dlsym (libc, "getmntent_r");
 * #endif
*/

/**
 * printf("\n");
 * printf("Feature detection macros:\n");
 * printf("\n");
 *
 * #ifdef _POSIX_SOURCE
 *   printf("_POSIX_SOURCE 			: defined\n");
 * #else
 *   printf("_POSIX_SOURCE	 		: undefined\n");
 * #endif
 *
 * #ifdef _POSIX_C_SOURCE
 *   printf("_POSIX_C_SOURCE 		: defined = %jdL\n", (intmax_t) _POSIX_C_SOURCE);
 * #else
 *   printf("_POSIX_C_SOURCE 		: undefined\n");
 * #endif
 *
 * #ifdef _ISOC99_SOURCE
 *   printf("_ISOC99_SOURCE 			: defined\n");
 * #else
 *   printf("_ISOC99_SOURCE 			: undefined\n");
 * #endif
 *
 * #ifdef _ISOC11_SOURCE
 *   printf("_ISOC11_SOURCE 			: defined\n");
 * #else
 *   printf("_ISOC11_SOURCE	 		: undefined\n");
 * #endif
 *
 * #ifdef _XOPEN_SOURCE
 *   printf("_XOPEN_SOURCE 			: defined = %d\n", _XOPEN_SOURCE);
 * #else
 *   printf("_XOPEN_SOURCE	 		: undefined\n");
 * #endif
 *
 * #ifdef _XOPEN_SOURCE_EXTENDED
 *   printf("_XOPEN_SOURCE_EXTENDED		: defined\n");
 * #else
 *   printf("_XOPEN_SOURCE_EXTENDED		: undefined\n");
 * #endif
 *
 * #ifdef _LARGEFILE64_SOURCE
 *   printf("_LARGEFILE64_SOURCE		: defined\n");
 * #else
 *   printf("_LARGEFILE64_SOURCE		: undefined\n");
 * #endif
 *
 * #ifdef _FILE_OFFSET_BITS
 *   printf("_FILE_OFFSET_BITS 		: defined = %d\n", _FILE_OFFSET_BITS);
 * #else
 *   printf("_FILE_OFFSET_BITS 		: undefined\n");
 * #endif
 *
 * #ifdef _TIME_BITS
 *   printf("_TIME_BITS 			: defined = %d\n", _TIME_BITS);
 * #else
 *   printf("_TIME_BITS		 	: undefined\n");
 * #endif
 *
 * #ifdef _BSD_SOURCE
 *   printf("_BSD_SOURCE 			: defined\n");
 * #else
 *   printf("_BSD_SOURCE 			: undefined\n");
 * #endif
 *
 * #ifdef _SVID_SOURCE
 *   printf("_SVID_SOURCE 			: defined\n");
 * #else
 *   printf("_SVID_SOURCE 			: undefined\n");
 * #endif
 *
 * #ifdef _DEFAULT_SOURCE
 *   printf("_DEFAULT_SOURCE 		: defined\n");
 * #else
 *   printf("_DEFAULT_SOURCE 		: undefined\n");
 * #endif
 *
 * #ifdef _ATFILE_SOURCE
 *   printf("_ATFILE_SOURCE 			: defined\n");
 * #else
 *   printf("_ATFILE_SOURCE 			: undefined\n");
 * #endif
 *
 * #ifdef _GNU_SOURCE
 *   printf("_GNU_SOURCE 			: defined\n");
 * #else
 *   printf("_GNU_SOURCE		 		: undefined\n");
 * #endif
 *
 * #ifdef _REENTRANT
 *   printf("_REENTRANT 			: defined\n");
 * #else
 *   printf("_REENTRANT		 	: undefined\n");
 * #endif
 *
 * #ifdef _THREAD_SAFE
 *   printf("_THREAD_SAFE 			: defined\n");
 * #else
 *   printf("_THREAD_SAFE 			: undefined\n");
 * #endif
 *
 * #ifdef _FORTIFY_SOURCE
 *   printf("_FORTIFY_SOURCE 		: defined\n");
 * #else
 *   printf("_FORTIFY_SOURCE 		: undefined\n");
 * #endif
 *
 * #ifdef __USE_MINGW_ANSI_STDIO
 *   printf("__USE_MINGW_ANSI_STDIO 		: defined\n");
 * #else
 *   printf("__USE_MINGW_ANSI_STDIO 		: undefined\n");
 * #endif
 *
*/

	printf("\n");
	printf("Build information:\n\n");

	printf("prefix                  : %s\n", 									PkgmanGetCommandLine->prefix);
  	printf("sysconfdir              : %s\n", 									PkgmanGetCommandLine->sysconfdir);
  	printf("conf file           	: %s\n", 									PkgmanGetConf->conffile);
  	printf("localstatedir           : %s\n", 									PkgmanGetCommandLine->localstatedir);
  	printf("database dir        	: %s\n", 									PkgmanGetConf->dbpath);
  	printf("cache dir           	: %s\n", 									PkgmanGetConf->cachedir);
	printf("compiler 		: %s\n", 											PkgmanGetSettings->pkgman_c_compiler);

	printf("\n");

	printf("Architecture            : @0@'.format(carch)\n");
  	printf("Host Type               : @0@'.format(chost)\n");
  	printf("File inode command      : @0@'.format(inodecmd)\n");
  	printf("File seccomp command    : @0@'.format(filecmd)\n");
  	printf("libalpm version         : %s\n", 									PkgmanGetConf->libalpm_version);
    printf("pacman version          : %s\n", 									PkgmanGetSettings->pkgman_version);

	printf("\n");

	printf("Directory and file information:\n\n");

	printf("root working directory  : %s\n", 									PkgmanGetCommandLine->rootdir);
  	printf("package extension       : %s\n", 									PkgmanGetSettings->pkg_ext);
    printf("source pkg extension    : %s\n", 									PkgmanGetSettings->src_ext);
    printf("build script name       : %s\n", 									PkgmanGetCommandLine->buildscript);
    printf("template directory      : %s\n",	 								PkgmanGetSettings->makepkg_template_dir);

	printf("\n");

	printf("Compilation options:\n\n");

	printf("i18n support            : @0@'.format(get_option('i18n'))\n");
    printf("Build docs              : @0@'.format(build_doc)\n");

#if (PKGMAN_DEBUG == 1)
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

	printf("pkgman_config");

	#ifdef PKGMAN_VERSION
		printf(" v%d.%d.%d", PKGMAN_VERSION_MAJOR, PKGMAN_VERSION_MINOR, PKGMAN_VERSION_PATCH);
		printf("-%s", PKGMAN_VERSION_TWEAK);
	#endif
	printf("\n"); /** Needed for nice formatting! */

	printf("Copyright (C) 2023 Nathan J. Hood (StoneyDSP) <nathanjhood@googlemail.com>\n");
	printf("\n");
	printf("License GPLv2: <https://gnu.org/licenses/gpl.htm>\n");
	printf("This software comes with ABSOLUTELY NO WARRANTY; This is free software, and you are free to change and redistribute it.\n");
	printf("\n");
	printf("Home page URL: https://github.com/StoneyDSP/msys2-libconfig.git\n");
	printf("Bug reports: https://github.com/StoneyDSP/msys2-libconfig/issues\n");

	return(EXIT_SUCCESS);
}
