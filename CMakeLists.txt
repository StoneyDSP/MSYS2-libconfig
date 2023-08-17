cmake_minimum_required(VERSION 3.18...3.27 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/share/cmake/Modules")

project(pkgman_config)
enable_language(C)

include(GNUInstallDirs)

add_library (pkgman_config_lib	                                     			STATIC)
add_library (pkgman_config::pkgman_config_lib                					ALIAS pkgman_config_lib)
add_library (pkgman::pkgman_config::pkgman_config_lib                			ALIAS pkgman_config_lib)

target_sources(pkgman_config_lib

	PUBLIC

		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
		$<INSTALL_INTERFACE:include>
)



target_sources (pkgman_config_lib

    PUBLIC

        FILE_SET pkgman_config_lib_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include>
        FILES
            # include/pkgman_config.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/pkgman_config.h>
            $<INSTALL_INTERFACE:include/pkgman_config.h>
)

target_sources (pkgman_config_lib
	PRIVATE
		"src/pkgman_config.c"
)


set_target_properties (pkgman_config_lib

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

target_compile_features(pkgman_config_lib
	PUBLIC
		c_std_17
)

target_compile_definitions(pkgman_config_lib
	PUBLIC
		_GNU_SOURCE
		_XOPEN_SOURCE
		_DEFAULT_SOURCE
)

file(COPY include/pkgman_config.h DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/include")

install(
	TARGETS pkgman_config_lib
	EXPORT pkgman_config_lib_targets
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILE_SET pkgman_config_lib_PUBLIC_HEADERS
)

install (
	EXPORT pkgman_config_lib_targets
	FILE pkgman_config_lib_targets.cmake
	NAMESPACE pkgman::pkgman_config::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/pkgman/pkgman_config"
)

# ##-- Create package config
include (CMakePackageConfigHelpers)

configure_package_config_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/share/pkgman_config_config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/pkgman_config_config.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/pkgman/pkgman_config"
)

install (
	FILES
	"${CMAKE_CURRENT_BINARY_DIR}/pkgman_config_config.cmake"
		# "${CMAKE_CURRENT_BINARY_DIR}/share/LibConfigConfigVersion.cmake"
	DESTINATION
		"${CMAKE_INSTALL_LIBDIR}/cmake/pkgman/pkgman_config"
)

export(
	EXPORT pkgman_config_lib_targets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/pkgman_config_targets.cmake"
	NAMESPACE pkgman::pkgman_config::
)
