#include <iostream>
#include <sstream>
#include <fstream>

// Return a named file's contents as a string
std::string load_file(char const * filepath)
{
    std::ifstream src(filepath);
    std::ostringstream buf;
    buf << src.rdbuf();
    return buf.str();
}


int main() {
	std::cout << load_file("data.xml") << std::endl;
	return 0;
}

