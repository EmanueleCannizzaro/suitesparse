
aux_source_directory(. SRC_LIST)

include_directories(. "${PROJECT_SOURCE_DIR}/src/klu")
include_directories(. "${PROJECT_SOURCE_DIR}/src/amd")
include_directories(. "${PROJECT_SOURCE_DIR}/src/colamd")
include_directories(. "${PROJECT_SOURCE_DIR}/src/btf")
include_directories(. "${PROJECT_SOURCE_DIR}/src/cholmod")

foreach(test ${SRC_LIST} )
  string( REPLACE ".c" "" executable ${test} )
  add_executable( ${executable} ${test} )
  target_link_libraries( ${executable} klu_zl klu_zi klu_dl klu_di cholmod_dl cholmod_di colamd_dl colamd_di amd_dl amd_di btf_dl btf_di)
  ##target_link_libraries( ${executable} klu_dl klu_di cholmod_dl cholmod_di colamd_dl colamd_di amd_dl amd_di btf_dl btf_di)  
endforeach (test)
