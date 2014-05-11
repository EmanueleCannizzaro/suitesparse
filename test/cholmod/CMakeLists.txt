
aux_source_directory(. SRC_LIST)

include_directories(. "${PROJECT_SOURCE_DIR}/src/cholmod")

foreach(test ${SRC_LIST} )
    string( REPLACE ".c" "" executable ${test} )
    if("${test}" MATCHES "cholmod_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} cholmod_dl)
    elseif("${test}" MATCHES "cholmod_i_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} cholmod_di)
    endif("${test}" MATCHES "cholmod_l_*")
endforeach (test)
