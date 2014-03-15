set(XERCES_DIR ${CMAKE_SOURCE_DIR}/xerces-c-3.1.1-x86-windows-vc-10.0)

include_directories(${XERCES_DIR}/include)

set(files stdin_parser file_parser)

foreach(file ${files})
	add_executable(${file} ${file}.cpp)
	target_link_libraries(${file}
		debug ${XERCES_DIR}/lib/xerces-c_3D.lib
		optimized ${XERCES_DIR}/lib/xerces-c_3.lib
	)
endforeach(file)

# install
install(TARGETS ${files}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION staticlib
	)

# install xerces library
install(FILES ${XERCES_DIR}/bin/xerces-c_3_1D.dll DESTINATION bin
	CONFIGURATIONS Debug
)

install(FILES ${XERCES_DIR}/bin/xerces-c_3_1.dll DESTINATION bin
	CONFIGURATIONS Release
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/examples/data DESTINATION bin)

