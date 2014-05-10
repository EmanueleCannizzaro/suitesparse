
aux_source_directory(. SRC_LIST)

include_directories(.)

add_library(CXSPARSE_DI SHARED ${SRC_LIST})
target_link_libraries(CXSPARSE_DI m)

add_library(CXSPARSE_DL SHARED ${SRC_LIST})
set_target_properties(CXSPARSE_DL PROPERTIES COMPILE_FLAGS "-DCS_LONG")
target_link_libraries(CXSPARSE_DL m)

add_library(CXSPARSE_CI SHARED ${SRC_LIST})
set_target_properties(CXSPARSE_CI PROPERTIES COMPILE_FLAGS "-DCS_COMPLEX")
target_link_libraries(CXSPARSE_CI m)

add_library(CXSPARSE_CL SHARED ${SRC_LIST})
set_target_properties(CXSPARSE_CL PROPERTIES COMPILE_FLAGS "-DCS_LONG -DCS_COMPLEX")
target_link_libraries(CXSPARSE_CL m)
