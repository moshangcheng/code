#include <iostream>
using namespace std;

template<class T>
T Honor(T coeff[], int n, const T& x) {
	T value = coeff[n];
	for (int i = 1; i <= n; i++)
		value = value * x + coeff[n - i];
	return value;
}

int main() {
	int n, x;
	cin >> n;
	int*a = new int[n + 1];
	for (int i = 0; i <= n; i++)
		cin >> a[i];
	cin >> x;
	cout << Honor(a, n, x) << endl;
	delete[] a;
	system("pause");
	return 0;
}

