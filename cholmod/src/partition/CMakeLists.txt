
file(GLOB HEADER_FILES "*.h")
file(GLOB SRC_LIST "*.c")

include_directories("../../../camd/src")
include_directories("../../../ccolamd/src")
include_directories("../../../../metis/include")

add_library(cholmod_partition_di SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(cholmod_partition_dl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})

#add_dependencies(cholmod_partition_di cholmod_core_di)
#add_dependencies(cholmod_partition_dl cholmod_core_dl)

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(cholmod_partition_di PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(cholmod_partition_dl PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )


