
FILE(GLOB SRC_LIST RELATIVE "${PROJECT_SOURCE_DIR}/test" *.c )
include_directories(. "${PROJECT_SOURCE_DIR}/src")
list(REMOVE_ITEM SRC_LIST "cs_demo.c")
#list(REMOVE_ITEM SRC_LIST "cs_di_demo.c")
#list(REMOVE_ITEM SRC_LIST "cs_dl_demo.c")
#list(REMOVE_ITEM SRC_LIST "cs_ci_demo.c")
#list(REMOVE_ITEM SRC_LIST "cs_cl_demo.c")

FILE(GLOB MATRIX_LIST RELATIVE "${PROJECT_SOURCE_DIR}/validation" "*.tri" )
message("${MATRIX_LIST}")

foreach(test ${SRC_LIST} )
  if("${test}" MATCHES ".c$")
    string(REPLACE ".c" "" executable ${test})
    add_executable( ${executable} ${test} )
    target_link_libraries( ${executable} cxsparse)
    set(MATRIX_LIST bcsstk01.tri lp_afiro.tri)
    foreach(matrix ${MATRIX_LIST} )
      add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}_${matrix}.out"
                     DEPENDS "${executable}"
                     COMMAND "${executable}"
                     ARGS < "${PROJECT_SOURCE_DIR}/matrix/${matrix}" > "${CMAKE_CURRENT_BINARY_DIR}/${executable}_${matrix}.out")
      add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}_${matrix}.out.diff"
                     DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}_${matrix}.out" "${PROJECT_SOURCE_DIR}/validation/${executable}_${matrix}.out"
                     COMMAND diff
                     ARGS "${CMAKE_CURRENT_BINARY_DIR}/${executable}_${matrix}.out" "${PROJECT_SOURCE_DIR}/validation/${executable}_${matrix}.out" > "${CMAKE_CURRENT_BINARY_DIR}/${executable}_${matrix}.out.diff")
      add_custom_target(my${executable}_${matrix} ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}_${matrix}.out.diff")
      add_test(NAME ${executable}_${matrix}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND diff "${CMAKE_CURRENT_BINARY_DIR}/${executable}_${matrix}.out" "${PROJECT_SOURCE_DIR}/validation/${executable}_${matrix}.out")
    endforeach(matrix)
  endif("${test}" MATCHES ".c$")
endforeach(test)
