#include <iostream>
using namespace std;
#include "LinkedStack.h"

int main() {
	int x;
	LinkedStack<int> L;
	L.Add(2).Add(1).Add(8);
	cout << " Top element is " << L.Top() << endl;
	L.Delete(x);
	cout << " Element deleted is " << x << endl;
	cout << " Top element is " << L.Top() << endl;
	system("pause");
	return 0;
}
