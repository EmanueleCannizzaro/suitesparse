
aux_source_directory(. SRC_LIST)

include_directories(.)

add_library(COLAMD SHARED ${SRC_LIST})
target_link_libraries(COLAMD m)

add_library(COLAMD_L SHARED ${SRC_LIST})
set_target_properties(COLAMD_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(COLAMD_L m)
