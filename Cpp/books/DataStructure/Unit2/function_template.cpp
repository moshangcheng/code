#include <iostream>
using namespace std;

template<class T>
void swap(T& a, T& b) {
	T c = a;
	a = b;
	b = c;
}

int main() {
	int a = 2, b = 1;
	swap(a, b);
	cout << a << " " << b << endl;
	double x = 2.1, y = 3.2;
	swap(x, y);
	cout << x << " " << y << endl;
	system("pause");
	return 0;
}

