# MSYS2-libconfig

A configuration header/library/executable to make it easier to build arch-linux 'pacman/alpm'-derived projects, thanks to modern C.

## latest...

## 16.08.23

How cool is C though? This is really my first contact with a project primarily written in (procedural) C, and I feel that having already battled both C++ and Javascript - and their individual foibles, quirks, and strengths - I really enjoy C as a powerful system-level tool that is necessarily both primitive, *and* strict.

Experience was suggesting to me that I probably had excessive allocations in 'main()', and uncertain code paths due to over-reliance on pre-processor 'ifdef's.

Furthermore, 'stringizing' using the classic preprocessor macro function sure is handy, but it doesn't null-terminate itself; nor really should it, if you're concatenating as much as we are here. Ignoring null-termination of these strings leaves us wide open to blowing holes in our memory allocations, even if we're passing to 'char array[]' of size '[FILENAME_MAX]' or so forth; the lack of null termination results in the remainder of the array being filled with zero's, meaning wasting a lot of memory footprint that we never actually needed anyway.

Considering that we would also like to be able to override many of these variables on the command line - which is tricky to stringify using macro functions combined with fallback cases - it would seem to make sense to investigate a new approach from the ground up, which fully incorporates the requirements.

Lastly, global variables are generally questionable practice when sharing code downstream with other projects. Even worse when they have very generic names, such as 'prefix'...

To this end, I refactored the configuration header to provide 'pkgman_\*' structs; data structures which group together all of the various project-required information, such as taking our 'const char* prefix = PREFIX' and morphing it into something you can call, like 'pkgman_config::prefix' which is a (null-terminated!) char array.

The expectation is that one can allocate one of these structs on the stack (i.e., inside a function call, probably 'main()'), perform a set of checks, an pass the check results (by reference!) back to the struct's members. Null-termination of computed strings would get taken care of tat the point of allocation. The populated struct can then be called from wherever, for example when another section of code requires the 'prefix' variable.

As a means of comparison, here is a short 'before/after' of the overall design so far.

Simple (before) approach, bugs'n'all:

```

#if __has_include(<stdio.h>)
  /**
   * Get 'printf()'
   */
#  include <stdio.h>
#  define HAS_STDIO_H 1
#else
#  define HAS_STDIO_H 0
#endif

/**
 * Stringify function macro (and sub-function)
 */
#define __STRINGIFY(X) #X
#define STRINGIFY(X) __STRINGIFY(X)

#ifndef PREFIX
#define PREFIX STRINGIFY(/usr)
#endif

/**
 * Use the value of 'HAS_STDIO_H' to determine if can use 'printf()'
 */
#define PRINT_PREFIX HAS_STDIO_H

/**
 * Assign 'PREFIX' to a global char array of system-dependent size '[PATH_MAX]'
 */
char prefix[PATH_MAX] = { PREFIX };

int main()
{

#if (PRINT_PREFIX == 1)

	printf("%s", prefix)

	return(0);

#else

	/**
	 * Error: Nothing to do...
	 */

	 return(1);

#endif

}
```

If the above actually compiles (I suspect it won't in many cases) and runs, it will print the value contained in the 'prefix' array to the console before exiting (as long as 'PRINT_PREFIX' == 1).

There are quite a few code smells in this approach.

The array size is whatever '[PATH_MAX]' is - it might be 96 unsigned ints, it might be 4096. We've placed the string "/usr" into it using the classic stringify preprocessor macro. This definition does not contain a null-terminating char, i.e. '\0'. The resulting char array would be something like:

```
char prefix[4096] = { '/', 'u', 's', 'r', '000', '000', '000', '000', '000', '000', '000', '000', '000', '000', '000', '000', '000','000', '000','000', '000', '000', (repeat until all 4096 values are filled)... }
```

... meaning, regardless if we actually *see* these zeros in our printout, they are certainly there, filling up all the remaining memory allocations out of 4096 ints (which are at least 4 bytes each, usually).

Running a debugger on the above code will also be hampered quite a bit by the use of (compile time!) preprocessor 'ifdef's to handle our (runtime!) control-flow logic. There is quite a bit of documentation and discussion online on the pitfalls of using preprocessor logic for runtime behaviour. Preprocessor 'ifdef'-style logical behaviour is fine *for managing preprocessor definitions*, not for managing runtime flow - we have standard 'if/else' for that :)

Once the program becomes heavily populated with assignments and other operations ('printf()') that become repititious in their style, we can save a lot of time by functionizing. Great approach, but not without considerations: particularly, knowing where memory allocations might get duplicated, and how to use compiler optimizations to keep the make certain that our memory footprint is actually what we might *assume* it to be. Looking at you, copy by reference!


Of course, all of the above is just normal C stuff, which I'm going through the motions of become familiar with.

Some reflection on the above points has led our refactor to incorporate some simple data structures that each resemble aspects of the project's requirements. We can allocate structs of known size and type, use more refined/modern testing approaches to populate the data, and pass this data to our allocated struct(s) using pointers to memory, possibly by use of a function wherever possible to guarantee conformity of conventions.

