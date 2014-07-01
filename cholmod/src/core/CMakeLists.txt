
file(GLOB HEADER_FILES "*.h")
file(GLOB SRC_LIST "*.c")

add_library(cholmod_core_di SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(cholmod_core_dl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(cholmod_core_di PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(cholmod_core_dl PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
