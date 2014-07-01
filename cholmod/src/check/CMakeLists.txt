
file(GLOB HEADER_FILES "*.h")
file(GLOB SRC_LIST "*.c")

add_library(cholmod_check_di SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(cholmod_check_dl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})

#add_dependencies(cholmod_check_di cholmod_core_di cholmod_blas_di)
#add_dependencies(cholmod_check_dl cholmod_core_dl cholmod_blas_dl)

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(cholmod_check_di PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(cholmod_check_dl PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )


