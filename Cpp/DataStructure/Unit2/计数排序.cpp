#include <iostream>
using namespace std;

template<class T>
void Rank(T a[], int n, int r[]) {
	for (int i = 0; i < n; i++)
		r[i] = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			if (a[j] <= a[i])
				r[i]++;
			else
				r[j]++;
}

template<class T>
void Swap(T& a, T& b) {
	T c = a;
	a = b;
	b = c;
}

template<class T>
void Rearrange(T a[], int n, int r[]) {
	Rank(a, n, r);
	for (int i = 0; i < n; i++)
		while (r[i] != i) {
			int t = r[i];
			Swap(a[i], a[t]);
			Swap(r[i], r[t]);
		}
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	int*a = new int[n];
	int*r = new int[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	Rearrange(a, n, r);
	delete[] a;
	delete[] r;
	system("pause");
	return 0;
}
