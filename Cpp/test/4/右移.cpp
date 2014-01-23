#include <iostream>
using namespace std;

//循环右移模板函数，可用于整数 
template<class T>
T xunhuan_r(T a, unsigned n) {
	T b = a << (sizeof(T) * 8 - n);
	T c = a >> n;
	return c | b;
}

/*inline unsigned xunhuan_l(unsigned a, unsigned n)
 {
 unsigned len, b, c;
 for(len = 31; a & (1<<len) == 0; len--);
 n %= len+1;
 b = a >> (len+1 - n);
 c = a << n;
 return c|b;
 }*/

//循环左移模板函数，可用于整数
template<class T>
T xunhuan_l(T a, unsigned n) {
	T b = a >> (sizeof(T) * 8 - n);
	T c = a << n;
	return c | b;
}

int main() {
	short a;
	unsigned n;
	while (cin >> a >> n) {
		cout << (a << n) << " " << (a >> n) << endl;
		//cout << xunhuan_r(a, n) << " " << xunhuan_l(a, n)<< endl;
	}
	return 0;
}
