
file(GLOB HEADER_FILES RELATIVE "${PROJECT_SOURCE_DIR}/src/core" "*.h")
set(SRC_LIST "cholmod_core.c")

file(GLOB SRC_LIST_REPEATED RELATIVE "${PROJECT_SOURCE_DIR}/src/core" "*.c")
list(REMOVE_ITEM SRC_LIST_REPEATED ${SRC_LIST})

##add_library(cholmod_core_core SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(cholmod_core_i SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})
add_library(cholmod_core_l SHARED OBJECT ${SRC_LIST_REPEATED} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  ##set_target_properties(cholmod_core_core PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(cholmod_core_i PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(cholmod_core_l PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

##add_library(cholmod_core SHARED $<TARGET_OBJECTS:cholmod_core_core> $<TARGET_OBJECTS:cholmod_core_i> $<TARGET_OBJECTS:cholmod_core_l>)
add_library(cholmod_core SHARED $<TARGET_OBJECTS:cholmod_core_i> $<TARGET_OBJECTS:cholmod_core_l>)
target_link_libraries(cholmod_core m)

