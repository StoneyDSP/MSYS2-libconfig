cmake_minimum_required(VERSION 3.17...3.26 FATAL_ERROR)

project(LibConfig)
enable_language(C)
enable_language(CXX)
enable_language(ASM)
enable_language(Fortran)
enable_language(OBJC)
enable_language(OBJCXX)

include(GNUInstallDirs)

set(LibConfig_INCLUDEDIR "${CMAKE_CURRENT_BINARY_DIR}/include")

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
##-- Dependency settings
##############################################################################

find_program(PYTHON python3)

# set(MESON_MAKE_SYMLINK "${PROJECT_BINARY_DIR}/build-aux/meson-make-symlink.sh")

find_program(BASH bash
	HINTS "/usr/bin"
	REQUIRED
	NO_DEFAULT_PATH
)

execute_process(
	COMMAND ${BASH} -c "IFS=.; echo \"\${BASH_VERSINFO[*]:0:3}\""
	# ECHO_OUTPUT_VARIABLE
	OUTPUT_VARIABLE BASH_VERSION
)
string(STRIP "${BASH_VERSION}" BASH_VERSION)
message(STATUS "Found BASH: ${BASH} (found version \"${BASH_VERSION}\")")

if(NOT DEFINED BASH_MIN_VERSION_REQUIRED)
	set(BASH_MIN_VERSION_REQUIRED "4.4.0")
else()
	if(BASH_MIN_VERSION_REQUIRED LESS "4.4.0")
		set(BASH_MIN_VERSION_REQUIRED "4.4.0")
	endif()
endif()

if(${BASH_VERSION} LESS_EQUAL ${BASH_MIN_VERSION_REQUIRED})
	message(FATAL_ERROR "Failed: Bash >= v${BASH_MIN_VERSION_REQUIRED} is required for libmakepkg scripts.")
endif()

# bashcompletion = dependency('bash-completion', required : false)
# if bashcompletion.found()
#   BASHCOMPDIR = bashcompletion.get_pkgconfig_variable('completionsdir')
# else
#   BASHCOMPDIR = join_paths(DATAROOTDIR, 'bash-completion/completions')
# endif

include(FindCURL)
include(FindLibArchive)
include(FindIntl)
include(FindOpenSSL) # crypto provider
set(ALPM_DEPS)
list(APPEND ALPM_DEPS "OpenSSL::Crypto")
list(APPEND ALPM_DEPS "LibArchive::LibArchive")
list(APPEND ALPM_DEPS "CURL::libcurl")
list(APPEND ALPM_DEPS "Intl::Intl")
set(ALPM_DEPS "${ALPM_DEPS}" CACHE STRING "")

set(HAVE_LIBCURL false)
if(CURL_FOUND)
	set(HAVE_LIBCURL true CACHE STRING "") # Stored as a string for lower-case C syntax
endif()

set(HAVE_LIBARCHIVE false)
if(LibArchive_FOUND)
	set(HAVE_LIBARCHIVE true CACHE STRING "") # Stored as a string for lower-case C syntax
endif()

set(HAVE_LIBSSL false)
if(OPENSSL_FOUND)
	set(HAVE_LIBSSL true CACHE STRING "") # Stored as a string for lower-case C syntax
endif()

##############################################################################
##-- Meson options
##############################################################################

# directories and filenames
if(NOT DEFINED root_dir)
	set(root_dir "/") # CACHE PATH "Sets the location of the root operating directory.")
endif()
set(ROOTDIR "${root_dir}") #  CACHE PATH ""

if(NOT DEFINED pkg_ext)
	set(pkg_ext ".pkg.tar.gz") # CACHE STRING "Sets the file extension used by packages.")
endif()
set(PKG_EXT "${pkg_ext}") # CACHE STRING "The file extension used by packages."

if(NOT DEFINED src_ext)
	set(src_ext ".src.tar.gz") # CACHE STRING "set the file extension used by source packages")
endif()
set(SRC_EXT "${src_ext}") # CACHE STRING "The file extension used by source packages."

if(NOT DEFINED scriptlet_shell)
	set(scriptlet_shell "/bin/sh") # CACHE FILEPATH "The full path of the shell used to run install scriptlets.")
