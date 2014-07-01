# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# Updated by Emanuele Cannizzaro () 2014-05-21
# -----------------------------------------------------------------

PROJECT(csparse)

option(CSPARSE_HAS_VERSION_FUNCTION OFF)
option(CSPARSE_DATE "Jun 20, 2012")

set(CSPARSE_VERSION_MAJOR 2)
set(CSPARSE_VERSION_MINOR 8)
set(CSPARSE_VERSION_PATCH 0)

set(SPARSE_MAIN_VERSION 2)
set(SPARSE_SUB_VERSION 8)
set(SPARSE_SUBSUB_VERSION 0)
set(SPARSE_VERSION ${SPARSE_MAIN_VERSION} * 1000 + ${SPARSE_SUB_VERSION})

add_subdirectory(src)
add_library(csparse SHARED $<TARGET_OBJECTS:csparse_di>)
target_link_libraries(csparse m)
add_subdirectory(test)
#add_subdirectory(doc)
