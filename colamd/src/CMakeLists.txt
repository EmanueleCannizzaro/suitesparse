
file(GLOB HEADER_FILES RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.h")
set(SRC_LIST "colamd_global.c" "colamd_defaults.c")

file(GLOB SRC_LIST_REPEATED RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.c")
list(REMOVE_ITEM SRC_LIST_REPEATED ${SRC_LIST})

add_library(colamd_core SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(colamd_i SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})
add_library(colamd_l SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(colamd_core PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(colamd_i PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(colamd_l PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

add_library(colamd SHARED $<TARGET_OBJECTS:colamd_core> $<TARGET_OBJECTS:colamd_i> $<TARGET_OBJECTS:colamd_l>)
target_link_libraries(colamd m)
