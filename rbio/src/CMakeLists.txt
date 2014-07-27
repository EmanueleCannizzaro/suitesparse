
file(GLOB HEADER_FILES RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.h")
set(SRC_LIST "rbio_global.c")

file(GLOB SRC_LIST_REPEATED RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.c")
list(REMOVE_ITEM SRC_LIST_REPEATED ${SRC_LIST})

add_library(rbio_core SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(rbio_i SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})
add_library(rbio_l SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(rbio_core PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(rbio_i PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(rbio_l PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

add_library(rbio SHARED $<TARGET_OBJECTS:rbio_core> $<TARGET_OBJECTS:rbio_i> $<TARGET_OBJECTS:rbio_l>)
target_link_libraries(rbio m)
