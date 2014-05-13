### ICU

- download icu4c-53\_1-Win32-msvc10.zip[here][1]
- usage

		unzip icu4c-53\_1-Win32-msvc10.zip
		mkdir build
		cd build
		cmake -DCMAKE_INSTALL_PREFIX=../install ..
		project properties->Debugging->Environment, add "PATH=..\..\icn\bin;%PATH%"

[1]: http://download.icu-project.org/files/icu4c/53.1/icu4c-53_1-Win32-msvc10.zip

