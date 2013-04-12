#include <iostream>
#include <typeinfo>  //for 'typeid' to work

class Person {
public:
	// ... Person members ...
	virtual ~Person() {}
};

class Employee : public Person {
public:
	// ... Employee members ...
	int EmployeeID;
};

int main () {
	Person person;
	Employee employee;
	Person *ptr = &employee;
	// The string returned by typeid::name is implementation-defined
	std::cout << typeid(person).name() << std::endl;   // Person (statically known at compile-time)
	std::cout << typeid(employee).name() << std::endl; // Employee (statically known at compile-time)
	std::cout << typeid(ptr).name() << std::endl;      // Person * (statically known at compile-time)
	std::cout << typeid(*ptr).name() << std::endl;     // Employee (looked up dynamically at run-time
	std::cout << typeid(void*).name() << std::endl;
	std::cout << typeid((char)0).name() << std::endl;
	std::cout << typeid((char*)0).name() << std::endl;
	std::cout << typeid((double)0).name() << std::endl;
	std::cout << typeid((double*)0).name() << std::endl;
	std::cout << typeid(void(*)()).name() << std::endl;
	std::cout << (typeid(*printf) == typeid(*scanf)) << std::endl;
	std::cout << typeid(&std::string::c_str).name() << std::endl;
	std::cout << typeid(&Employee::EmployeeID).name() << std::endl;
	return 0;
}
