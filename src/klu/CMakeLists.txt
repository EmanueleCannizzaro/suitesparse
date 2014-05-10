
aux_source_directory(. SRC_LIST)

include_directories(.)
include_directories(. "${PROJECT_SOURCE_DIR}/src/amd")
include_directories(. "${PROJECT_SOURCE_DIR}/src/colamd")
include_directories(. "${PROJECT_SOURCE_DIR}/src/btf")

add_library(KLU SHARED ${SRC_LIST})
target_link_libraries(KLU m)

add_library(KLU_L SHARED ${SRC_LIST})
set_target_properties(KLU_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(KLU_L m)
