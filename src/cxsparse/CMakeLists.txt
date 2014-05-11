
PROJECT(cxsparse)

set(SUITESPARSE_CXSPARSE_VERSION_MAJOR 3)
set(SUITESPARSE_CXSPARSE_VERSION_MINOR 1)
set(SUITESPARSE_CXSPARSE_VERSION_PATCH 2)


FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")



add_library(cxsparse_di SHARED ${SRC_LIST})
set_target_properties(cxsparse_di PROPERTIES COMPILE_FLAGS "-DCS_LONG=OFF -DCS_COMPLEX=OFF")
target_link_libraries(cxsparse_di m)

add_library(cxsparse_dl SHARED ${SRC_LIST})
set_target_properties(cxsparse_dl PROPERTIES COMPILE_FLAGS "-DCS_LONG=ON -DCS_COMPLEX=OFF")
target_link_libraries(cxsparse_dl m)

add_library(cxsparse_zi SHARED ${SRC_LIST})
set_target_properties(cxsparse_zi PROPERTIES COMPILE_FLAGS "-DCS_COMPLEX=ON -DCS_LONG=OFF")
target_link_libraries(cxsparse_zi m)

add_library(cxsparse_zl SHARED ${SRC_LIST})
set_target_properties(cxsparse_zl PROPERTIES COMPILE_FLAGS "-DCS_COMPLEX=ON -DCS_LONG=ON")
target_link_libraries(cxsparse_zl m)
