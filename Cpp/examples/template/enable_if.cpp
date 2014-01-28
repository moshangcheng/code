#include <iostream>
#include <string>

//The enable_if functions
template<bool _Test, class _Type = void>
struct enable_if
{       // type is undefined for assumed !_Test
};

template<class _Type>
struct enable_if<true, _Type>
{       // type is _Type for _Test
        typedef _Type type;
};

template <typename T>
struct remove_const
{
        typedef T type;
};

template <typename T>
struct remove_const<const T>
{
        typedef T type;
};

template <typename T>
struct remove_volatile
{
        typedef T type;
};

template <typename T>
struct remove_volatile<volatile T>
{
        typedef T type;
};

template <typename T>
struct remove_cv : remove_const<typename remove_volatile<T>::type> {};

template <typename T>
struct is_unqualified_pointer
{
        enum { value = false };
};

template <typename T>
struct is_unqualified_pointer<T*>
{
        enum { value = true };
};

template <typename T>
struct is_pointer : is_unqualified_pointer<typename remove_cv<T>::type> {};

template<bool T1, bool T2 = true, bool T3 = true, bool T4 = true>
struct eval_bool_expression_and
{
  static const bool value = T1 && T2 && T3 && T4;
};

template<bool T1, bool T2 = false, bool T3 = false, bool T4 = false>
struct eval_bool_expression_or
{
  static const bool value = T1 || T2 || T3 || T4;
};

template<bool T1>
struct eval_bool_expression_not
{
  static const bool value = !T1;
};

namespace private_impl {
        typedef char yes;
        typedef char (&no)[2];

        //if template argument doesn't support "<<" or ">>"
        //it's converted anyx to avoid compilation error
        struct anyx { template <class T> anyx(const T &); };

        no operator << (const anyx &, const anyx &);
        no operator >> (const anyx &, const anyx &);


        template <class T> yes check(T const&);
        no check(no);

        template <typename StreamType, typename T>
        struct has_loading_support {
                static StreamType & stream;
                static T & x;
                static const bool value = sizeof(check(stream >> x)) == sizeof(yes);
        };

        template <typename StreamType, typename T>
        struct has_saving_support {
                static StreamType & stream;
                static T & x;
                static const bool value = sizeof(check(stream << x)) == sizeof(yes);
        };

        template <typename StreamType, typename T>
        struct has_stream_operators {
                static const bool can_load = has_loading_support<StreamType, T>::value;
                static const bool can_save = has_saving_support<StreamType, T>::value;
                static const bool value = can_load && can_save;
        };
}

template<typename T>
struct supports_iostream : private_impl::has_stream_operators<std::iostream, T> {};

template<typename T>
typename enable_if<is_pointer<T>::value, void>::type print()
{
        std::cout << "pointer\n";
}

template<typename T>
typename enable_if<eval_bool_expression_and<eval_bool_expression_not<is_pointer<T>::value>::value, supports_iostream<T>::value>::value, void>::type print()
{
        std::cout << "non-pointer and supports stream\n";
}




int main() {
        int lInt = 3;
        /*std::cout << is_pointer<int>::value << std::endl;
        std::cout << is_pointer<int*>::value << std::endl;
        std::cout << is_pointer<const int*>::value << std::endl;
        std::cout << is_pointer<int* const>::value << std::endl;
        std::cout << eval_bool_expression<!is_pointer<int* const>::value, 0, 1 & 0, 1>::value << std::endl;*/
        enable_if<!is_pointer<int* const>::value, std::string> a;
        //std::cout << supports_iostream<std::string>::value << std::endl;
        print<int*>();
        print<std::string>();
        return 0;
}
