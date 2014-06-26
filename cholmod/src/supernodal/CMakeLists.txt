
aux_source_directory(. SRC_LIST)
include_directories(${SRC_LIST})
include_directories(..)

set(HEADER_FILES )
#set(HEADER_FILES *.h )

add_library(cholmod_supernodal_di SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(cholmod_supernodal_di lapack blas m)

add_library(cholmod_supernodal_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(cholmod_supernodal_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(cholmod_supernodal_dl lapack blas m)

add_dependencies(cholmod_supernodal_di cholmod_core_di)
add_dependencies(cholmod_supernodal_dl cholmod_core_dl)
