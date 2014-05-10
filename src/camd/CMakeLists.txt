
aux_source_directory(. SRC_LIST)

include_directories(.)

add_library(CAMD SHARED ${SRC_LIST})
target_link_libraries(CAMD m)

add_library(CAMD_L SHARED ${SRC_LIST})
set_target_properties(CAMD_L PROPERTIES COMPILE_FLAGS "-DDLONG=1")
target_link_libraries(CAMD_L m)
