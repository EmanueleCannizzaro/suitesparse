# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# Updated by Emanuele Cannizzaro () 2014-05-21
# -----------------------------------------------------------------

PROJECT(ccolamd)

option(CCOLAMD_HAS_VERSION_FUNCTION OFF)
option(CCOLAMD_DATE "Jun 20, 2012")

set(CCOLAMD_VERSION_MAJOR 2)
set(CCOLAMD_VERSION_MINOR 8)
set(CCOLAMD_VERSION_PATCH 0)

set(CCOLAMD_MAIN_VERSION 2)
set(CCOLAMD_SUB_VERSION 8)
set(CCOLAMD_SUBSUB_VERSION 0)
set(CCOLAMD_VERSION ${CCOLAMD_MAIN_VERSION} * 1000 + ${CCOLAMD_SUB_VERSION})

add_subdirectory(src)
add_library(ccolamd SHARED src/ccolamd_global.c $<TARGET_OBJECTS:ccolamd_di> $<TARGET_OBJECTS:ccolamd_dl>)
target_link_libraries(ccolamd m)
add_subdirectory(test)
add_subdirectory(doc)
