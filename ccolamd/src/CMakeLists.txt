
file(GLOB HEADER_FILES "*.h")
file(GLOB SRC_LIST "*.c")
list(REMOVE_ITEM SRC_LIST "${PROJECT_SOURCE_DIR}/src/ccolamd_global.c")

add_library(ccolamd_di SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
add_library(ccolamd_dl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
#add_library(ccolamd_zi SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})
#add_library(ccolamd_zl SHARED OBJECT ${SRC_LIST} ${HEADER_FILES})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(ccolamd_di PROPERTIES COMPILE_FLAGS "-fPIC")
  set_target_properties(ccolamd_dl PROPERTIES COMPILE_FLAGS "-fPIC -DDLONG=ON")
  #set_target_properties(ccolamd_zi PROPERTIES COMPILE_FLAGS "-fPIC -DZLONG=ON")
  #set_target_properties(ccolamd_zl PROPERTIES COMPILE_FLAGS "-fPIC -DZLONG=ON -DDLONG=ON")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
