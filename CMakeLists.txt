cmake_minimum_required(VERSION 3.17...3.26 FATAL_ERROR)

project(LibConfig)
enable_language(C)

# Detect msys2.ini to figure MSYS_ROOT_DIR
set(Z_MSYS_ROOT_DIR_CANDIDATE "${CMAKE_CURRENT_LIST_DIR}")
while(NOT DEFINED Z_MSYS_ROOT_DIR)
    if(EXISTS "${Z_MSYS_ROOT_DIR_CANDIDATE}msys2.ini")
        set(Z_MSYS_ROOT_DIR "${Z_MSYS_ROOT_DIR_CANDIDATE}msys64" CACHE INTERNAL "msys root directory")
    elseif(EXISTS "${Z_MSYS_ROOT_DIR_CANDIDATE}msys64/msys2.ini")
        set(Z_MSYS_ROOT_DIR "${Z_MSYS_ROOT_DIR_CANDIDATE}msys64" CACHE INTERNAL "msys root directory")
    elseif(IS_DIRECTORY "${Z_MSYS_ROOT_DIR_CANDIDATE}")
        get_filename_component(Z_MSYS_ROOT_DIR_TEMP "${Z_MSYS_ROOT_DIR_CANDIDATE}" DIRECTORY)
        if(Z_MSYS_ROOT_DIR_TEMP STREQUAL Z_MSYS_ROOT_DIR_CANDIDATE)
			message(FATAL_ERROR "Unable to determine default msys64 installation files directory!")
            #z_msys_add_fatal_error("Unable to determine default msys64 installation files directory!")
            break() # If unchanged, we have reached the root of the drive without finding msys64.
        endif()
        set(Z_MSYS_ROOT_DIR_CANDIDATE "${Z_MSYS_ROOT_DIR_TEMP}")
        unset(Z_MSYS_ROOT_DIR_TEMP)
    else()
        break()
    endif()
endwhile()
unset(Z_MSYS_ROOT_DIR_CANDIDATE)



##############################################################################
##-- Meson options
##############################################################################

# directories and filenames
if(NOT DEFINED root_dir)
	set(root_dir "/") # CACHE PATH "Sets the location of the root operating directory.")
endif()

if(NOT DEFINED pkg_ext)
	set(pkg_ext ".pkg.tar.gz") # CACHE STRING "Sets the file extension used by packages.")
endif()

if(NOT DEFINED src_ext)
	set(src_ext ".src.tar.gz") # CACHE STRING "set the file extension used by source packages")
endif()

if(NOT DEFINED scriptlet_shell)
	set(scriptlet_shell "/bin/sh") # CACHE FILEPATH "The full path of the shell used to run install scriptlets.")
endif()

if(NOT DEFINED ldconfig)
	set(ldconfig "/sbin/ldconfig") # CACHE FILEPATH "set the full path to ldconfig")
endif()

if(NOT DEFINED buildscript)
	set(buildscript "PKGBUILD")# CACHE STRING "set the build script name used by makepkg")
endif()

if(NOT DEFINED datarootdir)
	set(datarootdir "share") # CACHE PATH "FIXME")
endif()

if(NOT DEFINED makepkg_template_dir)
	set(makepkg_template_dir "/usr/share/makepkg-template") # CACHE FILEPATH "template dir used by makepkg-template")
endif()

if(NOT DEFINED debug_suffix)
	set(debug_suffix "debug") # CACHE STRING "suffix for split debugging symbol packages used by makepkg")
endif()

# # dependencies, features
# option('doc', type : 'feature', value : 'auto', description : 'generate docs and manpages')
# option('doxygen', type : 'feature', value : 'disabled', description : 'generate doxygen manpages and html')
# option('curl', type : 'feature', value : 'auto', description : 'use curl to download files')
# option('crypto', type : 'combo', choices : ['openssl', 'nettle'], description : 'select crypto implementation')
# option('gpgme', type : 'feature', value : 'auto', description : 'use GPGME for PGP signature verification')
# option('i18n', type : 'boolean', value : true, description : 'enable localization of pacman, libalpm and scripts')

