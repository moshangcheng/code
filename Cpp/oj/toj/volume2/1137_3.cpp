//用来产生1-MAX之间所有数的可能序列的个数 
#include <iostream>
using namespace std;

const int MAX = 21;
int a[MAX], num[MAX];

void gen(int m) {
	if (m >= MAX || a[m] >= MAX)
		return;
	num[a[m]]++;
	for (int i = 1; i <= m; i++) {
		a[m + 1] = a[m] + a[i];
		gen(m + 1);
	}
}

int main() {
	memset(num, 0, sizeof(num));
	a[1] = 1;
	gen(1);

	for (int i = 1; i < MAX; i++)
		cout << i << " " << num[i] << endl;
	system("pause");
	return 0;
}
