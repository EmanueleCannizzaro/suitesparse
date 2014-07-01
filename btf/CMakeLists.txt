# -----------------------------------------------------------------
# CMake build system for SuiteSparse
#  http://code.google.com/p/suitesparse-metis-for-windows/
# Created by Jose Luis Blanco (University of Almeria) 2013-2014
# Updated by jesnault (jerome.esnault@inria.fr) 2014-01-21
# Updated by Emanuele Cannizzaro () 2014-05-21
# -----------------------------------------------------------------

PROJECT(btf)

set(BTF_VERSION_MAJOR 1)
set(BTF_VERSION_MINOR 2)
set(BTF_VERSION_PATCH 0)

set(BTF_MAIN_VERSION 1)
set(BTF_SUB_VERSION 2)
set(BTF_SUBSUB_VERSION 0)
set(BTF_VERSION ${BTF_MAIN_VERSION} * 1000 + ${BTF_SUB_VERSION})

add_subdirectory(src)
add_library(btf SHARED $<TARGET_OBJECTS:btf_di> $<TARGET_OBJECTS:btf_dl>)
target_link_libraries(btf m)
add_subdirectory(doc)
