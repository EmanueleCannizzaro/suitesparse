
aux_source_directory(. SRC_LIST)

include_directories(.)
include_directories(. "${PROJECT_SOURCE_DIR}/src/cholmod")

add_library(SPQR SHARED ${SRC_LIST})
target_link_libraries(SPQR m)
