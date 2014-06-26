
aux_source_directory(. SRC_LIST)
include_directories(${SRC_LIST})
include_directories(..)

set(HEADER_FILES )
#set(HEADER_FILES *.h )

add_library(cholmod_modify_di SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(cholmod_modify_di m)

add_library(cholmod_modify_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(cholmod_modify_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(cholmod_modify_dl m)

add_dependencies(cholmod_modify_di cholmod_core_di)
add_dependencies(cholmod_modify_dl cholmod_core_dl)
