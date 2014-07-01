
file(GLOB HEADER_FILES "*.h")
file(GLOB SRC_LIST "*.c")

add_library(rbio SHARED ${SRC_LIST} ${HEADER_FILES})
target_link_libraries(rbio m)