The 'after' approach, as of today;
```
#if __has_include(<stdio.h>)
#  include <stdio.h>
#  define HAS_STDIO_H 1
#endif

#define PRINT_PREFIX HAS_STDIO_H

/**
 * Set some sort of flag to check if a new definition was passed in... we can use the result in our runtime logic.
 */
#ifdef (PREFIX)
#  define __CHANGE_PREFIX 1
#else
#  define __CHANGE_PREFIX 0
#endif

struct configuration
{
	char prefix [PATH_MAX];

} sConfiguration = {
	.prefix = { '/', 'u', 's', 'r', '\0' };
};

/**
 * The code below the struct instantiates a 'struct configuration' named 'sConfiguration', which we can check/populate by reference.
 */

int main()
{
	/**
	 * We need a pointer to our instantiated struct, let's call it 'GetConfig'...
	 */
	struct configuration* GetConfig = &sConfiguration;

	/**
	 * Now we use the pointer to access the member(s) of the struct... let's call it 'Prefix'
	 */
	char Prefix[PATH_MAX] = GetConfig->prefix;

	if (__CHANGE_PREFIX == 1)
	{
		Prefix = { PREFIX, '\0' };
	}

	if (HAS_STDIO_H)
	{
		printf("%s", Prefix);

		return (0);
	}

	/** Error: Nothing to do... */
	return (1);

}
```

That is a quite minimalized version of affairs that aims to demonstrate some of the backend changes that have occured, while the frontend/UI has continued to progress as before, but with fewer changes to report.

Nonetheless, here is a readout and build task of writing (this time built under msys64 UCRT64 subsystem and running in Windows Powershell; the binary seems to run in pretty much any terminal..?):

```
> .\"out\ucrt64\bin\pkgman_config.exe"

pkgman_config v6.0.2-6eca3e5d40d128e0fc4231d2c7bef45f6b2c8262

Checking for msys installation...

Success :: 'C:/msys64/msys2_shell.cmd'
Success :: 'C:/msys64/autorebase.bat'

Checking for required system headers...

Failed  :: '<mntent.h>'
Failed  :: '<sys/mnttab.h>'
Failed  :: '<sys/mount.h>'
Success :: '<sys/param.h>'
Failed  :: '<sys/resource.h>'
Success :: '<sys/stat.h>'
Failed  :: '<sys/statfs.h>'
Failed  :: '<sys/statvfs.h>'
Success :: '<sys/time.h>'
Success :: '<sys/types.h>'
Failed  :: '<sys/ucred.h>'
Failed  :: '<termios.h>'

Checking for required library dependencies...

Success :: 'msvcrt.dll'
Success :: 'libarchive-13.dll'
Success :: 'libcrypto-3-x64.dll'
Success :: 'libcurl-4.dll'
Success :: 'libgpgme-11.dll'
Success :: 'libintl-8.dll'

Checking for required functions...

Failed  :: 'getmntent()'
Failed  :: 'getmntinfo()'
Failed  :: 'strndup()'
Success :: 'strnlen()'
Success :: 'strsep()'
Success :: 'swprintf()'
Failed  :: 'tcflush()'

Checking for required struct members...

Failed  :: 'struct stat::st_blksize'
Failed  :: 'struct statvfs::f_flag'
Failed  :: 'struct statfs::f_flags'

Checking for required typedefs...


Build information:

prefix                  : C:\msys64\usr
sysconfdir              : C:\msys64\etc
conf file               : C:\msys64\etc\pkgman.conf
localstatedir           : C:\msys64\var
database dir            : C:\msys64\var\lib\pkgman\
cache dir               : C:\msys64\var\cache\pkgman\pkg\
compiler                : GNU 13.2.0

Architecture            : @0@'.(carch)
Host Type               : @0@'.(chost)
File inode command      : @0@'.(inodecmd)
File seccomp command    : @0@'.(filecmd)
libalpm version         : 13.0.2
pacman version          : 6.0.2

Directory and file information:

root working directory  : C:\
package extension       : .pkg.tar.gz
source pkg extension    : .src.tar.gz
build script name       : PKGBUILD
template directory      : C:\msys64\usr\share\makepkg-template

Compilation options:

i18n support            : @0@'.(get_option('i18n'))
Build docs              : @0@'.(build_doc)
debug build             : false
Use libcurl             : true
Use GPGME               : true
Use OpenSSL             : true
Use nettle              : false

pkgman_config v6.0.2-6eca3e5d40d128e0fc4231d2c7bef45f6b2c8262
Copyright (C) 2023 Nathan J. Hood (StoneyDSP) <nathanjhood@googlemail.com>

License GPLv2: <https://gnu.org/licenses/gpl.htm>
This software comes with ABSOLUTELY NO WARRANTY; This is free software, and you are free to change and redistribute it.

Home page URL: https://github.com/StoneyDSP/msys2-libconfig.git
Bug reports: https://github.com/StoneyDSP/msys2-libconfig/issues
```

```
C:/msys64/ucrt64/bin/x86_64-w64-mingw32-gcc.exe \
  -D_FILE_OFFSET_BITS=64 \
  -D_GNU_SOURCE=1 \
  -D_DEFAULT_SOURCE=1 \
  -D_XOPEN_SOURCE=700 \
  -D_XOPEN_SOURCE_EXTENDED \
  -D__USE_MINGW_ANSI_STDIO \
  -IC:/msys64/ucrt64/include \
  -IC:/msys64/ucrt64/include/curl \
  -IC:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/13.2.0/include \
  -I${workspaceFolder}/include \
  -LC:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/13.2.0 \
  -LC:/msys64/ucrt64/lib \
  -LC:/msys64/ucrt64/bin \
  -lucrtbase \
  -lkernel32 \
  -ladvapi32 \
  -lshell32 \
  -luser32 \
  -larchive \
  -ldl \
  -lcurl \
  -lgpgme \
  -lintl \
  -m64 \
  -save-temps \
  -Og \
  ${workspaceFolder}/src/pkgman_config.c \
  -o \
  ${workspaceFolder}/out/ucrt64/bin/pkgman_config.exe
```

