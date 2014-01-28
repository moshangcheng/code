#include <iostream>
#include <string>

class sfinae_base {
protected:
  typedef char no;
  typedef char yes[2];
public:
  void suppress_all_member_functions_are_private_warning();
};

#define ZORBA_DECL_HAS_MEM_FN(FN_NAME)                                \
template<typename T,typename S>                                       \
class has_##FN_NAME : public sfinae_base {                            \
	template<typename SignatureType,SignatureType> struct type_check; \
	template<class U> static yes& test(type_check<S,&T::FN_NAME>*);   \
	template<class U> static no& test(...);                           \
public:                                                               \
	static bool const value = sizeof( test<T>(0) ) == sizeof( yes );  \
}

ZORBA_DECL_HAS_MEM_FN(c_str);

int main() {
	std::cout << has_c_str<std::string, const char* (std::string::*)() const>::value << std::endl;
	return 0;
}
