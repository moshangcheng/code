#include <memory>
#include <iostream>

template<typename T>
class A
{
public:
	A(T v): a(v) {}

	typedef std::shared_ptr<A> Ptr;
private:
	T a;
};

template<typename T>
class B
{
public:
	// user typename for disambiguation
	B(typename A<T>::Ptr a)
	{}
};

int main() {
	A<int>::Ptr a = std::make_shared<A<int>>(3);
	B<int> b(a);

	const char* lpData = "abc";
	unsigned short* lpShort1 = (unsigned short*)lpData;
	unsigned short* lpShort2 = (unsigned short*)(lpData + 1);
	std::cout << lpShort1 << (lpShort1 < lpShort2 ? " < ": " = ") << lpShort2 << "\n";

	const int c1 = 1;
	const int c2 = 2;
	const int* pc1 = &c1;
	const int* pc2 = &c2;
	const int** ppc = &pc1;
	*ppc = pc2;
	//*ppc[0] = 3;
	return 0;
}