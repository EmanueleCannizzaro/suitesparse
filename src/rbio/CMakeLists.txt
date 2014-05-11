
set(SUITESPARSE_RBIO_VERSION_MAJOR 2)
set(SUITESPARSE_RBIO_VERSION_MINOR 1)
set(SUITESPARSE_RBIO_VERSION_PATCH 1)

aux_source_directory(. SRC_LIST)
include_directories(${SRC_LIST})

set(HEADER_FILES RBio.h)
#set(HEADER_FILES *.h )

add_library(rbio SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(rbio m)
