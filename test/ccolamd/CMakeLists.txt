
aux_source_directory(. SRC_LIST)

include_directories(. "${PROJECT_SOURCE_DIR}/src/ccolamd")

foreach(test ${SRC_LIST} )
    string( REPLACE ".c" "" executable ${test} )
    if("${test}" MATCHES "ccolamd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} ccolamd_dl)
    elseif("${test}" MATCHES "ccolamd_i_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} ccolamd_di)
    endif("${test}" MATCHES "ccolamd_l_*")
endforeach (test)
