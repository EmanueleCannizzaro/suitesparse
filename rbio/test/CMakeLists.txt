
FILE(GLOB SRC_LIST RELATIVE "${PROJECT_SOURCE_DIR}/test" *.c)
include_directories("${PROJECT_SOURCE_DIR}/src")

foreach(test ${SRC_LIST} )
  if("${test}" MATCHES ".c$")
    string(REPLACE ".c" "" executable ${test})
    add_executable( ${executable} ${test} ../../SuiteSparse_config.c)
    if("${test}" MATCHES "^rbio_l")
      set_target_properties(${executable} PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
    endif("${test}" MATCHES "^rbio_l")
    target_link_libraries( ${executable} rbio ${GLIB_PKG_LIBRARIES})
    FILE(GLOB MATRIX_LIST RELATIVE "${PROJECT_SOURCE_DIR}/matrix" "${PROJECT_SOURCE_DIR}/matrix/*.rb" )
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
endforeach (test)
