#include <iostream>
using namespace std;
#include "Queue.h"

int main() {
	int x;
	Queue<int> Q(10);
	Q.Add(1).Add(4).Add(2);
	cout << "First element is " << Q.First() << endl;
	cout << "Last element is " << Q.Last() << endl;
	Q.Delete(x);
	cout << "Element deleted is " << x << endl;
	cout << "First element is " << Q.First() << endl;
	cout << "Last element is " << Q.Last() << endl;
	system("pause");
	return 0;
}

