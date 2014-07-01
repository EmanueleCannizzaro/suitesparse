
FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")

add_library(cxsparse_di SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(cxsparse_dl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(cxsparse_ci SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(cxsparse_cl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(cxsparse_di PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(cxsparse_dl PROPERTIES COMPILE_FLAGS "-fPIC -DCS_LONG=ON")
  set_target_properties(cxsparse_ci PROPERTIES COMPILE_FLAGS "-fPIC -DCS_COMPLEX=ON")
  set_target_properties(cxsparse_cl PROPERTIES COMPILE_FLAGS "-fPIC -DCS_COMPLEX=ON -DCS_LONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