Note the updated library linkages, and the inclusion of '-ldl' (dlgcn-win32 for non-linux/cygwin systems) as mentioned in a previous post - because the UCRT64 subsystem doesn't have this function natively, it must be installed using a package manager, then added to the compile line as above. The actual file on disk is 'libdl.dll'

Probably our header should provide an 'interface library' (really just a header for inclusion) that can power 'pacman'-derived project builds, and the source file could compile into a library for downstream linkage. The compiled lib can link an executable for the user frontend, a la 'curl_config', 'LLVM-config', and so on. That is more 'seperation of concerns' than we currently have, but where we shall likely end up.

## 14.08.23

Latest readout, here using the "MSYS2" subsystem toolchain. Some of these tests are wrapped in functions now and under further development in other repos elsewhere (I'll keep this project in sync with any changes):

```
$ ./out/usr/bin/pkgman_config.exe

pkgman_config v6.0.2-81c0a15465cc6197b913e761833d2b486fc0c4fa

Checking for msys installation...

Success :: 'C:/msys64/msys2_shell.cmd'
Success :: 'C:/msys64/autorebase.bat'

Checking for required system headers...

Success :: '<mntent.h>'
Failed  :: '<sys/mnttab.h>'
Success :: '<sys/mount.h>'
Success :: '<sys/param.h>'
Success :: '<sys/stat.h>'
Success :: '<sys/statvfs.h>'
Success :: '<sys/types.h>'
Failed  :: '<sys/ucred.h>'
Success :: '<termios.h>'

Checking for required library dependencies...

Success :: 'ucrtbase.dll'
Success :: 'msvcrt.dll'
Success :: 'msys-2.0.dll'
Success :: 'msys-crypto-3.dll'
Success :: 'msys-curl-4.dll'
Success :: 'msys-gpgme-11.dll'

Checking for required functions...

Success :: 'char *strsep(char **stringp, const char *delim)'
Success :: 'char *strndup(const char *s, size_t n)'

Build information:

prefix                  : /usr
sysconfdir              : /etc
conf file               : /etc/pkgman.conf
localstatedir           : /var
database dir            : /var/lib/pacman/
cache dir               : /var/cache/pacman/pkg/
compiler                : GNU 11.3.0

Architecture            : @0@'.format(carch)
Host Type               : @0@'.format(chost)
File inode command      : @0@'.format(inodecmd)
File seccomp command    : @0@'.format(filecmd)
libalpm version         : 13.0.2
pacman version          : 6.0.2

Directory and file information:

root working directory  : /
package extension       : .pkg.tar.gz
source pkg extension    : .src.tar.gz
build script name       : PKGBUILD
template directory      : /usr/share/makepkg-template

Compilation options:

i18n support            : @0@'.format(get_option('i18n'))
Build docs              : @0@'.format(build_doc)
debug build             : false
Use libcurl             : true
Use GPGME               : true
Use OpenSSL             : true
Use nettle              : false

pkgman_config v6.0.2-81c0a15465cc6197b913e761833d2b486fc0c4fa
Copyright (C) 2023 Nathan J. Hood (StoneyDSP) <nathanjhood@googlemail.com>

License GPLv2: <https://gnu.org/licenses/gpl.htm>
This software comes with ABSOLUTELY NO WARRANTY; This is free software, and you are free to change and redistribute it.

Home page URL: https://github.com/StoneyDSP/msys2-libconfig.git
Bug reports: https://github.com/StoneyDSP/msys2-libconfig/issues

```

Here is the build task that generated the above:

```
C:/msys64/usr/bin/x86_64-pc-msys-gcc.exe \
-D_FILE_OFFSET_BITS=64 \
-D_GNU_SOURCE=1 \
-D_DEFAULT_SOURCE=1 \
-D_XOPEN_SOURCE=500 \
-D_XOPEN_SOURCE_EXTENDED \
-I${workspaceFolder}/include \
-IC:/msys64/usr/include \
-IC:/msys64/usr/include/curl \
-IC:/msys64/usr/include/w32api \
-IC:/msys64/usr/lib/gcc/x86_64-pc-msys/11.3.0/include \
-IC:/msys64/usr/lib/gcc/x86_64-pc-msys/11.3.0/include-fixed \
-LC:/msys64/usr/lib/gcc/x86_64-pc-msys/11.3.0 \
-LC:/msys64/usr/lib/w32api \
-LC:/msys64/usr/lib \
-lgcc_s \
-lgcc \
-lmsys-2.0 \
-lkernel32 \
-ladvapi32 \
-lshell32 \
-luser32 \
-lcurl \
-m64 \
-pipe \
-ggdb \
${workspaceFolder}/src/pkgman_config.c \
-o ${workspaceFolder}/out/usr/bin/pkgman_config.exe
```

## 11.08.23

Now building our package manager configurator successfully for *all* Msys64 susbsystems! :D There are some quirks from one to the other that I hope I can address further within the code... some differences in system header availability, for example.

It's really nice having ```dlopen()``` check the lib dependencies *on the executable platform*, instead of whatever got baked in during build time. It strikes me that ```fileopen()``` and family, not to mention ```getenv()```, should offer some similar run-time functionality... which suggests we could perhaps set the runtime checks (include dirs, lib loading, env vars, perhaps function symbol checks) as a callable function of the executable program, as a means of system introspection. This seems like a clever way of portable dependency management that perhaps we can hook back into later, when this is all subsumed back into my fork of vcpkg. For example, a failed header/lib check might trigger a package download to fetch the required content. Without trying to get too far ahead of oneself, but this might also pave the way to a simple GUI solution that does a simple task and doesn't need to do a whole lot more.

Latest readout... for MSYS/Cygwin:

```
$ ./out/usr/bin/pkgman_config.exe

pkgman_config v6.0.2-81c0a15465cc6197b913e761833d2b486fc0c4fa
Checking for dependencies...

"C:/Windows/System32" exists on this system.
Loaded 'ucrtbase.dll' successfully.

"C:/Windows/System32" exists on this system.
Loaded 'msvcrt.dll' successfully.

"/" exists on this system.
Loaded 'msys-2.0.dll' successfully.

"C:/msys64/usr/include/openssl" exists on this system.
Loaded 'msys-crypto-3.dll' successfully.

"C:/msys64/usr/include/curl" exists on this system.
Loaded 'msys-curl-4.dll' successfully.

"C:/msys64/usr/include/gpgme++" exists on this system.
Loaded 'msys-gpgme-11.dll' successfully.


Build information:

prefix                  : /usr
sysconfdir              : /etc
conf file               : /etc/pkgman.conf
localstatedir           : /var
database dir            : /var/lib/pacman/
cache dir               : /var/cache/pacman/pkg/
compiler                : GNU 11.3.0

Architecture            : @0@'.format(carch)
Host Type               : @0@'.format(chost)
File inode command      : @0@'.format(inodecmd)
File seccomp command    : @0@'.format(filecmd)
libalpm version         : 13.0.2
pacman version          : 6.0.2

Directory and file information:

root working directory  : /
package extension       : .pkg.tar.gz
source pkg extension    : .src.tar.gz
build script name       : PKGBUILD
template directory      : /usr/share/makepkg-template

Compilation options:

i18n support            : @0@'.format(get_option('i18n'))
Build docs              : @0@'.format(build_doc)
debug build             : false
Use libcurl             : true
Use GPGME               : true
Use OpenSSL             : true
Use nettle              : false

Checking for required system headers...

<mntent.h>                      : Success
<sys/mnttab.h>                  : Fail
<sys/mount.h>                   : Success
<sys/param.h>                   : Success
<sys/stat.h>                    : Success
<sys/statvfs.h>                 : Success
<sys/types.h>                   : Success
<sys/ucred.h>                   : Fail
<termios.h>                     : Success

...pkgman_config > Exiting successfully.
```

...and for UCRT64 (note the automatically-transformed paths from *nix to Windows style):

```
$ ./out/ucrt64/bin/pkgman_config.exe

pkgman_config v6.0.2-81c0a15465cc6197b913e761833d2b486fc0c4fa
Checking for dependencies...

"C:/Windows/System32" exists on this system.
Loaded 'ucrtbase.dll' successfully.

"C:/Windows/System32" exists on this system.
Loaded 'msvcrt.dll' successfully.

"C:\msys64" exists on this system.
Loaded 'msys-2.0.dll' successfully.

"C:/msys64/usr/include/openssl" exists on this system.
Loaded 'libcrypto.dll' successfully.

"C:/msys64/usr/include/curl" exists on this system.
Loaded 'libcurl-4.dll' successfully.

"C:/msys64/usr/include/gpgme++" exists on this system.
Loaded 'libgpgme-11.dll' successfully.


Build information:

prefix                  : C:\msys64\usr
sysconfdir              : C:\msys64\etc
conf file               : C:\msys64\etc\pkgman.conf
localstatedir           : C:\msys64\var
database dir            : C:\msys64\var\lib\pacman\
cache dir               : C:\msys64\var\cache\pacman\pkg\
compiler                : GNU 13.2.0

Architecture            : @0@'.format(carch)
Host Type               : @0@'.format(chost)
File inode command      : @0@'.format(inodecmd)
File seccomp command    : @0@'.format(filecmd)
libalpm version         : 13.0.2
pacman version          : 6.0.2

Directory and file information:

root working directory  : C:\
package extension       : .pkg.tar.gz
source pkg extension    : .src.tar.gz
build script name       : PKGBUILD
template directory      : C:\msys64\usr\share\makepkg-template

Compilation options:

i18n support            : @0@'.format(get_option('i18n'))
Build docs              : @0@'.format(build_doc)
debug build             : false
Use libcurl             : true
Use GPGME               : true
Use OpenSSL             : true
Use nettle              : false

Checking for required system headers...

<mntent.h>                      : Fail
<sys/mnttab.h>                  : Fail
<sys/mount.h>                   : Fail
<sys/param.h>                   : Success
<sys/stat.h>                    : Success
<sys/statvfs.h>                 : Fail
<sys/types.h>                   : Success
<sys/ucred.h>                   : Fail
<termios.h>                     : Fail

...pkgman_config > Exiting successfully.
```

## 10.08.23

The config executable is now building in both the 'MSYS2' *and* 'CLANG64' environments, including reporting correct(-ly portable) paths. In contrast to previous examples (under 'MSYS2'), here's the latest readout but compiler under 'CLANG64' - it's worth noting that the resulting binary can run in the 'CLANG64' bash shell, but it *also* runs happily from Windows Powershell, and *even* reports different linkages and paths when doing so :D This one is in fact taken from Powershell;

```
$ ./bin/pkgman_config.exe

pkgman_config v6.0.2-81c0a15465cc6197b913e761833d2b486fc0c4fa
Build information:

prefix                  : C:\msys64\usr
sysconfdir              : C:\msys64\etc
conf file               : C:\msys64\etc\pkgman.conf
localstatedir           : C:\msys64\var
database dir            : C:\msys64\var/lib/pacman/
cache dir               : C:\msys64\var/cache/pacman/pkg/
compiler                : Clang 16.0.5

Architecture            : @0@'.format(carch)
Host Type               : @0@'.format(chost)
File inode command      : @0@'.format(inodecmd)
File seccomp command    : @0@'.format(filecmd)
libalpm version         : @0@'.format(libalpm_version)
pacman version          : @0@'.format(PACKAGE_VERSION)

Directory and file information:

root working directory  : C:\
package extension       : .pkg.tar.gz
source pkg extension    : .src.tar.gz
build script name       : PKGBUILD
template directory      : C:\msys64\usr\share\makepkg-template

Compilation options:

i18n support            : @0@'.format(get_option('i18n'))
Build docs              : @0@'.format(build_doc)
debug build             : @0@'.format(get_option('buildtype') == 'debug')
Use libcurl             : false
Use GPGME               : false
Use OpenSSL             : true
Use nettle              : false

Feature detection macros:

_POSIX_SOURCE                   : undefined
_POSIX_C_SOURCE                 : undefined
_ISOC99_SOURCE                  : undefined
_ISOC11_SOURCE                  : undefined
_XOPEN_SOURCE                   : defined = 500
_XOPEN_SOURCE_EXTENDED          : defined
_LARGEFILE64_SOURCE             : undefined
_FILE_OFFSET_BITS               : defined = 64
_TIME_BITS                      : undefined
_BSD_SOURCE                     : undefined
_SVID_SOURCE                    : undefined
_DEFAULT_SOURCE                 : defined
_ATFILE_SOURCE                  : undefined
_GNU_SOURCE                     : defined
_REENTRANT                      : undefined
_THREAD_SAFE                    : undefined
_FORTIFY_SOURCE                 : undefined

Checking for required system headers...

<mntent.h>                      : Fail
<sys/mnttab.h>                  : Fail
<sys/mount.h>                   : Fail
<sys/param.h>                   : Success
<sys/param.h>                   : Success
<sys/statvfs.h>                 : Fail
<sys/types.h>                   : Success
<sys/ucred.h>                   : Fail
<termios.h>                     : Fail

Checking for dependencies...

"C:/Windows/System32" exists on this system.
Loaded 'msvcrt.dll' successfully.

"C:\msys64" exists on this system.
Loaded 'msys-2.0.dll' successfully.

"C:/msys64" exists on this system.
Loading 'libmingw32.a' attempt failed: "libmingw32.a": The specified module could not be found.

"C:/msys64/usr/include/openssl" exists on this system.
Loaded 'libcrypto.dll' successfully.

"C:/msys64/usr/include/curl" exists on this system.
Loaded 'libcurl-4.dll' successfully.

...pkgman_config > Exiting successfully.
```



To get the missing 'dlfcn' functions (for POSIX platforms) on the Msys susbsystems, they can be installed like so:

```
pacman -S mingw-w64-clang-x86_64-dlfcn
```

Which is in fact a port of this fantastic project: <a href="https://github.com/dlfcn-win32/dlfcn-win32">dlfcn-win32</a>

## Log 09.08.2023 - part II

With a few more defs in place, the config.exe readout is starting to take shape nicely;

```
$ ./bin/pkgman_config.exe

pkgman_config v.60002-81c0a15465cc6197b913e761833d2b486fc0c4fa

Build information:

prefix                  : /usr
sysconfdir              : /etc
conf file               : /etc/pacman.conf
localstatedir           : /var
database dir            : /var/lib/pacman/
cache dir               : /var/cache/pacman/pkg/
compiler                : @0@ @1@'.format(cc.get_id(), cc.version())

Architecture            : @0@'.format(carch)
Host Type               : @0@'.format(chost)
File inode command      : @0@'.format(inodecmd)
File seccomp command    : @0@'.format(filecmd)
libalpm version         : @0@'.format(libalpm_version)
pacman version          : @0@'.format(PACKAGE_VERSION)

Directory and file information:

root working directory  : /
package extension       : .pkg.tar.gz
source pkg extension    : .src.tar.gz
build script name       : PKGBUILD
template directory      : /usr/share/makepkg-template

Compilation options:

i18n support            : @0@'.format(get_option('i18n'))
Build docs              : @0@'.format(build_doc)
debug build             : @0@'.format(get_option('buildtype') == 'debug')
Use libcurl             : false
Use GPGME               : false
Use OpenSSL             : true
Use nettle              : false

Compiler info:

PKGMAN_GCC_VERSION: 1103

Feature detection macros:

_POSIX_SOURCE                   : defined
_POSIX_C_SOURCE                 : defined = 200809L
_ISOC99_SOURCE                  : undefined
_ISOC11_SOURCE                  : undefined
_XOPEN_SOURCE                   : defined = 500
_XOPEN_SOURCE_EXTENDED          : undefined
_LARGEFILE64_SOURCE             : undefined
_FILE_OFFSET_BITS               : undefined
_TIME_BITS                      : undefined
_BSD_SOURCE                     : undefined
_SVID_SOURCE                    : undefined
_DEFAULT_SOURCE                 : defined
_ATFILE_SOURCE                  : defined
_GNU_SOURCE                     : defined
_REENTRANT                      : undefined
_THREAD_SAFE                    : undefined
_FORTIFY_SOURCE                 : undefined

Checking for required system headers...

<mntent.h>                      : Success
<sys/mnttab.h>                  : Fail
<sys/mount.h>                   : Success
<sys/param.h>                   : Success
<sys/param.h>                   : Success
<sys/statvfs.h>                 : Success
<sys/types.h>                   : Success
<sys/ucred.h>                   : Fail
<termios.h>                     : Success

Checking for dependencies...

"C:/msys64/usr/include/openssl" exists on this system.
Loaded 'libcrypto.dll' successfully.

```
The code will benefit from some refactoring - a good few functions and perhaps structs would be really efficient here, but it's all in the pipeline, of course.

Would be nice to have some description strings (pulled from the meson build options and so forth) and perhaps an indicator of which '-D' to use to control the options, too...

## Log 09.08.2023

Ah, glorious C. Wish I had learned Unix C programming long ago... Currently, based on the previous two entries, our configuration header no longer actually requires any sort of build system in order to prepare the main package manager source files for building.

Running the below in a Windows terminal:

```
> C:/msys64/usr/bin/x86_64-pc-msys-gcc.exe \
	-IC:/path/to/repo/include \
	-IC:/msys64/usr/include \
	-IC:/msys64/usr/include/w32api \
	-IC:/msys64/usr/lib/gcc/x86_64-pc-msys/11.3.0/include \
	-IC:/msys64/usr/lib/gcc/x86_64-pc-msys/11.3.0/include-fixed \
	-LC:/msys64/usr/lib/gcc/x86_64-pc-msys/11.3.0 \
	-LC:/msys64/usr/lib/w32api \
	-LC:/msys64/usr/lib \
	-lgcc_s \
	-lgcc \
	-lmsys-2.0 \
	-lkernel32 \
	-ladvapi32 \
	-lshell32 \
	-luser32 \
	-lcurl \
	-m64 \
	-save-temps \
	-ggdb \
	C:/path/to/repo/src/pkgman/pkgman_config.c \
	-o C:/path/to/repo/bin/pkgman_config.exe
```

Will build the 'src/pkgman_config.c' file into a 'bin/pkgman_config.exe' program that we can execute in Bash.

I'm currently hacking on the Meson build file's readout and input options to the 'config object' settings to produce a focused and meaningful output (clearly a work in progress but at time of writing we get):

```
$ ./bin/pkgman_config.exe

pkgman_config
PKGMAN_VERSION: 60002

Build information:

prefix                  : /usr
sysconfdir              : /etc
conf file               : /etc/pacman.conf
localstatedir           : /var
database dir            : /var/lib/pacman/
cache dir               : /var/cache/pacman/pkg/
compiler                : @0@ @1@'.format(cc.get_id(), cc.version())

Architecture            : @0@'.format(carch)
Host Type               : @0@'.format(chost)
File inode command      : @0@'.format(inodecmd)
File seccomp command    : @0@'.format(filecmd)
libalpm version         : @0@'.format(libalpm_version)
pacman version          : @0@'.format(PACKAGE_VERSION)

Directory and file information:

root working directory  : 4206608
package extension       : @0@'.format(get_option('pkg-ext'))
  source pkg extension  : @0@'.format(get_option('src-ext'))
build script name       : @0@'.format(BUILDSCRIPT)
template directory      : @0@'.format(get_option('makepkg-template-dir'))

Compilation options:

i18n support            : @0@'.format(get_option('i18n'))
Build docs              : @0@'.format(build_doc)
debug build             : @0@'.format(get_option('buildtype') == 'debug')
Use libcurl             : @0@'.format(conf.get('HAVE_LIBCURL'))
Use GPGME               : @0@'.format(conf.get('HAVE_LIBGPGME'))
Use OpenSSL             : @0@'.format(conf.has('HAVE_LIBSSL') and conf.get('HAVE_LIBSSL') == 1)
Use nettle              : @0@'.format(conf.has('HAVE_LIBNETTLE') and conf.get('HAVE_LIBNETTLE') == 1)


Checking for dependencies...

"C:/msys64/usr/include/openssl" exists on this system.
Included '<openssl/crypto.h>' successfully.
Loaded 'libcrypto.dll' successfully.


Compiler info:

PKGMAN_CLANG_VERSION: 0
PKGMAN_GCC_VERSION: 1103
PKGMAN_ICC_VERSION: 0
PKGMAN_MSC_VERSION: 0


Feature detection macros:

_POSIX_SOURCE defined
_POSIX_C_SOURCE defined: 200809L
_DEFAULT_SOURCE defined
_ATFILE_SOURCE defined
_GNU_SOURCE defined

```

One quite important aspect to hold on to here is that the 'pkgman_config.h' file is intended to be *shared* by all the sub-projects, as a means of providing them a common configuration. (In actuality this is what 'util-common' and 'ini' are for in the original pacman project, but this approach is different in a few ways...)

Everything in 'pkgman_config.c' gets compiled into the executable. The idea would eventually be to have this executable accept command line args that allow the user to query the installation configuration of 'pkgman' (really, my hack on 'msys2-pacman'). We could pass it things like ```--cflags```, ```--sysroot``` and such forth... (see previous logs for more).

The importance to note is in the distinction of what definitions, header inclusions, and so forth belong in the 'pkgman_config.h' - to be shared among other subprojects using simple file include directives, and those which should go in 'pkgman_config.c' - which will *not be shared* with subprojects; it will only be used to create the 'pkgman_config.exe' *standalone* executable.

The meaning of this is, for example, using ```#if __has_include(<curl/curl.h>)``` might set ```#define HAS_CURL_H``` to a truthy value. This definition is safe to share downstream from here - in fact, our sub-projects are actually *looking* for such definitions already, so this nice tidy modern C compiler definition trick can be utilized here and safely passed around, which in fact makes one of the build-system config steps redundant, and hardens the codebase considerably :D

On the other hand of this, we should keep in mind that the downstream sources requesting to know ```#if defined HAS_CURL_H``` are already implementing everything else that they require, as long as the header include directive is already in place (which it is). These downstream source implementations will easily be interfered with, if we start trying to do their implementation work here in a centralized project. We should *not* start supplying ```dlopen('libcurl.dll')``` from this centralized project to our downstream subprojects, by any means. Doing so would almost certainly break everything that is already implemented and working as intended, including quite possibly some pre-existing functionality doing exactly this already, wherever it needs to (and equally not implemented, where *not* appropriate).

This might make it hard to pass certain checks to our downstream subprojects *without* some kind of configure run, for example ```HAVE_LIBCURL``` refers to the successful <b>loading</b> of a library (*not* the locating of it!) and our current solution still requires running in a ```main()``` entry point, of course.

Thus, we can liberate ourselves from some amount of build-system dependency brittleness, but not quite *all* of it; and the question of how much we can do so will depend on how far we intend to diverge from the source project, msys2-pacman (and by extension, arch-linux pacman).

## Log 08.08.2023

So, after quite some R'n'D in the form of digging through the GNUC docs, some well-established C-based libraries, and heavy empirical testing, I've discovered the joys of 'feature test macros' and their friends.

```
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

void *libc = dlopen ("msys-2.0.dll", 0);

#ifndef _MODE_T_DECLARED
typedef	unsigned int mode_t; /* permissions */
#define _MODE_T_DECLARED
#endif

```

This excellent slice of modernism is well-supported, according to my current tests, and potentially saves us from being bound to these brittle build systems and lengthy build scripts - as much as we do love them, of course.


One of the beauties of having so much of our config in place at the source-file level is that our IDE intellisense engines alone should be able to detect errors that we ourselves have defined as such, using the pre-processor. For example, if our intellisense compiler cannot find '``` <stdlib.h> ```' in the above example, we can fallback to a '``` # error "<stdlib.h> not found!" ```' warning, which will raise a red flag in the IDE before we even attempt to run a build :)

