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
//use one template parameter to implement SFINAE

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


struct test_struct {
	int test_value;
	int& StrangeName (int *, std::string&, void*) const;
};

HAS_MEM(int, test_value);
HAS_MEM_FN(int&, StrangeName, (int *, std::string&, void*) const);
HAS_MEM_FN(const char*, c_str, () const);


int main()
{
	std::string lStr("abc");
	test_struct lStruct;
	std::cout << has_member_test_value<int>::value << " " << has_member_fn_StrangeName<int>::value << std::endl;
	std::cout << has_member_test_value<std::string>::value << " " << has_member_fn_StrangeName<std::string>::value << " " << has_member_fn_c_str<std::string>::value << std::endl;
	std::cout << has_member_test_value<test_struct>::value << " " << has_member_fn_StrangeName<test_struct>::value << " " << has_member_fn_c_str<test_struct>::value << std::endl;

	return 0;
}