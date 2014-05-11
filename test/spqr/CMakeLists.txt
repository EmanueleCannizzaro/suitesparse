
aux_source_directory(. SRC_LIST)

include_directories(. "${PROJECT_SOURCE_DIR}/src/spqr")
include_directories(. "${PROJECT_SOURCE_DIR}/src/cholmod")

foreach(test ${SRC_LIST} )
  string( REPLACE ".c" "" executable ${test} )
  add_executable( ${executable} ${test} )
  target_link_libraries( ${executable} spqr cholmod_dl amd_dl)
endforeach (test)
