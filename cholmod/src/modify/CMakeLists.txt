
file(GLOB HEADER_FILES "*.h")
file(GLOB SRC_LIST "*.c")

include_directories("../../../amd/src")
include_directories("../../../colamd/src")

add_library(cholmod_modify_di SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(cholmod_modify_dl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})

#add_dependencies(cholmod_modify_di cholmod_core_di)
#add_dependencies(cholmod_modify_dl cholmod_core_dl)

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(cholmod_modify_di PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(cholmod_modify_dl PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
