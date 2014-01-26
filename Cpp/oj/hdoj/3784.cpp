/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=3784
 */
#include<cstdio>
#include <memory.h>
#include <vector>
using namespace std;

const int MAX = 1001;

bool isCovered[MAX];

//这道题目有陷阱，n<1000是一个烟幕弹，计算时中间值可能很大
void visit(int n) {
	for (; n > 1;) {
		n = n % 2 ? (3 * n + 1) / 2 : n / 2;
		if (n < MAX) {//n < MAX时才能赋值，否则会越界
			isCovered[n] = 1;
		}
	}
}

int main() {
	int n;
	vector<int> number;
	while (scanf("%d", &n) == 1 && n > 0) {
		number.clear();
		memset(isCovered, 0, sizeof(isCovered));

		int tempValue;
		for (int i = 0; i < n; i++) {
			scanf("%d", &tempValue);
			if (!isCovered[tempValue]) {
				visit(tempValue);
				number.push_back(tempValue);
			}
		}

		int notCoverdNumber = 0;
		for (int i = number.size() - 1; i >= 0; i--) {
			if (!isCovered[number[i]]) {
				if (notCoverdNumber++ > 0) {
					printf(" ");
				}
				printf("%d", number[i]);
			}
		}
		printf("\n");
	}
	return 0;
}
