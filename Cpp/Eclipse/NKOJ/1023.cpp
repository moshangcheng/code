/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1023.html
 */
#include <iostream>
#include <strstream>
#include <string>
using namespace std;

int main() {
	char c[1500];
	while (cin.getline(c, 1499, '\n')) {
		int x, S = 0;
		istrstream C(c);
		while (C >> x)
			S += x;
		cout << S << endl;
	}
	return 0;
}

