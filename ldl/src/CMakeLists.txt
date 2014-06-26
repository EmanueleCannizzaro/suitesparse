PROJECT(ldl)


set(SUITESPARSE_LDL_VERSION_MAJOR 2)
set(SUITESPARSE_LDL_VERSION_MINOR 1)
set(SUITESPARSE_LDL_VERSION_PATCH 0)

FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")


add_library(ldl_di SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(ldl_di m)

add_library(ldl_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(ldl_dl PROPERTIES COMPILE_FLAGS "-DLDL_LONG=ON")
target_link_libraries(ldl_dl m)

add_library(ldl_ci SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(ldl_ci PROPERTIES COMPILE_FLAGS "-DZLONG=ON")
target_link_libraries(ldl_ci m)

add_library(ldl_cl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(ldl_cl PROPERTIES COMPILE_FLAGS "-DZLONG=ON -DLDL_LONG=ON")
target_link_libraries(ldl_cl m)
