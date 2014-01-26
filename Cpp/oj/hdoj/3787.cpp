/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=3787
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int getValue(char* str, int length) {
	int value = 0;
	int isMinus = 1;
	for (int i = 0; i < length; i++) {
		if (str[i] == ',') {
			continue;
		} else if ('0' <= str[i] && str[i] <= '9') {
			value = value * 10 + str[i] - '0';
		} else if (str[i] == '-') {
			isMinus = -1;
		}
	}
	return value * isMinus;
}

int main() {
	char strA[20], strB[20];
	int A, B;
	while (scanf("%s%s", strA, strB) == 2) {
		A = getValue(strA, strlen(strA));
		B = getValue(strB, strlen(strB));
		printf("%d\n", A + B);
	}
}
