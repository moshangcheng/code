/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-18 下午10:25:39
 * @brief http://acm.nankai.edu.cn/p1120.html
 */
#include <iostream>
using namespace std;

int main() {
	int N, num = 0, s1, s2;
	cin >> N;
	while (num++ < N) {
		cin >> s1 >> s2;
		if ((s1 % 2 != s2 % 2) || (s1 < s2))
			cout << "impossible\n";
		else
			cout << (s1 + s2) / 2 << " " << (s1 - s2) / 2 << endl;
	}
	return 0;
}

