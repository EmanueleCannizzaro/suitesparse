
aux_source_directory(. SRC_LIST)
include_directories(${SRC_LIST})
include_directories(..)

set(HEADER_FILES )
#set(HEADER_FILES *.h )

add_library(cholmod_core_di SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(cholmod_core_di m)

add_library(cholmod_core_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(cholmod_core_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(cholmod_core_dl m)
