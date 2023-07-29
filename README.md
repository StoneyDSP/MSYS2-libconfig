# MSYS2-libconfig

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