Another highly interesting up-skill I've uncovered in this project is the use of the '```dlopen()```' function and family, from '```<dlfcn.h>```', which allows us to dynamically load libraries that our compiler is linking with using its '-l' args, essentially working as a sort-of '```#include <>```' mechanism that allows us to pull things like functions out of these libraries and use them in our code.


In the same vein as ```dlopen()``` comes the even more handy ```opendir()``` from the ```<dirent.h>``` header (also in the \*nix-only ```<unistd.h>``` header). With this, and its sibling functions, it seems we have the full means to at least *check* our dependencies - and, write logical error handling/fall-through support! - without needing to build, nor even build-system configure, the project! :D

Well, the above should hopefully be true - and achievable - at least for our main dependencies such as curl, libarchive, and whichever crypto provider is chosen (or found!).

Some good old psuedo-code (for *nix) to demonstrate:

```
#include <sys/types.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <unistd.h>

#if __has_include(<openssl/crypto.h>)
#  include <openssl/crypto.h>
#  define HAVE_OPENSSL 1
#elif __has_include(<nettle/crypto.h>)
#  include <nettle/crypto.h>
#  define HAVE_LIBNETTLE 1
#else
#  error "No crypto provider found!?"
#endif

#define CRYPTO_LIB "libcrypto.dll"

#if HAVE_OPENSSL
#  define CRYPTO_H_PATH "C:/msys64/usr/include/openssl/crypto.h"
#elif HAVE_LIBNETTLE
#  define CRYPTO_H_PATH "C:/msys64/usr/include/nettle/crypto.h"
#endif

#if (__WIN32__) || (__CYGWIN__)
int WinMain()
{
#else
int main()
{
#endif

	/** Check for header path... this could be more thorough, of course... */

	DIR *dip;
    struct dirent *dit;
    struct stat lsbuf;
    char currentPath[__FILENAME_MAX__];

	const char* crypto_header_path[] = {CRYPTO_H_PATH};

    if((dip = opendir(crypto_header_path)) == NULL)
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
		printf("crypto_header_path <%d> exists on this system.\n", crypto_header_path);
		printf("\n");
    } else {
		printf("\n");
		printf("crypto_header_path does not exist on this system.\n");
		printf("\n");

		exit(EXIT_FAILURE);
	}


	/** Get the chosen crypto lib */
	void* handle;
	char *error;

	handle = dlopen(CRYPTO_LIB, RTLD_LAZY);
	error = dlerror();

	if (!handle || error != NULL)
	{
		printf("\n");
		fprintf(stderr, "Loading 'libcrypto.dll' attempt failed: %s\n", error);
		printf("\n");
		exit(EXIT_FAILURE);
	} else {
		printf("\n");
		printf("Loaded 'libcrypto.dll' successfully.\n");
		printf("\n");
	}

	dlclose(handle);

	return (EXIT_SUCCESS);
}
```

