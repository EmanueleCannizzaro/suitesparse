
aux_source_directory(. SRC_LIST)

#SET(SRC_LIST *.c)
#list(REMOVE_ITEM SRC_LIST cs_demo.c)

include_directories(. "${PROJECT_SOURCE_DIR}/src/csparse")

foreach(test ${SRC_LIST} )
  if("${test}" MATCHES "cs_demo.c")
  else("${test}" MATCHES "cs_demo.c")
    string( REPLACE ".c" "" executable ${test} )
    add_executable( ${executable} ${test} "cs_demo.c")
    target_link_libraries( ${executable} csparse)
  endif("${test}" MATCHES "cs_demo.c")
endforeach (test)
