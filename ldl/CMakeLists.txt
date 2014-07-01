# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# Updated by Emanuele Cannizzaro () 2014-05-21
# -----------------------------------------------------------------

PROJECT(ldl)

option(LDL_HAS_VERSION_FUNCTION OFF)
option(LDL_DATE "Jun 20, 2012")

set(LDL_VERSION_MAJOR 2)
set(LDL_VERSION_MINOR 1)
set(OLAMD_VERSION_PATCH 0)

set(LDL_MAIN_VERSION 2)
set(LDL_SUB_VERSION 8)
set(LDL_SUBSUB_VERSION 0)
set(LDL_VERSION ${LDL_MAIN_VERSION} * 1000 + ${LDL_SUB_VERSION})

add_subdirectory(src)
#add_subdirectory(test)
add_subdirectory(doc)
