#include <iostream>
using namespace std;

template<class T>
void Swap(T& a, T& b) {
	T c = a;
	a = b;
	b = c;
}

template<class T>
void BubbleSort(T a[], int n) {
	for (int i = 0; i < n; i++) {
		bool swapped = false;
		for (int j = 0; j < n - i - 1; j++)
			if (a[j] > a[j + 1]) {
				Swap(a[j], a[j + 1]);
				swapped = true;
			}
		if (swapped == false)
			break;
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
	BubbleSort(a, n);
	system("pause");
	return 0;
}
