
file(GLOB HEADER_FILES RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.h")
set(SRC_LIST "cxsparse_convert.c" "cxsparse_demo.c")

file(GLOB SRC_LIST_REPEATED RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.c")
list(REMOVE_ITEM SRC_LIST_REPEATED ${SRC_LIST})

add_library(cxsparse_core SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(cxsparse_di SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})
add_library(cxsparse_dl SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})
add_library(cxsparse_ci SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})
add_library(cxsparse_cl SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(cxsparse_core PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(cxsparse_di PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(cxsparse_dl PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
  set_target_properties(cxsparse_ci PROPERTIES COMPILE_FLAGS "-fPIC -DDCOMPLEX=ON")
  set_target_properties(cxsparse_cl PROPERTIES COMPILE_FLAGS "-fPIC -DDCOMPLEX=ON -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

add_library(cxsparse SHARED $<TARGET_OBJECTS:cxsparse_core> $<TARGET_OBJECTS:cxsparse_di> $<TARGET_OBJECTS:cxsparse_dl> $<TARGET_OBJECTS:cxsparse_ci> $<TARGET_OBJECTS:cxsparse_cl>)
target_link_libraries(cxsparse m)
