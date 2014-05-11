
aux_source_directory(. SRC_LIST)

include_directories(. "${PROJECT_SOURCE_DIR}/src/ldl")

foreach(test ${SRC_LIST} )
    string( REPLACE ".c" "" executable ${test} )
    if("${test}" MATCHES "ldl_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} ldl_dl)
    elseif("${test}" MATCHES "ldl_i_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} ldl_di)
    endif("${test}" MATCHES "ldl_l_*")
endforeach (test)
