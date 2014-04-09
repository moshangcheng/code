#include <iostream>

#include "library1.h"

#include "derived.h"

void Foo1::hello()
{
	DerivedTC3().hello();
}