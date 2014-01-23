/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-8-23 上午09:00:19
 * @brief  C++必知必会 条款34 禁止或强制堆分配
 */

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

class NoHeap {
public:
protected:
	//如果NoHeap类不打算用做基类，new和delete操作符可以声明为private
	//否则，可以声明为protected
	void *operator new(size_t) {
		return NULL;
	}
	void operator delete(void*) {
	}
private:
	void* operator new[](size_t);
	void operator delete[](void*);
};

class OnHeap {
private:
	//OnHeap();
	~OnHeap();
public:
	OnHeap();
	void destroy() {
		delete this;
	}
};

int main() {
	NoHeap* nh;
	//nh = new NoHeap;编译错误!new操作符是protected
	//delete nh;编译错误！delete操作符是protected
	NoHeap* nhArray;
	//nhArray = new NoHeap[3];编译错误！new[]操作符是private
	//delete [] nhArray;编译错误！delete[]操作符是private
	//OnHeap oh;编译错误！析构函数是private
	return 0;
}
