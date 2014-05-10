
aux_source_directory(. SRC_LIST)

include_directories(.)
include_directories(..)
include_directories(. "${PROJECT_SOURCE_DIR}/src/camd")
include_directories(. "${PROJECT_SOURCE_DIR}/src/ccolamd")
include_directories(. "../../../../metis-5.1.0/include")

add_library(CHOLMOD_PARTITION SHARED ${SRC_LIST})
target_link_libraries(CHOLMOD_PARTITION "${PROJECT_SOURCE_DIR}/lib/libmetis.so" "${PROJECT_SOURCE_DIR}/lib/libGKlib.so" CAMD CCOLAMD m)

add_library(CHOLMOD_PARTITION_L SHARED ${SRC_LIST})
set_target_properties(CHOLMOD_PARTITION_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(CHOLMOD_PARTITION_L "${PROJECT_SOURCE_DIR}/lib/libmetis.so" "${PROJECT_SOURCE_DIR}/lib/libGKlib.so" CAMD_L CCOLAMD_L m)
