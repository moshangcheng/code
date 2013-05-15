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

class sfinae_base {
protected:
	typedef char no;
	typedef char yes[2];
public:
	void suppress_all_member_functions_are_private_warning();
};

#define HAS_MEM(NAME)																		\
template<typename T, typename MEM_TYPE> struct has_member_##NAME {							\
	struct Fallback { MEM_TYPE NAME; };														\
    struct Derived : T, Fallback { };														\
    template<typename C, C> struct type_check; 												\
	/*check whether type of "C::X" is "MEM_TYPE Fallback::*"*/								\
    template<typename C> static char (&f(type_check<MEM_TYPE Fallback::*, &C::NAME>*))[1]; 	\
    template<typename C> static char (&f(...))[2]; 											\
    static bool const value = sizeof(f<Derived>(0)) == sizeof(char[2]);						\
}

#define HAS_MEM_FN(NAME)																	\
template<typename T, typename MEM_TYPE> struct has_member_fn_##NAME { 						\
    template<typename C, C> struct type_check; 												\
    template<typename C> static char (&f(type_check<MEM_TYPE, &C::NAME>*))[1]; 				\
    template<typename C> static char (&f(...))[2]; 											\
    static bool const value = sizeof(f<T>(0)) == sizeof(char[1]);							\
}

#define HAS_MEM1(NAME)																		\
template<typename T, typename MEM_TYPE> struct has_member1_##NAME {							\
    template<typename C, C> struct type_check; 												\
	/*check whether type of "C::X" is "MEM_TYPE Fallback::*"*/								\
    template<typename C> static char (&f(type_check<MEM_TYPE, &C::NAME>*))[1]; 				\
    template<typename C> static char (&f(...))[2]; 											\
    static bool const value = sizeof(f<T>(0)) == sizeof(char[1]);							\
}

#define HAS_MEM_FN1(RETURNTYPE, NAME, PARAMS)																\
template<typename T> struct has_member_fn1_##NAME {															\
	template<typename C, C> struct type_check; 																\
    template<typename C> static char (&f(type_check<RETURNTYPE (T::*)PARAMS, &C::NAME>*))[1]; 				\
    template<typename C> static char (&f(...))[2]; 															\
    static bool const value = sizeof(f<T>(0)) == sizeof(char[1]);											\
}


HAS_MEM(test_value);
HAS_MEM1(test_value);
HAS_MEM_FN(c_str);
HAS_MEM_FN1(const char*, c_str, () const);
HAS_MEM_FN1(int, StrangeName, (int *, void *) const);

struct test_struct {
	int test_value;
	int StrangeName (int *, void *) const;
};

template<typename T>
class has_member_test_value_int : public has_member1_test_value<T, int> {};

template<typename T>
class has_member_fn_c_str_const_pc : public has_member_fn_c_str<T, const char*(T::*)() const> {};

int main()
{
	std::string lStr("abc");
	test_struct lStruct;

	//std::cout << has_member_fn_c_str<int, void>::value << std::endl;
	//std::cout << has_member1_test_value<int, void>::value << std::endl;
	//std::cout << has_member_fn_c_str<std::string, const char* (std::string::*)() const>::value << std::endl;
	//std::cout << has_member1_test_value<test_struct, int test_struct::*>::value << std::endl;

	std::cout << has_member_fn1_c_str<std::string>::value << std::endl;
	std::cout << has_member_fn1_c_str<test_struct>::value << std::endl;
	std::cout << has_member_fn1_StrangeName<std::string>::value << std::endl;
	std::cout << has_member_fn1_StrangeName<test_struct>::value << std::endl;


	//std::cout << has_member_test_value<int, int>::value << std::endl;
	//std::cout << has_member1_test_value<int, int>::value << std::endl;
	//std::cout << has_member_test_value_int<std::string>::value << std::endl;
	//std::cout << has_member_fn_c_str<std::string, const char*(std::string::*)() const>::value << std::endl;
	//std::cout << has_member_fn_c_str_const_pc<std::string>::value << std::endl;
	//std::cout << has_member_test_value<test_struct, int>::value << std::endl;
	//std::cout << has_member_test_value_int<test_struct>::value << std::endl;
	//std::cout << has_member_fn_c_str<test_struct, const char*(test_struct::*)() const>::value << std::endl;
	//std::cout << has_member_fn_c_str_const_pc<test_struct>::value << std::endl;
	return 0;
}