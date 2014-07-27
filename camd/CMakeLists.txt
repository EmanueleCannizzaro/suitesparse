# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# Updated by Emanuele Cannizzaro () 2014-05-21
# -----------------------------------------------------------------

PROJECT(camd)

option(CAMD_HAS_VERSION_FUNCTION OFF)
option(CAMD_DATE "Jun 20, 2012")

set(CAMD_VERSION_MAJOR 2)
set(CAMD_VERSION_MINOR 3)
set(CAMD_VERSION_PATCH 1)

set(CAMD_MAIN_VERSION 2)
set(CAMD_SUB_VERSION 3)
set(CAMD_SUBSUB_VERSION 1)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(doc)
