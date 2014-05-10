
aux_source_directory(. SRC_LIST)

include_directories(. "${PROJECT_SOURCE_DIR}/src/camd")

foreach(test ${SRC_LIST} )
    string( REPLACE ".c" "" executable ${test} )
    if("${test}" MATCHES "camd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} CAMD_L)
    else("${test}" MATCHES "camd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} CAMD)
    endif("${test}" MATCHES "camd_l_*")
endforeach (test)
