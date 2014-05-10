
aux_source_directory(. SRC_LIST)

include_directories(.)

add_library(CHOLMOD_CORE SHARED ${SRC_LIST})
target_link_libraries(CHOLMOD_CORE m)

add_library(CHOLMOD_CORE_L SHARED ${SRC_LIST})
set_target_properties(CHOLMOD_CORE_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(CHOLMOD_CORE_L m)
