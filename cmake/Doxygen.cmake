# Doxygen

# find doxygen package
find_package(Doxygen)

if (DOXYGEN_FOUND)
  message("found doxygen")

  # set input and output files
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

  # request to configure the file
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message("Starting doxygen build...")

  add_custom_target(doxy
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
  )
  
else (DOXYGEN_FOUND)
  message("could not find doxygen")

endif(DOXYGEN_FOUND)