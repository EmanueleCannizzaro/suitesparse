# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# Updated by Emanuele Cannizzaro () 2014-05-21
# -----------------------------------------------------------------

PROJECT(rbio)

option(RBIO_HAS_VERSION_FUNCTION OFF)
option(RBIO_DATE "Jun 20, 2012")

set(RBIO_VERSION_MAJOR 2)
set(RBIO_VERSION_MINOR 1)
set(RBIO_VERSION_PATCH 1)

set(RBIO_MAIN_VERSION 2)
set(RBIO_SUB_VERSION 1)
set(RBIO_SUBSUB_VERSION 1)
set(RBIO_VERSION ${RBIO_MAIN_VERSION} * 1000 + ${RBIO_SUB_VERSION})

add_subdirectory(src)
#add_subdirectory(test)
add_subdirectory(doc)
