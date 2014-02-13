#include <iostream>
#include <fstream>

void stream_copy(std::ostream& dst, std::istream& src)
{
    dst << src.rdbuf();
}

int main() {
	std::ifstream fin("data.xml");
	stream_copy(std::cout, fin);
	return 0;
}

