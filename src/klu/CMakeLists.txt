
PROJECT(klu)

set(SUITESPARSE_KLU_VERSION_MAJOR 1)
set(SUITESPARSE_KLU_VERSION_MINOR 2)
set(SUITESPARSE_KLU_VERSION_PATCH 1)

include_directories(../amd)
include_directories(../colamd)
include_directories(../btf)

FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.c")

add_library(klu_di SHARED ${SRC_LIST} ${HEADER_FILES})
#set_target_properties(klu_di PROPERTIES COMPILE_FLAGS "-DDLONG=OFF")
target_link_libraries(klu_di btf_di cholmod_di colamd_di amd_di m)

add_library(klu_dl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(klu_dl PROPERTIES COMPILE_FLAGS "-DDLONG=ON")
target_link_libraries(klu_dl btf_dl cholmod_dl colamd_dl amd_dl m)

add_library(klu_zi SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(klu_zi PROPERTIES COMPILE_FLAGS "-DCOMPLEX=ON")
#target_link_libraries(klu_zi btf_zi m)
target_link_libraries(klu_zi btf_di cholmod_di colamd_di amd_di m)

add_library(klu_zl SHARED ${SRC_LIST} ${HEADER_FILES})
set_target_properties(klu_zl PROPERTIES COMPILE_FLAGS "-DCOMPLEX=ON -DDLONG=ON")
#target_link_libraries(klu_zl btf_zl m)
target_link_libraries(klu_zi btf_dl cholmod_dl colamd_dl amd_dl m)
