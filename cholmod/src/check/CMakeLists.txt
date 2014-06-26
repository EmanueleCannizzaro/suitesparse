
aux_source_directory(. SRC_LIST)
include_directories(${SRC_LIST})
include_directories(..)

set(HEADER_FILES )
#set(HEADER_FILES *.h )

add_library(cholmod_check_di SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(cholmod_check_di cholmod_blas_di m)

add_library(cholmod_check_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(cholmod_check_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(cholmod_check_dl cholmod_blas_dl m)

add_dependencies(cholmod_check_di cholmod_core_di cholmod_blas_di)
add_dependencies(cholmod_check_dl cholmod_core_dl cholmod_blas_dl)
