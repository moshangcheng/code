/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1877
 */
#include <iostream>
#include <stack>
using namespace std;

int main() {

	unsigned int A, B, C, m;
	while (cin >> m && m > 0) {
		stack<int> s;
		cin >> A >> B;
		for (C = A + B; C > 0; C /= m)
			s.push(C % m);
		if (s.empty())
			cout << 0;
		else
			for (; !s.empty(); s.pop())
				cout << s.top();
		cout << endl;
	}
	return 0;
}
