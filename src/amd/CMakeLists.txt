
PROJECT(amd)

set(SUITESPARSE_AMD_VERSION_MAJOR 2)
set(SUITESPARSE_AMD_VERSION_MINOR 3)
set(SUITESPARSE_AMD_VERSION_PATCH 1)

FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")

add_library(amd_di SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(amd_di m)

add_library(amd_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(amd_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(amd_dl m)

add_library(amd_zi SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(amd_zi PROPERTIES COMPILE_FLAGS "-DZLONG=ON")
target_link_libraries(amd_zi m)

add_library(amd_zl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(amd_zl PROPERTIES COMPILE_FLAGS "-DZLONG=ON -DDLONG=ON")
target_link_libraries(amd_zl m)
