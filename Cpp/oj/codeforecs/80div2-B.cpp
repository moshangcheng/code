/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-8-7 下午06:58:33
 * @brief cf 80 div2
 */
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
	long long n;
	while (cin >> n) {
		long long a, s = 0;
		for (int i = 0; i < n; i++) {
			cin >> a;
			s += (i + 1) * a - i;
		}
		cout << s << endl;
	}
}