The author is a little tempted to add a project to the pipeline in the fashion of the above, as a sort-of 'portable dependency tester', possibly powered by a shebang to make it executable (and semi-configurable):

```
#!/usr/bin/env sh -e cc -I${cwd} -l${syslib_arg} --include ${sysheader_arg}

/**
 * cli args:
 *
 * syslib_arg=$1
 * sysheader_arg=$2
 * output=$3
 *
 * etc...
 *
 */

```

## initial log...


See <a href="https://github.com/facebook/folly">facebook/folly</a> for inspiration and guidance...

This library will need to implement a complete set of checks and associated pre-processor macros/defines needed to build the components of our custom <a href="https://github.com/StoneyDSP/MSYS2-pacman">'pacman' package manager for Msys64</a> using CMake and the <a href="https://github.com/StoneyDSP/MSYS2-toolchain">'MSYS2-toolchain'</a> project.

This will need to handle dependencies appropriately, which might otherwise be resolved at component-level - meaning, our components will need to 'include' this config library in some way as a means of resolving their individual dependencies. This can be done by exporting the config library targets and config/version handlers using CMake's import/export utilities.

Excellent overview here:

<a href="https://discourse.cmake.org/t/how-do-i-get-a-workspace-of-independent-subprojects/5154">Discourse: How do i get a workspace of independent subprojects</a>