# # tools
# option('file-seccomp', type: 'feature', value: 'auto', description: 'determine whether file is seccomp-enabled')
if(NOT DEFINED libalpm_version)
	set(libalpm_version "13.0.2")
endif()

if(NOT DEFINED prefix)
	set(prefix "/usr")
endif()

if(NOT DEFINED sysconfdir)
	set(sysconfdir "/etc")
endif()

if(NOT DEFINED localstatedir)
	set(localstatedir "/var")
endif()


##############################################################################
##-- Directory settings
##############################################################################

set(PREFIX "${Z_MSYS_ROOT_DIR}${prefix}")
cmake_path(APPEND DATAROOTDIR "${PREFIX}" "${datarootdir}")
cmake_path(APPEND SYSCONFDIR "${PREFIX}" "${sysconfdir}")
cmake_path(APPEND LOCALSTATEDIR "${PREFIX}" "${localstatedir}")
cmake_path(APPEND LOCALEDIR "${PREFIX}" "${DATAROOTDIR}/locale")
set(ROOTDIR "${Z_MSYS_ROOT_DIR}${root_dir}")
cmake_path(APPEND BINDIR "${PREFIX}" "/bin")
cmake_path(APPEND MANDIR "${PREFIX}" "${DATAROOTDIR}/man")
cmake_path(APPEND LIBMAKEPKGDIR "${PREFIX}" "${DATAROOTDIR}/makepkg")
cmake_path(APPEND PKGDATADIR "${PREFIX}" "${DATAROOTDIR}/${PROJECT_NAME}")

cmake_path(APPEND SCRIPTLET_SHELL "${BINDIR}" "${scriptlet_shell}")

# Put the above in the cache...
set(DATAROOTDIR "${DATAROOTDIR}" CACHE PATH "Read-only architecture-independent data root (share)" FORCE)
set(SYSCONFDIR "${SYSCONFDIR}" CACHE PATH "Read-only single-machine data (etc)" FORCE)
set(LOCALSTATEDIR "${LOCALSTATEDIR}" CACHE PATH "Modifiable single-machine data (var)" FORCE)
set(LOCALEDIR "${LOCALEDIR}" CACHE PATH "Locale-dependent data (DATAROOTDIR/locale)" FORCE)
set(ROOTDIR "${ROOTDIR}" CACHE PATH "" FORCE)
set(BINDIR "${BINDIR}" CACHE PATH "User executables (bin)" FORCE)
set(MANDIR "${MANDIR}" CACHE PATH "Man documentation (DATAROOTDIR/man)" FORCE)
set(LIBMAKEPKGDIR "${LIBMAKEPKGDIR}" CACHE PATH "" FORCE)
set(PKGDATADIR "${PKGDATADIR}" CACHE PATH "" FORCE)

find_program(PYTHON python3)
set(LDCONFIG "${ldconfig}")
set(MESON_MAKE_SYMLINK "${PROJECT_BINARY_DIR}/build-aux/meson-make-symlink.sh")

find_program(BASH bash
	HINTS "${Z_MSYS_ROOT_DIR}/usr/bin"
	NO_DEFAULT_PATH
)

# bashcompletion = dependency('bash-completion', required : false)
# if bashcompletion.found()
#   BASHCOMPDIR = bashcompletion.get_pkgconfig_variable('completionsdir')
# else
#   BASHCOMPDIR = join_paths(DATAROOTDIR, 'bash-completion/completions')
# endif

# # required join_paths() operations for the section after...
# cmake_path(APPEND LIBDIR "${PREFIX}" "/lib")
# cmake_path(APPEND SBINDIR "${PREFIX}" "/sbin")
# cmake_path(APPEND LIBEXECDIR "${PREFIX}" "/libexec")
# cmake_path(APPEND SHAREDSTATEDIR "${PREFIX}" "/com")
# cmake_path(APPEND INCLUDEDIR "${PREFIX}" "/include")

