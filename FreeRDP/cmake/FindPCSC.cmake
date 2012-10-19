
include(FindPkgConfig)

if (PKG_CONFIG_FOUND)
	pkg_check_modules(PCSC libpcsclite)
endif()

find_path(PCSC_INCLUDE_DIR pcsclite.h
	PATHS ${PCSC_INCLUDE_DIRS}
	PATH_SUFFIXES PCSC)

find_library(PCSC_LIBRARY pcsclite
	PATHS ${PCSC_LIBRARY_DIRS})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(PCSC DEFAULT_MSG PCSC_INCLUDE_DIR PCSC_LIBRARY)

mark_as_advanced(PCSC_INCLUDE_DIR PCSC_LIBRARY)

