# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# Updated by Emanuele Cannizzaro () 2014-05-21
# -----------------------------------------------------------------

PROJECT(cholmod)

option(CHOLMOD_HAS_VERSION_FUNCTION OFF)
option(CHOLMOD_DATE "Jun 20, 2012")

set(CHOLMOD_VERSION_MAJOR 2)
set(CHOLMOD_VERSION_MINOR 1)
set(CHOLMOD_VERSION_PATCH 2)

set(CHOLMOD_MAIN_VERSION 2)
set(CHOLMOD_SUB_VERSION 1)
set(CHOLMOD_SUBSUB_VERSION 2)
set(CHOLMOD_VERSION ${CHOLMOD_MAIN_VERSION} * 1000 + ${CHOLMOD_SUB_VERSION})

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(doc)
