#include <iostream>
#include <string>
#include <typeinfo>

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
    template<class U> static yes& test(type_check<S,&U::FN_NAME>*);   \
    template<class U> static no& test(...);                           \
public:                                                               \
    static bool const value = sizeof( test<T>(0) ) == sizeof( yes );  \
}

ZORBA_DECL_HAS_MEM_FN(c_str);

int main() {
   typedef const char* (std::string::*my_c_str)() const;
   my_c_str lpFn = &std::string::c_str;
   std::cout << typeid(my_c_str).name() << std::endl;
   std::cout << typeid(&std::string::c_str).name() << std::endl;
   std::cout << has_c_str<int, int>::value << std::endl;
   std::cout << has_c_str<std::string, const char* (std::string::*)() const>::value << std::endl;
   std::cout << has_c_str<std::pair<int, int>, const char* (std::pair<int, int>::*)() const>::value << std::endl;
   return 0;
}
