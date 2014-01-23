#include <iostream>
using namespace std;
#include "Array1D.h"

int main() {
	Array1D<int> M(5), N(5);
	for (int i = 0; i < 5; i++) {
		M[i] = i;
		N[i] = 10 - i;
	}
	M += 1;
	N = N - M;
	for (int i = 0; i < 5; i++)
		cout << N[i] << " ";
	cout << endl;
	for (int i = 0; i < 5; i++)
		cout << M[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}

