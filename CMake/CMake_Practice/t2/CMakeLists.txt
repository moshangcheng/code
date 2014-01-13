PROJECT(HELLO)
ADD_SUBDIRECTORY(src bin)

# install files
INSTALL(FILES COPYRIGHT README DESTINATION share/doc/cmake/t2)

# install programs
INSTALL(PROGRAMS runhello.sh DESTINATION bin)

# install directory
INSTALL(DIRECTORY doc/ DESTINATION share/doc/cmake/t2)
