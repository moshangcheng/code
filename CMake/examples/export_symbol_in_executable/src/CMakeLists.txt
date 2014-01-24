add_executable(main main.cpp)

set_target_properties(main PROPERTIES ENABLE_EXPORTS ON)

target_link_libraries(main hello)
