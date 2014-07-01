
file(GLOB HEADER_FILES "*.h")
file(GLOB SRC_LIST "*.c")

include_directories("../../../amd/src")
include_directories("../../../colamd/src")

add_library(cholmod_cholesky_di SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(cholmod_cholesky_dl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})

#add_dependencies(cholmod_cholesky_di cholmod_core_di amd_di colamd_di)
#add_dependencies(cholmod_cholesky_dl cholmod_core_dl amd_dl colamd_dl)

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(cholmod_cholesky_di PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(cholmod_cholesky_dl PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )


