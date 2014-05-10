
aux_source_directory(. SRC_LIST)

include_directories(.)

add_library(CSPARSE SHARED ${SRC_LIST})
target_link_libraries(CSPARSE m)
