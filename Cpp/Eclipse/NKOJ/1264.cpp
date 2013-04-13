/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1264.html
 */
#include <iostream>
using namespace std;

int main() {
	int m, n;
	while (cin >> m >> n) {
		if (m == 0)
			cout << (n + 1) << endl;
		if (m == 1)
			cout << (n + 2) << endl;
		if (m == 2)
			cout << (2 * n + 3) << endl;
		if (m == 3) {
			int s = 8;
			for (int i = 0; i < n; i++)
				s *= 2;
			s -= 3;
			cout << s << endl;
		}
	}
	return 0;
}