endif()
set(SCRIPTLET_SHELL "${scriptlet_shell}") # CACHE FILEPATH ""

if(NOT DEFINED ldconfig)
	set(ldconfig "/sbin/ldconfig") # CACHE FILEPATH "set the full path to ldconfig")
endif()
set(LDCONFIG "${ldconfig}") # CACHE FILEPATH "The full path to ldconfig."

if(NOT DEFINED buildscript)
	set(buildscript "PKGBUILD") # CACHE STRING "set the build script name used by makepkg")
endif()
set(BUILDSCRIPT "${buildscript}") # CACHE FILEPATH "The build script name used by makepkg."

if(NOT DEFINED datarootdir)
	set(datarootdir "share") # CACHE PATH "FIXME")
endif()
cmake_path(APPEND DATAROOTDIR "${PREFIX}" "${datarootdir}")
set(DATAROOTDIR "${DATAROOTDIR}" CACHE PATH "Read-only architecture-independent data root (share)")

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
set(LIB_VERSION "${libalpm_version}")

if(NOT DEFINED prefix)
	set(prefix "/usr")
endif()
set(PREFIX "${prefix}") # CACHE PATH ""

if(NOT DEFINED sysconfdir)
	set(sysconfdir "/etc")
endif()
cmake_path(APPEND SYSCONFDIR "${PREFIX}" "${sysconfdir}")
set(SYSCONFDIR "${SYSCONFDIR}") #  CACHE PATH "Read-only single-machine data (etc)"

if(NOT DEFINED localstatedir)
	set(localstatedir "/var")
endif()
cmake_path(APPEND LOCALSTATEDIR "${PREFIX}" "${localstatedir}")
set(LOCALSTATEDIR "${LOCALSTATEDIR}" CACHE PATH "Modifiable single-machine data (var)" FORCE)

##############################################################################
##-- Directory settings
##############################################################################

cmake_path(APPEND LOCALEDIR "${PREFIX}" "${DATAROOTDIR}/locale")
set(LOCALEDIR "${LOCALEDIR}" CACHE PATH "Locale-dependent data (DATAROOTDIR/locale)" FORCE)

cmake_path(APPEND BINDIR "${PREFIX}" "/bin")
set(BINDIR "${BINDIR}" CACHE PATH "User executables (bin)" FORCE)

cmake_path(APPEND MANDIR "${PREFIX}" "${DATAROOTDIR}/man")
set(MANDIR "${MANDIR}" CACHE PATH "Man documentation (DATAROOTDIR/man)" FORCE)

cmake_path(APPEND LIBDIR "${PREFIX}" "/lib")
set(LIBDIR "${LIBDIR}" CACHE PATH "Object code libraries (lib)")

cmake_path(APPEND SBINDIR "${PREFIX}" "/sbin")
set(SBINDIR "${SBINDIR}" CACHE PATH "System admin executables (sbin)")

cmake_path(APPEND LIBEXECDIR "${PREFIX}" "/libexec")
set(LIBEXECDIR "${LIBEXECDIR}" CACHE PATH "Program executables (libexec)")

cmake_path(APPEND SHAREDSTATEDIR "${PREFIX}" "/com")
set(SHAREDSTATEDIR "${SHAREDSTATEDIR}" CACHE PATH "Modifiable architecture-independent data (com)")

cmake_path(APPEND INCLUDEDIR "${PREFIX}" "/include")
set(INCLUDEDIR "${INCLUDEDIR}" CACHE PATH "C header files (include)")

set(DATADIR "${DATAROOTDIR}" CACHE PATH "Read-only architecture-independent data (DATAROOTDIR)")

cmake_path(APPEND INFODIR "${DATAROOTDIR}" "/info")
set(INFODIR "${INFODIR}" CACHE PATH "Info documentation (DATAROOTDIR/info)")

cmake_path(APPEND DOCDIR "${DATAROOTDIR}" "/doc" "/${PROJECT_NAME}")
set(DOCDIR "${DOCDIR}" CACHE PATH "Documentation root (DATAROOTDIR/doc/PROJECT_NAME)")

