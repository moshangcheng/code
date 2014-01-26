/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1081.html
 */
#include <iostream>
#include <string>
using namespace std;

int main() {
	string C1, C2;
	while (cin >> C1 >> C2) {
		int i, j = 0;
		for (i = 0; C1[i] != '\0'; i++) {
			bool flag = 0;
			while (C2[j] != '\0')
				if (C1[i] == C2[j++]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				break;
		}
		if (C1[i] == '\0')
			cout << "Yes\n";
		else
			cout << "No\n";
	}
	return 0;
}

