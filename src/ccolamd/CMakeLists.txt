
aux_source_directory(. SRC_LIST)

include_directories(.)

add_library(CCOLAMD SHARED ${SRC_LIST})
target_link_libraries(CCOLAMD m)

add_library(CCOLAMD_L SHARED ${SRC_LIST})
set_target_properties(CCOLAMD_L PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(CCOLAMD_L m)
