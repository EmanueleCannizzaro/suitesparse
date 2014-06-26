
FILE(GLOB SRC_LIST RELATIVE "${PROJECT_SOURCE_DIR}/test/klu" *.c )
include_directories(. "${PROJECT_SOURCE_DIR}/src/klu")
include_directories(. "${PROJECT_SOURCE_DIR}/src/amd")
include_directories(. "${PROJECT_SOURCE_DIR}/src/colamd")
include_directories(. "${PROJECT_SOURCE_DIR}/src/btf")
include_directories(. "${PROJECT_SOURCE_DIR}/src/cholmod")

foreach(test ${SRC_LIST} )
  if("${test}" MATCHES ".c$")
    string(REPLACE ".c" "" executable ${test})
    if("${executable}" MATCHES "klu_dl_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} klu_dl)
    elseif("${executable}" MATCHES "klu_di_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} klu_di)
    elseif("${executable}" MATCHES "klu_cl_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} klu_cl)
    elseif("${executable}" MATCHES "klu_ci_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} klu_ci)
    else("${executable}" MATCHES "klu_dl_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} klu_cl klu_ci klu_dl klu_di cholmod_dl cholmod_di colamd_dl colamd_di amd_dl amd_di btf_dl btf_di)
    endif("${executable}" MATCHES "klu_dl_*")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out"
                     DEPENDS "${executable}"
                     COMMAND "${executable}"
                     ARGS > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff"
                     DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/klu/${executable}.out"
                     COMMAND diff
                     ARGS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/klu/${executable}.out" > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_custom_target(my${executable} ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_test(NAME ${executable}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND diff "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/klu/${executable}.out")
  endif("${test}" MATCHES ".c$")
endforeach (test)
