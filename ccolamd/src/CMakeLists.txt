
file(GLOB HEADER_FILES RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.h")
set(SRC_LIST "ccolamd_global.c" "ccolamd_defaults.c")

file(GLOB SRC_LIST_REPEATED RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.c")
list(REMOVE_ITEM SRC_LIST_REPEATED ${SRC_LIST})

add_library(ccolamd_core SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(ccolamd_i SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})
add_library(ccolamd_l SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(ccolamd_core PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(ccolamd_i PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(ccolamd_l PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

add_library(ccolamd SHARED $<TARGET_OBJECTS:ccolamd_core> $<TARGET_OBJECTS:ccolamd_i> $<TARGET_OBJECTS:ccolamd_l>)
target_link_libraries(ccolamd m)
