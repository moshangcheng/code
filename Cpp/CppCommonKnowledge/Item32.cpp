/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-8-23 上午08:49:07
 * @brief C++必知必会 条款32 禁止复制
 */
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

class NoCopy {
public:
	NoCopy(int) {}
private:
	NoCopy(const NoCopy&);
	NoCopy& operator =(const NoCopy&);
};

int main() {
	NoCopy a(12);
	//NoCopy b(a);编译错误！调用拷贝构造函数
	//NoCopy b = a;编译错误！调用赋值操作符
	return 0;
}
