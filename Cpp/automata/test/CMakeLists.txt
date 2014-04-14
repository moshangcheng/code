include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(CSVParser ${CMAKE_SOURCE_DIR}/src/BooleanMatrix.h CSVParser.cpp)
add_executable(FaultToleranceCSVParser ${CMAKE_SOURCE_DIR}/src/BooleanMatrix.h FaultToleranceCSVParser.cpp)
add_executable(NoErrorCSVParser ${CMAKE_SOURCE_DIR}/src/BooleanMatrix.h NoErrorCSVParser.cpp)
add_executable(NFA ${CMAKE_SOURCE_DIR}/src/BooleanMatrix.h NFA.cpp)
