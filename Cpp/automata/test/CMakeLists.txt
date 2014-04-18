include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(CSVParser ${CMAKE_SOURCE_DIR}/src/BooleanMatrix.h CSVParser.cpp)
add_executable(FaultToleranceCSVParser ${CMAKE_SOURCE_DIR}/src/BooleanMatrix.h FaultToleranceCSVParser.cpp)
add_executable(NoErrorCSVParser ${CMAKE_SOURCE_DIR}/src/BooleanMatrix.h NoErrorCSVParser.cpp)
add_executable(BackScanDFA ${CMAKE_SOURCE_DIR}/src/BooleanMatrix.h BackScanDFA.cpp)
add_executable(ScanDFA ${CMAKE_SOURCE_DIR}/src/BooleanMatrix.h ScanDFA.cpp)
add_executable(GenerateScanDFA ${CMAKE_SOURCE_DIR}/src/BooleanMatrix.h GenerateScanDFA.cpp)
add_executable(GenerateScanNFA ${CMAKE_SOURCE_DIR}/src/BooleanMatrix.h GenerateScanNFA.cpp)
