
aux_source_directory(. SRC_LIST)

include_directories(.)
include_directories(..)

add_library(CHOLMOD_MODIFY SHARED ${SRC_LIST})
target_link_libraries(CHOLMOD_MODIFY m)

add_library(CHOLMOD_MODIFY_L SHARED ${SRC_LIST})
set_target_properties(CHOLMOD_MODIFY_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(CHOLMOD_MODIFY_L m)
