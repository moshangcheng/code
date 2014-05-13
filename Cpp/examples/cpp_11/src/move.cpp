#include <utility>      // std::move
#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>       // std::string

struct A {
	int v;
};

int main() {
	std::string foo = "foo-string";
	std::string bar = "bar-string";
	std::vector<std::string> myvector;

	myvector.push_back(foo);                    // copies
	myvector.push_back(std::move(bar));         // moves

	std::cout << "myvector contains:";
	for (std::string& x : myvector) std::cout << ' ' << x;
	std::cout << '\n';

	A a = { 3 };
	A&& b = std::move(a);

	std::cout << &a << " " << &b << std::endl;

	return 0;
}