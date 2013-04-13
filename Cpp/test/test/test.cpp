#include <iostream>

template<typename T> struct HasX { 
	struct Fallback { int x; }; // introduce member name "x"
	struct Derived : T, Fallback { };

	template<typename C, C> struct ChT; 
	
	//if T has member x, there is conflict when calling &C::x
	//so the first function is called for T not have member x
	template<typename C> static char (&f(ChT<int Fallback::*, &C::x>*))[1]; 
	template<typename C> static char (&f(...))[2]; 

	static bool const value = sizeof(f<Derived>(0)) == 2;
};

template<typename T> struct has_c_str { 
	//struct Fallback { const char* c_str(); };
	//struct Derived : T, Fallback { };

	template<typename C, C> struct ChT; 

	template<typename C> static char (&f(ChT<const char*(C::*)() const, &C::c_str>*))[1]; 
	template<typename C> static char (&f(...))[2]; 

	static bool const value = sizeof(f<T>(0)) == 1;//2;
};

#define HAS_MEM_FUNC(func)													\
	template<typename T, typename Sign>									    \
struct class_has_##func {													\
	typedef char yes[1];													\
	typedef char no [2];													\
	template <typename U, U> struct type_check;								\
	template <typename _1> static yes &chk(type_check<Sign, &_1::func> *);	\
	template <typename   > static no  &chk(...);							\
	static bool const value = sizeof(chk<T>(0)) == sizeof(yes);				\
}

HAS_MEM_FUNC(c_str);

struct A { int x; };
struct B { int z; };

int main() { 
	std::cout << has_c_str<std::string>::value << std::endl; // 1
	std::cout << has_c_str<A>::value << std::endl; // 0
	std::cout << class_has_c_str<std::string, const char*(std::string::*)() const>::value << std::endl; // 1
	std::cout << class_has_c_str<A, const char*(A::*)()>::value << std::endl; // 0
	return 0;
}