And wih reference to one of the more useful parts of the official CMake documentation:

<a href="https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html">Importing and exporting guide</a>.

Probably a nice touch would be to take this lib further by providing a compiled executable target, containing a command-line interface for querying the build-time config, much the same as <a href="https://github.com/llvm-project/LLVM">LLVM-config</a>

The original build system, driven by meson, defines mutliple sets of configs - for example, one configuration object is named "conf" and supplies a number of important vars, primarily for directory locations on disk.

Another configuration object named "substs" crops up which is largely similar, but has different string requirements (these vars requiring string quotation marks).

Yet another config object occurs in the same buidfile under the name "cdata" which is used to create bash function wrapper scripts, but with a particular set of file permissions...

To complicate matters somewhat, the original pacman build system specifies that *some* preprocessor definitions will be created when certain tests pass; but should the same test fail, there are cases where *no* preprocessor definition is created, and other cases where a definition is created - with either a boolean 'false' or integer '0' for a value!

One agreeable touch with the above method is that no configuration headers exist in the source tree at all - the file gets created during the configuration process and placed into the build tree (and supposedly copied into the install tree, but this is questionable since the vars contained will be end-user-dependent). The usual method with CMake is to use the 'cmakedefine' and 'cmakedefine01' preprocessor definitions and overwrite them in the config step. Personally I find this approach perfectly valid but somewhat messy; we end up with a file in the source tree that intellisense/browse paths tend to flag as faulty, which results in a messy workspace/IDE experience.

