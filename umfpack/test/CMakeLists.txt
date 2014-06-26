
FILE(GLOB SRC_LIST RELATIVE "${PROJECT_SOURCE_DIR}/test/umfpack" *.c )
list(REMOVE_ITEM SRC_LIST umf4_f77.c)
list(REMOVE_ITEM SRC_LIST umf4_z_f77.c)
list(REMOVE_ITEM SRC_LIST umfpack_xx_demo.c)

include_directories(. "${PROJECT_SOURCE_DIR}/src/umfpack")
include_directories(. "${PROJECT_SOURCE_DIR}/src/amd")
include_directories(. "${PROJECT_SOURCE_DIR}/src/cholmod")

foreach(test ${SRC_LIST} )
  if("${test}" MATCHES ".c$")
    string(REPLACE ".c" "" executable ${test})
    if("${executable}" MATCHES "umfpack_di_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} UMFPACK_DI CHOLMOD AMD)
    elseif("${executable}" MATCHES "umfpack_dl_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} UMFPACK_DL CHOLMOD_L AMD_L)
    elseif("${executable}" MATCHES "umfpack_zi_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} UMFPACK_ZI CHOLMOD AMD)
    elseif("${executable}" MATCHES "umfpack_zl_*")
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} UMFPACK_ZL CHOLMOD_L AMD_L)
    else()
      add_executable( ${executable} ${test} )
      target_link_libraries( ${executable} umfpack_zl umfpack_zi umfpack_dl umfpack_di cholmod_dl cholmod_di amd_dl amd_di)
    endif("${executable}" MATCHES "umfpack_di_*")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out"
                     DEPENDS "${executable}"
                     COMMAND "${executable}"
                     ARGS > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff" 
                     DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/umfpack/${executable}.out"
                     COMMAND diff
                     ARGS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/umfpack/${executable}.out" > "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_custom_target(my${executable} ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out.diff")
    add_test(NAME ${executable} 
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND diff "${CMAKE_CURRENT_BINARY_DIR}/${executable}.out" "${PROJECT_SOURCE_DIR}/data/umfpack/${executable}.out")
  endif("${test}" MATCHES ".c$")
endforeach (test)
