#include <type_traits>

template<typename T, bool DisableB = std::is_fundamental<T>::value>
struct HasOperatorMemberAccessor
{ 
private:
	typedef char no;
	struct yes { no m[2]; };

	struct ambiguator { char* operator ->() { return nullptr; } };
	struct combined : T, ambiguator { };
	static combined* make();

	template<typename U, U> struct check_impl;

	template<typename U, U> struct CheckType
	{
		static bool const value = 1;
	};

	template<typename U, yes> struct CheckType
	{
		static bool const value = 0;
	};

	template<typename U>
	static no check(
		U*,
		check_impl<char* (ambiguator::*)(), &U::operator ->>* = nullptr
		);
	static yes check(...);

public:
	static bool const value=CheckType<yes, check(make())>::value;
};

// false for fundamental types, else the definition of combined will fail
template<typename T>
struct HasOperatorMemberAccessor<T, true> : std::false_type { };

// true for non-void pointers
template<typename T>
struct HasOperatorMemberAccessor<T*, false> :
	std::integral_constant<
	bool,
	!std::is_same<typename std::remove_cv<T>::type, void>::value
	>
{ };

template<typename X>
struct PointerX
{
	X* operator ->() const { return nullptr; }
};

struct X { };

int main()
{
	static_assert(
		HasOperatorMemberAccessor<PointerX<bool>>::value,
		"PointerX<> has operator->"
		);
	static_assert(
		!HasOperatorMemberAccessor<X>::value,
		"X has no operator->"
		);
	static_assert(
		HasOperatorMemberAccessor<int*>::value,
		"int* is dereferencable"
		);
	static_assert(
		!HasOperatorMemberAccessor<int>::value,
		"int is not dereferencable"
		);
	static_assert(
		!HasOperatorMemberAccessor<void*>::value,
		"void* is not dereferencable"
		);
}
