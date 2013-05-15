#include <iostream>
#include <string>

//use SFINAE to judge whether a class has a member

#define HAS_MEM(TYPE, NAME)																					\
template<typename T> struct has_member_##NAME {																\
	template<typename C, C> struct type_check;																\
    template<typename C> static char (&f(type_check<TYPE C::*, &C::NAME>*))[1]; 							\
    template<typename C> static char (&f(...))[2]; 															\
    static bool const value = sizeof(f<T>(0)) == sizeof(char[1]);											\
}

#define HAS_MEM_FN(RETURNTYPE, NAME, PARAMS)																\
template<typename T> struct has_member_fn_##NAME {															\
	template<typename C, C> struct type_check; 																\
    template<typename C> static char (&f(type_check<RETURNTYPE (C::*)PARAMS, &C::NAME>*))[1]; 				\
    template<typename C> static char (&f(...))[2]; 															\
    static bool const value = sizeof(f<T>(0)) == sizeof(char[1]);											\
}

HAS_MEM(int, value);
HAS_MEM_FN(const char*, c_str, () const);
HAS_MEM_FN(int&, StrangeName, (int *, std::string&, void*) const);


struct TestStruct {
	int value;
	int& StrangeName (int *, std::string&, void*) const;
};

int main() {
	std::cout << nullptr.
	std::cout << "type int" << (has_member_value<int>::value ? " has" : " doesn't have ") << " member value\n";
	std::cout << "type int" << (has_member_fn_c_str<int>::value ? " has" : " doesn't have ") << " member function c_str\n";
	std::cout << "type int" << (has_member_fn_StrangeName<int>::value ? " has" : " doesn't have ") << " member function StrangeName\n";

	std::cout << "type TestStruct" << (has_member_value<TestStruct>::value ? " has" : " doesn't have") << " member value\n";
	std::cout << "type TestStruct" << (has_member_fn_c_str<TestStruct>::value ? " has" : " doesn't have") << " member function c_str\n";
	std::cout << "type TestStruct" << (has_member_fn_StrangeName<TestStruct>::value ? " has" : " doesn't have ") << " member function StrangeName\n";

	std::cout << "type std::string" << (has_member_value<std::string>::value ? " has" : " doesn't have") << " member value\n";
	std::cout << "type std::string" << (has_member_fn_c_str<std::string>::value ? " has" : " doesn't have") << " member function c_str\n";
	std::cout << "type std::string" << (has_member_fn_StrangeName<std::string>::value ? " has" : " doesn't have ") << " member function StrangeName\n";
	return 0;
}