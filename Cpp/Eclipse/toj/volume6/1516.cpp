#include <iostream>
using namespace std;

int main() {
	int n, d, u, sum, m;
	while (cin >> n >> u >> d && n > 0) {
		for (m = 1, sum = u; sum < n; m++)
			sum += u - d;
		cout << 2 * m - 1 << endl;
	}
	return 0;
}

