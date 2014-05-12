set(files chain chain_call reader covariant shared_ptr typename stdstream test)

foreach(file ${files})
	add_executable(${file} ${file}.cpp) 
endforeach(file)
