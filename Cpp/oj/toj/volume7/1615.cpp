//a*n^n-n+1是满足n个人的问题的通项公式，a为任意正整数
#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int i, n, maxi, num, tmp, lower_bound;
	while (cin >> n && n >= 0) {
		n--;
		for (maxi = 0, i = 2;; i++) {
			lower_bound = floor(log(n + i) / log(i));
			if (lower_bound < i)
				break;
			if (n % i != 0)
				continue;
			tmp = (n + i) / i * (i - 1);
			for (num = 1; tmp % i == 0 && num < i; num++)
				tmp = tmp / i * (i - 1);
			if (num == i && (tmp + 1) % i == 0)
				maxi = i;
		}
		n++;
		cout << n << " coconuts, ";
		if (maxi == 0)
			cout << "no solution\n";
		else
			cout << maxi << " people and 1 monkey\n";
	}
	return 0;
}

