
aux_source_directory(. SRC_LIST)

include_directories(. "${PROJECT_SOURCE_DIR}/src/csparse")

foreach(test ${SRC_LIST} )
    string( REPLACE ".c" "" executable ${test} )
    if("${test}" MATCHES "cs_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} CSPARSE_L)
    else("${test}" MATCHES "cs_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} CSPARSE)
    endif("${test}" MATCHES "cs_l_*")
endforeach (test)
