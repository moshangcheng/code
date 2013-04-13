#include <iostream>
using namespace std;
#include "LinkedMatrix.h"

int main() {
	LinkedMatrix<int> M, N;
	cin >> M;
	M.Transpose(N);
	cout << M << endl << N << endl;
	system("pause");
	return 0;
}
