/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-8-24 上午10:42:50
 * @brief
 */

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

class A {
private:
	int v;
public:
	A() {
		this->v = 0;
		cout << "调用A的默认构造函数\n";
	}
	A(int v) {
		this->v = v;
		cout << "调用A的构造函数\n";
	}
	A(const A& a) {
		this->v = a.v;
		cout << "调用A的拷贝构造函数\n";
	}
	void operator = (const A& a) {
		this->v = a.v;
		cout << "调用A的赋值操作符\n";
	}
};

class B {
private:
	A v;
public:
	B() {
		cout << "调用B的默认构造函数\n";
	}
	B(const A& a) {
		this->v = a;
		cout << "调用B的构造函数\n";
	}
};


A testFunc() {
	A a(4);
	return a;
}

int main() {
	//调用A的构造函数
	A a(3);
	//先调用A的默认构造函数初始化b.v
	//然后调用A的赋值操作符为b.v赋值
	//最后完成B的构造函数的调用
	B b(a);
	//函数返回a，a被赋值给一个临时变量，函数的返回值是此临时变量
	//A funcA = testFunc()语句调用1次构造函数、2次拷贝构造函数
	//A funcA; funcA = testFunc()语句调用1次默认构造函数、1次构造函数、1次拷贝构造函数，1次赋值运算符
	//经过编译器优化后，如gcc，第一种情形只调用了1次构造函数；
	//vc调用了1次构造函数、1次拷贝构造函数
	//相比vc，gcc将funcA对象和testFunc()内的a对象优化成一个对象了。
	//第二种情形，gcc编译下调用了1次默认构造函数、1次构造函数、1次赋值运算符；
	//vc调用了1次默认构造函数、1次构造函数，1次拷贝构造函数、1次赋值运算符。
	//相比vc，gcc将调用拷贝构造函数初始化临时变量的操作优化掉了。
	A funcA = testFunc();
	return 0;
}