cmake_path(APPEND RUNSTATEDIR "${LOCALSTATEDIR}" "/run")
set(RUNSTATEDIR "${RUNSTATEDIR}" CACHE PATH "Run-time variable data (LOCALSTATEDIR/run)")

# set(_GNU_SOURCE TRUE CACHE BOOL "")
set(PACKAGE "${PROJECT_NAME}" CACHE STRING "")
set(PACKAGE_VERSION "${PROJECT_VERSION}" CACHE STRING "")

cmake_path(APPEND LIBMAKEPKGDIR "${PREFIX}" "${DATAROOTDIR}/makepkg")
set(LIBMAKEPKGDIR "${LIBMAKEPKGDIR}" CACHE PATH "" FORCE)

cmake_path(APPEND PKGDATADIR "${PREFIX}" "${DATAROOTDIR}/${PROJECT_NAME}")
set(PKGDATADIR "${PKGDATADIR}" CACHE PATH "" FORCE)

cmake_path(APPEND SYSHOOKDIR "${DATAROOTDIR}" "/libalpm/hooks/")
set(SYSHOOKDIR "${SYSHOOKDIR}" CACHE PATH "")

cmake_path(APPEND CONFFILE "${SYSCONFDIR}" "/pacman.conf")
set(CONFFILE "${CONFFILE}" CACHE PATH "")

cmake_path(APPEND DBPATH "${LOCALSTATEDIR}" "lib/pacman/")
set(DBPATH "${DBPATH}" CACHE PATH "")

cmake_path(APPEND GPGDIR "${SYSCONFDIR}" "/pacman.d/gnupg/")
set(GPGDIR "${GPGDIR}" CACHE PATH "")

cmake_path(APPEND LOGFILE "${LOCALSTATEDIR}" "/log/pacman.log")
set(LOGFILE "${LOGFILE}" CACHE FILEPATH "")

cmake_path(APPEND CACHEDIR "${LOCALSTATEDIR}" "/cache/pacman/pkg/")
set(CACHEDIR "${CACHEDIR}" CACHE FILEPATH "")

cmake_path(APPEND HOOKDIR "${SYSCONFDIR}" "/pacman.d/hooks/")
set(HOOKDIR "${HOOKDIR}" CACHE FILEPATH "")


##############################################################################
##-- Compiler settings
##############################################################################

set(CMAKE_REQUIRED_DEFINITIONS "-D_GNU_SOURCE")
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
	set(CMAKE_REQUIRED_DEFINITIONS "_GNU_SOURCE")
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
set(HAVE_STRUCT_STAT_ST_BLKSIZE false)
CHECK_STRUCT_HAS_MEMBER("struct stat" st_blksize "sys/stat.h" has_struct_stat_st_blksize LANGUAGE C)
if(has_struct_stat_st_blksize)
	set(HAVE_STRUCT_STAT_ST_BLKSIZE true CACHE STRING "" FORCE)
endif()

set(HAVE_STRUCT_STATVFS_F_FLAG false)
CHECK_STRUCT_HAS_MEMBER("struct statvfs" f_flag "sys/statvfs.h" has_struct_statvfs_f_flag LANGUAGE C)
if(has_struct_statvfs_f_flag)
	set(HAVE_STRUCT_STATVFS_F_FLAG true CACHE STRING "" FORCE)
endif()

set(HAVE_STRUCT_STATFS_F_FLAGS false)
CHECK_STRUCT_HAS_MEMBER("struct statfs" f_flags "sys/param.h" has_struct_statfs_f_flags LANGUAGE C)
if(has_struct_statfs_f_flags)
	set(HAVE_STRUCT_STATFS_F_FLAGS true CACHE STRING "" FORCE)
else()
	CHECK_STRUCT_HAS_MEMBER("struct statfs" f_flags "sys/mount.h" has_struct_statfs_f_flags_sys_mount LANGUAGE C)
	if(has_struct_statfs_f_flags_sys_mount)
		set(HAVE_STRUCT_STATFS_F_FLAGS true CACHE STRING "" FORCE)
	endif()
endif()

include(CheckTypeSize)
set(PACMAN_REQUIRED_TYPES)
list(APPEND PACMAN_REQUIRED_TYPES
	mode_t
	uid_t
	off_t
	pid_t
	size_t
	ssize_t
	int64_t
)

