
PROJECT(ccolamd)

set(SUITESPARSE_CCOLAMD_VERSION_MAJOR 2)
set(SUITESPARSE_CCOLAMD_VERSION_MINOR 8)
set(SUITESPARSE_CCOLAMD_VERSION_PATCH 0)


FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")


add_library(ccolamd_di SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(ccolamd_di PROPERTIES COMPILE_FLAGS "-DDLONG=OFF -DZLONG=OFF")
target_link_libraries(ccolamd_di m)

add_library(ccolamd_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(ccolamd_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON -DZLONG=OFF")
target_link_libraries(ccolamd_dl m)

add_library(ccolamd_zi SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(ccolamd_zi PROPERTIES COMPILE_FLAGS "-DZLONG=ON -DDLONG=OFF")
target_link_libraries(ccolamd_zi m)

add_library(ccolamd_zl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(ccolamd_zl PROPERTIES COMPILE_FLAGS "-DZLONG=ON -DDLONG=ON")
target_link_libraries(ccolamd_zl m)
