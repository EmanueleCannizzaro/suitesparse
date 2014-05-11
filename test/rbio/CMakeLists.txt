
aux_source_directory(. SRC_LIST)

include_directories(. "${PROJECT_SOURCE_DIR}/src/rbio")

foreach(test ${SRC_LIST} )
  string( REPLACE ".c" "" executable ${test} )
  add_executable( ${executable} ${test} )
  target_link_libraries( ${executable} rbio cholmod_dl cholmod_di)
endforeach (test)
