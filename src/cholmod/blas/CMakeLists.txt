
aux_source_directory(. SRC_LIST)

include_directories(.)

add_library(CHOLMOD_BLAS SHARED ${SRC_LIST})
target_link_libraries(CHOLMOD_BLAS m)

add_library(CHOLMOD_BLAS_L SHARED ${SRC_LIST})
set_target_properties(CHOLMOD_BLAS_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(CHOLMOD_BLAS_L m)
