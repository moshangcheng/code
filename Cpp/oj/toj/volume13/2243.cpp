#include <iostream>
using namespace std;

int main() {
	int i, n;
	while (cin >> n && n > 0) {
		for (i = 1; n > 1; i++)
			if ((n & 1) == 1)
				n = 3 * n + 1;
			else
				n = n / 2;
		cout << i << endl;
	}
	return 0;
}
