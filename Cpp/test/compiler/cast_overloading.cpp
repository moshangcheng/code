/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:54:40
 * @brief 重载T*和const T*类型的强制转换操作符
 */
#include <iostream>
using namespace std;

template<typename T> class Ptr {
public:
	Ptr(const T& t) {
		m_ = new T(t);
	}
	~Ptr() {
		delete m_;
	}
	//返回值是T*，重载了()操作符
	operator T*() {
		return m_;
	}
	//返回值是const T*，重载了()操作符
	operator const T*() const {
		return m_;
	}

	T get() {
		return *m_;
	}
private:
	T* m_;
};

int main() {
	Ptr<int> Integer(3);
	cout << Integer.get() << endl;
	return 0;
}
