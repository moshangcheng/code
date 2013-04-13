/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1864
 */
#include <cmath>
#include <memory.h>
#include <cstdio>
using namespace std;

const int MAX = 30;
const int SINGLE_CHECK_VALUE = 100000;
const int SINGLE_ITEM__VALUE = 60000;

int checkNum;
int legalCheck[MAX];
int maxSum[MAX * SINGLE_CHECK_VALUE + 1];

void init() {
	checkNum = 0;
	memset(maxSum, 0, sizeof(maxSum));
}

int main() {
	int Q, N;
	double tempQ;
	while (scanf("%lf%d", &tempQ, &N) == 2) {
		if (N == 0) {
			break;
		}
		init();
		Q = floor(tempQ * 100);
		for (int i = 0; i < N; i++) {
			int m;
			char tempType;
			double tempPrice, sum, item[3];
			sum = 0;
			for (int j = 0; j < 3; j++) {
				item[j] = 0;
			}
			scanf("%d", &m);
			for (int j = 0; j < m; j++) {
				scanf(" %c:%lf", &tempType, &tempPrice);
				if (tempType > 'C') {
					sum = SINGLE_CHECK_VALUE / 100 + 1;
					continue;
				}
				item[tempType - 'A'] += tempPrice;
				sum += tempPrice;
			}
			if (sum * 100 > SINGLE_CHECK_VALUE) {
				continue;
			}
			for (int j = 0; j <= 3; j++) {
				if (item[j] * 100 > SINGLE_ITEM__VALUE) {
					break;
				}
				if (j == 3) {
					legalCheck[checkNum++] = floor(sum * 100);
				}
			}
		}

		for (int i = 0; i < checkNum; i++) {
			int temp = legalCheck[i];
			for (int j = Q; j >= temp; j--) {
				int tempMax = temp + maxSum[j - temp];
				if (tempMax > maxSum[j])
					maxSum[j] = tempMax;
			}
		}
		printf("%.2lf\n", maxSum[Q] / 100.00);
	}
}
