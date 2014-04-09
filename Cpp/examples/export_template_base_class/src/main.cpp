#include <iostream>
#include <vector>

#include "derived.h"
#include "library.h"

int main() {
	DerivedTC3().hello();
	Foo().hello();
	return 0;
}