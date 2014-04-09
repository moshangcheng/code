#include <iostream>

#include "derived.h"

#include "library.h"

DerivedTC3::DerivedTC3()
{
}

void DerivedTC3::hello()
{
	std::cout << "Derived class, the value is 3\n";
}