/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1536
 */
#include <iostream>
#include <memory.h>

using namespace std;

const int MAX = 10001;

int main() {
	int k, S[100], f[MAX], g[MAX], cookie = 1;
	memset(g, 0, sizeof(g));
	while (1) {
		cin >> k;
		if (!k)
			break;
		for (int i = 0; i < k; i++)
			cin >> S[i];
		for (int i = 0, j; i < MAX; i++, cookie++) {
			/*
			 * 计算所有i的子状态
			 */
			for (j = 0; j < k; j++)
				if (i - S[j] >= 0)
					g[f[i - S[j]]] = cookie;
			/*
			 * 计算f
			 */
			for (j = 0; g[j] == cookie; j++)
				;
			f[i] = j;
		}
		cin >> k;
		while (k--) {
			int h, j, mask = 0;
			cin >> h;
			while (h--) {
				cin >> j;
				mask ^= f[j];
			}
			cout << (mask ? "W" : "L");
		}
		cout << endl;
	}

	return 0;
}

