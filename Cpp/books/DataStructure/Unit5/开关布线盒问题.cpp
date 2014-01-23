#include <iostream>
#include "Stack.h"
using namespace std;

bool CheckBox(int*net, int n) {
	Stack<int>*s = new Stack<int> (n);
	for (int i = 0; i < n; i++)
		if (!s->IsEmpty()) {
			if (net[i] = net[s->Top()]) {
				int x;
				s->Delete(x);
			} else
				s->Add(i);
		} else
			s->Add(i);
	if (s->IsEmpty()) {
		delete s;
		cout << "Switch box is routable" << endl;
		return true;
	}
	delete s;
	cout << "Switch box is not routable" << endl;
	return false;
}

int main() {
	int n;
	cout << "Enter the number of pin\n";
	cin >> n;
	int*net = new int[n];
	cout << "Enter groups of pins\n";
	for (int i = 0; i < n; i++)
		cin >> net[i];
	CheckBox(net, n);
	delete[] net;
	system("pause");
	return 0;
}