Instead, I had been exploring ways to make the un-configured defines revert to sane defaults in a 'config.h' file, which our subprojects will include/link with as needed, and a seperate file for the actual configured defines pulled from the toolchain during config time, possibly taking the approach of writing this file at config-time. Currently, it's more useful to have the desired 'defines.h' written out in advance so that we can observe all interactions and catch potential errors early. The tricky part is having a pre-written 'defines.h' that CMake can easily over-write, AND our IDE/intellisense and other tools can interact with in a meaningful way.

The CMakeLists.txt as it currently exists, goes out of it's way to match the behaviour of the previous meson system where some definitions are written regardless if their test passes or fails, while others are excluded from being defined at all when their test fails. The 'config.h' however does accomodate for allowing every configuration test result to be written as a preprocessor definition, which is then handled and manipulated into the required boolean/integer value, or unset entirely, where needed, to interface with the remaining pacman codebase as intended.

This means we can either relax the handling in the CMakeLists file, *or* in the config.h header, and one or another, we'll have a set of definitions in a header that should correctly interface with the remaining pacman codebase; which to choose? It has been quite a time-burner having to implement this config library at all, due to the fact that the meson-driven version doesn't ship with any useable config header, et al. My opinion is that all source code should be buildable regardless of chosen build system. Therefore, I am choosing to take the approach of pre-implementing all of the required config as a full subproject in C, that should be buildable directly from the command line using nothing but native build tools and commands (no meson, CMake, etc required).

