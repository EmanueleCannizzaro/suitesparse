
file(GLOB HEADER_FILES RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.h")
set(SRC_LIST "camd_global.c" "camd_control.c" "camd_defaults.c" "camd_info.c")

file(GLOB SRC_LIST_REPEATED RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.c")
list(REMOVE_ITEM SRC_LIST_REPEATED ${SRC_LIST})

add_library(camd_core SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(camd_i SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})
add_library(camd_l SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(camd_core PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(camd_i PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(camd_l PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

add_library(camd SHARED $<TARGET_OBJECTS:camd_core> $<TARGET_OBJECTS:camd_i> $<TARGET_OBJECTS:camd_l>)
target_link_libraries(camd m)
