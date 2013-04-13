/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-26 上午11:32:13
 * @brief http://acm.nankai.edu.cn/p1427.html
 */

#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n;
	double k;
	while (cin >> n) {
		k = log2(n);
		n = int(k);
		if (n < k)
			n += 1;
		cout << n << endl;
	}
	return 0;
}
