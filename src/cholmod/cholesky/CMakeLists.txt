
include_directories(..)
include_directories("../../amd")
include_directories("../../colamd")

FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")

add_library(cholmod_cholesky_di SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(cholmod_cholesky_di amd_di colamd_di m)

add_library(cholmod_cholesky_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(cholmod_cholesky_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(cholmod_cholesky_dl amd_dl colamd_dl m)

add_dependencies(cholmod_cholesky_di cholmod_core_di amd_di colamd_di)
add_dependencies(cholmod_cholesky_dl cholmod_core_dl amd_dl colamd_dl)
