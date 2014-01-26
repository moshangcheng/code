#include <iostream>
using namespace std;

class Base//基类 
{
public:
	Base(int x = 0);//基类的构造函数，带缺省参数
	Base(Base &x);//基类的拷贝构造函数
	int Getb() {
		return b;
	}
private:
	int b;//基类的数据

};

class Drived: public Base//派生类
{
public:
	Drived(int x = 0, int y = 0);//派生类的构造函数，带缺省参数
	Drived(Drived &x);//派生类的拷贝构造函数
	int Getd() {
		return d;
	}
private:
	int d;//派生类的数据
};

Base::Base(int x) :
	b(x)//基类的构造函数实现
{
}
Base::Base(Base &x) :
	b(x.b)//基类的拷贝构造函数实现
{
}

Drived::Drived(int x, int y) :
	Base(x), d(y)//派生类的构造函数的实现
{
}
Drived::Drived(Drived &x) :
	Base(x), d(x.d)//派生类的拷贝构造函数的实现
{
}

int main() {
	Base bx(3), by;
	Drived dx(1, 2), dy = dx;
	cout << dy.Getd() << endl;
	cout << dy.Getb() << endl;
	system("pause");
	return 0;
}

