message(STATUS "IS MSVC: ${MSVC}")

include_directories(${CMAKE_SOURCE_DIR}/curl-7.34.0-devel-mingw32/include)

if(MSVC)
	# use import library built by me
	link_directories(${CMAKE_SOURCE_DIR}/lib)
else(MSVC)
	link_directories(${CMAKE_SOURCE_DIR}/curl-7.34.0-devel-mingw32/lib)
endif(MSVC)

add_executable(gzip_test gzip_test.cpp)
add_executable(simple simple.cpp)
add_executable(10_at_a_time 10_at_a_time.cpp)

if(WIN32)
	target_link_libraries(10_at_a_time Ws2_32)
endif(WIN32)

if(MSVC)
	target_link_libraries(gzip_test libcurl)
	target_link_libraries(simple libcurl)
	target_link_libraries(10_at_a_time libcurl)
else(MSVC)
	target_link_libraries(gzip_test curl)
	target_link_libraries(simple curl)
	target_link_libraries(10_at_a_time curl)
endif(MSVC)

# install
install(TARGETS gzip_test simple 10_at_a_time
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
