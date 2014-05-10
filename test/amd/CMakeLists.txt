
aux_source_directory(. SRC_LIST)

include_directories(. "${PROJECT_SOURCE_DIR}/src/amd")

foreach(test ${SRC_LIST} )
    string( REPLACE ".c" "" executable ${test} )
    if("${test}" MATCHES "amd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} AMD_L)
    else("${test}" MATCHES "amd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} AMD)
    endif("${test}" MATCHES "amd_l_*")
endforeach (test)
