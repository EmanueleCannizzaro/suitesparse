
aux_source_directory(. SRC_LIST)
include_directories(${SRC_LIST})
include_directories(..)

FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")

add_library(cholmod_blas_di SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(cholmod_blas_di m)

add_library(cholmod_blas_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(cholmod_blas_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(cholmod_blas_dl m)

add_dependencies(cholmod_blas_di cholmod_core_di)
add_dependencies(cholmod_blas_dl cholmod_core_dl)