/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1230.html
 */

#include <iostream>
#include <string>
using namespace std;

int Compute(string A, string B, char c) {
	int a = 0, b = 0;
	for (int i = 0; A[i] != '\0'; i++) {
		if (A[i] == c)
			a++;
		if (B[i] == c)
			b++;
	}
	return (a - b);
}

int main() {
	int Num;
	cin >> Num;
	while (Num--) {
		string Right[3], Left[3], Judge[3];
		int judge[3];
		bool Flag[12];
		for (int n = 0; n < 12; n++)
			Flag[n] = 1;

		for (int i = 0; i < 3; i++) {
			cin >> Left[i] >> Right[i] >> Judge[i];
			if (Judge[i] == "even")
				judge[i] = 0;
			if (Judge[i] == "up")
				judge[i] = 1;
			if (Judge[i] == "down")
				judge[i] = -1;
		}

		int m;
		char c;
		for (int j = 0; j < 12; j++) {
			c = char(j + 65);
			int a[3], i1, i2;
			for (int k = 0; k < 3; k++)
				a[k] = Compute(Left[k], Right[k], c);
			for (i1 = 0; i1 < 3; i1++)
				if (a[i1] != judge[i1])
					break;
			if (i1 == 3) {
				m = 1;
				break;
			}
			for (i2 = 0; i2 < 3; i2++)
				if (a[i2] != -judge[i2])
					break;
			if (i2 == 3) {
				m = -1;
				break;
			}
		}
		cout << c << " is the counterfeit coin and it is ";
		if (m == 1)
			cout << "heavy.\n";
		if (m == -1)
			cout << "light.\n";
	}
	return 0;
}

