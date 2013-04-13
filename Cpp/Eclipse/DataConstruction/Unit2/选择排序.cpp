#include <iostream>
using namespace std;

template<class T>
void Swap(T& a, T& b) {
	T c = a;
	a = b;
	b = c;
}

template<class T>
void SelectionSort(T a[], int n) {
	bool sorted = false;
	for (int i = 0; i < n && !sorted; i++) {
		int pos = n - 1;
		sorted = true;
		for (int j = n - 2; j > i - 1; j--)
			if (a[pos] > a[j])
				pos = j;
			else
				sorted = false;
		Swap(a[i], a[pos]);
	}
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	int*a = new int[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	SelectionSort(a, n);
	delete[] a;
	system("pause");
	return 0;
}
