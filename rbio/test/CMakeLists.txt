
FILE(GLOB SRC_LIST RELATIVE "${PROJECT_SOURCE_DIR}/test/rbio" *.c )
include_directories(. "${PROJECT_SOURCE_DIR}/src/rbio")

foreach(test ${SRC_LIST} )
  if("${test}" MATCHES ".c$")
    string(REPLACE ".c" "" executable ${test})
    if("${executable}" MATCHES "rb_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} rbio cholmod_dl cholmod_di)
    elseif("${executable}" MATCHES "rb_i_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} rbio cholmod_dl cholmod_di)
    else("${executable}" MATCHES "rb_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} rbio cholmod_dl cholmod_di)
    endif("${executable}" MATCHES "rb_l_*")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out"
                     DEPENDS "${executable}"
                     COMMAND "${executable}"
                     ARGS > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff"
                     DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/rbio/${executable}.out"
                     COMMAND diff
                     ARGS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/rbio/${executable}.out" > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_custom_target(my${executable} ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_test(NAME ${executable}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND diff "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/rbio/${executable}.out")
  endif("${test}" MATCHES ".c$")
endforeach (test)
