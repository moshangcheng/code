#pragma once

#include <iostream>

template<int T>
class TC
{
public:

	TC() {}

	virtual void hello() {
		std::cout << "the value is " << T << std::endl;
	}
};