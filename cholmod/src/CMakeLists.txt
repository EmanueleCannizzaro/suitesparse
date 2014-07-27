
add_subdirectory(core)
add_subdirectory(blas)
add_subdirectory(cholesky)
add_subdirectory(check)
add_subdirectory(modify)
add_subdirectory(partition)
add_subdirectory(supernodal)

file(GLOB HEADER_FILES RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.h")
file(GLOB SRC_LIST RELATIVE "${PROJECT_SOURCE_DIR}/src" "*.c")

##add_library(cholmod SHARED ${SRC_LIST} ${HEADER_FILES} $<TARGET_OBJECTS:cholmod_core> $<TARGET_OBJECTS:cholmod_blas> $<TARGET_OBJECTS:cholmod_cholesky> $<TARGET_OBJECTS:cholmod_check> $<TARGET_OBJECTS:cholmod_modify> $<TARGET_OBJECTS:cholmod_partition> $<TARGET_OBJECTS:cholmod_supernodal>)
##target_link_libraries(cholmod "${suitesparse_SOURCE_DIR}/lib/x64/linux/libmetis.so" "${suitesparse_SOURCE_DIR}/lib/x64/linux/libGKlib.so" ccolamd colamd camd amd lapack blas m)

