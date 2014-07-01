# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# Updated by Emanuele Cannizzaro () 2014-05-21
# -----------------------------------------------------------------

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

option(SPQR_HAS_VERSION_FUNCTION OFF)
option(SPQR_DATE "Jun 20, 2012")

set(SPQR_VERSION_MAJOR 1)
set(SPQR_VERSION_MINOR 3)
set(SPQR_VERSION_PATCH 1)

set(SPQR_MAIN_VERSION 1)
set(SPQR_SUB_VERSION 3)
set(SPQR_SUBSUB_VERSION 1)
set(SPQR_VERSION ${SPQR_MAIN_VERSION} * 1000 + ${SPQR_SUB_VERSION})

add_subdirectory(src)
#add_subdirectory(test)
add_subdirectory(doc)
