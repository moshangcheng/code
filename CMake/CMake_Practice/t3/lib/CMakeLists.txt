SET(LIBHELLO_SRC hello.c)

# add shared library
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})

# add static library
ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})

# set output name of static library
# SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")

#
SET_TARGET_PROPERTIES(hello PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

#
SET_TARGET_PROPERTIES(hello PROPERTIES VERSION 1.2 SOVERSION 1)

# install targets
INSTALL(TARGETS hello hello_static
	# On Windows, dll is treated as RUNTIME targets
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION staticlib)

# install header files
INSTALL(FILES hello.h DESTINATION include/hello)
