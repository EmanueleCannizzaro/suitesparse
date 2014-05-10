
aux_source_directory(. SRC_LIST)

include_directories(.)

add_library(CHOLMOD_SUPERNODAL SHARED ${SRC_LIST})
target_link_libraries(CHOLMOD_SUPERNODAL lapack blas m)

add_library(CHOLMOD_SUPERNODAL_L SHARED ${SRC_LIST})
set_target_properties(CHOLMOD_SUPERNODAL_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(CHOLMOD_SUPERNODAL_L lapack blas m)
