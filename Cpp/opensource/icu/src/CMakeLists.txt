set(ICU_DIR ${CMAKE_SOURCE_DIR}/icu)

include_directories(${ICU_DIR}/include)

set(files to_strfmt simple_converter datetime_parser)
set(libs icudt.lib icuin.lib icuio.lib icule.lib iculx.lib icutest.lib icutu.lib icuuc.lib testplug.lib)

foreach(file ${files})
    add_executable(${file} ${file}.cpp)
	foreach(lib ${libs})
		target_link_libraries(${file}
			debug ${ICU_DIR}/lib/${lib}
		)
	endforeach(lib)
endforeach(file)

# install
install(TARGETS ${files}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION staticlib
    )

# install icu library
install(DIRECTORY ${ICU_DIR}/bin/ DESTINATION bin
	PATTERN "*.exe" EXCLUDE
)
