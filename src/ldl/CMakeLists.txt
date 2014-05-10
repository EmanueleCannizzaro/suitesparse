
aux_source_directory(. SRC_LIST)

include_directories(.)

add_library(LDL SHARED ${SRC_LIST})
target_link_libraries(LDL m)

##add_definitions(-DDLONG=1)
add_library(LDL_L SHARED ${SRC_LIST})
set_target_properties(LDL_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(LDL_L m)
