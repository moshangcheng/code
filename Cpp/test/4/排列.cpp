#include <iostream>
using namespace std;

int n;
void Perm(int* a, int m);
void Swap(int& a, int& b);

int main() {
	while (cin >> n) {
		int* a = new int[n];
		for (int i = 0; i < n; i++)
			a[i] = i + 1;
		Perm(a, 0);
		delete[] a;
	}
	return 0;
}

void Perm(int* a, int m) {
	if (m == n) {
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl;
	} else {
		for (int i = m; i < n; i++) {
			Swap(a[i], a[m]);
			Perm(a, m + 1);
			Swap(a[i], a[m]);
		}
	}
}

void Swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}

