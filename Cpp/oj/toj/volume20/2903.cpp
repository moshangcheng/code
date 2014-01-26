#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int k, a[5], mi, digit, d;
	a[0] = 1;
	for (k = 1, mi = 10; k < 5; k++, mi *= 10)
		a[k] = a[k - 1] + (mi + mi / 10 - 1) * (mi - mi / 10) * k / 2;
	int N;
	while (cin >> N && N > 0) {
		int n, sum;
		for (k = 0, mi = 1;; k++, mi *= 10)
			if (a[k + 1] > N)
				break;
		sum = a[k];
		//求出满足n(n-1)=<x<n(n+1)的n. (n-1/2)^2=<x+1/2<(n+1/2)^2
		//即n-1/2=<sqrt(x+1/2)<n+1/2
		//即n-1=<sqrt(x+1/2)-1/2<n
		//即 cell[sqrt(x+1/2-1/2]=n-1;
		n = int(sqrt(2 * (N - sum) / (k + 1) + mi * mi - mi + 0.25) - 0.5) + 1;
		sum += (k + 1) * (mi + n - 1) * (n - mi) / 2;
		//(k+1)是n的十进制位数
		d = (N - sum) % (k + 1);
		while (d-- >= 0) {
			digit = n / mi;
			n = n % mi;
			mi = mi / 10;
		}
		cout << digit << endl;
	}
	return 0;
}

