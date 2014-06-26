
file(GLOB HEADER_FILES "*.h")
file(GLOB SRC_LIST "*.c")
list(REMOVE_ITEM SRC_LIST "${PROJECT_SOURCE_DIR}/src/camd_global.c")

add_library(camd_di SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(camd_dl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
#add_library(camd_zi SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
#add_library(camd_zl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(camd_di PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(camd_dl PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
  #set_target_properties(amd_zi PROPERTIES COMPILE_FLAGS "-fPIC -DZLONG=ON")
  #set_target_properties(amd_zl PROPERTIES COMPILE_FLAGS "-fPIC -DZLONG=ON -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
