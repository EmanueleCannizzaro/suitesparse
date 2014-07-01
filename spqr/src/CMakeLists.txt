
FILE(GLOB HEADER_FILES "*.h")
FILE(GLOB SRC_LIST "*.cpp")

include_directories("${cholmod_SOURCE_DIR}")

add_library(spqr SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(spqr m)
