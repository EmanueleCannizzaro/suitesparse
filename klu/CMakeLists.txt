# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# Updated by Emanuele Cannizzaro () 2014-05-21
# -----------------------------------------------------------------

PROJECT(klu)

option(KLU_HAS_VERSION_FUNCTION OFF)
option(KLU_DATE "Jun 20, 2012")

set(KLU_VERSION_MAJOR 1)
set(KLU_VERSION_MINOR 2)
set(KLU_VERSION_PATCH 1)

set(KLU_MAIN_VERSION 2)
set(KLU_SUB_VERSION 8)
set(KLU_SUBSUB_VERSION 0)
set(KLU_VERSION ${KLU_MAIN_VERSION} * 1000 + ${KLU_SUB_VERSION})

add_subdirectory(src)
add_library(klu SHARED  $<TARGET_OBJECTS:klu_di> $<TARGET_OBJECTS:klu_dl>)
target_link_libraries(klu m)
#add_subdirectory(test)
add_subdirectory(doc)
