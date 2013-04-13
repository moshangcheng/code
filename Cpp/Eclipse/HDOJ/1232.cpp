/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1232
 */
#include <cstdio>
using namespace std;

const int MAX = 1000;

int prt[MAX], root[MAX];

int Find(int e) {
	int j = e;
	while (!root[j])
		j = prt[j];

	int f = e;
	while (f != j) {
		int prt_f = prt[f];
		prt[f] = j;
		f = prt_f;
	}
	return j;
}

void Union(int i, int j) {
	if (prt[i] < prt[j]) {
		prt[j] += prt[i];
		root[i] = 0;
		prt[i] = j;
	} else {
		prt[i] += prt[j];
		root[j] = 0;
		prt[j] = i;
	}
}

int main() {

	int N, M, R;
	int i, tmp1, tmp2;
	while (scanf("%d", &N) && N > 0) {
		scanf("%d", &M);
		for (i = 0; i < MAX; i++) {
			prt[i] = 1;
			root[i] = 1;
		}
		for (i = 0; i < M; i++) {
			scanf("%d%d", &tmp1, &tmp2);
			tmp1 = Find(tmp1);
			tmp2 = Find(tmp2);
			if (tmp1 == tmp2)
				continue;
			Union(tmp1, tmp2);
		}
		for (R = 0, i = 1; i <= N; i++)
			if (root[i])
				R++;
		printf("%d\n", R - 1);
	}
	return 0;
}
