
PROJECT(csparse)

set(SUITESPARSE_CSPARSE_VERSION_MAJOR 3)
set(SUITESPARSE_CSPARSE_VERSION_MINOR 1)
set(SUITESPARSE_CSPARSE_VERSION_PATCH 2)

aux_source_directory(. SRC_LIST)
include_directories(${SRC_LIST})

set(HEADER_FILES cs.h)
#set(HEADER_FILES *.h )

add_library(csparse SHARED ${SRC_LIST})
target_link_libraries(csparse m)
