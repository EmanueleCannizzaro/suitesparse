
aux_source_directory(. SRC_LIST)

include_directories(.)
include_directories(..)
include_directories(. "${PROJECT_SOURCE_DIR}/src/amd")
include_directories(. "${PROJECT_SOURCE_DIR}/src/colamd")

add_library(CHOLMOD_CHOLESKY SHARED ${SRC_LIST})
target_link_libraries(CHOLMOD_CHOLESKY AMD COLAMD m)

add_library(CHOLMOD_CHOLESKY_L SHARED ${SRC_LIST})
set_target_properties(CHOLMOD_CHOLESKY_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(CHOLMOD_CHOLESKY_L AMD_L COLAMD_L m)
