set(files use_stringbuf use_mybuffer)

foreach(file ${files})
	add_executable(${file} ${file}.cpp) 
endforeach(file)
