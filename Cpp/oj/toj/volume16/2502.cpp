#include <iostream>
using namespace std;

const unsigned MAX = 100001;
unsigned gen[MAX];

int main() {
	int i, j, tp, T, N;
	gen[1] = gen[0] = 0;
	for (i = 1; i < MAX; i++) {
		for (j = 1, tp = 0; j <= i; j *= 10)
			tp += i % (10 * j) / j;
		if (tp + i < MAX && gen[tp + i] == 0)
			gen[tp + i] = i;
	}
	cin >> T;
	while (T-- > 0) {
		cin >> N;
		cout << gen[N] << endl;
	}
	return 0;
}
