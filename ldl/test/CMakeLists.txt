
FILE(GLOB SRC_LIST RELATIVE "${PROJECT_SOURCE_DIR}/test/ldl" *.c )
include_directories(. "${PROJECT_SOURCE_DIR}/src/ldl")

foreach(test ${SRC_LIST} )
  if("${test}" MATCHES ".c$")
    string(REPLACE ".c" "" executable ${test})
    if("${executable}" MATCHES "ldl_dl_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} ldl_dl)
    elseif("${executable}" MATCHES "ldl_di_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} ldl_di)
    elseif("${executable}" MATCHES "ldl_cl_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} ldl_cl)
    elseif("${executable}" MATCHES "ldl_ci_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} ldl_ci)
    else("${executable}" MATCHES "ldl_dl_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} ldl_cl ldl_ci ldl_dl ldl_di)
    endif("${executable}" MATCHES "ldl_dl_*")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out"
                     DEPENDS "${executable}"
                     COMMAND "${executable}"
                     ARGS > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff"
                     DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/ldl/${executable}.out"
                     COMMAND diff
                     ARGS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/ldl/${executable}.out" > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_custom_target(my${executable} ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_test(NAME ${executable}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND diff "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/ldl/${executable}.out")
  endif("${test}" MATCHES ".c$")
endforeach (test)
