project(xerces)

if(NOT MSVC)
	MESSAGE(FATAL_ERROR "only supports Windows and MSVC")
endif(NOT MSVC)

add_subdirectory(examples)
