
file(GLOB HEADER_FILES "*.h")
file(GLOB SRC_LIST "*.c")

add_library(cholmod_supernodal_di SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(cholmod_supernodal_dl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})

#add_dependencies(cholmod_supernodal_di cholmod_core_di)
#add_dependencies(cholmod_supernodal_dl cholmod_core_dl)

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(cholmod_supernodal_di PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(cholmod_supernodal_dl PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

