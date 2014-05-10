
aux_source_directory(. SRC_LIST)

include_directories(. "${PROJECT_SOURCE_DIR}/src/colamd")

foreach(test ${SRC_LIST} )
    string( REPLACE ".c" "" executable ${test} )
    if("${test}" MATCHES "colamd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} COLAMD_L)
    else("${test}" MATCHES "colamd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} COLAMD)
    endif("${test}" MATCHES "colamd_l_*")
endforeach (test)
