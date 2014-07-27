# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# Updated by Emanuele Cannizzaro () 2014-05-21
# -----------------------------------------------------------------

PROJECT(cxsparse)

option(CXSPARSE_HAS_VERSION_FUNCTION OFF)
option(CXSPARSE_DATE "Jun 20, 2012")

set(CXSPARSE_VERSION_MAJOR 2)
set(CXSPARSE_VERSION_MINOR 8)
set(CXSPARSE_VERSION_PATCH 0)

set(CXSPARSE_MAIN_VERSION 2)
set(CXSPARSE_SUB_VERSION 8)
set(CXSPARSE_SUBSUB_VERSION 0)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(doc)
