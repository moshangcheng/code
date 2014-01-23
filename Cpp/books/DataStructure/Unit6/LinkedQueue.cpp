#include <iostream>
using namespace std;
#include "LinkedQueue.h"

int main() {
	int x;
	LinkedQueue<int> L;
	L.Add(3).Add(8).Add(4).Add(2);
	cout << "First element is " << L.First() << endl;
	cout << "Last element is " << L.Last() << endl;
	L.Delete(x);
	cout << "Element deleted is " << x << endl;
	cout << "First element is " << L.First() << endl;
	cout << "Last element is " << L.Last() << endl;
	system("pause");
	return 0;
}