# # commandline options
# set(LIBDIR "${LIBDIR}" CACHE PATH "Object code libraries (lib)")
# set(SBINDIR "${SBINDIR}" CACHE PATH "System admin executables (sbin)")
# set(LIBEXECDIR "${LIBEXECDIR}" CACHE PATH "Program executables (libexec)")
# set(SHAREDSTATEDIR "${SHAREDSTATEDIR}" CACHE PATH "Modifiable architecture-independent data (com)")
# set(INCLUDEDIR "${INCLUDEDIR}" CACHE PATH "C header files (include)")

# set(DATADIR "${DATAROOTDIR}" CACHE PATH "Read-only architecture-independent data (DATAROOTDIR)")
# set(INFODIR "${DATAROOTDIR}/info" CACHE PATH "Info documentation (DATAROOTDIR/info)")
# set(DOCDIR "${DATAROOTDIR}/doc/${PROJECT_NAME}" CACHE PATH "Documentation root (DATAROOTDIR/doc/PROJECT_NAME)")
# set(RUNSTATEDIR "${LOCALSTATEDIR}/run" CACHE PATH "Run-time variable data (LOCALSTATEDIR/run)")


set(PREFIX "${PREFIX}" CACHE PATH "")
set(_GNU_SOURCE TRUE CACHE BOOL "")
set(PACKAGE "${CMAKE_PROJECT_NAME}" CACHE STRING "")
set(PACKAGE_VERSION "${CMAKE_PROJECT_VERSION}" CACHE STRING "")
set(LOCALEDIR "${LOCALEDIR}" CACHE PATH "")
set(SCRIPTLET_SHELL "${SCRIPTLET_SHELL}" CACHE FILEPATH "")
set(LDCONFIG "${LDCONFIG}" CACHE FILEPATH "")
set(LIB_VERSION "${libalpm_version}" CACHE STRING "")
cmake_path(APPEND SYSHOOKDIR "${DATAROOTDIR}" "/libalpm/hooks/")
cmake_path(APPEND CONFFILE "${SYSCONFDIR}" "/pacman.conf")
cmake_path(APPEND DBPATH "${LOCALSTATEDIR}" "lib/pacman/")
cmake_path(APPEND GPGDIR "${SYSCONFDIR}" "/pacman.d/gnupg/")
cmake_path(APPEND LOGFILE "${LOCALSTATEDIR}" "/log/pacman.log")
cmake_path(APPEND CACHEDIR "${LOCALSTATEDIR}" "/cache/pacman/pkg/")
cmake_path(APPEND HOOKDIR "${SYSCONFDIR}" "/pacman.d/hooks/")
set(SYSHOOKDIR "${SYSHOOKDIR}" CACHE PATH "")
set(CONFFILE "${CONFFILE}" CACHE PATH "")
set(DBPATH "${DBPATH}" CACHE PATH "")
set(GPGDIR "${GPGDIR}" CACHE PATH "")
set(LOGFILE "${LOGFILE}" CACHE FILEPATH "")
set(CACHEDIR "${CACHEDIR}" CACHE FILEPATH "")
set(HOOKDIR "${HOOKDIR}" CACHE FILEPATH "")
set(ROOTDIR "${ROOTDIR}" CACHE PATH "")

##############################################################################
##-- Compiler settings
##############################################################################

# set(CMAKE_REQUIRED_DEFINITIONS "-D_GNU_SOURCE")
set(CMAKE_REQUIRED_INCLUDES "${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES}" CACHE PATH "")
set(CMAKE_REQUIRED_LINK_OPTION "${CMAKE_C_IMPLICIT_LINK_DIRECTORIES}" CACHE STRING "")
set(CMAKE_REQUIRED_LIBRARIES "${CMAKE_C_IMPLICIT_LINK_LIBRARIES}" CACHE STRING "")

