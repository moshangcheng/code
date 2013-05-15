#include <iostream>

template<int T>
class TC {
public:
	static int data;
	int getData() {
		return data;
	}
};

int TC<1>::data = 1;
int TC<2>::data = 2;

int main() {
	std::cout << TC<1>::data << std::endl;
	std::cout << TC<2>::data << std::endl;
	return 0;
}