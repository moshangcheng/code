#include <iostream>
#include <sstream>
#include <vector>
struct D {
	int data;
};

int main() {
	std::vector<int> intv;
	intv.push_back(4);
	std::vector<int>::iterator iter = intv.begin();
	intv.erase(iter);
	--iter;
	return 0;
}
