/**
 * @file msystem.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <dirent.h> /* DIR */
#include <unistd.h> /* DIR - This is the Posix C Library */
#include <errno.h>


#ifdef __CYGWIN__
#  include <dlfcn.h>
#  include <cygwin/version.h>
#endif

#include "msystem/msystem.h"


#if (__WIN32__) || (__CYGWIN__)
int WinMain()
{
#else
int main()
{
#endif

	printf("\n");

	printf("Msystem information:\n\n");

	printf("MSYSTEM_CARCH           : %s\n", MSYSTEM_CARCH);
  	printf("MSYSTEM_CHOST           : %s\n", MSYSTEM_CHOST);
  	printf("MSYSTEM_PREFIX      	: %s\n", MSYSTEM_PREFIX);
	printf("MINGW_CHOST           	: %s\n", MINGW_CHOST);
  	printf("MINGW_PREFIX            : %s\n", MINGW_PREFIX);
  	printf("MINGW_PACKAGE_PREFIX    : %s\n", MINGW_PACKAGE_PREFIX);


	printf("\n");

	printf("Directory and file information:\n\n");

	printf("root working directory  : %d\n", MSYSTEM);
  	printf("package extension       : @0@'.format(get_option('pkg-ext'))\n");
    printf("  source pkg extension  : @0@'.format(get_option('src-ext'))\n");
    printf("build script name       : @0@'.format(BUILDSCRIPT)\n");
    printf("template directory      : @0@'.format(get_option('makepkg-template-dir'))\n");

	printf("\n");

	printf("Compilation options:\n\n");

	printf("i18n support            : @0@'.format(get_option('i18n'))\n");
    printf("Build docs              : @0@'.format(build_doc)\n");
  	printf("debug build             : @0@'.format(get_option('buildtype') == 'debug')\n");
  	printf("Use libcurl             : @0@'.format(conf.get('HAVE_LIBCURL'))\n");
  	printf("Use GPGME               : @0@'.format(conf.get('HAVE_LIBGPGME'))\n");
  	printf("Use OpenSSL             : @0@'.format(conf.has('HAVE_LIBSSL') and conf.get('HAVE_LIBSSL') == 1)\n");
  	printf("Use nettle              : @0@'.format(conf.has('HAVE_LIBNETTLE') and conf.get('HAVE_LIBNETTLE') == 1)\n");

	printf("\n");


	DIR *dip;
    struct dirent *dit;
    struct stat lsbuf;
    char currentPath[__FILENAME_MAX__];

	const char* msys_install_path = {"C:/msys64"};

    if((dip = opendir(msys_install_path)) == NULL)
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
    }

    if(S_ISDIR(lsbuf.st_mode)) {
		printf("\n");
		printf("msys_install_path <%d> exists on this system.\n", msys_install_path);
		printf("\n");
    } else {
		printf("\n");
		printf("msys_install_path <%d> does not exist on this system.\n", msys_install_path);
		printf("\n");
	}

	void* handle;
	char *error;

	handle = dlopen(MSYSTEM_RUNTIME_LIBRARY, RTLD_LAZY);
	error = dlerror();

	if (!handle || error != NULL)
	{
		printf("\n");
		fprintf(stderr, "Loading 'msys-2.0.dll' attempt failed: %s\n", error);
		printf("\n");
		exit(EXIT_FAILURE);
	} else {
		printf("\n");
		printf("Loaded 'msys-2.0.dll' successfully.\n");
		printf("\n");
#define HAVE_OPENSSL 1
	}

    struct mntent *(*getmntent_r) (FILE *, struct mntent *, char *, int) = dlsym (handle, "getmntent_r");

	dlclose(handle);

	return(EXIT_SUCCESS);
}
