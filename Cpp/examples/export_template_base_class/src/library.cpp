#include <iostream>

#include "library.h"

#include <vector>

#include "template.h"

void Foo::hello()
{
	//std::vector<int> v;
	TC<3>().hello();
}