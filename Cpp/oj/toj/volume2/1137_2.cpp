//标程 
#include <iostream>
using namespace std;

const int MAX = 101;
int a[MAX], best[MAX], path[MAX][MAX];

void gen(int m) {
	if (a[m] >= MAX)
		return;
	if (m > best[a[m]])
		return;
	else if (m < best[a[m]]) {
		best[a[m]] = m;
		for (int i = 0; i <= m; i++)
			path[a[m]][i] = a[i];
	}
	for (int i = m; i >= 0; i--) {//从M开始可减少时间
		a[m + 1] = a[m] + a[i];
		gen(m + 1);
	}
}

int main() {
	memset(best, 0x7f, sizeof(best));
	a[0] = 1;
	gen(0);
	int m, i;
	while (cin >> m && m > 0) {
		for (int i = 0; i < best[m]; i++)
			cout << path[m][i] << " ";
		cout << path[m][best[m]] << endl;
	}
	return 0;
}
