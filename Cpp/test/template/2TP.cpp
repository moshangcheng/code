#include <iostream>
#include <string>


//The enable_if functions
template<bool _Test, class _Type = void>
struct enable_if
{	// type is undefined for assumed !_Test
};

template<class _Type>
struct enable_if<true, _Type>
{	// type is _Type for _Test
	typedef _Type type;
};

//use template<typename C, C> to check type
//use two template parameters to implement SFINAE

#define HAS_MEM(NAME)																						\
template<typename T, typename TYPE> struct has_member_##NAME {												\
	template<typename C, C> struct type_check;																\
    template<typename C> static char (&f(type_check<TYPE C::*, &C::NAME>*))[1]; 							\
    template<typename C> static char (&f(...))[2]; 															\
    static bool const value = sizeof(f<T>(0)) == sizeof(char[1]);											\
}

#define HAS_MEM_FN(NAME)																					\
template<typename T, typename TYPE> struct has_member_fn_##NAME {											\
	template<typename C, C> struct type_check; 																\
    template<typename C> static char (&f(type_check<TYPE, &C::NAME>*))[1]; 									\
    template<typename C> static char (&f(...))[2]; 															\
    static bool const value = sizeof(f<T>(0)) == sizeof(char[1]);											\
}


struct TestStruct {
	int test_value;
	int& StrangeName (int *, std::string&, void*) const;
};

HAS_MEM(test_value);
HAS_MEM_FN(c_str);

template<typename T>
class has_member_test_value_1 : public has_member_test_value<T, int> { };

//This template class does NOT accpet NON-CLASS argument, such as int
template<typename T>
class has_member_fn_c_str_1 : public has_member_fn_c_str<T, const char* (T::*)() const> {};


int main()
{
	std::string lStr("abc");
	TestStruct lStruct;
	std::cout	<< has_member_test_value<int, int>::value << " "
				<< has_member_fn_c_str<int, int>::value << std::endl;

	std::cout	<< has_member_test_value<std::string, int>::value << " "
				<< has_member_fn_c_str<std::string, const char* (std::string::*)() const>::value << " "
				<< has_member_fn_c_str_1<std::string>::value << std::endl;

	std::cout	<< has_member_test_value<TestStruct, int>::value << " "
				<< has_member_fn_c_str<TestStruct, const char* (TestStruct::*)() const>::value << " "
				<< has_member_fn_c_str_1<TestStruct>::value << std::endl;

	return 0;
}