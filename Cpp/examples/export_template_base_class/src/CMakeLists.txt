add_library(derived SHARED exports.h template.h derived.h derived.cpp)
add_library(library STATIC exports.h template.h library.h library.cpp)
add_executable(main exports.h main.cpp)

set_target_properties(derived PROPERTIES COMPILE_DEFINITIONS "DERIVED_EXPORTS")
set_target_properties(library PROPERTIES COMPILE_DEFINITIONS "LIBRARY_EXPORTS")

# target_link_libraries(library derived)
# target_link_libraries(derived library)
target_link_libraries(main library derived)
