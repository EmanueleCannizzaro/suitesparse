
FILE(GLOB SRC_LIST RELATIVE "${PROJECT_SOURCE_DIR}/test" *.c )
include_directories(. "${PROJECT_SOURCE_DIR}/src")

foreach(test ${SRC_LIST} )
  if("${test}" MATCHES ".c$")
    string(REPLACE ".c" "" executable ${test})
    #if("${executable}" MATCHES "colamd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} colamd)
    #elseif("${executable}" MATCHES "colamd_i_*")
      #add_executable( ${executable} ${test} )
      #target_link_libraries( ${executable} colamd_di)
    #else("${executable}" MATCHES "colamd_l_*")
      #add_executable( ${executable} ${test} )
      #target_link_libraries( ${executable} colamd_di)
    #endif("${executable}" MATCHES "colamd_l_*")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out"
                     DEPENDS "${executable}"
                     COMMAND "${executable}"
                     ARGS > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff"
                     DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/${executable}.out"
                     COMMAND diff
                     ARGS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/${executable}.out" > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_custom_target(my${executable} ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_test(NAME ${executable}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND diff "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/${executable}.out")
  endif("${test}" MATCHES ".c$")
endforeach (test)
