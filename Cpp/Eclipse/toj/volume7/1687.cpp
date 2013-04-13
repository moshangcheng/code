#include <stdio.h>

char s[1000000];
int p[1000000], period[1000000];

int main() {
	int i, j, n, ntest = 0;
	while (scanf("%d", &n) == 1 && n > 0) {
		scanf("%s", s);
		printf("Test case #%d\n", ++ntest);
		period[0] = 1;
		p[0] = -1;
		for (j = -1, i = 1; i < n; i++) {
			while (j > -1 && s[j + 1] != s[i])
				j = p[j];
			if (s[j + 1] == s[i])
				j++;
			p[i] = j;
			if (j == -1)
				period[i] = i + 1;
			else if (period[i - j - 1] != period[j])
				period[i] = i + 1;
			else {
				period[i] = period[j];
				printf("%d %d\n", i + 1, (i + 1) / period[i]);
			}
		}
		printf("\n");
	}
	return 0;
}
