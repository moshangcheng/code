#include <iostream>
#include <string>

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


#define ZORBA_DECL_HAS_MEM_FN(FN_NAME)                                \
	template<typename T,typename S>                                     \
class has_##FN_NAME : public sfinae_base {                          \
	template<typename SignatureType,SignatureType> struct type_check; \
	template<class U> static yes& test(type_check<S,&U::FN_NAME>*);   \
	template<class U> static no& test(...);                           \
public:                                                             \
	static bool const value = sizeof( test<T>(0) ) == sizeof( yes );  \
}

ZORBA_DECL_HAS_MEM_FN( c_str );


void some_func(int i)
{
	std::cout << "void some_func(" << i << ")\n";
}

template <typename T> typename enable_if<has_c_str<T, char const* (T::*)() const>::value, std::string>::type some_func(T t)
{
	std::cout << "template <typename T> void some_func(T t)\n";
	return t.c_str();
}

int main()
{
	int is = 1;
	short s=12;
	std::string lStr("abc");
	some_func(s);
	std::cout << some_func(lStr) << std::endl;
	return 0;
}

