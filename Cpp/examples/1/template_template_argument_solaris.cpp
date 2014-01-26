#include <iostream>
#include <string>
#include <list>

//use SFINAE to judge whether a class has a member

template<typename T, T> struct type_check;

#define CHECK_FN(NAME)                                                                                      \
    template<typename T, typename T1>                                                                           \
char check_fn_##NAME(type_check<T1, &T::NAME>*);                                                            \
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


