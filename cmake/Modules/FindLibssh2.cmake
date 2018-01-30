# - Try to find libssh2
# Once done this will define
#  LIBUBOX_FOUND        - System has libssh2
#  LIBSSH2_INCLUDE_DIR  - The libssh2 include directories
#  LIBSSH2_LIBRARY      - The libraries needed to use libssh2

find_path(LIBSSH2_INCLUDE_DIR libssh2.h PATH_SUFFIXES libssh2)
find_library(LIBSSH2_LIBRARY ssh2 PATH_SUFFIXES lib64)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBSSH2_FOUND to TRUE
# if all listed variables are TRUE and the requested version matches.
find_package_handle_standard_args(libssh2 REQUIRED_VARS
                                  LIBSSH2_LIBRARY LIBSSH2_INCLUDE_DIR
                                  VERSION_VAR LIBSSH2_VERSION)

mark_as_advanced(LIBSSH2_INCLUDE_DIR LIBSSH2_LIBRARY)
