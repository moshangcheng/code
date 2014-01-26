#include <iostream>
#include <string>
#include <typeinfo>


//use static reference to check type
//because we can't get the address of operator
//so we can't check its type

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

int main() {
	std::cout << supports_iostream<std::string>::value << std::endl;
	std::cout << supports_iostream<int[3]>::value << std::endl;
	return 0;
}