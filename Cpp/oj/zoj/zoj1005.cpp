/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午04:28:55
 * @brief  http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=1005
 */
#include <iostream>

using namespace std;

int main() {
	int a, b, N;
	while (cin >> a >> b >> N) {
		if (a == N)
			cout << "fill A\n" << "pour A B\n" << "success" << endl;
		else {
			int temp = 0;
			while (temp != N) {
				cout << "fill A" << endl;
				cout << "pour A B" << endl;
				temp += a;
				if (temp > b) {
					temp -= b;
					cout << "empty B" << endl;
					cout << "pour A B" << endl;
				}
			}
			cout << "success" << endl;
		}
	}
	return 0;
}