foreach(_typedef IN LISTS PACMAN_REQUIRED_TYPES)
	if(NOT DEFINED HAVE_${_typedef})
		check_type_size(${_typedef} ${_typedef} LANGUAGE C)
		if (DEFINED ${_typedef})
		else ()
			# Set 'unsigned int' types
			if( _typedef STREQUAL mode_t OR
				_typedef STREQUAL uid_t OR
				_typedef STREQUAL size_t
			)
				set(${_typedef} "unsigned int" CACHE STRING "" FORCE)
			# Set 'unsigned int' types
			elseif( _typedef STREQUAL off_t OR
					_typedef STREQUAL pid_t OR
					_typedef STREQUAL ssize_t
			)
				set(${_typedef} "signed int" CACHE STRING "" FORCE)
			elseif(_typedef STREQUAL int64_t)
				set(${_typedef} "signed long int" CACHE STRING "" FORCE)
			endif()
			set(${_typedef}_CODE "#define ${_typedef} ${${_typedef}}" CACHE STRING "" FORCE)
		endif ()
	endif()
endforeach()
unset(_typedef)

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

# ###############################################################################
# ##-- Targets: 'libmakepkg::<libmakepkg_modules>'
# ###############################################################################

if (NOT ${PROJECT_SOURCE_DIR} EQUAL ${PROJECT_BINARY_DIR})

	configure_file(
		##-- Input
		"build-aux/configure.sh.in"
		##-- Output
		"configure.sh"
		##-- Modifier
		@ONLY
	)
endif ()
set(PACMAN_CONFIGURATION_SCRIPT "${PROJECT_BINARY_DIR}/configure.sh")

set(INPUT "${CMAKE_CURRENT_LIST_DIR}/include/pacman-defines.h")
set(OUTPUT "${CMAKE_BINARY_DIR}/include/pacman-defines.h")

add_custom_target(
	configure
	ALL ${BASH} -e ${PACMAN_CONFIGURATION_SCRIPT} "${INPUT}" "${OUTPUT}"
	SOURCES "${INPUT}"
	BYPRODUCTS "${OUTPUT}"
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	USES_TERMINAL
)

unset(INPUT)
unset(OUTPUT)


if (NOT ${PROJECT_SOURCE_DIR} EQUAL ${PROJECT_BINARY_DIR})

	configure_file("include/pacman-defines.h" 			"include/pacman-defines.h" @ONLY)
	configure_file("include/pacman-config.h" 			"include/pacman-config.h" @ONLY)

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
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/pacman-config.h>
            $<INSTALL_INTERFACE:include/pacman-config.h>
			# include/application/defines.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/pacman-defines.h>
            $<INSTALL_INTERFACE:include/pacman-defines.h>
)

set_target_properties (configuration

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        LIBRARY_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY lib
        PDB_OUTPUT_DIRECTORY     bin

		C_STANDARD 17
		C_STANDARD_REQUIRED TRUE
		# VISIBILITY_INLINES_HIDDEN TRUE
		HAS_CXX FALSE
)

target_compile_features(configuration
	INTERFACE
		c_std_17
)

# target_compile_definitions(configuration
# 	INTERFACE
# 		_GNU_SOURCE
# )

install(
	TARGETS configuration
	EXPORT LibConfigTargets
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILE_SET configuration_PUBLIC_HEADERS
)

install (
	EXPORT LibConfigTargets
	FILE LibConfigTargets.cmake
	NAMESPACE pacman::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/pacman/config"
)

# ##-- Create package config
include (CMakePackageConfigHelpers)

configure_package_config_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/share/LibConfigConfig.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/LibConfigConfig.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/LibConfig"
)

install (
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/LibConfigConfig.cmake"
		# "${CMAKE_CURRENT_BINARY_DIR}/share/LibConfigConfigVersion.cmake"
	DESTINATION
		"${CMAKE_INSTALL_LIBDIR}/cmake/LibConfig"
)

export(
	EXPORT LibConfigTargets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/LibConfigTargets.cmake"
	NAMESPACE pacman::
)
