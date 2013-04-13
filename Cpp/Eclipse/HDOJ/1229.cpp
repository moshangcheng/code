/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1229
 */
#include <iostream>
using namespace std;

bool compare(int m, int n, int k) {
	int i;
	for (i = 0; (m % 10 == n % 10) && i < k; m /= 10, n /= 10, i++)
		;
	return (i < k);
}

int main() {
	int A, B, K;
	while (cin >> A >> B >> K) {
		if (A == 0 && B == 0)
			break;
		if (compare(A, B, K))
			cout << A + B << endl;
		else
			cout << -1 << endl;
	}
	return 0;
}
