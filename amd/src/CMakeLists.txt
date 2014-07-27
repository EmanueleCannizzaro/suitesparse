
file(GLOB HEADER_FILES RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.h")
set(SRC_LIST "amd_global.c" "amd_control.c" "amd_defaults.c" "amd_info.c")

file(GLOB SRC_LIST_REPEATED RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.c")
list(REMOVE_ITEM SRC_LIST_REPEATED ${SRC_LIST})

add_library(amd_core SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(amd_i SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})
add_library(amd_l SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(amd_core PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(amd_i PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(amd_l PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

add_library(amd SHARED $<TARGET_OBJECTS:amd_core> $<TARGET_OBJECTS:amd_i> $<TARGET_OBJECTS:amd_l>)
target_link_libraries(amd m)

