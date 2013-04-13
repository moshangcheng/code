/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-4-15 下午07:52:07
 * @brief 欧拉函数 数论
 * @details http://hi.baidu.com/cjhh314/blog/item/fb1b2fe9001c883bb80e2d49.html
 */
#include <iostream>
using namespace std;

int EulerPHI(int n) {
	int m = n;
	for (int i = 2; i * i <= m; i++) {
		if (m % i == 0) {
			n -= n / i;
			for (; m % i == 0; m /= i)
				;
		}
	}
	if (m != 1)
		n -= n / m;
	return n;
}

int main() {
	int n;
	while (cin >> n)
		cout << EulerPHI(n) << endl;
	return 0;
}
