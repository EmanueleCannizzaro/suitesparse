
include_directories(..)
include_directories("../../../camd/src")
include_directories("../../../ccolamd/src")
include_directories("../../../../metis/include")

FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")

add_library(cholmod_partition_di SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(cholmod_partition_di "${suitesparse_SOURCE_DIR}/lib/libmetis.so" "${suitesparse_SOURCE_DIR}/lib/libGKlib.so" camd_di ccolamd_di m)

add_library(cholmod_partition_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(cholmod_partition_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(cholmod_partition_dl "${suitesparse_SOURCE_DIR}/lib/libmetis.so" "${suitesparse_SOURCE_DIR}/lib/libGKlib.so" camd_dl ccolamd_dl m)

add_dependencies(cholmod_partition_di cholmod_core_di)
add_dependencies(cholmod_partition_dl cholmod_core_dl)
