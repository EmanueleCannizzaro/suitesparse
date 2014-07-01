
FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")

include_directories("${amd_SOURCE_DIR}/src")
include_directories("${colamd_SOURCE_DIR}/src")
include_directories("${btf_SOURCE_DIR}/src")

add_library(klu_di SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(klu_dl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
#add_library(klu_ci SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
#add_library(klu_cl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(klu_di PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(klu_dl PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
  #set_target_properties(klu_ci PROPERTIES COMPILE_FLAGS "-DCOMPLEX=ON")
  #set_target_properties(klu_cl PROPERTIES COMPILE_FLAGS "-DCOMPLEX=ON -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
