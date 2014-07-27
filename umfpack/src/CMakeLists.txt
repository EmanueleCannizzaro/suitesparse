
FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")

include_directories("${amd_SOURCE_DIR}/src")
include_directories("${cholmod_SOURCE_DIR}")
include_directories("${cholmod_SOURCE_DIR}/..")
##include_directories("${PROJECT_SOURCE_DIR}/src")

add_library(umfpack_di SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(umfpack_dl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
#add_library(umfpack_ci SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
#add_library(umfpack_cl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(umfpack_di PROPERTIES COMPILE_FLAGS "-fPIC -DDINT=ON")
  set_target_properties(umfpack_dl PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
  #set_target_properties(umfpack_ci PROPERTIES COMPILE_FLAGS "-fPIC -DZINT=ON")
  #set_target_properties(umfpack_cl PROPERTIES COMPILE_FLAGS "-fPIC -DZLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

add_library(umfpack SHARED ${SRC_LIST} $<TARGET_OBJECTS:umfpack_di> $<TARGET_OBJECTS:umfpack_dl>)
target_link_libraries(umfpack cholmod colamd amd lapack blas m)
