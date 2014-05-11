
PROJECT(btf)

set(SUITESPARSE_BTF_VERSION_MAJOR 1)
set(SUITESPARSE_BTF_VERSION_MINOR 2)
set(SUITESPARSE_BTF_VERSION_PATCH 0)


FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")


add_library(btf_di SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(btf_di m)

add_library(btf_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(btf_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(btf_dl m)

add_library(btf_zi SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(btf_zi PROPERTIES COMPILE_FLAGS "-DZLONG=ON")
target_link_libraries(btf_zi m)

add_library(btf_zl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(btf_zl PROPERTIES COMPILE_FLAGS "-DZLONG=ON -DDLONG=ON")
target_link_libraries(btf_zl m)
