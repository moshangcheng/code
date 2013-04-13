#include <iostream>
using namespace std;
#include "Chain.h"
#include "LinkedStack.h"

int main() {
	int n = 0, r = 0;
	while (n < 2) {
		cout << "Enter the number of elements\n";
		cin >> n;
		if (n < 2)
			cout << "Too few elements\n";
	}
	while (r < 1) {
		cout << "Enter the number of relations\n";
		cin >> r;
		if (r < 1)
			cout << "Two few relations\n";
	}
	Chain<int>*chain = new Chain<int> [n + 1];
	for (int i = 1; i <= r; i++) {
		cout << "Enter next relation/pair\n";
		int a, b;
		cin >> a >> b;
		chain[a].Insert(0, b);
		chain[b].Insert(0, a);
	}

	LinkedStack<int> stack;
	bool*out = new bool[n + 1];
	for (int i = 1; i <= n; i++)
		out[i] = false;
	for (int i = 1; i <= n; i++)
		if (!out[i]) {
			cout << "Next class is: " << i << " ";
			out[i] = true;
			stack.Add(i);
			while (!stack.IsEmpty()) {
				int*q, j;
				stack.Delete(j);
				ChainIterator<int> c;
				q = c.Initialize(chain[j]);
				while (q) {
					if (!out[*q]) {
						cout << *q << " ";
						out[*q] = true;
						stack.Add(*q);
					}
					q = c.Next();
				}
			}
			cout << endl;
		}
	cout << endl << "End of class list" << endl;
	system("pause");
	return 0;
}

