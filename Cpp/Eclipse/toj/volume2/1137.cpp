//用来产生1-MAX之间所有数的最短序列长度及其可能个数 
#include <iostream>
using namespace std;

const int MAX = 101;
int a[MAX], num[MAX], best[MAX];

void gen(int m) {
	if (a[m] >= MAX)
		return;
	if (m == best[a[m]])
		num[a[m]]++;
	else if (m < best[a[m]]) {
		best[a[m]] = m;
		num[a[m]] = 1;
	} else
		return;
	for (int i = m; i >= 1; i--) {
		a[m + 1] = a[m] + a[i];
		gen(m + 1);
	}
}

int main() {
	memset(num, 0, sizeof(num));
	memset(best, 0x7f, sizeof(best));
	a[1] = 1;
	gen(1);

	for (int i = 1; i < MAX; i++)
		cout << i << " " << best[i] << " " << num[i] << endl;
	system("pause");
	return 0;
}
