#include<iostream>
using namespace std;

bool check(int i, int j) {
	int start = 0;
	j--;
	for (int leng = 2 * i; leng > i; leng--) {
		start = (start + j) % leng;
		if (start < i)
			return false;
	}
	return true;
}
int main() {
	int i, j;
	int a[13];
	for (i = 1; i < 14; i++) {
		for (j = i + 1;; j++)
			if (check(i, j))
				break;
		a[i - 1] = j;
	}
	while (cin >> i && i != 0)
		cout << a[i - 1] << endl;
	return 0;
}
