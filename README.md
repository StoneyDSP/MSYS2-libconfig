# MSYS2-libconfig

## latest...

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

Some good old psuedo-code to demonstrate:

```
#ifdef __CYGWIN__
#  include <dlfcn.h>
#  include <cygwin/version.h>
#endif


#  if PKGMAN_HAS_INCLUDE(<openssl/crypto.h>)
#    include <cstdlib>
#    define HAVE_CSTDLIB 1
#  elif PKGMAN_HAS_INCLUDE(<nettle/crypto.h>)
#    include <stdlib.h>
#    define HAVE_STDLIB_H 1
#  else
#    error "No crypto provider found!?"
#  endif


#define PKGMAN_CRYPTO_LIB "libcrypto.dll"


#if (__WIN32__) || (__CYGWIN__)
int WinMain()
{
#else
int main()
{
#endif

	/** Check for msys64 install path... this could be more thorough, of course... */

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


	/** Get some sort of lib */
	void* handle;
	char *error;

	handle = dlopen(PKGMAN_CRYPTO_LIB, RTLD_LAZY);
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
#define HAVE_OPENSSL 1
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
