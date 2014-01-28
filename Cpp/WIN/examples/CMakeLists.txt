if(NOT MSVC)
	message(FATAL_ERROR "only MSVC is supported")
endif(NOT MSVC)

include_directories()

set(files kerberos)

foreach(file ${files})
	add_executable(${file} ${file}.cpp)
endforeach(file)

target_link_libraries(kerberos Secur32)

# install
install(TARGETS ${files}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION staticlib
	)
