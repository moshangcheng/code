#include <iostream>
#include <math.h>
using namespace std;

const int MAX = 1000000;

int main() {
	int i, j, num = 0, sum;
	int prime[100000];
	bool isprm[1000001];
	memset(isprm, 0, 1);
	isprm[prime[num++] = 2] = 1;
	for (i = 3; i <= MAX; i++) {
		for (j = 0; prime[j] < sqrt(i); j++)
			if (i % prime[j] == 0)
				break;
		if (i % prime[j] != 0)
			isprm[prime[num++] = i] = 1;
	}
	while (cin >> sum && sum) {
		sum /= 2;
		for (i = 0; prime[i] <= sum; i++)
			if (isprm[2 * sum - prime[i]]) {
				cout << 2 * sum << " = " << prime[i] << " + " << 2 * sum
						- prime[i] << endl;
				break;
			}
	}
	return 0;
}

