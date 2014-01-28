include_directories(${CMAKE_SOURCE_DIR}/curl-7.34.0-devel-mingw32/include)

if(MSVC)
	# use import library built by me
	link_directories(${CMAKE_SOURCE_DIR}/lib)
else(MSVC)
	link_directories(${CMAKE_SOURCE_DIR}/curl-7.34.0-devel-mingw32/bin)
endif(MSVC)

set(files gzip_test simple 10_at_a_time libcurl_kerberos)

foreach(file ${files})
	add_executable(${file} ${file}.cpp)
	if(MSVC)
		target_link_libraries(${file} libcurl)
	else(MSVC)
		target_link_libraries(${file} curl)
	endif(MSVC)
endforeach(file)


if(WIN32)
	target_link_libraries(10_at_a_time Ws2_32)
endif(WIN32)

# install
install(TARGETS ${files}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION staticlib
	)

# install libcurl library
if(WIN32)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/curl-7.34.0-devel-mingw32/bin/ DESTINATION bin
    	PATTERN "*.exe" EXCLUDE
	)
endif(WIN32)
