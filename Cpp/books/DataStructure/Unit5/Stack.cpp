#include <iostream>
#include "Stack.h"
using namespace std;

int main() {
	int x;
	Stack<int> S(9);
	S.Add(3).Add(5).Add(9);
	cout << " Top element is " << S.Top() << endl;
	S.Delete(x);
	cout << " Element deleted is " << x << endl;
	cout << " Top element is " << S.Top() << endl;
	system("pause");
	return 0;
}