If nothing else, this should make it easier to inherit the custom pacman super-project, and continue to port it to new and emerging platforms and systems in the future.

Out of pure coincidence, I happened to be browsing the folly library out of curiousity, when I noticed that they had a quite similar handling method to my own in passing their CMake test results (as underscored/lowercased strings) to the preprocessor definitions (uppercased) - this method allows some 'wiggle room' between the test result and the preprocessor define, to do any required conversion/manipuation of the resulting value. Ideally we wouldn't be creating two sets of strings for every test/definition due to increased risk of naming collisions elsewhere, but this is certainly 'easier'/more productive than re-writing the pacman source files to handle preprocessor checks in an actual consistent manner (though I have yet to rule this out...). Contained in folly's CMake files library is a perfect example of how to implement this sub-project such that our other sub-projects can all pick it up, import it, link to it, and run as one unified configure, build, or install step in unison with the other components.

Unfortunately (in our case) though, folly depends on the 'cmakedefine' method, meaning a messy source tree, which it would be nice to avoid, so... it looks like I'll have to take all this inspiration and put it all together in some logical, system-agnostic, IDE-friendly custom implementation if I am to achieve all of my motivations here.

It strikes me that if the arch-linux package manager *and* facebook have landed on approaches that don't equate with my own, there is a high probability that I shall find some part of this task impossible and will need to revert to one of the above approaches. To this end, I'll be doing my best to at least account for that in my logic handling and expected build process as I proceed.
