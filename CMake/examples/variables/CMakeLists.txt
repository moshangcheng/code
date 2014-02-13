cmake_minimum_required(VERSION 2.8)

project(variables)

# must after project(), otherwise MSVC is not set
message(STATUS "First Try, WIN32: ${WIN32}")
message(STATUS "First Try, MSVC: ${MSVC}")

# try to get environment variables
message(STATUS "Get $PATH: $ENV{PATH}")
add_subdirectory(src)

# try to get build type
message(STATUS "Get build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Get C  Flag: ${CMAKE_C_FLAGS_DEBUG}")

