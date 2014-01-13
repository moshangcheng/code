# execute 'cmake -G "MinGw Makefiles" in CMD
# execute 'mingw32-make' in CMD
PROJECT (HELLO)
SET(SRC_LIST main.c)
MESSAGE(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE_DIR " ${HELLO_SOURCE_DIR})
ADD_EXECUTABLE(hello ${SRC_LIST})