include(CheckIncludeFile)
set(PACMAN_REQUIRED_SYSTEM_HEADERS)
list(APPEND PACMAN_REQUIRED_SYSTEM_HEADERS
	"mntent.h"
	"sys/mnttab.h"
	"sys/mount.h"
	"sys/param.h"
	"sys/statvfs.h"
	"sys/types.h"
	"sys/ucred.h"
	"termios.h"
)
foreach (_header IN LISTS PACMAN_REQUIRED_SYSTEM_HEADERS)
	set(_header_string ${_header})
	# underscorify(${_header})
	string(REPLACE [[/]] [[_]] _header_string "${_header_string}")
	string(REPLACE [[\]] [[_]] _header_string "${_header_string}")
	string(REPLACE [[.]] [[_]] _header_string "${_header_string}")
	string(REPLACE [[-]] [[_]] _header_string "${_header_string}")
	CHECK_INCLUDE_FILE("${_header}" has_${_header_string})
	if(has_${_header_string})
		string(TOUPPER ${_header_string} _header_string)
		##-- These shall print C-syntaxed booleans
		set(HAVE_${_header_string} true CACHE BOOL "Found required header file: ${_header}" FORCE)
	endif()
	unset(has_${_header_string})
endforeach()
unset(_header)
unset(_header_string)


include(CheckFunctionExists)
set(PACMAN_REQUIRED_SYSTEM_FUNCTIONS)
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "getmntent")
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "getmntinfo")
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "strndup")
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "strnlen")
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "strsep")
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "swprintf")
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "tcflush")
foreach (_symbol IN LISTS PACMAN_REQUIRED_SYSTEM_FUNCTIONS)
	set(CMAKE_REQUIRED_DEFINITIONS "-D_GNU_SOURCE")
	check_function_exists("${_symbol}" has_${_symbol})
	if(has_${_symbol})
		##-- These shall print integer 0's or 1's
		string(TOUPPER ${_symbol} _symbol)
		set(HAVE_${_symbol} 1 CACHE BOOL "" FORCE)
	endif()
	unset(has_${_symbol})
endforeach()
unset(_symbol)


include(CheckStructHasMember)
CHECK_STRUCT_HAS_MEMBER("struct stat" st_blksize "sys/stat.h" has_struct_stat_st_blksize LANGUAGE C)
if(has_struct_stat_st_blksize)
	set(HAVE_STRUCT_STAT_ST_BLKSIZE true CACHE BOOL "" FORCE)
endif()

CHECK_STRUCT_HAS_MEMBER("struct statvfs" f_flag "sys/statvfs.h" has_struct_statvfs_f_flag LANGUAGE C)
if(has_struct_statvfs_f_flag)
	set(HAVE_STRUCT_STATVFS_F_FLAG true CACHE BOOL "" FORCE)
endif()

CHECK_STRUCT_HAS_MEMBER("struct statfs" f_flags "sys/param.h" has_struct_statfs_f_flags LANGUAGE C)
if(has_struct_statfs_f_flags)
	set(HAVE_STRUCT_STATFS_F_FLAGS true CACHE BOOL "" FORCE)
else()
	CHECK_STRUCT_HAS_MEMBER("struct statfs" f_flags "sys/mount.h" has_struct_statfs_f_flags_sys_mount LANGUAGE C)
	if(has_struct_statfs_f_flags_sys_mount)
		set(HAVE_STRUCT_STATFS_F_FLAGS true CACHE BOOL "" FORCE)
	endif()
endif()

include(CheckTypeSize)
CHECK_TYPE_SIZE("unsigned int" "mode_t" LANGUAGE C)
CHECK_TYPE_SIZE("unsigned int" "uid_t" LANGUAGE C)
CHECK_TYPE_SIZE("signed int" "off_t" LANGUAGE C)
CHECK_TYPE_SIZE("signed int" "pid_t" LANGUAGE C)
CHECK_TYPE_SIZE("unsigned int" "size_t" LANGUAGE C)
CHECK_TYPE_SIZE("signed int" "ssize_t" LANGUAGE C)
CHECK_TYPE_SIZE("signed int long" "int64_t" BUILTIN_TYPES_ONLY LANGUAGE C)

if (HAVE_STRUCT_STATVFS_F_FLAG)
  	set(FSSTATSTYPE "struct statvfs" CACHE STRING "")
elseif (HAVE_STRUCT_STATFS_F_FLAGS)
  	set(FSSTATSTYPE "struct statfs" CACHE STRING "")
endif ()

