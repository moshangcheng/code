#include <iostream>
#include <string>
#include <list>

//use SFINAE to judge whether a class has a member


#define CHECK_FN(NAME)                                                                                      \
	template<typename T, typename T1>                                                                           \
	char check_fn_##NAME(std::typeof(T::NAME)*);                                                            \
	template<typename T, typename T1>                                                                           \
	int check_fn_##NAME(...);

CHECK_FN(getValue);

struct TestStruct {
	void getValue();
};

int main() {
	std::cout << sizeof(check_fn_getValue<std::string, void (std::string::*)()>(0)) << std::endl;
	std::cout << sizeof(check_fn_getValue<TestStruct, void (TestStruct::*)()>(0)) << std::endl;
	return 0;
}

