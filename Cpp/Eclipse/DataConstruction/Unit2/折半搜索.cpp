#include <iostream>
using namespace std;

template<class T>
int BinarySearch(T a[], const T& x, int n) {
	int left = 0, right = n - 1;
	while (left <= right) {
		int middle = (left + right) / 2;
		if (x == a[middle])
			return middle;
		else if (x > a[middle])
			left = middle + 1;
		else
			right = middle - 1;
	}
	return -1;
}

int main() {
	int n, x;
	cin >> n >> x;
	int*a = new int[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cout << BinarySearch(a, x, n) + 1 << endl;
	delete[] a;
	system("pause");
	return 0;
}