##-- These flags need to actually be added to the project, not just (or even) checked
if(CMAKE_BUILD_STYPE STREQUAL "Debug")
	include(CheckCCompilerFlag)
	check_c_compiler_flag(-Wcast-align HAS_CAST_ALIGN)
	check_c_compiler_flag(-Wclobbered HAS_CLOBBERED)
	check_c_compiler_flag(-Wempty-body HAS_EMPTY_BODY)
	check_c_compiler_flag(-Wfloat-equal HAS_FLOAT_EQUAL)
	check_c_compiler_flag(-Wformat-nonliteral HAS_FORMAT_NONLITERAL)
	check_c_compiler_flag(-Wformat-security HAS_FORMAT_SECURITY)
	check_c_compiler_flag(-Wignored-qualifiers HAS_IGNORED_QUALIFIERS)
	check_c_compiler_flag(-Wimplicit-fallthrough HAS_IMPLICIT_FALLTHROUGHS)
	check_c_compiler_flag(-Winit-self HAS_INIT_SELF)
	check_c_compiler_flag(-Wlogical-op HAS_LOGICAL_OP)
	check_c_compiler_flag(-Wmissing-declarations HAS_MISSING_DECLARATIONS)
	check_c_compiler_flag(-Wmissing-field-initializers HAS_MISSING_FIELD_INITIALIZERS)
	check_c_compiler_flag(-Wmissing-parameter-type HAS_MISSING_PARAMETER_TYPE)
	check_c_compiler_flag(-Wmissing-prototypes HAS_MISSING_PROTOTYPES)
	check_c_compiler_flag(-Wold-style-declaration HAS_OLD_STYLE_DECLARATION)
	check_c_compiler_flag(-Woverride-init HAS_OVERRIDE_INIT)
	check_c_compiler_flag(-Wpointer-arith HAS_POINTER_ARITH)
	check_c_compiler_flag(-Wredundant-decls HAS_REDUNDANT_DECLS)
	check_c_compiler_flag(-Wshadow HAS_SHADOW)
	check_c_compiler_flag(-Wsign-compare HAS_SIGN_COMPARE)
	check_c_compiler_flag(-Wstrict-aliasing HAS_STRICT_ALIASING)
	check_c_compiler_flag(-Wstrict-overflow=5 HAS_STRICT_OVERFLOW_EQ_5)
	check_c_compiler_flag(-Wstrict-prototypes HAS_STRICT_PROTOTYPES)
	check_c_compiler_flag(-Wtype-limits HAS_TYPE_LIMITS)
	check_c_compiler_flag(-Wuninitialized HAS_UNINITIALIZED)
	check_c_compiler_flag(-Wunused-but-set-parameter HAS_UNUSED_BUT_DET_PARAMETER)
	check_c_compiler_flag(-Wunused-parameter HAS_UNUSED_PARAMETER)
	check_c_compiler_flag(-Wwrite-strings HAS_WRITE_STRINGS)
	set(PACMAN_DEBUG 1)
endif()

if (NOT ${PROJECT_SOURCE_DIR} EQUAL ${PROJECT_BINARY_DIR})

	configure_file("include/config.h" 			"include/config.h" @ONLY)
	configure_file("include/defines.h" 			"include/defines.h" @ONLY)

endif()

add_library (configuration                                      	INTERFACE)
add_library (pacman::configuration                   				ALIAS configuration)

target_include_directories (configuration

    INTERFACE

        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_sources (configuration

    PUBLIC

        FILE_SET configuration_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include>
        FILES
            # include/application/configuration.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/config.h>
            $<INSTALL_INTERFACE:include/config.h>
			# include/application/defines.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/defines.h>
            $<INSTALL_INTERFACE:include/defines.h>
)

set_target_properties (configuration

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        LIBRARY_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY lib
        PDB_OUTPUT_DIRECTORY     bin

		C_STANDARD 99
		C_STANDARD_REQUIRED TRUE
		# VISIBILITY_INLINES_HIDDEN TRUE
		HAS_CXX FALSE
)

target_compile_features(configuration INTERFACE c_std_99)
