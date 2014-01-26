/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-28 下午03:35:48
 * @brief http://acm.nankai.edu.cn/p1038.html
 */

#include <iostream>
using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	while (N) {
		int a[13], b[6];
		for (int i = 0; i < N; i++)
			scanf("%d", &a[i]);
		for (int j = 0; j < 6; j++)
			b[j] = j;
		while (1) {
			for (int i = 0; i < 5; i++)
				printf("%d ", a[b[i]]);
			printf("%d\n", a[b[5]]);
			if (b[0] == (N - 6))
				break;
			int j, temp;
			for (j = 5; j > -1; j--) {
				temp = b[j] + 1;
				if (temp < N && (j == 5 || j < 5 && b[j + 1] != temp))
					break;
			}
			for (int k = j; k < 6; k++)
				b[k] = temp + k - j;
		}
		scanf("%d", &N);
		if (N)
			printf("\n");
	}
	return 0;
}
