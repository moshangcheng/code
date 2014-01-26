/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1214.html
 */
#include <iostream>
using namespace std;

int main() {
	int n, temp;
	while (cin >> n && n) {
		temp = n;
		for (int i = 2; i <= temp; i++)
			if (temp % i == 0) {
				n = n / i * (i - 1);
				while (temp % i == 0)
					temp = temp / i;
			}
		cout << n << endl;
	}
	return 0;
}

