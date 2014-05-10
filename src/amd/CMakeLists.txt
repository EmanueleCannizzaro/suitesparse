
aux_source_directory(. SRC_LIST)

include_directories(.)

add_library(AMD SHARED ${SRC_LIST})
target_link_libraries(AMD m)

##add_definitions(-DDLONG=1)
add_library(AMD_L SHARED ${SRC_LIST})
set_target_properties(AMD_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(AMD_L m)
