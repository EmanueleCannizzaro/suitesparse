
aux_source_directory(. SRC_LIST)

include_directories(. "${PROJECT_SOURCE_DIR}/src/colamd")

foreach(test ${SRC_LIST} )
    string( REPLACE ".c" "" executable ${test} )
    if("${test}" MATCHES "colamd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} colamd_dl)
    elseif("${test}" MATCHES "colamd_i_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} colamd_di)
    endif("${test}" MATCHES "colamd_l_*")
endforeach (test)
