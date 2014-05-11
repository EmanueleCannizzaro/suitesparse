
aux_source_directory(. SRC_LIST)
#FILE(GLOB SRC_LIST RELATIVE "${PROJECT_SOURCE_DIR}/test/amd" *.c )
#FILE(GLOB SRC_LIST *.c )
#list(REMOVE_ITEM SRC_LIST "${PROJECT_SOURCE_DIR}/test/amd/amd_demo.c")
include_directories(. "${PROJECT_SOURCE_DIR}/src/amd")

foreach(test ${SRC_LIST} )
  if("${test}" MATCHES ".c$")
    string(REPLACE ".c" "" executable ${test})
    if("${executable}" MATCHES "amd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} amd_dl)
    elseif("${executable}" MATCHES "amd_i_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} amd_di)
    else("${executable}" MATCHES "amd_l_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} amd_di)
    endif("${executable}" MATCHES "amd_l_*")
    add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/test/amd/${executable}.out"
                     DEPENDS ${executable} 
                     COMMAND ${executable}
                     ARGS > "${PROJECT_BINARY_DIR}/test/amd/${executable}.out")
    add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/test/amd/${executable}.out.diff" 
                     DEPENDS "${PROJECT_BINARY_DIR}/test/amd/${executable}.out" "${PROJECT_SOURCE_DIR}/data/amd/${executable}.out"
                     COMMAND diff
                     ARGS "${PROJECT_BINARY_DIR}/test/amd/${executable}.out" "${PROJECT_SOURCE_DIR}/data/amd/${executable}.out" > "${PROJECT_BINARY_DIR}/test/amd/${executable}.out.diff")
    set(AMD_TEST_FILES ${AMD_TEST_FILES} "${PROJECT_BINARY_DIR}/test/amd/${executable}.out.diff")
    #add_custom_command(TARGET ${executable}
                       #COMMAND ${CMAKE_COMMAND}
                       #ARGS -E echo ${AMD_TEST_FILES})
    #add_custom_target(my${executable} ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff)
  endif("${test}" MATCHES ".c$")
endforeach (test)

add_custom_target(AMD_TESTER ALL DEPENDS ${AMD_TEST_FILES})
