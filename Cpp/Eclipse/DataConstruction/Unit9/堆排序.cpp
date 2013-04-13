#include <iostream>
using namespace std;
#include "MaxHeap.h"

template<class T>
void HeapSort(T a[], int n) {
	MaxHeap<T> H(1);
	H.Initialize(a, n, n);
	T x;
	for (int i = n - 1; i > 0; i--) {
		H.DeleteMax(x);
		a[i + 1] = x;
	}
	H.Deactivate();
}

int main() {
	int n;
	cin >> n;
	int*a = new int[n + 1];
	for (int i = 1; i < n + 1; i++)
		cin >> a[i];
	HeapSort(a, n);
	for (int i = 1; i < n + 1; i++)
		cout << a[i] << " ";
	cout << endl;
	system("pause");
	delete[] a;
	return 0;
}
