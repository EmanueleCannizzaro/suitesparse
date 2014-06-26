
PROJECT(spqr)

#------------------------------------------------------------------------------
# SuiteSparseQR configuration:
#------------------------------------------------------------------------------

# The SuiteSparseQR library can be compiled with the following options:
#
# -DNPARTITION      do not include the CHOLMOD partition module
# -DNEXPERT         do not include the functions in SuiteSparseQR_expert.cpp
# -DHAVE_TBB        enable the use of Intel's Threading Building Blocks (TBB)

# default, without timing, without TBB:
# SPQR_CONFIG =
# with TBB:
# SPQR_CONFIG = -DHAVE_TBB

# This is needed for IBM AIX: (but not for and C codes, just C++)
# SPQR_CONFIG = -DBLAS_NO_UNDERSCORE

# with TBB, you must select this:
# TBB = -ltbb
# without TBB:
#TBB =

set(SUITESPARSE_SPQR_VERSION_MAJOR 1)
set(SUITESPARSE_SPQR_VERSION_MINOR 3)
set(SUITESPARSE_SPQR_VERSION_PATCH 1)

include_directories("../cholmod")

FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.cpp")

add_library(spqr SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(spqr m)
