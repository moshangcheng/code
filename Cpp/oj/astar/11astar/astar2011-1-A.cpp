#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int SIZE = 100001;

int number[SIZE];

int main() {
	int n, m, min, max, sum;
	while (scanf("%d%d", &n, &m) == 2) {
		for (int i = 0; i < m; i++) {
			scanf("%d", number + i);
		}

		sort(number, number + m);

		sum = 0;
		int cntLen = m, leftLen = 0;
		while (cntLen > 0) {
			min = number[m - cntLen];
			max = number[m - 1];
			sum += (min - 1) * cntLen * cntLen + cntLen * leftLen;
			leftLen = cntLen;
			for (int i = m - cntLen; i < m; i++) {
				number[i] -= min;
				if (number[i] == 0)
					cntLen--;
			}
		}
		printf("%d\n", sum);
	}
	return 0;
}
