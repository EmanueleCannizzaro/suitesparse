
FILE(GLOB SRC_LIST RELATIVE "${PROJECT_SOURCE_DIR}/test/ccolamd" *.c )
include_directories(. "${PROJECT_SOURCE_DIR}/src/ccolamd")

foreach(test ${SRC_LIST} )
  if("${test}" MATCHES ".c$")
    string(REPLACE ".c" "" executable ${test})
    if("${executable}" MATCHES "ccolamd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} ccolamd_dl ccolamd_di)
    elseif("${executable}" MATCHES "ccolamd_i_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} ccolamd_di)
    else("${executable}" MATCHES "ccolamd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} ccolamd_di)
    endif("${executable}" MATCHES "ccolamd_l_*")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out"
                     DEPENDS "${executable}"
                     COMMAND "${executable}"
                     ARGS > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff"
                     DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/ccolamd/${executable}.out"
                     COMMAND diff
                     ARGS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/ccolamd/${executable}.out" > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_custom_target(my${executable} ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_test(NAME ${executable}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND diff "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/ccolamd/${executable}.out")
  endif("${test}" MATCHES ".c$")
endforeach (test)
