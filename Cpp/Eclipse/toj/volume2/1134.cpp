#include <iostream>
using namespace std;

const int Num = 6;

int main() {
	int N;
	cin >> N;
	while (N) {
		int a[13], b[Num];
		for (int i = 0; i < N; i++)
			cin >> a[i];
		for (int j = 0; j < Num; j++)
			b[j] = j;
		while (1) {
			for (int i = 0; i < Num; i++) {
				cout << a[b[i]];
				if (i < (Num - 1))
					cout << " ";
			}
			cout << endl;
			if (b[0] == (N - Num))
				break;
			for (int j = Num - 1; j > -1; j--) {
				int temp = b[j] + 1, flag = 0;
				if (b[j] < (N - 1)) {
					flag = 1;
					for (int k = 0; k < Num; k++)
						if (b[k] == temp) {
							flag = 0;
							break;
						}
				}
				if (flag == 1) {
					for (int k = j; k < Num; k++)
						b[k] = temp - j + k;
					break;
				}
			}
		}
		cin >> N;
		if (N)
			cout << endl;
	}
	return 0;
}

