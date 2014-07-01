find_package(Doxygen)

if (NOT DOXYGEN_FOUND)
  message(FATAL_ERROR "Doxygen is needed to build the documentation. Please install it.")
endif (NOT DOXYGEN_FOUND)

if (DOXYGEN_FOUND)
  configure_file(Doxyfile.in ${PROJECT_SOURCE_DIR}/doc/Doxyfile  @ONLY IMMEDIATE)
  add_custom_target(UMFPACK_DOC ALL COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/doc/Doxyfile SOURCES)
endif(DOXYGEN_FOUND)
