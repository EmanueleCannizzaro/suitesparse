
aux_source_directory(. SRC_LIST)

include_directories(.)
include_directories(..)

add_library(CHOLMOD_CHECK SHARED ${SRC_LIST})
target_link_libraries(CHOLMOD_CHECK m)

add_library(CHOLMOD_CHECK_L SHARED ${SRC_LIST})
set_target_properties(CHOLMOD_CHECK_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(CHOLMOD_CHECK_L m)
