#include <iostream>
#include <memory>

class Base {
public:
	Base(int iv)
		: v(iv)
	{}

private:
	int v;
};

class Derived: public Base {
public:
	Derived(int v)
		: Base(v)
	{}

	~Derived()
	{
		std::cout << "destructor called\n";
	}
};

int main() {
	std::shared_ptr<Derived> lSharedPtr1 = std::make_shared<Derived>(3);

	Derived* lRawPtr = new Derived(3);

	std::shared_ptr<Derived> lSharedPtr2(lRawPtr);
	std::shared_ptr<Base> lSharedPtr3 = lSharedPtr2;
	//std::shared_ptr<Base> lSharedPtr3(lRawPtr);

	return 0;
}