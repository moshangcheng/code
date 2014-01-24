project(variables)

# must after project(), otherwise MSVC is not set
message(STATUS "First Try, WIN32: ${WIN32}")
message(STATUS "First Try, MSVC: ${MSVC}")

add_subdirectory(src)
