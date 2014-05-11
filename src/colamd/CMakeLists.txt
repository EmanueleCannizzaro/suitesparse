
PROJECT(colamd)

set(SUITESPARSE_COLAMD_VERSION_MAJOR 2)
set(SUITESPARSE_COLAMD_VERSION_MINOR 8)
set(SUITESPARSE_COLAMD_VERSION_PATCH 0)

include_directories(${SRC_LIST})


FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")


add_library(colamd_di SHARED ${SRC_LIST} ${HEADER_FILES})
#set_target_properties(colamd_di PROPERTIES COMPILE_FLAGS "-DDLONG=OFF -DZLONG=OFF")
target_link_libraries(colamd_di m)

add_library(colamd_dl SHARED ${SRC_LIST} ${HEADER_FILES})
#set_target_properties(colamd_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON -DZLONG=OFF")
set_target_properties(colamd_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(colamd_dl m)

add_library(colamd_zi SHARED ${SRC_LIST} ${HEADER_FILES})
#set_target_properties(colamd_zi PROPERTIES COMPILE_FLAGS "-DZLONG=ON -DDLONG=OFF")
set_target_properties(colamd_zi PROPERTIES COMPILE_FLAGS "-DZLONG=ON")
target_link_libraries(colamd_zi m)

add_library(colamd_zl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(colamd_zl PROPERTIES COMPILE_FLAGS "-DZLONG=ON -DDLONG=ON")
target_link_libraries(colamd_zl m)
