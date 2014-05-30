
PROJECT(camd)

set(SUITESPARSE_CAMD_VERSION_MAJOR 2)
set(SUITESPARSE_CAMD_VERSION_MINOR 3)
set(SUITESPARSE_CAMD_VERSION_PATCH 1)


FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")



add_library(camd_di SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(camd_di m)

add_library(camd_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(camd_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(camd_dl m)

add_library(camd_zi SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(camd_zi PROPERTIES COMPILE_FLAGS "-DZLONG=ON")
target_link_libraries(camd_zi m)

add_library(camd_zl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(camd_zl PROPERTIES COMPILE_FLAGS "-DZLONG=ON -DDLONG=ON")
target_link_libraries(camd_zl m)
