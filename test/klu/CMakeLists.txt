
aux_source_directory(. SRC_LIST)

include_directories(. "${PROJECT_SOURCE_DIR}/src/klu")
include_directories(. "${PROJECT_SOURCE_DIR}/src/amd")
include_directories(. "${PROJECT_SOURCE_DIR}/src/colamd")
include_directories(. "${PROJECT_SOURCE_DIR}/src/btf")
include_directories(. "${PROJECT_SOURCE_DIR}/src/cholmod")

foreach(test ${SRC_LIST} )
    string( REPLACE ".c" "" executable ${test} )
    ##if("${test}" MATCHES "amd_l_*")
      ##add_executable( ${executable} ${test} )
      ##target_link_libraries( ${executable} KLU_L)
    ##else("${test}" MATCHES "amd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} KLU CHOLMOD COLAMD AMD BTF)
    ##endif("${test}" MATCHES "amd_l_*")
endforeach (test)
