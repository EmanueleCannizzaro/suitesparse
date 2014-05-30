
FILE(GLOB SRC_LIST RELATIVE "${PROJECT_SOURCE_DIR}/test/cxsparse" *.c )
include_directories(. "${PROJECT_SOURCE_DIR}/src/cxsparse")

foreach(test ${SRC_LIST} )
  if("${test}" MATCHES ".c$")
    string(REPLACE ".c" "" executable ${test})
    if("${executable}" MATCHES "cs_dl_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} cxsparse_dl)
    elseif("${executable}" MATCHES "cs_di_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} cxsparse_di)
    elseif("${executable}" MATCHES "cs_cl_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} cxsparse_cl)
    elseif("${executable}" MATCHES "cs_ci_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} cxsparse_ci)
    else("${executable}" MATCHES "cs_dl_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} cxsparse_di)
    endif("${executable}" MATCHES "cs_dl_*")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out"
                     DEPENDS "${executable}"
                     COMMAND "${executable}"
                     ARGS > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff"
                     DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/cxsparse/${executable}.out"
                     COMMAND diff
                     ARGS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/cxsparse/${executable}.out" > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_custom_target(my${executable} ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_test(NAME ${executable}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND diff "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/cxsparse/${executable}.out")
  endif("${test}" MATCHES ".c$")
endforeach (test)
